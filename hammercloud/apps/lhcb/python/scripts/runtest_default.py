from datetime import datetime,timedelta
from urllib2 import URLError,HTTPError,Request,urlopen

from django.db.models import Count
from hc.lhcb.models import Test,TestState,Site,Result,SummaryTest,SummaryTestSite,Metric,TestMetric,SiteMetric,MetricType,TestLog,SummaryEvolution

from hc.core.utils.hc.stats import Stats
from numpy import *

import sys,time,random
import numpy
import types

from Ganga.Core.GangaThread import GangaThread
from Ganga.Utility.logging import getLogger
logger = getLogger()

##
## CHECK IF WE HAVE RECEIVED TESTID
##

try:
  testid = int(sys.argv[1])
except IndexError:
  print '  ERROR! Test ID required.'
  sys.exit()

## 
## EXTRACT TEST OBJECT FROM DB
##

try:
  test = Test.objects.get(pk=testid)
  if test.pause:
    logger.info('Un-pausing test.')
    test.pause = 0
    test.save()
    comment = 'Test modifications: pause -> False,'
    testlog = TestLog(test=test,comment=comment,user='gangarbt')
    testlog.save()
except:
  print ' ERROR! Could not extract Test %s from DB'%(testid)

value_types = {'DateTimeField':[]}

for rfield in Result._meta.fields:
  if rfield.__class__.__name__ == 'DateTimeField':
    value_types['DateTimeField'] += [rfield.name]


##
## AUXILIAR FUNTIONS
##

def test_active():

  # Replace second = 0 because at command starts submitting at second = 0.
  # If first submission is VERY quick, we can have problems on HC Monitoring thread
  # Fixed waiting 60 secs before startng thread

  if test.starttime < datetime.now() and test.endtime > datetime.now():
    logger.debug('Test %d is active'%(test.id))
    return True
  elif not test.starttime < datetime.now():
    logger.info('Test %d has not yet started'%(test.id))
    return False
  elif test.endtime < datetime.now():
    logger.info('Test %d has completed'%(test.id))
    return False

def test_paused():
   
  if test.pause:
    logger.info('Test %d is paused'%(test.id))
    return True
  else:
    return False

def test_sleep(t):
  logger.debug('Sleeping %d seconds'%t)
  time.sleep(t)

##
## UPDATE DATASETS
##

##
## COPY JOB
##

def _copyJob(job):

  site = job.backend.settings['Destination']

  logger.info('Copying job %d'%job.id)
  nRetries = 3

  try:
    j=job.copy()
#    previous_datasetpath = j.inputdata.datasetpath
    # ONLY ONE DATASET PER JOB !
    num = 1

    j.submit()

    test_state = test.getTestStates_for_test.filter(ganga_jobid=job.id)
    if test_state:
      test_state[0].copied = 1
      test_state[0].save()
    else:
      ts = TestState(test=test,ganga_jobid=job.id,copied=1)
      ts.save()
  
    logger.warning('Finished copying job %d'%job.id)
    return

  except:
    logger.warning('Failed to submit job %d for %s. Retrying %d more times.'%(j.id,site,nRetries))
    logger.warning(sys.exc_info()[0])
    logger.warning(sys.exc_info()[1])
    for i in xrange(nRetries):
      try:
        j.submit()
        test_state = test.getTestStates_for_test.filter(ganga_jobid=job.id)
        if test_state:
          test_state[0].copied = 1
          test_state[0].save()
        else:
          ts = TestState(test=test,ganga_jobid=job.id,copied=1)
          ts.save()
        logger.info('Finished copying job %d'%job.id)
        return
      except:
        logger.warning('Failed to submit job %d for %s. Retrying %d more times.'%(j.id,site,nRetries-i-1))
        logger.warning(sys.exc_info()[0])
        logger.warning(sys.exc_info()[1])
        test_sleep((i+1)*10)

  # if here then submission and retries all failed
  logger.error('Failed copying job %d for %s %d times.'%(job.id,site,nRetries))
  logger.error('Disabling test %d site %s with test_site.resubmit_enabled=0.'%(testid,site))
  test_site = test.getTestSites_for_test.filter(site__name=site)[0]
  test_site.resubmit_enabled = 0
  test_site.save()    

  # If we copy a job, we wait 10 secs, this way we wait for the other thread
  # to update the values in the DB.
  test_sleep(10)

