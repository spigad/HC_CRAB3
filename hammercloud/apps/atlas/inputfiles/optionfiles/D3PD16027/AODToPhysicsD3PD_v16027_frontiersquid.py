# $Id$
#
# @file D3PDMakerConfig/share/AODToPhysicsD3PD.py
# @author scott snyder <snyder@bnl.gov>
# @date Aug, 2009
# @brief Example for building a physics D3PD from an AOD.
#
import os
if (not (os.getenv('FRONTIER_SERVER', 'None')=='None')):
  print 'Frontier_server defined: '+os.getenv('FRONTIER_SERVER', 'None')
  os.environ['ATLAS_CONDDB']='bla'
  os.environ['FRONTIER_LOG_LEVEL']='debug'
else:
  print 'Frontier_server not defined: '+os.getenv('FRONTIER_SERVER', 'None')

print "Setting Max size to 10GB..."
from ROOT import TTree;TTree.SetMaxTreeSize(10000000000)


####################################################################
# Define the input file here.
#

from AthenaCommon.AthenaCommonFlags import athenaCommonFlags
import glob
fileList = glob.glob('/data/etp2/elmsheus/data/data10_7TeV.00153136.physics_L1Calo.merge.AOD.r1647_p306_p307_tid198696_00/*')
athenaCommonFlags.FilesInput = fileList
#athenaCommonFlags.FilesInput= ["AOD.pool.root"]

####################################################################
# Define the output file here.
#

if not globals().get('tupleFileOutput'):
    tupleFileOutput = 'physics.root'


# Fix https://twiki.cern.ch/twiki/bin/view/AtlasProtected/D3PDMakerCurrentRecipe

from TrackD3PDMaker.TrackD3PDMakerFlags import TrackD3PDFlags
TrackD3PDFlags.storeTrackPredictionAtBLayer = False

####################################################################
# Define other job options here.
#

athenaCommonFlags.EvtMax = 100

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


