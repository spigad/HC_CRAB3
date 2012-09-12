// This file's extension implies that it's C, but it's really -*- C++ -*-.
// $Id$
/**
 * @file SUSYTools/SUSYTools/SUSYObjDef.h
 * @author Renaud Bruneliere <Renaud.Bruneliere@cern.ch>
 * @date Feb, 2011
 * @brief Baseline SUSY object definitions.
 */

#ifndef SUSYTOOLS_SUSYOBJDEF_H
#define SUSYTOOLS_SUSYOBJDEF_H

#include <vector>
#include <string>
#include "TVector2.h"
#include "TLorentzVector.h"
#include "TRandom3.h"
#include "egammaAnalysisUtils/checkOQ.h"
#include "egammaAnalysisUtils/EnergyRescaler.h"
#include "egammaAnalysisUtils/egammaSFclass.h"
#include "MuonMomentumCorrections/SmearingClass.h"
#include "MuonEfficiencyCorrections/AnalysisMuonEfficiencyScaleFactors.h"
#include "JetSelectorTools/TJetCleaningTool.h"
#include "SUSYTools/JetID.hpp"
#include "SUSYTools/FudgeMCTool.h"
#include "JetUncertainties/MultijetJESUncertaintyProvider.h"
#include "JetResolution/JERProvider.h"
#include "MissingETUtility/METUtility.h"

namespace JetErr
{
  typedef enum  { JESDOWN,JESUP,NONE,JER } Syste;
}

class Container {
public:
  double pt, phi, eta;
  int index;

  inline bool operator > (const Container & other) const
  {
    if (pt>other.pt) return true;
    return false;
  }
  inline bool operator < (const Container & other) const
  {
    if (pt<other.pt) return true;
    return false;
  }
};

class SUSYObjDef : public TNamed
{
public:
  SUSYObjDef();
  ~SUSYObjDef();

  /// You should always call this function
  /// muon_momentum_dir = path to muon momentum corrections
  ///                     default path is $ROOTCOREDIR/../MuonMomentumCorrections/share/
  /// muon_sf_dir = path to muon scale factor MC corrections
  ///               default path is $ROOTCOREDIR/../MuonEfficiencyCorrections/share/
  /// muon_type = type of muon used for the scale factors
  ///             default is STACO_CB_plus_ST = STACO combined plus segment tagged muons
  /// muon_sf_int_lumi = respective integrated luminosities for data periods B,D,E,F,G,H,K+
  ///                    default values are taken from 
  ///                    data11_7TeV.periodAllYear_DetStatus-v35-pro09-03_CoolRunQuery-00-04-00_Susy.xml
  /// jetSelectorTools_file = JetSelectorTools python steering file
  ///                         default file is $ROOTCOREDIR/../JetSelectorTools/python/ConfiguredTJetCleaningTools.py
  /// jetSelectorTools_cfg = python method use to configure jet cleaning cuts, default are Loose cleaning cuts
  void initialize(std::string muon_momentum_dir = "",
                  std::string muon_sf_dir = "",
                  std::string muon_type = "STACO_CB_plus_ST",
                  std::string jes_file = "",
                  std::string jes_quarkgluon_file = "",
                  std::string jes_closebyjet_file = "",
                  std::string jer_file = "",
                  std::string jetSelectorTools_file = "",
                  std::string jetSelectorTools_cfg = "ConfiguredTJetCleaningTool_Loose()");
  void initialize(std::vector<double>& muon_sf_int_lum,
                  std::string muon_momentum_dir = "",
                  std::string muon_sf_dir = "",
                  std::string muon_type = "STACO_CB_plus_ST",
                  std::string jes_file = "",
                  std::string jes_quarkgluon_file = "",
                  std::string jes_closebyjet_file = "",
                  std::string jer_file = "",
                  std::string jetSelectorTools_file = "",
                  std::string jetSelectorTools_cfg = "ConfiguredTJetCleaningTool_Loose()");

  /// You should always call this function
  void finalize();

  /// Clear internal variables (this method should be called once per event)
  void Reset();

