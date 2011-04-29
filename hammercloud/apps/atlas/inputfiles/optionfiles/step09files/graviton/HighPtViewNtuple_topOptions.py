##################################################################
# Author: Akira Shibata (ashibata@cern.ch)
#         Amir Farbin (afarbin@cern.ch)
##################################################################


###########################################
# Common imports and includes (no need to edit)
###########################################
from AthenaCommon.AppMgr import theApp
from AthenaCommon.AppMgr import ToolSvc
from AthenaCommon.AppMgr import ServiceMgr

from AthenaCommon.AlgSequence import AlgSequence

from HighPtView.HighPtViewAnalysis import *

# read AOD
include ("AthenaPoolCnvSvc/ReadAthenaPool_jobOptions.py" )

###########################################
# Job Properties setting (change as appr)
###########################################
# specify input filea
EventSelector = ServiceMgr.EventSelector
if not isinstance(EventSelector.InputCollections,list):
  EventSelector.InputCollections = ["AOD.pool.root"]

#EventSelector.InputCollections = ["AOD.pool.root"]

###########################################
# Pre-config settings (change as appropriate)
###########################################
# instanciate the top alg sequence for athena, only one is required
theJob = AlgSequence()

# you can set the following option from outside either by using -c option of athena
# or including another joboption BEFORE this jobOption. That's what the "if not..." does
# so the following is the default
if not "Mode" in dir():                Mode=["FullReco", "Truth", "Atlfast"]
if not "DetailLevel" in dir():         DetailLevel=["BasicAOD", "El_Info:FullStandardAOD","Ph_Info:FullStandardAOD"] # Or "FullStandardAOD", "Kinematics", ...
if not "Branches" in dir():            Branches= ["MuidTau1p3p"] #,"MuidTauRec","StacoTau1p3p","StacoTauRec"]
if not "KinematicsOnly" in dir():      KinematicsOnly=False # This overrides DetailLevel setting it to Kinematics
if not "NtupleName" in dir():          NtupleName="HighPtAANtuple.root"
if not "DoScreenDump" in dir():        DoScreenDump=True
if not "ShowUserData" in dir():        ShowUserData=False
if not "DoNtupleDump" in dir():        DoNtupleDump=True
if not "OutputLevel" in dir():         OutputLevel=3
if not "DoTrigger" in dir():           DoTrigger=False
if not "OutputDirectory" in dir():     OutputDirectory="."
if not 'SingleHPTVFile' in dir():      SingleHPTVFile=False
if not "TriggerLevels" in dir():       TriggerLevels=[ "L1", "L2", "EF",
                                                       "Muon", "E/Gamma", "Electron", "Photon", "Tau",
                                                       "Jet", "MissingEt" ]
if not "SaveHLTMET" in dir():          SaveHLTMET=False # Our test AOD sample didn't have this info

if not "TruthInserter" in dir():       TruthInserter=HighPtTruthInserter
if not "RecoInserter" in dir():        RecoInserter=HighPtSingleInserters
if not "AnalysisModules" in dir():     AnalysisModules={}

if not "ExtraMETKeys" in dir():        ExtraMETKeys=[]

if not "TriggerView" in dir():         TriggerView=False
if not "TrigDecInFullRecTree" in dir(): TrigDecInFullRecTree=True

if not "StoreGateDump" in dir():       StoreGateDump=False
if not "InserterConfiguration" in dir(): InserterConfiguration=None

if not "PerfSaveDeltaR" in dir():      PerfSaveDataR=False

if StoreGateDump:
  print "Setting StoreGateDump"
  ServiceMgr.StoreGateSvc.Dump = True  

###########################################
# Prepare Truth Objects
###########################################
if "Truth" in Mode:
  include("HighPtView/TruthThinning_jobOptions.py")

