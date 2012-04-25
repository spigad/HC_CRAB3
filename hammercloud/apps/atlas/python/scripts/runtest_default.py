from datetime import datetime, timedelta
from random import shuffle

from django.db.models import Count
from hc.atlas.models import Test, TestState, Site, Result, SummaryTest, SummaryTestSite, Metric, TestMetric, SiteMetric, MetricType, TestLog, SummaryEvolution
from lib.summary import summary

from hc.core.utils.hc.stats import Stats
from numpy import *

import os, sys, time, random, commands, gc
import numpy
import types
import fnmatch

from Ganga.Utility.Config import getConfig
configPanda = getConfig('Panda')

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
  test = Test.objects.get(pk=testid) #select_related('template', 'metricperm__index', 'metricperm__summary', 'metricperm__pertab').get(pk=testid)
  if test and not test.is_golden:
    import guppy
    from guppy.heapy import Remote
    Remote.on()
  if test.pause:
    logger.info('Un-pausing test.')
    test.pause = 0
    test.save()
    comment = 'Test modifications: pause -> False,'
    testlog = TestLog(test=test, comment=comment, user='gangarbt', severity='testinfo')
    testlog.save()
except:
  print ' ERROR! Could not extract Test %s from DB' % (testid)

value_types = {'DateTimeField':[]}

for rfield in Result._meta.fields:
  if rfield.__class__.__name__ == 'DateTimeField':
    value_types['DateTimeField'] += [rfield.name]

# get category
category = test.template.category
logger.info('Test category: %s' % category)

# Path of the working directory
if os.environ.has_key('HCAPP'):
  basePath = os.environ['HCAPP']
else:
  basePath = '/tmp'

##
## AUXILIAR FUNTIONS
##

def test_active():

  if test.starttime < datetime.now() and test.endtime > datetime.now():
    logger.debug('Test %d is active' % (test.id))
    return True
  elif not test.starttime < datetime.now():
    logger.debug('Test %d has not yet started' % (test.id))
    return False
  elif not test.endtime > datetime.now():
    logger.debug('Test %d has completed' % (test.id))
    return False
  else:
    return False

def test_paused():

  if test.pause:
    logger.info('Test %d is paused' % (test.id))
    return True
  return False

def test_sleep(t):
  #logger.debug('Sleeping %d seconds'%t)
  time.sleep(t)

##
## UPDATE DATASETS
##
datasetsAtSite = {}
def updateDatasets(site, num):
  global datasetsAtSite
  global dsLocationsAtSite
  global basePath
  from dq2.clientapi.DQ2 import DQ2
  dq2 = DQ2()

  datasets = []
  dsLocation = {}

  try:
    (datasets, dsLocation, ts) = datasetsAtSite[site]
    logger.info('Read %d datasets for %s from cache (from %d)' % (len(datasets), site, int(ts)))
  except:
    # get DDM name from site
    location = Site.objects.filter(name=site)[0].ddm
    locations = location.split(',')
    # hack for CERN
    if 'CERN-PROD_LOCALGROUPDISK' in locations:
        locations.remove('CERN-PROD_LOCALGROUPDISK')

    # Dataset patterns
    datasetpatterns = []

    patterns = [ td.dspattern.pattern for td in test.getTestDspatterns_for_test.all() ] #select_related('dspattern').all() ]

    for pattern in patterns:
      if pattern.startswith('/'):
        file = open(basePath + '/inputfiles/dspatterns' + pattern)
        for l in file:
          datasetpatterns.append(l.strip())
        file.close()
      elif pattern.startswith('http'):
        import urllib2
        url = pattern
        try:
          tmp_patterns = urllib2.urlopen(url).read().split()
          for p in tmp_patterns:
            if p not in datasetpatterns:
              datasetpatterns.append(p)
        except:
          logger.error('failed to download url pattern'%url)
      else:
        datasetpatterns.append(pattern)

    # get list of datasets
    for location in locations:
      for datasetpattern in datasetpatterns:
        try:
          #temp = list(dq2.listDatasetsByNameInSite(site=location, name=datasetpattern))
          temp1 = dq2.listDatasetsByNameInSite(site=location, complete=None, name=None, p=None, rpp=None, group=None )
          temp1 = list(temp1)
          temp = fnmatch.filter(temp1, datasetpattern)
          temp = list(temp)
          datasets = datasets + temp
          for ds in temp:
            dsLocation[ds] = location
        except:
          pass
    ts = time.time()
    datasetsAtSite[site] = (datasets, dsLocation, ts)
    logger.info('Wrote %d datasets for %s to cache at %d' % (len(datasets), site, int(ts)))
    #TODO: checl that you got some datasets


  shuffle(datasets)

  gooddatasets = []
  for dataset in datasets:
    try:
      # Remove bad dataset patterns
      if dataset.find('singlepart')>=0 or dataset.find('pile')>=0 or (dataset.find('test')>=0 and not 'HCtest' in dataset) or dataset.find('atlfast')>=0 or dataset.find('users')>=0 or dataset.find('higgswg')>=0 or dataset.find('_sub')>=0 or dataset.find('DAOD')>=0 or dataset.find('D2AOD')>=0:
        print 'Skipping %s' %dataset
        continue
      # check if frozen and complete
      location = dsLocation[dataset]
      datasetsiteinfo = dq2.listFileReplicas(location, dataset)
      # Skip is data is not immutable
      immutable = datasetsiteinfo[0]['immutable']
      if not immutable:
        continue
      # Skip dataset if not complete at site
      try:
        incompleteLocations = dq2.listDatasetReplicas(dataset)[dq2.listDatasets(dataset)[dataset]['vuids'][0]][0]
      except:
        incompleteLocations = []
      if location in incompleteLocations:
        continue
      gooddatasets.append(dataset)
      if len(gooddatasets) >= num:
        return gooddatasets
    except:
      logger.warning('updateDatasets: error checking dataset %s' % dataset)
      logger.warning(sys.exc_info()[0])
      logger.warning(sys.exc_info()[1])
      continue

  return gooddatasets