  /// Baseline SUSY Electron object definition
  /// Variable used for electron smearing systematic: int value 0:nominal, 1: smearcorr_down, 2: smearcorr_up
  bool IsElectron(int iEl, int RunNumber,
                  float el_cl_eta, float el_cl_phi, float el_cl_E, float el_tracketa, float el_trackphi,
                  int el_author, int el_mediumPP, unsigned int el_OQ, int el_nPixHits, int el_nSCTHits, float el_wet,
                  bool isData, float etcut = 20000., float etacut = 2.47, bool ischeckOQ = false, int value = 0,
                  bool isAF2 = false);
  /// Additionnal SUSY Electron criteria for signal selection: relative isolation cut on ptcone20/pt
  /// In order to be on plateau of e20_medium, offline cut is set to 25 GeV
  bool IsSignalElectron(int iEl, int el_tightPP, float el_ptcone20, 
                        float etcut = 25000., float isocut = 0.1);
  /// Electron/Photon crack veto
  bool IsInCrack(float el_cl_eta) { return (fabs(el_cl_eta) > 1.37 && fabs(el_cl_eta) < 1.52); }
  /// Electron helper functions
  void SetElecTLV(int iEl,
                  float el_cl_eta, float el_cl_phi, float el_cl_E, float el_tracketa, float el_trackphi,
                  int el_nPixHits, int el_nSCTHits, bool isData, int value, bool isAF2);
  TLorentzVector  GetElecTLV()        { return m_el[m_iEl]; }
  TLorentzVector& GetElecTLV(int iEl) { return m_el[iEl]; }

  /// Baseline SUSY Photon object definition
  /// Selection cuts are taken from 
  /// https://twiki.cern.ch/twiki/bin/view/AtlasProtected/SMDirectPhoton2011Common
  /// isloose == false => use PhotonIDTool::PhotonCutsTight(6)
  /// isloose == true  => use PhotonIDTool::PhotonCutsLoose(3)
  bool IsPhoton(int iPh, int RunNumber,
                float ph_cl_pt, float ph_cl_eta, float ph_cl_phi, float ph_cl_E, float ph_etas2,
                unsigned int ph_isEM, unsigned int ph_OQ, int ph_hasconv, int ph_isConv, 
                float ph_reta, float ph_rphi, float ph_Ethad1, float ph_Ethad, 
                float ph_E277, float ph_E237, float ph_E233, float ph_weta2, float ph_f1,
                float ph_emaxs1, float ph_Emax2, float ph_Emins1, float ph_fside, float ph_wstot, float ph_ws3,
                bool isData, float ptcut = 20000., float etacut = 2.37, bool ischeckOQ = false, int value = 0,
                bool isloose = false, bool isAF2 = false);
  /// Additionnal SUSY Photon criteria for signal selection: isolation cut on Etcone40 (corrected)
  /// Isolation variables are described there:
  /// https://twiki.cern.ch/twiki/bin/view/AtlasProtected/CaloIsolationCorrections
  /// In order to be on plateau of EF_g80_loose, offline cut is set to 85 GeV
  bool IsSignalPhoton(int iPh, float ph_Etcone40_corrected,
                      float ptcut = 85000., float isocut = 3000.);
  bool IsSignalPhotonCompIso(int iPh, float ph_Etcone40_ED_corrected, float ph_Etcone40,
                             float ph_cl_E, float ph_cl_eta, float ph_etas2, float ph_etap, float ph_isConv,
                             bool isData, float ptcut = 85000., float isocut = 3000.);
  /// Photon helper functions
  void SetPhotonTLV(int iPh,
                    float ph_cl_pt, float el_cl_eta, float el_cl_phi, float el_cl_E, float ph_etas2,
                    bool isData, int value, bool isAF2);
  TLorentzVector  GetPhotonTLV()        { return m_ph[m_iPh]; }
  TLorentzVector& GetPhotonTLV(int iPh) { return m_ph[iPh]; }

  double scaleForFFUnconvertedPhoton(double pT, double eta, bool isconv);

