#!/usr/bin/env python
import os,sys,subprocess

## Common packages required by SUSYTools
lpkgs = [
'svn co svn+ssh://flegger@svn.cern.ch/reps/atlasoff/PhysicsAnalysis/D3PDTools/RootCore/tags/RootCore-00-00-31 RootCore',
'svn co svn+ssh://flegger@svn.cern.ch/reps/atlasoff/PhysicsAnalysis/AnalysisCommon/ObjectSelectorCore/tags/ObjectSelectorCore-00-00-09 ObjectSelectorCore',
'svn co svn+ssh://flegger@svn.cern.ch/reps/atlasoff/PhysicsAnalysis/JetMissingEtID/JetSelectorTools/tags/JetSelectorTools-00-00-11 JetSelectorTools',
'svn co svn+ssh://flegger@svn.cern.ch/reps/atlasoff/PhysicsAnalysis/MuonID/MuonIDAnalysis/MuonEfficiencyCorrections/tags/MuonEfficiencyCorrections-01-00-10 MuonEfficiencyCorrections',
'svn co svn+ssh://flegger@svn.cern.ch/reps/atlasoff/PhysicsAnalysis/MuonID/MuonIDAnalysis/MuonMomentumCorrections/tags/MuonMomentumCorrections-00-04-01 MuonMomentumCorrections',
'svn co svn+ssh://flegger@svn.cern.ch/reps/atlasoff/Reconstruction/egamma/egammaEvent/tags/egammaEvent-03-06-20/cmt svn+ssh://flegger@svn.cern.ch/reps/atlasoff/Reconstruction/egamma/egammaEvent/tags/egammaEvent-03-06-20/egammaEvent svn+ssh://flegger@svn.cern.ch/reps/atlasoff/Reconstruction/egamma/egammaEvent/tags/egammaEvent-03-06-20/Root egammaEvent',
'svn co svn+ssh://flegger@svn.cern.ch/reps/atlasoff/Reconstruction/egamma/egammaAnalysis/egammaAnalysisUtils/tags/egammaAnalysisUtils-00-02-70 egammaAnalysisUtils', 
'svn co svn+ssh://flegger@svn.cern.ch/reps/atlasoff/PhysicsAnalysis/JetTagging/JetTagPerformanceCalibration/CalibrationDataInterface/tags/CalibrationDataInterface-00-00-11/cmt svn+ssh://flegger@svn.cern.ch/reps/atlasoff/PhysicsAnalysis/JetTagging/JetTagPerformanceCalibration/CalibrationDataInterface/tags/CalibrationDataInterface-00-00-11/CalibrationDataInterface svn+ssh://flegger@svn.cern.ch/reps/atlasoff/PhysicsAnalysis/JetTagging/JetTagPerformanceCalibration/CalibrationDataInterface/tags/CalibrationDataInterface-00-00-11/Root svn+ssh://flegger@svn.cern.ch/reps/atlasoff/PhysicsAnalysis/JetTagging/JetTagPerformanceCalibration/CalibrationDataInterface/tags/CalibrationDataInterface-00-00-11/src CalibrationDataInterface',
'svn co svn+ssh://flegger@svn.cern.ch/reps/atlasoff/DataQuality/GoodRunsLists/tags/GoodRunsLists-00-00-96 GoodRunsLists',
'svn co svn+ssh://flegger@svn.cern.ch/reps/atlasoff/PhysicsAnalysis/AnalysisCommon/PileupReweighting/tags/PileupReweighting-00-02-01 PileupReweighting',
'svn co svn+ssh://flegger@svn.cern.ch/reps/atlasoff/Reconstruction/Jet/JetUncertainties/tags/JetUncertainties-00-03-05-01 JetUncertainties',
'svn co svn+ssh://flegger@svn.cern.ch/reps/atlasoff/Reconstruction/Jet/JetResolution/tags/JetResolution-00-00-09 JetResolution',
'svn co svn+ssh://flegger@svn.cern.ch/reps/atlasoff/Reconstruction/MissingETUtility/tags/MissingETUtility-00-02-10 MissingETUtility',
'svn co svn+ssh://flegger@svn.cern.ch/reps/atlasoff/PhysicsAnalysis/AnalysisCommon/ReweightUtils/tags/ReweightUtils-00-02-03 ReweightUtils',
'svn co svn+ssh://flegger@svn.cern.ch/reps/atlasoff/Trigger/TrigAnalysis/TrigRootAnalysis/tags/TrigRootAnalysis-00-00-07 TrigRootAnalysis',
]

## Extra packages
# - Fake lepton background
#lpkgs += ['']

def parseCmdLine(args):
    """ Parse input command line to optdict.
    To get the whole list of options type : install.py -h"""
    from optparse import OptionParser
    parser = OptionParser()
    parser.add_option("--vclean", dest="vclean", help="Remove pkg before checking-out new version",
                      action='store_true', default=False) 
    (config, args) = parser.parse_args(args)
    return config

def doc():
    return """
Short instructions
==================

If you have not done so:
cd RootCore
./configure
source scripts/setup.sh
cd ..

Then every time you start a new session you should:
source RootCore/scripts/setup.sh

To compile:
$ROOTCOREDIR/scripts/find_packages.sh
$ROOTCOREDIR/scripts/compile.sh

Further informations on RootCore can be found on:
https://twiki.cern.ch/twiki/bin/view/AtlasProtected/RootCore
"""

def removeObsolete(mylpkgs):
    for pkg in mylpkgs:
        if len(pkg.split()) < 4: continue
        pkgname = pkg.split()[len(pkg.split())-1]
        if not os.path.isdir(pkgname): continue
        pkgtag  = pkg.split()[2]
        if not 'tags/' in pkgtag: continue
        pkgtag = pkgtag.split('tags/')[1].split('/')[0]
        if os.path.isfile('%s/.svn/entries' % pkgname):
            fname = '%s/.svn/entries' % pkgname
        elif os.path.isfile('%s/cmt/.svn/entries' % pkgname):
            fname = '%s/cmt/.svn/entries' % pkgname
        else:
            continue
        fentries = open(fname,'r')
        found = False
        for line in fentries:
            if not pkgtag in line: continue
            found = True
            break
        fentries.close()
        if found: continue
        print 'removing',pkgname,'to prepare new tag',pkgtag
        ret = subprocess.call('rm -Rf %s' % pkgname, shell=True)
    return

## Check-out
def checkout(mylpkgs):
    ret = 0
    for pkg in mylpkgs:
        print 'checking-out',pkg.split()[len(pkg.split())-1]
        ret = subprocess.call(pkg, shell=True)
        if ret == 0: continue
        print pkg,'returned with code',ret
        break
    return

def main():
    config = parseCmdLine(sys.argv[1:])
    if config.vclean: removeObsolete(lpkgs)
    checkout(lpkgs)
    ## Print short instructions
    print doc()
    return

if __name__ == "__main__":
    main()
