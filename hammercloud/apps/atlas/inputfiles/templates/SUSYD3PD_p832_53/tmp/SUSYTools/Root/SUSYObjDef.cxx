
// $Id$
/**
 * @file SUSYTools/src/SUSYObjDef.cxx
 * @author Renaud Bruneliere <Renaud.Bruneliere@cern.ch>
 * @date Feb, 2011
 * @brief Baseline SUSY object definitions.
 *
 * Example usage:
 * if (mySUSYObj.IsElectron(...)) myeltlv = GetElecTLV();
 * if (mySUSYObj.IsMuon(...)) mymutlv = GetMuonTLV();
 * 
 */

#include <cstdlib>
#include "TPython.h"

#include "SUSYTools/SUSYObjDef.h"
#include "SUSYTools/PhotonIDTool.h"
#include "egammaEvent/egammaPIDdefs.h"
#include "egammaAnalysisUtils/CaloIsoCorrection.h"

SUSYObjDef::SUSYObjDef() : m_iEl(0), m_iPh(0), m_iMu(0), m_iJet(0), 
                           m_mcp_smear(0), m_muon_sf(0), m_JetCleanTool(0), m_myJes(0), m_myJER(0), _metUtility(0)
{
  // Resize vector of TLorentzVector at beginning
  // Takes memory but avoids usage of push_back which is more time consumming
  m_el.resize(m_NPartMax);
  m_ph.resize(m_NPartMax);
  m_mu.resize(m_NPartMax);
  m_jet.resize(2*m_NPartMax);
  _forMETJesUp.resize(2*m_NPartMax,0.);
  _forMETJesDown.resize(2*m_NPartMax,0.);
  _forMETJerUp.resize(2*m_NPartMax,0.);
  _forMETJerDown.resize(2*m_NPartMax,0.);
  
  // Electron scale smearing
  m_eRescale.useDefaultCalibConstants("2011");

  // https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/PhotonFudgeFactors
  // ps = 8 : Tight + isolation ( FF from whole 2011 data and MC11a (JF17+JF35+JF70)) 
  m_FFTool.SetPreselection(8);
  
  Reset();
}

SUSYObjDef::~SUSYObjDef()
{
  if (m_mcp_smear) delete m_mcp_smear;
  if (m_muon_sf) delete m_muon_sf;
  
  if (m_myJes) delete m_myJes;
  if (m_myJER) delete m_myJER;
}

void SUSYObjDef::initialize(std::string muon_momentum_dir,
                            std::string muon_sf_dir,
                            std::string muon_type,
                            std::string jes_file,
                            std::string jes_quarkgluon_file,
                            std::string jes_closebyjet_file,
                            std::string jer_file,
                            std::string jetSelectorTools_file,
                            std::string jetSelectorTools_cfg)
{
  std::vector<double> muon_sf_int_lum;
  muon_sf_int_lum.clear(); 
  SUSYObjDef::initialize(muon_sf_int_lum,muon_momentum_dir,muon_sf_dir,muon_type,
                         jes_file,jes_quarkgluon_file,jes_closebyjet_file,jer_file,
                         jetSelectorTools_file,jetSelectorTools_cfg);
}
void SUSYObjDef::initialize(std::vector<double>& muon_sf_int_lum,
                            std::string muon_momentum_dir,
                            std::string muon_sf_dir,
                            std::string muon_type,
                            std::string jes_file,
                            std::string jes_quarkgluon_file,
                            std::string jes_closebyjet_file,
                            std::string jer_file,
                            std::string jetSelectorTools_file,
                            std::string jetSelectorTools_cfg){
  std::string maindir = "";
  char *tmparea=getenv("ROOTCOREDIR");
  if (tmparea != NULL) {
    maindir = tmparea;
    maindir = maindir + "/../";
  }

  //to run with proof
  if (maindir == "") maindir = "/data/etp4/flegger/susy/D3PDReader_p832_53/"; 
  cout << "Using path "<<maindir<<endl;

  // Muon id efficiency scale factors
  // Initialize MuonEfficiencyScaleFactors
  if (muon_sf_int_lum.size() == 0) {
    // Default luminosity numbers are taken from
    //http://atlasdqm.web.cern.ch/atlasdqm/grlgen/Susy/Susy_v01/data11_7TeV.periodAllYear_DetStatus-v36-pro10_CoolRunQuery-00-04-08_Susy.xml
    muon_sf_int_lum.resize(11,0.);
    muon_sf_int_lum[0]  = 11.9912; // luminosity for period B = [177986, 178109]
    muon_sf_int_lum[1]  = 175.533;  // luminosity for period D = [179710, 180481]
    muon_sf_int_lum[2]  = 50.6941; // luminosity for period E = [180614, 180776]
    muon_sf_int_lum[3]  = 130.918; // luminosity for period F = [182013, 182519]
    muon_sf_int_lum[4]  = 501.769; // luminosity for period G = [182726, 183462]
    muon_sf_int_lum[5]  = 256.386; // luminosity for period H = [183544, 184169]
    muon_sf_int_lum[6]  = 339.135; // luminosity for period I = [185353, 186493]
    muon_sf_int_lum[7]  = 227.443; // luminosity for period J = [186516, 186755]
    muon_sf_int_lum[8]  = 590.621; // luminosity for period K = [186873, 187815]
    muon_sf_int_lum[9]  = 1373.49;  // luminosity for period L = [188902, 190343]
    muon_sf_int_lum[10] = 989.656; // luminosity for period M = [190503, 191933]
  }
  std::string unit("MeV");
  if (muon_sf_dir == "") muon_sf_dir = maindir + "MuonEfficiencyCorrections/share/"; // Default path
  if (!m_muon_sf) 
    m_muon_sf = new Analysis::AnalysisMuonEfficiencyScaleFactors(muon_type,muon_sf_int_lum,unit,muon_sf_dir);

  // Muon momentum scale corrections
  if (!m_mcp_smear) {
    if (muon_momentum_dir == "") muon_momentum_dir = maindir + "MuonMomentumCorrections/share/"; // Default path
    m_mcp_smear = new MuonSmear::SmearingClass("Data11","staco","q_pT","Rel17",muon_momentum_dir);
    m_mcp_smear->UseScale(1);
  }
  // Initialize jet cleaning tool
  // Do not use at the moment because python access is causing a crash when athena is setup
//  if (!m_JetCleanTool) {
//    if (jetSelectorTools_file == "") { // Default path
//      char *tmparea=getenv("ROOTCOREDIR");
//      if (tmparea != NULL) jetSelectorTools_file = tmparea;
//      jetSelectorTools_file = jetSelectorTools_file + "/../JetSelectorTools/python/ConfiguredTJetCleaningTools.py"; 
//    }
//    TPython::LoadMacro(jetSelectorTools_file.c_str());
//    m_JetCleanTool = static_cast<Root::TJetCleaningTool*>((void*)TPython::Eval(jetSelectorTools_cfg.c_str()));
//    m_JetCleanTool->initialize();
//  }
  
  // For JES 
  // Default path
  if (jes_file == "") jes_file = maindir + "JetUncertainties/share/JESUncertainty.root"; 
  if (jes_quarkgluon_file == "") jes_quarkgluon_file = maindir + "JetUncertainties/analysisPlots/MJESttbarSemi_rel16Example.root"; 
  if (jes_closebyjet_file == "") jes_closebyjet_file = maindir + "JetUncertainties/share/MJESUncertainty.root"; 
  if (jer_file == "") jer_file = maindir + "JetResolution/share/JERProviderPlots.root";
  std::cout << "JES Uncertainty Provider--> reading file" << jes_file << std::endl;
  std::cout << "JER Uncertainty Provider--> reading file" << jer_file << std::endl;
  m_myJes=new MultijetJESUncertaintyProvider("AntiKt4EMJESTopoJets",jes_quarkgluon_file,jes_closebyjet_file,jes_file);
  m_myJes->includeFlavorComposition(false);
  m_myJes->init();
  m_myJER = new JERProvider("AntiKt4TopoJES","Truth",jer_file);
  m_myJER->init();

  // code from TJ 
  _metUtility = new METUtility;
  _metUtility->defineMissingET(true, true, false, true, false, false, true, true, false);
  // Turn on (off) the relevant MET terms
  // RefEle, RefGamma, (RefTau), RefJet, (SoftJets), (RefMuon), MuonTotal, CellOut, (CellOut_Eflow)
  _metUtility->setCellFix(true);
  _metUtility->setIsMuid(false);
  _metUtility->doForwardEtaCut(false);

  // Reset internal variables
  Reset();
}

