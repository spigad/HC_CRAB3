Job (
 name = '' ,
 outputsandbox = [] ,
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
 merger = None ,
 inputsandbox = [ ] ,
 application = Athena (
    atlas_release = '14.5.1' ,
    atlas_project = '' ,
    exclude_package = [] ,
    atlas_production = '' ,
    atlas_cmtconfig = 'i686-slc4-gcc34-opt' ,
    exclude_from_user_area = [] ,
    options = '' ,
    collect_stats = True ,
    user_setupfile = File (
       name = '' ,
       subdir = '.' 
       ) ,
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
   datasetname = '####OUTPUTDATASETNAME####'  ,
   use_shortfilename = False ,
   outputdata = ['thin_1l.DPD.pool.root', 'hist.root'] ,
   local_location = '' ,
   location = ''
   ) ,
 splitter = DQ2JobSplitter (
   numsubjobs = 1 ,
   numfiles = 0 ,
   use_lfc = False ,
   update_siteindex = False,
   use_blacklist = False
 ) ,
 backend = LCG (
    middleware = 'GLITE' ,
    CE = '' ,
    perusable = False ,
    jobtype = 'Normal' ,
    requirements = AtlasLCGRequirements (
       dq2client_version = '0.1.24' ,
       nodenumber = 1 ,
       ipconnectivity = False ,
       sites = [ ####SITES#### ] ,
       cputime = 1440 ,
       other = [] ,
       memory = None ,
       excluded_sites = [] ,
       software = ['VO-atlas-offline-14.2.20-i686-slc4-gcc34-opt'] ,
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
