Job (
 name = '' ,
 outputsandbox = [] ,
 info = JobInfo (
    monitor = None 
    ) ,
 inputdata = DQ2Dataset (
    match_ce_all = False ,
    tag_info = {} ,
    datatype = '' ,
    exclude_pattern = [] ,
    guids = [] ,
    exclude_names = [] ,
    check_md5sum = False ,
    dataset = ####DATASET#### ,
    min_num_files = 0 ,
    accessprotocol = '' ,
    tagdataset = [] ,
    names = [] ,
    number_of_files = 1 ,
    use_aodesd_backnav = False ,
    type = '####INPUTTYPE####' ,
    failover = False 
    ) ,
 merger = None ,
 inputsandbox = [ ] ,
 application = Athena (
    atlas_project = '' ,
    max_events = 100 ,
    atlas_exetype = 'ATHENA' ,
    atlas_run_dir = './' ,
    stats = {} ,
    user_area_path = '/tmp/elmsheus' ,
    atlas_supp_stream = [] ,
    collect_stats = True ,
    atlas_cmtconfig = 'i686-slc5-gcc43-opt' ,
    exclude_package = [] ,
    append_to_user_area = [] ,
    athena_compile = False ,
    trf_parameter = {} ,
    recex_type = '' ,
    atlas_run_config = {'input': {}, 'other': {}, 'output': {'alloutputs': ['physics.root'], 'outAANT': [('D3PD', 'D3PD', 'physics.root')]}} ,
    atlas_environment = [] ,
    atlas_production = '',
    atlas_release = '16.0.3' ,
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
    outputdata = [ ] ,
    local_location = '' ,
    location = ''
    ) ,
 splitter = DQ2JobSplitter (
    update_siteindex = False ,
    numsubjobs = 1 ,
    use_lfc = False ,
    filesize = 0 ,
    use_blacklist = False ,
    numfiles = 0 
    ) ,
 backend = Panda (
    site = ####SITES#### ,
    accessmode = '####INPUTTYPE####'
    )

 ) 

