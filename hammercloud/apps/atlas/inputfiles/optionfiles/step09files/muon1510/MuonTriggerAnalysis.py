# Author: Ketevi A. Assamagan
# BNL, June 12, 2004

#SkipEvents = 100
# get a handle on the ServiceManager which holds all the services
from AthenaCommon.AppMgr import ServiceMgr
# Event selector
import AthenaPoolCnvSvc.ReadAthenaPool
#EventSelector.BackNavigation = True

# Particle Properties
from PartPropSvc.PartPropSvcConf import PartPropSvc

# the POOL converters
include( "ParticleBuilderOptions/ESD_PoolCnv_jobOptions.py" )
include( "ParticleBuilderOptions/AOD_PoolCnv_jobOptions.py")
include( "ParticleBuilderOptions/McAOD_PoolCnv_jobOptions.py")
include( "EventAthenaPool/EventAthenaPool_joboptions.py" )

# The AOD input file

ServiceMgr.EventSelector.InputCollections = [ "/scratch/data/"]


# Athena-Aware NTuple making Tools
CBNTAthenaAware = True
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
from TrigDecision.TrigDecisionConfig import TrigDecisionTool
tdt = TrigDecisionTool()
ToolSvc += tdt
# flags needed for TriggerConfigGetter
from RecExConfig.RecFlags  import rec
rec.readRDO=False
rec.readAOD=True
rec.doWriteAOD=False
rec.doWriteESD=False

# To read files with trigger config stored as in-file meta-data,
# i.e. 13.0.40 and above: ds
# To read AOD produced with 13.0.30 you need to change ds to aod:
from TriggerJobOpts.TriggerFlags import TriggerFlags
TriggerFlags.configurationSourceList = ['ds']

# set up trigger config service
from TriggerJobOpts.TriggerConfigGetter import TriggerConfigGetter
cfg =  TriggerConfigGetter()

# might be needed for TriggerConfigGetter...
from RecExConfig.RecFlags  import rec
rec.readAOD=True
rec.doWriteAOD=False
rec.doWriteESD=False
# set up trigger config service
from TriggerJobOpts.TriggerConfigGetter import TriggerConfigGetter
cfg =  TriggerConfigGetter()
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

# Number of Events to process
theApp.EvtMax = 5000
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


