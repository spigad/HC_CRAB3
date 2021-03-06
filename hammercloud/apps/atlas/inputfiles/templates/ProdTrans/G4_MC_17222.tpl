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
    dbrelease = 'LATEST' ,
    prod_source_label = 'prod_test' ,
    output_files = ['Hits.hc_####TESTID####.HITS.pool.root'] ,
    randomize_lfns = True ,
    input_type = 'Evgen' ,
    output_type = 'Hits' ,
    priority = 10000 ,
    core_count = 8 ,
    job_parameters = 'maxEvents=8 skipEvents=0 randomSeed=568 geometryVersion=ATLAS-GEO-18-01-00 conditionsTag=OFLCOND-SDR-BS7T-05-03 physicsList=QGSP_BERT --ignoreerrors=True'
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
