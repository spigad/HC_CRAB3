Job (
 inputdata = DQ2Dataset (
    number_of_files = 2 ,
    dataset = ####DATASET#### ,
    type = '####INPUTTYPE####'
    ) ,
 application = Athena (
    atlas_exetype = 'TRF' ,
    atlas_run_dir = './' ,
    collect_stats = True ,
    atlas_cmtconfig = 'i686-slc5-gcc43-opt' ,
    atlas_run_config = {'input': {}, 'other': {}, 'output': {}} ,
    atlas_environment = ['DBRELEASE_OVERRIDE=13.8.3'] ,
    atlas_dbrelease = 'ddo.000001.Atlas.Ideal.DBRelease.v130803:DBRelease-13.8.3.tar.gz' ,
    options = 'Reco_trf.py inputESDFile=%IN RunNumber=152166 autoConfiguration=everything preInclude=RecJobTransforms/Reprocessing2010_preInclude.py DBRelease=DBRelease-13.8.3.tar.gz AMITag=p306 outputESDFile=%OUT.ESD.pool.root.1 outputAODFile=%OUT.AOD.pool.root.1 outputNTUP_TRIGFile=%OUT.NTUP_TRIG.root.1 outputDESDM_EGAMMAFile=%OUT.DESDM_EGAMMA.pool.root.1 outputDESD_PHOJETFile=%OUT.DESD_PHOJET.pool.root.1 outputDESD_SGLELFile=%OUT.DESD_SGLEL.pool.root.1 outputDESDM_CALJETFile=%OUT.DESDM_CALJET.pool.root.1 outputDESDM_TRACKFile=%OUT.DESDM_TRACK.pool.root.1 outputDESD_METFile=%OUT.DESD_MET.pool.root.1 --ignoreerrors=True' ,
    atlas_release = '16.0.2' ,
    option_file = [ File (
       name = '####JOBOPTIONS####' ,
       subdir = '.' 
       ) , ] ,
    user_area = File (
       name = '####USERAREA####' ,
       subdir = '.' 
       ) 
    ) ,
 outputdata = DQ2OutputDataset (
    datasetname = '####OUTPUTDATASETNAME####' ,
    outputdata = ['ESD.pool.root.1', 'AOD.pool.root.1', 'NTUP_TRIG.root.1', 'DESDM_EGAMMA.pool.root.1', 'DESD_PHOJET.pool.root.1', 'DESD_SGLEL.pool.root.1', 'DESDM_CALJET.pool.root.1', 'DESDM_TRACK.pool.root.1', 'DESD_MET.pool.root.1'] 
    ) ,
 splitter = DQ2JobSplitter (
    update_siteindex = False ,
    filesize = 0 ,
    use_blacklist = False ,
    numfiles = 2 
    ) ,
 backend = Panda (
    site = ####SITES#### ,
    nobuild = True ,
    accessmode = '####INPUTTYPE####' 
 ) 
)