void SUSYObjDef::finalize()
{
  if (m_JetCleanTool) m_JetCleanTool->finalize();
}

void SUSYObjDef::Reset()
{
  // To gain time, reset only TLorentzVector previously used
  for (unsigned i = 0; i <= unsigned(m_iEl); i++)
    m_el[i].SetPxPyPzE(0.,0.,0.,0.);
  for (unsigned i = 0; i <= unsigned(m_iPh); i++)
    m_ph[i].SetPxPyPzE(0.,0.,0.,0.);
  for (unsigned i = 0; i <= unsigned(m_iMu); i++)
    m_mu[i].SetPxPyPzE(0.,0.,0.,0.);
  for (unsigned i = 0; i <= unsigned(m_iJet); i++)
    m_jet[i].SetPxPyPzE(0.,0.,0.,0.);

  m_iEl = m_iMu = m_iJet = m_iPh = 0;
}

bool SUSYObjDef::IsElectron(int iEl,
                            int RunNumber,
                            float el_cl_eta,
                            float el_cl_phi,
                            float el_cl_E,
                            float el_tracketa,
                            float el_trackphi,
                            int el_author,
                            int el_mediumPP,
                            unsigned int el_OQ,
                            int el_nPixHits,
                            int el_nSCTHits,
                            float el_wet,
                            bool isData,
                            float etcut,
                            float etacut,
                            bool ischeckOQ,
			    int value,
                            bool isAF2)
{
  bool istlvset = false;
  // Because smearing is slowing down processing time, the method SUSYObjDef::SetElecTLV is called only for electrons
  // passing the whole selection or entering RefEle term
  // Consequence: electrons which do not pass previous conditions have no TLorentzVector filled
  if (el_wet != 0.) {
    istlvset = true;
    SUSYObjDef::SetElecTLV(iEl,el_cl_eta,el_cl_phi,el_cl_E,el_tracketa,el_trackphi,
                           el_nPixHits,el_nSCTHits,isData,value,isAF2);
  }
  if (fabs(el_cl_eta) >= etacut) return false; // Fiducial cuts are done on cluster position
  if (!(el_author == 1 || el_author == 3)) return false; // Keep only cluster-seeded electrons
  //if (el_loose) return false;
  if (!el_mediumPP) return false;
  if ((el_OQ & egammaPID::BADCLUSELECTRON) != 0) return false; // Check object quality flag
  if (ischeckOQ && m_egammaOQ.checkOQClusterElectron(RunNumber,el_cl_eta,el_cl_phi) == 3) return false; // Check if necessary  that we are not in a dead region
  if (!istlvset)
    SUSYObjDef::SetElecTLV(iEl,el_cl_eta,el_cl_phi,el_cl_E,el_tracketa,el_trackphi,
                           el_nPixHits,el_nSCTHits,isData,value,isAF2);
  if (m_el[iEl].Pt() <= etcut) return false; // eT cut done after rescaling/smearing
  return true;
}

bool SUSYObjDef::IsSignalElectron(int iEl,
                                  int el_tightPP,
                                  float el_ptcone20,
                                  float etcut,
                                  float isocut)
{
  // Warning: make sure you called IsElectron before
  if (!el_tightPP) return false;
  if (m_el[iEl].Pt() <= etcut) return false; // eT cut (might be necessary for leading electron to pass trigger)
  if (isocut > 0. && m_el[iEl].Pt() > 0. && el_ptcone20/m_el[iEl].Pt() >= isocut) return false;
  return true;
}

void SUSYObjDef::SetElecTLV(int iEl,
                            float el_cl_eta,
                            float el_cl_phi,
                            float el_cl_E,
                            float el_tracketa,
                            float el_trackphi,
                            int el_nPixHits,
                            int el_nSCTHits,
                            bool isData,
			    int value,
                            bool isAF2)
{
  if (iEl >= int(m_el.size())) m_el.resize(iEl+10);
  // Electron direction: https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/ElectronsEnergyDirection
  float el_eta = 0.;
  float el_phi = 0.;
  if (el_nPixHits+el_nSCTHits < 4) {
    el_eta = el_cl_eta;
    el_phi = el_cl_phi;
  } else {
    el_eta = el_tracketa;
    el_phi = el_trackphi;
  }
  // Energy scale and resolution: 
  // https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/EnergyScaleResolutionRecommendations
  std::string part_type="ELECTRON";
  float el_E = el_cl_E;
  // Energy calibration around the barrel-endcap crack region (both data/MC)
  //el_E = el_E*m_eRescale.applyMCCalibrationMeV(el_cl_eta,el_E,"ELECTRON");
  el_E = el_E*m_eRescale.applyMCCalibrationMeV(el_cl_eta,el_E/cosh(el_eta),"ELECTRON");  //bug fix
  if (!isData) { // Smear
    int seed = int(1.e+5*fabs(el_cl_phi));
    if(!seed) ++seed;
    m_eRescale.SetRandomSeed(seed); 
    // int value   0:nominal, 1: smearcorr_down, 2: smearcorr_up
    // A new argument as a string version number has been added which could be either "2011" or "2010" 
    // depending on the data year.
    // All MC11c (MC11a/b) physics samples are produced with zero constant term for the LAr EM resolution.
    // The "mc_withCT" argument of the smearing function (getSmearingCorrection) should therefore be set to false.
    double smearcorr = m_eRescale.getSmearingCorrectionMeV(el_cl_eta,el_cl_E,value,false,"2011");
    el_E *= smearcorr;
    // Atlfast specific calibration corrections
    if (isAF2) el_E *= m_eRescale.applyAFtoG4(el_cl_eta);
  } else { // Residual energy scale corrections to be applied to data
    el_E = m_eRescale.applyEnergyCorrectionMeV(el_cl_eta,el_cl_phi,el_E,el_E/cosh(el_eta),value,"ELECTRON");
  }
  // Neglect electron mass
  m_el[iEl].SetPtEtaPhiE(el_E/cosh(el_eta),el_eta,el_phi,el_E);
  m_iEl = iEl;
}

