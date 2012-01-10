# Author: Jyothsna Rani Komaragiri

from AthenaCommon.AppMgr import theApp
from AthenaCommon.AppMgr import ToolSvc
from AthenaCommon.AppMgr import ServiceMgr

from GaudiSvc.GaudiSvcConf import THistSvc
ServiceMgr+=THistSvc()

from AthenaCommon.AlgSequence import AlgSequence

theJob = AlgSequence()

from SUSYValidation.SUSYValidationConf import *

########### Read in AOD

# Event selector
import AthenaPoolCnvSvc.ReadAthenaPool

from PartPropSvc.PartPropSvcConf import *
#include( "PartPropSvc/PartPropSvc.py" )

# the POOL converters
###===###include( "ParticleBuilderOptions/ESD_PoolCnv_jobOptions.py" )
###===###include( "ParticleBuilderOptions/AOD_PoolCnv_jobOptions.py")
###===###include( "ParticleBuilderOptions/McAOD_PoolCnv_jobOptions.py")
###===###include( "EventAthenaPool/EventAthenaPool_joboptions.py" )
###===###include( "JetTagEvent/JetTagEventDict_joboptions.py" )

#include("EventViewConfiguration/EventViewFullInclude_jobOptions.py")

# Suggested by Hong
#theApp.Dlls += [ "RecAthenaPoolPoolCnv" ]

# Read in the AOD from POOL - AOD.pool.root
# this file is produced by running the AOD builders of the RDO raw data
# The AOD input file

# Read in AOD file
ServiceMgr.EventSelector.InputCollections = ["AOD.pool.root"]
#include( "InputCollections.py" )
# Set output level threshold (2=DEBUG, 3=INFO, 4=WARNING, 5=ERROR, 6=FATAL )
ServiceMgr.MessageSvc = Service( "MessageSvc" )
ServiceMgr.MessageSvc.OutputLevel = INFO

# Trigger configuration
doTrigger = False

########### Run analysis

# Number of Events to process
theApp.EvtMax = -1
#theApp.EvtMax = 50
ServiceMgr.MessageSvc.defaultLimit = 9999999  # all messages

if "doTrigger" not in dir():
 doTrigger = True

if "doAudit" not in dir():
 doAudit=True

# The user analysis algorithm to be executed
from AthenaCommon.AlgSequence import AlgSequence
topSequence = AlgSequence()

from TrigDecision.TrigDecisionConfig import TrigDecisionTool_XMLConfig
from AthenaCommon.AppMgr import ToolSvc
from TrigDecision.TrigDecisionConfig import *
ToolSvc += TrigDecisionTool_XMLConfig('TrigDecisionTool')

###Select Input
TrigMissingET="HLTAutoKey_TrigEFMissingET_145610168_1"
TrigDecision="TrigDecision"

McEventCollection="GEN_AOD"
TruthParticleContainer="SpclMC"

TrackParticleContainer="TrackParticleCandidate"
TruthJetContainer="Cone4TruthJets"
JetContainer="Cone4H1TowerJets"

ElectronContainer="ElectronAODCollection"
MuonContainer="StacoMuonCollection"
MuonSpShowerContainer="MuonSpShowers"
TauJetContainer="TauRecContainer"
TauDetailsContainer="TauRecDetailsContainer"

PhotonContainer="PhotonAODCollection"
MissingET="MET_RefFinal"
MissingEtTruth ="MET_Truth"

#####
MetPlot = EVPlot("MetPlot")
MetPlot.DoTrigger = doTrigger
MetPlot.HistToolKeys = [ "EVGlobalTool/gTool" ]
MetPlot+=EVGlobalTool("gTool")
MetPlot.gTool.InputJets=JetContainer
MetPlot.gTool.McEventName=McEventCollection
MetPlot.gTool.MuonName=MuonContainer
MetPlot.gTool.InputEventView=MissingET
MetPlot.gTool.InputTruthView=MissingEtTruth
MetPlot.gTool.MuonShowers = MuonSpShowerContainer
MetPlot.gTool.TriggerMissingETName=TrigMissingET
MetPlot.gTool.TriggerDecisionName=TrigDecision
MetPlot.TrigDecisionTool = ToolSvc.TrigDecisionTool
theJob+=MetPlot

LeptonPlot = EVPlot("LeptonPlot")
LeptonPlot.DoTrigger = doTrigger
LeptonPlot.HistToolKeys = [ "EVElectronTool/eTool", "EVMuonTool/muTool", "EVTauTool/tauTool" ]
LeptonPlot+=EVElectronTool("eTool")
LeptonPlot.eTool.InputEventView=ElectronContainer
LeptonPlot.eTool.InputTruthView=TruthParticleContainer
LeptonPlot.eTool.McEventName=McEventCollection
LeptonPlot.eTool.OutputLevel=INFO
LeptonPlot+=EVMuonTool("muTool")
LeptonPlot.muTool.InputEventView=MuonContainer
LeptonPlot.muTool.InputTruthView=TruthParticleContainer
LeptonPlot.muTool.MET=MissingET
LeptonPlot.muTool.McEventName=McEventCollection
LeptonPlot.muTool.OutputLevel=INFO
LeptonPlot+=EVTauTool("tauTool")
LeptonPlot.tauTool.TauContainerName=TauJetContainer
LeptonPlot.tauTool.TauDetailsContainerName=TauDetailsContainer
LeptonPlot.tauTool.InputTruthView=TruthParticleContainer
LeptonPlot.tauTool.JetContaineName=JetContainer
LeptonPlot.tauTool.McEventName=McEventCollection
LeptonPlot.TrigDecisionTool = ToolSvc.TrigDecisionTool
LeptonPlot.tauTool.OutputLevel=INFO
theJob+=LeptonPlot

