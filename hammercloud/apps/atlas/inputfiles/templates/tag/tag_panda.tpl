Job (
 inputdata = DQ2Dataset (
    dataset = ####DATASET#### ,
    ) ,
 application = Athena (
    atlas_run_dir = 'PhysicsAnalysis/AnalysisCommon/UserAnalysis/run/' ,
    collect_stats = True ,
    atlas_run_config = {'input': {'inColl': True}, 'other': {}, 'output': {'outStreamG': ['StreamDPD'], 'alloutputs': ['SkimmedThin.AOD.pool.root']}} , 
    atlas_release = '15.2.0' ,
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