double SUSYObjDef::scaleForFFUnconvertedPhoton(double pT, double eta, bool isconv)
{
  if(fabs(eta) < 1.81 || !isconv) return 1.;
  // Snippet from https://twiki.cern.ch/twiki/bin/view/AtlasProtected/PhotonFudgeFactors
  // temporary obtained by comparing FFMC to electron extrapolation
  // apply this scale factor for FFed unconverted photon
  // in 1.81 < |eta| < 2.37 (use ph_eta2 in DPD)
  // pT in GeV
  if (pT<25.) return 0.86;
  else if (pT<30.) return 0.89;
  else if (pT<35.) return 0.94;
  else if (pT<40.) return 0.92;
  else if (pT<45.) return 0.98;
  else return 0.97;
}

bool SUSYObjDef::IsPhoton(int iPh,
                          int RunNumber,
                          float ph_cl_pt,
                          float ph_cl_eta,
                          float ph_cl_phi,
                          float ph_cl_E,
                          float ph_etas2,
                          unsigned int ph_isEM,
                          unsigned int ph_OQ,
			  int ph_hasconv,
			  int ph_isConv,
			  float ph_reta,
			  float ph_rphi,
                          float ph_Ethad1,
                          float ph_Ethad,
                          float ph_E277,
                          float ph_E237,
                          float ph_E233,
                          float ph_weta2,
                          float ph_f1,
                          float ph_emaxs1,
                          float ph_Emax2,
                          float ph_Emins1,
                          float ph_fside,
                          float ph_wstot,
                          float ph_ws3,
                          bool isData,
                          float ptcut,
                          float etacut,
                          bool ischeckOQ,
			  int value,
                          bool isloose,
                          bool isAF2)
{
  SUSYObjDef::SetPhotonTLV(iPh,ph_cl_pt,ph_cl_eta,ph_cl_phi,ph_cl_E,ph_etas2,isData,value,isAF2);
  if (m_ph[iPh].Pt() <= ptcut) return false; // pT cut done after rescaling/smearing
  if (fabs(m_ph[iPh].Eta()) >= etacut) return false;
  // https://twiki.cern.ch/twiki/bin/view/AtlasProtected/HSG1WinterConf2012#Inclusive_selection
  // Supposedly using the AR bit requires recomputing the ID efficiencies etc.
  // if ((ph_isEM & 0x800000) != 0) return false; // electron/photon ambiguity resolver (AR) bit removal
  if ((ph_OQ&34214) != 0) return false; // Check object quality flag
  // https://twiki.cern.ch/twiki/bin/view/AtlasProtected/LArCleaningAndObjectQuality#Photon_Cleaning
  if ((ph_OQ&134217728) != 0 && (ph_reta > 0.98 || ph_rphi > 1.0 || (ph_OQ&67108864) != 0)) return false;
  if (ischeckOQ && m_egammaOQ.checkOQClusterPhoton(RunNumber,ph_cl_eta,ph_cl_phi,ph_hasconv) == 3) return false; // Check if necessary that we are not in a dead region
  // Compute extra variables originally coming from PAU
  // A map between PAU variable names and PhotonD3PDMaker is available there:
  // https://twiki.cern.ch/twiki/pub/AtlasProtected/PhotonD3PDMaker/PAU_PD3PD_ph_map.txt
  float factor = m_ph[iPh].E()/ph_cl_E;
  double rhad1 = ph_Ethad1/m_ph[iPh].Pt();
  double rhad  = ph_Ethad/m_ph[iPh].Pt();
  double e277  = ph_E277;
  double reta  = ph_reta;
  double rphi  = ph_rphi;
  double weta2 = ph_weta2;
  double f1    = ph_f1;
  double fside = ph_fside;
  double wstot = ph_wstot;
  double ws3   = ph_ws3;
  double deltae = ph_Emax2*factor - ph_Emins1*factor;
  double eratio = (ph_emaxs1+ph_Emax2)==0. ? 0 : (ph_emaxs1-ph_Emax2)/(ph_emaxs1+ph_Emax2);
  // Fudge factors
  // https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/PhotonFudgeFactors
  if (!isData)
    m_FFTool.FudgeShowers(m_ph[iPh].Pt(),(double)ph_etas2,rhad1,rhad,e277,reta,rphi,weta2,f1,
                          fside,wstot,ws3,deltae,eratio,ph_isConv);

  // Photon identification
  SUSY::PhotonIDTool photonIDTool(m_ph[iPh].Pt(),(double)fabs(ph_etas2),rhad1,rhad,ph_E277*factor,
                                  reta,rphi,weta2,f1,fside,wstot,ws3,deltae,eratio,ph_isConv);
  // H->gg is using PhotonCutsLoose(3) equivalent to ph_loose as preselection cut and 
  // PhotonCutsTight(6) equivalent to ph_tight for candidates
  if (isloose) return photonIDTool.PhotonCutsLoose(3);
  return photonIDTool.PhotonCutsTight(6);
}

bool SUSYObjDef::IsSignalPhoton(int iPh,
                                float ph_Etcone40_corrected,
                                float ptcut,
                                float isocut)
{
  // Warning: make sure you called IsPhoton before
  if (m_ph[iPh].Pt() <= ptcut) return false; // pT cut (might be necessary for leading photon to pass trigger)
  if (isocut > 0. && ph_Etcone40_corrected >= isocut) return false;
  return true;
}

