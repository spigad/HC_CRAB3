
Job (
 name = '' ,
 outputsandbox = [] ,
 info = JobInfo (
    monitor = JobExecutionMonitor (
       realtime = True ,
       enabled = True ,
       ctracer = JEMCTraceOptions (
          traceApps = '' ,
          resolveValues = False ,
          enabled = False ,
          maxStructDepth = 2 ,
          traceModules = '' 
          ) ,
       advanced = JEMAdvancedOptions (
          debug = True ,
          logging = JEMLoggingConfig (
             default_level = 10 ,
             host = 'localhost' ,
             logfile = 'JEM.log' ,
             port = 14380 
             ) ,
          wn = JEMWNConfig (
             connect_wait_delay = 1.0 ,
             think_delay = 0.01 ,
             shmem_size = 8388608 ,
             script = '' ,
             logfile_archive_name = 'JEM_LOG.tgz' ,
             dump_bitmap_width = 128 ,
             logfile_archive_content 
= 'JEM_MON.jmd,JEM.log,logdumptrigger.log,ringbuffer_dump.bmp' ,
             trigger 
= 'ApproveAllTrigger,DiscardAllTrigger,StatisticsTrigger,LogDumpTrigger' ,
             shutdown_bailout_time = 30 ,
             preprocessor = 'JEMv2Converter' ,
             dump_bitmap = True ,
             connect_timeout = 10.0 ,
             valves = 'StompValve,LocalLogValve' 
             ) ,
          systemmonitor = JEMSystemMonitorConfig (
             disable = False ,
             sampling_delay = 5.0 
             ) ,
          bashmonitor = JEMBashMonitorConfig (
             debug_wait = False ,
             disable = True 
             ) ,
          locallogvalve = JEMLocalLogValveConfig (
             filename = 'JEM_MON.jmd' 
             ) ,
          ctracer = JEMCTracerConfig (
             callee_blacklist = '' ,
             resolve_level = 2 ,
             both_blacklist = '' ,
             trace_apps = '' ,
             trace_modules = '' ,
             caller_blacklist = '' ,
             disable = True ,
             debug_wait = False ,
             resolve_values = False 
             ) ,
          logdumptrigger = JEMLogDumpTriggerConfig (
             dump_shmem = False ,
             pid_in_filename = False 
             ) ,
          stompvalve = JEMStompValveConfig (
             host = 'mq.pleiades.uni-wuppertal.de' ,
             port = 6163 
             ) ,
          pythonmonitor = JEMPythonMonitorConfig (
             traceCalls = True ,
             traceLines = False ,
             traceReturns = True ,
             l1trigger = 'PyStdLibCallsTrigger' ,
             disable = True ,
             log_terminating_exception = False ,
             traceExceptions = True ,
             vicinityLines = 2 
             ) 
          ) 
       ) 
    ) ,
 inputdata = DQ2Dataset (
    match_ce_all = False ,
    datatype = '' ,
    failover = False ,
    guids = [] ,
    exclude_names = [] ,
    check_md5sum = False ,
    dataset = ####DATASET#### ,
    min_num_files = 0 ,
    accessprotocol = '' ,
    tagdataset = [] ,
    names = [] ,
    number_of_files = 0 ,
    use_aodesd_backnav = False ,
    type = '####INPUTTYPE####' 
    ) ,
 merger = None ,
 inputsandbox = [ ] ,
 application = Athena (
    atlas_project = '' ,
    atlas_exetype = 'ATHENA' ,
    atlas_run_dir = 'PhysicsAnalysis/AnalysisCommon/UserAnalysis/run/' ,
    stats = {} ,
    atlas_supp_stream = [] ,
    collect_stats = True ,
    atlas_cmtconfig = 'i686-slc5-gcc43-opt' ,
    exclude_package = [] ,
    athena_compile = False ,
    trf_parameter = {} ,
    atlas_run_config = {'input': {}, 'other': {}, 'output': {'outTHIST': ['AANT'], 'alloutputs': ['muTri.root']}} ,
    atlas_environment = [] ,
    atlas_production = '' ,
    atlas_release = '15.6.6' ,
    atlas_dbrelease = 'ddo.000001.Atlas.Ideal.DBRelease.v100701:DBRelease-10.7.1.tar.gz' ,
    options = '' ,
    atlas_use_AIDA = False ,
    exclude_from_user_area = ['*.o', '*.root*', '*.exe', 'BPhys'] ,
    option_file = [ File (
       name = '####JOBOPTIONS####' ,
       subdir = '.' 
       ) , ] ,
    user_setupfile = File (
       name = '' ,
       subdir = '.' 
       ) ,
    group_area = File (
       name = '' ,
       subdir = '.' 
       ) ,
    user_area = File (
       name = '####USERAREA####' ,
       subdir = '.' 
       ) 
    ) ,
 outputdata = DQ2OutputDataset (
    datasetname = '####OUTPUTDATASETNAME####' ,
    use_shortfilename = False ,
    outputdata = ['muTri.root'] ,
    local_location = '' ,
    location = '' 
    ) ,
 splitter = DQ2JobSplitter (
    update_siteindex = False ,
    numsubjobs = 1 ,
    use_lfc = False ,
    filesize = 30000 ,
    use_blacklist = False ,
    numfiles = 0
    ) ,
 backend = LCG (
    middleware = 'GLITE' ,
    CE = '' ,
    perusable = False ,
    jobtype = 'Normal' ,
    requirements = AtlasLCGRequirements (
       dq2client_version = '0.1.33' ,
       nodenumber = 1 ,
       ipconnectivity = False ,
       sites = [ ####SITES#### ] ,
       cputime = 1440 ,
       other = [] ,
       memory = None ,
       excluded_sites = [] ,
       software = [] ,
       os = '' ,
       cloud = 'DE' ,
       walltime = None 
       ) ,
    sandboxcache = LCGSandboxCache (
       protocol = 'lcg' ,
       srm_token = '' ,
       lfc_host = 'prod-lfc-atlas-central.cern.ch' ,
       se_type = 'srmv2' ,
       se_rpath = 'generated' ,
       max_try = 1 ,
       se = 'srm.cern.ch' 
       ) 
    ) 
 ) 

