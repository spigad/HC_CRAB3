#Ganga# File created by Ganga - Fri May 15 14:34:55 2009
#Ganga#
#Ganga# Object properties may be freely edited before reloading into Ganga
#Ganga#
#Ganga# Lines beginning #Ganga# are used to divide object definitions,
#Ganga# and must not be deleted

#Ganga# Job object (category: jobs)
Job (
 name = '' ,
 outputsandbox = [] ,
 info = JobInfo (
    ) ,
 inputdata = DQ2Dataset (
    match_ce_all = False ,
    datatype = '' ,
    failover = False ,
    guids = [] ,
    exclude_names = [] ,
    check_md5sum = False ,
    dataset = ['mc08.105200.T1_McAtNlo_Jimmy.recon.AOD.e357_s462_r635_tid045663'] ,
    min_num_files = 0 ,
    accessprotocol = '' ,
    tagdataset = [] ,
    names = [] ,
    number_of_files = 125 ,
    use_aodesd_backnav = False ,
    type = '' 
    ) ,
 merger = AthenaOutputMerger (
    subjobs = [] ,
    sum_outputdir = '' ,
    ignorefailed = False 
    ) ,
 inputsandbox = [ ] ,
 application = Athena (
    atlas_project = '' ,
    max_events = 250 ,
    atlas_exetype = 'ATHENA' ,
    atlas_run_dir = 'PhysicsAnalysis/AnalysisCommon/UserAnalysis/run/' ,
    stats = {} ,
    user_area_path = '/tmp/ebke' ,
    atlas_supp_stream = [] ,
    collect_stats = False ,
    atlas_cmtconfig = 'i686-slc4-gcc34-opt' ,
    exclude_package = [] ,
    athena_compile = False ,
    trf_parameter = {} ,
    atlas_run_config = {'input': {}, 'other': {}, 'output': {'outTHIST': ['AANT']}} ,
    atlas_environment = [] ,
    atlas_production = '' ,
    atlas_release = '15.1.0' ,
    atlas_dbrelease = '' ,
    options = '' ,
    atlas_use_AIDA = False ,
    exclude_from_user_area = ['*.o', '*.root*', '*.exe', 'BPhys'] ,
    option_file = [ File (
       name = '/afs/cern.ch/user/e/ebke/testarea/15.1.0/PhysicsAnalysis/AnalysisCommon/UserAnalysis/run/MuonTriggerAnalysis.py' ,
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
       name = '/tmp/ebke/sources.f04f7b82-3541-4bff-a000-1ee9d9e7b3a7.tar.gz' ,
       subdir = '.' 
       ) 
    ) ,
 outputdata = DQ2OutputDataset (
    datasetname = 'user08.JohannesEbke.ganga.8.20090515' ,
    use_shortfilename = False ,
    outputdata = [] ,
    local_location = '' ,
    location = '' 
    ) ,
 splitter = DQ2JobSplitter (
    update_siteindex = True ,
    numsubjobs = 20 ,
    use_lfc = False ,
    filesize = 0 ,
    use_blacklist = True ,
    numfiles = 7 
    ) ,
 backend = Panda (
    extOutFile = [] ,
    site = 'ANALY_FZK' ,
    libds = None ,
    requirements = PandaRequirements (
       notSkipMissing = False ,
       cputime = -1 ,
       corCheck = False ,
       long = False ,
       memory = -1 ,
       cloud = 'DE' 
       ) 
    ) 
 ) 

