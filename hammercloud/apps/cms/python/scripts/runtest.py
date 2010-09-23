# HammerCloud runtest-cms.py
#
# Runs in a single ganga session to sleep, write changes to the db, and kill
# leftovers after the test completes 

import os,time,sys,commands,random,datetime
import hcutil
import Ganga.Utility.Config
from Ganga.Core.GangaThread import GangaThread
from Ganga.Utility.logging import getLogger
from urllib2 import URLError,HTTPError,Request,urlopen
logger = getLogger()


def test_active(cursor):
    cursor.execute('select starttime<now(),endtime>now() from test where id=%s'%testid)
    r = cursor.fetchone()
    if r[0] and r[1]:
        logger.debug('Test %d is active'%testid)
        return True
    elif not r[0]:
        logger.info('Test %d has not yet started'%testid)
    elif not r[1]:
        logger.info('Test %d has completed'%testid)
    return False

def test_paused(cursor):
    cursor.execute('select pause from test where id=%s'%testid)
    r = cursor.fetchone()
    if r[0]:
        logger.info('Test %d is paused'%testid)
        return True
    return False

def updateDatasets(cursor,site):
 
    patterns = []
   
    cursor.execute("select dspattern.pattern from dspattern,test_dspattern where test_dspattern.test=%d and test_dspattern.dspattern=dspattern.id"%testid)
    patterns = cursor.fetchall()    

#    logger.warning(patterns)

    datasets = []

    for pattern in patterns:
    
        dataset = ''

#        logger.warning(pattern[0])

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
        
def _copyJob(cursor,job,site):
    logger.info('Copying job %d'%job.id)
    nRetries = 3
    try:
        j=job.copy()
        previous_datasetpath = j.inputdata.datasetpath
        logger.info('Previous input datasets = %s'%previous_datasetpath)
 
        # ONLY ONE DATASET PER JOB !
        num = 1

        #try:
        #    cursor.execute("select num_datasets_per_bulk from test_site,site where site.name='%s' and site.id=test_site.site and test_site.test=%s"%(site,testid))
        #    num = cursor.fetchone()[0]
        #except:
        #    num = len(j.inputdata.datasetpath)
   
        try:
            j.inputdata.datasetpath = updateDatasets(cursor,site)
        except:
            logger.warning('Unexpected error:'+str(sys.exc_info()[0]))
            logger.warning('Failed to get new datasets. Using previous datasets.')
            j.inputdata.datasetpath = previous_datasetpath

        logger.info('New input datasets = %s'%j.inputdata.datasetpath)
        j.submit()

        cursor.execute('insert test_state set test=%s, ganga_jobid=%s, copied=1 on duplicate key update copied=1'%(testid,job.id))
        logger.warning('Finished copying job %d'%job.id)
        return
    except:
        logger.warning('Failed to submit job %d for %s. Retrying %d more times.'%(j.id,site,nRetries))
        logger.warning(sys.exc_info()[0])
        logger.warning(sys.exc_info()[1])
        for i in xrange(nRetries):
            try:
                j.submit()
                cursor.execute('insert test_state set test=%s, ganga_jobid=%s, copied=1 on duplicate key update copied=1'%(testid,job.id))
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
    cursor.execute('update test_site set resubmit_enabled=0 where test=%s and site in (select id from site where name=\'%s\')'%(testid,site))

# We copy a job under these circumstances:
#  1. test_site.resubmit_enabled is True and test_state(test,jobid).copied is False and #submitted < 30% and #failed < 70%
#
# We also do the following:
#  1. If #failed > 70%, set test_site.resubmit_enabled to False
#  2. If a job is copied, set test_state(test,jobid).copied to True
#
def copyJob(cursor,job):

