Job (
 application = Executable (
    exe = 'lcgtest.sh' ,
    args = [] 
 ),
 outputdata = DQ2OutputDataset (
    datasetname = '####OUTPUTDATASETNAME####'
 ),
 inputsandbox = [File(name='/data/hammercloud/atlas/inputfiles/lcgutils/lcgtest.sh',subdir='.')] ,
 backend = Panda (
    site = ####SITES####,
 )
) 
