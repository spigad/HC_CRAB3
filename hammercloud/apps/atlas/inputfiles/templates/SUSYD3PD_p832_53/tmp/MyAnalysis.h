#ifndef Analysis_h
#define Analysis_h

#include <iostream>
#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <THnSparse.h>
//#include <JESUncertaintyProvider.h>
//#include <EMJESfix.hpp>
#include "SUSYTools/SUSYObjDef.h"
#include "GoodRunsLists/TGoodRunsListReader.h"
#include "PileupReweighting/TPileupReweighting.h"

class MyAnalysis
{

  public:
    //Constructors
    MyAnalysis(D3PDSelector * inst); //Constructor with D3PD Selector Object

    //Destructor
    virtual ~MyAnalysis() {}; //default destructor

    //Analysis Methods
    virtual unsigned int Pre_OPS_OR(Long64_t entry);
    virtual unsigned int Between_OPS_and_OR(Long64_t entry);
    virtual void doAnalysis(Long64_t entry);
    virtual void finalizeEvent(Long64_t entry);
    
    //static postAnalysis method (Drawing/Saving)
    static void postAnalysis (TSelectorList* fOutput);
    
    //ST calc
    double CalcTranSphericity(double sumpx2,double sumpy2,double sumpxpy);
    
    //sort array in descending order
    void sort(float *lep_pt, float *lep_px, float *lep_py, float *lep_pz, float *lep_e, float *lep_isMuon, float *lep_charge, unsigned int n_leptons);

    void fill_histo(double mc_event_weight, unsigned int nbin, float MET);
    void fill_histo(double mc_event_weight, unsigned int nbin);
   void fill_histo(double mc_event_weight, unsigned int nbin, float MET, float inv_mass, float m_eff, float m_t, float htmiss, int isOS);
        
    int getIndex(std::string contname, float pt, float eta, float phi);
    	    
    std::string getTriggerElectron(int runNumber);
    std::string getTriggerMuon(int runNumber);
    int doGenCutDrellYan(Long64_t entry); 
    int getProcess(Long64_t entry);
    double getPileUpWeightElectron(int nGoodPV);      	    		        
    double getPileUpWeightMuon(int nGoodPV);      	    		        
    double getMuonTriggerWeight(int index);  
    
    bool  PassedTriggerL1(double etaOff, double phiOff, int &EFindex, 
           unsigned int nEFObject, std::vector<float> *EFetaVector, std::vector<float> *EFphiVector);
    bool passEM10VH(float eta, float Et, float VH);     
    bool passEM16VH(float eta, float Et, float VH);     
    bool passEM18VH(float eta, float Et, float VH);     
    double getMuonTriggerWeight(float pt, float eta, float phi, float ptcone20, int isCom);  
    float getMuonTriggerMatch(int muo_off_index, string trig_name_mu, float DeltaRMin) ;   
    float getElectronTriggerMatch(int ele_off_index, string trig_name_ele, float DeltaRMin) ;   
    float MuonHasTriggerMatch(string trig_name_mu, float DeltaRMin, int trig_EF_trigmuonef_n, vector<int> *trig_EF_trigmuonef_track_n, 
       float mu_staco_pt, float mu_staco_eta, float mu_staco_phi, vector<vector<float> > *trig_EF_trigmuonef_track_CB_pt, 
       vector<vector<float> > *trig_EF_trigmuonef_track_CB_eta, vector<vector<float> >
       *trig_EF_trigmuonef_track_CB_phi, vector<vector<int> > *trig_EF_trigmuonef_track_CB_hasCB);          
    bool MuonHasL1L2TriggerMatch(float Pt, float DeltaRMin, int trig_onl_mu_n, float mu_staco_pt, float mu_staco_eta, float mu_staco_phi, 
      vector<float> *trig_onl_mu_pt, vector<float> *trig_onl_mu_eta, vector<float> *trig_onl_mu_phi);
    float MuonHasTriggerMatch_EFmu6(int trig_EF_trigmuonef_n, vector<int> *trig_EF_trigmuonef_track_n, float mu_staco_pt, float mu_staco_eta, float mu_staco_phi, 
        vector<vector<float> > *trig_EF_trigmuonef_track_CB_pt, vector<vector<float> > *trig_EF_trigmuonef_track_CB_eta, 
	vector<vector<float> > *trig_EF_trigmuonef_track_CB_phi, vector<vector<int> > *trig_EF_trigmuonef_track_CB_hasCB);
     
      
    //Histograms
    
    TH1F* some_histo;

