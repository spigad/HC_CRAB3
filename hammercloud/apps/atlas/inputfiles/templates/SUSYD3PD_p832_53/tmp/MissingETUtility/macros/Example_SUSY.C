#define Example_cxx
#include "Example.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "../MissingETUtility/METUtility.h"

#include "TLorentzVector.h"

#include "JetUncertainties/JESUncertaintyProvider.h"
#include "JetResolution/JERProvider.h"
#include "egammaAnalysisUtils/EnergyRescaler.h"
#include "MuonMomentumCorrections/SmearingClass.h"

void Example::Loop(int nfirst, int Nentries)
{

  //start of loop/ntuple stuff
  if (fChain == 0) return;

  if(Nentries<0) Nentries = fChain->GetEntries();
  
  bool verbose = true;

  dataout = new TFile("METUtil_test_SUSY.root","RECREATE");

  h_refFinal_D3PD    = new TH1D("h_refFinal_D3PD","RefFinal from D3PD;E_{T}^{miss} [GeV]; Events / 5 GeV",50,0,250);
  h_refFinal_METUtil = new TH1D("h_refFinal_METUtil","RefFinal from METUtility;E_{T}^{miss} [GeV]; Events / 5 GeV",50,0,250);
  h_refFinal_Diff    = new TH1D("h_refFinal_Diff","RefFinal: Difference between D3PD and METUtility;E_{T}^{miss} [GeV]; Events / GeV",50,-25,25);
  h_refFinal_Delta   = new TH1D("h_refFinal_Delta","Uncertainty on RefFinal;E_{T}^{miss} [GeV]; Events / GeV",50,0,50);

  h_refFinal_SUSYmu  = new TH1D("h_refFinal_SUSYmu","RefFinal with recalculated muon term;E_{T}^{miss} [GeV]; Events / 5 GeV",50,0,250);
  h_refFinal_SUSYMU  = new TH1D("h_refFinal_SUSYMU","RefFinal with recalculated muon term in METUtility;E_{T}^{miss} [GeV]; Events / 5 GeV",50,0,250);

  h_refFinal_JESUp   = new TH1D("h_refFinal_JESUp","RefFinal with JES up;E_{T}^{miss} [GeV]; Events / 5 GeV",50,0,250);
  h_refFinal_JESDown = new TH1D("h_refFinal_JESDown","RefFinal with JES down;E_{T}^{miss} [GeV]; Events / 5 GeV",50,0,250);

  h_refFinal_EESUp   = new TH1D("h_refFinal_EESUp","RefFinal with EES up;E_{T}^{miss} [GeV]; Events / 5 GeV",50,0,250);
  h_refFinal_EESDown = new TH1D("h_refFinal_EESDown","RefFinal with EES down;E_{T}^{miss} [GeV]; Events / 5 GeV",50,0,250);

  h_refFinal_MESUp   = new TH1D("h_refFinal_MESUp","RefFinal with MES up;E_{T}^{miss} [GeV]; Events / 5 GeV",50,0,250);
  h_refFinal_MESDown = new TH1D("h_refFinal_MESDown","RefFinal with MES down;E_{T}^{miss} [GeV]; Events / 5 GeV",50,0,250);

  h_refFinal_MERIDUp   = new TH1D("h_refFinal_MERIDUp","RefFinal with MERID up;E_{T}^{miss} [GeV]; Events / 5 GeV",50,0,250);
  h_refFinal_MERIDDown = new TH1D("h_refFinal_MERIDDown","RefFinal with MERID down;E_{T}^{miss} [GeV]; Events / 5 GeV",50,0,250);

  h_refFinal_MERMSUp   = new TH1D("h_refFinal_MERMSUp","RefFinal with MERMS up;E_{T}^{miss} [GeV]; Events / 5 GeV",50,0,250);
  h_refFinal_MERMSDown = new TH1D("h_refFinal_MERMSDown","RefFinal with MERMS down;E_{T}^{miss} [GeV]; Events / 5 GeV",50,0,250);

  h_refFinal_COUp    = new TH1D("h_refFinal_COUp","RefFinal with CellOut up;E_{T}^{miss} [GeV]; Events / 5 GeV",50,0,250);
  h_refFinal_CODown  = new TH1D("h_refFinal_CODown","RefFinal with CellOut down;E_{T}^{miss} [GeV]; Events / 5 GeV",50,0,250);
 
  JESUncertaintyProvider _JES("AntiKt4EMJESTopoJets", "../../Jet/JetUncertainties/share/JESUncertainty.root");
  _JES.init();

  JERProvider _JER("AntiKt4TopoJES", "Truth", "../../Jet/JetResolution/share/JERProviderPlots.root");
  _JER.init();

  eg2011::EnergyRescaler _egammaTool;
  _egammaTool.useDefaultCalibConstants("2011");

  MuonSmear::SmearingClass _muonTool;
  _muonTool.UseScale(1);

  METUtility *metCheck = new METUtility;
  metCheck->defineMissingET(true, false, true, true, false, false, true, true, false);
  // Turn on (off) the relevant MET terms
  // RefEle, (RefGamma), (RefTau), RefJet, (SoftJets), (RefMuon), MuonTotal, CellOut, (CellOut_Eflow)
  metCheck->setCellFix(false);
  metCheck->setIsMuid(false);
  metCheck->doForwardEtaCut(false);

  METUtility *metSys = new METUtility;
  metSys->defineMissingET(true, false, false, true, false, false, true, true, false);
  metSys->setCellFix(true);
  metSys->setIsMuid(false);
  metSys->doForwardEtaCut(false);
  metSys->setPileUpUncertainty(0.10);

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=nfirst; jentry<Nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;


    double MET_Simplified20_RefEle_et = sqrt(MET_Simplified20_RefEle_etx*MET_Simplified20_RefEle_etx
					     + MET_Simplified20_RefEle_ety*MET_Simplified20_RefEle_ety);
    double MET_Simplified20_RefGamma_et = sqrt(MET_Simplified20_RefGamma_etx*MET_Simplified20_RefGamma_etx
					       + MET_Simplified20_RefGamma_ety*MET_Simplified20_RefGamma_ety);
    double MET_Simplified20_RefJet_et = sqrt(MET_Simplified20_RefJet_etx*MET_Simplified20_RefJet_etx
					     + MET_Simplified20_RefJet_ety*MET_Simplified20_RefJet_ety);
    double MET_Simplified20_Muon_Total_Staco_et = sqrt(MET_Simplified20_Muon_Total_Staco_etx*MET_Simplified20_Muon_Total_Staco_etx
						       + MET_Simplified20_Muon_Total_Staco_ety*MET_Simplified20_Muon_Total_Staco_ety);
    double MET_Simplified20_CellOut_et = sqrt(MET_Simplified20_CellOut_etx*MET_Simplified20_CellOut_etx
					      + MET_Simplified20_CellOut_ety*MET_Simplified20_CellOut_ety);
    double MET_Simplified20_RefFinal_et = sqrt(MET_Simplified20_RefFinal_etx*MET_Simplified20_RefFinal_etx
					       + MET_Simplified20_RefFinal_ety*MET_Simplified20_RefFinal_ety);


    if(verbose || jentry%1000==0) cout << "Entry " << jentry
				       << ", run " << RunNumber << ", event " << EventNumber << endl;
    

    //First, we get the jet energy scale uncertainties and the resolutions of the jets
    vector<float> jesUp;
    vector<float> jesDown;
    vector<float> jetResUp;
    vector<float> jetResDown;

    TRandom *jetRandom = new TRandom;
    jetRandom->SetSeed(EventNumber);

    for(unsigned int iJet = 0; iJet < jet_AntiKt4TopoNewEM_pt->size(); ++iJet){
      float jesShift = 0.14;
//       float jerShift = 0.14;//this is just a default value for out of bound jets. Chosen from the value for eta > 2.1 to be conservative.
//       float deltaJerShift = 0.0;
      if(jet_AntiKt4TopoNewEM_pt->at(iJet) > 15000.0 && jet_AntiKt4TopoNewEM_pt->at(iJet) < 7000000.0 && fabs(jet_AntiKt4TopoNewEM_eta->at(iJet)) < 4.5){
	jesShift = _JES.getRelUncert(jet_AntiKt4TopoNewEM_pt->at(iJet), jet_AntiKt4TopoNewEM_eta->at(iJet));
      }
      jesUp.push_back(jesShift);
      jesDown.push_back(-1.0*jesShift);
	
//       if(jet_AntiKt4TopoNewEM_pt->at(iJet) > 10000.0 && jet_AntiKt4TopoNewEM_pt->at(iJet) < 5000.0*1000.0){
// 	jerShift = _JER.getSigma(jet_AntiKt4TopoNewEM_pt->at(iJet)/1000.0, jet_AntiKt4TopoNewEM_eta->at(iJet)); //dubious whether we should apply this to LC jets, derived for EMJES
// 	deltaJerShift = _JER.getUncert(jet_AntiKt4TopoNewEM_pt->at(iJet)/1000.0, jet_AntiKt4TopoNewEM_eta->at(iJet));
//       }

//       float smearShiftUp = jetRandom->Gaus(0.0, jerShift+deltaJerShift);
//       float smearShiftDown = jetRandom->Gaus(0.0, jerShift-deltaJerShift);


//       jetResUp.push_back(smearShiftUp);
//       jetResDown.push_back(smearShiftDown);
    }//end of jet loop
    if(verbose)  cout << endl;

    
    //now we get the same for electrons. We also smear the electrons -- the method should be similar for photons
    vector<float> eesUp;
    vector<float> eesDown;
    vector<float> eerUp;
    vector<float> eerDown;
    vector<float> *el_smeared_pt = new vector<float>;
      
    for (unsigned int iEl = 0; iEl < el_pt->size(); ++iEl){

      _egammaTool.SetRandomSeed(int(1.e+5*fabs(el_phi->at(iEl))));
      //set the seed however you like, I'm following the SUSYTools example

      float smear = _egammaTool.getSmearingCorrectionMeV(el_cl_eta->at(iEl), el_E->at(iEl), 0, true);
      float smearUp = _egammaTool.getSmearingCorrectionMeV(el_cl_eta->at(iEl), el_E->at(iEl), 2, true);
      float smearDown = _egammaTool.getSmearingCorrectionMeV(el_cl_eta->at(iEl), el_E->at(iEl), 1, true);

      el_smeared_pt->push_back(smear*el_pt->at(iEl));
      eerUp.push_back((smearUp - smear)/smear);
      eerDown.push_back((smearDown - smear)/smear);
      double energyUp = 0.03; //EnergyRescaler does jack if you feed it a float
      double energyDown = -0.03;

      _egammaTool.getErrorMeV(el_cl_eta->at(iEl), el_Et->at(iEl), energyUp, energyDown, "ELECTRON");

      eesUp.push_back(static_cast<float>(energyUp)); 
      eesDown.push_back(static_cast<float>(energyDown));
    }//end of electron loop


    //and now the same for muons
    vector<float> *mu_staco_smeared_pt = new vector<float>;
    vector<float> *mu_staco_smeared_ms_pt = new vector<float>;
      
    vector<float> cb_meridUp;
    vector<float> cb_meridDown;
    vector<float> cb_mermsUp;
    vector<float> cb_mermsDown;
    vector<float> mermsUp;
    vector<float> mermsDown;

    vector<float> mesUp;
    vector<float> mesDown;

      
    for(unsigned int iMu = 0; iMu < mu_staco_pt->size(); ++iMu){

      double ptcb = mu_staco_pt->at(iMu);
      double ptid = (mu_staco_id_qoverp_exPV->at(iMu) != 0.) ? fabs(sin(mu_staco_id_theta_exPV->at(iMu))/mu_staco_id_qoverp_exPV->at(iMu)) : 0.;
      double ptms = (mu_staco_me_qoverp_exPV->at(iMu) != 0.) ? fabs(sin(mu_staco_me_theta_exPV->at(iMu))/mu_staco_me_qoverp_exPV->at(iMu)) : 0.;
      _muonTool.SetSeed(int(1.e+5*fabs(mu_staco_phi->at(iMu))));
      double etaMu = mu_staco_eta->at(iMu);
      _muonTool.Event(ptms, ptid, ptcb, etaMu);


      Float_t smearedCombinedPt = _muonTool.pTCB();
      if(!mu_staco_isCombinedMuon->at(iMu)) smearedCombinedPt = _muonTool.pTMS() + _muonTool.pTID();

      Float_t smearedMSPt = _muonTool.pTMS();


      mu_staco_smeared_ms_pt->push_back(ptms);
      mu_staco_smeared_pt->push_back(smearedCombinedPt);

      double ptMS_smeared, ptID_smeared, ptCB_smeared;
      float smearedpTMS, smearedpTID, smearedpTCB;
      smearedpTMS = 0.1; smearedpTID = 0.1; smearedpTCB = 0.1;
      _muonTool.PTVar(ptMS_smeared, ptID_smeared, ptCB_smeared, "MSLOW");
      smearedpTMS = ptMS_smeared/smearedMSPt - 1.0;
      smearedpTCB = ptCB_smeared/smearedCombinedPt - 1.0;
      mermsDown.push_back(smearedpTMS);
      cb_mermsDown.push_back(smearedpTCB);
      _muonTool.PTVar(ptMS_smeared, ptID_smeared, ptCB_smeared, "MSUP");
      smearedpTMS = ptMS_smeared/smearedMSPt - 1.0;
      smearedpTCB = ptCB_smeared/smearedCombinedPt - 1.0;
      mermsUp.push_back(smearedpTMS);
      cb_mermsUp.push_back(smearedpTCB);
      _muonTool.PTVar(ptMS_smeared, ptID_smeared, ptCB_smeared, "IDUP");
      smearedpTCB = ptCB_smeared/smearedCombinedPt - 1.0;
      cb_meridUp.push_back(smearedpTCB);
      _muonTool.PTVar(ptMS_smeared, ptID_smeared, ptCB_smeared, "IDLOW");
      smearedpTCB = ptCB_smeared/smearedCombinedPt - 1.0;
      cb_meridDown.push_back(smearedpTCB);
	
      //get energies uncertainty from smearing class itself, it's in there but without a function to retrieve them. And only for CB?
      if(fabs(mu_staco_eta->at(iMu)) < 1.05){
	mesUp.push_back(0.0006);
	mesDown.push_back(-0.0006);
      }
      else if (fabs(mu_staco_eta->at(iMu)) < 1.7){
	mesUp.push_back(0.0013);
	mesDown.push_back(-0.0013);
      }
      else if (fabs(mu_staco_eta->at(iMu)) < 2.0){
	mesUp.push_back(0.0021);
	mesDown.push_back(-0.0021);
      }
      else {
	mesUp.push_back(0.0022);
	mesDown.push_back(-0.0022);
      }


    }//end of muon loop

      
    if(verbose)   cout << "Checking Rebuilding from METComposition Map Works:" << endl;
    metCheck->reset();

    //this is an example of how to simply rebuild MET from available objects
    //       metCheck = new METUtility;
    metCheck->setObjects("jets", jet_AntiKt4TopoNewEM_pt, jet_AntiKt4TopoNewEM_eta, jet_AntiKt4TopoNewEM_phi, jet_AntiKt4TopoNewEM_E, jet_AntiKt4TopoNewEM_MET_Simplified20_wet, jet_AntiKt4TopoNewEM_MET_Simplified20_wpx, jet_AntiKt4TopoNewEM_MET_Simplified20_wpy, jet_AntiKt4TopoNewEM_MET_Simplified20_statusWord);

    metCheck->setElectronParameters(el_pt, el_eta, el_phi, el_MET_Simplified20_wet, el_MET_Simplified20_wpx, el_MET_Simplified20_wpy, el_MET_Simplified20_statusWord);

    metCheck->setMuonParameters(mu_staco_pt, mu_staco_eta, mu_staco_phi, mu_staco_MET_Simplified20_wet, mu_staco_MET_Simplified20_wpx, mu_staco_MET_Simplified20_wpy, mu_staco_MET_Simplified20_statusWord);
    metCheck->setExtraMuonParameters(mu_staco_ms_qoverp, mu_staco_ms_theta, mu_staco_ms_phi, mu_staco_charge);
    //    metCheck->setPhotonParameters(ph_pt, ph_eta, ph_phi, ph_MET_wet, ph_MET_wpx, ph_MET_wpy, ph_MET_statusWord);
    //    metCheck->setMETTerm("RefGamma", MET_Simplified20_RefGamma_etx, MET_Simplified20_RefGamma_ety, MET_Simplified20_RefGamma_sumet);
    metCheck->setMETTerm("CellOut", MET_Simplified20_CellOut_etx, MET_Simplified20_CellOut_ety, MET_Simplified20_CellOut_sumet);

//     metCheck->setTauParameters(tau_pt, tau_eta, tau_phi, tau_MET_Simplified20_wet, tau_MET_Simplified20_wpx, tau_MET_Simplified20_wpy, tau_MET_Simplified20_statusWord);

    float refEle_et = metCheck->getMissingET("RefEle").et();
    float refGamma_et = metCheck->getMissingET("RefGamma").et();
    float refJet_et = metCheck->getMissingET("RefJet").et();
    float refCellOut_et = metCheck->getMissingET("CellOut").et();
    float muonTotal_et = metCheck->getMissingET("MuonTotal").et();
    float refFinal_et = metCheck->getMissingET("RefFinal").et();

    float refEle_etx = metCheck->getMissingET("RefEle").etx();
    float refGamma_etx = metCheck->getMissingET("RefGamma").etx();
    float refJet_etx = metCheck->getMissingET("RefJet").etx();
    float refCellOut_etx = metCheck->getMissingET("CellOut").etx();
    float muonTotal_etx = metCheck->getMissingET("MuonTotal").etx();
    float refFinal_etx = metCheck->getMissingET("RefFinal").etx();
    
    if(verbose) {
      cout << "+++++++++++++++++++++++++++++" << endl;
      cout << "Term:    Original       Tool output" << endl;
      cout << "Ref Ele etx: " << MET_Simplified20_RefEle_etx << " vs " << refEle_etx << endl;
      cout << "Ref Gamma etx: " << MET_Simplified20_RefGamma_etx << " vs " << refGamma_etx << endl;
      cout << "Ref Jet etx: " << MET_Simplified20_RefJet_etx << " vs " << refJet_etx << endl;
      cout << "Muon_Total_Staco etx: " << MET_Simplified20_Muon_Total_Staco_etx << " vs " << muonTotal_etx << endl;
      cout << "CellOut etx: " << MET_Simplified20_CellOut_etx << " vs " << refCellOut_etx << endl;
      cout << "Ref Final etx: " << MET_Simplified20_RefFinal_etx << " vs " << refFinal_etx << endl;
    }
      
    METObject myMET;
    myMET = metCheck->getMissingET("RefFinal");
    if(verbose) {
      cout << "RefFinal components, etx = " << myMET.etx() << ", ety = " << myMET.ety() << ", sumet = " << myMET.sumet() << ", phi = " << myMET.phi() << ", et = " << myMET.et() << endl;
      cout << "Significance of RefFinal is " << myMET.sig() << endl;
      cout << "+++++++++++++++++++++++++++++" << endl;
    }
     
    if(verbose)  cout << "Demonstration of smearing and systematics" << endl;

    //this demonstration is for doing smearing and systematics

    metSys->reset();

    metSys->setObjects("jets", jet_AntiKt4TopoNewEM_pt, jet_AntiKt4TopoNewEM_eta, jet_AntiKt4TopoNewEM_phi, jet_AntiKt4TopoNewEM_E, jet_AntiKt4TopoNewEM_MET_Simplified20_wet, jet_AntiKt4TopoNewEM_MET_Simplified20_wpx, jet_AntiKt4TopoNewEM_MET_Simplified20_wpy, jet_AntiKt4TopoNewEM_MET_Simplified20_statusWord);
    metSys->setExtraJetParameters(jet_AntiKt4TopoNewEM_EMJES, jet_AntiKt4TopoNewEM_m, jet_AntiKt4TopoNewEM_eta, jet_AntiKt4TopoNewEM_phi);
    metSys->setElectronParameters(el_smeared_pt, el_eta, el_phi, el_MET_wet, el_MET_wpx, el_MET_wpy, el_MET_statusWord);
    metSys->setMuonParameters(mu_staco_smeared_pt, mu_staco_eta, mu_staco_phi, mu_staco_MET_wet, mu_staco_MET_wpx, mu_staco_MET_wpy, mu_staco_MET_statusWord);
    metSys->setExtraMuonParameters(mu_staco_smeared_ms_pt, mu_staco_ms_theta, mu_staco_ms_phi);
	
    //    metSys->setMETTerm("RefGamma", MET_Simplified20_RefGamma_etx, MET_Simplified20_RefGamma_ety, MET_Simplified20_RefGamma_sumet);
    metSys->setMETTerm("CellOut", MET_Simplified20_CellOut_etx, MET_Simplified20_CellOut_ety, MET_Simplified20_CellOut_sumet);

    metSys->setObjectEnergyUncertainties("jets", jesUp, jesDown);
    //    metSys->setObjectResolutionShift("jets", jetResUp, jetResDown);

    metSys->setObjectEnergyUncertainties("electrons", eesUp, eesDown);
    metSys->setObjectResolutionShift("electrons", eerUp, eerDown);

    metSys->setObjectResolutionShift("comboms", cb_mermsUp, cb_mermsDown);
    metSys->setObjectResolutionShift("comboid", cb_meridUp, cb_meridDown);
    metSys->setObjectResolutionShift("spectromuons", mermsUp, mermsDown);

    metSys->setObjectEnergyUncertainties("muons", mesUp, mesDown);
	
    h_refFinal_D3PD->Fill(MET_Simplified20_RefFinal_et/1e3);
    h_refFinal_METUtil->Fill(refFinal_et/1e3);
    h_refFinal_Diff->Fill((MET_Simplified20_RefFinal_et-refFinal_et)/1e3);
    h_refFinal_Delta->Fill(metSys->absDeltaMissingET("RefFinal").et()/1e3);

    h_refFinal_JESUp->Fill(metSys->getMissingET("RefFinal","JESUp").et()/1e3);
    h_refFinal_JESDown->Fill(metSys->getMissingET("RefFinal","JESDown").et()/1e3);

    h_refFinal_EESUp->Fill(metSys->getMissingET("RefFinal","EESUp").et()/1e3);
    h_refFinal_EESDown->Fill(metSys->getMissingET("RefFinal","EESDown").et()/1e3);

    h_refFinal_MERIDUp->Fill(metSys->getMissingET("RefFinal","MERIDUp").et()/1e3);
    h_refFinal_MERIDDown->Fill(metSys->getMissingET("RefFinal","MERIDDown").et()/1e3);

    h_refFinal_MERMSUp->Fill(metSys->getMissingET("RefFinal","MERMSUp").et()/1e3);
    h_refFinal_MERMSDown->Fill(metSys->getMissingET("RefFinal","MERMSDown").et()/1e3);

    h_refFinal_MESUp->Fill(metSys->getMissingET("RefFinal","MESUp").et()/1e3);
    h_refFinal_MESDown->Fill(metSys->getMissingET("RefFinal","MESDown").et()/1e3);

    h_refFinal_COUp->Fill(metSys->getMissingET("RefFinal","AllClustersUp").et()/1e3);
    h_refFinal_CODown->Fill(metSys->getMissingET("RefFinal","AllClustersDown").et()/1e3);

    // Do computation following the SUSY prescription of recomputing the muon MET term

    metCheck->reset();

    double MET_Simp20_etx = MET_Simplified20_RefFinal_etx - MET_Simplified20_Muon_Total_Staco_etx;
    double MET_Simp20_ety = MET_Simplified20_RefFinal_ety - MET_Simplified20_Muon_Total_Staco_ety;

    double MET_susyMu_etx = 0;
    double MET_susyMu_ety = 0;

    vector<float> new_pt;
    vector<vector<unsigned int> > new_statusWord;
    vector<vector<float> > new_wet, new_wpx, new_wpy;
    for(int imu=0; imu<mu_staco_n; imu++) {
      TLorentzVector mu_TLV;
      double pt, phi, eta, m;
      m = 105.66;
      eta = mu_staco_eta->at(imu);
      phi = mu_staco_phi->at(imu);

      if(mu_staco_isCombinedMuon->at(imu)) {
	pt  = (mu_staco_id_qoverp_exPV->at(imu) != 0) ? 
	  fabs(sin(mu_staco_id_theta_exPV->at(imu))/mu_staco_id_qoverp_exPV->at(imu)) : 0.;
      } else {
	pt = mu_staco_pt->at(imu);
      }
      mu_TLV.SetPtEtaPhiM(pt,eta,phi,m);

      bool accept = mu_TLV.Pt()>10e3 && fabs(mu_TLV.Eta())<2.4;

      // Muon quality cuts
      bool quality = ( (mu_staco_isCombinedMuon->at(imu) || 
			mu_staco_isLowPtReconstructedMuon->at(imu)) &&
		       mu_staco_loose->at(imu) );

      // Track quality requirements
      int nTRTOutliers = mu_staco_nTRTOutliers->at(imu);
      int nTRTTotal    = nTRTOutliers + mu_staco_nTRTHits->at(imu);
      float trackEta   = -log(tan(mu_staco_id_theta->at(imu)/2));
      bool trackisgood = 
	( !mu_staco_expectBLayerHit->at(imu) || mu_staco_nBLHits->at(imu) > 0 ) &&
	( mu_staco_nPixHits->at(imu) + mu_staco_nPixelDeadSensors->at(imu) > 1 ) &&
	( mu_staco_nSCTHits->at(imu) + mu_staco_nSCTDeadSensors->at(imu) >= 6 ) &&
	( mu_staco_nPixHoles->at(imu) + mu_staco_nSCTHoles->at(imu) < 3 ) &&
	( fabs(trackEta) > 1.9 || nTRTTotal > 5 ) &&
	( nTRTTotal <= 5 || nTRTOutliers < 0.9*nTRTTotal );

      bool select = accept && quality && trackisgood;

      new_pt.push_back(mu_TLV.Pt());

      if(select) {
	MET_susyMu_etx -= mu_TLV.Px();
	MET_susyMu_ety -= mu_TLV.Py();
	vector<float> univec;
	univec.push_back(1.);
	new_wet.push_back(univec);
	new_wpx.push_back(univec);
	new_wpy.push_back(univec);
      } else {
	vector<float> zerovec;
	zerovec.push_back(0.);
	new_wet.push_back(zerovec);
	new_wpx.push_back(zerovec);
	new_wpy.push_back(zerovec);
      }
      vector<unsigned int> defvec;
      defvec.push_back(MissingETTags::DEFAULT);
      new_statusWord.push_back(defvec);
    }

    double MET_Simp20_et = sqrt(MET_Simp20_etx*MET_Simp20_etx + MET_Simp20_ety*MET_Simp20_ety);

    metCheck->setObjects("jets", jet_AntiKt4TopoNewEM_pt, jet_AntiKt4TopoNewEM_eta, jet_AntiKt4TopoNewEM_phi, jet_AntiKt4TopoNewEM_E, 
			 jet_AntiKt4TopoNewEM_MET_Simplified20_wet, jet_AntiKt4TopoNewEM_MET_Simplified20_wpx,
			 jet_AntiKt4TopoNewEM_MET_Simplified20_wpy, jet_AntiKt4TopoNewEM_MET_Simplified20_statusWord);

    metCheck->setElectronParameters(el_pt, el_eta, el_phi, el_MET_wet, el_MET_wpx, el_MET_wpy, el_MET_statusWord);
    //    metCheck->setPhotonParameters(ph_pt, ph_eta, ph_phi, ph_MET_wet, ph_MET_wpx, ph_MET_wpy, ph_MET_statusWord);
    metCheck->setMETTerm("RefGamma", MET_Simplified20_RefGamma_etx, MET_Simplified20_RefGamma_ety, MET_Simplified20_RefGamma_sumet);

    metCheck->setMETTerm("CellOut", MET_Simplified20_CellOut_etx, MET_Simplified20_CellOut_ety, MET_Simplified20_CellOut_sumet);

    if(verbose && (abs(MET_susyMu_etx)>0 || abs(MET_susyMu_ety)>0)) {
      METObject noMu_susy = metCheck->getMissingET("RefFinal");
      cout << "Muonless MET computed by hand: etx = " << MET_Simp20_etx << ", ety = " << MET_Simp20_ety << endl;
      cout << "Muonless MET computed by METUtil: etx = " << noMu_susy.etx() << ", ety = " << noMu_susy.ety() << endl;
    }

    MET_Simp20_etx += MET_susyMu_etx;
    MET_Simp20_ety += MET_susyMu_ety;

    metCheck->setMuonParameters(&new_pt, mu_staco_eta, mu_staco_phi, &new_wet, &new_wpx, &new_wpy, &new_statusWord);
    metCheck->setExtraMuonParameters(mu_staco_ms_qoverp, mu_staco_ms_theta, mu_staco_ms_phi, mu_staco_charge);

    if(verbose && (abs(MET_susyMu_etx)>0 || abs(MET_susyMu_ety)>0)) {
      METObject muonTotal_susy = metCheck->getMissingET("MuonTotal");
      cout << "Muon MET computed by hand: etx = " << MET_susyMu_etx << ", ety = " << MET_susyMu_ety << endl;
      cout << "Muon MET computed by METUtil: etx = " << muonTotal_susy.etx() << ", ety = " << muonTotal_susy.ety() << endl;
    }

    h_refFinal_SUSYmu->Fill(MET_Simp20_et/1e3);
    h_refFinal_SUSYMU->Fill(metCheck->getMissingET("RefFinal").et()/1e3);

  }//end of loop

  dataout->Print();
  dataout->Write();
  dataout->Close();

  delete metSys;
  delete metCheck;
   
}//end of macro