  /// Baseline SUSY Muon object definition
  /// Variable used for muon smearing systematic: THESTRING {"", "MSLOW", "MSUP", "IDLOW", "IDUP"}
  bool IsMuon(int iMu,
              float mu_staco_pt, float mu_staco_eta, float mu_staco_phi, float mu_staco_E,
              float mu_staco_me_qoverp_exPV, float mu_staco_id_qoverp_exPV,
              float mu_staco_me_theta_exPV, float mu_staco_id_theta_exPV, float mu_staco_id_theta,
              int mu_staco_isCombinedMuon, int mu_staco_isSegmentTaggedMuon,
              int mu_staco_loose, int mu_staco_expectBLayerHit, int mu_staco_nBLHits, int mu_staco_nPixHits,
              int mu_staco_nPixelDeadSensors, int mu_staco_nPixHoles, int mu_staco_nSCTHits,
              int mu_staco_nSCTDeadSensors, int mu_staco_nSCTHoles, int mu_staco_nTRTHits, int mu_staco_nTRTOutliers,
              bool isData, float ptcut = 10000., float etacut = 2.4, std::string THESTRING = "");
  /// Additionnal SUSY Signal Muon criteria: absolute isolation cut on ptcone20
  /// In order to be on plateau of mu18, offline cut is set to 20 GeV
  bool IsSignalMuon(int iMu, float mu_staco_ptcone20, float ptcut = 20000., float isocut = 1800.);
  /// Cosmic rejection cuts
  /// WARNING: as method is named, it returns TRUE if |z0PV|>1mm OR |d0PV|>0.2mm, i.e. if a cosmic candidate is found
  bool IsCosmicMuon(float mu_staco_z0_exPV, float mu_staco_d0_exPV, float z0cut = 1., float d0cut = 0.2);
  /// Muon quality rejection cuts at the moment based on sigma(q/p)/|q/p|
  /// This cut should be checked on every muon passing IsMuon and before overlap removal
  /// If a muon is bad (method returns TRUE), then you should reject the event (Etmiss computation cannot be trusted)
  bool IsBadMuon(float mu_staco_qoverp_exPV, float mu_staco_cov_qoverp_exPV, float qopcut = 0.2);
  /// Muon helper functions
  void SetMuonTLV(int iMu,
                  float mu_staco_pt, float mu_staco_eta, float mu_staco_phi, float mu_staco_E,
                  float mu_staco_me_qoverp_exPV, float mu_staco_id_qoverp_exPV,
                  float mu_staco_me_theta_exPV, float mu_staco_id_theta_exPV, 
                  int mu_staco_isCombinedMuon, bool isData, std::string THESTRING);
  TLorentzVector  GetMuonTLV()        { return m_mu[m_iMu]; }
  TLorentzVector& GetMuonTLV(int iMu) { return m_mu[iMu]; }

  /// Check if an offline muon is matched to the muon used by trigger
  bool MuonHasTriggerMatch(double mu_staco_eta,
			   double mu_staco_phi,
			   vector<int> *trig_EF_trigmuonef_signature,
			   int& EFindex,
			   int& EFtrackindex,
			   unsigned int trig_EF_trigmuonef_n,
			   vector<vector<float> > *trig_EF_trigmuonef_track_CB_eta,
			   vector<vector<float> > *trig_EF_trigmuonef_track_CB_phi,
			   vector<vector<int> > *trig_EF_trigmuonef_track_CB_hasCB);

  /// Baseline SUSY Tau object definition
  bool IsTau(float tau_Et, float tau_eta, float tau_charge,
	     int tau_author, int tau_numTrack, int tau_JETBDTLoose, int tau_JETBDTMedium, int tau_JETBDTTight, int tau_electronVetoTight,
	     bool isData, float ptcut = 15000., float etacut = 2.5, int bdtoneprongcut = 3, int bdtthreeprongcut = 2);

