#!/usr/bin/env python

from __future__ import print_function

__author__ = "Tim Brooks <brooks@cern.ch>"
__doc__    = """
Python script used to run on SUSY D3PDs. Currently runs baseline and R&D di-lepton analysis.
Usage: 
chmod u+x susycutflow_2lep.py
./susycutflow_2lep.py --help
./susycutflow_2lep.py

Tommaso Lari, 21-apr-2011:
  Output is now written on out.log (unless changed with --out flag)
  Updated trigger strategy. Defaults are ok to run on MC; set --isdataeg
  when running on electron stream and --isdatamu when running on muon stream

based on susycutflow_1lep.py by:
Renaud Bruneliere <Renaud.Bruneliere@cern.ch>
"""

from time import time
from datetime import datetime
from array import array
from math import *
from os import listdir, environ
import os.path
import sys
import subprocess
import shutil
import ROOT

class Cutflow(object):
    state = True
    def __init__(self, cuts, name="cutflow"):
        self.cuts = cuts
        self.name = name
        self.state = True
        self.counts = {}
        for cut in cuts:
            self.counts[cut] = 0

    def fails(self, *args):
        self.state = False

    def newEvent(self):
        self.state = True

    def passes(self, cut, weight=1):
        if self.state:
            #print("{0:s} filling {1:s}({2:f}) with {3:f}".format(self.name, cut, self.counts[cut], weight))
            self.counts[cut] += weight

    def total(self, cutname=None):
        if cutname:
            return self.counts[cutname]
        else:
            return self.counts[self.cuts[0]]

    def debug(self):
        print(self.counts)

    def __repr__(self):
        if self.state: state = "passed"
        else:          state = "failed"

        return '<Cutflow state="{0:s}" sum_total="{1:g}">' \
                .format(state, self.total() )
    def __nonzero__(self):
        return self.state
    __bool__ = __nonzero__     # New python3 style truth testing
        
def parseCmdLine():
    """ Parse input command line to optdict.
    To get the whole list of options type : susycutflow_2lep.py -h"""
    from argparse import ArgumentParser
    parser = ArgumentParser()
    a = parser.add_argument
    a("--infile", dest="infile", help="Input file",
                      default='/castor/cern.ch/atlas/atlascerngroupdisk/phys-susy/D4PD/p60x/user.bruneli.mc10_7TeV.106484.SU4_herwigpp_susy.merge.NTUP_SUSY.e598_s933_s946_r2302_r2300_p601_v3/user.bruneli.006134._00001.susy.root') 
    a("--out", dest="outfile", help="output", default='')
    a("--isdata", dest="isdata", help="Data or Monte Carlo ?",
                      action='store_true', default=False) 
    a("--stream", dest="stream", help="Data stream",default='Muons') 
    a("--trgwgt", dest="trgwgt", help="Apply a data-driven weight to emulate trigger in MC ?",
                      action='store_true', default=False)
    a("--PUwgt", dest="PUwgt", help="Apply pileup reweighting to MC ?",
                      action='store_true', default=False)
    a("--JVFwgt", dest="JVFwgt", help="Apply jvf reweighting to MC ?",
                      action='store_true', default=False)
    a("--jesup", dest="jesup", help="Rescale jet energy scale by +1 sigma",
                      action='store_true', default=False)
    a("--jesdown", dest="jesdown", help="Rescale jet energy scale by -1 sigma",
                      action='store_true', default=False)
    a("--jer", dest="jer", help="Smear jet energy scale by 1 sigma",
                      action='store_true', default=False)
    a("--nevts", type=int, dest="nevts", help="Maximum number of events to process", default=-1)
    a("--PUgen", dest="PUgen", help="Generate pileup reweighting file ?",
                      action='store_true', default=False)
    # Some old options: should still do the right thing (TM)
    a("--isdataeg", dest="isdataeg", help="egamma data stream",
                      action='store_true', default=False)
    a("--isdatamu", dest="isdatamu", help="muons data stream",
                      action='store_true', default=False)
    a("-v", dest="verbose", help="Print detailed information",
                      action='store_true', default=False)

    config = parser.parse_args()
    if config.isdataeg or config.isdatamu:
        config.isdata = True
        if config.isdataeg: config.stream = 'Egamma'
    return config

def getinfiles(infile):
    """ Get input files from castor directory.
    Remember to never run directly on castor"""
    ret = subprocess.call('xrdcp root://castoratlas/%s $TMPDIR/' % infile,shell=True)
    if ret != 0: print("getinfiles: could not copy",infile,"\nEXIT")
    newfile = '$TMPDIR/%s' % infile.split('/')[len(infile.split('/'))-1]
    return newfile