##
## JOB TO SITE
##

def jobToSite(job):
  siteMap = {
#    'ANALY_LONG_LYON': 'ANALY_LYON',
#    'ANALY_LONG_BNL_ATLAS': 'ANALY_BNL_ATLAS_1',
#    'ANALY_LONG_LYON_DCACHE': 'ANALY_LYON_DCACHE'
  }

  site = ''
  if job.backend._impl._name in [ 'LCG', 'CREAM']:
    site = job.backend.requirements.sites[0]
  elif job.backend._impl._name == 'NG':
    if job.backend.CE:
      site = job.backend.CE
    else:
      site = 'condor.titan.uio.no'
  elif job.backend._impl._name == 'Panda':
    try:
      site = siteMap[job.backend.site]
    except KeyError:
      site = job.backend.site
  if not site:
    logger.error('Could not detect site for job %d. Leaving copyJob. %s' % (job.id, job.backend))
  return site

##
## COPY JOB
##
newJobLastAttempt = {}

def _copyJob(job, site):
  global category
  global newJobLastAttempt

  logger.info('Copying job %d' % job.id)
  if category == 'stress':
    nRetries = 1
  else:
    nRetries = 0
  try:
    if job.status == 'new':
      j = job
      logger.info('Not marking job %d as copied (reusing job %d in "new" state)' % (job.id, j.id))
      try:
        if time.time() - 600 < newJobLastAttempt[j.id]:
          logger.info('Skipping job %d in "new" state. Trying once every 10 minutes.' % j.id)
          return
      except:
        pass
      newJobLastAttempt[j.id] = time.time()
    else:
      j = job.copy()
      test_state = test.getTestStates_for_test.filter(ganga_jobid=job.id)
      if test_state:
        test_state = test_state[0]
      else:
        test_state = TestState(test=test, ganga_jobid=job.id)
      test_state.copied = 1
      test_state.save()
      logger.info('Marked job %d as copied (new one is job %d)' % (job.id, j.id))

    uuid = commands.getoutput('uuidgen')[0:3]
    t = int(time.time())
    if configPanda['processingType'] != 'gangarobot-rctest':
        j.outputdata.datasetname = 'hc%d.%s.%s.%s' % (testid, site, uuid, t)
    j.outputdata.location = ''
    if j.inputdata and j.inputdata._impl._name == 'DQ2Dataset':
      previous_datasets = j.inputdata.dataset
      logger.info('Previous input datasets = %s' % previous_datasets)
      try:
        test_site = test.getTestSites_for_test.filter(site__name=site)
        num = test_site[0].num_datasets_per_bulk
      except:
        num = len(j.inputdata.dataset)

      try:
        j.inputdata.dataset = updateDatasets(site, num)
        if not j.inputdata.dataset:
          j.inputdata.dataset = previous_datasets[0:num]
      except:
        logger.warning('Failed to get new datasets from DQ2. Using previous datasets.')
        logger.warning(sys.exc_info()[0])
        logger.warning(sys.exc_info()[1])
        j.inputdata.dataset = previous_datasets[0:num]

      logger.info('New input datasets = %s' % j.inputdata.dataset)

    j.submit()
    logger.info('Finished copying job %d' % job.id)
    test_sleep(2)
    return
  except:
    logger.warning('Failed to submit job %d for %s. Retrying %d more times.' % (j.id, site, nRetries))
    logger.warning(sys.exc_info()[0])
    logger.warning(sys.exc_info()[1])
    for i in xrange(nRetries):
      try:
        uuid = commands.getoutput('uuidgen')[0:3]
        t = int(time.time())
        if configPanda['processingType'] != 'gangarobot-rctest':
            j.outputdata.datasetname = 'hc%d.%s.%s.%s' % (testid, site, uuid, t)
        test_sleep((i + 1) * 2)
        j.submit()
        test_state = test.getTestStates_for_test.filter(ganga_jobid=job.id)
        if test_state:
          test_state = test_state[0]
        else:
          test_state = TestState(test=test, ganga_jobid=job.id)
        test_state.copied = 1
        test_state.save()
        logger.info('Finished copying job %d' % job.id)
        test_sleep(2)
        return
      except:
        logger.warning('Failed to submit job %d for %s. Retrying %d more times.' % (j.id, site, nRetries - i - 1))
        logger.warning(sys.exc_info()[0])
        logger.warning(sys.exc_info()[1])

  # if here then submission and retries all failed
  logger.error('Failed copying job %d for %s %d times.' % (job.id, site, nRetries))
  if category == 'stress':
    logger.error('Disabling test %d site %s with test_site.resubmit_enabled=0.' % (testid, site))
    test_site = test.getTestSites_for_test.filter(site__name=site)[0]
    test_site.resubmit_enabled = 0
    test_site.save()

