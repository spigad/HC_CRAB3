import FWCore.ParameterSet.Config as cms

process = cms.Process("PAT")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(100)
process.Timing = cms.Service("Timing",useJobReport = cms.untracked.bool(True))
#process.MessageLogger.cerr.threshold = cms.untracked.string("INFO")
#process.MessageLogger = cms.Service( "MessageLogger", categories = cms.untracked.vstring('info', 'debug','cout') )
#process.MessageLogger.cerr.FwkSummary = cms.untracked.PSet( reportEvery = cms.untracked.int32(1000000), limit = cms.untracked.int32(10000000) )
#process.MessageLogger.cerr.FwkReport = cms.untracked.PSet( reportEvery = cms.untracked.int32(100000), limit = cms.untracked.int32(10000000) )
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
#process.options = cms.untracked.PSet( Rethrow = cms.untracked.vstring('ProductNotFound') )
process.options = cms.untracked.PSet(SkipEvent = cms.untracked.vstring('ProductNotFound')) 
### source
process.source = cms.Source("PoolSource", 
     fileNames = cms.untracked.vstring(

'/store/data/Run2010A/EG/RECO/v4/000/139/020/1A3BDC11-5284-DF11-97BE-003048F1C58C.root'
#,'/store/data/Run2010A/EG/RECO/v4/000/139/096/C29F3C56-E184-DF11-977E-0030487CD13A.root'
#,' /store/data/Run2010A/EG/RECO/v4/000/139/407/84F6A982-7B88-DF11-86F1-000423D987E0.root'
#,'/store/data/Run2010A/EG/RECO/v4/000/139/781/427F7F65-478B-DF11-99F7-0016177CA778.root' ###May be this has my lumiSec
#,'/store/data/Run2010A/EG/RECO/v4/000/140/059/2E2DDD0E-948E-DF11-8125-003048F1C424.root'
#,'/store/data/Run2010A/EG/RECO/v4/000/140/124/568F0F04-238F-DF11-A412-0030487A3C9A.root'
#,'/store/data/Run2010A/EG/RECO/v4/000/140/124/38C3016B-638F-DF11-8232-003048F11114.root'
#,'/store/data/Run2010A/EG/RECO/v4/000/140/124/DE42818E-818F-DF11-8C7B-001617E30D0A.root'
#,'/store/data/Run2010A/EG/RECO/v4/000/140/158/9CFF8901-FE8F-DF11-9822-001D09F24664.root'
##    'file:/scratch/Summer2009/bJet_RAW2DIGI_RECOSIM_n5e314.root'
 )
)
#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange(
#        '139020:426  -139020:426'
#        ,'139096:214 -139096:214'
#        ,'139407:1060-139407:1060'
#        ,'140059:755 -140059:755'
#        ,'140124:16  - 140124:16'
#        ,'140124:1251-140124:1251'
#        ,'140124:1606-140124:1606'
#        ,'140158:263 -140158:263 '
#        )


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

## Load additional processes
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
## global tags:
process.GlobalTag.globaltag = cms.string('GR_R_35X_V8B::All')
#process.GlobalTag.globaltag = cms.string('START3X_V26A::All')
process.load("Configuration.StandardSequences.MagneticField_cff")


################################################################################################
###    P r e p a r a t i o n      o f    t h e    P A T    O b j e c t s   f r o m    A O D  ###
################################################################################################

## pat sequences to be loaded:
#process.load("PhysicsTools.PFCandProducer.PF2PAT_cff")
process.load("PhysicsTools.PatAlgos.patSequences_cff")
#process.load("PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff")
##
## %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
## modify the final pat sequence: keep only electrons + METS (muons are needed for met corrections)
process.load("RecoEgamma.EgammaIsolationAlgos.egammaIsolationSequence_cff")
#process.patElectronIsolation = cms.Sequence(process.egammaIsolationSequence)
#
process.patElectrons.isoDeposits = cms.PSet()
process.patElectrons.userIsolation = cms.PSet(
#       tracker = cms.PSet(
#            src = cms.InputTag("electronTrackIsolationScone"),
#        ),
#        ecal = cms.PSet(
#            src = cms.InputTag("electronEcalRecHitIsolationLcone"),
#        ),
#        hcal = cms.PSet(
#            src = cms.InputTag("electronHcalTowerIsolationLcone"),
#        ),
#        user = cms.VPSet(),
    )

