from datetime import datetime,timedelta
from urllib2 import URLError,HTTPError,Request,urlopen

from django.db.models import Count
from hc.cms.models import Test,TestState,Site,Result,SummaryTest,SummaryTestSite,Metric,TestMetric,SiteMetric,MetricType,TestLog,SummaryEvolution

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

def updateDatasets(site):

  patterns = [ td.dspattern.pattern for td in test.getTestDspatterns_for_test.all() ]
  datasets = []

  for pattern in patterns:

    dataset = ''
    try:

      str = 'https://cmsweb.cern.ch/dbs_discovery/aSearchShowAll?case=on&cff=0&caseSensitive=on&userInput=find%20dataset%20where%20dataset%20like%20%25'+pattern+'%25%20and%20site%3D'+site+'%20and%20dataset.status%20like%20VALID*&grid=0&fromRow=0&xml=0&sortName=&dbsInst=cms_dbs_prod_global&html=1&limit=-1&sortOrder=desc&userMode=user&method=dbsapi'

      #logger.info(str)
  
      request = Request(str)
      f = urlopen(request)
      dataset = f.read()
      f.close()  

    except HTTPError, e:
      logger.warning("Error: "+str(e))
    except URLError, e:
      logger.warning("Error: "+str(e))

    #logger.info(dataset)

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

def _copyJob(job):

  try:
    site = job.inputdata.CE_white_list
    if site is None:
      site = job.inputdata.target_site
  except:
    logger.error('The site cannot be read from the Ganga CRABDataset (_copyJob)')
    return

  logger.info('Copying job %d'%job.id)
  nRetries = 3

  try:
    j=job.copy()
    previous_datasetpath = j.inputdata.datasetpath
#    logger.info('Previous input datasets = %s'%previous_datasetpath)

    # ONLY ONE DATASET PER JOB !
    num = 1

#    try:
#      j.inputdata.datasetpath = updateDatasets(site)
#    except:
#      logger.warning('Unexpected error:'+str(sys.exc_info()[0]))
#      logger.warning('Failed to get new datasets. Using previous datasets.')
#      j.inputdata.datasetpath = previous_datasetpath

#    logger.info('New input datasets = %s'%j.inputdata.datasetpath)
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

  try:
    site = job.inputdata.CE_white_list
    if site is None:
      site = job.inputdata.target_site
  except:
    logger.error('The site cannot be read from the Ganga CRABDataset (copyJob)')
    return

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

    try:
      site = j.inputdata.CE_white_list
      if site is None:
        site = j.inputdata.target_site
    except:
      logger.error('The site cannot be read from the Ganga CRABDataset (print_summary 1)')
      site = '<unknown>'

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

    try:
      site = j.inputdata.CE_white_list
      if site is None:
        site = j.inputdata.target_site
    except:
      logger.error('The site cannot be read from the Ganga CRABDataset (print_summary 2)')
      site = '<unknown>'


    t = len(j.subjobs)
    s = len(j.subjobs.select(status='submitted'))
    r = len(j.subjobs.select(status='running'))
    c = len(j.subjobs.select(status='completed'))
    f = len(j.subjobs.select(status='failed'))

    logger.info('UNCOPIED Job %d: %s t:%d s:%d r:%d c:%d f:%d'%(j.id,site,t,s,r,c,f))

##
## PROCESS SUBJOBS
##

def process_subjob(job,subjob):

  try:
    site = job.inputdata.CE_white_list
    if site is None:
      site = job.inputdata.target_site
  except:
    logger.error('The site cannot be read from the Ganga CRABDataset (process_subjob)')
    return
  
  logger.debug('Processing jobs(%d).subjobs(%d) with status %s'%(job.id,subjob.id,subjob.status))

  # return if result is already fixed
  result = test.getResults_for_test.filter(ganga_jobid=job.id).filter(ganga_subjobid=subjob.id)
  if result and result[0].fixed:
    logger.debug('subjob result is already fixed in database... skipping')
    return False

  #Iterate over all them
  #SECTIONS = config.sections()

  results = {'ganga_status':subjob.status[0],'ganga_time_1':subjob.time.new(),'ganga_time_2':subjob.time.submitting(),'ganga_time_3':subjob.time.submitted(),'ganga_time_5':subjob.time.final()}
  metrics = []

  for key,value in subjob.backend.report.items():
    results[key] = value

  for key in subjob.backend.fjr.keys():
    for subkey,subvalue in subjob.backend.fjr[key].items():
      results[subkey] = subvalue

  if results.has_key('CpuTime'):
    value = results['CpuTime']
    del results['CpuTime']

    value   = value.replace('&quot;','')
    value   = value.replace('"','')
    cpudata = value.split(' ')

    results['UserCPUTime']   = cpudata[0]
    results['SysCPUTime']    = cpudata[1]
    results['CPUPercentage'] = cpudata[2].replace('%','')

  if results.has_key('submissionTime'): 
    results['submit_time'] = results['submissionTime']
    del results['submissionTime']

  if results.has_key('startTime'):
    results['start_time'] = results['startTime']
    del results['startTime']

  if results.has_key('stopTime'):
    results['stop_time'] = results['stopTime']
    del results['stopTime']

  if results.has_key('statusReason'):
    results['reason'] = results['statusReason']
