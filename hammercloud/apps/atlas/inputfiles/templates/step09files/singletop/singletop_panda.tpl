Job (
 inputdata = DQ2Dataset (
    dataset = ####DATASET#### ,
    type = '####INPUTTYPE####'
    ) ,
 application = Athena (
    atlas_project = 'AtlasProduction' ,
    collect_stats = True ,
    atlas_run_dir = 'users/ccurtis/BUSTopAnalysis/run/' ,
    atlas_run_config = {'input': {}, 'other': {}, 'output': {'outTHIST': ['AANT', 'TREES'], 'alloutputs': ['BUSTopAlg.root', 'BUSTopAlgTrees.root']}} ,
    atlas_production = '14.5.0.5' ,
    atlas_release = '14.5.0' ,
    option_file = [File(name='####JOBOPTIONS####',subdir='.')] ,
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
    numsubjobs = 1 ,
    use_lfc = False ,
    filesize = 0 ,
    use_blacklist = False ,
    numfiles = 0 
    ) ,
 backend = Panda (
    site = ####SITES####
 ) 
)
