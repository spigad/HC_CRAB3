# This is the job options that does AOD based skimming and thinning
###############################################################
#
# Job options file
#
# Authors: Davide Costanzo, Stathes Paganis, Sven Menke
# Anastopoulos Christos 
#==============================================================
#--------------------------------------------------------------
# Load POOL support
#--------------------------------------------------------------
import AthenaPoolCnvSvc.ReadAthenaPool
from AthenaCommon.AppMgr import ServiceMgr as svcMgr

from AthenaCommon.AlgSequence import AlgSequence
topSequence = AlgSequence()

###############################
# Load thinning service
###############################

from AthenaServices.Configurables import ThinningSvc
svcMgr += ThinningSvc()
# the output stream(s) to apply thinning on
svcMgr.ThinningSvc.Streams += ['StreamDPD']

#Needed for some tracks (some tracks may have elements which need the
# detector description)
#DetDescrVersion = 'ATLAS-CSC-05-01-00'
#include("RecExCond/AllDet_detDescr.py")
#--------------------------------------------------------------
# Event related parameters
#--------------------------------------------------------------
theApp.EvtMax = -1

#
#--------------------------------------------------------------
# Set output level threshold (2=DEBUG, 3=INFO, 4=WARNING, 5=ERROR, 6=FATAL )
#--------------------------------------------------------------
MessageSvc = Service( "MessageSvc" )
#MessageSvc.OutputLevel = 3
#svcMgr.EventSelector.InputCollections =[ "/afs/cern.ch/atlas/groups/PAT/Tutorial/AtlasOffline-14.2.10/AODs/valid1.005200.T1_McAtNlo_Jimmy.recon.AOD.e322_s435_r432_tid022496/AOD.022496._00001.pool.root.1"]#
svcMgr.EventSelector.InputCollections =[ "/afs/cern.ch/atlas/groups/PAT/Tutorial/AtlasOffline-14.2.20/Data/valid3.005200.T1_McAtNlo_Jimmy.recon.AOD.e322_s412_r520_tid024596/AOD.024596._00001.pool.root.1"]
svcMgr.EventSelector.InputCollections =[ "mc08.109625.AlpgenJimmyttbarbbbarlnqqNp0.recon.AOD.e437_a84_tid076117/AOD.076117._000008.pool.root.1"]
svcMgr.EventSelector.InputCollections =[ "mc08.105205.AcerMCttbar.merge.TAG.e429_s462_r635_t53_tid075832/TAG.075832._000003.pool.root.1"]

#svcMgr.EventSelector.InputCollections =inFileName


#To create some jets on the fly on the AOD use the next lines. One jet collection is done
#from the local hadron calibrated topo clusters LCTopo, the other from the stable Monte
#Carlo truth particles Truth. Both jet collections are of the Kt type with an R parameter of 0.4:

from JetRec.JetRecFlags import jetFlags
jetFlags.inputFileType = "AOD" #

from JetRec.JetGetters import *  

Kt4alg = make_StandardJetGetter('Kt', 0.4, 'LCTopo').jetAlgorithmHandle()
Kt4alg.OutputLevel = 3

#Kt4talg = make_StandardJetGetter('Kt', 0.4, 'Truth').jetAlgorithmHandle()
#Kt4talg.OutputLevel = 3

include( "PyAnalysisCore/InitPyAnalysisCore.py")
include( "DPDUtils/ThinningSvcWrapper_jobOptions.py" )

include( "DPDUtils/semilep_ttbarFilterAlgorithm.py" )

filAlg=ttbarFilterAlgorithm("ttbarFilter")
# to change properties of the filter instantiate it like this:
# filAlg=ttbarFilterAlgorithm("ttbarFilter",JetMinEt=40*GeV)
topSequence  += ConfigurablePyAlgorithm("ttbarFilter")

#==============================================================
#
# End of job options file
#
###############################################################
#--------------------------------------------------------------
#---   Secondary Write portion  ----- Don't change it !!!
#--------------------------------------------------------------
from AthenaPoolCnvSvc.WriteAthenaPool import AthenaPoolOutputStream
StreamDPD = AthenaPoolOutputStream("StreamDPD")
StreamDPD.ItemList =  ['EventInfo#*', 'TrackRecordCollection#*']
StreamDPD.ItemList += ['ElectronContainer#ElectronAODCollection']
StreamDPD.ItemList += ['egDetailContainer#egDetailAOD']
StreamDPD.ItemList += ['MissingET#MET_RefFinal']
StreamDPD.ItemList += ['MissingET#MET_LocHadObj']
StreamDPD.ItemList += ['CaloClusterContainer#CaloCalTopoCluster']
StreamDPD.ItemList += ['Analysis::MuonContainer#StacoMuonCollection']
StreamDPD.ItemList += ['JetCollection#Kt4LCTopoJets']
StreamDPD.ItemList += ['JetKeyDescriptor#JetKeyMap']
StreamDPD.ItemList += ['JetCollection#Kt4TruthJets']
StreamDPD.ItemList += ['Rec::TrackParticleContainer#TrackParticleCandidate']
StreamDPD.ItemList += ['Rec::TrackParticleContainer#StacoTrackParticles']
StreamDPD.ItemList += ['TruthParticleContainer#SpclMC']
StreamDPD.ItemList += ['McEventCollection#GEN_AOD']

StreamDPD.OutputFile = "SkimmedThin.AOD.pool.root"
#StreamDPD.OutputFile = outFileName
StreamDPD.ForceRead=TRUE;  #force read of output data objs
StreamDPD.AcceptAlgs=["ttbarFilter"]


ChronoStatSvc = Service( "ChronoStatSvc" )
ChronoStatSvc.ChronoDestinationCout = True

ChronoStatSvc.PrintUserTime     = True
ChronoStatSvc.PrintSystemTime   = True
ChronoStatSvc.PrintEllapsedTime = True
AthenaPoolCnvSvc = Service( "AthenaPoolCnvSvc" )
AthenaPoolCnvSvc.UseDetailChronoStat = True

MessageSvc = Service("MessageSvc")
#MessageSvc.OutputLevel = DEBUG
#MessageSvc.OutputLevel = ERROR

#EventSelector.InputCollections = [ /afs/cern.ch/atlas/maxidisk/d39/tutorial/tag/streamtest.004881.inclEle.merge.TAG.v12000605_tid009349._00001.pool" ]
svcMgr.EventSelector.CollectionType="ExplicitROOT"
svcMgr.EventSelector.Query = ""
