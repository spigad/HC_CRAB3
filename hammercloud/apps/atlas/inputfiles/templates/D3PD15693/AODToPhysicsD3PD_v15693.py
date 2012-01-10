# $Id$
#
# @file D3PDMakerConfig/share/AODToPhysicsD3PD.py
# @author scott snyder <snyder@bnl.gov>
# @date Aug, 2009
# @brief Example for building a physics D3PD from an AOD.
#

#import os
#os.environ['ATLAS_CONDDB']='bla'
#os.environ['FRONTIER_LOG_LEVEL']='debug'

###################################################################3
# Define the input file here.
#

import glob
#fileList = glob.glob('/tmp/elmsheus/data10_7TeV.00153599.physics_MuonswBeam.merge.DESD_SGLMU.f251_m467/*')
fileList = glob.glob('/tmp/elmsheus/mc09_7TeV.106051.PythiaZmumu_1Lepton.merge.AOD.e468_s765_s767_r1207_r1210_tid124214_00/*')

from AthenaCommon.AthenaCommonFlags import athenaCommonFlags
#athenaCommonFlags.FilesInput= ["AOD.pool.root"]
athenaCommonFlags.FilesInput= fileList


###################################################################3
# Define the output file here.
#

if not globals().get('tupleFileOutput'):
    tupleFileOutput = 'physics.root'


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

from D3PDMakerConfig.physicsD3PD import physicsD3PD
alg = physicsD3PD (tupleFileOutput)


from AthenaCommon.AppMgr import ServiceMgr
ServiceMgr.MessageSvc.OutputLevel = INFO
ServiceMgr.MessageSvc.infoLimit = 0