#    site = job.backend.actualCE
    site = job.inputdata.CE_white_list

    logger.debug('copyJob called for job %d at site %s'%(job.id,site))
    try:
        cursor.execute('select test_site.resubmit_enabled,test_site.resubmit_force,test_site.min_queue_depth,test_site.max_running_jobs from test_site,site where site.name=\'%s\' and site.id=test_site.site and test_site.test=%s'%(site,testid))
        (enabled,force,min_queue_depth,max_running_jobs) = cursor.fetchone()
        
    except:
        logger.warning('failed to copyJob id %d site %s'%(job.id,site))
        return 


    if force:
        logger.info('Forced copy')
        _copyJob(cursor,job,site)
        logger.debug('Setting test_site.resubmit_force=0 to prevent flood.')
        cursor.execute('update test_site set resubmit_force=0 where test=%s and site in (select id from site where name=\'%s\')'%(testid,site))
        return

    if not enabled:
        logger.debug('Not copying job %d: test_site.resubmit_enabled is False for test %d at %s'%(job.id,testid,site))
        return

    cursor.execute('select copied from test_state where test=%s and ganga_jobid=%s'%(testid,job.id))
    try:
        if cursor.fetchone()[0]:
   	    logger.debug('Not copying job %d: test_state(test,jobid).copied is True'%job.id)
            return
    except:
        pass

    # submitted
    cursor.execute("select count(*) from result where (ganga_status='s') and test=%s and site='%s'"%(testid,site)); 
    submitted = cursor.fetchone()[0]

    # running 
    cursor.execute("select count(*) from result where (ganga_status='r') and test=%s and site='%s'"%(testid,site)); 
    running = cursor.fetchone()[0]

    if submitted > min_queue_depth:
        logger.debug('Not copying job %d: %d submitted > q.d %d'%(job.id,submitted,min_queue_depth))
        return
   
    if running > max_running_jobs:
        logger.debug('Not copying job %d: %d running > %d max'%(job.id,running,max_running_jobs))
        return
    
    if len(job.subjobs) < 1:
        logger.debug('Job %d has 0 subjobs. Not copying.'%job.id)
        return

    # total last 3 hours
    cursor.execute("select count(*) from result where (ganga_status='f' or ganga_status='c') and mtime>date_sub(now(),interval 1 hour) and test=%s and site='%s'"%(testid,site)); 
    total = cursor.fetchone()[0]

    # failed last 3 hours
    cursor.execute("select count(*) from result where (ganga_status='f') and mtime>date_sub(now(),interval 1 hour) and test=%s and site='%s'"%(testid,site)); 
    failed = cursor.fetchone()[0]
   
    if total>20: 
        if float(failed)/float(total) > 0.7:
            logger.warning('Not copying job %d: %d failed from %d finished (copy when <= 0.7)'%(job.id,failed,total))
            logger.warning('Disabling site %s: test_site.resubmit_enabled <- 0'%site)
            cursor.execute('update test_site set resubmit_enabled=0 where test=%s and site in (select id from site where name=\'%s\')'%(testid,site))
            return

    logger.warning('Job %d at %s ran the gauntlet: %d submitted, %d running, %d failed, %d finished'%(job.id,site,submitted,running,failed,total))
    _copyJob(cursor,job,site)
    return
    

lastsummary=0
def print_summary(cursor):
    global lastsummary
    if time.time()<lastsummary+300:
        return
    lastsummary=time.time()
    logger.info('JOB SUMMARY:')

    active = 0
    for j in jobs:    

#        site = jobToSite(j)
#        site = j.backend.actualCE        
        site = j.inputdata.CE_white_list

        t = len(j.subjobs)
        s = len(j.subjobs.select(status='submitted'))
        r = len(j.subjobs.select(status='running'))
        c = len(j.subjobs.select(status='completed'))
        f = len(j.subjobs.select(status='failed'))
        active = active + s + r
        cursor.execute('select copied from test_state where test=%s and ganga_jobid=%s'%(testid,j.id))
        copied = 0
        try:
            if cursor.fetchone()[0]:
                copied = 1
        except:
            pass

        logger.info('Job %d: %s t:%d s:%d r:%d c:%d f:%d copied:%d'%(j.id,site,t,s,r,c,f,copied))
    
    logger.info('NUM JOBS TO BE MONITORED: %d'%active)

#    try:
#        from Ganga.Lib.LCG.LCG import *
#        downloader = get_lcg_output_downloader()
#        logger.info('NUM JOBS IN DOWNLOAD QUEUE: %d'%downloader.data.queue.qsize())
#    except:
#        pass

    logger.info('PROGRESS ON UNCOPIED JOBS:')
    for j in jobs:
        cursor.execute('select copied from test_state where test=%s and ganga_jobid=%s'%(testid,j.id))
        try:
            if cursor.fetchone()[0]:
                continue
        except:
            pass

#        site = j.backend.actualCE
        site = j.inputdata.CE_white_list     

        t = len(j.subjobs)
        s = len(j.subjobs.select(status='submitted'))
        r = len(j.subjobs.select(status='running'))
        c = len(j.subjobs.select(status='completed'))
        f = len(j.subjobs.select(status='failed'))

        logger.info('UNCOPIED Job %d: %s t:%d s:%d r:%d c:%d f:%d'%(j.id,site,t,s,r,c,f))

def test_sleep(t):
    logger.debug('Sleeping %d seconds'%t)
    time.sleep(t)

def process_subjob(cursor,job,subjob):
    logger.debug('Processing jobs(%d).subjobs(%d) with status %s'%(job.id,subjob.id,subjob.status))

    # return if result is already fixed
    cursor.execute('select fixed from result where test=%d and ganga_jobid=%d and ganga_subjobid=%d'%(testid,job.id,subjob.id))
    try:
        if int(cursor.fetchone()[0]):
            logger.debug('subjob result is already fixed in database... skipping')
            return False
    except: 
        pass

# NOT NEEDED NOW
#    if (subjob.status=='completed' and not subjob.application.stats) or subjob.status=='failed':
#        logger.warning('Forced postprocess')
#        try:
#            subjob.application.postprocess()
#        except:
#            logger.warning('Error in postprocess')
#            logger.warning(sys.exc_info()[0])
#            logger.warning(sys.exc_info()[1])

#    stats = {}
#    try:
#        stats = subjob.application.stats
#    except:
#        pass