##
## Pre-calculated electron identification selections
##
## set the variable false if you don't need them, or if you use your own PSet
##
## any input tag you set corresponds to a valuemap that either it is stored in the event
## or you create it yourself
process.patElectrons.addElectronID = cms.bool(True)
process.patElectrons.electronIDSources = cms.PSet(
    simpleEleId95relIso= cms.InputTag("simpleEleId95relIso"),
    simpleEleId90relIso= cms.InputTag("simpleEleId90relIso"),
    simpleEleId85relIso= cms.InputTag("simpleEleId85relIso"),
    simpleEleId80relIso= cms.InputTag("simpleEleId80relIso"),
    simpleEleId70relIso= cms.InputTag("simpleEleId70relIso"),
    simpleEleId60relIso= cms.InputTag("simpleEleId60relIso"),
    simpleEleId95cIso= cms.InputTag("simpleEleId95cIso"),
    simpleEleId90cIso= cms.InputTag("simpleEleId90cIso"),
    simpleEleId85cIso= cms.InputTag("simpleEleId85cIso"),
    simpleEleId80cIso= cms.InputTag("simpleEleId80cIso"),
    simpleEleId70cIso= cms.InputTag("simpleEleId70cIso"),
    simpleEleId60cIso= cms.InputTag("simpleEleId60cIso"),    
    )
