#!/usr/bin/env python

import os,sys,subprocess,datetime,copy,math,array,shutil,ROOT

__author__ = "Renaud Bruneliere <Renaud.Bruneliere@cern.ch>"
__doc__    = """
Python script used to run on SUSY D3PDs. At the moment it mimics cuts from 2010 1-lepton analysis.
Usage: 
chmod u+x susycutflow_1lep.py
./susycutflow_1lep.py --help
./susycutflow_1lep.py
"""

fdefault = ['/eos/atlas/atlascerngroupdisk/phys-susy/NTUP_SUSY/p832/mc11_7TeV.106484.SU4_herwigpp_susy.merge.NTUP_SUSY.e835_s1310_s1300_r2920_r2900_p832/NTUP_SUSY.608540._000001.root','/castor/cern.ch/atlas/atlascerngroupdisk/phys-susy/D4PD/p60x/user.bruneli.data11_7TeV.00182455.physics_Egamma.merge.NTUP_SUSY.f381_m861_p602_v1/user.bruneli.006870._00001.susy.root','/castor/cern.ch/atlas/atlascerngroupdisk/phys-susy/D4PD/p60x/user.bruneli.data11_7TeV.00182455.physics_Muons.merge.NTUP_SUSY.f381_m861_p602_v1/user.bruneli.006898._00001.susy.root']

def parseCmdLine(args):
    """ Parse input command line to optdict.
    To get the whole list of options type : susycutflow_1lep.py -h"""
    from optparse import OptionParser
    parser = OptionParser()
    parser.add_option("--infile", dest="infile", help="Input file",default='default') 
    parser.add_option("--isdata", dest="isdata", help="Data or Monte Carlo ?",
                      action='store_true', default=False) 
    parser.add_option("--stream", dest="stream", help="Data stream",default='Muons') 
    parser.add_option("--trgwgt", dest="trgwgt", help="Apply a data-driven weight to emulate trigger in MC ?",
                      action='store_true', default=False)
    parser.add_option("--PUwgt", dest="PUwgt", help="Apply pileup reweighting to MC ?",
                      action='store_true', default=False)
    parser.add_option("--JVFwgt", dest="JVFwgt", help="Apply jvf reweighting to MC ?",
                      action='store_true', default=False)
    parser.add_option("--jesup", dest="jesup", help="Rescale jet energy scale by +1 sigma",
                      action='store_true', default=False)
    parser.add_option("--jesdown", dest="jesdown", help="Rescale jet energy scale by -1 sigma",
                      action='store_true', default=False)
    parser.add_option("--jer", dest="jer", help="Smear jet energy scale by 1 sigma",
                      action='store_true', default=False)
    parser.add_option("--nevts", type="int", dest="nevts", help="Maximum number of events to process", default=-1)
    parser.add_option("--PUgen", dest="PUgen", help="Generate pileup reweighting file ?",
                      action='store_true', default=False)
    parser.add_option("--nojetsmear", dest="nojetsmear", help="Switch off the jet smearing",
                      action='store_true', default=False)
    (config, args) = parser.parse_args(args)
    return config

def getinfiles(config):
    """ Get input files from castor directory.
    Remember to never run directly on castor"""
    infile = config.infile
    if config.infile == 'default':
        if config.isdata and config.stream == 'Egamma':
            infile = fdefault[1]
        elif config.isdata and config.stream == 'Muons':
            infile = fdefault[2]
        else:
            infile = fdefault[0]
    ret = subprocess.call('xrdcp root://eosatlas/%s $TMPDIR/' % infile,shell=True)
    if ret != 0: print "getinfiles: could not copy",infile,"\nEXIT"
    newfile = '$TMPDIR/%s' % infile.split('/')[len(infile.split('/'))-1]
    return newfile

## Recommended trigger chains can be found on:
## https://twiki.cern.ch/twiki/bin/view/AtlasProtected/SusyObjectDefinitionsr17#Trigger
## For MC, two menus were used for mc11b:
## https://atlas-trigconf.cern.ch/mc/smkey/310/l1key/139/hltkey/252/ and
## https://atlas-trigconf.cern.ch/mc/smkey/308/l1key/134/hltkey/246/
## with the following setup
## {180164:"MCRECO:DB:TRIGGERDBMC:308,134,246",183003:"MCRECO:DB:TRIGGERDBMC:308,134,246",186169:"MCRECO:DB:TRIGGERDBMC:308,134,246",189751:"MCRECO:DB:TRIGGERDBMC:310,139,252"}
def getElTriggerSetup(RunNumber,isdata):
    lname = [['EF_e20_medium'],10]
    if RunNumber >= 188902: # period K or MC for latest Cond period
        lname = [['EF_e22vh_medium1','EF_e45_medium1'],18]
    elif RunNumber >= 186873 and isdata: # period L-M
        lname = [['EF_e22_medium'],14]
    return lname

def getMuTriggerSetup(RunNumber,isdata):
    lname = ['EF_mu18']
    if RunNumber >= 186516 and isdata: # period >= J
        lname = ['EF_mu18_L1J10']
    return lname

