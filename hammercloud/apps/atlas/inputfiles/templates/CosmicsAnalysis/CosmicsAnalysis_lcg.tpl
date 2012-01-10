
Job (
 name = '' ,
 outputsandbox = [] ,
 info = JobInfo (
    ) ,
 inputdata = DQ2Dataset (
    match_ce_all = False ,
    datatype = 'MC' ,
    exclude_pattern = [] ,
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
    type = '####INPUTTYPE####' ,
    failover = False 
    ) ,
 merger = None ,
 inputsandbox = [ ] ,
 application = Athena (
    atlas_project = '' ,
    max_events = -999 ,
    atlas_exetype = 'ATHENA' ,
    atlas_run_dir = 'CosmicsAnalysis/run/' ,
    stats = {} ,
    user_area_path = '/tmp/elmsheus' ,
    atlas_supp_stream = [] ,
    collect_stats = True ,
    atlas_cmtconfig = 'i686-slc4-gcc34-opt' ,
    exclude_package = [] ,
    append_to_user_area = [] ,
    athena_compile = False ,
    trf_parameter = {} ,
    recex_type = '' ,
    atlas_run_config = {'input': {}, 'other': {}, 'output': {'alloutputs': []}} ,
    atlas_environment = [ ] ,
    atlas_production = '' ,
    atlas_release = '15.5.0' ,
    atlas_dbrelease = '' ,
    options = '' ,
    atlas_use_AIDA = False ,
    exclude_from_user_area = [] ,
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
    isGroupDS = False ,
    use_shortfilename = False ,
    groupname = '' ,
    outputdata = ['Cosmic_09Data_IDCosmic.root' ] ,
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
       dq2client_version = '0.1.28' ,
       nodenumber = 1 ,
       ipconnectivity = False ,
       sites = [ ####SITES####  ] ,
       cputime = 1440 ,
       other = [] ,
       memory = None ,
       excluded_sites = [] ,
       software = [] ,
       os = '' ,
       cloud = '' ,
       walltime = None 
       ) ,
    sandboxcache = DQ2SandboxCache (
       protocol = 'dq2' ,
       max_try = 1 ,
       setup = '/afs/cern.ch/atlas/offline/external/GRID/ddm/DQ2Clients/latest/setup.sh' ,
       local_site_id = 'CERN-PROD_SCRATCHDISK' 
       ) 
    ) 
 ) 