# We copy a job under these circumstances:
#  1. test_site.resubmit_enabled is True and test_state(test,jobid).copied is False and #submitted < 30% and #failed < 70%
#
# We also do the following:
#  1. If #failed > 70%, set test_site.resubmit_enabled to False
#  2. If a job is copied, set test_state(test,jobid).copied to True
#
def copyJob(job):
  global category

  site = jobToSite(job)

  test_site = test.getTestSites_for_test.filter(site__name=site)
  if not test_site:
    logger.warning('Failed to get TestSite with Test: %s and Site: %s' % (test.id, site))
    return
  else:
    test_site = test_site[0]

  if test_site.resubmit_force:
    logger.info('Forced copy')
    _copyJob(job, site)
    logger.info('Setting test_site.resubmit_force=0 to prevent flood.')
    test_site.resubmit_force = 0
    test_site.save()
    return

  if not test_site.resubmit_enabled:
    logger.debug('Not copying job %d: test_site.resubmit_enabled is False for test %d at %s'%(job.id,testid,site))
    return

  test_state = test.getTestStates_for_test.filter(ganga_jobid=job.id)
  if test_state:
    if test_state[0].copied:
      logger.debug('Not copying job %d: test_state(test,jobid).copied is True' % (job.id))
      return


  # submitted
  submitted = test.getResults_for_test.filter(ganga_status='s').filter(site__name=site).exclude(ganga_subjobid=1000000).count()
  #submitted = Result.objects.filter(test=test).filter(ganga_status='s').filter(site__name=site).exclude(ganga_subjobid=1000000).count()

  # running
  running = test.getResults_for_test.filter(ganga_status='r').filter(site__name=site).exclude(ganga_subjobid=1000000).count()
  #running = Result.objects.filter(test=test).filter(ganga_status='r').filter(site__name=site).exclude(ganga_subjobid=1000000).count()

  if submitted > test_site.min_queue_depth:
    logger.debug('Not copying job %d: %d submitted > q.d %d'%(job.id,submitted,test_site.min_queue_depth))
    return

  if running > test_site.max_running_jobs:
    logger.debug('Not copying job %d: %d running > %d max'%(job.id,running,test_site.max_running_jobs))
    return