bool SUSYObjDef::IsSignalPhotonCompIso(int iPh,
                                       float ph_Etcone40_ED_corrected,
                                       float ph_Etcone40,
                                       float ph_cl_E,
                                       float ph_cl_eta,
                                       float ph_etas2,
                                       float ph_etap,
                                       float ph_isConv,
                                       bool isData,
                                       float ptcut,
                                       float isocut)
{
  // Recompute isolation from egammaAnalysisUtils
  float ph_Etcone40_corrected = CaloIsoCorrection::GetPtEDCorrectedIsolation(ph_Etcone40,
                                                                             ph_Etcone40_ED_corrected,
                                                                             ph_cl_E,
                                                                             ph_etas2,
                                                                             ph_etap,
                                                                             ph_cl_eta,
                                                                             40,
                                                                             !isData,// true for MC, false for DATA
                                                                             ph_Etcone40,
                                                                             ph_isConv,
                                                                             CaloIsoCorrection::PHOTON);
  return SUSYObjDef::IsSignalPhoton(iPh,ph_Etcone40_corrected,ptcut,isocut);
}

void SUSYObjDef::SetPhotonTLV(int iPh,
                              float ph_cl_pt,
                              float ph_cl_eta,
                              float ph_cl_phi,
                              float ph_cl_E,
                              float ph_etas2,
                              bool isData,
                              int value,
                              bool isAF2)
{
  if (iPh >= int(m_ph.size())) m_ph.resize(iPh+10);
  // Energy scale and resolution: 
  // https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/EnergyScaleResolutionRecommendations
  float ph_E = ph_cl_E;
  if (isData) { // Residual energy scale corrections to be applied to data
    ph_E = m_eRescale.applyEnergyCorrectionMeV(ph_cl_eta,ph_cl_phi,ph_E,ph_cl_pt,value,"UNCONVERTED_PHOTON");
  } else {
    int seed = int(1.e+5*fabs(ph_cl_phi));
    if(!seed) ++seed;
    m_eRescale.SetRandomSeed(seed); 
    // int value   0:nominal, 1: smearcorr_down, 2: smearcorr_up
    // A new argument as a string version number has been added which could be either "2011" or "2010" 
    // depending on the data year.
    // All MC11c (MC11a/b) physics samples are produced with zero constant term for the LAr EM resolution.
    // The "mc_withCT" argument of the smearing function (getSmearingCorrection) should therefore be set to false.
    double smearcorr = m_eRescale.getSmearingCorrectionMeV(ph_etas2,ph_cl_E,value,false,"2011");
    ph_E *= smearcorr;
    // Atlfast specific calibration corrections
    if (isAF2) ph_E *= m_eRescale.applyAFtoG4(ph_etas2);
  }
  // SMDP and Higgs->gg recommendations from 
  // https://twiki.cern.ch/twiki/bin/view/AtlasProtected/HSG1WinterConf2012#Inclusive_selection
  m_ph[iPh].SetPtEtaPhiE(ph_E/cosh(ph_etas2),ph_etas2,ph_cl_phi,ph_E);
  m_iPh = iPh;
}

bool SUSYObjDef::IsMuon(int iMu,
                        float mu_staco_pt,
                        float mu_staco_eta,
                        float mu_staco_phi,
                        float mu_staco_E,
                        float mu_staco_me_qoverp_exPV,
                        float mu_staco_id_qoverp_exPV,
                        float mu_staco_me_theta_exPV,
                        float mu_staco_id_theta_exPV,
                        float mu_staco_id_theta,
                        int mu_staco_isCombinedMuon,
                        int mu_staco_isSegmentTaggedMuon,
                        int mu_staco_loose,
                        int mu_staco_expectBLayerHit, 
                        int mu_staco_nBLHits,
                        int mu_staco_nPixHits,
                        int mu_staco_nPixelDeadSensors,
                        int mu_staco_nPixHoles,
                        int mu_staco_nSCTHits,
                        int mu_staco_nSCTDeadSensors,
                        int mu_staco_nSCTHoles,
                        int mu_staco_nTRTHits,
                        int mu_staco_nTRTOutliers,
                        bool isData,
                        float ptcut,
                        float etacut,
			std::string THESTRING)
{
  SUSYObjDef::SetMuonTLV(iMu,mu_staco_pt,mu_staco_eta,mu_staco_phi,mu_staco_E,
                         mu_staco_me_qoverp_exPV,mu_staco_id_qoverp_exPV,
                         mu_staco_me_theta_exPV,mu_staco_id_theta_exPV,mu_staco_isCombinedMuon,isData,THESTRING);

  // Acceptance cuts
  if (m_mu[iMu].Pt() <= ptcut) return false;
  if (fabs(m_mu[iMu].Eta()) >= etacut) return false;

  // Muon quality cuts (keep only combined OR segment tagged muons)
  //if (!(mu_staco_isCombinedMuon)) return false;
  if (!(mu_staco_isCombinedMuon || mu_staco_isSegmentTaggedMuon)) return false;
  if (!mu_staco_loose) return false;

  // Track quality requirements
  if (mu_staco_expectBLayerHit && mu_staco_nBLHits == 0) return false;
  if (mu_staco_nPixHits + mu_staco_nPixelDeadSensors <= 1) return false;
  if (mu_staco_nSCTHits + mu_staco_nSCTDeadSensors < 6) return false;
  if (mu_staco_nPixHoles + mu_staco_nSCTHoles >= 3) return false;
  int nTRTOutliers = mu_staco_nTRTOutliers;
  int nTRTTotal    = nTRTOutliers + mu_staco_nTRTHits;
  float trackEta = -log(tan(mu_staco_id_theta/2));
  if (fabs(trackEta) < 1.9 && nTRTTotal <= 5) return false;
  if (nTRTTotal > 5 && nTRTOutliers >= 0.9*nTRTTotal) return false;

  return true;
}

bool SUSYObjDef::IsSignalMuon(int iMu, float mu_staco_ptcone20, float ptcut, float isocut)
{
  if (m_mu[iMu].Pt() <= ptcut) return false;                    // pT cut (might be necessary for leading electron to pass trigger)
  if (isocut > 0. && mu_staco_ptcone20 >= isocut) return false; // Muon isolation cut
  return true;
}

bool SUSYObjDef::IsCosmicMuon(float mu_staco_z0_exPV, float mu_staco_d0_exPV, float z0cut, float d0cut)
{
  // Muon cosmic rejection cuts.
  // Method returns TRUE if there is a cosmic candidate !
  // See https://indico.cern.ch/getFile.py/access?contribId=6&resId=0&materialId=slides&confId=132166 
  if (fabs(mu_staco_z0_exPV) >= z0cut) return true;
  if (fabs(mu_staco_d0_exPV) >= d0cut) return true;

  return false;
}

bool SUSYObjDef::IsBadMuon(float mu_staco_qoverp_exPV, float mu_staco_cov_qoverp_exPV, float qopcut)
{
  if (qopcut > 0. && mu_staco_qoverp_exPV != 0 && mu_staco_qoverp_exPV > -99999.) {
    float qoperror = sqrt(mu_staco_cov_qoverp_exPV)/fabs(mu_staco_qoverp_exPV);
    if (qoperror >= qopcut) return true;
  }
  return false;
}

