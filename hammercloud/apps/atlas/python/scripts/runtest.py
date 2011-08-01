# HammerCloud runtest.py
#
# Runs in a single ganga session to sleep, write changes to the db, and kill
# leftovers after the test completes 

import os,time,sys,hcutil,commands
from Ganga.Core.GangaThread import GangaThread
from Ganga.Utility.logging import getLogger
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

def updateDatasets(cursor,site,num):
    from dq2.clientapi.DQ2 import DQ2
    dq2=DQ2()

    # get DDM name from site
    cursor.execute ("select ddm from site where name='%s'"%site)
    location = cursor.fetchall()[0][0]
    locations = location.split(',')

    # Dataset patterns
    datasetpatterns = []
    cursor.execute("select dspattern.pattern from dspattern,test_dspattern where test_dspattern.test=%d and test_dspattern.dspattern=dspattern.id"%testid)
    rows = cursor.fetchall()
    for row in rows:
        if row[0].startswith('/'):
            file = open(row[0])
            for l in file:
                datasetpatterns.append(l.strip())
            file.close()
        else:
            datasetpatterns.append(row[0])

    # get list of datasets
    datasets = []
    for location in locations:
        for datasetpattern in datasetpatterns:
            temp = list(dq2.listDatasetsByNameInSite(site=location, name=datasetpattern))
            datasets = datasets + temp

    from random import shuffle
    shuffle(datasets)

    gooddatasets = []
    for location in locations:
        for dataset in datasets:
            try:
                # check if frozen and complete
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
                if len(gooddatasets)>=num:
                    return gooddatasets
                    
            except:
                continue

    return gooddatasets
    
def _copyJob(cursor,job,site):
    logger.info('Copying job %d'%job.id)
    nRetries = 3
    try:
        j=job.copy()
        uuid = commands.getoutput('uuidgen')[0:3]
        t = int(time.time())
        j.outputdata.datasetname='hc.%d.%s.%s.%s'%(testid,site,t,uuid)
        j.outputdata.location=''
        previous_datasets = j.inputdata.dataset
        logger.info('Previous input datasets = %s'%previous_datasets)
        try:
            cursor.execute("select num_datasets_per_bulk from test_site,site where site.name='%s' and site.id=test_site.site and test_site.test=%s"%(site,testid))
            num = cursor.fetchone()[0]
        except:
            num = len(j.inputdata.dataset)
    
        try:
            j.inputdata.dataset = updateDatasets(cursor,site,num)
        except:
            logger.warning('Failed to get new datasets from DQ2. Using previous datasets.')
            j.inputdata.dataset = previous_datasets[0:num]

        logger.info('New input datasets = %s'%j.inputdata.dataset)
        j.submit()
        cursor.execute('insert test_state set test=%s, ganga_jobid=%s, copied=1 on duplicate key update copied=1'%(testid,job.id))
        logger.info('Finished copying job %d'%job.id)
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