JetPlot = EVPlot("JetPlot")
JetPlot.DoTrigger = doTrigger
JetPlot.HistToolKeys = [ "EVJetTool/jTool","EVbJetTool/bjTool" ]
JetPlot+=EVJetTool("jTool")
JetPlot.jTool.InputEventView=JetContainer
JetPlot.jTool.InputTruthView=TruthJetContainer
JetPlot.jTool.McEventName=McEventCollection
JetPlot.jTool.OutputLevel=INFO
JetPlot+=EVJetTool("bjTool")
JetPlot.bjTool.InputEventView=JetContainer
JetPlot.bjTool.InputTruthView=TruthJetContainer
JetPlot.bjTool.InputTruthParticles=TruthParticleContainer
JetPlot.bjTool.InputTrackParticles=TrackParticleContainer
JetPlot.bjTool.McEventName=McEventCollection
JetPlot.TrigDecisionTool = ToolSvc.TrigDecisionTool
JetPlot.bjTool.OutputLevel=INFO
theJob+=JetPlot

PhotonPlot = EVPlot("PhotonPlot")
PhotonPlot+=EVPhotonTool("gmtool")
PhotonPlot.DoTrigger = doTrigger
PhotonPlot.HistToolKeys = [ "EVPhotonTool/gmtool" ]
PhotonPlot.gmtool.InputEventView=PhotonContainer
PhotonPlot.gmtool.InputTruthView=TruthParticleContainer
PhotonPlot.gmtool.McEventName=McEventCollection
PhotonPlot.TrigDecisionTool = ToolSvc.TrigDecisionTool
PhotonPlot.gmtool.OutputLevel=INFO
theJob+=PhotonPlot

SusyPlot = EVPlot("SusyPlot")
SusyPlot.DoTrigger = doTrigger
SusyPlot.HistToolKeys = [ "EVSusyRec/susyTool" ]
SusyPlot+=EVSusyRec("susyTool")
SusyPlot.susyTool.ElectronName=ElectronContainer
SusyPlot.susyTool.MuonName=MuonContainer
SusyPlot.susyTool.TauName=TauJetContainer
SusyPlot.susyTool.JetName=JetContainer
SusyPlot.susyTool.MetName=MissingET
SusyPlot.susyTool.TruthName=TruthParticleContainer
SusyPlot.susyTool.McEventName=McEventCollection
SusyPlot.TrigDecisionTool = ToolSvc.TrigDecisionTool
SusyPlot.susyTool.OutputLevel=INFO
theJob+=SusyPlot

SusyPlot.susyTool.PtLeptonCut = 20*GeV
SusyPlot.susyTool.PtLeptonPreCut = 10*GeV 
SusyPlot.susyTool.etaLeptonCut = 2.5
SusyPlot.susyTool.EtIsolCut = 10*GeV
SusyPlot.susyTool.EtMissCut = 100*GeV
SusyPlot.susyTool.etaJetCut = 2.5
SusyPlot.susyTool.PtJetCut = 20*GeV
SusyPlot.susyTool.PtJet0Cut = 100*GeV
SusyPlot.susyTool.PtJet1Cut = 50*GeV
SusyPlot.susyTool.MeffCut = 800*GeV
SusyPlot.susyTool.MTCut = 100*GeV
SusyPlot.susyTool.STCut = 0.2
SusyPlot.susyTool.CrackVeto = False

##

# Root Ntuple output file and name
ServiceMgr.THistSvc.Output = ["hist DATAFILE='SUSYValidation.root' OPT='RECREATE'"]

###################### Detail time measurement and auditors
# Use auditors
theApp.AuditAlgorithms=True
theApp.Dlls += [ "GaudiAud" ]

#include ("LSFTimeKeeper/LSFTimeKeeperOptions.py")
#LSFTimeKeeperSvc= Service("LSFTimeKeeperSvc")
#LSFTimeKeeperSvc.OutputLevel=INFO

#theAuditorSvc = AuditorSvc()
#theAuditorSvc.Auditors  += [ "ChronoAuditor"]

AthenaPoolCnvSvc = Service("AthenaPoolCnvSvc")
AthenaPoolCnvSvc.UseDetailChronoStat = TRUE

#increase the number of letter reserved to the alg/tool name from 18 to 30
ServiceMgr.MessageSvc.Format = "% F%40W%S%7W%R%T %0W%M"

#
# write out a list of all Storegate collection with their keys and
# lock/unlock state. Very useful for debugging purpose
#
#StoreGateSvc = Service ("StoreGateSvc" )
#StoreGateSvc.Dump = True
