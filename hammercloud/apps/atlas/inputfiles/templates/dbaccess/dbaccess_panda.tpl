
Job (
 name = '' ,
 outputsandbox = [] ,
 info = JobInfo (
    ) ,
 inputdata = None ,
 merger = None ,
 inputsandbox = [ File (
    name = '####JOBOPTIONS####' ,
    subdir = '.' 
    ) , File (
    name = '/data/gangarobot/hammercloud/inputfiles/dbaccess/panda.sh' ,
    subdir = '.'
    ) , ] ,
 application = Executable (
    exe = 'panda.sh' ,
    env = {} ,
    args = ['15.3.1', '####JOBOPTIONSFILENAME####'] 
    ) ,
 outputdata = DQ2OutputDataset (
    datasetname = '####OUTPUTDATASETNAME####' ,
    ) ,
 splitter = ArgSplitter (
    args = [[''] for i in range(####NUM####)]
    ) ,
 backend = Panda (
    extOutFile = [] ,
    site = ####SITES#### ,
    libds = None ,
    requirements = PandaRequirements (
       notSkipMissing = False ,
       cputime = -1 ,
       corCheck = False ,
       long = False ,
       memory = -1 ,
       excluded_sites = [] ,
       cloud = 'US' 
       ) 
    ) 
 ) 

