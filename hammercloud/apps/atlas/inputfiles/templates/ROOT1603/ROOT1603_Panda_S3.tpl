Job (
 name = '' ,
 outputsandbox = [] ,
 info = JobInfo (
    ) ,
 inputdata = ATLASTier3Dataset (
    pfnListFile = ####DATASET####
    ) ,
 merger = None ,
 inputsandbox = [ ] ,
 application = Athena (
    collect_stats = True ,
    atlas_environment = [] ,
    atlas_release = '' ,
    atlas_project = '' ,
    atlas_dbrelease = '' ,
    exclude_package = [] ,
    atlas_production = '' ,
    options = '' ,
    atlas_use_AIDA = False ,
    atlas_cmtconfig = '' ,
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
 splitter = ATLASTier3Splitter (
    numjobs = 0 ,
    numfiles = 10
    ) ,
 backend = Panda (
    nobuild = False ,
    site = ####SITES#### ,
    accessmode = '####INPUTTYPE####',
    requirements = PandaRequirements (
        rootver = "5.33.01s3"
      ), 
    )  
 ) 
