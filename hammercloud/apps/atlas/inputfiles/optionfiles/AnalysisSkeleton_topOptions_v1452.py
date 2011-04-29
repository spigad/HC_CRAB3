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
#ServiceMgr.EventSelector.InputCollections = [ "/scratch/data/mc08.105013.J4_pythia_jetjet.recon.AOD.e344_s456_r456_tid024235/AOD.024235._01010.pool.root.2"]
#ServiceMgr.EventSelector.InputCollections = [ "/scratch/data/valid3.005200.T1_McAtNlo_Jimmy.recon.AOD.e322_s412_r555_tid026941/AOD.026941._00034.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections = [ "/scratch/data/mc08.106051.PythiaZmumu_1Lepton.recon.AOD.e347_s462_r541_tid028716/AOD.028716._03666.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.106051.PythiaZmumu_1Lepton.recon.AOD.e347_s462_r541_tid028716/AOD.028716._03430.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.106051.PythiaZmumu_1Lepton.recon.AOD.e347_s462_r541_tid028716/AOD.028716._03440.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.106051.PythiaZmumu_1Lepton.recon.AOD.e347_s462_r541_tid028716/AOD.028716._03050.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.106051.PythiaZmumu_1Lepton.recon.AOD.e347_s462_r541_tid028716/AOD.028716._02891.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.106051.PythiaZmumu_1Lepton.recon.AOD.e347_s462_r541_tid028716/AOD.028716._03499.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.106051.PythiaZmumu_1Lepton.recon.AOD.e347_s462_r541_tid028716/AOD.028716._03318.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.106051.PythiaZmumu_1Lepton.recon.AOD.e347_s462_r541_tid028716/AOD.028716._03798.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.106051.PythiaZmumu_1Lepton.recon.AOD.e347_s462_r541_tid028716/AOD.028716._03063.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.106051.PythiaZmumu_1Lepton.recon.AOD.e347_s462_r541_tid028716/AOD.028716._02992.pool.root.2"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.106051.PythiaZmumu_1Lepton.recon.AOD.e347_s462_r541_tid028716/AOD.028716._03635.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.106051.PythiaZmumu_1Lepton.recon.AOD.e347_s462_r541_tid028716/AOD.028716._03384.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.106051.PythiaZmumu_1Lepton.recon.AOD.e347_s462_r541_tid028716/AOD.028716._03340.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.106051.PythiaZmumu_1Lepton.recon.AOD.e347_s462_r541_tid028716/AOD.028716._03295.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.106051.PythiaZmumu_1Lepton.recon.AOD.e347_s462_r541_tid028716/AOD.028716._02881.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.106051.PythiaZmumu_1Lepton.recon.AOD.e347_s462_r541_tid028716/AOD.028716._03517.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.106051.PythiaZmumu_1Lepton.recon.AOD.e347_s462_r541_tid028716/AOD.028716._03584.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.106051.PythiaZmumu_1Lepton.recon.AOD.e347_s462_r541_tid028716/AOD.028716._03153.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.106051.PythiaZmumu_1Lepton.recon.AOD.e347_s462_r541_tid028716/AOD.028716._03191.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.106051.PythiaZmumu_1Lepton.recon.AOD.e347_s462_r541_tid028716/AOD.028716._02904.pool.root.2"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.106051.PythiaZmumu_1Lepton.recon.AOD.e347_s462_r541_tid028716/AOD.028716._03261.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.106051.PythiaZmumu_1Lepton.recon.AOD.e347_s462_r541_tid028716/AOD.028716._03488.pool.root.1"]

#ServiceMgr.EventSelector.InputCollections = [ "/scratch/data/mc08.105200.T1_McAtNlo_Jimmy.recon.AOD.e357_s462_r541_tid025888/AOD.025888._00002.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.105200.T1_McAtNlo_Jimmy.recon.AOD.e357_s462_r541_tid025888/AOD.025888._00006.pool.root.1"]                               
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.105200.T1_McAtNlo_Jimmy.recon.AOD.e357_s462_r541_tid025888/AOD.025888._00013.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.105200.T1_McAtNlo_Jimmy.recon.AOD.e357_s462_r541_tid025888/AOD.025888._00018.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.105200.T1_McAtNlo_Jimmy.recon.AOD.e357_s462_r541_tid025888/AOD.025888._00021.pool.root.2"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.105200.T1_McAtNlo_Jimmy.recon.AOD.e357_s462_r541_tid025888/AOD.025888._00045.pool.root.1"]                               
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.105200.T1_McAtNlo_Jimmy.recon.AOD.e357_s462_r541_tid025888/AOD.025888._00056.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.105200.T1_McAtNlo_Jimmy.recon.AOD.e357_s462_r541_tid025888/AOD.025888._00067.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.105200.T1_McAtNlo_Jimmy.recon.AOD.e357_s462_r541_tid025888/AOD.025888._00068.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.105200.T1_McAtNlo_Jimmy.recon.AOD.e357_s462_r541_tid025888/AOD.025888._00076.pool.root.1"]                               
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.105200.T1_McAtNlo_Jimmy.recon.AOD.e357_s462_r541_tid025888/AOD.025888._00085.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.105200.T1_McAtNlo_Jimmy.recon.AOD.e357_s462_r541_tid025888/AOD.025888._00103.pool.root.2"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.105200.T1_McAtNlo_Jimmy.recon.AOD.e357_s462_r541_tid025888/AOD.025888._00118.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.105200.T1_McAtNlo_Jimmy.recon.AOD.e357_s462_r541_tid025888/AOD.025888._00136.pool.root.1"]                               
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.105200.T1_McAtNlo_Jimmy.recon.AOD.e357_s462_r541_tid025888/AOD.025888._00148.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.105200.T1_McAtNlo_Jimmy.recon.AOD.e357_s462_r541_tid025888/AOD.025888._00165.pool.root.2"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.105200.T1_McAtNlo_Jimmy.recon.AOD.e357_s462_r541_tid025888/AOD.025888._00168.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.105200.T1_McAtNlo_Jimmy.recon.AOD.e357_s462_r541_tid025888/AOD.025888._00185.pool.root.1"]                               
#ServiceMgr.EventSelector.InputCollections += [ "/scratch/data/mc08.105200.T1_McAtNlo_Jimmy.recon.AOD.e357_s462_r541_tid025888/AOD.025888._00187.pool.root.1"]            
#ServiceMgr.EventSelector.InputCollections = [ "/scratch/data/mc08.106021.PythiaWmunu_1Lepton.recon.AOD.e352_s462_r617_tid041726/AOD.041726._00876.pool.root.1"]
#ServiceMgr.EventSelector.InputCollections = [ "/tmp/elmsheus/mc08.105200.T1_McAtNlo_Jimmy.recon.AOD.e357_s462_r541_tid026357/AOD.026357._00511.pool.root.1"]
ServiceMgr.EventSelector.InputCollections = [ "/tmp/elmsheus/mc08.105200.T1_McAtNlo_Jimmy.recon.AOD.e357_s462_r635_tid045663/AOD.045663._00161.pool.root.1"]

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

AthenaPoolCnvSvc = Service("AthenaPoolCnvSvc")
AthenaPoolCnvSvc.UseDetailChronoStat = TRUE

StoreGateSvc = Service( "StoreGateSvc" )
#StoreGateSvc.Dump = True 
#MessageSvc.OutputLevel = INFO