##
process.patElectrons.addGenMatch = cms.bool(False)
process.patElectrons.embedGenMatch = cms.bool(False)
process.patElectrons.embedTrack = cms.bool(True)
##
#process.load("ZEE.simpleEleIdSequence_cff")
simpleCutBasedElectronID = cms.EDProducer("EleIdCutBasedExtProducer",

#   import here your collections
    src = cms.InputTag("gsfElectrons"),
    #reducedBarrelRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
    #reducedEndcapRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
    # Spring10 uses these names:
    reducedBarrelRecHitCollection = cms.InputTag("reducedEcalRecHitsEB"),
    reducedEndcapRecHitCollection = cms.InputTag("reducedEcalRecHitsEE"),
    # if you want the vertices or the offline beam spot
    verticesCollection = cms.InputTag("offlineBeamSpot"),
    dataMagneticFieldSetUp = cms.bool(False),
    dcsTag = cms.InputTag("scalersRawToDigi"),                                          
    algorithm = cms.string('eIDCB'),

    #electronIDType: robust  for the simple Cut-Based
    #electronQuality: see later
    #electronVersion: use V03 with the offline beam spot
    electronIDType  = cms.string('robust'),
    electronQuality = cms.string('test'),
    electronVersion = cms.string('V04'),

####
#### Selections with Relative Isolation                                          
    robust95relIsoEleIDCutsV04 = cms.PSet(
           barrel =  cms.vdouble(5.0e-01, 1.0e-02, 8.0e-01, 7.0e-03, -1, -1, 9999., 9999., 9999., 9999., 9999., 1.5e-01, 
                                 2.0e+00, 1.2e-01, 9999., 9999., 9999., 9999., 0.0, -9999., 9999., 9999., 1, -1, 0.0, 0.0, ),
           endcap =  cms.vdouble(7.0e-02, 3.0e-02, 7.0e-01, 9999., -1, -1, 9999., 9999., 9999., 9999., 9999., 8.0e-02, 
                                 6.0e-02, 5.0e-02, 9999., 9999., 9999., 9999., 0.0, -9999., 9999., 9999., 1, -1, 0.0, 0.0, ),
#           endcap =  cms.vdouble(7.0e-02, 3.0e-02, 7.0e-01, 1.0e-02, -1, -1, 9999., 9999., 9999., 9999., 9999., 8.0e-02, 
#                                 6.0e-02, 5.0e-02, 9999., 9999., 9999., 9999., 0.0, -9999., 9999., 9999., 1, -1, 0.0, 0.0, ),
    ),
    robust90relIsoEleIDCutsV04 = cms.PSet(
           barrel =  cms.vdouble(1.2e-01, 1.0e-02, 8.0e-01, 7.0e-03, -1, -1, 9999., 9999., 9999., 9999., 9999., 1.2e-01, 
                                 9.0e-02, 1.0e-01, 9999., 9999., 9999., 9999., 0.0, -9999., 9999., 9999., 1, -1, 0.02, 0.02, ),
           endcap =  cms.vdouble(5.0e-02, 3.0e-02, 7.0e-01, 9999., -1, -1, 9999., 9999., 9999., 9999., 9999., 5.0e-02, 
                                 6.0e-02, 3.0e-02, 9999., 9999., 9999., 9999., 0.0, -9999., 9999., 9999., 1, -1, 0.02, 0.02, ),      
#           endcap =  cms.vdouble(5.0e-02, 3.0e-02, 7.0e-01, 9.0e-03, -1, -1, 9999., 9999., 9999., 9999., 9999., 5.0e-02, 
#                                 6.0e-02, 3.0e-02, 9999., 9999., 9999., 9999., 0.0, -9999., 9999., 9999., 1, -1, 0.02, 0.02, ),
    ),
    robust85relIsoEleIDCutsV04 = cms.PSet(
           barrel =  cms.vdouble(4.0e-02, 1.0e-02, 6.0e-02, 6.0e-03, -1, -1, 9999., 9999., 9999., 9999., 9999., 9.0e-02, 
                                 8.0e-02, 1.0e-01, 9999., 9999., 9999., 9999., 0.0, -9999., 9999., 9999., 1, -1, 0.02, 0.02, ),
           endcap =  cms.vdouble(2.5e-02, 3.0e-02, 4.0e-02, 9999., -1, -1, 9999., 9999., 9999., 9999., 9999., 5.0e-02, 
                                 5.0e-02, 2.5e-02, 9999., 9999., 9999., 9999., 0.0, -9999., 9999., 9999., 1, -1, 0.02, 0.02, ),
#           endcap =  cms.vdouble(2.5e-02, 3.0e-02, 4.0e-02, 7.0e-03, -1, -1, 9999., 9999., 9999., 9999., 9999., 5.0e-02, 
#                                 5.0e-02, 2.5e-02, 9999., 9999., 9999., 9999., 0.0, -9999., 9999., 9999., 1, -1, 0.02, 0.02, ),
    ),
    robust80relIsoEleIDCutsV04 = cms.PSet(
           barrel =  cms.vdouble(4.0e-02, 1.0e-02, 6.0e-02, 4.0e-03, -1, -1, 9999., 9999., 9999., 9999., 9999., 9.0e-02, 
                                 7.0e-02, 1.0e-01, 9999., 9999., 9999., 9999., 0.0, -9999., 9999., 9999., 0, -1, 0.02, 0.02, ),
           endcap =  cms.vdouble(2.5e-02, 3.0e-02, 3.0e-02, 9999., -1, -1, 9999., 9999., 9999., 9999., 9999., 4.0e-02, 
                                 5.0e-02, 2.5e-02, 9999., 9999., 9999., 9999., 0.0, -9999., 9999., 9999., 0, -1, 0.02, 0.02, ),      
#           endcap =  cms.vdouble(2.5e-02, 3.0e-02, 3.0e-02, 7.0e-03, -1, -1, 9999., 9999., 9999., 9999., 9999., 4.0e-02, 
#                                 5.0e-02, 2.5e-02, 9999., 9999., 9999., 9999., 0.0, -9999., 9999., 9999., 0, -1, 0.02, 0.02, ),
    ),
    # 70% point modified with restricting cuts to physical values                                                                   
    robust70relIsoEleIDCutsV04 = cms.PSet(
           barrel =  cms.vdouble(2.5e-02, 1.0e-02, 3.0e-02, 4.0e-03, -1, -1, 9999., 9999., 9999., 9999., 9999., 5.0e-02, 
                                 6.0e-02, 3.0e-02, 9999., 9999., 9999., 9999., 0.0, -9999., 9999., 9999., 0, -1, 0.02, 0.02, ),
           endcap =  cms.vdouble(2.5e-02, 3.0e-02, 2.0e-02, 9999., -1, -1, 9999., 9999., 9999., 9999., 9999., 2.5e-02, 
                                 2.5e-02, 2.0e-02, 9999., 9999., 9999., 9999., 0.0, -9999., 9999., 9999., 0, -1, 0.02, 0.02, ),
#           endcap =  cms.vdouble(2.5e-02, 3.0e-02, 2.0e-02, 5.0e-03, -1, -1, 9999., 9999., 9999., 9999., 9999., 2.5e-02, 
#                                 2.5e-02, 2.0e-02, 9999., 9999., 9999., 9999., 0.0, -9999., 9999., 9999., 0, -1, 0.02, 0.02, ),
    ),
    # 60% point modified with restricting cuts to physical values                      
    robust60relIsoEleIDCutsV04 = cms.PSet(
           barrel =  cms.vdouble(2.5e-02, 1.0e-02, 2.5e-02, 4.0e-03, -1, -1, 9999., 9999., 9999., 9999., 9999., 4.0e-02, 
                                 4.0e-02, 3.0e-02, 9999., 9999., 9999., 9999., 0.0, -9999., 9999., 9999., 0, -1, 0.02, 0.02, ),
           endcap =  cms.vdouble(2.5e-02, 3.0e-02, 2.0e-02, 9999., -1, -1, 9999., 9999., 9999., 9999., 9999., 2.5e-02, 
                                 2.0e-02, 2.0e-02, 9999., 9999., 9999., 9999., 0.0, -9999., 9999., 9999., 0, -1, 0.02, 0.02, ),      
#           endcap =  cms.vdouble(2.5e-02, 3.0e-02, 2.0e-02, 5.0e-03, -1, -1, 9999., 9999., 9999., 9999., 9999., 2.5e-02, 
#                                 2.0e-02, 2.0e-02, 9999., 9999., 9999., 9999., 0.0, -9999., 9999., 9999., 0, -1, 0.02, 0.02, ),
    ),

####
#### Selections with Combined Isolation

    robust95cIsoEleIDCutsV04 = cms.PSet(
           barrel =  cms.vdouble(5.0e-01, 1.0e-02, 8.0e-01, 7.0e-03, -1, -1, 9999., 9999., 9999., 9999., 9999., 9999., 
                                 9999., 9999., 9999., 9999., 9999., 1.5e-01, 0.0, -9999., 9999., 9999., 1, -1, 0.0, 0.0, ),
           endcap =  cms.vdouble(7.0e-02, 3.0e-02, 7.0e-01, 9999., -1, -1, 9999., 9999., 9999., 9999., 9999., 9999., 
                                 9999., 9999., 9999., 9999., 9999., 1.0e-01, 0.0, -9999., 9999., 9999., 1, -1, 0.0, 0.0, ),           
#           endcap =  cms.vdouble(7.0e-02, 3.0e-02, 7.0e-01, 1.0e-02, -1, -1, 9999., 9999., 9999., 9999., 9999., 9999., 
#                                 9999., 9999., 9999., 9999., 9999., 1.0e-01, 0.0, -9999., 9999., 9999., 1, -1, 0.0, 0.0, ),
    ),
    robust90cIsoEleIDCutsV04 = cms.PSet(
           barrel =  cms.vdouble(1.2e-01, 1.0e-02, 8.0e-01, 7.0e-03, -1, -1, 9999., 9999., 9999., 9999., 9999., 9999., 
                                 9999., 9999., 9999., 9999., 9999., 1.0e-01, 0.0, -9999., 9999., 9999., 1, -1, 0.02, 0.02, ),
           endcap =  cms.vdouble(5.0e-02, 3.0e-02, 7.0e-01, 9999., -1, -1, 9999., 9999., 9999., 9999., 9999., 9999., 
                                 9999., 9999., 9999., 9999., 9999., 7.0e-02, 0.0, -9999., 9999., 9999., 1, -1, 0.02, 0.02, ),        
#           endcap =  cms.vdouble(5.0e-02, 3.0e-02, 7.0e-01, 9.0e-03, -1, -1, 9999., 9999., 9999., 9999., 9999., 9999., 
#                                 9999., 9999., 9999., 9999., 9999., 7.0e-02, 0.0, -9999., 9999., 9999., 1, -1, 0.02, 0.02, ),
    ),
    robust85cIsoEleIDCutsV04 = cms.PSet(
           barrel =  cms.vdouble(4.0e-02, 1.0e-02, 6.0e-02, 6.0e-03, -1, -1, 9999., 9999., 9999., 9999., 9999., 9999., 
                                 9999., 9999., 9999., 9999., 9999., 9.0e-02, 0.0, -9999., 9999., 9999., 1, -1, 0.02, 0.02, ),
           endcap =  cms.vdouble(2.5e-02, 3.0e-02, 4.0e-02, 9999., -1, -1, 9999., 9999., 9999., 9999., 9999., 9999., 
                                 9999., 9999., 9999., 9999., 9999., 6.0e-02, 0.0, -9999., 9999., 9999., 1, -1, 0.02, 0.02, ),
#           endcap =  cms.vdouble(2.5e-02, 3.0e-02, 4.0e-02, 7.0e-03, -1, -1, 9999., 9999., 9999., 9999., 9999., 9999., 
#                                 9999., 9999., 9999., 9999., 9999., 6.0e-02, 0.0, -9999., 9999., 9999., 1, -1, 0.02, 0.02, ),
    ),
    robust80cIsoEleIDCutsV04 = cms.PSet(
           barrel =  cms.vdouble(4.0e-02, 1.0e-02, 6.0e-02, 4.0e-03, -1, -1, 9999., 9999., 9999., 9999., 9999., 9999., 
                                 9999., 9999., 9999., 9999., 9999., 7.0e-02, 0.0, -9999., 9999., 9999., 0, -1, 0.02, 0.02, ),
           endcap =  cms.vdouble(2.5e-02, 3.0e-02, 3.0e-02, 9999., -1, -1, 9999., 9999., 9999., 9999., 9999., 9999., 
                                 9999., 9999., 9999., 9999., 9999., 6.0e-02, 0.0, -9999., 9999., 9999., 0, -1, 0.02, 0.02, ),        
#           endcap =  cms.vdouble(2.5e-02, 3.0e-02, 3.0e-02, 7.0e-03, -1, -1, 9999., 9999., 9999., 9999., 9999., 9999., 
#                                 9999., 9999., 9999., 9999., 9999., 6.0e-02, 0.0, -9999., 9999., 9999., 0, -1, 0.02, 0.02, ),
    ),
    # 70% point modified with restricting cuts to physical values                                          
    robust70cIsoEleIDCutsV04 = cms.PSet(
           barrel =  cms.vdouble(2.5e-02, 1.0e-02, 3.0e-02, 4.0e-03, -1, -1, 9999., 9999., 9999., 9999., 9999., 9999., 
                                 9999., 9999., 9999., 9999., 9999., 4.0e-02, 0.0, -9999., 9999., 9999., 0, -1, 0.02, 0.02, ),
           endcap =  cms.vdouble(2.5e-02, 3.0e-02, 2.0e-02, 9999., -1, -1, 9999., 9999., 9999., 9999., 9999., 9999., 
                                 9999., 9999., 9999., 9999., 9999., 3.0e-02, 0.0, -9999., 9999., 9999., 0, -1, 0.02, 0.02, ),
#           endcap =  cms.vdouble(2.5e-02, 3.0e-02, 2.0e-02, 5.0e-03, -1, -1, 9999., 9999., 9999., 9999., 9999., 9999., 
#                                 9999., 9999., 9999., 9999., 9999., 3.0e-02, 0.0, -9999., 9999., 9999., 0, -1, 0.02, 0.02, ),
    ),
    # 60% point modified with restricting cuts to physical values
    robust60cIsoEleIDCutsV04 = cms.PSet(
           barrel =  cms.vdouble(2.5e-02, 1.0e-02, 2.5e-02, 4.0e-03, -1, -1, 9999., 9999., 9999., 9999., 9999., 9999., 
                                 9999., 9999., 9999., 9999., 9999., 3.0e-02, 0.0, -9999., 9999., 9999., 0, -1, 0.02, 0.02, ),
           endcap =  cms.vdouble(2.5e-02, 3.0e-02, 2.0e-02, 9999., -1, -1, 9999., 9999., 9999., 9999., 9999., 9999., 
                                 9999., 9999., 9999., 9999., 9999., 2.0e-02, 0.0, -9999., 9999., 9999., 0, -1, 0.02, 0.02, ),
#           endcap =  cms.vdouble(2.5e-02, 3.0e-02, 2.0e-02, 5.0e-03, -1, -1, 9999., 9999., 9999., 9999., 9999., 9999., 
#                                 9999., 9999., 9999., 9999., 9999., 2.0e-02, 0.0, -9999., 9999., 9999., 0, -1, 0.02, 0.02, ),
    ),

)

