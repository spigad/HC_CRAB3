Job (
 name = '' ,
 outputsandbox = [] ,
 info = JobInfo (
    ) ,
 merger = None ,
 inputsandbox = [ ] ,
 application = ProdTrans (
    atlas_release = '16.6.5' ,
    home_package = 'AtlasPhysics/16.6.5.5.1' ,
    transformation = 'Evgen_trf.py' ,
    atlas_cmtconfig = 'i686-slc5-gcc43-opt' ,
    dbrelease = '' ,
    prod_source_label = 'prod_test' ,
    output_files = ['####TESTID####.evgen.EVNT.pool.root'] ,
    randomize_lfns = True ,
    output_type = 'Evgen' ,
    job_parameters = 'ecmEnergy=7000 runNumber=105048 firstEvent=19901 maxEvents=101 randomSeed=200 jobConfig=MC10.105048.PythiaB_ccmu3mu1X.py EvgenJobOpts=MC10JobOpts-latest-test.tar.gz --ignoreerrors=True'
    ) ,
 outputdata = DQ2OutputDataset (
    datasetname = '####OUTPUTDATASETNAME####'
   ) ,
 splitter = DQ2JobSplitter (
    numfiles = 1 
    ) ,
 backend = Panda (
    site = ####SITES####
    )
 )