def copyJob(job):

  site = job.backend.settings['Destination']

  logger.debug('copyJob called for job %d at site %s'%(job.id,site))

  test_site = test.getTestSites_for_test.filter(site__name=site)
  if not test_site:
    logger.info('Failed to get TestSite with Test: %s and Site: %s'%(test.id,site))
    return
  else:
    test_site = test_site[0]
  
  if test_site.resubmit_force:
    logger.info('Forced copy')
    _copyJob(job)
    logger.debug('Setting test_site.resubmit_force=0 to prevent flood.')
    test_site.resubmit_force = 0
    test_site.save()
    return

  if not test_site.resubmit_enabled:
    logger.debug('Not copying job %d: test_site.resubmit_enabled is False for test %d at %s'%(job.id,test.id,site))
    return

  test_state = test.getTestStates_for_test.filter(ganga_jobid=job.id)
  if test_state:
    if test_state[0].copied:
      logger.debug('Not copying job %d: test_state(test,jobid).copied is True'%(job.id))
      return

  # submitted
  submitted = test.getResults_for_test.filter(ganga_status='s').filter(site__name=site).count()

  # running
  running = test.getResults_for_test.filter(ganga_status='r').filter(site__name=site).count()

  if submitted > test_site.min_queue_depth:
    logger.debug('Not copying job %d: %d submitted > q.d %d'%(job.id,submitted,test_site.min_queue_depth))
    return

  if running > test_site.max_running_jobs:
    logger.debug('Not copying job %d: %d running > %d max'%(job.id,running,test_site.max_running_jobs))
    return

  if len(job.subjobs) < 1:
    logger.debug('Job %d has 0 subjobs. Not copying.'%job.id)
    return

  # total last 1 hours
  total = test.getResults_for_test.filter(site__name=site).filter(ganga_status__in=['c','f']).filter(mtime__gt=datetime.now()-timedelta(hours=1)).count()

  # failed last 1 hours
  failed = test.getResults_for_test.filter(site__name=site).filter(ganga_status='f').filter(mtime__gt=datetime.now()-timedelta(hours=1)).count()

  #If the test is functional, we do not blacklist the site !
  if test.template.category == 'stress':

    if total>20:
      if float(failed)/float(total) > 0.7:
        logger.warning('Not copying job %d: %d failed from %d finished (copy when <= 0.7)'%(job.id,failed,total))
        logger.warning('Disabling site %s: test_site.resubmit_enabled <- 0'%(site))
        test_site.resubmit_enabled = 0
        test_site.save()
        return

  logger.warning('Job %d at %s ran the gauntlet. %d submitted, %d running, %d failed, %d finished'%(job.id,site,submitted,running,failed,total))
  _copyJob(job)
  return

##
## PRINT SUMMARY
##

