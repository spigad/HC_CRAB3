#include <iostream>
#include <fstream>
using namespace std;
#include "Analysis.h"
#include "TGraph.h"
#include "TMarker.h"
#include "TCanvas.h"
#include "TText.h"
#include "TBox.h"
#include "TMatrixDSym.h"
#include "TMatrixDSymEigen.h"
//#include "checkOQ.C"
#include "JetID.cpp"
#include "egammaSFclass.C"

//#include "JESUncertaintyProvider.cxx"
//#include "SuSyJERProvider.C"

#define KEEP_EVENT 0 //used in Pre_OPS_OR
#define SKIP_EVENT 1

//select stream
//#define ELECTRON 1
//#define MUON 1
#define MC 1
//#define PILEUP 1

//#define CUTFLOW_ELE
//#define CUTFLOW_MUO

//#define QCDBG

//default for MC
std::string L1_el = "EF_e10_medium"; 
std::string L1_mu = "EF_mu10_MSonly"; 

//saves histo to a dummy file if unset
#define HISTO 1

//#define JESPLUS
//#define JESMINUS
//#define JER

//#define ELESPLUS
//#define ELESMINUS
//#define ELERECO
//#define ELER

//#define MUOSPLUS
//#define MUOSMINUS
//#define MUORECO
//#define MUOR
 
bool verbose = false;
//bool verbose = true;

const char *name_cutflow[]={
  "no cut",
  "GRL cut",
#ifdef CUTFLOW_ELE  
  "trigger cut (trgEl)",
#else 
  #ifdef CUTFLOW_MUO 
  "trigger cut (trgMu)",
  #else
  "trigger cut ( EgammaStream && TrgEl) || (MuonsStream && TrgMu) || ( MC && (trgEl || trgMu))",
  #endif
#endif
  "jet cleaning",
  ">= 1 vertex with > 4 tracks (No cut on vertex type!!)",
  "Event veto (crack + cosmic muons)",
  "MUMU + EE + EMU", 

  "EE == (EgammaStream || MC) && trgEl && 2 electrons with pt > (20,10) GeV", 
  " && RobusterTight",
  " && pt > (20,20) GeV", 
  " && IsoEle: etcone20/pt >= 0.15 (not applied)",
  " && OS ",
  " && OS && MET cut > 100 GeV ",
  " && OS && MET cut > 125 GeV ",
  " && OS && MET cut > 150 GeV ",
  " && SS && MET cut > 60 GeV ",
  " && SS && MET cut > 80 GeV ",
  " && SS && MET cut > 100 GeV ",
  " && OS && IsoEle",
  " && OS && IsoEle && MET cut > 100 GeV ",
  " && OS && IsoEle && MET cut > 125 GeV ",
  " && OS && IsoEle && MET cut > 150 GeV ",
  " && SS && IsoEle && MET cut > 60 GeV ",
  " && SS && IsoEle && MET cut > 80 GeV ",
  " && SS && IsoEle && MET cut > 100 GeV ",
//  " && SS && IsoEle && MET cut > 150 GeV ",
    
  "EMU == ((EgammaStream || MC) && TrgEl && pt(e) > 20 GeV) || ((MuonStream || MC) && TrgMu && pt(mu) > 20 GeV) ", 
  " && RobusterTight",
  " && pt > (20,20) GeV", 
  " && ((pt(e) > pt(mu) && TrgEl) || (pt(mu) > pt(e) && TrgMu)) ",
  " && IsoEle: etcone20/pt >= 0.15 (not applied)",
  " && OS ",
  " && OS && MET cut > 100 GeV ",
  " && OS && MET cut > 125 GeV ",
  " && OS && MET cut > 150 GeV ",
  " && SS && MET cut > 60 GeV ",
  " && SS && MET cut > 80 GeV ",
  " && SS && MET cut > 100 GeV ",
  " && OS && IsoEle",
  " && OS && IsoEle && MET cut > 100 GeV ",
  " && OS && IsoEle && MET cut > 125 GeV ",
  " && OS && IsoEle && MET cut > 150 GeV ",
  " && SS && IsoEle && MET cut > 60 GeV ",
  " && SS && IsoEle && MET cut > 80 GeV ",
  " && SS && IsoEle && MET cut > 100 GeV ",
//  " && SS && IsoEle && MET cut > 150 GeV ",

  "MUMU == (MuonsStream || MC) && trgMu && 2 muons with pt > (20,10) GeV", 
  " && pt > (20,20) GeV", 
  " && OS ",
  " && OS && MET cut > 100 GeV ",
  " && OS && MET cut > 125 GeV ",
  " && OS && MET cut > 150 GeV ",
  " && SS && MET cut > 60 GeV ",
  " && SS && MET cut > 80 GeV ",
  " && SS && MET cut > 100 GeV ",
//  " && SS && MET cut > 150 GeV ",
  };
  
const char *name_controlregion[]={
 "MET<20 GeV, !(60<Mll<80 GeV), SS", "MET<20 GeV, !(60<Mll<80 GeV)","MET<20 GeV, !(60<Mll<80 GeV), 1 jet pt>50 GeV",  //QCD
 "MET<30 GeV, !(60<Mll<80 GeV), SS", "MET<30 GeV, !(60<Mll<80 GeV)","MET<30 GeV, !(60<Mll<80 GeV), 1 jet pt>50 GeV",
 "MET<40 GeV, !(60<Mll<80 GeV), SS", "MET<40 GeV, !(60<Mll<80 GeV)","MET<40 GeV, !(60<Mll<80 GeV), 1 jet pt>50 GeV",
 "MET<20 GeV, 80<Mll<100 GeV, OS","MET<30 GeV, 80<Mll<100 GeV, OS", "MET<40 GeV, 80<Mll<100 GeV, OS", // Z jets
 "30<MET<50 GeV, 40<MT<80 GeV", "40<MET<60 GeV, 40<MT<80 GeV", "40<MET<60 GeV, 60<MT<80" // W jets 
 };

const char *name_signalregion[]={
 "MET>20 GeV, 1 jet pt>20 GeV, MT>40 GeV", "MET>40 GeV, 1 jet pt>20 GeV, MT>40 GeV", "MET>60 GeV, 1 jet pt>20 GeV, MT>40 GeV",  
 "MET>20 GeV, 1 jet pt>30 GeV, MT>40 GeV", "MET>20 GeV, 1 jet pt>40 GeV, MT>40 GeV", "MET>20 GeV, 1 jet pt>50 GeV, MT>40 GeV",  
 "MET>60 GeV, 1 jet pt>20 GeV, MT>60 GeV", "MET>60 GeV, 1 jet pt>40 GeV, MT>80 GeV", "MET>60 GeV, 1 jet pt>20 GeV, MT>100 GeV",  
 "MET>40 GeV, 1 jet pt>30 GeV, MT>40 GeV", "MET>40 GeV, 1 jet pt>40 GeV, MT>40 GeV", "MET>40 GeV, 1 jet pt>50 GeV, MT>40 GeV",  
 "MET>60 GeV, 1 jet pt>30 GeV, MT>80 GeV", "MET>60 GeV, 1 jet pt>40 GeV, MT>80 GeV", "MET>60 GeV, 1 jet pt>50 GeV, MT>80 GeV"  
 };

int ndrellyan, ndrellyanNOT; 
bool drellyan = false;
int trgMu = 0;
int trgEl = 0;

bool ZVeto = false;

  ofstream myfile, debugfile, dileptonfile;

#include "functions.h"

  /*------------------------------------------------------------------------
    
                   Before OPS and OR  
  
  --------------------------------------------------------------------------*/

