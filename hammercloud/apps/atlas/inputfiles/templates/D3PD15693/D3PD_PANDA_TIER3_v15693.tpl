Job (
 name = '' ,
 outputsandbox = [] ,
 info = JobInfo (
    monitor = None 
    ) ,
 inputdata = ATLASTier3Dataset (
    pfnListFile = ####DATASET#### 
    ) ,
 merger = None ,
 inputsandbox = [ ] ,
 application = Athena (
    atlas_project = 'AtlasProduction' ,
    max_events = -999 ,
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
    atlas_run_config = {'input': {}, 'other': {}, 'output': {'outAANT': [('AANT1', 'AANT1')], 'outTHIST': ['GLOBAL'], 'alloutputs': ['physics.root', 'histo.root']}} ,
    atlas_environment = [] ,
    atlas_production = '15.6.9.3' ,
    atlas_release = '15.6.9' ,
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
    ) ,
 splitter = ATLASTier3Splitter (
    numjobs = 0 ,
    numfiles = 5
    ) ,
 backend = Panda (
    site = ####SITES####,
    accessmode = '####INPUTTYPE####'
    )
 ) 