process.simpleEleId95relIso = simpleCutBasedElectronID.clone()
process.simpleEleId95relIso.electronQuality = '95relIso'

process.simpleEleId90relIso = simpleCutBasedElectronID.clone()
process.simpleEleId90relIso.electronQuality = '90relIso'

process.simpleEleId85relIso = simpleCutBasedElectronID.clone()
process.simpleEleId85relIso.electronQuality = '85relIso'

process.simpleEleId80relIso = simpleCutBasedElectronID.clone()
process.simpleEleId80relIso.electronQuality = '80relIso'

process.simpleEleId70relIso = simpleCutBasedElectronID.clone()
process.simpleEleId70relIso.electronQuality = '70relIso'

process.simpleEleId60relIso = simpleCutBasedElectronID.clone()
process.simpleEleId60relIso.electronQuality = '60relIso'


process.simpleEleId95cIso = simpleCutBasedElectronID.clone()
process.simpleEleId95cIso.electronQuality = '95cIso'

process.simpleEleId90cIso = simpleCutBasedElectronID.clone()
process.simpleEleId90cIso.electronQuality = '90cIso'

process.simpleEleId85cIso = simpleCutBasedElectronID.clone()
process.simpleEleId85cIso.electronQuality = '85cIso'

process.simpleEleId80cIso = simpleCutBasedElectronID.clone()
process.simpleEleId80cIso.electronQuality = '80cIso'

