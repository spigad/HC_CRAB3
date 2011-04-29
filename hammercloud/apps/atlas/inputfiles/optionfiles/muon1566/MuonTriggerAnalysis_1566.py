

from AthenaCommon.AthenaCommonFlags import athenaCommonFlags
from RecExConfig.RecFlags import rec


# The AOD input file
#athenaCommonFlags.FilesInput = [ "/scratch/michela/data/mc08.108422.Pythia_directJpsimu2p5mu2p5.recon.ESD.e355_s462_s520_r809_tid092538/ESD.092538._000021.pool.root.1"]
athenaCommonFlags.FilesInput = [ '/tmp/elmsheus/mc08.108422.Pythia_directJpsimu2p5mu2p5.merge.AOD.e355_s462_r635_t53_tid064600/AOD.064600._00001.pool.root.1' ]

rec.AutoConfiguration=['everything']

#do not run trigger; this overrides AutoConfiguration
rec.doTrigger.set_Value_and_Lock(False)

# Output log setting; this is for the framework in general and overrides AutoConfiguration
rec.OutputLevel.set_Value_and_Lock(INFO); 

# Input/Output read/write locked settings; this 
rec.doCBNT.set_Value_and_Lock(False)
rec.doWriteAOD.set_Value_and_Lock(False)
rec.doWriteESD.set_Value_and_Lock(False)
rec.doWriteTAG.set_Value_and_Lock(False)
#To specify a new condition
#globalflags.ConditionsTag.set_Value_and_Lock('someNewConditionsTag')

# main jobOption - must always be included
include ("RecExCommon/RecExCommon_topOptions.py")



include ("CBNT_Athena/CBNT_AthenaAware_jobOptions.py")
include ("CBNT_Athena/CBNT_EventInfo_jobOptions.py")

# list of the algorithms to be executed at run time
from UserAnalysis.UserAnalysisConf import AnalysisSkeleton
CBNT_AthenaAware += AnalysisSkeleton() 

############# The properties of the AnalysisSkeleton Algorithm
CBNT_AthenaAware.AnalysisSkeleton.MCParticleContainer = "SpclMC"
CBNT_AthenaAware.AnalysisSkeleton.DeltaRMatchCut = 0.15
CBNT_AthenaAware.AnalysisSkeleton.DeltaRMatchCutLOW = 0.15
CBNT_AthenaAware.AnalysisSkeleton.DeltaRMatchCutL1 = 0.15
CBNT_AthenaAware.AnalysisSkeleton.MaxDeltaR = 0.9999
CBNT_AthenaAware.AnalysisSkeleton.doMCTruth = False
CBNT_AthenaAware.AnalysisSkeleton.doTrigDec = True
#CBNT_AthenaAware.AnalysisSkeleton.OutputLevel = DEBUG
CBNT_AthenaAware.AnalysisSkeleton.OutputLevel = ERROR

##
##########################################
## Set up trigger configuration service and metadata service is relies on, for analysis job without RecExCommon

from AthenaCommon.GlobalFlags import GlobalFlags
GlobalFlags.DetGeo.set_atlas()

##############################################################
# Set up trigger configuration service and metadata service it relies on, for analysis job without RecExCommon
# set up trigger decision tool
from AthenaCommon.AppMgr import ToolSvc
from TrigDecisionTool.TrigDecisionToolConf import Trig__TrigDecisionTool
tdt = Trig__TrigDecisionTool("TrigDecisionTool")
ToolSvc += tdt


# flags needed for TriggerConfigGetter
from RecExConfig.RecFlags  import rec
rec.readRDO=False
rec.readAOD=True
rec.doWriteAOD=False
rec.doWriteESD=False



###############################################################
## END of trigger setup

##########################################
# setup TTree registration Service
# save ROOT histograms and Tuple
from GaudiSvc.GaudiSvcConf import THistSvc
ServiceMgr += THistSvc()
ServiceMgr.THistSvc.Output = [ "AANT DATAFILE='muTri.root' OPT='RECREATE'" ]
from AnalysisTools.AnalysisToolsConf import AANTupleStream
topSequence += AANTupleStream()
topSequence.AANTupleStream.ExtraRefNames = [ "StreamESD","Stream1" ]
topSequence.AANTupleStream.OutputName = 'pippo.root'
topSequence.AANTupleStream.WriteInputDataHeader = True
topSequence.AANTupleStream.OutputLevel = WARNING

# Set output level threshold (2=DEBUG, 3=INFO, 4=WARNING, 5=ERROR, 6=FATAL )
ServiceMgr.MessageSvc.OutputLevel = INFO
ServiceMgr.MessageSvc.infoLimit = 0

# Number of Events to process
theApp.EvtMax = 5
#theApp.SkipEvents = 500
#ServiceMgr.EventSelector.SkipEvents = SkipEvents

###################### For interactive analysis
#include ("PyAnalysisCore/InitPyAnalysisCore.py")

###################### Detail time measurement and auditors
# Use auditors
#theApp.AuditAlgorithms=True
#theApp.Dlls += [ "GaudiAud" ]

from GaudiSvc.GaudiSvcConf import AuditorSvc
ServiceMgr.AuditorSvc.Auditors  += [ "ChronoAuditor"]

#AthenaPoolCnvSvc = Service("AthenaPoolCnvSvc")
#AthenaPoolCnvSvc.UseDetailChronoStat = TRUE

StoreGateSvc = Service( "StoreGateSvc" )
#StoreGateSvc.Dump = True 
#MessageSvc.OutputLevel = INFO