#  if len(job.subjobs) < 1:
#    logger.warning('Job %d has 0 subjobs. Not copying.'%job.id)
#    return

  if job.backend._impl._name == 'Panda':
    if job.backend.buildjob and job.backend.buildjob.status not in ['finished', 'failed']:
      logger.warning('Job %d has an incomplete buildjob. Not copying.' % job.id)
      return
    if len(job.backend.buildjobs) > 0 and job.backend.buildjobs[0].status not in ['finished', 'failed']:
      logger.warning('Job %d has an incomplete buildjob. Not copying.' % job.id)
      return


  # total last 1 hours
  total = test.getResults_for_test.filter(site__name=site).filter(ganga_status__in=['c', 'f']).filter(mtime__gt=datetime.now() - timedelta(hours=1)).exclude(ganga_subjobid=1000000).count()
  #total = Result.objects.filter(test=test).filter(site__name=site).filter(ganga_status__in=['c', 'f']).filter(mtime__gt=datetime.now() - timedelta(hours=1)).exclude(ganga_subjobid=1000000).count()

  # failed last 1 hours
  failed = test.getResults_for_test.filter(site__name=site).filter(ganga_status='f').filter(mtime__gt=datetime.now() - timedelta(hours=1)).exclude(ganga_subjobid=1000000).count()
  #failed = Result.objects.filter(test=test).filter(site__name=site).filter(ganga_status='f').filter(mtime__gt=datetime.now() - timedelta(hours=1)).exclude(ganga_subjobid=1000000).count()

  if category == 'stress' and total > 20 and float(failed) / float(total) > 0.7:
    logger.warning('Not copying job %d: %d failed from %d finished (copy when <= 0.7)' % (job.id, failed, total))
    logger.warning('Disabling site %s: test_site.resubmit_enabled <- 0' % site)
    test_site.resubmit_enabled = 0
    test_site.save()
    return

  # Check if build job failed due to missing CMTCONFIG
  bfailed = test.getResults_for_test.filter(site__name=site).filter(ganga_status='f').filter(ganga_subjobid=1000000).filter(mtime__gt=datetime.now() - timedelta(hours=1)).filter(exit_status_2__in=[1109,1211]).exclude(reason__contains='cvmfs').count()
  
  if bfailed > 0:
    logger.warning('Not copying job %d: build job failed with pilot error code 1109 or 1211' % job.id)
    logger.warning('Disabling site %s: test_site.resubmit_enabled <- 0' % site)
    test_site.resubmit_enabled = 0
    test_site.save()
    return

  logger.info('Job %d at %s ran the gauntlet: %d submitted, %d running, %d failed, %d finished' % (job.id, site, submitted, running, failed, total))
  _copyJob(job, site)
  return

##
## PRINT SUMMARY
##

lastsummary = 0
def print_summary():

  global lastsummary
  if time.time() < lastsummary + 300:
    return
  lastsummary = time.time()

  try: 
    #TRIM fixed jobs
    logger.debug('TRIM: removing old fixed jobs')
    for j in jobs:
      # check if this job has been copied
      copied = False
      test_state = test.getTestStates_for_test.filter(ganga_jobid=j.id)
      if not test_state or not test_state[0].copied:
        logger.debug("TRIM: %d not yet copied, skipping" % j.id)
        continue

      # check if master and all subjobs are fixed
      num_fixed = test.getResults_for_test.filter(ganga_jobid=j.id).filter(fixed=True).count()
      if num_fixed < len(j.subjobs) + 1:
        logger.debug("TRIM: %d/%d subjobs fixed for job %d, skipping" % (num_fixed,len(j.subjobs)+1,j.id))
        continue

      logger.info("TRIM: removing job %d" % j.id)
      j.remove()
  except:
    logger.warning("TRIM: %s" % repr(sys.exc_info()))
    pass

  x = gc.collect()
  logger.debug("GC Collected %d things" % x)

  logger.info('JOB SUMMARY:')

  active = 0
  for j in jobs:

    site = jobToSite(j)

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

    if not (c + f == t and copied):
      logger.info('Job %d: %s t:%d s:%d r:%d c:%d f:%d copied:%d' % (j.id, site, t, s, r, c, f, copied))

  logger.info('NUM JOBS TO BE MONITORED: %d' % active)

  try:
    from Ganga.Lib.LCG.LCG import *
    downloader = get_lcg_output_downloader()
    logger.info('NUM JOBS IN DOWNLOAD QUEUE: %d' % downloader.data.queue.qsize())
  except:
    pass

  logger.info('PROGRESS ON UNCOPIED JOBS:')
  for j in jobs:

    test_state = test.getTestStates_for_test.filter(ganga_jobid=j.id)
    if test_state and test_state[0].copied:
      continue

    site = jobToSite(j)

    t = len(j.subjobs)
    s = len(j.subjobs.select(status='submitted'))
    r = len(j.subjobs.select(status='running'))
    c = len(j.subjobs.select(status='completed'))
    f = len(j.subjobs.select(status='failed'))

    logger.info('UNCOPIED Job %d: %s t:%d s:%d r:%d c:%d f:%d' % (j.id, site, t, s, r, c, f))

##
## PROCESS JOB
##

