Job (
 name = '' ,
 outputsandbox = [] ,
 info = JobInfo (
    ) ,
 inputdata = ATLASTier3Dataset (
    names = ['42'] 
   ) ,
 merger = None ,
 inputsandbox = [ ] ,
 application = Athena (
    collect_stats = True ,
    atlas_release = '17.X.0' ,
    atlas_project = 'AtlasOffline_rel' ,
    atlas_production = '0' ,
    atlas_cmtconfig = 'x86_64-slc5-gcc43-opt' ,
    max_events = 10 ,
    atlas_run_dir = './' ,
    atlas_exetype = 'ATHENA' ,
    athena_compile = False ,
    atlas_run_config = {'input': {'noInput': True}, 'other': {}, 'output': {'alloutputs': []}} ,
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
   ) ,
 splitter = ATLASTier3Splitter (
    numfiles = 1 ,
    numjobs = 1 
   ) ,
 backend = Panda (
    nobuild = True ,
    site = ####SITES#### ,
    accessmode = '####INPUTTYPE####' 
    )  
 ) 
