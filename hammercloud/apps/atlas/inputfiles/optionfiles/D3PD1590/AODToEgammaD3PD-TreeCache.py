# $Id$
#
# @file D3PDMakerConfig/share/AODToEgammaD3PD.py
# @author scott snyder <snyder@bnl.gov>
# @date Aug, 2009
# @brief Example for building an egamma D3PD from an AOD.
#


###################################################################3
# Define the input file here.
#

from AthenaCommon.AthenaCommonFlags import athenaCommonFlags
athenaCommonFlags.FilesInput= ["/afs/cern.ch/user/d/dvanders/public/AOD.pool.root"]

###################################################################3
# Define the output file here.
#

if not globals().get('tupleFileOutput'):
    tupleFileOutput = 'egamma.root'


###################################################################3
# Define other job options here.
#

athenaCommonFlags.EvtMax = -1

# Example of changing D3PD maker flags.
from D3PDMakerConfig.D3PDMakerFlags import D3PDMakerFlags
#D3PDMakerFlags.DoTrigger = False


###################################################################3
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


###################################################################3
# Make the D3PD.
#

from D3PDMakerConfig.egammaD3PD import egammaD3PD
alg = egammaD3PD (tupleFileOutput)

### Turn on the tree cache for the CollectionTree - tree cache only
### works for one tree. And set tree cache size - default is 10 MB (10 000 000)
###svcMgr.AthenaPoolCnvSvc.InputPoolAttributes += [ "ContainerName = 'CollectionTree'; TREE_CACHE = '100000'" ]
svcMgr.AthenaPoolCnvSvc.InputPoolAttributes += [ "ContainerName = 'CollectionTree'; TREE_CACHE = '10000000'" ]
### Set number of events for learning before turning on cache - default is 5
svcMgr.AthenaPoolCnvSvc.InputPoolAttributes += [ "TREE_CACHE_LEARN_EVENTS = '6'" ]
##
### Print out values - must have PoolSvc in info mode
svcMgr.PoolSvc.OutputLevel = INFO
svcMgr.AthenaPoolCnvSvc.InputPoolAttributes += [ "TREE_CACHE_LEARN_EVENTS = 'int'" ]
svcMgr.AthenaPoolCnvSvc.InputPoolAttributes += [ "TREE_CACHE_SIZE = 'int'" ]
##
### Print out for each event the number of bytes read and the number of
### read calls. With the tree cache, one should see jumps in the bytes
### read by the cache size, i.e. the bytes read should not change each
### event. However, the cache only works on one tree - the main event
### tree (CollectionTree) - and we read some things from other trees, so
### one does see a small increase event-by-event.
svcMgr.PoolSvc.OutputLevel = INFO
svcMgr.AthenaPoolCnvSvc.PrintInputAttrPerEvt += [ "BYTES_READ = 'double'" ]
svcMgr.AthenaPoolCnvSvc.PrintInputAttrPerEvt += [ "READ_CALLS = 'int'" ]

