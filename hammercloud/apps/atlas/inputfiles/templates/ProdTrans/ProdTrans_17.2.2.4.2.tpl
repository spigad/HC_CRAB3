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
    home_package = 'AtlasPhysics/17.2.2.4.2' ,
    transformation = 'Reco_trf.py' ,
    atlas_cmtconfig = 'i686-slc5-gcc43-opt' ,
    dbrelease = 'LATEST',
    prod_source_label = 'rc_test' ,
    output_files = ['NTUP_SMWZ.hc_####TESTID####.root'] ,
    randomize_lfns = True ,
    job_parameters = 'maxEvents=100 autoConfiguration=everything AMI=p1067 outputNTUP_SMWZFile=NTUP_SMWZ.hc_####TESTID####.root --ignoreerrors=True'
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
