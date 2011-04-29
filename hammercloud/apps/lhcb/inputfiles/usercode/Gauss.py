##############################################################################
# File for running Gauss with postMC09 configuration
# (3.5 TeV beams, nu=1, no spill-over)
#
# Syntax is:
#   gaudirun.py Gauss-DEV.py <someInputJobConfiguration>.py
##############################################################################

from Gaudi.Configuration import *
importOptions("$APPCONFIGOPTS/Gauss/Beam3500GeV-md100-nu1.py")

##############################################################################
# latest database tags
##############################################################################
from Configurables import DDDBConf, CondDB, LHCbApp

#CondDB().Simulation = True             # Already taken care of in Gauss()
LHCbApp().DDDBtag   = "head-20101206"   # Must be set for selecting VELO
                                        # geometry list in Gauss()

DDDBConf(DataType = "2010")
CondDB().UseLatestTags = ["2010"]

#
# Options specific for a given job
# ie. setting of random number seed and name of output files
#

from Gauss.Configuration import *

#--Generator phase, set random numbers
GaussGen = GenInit("GaussGen")
GaussGen.FirstEventNumber = 1
GaussGen.RunNumber        = 1082

#--Number of events
nEvts = 50
LHCbApp().EvtMax = nEvts

Gauss().Output = 'NONE'
Gauss().Histograms = 'NONE'
#--Set name of output files for given job (uncomment the lines)
#  Note that if you do not set it Gauss will make a name based on event type,
#  number of events and the date
#idFile = 'GaussTest'
#HistogramPersistencySvc().OutputFile = idFile+'-histos.root'
#
#OutputStream("GaussTape").Output = "DATAFILE='PFN:%s.sim' TYP='POOL_ROOTTREE' OPT='RECREATE'"%idFile

#GenMonitor = GaudiSequencer( "GenMonitor" )
#SimMonitor = GaudiSequencer( "SimMonitor" )
#GenMonitor.Members += [ "GaussMonitor::CheckLifeTimeHepMC/HepMCLifeTime" ]
#SimMonitor.Members += [ "GaussMonitor::CheckLifeTimeMC/MCLifeTime" ]