process.simpleEleId70cIso = simpleCutBasedElectronID.clone()
process.simpleEleId70cIso.electronQuality = '70cIso'

process.simpleEleId60cIso = simpleCutBasedElectronID.clone()
process.simpleEleId60cIso.electronQuality = '60cIso'



process.simpleEleIdSequence = cms.Sequence(process.simpleEleId95relIso+
                                   process.simpleEleId90relIso+
                                   process.simpleEleId85relIso+
                                   process.simpleEleId80relIso+
                                   process.simpleEleId70relIso+
                                   process.simpleEleId60relIso+
                                   process.simpleEleId95cIso+
                                   process.simpleEleId90cIso+
                                   process.simpleEleId85cIso+
                                   process.simpleEleId80cIso+
                                   process.simpleEleId70cIso+
                                   process.simpleEleId60cIso
                                   )

process.patElectronIDs = cms.Sequence(process.simpleEleIdSequence)
process.makePatElectrons = cms.Sequence(process.patElectronIDs*process.patElectrons)
#process.makePatElectrons = cms.Sequence(process.patElectrons)
process.patDefaultSequence = cms.Sequence(process.makePatElectrons)
##  ################################################################################
##
##  the filter to select the candidates from the data samples
##
## WARNING: you may want to modify this item:  T R I G G E R     S E L E C T I O N
HLT_process_name = "HLT"   # 
# trigger path selection and  trigger filter name
HLT_path_name          = "HLT_Photon10_L1R" 
HLT_filter_name        = "hltL1NonIsoHLTNonIsoSinglePhotonEt10HcalIsolFilter"
HLT_path_name_extra0   = "HLT_Photon15_L1R"
HLT_filter_name_extra0 = cms.untracked.InputTag("hltL1NonIsoHLTNonIsoSinglePhotonEt15HcalIsolFilter","",HLT_process_name)
HLT_path_name_extra1   = "HLT_Photon15_Cleaned_L1R"
HLT_filter_name_extra1 = cms.untracked.InputTag("hltL1NonIsoHLTNonIsoSinglePhotonEt15CleanedHcalIsolFilter","",HLT_process_name)
HLT_path_name_extra2   = "HLT_Photon20_Cleaned_L1R"
HLT_filter_name_extra2 = cms.untracked.InputTag("hltL1NonIsoHLTNonIsoSinglePhotonEt20CleanedHcalIsolFilter","",HLT_process_name)
HLT_path_name_extra3   = "HLT_Ele15_SW_CaloEleId_L1R"
HLT_filter_name_extra3 = cms.untracked.InputTag("hltL1NonIsoHLTNonIsoSingleElectronEt15CaloEleIdPixelMatchFilter","",HLT_process_name)
#HLT_path_name_extra3   = "HLT_Photon15_Cleaned_L1R"
#HLT_filter_name_extra3 = cms.untracked.InputTag("hltL1NonIsoHLTNonIsoSinglePhotonEt15CleanedHcalIsolFilter","",HLT_process_name)
#HLT_path_name_extra4   = "HLT_Photon15_L1R"
#HLT_filter_name_extra4 = cms.untracked.InputTag("hltL1NonIsoHLTNonIsoSinglePhotonEt15HcalIsolFilter","",HLT_process_name)
#HLT_path_name_extra5   = "HLT_Photon15_Cleaned_L1R"
#HLT_filter_name_extra5 = cms.untracked.InputTag("hltL1NonIsoHLTNonIsoSinglePhotonEt15CleanedHcalIsolFilter","",HLT_process_name)