def process_job(job):

  logger.debug('Processing jobs(%d) with status %s' % (job.id, job.status))

  SUBJOB_ID = 1000000

  # return if result is already fixed
  result = test.getResults_for_test.filter(ganga_jobid=job.id).filter(ganga_subjobid=SUBJOB_ID)
  if result and result[0].fixed:
    logger.debug('subjob result is already fixed in database... skipping')
    return False

  try:
    if not test.output_dataset and test.getResults_for_test.filter(ganga_status='c'):
      test.output_dataset = '.'.join(test.getResults_for_test.filter(ganga_status='c')[0].outds.split('.')[0:3])+'.*'
      test.save()
  except:
    logger.warning('error setting test.output_dataset')
    pass

  stats = {}
  try:
    stats = job.application.stats
  except:
    try:
      stats = job._impl.backend.get_stats()
    except:
      #logger.warning('Ganga application stats for job not available')
      pass

  metrics = ['percentcpu', 'systemtime', 'usertime', 'site', 'totalevents', 'wallclock', 'stoptime', 'outse', 'starttime', 'exitstatus', 'numfiles3', 'gangatime1', 'gangatime2', 'gangatime3', 'gangatime4', 'gangatime5', 'jdltime', 'NET_ETH_RX_PREATHENA', 'NET_ETH_RX_AFTERATHENA', 'pandatime1', 'pandatime2', 'pandatime3', 'pandatime4', 'pandatime5', 'arch', 'submittime']
  for m in metrics:
    try:
      x = stats[m]
    except KeyError:
      stats[m] = None

  outds = None
  try:
    outds = job.outputdata.datasetname
  except:
    pass

  inds = None
  try:
    inds = job.inputdata.dataset[0]
  except:
    pass

  innumfiles = 0
  try:
    innumfiles = job.inputdata.number_of_files
  except:
    pass

  #Translate from stats to DB names
  results = {'ganga_status'          :job.status[0],
             'ganga_time_1'          :stats['gangatime1'],
             'ganga_time_2'          :stats['gangatime2'],
             'ganga_time_3'          :stats['gangatime3'],
             'ganga_time_4'          :stats['gangatime4'],
             'ganga_time_5'          :stats['gangatime5'],
             'start_time'            :stats['starttime'],
             'submit_time'           :stats['submittime'],
             'stop_time'             :stats['stoptime'],
             'jdl_time'              :stats['jdltime'],
             'pandatime1'            :stats['pandatime1'],
             'pandatime2'            :stats['pandatime2'],
             'pandatime3'            :stats['pandatime3'],
             'pandatime4'            :stats['pandatime4'],
             'pandatime5'            :stats['pandatime5'],
             'output_location'       :stats['outse'],
             'wallclock'             :stats['wallclock'],
             'arch'                  :stats['arch'],
             'percent_cpu'           :stats['percentcpu'],
             'numevents'             :stats['totalevents'],
             'NET_ETH_RX_PREATHENA'  :stats['NET_ETH_RX_PREATHENA'],
             'NET_ETH_RX_AFTERATHENA' :stats['NET_ETH_RX_AFTERATHENA'],
             'inds'                  :inds,
             'outds'                 :outds,
             'reason'                :str(job.backend.reason).replace('\n',' '),
             'ganga_number_of_files' :innumfiles,
             }

  if job.backend._impl._name in ['LCG', 'CREAM']:
    logfile_guid = None
    logfile_loc = None
    for outfile in job.outputdata.output:
      if outfile.find('.log.tgz') != -1:
        logfile_guid = outfile.split(',')[2]
        logfile_loc = outfile.split(',')[5]
      if not stats['outse']:
        results['output_location'] = logfile_loc

    results['site'] = job.backend.requirements.sites[0]
    results['exit_status_1'] = job.backend.exitcode
    results['exit_status_2'] = stats['exitstatus']
    results['numfiles'] = stats['numfiles3']
    results['submit_time'] = None
    results['backendID'] = repr(job.backend.id)
    results['actual_ce'] = job.backend.actualCE
    results['logfile_guid'] = logfile_guid

    if job.status == 'running' and job.backend.status == 'Done (Success)':
      results['ganga_status'] = 'd'

  elif job.backend._impl._name == 'NG':

    sit = 'condor.titan.uio.no'
    if job.backend.CE:
      sit = job.backend.CE

    results['site'] = sit
    results['exit_status_1'] = stats['exitstatus']
    results['exit_status_2'] = stats['exitstatus']
    results['numfiles'] = stats['numfiles3']
    results['submit_time'] = None
    results['backendID'] = job.backend.id
    results['actual_ce'] = job.backend.actualCE
    results['logfile_guid'] = None

    if job.status == 'submitted' and not job.backend.status:
      results['ganga_status'] = 'n'

  elif job.backend._impl._name == 'Panda':
    try:
      results['pandatime1'] = int(stats['pandatime1'])
    except:
      pass
    try:
      results['pandatime2'] = int(stats['pandatime2'])
    except:
      pass
    try:
      results['pandatime3'] = int(stats['pandatime3'])
    except:
      pass
    try:
      results['pandatime4'] = int(stats['pandatime4'])
    except:
      pass
    try:
      results['pandatime5'] = int(stats['pandatime5'])
    except:
      pass
    
    try:
      results['exit_status_2'] = int(job.backend.buildjobs[0].jobSpec['pilotErrorCode'])
      results['reason'] = str(job.backend.buildjobs[0].jobSpec['pilotErrorDiag']).replace('\n',' ')
    except:
      results['exit_status_2'] = job.backend.piloterrorcode
      results['reason'] = ''

    results['site'] = jobToSite(job)
    results['exit_status_1'] = job.backend.exitcode
    results['numfiles'] = innumfiles
    results['submit_time'] = stats['submittime']
    results['backendID'] = job.backend.id
    results['actual_ce'] = 'unknown'
    results['logfile_guid'] = None
    if job.backend.status == 'holding':
      results['ganga_status'] = 'h'

  if job.status == 'completing':
    results['ganga_status'] = 'g'

  #SITE
  if "'" in results['site']:
    results['site'] = results['site'].replace("'", '')

  #EVENTRATE
  if results['numevents'] != 'NULL' and results['wallclock'] != 'NULL':
    try:
      eventrate = float(results['numevents']) / float(results['wallclock'])
      results['eventrate'] = eventrate
    except:
      pass
      #logger.warning('Bug during pj eventrate')


  #EVENTS/ATHENA
  if results['numevents'] != 'NULL':
    time = 0
    if results['pandatime3'] != 'NULL':
      time = results['pandatime3']
    elif results['ganga_time_4'] != 'NULL' and results['ganga_time_3'] != 'NULL':
      time = results['ganga_time_4'] - results['ganga_time_3']

    if time:
      try:
        events_athena = float(results['numevents']) / float(time)
        results['events_athena'] = events_athena
      except:
        pass
        #logger.warning('Bug during pj event_athena')

  try:
    results['site'] = Site.objects.filter(name=results['site'])[0]
  except:
    logger.warning('Could not find site %s' % (results['site']))
    return False

  result = test.getResults_for_test.filter(site__name=results['site'].name).filter(ganga_jobid=job.id).filter(ganga_subjobid=SUBJOB_ID)
  if result:
    result = result[0]
  else:
    result = Result(test=test, site=results['site'], ganga_jobid=job.id, ganga_subjobid=SUBJOB_ID)

  for k, v in results.items():
    if k in value_types['DateTimeField'] and type(v) == types.StringType:
      if v:
        try:
          v = datetime.strptime(v, '%Y-%m-%d %H:%M:%S')
        except:
          logger.warning('Process_job: %s %s' % (k, v))
      else:
        continue
    elif k in value_types['DateTimeField']:
#      logger.info([k,v])
      continue
    if v and v != 'NULL':
      setattr(result, k, v)
#    elif v == 'NULL':
#      logger.info([k,v])

  if result.ganga_status in ('c', 'f'):
    #logger.warning('Job is in final state, marking row as fixed')
    result.fixed = 1

  result.save()

##
## PROCESS SUBJOBS
##

def process_subjob(job, subjob):

  logger.debug('Processing jobs(%d).subjobs(%d) with status %s' % (job.id, subjob.id, subjob.status))

  # return if result is already fixed
  result = test.getResults_for_test.filter(ganga_jobid=job.id).filter(ganga_subjobid=subjob.id)
  if result and result[0].fixed:
    logger.debug('subjob result is already fixed in database... skipping')
    return False

  stats = None
  try:
    stats = subjob.application.stats
  except:
    try:
      stats = subjob._impl.backend.get_stats()
    except:
      pass

  if (subjob.status == 'completed' and not stats) or subjob.status == 'failed':
    logger.warning('Forced postprocess')
    try:
      subjob.application.postprocess()
    except:
      logger.warning('Error in postprocess')
      logger.warning(sys.exc_info()[0])
      logger.warning(sys.exc_info()[1])

  stats = {}
  try:
    stats = subjob.application.stats
  except:
    try:
      stats = subjob._impl.backend.get_stats()
    except:
      #logger.warning('Ganga application stats not avaible')
      pass

  metrics = ['percentcpu', 'systemtime', 'usertime', 'site', 'totalevents', 'wallclock', 'stoptime', 'outse', 'starttime', 'exitstatus', 'numfiles3', 'gangatime1', 'gangatime2', 'gangatime3', 'gangatime4', 'gangatime5', 'jdltime', 'NET_ETH_RX_PREATHENA', 'NET_ETH_RX_AFTERATHENA', 'pandatime1', 'pandatime2', 'pandatime3', 'pandatime4', 'pandatime5', 'arch', 'submittime']
  for m in metrics:
    try:
      x = stats[m]
    except KeyError:
      #logger.warning('Metric "%s" not available in Ganga application stats' % m)
      stats[m] = None

  outds = None
  try:
    outds = subjob.outputdata.datasetname
  except:
    pass

  inds = None
  try:
    inds = subjob.inputdata.dataset[0]
  except:
    pass

  innumfiles = 0
  try:
    innumfiles = subjob.inputdata.number_of_files
  except:
    pass

  #Translate from stats to DB names
  results = {'ganga_status'          :subjob.status[0],
             'ganga_time_1'          :stats['gangatime1'],
             'ganga_time_2'          :stats['gangatime2'],
             'ganga_time_3'          :stats['gangatime3'],
             'ganga_time_4'          :stats['gangatime4'],
             'ganga_time_5'          :stats['gangatime5'],
             'start_time'            :stats['starttime'],
             'submit_time'           :stats['submittime'],
             'stop_time'             :stats['stoptime'],
             'jdl_time'              :stats['jdltime'],
             'pandatime1'            :stats['pandatime1'],
             'pandatime2'            :stats['pandatime2'],
             'pandatime3'            :stats['pandatime3'],
             'pandatime4'            :stats['pandatime4'],
             'pandatime5'            :stats['pandatime5'],
             'output_location'       :stats['outse'],
             'wallclock'             :stats['wallclock'],
             'arch'                  :stats['arch'],
             'percent_cpu'           :stats['percentcpu'],
             'numevents'             :stats['totalevents'],
             'NET_ETH_RX_PREATHENA'  :stats['NET_ETH_RX_PREATHENA'],
             'NET_ETH_RX_AFTERATHENA':stats['NET_ETH_RX_AFTERATHENA'],
             'inds'                  :inds,
             'outds'                 :outds,
             'reason'                :str(subjob.backend.reason).replace('\n',' '),
             'ganga_number_of_files' :innumfiles,
             }

  if subjob.backend._impl._name in ['LCG', 'CREAM']:
    logfile_guid = None
    logfile_loc = None
    for outfile in job.outputdata.output:
      if outfile.find('.log.tgz') != -1:
        logfile_guid = outfile.split(',')[2]
        logfile_loc = outfile.split(',')[5]
      if not stats['outse']:
        results['output_location'] = logfile_loc

    results['site'] = subjob.backend.requirements.sites[0]
    results['exit_status_1'] = subjob.backend.exitcode
    results['exit_status_2'] = stats['exitstatus']
    results['numfiles'] = stats['numfiles3']
    results['submit_time'] = None
    results['backendID'] = repr(subjob.backend.id)
    results['actual_ce'] = subjob.backend.actualCE
    results['logfile_guid'] = logfile_guid

    if subjob.status == 'running' and subjob.backend.status == 'Done (Success)':
      results['ganga_status'] = 'd'

  elif subjob.backend._impl._name == 'NG':

    sit = 'condor.titan.uio.no'
    if subjob.backend.CE:
      sit = subjob.backend.CE

    results['site'] = sit
    results['exit_status_1'] = stats['exitstatus']
    results['exit_status_2'] = stats['exitstatus']
    results['numfiles'] = stats['numfiles3']
    results['submit_time'] = None
    results['backendID'] = subjob.backend.id
    results['actual_ce'] = subjob.backend.actualCE
    results['logfile_guid'] = None

    if subjob.status == 'submitted' and not subjob.backend.status:
      results['ganga_status'] = 'n'

  elif subjob.backend._impl._name == 'Panda':
    try:
      results['pandatime1'] = int(stats['pandatime1'])
    except:
      pass
    try:
      results['pandatime2'] = int(stats['pandatime2'])
    except:
      pass
    try:
      results['pandatime3'] = int(stats['pandatime3'])
    except:
      pass
    try:
      results['pandatime4'] = int(stats['pandatime4'])
    except:
      pass
    try:
      results['pandatime5'] = int(stats['pandatime5'])
    except:
      pass

    results['site'] = jobToSite(subjob)
    results['exit_status_1'] = subjob.backend.exitcode
    results['exit_status_2'] = subjob.backend.piloterrorcode
    results['numfiles'] = innumfiles
    results['submit_time'] = stats['submittime']
    results['backendID'] = subjob.backend.id
    results['actual_ce'] = 'unknown'
    results['logfile_guid'] = None
    if subjob.backend.status == 'holding':
      results['ganga_status'] = 'h'
    try:
      if subjob.backend.status == 'defined' and job.backend.buildjobs[0].status == 'failed':
        results['ganga_status'] = 'k'
    except IndexError:
      pass


  if subjob.status == 'completing':
    results['ganga_status'] = 'g'

  #SITE
  if "'" in results['site']:
    results['site'] = results['site'].replace("'", '')

  try:
    results['site'] = Site.objects.filter(name=results['site'])[0]
  except:
    logger.warning('Could not find site %s' % (results['site']))
    return False

  #EVENTRATE
  if results['numevents'] != 'NULL' and results['wallclock'] != 'NULL':
    try:
      eventrate = float(results['numevents']) / float(results['wallclock'])
      results['eventrate'] = eventrate
    except:
      pass
      #logger.warning('Bug during sj eventrate')
                

  #EVENTS/ATHENA
  if results['numevents'] != 'NULL':

    time = 0
    if results['pandatime3'] != 'NULL':
      time = results['pandatime3']
    elif results['ganga_time_4'] != 'NULL' and results['ganga_time_3'] != 'NULL':
      time = results['ganga_time_4'] - results['ganga_time_3']

    if time:
      try:
        events_athena = float(results['numevents']) / float(time)
        results['events_athena'] = events_athena
      except:
        pass
        #logger.warning('Bug during sj event_athena')


  logger.debug('Writing to DB')

  result = test.getResults_for_test.filter(site__name=results['site'].name).filter(ganga_jobid=job.id).filter(ganga_subjobid=subjob.id)

  if result:
    result = result[0]
  else:
    try:
      result = Result(test=test, site=results['site'], ganga_jobid=job.id, ganga_subjobid=subjob.id)
    except:
      logger.warning('Error here!')

  for k, v in results.items():
    if k in value_types['DateTimeField'] and type(v) == types.StringType:
      if v:
        try:
          v = datetime.strptime(v, '%Y-%m-%d %H:%M:%S')
        except:
          logger.warning('Process_job(Str): %s %s' % (k, v))
      else:
        continue
    elif k in value_types['DateTimeField'] and (type(v) == types.IntType or type(v) == types.FloatType):
      if v:
        try:
          v = datetime.fromtimestamp(v)
        except:
          logger.warning('Process_job(Int): %s %s' % (k, v))
      else:
        continue
    elif k in value_types['DateTimeField']:
      continue

    if v and v != 'NULL':
      setattr(result, k, v)