def main():
    print "susycutflow_1lep.py: starting",datetime.datetime.now()
    config = parseCmdLine(sys.argv[1:])

    ## Read input file
    infile = config.infile
    if '/castor/cern.ch' in config.infile or config.infile == 'default': infile = getinfiles(config)
    t = ROOT.TChain("susy")
    t.Add(infile)

    ## Fixes for vectors
    ROOT.gInterpreter.GenerateDictionary("vector<vector<float> >","vector")
    ROOT.gInterpreter.GenerateDictionary("vector<vector<int> >","vector")
    ROOT.gInterpreter.GenerateDictionary("vector<vector<unsigned int> >","vector")

    ## Load RootCore libs
    if os.path.exists("%s/preload" % os.environ['ROOTCOREDIR']):
        fpreload = open("%s/preload" % os.environ['ROOTCOREDIR'],"r")
        for line in fpreload:
            line = line.split('\n')[0]
            if line == "": continue
            ROOT.gSystem.Load(line)
    for libname in os.listdir("%s/lib/" % os.environ['ROOTCOREDIR']):
        if not (libname.startswith("lib") and libname.endswith(".so")): continue
        ROOT.gSystem.Load("%s/lib/%s" % (os.environ['ROOTCOREDIR'],libname))

    ## Initialize tools
    susyObjDef = ROOT.SUSYObjDef()
    susyObjDef.initialize()
    fakeMetEst = ROOT.FakeMetEstimator()
    fakeMetEst.initialize("../data/fest_periodF_v1.root")
    have_grl = False
    if config.isdata and os.path.exists("%s/lib/libGoodRunsLists.so" % os.environ['ROOTCOREDIR']):
        have_grl = True
        grl_reader = ROOT.Root.TGoodRunsListReader('data11_7TeV.periodAllYear_DetStatus-v36-pro10_CoolRunQuery-00-04-08_Susy.xml')
        grl_reader.AddXMLFile("data11_7TeV.periodAllYear_DetStatus-v36-pro10_CoolRunQuery-00-04-08_Susy.xml");
        grl_reader.Interpret()
        goodrunslist = grl_reader.GetMergedGRLCollection()
        goodrunslist.Summary(True) # Print out a list of all good runs and lbns
    have_pileuptool = False
    if config.PUgen and os.path.exists("%s/lib/libPileupReweighting.so" % os.environ['ROOTCOREDIR']):
        genPileUpTool = ROOT.Root.TPileupReweighting("genPileUpTool")
        genPileUpTool.UsePeriodConfig("MC11b")
        genPileUpTool.Initialize()
    if config.PUwgt and os.path.exists("%s/lib/libPileupReweighting.so" % os.environ['ROOTCOREDIR']):
        have_pileuptool = True
        elPileUpTool = ROOT.Root.TPileupReweighting("elPileUpTool")
        if os.path.isfile("../data/mc11b_generated.root"):
            print "using generated PU file for electrons"
            elPileUpTool.AddConfigFile("../data/mc11b_generated.root")
        else:
            print "using default PU file for electrons"
            elPileUpTool.AddConfigFile("../../PileupReweighting/share/mc11b_defaults.prw.root")
        elPileUpTool.AddLumiCalcFile("../data/susy_1Electron_avgintperbx.root")
        elPileUpTool.SetUnrepresentedDataAction(2) # Action needs investigation
        #elPileUpTool.SetDataScaleFactors(0.9) # You can apply this command by default or to study pileup unc.
        tool_failure = elPileUpTool.Initialize()
        if tool_failure: print("El PileUpTool failed to initialise with code: %d" %tool_failure)
        muPileUpTool = ROOT.Root.TPileupReweighting("muPileUpTool")
        if os.path.isfile("../data/mc11b_generated.root"):
            print "using generated PU file for muons"
            muPileUpTool.AddConfigFile("../data/mc11b_generated.root")
        else:
            print "using default PU file for muons"
            muPileUpTool.AddConfigFile("../../PileupReweighting/share/mc11b_defaults.prw.root")
        muPileUpTool.AddLumiCalcFile("../data/susy_1Muon_avgintperbx.root")            
        muPileUpTool.SetUnrepresentedDataAction(2) # Action needs investigation
        #muPileUpTool.SetDataScaleFactors(0.9) # You can apply this command by default or to study pileup unc.
        tool_failure = muPileUpTool.Initialize()
        if tool_failure: print("Mu PileUpTool failed to initialise with code: %d" %tool_failure)
        #print("Pileup weights:")
        #for i in range(25):
        #    print("weight(mu = %4.1f) = %13.10f(EL) %13.10f(MU)" %(float(i), elPileUpTool.getPileupWeight(i), muPileUpTool.getPileupWeight(i) ) )

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
    cuts = [[0,0,0,'No cut'],
            [0,0,0,'GRL'],
            [0,0,0,'Trigger'],
            [0,0,0,'Jet/MET Cleaning'],
            [0,0,0,'LAr hole veto'],
            [0,0,0,'Primary vertex cut'],
            #[0,0,0,'Electron crack removal'], Obsolete for 2011 analysis
            [0,0,0,'Cosmic or Bad muon veto'],
            [0,0,0,'Lepton cut'],
            [0,0,0,'>=1 jet pT>100 GeV'],
            [0,0,0,'==3 jets pT>25 GeV'],
            [0,0,0,'MET > 250 GeV'],
            [0,0,0,'mT > 100 GeV'],
            [0,0,0,'MET > 0.3 Meff'],
            [0,0,0,'Meff > 1200 GeV'],
            ]
    elcuts = copy.deepcopy(cuts)
    mucuts = copy.deepcopy(cuts)
    nevts_LArHole = [[0.,0.],[0.,0.]]
    for iEvt in range(nEvts):
        if nEvts < 10 or iEvt%(nEvts/10) == 0: print "Reading event",iEvt,"/",nEvts
        t.GetEntry(iEvt)

        ## If generating pileup MC file don't need to run cutflow
        if config.PUgen:
            genPileUpTool.Fill(t.RunNumber,t.mc_channel_number,t.mcevt_weight[0][0],t.averageIntPerXing)
            continue

        ## Do not forget to clear arrays once per event
        susyObjDef.Reset()

        ##
        ## PART-1 Object selection
        ##

        ## Prior to any selection, smear jets in MC
        ## WARNING: vector content is modified !!!
        if (not config.nojetsmear) and (not config.isdata)  :
            susyObjDef.SmearJets(t.jet_AntiKt4TopoNewEM_pt,
				 t.jet_AntiKt4TopoNewEM_eta,
				 t.jet_AntiKt4TopoNewEM_phi,
				 t.jet_AntiKt4TopoNewEM_E)

        ##
        ## Get electrons
        ##
        el_idx = {'signal':[],'baseline':[],'crack':[],'trgmatch':[],'met':ROOT.std.vector(int)()}
        elTrgSetup = getElTriggerSetup(t.RunNumber,config.isdata)
        elTrigCond = False
        itrig = 0
        for itrg,trgName in enumerate(elTrgSetup[0]):
            elTrigCond = elTrigCond or getattr(t,trgName)
        elTrigSet = elTrgSetup[1]

        for iEl in range(t.el_n):
            # Check if offline electron is matched to an EF electron trigger object
            # Be careful, D3PD variables depend on trigger chain used (=> different for various data run nb or mc)
            # Trigger matching is described on https://twiki.cern.ch/twiki/bin/view/AtlasProtected/EgammaTriggerMatching
            EFindex = ROOT.Long(-1)
            for itrg,trgName in enumerate(elTrgSetup[0]):
                trig_EF_el_EF = getattr(t,'trig_EF_el_'+trgName)
                if ROOT.PassedTriggerEF(t.el_tracketa.at(iEl),t.el_trackphi.at(iEl),trig_EF_el_EF,
                                        EFindex,t.trig_EF_el_n,t.trig_EF_el_eta,t.trig_EF_el_phi):
                    el_idx['trgmatch'].append(iEl)
                    break

            # Apply baseline SUSY electron selection 
            myRunNb = 180614 # This setup is obsolete and harmless cause checkOQ is no more used
            if t.el_MET_Simplified20_wpx.at(iEl).at(0) != 0. and not t.el_medium.at(iEl):
                print t.el_medium.at(iEl),t.el_MET_Simplified20_wpx.at(iEl).at(0)
            if susyObjDef.IsElectron(iEl,myRunNb,
                                     t.el_cl_eta.at(iEl),t.el_cl_phi.at(iEl),t.el_cl_E.at(iEl),
                                     t.el_tracketa.at(iEl),t.el_trackphi.at(iEl),
                                     t.el_author.at(iEl),t.el_mediumPP.at(iEl),t.el_OQ.at(iEl),
                                     t.el_nPixHits.at(iEl),t.el_nSCTHits.at(iEl),
                                     t.el_MET_Simplified20_wet.at(iEl).at(0),config.isdata,10000.):
                el_idx['baseline'].append(iEl)
                # Check whether a baseline electron is within crack region
                if susyObjDef.IsInCrack(t.el_cl_eta.at(iEl)):
                    el_idx['crack'].append(iEl)
                # Apply additionnal cuts for signal electrons 
                # lepton pt cut is raised to 25 GeV to match e20_medium trigger
                if susyObjDef.IsSignalElectron(iEl,t.el_tightPP.at(iEl),t.el_ptcone20.at(iEl),25000.):
                    el_idx['signal'].append(iEl)
            if t.el_MET_Simplified20_wet.at(iEl).at(0) != 0.:
                el_idx['met'].push_back(iEl)


        ##
        ## Get muons
        ##
        mu_idx = {'signal':[],'baseline':[],'cosmic':[],'bad':[],'trgmatch':[],'met':ROOT.std.vector(int)()}
        muTrgSetup = getMuTriggerSetup(t.RunNumber,config.isdata)
        muTrigCond = False
        for trgName in muTrgSetup:
            muTrigCond = muTrigCond or getattr(t,trgName)
        trig_EF_trigmuonef_signature = getattr(t,'trig_EF_trigmuonef_'+muTrgSetup[0])
        for iMu in range(t.mu_staco_n):
            # Check if offline muon is matched to a muon trigger object
            EFindex = ROOT.Long(-1)
            EFtrackindex = ROOT.Long(-1)
            if susyObjDef.MuonHasTriggerMatch(t.mu_staco_eta.at(iMu),t.mu_staco_phi.at(iMu),
                                              trig_EF_trigmuonef_signature,EFindex,EFtrackindex,
                                              t.trig_EF_trigmuonef_n,t.trig_EF_trigmuonef_track_CB_eta,
                                              t.trig_EF_trigmuonef_track_CB_phi,t.trig_EF_trigmuonef_track_CB_hasCB):
                mu_idx['trgmatch'].append(iMu)

            # Baseline muon selection does not include any isolation cut => directly used in Etmiss computation
            if susyObjDef.IsMuon(iMu,t.mu_staco_pt.at(iMu),t.mu_staco_eta.at(iMu),t.mu_staco_phi.at(iMu),
                                 t.mu_staco_E.at(iMu),
                                 t.mu_staco_me_qoverp_exPV.at(iMu),t.mu_staco_id_qoverp_exPV.at(iMu),
                                 t.mu_staco_me_theta_exPV.at(iMu),t.mu_staco_id_theta_exPV.at(iMu),
                                 t.mu_staco_id_theta.at(iMu),
                                 t.mu_staco_isCombinedMuon.at(iMu),t.mu_staco_isSegmentTaggedMuon.at(iMu),
                                 t.mu_staco_loose.at(iMu),
                                 t.mu_staco_expectBLayerHit.at(iMu),t.mu_staco_nBLHits.at(iMu),
                                 t.mu_staco_nPixHits.at(iMu),t.mu_staco_nPixelDeadSensors.at(iMu),
                                 t.mu_staco_nPixHoles.at(iMu),t.mu_staco_nSCTHits.at(iMu),
                                 t.mu_staco_nSCTDeadSensors.at(iMu),t.mu_staco_nSCTHoles.at(iMu),
                                 t.mu_staco_nTRTHits.at(iMu),t.mu_staco_nTRTOutliers.at(iMu),
                                 config.isdata,10000.,2.4):
                mu_idx['met'].push_back(iMu)
                mu_idx['baseline'].append(iMu)
                # Additionnal cut for signal muons: check whether it also pass isolation cut and if pT>20 GeV
                if susyObjDef.IsSignalMuon(iMu,t.mu_staco_ptcone20.at(iMu)): 
                    mu_idx['signal'].append(iMu)
                # Check whether muon could be a cosmic candidate
                if susyObjDef.IsCosmicMuon(t.mu_staco_z0_exPV.at(iMu),t.mu_staco_d0_exPV.at(iMu),5.,2.):
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
            ## Basic LAr hole veto applies to any jet (before overlap removal)
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
            local_truth_flavor = 0
            if not config.isdata:
                local_truth_flavor = t.jet_AntiKt4TopoNewEM_flavor_truth_label.at(iJet)
                
            if susyObjDef.IsJet(iJet,t.jet_AntiKt4TopoNewEM_pt.at(iJet),t.jet_AntiKt4TopoNewEM_eta.at(iJet),
                                t.jet_AntiKt4TopoNewEM_phi.at(iJet),t.jet_AntiKt4TopoNewEM_E.at(iJet),
                                t.jet_AntiKt4TopoNewEM_emscale_eta.at(iJet),
                                t.jet_AntiKt4TopoNewEM_emfrac.at(iJet),t.jet_AntiKt4TopoNewEM_hecf.at(iJet),
                                t.jet_AntiKt4TopoNewEM_LArQuality.at(iJet),t.jet_AntiKt4TopoNewEM_HECQuality.at(iJet),
                                t.jet_AntiKt4TopoNewEM_AverageLArQF.at(iJet),
                                t.jet_AntiKt4TopoNewEM_Timing.at(iJet),t.jet_AntiKt4TopoNewEM_sumPtTrk.at(iJet),
                                t.jet_AntiKt4TopoNewEM_fracSamplingMax.at(iJet),
                                t.jet_AntiKt4TopoNewEM_NegativeE.at(iJet),
                                local_truth_flavor,
                                config.isdata,20000.,10.,ROOT.JetID.VeryLooseBad,whichsyste,config.nojetsmear):
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
            elif isgoodjet and math.fabs(susyObjDef.GetJetTLV(iJet).Eta()) < 2.8:
                jet_idx['goodpt'].append(susyObjDef.GetJetTLV(iJet).Pt())
                jet_idx['good'].append(iJet)
              
        ## Apply descendent pT sorting of jets
        ptandidx = zip(jet_idx['goodpt'],jet_idx['good'])
        ptandidx.sort(reverse=True)
        del jet_idx['good'][:],jet_idx['goodpt'][:]
        jet_idx['good']   = [ x[1] for x in ptandidx ]
        jet_idx['goodpt'] = [ x[0] for x in ptandidx ]

        ## Additonnal eta and JVF requirements used in 1-lepton analysis to define "signal" jets
        ## Those cuts are necessary to reduce pileup jets
        jvfWeightEle = 1.
        jvfWeightMuo = 1.
        for iJet in jet_idx['good']:
            passJVF = t.jet_AntiKt4TopoNewEM_jvtxf.at(iJet) > 0.75
            if config.JVFwgt and t.jet_AntiKt4TopoNewEM_pt.at(iJet) > 25000.:
                jvfWeightEle *= jvfReweightingEle.getJVFWeight(passJVF)
                jvfWeightMuo *= jvfReweightingMuo.getJVFWeight(passJVF)
            if math.fabs(t.jet_AntiKt4TopoNewEM_eta.at(iJet)) < 2.5 and passJVF:
                jet_idx['signal'].append(iJet)
        
        ## Check if one of 3 leading jets (pt>25GeV, |eta|<2.5) is tagged as b-jet
        if not config.isdata:
            pt_btag = ROOT.std.vector(float)()
            eta_btag = ROOT.std.vector(float)()
            val_btag = ROOT.std.vector(float)()
            pdgid_btag = ROOT.std.vector(int)()
        for idx,iJet in enumerate(jet_idx['signal']):
            if idx > 2: break
            if math.fabs(t.jet_AntiKt4TopoNewEM_eta.at(iJet)) < 2.5 and t.jet_AntiKt4TopoNewEM_pt.at(iJet) > 25000.:
                if susyObjDef.IsBJet(t.jet_AntiKt4TopoNewEM_flavor_weight_JetFitterCOMBNN.at(iJet),"JetFitterCOMBNN"):
                    jet_idx['btagged'].append(iJet)
                ## Fill information to compute b-tagging weight
                if not config.isdata:
                    pt_btag.push_back(t.jet_AntiKt4TopoNewEM_pt.at(iJet))
                    eta_btag.push_back(t.jet_AntiKt4TopoNewEM_eta.at(iJet))
                    val_btag.push_back(t.jet_AntiKt4TopoNewEM_flavor_weight_JetFitterCOMBNN.at(iJet))
                    pdgid_btag.push_back(t.jet_AntiKt4TopoNewEM_flavor_truth_label.at(iJet))
          
        # r17 working points and b-tagging scaling factors are documented on:
        # https://twiki.cern.ch/twiki/bin/view/AtlasProtected/Analysis17
        # This is just an example on how to compute b-tagging weights but it is not used later in this pg
        if not config.isdata and pt_btag.size() > 0:
            wgtbtag = ROOT.BTagCalib.BTagCalibrationFunction(pt_btag,eta_btag,val_btag,pdgid_btag,0,"JetFitterCOMBNN","1_80",1.8,'../data/BTagCalibration.env','../data/')
            #print t.EventNumber,'number of b-tagged jets',len(jet_idx['btagged']),'weight =',wgtbtag.first,pt_btag.size()

        ##
        ## Compute simplified refined Etmiss 
        ##
        ## (make use of el_idx['met'] and mu_idx['met'] which contain list of electrons/muons to be included in Etmiss)
        met = susyObjDef.GetMET(t.jet_AntiKt4TopoNewEM_pt,
                                t.jet_AntiKt4TopoNewEM_eta,
                                t.jet_AntiKt4TopoNewEM_phi,
                                t.jet_AntiKt4TopoNewEM_E,
                                t.jet_AntiKt4TopoNewEM_MET_Simplified20_wet,
                                t.jet_AntiKt4TopoNewEM_MET_Simplified20_wpx,
                                t.jet_AntiKt4TopoNewEM_MET_Simplified20_wpy,
                                t.jet_AntiKt4TopoNewEM_MET_Simplified20_statusWord,
                                el_idx['met'],
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
        ## Apply lepton veto (done on every jet !)
        ##
        for iJet in jet_idx['good']:
            mylist = copy.deepcopy(el_idx['baseline'])
            for iEl in mylist:
                if susyObjDef.GetElecTLV(iEl).DeltaR(susyObjDef.GetJetTLV(iJet)) > 0.4: continue
                el_idx['baseline'].remove(iEl)
                if iEl in el_idx['signal']: el_idx['signal'].remove(iEl)
            mylist = copy.deepcopy(mu_idx['baseline'])
            for iMu in mylist:
                if susyObjDef.GetMuonTLV(iMu).DeltaR(susyObjDef.GetJetTLV(iJet)) > 0.4: continue
                mu_idx['baseline'].remove(iMu)
                if iMu in mu_idx['cosmic']: mu_idx['cosmic'].remove(iMu) # Check cosmic cut only if sufficiently away from a jet
                if iMu in mu_idx['signal']: mu_idx['signal'].remove(iMu)

        ##
        ## LAr hole veto
        ##
        ## Basic veto: done above while filling jets
        if len(jet_idx['LArHoleVeto']): nevts_LArHole[0][0] += 1
        ## Smarter veto: compute the fake MET estimator based on BCH_CORR variables
        fakeMetEst_jet_idx = []
        for iJet in range(t.jet_AntiKt4TopoNewEM_n):
            if t.jet_AntiKt4TopoNewEM_pt.at(iJet) <= 20000.: continue # Keep only jets with pT > 20 GeV
            ispass = susyObjDef.IsLArHole(t.jet_AntiKt4TopoNewEM_eta.at(iJet),t.jet_AntiKt4TopoNewEM_phi.at(iJet))
            if not ispass: continue
            ## With mc11(a/b) we can use the same method for both data and mc 
            #if config.isdata:
            ispass = ispass and fakeMetEst.isBad(t.jet_AntiKt4TopoNewEM_pt.at(iJet),
                                  t.jet_AntiKt4TopoNewEM_BCH_CORR_JET.at(iJet),
                                  t.jet_AntiKt4TopoNewEM_BCH_CORR_CELL.at(iJet),
                                  t.jet_AntiKt4TopoNewEM_BCH_CORR_DOTX.at(iJet),
                                  t.jet_AntiKt4TopoNewEM_phi.at(iJet),met.Px(),met.Py(),10000.,10.,-1.,-1.)
            #else:
            #    ispass = ispass and fakeMetEst.isBadEmul(t.jet_AntiKt4TopoNewEM_pt.at(iJet),
            #                          t.jet_AntiKt4TopoNewEM_eta.at(iJet),
            #                          t.jet_AntiKt4TopoNewEM_phi.at(iJet),met.Px(),met.Py(),
            #                          t.jet_AntiKt4TopoNewEM_BCH_CORR_JET.at(iJet),
            #                          t.jet_AntiKt4TopoNewEM_BCH_CORR_CELL.at(iJet),
            #                          t.jet_AntiKt4TopoNewEM_BCH_CORR_DOTX.at(iJet),10000.,10.,-1.,-1.)
            if not ispass: continue
            fakeMetEst_jet_idx.append(iJet)
        if len(fakeMetEst_jet_idx): nevts_LArHole[0][1] += 1 

        ##
        ## PART-2 Event selection - do it only for 1-lepton + 3 jets loose channel
        ##
        icut = 0
        wgt = [1.,1.] # el,mu channels respectively

        # No extra period weight with new pileup reweighting
        puwgt = [1.,1.] # el,mu channels respectively
        passel = True
        passmu = True
        if not config.isdata and config.PUwgt and have_pileuptool:
            puwgt[0] *= elPileUpTool.GetCombinedWeight(t.RunNumber,t.mc_channel_number,t.averageIntPerXing)
            puwgt[1] *= muPileUpTool.GetCombinedWeight(t.RunNumber,t.mc_channel_number,t.averageIntPerXing)
        elcuts[icut][0] += 1 
        mucuts[icut][0] += 1
        elcuts[icut][1] += wgt[0]
        mucuts[icut][1] += wgt[1]
        elcuts[icut][2] += wgt[0]*puwgt[0] 
        mucuts[icut][2] += wgt[1]*puwgt[1]
        icut += 1

        # Apply GRL selection if we loaded the reader OK
        if not have_grl or not config.isdata or goodrunslist.HasRunLumiBlock(t.RunNumber, t.lbn):
            elcuts[icut][0] += 1 
            mucuts[icut][0] += 1
            elcuts[icut][1] += wgt[0]
            mucuts[icut][1] += wgt[1]
            elcuts[icut][2] += wgt[0]*puwgt[0] 
            mucuts[icut][2] += wgt[1]*puwgt[1]
        else:
            passel = passmu = False
        icut += 1

        # Trigger
        if not config.isdata: # MC treatment, do reweighting or apply scale factors
            if passel and elTrigCond: 
                if len(el_idx['baseline']):
                    elidx = el_idx['baseline'][0]
                    wgt[0] = wgt[0] * susyObjDef.GetTrigElecSF(t.el_cl_eta.at(elidx),t.el_cl_E.at(elidx)/math.cosh(t.el_tracketa.at(elidx)),elTrigSet)
                elcuts[icut][0] += 1 
                elcuts[icut][1] += wgt[0]
                elcuts[icut][2] += wgt[0]*puwgt[0] 
            else:
                passel = False
            if passmu and config.trgwgt and len(mu_idx['baseline']):
                muidx = mu_idx['baseline'][0]
                value_array = array.array('d',[t.mu_staco_pt.at(muidx),t.mu_staco_eta.at(muidx),t.mu_staco_phi.at(muidx),t.mu_staco_ptcone20.at(muidx),float(t.mu_staco_isCombinedMuon.at(muidx) == True)])
                weight_muon = ROOT.APEvtWeight(ROOT.APEvtWeight.kMuon)
                weight_muon.AddWeightToEvt(trigWeighter.GetWeight(value_array))
                wgt[1] *= weight_muon.GetWeight()
                mucuts[icut][0] += 1
                mucuts[icut][1] += wgt[1]
                mucuts[icut][2] += wgt[1]*puwgt[1]
            elif passmu and not config.trgwgt and muTrigCond:
                if len(mu_idx['trgmatch']):
                    if len(mu_idx['baseline']) and mu_idx['baseline'][0] in mu_idx['trgmatch']:
                        muidx = mu_idx['baseline'][0]
                    else:
                        muidx = mu_idx['trgmatch'][0]
                    wgt[1] = wgt[1] * muTrgSFTool.GetScaleFactor(t.mu_staco_eta.at(muidx),t.mu_staco_phi.at(muidx),
                                                                 t.mu_staco_pt.at(muidx)/1000.) # pt is in GeV
                mucuts[icut][0] += 1
                mucuts[icut][1] += wgt[1]
                mucuts[icut][2] += wgt[1]*puwgt[1]
            else:
                passmu = False
        else: # Data
            if passel and elTrigCond:
                elcuts[icut][0] += 1 
                elcuts[icut][1] += wgt[0]
                elcuts[icut][2] += wgt[0]*puwgt[0] 
            else: passel = False
            if passmu and muTrigCond:
                mucuts[icut][0] += 1
                mucuts[icut][1] += wgt[1]
                mucuts[icut][2] += wgt[1]*puwgt[1]
            else: passmu = False
        icut += 1

        # Jet/MET cleaning cut
        # larError check is only applied to data
        if len(jet_idx['bad']) == 0 and (not config.isdata or t.larError == 0):
            if passel:
                elcuts[icut][0] += 1 
                elcuts[icut][1] += wgt[0]
                elcuts[icut][2] += wgt[0]*puwgt[0] 
            if passmu:
                mucuts[icut][0] += 1
                mucuts[icut][1] += wgt[1]
                mucuts[icut][2] += wgt[1]*puwgt[1]
        else:
            passel = passmu = False
        icut += 1

        # LAr hole veto based on smart veto
        if len(fakeMetEst_jet_idx) == 0:
            if passel:
                elcuts[icut][0] += 1 
                elcuts[icut][1] += wgt[0]
                elcuts[icut][2] += wgt[0]*puwgt[0] 
            if passmu:
                mucuts[icut][0] += 1
                mucuts[icut][1] += wgt[1]
                mucuts[icut][2] += wgt[1]*puwgt[1]
        else:
            passel = passmu = False
        icut += 1

        # Good primary vertex
        if susyObjDef.IsGoodVertex(t.vx_nTracks):
            if passel:
                elcuts[icut][0] += 1 
                elcuts[icut][1] += wgt[0]
                elcuts[icut][2] += wgt[0]*puwgt[0] 
            if passmu:
                mucuts[icut][0] += 1
                mucuts[icut][1] += wgt[1]
                mucuts[icut][2] += wgt[1]*puwgt[1]
        else:
            passel = passmu = False
        icut += 1

        # Electron crack removal (obsolete)
        #if len(el_idx['crack']) == 0:
        #    if passel: elcuts[icut][0] += wgt[0]
        #    if passmu: mucuts[icut][0] += wgt[1]
        #else:
        #    passel = passmu = False
        #icut += 1

        # Cosmic or Bad muon veto
        if len(mu_idx['cosmic']) == 0 and len(mu_idx['bad']) == 0:
            if passel:
                elcuts[icut][0] += 1 
                elcuts[icut][1] += wgt[0]
                elcuts[icut][2] += wgt[0]*puwgt[0] 
            if passmu:
                mucuts[icut][0] += 1
                mucuts[icut][1] += wgt[1]
                mucuts[icut][2] += wgt[1]*puwgt[1]
        else:
            passel = passmu = False
        icut += 1

        # Lepton cut
        #
        # Compute event weight for Monte Carlo when selecting leptons
        # event weight is computed after overlap removal (could be debated)
        # Still need to figure out whether noniso muons should also be rescaled ? (they are good muons) 
        if not config.isdata:
            for iEl in el_idx['signal']:
                wgt[0] *= susyObjDef.GetSignalElecSF(t.el_cl_eta.at(iEl),t.el_cl_E.at(iEl)/math.cosh(t.el_tracketa.at(iEl)))
            for iMu in mu_idx['signal']:
                wgt[1] *= susyObjDef.GetSignalMuonSF(iMu)
        passel = passel and len(el_idx['signal']) == 1 and len(mu_idx['baseline']) == 0 and len(el_idx['baseline']) == 1
        # For electron, request also that the selected offline electron is matching the electron trigger object
        # Since for MC, SF are used, do the matching both on data and MC
        passel = passel and len(el_idx['trgmatch']) and (el_idx['signal'][0] in el_idx['trgmatch'])
        if passel:
            elcuts[icut][0] += 1 
            elcuts[icut][1] += wgt[0]
            elcuts[icut][2] += wgt[0]*puwgt[0] 
        passmu = passmu and len(mu_idx['signal']) == 1 and len(mu_idx['baseline']) == 1 and len(el_idx['baseline']) == 0
        # For muon, request also that the selected offline muon is matching the muon trigger object
        if config.isdata or not config.trgwgt: 
            passmu = passmu and len(mu_idx['trgmatch']) and (mu_idx['signal'][0] in mu_idx['trgmatch'])
        if passmu:
            mucuts[icut][0] += 1
            mucuts[icut][1] += wgt[1]
            mucuts[icut][2] += wgt[1]*puwgt[1]
        icut += 1

        # Check leading jet pT > 100 GeV
        if len(jet_idx['signal']) and susyObjDef.GetJetTLV(jet_idx['signal'][0]).Pt() > 100000.:
            if passel:
                elcuts[icut][0] += 1 
                elcuts[icut][1] += wgt[0]
                elcuts[icut][2] += wgt[0]*puwgt[0] 
            if passmu:
                mucuts[icut][0] += 1
                mucuts[icut][1] += wgt[1]
                mucuts[icut][2] += wgt[1]*puwgt[1]
        else:
            passel = passmu = False
        icut += 1

        # Check if there are >= 3 jets pT > 25 GeV (3 jets signal region + 4th jet veto if pT(4th) > 80 GeV)
        if len(jet_idx['signal']) >= 3 and susyObjDef.GetJetTLV(jet_idx['signal'][2]).Pt() > 25000. and (len(jet_idx['signal']) == 3 or susyObjDef.GetJetTLV(jet_idx['signal'][3]).Pt() <= 80000.):
            if passel:
                elcuts[icut][0] += 1 
                elcuts[icut][1] += wgt[0]
                elcuts[icut][2] += wgt[0]*puwgt[0] 
            if passmu:
                mucuts[icut][0] += 1
                mucuts[icut][1] += wgt[1]
                mucuts[icut][2] += wgt[1]*puwgt[1]
        else:
            passel = passmu = False
        icut += 1

        # MET cut

        if met.Mod() > 250000.:
            if passel:
                elcuts[icut][0] += 1 
                elcuts[icut][1] += wgt[0]
                elcuts[icut][2] += wgt[0]*puwgt[0] 
            if passmu:
                mucuts[icut][0] += 1
                mucuts[icut][1] += wgt[1]
                mucuts[icut][2] += wgt[1]*puwgt[1]
        else:
            passel = passmu = False
        icut += 1
        meff = met.Mod()

        # mT cut
        if passel:
            elpt  = susyObjDef.GetElecTLV(el_idx['signal'][0]).Pt()
            elphi = susyObjDef.GetElecTLV(el_idx['signal'][0]).Phi()
            mT = math.sqrt(2.*elpt*met.Mod()*(1. - math.cos(ROOT.TVector2.Phi_mpi_pi(elphi-met.Phi()))))
            meff += elpt
            if mT > 100000.:
                elcuts[icut][0] += 1 
                elcuts[icut][1] += wgt[0]
                elcuts[icut][2] += wgt[0]*puwgt[0] 
            else:
                passel = False
        if passmu:
            mupt  = susyObjDef.GetMuonTLV(mu_idx['signal'][0]).Pt()
            muphi = susyObjDef.GetMuonTLV(mu_idx['signal'][0]).Phi()
            mT = math.sqrt(2.*mupt*met.Mod()*(1. - math.cos(ROOT.TVector2.Phi_mpi_pi(muphi-met.Phi()))))
            meff += mupt
            if mT > 100000.:
                mucuts[icut][0] += 1
                mucuts[icut][1] += wgt[1]
                mucuts[icut][2] += wgt[1]*puwgt[1]
            else:
                passmu = False
        icut += 1

        # MET > 0.3*Meff
        if passel or passmu:
            for iJet in range(3):
                meff += susyObjDef.GetJetTLV(jet_idx['signal'][iJet]).Pt()
        if met.Mod() > 0.3*meff:
            if passel:
                elcuts[icut][0] += 1 
                elcuts[icut][1] += wgt[0]
                elcuts[icut][2] += wgt[0]*puwgt[0] 
            if passmu:
                mucuts[icut][0] += 1
                mucuts[icut][1] += wgt[1]
                mucuts[icut][2] += wgt[1]*puwgt[1]
        else:
            passel = passmu = False
        icut += 1

        # Meff > 1200000
        if meff > 1200000.:
            if passel:
                elcuts[icut][0] += 1 
                elcuts[icut][1] += wgt[0]
                elcuts[icut][2] += wgt[0]*puwgt[0] 
            if passmu:
                mucuts[icut][0] += 1
                mucuts[icut][1] += wgt[1]
                mucuts[icut][2] += wgt[1]*puwgt[1]
        else:
            passel = passmu = False
    if not config.PUwgt: print "WARNING: pileup reweighting is off ! To run with it: ./susycutflow_1lep.py --PUwgt"
    print "susycutflow_1lep.py: electron cutflow summary"
    print "%2s %25s %8s %8s %8s" % ("","Cut name","Entries","Evts","Evts(PU)")
    for icut,cut in enumerate(elcuts):
        print "%2d %25s %8d %8.2f %8.2f" % (icut,cut[3],cut[0],cut[1],cut[2])
    print "susycutflow_1lep.py: muon cutflow summary"
    print "%2s %25s %8s %8s %8s" % ("","Cut name","Entries","Evts","Evts(PU)")
    for icut,cut in enumerate(mucuts):
        print "%2d %25s %8d %8.2f %8.2f" % (icut,cut[3],cut[0],cut[1],cut[2])
    print "susycutflow_1lep.py: ending",datetime.datetime.now()

    if config.PUgen: genPileUpTool.WriteToFile("../data/mc11b_generated.root")
    susyObjDef.finalize()


if __name__ == '__main__':
    main()
