Job (
 inputdata = CRABDataset (
    show_prod = 1 ,
    datasetpath = '####DATASETPATH####',
    pset = '####PSET####',
    ignore_edm_output = 1,
    use_dbs_1 = 0,
    return_data = 1,
    thresholdLevel = 0,
    total_number_of_events = 100000,
    events_per_job = 1000,
    split_by_event = 1,
    jobtype = 'cmssw',
    scheduler = 'glite',
    rb = 'HC',
    remove_default_blacklist = 1,
    #CE_white_list = '####CE_WHITE_LIST####',
    SE_white_list = '####SE_WHITE_LIST####',
    retry_count = 0,
    dont_check_proxy = 1,
    xml_report = 'report.xml',
    role = 'production',
    ) ,
 application = CRABApp () ,
 backend = CRABBackend (),
 splitter = CRABSplitter ()
)