lastsummary = 0
def print_summary():

  global lastsummary
  if time.time()<lastsummary+300:
    return
  lastsummary=time.time()
  logger.info('JOB SUMMARY:')

  active = 0
  for j in jobs:

    site = j.backend.settings['Destination']

    t = len(j.subjobs)
    s = len(j.subjobs.select(status='submitted'))
    r = len(j.subjobs.select(status='running'))
    c = len(j.subjobs.select(status='completed'))
    f = len(j.subjobs.select(status='failed'))
    active = active + s + r

    copied = 0    
    test_state = test.getTestStates_for_test.filter(ganga_jobid=j.id)
    if test_state and test_state[0].copied:
      copied = 1

    if not (c+f==t and copied):
      logger.info('Job %d: %s t:%d s:%d r:%d c:%d f:%d copied:%d'%(j.id,site,t,s,r,c,f,copied))

  logger.info('NUM JOBS TO BE MONITORED: %d'%active)

  logger.info('PROGRESS ON UNCOPIED JOBS:')
  for j in jobs:

    test_state = test.getTestStates_for_test.filter(ganga_jobid=j.id)
    if test_state and test_state[0].copied:
      continue

    site = j.backend.settings['Destination']

    t = len(j.subjobs)
    s = len(j.subjobs.select(status='submitted'))
    r = len(j.subjobs.select(status='running'))
    c = len(j.subjobs.select(status='completed'))
    f = len(j.subjobs.select(status='failed'))

    logger.info('UNCOPIED Job %d: %s t:%d s:%d r:%d c:%d f:%d'%(j.id,site,t,s,r,c,f))

##
## PROCESS SUBJOBS
##

def process_subjob(job,subjob,thread_dirac_server):

  site = job.backend.settings['Destination']
  
  DIRAC_ID = subjob.backend.id
  try:
    DIRAC_attributes = thread_dirac_server.execute('result=DiracLHCb().attributes(%s)'%(DIRAC_ID))
  except:
    DIRAC_attributes = {}
    logger.warning('PROCESS_SUBJOB: result=DiracLHCb().attributes(%s)'%(DIRAC_ID))

  results = {'ganga_status':subjob.status[0],'reason':' ','ganga_time_1':subjob.time.new(),'ganga_time_2':subjob.time.submitting(),'ganga_time_3':subjob.time.submitted(),'ganga_time_5':subjob.time.final()}

  attributes = {'JobID':'backendID',
                'StartExecTime':'start_time',
                'EndExecTime':'stop_time',
                'SubmissionTime':'submit_time',
                'ApplicationStatus':'reason',
                'MinorStatus':'reason'}

  if DIRAC_attributes and DIRAC_attributes.has_key('OK') and DIRAC_attributes['OK'] and DIRAC_attributes.has_key('Value'):
    for attribute in attributes.keys():
      if DIRAC_attributes['Value'].has_key(attribute):
        attribute_value = DIRAC_attributes['Value'][attribute]
        if attributes[attribute] == 'reason':
          results[attributes[attribute]] += '%s. '%(attribute_value)
        else:
          results[attributes[attribute]] = attribute_value

  logger.debug('Processing jobs(%d).subjobs(%d) with status %s'%(job.id,subjob.id,subjob.status))

  # return if result is already fixed
  result = test.getResults_for_test.filter(ganga_jobid=job.id).filter(ganga_subjobid=subjob.id)
  if result and result[0].fixed:
    logger.debug('subjob result is already fixed in database... skipping')
    return False

  metrics = {'LocalBatchID':'local_batch_id',
             'LoadAverage':'load_average',
             'WallClockTime(s)':'wallclock',
             'NormCPUTime(s)':'norm_cpu_time',
             'ScaledCPUTime':'scaled_cpu_time',
             'MemoryUsed(kb)':'memory',
             'TotalCPUTime(s)':'total_cpu_time'}

  DIRAC_values = {}

  try:
    DIRAC_parameters = thread_dirac_server.execute('result=DiracLHCb().parameters(%s)'%(DIRAC_ID))
    if DIRAC_parameters.has_key('Value') and isinstance(DIRAC_parameters['Value'],dict):
      DIRAC_values = DIRAC_parameters['Value']
  except:
    DIRAC_values = {}
    logger.warning('PROCESS_SUBJOB: result=DiracLHCb().parameters(%s)'%(DIRAC_ID))

  if DIRAC_values:
    for metric in metrics.keys():
      if DIRAC_values.has_key(metric):
        metric_value = DIRAC_values[metric]
        if metric ==  ['Memory(kB)']:
          metric_value = metric_value.split('k')[0]
        results[metrics[metric]] = metric_value

  logger.debug('Writing to DB')

  if not test.getTestSites_for_test.filter(site__name=site):
    sites = test.getTestSites_for_test.filter(site__name='UNKNOWN')
    if sites:
      site = sites[0].site.name
    else:
      sites = test.getTestSites_for_test.all()
      site = sites[(job.id + subjob.id)%len(sites)].site.name

  result = test.getResults_for_test.filter(ganga_jobid=job.id).filter(ganga_subjobid=subjob.id)

  if result:
    result = result[0]
  else:
    result = Result(test=test,ganga_jobid=job.id,ganga_subjobid=subjob.id)

  site = Site.objects.filter(name=site)[0]
  result.site = site
  result.ganga_status = subjob.status[0]
  result.save()

  for k,v in results.items():
    if k in value_types['DateTimeField'] and not v.__class__.__name__ == 'DateTimeField':
      if v:
        try:
          #Remove second fractions
          v = v.split('.')[0]
          v = datetime.strptime(v,'%Y-%m-%d %H:%M:%S')
        except:
