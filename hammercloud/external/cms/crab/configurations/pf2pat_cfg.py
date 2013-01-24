import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing

process = cms.Process("NTupleProducer")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = "ERROR"
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")


############ PF2PAT ##########################################
# load the standard PAT config
process.load("PhysicsTools.PatAlgos.patSequences_cff")
from PhysicsTools.PatAlgos.patEventContent_cff import patEventContent

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(50000) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
'/store/mc/HC/GenericTTbar/GEN-SIM-RECO/CMSSW_5_3_1_START53_V5-v1/0010/B4C55F00-BDAD-E111-9841-003048D2C1C4.root'
    )
                            )


# Add a pro forma output module because PF2PAT complains otherwise...
process.out = cms.OutputModule("PoolOutputModule",
                               # save only events passing the full path
                               SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                               # save PAT Layer 1 output; you need a '*' to
                               outputCommands = cms.untracked.vstring('drop *' )
                               )

############
# Global Tag: this MUST BE UPDATED IF MAJOR/MINOR RELEASE IS CHANGED (eg from 5_3 to 5_4)
# list of GlobalTags: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideFrontierConditions
process.GlobalTag.globaltag = cms.string("START52_V7::All")


####################
# PF2PAT sequence: this can change with MINOR/MAJOR releases, please check here:
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookPF2PAT
# http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/CMSSW/PhysicsTools/PatAlgos/test/patTuple_PF2PAT_cfg.py
from PhysicsTools.PatAlgos.tools.pfTools import *
postfix = "PFlow"
jetAlgo="AK5"
usePF2PAT(process,runPF2PAT=True, jetAlgo=jetAlgo, runOnMC=True, postfix=postfix)

#the dump, just for test (disabled)
process.dump=cms.EDAnalyzer('EventContentAnalyzer')

#Timing module
process.Timing = cms.Service("Timing",
                             useJobReport = cms.untracked.bool(True)
                             )

### TFileAdaptor settings
#process.AdaptorConfig = cms.Service("AdaptorConfig",
#                                    tempDir=cms.untracked.string(""),
#                                    cacheHint=cms.untracked.string("lazy-download"),
#                                    readHint=cms.untracked.string("auto-detect"))
#process.source.cacheSize = cms.untracked.uint32(20*1024*1024)

process.p = cms.Path(
    process.patPF2PATSequence
    #+ process.dump
    )