#    config = Ganga.Utility.Config.getConfig('Metrics')
#    location = config['location']
#    if not os.path.exists(location):
#        return False
#    config = ConfigParser()
#    config.read(location)

    #Iterate over all them
    #SECTIONS = config.sections()
    
    results = {}

#    # Only five sections work here...
#    if subjob.backend.fjr.has_key('CrabTiming'):
#        for n,v in config.items('CrabTiming'):
#            metrics[n]=v  

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

#    for m in metrics:
#        try:
#            x = stats[m]
#        except KeyError:
#            #stats[m]='NULL'
#            if m in ['wrapperexitcode','exeexitcode','stageouttime','wrappertime','exetime','usercputime','syscputime','cpupercentage']:
#                stats[m] = -1
#            elif m in ['starttime','submittingtime','submittime','runningtime','endtime']:
#                stats[m] = datetime.datetime(1970,1,1,0,0,0)
#            else:
#                stats[m] = 'NULL'         

    # fill vals array
    try:

        vals = [testid,job.id,subjob.id,subjob.status[0],subjob.inputdata.CE_white_list]+[v for k,v in results.items()]    
        
    except:
        logger.warning("Error in metric values: skipping this subjob")
        logger.warning(sys.exc_info()[0])
        logger.warning(sys.exc_info()[1])
        return False

#    if subjob.status=='completing':
#        vals[3]='g'

#    logger.warning(vals)
  
    logger.debug('Writing to DB') 
    try: # insert new result 
        
        fields = ','.join([k for k in results.keys()])
        values = ','.join(['%s' for i in xrange(0,len(results))])

        if fields:
          fields = ','+fields

        if values:
          values = ','+values        

        cmd = "insert result (test,ganga_jobid,ganga_subjobid,ganga_status,site"+fields+") values (%s,%s,%s,%s,%s"+values+")"
#        logger.warning(cmd)    
        cursor.execute(cmd,vals)
#        logger.info('New row inserted')
    except: # update existing result

        field_value = ', '.join([str(k)+'=%s' for k in results.keys()])

        if field_value:
          field_value = ','+field_value

        cmd = "update result set ganga_status=%s,site=%s"+field_value+" where test=%s and ganga_jobid=%s and ganga_subjobid=%s";  
#        logger.warning(cmd)
        val = vals[3:]+vals[0:3]
        cursor.execute(cmd,val)
#        logger.info('Existing row updated')
    
    if subjob.status in ('completed','failed'):
        logger.debug('Subjob is in final state, marking row as fixed')
        cursor.execute('update result set fixed=1 where test=%d and ganga_jobid=%d and ganga_subjobid=%d'%(testid,job.id,subjob.id))

# MAIN LOOP

try:
    testid = int(sys.argv[1])
except IndexError:
    print "testid required"
    sys.exit()

logger.info('HammerCloud runtest-cms.py started for test %d'%testid)

def hc_copy_thread():
    test_sleep(60)
    conn2 = hcutil.connect()
    cursor2 = conn2.cursor ()
    logger.info('HC Copy Thread: Connected to DB')
    while (test_active(cursor2) and not test_paused(cursor2) and not ct.should_stop()):
        logger.debug('HC Copy Thread: TOP OF MAIN LOOP')
        for job in jobs:
            if test_paused(cursor2) or ct.should_stop():
                break
            copyJob(cursor2,job)
            conn2.commit()
#        conn2.commit()
        test_sleep(10)
    cursor2.close ()
    conn2.commit()
    conn2.close()
    logger.info('HC Copy Thread: Disconnected from DB')

ct = GangaThread(name="HCCopyThread", target=hc_copy_thread)

conn = hcutil.connect()
cursor = conn.cursor ()
logger.info('Connected to DB')

if len(jobs):
    ct.start()
    while (test_active(cursor) and not test_paused(cursor)):
        try:
            print_summary(cursor)
        except:
            logger.warning('Bug during print_summary')
            logger.warning(sys.exc_info()[0])
            logger.warning(sys.exc_info()[1])
        for job in jobs:
            for subjob in job.subjobs:
                try:
                    process_subjob(cursor,job,subjob)
                    conn.commit()
                except:
                    logger.warning('Exception in process_subjob:')
                    logger.warning(sys.exc_info()[0])
                    logger.warning(sys.exc_info()[1])
            conn.commit()
            if test_paused(cursor):
                break
        conn.commit()
        test_sleep(10)
else:
    logger.warning('No jobs to monitor. Exiting now.')

paused = test_paused(cursor)
cursor.execute('update test set pause=0 where test.id=%d'%testid)
if not paused:
    cursor.execute("update test set state='completed',endtime=now() where test.id=%d"%testid)
cursor.close ()
conn.commit()
conn.close()
logger.info('Disconnected from DB')

if not paused:
    logger.info('Killing leftover "submitted" jobs')
    jobs.select(status='submitted').kill()
    logger.info('Killing leftover "running" jobs')
    jobs.select(status='running').kill()


logger.info('HammerCloud runtest.py exiting')