#    elif v == 'NULL':
#      logger.info([k,v])

  if result.ganga_status in ('c', 'f'):
    #logger.warning('SubJob is in final state, marking row as fixed')
    result.fixed = 1

  result.save()

##
## SUMMARIZE
##

def summarize():
  logger.info('Summarize (using lib)')
  summary.summarize('atlas',test,completed=False)
  logger.info('Summarize ended')

##
## PLOT
##

def plot(completed=False):
  logger.info('Plot (using lib)')
  summary.plot('atlas',test,completed=completed)
  logger.info('Plot ended')
    #logger.info(value[0])    

##
## MAIN LOOP
##

logger.info('HammerCloud runtest.py started for test %d' % testid)

def hc_plot_summarize():
  test_sleep(60)
  while(not pt.should_stop()):
    logger.info('HC Plot and Summary thread init %s' % (datetime.now()))
    summarize()
    plot()
    logger.info('HC Plot and Summary thread end %s' % (datetime.now()))
    test_sleep(300)
  logger.info('HC Plot Summarize Thread: Disconnected.')

def hc_copy_thread():
  test_sleep(30)
  logger.info('HC Copy Thread: Connected to DB')
  while (test_active() and not test_paused() and not ct.should_stop()):
    logger.info('HC Copy Thread: TOP OF MAIN LOOP')
    for job in jobs:
      if not test_active() or test_paused() or ct.should_stop():
         break
      copyJob(job)
    test_sleep(10)

  logger.info('HC Copy Thread: Disconnected from DB')

