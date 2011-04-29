Job (
 inputdata = DQ2Dataset (
    dataset = ####DATASET#### ,
    type = '####INPUTTYPE####'
    ) ,
 application = Athena (
    atlas_project = 'AtlasProduction' ,
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
    outputdata=['BUSTopAlg.root', 'BUSTopAlgTrees.root']
    ) ,
 splitter = DQ2JobSplitter (
    update_siteindex = False ,
    numsubjobs = 1 ,
    use_lfc = False ,
    filesize = 0 ,
    use_blacklist = False ,
    numfiles = 0 
    ) ,
 backend = NG (
    check_availability = False ,
    submit_options = [] ,
    middleware = 'ARC' ,
    CE = ####SITES#### ,
    clean = [] ,
    RejectCE = '' ,
    requirements = NGRequirements (
       runtimeenvironment = ['APPS/HEP/ATLAS-14.5.0.5'] ,
       cputime = 1440 ,
       other = [] ,
       memory = 1500 ,
       disk = 1000 ,
       walltime = 1440
       )
    )
)
