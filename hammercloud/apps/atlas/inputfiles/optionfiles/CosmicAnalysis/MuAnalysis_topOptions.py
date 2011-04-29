# Frontier settings
import os

#os.environ['ATLAS_CONDDB']='bla'

#os.environ['FRONTIER_SERVER']=''

# for FZK
#os.environ['ATLAS_POOLCOND_PATH']='/sw/atlas/sl5/local/conditions'
#os.environ['FRONTIER_SERVER']='(serverurl=http://atlassq1-fzk.gridka.de:8021/fzk)'

#For HH
#os.environ['ATLAS_POOLCOND_PATH']='/opt/vo/atlas/local/conditions'
#os.environ['FRONTIER_SERVER']="(serverurl=http://atlassq1-fzk.gridka.de:8021/fzk)(proxyurl=http://t2-atlas-db0.desy.de:3128)"

#For LRZ-LMU
#os.environ['ATLAS_POOLCOND_PATH']='/opt/vo/atlas/local/conditions'
#os.environ['FRONTIER_SERVER']='FRONTIER_SERVER=(serverurl=http://atlassq1-fzk.gridka.de:8021/fzk)(proxyurl=http://lcg-lrz-vobox.grid.lrz-muenchen.de:3128)'

#os.environ['FRONTIER_LOG_LEVEL']='debug'
# Should not need to change defualt actually!(10)
#os.environ['FRONTIER_READTIMEOUTSECS']='60'


#
import glob
from AthenaCommon.AthenaCommonFlags import athenaCommonFlags
from AthenaCommon.GlobalFlags import globalflags
from AthenaCommon.AlgSequence import AlgSequence
from AthenaCommon.AppMgr import ToolSvc,theApp,ServiceMgr
from AthenaCommon.Resilience import treatException,protectedInclude

##
## The following try... except is only needed for ganga!
##

try:
    import string
    inp=open("input.py").readlines()
    print inp
    print
    for i in inp:
        print i
        if i.find("ServiceMgr.EventSelector.InputCollections")>=0 or i.find("mySampleList = ")>=0:
            print "--> Found match"
            t=i.split("=")
            print t
            filename = t[1].strip()
            exec("athenaCommonFlags.FilesInput.set_Value_and_Lock("+filename+")")
            print "Result"
            print athenaCommonFlags.FilesInput
except Exception, inst:
    print inst
    pass
##
## End of hack for ganga
##

## get the input collection from FileStagerInputCollection
## try-except statement as a workaround for passing through the prepare() method
ic = []
try:
    if FileStagerInputCollection:
        ic = FileStagerInputCollection
except NameError:
    pass

# POOL input
import AthenaPoolCnvSvc.ReadAthenaPool
ServiceMgr.PoolSvc.AttemptCatalogPatch=True
globalflags.DataSource.set_Value_and_Lock('data')

# Auto geometry ?
from RecExConfig.RecFlags import rec

try:
    if ic:
        athenaCommonFlags.FilesInput.set_Value_and_Lock( ic )
    globalflags.InputFormat.set_Value_and_Lock('pool')
    rec.AutoConfiguration.unlock()
    rec.AutoConfiguration.set_Value_and_Lock( ['FieldAndGeo', 'ConditionsTag'])
#rec.AutoConfiguration = ['everything']
#rec.AutoConfiguration.set_Value_and_Lock( ['everything'])
#athenaCommonFlags.PoolESDInput.set_Value_and_Lock([''])
#rec.readESD.set_Value_and_Lock(True)
    if len(rec.AutoConfiguration())>0:
        from RecExConfig.AutoConfiguration import ConfigureFromListOfKeys
        ConfigureFromListOfKeys(rec.AutoConfiguration())
except:
    pass

# Detector geometry and magnetic field 
#globalflags.DetDescrVersion.set_Value_and_Lock('ATLAS-GEO-03-00-00')
#globalflags.DetDescrVersion.set_Value_and_Lock('ATLAS-GEONF-08-00-00')
include("RecExCond/AllDet_detDescr.py")
#from RecExCommission.RecExCommission_MagneticFieldConfig import setFieldConfig
#setFieldConfig(RunNumber)      
topSequence = AlgSequence()

# Conditions
#globalflags.ConditionsTag.set_Value_and_Lock('COMCOND-REPC-003-00')
#globalflags.ConditionsTag.set_Value_and_Lock('COMCOND-REPC-002-13') # for current remote DB  !!!!SLOW!!!!
#include("RecJobTransforms/UseOracle.py") # for current remote DB  !!!!SLOW!!!!
from IOVDbSvc.CondDB import conddb
conddb.setGlobalTag(globalflags.ConditionsTag())

# Trigger
from TriggerJobOpts.TriggerConfigGetter import TriggerConfigGetter
cfg = TriggerConfigGetter('ReadPool')

# The Main Job Options
include("RecExCommission/RecExCommission.py")                

# POOL input
#import AthenaPoolCnvSvc.ReadAthenaPool
#svcMgr.PoolSvc.AttemptCatalogPatch=True
#fileList = glob.glob('/tmp/elmsheus/data09_cos.00122189.physics_CosmicMuons.merge.DPD_TILECOMM.r733_p37_tid074135/*')
#svcMgr.EventSelector.InputCollections = fileList

#athenaCommonFlags.FilesInput = [svcMgr.EventSelector.InputCollections[0]]

# Set output level threshold (2=DEBUG, 3=INFO, 4=WARNING, 5=ERROR, 6=FATAL )
ServiceMgr.MessageSvc.OutputLevel = INFO
ServiceMgr.MessageSvc.infoLimit = 0
#theApp.EvtMax = 10

# Load MuAnalysis
from CosmicsAnalysis.CosmicsAnalysisConf import MuAnalysis
m = MuAnalysis()
m.OutputLevel = WARNING
m.tilemuon_filler = "TileCosmicMuonHT"
#m.specmuon_filler = "StacoMuonCollection"
m.specmuon_filler = "MuidMuonCollection"
m.calocell_filler = "AllCalo"
m.calomuon_filler = "CaloMuonCollection"
m.OutputLevel = INFO
m.OutputFile = "Cosmic_09Data_IDCosmic.root"
topSequence += m

# use closest DB replica
from AthenaCommon.AppMgr import ServiceMgr
from PoolSvc.PoolSvcConf import PoolSvc
ServiceMgr+=PoolSvc(SortReplicas=True)
from DBReplicaSvc.DBReplicaSvcConf import DBReplicaSvc
ServiceMgr+=DBReplicaSvc(UseCOOLSQLite=False)



from GaudiSvc.GaudiSvcConf import AuditorSvc
ServiceMgr.AuditorSvc.Auditors  += [ "ChronoAuditor"]
#AthenaPoolCnvSvc = Service("AthenaPoolCnvSvc")
#AthenaPoolCnvSvc.UseDetailChronoStat = TRUE