  /// SUSY Jet object definition
  bool IsJet(int iJet, float jet_AntiKt4TopoNewEM_pt, float jet_AntiKt4TopoNewEM_eta, float jet_AntiKt4TopoNewEM_phi,
             float jet_AntiKt4TopoNewEM_E, float jet_AntiKt4TopoNewEM_emscale_eta, 
             float jet_AntiKt4TopoNewEM_emfrac, float jet_AntiKt4TopoNewEM_hecf,
             float jet_AntiKt4TopoNewEM_LArQuality, float jet_AntiKt4TopoNewEM_HECQuality, float jet_AntiKt4TopoNewEM_AverageLArQF, 
             float jet_AntiKt4TopoNewEM_Timing, float jet_AntiKt4TopoNewEM_sumPtTrk, 
             float jet_AntiKt4TopoNewEM_fracSamplingMax,
             float jet_AntiKt4TopoNewEM_NegativeE, int jet_AntiKt4TopoNewEM_flavor_truth_label, 
             bool isData, float ptcut = 20000., float etacut = 2.8,
             JetID::BadJetCategory criteria = JetID::VeryLooseBad,
	     JetErr::Syste whichsyste = JetErr::NONE,
	     bool nojetsmear = false,
	     double drmin=0);
  /// Jet helper functions
  void SetJetTLV(int iJet, float jet_AntiKt4TopoNewEM_pt, float jet_AntiKt4TopoNewEM_eta, 
                 float jet_AntiKt4TopoNewEM_phi, float jet_AntiKt4TopoNewEM_E);
  TLorentzVector  GetJetTLV()         { return m_jet[m_iJet]; }
  TLorentzVector& GetJetTLV(int iJet) { return m_jet[iJet]; }

  // Smearing jets, it actually changes the values in the AntiKt4TopoNewEM_pt and similar vectors

  void SmearJets(std::vector<float>* jetpt,
		 std::vector<float>* jeteta,
		 std::vector<float>* jetphi,
		 std::vector<float>* jete);

  /// SUSY B-Jet object definition
  /// jet_AntiKt4TopoNewEM_flavor_weight_xxx should be replaced by [SV0, JetFitterCOMBNN, Comb, JetProb]
  /// corresponding to jetTagger name.
  /// op is operating point for a given tagger. You can find the different thresholds on:
  ///   * r17 analysis: https://twiki.cern.ch/twiki/bin/view/AtlasProtected/BTagCalibWinter2012
  ///   * r16 analysis: https://twiki.cern.ch/twiki/bin/view/AtlasProtected/Analysis16
  /// By default (when op=999), preliminary r17 operating points are used
  bool IsBJet(float jet_AntiKt4TopoNewEM_flavor_weight_xxx, std::string jetTagger = "JetFitterCOMBNN", float op = 999.);

  /// Basic LAr hole veto
  bool IsLArHoleVeto(float jet_AntiKt4TopoNewEM_pt, float jet_AntiKt4TopoNewEM_eta, float jet_AntiKt4TopoNewEM_phi,
                     float jet_AntiKt4TopoNewEM_BCH_CORR_JET, float jet_AntiKt4TopoNewEM_BCH_CORR_CELL, 
                     bool kIsData, float ptcut = 40000., int RunNumber = 180614);

  /// Is an object pointing in the LAr hole
  bool IsLArHole(float eta, float phi, 
                 float etamin = -0.1, float etamax = 1.5, 
                 float phimin = -0.9, float phimax = -0.5) {
    if (eta < etamin || eta > etamax) return false;
    if (phi < phimin || phi > phimax) return false;
    return true;
  }

  /// Etmiss computation via MissingEtUtility package. 
  /// Warning: it requires:
  ///  - m_mu array to be filled (muon selection applied) before calling this function
  ///  - m_el array to be filled (baseline electron selection with a 10 GeV pt veto) before calling 
  TVector2 GetMET(const std::vector<float>* jetpt,
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
		  float METCellOutetx, float METCellOutety, float METCellOutsumet,
		  float METRefGamma_etx, float METRefGamma_ety, float METRefGammasumet,
		  const std::vector<int>& vmuidx,
		  const std::vector<float>* mu_staco_ms_qoverp, 
		  const std::vector<float>* mu_staco_ms_theta, 
		  const std::vector<float>* mu_staco_ms_phi, 
		  const std::vector<float>* mu_staco_charge,
		  JetErr::Syste syste=JetErr::NONE);
  TVector2 computeMETComponent(string whichcomponent,
			       JetErr::Syste syste=JetErr::NONE);