#    del results['statusReason']

  if results.has_key('schedulerId'):
    results['backendID'] = results['schedulerId']

  logger.debug('Writing to DB')

  result = test.getResults_for_test.filter(site__name=site).filter(ganga_jobid=job.id).filter(ganga_subjobid=subjob.id)
  if result:
    result = result[0]
  else:
    site = Site.objects.filter(name=site)[0]
    result = Result(test=test,site=site,ganga_jobid=job.id,ganga_subjobid=subjob.id,ganga_status=subjob.status[0])

  for k,v in results.items():
    if k in value_types['DateTimeField'] and type(v) == types.StringType:
      if v:
        v = datetime.strptime(v,'%Y-%m-%d %H:%M:%S')
      else:
        continue
    setattr(result,k,v)
  result.save()

  #logger.info(results)

  if subjob.status in ('completed','failed'):
    logger.debug('Subjob is in final state, marking row as fixed')
    result.fixed = 1
    result.save()    


##
## SUMMARIZE
##

def summarize():

  s_t   = test.getSummaryTests_for_test.all()[0]
  s_t_s = test.getSummaryTestSites_for_test.all()

  stats = Stats()  

  Qobjects                = {}
  Qobjects['test']        = [test]
  #small hack to remove duplicated in the list
  Qobjects['metric_type'] = list(set(list(test.metricperm.index.all()) + list(test.metricperm.pertab.all()) + list(test.metricperm.summary.all())))
  Qobjects['site']        = [ ts.site for ts in test.getTestSites_for_test.all() ]
  
  commands = {'sort_by':'test','type':'raw_value','completed':False}
  
  title,values = stats.process(Qobjects,commands)[0]
  values = dict(values)

  s_t.submitted = float(test.getResults_for_test.filter(ganga_status='s').count())
  s_t.running   = float(test.getResults_for_test.filter(ganga_status='r').count())
  s_t.completed = float(test.getResults_for_test.filter(ganga_status='c').count())
  s_t.failed    = float(test.getResults_for_test.filter(ganga_status='f').count())
  s_t.total     = float(test.getResults_for_test.count())
     
  if s_t.total:
    s_t.c_t = s_t.completed / s_t.total
    s_t.f_t = s_t.failed / s_t.total

  if s_t.completed or s_t.failed:
    s_t.c_cf = s_t.completed / (s_t.completed + s_t.failed)

  if values.has_key('Overall.'):
    for metric in test.metricperm.summary.all():
#      logger.info(metric.name)
      rate = [float(dic[metric.name]) for dic in values['Overall.'] if (metric.name != 'c_cf' and dic[metric.name] != None)]
#      logger.info(rate)
      if rate:
        mean = round(numpy.mean(rate),3)
