
Job (
 name = '' ,
 outputsandbox = [] ,
 info = JobInfo (
    ) ,
 inputdata = None ,
 merger = None ,
 inputsandbox = [ ] ,
 application = Athena (
    atlas_project = '' ,
    max_events = 100 ,
    atlas_exetype = 'ATHENA' ,
    atlas_run_dir = '' ,
    stats = {} ,
    user_area_path = '' ,
    atlas_supp_stream = [] ,
    collect_stats = True ,
    atlas_cmtconfig = '' ,
    exclude_package = [] ,
    append_to_user_area = [] ,
    athena_compile = False ,
    trf_parameter = {} ,
    recex_type = '' ,
    atlas_run_config = {} ,
    atlas_environment = [] ,
    atlas_production = '' ,
    atlas_release = '15.3.1' ,
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
       name = '' ,
       subdir = '.' 
       ) 
    ) ,
 outputdata = None ,
 splitter = ArgSplitter (
    args = [[''] for i in range(####NUM####)] 
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

