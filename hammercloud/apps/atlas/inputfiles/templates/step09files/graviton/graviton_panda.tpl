Job (
 inputdata = DQ2Dataset (
    dataset = ####DATASET#### ,
    ) ,
 application = Athena (
    atlas_run_dir = 'PhysicsAnalysis/HighPtPhys/HighPtView/run/' ,
    collect_stats = True ,
    atlas_run_config = {'input': {'noInput': True}, 'other': {}, 'output': {'outAANT': [('EVAANtupleDump0Stream', 'AANT0')]}} ,
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
