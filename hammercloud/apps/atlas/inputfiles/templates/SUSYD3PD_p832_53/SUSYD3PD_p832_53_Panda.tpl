Job (
 name = '' ,
 outputsandbox = [] ,
 info = JobInfo (
    ) ,
 inputdata = DQ2Dataset (
    match_ce_all = False ,
    datatype = '' ,
    failover = False ,
    accessprotocol = '' ,
    guids = [] ,
    check_md5sum = False ,
    exclude_names = [] ,
    dataset = ####DATASET#### ,
    min_num_files = 0 ,
    tagdataset = [] ,
    names = [] ,
    number_of_files = 0 ,
    use_aodesd_backnav = False ,
    type = '####INPUTTYPE####'
    ) ,
 merger = None ,
 inputsandbox = [ File (
    name = '/data/hc/apps/atlas/inputfiles/templates/SUSYD3PD_p832_53/dummy', 
    subdir = '.' 
     ) , ] ,
 application = Athena (
    atlas_project = '' ,
    atlas_release = '17.0.2' ,
    useAthenaPackages = False ,
    exclude_package = [] ,
    run_event = [] ,
    glue_packages = [] ,
    atlas_run_dir = './' ,
    atlas_production = '' ,
    useNoDebugLogs = False ,
    run_event_file = '' ,
    recex_type = '' ,
    max_events = -999 ,
    exclude_from_user_area = [] ,
    atlas_exetype = 'EXE' ,
    atlas_run_config = {'input': {}, 'other': {}, 'output': {}} ,
    atlas_environment = [] ,
    trf_parameter = {} ,
    skip_events = 0 ,
    user_area_path = '' ,
    collect_stats = True ,
    athena_compile = True ,
    useRootCoreNoBuild = False ,
    options = '' ,
    atlas_cmtconfig = '' ,
    useRootCore = True ,
    append_to_user_area = [] ,
    atlas_supp_stream = [] ,
    atlas_use_AIDA = False ,
    is_prepared = True ,
    user_setupfile = File (
       name = '' ,
       subdir = '.' 
       ) ,
    option_file = [ File (
       name = '####JOBOPTIONS####' ,
       subdir = '.'
       ) , ] ,
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
    datasetname = '####OUTPUTDATASETNAME####',  
    outputdata = ['histos.root'] ,
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
 backend = Panda (
    site = ####SITES#### ,
    accessmode = '####INPUTTYPE####' 
    )  
 ) 