def main():
    print("susycutflow_2lep.py: starting", datetime.now() )
    config = parseCmdLine()
    verbose = config.verbose

    ## redefine output
    if config.outfile:
      out_file = open(config.outfile, 'w');
      sys.stdout = out_file  

    ## Read input file
    infiles = config.infile
    t = ROOT.TChain("susy")
    for infile in infiles.split(','):
      print("Loading file " + infile)
      if '/castor/cern.ch' in config.infile: infile = getinfiles(config.infile)
      t.Add(infile)

    ## Load RootCore libs
    if os.path.exists("%s/preload" % environ['ROOTCOREDIR']):
        fpreload = open("%s/preload" % environ['ROOTCOREDIR'],"r")
        for line in fpreload:
            line = line.split('\n')[0]
            if line == "": continue
            ROOT.gSystem.Load(line)
    for libname in listdir("%s/lib/" % environ['ROOTCOREDIR']):
        if not (libname.startswith("lib") and libname.endswith(".so")): continue
        ROOT.gSystem.Load("%s/lib/%s" % (environ['ROOTCOREDIR'],libname))
    have_grl = False
    if config.isdata and os.path.exists("%s/lib/libGoodRunsLists.so" % environ['ROOTCOREDIR']):
        have_grl = True
        grl_reader = ROOT.Root.TGoodRunsListReader('data11_7TeV.periodAllYear_DetStatus-v36-pro10_CoolRunQuery-00-04-08_Susy.xml')
        grl_reader.Interpret()
        goodrunslist = grl_reader.GetMergedGRLCollection()
        goodrunslist.Summary() # Print out a little summary of runs
        #goodrunslist.Summary(True) # Print out a list of all good runs and lbns
    have_pileuptool = False
    if config.PUgen and os.path.exists("%s/lib/libPileupReweighting.so" % environ['ROOTCOREDIR']):
        genPileUpTool = ROOT.Root.TPileupReweighting("PUgen")
        genPileUpTool.AddPeriod(180164, 177986,180481) # Period B-D
        genPileUpTool.AddPeriod(183003, 180614,184169) # Period E-H
        genPileUpTool.AddPeriod(185649, 185353,186934) # Period I-K1
        genPileUpTool.AddPeriod(185761, 186935,999999) # Period >=K2
        genPileUpTool.initialize()
    if config.PUwgt and os.path.exists("%s/lib/libPileupReweighting.so" % environ['ROOTCOREDIR']):
        have_pileuptool = True
        elPileUpTool = ROOT.Root.TPileupReweighting("Electrons")
        elPileUpTool.MergeMCRunNumbers(185649,185761)
        elPileUpTool.SetUnrepresentedDataAction(2)
        if os.path.isfile("../data/mc11a_generated.root"):
            print("using generated PU file")
            tool_failure = elPileUpTool.initialize("../data/susy_1Electron_avgintperbx.root", "LumiMetaData", "../data/mc11a_generated.root", "MCPileupReweighting")
        else:
            print("using default PU file")
            tool_failure = elPileUpTool.initialize("../data/susy_1Electron_avgintperbx.root", "LumiMetaData", "../../PileupReweighting/share/mc11a_defaults.root", "MCPileupReweighting")
        if tool_failure: print("El PileUpTool failed to initialise with code: %d" %tool_failure)
        muPileUpTool = ROOT.Root.TPileupReweighting("Muons")
        muPileUpTool.MergeMCRunNumbers(185649,185761)
        muPileUpTool.SetUnrepresentedDataAction(2)
        if os.path.isfile("../data/mc11a_generated.root"):
            print("using generated PU file")
            tool_failure = muPileUpTool.initialize("../data/susy_1Muon_avgintperbx.root", "LumiMetaData", "../data/mc11a_generated.root", "MCPileupReweighting")
        else:
            print("using default PU file")
            tool_failure = muPileUpTool.initialize("../data/susy_1Muon_avgintperbx.root", "LumiMetaData", "../../PileupReweighting/share/mc11a_defaults.root", "MCPileupReweighting")
        #print("Pileup weights:")
        #for i in range(25):
        #    print("weight(mu = %4.1f) = %13.10f(EL) %13.10f(MU)" %(float(i), elPileUpTool.getPileupWeight(i), muPileUpTool.getPileupWeight(i) ) )
    susyObjDef = ROOT.SUSYObjDef()
    susyObjDef.initialize()
    fakeMetEst = ROOT.FakeMetEstimator()
    fakeMetEst.initialize("../data/fest_periodF_v1.root")

    ## Copy files used for b-tagging locally
    shutil.copyfile('../data/BTagCalibration.env','BTagCalibration.env')
    shutil.copyfile('../data/BTagCalibrations.root','BTagCalibrations.root')

    ## Prepare class for muon trigger rescaling in MC
    trigWeighter = None # data-driven method
    if not config.isdata:
        reweight_file = ROOT.TFile("../data/EF_mu18.root")
        trig_numerator_hist   = reweight_file.Get("passes") # Get the numerator histogram
        trig_denominator_hist = reweight_file.Get("trials") # Get the denominator histogram
        trigWeighter = ROOT.APReweightND(trig_denominator_hist,trig_numerator_hist,True) # Instantiate the tool
        reweight_file.Close()
    muTrgSFTool = ROOT.MuonTriggerSFTool()
    muTrgSFTool.initialize("../data/trigger/SF_for_EPS.root","../data/trigger/SF_barrel_ptdep.root")

    ## Jet vertex fraction correction factors
    jvfReweighting = None
    if config.JVFwgt:
        jvfReweightingEle = ROOT.SUSY.TJVFReweighting("tjvfEle")
        jvfReweightingEle.initialize("../data/jvfWeights.root","electron",3)
        jvfReweightingMuo = ROOT.SUSY.TJVFReweighting("tjvfMuo")
        jvfReweightingMuo.initialize("../data/jvfWeights.root","muon",3)

    ## Treatment of jet/Etmiss uncertainties
    whichsyste = ROOT.JetErr.NONE
    if config.jesup:
        whichsyste = ROOT.JetErr.JESUP
    elif config.jesdown:
        whichsyste = ROOT.JetErr.JESDOWN
    elif config.jer:
        whichsyste = ROOT.JetErr.JER

    ## Loop over events (not at all optimized for speed, more for clarity)
    if config.nevts > 0:
        nEvts = config.nevts
    else:
        nEvts = t.GetEntries()
    cutnames = ['No cut',
                'GRL',
                'LArError',
                'Electron LArHole veto',
                'Jet LArHole veto',
                'Trigger',
                'Jet/MET cleaning',
                'Good primary vertex',
                #'Electron crack removal',
                'Cosmic muon veto',
                'Dilepton requirement',
                'Lepton signs & M_ll > 20GeV',
                'Tight iso electrons',
                '(OS+Jets)Njet(30,30,30) >= 2',
                '(OS+Jets)Bjet-Veto',
                '(OS+Jets)Zmll-Veto',
                '(OS+Jets)MET > 50 GeV',

                '(OS-JetVeto)Njet(30) < 1',
                '(OS-JetVeto)Zmll-Veto',
                '(OS-JetVeto)MET > 100 GeV',
                '(OS-JetVeto)MET > 120 GeV',

                '(SS-JetVeto)Njet(30) < 1',
                '(SS-JetVeto)MET > 100 GeV',
                ]

    # Prepare some Cutflows
    cuts_OSEE = Cutflow(cutnames, "OSEE")
    cuts_OSEM = Cutflow(cutnames, "OSEM")
    cuts_OSME = Cutflow(cutnames, "OSME")
    cuts_OSMM = Cutflow(cutnames, "OSMM")
    cuts_SSEE = Cutflow(cutnames, "SSEE")
    cuts_SSEM = Cutflow(cutnames, "SSEM")
    cuts_SSME = Cutflow(cutnames, "SSME")
    cuts_SSMM = Cutflow(cutnames, "SSMM")

    # Bundle these up for clarity
    cuts_OSE = [cuts_OSEE, cuts_OSEM]
    cuts_OSM = [cuts_OSMM, cuts_OSME]
    cuts_SSE = [cuts_SSEE, cuts_SSEM]
    cuts_SSM = [cuts_SSMM, cuts_SSME]

    cuts_EE = [cuts_OSEE, cuts_SSEE]
    cuts_EM = [cuts_OSEM, cuts_SSEM]
    cuts_ME = [cuts_OSME, cuts_SSME]
    cuts_MM = [cuts_OSMM, cuts_SSMM]

    cuts_OS = cuts_OSE + cuts_OSM       # Opposite sign cutflows
    cuts_SS = cuts_SSE + cuts_SSM       # Same sign cutflows

    cuts_SF = cuts_EE + cuts_MM
    cuts_DF = cuts_EM + cuts_ME

    cuts_E = cuts_OSE + cuts_SSE        # Cutflows with electron triggers
    cuts_M = cuts_OSM + cuts_SSM        #    "    muon triggers

    cuts_all = cuts_E + cuts_M          # All cutflows

    # Helper function to pass all cutflows that have not yet failed
    def passAny(cut_name, el_wgt, mu_wgt):
        for cutflow in cuts_E:
            cutflow.passes(cut_name, el_wgt)
        for cutflow in cuts_M:
            cutflow.passes(cut_name, mu_wgt)

    start_time = time()
    for iEvt in range(nEvts):
        if time() - start_time > 15:
          print("Reading event",iEvt,"/",nEvts)
          start_time = time()
        t.GetEntry(iEvt)

        ## Do not forget to clear arrays once per event
        susyObjDef.Reset()

        for cutflow in cuts_all: cutflow.newEvent()

        ## Get electrons
        ## WARNING: with 2011 data there is a new flag el_OQ to check object quality
        el_idx = {'signal':[],'baseline':[],'crack':[],'met':ROOT.std.vector(int)()}
        for iEl in range(t.el_n):
            # Apply baseline SUSY electron selection 
            # On Monte Carlo, if you need rejecting electrons in dead regions of LAr, then set t.RunNumber = 180614
            # For further information, please check https://twiki.cern.ch/twiki/bin/view/AtlasProtected/LArCleaningAndObjectQuality#Dealing_with_LAr_hardware_proble
            myRunNb = 180614 # Reject electrons in LAr hole by default both in data AND MC
            if susyObjDef.IsElectron(iEl,myRunNb,
                                     t.el_cl_eta.at(iEl),t.el_cl_phi.at(iEl),t.el_cl_E.at(iEl),
                                     t.el_tracketa.at(iEl),t.el_trackphi.at(iEl),
                                     t.el_author.at(iEl),t.el_mediumPP.at(iEl),t.el_OQ.at(iEl),
                                     t.el_nPixHits.at(iEl),t.el_nSCTHits.at(iEl),
                                     config.isdata,10000,2.47,False):
                el_idx['met'].push_back(iEl)
                el_idx['baseline'].append(iEl)
                # Check whether a baseline electron is within crack region
                if susyObjDef.IsInCrack(t.el_cl_eta.at(iEl)):
                    el_idx['crack'].append(iEl)
                # Apply additionnal cuts for signal electrons 
                # Electron pt cut is 10 GeV, with a leading electron above 25GeV for e20_medium trigger
                # Electron ptcone20/pt must be < 0.1
                if susyObjDef.IsSignalElectron(iEl,t.el_tightPP.at(iEl),t.el_ptcone20.at(iEl),10000.,0.1):
                    el_idx['signal'].append(iEl)

        ## Get muons
        ##
        mu_idx = {'signal':[],'baseline':[],'cosmic':[],'bad':[],'trgmatch':[],'met':ROOT.std.vector(int)()}
        for iMu in range(t.mu_staco_n):
            # Check if offline muon is matched to a muon trigger object
            if susyObjDef.MuonHasTriggerMatch(iMu,t.mu_staco_n,t.trig_EF_trigmuonef_n,t.trig_EF_trigmuonef_track_n,
                                              t.mu_staco_pt,t.mu_staco_eta,t.mu_staco_phi,
                                              t.trig_EF_trigmuonef_track_CB_pt, t.trig_EF_trigmuonef_track_CB_eta,
                                              t.trig_EF_trigmuonef_track_CB_phi, t.trig_EF_trigmuonef_track_CB_hasCB):
                mu_idx['trgmatch'].append(iMu)

            # Baseline muon selection does not include any isolation cut => directly used in Etmiss computation
            if susyObjDef.IsMuon(iMu,t.mu_staco_pt.at(iMu),t.mu_staco_eta.at(iMu),t.mu_staco_phi.at(iMu),
                                 t.mu_staco_E.at(iMu),
                                 t.mu_staco_me_qoverp_exPV.at(iMu),t.mu_staco_id_qoverp_exPV.at(iMu),
                                 t.mu_staco_me_theta_exPV.at(iMu),t.mu_staco_id_theta_exPV.at(iMu),
                                 t.mu_staco_id_theta.at(iMu),
                                 t.mu_staco_isCombinedMuon.at(iMu),t.mu_staco_isLowPtReconstructedMuon.at(iMu),
                                 t.mu_staco_loose.at(iMu),
                                 t.mu_staco_expectBLayerHit.at(iMu),t.mu_staco_nBLHits.at(iMu),
                                 t.mu_staco_nPixHits.at(iMu),t.mu_staco_nPixelDeadSensors.at(iMu),
                                 t.mu_staco_nPixHoles.at(iMu),t.mu_staco_nSCTHits.at(iMu),
                                 t.mu_staco_nSCTDeadSensors.at(iMu),t.mu_staco_nSCTHoles.at(iMu),
                                 t.mu_staco_nTRTHits.at(iMu),t.mu_staco_nTRTOutliers.at(iMu),
                                 config.isdata,10000.,2.4):
                mu_idx['met'].push_back(iMu)
                mu_idx['baseline'].append(iMu)
                # Additionnal cut for signal muons: check whether it also pass isolation cut and if pT>10 GeV
                # Add leading muon cut of 20 GeV later
                if susyObjDef.IsSignalMuon(iMu,t.mu_staco_ptcone20.at(iMu),10000.): 
                    mu_idx['signal'].append(iMu)
                # Check whether muon could be a cosmic candidate: |z0|>1mm or |d0|>0.2mm
                if susyObjDef.IsCosmicMuon(t.mu_staco_z0_exPV.at(iMu),t.mu_staco_d0_exPV.at(iMu), 1.0, 0.2):
                    mu_idx['cosmic'].append(iMu)
                # Check whether muon is badly reconstructed
                if susyObjDef.IsBadMuon(t.mu_staco_qoverp_exPV.at(iMu),t.mu_staco_cov_qoverp_exPV.at(iMu)):
                    mu_idx['bad'].append(iMu)

        ##
        ## Get jets
        ##
        ## It is assumed that no sorting of jets as function of jet pT is necessary with AntiKt4TopoNewEM jets
        jet_idx = {'signal':[],'good':[],'bad':[],'LArHoleVeto':[],'goodpt':[],'btagged':[]}
        for iJet in range(t.jet_AntiKt4TopoNewEM_n):
            ## LAr hole veto applies to any jet (before overlap removal)
            ## Recommend to apply jet veto only to N leading jets in an N jet channel
            if susyObjDef.IsLArHoleVeto(t.jet_AntiKt4TopoNewEM_pt.at(iJet),t.jet_AntiKt4TopoNewEM_eta.at(iJet),
                                        t.jet_AntiKt4TopoNewEM_phi.at(iJet),
                                        t.jet_AntiKt4TopoNewEM_BCH_CORR_JET.at(iJet), 
                                        t.jet_AntiKt4TopoNewEM_BCH_CORR_CELL.at(iJet), 
                                        config.isdata,40000.):
                ## Skip event
                jet_idx['LArHoleVeto'].append(iJet)

            ## Do not apply any eta cut for jet cleaning
            ## Remember jet cleaning is applied only to data
            isgoodjet = False
            if susyObjDef.IsJet(iJet,t.jet_AntiKt4TopoNewEM_pt.at(iJet),t.jet_AntiKt4TopoNewEM_eta.at(iJet),
                                t.jet_AntiKt4TopoNewEM_phi.at(iJet),t.jet_AntiKt4TopoNewEM_E.at(iJet),
                                t.jet_AntiKt4TopoNewEM_emscale_eta.at(iJet),
                                t.jet_AntiKt4TopoNewEM_emfrac.at(iJet),t.jet_AntiKt4TopoNewEM_hecf.at(iJet),
                                t.jet_AntiKt4TopoNewEM_LArQuality.at(iJet),t.jet_AntiKt4TopoNewEM_HECQuality.at(iJet),
                                t.jet_AntiKt4TopoNewEM_Timing.at(iJet),t.jet_AntiKt4TopoNewEM_sumPtTrk.at(iJet),
                                t.jet_AntiKt4TopoNewEM_fracSamplingMax.at(iJet),
                                t.jet_AntiKt4TopoNewEM_NegativeE.at(iJet),
                                config.isdata,20000.,10.,ROOT.JetID.LooseBad,whichsyste):
                isgoodjet = True

            ## Consider only jets with pT > 20 GeV for following
            if t.jet_AntiKt4TopoNewEM_pt.at(iJet) <= 20000.: continue

            ## Check overlap removal with electrons, skip jets overlapping with electrons
            isoverlap = False
            for iEl in el_idx['baseline']:
                if susyObjDef.GetElecTLV(iEl).DeltaR(susyObjDef.GetJetTLV(iJet)) > 0.2: continue
                isoverlap = True
                break
            if isoverlap: continue

            ## Flag remaining jets
            if not isgoodjet:
                jet_idx['bad'].append(iJet)
            elif isgoodjet and fabs(t.jet_AntiKt4TopoNewEM_eta.at(iJet)) < 2.8:
                jet_idx['goodpt'].append(t.jet_AntiKt4TopoNewEM_pt.at(iJet))
                jet_idx['good'].append(iJet)
              
        ## Apply descendent pT sorting of jets
        ptandidx = zip(jet_idx['goodpt'],jet_idx['good'])
        ptandidx.sort(reverse=True)
        del jet_idx['good'][:],jet_idx['goodpt'][:]
        jet_idx['good']   = [ x[1] for x in ptandidx ]
        jet_idx['goodpt'] = [ x[0] for x in ptandidx ]

        ## Additonnal JVF requirement used in 2-lepton analysis
        jvfWeightEle = 1.
        jvfWeightMuo = 1.
        for iJet in jet_idx['good']:
            passJVF = abs(t.jet_AntiKt4TopoNewEM_jvtxf.at(iJet)) > 0.75
            if config.JVFwgt and t.jet_AntiKt4TopoNewEM_pt.at(iJet) > 25000.:
                jvfWeightEle *= jvfReweightingEle.getJVFWeight(passJVF)
                jvfWeightMuo *= jvfReweightingMuo.getJVFWeight(passJVF)
            if passJVF:
                jet_idx['signal'].append(iJet)
        
        ## Compute corrected Etmiss (make use of mu_idx['met'] which contains list of muons to be included in Etmiss)
        for iJet in jet_idx['signal']:
            if fabs(t.jet_AntiKt4TopoNewEM_pt.at(iJet) ) > 25000.:
                if t.jet_AntiKt4TopoNewEM_flavor_weight_JetFitterCOMBNN.at(iJet) > 2.0:
                    jet_idx['btagged'].append(iJet)
        ## First compute Etx and Ety up to abs(eta)<4.5 (jet/etmiss wg recommendations)
        etx_RefFinal = t.MET_Simplified20_RefFinal_etx_CentralReg + t.MET_Simplified20_RefFinal_etx_EndcapRegion + t.MET_Simplified20_RefFinal_etx_ForwardReg
        ety_RefFinal = t.MET_Simplified20_RefFinal_ety_CentralReg + t.MET_Simplified20_RefFinal_ety_EndcapRegion + t.MET_Simplified20_RefFinal_ety_ForwardReg
        etx_RefJet = t.MET_Simplified20_RefJet_etx_CentralReg + t.MET_Simplified20_RefJet_etx_EndcapRegion + t.MET_Simplified20_RefJet_etx_ForwardReg
        ety_RefJet = t.MET_Simplified20_RefJet_ety_CentralReg + t.MET_Simplified20_RefJet_ety_EndcapRegion + t.MET_Simplified20_RefJet_ety_ForwardReg
        if whichsyste == ROOT.JetErr.NONE:
            met = susyObjDef.GetMET(etx_RefFinal,ety_RefFinal,etx_RefJet,ety_RefJet,
                    t.MET_Simplified20_Muon_Total_Staco_etx,t.MET_Simplified20_Muon_Total_Staco_ety,
                    mu_idx['met'],el_idx['met'],False)
        else: # Propagate JES/JER uncertainty to Etmiss
            met = susyObjDef.GetMETUtil(t.jet_AntiKt4TopoNewEM_pt,
				        t.jet_AntiKt4TopoNewEM_eta,
				        t.jet_AntiKt4TopoNewEM_phi,
				        t.jet_AntiKt4TopoNewEM_E,
				        t.jet_AntiKt4TopoNewEM_MET_Simplified20_wet,
                                        t.jet_AntiKt4TopoNewEM_MET_Simplified20_wpx,
                                        t.jet_AntiKt4TopoNewEM_MET_Simplified20_wpy,
                                        t.jet_AntiKt4TopoNewEM_MET_Simplified20_statusWord,
                                        t.el_pt,
                                        t.el_eta,
                                        t.el_phi,
                                        t.el_MET_Simplified20_wet,
                                        t.el_MET_Simplified20_wpx,
                                        t.el_MET_Simplified20_wpy,
                                        t.el_MET_Simplified20_statusWord,
                                        t.MET_Simplified20_CellOut_etx,
                                        t.MET_Simplified20_CellOut_ety,
                                        t.MET_Simplified20_CellOut_sumet,
                                        t.MET_Simplified20_RefGamma_etx,
                                        t.MET_Simplified20_RefGamma_ety,
                                        t.MET_Simplified20_RefGamma_sumet,
                                        mu_idx['met'],
                                        t.mu_staco_ms_qoverp, 
                                        t.mu_staco_ms_theta, 
                                        t.mu_staco_ms_phi, 
                                        t.mu_staco_charge,
                                        whichsyste)

        ##
        ## Apply lepton veto
        ##
        for iJet in jet_idx['good']:
            for iEl in el_idx['baseline']:
                if susyObjDef.GetElecTLV(iEl).DeltaR(susyObjDef.GetJetTLV(iJet)) > 0.4: continue
                el_idx['baseline'].remove(iEl)
                if iEl in el_idx['signal']: el_idx['signal'].remove(iEl)
            for iMu in mu_idx['baseline']:
                if susyObjDef.GetMuonTLV(iMu).DeltaR(susyObjDef.GetJetTLV(iJet)) > 0.4: continue
                mu_idx['baseline'].remove(iMu)
                if iMu in mu_idx['cosmic']: mu_idx['cosmic'].remove(iMu) # Check cosmic cut only if sufficiently away from a jet
                if iMu in mu_idx['signal']: mu_idx['signal'].remove(iMu)

        ## Make cuts
        wgt = {'el': 1., 'mu': 1.} # el,mu channels respectively
        if not config.isdata:
          if have_pileuptool:
            wgt['el'] *= elPileUpTool.getPileupWeight(t.lbn)
            wgt['mu'] *= muPileUpTool.getPileupWeight(t.lbn)

        for cutflow in cuts_E: cutflow.passes('No cut', wgt['el'])
        for cutflow in cuts_M: cutflow.passes('No cut', wgt['mu'])

        # Apply GRL selection if we loaded the reader OK
        if not have_grl or not config.isdata or goodrunslist.HasRunLumiBlock(t.RunNumber, t.lbn):
          for cutflow in cuts_E: cutflow.passes('GRL', wgt['el'])
          for cutflow in cuts_M: cutflow.passes('GRL', wgt['mu'])
        else:
          for cutflow in cuts_all: cutflow.fails()
        if any(cuts_all) and (t.larError == 0 or not config.isdata):
          for cutflow in cuts_E: cutflow.passes('LArError', wgt['el'])
          for cutflow in cuts_M: cutflow.passes('LArError', wgt['mu'])
        else:
          for cutflow in cuts_all: cutflow.fails()

        if any(cuts_all):
            for el in el_idx['baseline']:
                el_tlv = susyObjDef.GetElecTLV(el)
                if susyObjDef.IsLArHole(t.el_cl_eta[el], t.el_cl_phi[el]):
                    for cutflow in cuts_all: cutflow.fails()
            for cutflow in cuts_E: cutflow.passes('Electron LArHole veto', wgt['el'])
            for cutflow in cuts_M: cutflow.passes('Electron LArHole veto', wgt['mu'])

            if not len(jet_idx['LArHoleVeto']):
                for cutflow in cuts_E: cutflow.passes('Jet LArHole veto', wgt['el'])
                for cutflow in cuts_M: cutflow.passes('Jet LArHole veto', wgt['mu'])
            else:
                for cutflow in cuts_all: cutflow.fails()
        # Trigger
        if any(cuts_all):
          if config.isdata:
            if config.isdataeg or config.isdatamu:
              trig_el = t.EF_e20_medium and config.isdataeg
              trig_mu = t.EF_mu18 and config.isdatamu
            else:
              trig_el = t.EF_e20_medium
              trig_mu = t.EF_mu18
          else:
            trig_el = t.EF_e20_medium
            if config.trgwgt:
              trig_mu = False
              mu_SF = 1.0
              for iMu in mu_idx['signal']:
                  value_array = array('d',[t.mu_staco_pt.at(iMu),t.mu_staco_eta.at(iMu),t.mu_staco_phi.at(iMu),t.mu_staco_ptcone20.at(iMu),float(t.mu_staco_isCombinedMuon.at(iMu) == True)])
                  muon_weight = ROOT.APEvtWeight(ROOT.APEvtWeight.kMuon)
                  muon_weight.AddWeightToEvt(trigWeighter.GetWeight(value_array))
                  mu_SF *= (1-muon_weight.GetWeight() )
                  if verbose: print("Muon SF: %12.6f event %8d muon_pt = %12.6f" %(mu_SF, t.EventNumber, t.mu_staco_pt.at(iMu) ) )
                  wgt['mu'] *= mu_SF
                  trig_mu = True
              wgt['mu'] *= 1 - mu_SF
            else:
              trig_mu = t.EF_mu18
        
        if any(cuts_E) and trig_el: 
            for cutflow in cuts_E: cutflow.passes('Trigger', wgt['el'])
        else:
            for cutflow in cuts_E: cutflow.fails()
        if any(cuts_M) and trig_mu: # mu triggers are simulated by weighting. See above
            for cutflow in cuts_M: cutflow.passes('Trigger', wgt['mu'])
        else:
            for cutflow in cuts_M: cutflow.fails()

        # Jet/MET cleaning cut
        if len(jet_idx['bad']) == 0:
            if any(cuts_E):
                for cutflow in cuts_E: cutflow.passes('Jet/MET cleaning', wgt['el'])
            if any(cuts_M):
                for cutflow in cuts_M: cutflow.passes('Jet/MET cleaning', wgt['mu'])
        else:
            if any(cuts_all) and verbose: print("BadJet: %8d; jet: %2d" %(t.EventNumber, jet_idx['bad'][0]) )
            if config.isdata:
                for cutflow in cuts_all: cutflow.fails()
        # Good primary vertex
        #if susyObjDef.IsGoodVertex(t.vx_nTracks):
        if t.vx_nTracks.at(0) > 4:
            if any(cuts_E):
                for cutflow in cuts_E: cutflow.passes('Good primary vertex', wgt['el'])
            if any(cuts_M):
                for cutflow in cuts_M: cutflow.passes('Good primary vertex', wgt['mu'])
        else:
            if any(cuts_all) and verbose: print("BadVertex: %8d; %1d tracks" %(t.EventNumber, t.vx_nTracks.at(0) ) )
            for cutflow in cuts_all: cutflow.fails()
        # Cosmic muon event veto:
        if len(mu_idx['cosmic']) == 0:
            if any(cuts_E):
                for cutflow in cuts_E: cutflow.passes('Cosmic muon veto', wgt['el'])
            if any(cuts_M):
                for cutflow in cuts_M: cutflow.passes('Cosmic muon veto', wgt['mu'])
        else:
            if any(cuts_all) and verbose: print("CosmicMuon: %d" %t.EventNumber)
            for cutflow in cuts_all: cutflow.fails()

        if not any(cuts_all): continue # If the event has failed up to this point - stop here

        ## Now the dilepton cutflow diverges:
        iL1 = iL2 = lL1 = lL2 = cL1 = cL2 = None  # We'll need these lepton indices later
        ## Check leading lepton (as per trigger) is > 25GeV for electrons and > 20GeV for muons
        if any(cuts_EE):
            if len(mu_idx['signal']) == 0 and len(el_idx['baseline']) == 2:
                iL1 = el_idx['baseline'][0]
                iL2 = el_idx['baseline'][1]
                lL1 = susyObjDef.GetElecTLV(iL1)
                lL2 = susyObjDef.GetElecTLV(iL2)
                cL1 = t.el_charge.at(iL1)
                cL2 = t.el_charge.at(iL2)
                if lL1.Pt() > 25000 or lL2.Pt() > 25000:
                    for cutflow in cuts_EE: cutflow.passes('Dilepton requirement', wgt['el'])
            else:
              for cutflow in cuts_EE: cutflow.fails()

        ## EMU channel with electron trigger. Electron must have 25 GeV
        if any(cuts_DF):
            if len(mu_idx['signal']) == 1 and len(el_idx['baseline']) == 1:
                iL1 = el_idx['baseline'][0]
                iL2 = mu_idx['signal'][0]
                lL1 = susyObjDef.GetElecTLV(iL1)
                lL2 = susyObjDef.GetMuonTLV(iL2)
                cL1 = t.el_charge.at(iL1)
                cL2 = t.mu_staco_charge.at(iL2)
                if any(cuts_EM) and lL1.Pt() > 25000:
                    for cutflow in cuts_EM: cutflow.passes('Dilepton requirement', wgt['el'])
                ## EMU channel with muon trigger. Muon must have 20 GeV
                ## and overlap with electron-triggered events must be removed
                elif any(cuts_ME) and lL2.Pt() > 20000 and (lL1.Pt() < 25000 or not trig_el):
                    for cutflow in cuts_ME: cutflow.passes('Dilepton requirement', wgt['mu'])
                else:
                    for cutflow in cuts_DF: cutflow.fails()
            else:
                for cutflow in cuts_DF: cutflow.fails()

        ## MUMU
        if any(cuts_MM):
            if len(mu_idx['signal']) == 2 and len(el_idx['baseline']) == 0:
                iL1 = mu_idx['signal'][0]
                iL2 = mu_idx['signal'][1]
                lL1 = susyObjDef.GetMuonTLV(iL1)
                lL2 = susyObjDef.GetMuonTLV(iL2)
                cL1 = t.mu_staco_charge.at(iL1)
                cL2 = t.mu_staco_charge.at(iL2)
                if lL1.Pt() > 20000 or lL2.Pt() > 20000:
                    for cutflow in cuts_MM: cutflow.passes('Dilepton requirement', wgt['mu'])
                else:
                    for cutflow in cuts_MM: cutflow.fails()
            else:
                for cutflow in cuts_MM: cutflow.fails()

        # OS and M_ll requirement
        dilepton_mass = 0
        if any(cuts_all):
            dilepton_mass = (lL1 + lL2).M()
            if dilepton_mass < 20000:
                for cutflow in cuts_all: cutflow.fails()
            
            if cL1*cL2 < 0:
                for cutflow in cuts_OSE: cutflow.passes('Lepton signs & M_ll > 20GeV', wgt['el'])
                for cutflow in cuts_OSM: cutflow.passes('Lepton signs & M_ll > 20GeV', wgt['mu'])
            else:
                for cutflow in cuts_OS: cutflow.fails()
            if cL1*cL2 > 0:
                for cutflow in cuts_SSE: cutflow.passes('Lepton signs & M_ll > 20GeV', wgt['el'])
                for cutflow in cuts_SSM: cutflow.passes('Lepton signs & M_ll > 20GeV', wgt['mu'])
            else: 
                for cutflow in cuts_SS: cutflow.fails()

        # Calculate the mT and meff
        if any(cuts_all):
            pt = [lL1.Pt(), lL2.Pt()]
            phi = [lL1.Phi(), lL2.Phi()]
            if pt[1] > pt[0]:
                pt.reverse()
                phi.reverse()
            mT = sqrt(2.*pt[0]*met.Mod()*(1. - cos(ROOT.TVector2.Phi_mpi_pi(phi[0] - met.Phi()))))
            meff = met.Mod() + pt[0] + pt[1]
            for jet in jet_idx['good']:
                meff += susyObjDef.GetJetTLV(jet).Pt()

        if any(cuts_EE):
            if len(el_idx['signal']) == 2 and len(mu_idx['signal']) == 0:
                if verbose: print("SignalEvent: (%6d;%4d;%8d) %2d muons, %2d electrons, M_ll: %8.3f, M_Et: %8.3f, M_Eff: %8.3f OSEE" %(t.RunNumber, t.lbn, t.EventNumber, len(mu_idx['signal']), len(el_idx['baseline']), mDl/1000, met.Mod()/1000, meff/1000) )
                for cutflow in cuts_EE:
                    cutflow.passes('Tight iso electrons', wgt['el'])
            else:
                for cutflow in cuts_EE: cutflow.fails()
        if any(cuts_DF):
            if len(el_idx['signal']) == 1 and len(mu_idx['signal']) == 1:
                if verbose: print("SignalEvent: (%6d;%4d;%8d) %2d muons, %2d electrons, M_ll: %8.3f, M_Et: %8.3f, M_Eff: %8.3f OSEE" %(t.RunNumber, t.lbn, t.EventNumber, len(mu_idx['signal']), len(el_idx['baseline']), mDl/1000, met.Mod()/1000, meff/1000) )
                for cutflow in cuts_DF:
                    cutflow.passes('Tight iso electrons', wgt['el'])
            else:
                for cutflow in cuts_DF: cutflow.fails()
        if any(cuts_MM):
            if verbose: print("SignalEvent: (%6d;%4d;%8d) %2d muons, %2d electrons, M_ll: %8.3f, M_Et: %8.3f, M_Eff: %8.3f OSEE" %(t.RunNumber, t.lbn, t.EventNumber, len(mu_idx['signal']), len(el_idx['baseline']), mDl/1000, met.Mod()/1000, meff/1000) )
            for cutflow in cuts_MM:
                cutflow.passes('Tight iso electrons', wgt['el'])

        if not any(cuts_all): continue

        ## Compute event weight for Monte Carlo when selecting leptons
        ## event weight is computed after overlap removal (could be debated)
        ## Still need to figure out whether noniso muons should also be rescaled ? (they are good combined muons) 
        ## WARNING: Do NOT reweight MC when comparing to new 2011 data
        if not config.isdata:
            lepton_SF = 1.0
            for iEl in el_idx['signal']:
                lepton_SF *= susyObjDef.GetSignalElecSF(t.el_cl_eta.at(iEl),t.el_cl_E.at(iEl)/cosh(t.el_cl_eta.at(iEl)))
            for iMu in mu_idx['signal']:
                lepton_SF *= susyObjDef.GetSignalMuonSF(iMu)
            wgt['el'] *= lepton_SF
            wgt['mu'] *= lepton_SF

        ##
        ## Signal regions:
        ##

        # OS + Jets
        # signal jets pass JVF
        Njets = 0
        for idx in jet_idx['signal']:
            TLV = susyObjDef.GetJetTLV(idx)
            if TLV.Pt() > 30000.:
                Njets += 1

        if Njets >= 2:
            passAny('(OS+Jets)Njet(30,30,30) >= 2', wgt['el'], wgt['mu'])
            NBjets = 0
            if len(jet_idx['btagged']) == 0:
                passAny('(OS+Jets)Bjet-Veto', wgt['el'], wgt['mu'])
                if 80 < dilepton_mass < 100:
                    passAny('(OS+Jets)Zmll-Veto', wgt['el'], wgt['mu'])
                    if met.Mod() > 50000.:
                        passAny('(OS+Jets)MET > 50 GeV', wgt['el'], wgt['mu'])

        Njets = 0
        for idx in jet_idx['signal']:
            TLV = susyObjDef.GetJetTLV(idx)
            if TLV.Pt() > 30000. and TLV.Eta() < 2.8:
                Njets += 1

        if Njets == 0:
            passAny('(OS-JetVeto)Njet(30) < 1', wgt['el'], wgt['mu'])
            if 80 < dilepton_mass < 100:
                passAny('(OS-JetVeto)Zmll-Veto', wgt['el'], wgt['mu'])
                if met.Mod() > 100000.:
                    passAny('(OS-JetVeto)MET > 100 GeV', wgt['el'], wgt['mu'])
                if met.Mod() > 120000.:
                    passAny('(OS-JetVeto)MET > 120 GeV', wgt['el'], wgt['mu'])

        if Njets == 0:
            passAny('(SS-JetVeto)Njet(30) < 1', wgt['el'], wgt['mu'])
            if met.Mod() > 100000.:
                passAny('(SS-JetVeto)MET > 100 GeV', wgt['el'], wgt['mu'])

    for cutflow in cuts_all:
        print("susycutflow_2lep.py: {0:s} cutflow summary".format(cutflow.name))
        for icut,cut in enumerate(cutnames):
            print("{0:2d} {1:35s} {2:15.6f}".format(icut,cut,cutflow.total(cut) ) )

    print("susycutflow_2lep.py: ending", datetime.now() )

if __name__ == '__main__':
    main()
