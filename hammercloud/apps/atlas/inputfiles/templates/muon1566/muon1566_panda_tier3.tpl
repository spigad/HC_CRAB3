
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
    atlas_project = '' ,
    atlas_exetype = 'ATHENA' ,
    atlas_run_dir = 'PhysicsAnalysis/AnalysisCommon/UserAnalysis/run/' ,
    stats = {} ,
    atlas_supp_stream = [] ,
    collect_stats = True ,
    atlas_cmtconfig = 'i686-slc5-gcc43-opt' ,
    exclude_package = [] ,
    athena_compile = True ,
    trf_parameter = {} ,
    atlas_run_config = {'input': {}, 'other': {}, 'output': {'outTHIST': ['AANT'], 'alloutputs': ['muTri.root']}} ,
    atlas_environment = [] ,
    atlas_production = '' ,
    atlas_release = '15.6.6' ,
    atlas_dbrelease = 'LATEST' ,
    options = '' ,
    atlas_use_AIDA = False ,
    exclude_from_user_area = ['*.o', '*.root*', '*.exe', 'BPhys'] ,
    option_file = [ File (
       name = '####JOBOPTIONS####' ,
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