def jobToSite(job):
    siteMap = {
      'ANALY_LONG_LYON': 'ANALY_LYON',
      'ANALY_LONG_BNL_ATLAS': 'ANALY_BNL_ATLAS_1',
      'ANALY_LONG_LYON_DCACHE': 'ANALY_LYON_DCACHE'
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
        logger.error('Could not detect site for job %d. Leaving copyJob. %s'%(job.id,job.backend))
    return site

# We copy a job under these circumstances:
#  1. test_site.resubmit_enabled is True and test_state(test,jobid).copied is False and #submitted < 30% and #failed < 70%
#
# We also do the following:
#  1. If #failed > 70%, set test_site.resubmit_enabled to False
#  2. If a job is copied, set test_state(test,jobid).copied to True
#
def copyJob(cursor,job):
    site = jobToSite(job)

#    logger.warning('copyJob called for job %d at site %s'%(job.id,site))
    try:
        cursor.execute('select test_site.resubmit_enabled,test_site.resubmit_force,test_site.min_queue_depth,test_site.max_running_jobs from test_site,site where site.name=\'%s\' and site.id=test_site.site and test_site.test=%s'%(site,testid))
        (enabled,force,min_queue_depth,max_running_jobs) = cursor.fetchone()
    except:
        logger.warning('failed to copyJob id %d site %s'%(job.id,site))
        return 

    if force:
        logger.info('Forced copy')
        _copyJob(cursor,job,site)
        logger.info('Setting test_site.resubmit_force=0 to prevent flood.')
    	cursor.execute('update test_site set resubmit_force=0 where test=%s and site in (select id from site where name=\'%s\')'%(testid,site))
        return

    if not enabled:
        #logger.info('Not copying job %d: test_site.resubmit_enabled is False for test %d at %s'%(job.id,testid,site))
        return

    cursor.execute('select copied from test_state where test=%s and ganga_jobid=%s'%(testid,job.id))
    try:
        if cursor.fetchone()[0]:
#       	    logger.warning('Not copying job %d: test_state(test,jobid).copied is True'%job.id)
            return
    except:
        pass

    # submitted
    cursor.execute("select count(*) from result where (ganga_status='s') and test=%s and site='%s' and ganga_subjobid!=1000000"%(testid,site)); 
    submitted = cursor.fetchone()[0]

    # running 
    cursor.execute("select count(*) from result where (ganga_status='r') and test=%s and site='%s' and ganga_subjobid!=1000000"%(testid,site)); 
    running = cursor.fetchone()[0]

    if submitted > min_queue_depth:
        #logger.info('Not copying job %d: %d submitted > q.d %d'%(job.id,submitted,min_queue_depth))
        return
   
    if running > max_running_jobs:
        #logger.info('Not copying job %d: %d running > %d max'%(job.id,running,max_running_jobs))
        return
    
    if len(job.subjobs) < 1:
        logger.warning('Job %d has 0 subjobs. Not copying.'%job.id)
        return

    if job.backend._impl._name == 'Panda':
        if job.backend.buildjob and job.backend.buildjob.status not in ['finished','failed']:
            logger.warning('Job %d has an incomplete buildjob. Not copying.'%job.id)
            return
        #elif len(job.backend.buildjobs) > 1 and job.backend.buildjobs[0].status not in ['finished','failed']:
        #    logger.warning('Job %d has an incomplete buildjob. Not copying.'%job.id)
        #    return

    # total last 3 hours
    cursor.execute("select count(*) from result where (ganga_status='f' or ganga_status='c') and mtime>date_sub(now(),interval 1 hour) and test=%s and site='%s' and ganga_subjobid!=1000000"%(testid,site)); 
    total = cursor.fetchone()[0]

    # failed last 3 hours
    cursor.execute("select count(*) from result where (ganga_status='f') and mtime>date_sub(now(),interval 1 hour) and test=%s and site='%s' and ganga_subjobid!=1000000"%(testid,site)); 
    failed = cursor.fetchone()[0]
   
    if total>20: 
        if float(failed)/float(total) > 0.7:
            logger.warning('Not copying job %d: %d failed from %d finished (copy when <= 0.7)'%(job.id,failed,total))
            logger.warning('Disabling site %s: test_site.resubmit_enabled <- 0'%site)
            cursor.execute('update test_site set resubmit_enabled=0 where test=%s and site in (select id from site where name=\'%s\')'%(testid,site))
            return

    logger.info('Job %d at %s ran the gauntlet: %d submitted, %d running, %d failed, %d finished'%(job.id,site,submitted,running,failed,total))
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
        site = jobToSite(j)
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

    try:
        from Ganga.Lib.LCG.LCG import *
        downloader = get_lcg_output_downloader()
        logger.info('NUM JOBS IN DOWNLOAD QUEUE: %d'%downloader.data.queue.qsize())
    except:
        pass

    logger.info('PROGRESS ON UNCOPIED JOBS:')
    for j in jobs:
        cursor.execute('select copied from test_state where test=%s and ganga_jobid=%s'%(testid,j.id))
        try:
            if cursor.fetchone()[0]:
                continue
        except:
            pass

        site = jobToSite(j)
        t = len(j.subjobs)
        s = len(j.subjobs.select(status='submitted'))
        r = len(j.subjobs.select(status='running'))
        c = len(j.subjobs.select(status='completed'))
        f = len(j.subjobs.select(status='failed'))

        logger.info('UNCOPIED Job %d: %s t:%d s:%d r:%d c:%d f:%d'%(j.id,site,t,s,r,c,f))

def test_sleep(t):
    #logger.info('Sleeping %d seconds'%t)
    time.sleep(t)

def process_job(cursor,job):
    logger.debug('Processing jobs(%d) with status %s'%(job.id,job.status))

    # return if result is already fixed
    cursor.execute('select fixed from result where test=%d and ganga_jobid=%d and ganga_subjobid=1000000'%(testid,job.id))
    try:
        if int(cursor.fetchone()[0]):
            logger.debug('master job result is already fixed in database... skipping')
            return False
    except: 
        pass

    stats = {}
    try:
        stats = job.application.stats
    except:
        pass
    metrics = ['percentcpu','systemtime','usertime','site','totalevents','wallclock','stoptime','outse','starttime','exitstatus','numfiles3','gangatime1','gangatime2','gangatime3','gangatime4','gangatime5','jdltime','NET_ETH_RX_PREATHENA','NET_ETH_RX_AFTERATHENA','pandatime1','pandatime2','pandatime3','pandatime4','pandatime5','arch','submittime']
    for m in metrics:
        try:
            x = stats[m]
        except KeyError:
            stats[m]='NULL'
   
    outds='NULL'
    try:
        outds=job.outputdata.datasetname
    except:
        pass

    inds='NULL'
    try:
        inds=job.inputdata.dataset[0]
    except:
        pass

    innumfiles=0
    try:
        innumfiles=job.inputdata.number_of_files
    except:
        pass

    # fill vals array
    try:
        if job.backend._impl._name in [ 'LCG', 'CREAM']:
            logfile_guid=None
            for outfile in job.outputdata.output:
                if outfile.find('.log.tgz')!=-1:
                    logfile_guid=outfile.split(',')[2]
            vals = [testid,job.id,1000000,job.status[0],job.backend.requirements.sites[0],job.backend.exitcode,stats['exitstatus'],inds,outds,stats['outse'],'NULL',stats['starttime'],stats['wallclock'],stats['totalevents'],stats['numfiles3'],stats['percentcpu'],stats['stoptime'],stats['gangatime1'],stats['gangatime2'],stats['gangatime3'],stats['gangatime4'],stats['gangatime5'],stats['jdltime'],innumfiles,repr(job.backend.id),job.backend.reason,stats['NET_ETH_RX_PREATHENA'],stats['NET_ETH_RX_AFTERATHENA'],stats['pandatime1'],stats['pandatime2'],stats['pandatime3'],stats['pandatime4'],stats['pandatime5'],stats['arch'],job.backend.actualCE,logfile_guid]
            if job.status=='running' and job.backend.status=='Done (Success)':
                vals[3] = 'd'
        elif job.backend._impl._name == 'NG':
            sit = 'condor.titan.uio.no'
            if job.backend.CE:
                sit = job.backend.CE
            vals = [testid,job.id,1000000,job.status[0],sit,stats['exitstatus'],stats['exitstatus'],inds,outds,stats['outse'],'NULL',stats['starttime'],stats['wallclock'],stats['totalevents'],stats['numfiles3'],stats['percentcpu'],stats['stoptime'],stats['gangatime1'],stats['gangatime2'],stats['gangatime3'],stats['gangatime4'],stats['gangatime5'],stats['jdltime'],innumfiles,job.backend.id,job.backend.reason,stats['NET_ETH_RX_PREATHENA'],stats['NET_ETH_RX_AFTERATHENA'],stats['pandatime1'],stats['pandatime2'],stats['pandatime3'],stats['pandatime4'],stats['pandatime5'],stats['arch'],job.backend.actualCE,None]
            if job.status=='submitted' and not job.backend.status:
                vals[3] = 'n'
        elif job.backend._impl._name == 'Panda':
            vals = [testid,job.id,1000000,job.status[0],jobToSite(job),job.backend.exitcode,job.backend.piloterrorcode,inds,outds,stats['outse'],stats['submittime'],stats['starttime'],stats['wallclock'],stats['totalevents'],innumfiles,stats['percentcpu'],stats['stoptime'],stats['gangatime1'],stats['gangatime2'],stats['gangatime3'],stats['gangatime4'],stats['gangatime5'],stats['jdltime'],innumfiles,job.backend.id,job.backend.reason,stats['NET_ETH_RX_PREATHENA'],stats['NET_ETH_RX_AFTERATHENA'],stats['pandatime1'],stats['pandatime2'],stats['pandatime3'],stats['pandatime4'],stats['pandatime5'],stats['arch'],'unknown',None]
    except:
        logger.warning("Error in metric values: skipping this job")
        logger.warning(sys.exc_info()[0])
        logger.warning(sys.exc_info()[1])
        return False

    if job.status=='completing':
        vals[3]='g'
  
    logger.debug('Writing to DB') 
    try: # insert new result 
        cmd = "insert result (test,ganga_jobid,ganga_subjobid,ganga_status,site,exit_status_1,exit_status_2,inds,outds,output_location,submit_time,start_time,wallclock,numevents,numfiles,percent_cpu,stop_time,ganga_time_1,ganga_time_2,ganga_time_3,ganga_time_4,ganga_time_5,jdl_time,ganga_number_of_files,backend_id,backend_reason,net_eth_rx_preathena,net_eth_rx_postathena,pandatime1,pandatime2,pandatime3,pandatime4,pandatime5,arch,actual_ce,logfile_guid) values (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,from_unixtime(%s),from_unixtime(%s),%s,%s,%s,%s,from_unixtime(%s),from_unixtime(%s),from_unixtime(%s),from_unixtime(%s),from_unixtime(%s),from_unixtime(%s),from_unixtime(%s),%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)"
        cursor.execute(cmd,vals)
        logger.debug('New row inserted')
    except: # update existing result
        cmd = "update result set ganga_status=%s,site=%s,exit_status_1=%s,exit_status_2=%s,inds=%s,outds=%s,output_location=%s,submit_time=from_unixtime(%s),start_time=from_unixtime(%s),wallclock=%s,numevents=%s,numfiles=%s,percent_cpu=%s,stop_time=from_unixtime(%s),ganga_time_1=from_unixtime(%s),ganga_time_2=from_unixtime(%s),ganga_time_3=from_unixtime(%s),ganga_time_4=from_unixtime(%s),ganga_time_5=from_unixtime(%s),jdl_time=from_unixtime(%s),ganga_number_of_files=%s,backend_id=%s,backend_reason=%s,net_eth_rx_preathena=%s,net_eth_rx_postathena=%s,pandatime1=%s,pandatime2=%s,pandatime3=%s,pandatime4=%s,pandatime5=%s,arch=%s,actual_ce=%s,logfile_guid=%s where test=%s and ganga_jobid=%s and ganga_subjobid=%s";
        val = vals[3:]+vals[0:3]
        cursor.execute(cmd,val)
        logger.debug('Existing row updated')
    
    if job.status in ('completed','failed'):
        logger.debug('Job is in final state, marking row as fixed')
        cursor.execute('update result set fixed=1 where test=%d and ganga_jobid=%d and ganga_subjobid=1000000'%(testid,job.id))



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

#    if subjob.status in ('completed','failed'):# and not subjob.application.stats:
    if (subjob.status=='completed' and not subjob.application.stats) or subjob.status=='failed':
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
        pass
    metrics = ['percentcpu','systemtime','usertime','site','totalevents','wallclock','stoptime','outse','starttime','exitstatus','numfiles3','gangatime1','gangatime2','gangatime3','gangatime4','gangatime5','jdltime','NET_ETH_RX_PREATHENA','NET_ETH_RX_AFTERATHENA','pandatime1','pandatime2','pandatime3','pandatime4','pandatime5','arch','submittime']
    for m in metrics:
        try:
            x = stats[m]
        except KeyError:
            stats[m]='NULL'
   
    outds='NULL'
    try:
        outds=subjob.outputdata.datasetname
    except:
        pass

    inds='NULL'
    try:
        inds=subjob.inputdata.dataset[0]
    except:
        pass

    innumfiles=0
    try:
        innumfiles=subjob.inputdata.number_of_files
    except:
        pass

    # fill vals array
    try:
        if subjob.backend._impl._name in [ 'LCG', 'CREAM' ]:
            logfile_guid=None
            for outfile in subjob.outputdata.output:
                if outfile.find('.log.tgz')!=-1:
                    logfile_guid=outfile.split(',')[2]
            vals = [testid,job.id,subjob.id,subjob.status[0],subjob.backend.requirements.sites[0],subjob.backend.exitcode,stats['exitstatus'],inds,outds,stats['outse'],'NULL',stats['starttime'],stats['wallclock'],stats['totalevents'],stats['numfiles3'],stats['percentcpu'],stats['stoptime'],stats['gangatime1'],stats['gangatime2'],stats['gangatime3'],stats['gangatime4'],stats['gangatime5'],stats['jdltime'],innumfiles,subjob.backend.id,subjob.backend.reason,stats['NET_ETH_RX_PREATHENA'],stats['NET_ETH_RX_AFTERATHENA'],stats['pandatime1'],stats['pandatime2'],stats['pandatime3'],stats['pandatime4'],stats['pandatime5'],stats['arch'],subjob.backend.actualCE,logfile_guid]
            if subjob.status=='running' and subjob.backend.status=='Done (Success)':
                vals[3] = 'd'
        elif subjob.backend._impl._name == 'NG':
            sit = 'condor.titan.uio.no'
            if subjob.backend.CE:
                sit = subjob.backend.CE
            vals = [testid,job.id,subjob.id,subjob.status[0],sit,stats['exitstatus'],stats['exitstatus'],inds,outds,stats['outse'],'NULL',stats['starttime'],stats['wallclock'],stats['totalevents'],stats['numfiles3'],stats['percentcpu'],stats['stoptime'],stats['gangatime1'],stats['gangatime2'],stats['gangatime3'],stats['gangatime4'],stats['gangatime5'],stats['jdltime'],innumfiles,subjob.backend.id,subjob.backend.reason,stats['NET_ETH_RX_PREATHENA'],stats['NET_ETH_RX_AFTERATHENA'],stats['pandatime1'],stats['pandatime2'],stats['pandatime3'],stats['pandatime4'],stats['pandatime5'],stats['arch'],subjob.backend.actualCE,None]
            if subjob.status=='submitted' and not subjob.backend.status:
                vals[3] = 'n'
        elif subjob.backend._impl._name == 'Panda':
#            if subjob.backend.actualCE != 'ANALY_ARC':
            vals = [testid,job.id,subjob.id,subjob.status[0],jobToSite(subjob),subjob.backend.exitcode,subjob.backend.piloterrorcode,inds,outds,stats['outse'],stats['submittime'],stats['starttime'],stats['wallclock'],stats['totalevents'],innumfiles,stats['percentcpu'],stats['stoptime'],stats['gangatime1'],stats['gangatime2'],stats['gangatime3'],stats['gangatime4'],stats['gangatime5'],stats['jdltime'],innumfiles,subjob.backend.id,subjob.backend.reason,stats['NET_ETH_RX_PREATHENA'],stats['NET_ETH_RX_AFTERATHENA'],stats['pandatime1'],stats['pandatime2'],stats['pandatime3'],stats['pandatime4'],stats['pandatime5'],stats['arch'],'unknown',None]
#            else:
                #vals = [testid,job.id,subjob.id,subjob.status[0],subjob.backend.jobSpec['computingElement'],subjob.backend.exitcode,subjob.backend.piloterrorcode,subjob.inputdata.dataset[0],outds,stats['outse'],stats['submittime'],stats['starttime'],stats['wallclock'],stats['totalevents'],subjob.inputdata.number_of_files,stats['percentcpu'],stats['stoptime'],stats['gangatime1'],stats['gangatime2'],stats['gangatime3'],stats['gangatime4'],stats['gangatime5'],stats['jdltime'],subjob.inputdata.number_of_files,subjob.backend.id,subjob.backend.reason,stats['NET_ETH_RX_PREATHENA'],stats['NET_ETH_RX_AFTERATHENA'],stats['pandatime1'],stats['pandatime2'],stats['pandatime3'],stats['pandatime4'],stats['arch']]
    except:
        logger.warning("Error in metric values: skipping this subjob")
        logger.warning(sys.exc_info()[0])
        logger.warning(sys.exc_info()[1])
        return False

    if subjob.status=='completing':
        vals[3]='g'
  
    logger.debug('Writing to DB') 
    try: # insert new result 
        cmd = "insert result (test,ganga_jobid,ganga_subjobid,ganga_status,site,exit_status_1,exit_status_2,inds,outds,output_location,submit_time,start_time,wallclock,numevents,numfiles,percent_cpu,stop_time,ganga_time_1,ganga_time_2,ganga_time_3,ganga_time_4,ganga_time_5,jdl_time,ganga_number_of_files,backend_id,backend_reason,net_eth_rx_preathena,net_eth_rx_postathena,pandatime1,pandatime2,pandatime3,pandatime4,pandatime5,arch,actual_ce,logfile_guid) values (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,from_unixtime(%s),from_unixtime(%s),%s,%s,%s,%s,from_unixtime(%s),from_unixtime(%s),from_unixtime(%s),from_unixtime(%s),from_unixtime(%s),from_unixtime(%s),from_unixtime(%s),%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)"
        cursor.execute(cmd,vals)
        logger.debug('New row inserted')
    except: # update existing result
        cmd = "update result set ganga_status=%s,site=%s,exit_status_1=%s,exit_status_2=%s,inds=%s,outds=%s,output_location=%s,submit_time=from_unixtime(%s),start_time=from_unixtime(%s),wallclock=%s,numevents=%s,numfiles=%s,percent_cpu=%s,stop_time=from_unixtime(%s),ganga_time_1=from_unixtime(%s),ganga_time_2=from_unixtime(%s),ganga_time_3=from_unixtime(%s),ganga_time_4=from_unixtime(%s),ganga_time_5=from_unixtime(%s),jdl_time=from_unixtime(%s),ganga_number_of_files=%s,backend_id=%s,backend_reason=%s,net_eth_rx_preathena=%s,net_eth_rx_postathena=%s,pandatime1=%s,pandatime2=%s,pandatime3=%s,pandatime4=%s,pandatime5=%s,arch=%s,actual_ce=%s,logfile_guid=%s where test=%s and ganga_jobid=%s and ganga_subjobid=%s";
        val = vals[3:]+vals[0:3]
        cursor.execute(cmd,val)
        logger.debug('Existing row updated')
    
    if subjob.status in ('completed','failed'):
        logger.debug('Subjob is in final state, marking row as fixed')
        cursor.execute('update result set fixed=1 where test=%d and ganga_jobid=%d and ganga_subjobid=%d'%(testid,job.id,subjob.id))

#        if subjob.backend._impl._name == 'LCG':
#            dir = subjob.outputdir
#            logger.info('Writing job wms status to %s/wms.log.gz'%subjob.outputdir)
#            os.system('./hc-wms-status.sh %s | gzip - > %s/wms.log.gz'%(subjob.backend.id,subjob.outputdir))




# MAIN LOOP

try:
    testid = int(sys.argv[1])
except IndexError:
    print "testid required"
    sys.exit()

logger.info('HammerCloud runtest.py started for test %d'%testid)

def hc_copy_thread():
    test_sleep(60)
    conn2 = hcutil.connect()
    cursor2 = conn2.cursor ()
    logger.info('HC Copy Thread: Connected to DB')
    while (test_active(cursor2) and not test_paused(cursor2) and not ct.should_stop()):
        logger.info('HC Copy Thread: TOP OF MAIN LOOP')
        for job in jobs:
            if test_paused(cursor2) or ct.should_stop():
                break
            copyJob(cursor2,job)
            conn2.commit()
        conn2.commit()
        test_sleep(20)
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
            try:
                process_job(cursor,job)
                conn.commit()
            except:
                logger.warning('Exception in process_job:')
                logger.warning(sys.exc_info()[0])
                logger.warning(sys.exc_info()[1])
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
        test_sleep(20)
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
