Job (
 inputdata = DQ2Dataset (
    match_ce_all = False ,
    accessprotocol = '' ,
    guids = [] ,
    exclude_names = [] ,
    dataset = ####DATASET#### ,
    min_num_files = 0 ,
    tagdataset = [] ,
    names = [] ,
    number_of_files = 0 ,
    use_aodesd_backnav = False ,
    type = '####INPUTTYPE####'
    ) ,
 application = Athena (
    atlas_release='14.5.0',
    collect_stats = True ,
    option_file = [ File (
       name = '####JOBOPTIONS####' ,
       subdir = '.'
       ) , ] ,
    user_area = File (
       name = '####USERAREA####' ,
       subdir = '.'
       ) ,
    atlas_run_config = {'input': {}, 'other': {}, 'output': {'outAANT': [('AANTupleStream', 'AANT')]}},
    atlas_run_dir = 'PhysicsAnalysis/AnalysisCommon/UserAnalysis/run/'
    ) ,
 outputdata = DQ2OutputDataset (
   datasetname = '####OUTPUTDATASETNAME####'  
   ) ,
 splitter = DQ2JobSplitter (
   numsubjobs = 1 ,
   numfiles = 0 ,
   use_lfc = False ,
   update_siteindex = False,
   use_blacklist = False
 ) ,
 backend = Panda (
   site = ####SITES#### 
 )
)
