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

#include("input.r557.py")
#include("input.r557.py")
#include("input.r538.py")
ServiceMgr.EventSelector.InputCollections = [ "/scratch/data/mc08.105013.J4_pythia_jetjet.recon.AOD.e344_s456_r456_tid024235/AOD.024235._01010.pool.root.2"]
#ServiceMgr.EventSelector.InputCollections = [ "/scratch/data/mc08.005120.PythiaZgam_allLep.recon.AOD.e327_s400_d99_r474_tid023508/AOD.023508._00031.pool.root.2"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.107042.singlepart_gamma_Et60.recon.AOD.e342_s439_r546_tid026479/AOD.026479._00209.pool.root.8"]
#ServiceMgr.EventSelector.InputCollections = [ "/scratch/data/AOD.pool.NOroidriven.rel3.t0.root"]
#ServiceMgr.EventSelector.InputCollections = [ "/scratch/data/AOD.1.142x.rel5.pool.root"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/AOD.2.142x.rel5.pool.root"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/AOD.3.142x.rel5.pool.root"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/AOD.4.142x.rel5.pool.root"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/FDR2/fdr08_run2.0052300.physics_Muon.merge.AOD.o3_f48_m27/fdr08_run2.0052300.physics_Muon.merge.AOD.o3_f48_m27._0001.1"]
#ServiceMgr.EventSelector.InputCollections = [ "/scratch/data/AOD.pool.mu10.root"]
#include("input140001.py")
#include("input1410.py")
#include("input13030pile.py")
#include("input13030pile.py")
#include("input1303002.py")


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

## set up trigger decision tool
#from TrigDecision.TrigDecisionConfig import TrigDecisionTool
#tdt = TrigDecisionTool()
#tdt.UseFDRMode = True;
#####################ToolSvc += tdt

# might be needed for TriggerConfigGetter...
from RecExConfig.RecFlags  import rec
rec.readAOD=True
rec.doWriteAOD=False
rec.doWriteESD=False
# set up trigger config service
from TriggerJobOpts.TriggerConfigGetter import TriggerConfigGetter
cfg =  TriggerConfigGetter()

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
#theApp.EvtMax = 5000
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

AthenaPoolCnvSvc = Service("AthenaPoolCnvSvc")
AthenaPoolCnvSvc.UseDetailChronoStat = TRUE

StoreGateSvc = Service( "StoreGateSvc" )
#StoreGateSvc.Dump = True 
#MessageSvc.OutputLevel = INFO


