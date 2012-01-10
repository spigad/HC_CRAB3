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
athenaCommonFlags.FilesInput= ["AOD.pool.root"]

####################################################################
# Define the output file here.
#

if not globals().get('tupleFileOutput'):
    tupleFileOutput = 'physics.root'

from D3PDMakerConfig.D3PDProdFlags import prodFlags
prodFlags.WritePhysicsD3PD = True
prodFlags.WritePhysicsD3PD.FileName = tupleFileOutput
prodFlags.WritePhysicsD3PD.lock()

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
rec.DPDMakerScripts.append( "D3PDMakerConfig/PhysicsD3PD_prodJobOFragment.py" )
rec.doCBNT.set_Value_and_Lock( False )
rec.doAOD.set_Value_and_Lock( False )
rec.doWriteTAG.set_Value_and_Lock( False )
rec.doWriteAOD.set_Value_and_Lock( False )
include ("RecExCommon/RecExCommon_topOptions.py")
