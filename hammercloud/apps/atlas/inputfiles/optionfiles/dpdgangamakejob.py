## job option to :
##  - read in a pool file
##  - schedule an algorithm
##    - read in some collections (jets, electrons, ...)
##    - apply some filters
##    - select interesting events
##    - create histograms
##  - write out selected and filtered events in a pool file
##  - write out histograms in a root file

#if not "outputFileName"     in dir():      outputFileName="P1.directgaugino.root"
#if not "inputList"     in dir():           inputList="mssm24.dg_p1.py"

# import some useful constants for message level
import AthenaCommon.Constants as Lvl

# for job configuration: the application manager object
# as the name implies, there is only one application manager
from AthenaCommon.AppMgr import theApp

# for job configuration: the object to hold all services
# note: the real object is 'ServiceMgr' but we give it a shorter alias 'svcMgr'
from AthenaCommon.AppMgr import ServiceMgr as svcMgr

# for job configuration: the object to hold the sequence of algorithms to
# be run in turn
from AthenaCommon.AlgSequence import AlgSequence
job = AlgSequence()

#
#--------------------------------------------------------------
# Set output level threshold (2=DEBUG, 3=INFO, 4=WARNING, 5=ERROR, 6=FATAL )
#--------------------------------------------------------------
MessageSvc = Service( "MessageSvc" )
MessageSvc.OutputLevel = 3


# configure the job to read in pool files
import AthenaPoolCnvSvc.ReadAthenaPool
# now, svcMgr has a service, EventSelector, which can be configured to run over
# a few input files
svcMgr.EventSelector.InputCollections = [
    "mc08.107682.AlpgenJimmyWenuNp2_pt20.recon.AOD.e368_s462_r563_tid029541/AOD.029541._00033.pool.root.1",
    ]

#include(inputList)

# configure the job to run over all input events
theApp.EvtMax = -1

##
# Needed for some tracks (some tracks may have elements which need the
# detector description)
DetDescrVersion = 'ATLAS-GEO-02-01-00'
include("RecExCond/AllDet_detDescr.py")
##

# schedule our analysis algorithm
from MyPyAna.SUSYAna import susyAna
job += susyAna()
job.susyAna.OutputLevel = INFO

from MyPyAna.EVFilter import EVFilter
job += EVFilter()
# Nlep greater than:
job.EVFilter.Nlep = 1

#job.EVFilter.OutputLevel = INFO

# test if a THistSvc instance was already configured
# all automatically-generated configurables can be queried under
# the 'CfgMgr' namespace
svcMgr += CfgMgr.THistSvc()

# configure the job for writing out root files
# Note we the '+=' operator and *NOT* the '=' operator
svcMgr.THistSvc.Output += [
    "%(streamname)s DATAFILE='%(filename)s' TYP='ROOT' OPT='%(mode)s'" % \
      {
        'streamname' : "myoutstream",
        'filename'   : "hist.root",
        'mode'       : "RECREATE",
      }
    ]

# configure the job for writing out pool files

import AthenaPoolCnvSvc.WriteAthenaPool

# schedule a writing algorithm
job += CfgMgr.AthenaOutputStream ("OutStream")
outStream = job.OutStream
outStream.WritingTool = "AthenaPoolOutputStreamTool"

# configure thinning svc
from AthenaServices.Configurables import ThinningSvc
svcMgr += ThinningSvc()
# the list of output streams to thin
svcMgr.ThinningSvc.Streams += ['OutStream']


# the list of items (ClassName#StoreGateKey) to be written out
outStream.ItemList = [
    "EventInfo#*",
    "TrackRecordCollection#*",
    'ElectronContainer#ElectronAODCollection',
    'egDetailContainer#egDetailAOD',
    
    'MissingET#MET_RefFinal',
    'MissingET#MET_LocHadObj',
    #'CaloClusterContainer#CaloCalTopoCluster',
    'Analysis::MuonContainer#StacoMuonCollection',
    'Analysis::MuonContainer#MuidMuonCollection',
    'Analysis::TauJetContainer#*',
    'Analysis::TauDetailsContainer#*',

##     'JetCollection#Kt4LCTopoJets',
##     'JetCollection#Kt4TruthJets',
    'JetCollection#Cone4H1TowerJets',
##     'JetKeyDescriptor#JetKeyMap',
    
    'Rec::TrackParticleContainer#TrackParticleCandidate',
    'Rec::TrackParticleContainer#StacoTrackParticles',

    # truth
    'TruthParticleContainer#SpclMC',
    #'McEventCollection#GEN_AOD',
    ]
# the name of the output file
outStream.OutputFile = "thin_1l.DPD.pool.root"
# force read of all objects in StoreGate before writting
outStream.ForceRead = True

# the name of the algorithm(s) telling OutStream if an event has successfully
# passed the cuts and can thus be written out
outStream.AcceptAlgs = [ "EVFilter" ]

## EOF ##