ct = GangaThread(name="HCCopyThread", target=hc_copy_thread)
pt = GangaThread(name="HCPlotSummary", target=hc_plot_summarize)

logger.info('Connected to DB')

noJobs = False
hasSubjobs = False
for j in jobs:
  if len(j.subjobs):
    hasSubjobs = True
if hasSubjobs:
  ct.start()
  pt.start()
  while (test_active() and not test_paused()):

    #We need to refresh the test object
    test = Test.objects.get(pk=testid) #select_related('template', 'metricperm__index', 'metricperm__summary', 'metricperm__pertab').get(pk=testid)

    try:
      print_summary()
    except:
      logger.warning('Bug during print_summary')
      logger.warning(sys.exc_info()[0])
      logger.warning(sys.exc_info()[1])
    for job in jobs:
      try:
        process_job(job)
      except:
        logger.warning('Exception in process_job:')
        logger.warning(sys.exc_info()[0])
        logger.warning(sys.exc_info()[1])
      for subjob in job.subjobs:
        try:
          process_subjob(job, subjob)
        except:
          logger.warning('Exception in process_subjob:')
          logger.warning(sys.exc_info()[0])
          logger.warning(sys.exc_info()[1])
        if test_paused():
          break
   
    test_sleep(20)
else:
  noJobs = True
  logger.warning('No jobs to monitor. Exiting now.')

#Stop plotting and summarizing thread.
pt.stop()

paused = test_paused()

if not paused:
  if noJobs:
    test.state = 'error'
  else:
    test.state = "completed"
  test.endtime = datetime.now()
  test.save()
  logger.info('Test state updated to %s' % (test.state))

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
logger.info('But before, the last plots...')

summarize()
plot(True)

logger.info('Over and out. Have a good day.')