#        logger.info([metric.name,mean])
        setattr(s_t,metric.name,mean)     
  
  s_t.save()

  frozen_time = datetime.now()

  evol_lock   = SummaryEvolution.objects.filter(test=test).filter(time__gt=frozen_time-timedelta(minutes=5))

  for sts in s_t_s:
    sts.submitted = float(test.getResults_for_test.filter(site=sts.test_site.site).filter(ganga_status='s').count())
    sts.running   = float(test.getResults_for_test.filter(site=sts.test_site.site).filter(ganga_status='r').count())
    sts.completed = float(test.getResults_for_test.filter(site=sts.test_site.site).filter(ganga_status='c').count())
    sts.failed    = float(test.getResults_for_test.filter(site=sts.test_site.site).filter(ganga_status='f').count())
    sts.total     = float(test.getResults_for_test.filter(site=sts.test_site.site).count())

    if not evol_lock:
      #Save to Summary Evolution
      se = SummaryEvolution(test=test,site=sts.test_site.site,time=frozen_time)
      se.submitted = sts.submitted
      se.running   = sts.running  
      se.completed = sts.completed
      se.failed    = sts.failed   
      se.total     = sts.total    
      se.save()

    if sts.total:
      sts.c_t = sts.completed / sts.total
      sts.f_t = sts.failed / sts.total

    if sts.completed or sts.failed:
      sts.c_cf = sts.completed / (sts.completed + sts.failed)

    if values.has_key(sts.test_site.site.name):
      for metric in test.metricperm.summary.all():
#        logger.info(metric.name)
        rate = [float(dic[metric.name]) for dic in values[sts.test_site.site.name] if (metric.name != 'c_cf' and dic[metric.name] != None)]
#        logger.info(rate)
        if rate:
          mean = round(numpy.mean(rate),3)
#          logger.info('Site:'+str([metric.name,mean]))
          setattr(sts,metric.name,mean)
  
    sts.save()  

#  logger.info('End summarize')

##
## PLOT
##

def plot(completed=False):

  s_t   = test.getSummaryTests_for_test.all()[0]
  s_t_s = test.getSummaryTestSites_for_test.all()

  stats = Stats()

  Qobjects                = {}
  Qobjects['test']        = [test]
  #small hack to remove duplicated in the list
  Qobjects['metric_type'] = list(set(list( test.metricperm.index.all()) + list(test.metricperm.pertab.all()) ))
  Qobjects['site']        = [ ts.site for ts in test.getTestSites_for_test.all() ]

  commands = {'sort_by':'test','type':'plot','completed':completed}

  test_title,values = stats.process(Qobjects,commands)[0][0]
#  logger.info(values)
  for metric_title,urls in values:

    mt = MetricType.objects.filter(title=metric_title)
    if mt:

      for plot_title,url in urls: 

        if plot_title == 'Overall.':
          # then, it goes to TestMetric

          test_metric = test.getTestMetrics_for_test.filter(metric__metric_type__title=metric_title)

          if test_metric:
            test_metric = test_metric[0]
            metric = test_metric.metric
            metric.url = url
            metric.save()
#            test_metric.metric.url = url
#            test_metric.save()
#            logger.info('Refreshed metric.')
          else:
            m = Metric(url=url,metric_type=mt[0])
            m.save()
            tm = TestMetric(metric=m,test=test)
            tm.save()
#            logger.info('Created metric.')

        else:
          # then, it goes to SiteMetric

          site = Site.objects.filter(name=plot_title)
          if site:

            site_metric = test.getSiteMetrics_for_test.filter(site=site[0]).filter(metric__metric_type__title=metric_title)
            
            if site_metric:
              site_metric = site_metric[0]
              metric = site_metric.metric
              metric.url = url
              metric.save()
#              logger.info('Site metric refreshed.')
            else:
              m = Metric(url=url,metric_type=mt[0])
              m.save()
              sm = SiteMetric(metric=m,test=test,site=site[0])
              sm.save()
#              logger.info('Created site metric')
          else:
            logger.info("Wow, I don't know this site: %s"%(plot_title))

    else:
      logger.info('No metric type recognised with this name: %s'%(metric_title))

    #logger.info(value[0])    

##
## MAIN LOOP
##

logger.info('HammerCloud runtest.py started for test %d'%testid)

def hc_plot_summarize():
  test_sleep(60)
  while(not pt.should_stop()):
    logger.info('HC Plot and Summary thread init %s'%(datetime.now()))
    summarize()
    plot()
    logger.info('HC Plot and Summary thread end %s'%(datetime.now()))
    test_sleep(300)
  logger.info('HC Plot Summarize Thread: Disconnected.')

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
#pt = GangaThread(name="HCPlotSummary", target=hc_plot_summarize)

logger.info('Connected to DB')

if len(jobs):
  ct.start()
#  pt.start()

  while (test_active() and not test_paused()):

    #We need to refresh the test object
    test = Test.objects.get(pk=testid)

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

#Stop plotting and summarizing thread.
#pt.stop()
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

#summarize()
#plot(True)

logger.info('Over and out. Have a good day.')