void SUSYObjDef::SetMuonTLV(int iMu,
                            float mu_staco_pt,
                            float mu_staco_eta,
                            float mu_staco_phi,
                            float /*mu_staco_E*/,
                            float mu_staco_me_qoverp_exPV,
                            float mu_staco_id_qoverp_exPV,
                            float mu_staco_me_theta_exPV,
                            float mu_staco_id_theta_exPV,
                            int mu_staco_isCombinedMuon,
                            bool isData,
			    std::string THESTRING)
{
  if (iMu >= int(m_mu.size())) m_mu.resize(iMu+10);
  float mypt = mu_staco_pt;
  if (!isData && m_mcp_smear) {
    /** Use the MC event number to set seed so that the random numbers are reproducible by
        different analyzers **/
    float ptcb = mu_staco_pt;
    float ptid = (mu_staco_id_qoverp_exPV != 0.) ? fabs(sin(mu_staco_id_theta_exPV)/mu_staco_id_qoverp_exPV) : 0.;
    float ptms = (mu_staco_me_qoverp_exPV != 0.) ? fabs(sin(mu_staco_me_theta_exPV)/mu_staco_me_qoverp_exPV) : 0.;
    //m_mcp_smear.SetSeed(EventNumber+iMu*1000000);
    int seed = int(fabs(mu_staco_phi*1.e+5));
    if(!seed) ++seed;
    m_mcp_smear->SetSeed(seed);
    m_mcp_smear->Event(ptms,ptid,ptcb,mu_staco_eta); 

    if (THESTRING == "") {
      if (mu_staco_isCombinedMuon)
	mypt = m_mcp_smear->pTCB();
      else
	mypt = m_mcp_smear->pTID();
    } else {
      double pTMS_smeared = 0.;
      double pTID_smeared = 0.;
      double pTCB_smeared = 0.;
      
      // Valid values for "THESTRING": {"MSLOW", "MSUP", "IDLOW", "IDUP"} 
      m_mcp_smear->PTVar(pTMS_smeared, pTID_smeared, pTCB_smeared, THESTRING);
      
      if (mu_staco_isCombinedMuon)
	mypt = pTCB_smeared;
      else
	mypt = pTID_smeared;
    }
  }
  // Keep eta,phi fixed when smearing muon pt
  m_mu[iMu].SetPtEtaPhiM(mypt,mu_staco_eta,mu_staco_phi,105.66);
  m_iMu = iMu;
}

bool SUSYObjDef::IsTau(float tau_Et,
		       float tau_eta,
		       float tau_charge,
		       int tau_author,
		       int tau_numTrack, 
		       int tau_JETBDTLoose, 
		       int tau_JETBDTMedium, 
		       int tau_JETBDTTight,
		       int tau_electronVetoTight,
		       bool isData, 
		       float ptcut, 
		       float etacut, 
		       int bdtoneprongcut, 
		       int bdtthreeprongcut)
{
  // baseline selection cuts
  if (tau_Et <= ptcut) return false;
  if (fabs(tau_eta) >= etacut) return false;
  if (tau_author != 1 && tau_author != 3) return false;
  
  // id
  if (tau_numTrack != 1 && tau_numTrack != 3) return false;
  if (tau_electronVetoTight == 1) return false;
  if (tau_numTrack == 1)
    {
      if (bdtoneprongcut == 1 && tau_JETBDTLoose != 1) return false;
      if (bdtoneprongcut == 2 && tau_JETBDTMedium != 1) return false;
      if (bdtoneprongcut == 3 && tau_JETBDTTight != 1) return false;
    }
  if (tau_numTrack == 3)
    {
      if (bdtthreeprongcut == 1 && tau_JETBDTLoose != 1) return false;
      if (bdtthreeprongcut == 2 && tau_JETBDTMedium != 1) return false;
      if (bdtthreeprongcut == 3 && tau_JETBDTTight != 1) return false;
    }
  

  return true;
}


