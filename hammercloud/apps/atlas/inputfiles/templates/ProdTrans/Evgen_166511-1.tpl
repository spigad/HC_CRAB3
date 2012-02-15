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
    output_files = ['####TESTID####.evgen.pool.root'] ,
    randomize_lfns = True ,
    job_parameters = '2760 105723 19901 501 200 MC10.105723.PythiaB_cce3X.py NONE NONE NONE MC10JobOpts-latest-test.tar.gz --ignoreerrors=True '
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
