
Job (
 name = '' ,
 outputsandbox = [] ,
 info = JobInfo (
    ) ,
 inputdata = ATLASTier3Dataset (
    pfnListFile = ####DATASET####
    ) ,
 merger = None ,
 inputsandbox = [ '####JOBOPTIONS####' ] ,
 application = Athena (
    atlas_project = '' ,
    atlas_exetype = 'EXE' ,
    atlas_run_dir = './' ,
    stats = {} ,
    atlas_supp_stream = [] ,
    collect_stats = True ,
    atlas_cmtconfig = 'i686-slc5-gcc43-opt' ,
    exclude_package = [] ,
    athena_compile = False ,
    trf_parameter = {} ,
    atlas_run_config = {'input': {}, 'other': {}, 'output': {}} ,
    atlas_environment = [] ,
    atlas_production = '' ,
    atlas_release = '17.0.2' ,
    atlas_dbrelease = 'LATEST' ,
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
    use_shortfilename = False ,
    outputdata = ['histos.root'] ,
    local_location = '' ,
    location = '' 
    ) ,
 splitter = ATLASTier3Splitter (
    numjobs = 0 ,
    numfiles = 100
    ) ,
 backend = CREAM (
    CE = 'grid-cr9.desy.de:8443/cream-pbs-atlas' ,
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
       dataset_name = '' ,
       max_try = 1 ,
       setup = '/afs/cern.ch/atlas/offline/external/GRID/ddm/DQ2Clients/setup.sh' ,
       local_site_id = 'CERN-PROD_SCRATCHDISK'
       )
    )
 ) 