  /// Primary vertex cut
  bool IsGoodVertex(std::vector<int>* vx_nTracks);

  /// Method used as python wrapper to get tightPP electron reco efficiency (and uncertainty)
  /// mode 0: apply both id efficiency SF (default is tightPP) and reco+trkqual efficiency SF
  /// mode 1: apply only id efficiency SF (default is tightPP)
  /// mode 2: apply only reco+trkqual efficiency SF 
  ///    * Loose SF (set=0)
  ///    * Medium SF (set=1)
  ///    * Tight SF (set=2)
  ///    * e20_medium trigger SF (set=3) (use set 8 or 10 for release 17 2011 data/MC11a)
  ///    * reco+trkqual SF (set=4)
  ///    * Loose++ SF (set=5)
  ///    * Medium++ SF (set=6)
  ///    * Tight++ SF (set=7)
  /// release 15 2010 data/MC09 (rel=0)
  /// release 16 2010 data/MC10 (rel=1)
  /// release 16.6 estimated from 2010 data (rel=2)  / 
  /// release 16.6 estimated from 2011 data "EPS recommendations" (rel=3) /
  /// release 16.6 estimated from 2011 data "EPS recommendations" including Jpsi measurements (rel=4)
  /// release 17 estimated from 2011 data/MC11a "CERN council recommendations" (rel=5)
  /// release 17 estimated from 2011 data/MC11a/b/c "Moriond recommendations" G4 FullSim MC (rel=6)
  /// release 17 estimated from 2011 data/MC11a/b/c "Moriond recommendations" AFII MC (rel=7)
  /// measured with probes in the 20-50 GeV range (range=0) or 30-50 GeV (range=1) 
  /// and correcting (etcorrection=1) or not (etcorrection=0) for the ET-dependence
  /// el_cl_et := cluster_E/cosh(track_eta)
  float GetSignalElecSF(float el_cl_eta, float el_cl_et, int set = 7, int rel = 6, int mode = 0, int range = 0) { 
    float sf = 1.;
    if (mode == 0 || mode == 1) sf *= m_egammaSFclass.scaleFactor(el_cl_eta,el_cl_et,set,range,rel).first;
    if (mode == 0 || mode == 2) sf *= m_egammaSFclass.scaleFactor(el_cl_eta,el_cl_et,4,range,rel).first;
    return sf; 
  }
  float GetSignalElecSFUnc(float el_cl_eta, float el_cl_et, int set = 7, int rel = 6, int mode = 0, int range = 0) { 
    float sfUnc = 0.;
    if (mode == 0 || mode == 1) sfUnc = m_egammaSFclass.scaleFactor(el_cl_eta,el_cl_et,set,range,rel).second;
    if (mode == 0 || mode == 2) sfUnc = sqrt(sfUnc*sfUnc + m_egammaSFclass.scaleFactor(el_cl_eta,el_cl_et,4,range,rel).second*m_egammaSFclass.scaleFactor(el_cl_eta,el_cl_et,4,range,rel).second);
    return sfUnc;
  }
  ///    * e20_medium trigger SF w.r.t Medium++ offline (set=8)
  ///    * e20_medium MC efficiency w.r.t Medium++ offline (set=9)
  ///    * e20_medium trigger SF w.r.t Tight++ offline (set=10)
  ///    * e20_medium MC efficiency w.r.t Tight++ offline (set=11)
  ///    * e22_medium trigger SF w.r.t Medium++ offline (set=12)
  ///    * e22_medium MC efficiency w.r.t Medium++ offline (set=13)
  ///    * e22_medium trigger SF w.r.t Tight++ offline (set=14)
  ///    * e22_medium MC efficiency w.r.t Tight++ offline (set=15)
  ///    * e22vh_medium1 trigger SF (using e22_medium1 on MC11a) w.r.t Medium++ offline (set=16)
  ///    * e22_medium1 MC efficiency w.r.t Medium++ offline (set=17)
  ///    * e22vh_medium1 trigger SF (using e22_medium1 on MC11a) w.r.t Tight++ offline (set=18)
  ///    * e22_medium1 MC efficiency w.r.t Tight++ offline (set=19)
  ///    * e20_medium MC efficiency w.r.t Loose++ offline (set=20)
  ///    * e22_medium1 MC efficiency w.r.t Loose++ offline (set=21)
  ///    * e22vh_medium1 MC efficiency w.r.t Loose++ offline (set=22)
  float GetTrigElecSF(float el_cl_eta, float el_cl_et = 25000., int set = 10, int rel = 6, int range = 0) { 
    return m_egammaSFclass.scaleFactor(el_cl_eta,el_cl_et,set,range,rel).first; 
  }
  float GetTrigElecSFUnc(float el_cl_eta, float el_cl_et = 25000., int set = 10, int rel = 6, int range = 0) { 
    return m_egammaSFclass.scaleFactor(el_cl_eta,el_cl_et,set,range,rel).second; 
  }

