#ifndef Analysis_h
#define Analysis_h

#include <iostream>
#include <TH1F.h>
#include <TH2F.h>
#include <JESUncertaintyProvider.h>
#include <MultijetJESUncertaintyProvider.h>
#include <EMJESfix.hpp>
#include "checkOQ.h"
//#include "SmearingClass.h"

class Analysis
{

  public:
    //Constructors
    Analysis(D3PDSelector * inst); //Constructor with D3PD Selector Object

    //Destructor
    virtual ~Analysis() {}; //default destructor

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
    void fill_histo(double mc_event_weight, unsigned int nbin, float MET, float inv_mass, float m_eff, float m_t, float htmiss, int isOS);

    
    //jet cleaning variables
    float HECF(unsigned int iJet,
                 std::vector<float>* jet_AntiKt4H1Topo_emscale_E,
                 std::vector<float>* jet_AntiKt4H1Topo_e_HEC0,
                 std::vector<float>* jet_AntiKt4H1Topo_e_HEC1,
                 std::vector<float>* jet_AntiKt4H1Topo_e_HEC2,
                 std::vector<float>* jet_AntiKt4H1Topo_e_HEC3);

    float TileGap3F(unsigned int iJet,
		std::vector<float>* jet_AntiKt4H1Topo_emscale_E,
		std::vector<float>* jet_AntiKt4H1Topo_e_TileGap3);
		
    bool IsBad(unsigned int iJet,
	   float hecF,
	   std::vector<float>* jet_AntiKt4H1Topo_n90,
	   std::vector<float>* jet_AntiKt4H1Topo_timing,
	   std::vector<float>* jet_AntiKt4H1Topo_quality,
	   std::vector<float>* jet_AntiKt4H1Topo_emfrac);
	   		
    bool IsUgly(unsigned int iJet,
	    float tileGap3F,
	    std::vector<float>* jet_AntiKt4H1Topo_BCH_CORR_CELL);

    float IsSelMuo(unsigned int iMuo);  //returns smeared pt
    bool IsSelEle(unsigned int iEle);
    bool IsRobusterTight(unsigned int iEle);
    bool IsIsolated(unsigned int iEle);
	    
    bool isGRL(int runNumber, int lumiBlock);
    std::string getTriggerElectron(int runNumber);
    std::string getTriggerMuon(int runNumber);
    Int_t CheckGRL(Int_t run, Int_t lb); 
    int doGenCutDrellYan(Long64_t entry); 
    int getProcess(Long64_t entry);
    double getPileUpWeight(int nGoodPV);      	    		        
    
    //Histograms
    
    TH1F* some_histo;

    TH2F* h_e_nb;
    TH2F* h_e_eta;
    TH2F* h_e_pt;
    TH2F* h_e_phi;
    TH2F* h_e_etcone20;
    TH2F* h_e_charge;
    
    TH2F* h_mu_nb;
    TH2F* h_mu_eta;
    TH2F* h_mu_pt;
    TH2F* h_mu_phi;
    TH2F* h_mu_etcone20;
    TH2F* h_mu_charge;
    
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
    
    TH2F* h_cutflow_susy;
    TH2F* h_nGoodPV;
    
    TH1F* cutflow_histo;
    TH1F* runNumber_histo;
    TH1F* controlregion_histo; 
    TH1F* signalregion_histo;
    
    int m_cutflow[35];
    int eventNumber, runNumber;
    unsigned int bin;
    double mc_evt_weight;
    
  //lepton and jet variables
  unsigned int n_ele, n_muo, n_jet, nGoodPV;  
  std::vector<float> ele_eta, ele_cl_eta, ele_pt, ele_E, ele_px, ele_py, ele_phi, ele_etcone20, ele_charge;  
  std::vector<float> muo_eta, muo_pt, muo_E, muo_px, muo_py, muo_phi, muo_etcone20, muo_charge, muo_z0;
  std::vector<float> jet_eta, jet_pt, jet_px, jet_py, jet_phi, jet_jes, jet_E;  

   int susyprocess;
  SmearingClass mcp_smear;

  protected:
    D3PDSelector * m_sel;


};

#endif

