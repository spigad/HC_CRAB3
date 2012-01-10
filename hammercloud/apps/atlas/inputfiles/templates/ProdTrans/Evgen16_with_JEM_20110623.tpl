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
    atlas_release = '16.6.5' ,
    home_package = 'AtlasPhysics/16.6.5.5.1' ,
    transformation = 'Evgen_trf.py' ,
    atlas_cmtconfig = 'i686-slc5-gcc43-opt' ,
    dbrelease = 'LATEST' ,
    prod_source_label = 'rc_test' ,
    output_files = ['####TESTID####_evgen.pool.root'] ,
    randomize_lfns = True ,
    job_parameters = '2760 105048 19901 101 200 MC10.105048.PythiaB_ccmu3mu1X.py %s NONE NONE NONE MC10JobOpts-latest-test.tar.gz autoConfiguration=everything --ignoreerrors=True --enable-jem ' % (output_files)
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