unsigned int Analysis::Pre_OPS_OR(Long64_t entry)
{
   (void)entry; //avoid compiler warnings
     
  
  //if (entry >= 1000) return SKIP_EVENT;

  /*------------------------------------------------------------------------
    
                   Recalculate some variables  
  
  --------------------------------------------------------------------------*/
 
  // recalculate MET
  
  float MET_x = m_sel->GetScalarVal<float>("MET_CellOut_etx");
  float MET_y = m_sel->GetScalarVal<float>("MET_CellOut_ety");
  float MET = sqrt(MET_x*MET_x + MET_y*MET_y); 
      
  /*------------------------------------------------------------------------
    
                   Cutflow  
  
  --------------------------------------------------------------------------*/

  bin =0;
  
  susyprocess = -1.;
  
  //get SUSY process if MC
#ifdef MC
  if (runNumber < 150000)  susyprocess = getProcess(entry);    
#endif
  
  runNumber = m_sel->GetScalarVal<int>("RunNumber");  
  eventNumber = m_sel->GetScalarVal<int>("EventNumber");  
  
  mc_evt_weight = 1.;
    
  //get event weight for ttbar
  if ((runNumber == 105200)||(runNumber == 105204)){  
//    cout << "MC sample, getting MC evt weight from file"<<endl;
    std::vector<double> mcevt_weight = m_sel->GetRawVector< std::vector<double> >( "mcevt_weight" );
    mc_evt_weight = mcevt_weight.at(0);
  }
  std::vector<int>vx_nTracks = m_sel->GetRawVector< std::vector<int> >("vx_nTracks");
  
// Get number of good primary vertices for MC pile-up reweighting

  bool gIsGoodPrimaryVertex = false;
  nGoodPV = 0;
  
  for (unsigned int ivx = 0; ivx < vx_nTracks.size(); ivx++)
    if (vx_nTracks.at(ivx) > 4) {
      gIsGoodPrimaryVertex = true;
      nGoodPV ++;  
    }

  // CUT 0 --- no cut  -- NO PILEUP REWEIGHTING at this point!!!
  fill_histo(mc_evt_weight, bin, MET);  
  runNumber_histo->Fill(runNumber,mc_evt_weight); 

// Pile-Up
#ifdef PILEUP
  if (!(
    (runNumber == 109281)||   //runs without pileup
    (runNumber == 209435)||
    (runNumber == 108326)||
    (runNumber == 105985)||
    (runNumber == 105986)||
    (runNumber == 105987)||
    (runNumber == 108321)||
    (runNumber == 108322)
    )) mc_evt_weight = mc_evt_weight*getPileUpWeight(nGoodPV) ;
#endif
   
  // CUT 1 - GRL from https://twiki.cern.ch/twiki/pub/AtlasProtected/GoodRunListSummer2010/

#ifdef MC
  if ((runNumber == 108319)||(runNumber == 108320)) {
     drellyan = true;
     ndrellyan++;     
     if (!(doGenCutDrellYan(entry))) return SKIP_EVENT;       
     ndrellyanNOT++;  
     
   }//end if drell yan
#else 
  int lumiBlock = m_sel->GetScalarVal<int>("lbn");  
  if ((runNumber > 150000)&&(runNumber < 200000))
    if (!(CheckGRL(runNumber, lumiBlock))) return SKIP_EVENT;    
#endif
  
  bin += 1;
  fill_histo(mc_evt_weight, bin, MET);  
  
  if (verbose) 
    if (eventNumber % 1 == 0) cout << "Event "<<eventNumber<< " run number " << runNumber<<endl;

// CUT 2 L1 cut
  
  int L1 = 0;  
  
  //default for MC
#ifdef MC
  trgEl = m_sel->GetScalarVal<int>(L1_el);
  trgMu = m_sel->GetScalarVal<int>(L1_mu);
  L1 = (trgEl||trgMu);
  #ifdef CUTFLOW_ELE
  L1 = (trgEl);
  #endif
  #ifdef CUTFLOW_MUO
  L1 = (trgMu);
  #endif  
#else
// overwrite if data  
  L1_el = getTriggerElectron(runNumber);
  trgEl = m_sel->GetScalarVal<int>(L1_el);
  L1_mu = getTriggerMuon(runNumber);  
  trgMu = m_sel->GetScalarVal<int>(L1_mu);
  #ifdef ELECTRON
  L1 = trgEl;
  #endif
  #ifdef MUON
  L1 = trgMu; 
  #endif
#endif 
  
  if (!(L1==1))  return SKIP_EVENT;

  bin += 1;  
  fill_histo(mc_evt_weight, bin, MET);  
    
// CUT 3 jet cleaning cuts 
  
  std::vector<float> jet_AntiKt4H1Topo_emscale_pt  = m_sel->GetVectorByType< std::vector<float> >("JET","_emscale_pt",  &n_jet);
  std::vector<float> jet_AntiKt4H1Topo_emscale_eta = m_sel->GetVectorByType< std::vector<float> >("JET","_emscale_eta", &n_jet);
  std::vector<float> jet_AntiKt4H1Topo_EMJES       = m_sel->GetVectorByType< std::vector<float> >("JET","_EMJES",       &n_jet);

  std::vector<float> jet_AntiKt4H1Topo_n90         = m_sel->GetVectorByType< std::vector<float> >("JET","_n90",        &n_jet);
  std::vector<float> jet_AntiKt4H1Topo_Timing      = m_sel->GetVectorByType< std::vector<float> >("JET","_Timing",     &n_jet);   
  std::vector<float> jet_AntiKt4H1Topo_LArQuality  = m_sel->GetVectorByType< std::vector<float> >("JET","_LArQuality", &n_jet);  
//  std::vector<float> jet_AntiKt4H1Topo_timing    = m_sel->GetVectorByType< std::vector<float> >("JET","_timing",     &n_jet);  
//  std::vector<float> jet_AntiKt4H1Topo_quality   = m_sel->GetVectorByType< std::vector<float> >("JET","_quality",    &n_jet);  
  std::vector<float> jet_AntiKt4H1Topo_emfrac      = m_sel->GetVectorByType< std::vector<float> >("JET","_emfrac",     &n_jet);
  std::vector<float> jet_AntiKt4H1Topo_hecf        = m_sel->GetVectorByType< std::vector<float> >("JET","_hecf",       &n_jet);
  std::vector<double> jet_AntiKt4H1Topo_fracSamplingMax = m_sel->GetVectorByType< std::vector<double> >("JET","_fracSamplingMax", &n_jet);
    
  if (n_jet){
    
    for (unsigned int iJet = 0; iJet < n_jet; iJet++){

      if ((jet_AntiKt4H1Topo_emscale_pt.at(iJet)*jet_AntiKt4H1Topo_EMJES.at(iJet)) > 20000.){
    
      
//      bool isbad_tight = JetID::isBad(JetID::TightBad, jet_AntiKt4H1Topo_LArQuality.at(iJet),  jet_AntiKt4H1Topo_n90.at(iJet),  jet_AntiKt4H1Topo_emfrac.at(iJet),  jet_AntiKt4H1Topo_hecf.at(iJet),  jet_AntiKt4H1Topo_Timing.at(iJet), jet_AntiKt4H1Topo_fracSamplingMax.at(iJet), jet_AntiKt4H1Topo_emscale_eta.at(iJet));
	bool isbad_loose = JetID::isBad(JetID::LooseBad, jet_AntiKt4H1Topo_LArQuality.at(iJet),  jet_AntiKt4H1Topo_n90.at(iJet),  jet_AntiKt4H1Topo_emfrac.at(iJet),  jet_AntiKt4H1Topo_hecf.at(iJet),  jet_AntiKt4H1Topo_Timing.at(iJet), jet_AntiKt4H1Topo_fracSamplingMax.at(iJet), jet_AntiKt4H1Topo_emscale_eta.at(iJet));

        if (isbad_loose) {
	  //cout << eventNumber <<endl;
	  return SKIP_EVENT;
	  
 	}  
      }//end if jet_pt > 20 GeV  
    }//end loop over jets
    
    
  }//end if n jets
  
  bin += 1;
  fill_histo(mc_evt_weight, bin, MET);  

// CUT 4 Check there is a good vertex

  if (not(gIsGoodPrimaryVertex)) return SKIP_EVENT;

  bin += 1;
  fill_histo(mc_evt_weight, bin, MET);  

  return KEEP_EVENT; 

}

unsigned int Analysis::Between_OPS_and_OR(Long64_t entry) 
{
   (void)entry; //avoid compiler warnings

  return KEEP_EVENT;
}

  /*------------------------------------------------------------------------
    
                   Do the Analysis  
  
  --------------------------------------------------------------------------*/


