#Ganga# Job object (category: jobs)
Job (
 inputdata = DQ2Dataset (
    dataset = ####DATASET#### ,
    type = '####INPUTTYPE####' ,
    ) , 
 application = Athena (
    atlas_project = '' ,
    atlas_exetype = 'ATHENA' ,
    atlas_run_dir = './' ,
    user_area_path = '/tmp/dvanders' ,
    atlas_cmtconfig = 'i686-slc5-gcc43-opt' ,
    athena_compile = False ,
    atlas_run_config = {'input': {}, 'other': {}, 'output': {'outAANT': [('D3PD', 'D3PD')], 'outTHIST': ['GLOBAL'], 'alloutputs': ['physics.root', 'histo.root']}} ,
    atlas_production = '' ,
    atlas_release = '15.9.0' ,
    atlas_dbrelease = 'LATEST' ,
    collect_stats = True ,
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
    datasetname = '####OUTPUTDATASETNAME####' ,
    ) ,
 splitter = DQ2JobSplitter (
    update_siteindex = False ,
    use_blacklist = False ,
    numfiles = 1 
    ) ,
 backend = Panda (
    site = ####SITES####,
    accessmode = '####INPUTTYPE####'
    )
 ) 