  /// Method used as python wrapper to get muon reco efficiency (and uncertainty)
  /// We assume that isolation does not introduce an additionnal bias
  float GetSignalMuonSF(int iMu);
  float GetSignalMuonSFUnc(int iMu);

  // Methods to retrieve the different tools
  egammaOQ&               GetegammaOQ()       { return m_egammaOQ; }
  eg2011::EnergyRescaler& GetEnergyRescaler() { return m_eRescale; }
  egammaSFclass&          GetegammaSFclass()  { return m_egammaSFclass; }
  MuonSmear::SmearingClass*                     GetSmearingClass()                  { return m_mcp_smear; }
  Analysis::AnalysisMuonEfficiencyScaleFactors* GetMuonSFClass()                    { return m_muon_sf; }
  MultijetJESUncertaintyProvider*               GetMultijetJESUncertaintyProvider() { return m_myJes; }
  JERProvider*            GetJERProvider()    { return m_myJER; }
  METUtility*             GetMETUtility()     { return _metUtility; }

private:
  /// Array of TLorentzVector which can be used later in analysis (like for Etmiss computation)
  static const unsigned int m_NPartMax = 100;
  std::vector<TLorentzVector> m_el;
  std::vector<TLorentzVector> m_ph;
  std::vector<TLorentzVector> m_mu;
  std::vector<TLorentzVector> m_jet;
  /// Index of last object in array
  int m_iEl;
  int m_iPh;
  int m_iMu;
  int m_iJet;

  TRandom3 m_random; //! don't persisitify

  /// Class used to detect dead material in LAr
  egammaOQ m_egammaOQ; //! don't persistify
  /// Class used to rescale electron energy in data and smear electron energy in MC
  eg2011::EnergyRescaler m_eRescale; //! don't persistify
  /// Class used to correct MC electron reco efficiencies
  egammaSFclass  m_egammaSFclass; //! don't persistify

  /// Class used to correct photon shower shapes in MC
  SUSY::FudgeMCTool m_FFTool; //! don't persistify
  
  /// Class used to smear muon energy in MC
  MuonSmear::SmearingClass* m_mcp_smear;
  /// Class used to rescale MC muon reco efficiencies
  Analysis::AnalysisMuonEfficiencyScaleFactors* m_muon_sf;

  /// Class used to apply jet cleaning
  Root::TJetCleaningTool* m_JetCleanTool;
  // JES
  MultijetJESUncertaintyProvider* m_myJes;
  std::vector<float> _forMETJesUp;
  std::vector<float> _forMETJesDown;
  std::vector<float> _forMETJerUp;
  std::vector<float> _forMETJerDown;
  // JER
  JERProvider* m_myJER;
  // MET
  METUtility* _metUtility;
  
  #ifndef SUSY_ATHENA
  ClassDef(SUSYObjDef,1)
  #endif  
};

#endif // not SUSYTOOLS_SUSYOBJDEF_H
