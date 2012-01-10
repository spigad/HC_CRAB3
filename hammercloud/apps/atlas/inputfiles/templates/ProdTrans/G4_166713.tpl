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
    atlas_release = '16.6.7' ,
    home_package = 'AtlasProduction/16.6.7.13' ,
    transformation = 'AtlasG4_trf.py' ,
    atlas_cmtconfig = 'i686-slc5-gcc43-opt' ,
    dbrelease = 'LATEST' ,
    prod_source_label = 'prod_test' ,
    output_files = ['Hits.hc_####TESTID####.HITS.pool.root'] ,
    randomize_lfns = True ,
    input_type = 'Evgen' ,
    output_type = 'Hits' ,
    priority = 10000 ,
    job_parameters = 'maxEvents=1 skipEvents=0 randomSeed=568 geometryVersion=ATLAS-GEO-11-00-00 conditionsTag=OFLCOND-SDR-BS7T-02 --ignoreerrors=True'
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
