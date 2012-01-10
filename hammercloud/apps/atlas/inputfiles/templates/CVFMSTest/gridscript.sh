#!/bin/bash

# To run on grid:
# export PATHENA_GRID_SETUP_SH=/afs/cern.ch/project/gd/LCG-share/current/etc/profile.d/grid_env.sh
# source /afs/cern.ch/atlas/offline/external/GRID/DA/panda-client/latest/etc/panda/panda_setup.sh
# prun --exec "source gridscript.sh %IN" --outDS user.dewhurst.CVMFSTest.1 --inDS data10_7TeV.00161379.physics_Muons.merge.AOD.f282_m578 --nFilesPerJob 1 --site ANALY_RAL

echo "import AthenaPoolCnvSvc.ReadAthenaPool" &> jobOptions.py
echo "from AthenaCommon.AppMgr import ServiceMgr" >> jobOptions.py
echo "ServiceMgr.EventSelector.InputCollections = [\"$1\"]">> jobOptions.py
echo "theApp.EvtMax = -1" >> jobOptions.py
echo "ToolSvc = Service('ToolSvc')" >> jobOptions.py
echo "from InDetBeamSpotFinder.InDetBeamSpotFinderConf import InDet__InDetBeamSpotReader as InDetBeamSpotReader" >> jobOptions.py
echo "from AthenaCommon.AlgSequence import AlgSequence" >> jobOptions.py
echo "topSequence = AlgSequence()" >> jobOptions.py
echo "topSequence += InDetBeamSpotReader()" >> jobOptions.py
# Configure how job access conditions files
echo "from AthenaCommon.GlobalFlags import globalflags" >> jobOptions.py
echo "globalflags.DetGeo.set_Value_and_Lock('atlas')" >> jobOptions.py
echo "globalflags.DataSource.set_Value_and_Lock('data')" >> jobOptions.py
echo "from IOVDbSvc.CondDB import conddb" >> jobOptions.py
echo "include(\"InDetBeamSpotService/BeamCondSvc.py\")" >> jobOptions.py

export VO_ATLAS_SW_DIR=/cvmfs/atlas.cern.ch/repo/sw
export RELEASE=17.0.3
export ATLAS_POOLCOND_PATH="/cvmfs/atlas.cern.ch/repo/conditions"
echo "setting VO_ATLAS_SW_DIR to $VO_ATLAS_SW_DIR" 
echo "The release to be used is $RELEASE"
source $VO_ATLAS_SW_DIR/software/$RELEASE/cmtsite/asetup.sh AtlasOffline $RELEASE
athena.py jobOptions.py

