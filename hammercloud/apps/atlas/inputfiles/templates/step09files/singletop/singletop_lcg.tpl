Job (
 inputdata = DQ2Dataset (
    dataset = ####DATASET#### ,
    ) ,
 application = Athena (
    atlas_project = 'AtlasProduction' ,
    atlas_run_dir = '' ,
    collect_stats = True ,
    atlas_release = '14.5.0' ,
    atlas_production = '14.5.0.5' ,
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
    filesize = 30000 ,
    use_blacklist = False ,
    numfiles = 0 
    ) ,

 backend = LCG (
    middleware = 'GLITE' ,
    CE = '' ,
    perusable = False ,
    jobtype = 'Normal' ,
    requirements = AtlasLCGRequirements (
       dq2client_version = '0.1.27' ,
       nodenumber = 1 ,
       ipconnectivity = False ,
       sites = [ ####SITES#### ] ,
       cputime = None ,
       other = [] ,
       memory = None ,
       excluded_sites = [] ,
       software = [] ,
       os = '' ,
       cloud = '' ,
       walltime = None
       ) ,
    sandboxcache = LCGSandboxCache (
       protocol = 'lcg' ,
       max_try = 1
       )
    )
)
