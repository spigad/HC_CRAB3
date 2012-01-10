# $Id$
#
# @file D3PDMakerConfig/share/AODToEgammaD3PD.py
# @author scott snyder <snyder@bnl.gov>
# @date Aug, 2009
# @brief Minimal stand-alone example for building a physics D3PD from an AOD.
#

import glob 
fileList = glob.glob('/data/etp/ebke/Data/data09_900GeV.00141811.physics_MuonswBeam.merge.DESD_COLLCAND.f187_m305/*')

# Input and output files.
if not globals().get('poolFileInput'):
    #poolFileInput = "AOD.pool.root"
    poolFileInput = fileList
if not globals().get('tupleFileOutput'):
    tupleFileOutput = 'physics.root'

#theApp.EvtMax = 10

# Turn this on to enable the detector description.
# Without this, some event information that depends on the geometry
# will not be available.  On the other hand, Athena will initialize
# much faster.
if not globals().has_key('use_dd'):
    use_dd = False


if use_dd:
    from AthenaCommon.DetFlags      import DetFlags
    DetFlags.detdescr.all_setOn()
    import AtlasGeoModel.GeoModelInit
    svcMgr.GeoModelSvc.AutomaticGeometryVersion = True


#####################################################
# Set up reading the input file.
#

if type(poolFileInput) == type(""):
    poolFileInput = [poolFileInput]

# Disable inputFilePeeker cache.
# The cache just goes by the file name.
# So if, for example, you're reading the input file via a symlink and you
# change where the symlink points, the old cached info will still be used.
# This can be terribly confusing.
# So disable the cache for now.
import PyUtils.AthFile as af
af.server.flush_cache()
try:
    af.server.disable_pers_cache()
except AttributeError: # backward compat...
    pass

import AthenaPoolCnvSvc.ReadAthenaPool
ServiceMgr.EventSelector.InputCollections = poolFileInput
from AthenaCommon.AthenaCommonFlags import athenaCommonFlags
athenaCommonFlags.FilesInput.set_Value_and_Lock(poolFileInput)
from RecExConfig.InputFilePeeker import inputFileSummary


from RecExConfig.AutoConfiguration import ConfigureFromListOfKeys
try:
    ConfigureFromListOfKeys (['ProjectName',
                              'BeamType',
                              'RealOrSim',
                              'DoTruth',
                              'LumiFlags'])
except:
    print 'ATTENTION: ConfigureFromListOfKeys has failed !!!!!!!!!!!!!!'
    pass

# Backwards compatibility for taus.
from AthenaCommon.AlgSequence import AlgSequence
topSequence = AlgSequence()
from TauTools.TauToolsConf import TauCommonDetailsMerger
topSequence += TauCommonDetailsMerger("TauCommonDetailsMerger")


#####################################################
# Set up the D3PD maker.
#

from D3PDMakerConfig.physicsD3PD import physicsD3PD
alg = physicsD3PD (tupleFileOutput)


#####################################################
# Set up TrigConfigSvc, for AOD reading.
#
from AthenaCommon.GlobalFlags import GlobalFlags
GlobalFlags.DetGeo.set_atlas()

from RecExConfig.RecFlags import rec
rec.readRDO=False
rec.readAOD=True
rec.doWriteESD=False
rec.doWriteAOD=False
rec.doWriteTAG=False

from D3PDMakerConfig.D3PDMakerFlags import D3PDMakerFlags
if D3PDMakerFlags.DoTrigger():
    from TriggerJobOpts.TriggerFlags import TriggerFlags

    # ds seems to read config information from in-file metadata.
    # But the trigger configuration then falls over if no keys are actually
    # present in metadata.  Fallback to xml configuration in that case.
    TriggerFlags.configurationSourceList=['xml']
    for k in inputFileSummary['metadata'].keys():
        if k.startswith ('/TRIGGER/'):
            TriggerFlags.configurationSourceList=['ds']
            break
    from TriggerJobOpts.TriggerConfigGetter import TriggerConfigGetter
    cfg = TriggerConfigGetter()

# use closest DB replica
from AthenaCommon.AppMgr import ServiceMgr
from PoolSvc.PoolSvcConf import PoolSvc
ServiceMgr+=PoolSvc(SortReplicas=True)
from DBReplicaSvc.DBReplicaSvcConf import DBReplicaSvc
ServiceMgr+=DBReplicaSvc(UseCOOLSQLite=False)
                         
# Set output level threshold (2=DEBUG, 3=INFO, 4=WARNING, 5=ERROR, 6=FATAL )
ServiceMgr.MessageSvc.OutputLevel = INFO
ServiceMgr.MessageSvc.infoLimit = 0
