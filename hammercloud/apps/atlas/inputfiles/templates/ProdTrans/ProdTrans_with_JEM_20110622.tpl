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
    transformation = 'Reco_trf.py' ,
    atlas_cmtconfig = 'i686-slc5-gcc43-opt' ,
    dbrelease = 'LATEST' ,
    prod_source_label = 'rc_test' ,
    output_files = ['NTUP_TOP.hc_####TESTID####.root'] ,
    randomize_lfns = True ,
    job_parameters = 'maxEvents=10 autoConfiguration=everything topOptions=TopInputsD3PDMaker/PrepareTopInputs.py --ignoreerrors=True --enable-jem '
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