#          logger.info(v)
          continue
      else:
        continue
    setattr(result,k,v)
  result.save()

  #logger.info(results)

  if result.ganga_status in ('c','f'):
    if result.ganga_status == 'f':
      logger.info('%s %s'%(site,result.ganga_status))

    logger.debug('Subjob is in final state, marking row as fixed')
    result.fixed = 1
    result.save()

##
## MAIN LOOP
##

logger.info('HammerCloud runtest.py started for test %d'%testid)

def hc_monitor_thread():
  logger.info('HC Monitor Thread: Connected to DB')

  from GangaLHCb.Lib.DIRAC.DiracServer import DiracServer
  thread_dirac_server = DiracServer()

  while (test_active() and not test_paused() and not ct.should_stop()):

#    logger.info('HC Monitor Thread: TOP OF LOOP')

    #We need to refresh the test object
    #test = Test.objects.get(pk=testid)

    try:
      print_summary()
    except:
      logger.warning('Bug during print_summary')
      logger.warning(sys.exc_info()[0])
      logger.warning(sys.exc_info()[1])
    for job in jobs:
      for subjob in job.subjobs:
        try:
          process_subjob(job,subjob,thread_dirac_server)
        except:
          logger.warning('Exception in process_subjob:')
          logger.warning(sys.exc_info()[0])
          logger.warning(sys.exc_info()[1])
      if test_paused() or ct.should_stop():
        break

    test_sleep(10)

  logger.info('HC Monitor Thread: Disconnected from DB')

ct = GangaThread(name="HCMonitorThread", target=hc_monitor_thread)

logger.info('Connected to DB')

if len(jobs):
  # Wait one minute, to let the minute counter update, and avoid
  # problems with the at command submitting on second = 0
  test_sleep(60)
  ct.start()
  test_sleep(60)
  while (test_active() and not test_paused()):

    test = Test.objects.get(pk=testid)
#    logger.info('HC Copy Thread: TOP OF MAIN LOOP')
    for job in jobs:
      if not test_active() or test_paused() or ct.should_stop():
        break
      copyJob(job)
    test_sleep(10)
  logger.info('Main thread exited.')

else:
  logger.warning('No jobs to monitor. Exiting now.')

#Stop thread.
ct.stop()

paused = test_paused()

if not paused:
  test.state   = 'completed'
  test.endtime = datetime.now()
  test.save()
  logger.info('Test state updated to %s'%(test.state))

logger.info('Disconnected from DB')

if not paused:
  try:
    logger.info('Killing leftover "submitted" jobs')
    jobs.select(status='submitted').kill()
    logger.info('Killing leftover "running" jobs')
    jobs.select(status='running').kill()
  except:
    logger.warning('Error killing jobs. PLEASE CHECK !')

logger.info('HammerCloud runtest.py exiting')
logger.info('Buf before, the last plots...')

logger.info('Over and out. Have a good day.')

