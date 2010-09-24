from datetime import datetime,timedelta
from urllib2 import URLError,HTTPError,Request,urlopen

from django.db.models import Count
from hc.cms.models import Test,TestState,Site,Result

import sys,time,random

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
except:
  print ' ERROR! Could not extract Test %s from DB'%(testid)



##
## AUXILIAR FUNTIONS
##

def test_active():
    if test.starttime < datetime.now() and test.endtime > datetime.now():
        logger.debug('Test %d is active'%(test.id))
        return True
    elif not test.starttime < datetime.now():
        logger.info('Test %d has not yet started'%(test.id))
    elif not test.endtime > datetime.now():
        logger.info('Test %d has completed'%(test.id))
    return False

def test_paused():
    if test.pause:
        logger.info('Test %d is paused'%(test.id))
        return True
    return False

def test_sleep(t):
  logger.debug('Sleeping %d seconds'%t)
  time.sleep(t)



##
## UPDATE DATASETS
##

def updateDatasets(site):

  patterns = [ td.dspattern.pattern for td in test.getTestDspatterns_for_test.all() ]
  datasets = []

  for pattern in patterns:

    dataset = ''
    try:

      str = 'https://cmsweb.cern.ch/dbs_discovery/aSearchShowAll?case=on&cff=0&caseSensitive=on&userInput=find%20dataset%20where%20dataset%20like%20%25'+pattern[0]+'%25%20and%20site%3D'+site+'%20and%20dataset.status%20like%20VALID*&grid=0&fromRow=0&xml=0&sortName=&dbsInst=cms_dbs_prod_global&html=1&limit=-1&sortOrder=desc&userMode=user&method=dbsapi'
      request = Request(str)
      f = urlopen(request)
      dataset = f.read()
      f.close()  

    except HTTPError, e:
      logger.warning("Error: "+str(e))
    except URLError, e:
      logger.warning("Error: "+str(e))

    dataset = dataset.replace(' ','')
    ds = dataset.split('\n')
    try:
      ds.remove('')
    except:
      pass
    for dset in ds:
      if not dset in datasets:
        datasets.append(dset)

  random.shuffle(datasets)
  return datasets[0]
 

  
##
## COPY JOB
##

def _copyjob(job):

  site = job.inputdata.CE_white_list

  logger.info('Copying job %d'%job.id)
  nRetries = 3

  try:
    j=job.copy()
    previous_datasetpath = j.inputdata.datasetpath
    logger.info('Previous input datasets = %s'%previous_datasetpath)

    # ONLY ONE DATASET PER JOB !
    num = 1

    try:
      j.inputdata.datasetpath = updateDatasets(site)
    except:
      logger.warning('Unexpected error:'+str(sys.exc_info()[0]))
      logger.warning('Failed to get new datasets. Using previous datasets.')
      j.inputdata.datasetpath = previous_datasetpath

    logger.info('New input datasets = %s'%j.inputdata.datasetpath)
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


def copyJob(job):

  site = job.inputdata.CE_white_list

  logger.debug('copyJob called for job %d at site %s'%(job.id,site))

  test_site = test.getTestSites_for_test.filter(site__name=site)
  if not test_site:
    print 'Failed to get TestSite with Test: %s and Site: %s'%(test.id,site)
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
  submitted = len(test.getResults_for_test.filter(ganga_status='s').filter(site__name=site))

  # running
  running = len(test.getResults_for_test.filter(ganga_status='r').filter(site__name=site))

  if submitted > test_site.min_queue_depth:
    logger.debug('Not copying job %d: %d submitted > q.d %d'%(job.id,submitted,test_site,min_queue_depth))
    return

  if running > test_site.max_running_jobs:
    logger.debug('Not copying job %d: %d running > %d max'%(job.id,running,test_site.max_running_jobs))
    return

  if len(job.subjobs) < 1:
    logger.debug('Job %d has 0 subjobs. Not copying.'%job.id)
    return

  # total last 1 hours
  total = len(test.getResults_for_test.filter(site__name=site).filter(ganga_status__in=['c','f']).filter(mtime__gt=datetime.now()-timedelta(days=1)))

  # failed last 1 hours
  failed = len(test.getResults_for_test.filter(site__name=site).filter(ganga_status='f').filter(mtime__gt=datetime.now()-timedelta(days=1)))

  if total>20:
    if float(failed)/float(total) > 0.7:
      logger.warning('Not copying job %d: %d failed from %d finished (copy when <= 0.7)'%(job.id,failed,total))
      logger.warning('Disabling site %s: test_site.resubmit_enabled <- 0'%(site))
      test_site.resubmit_enabled = 0
      test_site.save()
      return

  logger.warning('Job %d at %s ran the gauntlet: %d submitted, %d running, %d failed, %d finished'%(job.id,site,submitted,running,failed,total))
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

    site = j.inputdata.CE_white_list

    t = len(j.subjobs)
    s = len(j.subjobs.select(status='submitted'))
    r = len(j.subjobs.select(status='running'))
    c = len(j.subjobs.select(status='completed'))
    f = len(j.subjobs.select(status='failed'))
    active = active + s + r

    copied = 0    
    test_state = test.getTestStates_for_test.filter(ganga_jobid=job.id)
    if test_state and test_state[0].copied:
      copied = 1

    logger.info('Job %d: %s t:%d s:%d r:%d c:%d f:%d copied:%d'%(j.id,site,t,s,r,c,f,copied))

  logger.info('NUM JOBS TO BE MONITORED: %d'%active)

  logger.info('PROGRESS ON UNCOPIED JOBS:')
  for j in jobs:

    test_state = test.getTestStates_for_test.filter(ganga_jobid=job.id)
    if test_state and test_state[0].copied:
      continue

    site = j.inputdata.CE_white_list

    t = len(j.subjobs)
    s = len(j.subjobs.select(status='submitted'))
    r = len(j.subjobs.select(status='running'))
    c = len(j.subjobs.select(status='completed'))
    f = len(j.subjobs.select(status='failed'))

    logger.info('UNCOPIED Job %d: %s t:%d s:%d r:%d c:%d f:%d'%(j.id,site,t,s,r,c,f))