bool SUSYObjDef::IsJet(int iJet, 
                       float jet_AntiKt4TopoNewEM_pt,
                       float jet_AntiKt4TopoNewEM_eta,
                       float jet_AntiKt4TopoNewEM_phi,
                       float jet_AntiKt4TopoNewEM_E,
                       float jet_AntiKt4TopoNewEM_emscale_eta,
                       float jet_AntiKt4TopoNewEM_emfrac,
                       float jet_AntiKt4TopoNewEM_hecf,
                       float jet_AntiKt4TopoNewEM_LArQuality,
                       float jet_AntiKt4TopoNewEM_HECQuality,
                       float jet_AntiKt4TopoNewEM_AverageLArQF,
                       float jet_AntiKt4TopoNewEM_Timing,
                       float jet_AntiKt4TopoNewEM_sumPtTrk,
                       float jet_AntiKt4TopoNewEM_fracSamplingMax,
                       float jet_AntiKt4TopoNewEM_NegativeE,
		       int jet_AntiKt4TopoNewEM_flavor_truth_label,
                       bool isData,
                       float ptcut,
                       float etacut,
                       JetID::BadJetCategory criteria,
		       JetErr::Syste whichsyste, 
		       bool nojetsmear,
		       double drmin)
{

  if (iJet >= int(m_jet.size())) {
    m_jet.resize(iJet+10);
    _forMETJesUp.resize(iJet+10,0.);
    _forMETJesDown.resize(iJet+10,0.);
    _forMETJerUp.resize(iJet+10,0.);
    _forMETJerDown.resize(iJet+10,0.);
  }

  double jetpt=jet_AntiKt4TopoNewEM_pt;
  double jetE=jet_AntiKt4TopoNewEM_E;
  double jeteta=jet_AntiKt4TopoNewEM_eta;
  double jetphi=jet_AntiKt4TopoNewEM_phi;

  // JES HANDLING
  double uncert=0;
  int myNVtx=1;
  double factor=1;


  // I.Vivarelli, 18/12/2011 - the new JES provider includes pileup uncertainties

  if(whichsyste==JetErr::JESUP) { 
    if(jetpt>20000&&fabs(jeteta)<4.5) 
      uncert=m_myJes->getRelPosUncert(jetpt, jeteta,drmin, 
				      MultijetJESUncertaintyProvider::ALL, myNVtx);
    _forMETJesUp.at(iJet)=uncert;
    _forMETJesDown.at(iJet)=0.;
  }
  if(whichsyste==JetErr::JESDOWN) { 
    if(jetpt>20000&&fabs(jeteta)<4.5) 
      uncert=m_myJes->getRelNegUncert(jetpt, jeteta,drmin, 
				      MultijetJESUncertaintyProvider::ALL, myNVtx);
    factor=-1;
    _forMETJesUp.at(iJet)=0.;
    _forMETJesDown.at(iJet)=uncert*factor;
  }
  
  // I.Vivarelli, 18/12/2011 - no need anymore for hand made pileup uncertainties
  


  /*  if(whichsyste==JetErr::JESUP||whichsyste==JetErr::JESDOWN) {
    double totuncert=0;
    // this is the additional uncert for pileup - from Chris Y.
    if(fabs(jet_AntiKt4TopoNewEM_eta)>0 && 
       fabs(jet_AntiKt4TopoNewEM_eta)<2.1 
       && jetpt>20000. && jetpt<50000.)   totuncert=sqrt(0.05*0.05 + uncert*uncert);
    if(fabs(jet_AntiKt4TopoNewEM_eta)>0 && 
       fabs(jet_AntiKt4TopoNewEM_eta)<2.1 
       && jetpt>50000. && jetpt<100000.)  totuncert=sqrt(0.02*0.02 + uncert*uncert);
    if(fabs(jet_AntiKt4TopoNewEM_eta)>2.1 && 
       fabs(jet_AntiKt4TopoNewEM_eta)<4.5 && 
       jetpt>20000. && jetpt<50000.)      totuncert=sqrt(0.07*0.07 + uncert*uncert);
    if(fabs(jet_AntiKt4TopoNewEM_eta)>2.1 && 
       fabs(jet_AntiKt4TopoNewEM_eta)<4.5 && 
       jetpt>50000. && jetpt<100000.)     totuncert=sqrt(0.03*0.03 + uncert*uncert);
    if(jetpt>100000.)                     totuncert=uncert;
    jetpt=jetpt*(1+ (factor*totuncert));	// (factor = +1 or -1 for positive or negative uncert.)
    jetE=jetE*(1+ (factor*totuncert));	// (factor = +1 or -1 for positive or negative uncert.)
    }*/

  // Additional b-jet uncertainty

  float bjetunc = 0;
  
  if ((!isData) && jet_AntiKt4TopoNewEM_flavor_truth_label == 5){
    if (jetpt > 20000 && jetpt <=40000){
      bjetunc = 0.025;
    } 
    if (jetpt > 40000 && jetpt <=80000){
      bjetunc = 0.020;
    } 
    if (jetpt > 80000 && jetpt <= 210000){
      bjetunc = 0.017;
    } 
    if (jetpt > 210000 && jetpt < 600000){
      bjetunc = 0.011;
    } 
    if (jetpt > 600000){
      bjetunc = 0.0076;
    } 

    uncert = sqrt(uncert*uncert + bjetunc*bjetunc);
  }

  if (whichsyste == JetErr::JESUP || whichsyste == JetErr::JESDOWN){
    jetpt=jetpt*(1+ (factor*uncert));	// (factor = +1 or -1 for positive or negative uncert.)
    jetE=jetE*(1+ (factor*uncert));	// (factor = +1 or -1 for positive or negative uncert.)
  }

  if(whichsyste==JetErr::JESUP) { 
    _forMETJesUp.at(iJet)=uncert;
    _forMETJesDown.at(iJet)=0.;
  }
  if(whichsyste==JetErr::JESDOWN) { 
    factor=-1;
    _forMETJesUp.at(iJet)=0.;
    _forMETJesDown.at(iJet)=uncert*factor;
  }


  // JER HANDLING 
  if(whichsyste==JetErr::JER){
    
    double smearingFactorSyst = 0;
    double jetsmear = 1;
    if (fabs(jeteta) < 4.5 && jetpt > 10000){
      smearingFactorSyst = m_myJER->getSmearingFactorSyst(jetpt/1000.,jeteta);
      int seed = int(fabs(jetphi*1.e+5));
      if(!seed) ++seed;
      m_random.SetSeed(seed);
      jetsmear = m_random.Gaus(1,smearingFactorSyst);
    }

    // Not sure what to do with these two terms, leaving them like they are for the moment

    _forMETJerUp.at(iJet)=jetsmear - 1;
    _forMETJerDown.at(iJet)=1 - jetsmear;

    

    jetpt = jetpt * jetsmear;
    jetE = jetE * jetsmear;
  }


  SUSYObjDef::SetJetTLV(iJet,jetpt,jeteta,jet_AntiKt4TopoNewEM_phi,jetE);

  // Acceptance cuts
  if (m_jet[iJet].Pt() <= ptcut) return false;
  if (fabs(jet_AntiKt4TopoNewEM_eta) >= etacut) return false;

  // Quality cuts for jet cleaning as described on
  // https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/HowToCleanJets2011#How_to_clean_jets
  bool isgoodjet = true;
  if (JetID::isBadJet(criteria,jet_AntiKt4TopoNewEM_emfrac,jet_AntiKt4TopoNewEM_hecf,
		      jet_AntiKt4TopoNewEM_LArQuality,jet_AntiKt4TopoNewEM_HECQuality,
		      jet_AntiKt4TopoNewEM_Timing,jet_AntiKt4TopoNewEM_sumPtTrk/1000.,
		      jet_AntiKt4TopoNewEM_emscale_eta,jetpt/1000.,
		      jet_AntiKt4TopoNewEM_fracSamplingMax,jet_AntiKt4TopoNewEM_NegativeE,
                      jet_AntiKt4TopoNewEM_AverageLArQF))
    isgoodjet = false;
    
  return isgoodjet;
}

void SUSYObjDef::SetJetTLV(int iJet,
                           float jet_AntiKt4TopoNewEM_pt,
                           float jet_AntiKt4TopoNewEM_eta,
                           float jet_AntiKt4TopoNewEM_phi,
                           float jet_AntiKt4TopoNewEM_E)
{
  m_jet[iJet].SetPtEtaPhiE(jet_AntiKt4TopoNewEM_pt,jet_AntiKt4TopoNewEM_eta,
                           jet_AntiKt4TopoNewEM_phi,jet_AntiKt4TopoNewEM_E);
  m_iJet = iJet;
}

bool SUSYObjDef::IsBJet(float jet_AntiKt4TopoNewEM_flavor_weight_xxx, std::string jetTagger, float op)
{ 
  // Default operating points are taken from 
  // https://twiki.cern.ch/twiki/bin/view/AtlasProtected/BTagCalibWinter2012#Working_Points_to_Calibrate
  float opdef = 1.80;
  if (jetTagger == "SV0")
    opdef = 5.65; // 50% efficiency
  else if (jetTagger == "JetProb") // Might require a -log(w).... need to check
    opdef = 2.65; // 50% efficiency
  else if (jetTagger == "Comb") // IP3D+SV1 is corresponding to jet_AntiKt4TopoNewEM_flavor_weight_Comb
    opdef = 4.55; // 60% efficiency
  else if (jetTagger == "JetFitterCOMBNN")
    opdef = 1.80; // 60% efficiency

  float opcut = opdef;
  if (op != 999.) opcut = op;
  return (jet_AntiKt4TopoNewEM_flavor_weight_xxx > opcut);
}

