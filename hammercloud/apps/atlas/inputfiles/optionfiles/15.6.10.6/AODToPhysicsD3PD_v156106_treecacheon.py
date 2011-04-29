# $Id$
#
# @file D3PDMakerConfig/share/AODToPhysicsD3PD.py
# @author scott snyder <snyder@bnl.gov>
# @date Aug, 2009
# @brief Example for building a physics D3PD from an AOD.
#

print "Setting Max size to 10GB..."
from ROOT import TTree;TTree.SetMaxTreeSize(10000000000)

####################################################################
# Define the input file here.
#

from AthenaCommon.AthenaCommonFlags import athenaCommonFlags
import glob
fileList = glob.glob('/tmp/elmsheus/data09_900GeV.00140541.physics_MinBias.merge.AOD.r1093_p101_tid118749_00/*')
athenaCommonFlags.FilesInput= fileList


####################################################################
# Define the output file here.
#

if not globals().get('tupleFileOutput'):
    tupleFileOutput = 'physics.root'


####################################################################
# Define other job options here.
#

athenaCommonFlags.EvtMax = -1

# Example of changing D3PD maker flags.
from D3PDMakerConfig.D3PDMakerFlags import D3PDMakerFlags
#D3PDMakerFlags.DoTrigger = False


####################################################################
# Configure RecExCommon.
#

from RecExConfig.RecFlags import rec
rec.doCBNT.set_Value_and_Lock(False)
rec.doWriteESD.set_Value_and_Lock(False)
rec.doWriteAOD.set_Value_and_Lock(False)
rec.doAOD.set_Value_and_Lock(False)
rec.doESD.set_Value_and_Lock(False)
rec.doDPD.set_Value_and_Lock(False)
rec.doWriteTAG.set_Value_and_Lock(False)
rec.doForwardDet.set_Value_and_Lock(False)
include ("RecExCommon/RecExCommon_topOptions.py")


####################################################################
# Make the D3PD.
#

from D3PDMakerConfig.physicsD3PD import physicsD3PD
alg = physicsD3PD (tupleFileOutput)


# Log monitoring
from AthenaCommon.AppMgr import ServiceMgr
ServiceMgr.MessageSvc.OutputLevel = INFO
ServiceMgr.MessageSvc.infoLimit = 0

###################################################################3
# RDs treecache stuff

# Turn on the tree cache for the CollectionTree - tree cache only
# works for one tree. And set tree cache size - default is 10 MB (10 000 000)
#svcMgr.AthenaPoolCnvSvc.InputPoolAttributes += [ "ContainerName = 'CollectionTree'; TREE_CACHE = '100000'" ]
ServiceMgr.AthenaPoolCnvSvc.InputPoolAttributes += [ "ContainerName = 'CollectionTree'; TREE_CACHE = '10000000'" ]
# Set number of events for learning before turning on cache - default is 5
ServiceMgr.AthenaPoolCnvSvc.InputPoolAttributes += [ "TREE_CACHE_LEARN_EVENTS = '6'" ]
# Print out values - must have PoolSvc in info mode
ServiceMgr.PoolSvc.OutputLevel = INFO
ServiceMgr.AthenaPoolCnvSvc.InputPoolAttributes += [ "TREE_CACHE_LEARN_EVENTS = 'int'" ]
ServiceMgr.AthenaPoolCnvSvc.InputPoolAttributes += [ "TREE_CACHE_SIZE = 'int'" ]

# Print out for each event the number of bytes read and the number of
# read calls. With the tree cache, one should see jumps in the bytes
# read by the cache size, i.e. the bytes read should not change each
# event. However, the cache only works on one tree - the main event
# tree (CollectionTree) - and we read some things from other trees, so
# one does see a small increase event-by-event.
ServiceMgr.PoolSvc.OutputLevel = INFO
#ServiceMgr.AthenaPoolCnvSvc.PrintInputAttrPerEvt += [ "BYTES_READ = 'double'" ]
#ServiceMgr.AthenaPoolCnvSvc.PrintInputAttrPerEvt += [ "READ_CALLS = 'int'" ]


###################################################################
# Switch on Perfmon
#
from PerfMonComps.PerfMonFlags import jobproperties
jobproperties.PerfMonFlags.doMonitoring = True