    TH2F* h_e_nb;
    TH2F* h_e_eta;
    TH2F* h_e_pt;
    TH2F* h_e_phi;
    TH2F* h_e_ptcone20;
    TH2F* h_e_charge;
    TH2F* h_el_eta;
    TH2F* h_el_phi;
    TH2F* h_el_pt;
    TH2F* h_e2l_eta;
    TH2F* h_e2l_phi;
    TH2F* h_e2l_pt;
    TH2F* h_el_trg_eta;
    TH2F* h_el_trg_phi;
    TH2F* h_el_trg_pt;
    TH3F* h_el_trg_eta_phi;
    TH3F* h_el_trg_pt_eta;
    
    TH2F* h_mu_nb;
    TH2F* h_mu_eta;
    TH2F* h_mu_pt;
    TH2F* h_mu_phi;
    TH2F* h_mu_ptcone20;
    TH2F* h_mu_charge;
    TH2F* h_mul_eta;
    TH2F* h_mul_phi;
    TH2F* h_mul_pt;
    TH2F* h_mu2l_eta;
    TH2F* h_mu2l_phi;
    TH2F* h_mu2l_pt;
    TH2F* h_mu_trg_eta;
    TH2F* h_mu_trg_phi;
    TH2F* h_mu_trg_pt;
    TH2F* h_mu_trg_eta_barrel;
    TH2F* h_mu_trg_phi_barrel;
    TH2F* h_mu_trg_pt_barrel;
    TH2F* h_mu_trg_eta_endcap;
    TH2F* h_mu_trg_phi_endcap;
    TH2F* h_mu_trg_pt_endcap;
    TH3F* h_mu_trg_eta_phi;
    TH3F* h_mu_trg_pt_eta;
    
    TH2F* h_jet_nb;
    TH2F* h_jet_eta;
    TH2F* h_jet_phi;
    TH2F* h_jet_pt;
    TH2F* h_jetl_eta;
    TH2F* h_jetl_phi;
    TH2F* h_jetl_pt;
    TH2F* h_jet2l_eta;
    TH2F* h_jet2l_phi;
    TH2F* h_jet2l_pt;
    
    TH2F* h_met;
    TH2F* h_meff;
    TH2F* h_invmass;
    TH2F* h_mt;
    TH2F* h_invmass_OS;
    TH2F* h_invmass_SS;
    TH2F* h_met_OS;
    TH2F* h_met_SS;
    TH2F* h_htmiss_OS;
    TH2F* h_htmiss_SS;
    
    TH2D* h_cutflow_susy;
    TH2F* h_nGoodPV;

    TH1F* h_trg1;
    TH1F* h_trg1_dR;
    TH1F* h_trg1_d3pd;
    TH1F* h_trg1_d3pd_dR;
    TH1F* h_trg1_deltaR;
    TH1F* h_trg2;
    TH1F* h_trg2_dR;
    TH1F* h_trg2_d3pd;
    TH1F* h_trg2_d3pd_dR;
    TH1F* h_trg2_deltaR;
    
    
    TH1D* cutflow_histo;
    TH1D* runNumber_histo;
    
    int m_cutflow[35];
    int eventNumber, runNumber;
    unsigned int bin;
    double mc_evt_weight;
    
  //lepton and jet variables
  unsigned int n_ele, n_muo, n_jet, nGoodPV;
  std::vector<unsigned int> ele_isEM;   
  std::vector<float> ele_eta, ele_tracketa, ele_trackphi,ele_cl_eta, ele_cl_phi, ele_pt, ele_cl_E, ele_phi, ele_ptcone20, ele_etcone20, ele_et, ele_charge;  
  std::vector<float> muo_eta, muo_pt, muo_phi, muo_ptcone20, muo_charge, muo_d0, muo_z0;
  std::vector<float> jet_eta, jet_pt, jet_px, jet_py, jet_phi, jet_jes, jet_E, jet_BCH_CORR_JET, jet_BCH_CORR_CELL, jet_jvtxf, jet_flavor_weight_xxx;  
  std::vector<int> jet_isSignal;  
  float trg_eta, trg_pt, trg_phi;  

  int susyprocess;

//GRL reader

    Root::TGoodRunsListReader m_goodRunsListReader;
    Root::TGoodRunsList m_goodRunsList;

//PileUp reweighting
    Root::TPileupReweighting* m_tPileUp;

//Muon Trigger reweighting
    THnSparse * m_passes;
    THnSparse * m_trials;

  protected:
    D3PDSelector * m_sel;
    TTree * fChain;


};

#endif

