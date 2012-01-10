Job (
 name = '' ,
 outputsandbox = [] ,
 info = JobInfo (
    ) ,
 inputdata = DQ2Dataset (
    match_ce_all = False ,
    datatype = 'MC' ,
    failover = False ,
    accessprotocol = '' ,
    guids = [] ,
    check_md5sum = False ,
    exclude_names = [] ,
    dataset = ####DATASET#### ,
    min_num_files = 50 ,
    tagdataset = [] ,
    names = [] ,
    number_of_files = 50 ,
    use_aodesd_backnav = False ,
    type = '####INPUTTYPE####'
    ) ,
 merger = None ,
 inputsandbox = [ ] ,
 application = Athena (
    collect_stats = True ,
    atlas_environment = [] ,
    atlas_release = '16.0.3' ,
    atlas_project = '' ,
    exclude_package = [] ,
    atlas_production = '' ,
    options = '' ,
    atlas_use_AIDA = False ,
    atlas_cmtconfig = 'i686-slc5-gcc43-opt' ,
    max_events = -999 ,
    exclude_from_user_area = [] ,
    atlas_run_dir = './' ,
    atlas_exetype = 'EXE' ,
    athena_compile = False ,
    trf_parameter = {} ,
    atlas_run_config = {'input': {}, 'other': {}, 'output': {}} ,
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
    use_blacklist = False ,
    numfiles = 0
    ) ,
 backend = Panda (
    nobuild = True ,
    site = ####SITES#### ,
    accessmode = '####INPUTTYPE####' 
    )  
 ) 