##
## PROCESS SUBJOBS
##

def process_subjob(cursor,job,subjob):

  logger.debug('Processing jobs(%d).subjobs(%d) with status %s'%(job.id,subjob.id,subjob.status))

  # return if result is already fixed
  result = test.getResults_for_test.filter(ganga_jobid=job.id).filter(ganga_subjobid=subjob.id)
  if result and result[0].fixed:
    logger.debug('subjob result is already fixed in database... skipping')
    return False

  #Iterate over all them
  #SECTIONS = config.sections()

  results = {}
  metrics = []

  for key,value in subjob.backend.report.items():
    results[key] = value

  for key in subjob.backend.fjr.keys():
    for subkey,subvalue in subjob.backend.fjr[key].items():
      results[subkey] = subvalue

  if results.has_key('CpuTime'):
    value = results['CpuTime']
    del results['CpuTime']

    value = value.replace('&quot;','')
    #cputime.replace('"','')
    cpudata = value.split(' ')
    results['UserCPUTime'] = cpudata[0]
    results['SysCPUTime'] = cpudata[1]
    results['CPUPercentage'] = cpudata[2].replace('%"','')

  logger.debug('Writing to DB')

  result = test.getResults_for_test.filter(site__name=site).filter(ganga_jobid=job.id).filter(ganga_subjobid=subjob.id)
  if result:
    result = result[0]
  else:
    result = Result(test=test,site=site,ganga_jobid=ganga_jobid,ganga_subjobid=ganga_subjobid)

  for k,v in results.items():
    setattr(result,k,v)   
  result.save()

  if subjob.status in ('completed','failed'):
    logger.debug('Subjob is in final state, marking row as fixed')
    result.fixed = 1
    result.save()    

##
## MAIN LOOP
##

logger.info('HammerCloud runtest.py started for test %d'%testid)

def hc_copy_thread():
  test_sleep(60)
  logger.info('HC Copy Thread: Connected to DB')
  while (test_active() and not test_paused() and not ct.should_stop()):
    logger.debug('HC Copy Thread: TOP OF MAIN LOOP')
    for job in jobs:
      if test_paused() or ct.should_stop():
        break
      copyJob(job)
    test_sleep(10)
  logger.info('HC Copy Thread: Disconnected from DB')

ct = GangaThread(name="HCCopyThread", target=hc_copy_thread)

logger.info('Connected to DB')

if len(jobs):
  ct.start()
  while (test_active() and not test_paused()):
    try:
      print_summary()
    except:
      logger.warning('Bug during print_summary')
      logger.warning(sys.exc_info()[0])
      logger.warning(sys.exc_info()[1])
    for job in jobs:
      for subjob in job.subjobs:
        try:
          process_subjob(job,subjob)
        except:
          logger.warning('Exception in process_subjob:')
          logger.warning(sys.exc_info()[0])
          logger.warning(sys.exc_info()[1])
      if test_paused():
        break
    test_sleep(10)
else:
  logger.warning('No jobs to monitor. Exiting now.')

paused = test_paused()
test.pause = 0
test.save()

if not paused:
  test.state   = 'completed'
  test.endtime = datetime.now()
  test.save()

logger.info('Disconnected from DB')

if not paused:
  logger.info('Killing leftover "submitted" jobs')
  jobs.select(status='submitted').kill()
  logger.info('Killing leftover "running" jobs')
  jobs.select(status='running').kill()

logger.info('HammerCloud runtest.py exiting')