void SUSYObjDef::SmearJets(std::vector<float>* jetpt,
			   std::vector<float>* jeteta,
			   std::vector<float>* jetphi,
			   std::vector<float>* jete)
{
  double smearingFactorMC = 0;
  double jetsmear = 0;

  for (unsigned int i = 0; i < jetpt->size(); ++i){
    if (fabs(jeteta->at(i)) < 4.5 && jetpt->at(i) > 10000){
      smearingFactorMC = m_myJER->getSmearingFactorMC(jetpt->at(i)/1000.,jeteta->at(i));
      int seed = int(fabs(jetphi->at(i) *1.e+5));
      if(!seed) ++seed;
      m_random.SetSeed(seed);
      jetsmear = m_random.Gaus(1,smearingFactorMC);
      jetpt->at(i) = jetpt->at(i) * jetsmear;
      jete->at(i) = jete->at(i) * jetsmear;
    }
  }
}


bool SUSYObjDef::IsLArHoleVeto(float jet_AntiKt4TopoNewEM_pt, float jet_AntiKt4TopoNewEM_eta, 
                               float jet_AntiKt4TopoNewEM_phi, 
                               float jet_AntiKt4TopoNewEM_BCH_CORR_JET, float jet_AntiKt4TopoNewEM_BCH_CORR_CELL, 
                               bool kIsData, float ptcut, int RunNumber)
{
  if (!SUSYObjDef::IsLArHole(jet_AntiKt4TopoNewEM_eta,jet_AntiKt4TopoNewEM_phi)) return false;
  float pt = ptcut;
  // Correct threshold cut by missing energy in LAr hole in data. 
  // BCH_CORR_CELL is necessary to take into account dead tile module near LAr hole. 
  if (kIsData && RunNumber >= 180614) 
    pt = pt*(1. - jet_AntiKt4TopoNewEM_BCH_CORR_JET)/(1. - jet_AntiKt4TopoNewEM_BCH_CORR_CELL);
  if (jet_AntiKt4TopoNewEM_pt <= pt) return false;
  return true;
}


TVector2 SUSYObjDef::GetMET(const std::vector<float>* jetpt,
		            const std::vector<float>* jeteta,
		            const std::vector<float>* jetphi,
		            const std::vector<float>* jete,
		            const std::vector<vector<float> >* jetwet,
		            const std::vector<vector<float> >* jetwpx,
		            const std::vector<vector<float> >* jetwpy,
		            const std::vector<vector<unsigned int> >* jetstatus,
		            const std::vector<int>& velidx,
		            const std::vector<vector<float> >* elwet,
		            const std::vector<vector<float> >* elwpx,
		            const std::vector<vector<float> >* elwpy,
		            const std::vector<vector<unsigned int> >* elstatus,
		            float METCellOutetx45, float METCellOutety45, float METCellOutsumet45,
		            float METRefGamma_etx45, float METRefGamma_ety45, float METRefGammasumet45,
		            const std::vector<int>& vmuidx,
		            const std::vector<float>* mu_staco_ms_qoverp, 
		            const std::vector<float>* mu_staco_ms_theta, 
		            const std::vector<float>* mu_staco_ms_phi, 
		            const std::vector<float>* mu_staco_charge,
		            JetErr::Syste syste)
{

  // I.Vivarelli - have to resmear the objects here - should be safe, as I am setting the seed to exactly the same number used in IsJet
  
  _metUtility->reset();
  _metUtility->setObjects("jets", jetpt, jeteta, jetphi, jete, jetwet, jetwpx, jetwpy, jetstatus);
  vector<float> jesup;
  vector<float> jesdown;
  vector<float> jerup;
  vector<float> jerdown;
  for(size_t iJet=0;iJet<jetpt->size();iJet++) {
    jesup.push_back(_forMETJesUp.at(iJet));
    jesdown.push_back(_forMETJesDown.at(iJet));
    jerup.push_back(_forMETJerUp.at(iJet));
    jerdown.push_back(_forMETJerDown.at(iJet));
  }	       
  vector<float> elpt(velidx.size());
  vector<float> eleta(velidx.size());
  vector<float> elphi(velidx.size());
  vector<vector<unsigned int> > new_elstatus;
  vector<vector<float> > new_elwet, new_elwpx, new_elwpy;
  for (unsigned int iEl = 0; iEl < velidx.size(); iEl++) {
    elpt[iEl] = m_el[velidx.at(iEl)].Pt();
    eleta[iEl] = m_el[velidx.at(iEl)].Eta();
    elphi[iEl] = m_el[velidx.at(iEl)].Phi();
    new_elstatus.push_back(elstatus->at(velidx.at(iEl)));
    new_elwet.push_back(elwet->at(velidx.at(iEl)));
    new_elwpx.push_back(elwpx->at(velidx.at(iEl)));
    new_elwpy.push_back(elwpy->at(velidx.at(iEl)));
  }
  if(syste==JetErr::JESUP)   _metUtility->setObjectEnergyUncertainties("jets", jesup,jesdown);
  else if(syste==JetErr::JESDOWN) _metUtility->setObjectEnergyUncertainties("jets", jesup,jesdown);
  else if(syste==JetErr::JER)     _metUtility->setObjectResolutionShift("jets", jerup, jerdown);
  _metUtility->setElectronParameters(&elpt, &eleta, &elphi, &new_elwet, &new_elwpx, &new_elwpy, &new_elstatus);
  _metUtility->setMETTerm("RefGamma", METRefGamma_etx45,  METRefGamma_ety45,  METRefGammasumet45);
  _metUtility->setMETTerm("CellOut", METCellOutetx45,  METCellOutety45,  METCellOutsumet45);
  vector<float> mupt;
  vector<float> mueta;
  vector<float> muphi;
  vector<vector<unsigned int> > new_statusWord;
  vector<vector<float> > new_wet, new_wpx, new_wpy;

  for (unsigned int iMuIdx = 0; iMuIdx < vmuidx.size(); iMuIdx++)
    {
      mupt.push_back(m_mu[vmuidx.at(iMuIdx)].Vect().Pt());
      mueta.push_back(m_mu[vmuidx.at(iMuIdx)].Vect().Eta());
      muphi.push_back(m_mu[vmuidx.at(iMuIdx)].Vect().Phi());
      vector<float> univec;
      univec.push_back(1.);
      new_wet.push_back(univec);
      new_wpx.push_back(univec);
      new_wpy.push_back(univec);
      vector<unsigned int> defvec;
      defvec.push_back(MissingETTags::DEFAULT);
      new_statusWord.push_back(defvec);
    }   
  
  _metUtility->setMuonParameters(&mupt, &mueta, &muphi, &new_wet, &new_wpx, &new_wpy, &new_statusWord);
  _metUtility->setExtraMuonParameters(mu_staco_ms_qoverp, mu_staco_ms_theta, mu_staco_ms_phi, mu_staco_charge);

  METObject finalMet;

  switch(syste) {
  case JetErr::JESUP: finalMet=_metUtility->getMissingET("RefFinal","JESUp"); break;
  case JetErr::JESDOWN: finalMet=_metUtility->getMissingET("RefFinal","JESDown"); break;
  case JetErr::JER: finalMet=_metUtility->getMissingET("RefFinal","JERUp"); break;
  case JetErr::NONE: finalMet=_metUtility->getMissingET("RefFinal"); break;
  }


  TVector2 met(finalMet.etx(),finalMet.ety());
  return(met);
}

