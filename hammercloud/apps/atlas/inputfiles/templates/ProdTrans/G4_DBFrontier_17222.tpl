Job (
 name = '' ,
 outputsandbox = [] ,
 info = JobInfo (
    ) ,
 inputdata = DQ2Dataset (
    dataset = ####DATASET#### ,
    number_of_files = 1 
    ) ,
 merger = None ,
 inputsandbox = [ ] ,
 application = ProdTrans (
    atlas_release = '17.2.2' ,
    home_package = 'AtlasProduction/17.2.2.2' ,
    transformation = 'AtlasG4_trf.py' ,
    atlas_cmtconfig = 'x86_64-slc5-gcc43-opt' ,
    dbrelease = '' ,
    prod_source_label = 'prod_test' ,
    output_files = ['Hits.hc_####TESTID####.HITS.pool.root'] ,
    randomize_lfns = True ,
    input_type = 'Evgen' ,
    output_type = 'Hits' ,
    priority = 10000 ,
    job_parameters = 'maxEvents=2 skipEvents=750 preInclude=SimulationJobOptions/preInclude.FrozenShowersFCalOnly.py,SimulationJobOptions/preInclude.BeamPipeKill.py preExec=simFlags.RandomSvc=\'AtDSFMTGenSvc\ postExec="from DBReplicaSvc.DBReplicaSvcConf import DBReplicaSvc;ServiceMgr+=DBReplicaSvc(COOLSQLiteVetoPattern=\'DBRelease\')" geometryVersion=ATLAS-GEO-20-00-01_VALIDATION conditionsTag=OFLCOND-MC12-SIM-00 AMITag=s1509 randomSeed=216 physicsList=QGSP_BERT --ignoreerrors=True'
    ) ,
 outputdata = DQ2OutputDataset (
    datasetname = '####OUTPUTDATASETNAME####'
   ) ,
 splitter = DQ2JobSplitter (
    update_siteindex = False ,
    numfiles = 1 
    ) ,
 backend = Panda (
    site = ####SITES####
    )
 )