###########################################
# Prepare Trigger Objects
###########################################
if DoTrigger:
  from EventViewTrigger.TrigDecisionToolOnAOD_module import TrigDecisionToolOnAOD
  TrigDecisionToolOnAOD().setRelease( "13.0.30" )
  from EventViewTrigger import *
  if TriggerView:
    # include full trigger tree
    triggerLooper = EVMultipleOutputToolLooper( "triggerLooper" )
    triggerLooper.EventViewCollectionOutputName = "TriggerView"
    theJob += triggerLooper
    theJob.triggerLooper += TriggerPreparators( "trigPreparators", slices = [ "Muon", "Electron", "Photon", "Tau", "Jet"  ] )
    theJob.triggerLooper += TriggerInserters( "trigInserters", slices = [ "Muon", "Electron", "Photon", "Tau", "Jet"  ] )
    theJob.triggerLooper += TriggerCalculators( "trigCalculators", slices = [ "Muon", "Electron", "Jet", "Tau", "Photon" ] )

    theJob.triggerLooper += EVTrigDecisionUserDataAOD("trigDec")
    
    if DoScreenDump:
      triggerLooper += EVScreenDump("ScreenDumperTrigger", printUD=ShowUserData)

    triggerLooper += AANtupleFromUserData( "TriggerAADumper", filename = "Trigger_"+NtupleName,
                                           sequencer = theJob, EventTree = True,
                                           CandTree = False, Prefix = "Trigger" )
  else:
    TriggerPrepLooper= EVMultipleOutputToolLooper("TriggerPrepLooper")
    TriggerPrepLooper.EventViewCollectionOutputName="DummyTriggerView"
    if "L1" in TriggerLevels:
      TriggerPrepLooper += LVL1Preparator("L1TrigPrep")
    if "L2" in TriggerLevels:
      TriggerPrepLooper += LVL2Preparators("L2TrigPrep")      
    if "EF" in TriggerLevels:
      TriggerPrepLooper += EFPreparators("EFTrigPrep")
    theJob += TriggerPrepLooper

print "Configuring HighPtView..."

###########################################
# General Configuration
###########################################

MyAnalysis=HighPtViewAnalysis(theJob,
                              mode=Mode,
                              doTrigger=DoTrigger,
                              trigDecInFullRecTree=TrigDecInFullRecTree,
                              doNtupleDump=DoNtupleDump,
                              doScreenDump=DoScreenDump,
                              outputLevel=OutputLevel,
                              kinematicsOnly=KinematicsOnly,
                              showUserData=ShowUserData,
                              detailLevel=DetailLevel,
                              saveHLTMET=SaveHLTMET,
                              TruthInserter=TruthInserter,
                              RecoInserter=RecoInserter,
                              AnalysisModules=AnalysisModules,
                              extraMETKeys=ExtraMETKeys,
                              InserterConfiguration=InserterConfiguration)

###########################################
# The Analysis
###########################################

branchNum=0

HPTVSequence=[]

for Branch in Branches:
  if 'HPTVNtupleOutput' in dir():
    if SingleHPTVFile:
      HPTVSequence+=MyAnalysis.schedule(Branch,NtupleName=SingleHPTVNtupleOutput, TreePrefix=Branch+"_")
    else:
      HPTVSequence+=MyAnalysis.schedule(Branch,NtupleName=HPTVNtupleOutput[branchNum])
    branchNum+=1
  else:
    if SingleHPTVFile:
      HPTVSequence+=MyAnalysis.schedule(Branch,NtupleName=OutputDirectory+"/"+NtupleName, TreePrefix=Branch+"_")
    else:
      HPTVSequence+=MyAnalysis.schedule(Branch,NtupleName=OutputDirectory+"/"+Branch+"_"+NtupleName)

# Move ntuple streams to the END

NtupleStreams=[]

for Step in HPTVSequence:
  if 'EVAANtupleDump' in Step.name():
    NtupleStreams+=[Step]
  else:
    theJob+=Step

theJob+=NtupleStreams

print "Done Configuring HighPtView..."


###########################################
# Final setup (no need to edit)
###########################################
ServiceMgr.MessageSvc.Format = "% F%70W%S%7W%R%T %0W%M"
ServiceMgr.StatusCodeSvc.SuppressCheck=True

print theJob
print "TopAlg:"
print theApp.TopAlg