TVector2 SUSYObjDef::computeMETComponent(string whichcomponent, JetErr::Syste syste)
{
  METObject finalMet;
  
  switch(syste) {
  case JetErr::JESUP: finalMet=_metUtility->getMissingET(whichcomponent,"JESUp"); break;
  case JetErr::JESDOWN: finalMet=_metUtility->getMissingET(whichcomponent,"JESDown"); break;
  case JetErr::JER: finalMet=_metUtility->getMissingET(whichcomponent,"JERUp"); break;
  case JetErr::NONE: finalMet=_metUtility->getMissingET(whichcomponent); break;
  }
  
  TVector2 met(finalMet.etx(),finalMet.ety());
  return(met);
}


bool SUSYObjDef::IsGoodVertex(std::vector<int>* vx_nTracks)
{
  // Check if primary vertex is a good vertex
  bool isGoodPrimaryVertex = false;
  if (vx_nTracks->size() && vx_nTracks->at(0) > 4) isGoodPrimaryVertex = true; // Jet-MET wg requirement
  //for (unsigned int ivx = 0; ivx < vx_nTracks->size(); ivx++)
  //  if (vx_nTracks->at(ivx) > 4) {
  //    isGoodPrimaryVertex = true; // Jet-MET wg requirement
  //    break;
  //  }
  return isGoodPrimaryVertex;
}

float SUSYObjDef::GetSignalMuonSF(int iMu)
{
  if (!m_muon_sf) {
    std::cout << "WARNING: SUSYObjDef::GetSignalMuonSF empty class, did you call SUSYObjDef::Initialize ?" 
              << std::endl;
    return 0.;
  }
  return m_muon_sf->scaleFactor(m_mu[iMu]);
}

float SUSYObjDef::GetSignalMuonSFUnc(int iMu)
{
  if (!m_muon_sf) {
    std::cout << "WARNING: SUSYObjDef::GetSignalMuonSFUnc empty class, did you call SUSYObjDef::Initialize ?" 
              << std::endl;
    return 0.;
  }
  return m_muon_sf->scaleFactorUncertainty(m_mu[iMu]);
}

bool SUSYObjDef::MuonHasTriggerMatch(double mu_staco_eta,
				     double mu_staco_phi,
				     vector<int> *trig_EF_trigmuonef_signature,
				     int& EFindex,
				     int& EFtrackindex,
				     unsigned int trig_EF_trigmuonef_n,
				     vector<vector<float> > *trig_EF_trigmuonef_track_CB_eta,
				     vector<vector<float> > *trig_EF_trigmuonef_track_CB_phi,
				     vector<vector<int> > *trig_EF_trigmuonef_track_CB_hasCB)
{
  // Code largely based on egammaAnalysisUtils/egammaTriggerMatching.cxx

  EFindex = -1;
  EFtrackindex = -1;

  if (trig_EF_trigmuonef_n==0) {
    //std::cout << "No EF object to be tested" << std::endl;
    return false;
  }
  
  // checking consistency
  if (!trig_EF_trigmuonef_signature) {
    std::cout << "ERROR: empty pointer provided for trig_EF_trigmuonef_signature .... returning false" << std::endl;
    return false;
  }
  if (trig_EF_trigmuonef_signature->size() != trig_EF_trigmuonef_n) {
    std::cout << "ERROR: mismatch in the size of the trig_EF_trigmuonef_signature vector: " << trig_EF_trigmuonef_signature->size() << "  --> expected: " <<  trig_EF_trigmuonef_n << std::endl;
    return false;
  }

  if (!trig_EF_trigmuonef_track_CB_eta) {
    std::cout << "ERROR: empty pointer provided for trig_EF_trigmuonef_track_CB_eta .... returning false" << std::endl;
    return false;
  }
  if (trig_EF_trigmuonef_track_CB_eta->size() != trig_EF_trigmuonef_n) {
    std::cout << "ERROR: mismatch in the size of the trig_EF_trigmuonef_track_CB_eta vector: " << trig_EF_trigmuonef_track_CB_eta->size() << "  --> expected: " <<  trig_EF_trigmuonef_n << std::endl;
    return false;
  }

  if (trig_EF_trigmuonef_track_CB_phi==0) {
    std::cout << "ERROR: empty pointer provided for trig_EF_trigmuonef_track_CB_phi .... returning false" << std::endl;
    return false;
  }
  if (trig_EF_trigmuonef_track_CB_phi->size() != trig_EF_trigmuonef_n) {
    std::cout << "ERROR: mismatch in the size of the trig_EF_trigmuonef_track_CB_phi vector: " << trig_EF_trigmuonef_track_CB_phi->size() << "  --> expected: " <<  trig_EF_trigmuonef_n << std::endl;
    return false;
  }
  
  double dRMax = 100;
 
  for (unsigned int imu=0; imu<trig_EF_trigmuonef_n; ++imu) {

    if ( !trig_EF_trigmuonef_signature->at(imu) ) continue;
    unsigned int ntracks = trig_EF_trigmuonef_track_CB_eta->at(imu).size();

    for (unsigned int itrack=0; itrack<ntracks; ++itrack) {
      
      double etaEF = trig_EF_trigmuonef_track_CB_eta->at(imu).at(itrack);
      double phiEF = trig_EF_trigmuonef_track_CB_phi->at(imu).at(itrack);

      double dphi = TVector2::Phi_mpi_pi(phiEF - mu_staco_phi);
      double deta = mu_staco_eta - etaEF;
      double deltaR=sqrt(dphi*dphi + deta*deta);
      if ( deltaR < dRMax ) {
	dRMax = deltaR;
	EFindex = imu;
	EFtrackindex = itrack;
      }
    }
  }
 
  if ( dRMax <= 0.15 ) {
    return true;
  } 

  EFindex = -1;
  EFtrackindex = -1;
  return false;
}

