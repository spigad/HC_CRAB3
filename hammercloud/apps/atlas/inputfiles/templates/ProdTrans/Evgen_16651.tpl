Job (
 name = '' ,
 outputsandbox = [] ,
 info = JobInfo (
    ) ,
 merger = None ,
 inputsandbox = [ ] ,
 application = ProdTrans (
    atlas_release = '16.6.5' ,
    home_package = 'AtlasProduction/16.6.5.1' ,
    transformation = 'Evgen_trf.py' ,
    atlas_cmtconfig = 'i686-slc5-gcc43-opt' ,
    dbrelease = '' ,
    prod_source_label = 'prod_test' ,
    output_files = ['####TESTID####.evgen.EVNT.pool.root'] ,
    randomize_lfns = True ,
    output_type = 'Evgen' ,
    priority = 10000 ,
    job_parameters = 'ecmEnergy=7000 runNumber=105048 firstEvent=19901 maxEvents=101 randomSeed=99 jobConfig=MC10JobOptions/MC10.105048.PythiaB_ccmu3mu1X.py EvgenJobOpts=MC10JobOpts-latest-test.tar.gz --ignoreerrors=True'
    ) ,
 outputdata = DQ2OutputDataset (
    datasetname = '####OUTPUTDATASETNAME####'
   ) ,
 splitter = GenericSplitter (
    attribute = 'atlas_release' ,
    values = ['16.6.5'] 
   ) ,
 backend = Panda (
    site = ####SITES####
    )
 )
