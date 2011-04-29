
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
    atlas_dbrelease = 'LATEST' ,
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
    CE = 'grid-cr9.desy.de:8443/cream-pbs-desy' ,
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

