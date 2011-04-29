include( "BUSTopAnalysis/BUSTopAnalysis_jobOptions.py" )
include( "BUSTopTools/BUSTopTagTool.py" )
#include( "filelist_5502_1.py" )
include( "BUSTopAnalysis/BUSTopInitAlg_jobOptions.py" )

include( "BUSTopPreselection/BUSTopTruth_jobOptions.py" )

include( "BUSTopAnalysis/BUSTopAlg_jobOptions.py" )

include( "BUSTopPreselection/BUSTopTriggerDecision_jobOptions.py" )

include( "BUSTopPreselection/BUSTopMuonFilter_jobOptions.py" )
include( "BUSTopPreselection/BUSTopElectronFilter_jobOptions.py" )
include( "BUSTopPreselection/BUSTopOverlap_jobOptions.py" )
include( "BUSTopPreselection/BUSTopJES_jobOptions.py" )
include( "BUSTopPreselection/BUSTopBJetTagger_jobOptions.py" )

include( "BUSTopPreselection/BUSTopPreselection_jobOptions.py" )

include( "BUSTopAnalysis/BUSTopCSCSelection_jobOptions.py" )

include( "BUSTopAnalysis/BUSTopSelection_jobOptions.py" )

include( "BUSTopReconstruction/BUSTopNeutrinoReconstruction_jobOptions.py" )
include( "BUSTopReconstruction/BUSTopWReconstruction_jobOptions.py" )
include( "BUSTopReconstruction/BUSTopTReconstruction_jobOptions.py" )

include( "BUSTopAnalysis/BUSTopSpinAnalysis_jobOptions.py" )

include( "BUSTopAnalysis/BUSTopNeutrinoAnalysis_jobOptions.py" )
include( "BUSTopAnalysis/BUSTopWAnalysis_jobOptions.py" )
include( "BUSTopAnalysis/BUSTopTAnalysis_jobOptions.py" )

include( "BUSTopAnalysis/BUSTopEtMissAnalysis_jobOptions.py" )
include( "BUSTopAnalysis/BUSTopJetAnalysis_jobOptions.py" )
include( "BUSTopAnalysis/BUSTopMuonAnalysis_jobOptions.py" )
include( "BUSTopAnalysis/BUSTopElectronAnalysis_jobOptions.py" )

include( "BUSTopAnalysis/BUSTopHistogramDump_jobOptions.py" )
include( "BUSTopAnalysis/BUSTopZSelection_jobOptions.py" )

include( "BUSTopAnalysis/BUSTopTTreeWriter_jobOptions.py" )

ServiceMgr.EventSelector.InputCollections = [ "AOD.pool.root" ]