#
process.zeeFilter = cms.EDFilter('ZeeCandidateFilter',
                                  ### the input collections needed:
                                  electronCollectionTag = cms.untracked.InputTag("patElectrons","","PAT"),
                                  triggerCollectionTag = cms.untracked.InputTag("TriggerResults","",HLT_process_name),
                                  triggerEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","",HLT_process_name),
                                  hltpath = cms.untracked.string(HLT_path_name), 
                                  hltpathFilter = cms.untracked.InputTag(HLT_filter_name,"",HLT_process_name),
                                  ebRecHits = cms.untracked.InputTag("reducedEcalRecHitsEB"),
                                  eeRecHits = cms.untracked.InputTag("reducedEcalRecHitsEE"),
                                  PrimaryVerticesCollection = cms.untracked.InputTag("offlinePrimaryVertices"),
                                  ### here the preselection is applied
                                  # fiducial cuts:
                                  BarrelMaxEta = cms.untracked.double(1.4442),
                                  EndCapMinEta = cms.untracked.double(1.566),
                                  EndCapMaxEta = cms.untracked.double(2.5),
                                  # demand ecal driven electron:
                                  
useEcalDrivenElectrons = cms.untracked.bool(True),
                                  # demand offline spike cleaning with the Swiss Cross criterion:
                                  useSpikeRejection = cms.untracked.bool(True),
                                  spikeCleaningSwissCrossCut = cms.untracked.double(0.95),
                                  # demand geometrically matched to an HLT object with ET>15GeV
                                  useTriggerInfo = cms.untracked.bool(True),
                                  electronMatched2HLT = cms.untracked.bool(True),
                                  electronMatched2HLT_DR = cms.untracked.double(0.2),
                                  useHLTObjectETCut = cms.untracked.bool(True),
                                  hltObjectETCut = cms.untracked.double(10.),
                                  useExtraTrigger = cms.untracked.bool(True),
                                  vHltpathExtra = cms.untracked.vstring(HLT_path_name_extra0,HLT_path_name_extra1,HLT_path_name_extra2,HLT_path_name_extra3),
                                  vHltpathFilterExtra = cms.untracked.VInputTag(HLT_filter_name_extra0, HLT_filter_name_extra1,HLT_filter_name_extra2, HLT_filter_name_extra3),
                                  # ET Cut in the SC
                                  ETCut = cms.untracked.double(10.),                                  
                                  # Other parameters of the code - leave them as they are
                                  useValidFirstPXBHit = cms.untracked.bool(False),
                                  useConversionRejection = cms.untracked.bool(False),
                                  useExpectedMissingHits = cms.untracked.bool(False),
                                  maxNumberOfExpectedMissingHits = cms.untracked.int32(1),
                                  # calculate some new cuts
                                  calculateValidFirstPXBHit = cms.untracked.bool(True),
                                  calculateConversionRejection = cms.untracked.bool(True),
                                  calculateExpectedMissingHits = cms.untracked.bool(True),
                                  # we are dealing with DATA
                                  dataMagneticFieldSetUp = cms.untracked.bool(True),
                                  dcsTag = cms.untracked.InputTag("scalersRawToDigi"),
                                  )

