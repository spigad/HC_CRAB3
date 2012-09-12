############################################################
# BPhysAnalysisMasterAuto.py
# These are the master job options for running your analysis
# Include your own job options as shown below ensuring you
# do not overwrite things set here
# RUNS AUTOCONFIG - no need to set tags
############################################################

import glob
fileList = glob.glob('/data/etp1/elmsheus/data/mc11_7TeV.105009.J0_pythia_jetjet.merge.AOD.e815_s1273_s1274_r2731_r2780_tid541564_00/*')

from AthenaCommon.AthenaCommonFlags import athenaCommonFlags
athenaCommonFlags.FilesInput = fileList

from RecExConfig.RecFlags import rec

rec.doTrigger.set_Value_and_Lock(False) # leave false; nothing to do with trigger analysis  

# include your algorithm job options here
rec.UserAlgs.set_Value_and_Lock("jobOptions.py")

# Output log setting; this is for the framework in general
# You may over-ride this in your job options for your algorithm
rec.OutputLevel.set_Value_and_Lock(INFO);

# Write settings; keep all of these to false.
# Control the writing of your own n-tuple in the alg's job options
rec.doCBNT.set_Value_and_Lock(False)
rec.doWriteAOD.set_Value_and_Lock (False)
rec.doWriteTAG.set_Value_and_Lock (False)
rec.doWriteESD.set_Value_and_Lock (False)


# Needed for TAG
#from AthenaCommon.AthenaCommonFlags import athenaCommonFlags
#from PoolSvc.PoolSvcConf import PoolSvc
#svcMgr.PoolSvc.ReadCatalog +=["xmlcatalog_file:PoolFileCatalog.xml"]
#athenaCommonFlags.PoolInputQuery = "EventNumber==170382"

# main jobOption - must always be included
include("RecJobTransforms/UseOracle.py") # DB access
include ("RecExCommon/RecExCommon_topOptions.py")

theApp.EvtMax = -1 # number of event to process

# Stops writing of monitoring ntuples (big files)
from PerfMonComps.PerfMonFlags import jobproperties as jp
jp.PerfMonFlags.doMonitoring = False
jp.PerfMonFlags.doFastMon = False

