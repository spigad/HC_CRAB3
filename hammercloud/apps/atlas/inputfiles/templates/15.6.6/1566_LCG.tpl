Job (
 name = '' ,
 outputsandbox = [] ,
 info = JobInfo (
    ) ,
 inputdata = DQ2Dataset (
    match_ce_all = False ,
    accessprotocol = '' ,
    datatype = 'MC' ,
    failover = False ,
    guids = [] ,
    exclude_names = [] ,
    check_md5sum = False ,
    dataset = ####DATASET#### ,
    min_num_files = 0 ,
    tagdataset = [] ,
    names = [] ,
    number_of_files = 1 ,
    use_aodesd_backnav = False ,
    type = '####INPUTTYPE####'
    ) ,
 merger = None ,
 inputsandbox = [ ] ,
 application = Athena (
    collect_stats = True ,
    atlas_environment = [] ,
    atlas_release = '15.6.6' ,
    atlas_project = '' ,
    exclude_package = [] ,
    atlas_production = '' ,
    atlas_dbrelease = 'LATEST' ,
    options = '' ,
    atlas_cmtconfig = 'i686-slc5-gcc43-opt' ,
    max_events = 100 ,
    exclude_from_user_area = [] ,
    atlas_exetype = 'ATHENA' ,
    atlas_run_config = {'input': {}, 'other': {}, 'output': {'outAANT': [('AANT1', 'AANT1')], 'outTHIST': ['GLOBAL'], 'alloutputs': ['physics.root', 'histo.root']}} ,
    atlas_run_dir = './' ,
    user_setupfile = File (
       name = '' ,
       subdir = '.' 
       ) ,
    option_file = [ File (
       name = '####JOBOPTIONS####' ,
       subdir = '.'
       ) , ] ,
    user_area = File (
       name = '####USERAREA####' ,
       subdir = '.'
       ) 
    ) ,
 outputdata = DQ2OutputDataset (
    datasetname = '####OUTPUTDATASETNAME####',  
    use_shortfilename = False ,
    outputdata = ['physics.root'] ,
    local_location = '' ,
    location = '' 
   ) ,
 splitter = DQ2JobSplitter (
    update_siteindex = False ,
    numsubjobs = 1 ,
    use_lfc = False ,
    filesize = 0 ,
    use_blacklist = False ,
    numfiles = 1
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
       cputime = None ,
       other = [] ,
       memory = None ,
       excluded_sites = [] ,
       software = ['VO-atlas-offline-15.6.6-i686-slc5-gcc43-opt'] ,
       os = '' ,
       cloud = '' ,
       walltime = None 
       ) ,
    sandboxcache = LCGSandboxCache (
       protocol = 'lcg' ,
       max_try = 1 
       ) 
    ) 
 ) 