####################################################################################
##  ################################################################################
##
##  the filter to select the candidates from the data samples
##
## WARNING: you may want to modify this item:  T R I G G E R     S E L E C T I O N
# require physics declared

# require scraping filter
process.scrapingVeto = cms.EDFilter("FilterOutScraping",
                                    applyfilter = cms.untracked.bool(True),
                                    debugOn = cms.untracked.bool(False),
                                    numtrack = cms.untracked.uint32(10),
                                    thresh = cms.untracked.double(0.2)
                                    )

##############Good Vertex filter
process.primaryVertexFilter = cms.EDFilter("GoodVertexFilter",
                                           vertexCollection = cms.InputTag('offlinePrimaryVertices'),
                                           minimumNDOF = cms.uint32(4) ,
                                           maxAbsZ = cms.double(15),
                                           maxd0 = cms.double(2)
                                           )

##############################
process.zeePath = cms.Path(process.scrapingVeto*
                           process.primaryVertexFilter*
                           process.patDefaultSequence*
                           process.zeeFilter)

process.zeeOutputModule = cms.OutputModule( "PoolOutputModule",
                                             fileName = cms.untracked.string("zeeCandidates.root"),
                                             outputCommands = cms.untracked.vstring(
#                                                     'keep *'
                                                    'drop *',
                                                    'keep *_*_selectedZeeCandidates_*', 
                                                    ),
                                            SelectEvents = cms.untracked.PSet(
                                                         SelectEvents = cms.vstring('zeePath',),),

                                             )

process.outpath = cms.EndPath(process.zeeOutputModule)