void Analysis::doAnalysis(Long64_t entry)
{
  (void)entry;
  
//  if (verbose)  std::cout << "Entry " << entry << " in Analysis (after OPS and OR) " << std::endl;
//  std::cout << "Entry " << entry << " in Analysis (after OPS and OR) " << std::endl;

  /*------------------------------------------------------------------------
    
                   Filling variables   
  
  --------------------------------------------------------------------------*/

  int isOS = 0;
  bool OS = false;
  int nLeadingEl = 0;
  int nLeadingMu = 0;
  bool isIsoEle = false;
  
  // LEPTONS
  
  n_ele = m_sel->GetFinSizeByType("ELE"); //final electrons 
  n_muo = m_sel->GetFinSizeByType("MUO"); //final muons
  
  ele_eta      = m_sel->GetFinVectorByType< std::vector<float> >("ELE","_eta", &n_ele);
  ele_cl_eta   = m_sel->GetFinVectorByType< std::vector<float> >("ELE","_cl_eta", &n_ele);
  ele_phi      = m_sel->GetFinVectorByType< std::vector<float> >("ELE","_phi", &n_ele);
  ele_pt       = m_sel->GetFinVectorByType< std::vector<float> >("ELE","_pt", &n_ele);
  ele_px       = m_sel->GetFinVectorByType< std::vector<float> >("ELE","_px", &n_ele);
  ele_py       = m_sel->GetFinVectorByType< std::vector<float> >("ELE","_py", &n_ele);
  ele_E        = m_sel->GetFinVectorByType< std::vector<float> >("ELE","_E", &n_ele);
  ele_etcone20 = m_sel->GetFinVectorByType< std::vector<float> >("ELE","_Etcone20", &n_ele);
  ele_charge   = m_sel->GetFinVectorByType< std::vector<float> >("ELE","_charge", &n_ele);
  
  muo_eta      = m_sel->GetFinVectorByType< std::vector<float> >("MUO","_eta", &n_muo);
  muo_pt       = m_sel->GetFinVectorByType< std::vector<float> >("MUO","_pt", &n_muo);
  muo_E        = m_sel->GetFinVectorByType< std::vector<float> >("MUO","_E", &n_muo);
  muo_px       = m_sel->GetFinVectorByType< std::vector<float> >("MUO","_px", &n_muo);
  muo_py       = m_sel->GetFinVectorByType< std::vector<float> >("MUO","_py", &n_muo);
  muo_phi      = m_sel->GetFinVectorByType< std::vector<float> >("MUO","_phi", &n_muo);
  muo_etcone20 = m_sel->GetFinVectorByType< std::vector<float> >("MUO","_etcone20", &n_muo);
  muo_charge   = m_sel->GetFinVectorByType< std::vector<float> >("MUO","_charge", &n_muo);
  muo_z0       = m_sel->GetFinVectorByType< std::vector<float> >("MUO","_z0_exPV", &n_muo);

  
  // in this case, all leptons are leading lepons (pt > 20 GeV)
  
  if (n_ele)    
    for (unsigned int i = 0; i < n_ele; i++)   
      nLeadingEl++;  

  if (n_muo)    
    for (unsigned int i = 0; i < n_muo; i++)   
      nLeadingMu++;  

  // JETS before OR
  unsigned int n_jet_init = m_sel->GetSizeByType("JET"); 
  std::vector<float> jet_init_pt  = m_sel->GetVectorByType< std::vector<float> >("JET","_emscale_pt", &n_jet_init);
  std::vector<float> jet_init_E   = m_sel->GetVectorByType< std::vector<float> >("JET","_emscale_E", &n_jet_init);
  std::vector<float> jet_init_jes = m_sel->GetVectorByType< std::vector<float> >("JET","_EMJES", &n_jet_init);
  std::vector<float> jet_init_eta = m_sel->GetVectorByType< std::vector<float> >("JET","_emscale_eta", &n_jet_init);
  std::vector<float> jet_init_phi = m_sel->GetVectorByType< std::vector<float> >("JET","_emscale_phi", &n_jet_init);

  // SELECTED JETS 
  n_jet = m_sel->GetFinSizeByType("JET"); 
  jet_pt  = m_sel->GetFinVectorByType< std::vector<float> >("JET","_emscale_pt", &n_jet);
  jet_E   = m_sel->GetFinVectorByType< std::vector<float> >("JET","_emscale_E", &n_jet);
  jet_jes = m_sel->GetFinVectorByType< std::vector<float> >("JET","_EMJES", &n_jet);
  jet_eta = m_sel->GetFinVectorByType< std::vector<float> >("JET","_emscale_eta", &n_jet);
  jet_phi = m_sel->GetFinVectorByType< std::vector<float> >("JET","_emscale_phi", &n_jet);

  
  //JES
/*  
  EMJESFixer jetEMJESfixer;
  std::string filename = "JESUncertainty.root";
  cout << "Initialize JESUncertainty.root"<<endl;
#ifdef GRID
   char *rpath  = getenv( "PWD" );
#else   
   char *rpath  = "/afs/naf.desy.de/user/l/legger/D3PDReader";
#endif

   if ( rpath == 0 ) { // if ENV-var not set use default
     filename="./"+filename;
   }else{
     std::string path(rpath);
     filename= path + "/"+filename ;
   }
  JESUncertaintyProvider myJES("AntiKt4H1TopoJets",filename);
  myJES.init();

  //correct jets BEFORE overlap removal

// JES correction  
  if (n_jet_init)    
    for (unsigned int i = 0; i < n_jet_init; i++)  { 
      if( jet_init_jes.at(i) == 0. ) jet_init_jes.at(i) = jetEMJESfixer.fixAntiKt4H1Topo(jet_init_pt.at(i),jet_init_eta.at(i));  
      float JESUncertainty = 0;
      if ((fabs(jet_init_pt.at(i)*jet_init_jes.at(i)) > 15000.)&& (fabs(jet_init_eta.at(i))<4.5)) JESUncertainty = myJES.getRelUncert(jet_init_pt.at(i)*jet_init_jes.at(i), jet_init_eta.at(i), JESUncertaintyProvider::NOPILEUP);
#ifdef JESPLUS      
      jet_init_jes.at(i) =  jet_init_jes.at(i) * (1 + JESUncertainty);
#endif
#ifdef JESMINUS      
      jet_init_jes.at(i) =  jet_init_jes.at(i) * (1 - JESUncertainty);
#endif
#ifdef JER 
      //rescale jes by jer
      double cor=getSmearingCor(jet_init_jes.at(i)*jet_init_pt.at(i)/1000.); 
      jet_init_jes.at(i) =  jet_init_jes.at(i) * cor ;
#endif
  }
  
  
// correct for close-by jets
  if (n_jet_init)    
     for (unsigned int iJet_init = 0; iJet_init < n_jet_init; iJet_init++)   { 
     
       float JESUncertainty = 0; 
            
       for (unsigned int iJet_init2 = 0; iJet_init2 < n_jet_init; iJet_init2++)   { 
           if (fabs(jet_init_pt[iJet_init2]*jet_init_jes[iJet_init2]) > 10000.){
             float dR = deltaR(jet_init_eta[iJet_init2],jet_init_phi[iJet_init2],jet_init_eta[iJet_init],jet_init_phi[iJet_init]);
	     
	     if (dR < 0.6 && dR > 0.) {    
	       
#ifdef JESPLUS      
               JESUncertainty +=.05;
#endif      
#ifdef JESMINUS      
               JESUncertainty -=.05;
#endif      
               break;
             }
	     
	   }  //end if selected jet  
       }//end loop over jets 

#ifdef JESPLUS      
      jet_init_jes.at(iJet_init) =  jet_init_jes.at(iJet_init) * (1 + JESUncertainty);
#endif      
#ifdef JESMINUS      
      jet_init_jes.at(iJet_init) =  jet_init_jes.at(iJet_init) * (1 - JESUncertainty);
#endif      
  }

*/
   
  //MET
  
  float MET_x = m_sel->GetScalarVal<float>("MET_CellOut_etx");
  float MET_y = m_sel->GetScalarVal<float>("MET_CellOut_ety");
  //float MET_phi = m_sel->GetScalarVal<float>("MET_CellOut_phi");

  float MET = sqrt(MET_x*MET_x + MET_y*MET_y);    

 //Remove the muon term from the MET:
 
   MET_x -= m_sel->GetScalarVal<float>("MET_Muon_Total_Staco_etx");
   MET_y -= m_sel->GetScalarVal<float>("MET_Muon_Total_Staco_ety");
  
   int n_muo_init = m_sel->GetSizeByType("MUO"); //final muons
  
   //Loop over the selected muons (before the 'overlap removal' and without any isolation (ptcone20) cut):
   if (n_muo_init)
    for(int imu=0;imu<n_muo_init;imu++){
      float smeared_pt = IsSelMuo(imu); 
      if (smeared_pt>=0.){
        MET_x -= smeared_pt*cos(m_sel->GetValByType<float> ("MUO","_phi", imu));
        MET_y -= smeared_pt*sin(m_sel->GetValByType<float> ("MUO","_phi", imu));
      }
    }

   MET =sqrt(pow(MET_x,2)+pow(MET_y,2));
  
 /// correct MET for electron term, on all electrons BEFORE overlap removal passing all selection cuts and RobustMedium
 
  unsigned int n_ele_init = m_sel->GetSizeByType("ELE"); 
    
  TLorentzVector *vec = new TLorentzVector();
  if (n_ele_init)
    for (unsigned int iEle = 0; iEle < n_ele_init; iEle++)   { 
    
      int medium = m_sel->GetValByType<int>("ELE","_medium", iEle);  
      float Eta = m_sel->GetValByType<float>("ELE","_eta", iEle);  
      float Phi = m_sel->GetValByType<float>("ELE","_phi", iEle); 
      float Px  = m_sel->GetValByType<float>("ELE","_px", iEle); 
      float Py  = m_sel->GetValByType<float>("ELE","_py", iEle); 
       
      if ((medium != 1) && IsSelEle(iEle)){        
        if (n_jet_init) for (unsigned int iJet = 0; iJet < n_jet_init; iJet++)   { 
      
//           if (( fabs(jet_init_eta[iJet]) < 2.5 ) &&( fabs(jet_init_pt[iJet]) > 20000. )){
             float dR = deltaR(Eta,Phi,jet_init_eta[iJet],jet_init_phi[iJet]);
	     
	     if (dR < 0.2) {    
	       
	       vec->SetPtEtaPhiE(jet_init_jes[iJet]*jet_init_pt[iJet], jet_init_eta[iJet], jet_init_phi[iJet], jet_init_jes[iJet]*jet_init_E[iJet]);
//	       vec->SetPtEtaPhiE(jet_jes[iJet]*jet_pt[iJet], jet_eta[iJet], jet_phi[iJet], jet_jes[iJet]*jet_E[iJet]);

               MET_x += (*vec).Px() - Px;
               MET_y += (*vec).Py() - Py; 
             }
//	   }  //end if selected jet  // NO CUTS on jets
         } //end loop over jets
      } //end if sel ele	  
    }//end loop over ele
    
   MET =sqrt(pow(MET_x,2)+pow(MET_y,2));
 
  //JES correction to MET 
/*  
  double sumjetpx1 = 0;
  double sumjetpy1 = 0;
  double sumjetpx2 = 0;
  double sumjetpy2 = 0;
    
  if (n_jet)
   for (unsigned int iJet = 0; iJet < n_jet; iJet++)   {
     //before correction
     if( ((jet_pt.at(iJet)*jet_jes.at(iJet))>20000) && (fabs(jet_eta.at(iJet))<4.5) ) {

       float JESUncertainty = myJES.getRelUncert(jet_pt.at(iJet)*jet_jes.at(iJet), jet_eta.at(iJet), JESUncertaintyProvider::NOPILEUP);
       float jes_new = jet_jes.at(iJet); 
       float emjes = jet_jes.at(iJet); 

// look if there are close-by jets
       for (unsigned int iJet_init = 0; iJet_init < n_jet_init; iJet_init++)   { 
//        if (n_jet) for (unsigned int iJet = 0; iJet < n_jet; iJet++)   { 
//             float dR = deltaR(Eta,Phi,jet_eta[iJet],jet_phi[iJet]);
      
           if (fabs(jet_init_pt[iJet_init]) > 10000.){
             float dR = deltaR(jet_eta.at(iJet),jet_phi.at(iJet),jet_init_eta[iJet_init],jet_init_phi[iJet_init]);
	     
	     if (dR < 0.6 && dR > 0.) {    
	       
#ifdef JESPLUS      
               JESUncertainty +=.05;
#endif      
#ifdef JESMINUS      
               JESUncertainty -=.05;
#endif      
               break;
             }
	     
	   }  //end if selected jet  // NO CUTS on jets
       }//end loop over jets 

#ifdef JESPLUS      
       jes_new = emjes * (1 + JESUncertainty);
#endif      
#ifdef JESMINUS      
       jes_new = emjes * (1 - JESUncertainty);
#endif      
#ifdef JER 
      //rescale jes by jer
      double cor=getSmearingCor(jet_jes.at(iJet)*jet_pt.at(iJet)/1000.); 
      jes_new =  emjes * cor ;
#endif

       sumjetpx1 += emjes * (jet_pt.at(iJet)) * cos(jet_phi.at(iJet));
       sumjetpy1 += emjes * (jet_pt.at(iJet)) * sin(jet_phi.at(iJet));
       sumjetpx2 += jes_new * (jet_pt.at(iJet)) * cos(jet_phi.at(iJet));
       sumjetpy2 += jes_new * (jet_pt.at(iJet)) * sin(jet_phi.at(iJet));
     }

   }
 
  MET_x = MET_x + sumjetpx1 - sumjetpx2;
  MET_y = MET_y + sumjetpy1 - sumjetpy2;

//   if (!((sumjetpx1 - sumjetpx2)==0.)) cout << "ERROR (sumjetpx1 - sumjetpx2) "<<(sumjetpx1 - sumjetpx2)<<endl;
//   if (!((sumjetpy1 - sumjetpy2)==0.)) cout << "ERROR (sumjetpy1 - sumjetpy2) "<<(sumjetpy1 - sumjetpy2)<<endl;
  
  MET =sqrt(pow(MET_x,2)+pow(MET_y,2));

//correct selected jets for the rest of the analysis
 
  if (n_jet)    
    for (unsigned int i = 0; i < n_jet; i++){   
      if( jet_jes.at(i) == 0. ) jet_jes.at(i) = jetEMJESfixer.fixAntiKt4H1Topo(jet_pt.at(i),jet_eta.at(i));  
      float JESUncertainty = 0;
      if ((fabs(jet_jes.at(i) *jet_pt.at(i)) > 15000.)&& (fabs(jet_eta.at(i))<4.5)) JESUncertainty == myJES.getRelUncert(jet_jes.at(i) *jet_pt.at(i), jet_eta.at(i), JESUncertaintyProvider::NOPILEUP);

// look if there are close-by jets
      for (unsigned int iJet_init = 0; iJet_init < n_jet_init; iJet_init++)   { 
      
           if (fabs(jet_init_pt[iJet_init]) > 10000.){
             float dR = deltaR(jet_eta.at(i),jet_phi.at(i),jet_init_eta[iJet_init],jet_init_phi[iJet_init]);
	     
	     if (dR < 0.6 && dR > 0.) {    
	       
#ifdef JESPLUS      
               JESUncertainty +=.05;
#endif      
#ifdef JESMINUS      
               JESUncertainty -=.05;
#endif      
               break;
             }
	     
	   }  //end if selected jet  // NO CUTS on jets
       }//end loop over jets 
#ifdef JESPLUS      
      jet_jes.at(i) =  jet_jes.at(i) * (1 + JESUncertainty);
#endif
#ifdef JESMINUS      
      jet_jes.at(i) =  jet_jes.at(i) * (1 - JESUncertainty);
#endif
#ifdef JER 
      //rescale jes by jer
      double cor=getSmearingCor(jet_jes.at(i)*jet_pt.at(i)/1000.); 
      //cout << jet_jes.at(i)*jet_pt.at(i) << " "<<cor<<endl;    
      jet_jes.at(i) =  jet_jes.at(i) * cor ;
#endif
   }
*/     
  float inv_mass = -1;
  float htmiss = 0.;
  float m_eff = MET;
  float m_T = -1;
  
       
  //CALCULATE LEADING JETS AND OTHER VARIABLES
         
  bool leadingJet = false;
  unsigned int nLowPtjets = 0;  
  
  if (n_jet)    
    for (unsigned int iJet = 0; iJet < n_jet; iJet++)   { 
      
      float jetpt = (jet_pt.at(iJet))*(jet_jes.at(iJet));
      if (jet_jes.at(iJet) == 0.) cout << "ERROR JES = 0 (after fix)"<<endl;      
      if (jetpt > 50000.) {
        leadingJet = true;
	m_eff += jetpt ;
	htmiss += jetpt ;
      } else if (jetpt > 20000.) {
        nLowPtjets++;
	m_eff += jetpt ;    
	htmiss += jetpt ;        
      }
    }
    
  /*------------------------------------------------------------------------
    
                   Cutflow  
  
  --------------------------------------------------------------------------*/

//DEBUG

  if ((eventNumber == 14375677)||(eventNumber == 27869906)||(eventNumber == 5572251)){
     cout << "Event "<<eventNumber<<endl;
     cout << L1_el << " " << trgEl << " "<< L1_mu << " "<<trgMu <<endl; 
     debugfile << "Event "<<eventNumber<<" "<< L1_el << " " << trgEl << " "<< L1_mu << " "<<trgMu <<endl; 
     
     cout << "n muons "<< n_muo<<endl;  
     if (n_muo){
        for (unsigned int i = 0; i < n_muo; i++){
          cout << "muon "<< i<<" : pt "<<muo_pt[i]<<" eta "<< muo_eta[i]<<" phi "<< muo_phi[i]<<" charge "<< muo_charge[i]<<endl;  	  
        }//end loop over muons  
	
     
     }//end if n muons
     cout << "n electrons "<< n_ele<<endl;  
     if (n_ele){
        for (unsigned int i = 0; i < n_ele; i++){
          cout << "electron "<< i<<" : pt "<<ele_pt[i]<<" : E "<<ele_E[i]<<" eta "<< ele_eta[i]<<" phi "<< ele_phi[i]<<" charge "<< ele_charge[i]<<endl;  	  
          debugfile << "electron "<< i<<" : pt "<<ele_pt[i]<<" : E "<<ele_E[i]<<" eta "<< ele_eta[i]<<" phi "<< ele_phi[i]<<" charge "<< ele_charge[i]<<endl;  	  
	}   
     }
     cout << "n jets "<< n_jet<<endl;  
     if (n_jet){
        for (unsigned int i = 0; i < n_jet; i++){
          cout << "jet "<< i<<" : pt(JES) "<<jet_pt[i]*jet_jes[i]<<" eta "<< jet_eta[i]<<" phi "<< jet_phi[i]<<endl;  	  
	}   
     }          
   } 

// No cuts
  bin += 1;
  fill_histo(mc_evt_weight, bin, MET);  


//  debugfile <<eventNumber<< endl;
   
/* MT calculation  
  float lep_pt, lep_phi;
  if (n_ele){
    if (n_muo){
    
      if (ele_pt[0]>=muo_pt[0]){
        lep_pt = ele_pt[0];
        lep_phi = ele_phi[0];          
      } else {
        lep_pt = muo_pt[0];
        lep_phi = muo_phi[0];
      } 
    
    }else{
      lep_pt = ele_pt[0];
      lep_phi = ele_phi[0];          
    }  
  } else {
    lep_pt = muo_pt[0];
    lep_phi = muo_phi[0];
  }

  m_T = sqrt(2.*MET*lep_pt*(1. - cos(lep_phi-MET_phi)));
*/

  
  // EXACTLY 2 leptons after object selection 
  float myEventWeight = 1;
  
  if (!((n_ele +n_muo)==2)) return ;
  
  // EE , EMU and MUMU definitions
     
  TLorentzVector* vec1 = new TLorentzVector();
  TLorentzVector* vec2 = new TLorentzVector();
  
  bool ee = false;
  bool emu = false;
  bool mumu = false;
  egammaSFclass  egamma;
  
  if (n_ele ==2) {                     // EE case  

#ifdef CUTFLOW_MUO  
  return;
#endif  

    if (!(trgEl)) return;//-- trigger requirement 
    if (!(nLeadingEl)) return;//-- 1 pt > 20 GeV
    
#ifdef MUON  //only for electron stream and MC
#else
    ee = true;
    dileptonfile <<"EE event nb: "<<eventNumber<<" run nb: "<<runNumber <<endl;
#endif    
     
    vec1->SetPtEtaPhiE(ele_pt[0], ele_eta[0], ele_phi[0], ele_E[0]);
    vec2->SetPtEtaPhiE(ele_pt[1], ele_eta[1], ele_phi[1], ele_E[1]);
  
    isOS = -1;  
    if ((ele_charge[0]*ele_charge[1])==-1.) {
      OS = true; 
      isOS = 1;
    } 
    
    if ( ((ele_etcone20[0]/ele_pt[0]) < 0.15) && ((ele_etcone20[1]/ele_pt[1]) < 0.15))    isIsoEle = true;

// EVENT WEIGHT for selected ELECTRONS
// RobustLoose (set=0), RobustMedium (set=1) and RobusterTight (set=2)
    
    int myset0 = 1; 
    int myset1 = 1; 
    if (IsRobusterTight(0)) myset0 = 2;
    if (IsRobusterTight(1)) myset1 = 2;

    myEventWeight *= egamma.scaleFactor(ele_cl_eta[0], myset0, 0, 0).first;
    myEventWeight *= egamma.scaleFactor(ele_cl_eta[1], myset1, 0, 0).first;
    
    m_eff += ele_pt[0]+ele_pt[1]; //to calculate meff
    htmiss += ele_pt[0]+ele_pt[1]; //to calculate meff
  
  } else if (n_muo ==2) {            // MUMU case

#ifdef CUTFLOW_ELE  
  return;
#endif  

    if (!(trgMu)) return;//-- trigger requirement 
    if (!(nLeadingMu)) return;//-- 1 pt > 20 GeV
    
#ifdef ELECTRON  //only for muon stream and MC
#else
    dileptonfile <<"MUMU event nb: "<<eventNumber<<" run nb: "<<runNumber <<endl;
    mumu = true;
#endif

    vec1->SetPtEtaPhiE(muo_pt[0], muo_eta[0], muo_phi[0], muo_E[0]);
    vec2->SetPtEtaPhiE(muo_pt[1], muo_eta[1], muo_phi[1], muo_E[1]);
  
    isOS = -1;  
    if ((muo_charge[0]*muo_charge[1])==-1.) {
      OS = true; 
      isOS = 1;
    } 
  
    m_eff += muo_pt[0]+muo_pt[1]; //to calculate meff
    htmiss += muo_pt[0]+muo_pt[1]; //to calculate meff
  
  } else if ((n_muo == 1 ) &&(n_ele == 1) ) {          // EMU case

#ifdef CUTFLOW_ELE
    if (!(trgEl && nLeadingEl)) return; 
#else    
  #ifdef CUTFLOW_MUO
    if (!(trgMu && (!trgEl)&&nLeadingMu)) return; 
  #else
    #ifdef ELECTRON
      if (!(trgEl && nLeadingEl )) return;   
    #endif
    #ifdef MUON
      if (!( trgMu && (!trgEl)&&nLeadingMu) ) return;   
    #endif
    #ifdef MC
    if (!((trgEl && nLeadingEl) || ( trgMu && nLeadingMu)) ) return; 
    #endif    
  #endif  
#endif    

// EVENT WEIGHT for selected ELECTRONS
// RobustLoose (set=0), RobustMedium (set=1) and RobusterTight (set=2)
    
    int myset0 = 1; 
    if (IsRobusterTight(0)) myset0 = 2;
    myEventWeight *= egamma.scaleFactor(ele_cl_eta[0], myset0, 0, 0).first;

    emu = true;   
    dileptonfile <<"EMU event nb: "<<eventNumber<<" run nb: "<<runNumber <<endl;
      
    vec1->SetPtEtaPhiE(ele_pt[0], ele_eta[0], ele_phi[0], ele_E[0]);
    vec2->SetPtEtaPhiE(muo_pt[0], muo_eta[0], muo_phi[0], muo_E[0]);
  
    isOS = -1;  
    if ((ele_charge[0]*muo_charge[0])==-1.) {
      OS = true; 
      isOS = 1;
    }   

    if ((ele_etcone20[0]/ele_pt[0]) < 0.15)     isIsoEle = true;
   
    m_eff += ele_pt[0]+muo_pt[0]; // to calculate meff    
    htmiss += ele_pt[0]+muo_pt[0]; // to calculate meff    

  } else return ; //no dilepton event
  
  inv_mass = ((*vec1)+(*vec2)).M();  

  // dilepton mass > 5 GeV    
  if (!(inv_mass >= 5000.)) return;

  if (verbose)   cout <<"event nb: "<<eventNumber<<" run nb: "<<runNumber << "    mll: "<< inv_mass<<  "    MET: "<<MET<<endl;


// QCD reject ee for Jx muon, and emu mumu for Jx

  if ((runNumber == 109276) && ee ) return;
  if ((runNumber == 109277) && ee ) return;
  if ((runNumber == 109278) && ee ) return;
  if ((runNumber == 109279) && ee ) return;
  if ((runNumber == 109280) && ee ) return;
  if ((runNumber == 109281) && ee ) return;
  if ((runNumber == 209435) && ee ) return;
  
  if ((runNumber == 105009) && (emu || mumu) ) return;
  if ((runNumber == 105010) && (emu || mumu) ) return;  
  if ((runNumber == 105011) && (emu || mumu) ) return;
  if ((runNumber == 105012) && (emu || mumu) ) return;
  if ((runNumber == 105013) && (emu || mumu) ) return;
  if ((runNumber == 105014) && (emu || mumu) ) return;
  if ((runNumber == 105015) && (emu || mumu) ) return;  
    
  if ((runNumber == 108326) && (emu || mumu) ) return;


  // DEBUG
  
  if (verbose){
     //cout << "n muons "<< n_muo<<endl;  

     TLorentzVector* truth_vec1 = new TLorentzVector();
     TLorentzVector* truth_vec2 = new TLorentzVector();
     if (n_muo){
        for (unsigned int i = 0; i < n_muo; i++){
          cout << "muon "<< i<<" : pt "<<muo_pt[i]<<" eta "<< muo_eta[i]<<" phi "<< muo_phi[i]<<" charge "<< muo_charge[i]<<endl;  	  

	  
	  if (drellyan){
	    float true_eta =  m_sel->GetFinValByType<float>("MUO","_truth_eta", i);
	    float true_phi =  m_sel->GetFinValByType<float>("MUO","_truth_phi", i);
	    float true_pt  =  m_sel->GetFinValByType<float>("MUO","_truth_pt", i);
	    int type    =     m_sel->GetFinValByType<int>  ("MUO","_truth_type", i);
	    int mothertype =  m_sel->GetFinValByType<int>  ("MUO","_truth_mothertype", i);
	    int barcode    =  m_sel->GetFinValByType<int>  ("MUO","_truth_barcode", i);
	    int motherbarcode = m_sel->GetFinValByType<int>("MUO","_truth_motherbarcode", i);
          
	    if (i==0){
	      truth_vec1->SetPtEtaPhiM(true_pt, true_eta, true_phi, 0.0);
            }else if (i==1){
	      truth_vec2->SetPtEtaPhiM(true_pt, true_eta, true_phi, 0.0);
            }else{
	      cout << "WARNING more than 2 leptons!"<<endl;
	    }
            cout << " true muon "<< i<<" : pt "<<true_pt<<" eta "<< true_eta<<endl;
	    cout << " barcode "<< barcode<<" mother barcode "<< motherbarcode<<" type "<< type<<" mother type "<< mothertype<<endl;  	  
	  }//end if drell yan
	   
        }//end loop over muons  
	
	if (drellyan){
	  float truth_inv_mass = ((*truth_vec1)+(*truth_vec2)).M();
          cout << "truth inv mass "<<truth_inv_mass<<endl;
        }//end if drellyan
     
     }//end if n muons
     //cout << "n electrons "<< n_ele<<endl;  
     if (n_ele){
        for (unsigned int i = 0; i < n_ele; i++){
          cout << "electron "<< i<<" : pt "<<ele_pt[i]<<" eta "<< ele_eta[i]<<" phi "<< ele_phi[i]<<" charge "<< ele_charge[i]<<endl;  	  
	}   
     }
     if (n_jet){
        for (unsigned int i = 0; i < n_jet; i++){
          cout << "jet "<< i<<" : pt(JES) "<<jet_pt[i]*jet_jes[i]<<" eta "<< jet_eta[i]<<" phi "<< jet_phi[i]<<endl;  	  
	}   
     }     
     
     cout << "L1mu: "<< trgMu<< " L1el: "<<trgEl<<endl;
   }
     
  // apply electron weight
  
  //cout << mc_evt_weight<<endl;
  
  #ifdef MC
  mc_evt_weight*=myEventWeight;
  #endif
  //cout << myEventWeight<<endl;

  
  /*------------------------------------------------------------------------
    
                   Fill ee, emu, mumu  
  
  --------------------------------------------------------------------------*/
  //  ee+emu+mumu cut 


  bin += 1;
  if (
   (ee && IsRobusterTight(0) && IsRobusterTight(1) && (nLeadingEl == 2)&&isIsoEle) ||
   (emu && IsRobusterTight(0) && ((nLeadingEl + nLeadingMu) == 2) &&isIsoEle) ||
   (mumu && (nLeadingMu == 2))
  ) {
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);      
    debugfile <<"RunNo="<<runNumber<<"  EventNo="<< eventNumber<<"  MET="<< MET <<endl;
  }
  
  //  ee cut 
  bin += 1;
  if (ee) {
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);      
  }

  // ee && robusterTight
  bin += 1;
  if (ee && IsRobusterTight(0) && IsRobusterTight(1)) {
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);      
  }

  // ee && robusterTight && pt > 20 GeV
  bin += 1;
  if (ee && IsRobusterTight(0) && IsRobusterTight(1) && (nLeadingEl == 2)) {
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
  }

  // ee && robusterTight && pt > 20 GeV && isolation
  bin += 1;
  if (ee && IsRobusterTight(0) && IsRobusterTight(1) && (nLeadingEl == 2)&&isIsoEle) 
  {
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
  }
  //  ee && OS cut 
  bin += 1;
  if (ee && IsRobusterTight(0) && IsRobusterTight(1) && (nLeadingEl == 2) && OS) {
    if ((inv_mass<=100000.)&&(inv_mass>=60000.)) ZVeto = true;
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
  }
    
  // ee && OS cut && MET cut > 100 
  bin += 1;
  if (ee && IsRobusterTight(0) && IsRobusterTight(1) && (nLeadingEl == 2) && OS && (MET > 100000.)) {  
    //cout << eventNumber <<" "<< MET <<endl;
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   

  // ee && OS cut && MET cut > 125 
  bin += 1;
  if (ee && IsRobusterTight(0) && IsRobusterTight(1) && (nLeadingEl == 2) && OS && (MET > 125000.)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   

  // ee && OS cut && MET cut > 150 
  bin += 1;
  if (ee && IsRobusterTight(0) && IsRobusterTight(1) && (nLeadingEl == 2) && OS && (MET > 150000.)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   

  // ee && SS cut && MET cut > 60 
  bin += 1;
  if (ee && IsRobusterTight(0) && IsRobusterTight(1) && (nLeadingEl == 2) && (!OS) && (MET > 60000.)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   

  // ee && SS cut && MET cut > 80
  bin += 1;
  if (ee && IsRobusterTight(0) && IsRobusterTight(1) && (nLeadingEl == 2) && (!OS) && (MET > 80000.)) {  
    //cout << eventNumber <<" "<< MET <<endl;
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   

  // ee && SS cut && MET cut > 100 
  bin += 1;
  if (ee && IsRobusterTight(0) && IsRobusterTight(1) && (nLeadingEl == 2) && (!OS) && (MET > 100000.)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   
  
  //  ee && OS cut 
  bin += 1;
  if (ee && IsRobusterTight(0) && IsRobusterTight(1) && (nLeadingEl == 2)&&isIsoEle && OS) {
    if ((inv_mass<=100000.)&&(inv_mass>=60000.)) ZVeto = true;
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
  }
    
  // ee && OS cut && MET cut > 100 
  bin += 1;
  if (ee && IsRobusterTight(0) && IsRobusterTight(1) && (nLeadingEl == 2)&&isIsoEle && OS && (MET > 100000.)) {  
    //cout << eventNumber <<" "<< MET <<endl;
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   

  // ee && OS cut && MET cut > 125 
  bin += 1;
  if (ee && IsRobusterTight(0) && IsRobusterTight(1) && (nLeadingEl == 2)&&isIsoEle && OS && (MET > 125000.)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   

  // ee && OS cut && MET cut > 150 
  bin += 1;
  if (ee && IsRobusterTight(0) && IsRobusterTight(1) && (nLeadingEl == 2)&&isIsoEle && OS && (MET > 150000.)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   

  // ee && SS cut && MET cut > 60 
  bin += 1;
  if (ee && IsRobusterTight(0) && IsRobusterTight(1) && (nLeadingEl == 2)&&isIsoEle && (!OS) && (MET > 60000.)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   

  // ee && SS cut && MET cut > 80
  bin += 1;
  if (ee && IsRobusterTight(0) && IsRobusterTight(1) && (nLeadingEl == 2)&&isIsoEle && (!OS) && (MET > 80000.)) {  
    //cout << eventNumber <<" "<< MET <<endl;
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   

  // ee && SS cut && MET cut > 100 
  bin += 1;
  if (ee && IsRobusterTight(0) && IsRobusterTight(1) && (nLeadingEl == 2)&&isIsoEle && (!OS) && (MET > 100000.)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   
 
  //  emu cut 
  bin += 1;  
  if (emu) {
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);      
  }
  
  // emu && robusterTight
  bin += 1;  
  if (emu &&  IsRobusterTight(0)) {
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);      
  }

  // emu && robusterTight && pt > 20 GeV
  bin += 1;  
  if (emu &&  IsRobusterTight(0) && ((nLeadingEl + nLeadingMu) == 2)) {
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);      
  }
  
  //  emu cut && robusterTight && pt > 20 GeV 
  bin += 1;  
  if (emu &&  IsRobusterTight(0) && ((nLeadingEl + nLeadingMu) == 2))  {
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);      
  }
  
  //  emu &&  robusterTight && pt > 20 GeV && isolation (not applied)
  bin += 1;  
  if (emu &&  IsRobusterTight(0) && ((nLeadingEl + nLeadingMu) == 2) &&isIsoEle) {
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
  }

  //  emu && OS cut (not applied)
  bin += 1;  
  if (emu && IsRobusterTight(0) && ((nLeadingEl + nLeadingMu) == 2) && OS) {
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
  }

  // emu  && OS cut && MET cut > 100 
  bin += 1;
  if (emu && IsRobusterTight(0) && ((nLeadingEl + nLeadingMu) == 2) && OS && (MET > 100000.)) {    
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 } 

  // emu  && OS cut && MET cut > 125 

  bin += 1;
  if (emu && IsRobusterTight(0) && ((nLeadingEl + nLeadingMu) == 2) && OS && (MET > 125000.)) {    
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 } 

  // emu  && OS cut && MET cut > 150 
  bin += 1;
  if (emu && IsRobusterTight(0) && ((nLeadingEl + nLeadingMu) == 2) && OS && (MET > 150000.)) {    
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 } 

  // emu  && SS cut && MET cut > 60 
  bin += 1;
  if (emu && IsRobusterTight(0) && ((nLeadingEl + nLeadingMu) == 2) && (!OS) && (MET > 60000.)) {    
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 } 

  // emu  && SS cut && MET cut > 80
  bin += 1;
  if (emu && IsRobusterTight(0) && ((nLeadingEl + nLeadingMu) == 2) && (!OS) && (MET > 80000.)) {    
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 } 

  // emu  && SS cut && MET cut > 100 
  bin += 1;
  if (emu && IsRobusterTight(0) && ((nLeadingEl + nLeadingMu) == 2) && (!OS) && (MET > 100000.)) {    
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }  
  //  emu && OS cut (not applied)
  bin += 1;  
  if (emu && IsRobusterTight(0) && ((nLeadingEl + nLeadingMu) == 2) &&isIsoEle&& OS) {
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
  }

  // emu  && OS cut && MET cut > 100 
  bin += 1;
  if (emu && IsRobusterTight(0) && ((nLeadingEl + nLeadingMu) == 2) &&isIsoEle&& OS && (MET > 100000.)) {    
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);
    //cout <<"event nb: "<<eventNumber<<  "    MET: "<<MET<<endl;  
 } 

  // emu  && OS cut && MET cut > 125 

  bin += 1;
  if (emu && IsRobusterTight(0) && ((nLeadingEl + nLeadingMu) == 2) &&isIsoEle&& OS && (MET > 125000.)) {    
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 } 

  // emu  && OS cut && MET cut > 150 
  bin += 1;
  if (emu && IsRobusterTight(0) && ((nLeadingEl + nLeadingMu) == 2) &&isIsoEle&& OS && (MET > 150000.)) {    
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 } 

  // emu  && SS cut && MET cut > 60 
  bin += 1;
  if (emu && IsRobusterTight(0) && ((nLeadingEl + nLeadingMu) == 2) &&isIsoEle&& (!OS) && (MET > 60000.)) {    
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 } 

  // emu  && SS cut && MET cut > 80
  bin += 1;
  if (emu && IsRobusterTight(0) && ((nLeadingEl + nLeadingMu) == 2) &&isIsoEle&& (!OS) && (MET > 80000.)) {    
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 } 

  // emu  && SS cut && MET cut > 100 
  bin += 1;
  if (emu && IsRobusterTight(0) && ((nLeadingEl + nLeadingMu) == 2) &&isIsoEle&& (!OS) && (MET > 100000.)) {    
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }  
   
  //  mumu cut 
  bin += 1;  
  if (mumu) {
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);      
  }

  //  mumu  && pt > 20 GeV 
  bin += 1;  
  if (mumu && (nLeadingMu == 2)) {
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);      
  }
  
  //  mumu && OS cut (not applied)
  bin += 1;  
  if (mumu && (nLeadingMu == 2) && OS) {    
    if ((inv_mass<=100000.)&&(inv_mass>=60000.)) ZVeto = true;
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
  }

  // mumu && MET cut > 100 && OS
  bin += 1;
  if (mumu && (nLeadingMu == 2) && OS && (MET > 100000.)) {    
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 } 

  // mumu && MET cut > 125 && OS
  bin += 1;
  if (mumu && (nLeadingMu == 2) && OS && (MET > 125000.)) {    
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 } 

  // mumu && MET cut > 150 && OS
  bin += 1;
  if (mumu && (nLeadingMu == 2) && OS && (MET > 150000.)) {    
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 } 

  // mumu && MET cut > 60 && SS
  bin += 1;
  if (mumu && (nLeadingMu == 2) && (!OS) && (MET > 60000.)) {    
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 } 
  
  // mumu && MET cut > 60 && SS
  bin += 1;
  if (mumu && (nLeadingMu == 2) && (!OS) && (MET > 80000.)) {    
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 } 
  // mumu && MET cut > 100 && SS
  bin += 1;
  if (mumu && (nLeadingMu == 2) && (!OS) && (MET > 100000.)) {    
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 } 
  
//fill histo for control region study for QCD normalization

   if ((MET < 20000.)&&(inv_mass >= 5000.)&&(ZVeto)&&(!OS))	 controlregion_histo->Fill( 0., mc_evt_weight);   // QCD
   if ((MET < 20000.)&&(inv_mass >= 5000.)&&(ZVeto))		 controlregion_histo->Fill( 1., mc_evt_weight);   
   if ((MET < 20000.)&&(inv_mass >= 5000.)&&(ZVeto)&&leadingJet) controlregion_histo->Fill( 2., mc_evt_weight);   
   if ((MET < 30000.)&&(inv_mass >= 5000.)&&(ZVeto)&&(!OS))	 controlregion_histo->Fill( 3., mc_evt_weight);   
   if ((MET < 30000.)&&(inv_mass >= 5000.)&&(ZVeto))		 controlregion_histo->Fill( 4., mc_evt_weight);   
   if ((MET < 30000.)&&(inv_mass >= 5000.)&&(ZVeto)&&leadingJet) controlregion_histo->Fill( 5., mc_evt_weight);   
   if ((MET < 40000.)&&(inv_mass >= 5000.)&&(ZVeto)&&(!OS))	 controlregion_histo->Fill( 6., mc_evt_weight);   
   if ((MET < 40000.)&&(inv_mass >= 5000.)&&(ZVeto))		 controlregion_histo->Fill( 7., mc_evt_weight);   
   if ((MET < 40000.)&&(inv_mass >= 5000.)&&(ZVeto)&&leadingJet) controlregion_histo->Fill( 8., mc_evt_weight);   
   if ((MET < 20000.)&& ZVeto)  					      controlregion_histo->Fill( 9., mc_evt_weight);  // Zjets   
   if ((MET < 30000.)&& ZVeto)  					      controlregion_histo->Fill(10., mc_evt_weight);   
   if ((MET < 40000.)&& ZVeto)  					      controlregion_histo->Fill(11., mc_evt_weight);	  
   if ((MET > 30000.)&&(inv_mass <= 60000.)&&(MET < 50000.)&& (m_T <= 80000.)&& (m_T >= 40000.)) controlregion_histo->Fill(12., mc_evt_weight); // Wjets   
   if ((MET > 40000.)&&(inv_mass <= 60000.)&&(MET < 60000.)&& (m_T <= 80000.)&& (m_T >= 40000.)) controlregion_histo->Fill(13., mc_evt_weight); 
   if ((MET > 40000.)&&(inv_mass <= 60000.)&&(MET < 60000.)&& (m_T <= 80000.)&& (m_T >= 60000.)) controlregion_histo->Fill(14., mc_evt_weight); 

   if ((MET > 20000.)&&(leadingJet)&&(m_T > 40000.))	  signalregion_histo->Fill( 0., mc_evt_weight);   
   if ((MET > 40000.)&&(leadingJet)&&(m_T > 40000.))	  signalregion_histo->Fill( 1., mc_evt_weight);   
   if ((MET > 60000.)&&(leadingJet)&&(m_T > 40000.))	  signalregion_histo->Fill( 2., mc_evt_weight);   
   if ((MET > 20000.)&&(leadingJet)&&((jet_pt.at(0))*(jet_jes.at(0)) > 30000.) &&(m_T > 40000.)) signalregion_histo->Fill( 3., mc_evt_weight);   
   if ((MET > 20000.)&&(leadingJet)&&((jet_pt.at(0))*(jet_jes.at(0)) > 40000.) &&(m_T > 40000.)) signalregion_histo->Fill( 4., mc_evt_weight);   
   if ((MET > 20000.)&&(leadingJet)&&((jet_pt.at(0))*(jet_jes.at(0)) > 50000.) &&(m_T > 40000.)) signalregion_histo->Fill( 5., mc_evt_weight);   
   if ((MET > 60000.)&&(leadingJet)&&(m_T > 60000.))	  signalregion_histo->Fill( 6., mc_evt_weight);   
   if ((MET > 60000.)&&(leadingJet)&&(m_T > 80000.))	  signalregion_histo->Fill( 7., mc_evt_weight);   
   if ((MET > 60000.)&&(leadingJet)&&(m_T > 100000.))	  signalregion_histo->Fill( 8., mc_evt_weight);   
   if ((MET > 40000.)&&(leadingJet)&&((jet_pt.at(0))*(jet_jes.at(0)) > 30000.) &&(m_T > 40000.)) signalregion_histo->Fill( 9., mc_evt_weight);   
   if ((MET > 40000.)&&(leadingJet)&&((jet_pt.at(0))*(jet_jes.at(0)) > 40000.) &&(m_T > 40000.)) signalregion_histo->Fill( 10., mc_evt_weight);   
   if ((MET > 40000.)&&(leadingJet)&&((jet_pt.at(0))*(jet_jes.at(0)) > 50000.) &&(m_T > 40000.)) signalregion_histo->Fill( 11., mc_evt_weight);   
   if ((MET > 60000.)&&(leadingJet)&&((jet_pt.at(0))*(jet_jes.at(0)) > 30000.) &&(m_T > 80000.)) signalregion_histo->Fill( 12., mc_evt_weight);   
   if ((MET > 60000.)&&(leadingJet)&&((jet_pt.at(0))*(jet_jes.at(0)) > 40000.) &&(m_T > 80000.)) signalregion_histo->Fill( 13., mc_evt_weight);   
   if ((MET > 60000.)&&(leadingJet)&&((jet_pt.at(0))*(jet_jes.at(0)) > 50000.) &&(m_T > 80000.)) signalregion_histo->Fill( 14., mc_evt_weight);   

 // The END
 return;
}


void Analysis::finalizeEvent(Long64_t entry)
{
  (void)entry;
  return;

}


/*static*/ void Analysis::postAnalysis (TSelectorList* fOutput)
{
  // (void)fOutput; //avoid compiler warnings
 
  //This METhod is declared as static in the header file
  //Why?
  //This comes from the fact that PROOF calls the METhod Terminate (which then calls this METhod) on the master thread.
  //However, when running PROOF, the code above usually runs in Slave Threads. 
  //The master thread (which is running when the computer gets here), doesn't have acces to the member variables in the slave threads.
  
  //All you can do here is get Objects from fOutput-List and Draw them or save them to a file
  TString filename = "result";

#ifdef QCDBG
  filename = "qcd";
#else
#endif
#ifdef JESPLUS      
  filename = "jesplus";
#endif
#ifdef JESMINUS      
  filename = "jesminus";
#endif  
#ifdef JER      
  filename = "jer";
#endif
#ifdef ELESPLUS
  filename = "elesplus";
#endif
#ifdef ELESMINUS
  filename = "elesminus";
#endif
#ifdef ELERECO
  filename = "elereco";
#endif
#ifdef ELER
  filename = "eler";
#endif

#ifdef MUOSPLUS
  filename = "muosplus";
#endif
#ifdef MUOSMINUS
  filename = "muosminus";
#endif
#ifdef MUORECO
  filename = "muoreco";
#endif
#ifdef MUOR
  filename = "muor";
#endif

//  TH1F * dada = (TH1F*)fOutput->FindObject("some_histo")->Clone();
  TH1F *cutflow = (TH1F*)fOutput->FindObject("cutflow_histo")->Clone();
  TH1F *controlregion = (TH1F*)fOutput->FindObject("controlregion_histo")->Clone();
  TH1F *signalregion = (TH1F*)fOutput->FindObject("signalregion_histo")->Clone();
  TH1F *runNumber = (TH1F*)fOutput->FindObject("runNumber_histo")->Clone();
 
  TH2F* cutflow_susy      = (TH2F*)fOutput->FindObject("h_cutflow_susy")->Clone();
  
  TH2F* e_nb_histo        = (TH2F*)fOutput->FindObject("h_e_nb")->Clone();
   
  TH2F* e_eta_histo       = (TH2F*)fOutput->FindObject("h_e_eta")->Clone();
  TH2F* e_pt_histo        = (TH2F*)fOutput->FindObject("h_e_pt")->Clone();
  TH2F* e_phi_histo       = (TH2F*)fOutput->FindObject("h_e_phi")->Clone();
  TH2F* e_etcone20_histo  = (TH2F*)fOutput->FindObject("h_e_etcone20")->Clone();
  TH2F* e_charge_histo    = (TH2F*)fOutput->FindObject("h_e_charge")->Clone();
   
  TH2F* mu_nb_histo       = (TH2F*)fOutput->FindObject("h_mu_nb")->Clone();
  TH2F* mu_eta_histo      = (TH2F*)fOutput->FindObject("h_mu_eta")->Clone();
  TH2F* mu_pt_histo       = (TH2F*)fOutput->FindObject("h_mu_pt")->Clone();
  TH2F* mu_phi_histo      = (TH2F*)fOutput->FindObject("h_mu_phi")->Clone();
  TH2F* mu_etcone20_histo = (TH2F*)fOutput->FindObject("h_mu_etcone20")->Clone();
  TH2F* mu_charge_histo   = (TH2F*)fOutput->FindObject("h_mu_charge")->Clone();
  
  TH2F* jet_nb_histo      = (TH2F*)fOutput->FindObject("h_jet_nb")->Clone();
  TH2F* jet_eta_histo     = (TH2F*)fOutput->FindObject("h_jet_eta")->Clone();
  TH2F* jet_phi_histo     = (TH2F*)fOutput->FindObject("h_jet_phi")->Clone();
  TH2F* jet_pt_histo      = (TH2F*)fOutput->FindObject("h_jet_pt")->Clone();
  TH2F* jetl_eta_histo    = (TH2F*)fOutput->FindObject("h_jetl_eta")->Clone();
  TH2F* jetl_phi_histo    = (TH2F*)fOutput->FindObject("h_jetl_phi")->Clone();
  TH2F* jetl_pt_histo     = (TH2F*)fOutput->FindObject("h_jetl_pt")->Clone();
  TH2F* jet2l_eta_histo   = (TH2F*)fOutput->FindObject("h_jet2l_eta")->Clone();
  TH2F* jet2l_phi_histo   = (TH2F*)fOutput->FindObject("h_jet2l_phi")->Clone();
  TH2F* jet2l_pt_histo    = (TH2F*)fOutput->FindObject("h_jet2l_pt")->Clone();
  
  TH2F* met_histo         = (TH2F*)fOutput->FindObject("h_met")->Clone();
  TH2F* met_OS_histo      = (TH2F*)fOutput->FindObject("h_met_OS")->Clone();
  TH2F* met_SS_histo      = (TH2F*)fOutput->FindObject("h_met_SS")->Clone();
  TH2F* meff_histo        = (TH2F*)fOutput->FindObject("h_meff")->Clone();
  TH2F* mt_histo          = (TH2F*)fOutput->FindObject("h_mt")->Clone();
  TH2F* invmass_histo     = (TH2F*)fOutput->FindObject("h_invmass")->Clone();
  TH2F* invmassOS_histo   = (TH2F*)fOutput->FindObject("h_invmass_OS")->Clone();
  TH2F* invmassSS_histo   = (TH2F*)fOutput->FindObject("h_invmass_SS")->Clone();
  TH2F* htmissOS_histo    = (TH2F*)fOutput->FindObject("h_htmiss_OS")->Clone();
  TH2F* htmissSS_histo    = (TH2F*)fOutput->FindObject("h_htmiss_SS")->Clone();
  TH2F* nGoodPV_histo     = (TH2F*)fOutput->FindObject("h_nGoodPV")->Clone();
 
  double run = runNumber->GetMean();
//  char runNb[10];
//  cout << "RUN NUMBER "<<run<<endl; 
//  sprintf(runNb, "_%d", ((int)run));
  std::stringstream out;
  out << "_"<<run;
  std::string runNb = out.str();
   
 
#ifdef HISTO

//#ifdef MC  
  filename += (TString)runNb;
//#endif
  
  //int n_events =cutflow->GetBinContent(1);
  //std::cout << "Final Cutflow after "<<n_events<<" events for two lepton selection "  << std::endl;
  std::cout << "Final Cutflow for run "<<run  << std::endl;
  
  //electron stream
  #ifdef ELECTRON
  filename += "_electronStream";
  std::cout << "Electron stream " << std::endl;    
  #endif
  #ifdef MUON
  filename += "_muonStream";
  std::cout << "Muon stream " << std::endl;    
  #endif
  
#endif

  filename = "histos";
// Opening files

#ifdef GRID
   char *rpath  = getenv( "PWD" );
#else   
   char *rpath  = "/afs/naf.desy.de/user/l/legger/D3PDReader";
#endif


   if ( rpath == 0 ) { // if ENV-var not set use default
     filename="./"+filename;
   }else{
     std::string path(rpath);
     filename= path + "/"+filename ;
   }

//root file

  TFile* Target = new TFile( filename+".root", "RECREATE");
  cout << "Writing output to "<<filename<<".root,txt"<<endl;

//txt file
  filename = filename+".txt"; 
  
#ifdef HISTO
  const char* name_txtfile=filename.Data(); 
  
  //cout << "Opening txt file "<<name_txtfile<<endl;
  myfile.open(name_txtfile);
#else 
  //save to dummy file
  myfile.open("./file.txt");
#endif
  
  myfile << "Final Cutflow for run "<<run  << std::endl;
  
  #ifdef ELECTRON
  myfile << "Electron stream "<< std::endl ;
  #endif
  #ifdef MUON
  myfile << "Muon stream "<< std::endl ;
  #endif
    
//  for (unsigned int cf = 0; cf < 56; cf++)  SS MET > 150 GeV 
  for (unsigned int cf = 0; cf < 53; cf++)
  {
    Double_t nbin_content =cutflow->GetBinContent(cf+1);
    std::cout << "Cut " << cf <<" : " <<  (nbin_content)<<"		  "<< name_cutflow[cf]<<std::endl;
    myfile    << "Cut " << cf <<" : " <<  (nbin_content)<<"		  "<< name_cutflow[cf]<<std::endl; 
  }

  if (ndrellyan>0.)
    cout << "drellyan efficiency "<< 1.*ndrellyanNOT/ndrellyan<<endl;

//  dada->Write();
  cutflow->Write();
  cutflow_susy->Write();
  runNumber->Write();
  controlregion->Write();
  signalregion->Write();
 
  e_nb_histo->Write();       
  e_eta_histo->Write();      
  e_pt_histo ->Write();      
  e_phi_histo->Write();      
  e_etcone20_histo->Write(); 
  e_charge_histo->Write();

  mu_nb_histo ->Write();     
  mu_eta_histo ->Write();    
  mu_pt_histo ->Write();     
  mu_phi_histo ->Write();    
  mu_etcone20_histo->Write();
  mu_charge_histo->Write();

  jet_nb_histo  ->Write();
  jet_eta_histo ->Write();
  jet_phi_histo ->Write();
  jet_pt_histo  ->Write();
  jetl_eta_histo ->Write();
  jetl_phi_histo ->Write();
  jetl_pt_histo  ->Write();
  jet2l_eta_histo ->Write();
  jet2l_phi_histo ->Write();
  jet2l_pt_histo  ->Write();

  met_histo  ->Write(); 
  met_OS_histo    ->Write(); 
  met_SS_histo    ->Write(); 

  meff_histo      ->Write(); 
  mt_histo      ->Write(); 
  invmass_histo   ->Write(); 
  invmassOS_histo   ->Write(); 
  invmassSS_histo   ->Write(); 
  htmissOS_histo   ->Write(); 
  htmissSS_histo   ->Write(); 
  nGoodPV_histo   ->Write(); 

  delete cutflow;
  delete cutflow_susy;
  delete runNumber;
  delete controlregion;
  delete signalregion;
  delete e_nb_histo;      
  delete e_eta_histo;      
  delete e_pt_histo;       
  delete e_phi_histo;      
  delete e_etcone20_histo; 
  delete e_charge_histo; 
  delete mu_nb_histo;      
  delete mu_eta_histo;     
  delete mu_pt_histo;      
  delete mu_phi_histo;     
  delete mu_etcone20_histo;
  delete mu_charge_histo; 
  delete jet_nb_histo; 
  delete jet_eta_histo;
  delete jet_phi_histo;
  delete jet_pt_histo;
  delete jetl_eta_histo;
  delete jetl_phi_histo;
  delete jetl_pt_histo;
  delete jet2l_eta_histo;
  delete jet2l_phi_histo;
  delete jet2l_pt_histo;
  delete met_histo;   
  delete met_OS_histo;     
  delete met_SS_histo;     
  delete meff_histo;       
  delete mt_histo;       
  delete invmass_histo;
  delete invmassOS_histo;
  delete invmassSS_histo;
  delete htmissOS_histo;
  delete htmissSS_histo;
  delete nGoodPV_histo;
      
  myfile.close();
  debugfile.close();
  dileptonfile.close();
  Target->Close();   
    
//  std::cout << "returning from PostAnalysis   "<<std::endl;
  return;

}


