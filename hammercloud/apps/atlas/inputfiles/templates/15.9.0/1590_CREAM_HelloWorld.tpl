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
    atlas_run_config = {'input': {'noInput': True}, 'other': {}, 'output': {'alloutputs': []}} ,
    atlas_run_dir = './' ,
    collect_stats = True ,
    atlas_environment = [] ,
    atlas_release = '15.9.0' ,
    atlas_project = '' ,
    exclude_package = [] ,
    atlas_production = '' ,
    options = '' ,
    atlas_cmtconfig = 'i686-slc5-gcc43-opt' ,
    max_events = 10 ,
    exclude_from_user_area = [] ,
    atlas_exetype = 'ATHENA' ,
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
    outputdata = [ 'HelloWorldOptions.py' ]  ,
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
 backend = CREAM (
    CE = '' ,
    jobtype = 'Normal' ,
    requirements = AtlasCREAMRequirements (
       dq2client_version = '' ,
       nodenumber = 1 ,
       ipconnectivity = False ,
       sites = [ ####SITES#### ] ,
       cputime = 1440 ,
       other = [] ,
       memory = None ,
       excluded_sites = [] ,
       walltime = None ,
       os = '' ,
       cloud = 'ALL' ,
       software = []
       ) ,
    sandboxcache = DQ2SandboxCache (
       protocol = 'dq2' ,
       dataset_name = 'user.elmsheus.3b761527ef0e630473193b3d3eb2b0d5.input' ,
       max_try = 1 ,
       setup = '/afs/cern.ch/atlas/offline/external/GRID/ddm/DQ2Clients/setup.sh' ,
       local_site_id = 'CERN-PROD_SCRATCHDISK'
       )
    )
 ) 
