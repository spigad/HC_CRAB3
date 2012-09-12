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

import glob
FilesInput = glob.glob('/data/etp1/elmsheus/data/mc11_7TeV.105009.J0_pythia_jetjet.merge.AOD.e815_s1273_s1274_r3086_r3063_tid640590_00/*')

from AthenaCommon.AthenaCommonFlags import athenaCommonFlags
#athenaCommonFlags.FilesInput= ["AOD.pool.root"]


###################################################################3
# Define the output file here.
#

if not globals().get('tupleFileOutput'):
    tupleFileOutput = 'egamma.root'

from D3PDMakerConfig.D3PDProdFlags import prodFlags
prodFlags.WriteEgammaD3PD = True
prodFlags.WriteEgammaD3PD.FileName = tupleFileOutput
prodFlags.WriteEgammaD3PD.lock()

###################################################################3
# Define other job options here.
#

athenaCommonFlags.EvtMax = -1

# Example of changing D3PD maker flags.
from D3PDMakerConfig.D3PDMakerFlags import D3PDMakerFlags
#D3PDMakerFlags.DoTrigger = False


###################################################################
# Configure RecExCommon.
#

from RecExConfig.RecFlags import rec
rec.DPDMakerScripts.append( "D3PDMakerConfig/EgammaD3PD_prodJobOFragment.py" )
rec.doCBNT.set_Value_and_Lock( False )
rec.doWriteTAG.set_Value_and_Lock( False )
include( "RecExCommon/RecExCommon_topOptions.py" )
