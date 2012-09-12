#include <iostream>
#include <fstream>
using namespace std;
#include "MyAnalysis.h"
#include "TGraph.h"
#include "TMarker.h"
#include "TCanvas.h"
#include "TText.h"
#include "TBox.h"
#include "TMatrixDSym.h"
#include "TMatrixDSymEigen.h"
#include "TopTagger.C"
#include "mt2_bisect.cpp"
#include "TChainElement.h"

#include "triggerMatchE.cxx"

#define KEEP_EVENT 0 //used in Pre_OPS_OR
#define SKIP_EVENT 1

#define PI 3.1415926536

std::string L1_el = ELETRG;
std::string L1_mu = MUOTRG;
 
bool verbose = false;
//bool verbose = true;
  bool trg0 = false;  
  bool trg1 = false;
bool isBadMuon = false;

char const*  name_cutflow[]={
#ifdef MC  
  "no cut - with Pileup reweight",
  "no cut",
#else 
  "no cut",
  "GRL cut",
#endif
  "Lar error cut",
//  "Lar veto electron", //OBSOLETE
  "Lar veto jet",
  "jet cleaning",
  ">= 1 vertex with > 4 tracks",
  "Bad muon veto",
  "Cosmic veto",

#ifdef TRGSTUDY
  "EF_e10_medium_mu6",
  "EF_e10_medium_mu6 || singleElectron",
  "EF_e10_medium_mu6 || singleMuon",
  "EF_e10_medium_mu6 || singleMuon || singleElectron",
  "singleMuon || singleElectron",
#ifdef ACCEPTANCE  
  "EMU", 
  "&& EF_e10_medium_mu6",
  "&& EF_e10_medium_mu6 || singleElectron",
  "&& EF_e10_medium_mu6 || singleMuon",
  "&& EF_e10_medium_mu6 || singleMuon || singleElectron",
  "&& singleMuon || singleElectron",
#endif
#ifdef TAGPROBE  
  "Zee Tag", 
  " & Probe (EF_e10_medium)", 
  "Zmumu Tag", 
  " & Probe (EF_mu6)", 
  "Bootstrap for electron: muon matched to EF_mu6", 
  " && electron matched to EF_e10_medium", 
  "Bootstrap for muon: electron matched to EF_e10_medium", 
  " && muon matched to EF_mu6", 
#endif
#else
#ifdef ELECTRON
  "EE", 
#endif
#ifdef MUON
  "MUMU", 
#endif
  " && mll cut",
  " && OS ",
//  " && OS && TightIso",
  " && OS && Jet veto ",
  " && OS && Jet veto && Z veto ",
  " [SR1] && Jet veto && Z veto && METRel > 100 GeV",
  " && OS && nJet >= 2",
  " && OS && nJet >= 2 && Z veto",
  " && OS && nJet >= 2 && Z veto && Bjet veto",
  " && OS && nJet >= 2 && Z veto && Bjet veto && MCT Veto",
  " [SR3] && nJet >= 2 && Z veto && Bjet veto && MCT Veto && METRel > 50 GeV",
  " && OS && Jet veto && Z veto && METRel > 40 GeV",
  " && OS && Jet veto && Z veto && METRel > 40 GeV && Pt(l1) > 50 GeV",
  " && OS && Jet veto && Z veto && METRel > 40 GeV && Pt(l1) > 50 GeV && Pt(l1)+Pt(l2) > 100 GeV",
  " && OS && Jet veto && Z veto && METRel > 40 GeV && Pt(l1) > 50 GeV && Pt(l1)+Pt(l2) > 100 GeV && dPhi(MET,ll) > 2.5",
  " [SR4] && Jet veto && Z veto && METRel > 40 GeV && Pt(l1) > 50 GeV && Pt(l1)+Pt(l2) > 100 GeV && dPhi(MET,ll) > 2.5 && dPhi(MET,l2) > 0.5",
  " [SR5] && Jet veto && Z veto && METRel > 40 GeV && mT2 > 90 GeV",
  " && SS ",
  " && SS && Jet veto",
  " [SR2] && Jet veto && METRel > 100 GeV",
    
  "EMU ", 
  " && mll cut", 
  " && OS ",
  " && OS && Jet veto ",
  " && OS && Jet veto && Z veto ",
  " [SR1] && Jet veto && Z veto && METRel > 100 GeV",
  " && SS ",
  " && SS && Jet veto",
  " [SR2] && Jet veto && METRel > 100 GeV",
#endif
  };
  

int ndrellyan, ndrellyanNOT; 
bool drellyan = false;
int trgMu = 0;
int trgEl = 0;
#ifdef TRGSTUDY
int nEvents = 0; 
Bool_t isResurrected = false;
Bool_t isPassed = false;
Bool_t passedThrough = false;
Bool_t requireDecision = false;
#endif
 
//fill leptons variable BEFORE overlap removal for MET calculations
std::vector<int> velidx_beforeOR;
std::vector<int> vmuidx_beforeOR;
TVector2 met, met2;

ofstream myfile, debugfile, dileptonfile;

#include "functions.h"

  /*------------------------------------------------------------------------
    
                   Before OPS and OR  
  
  --------------------------------------------------------------------------*/

unsigned int MyAnalysis::Pre_OPS_OR(Long64_t entry){
  (void)entry; //avoid compiler warnings
  //if (entry > 100) return SKIP_EVENT;
  //if (entry < 1) return SKIP_EVENT;
      
  m_SUSYObjDef.Reset();

  jetpt_smeared  = m_sel->GetRawVector< std::vector<float> >("jet_AntiKt4TopoNewEM_pt");
  jeteta_smeared = m_sel->GetRawVector< std::vector<float> >("jet_AntiKt4TopoNewEM_eta");
  jetphi_smeared = m_sel->GetRawVector< std::vector<float> >("jet_AntiKt4TopoNewEM_phi");
  jetE_smeared   = m_sel->GetRawVector< std::vector<float> >("jet_AntiKt4TopoNewEM_E");  

  if (!(isData)){
    m_SUSYObjDef.SmearJets(&jetpt_smeared, &jeteta_smeared,&jetphi_smeared, &jetE_smeared) ;   
  }

//reject event here, otherwise crash due to not found variables
  runNumber = m_sel->GetScalarVal<int>("RunNumber");
  int lumiBlock = m_sel->GetScalarVal<int>("lbn");  
  if (isData)
    if (!(m_goodRunsList.HasRunLumiBlock(runNumber, lumiBlock))) return SKIP_EVENT;    
 
#ifdef TRGSTUDY
    
  int EF_mu6 = m_sel->GetScalarVal<int>("EF_mu6");
  
  #ifdef MC
  if (EF_mu6 > 0) isResurrected = true;
  else isResurrected = false;
  
  #else //resurrect trigger on data
  // get tree to initialize trigger tool
  if (nEvents == 0){ //first event in file
  
    cout << " initializing Trigger tool --- n Events: "<<nEvents<<endl;
    fChain = m_sel-> GetChain();
    //Long64_t nentries = fChain->GetEntries();    
    //cout << "Entry: "<< entry<< " - Getting Event tree with "<<nentries<<" entries"<<endl;

    TTree * fChainConf = fChain->GetFriend("susyMeta/TrigConfTree");
    //nentries = fChainConf->GetEntries(); 
    //cout << "Entry: "<< entry<< " - Getting Trigger info tree with "<<nentries<<" entries"<<endl;

    m_triggerTool = new D3PD::TrigDecisionToolD3PD(fChain,fChainConf);
  }   
  m_triggerTool->GetEntry(nEvents);  
  
 /* std::vector< std::string >  triggerPassed = m_triggerTool->GetPassedTriggers();
  
  if (triggerPassed.size())
    for (unsigned int i = 0; i < triggerPassed.size(); i++) {
      cout << "Entry "<<entry<<" passed "<<triggerPassed[i]<<endl;
    }
  
  //read event for triggertool  
  int EF_mu18 = m_sel->GetScalarVal<int>("EF_mu18");
  const std::string name = "EF_mu18";      
  bool isPassed = m_triggerTool->IsPassed(name, D3PD::TrigDefs::Physics);//allowResurrected);
  cout << "Entry "<<entry<<" passed EF_mu18 "<<isPassed<<" from D3PD "<< EF_mu18<<endl;*/
  const std::string name2 = "EF_mu6";      
  isPassed = m_triggerTool->IsPassed(name2, D3PD::TrigDefs::Physics);
  isResurrected = m_triggerTool->IsPassed(name2, D3PD::TrigDefs::allowResurrected);
  passedThrough = m_triggerTool->IsPassed(name2, D3PD::TrigDefs::passedThrough);
  requireDecision = m_triggerTool->IsPassed(name2, D3PD::TrigDefs::requireDecision);
  //cout << "Entry "<<entry<<" passed "<<isPassed<<" from D3PD "<< EF_mu6<<" isResurrected "<<isResurrected<<endl;*/
  
  #endif
  nEvents++;
  			 
#endif

  return KEEP_EVENT; 
}
  

unsigned int MyAnalysis::Between_OPS_and_OR(Long64_t entry) 
{
   (void)entry; //avoid compiler warnings

  //fill leptons variable BEFORE overlap removal
  std::vector<int> velidx;
  std::vector<int> vmuidx;
  vmuidx_beforeOR.clear();
  velidx_beforeOR.clear();
  
// calculate on not isolated muons!
      
  n_muo = m_sel->GetSizeByType("MUO"); //final electrons 
  if (n_muo){
    for (unsigned int i = 0; i < n_muo; i++) {      
      float eta = m_sel->GetValByType<float>("MUO","_eta", i);
      float phi = m_sel->GetValByType<float>("MUO","_phi", i);
      float E  = m_sel->GetValByType<float>("MUO","_E", i);
      float pt = m_sel->GetValByType<float>("MUO","_pt", i);      
      float me_qoverp_exPV = m_sel->GetValByType<float>("MUO","_me_qoverp_exPV", i);
      float id_qoverp_exPV = m_sel->GetValByType<float>("MUO","_id_qoverp_exPV", i);
      float id_theta_exPV  = m_sel->GetValByType<float>("MUO","_id_theta_exPV", i);
      float me_theta_exPV  = m_sel->GetValByType<float>("MUO","_me_theta_exPV", i);
      float id_theta  = m_sel->GetValByType<float>("MUO","_id_theta", i);
      //float ptcone20 = m_sel->GetValByType<float>("MUO","_ptcone20", i);  //isolation not to be applied to MET recalculation!	      
      int isComMuo = m_sel->GetValByType<int>("MUO","_isCombinedMuon", i);
      int isLowPt  = m_sel->GetValByType<int>("MUO","_isLowPtReconstructedMuon", i);
      //int tight  = m_sel->GetValByType<int>("MUO","_tight", i);
      int loose  = m_sel->GetValByType<int>("MUO","_loose", i); 
      int expectBLayerHit = m_sel->GetValByType<int>("MUO","_expectBLayerHit", i);
      int nPixelDeadSensors = m_sel->GetValByType<int>("MUO","_nPixelDeadSensors", i);
      int nSCTDeadSensors = m_sel->GetValByType<int>("MUO","_nSCTDeadSensors", i);
      int nBLHits = m_sel->GetValByType<int>("MUO","_nBLHits", i);
      int nPixHits = m_sel->GetValByType<int>("MUO","_nPixHits", i);
      int nPixHoles = m_sel->GetValByType<int>("MUO","_nPixHoles", i);
      int nSCTHits = m_sel->GetValByType<int>("MUO","_nSCTHits", i);
      int nSCTHoles = m_sel->GetValByType<int>("MUO","_nSCTHoles", i);
      int nTRTHits = m_sel->GetValByType<int>("MUO","_nTRTHits", i);
      int nTRTOutliers = m_sel->GetValByType<int>("MUO","_nTRTOutliers", i);
      bool isMuo = m_SUSYObjDef.IsMuon(i, pt, eta, phi, E, me_qoverp_exPV, id_qoverp_exPV, me_theta_exPV, id_theta_exPV, id_theta, isComMuo, isLowPt,
              loose, expectBLayerHit, nBLHits, nPixHits, nPixelDeadSensors, nPixHoles, nSCTHits, nSCTDeadSensors, nSCTHoles,
	      nTRTHits, nTRTOutliers, isData, MU_PT_CUT, MU_ETA_CUT, "");      
      if (isMuo) {
	vmuidx.push_back(i);        
	vmuidx_beforeOR.push_back(i);
        float qoverp_exPV = m_sel->GetValByType<float>("MUO","_qoverp_exPV", i);
        float cov_qoverp_exPV = m_sel->GetValByType<float>("MUO","_cov_qoverp_exPV", i);
        if (m_SUSYObjDef.IsBadMuon(qoverp_exPV,cov_qoverp_exPV,0.2)) isBadMuon = true; 
	}
      }
  }
  

// MET util NEW WAY -- electrons
    
  std::vector<float> elpt  = m_sel->GetRawVector< std::vector<float> >("el_pt");  //not smeared
  std::vector<float> eleta = m_sel->GetRawVector< std::vector<float> >("el_eta"); //
  std::vector<float> elphi = m_sel->GetRawVector< std::vector<float> >("el_phi"); //
  std::vector<float> elclE = m_sel->GetRawVector< std::vector<float> >("el_cl_E"); //
  std::vector<float> elcleta = m_sel->GetRawVector< std::vector<float> >("el_cl_eta"); //
  std::vector<float> elclphi = m_sel->GetRawVector< std::vector<float> >("el_cl_phi"); //
  std::vector<float> eltreta = m_sel->GetRawVector< std::vector<float> >("el_tracketa"); //
  std::vector<float> eltrphi = m_sel->GetRawVector< std::vector<float> >("el_trackphi"); //
  std::vector<int> elnPix = m_sel->GetRawVector< std::vector<int> >("el_nPixHits"); //
  std::vector<int> elnSCT = m_sel->GetRawVector< std::vector<int> >("el_nSCTHits"); //
  std::vector< std::vector<float> > elwet = m_sel->GetRawVector< std::vector< std::vector<float> > >( "el_MET_Simplified20_wet" );
  std::vector< std::vector<float> > elwpx = m_sel->GetRawVector< std::vector< std::vector<float> > >( "el_MET_Simplified20_wpx" );
  std::vector< std::vector<float> > elwpy = m_sel->GetRawVector< std::vector< std::vector<float> > >( "el_MET_Simplified20_wpy" );
  std::vector<vector<unsigned int> > elstatus = m_sel->GetRawVector< std::vector< std::vector<unsigned int> > >( "el_MET_Simplified20_statusWord" );
 
  //all electrons 
  if (elpt.size())
    for (unsigned int i = 0; i < elpt.size(); i++)    {       

    if (elwet.at(i).at(0) != 0.){
      // set by defualt only for electrons passing isElectron, now do smearing for all electrons
      m_SUSYObjDef.SetElecTLV(i,elcleta[i],elclphi[i],elclE[i],eltreta[i],eltrphi[i], elnPix[i],elnSCT[i],isData,0,false);	 
      TLorentzVector vec;
      vec = m_SUSYObjDef.m_el[i];
      elpt.at(i) = vec.Pt(); //smeared       
      eleta.at(i) = vec.Eta();       
      elphi.at(i) = vec.Phi();
      velidx.push_back(i);
    }  
  }
  
/*  
  //baseline electrons before OR 
  n_ele = m_sel->GetFinSizeByType("ELE"); //final electrons 

  ele_eta      = m_sel->GetFinVectorByType< std::vector<float> >("ELE","_eta", &n_ele);
  ele_phi      = m_sel->GetFinVectorByType< std::vector<float> >("ELE","_phi", &n_ele);
  ele_pt       = m_sel->GetFinVectorByType< std::vector<float> >("ELE","_pt", &n_ele);

  std::vector< std::vector<float> > elwet_beforeOR,elwpx_beforeOR,elwpy_beforeOR;
  std::vector<vector<unsigned int> > elstatus_beforeOR;
  
  if (n_ele){
    for (unsigned int i = 0; i < n_ele; i++) {
      int index = getIndex("ELE", ele_pt[i], ele_eta[i], ele_phi[i]);      
      velidx_beforeOR.push_back(index);
      elstatus_beforeOR.push_back(elstatus.at(index));
      elwet_beforeOR.push_back(elwet.at(index));
      elwpx_beforeOR.push_back(elwpx.at(index));
      elwpy_beforeOR.push_back(elwpy.at(index));
    }
  }*/
  
  // MET util NEW WAY -- jets
  
  std::vector< std::vector<float> > jetwet = m_sel->GetRawVector< std::vector< std::vector<float> > >( "jet_AntiKt4TopoNewEM_MET_Simplified20_wet" );
  std::vector< std::vector<float> > jetwpx = m_sel->GetRawVector< std::vector< std::vector<float> > >( "jet_AntiKt4TopoNewEM_MET_Simplified20_wpx" );
  std::vector< std::vector<float> > jetwpy = m_sel->GetRawVector< std::vector< std::vector<float> > >( "jet_AntiKt4TopoNewEM_MET_Simplified20_wpy" );
  std::vector<vector<unsigned int> > jetstatus = m_sel->GetRawVector< std::vector< std::vector<unsigned int> > >( "jet_AntiKt4TopoNewEM_MET_Simplified20_statusWord" );

  float METCellOutetx45 = m_sel->GetScalarVal<float>("MET_Simplified20_CellOut_etx");
  float METCellOutety45 = m_sel->GetScalarVal<float>("MET_Simplified20_CellOut_ety");
  float METCellOutsumet45 = m_sel->GetScalarVal<float>("MET_Simplified20_CellOut_sumet");
  float METRefGammaetx45 = m_sel->GetScalarVal<float>("MET_Simplified20_RefGamma_etx");
  float METRefGammaety45 = m_sel->GetScalarVal<float>("MET_Simplified20_RefGamma_ety"); 
  float METRefGammasumet45 = m_sel->GetScalarVal<float>("MET_Simplified20_RefGamma_sumet"); 

// MET util NEW WAY -- muons
  
  std::vector<float> mu_staco_ms_qoverp  = m_sel->GetRawVector< std::vector<float> >("mu_staco_ms_qoverp");
  std::vector<float> mu_staco_ms_theta = m_sel->GetRawVector< std::vector<float> >("mu_staco_ms_theta");
  std::vector<float> mu_staco_ms_phi = m_sel->GetRawVector< std::vector<float> >("mu_staco_ms_phi");
  std::vector<float> mu_staco_charge = m_sel->GetRawVector< std::vector<float> >("mu_staco_charge");
					
  met = m_SUSYObjDef.GetMET(&jetpt_smeared,
			    &jeteta_smeared,
			    &jetphi_smeared,
			    &jetE_smeared,
			    &jetwet,
			    &jetwpx,
			    &jetwpy,
			    &jetstatus,
			    velidx,
			    &elwet,
			    &elwpx,
			    &elwpy,
			    &elstatus,
			    METCellOutetx45, METCellOutety45, METCellOutsumet45,
			    METRefGammaetx45, METRefGammaety45, METRefGammasumet45,
			    vmuidx_beforeOR,
			    &mu_staco_ms_qoverp, 
			    &mu_staco_ms_theta, 
			    &mu_staco_ms_phi, 
			    &mu_staco_charge,
			    JetErr::NONE);

  return KEEP_EVENT;
}

  /*------------------------------------------------------------------------
    
                   Do the Analysis  
  
  --------------------------------------------------------------------------*/


void MyAnalysis::doAnalysis(Long64_t entry)
{
  (void)entry;

//  if (verbose)  std::cout << "Entry " << entry << " in Analysis (after OPS and OR) " << std::endl;
//  std::cout << "Entry " << entry << " in Analysis (after OPS and OR) " << std::endl;

  /*------------------------------------------------------------------------
    
                   Filling variables   
  
  --------------------------------------------------------------------------*/

  runNumber = m_sel->GetScalarVal<int>("RunNumber");
  int runNumberPileUp = m_sel->GetScalarVal<int>("RunNumber");
        
  if (!isData) runNumber = m_sel->GetScalarVal<int>("mc_channel_number");  
  
#ifdef PILEUP
  float averageIntPerXing = m_sel->GetScalarVal<float>("averageIntPerXing"); 
#endif
  eventNumber = m_sel->GetScalarVal<int>("EventNumber");
  int lumiBlock = m_sel->GetScalarVal<int>("lbn");  
  int larError = m_sel->GetScalarVal<int>("larError");
    
  //get SUSY process if SUSY grids
  susyprocess = -1;
  if ((runNumber > 120000)&&(runNumber < 150000))  susyprocess = getProcess(entry);    
  
  //get event weight for ttbar
  mc_evt_weight = 1.;

  if ((runNumber == 105200)||(runNumber == 105204)){  
//    cout << "MC sample, getting MC evt weight from file"<<endl;
    std::vector< std::vector<double> > mcevt_weight = m_sel->GetRawVector< std::vector< std::vector<double> > >( "mcevt_weight" );
    if ((mcevt_weight.size())>0)
      if (((mcevt_weight.at(0)).size())>0)
        mc_evt_weight = (mcevt_weight.at(0)).at(0);
  }

  //DY generator cut
  if ((runNumber == 108319)||(runNumber == 108320)) {
     drellyan = true;
     ndrellyan++;     
     if (!(doGenCutDrellYan(entry))) return ;       
     ndrellyanNOT++;  
     
   }//end if drell yan

  if ((runNumber <= 150000)||(runNumber >= 200000)) isData =  false;      
  
  isCosmic = false;
  isLarElectron = false;    
  isLarJet = false;

  int isOS = 0;
  bool OS = false;
  int nLeadingEl = 0;
  int nLeadingMu = 0;
  bool isIsoEle = false;
  bool isIsoMuo = false;
  
  // LEPTONS
  
  n_ele = m_sel->GetFinSizeByType("ELE"); //final electrons 
  n_muo = m_sel->GetFinSizeByType("MUO"); //final muons
  
  ele_eta      = m_sel->GetFinVectorByType< std::vector<float> >("ELE","_eta", &n_ele);
  ele_phi      = m_sel->GetFinVectorByType< std::vector<float> >("ELE","_phi", &n_ele);
  ele_tracketa = m_sel->GetFinVectorByType< std::vector<float> >("ELE","_tracketa", &n_ele);
  ele_trackphi = m_sel->GetFinVectorByType< std::vector<float> >("ELE","_trackphi", &n_ele);
  ele_pt       = m_sel->GetFinVectorByType< std::vector<float> >("ELE","_pt", &n_ele);
  ele_cl_eta   = m_sel->GetFinVectorByType< std::vector<float> >("ELE","_cl_eta", &n_ele);
  ele_cl_phi   = m_sel->GetFinVectorByType< std::vector<float> >("ELE","_cl_phi", &n_ele);
  ele_cl_E     = m_sel->GetFinVectorByType< std::vector<float> >("ELE","_cl_E", &n_ele);
  ele_ptcone20 = m_sel->GetFinVectorByType< std::vector<float> >("ELE","_ptcone20", &n_ele);
  ele_charge   = m_sel->GetFinVectorByType< std::vector<float> >("ELE","_charge", &n_ele);
  ele_isEM     = m_sel->GetFinVectorByType< std::vector<unsigned int> >("ELE","_tightPP", &n_ele);
  ele_etcone20 = m_sel->GetFinVectorByType< std::vector<float> >("ELE","_Etcone20", &n_ele);
  ele_et       = m_sel->GetFinVectorByType< std::vector<float> >("ELE","_Et", &n_ele);
  
  muo_eta      = m_sel->GetFinVectorByType< std::vector<float> >("MUO","_eta", &n_muo);
  muo_pt       = m_sel->GetFinVectorByType< std::vector<float> >("MUO","_pt", &n_muo);
  muo_phi      = m_sel->GetFinVectorByType< std::vector<float> >("MUO","_phi", &n_muo);
  muo_charge   = m_sel->GetFinVectorByType< std::vector<float> >("MUO","_charge", &n_muo);
  muo_ptcone20 = m_sel->GetFinVectorByType< std::vector<float> >("MUO","_ptcone20", &n_muo);
  muo_d0       = m_sel->GetFinVectorByType< std::vector<float> >("MUO","_d0_exPV", &n_muo);
  muo_z0       = m_sel->GetFinVectorByType< std::vector<float> >("MUO","_z0_exPV", &n_muo);
  std::vector<int> isCom = m_sel->GetFinVectorByType< std::vector<int> >("MUO","_isCombinedMuon", &n_muo);
  
  // SELECTED JETS 
  n_jet = m_sel->GetFinSizeByType("JET"); 
  jet_pt  = m_sel->GetFinVectorByType< std::vector<float> >("JET","_pt", &n_jet);
  jet_eta = m_sel->GetFinVectorByType< std::vector<float> >("JET","_eta", &n_jet);
  jet_phi = m_sel->GetFinVectorByType< std::vector<float> >("JET","_phi", &n_jet);
  jet_jvtxf = m_sel->GetFinVectorByType< std::vector<float> >("JET","_jvtxf", &n_jet);
  jet_flavor_weight_xxx  = m_sel->GetFinVectorByType< std::vector<float> >("JET","_flavor_weight_JetFitterCOMBNN", &n_jet); 
#ifdef MC
  std::vector<float> jet_flavor_truth_label  = m_sel->GetFinVectorByType< std::vector<float> >("JET","_flavor_truth_label", &n_jet); 
#endif
  
  // INITIAL JETS 
  unsigned int n_jet_ini = m_sel->GetSizeByType("JET"); 
  std::vector<float> jet_BCH_CORR_JET_ini  = m_sel->GetVectorByType< std::vector<float> >("JET","_BCH_CORR_JET", &n_jet_ini);
  std::vector<float> jet_BCH_CORR_CELL_ini = m_sel->GetVectorByType< std::vector<float> >("JET","_BCH_CORR_CELL", &n_jet_ini);
  std::vector<float> jet_BCH_CORR_DOTX_ini = m_sel->GetVectorByType< std::vector<float> >("JET","_BCH_CORR_DOTX", &n_jet_ini);

  //fill with smeared quantities (only selected electrons)
  std::vector<float> ele_pt_smeared,ele_eta_smeared,ele_phi_smeared;
  if (n_ele)
    for (unsigned int i = 0; i < n_ele; i++)  {
      unsigned int index = getIndex("ELE", ele_pt[i], ele_eta[i], ele_phi[i]);
      TLorentzVector vec;
      vec = m_SUSYObjDef.m_el[index];
      ele_pt_smeared.push_back(vec.Pt());
      ele_eta_smeared.push_back(vec.Eta());
      ele_phi_smeared.push_back(vec.Phi());
             
      //if (m_SUSYObjDef.IsLArHole(vec.Eta(), vec.Phi())) isLarElectron = true;   //after smearing
      if (m_SUSYObjDef.IsLArHole(ele_cl_eta[i], ele_cl_phi[i])) isLarElectron = true; 
        
    }
  
  // Lar hole for jets, pt > 20 GeV, use runNumber for both data,mc  
  if (n_jet_ini){
    for (unsigned int i = 0; i < n_jet_ini; i++){
      if (m_SUSYObjDef.IsLArHoleVeto(jetpt_smeared.at(i), jeteta_smeared.at(i), jetphi_smeared.at(i), jet_BCH_CORR_JET_ini[i], jet_BCH_CORR_CELL_ini[i], isData, 20000., runNumberPileUp)) {
	  if (fakeMetEst.isBad(jetpt_smeared.at(i),jet_BCH_CORR_JET_ini[i], jet_BCH_CORR_CELL_ini[i],jet_BCH_CORR_DOTX_ini[i],jetphi_smeared.at(i),met.Px(),met.Py(),10000.,10.,-1.,-1.)) 
	    isLarJet = true;
      }
    }	     
  }
    
  //------------------------------------------------------------------------
    
  //                 Cutflow  
  
  //-------------------------------------------------------------------------


//DEBUG
/*  if ((eventNumber == 30000)){
//  if ((eventNumber == 30000)||(eventNumber == 49930)||(eventNumber == 49072)||(eventNumber == 5504)){
//    if ((entry == 6837)){
     cout <<endl<< "Event "<<eventNumber  << " "<< L1_el << " " << trgEl << " "<< L1_mu << " "<<trgMu <<endl; 
     debugfile << "Event "<<eventNumber<<" "<< L1_el << " " << trgEl << " "<< L1_mu << " "<<trgMu <<endl; 
     
     int n_muo_ini = m_sel->GetSizeByType("MUO");
     cout << "n initial muons "<< n_muo_ini<<endl;
     
     if (n_muo_ini>0) {
        for (unsigned int i = 0; i < n_muo_ini; i++){
          TLorentzVector vec = m_SUSYObjDef.m_mu[i];
          cout << "pt "<<m_sel->GetValByType<float>("MUO","_pt", i)<<" after smearing : pt "<<vec.Pt()<<endl;  	       
        } 
     }
       
     cout << "n baseline muons (after OR) "<< n_muo<<endl;
     if (n_muo){
        for (unsigned int i = 0; i < n_muo; i++){
          cout << "muon "<< i<<" : pt "<<muo_pt[i]<<" eta "<< muo_eta[i]<<" phi "<< muo_phi[i]<<" charge "<< muo_charge[i]<<endl;  	  
          int index = getIndex("MUO", muo_pt[i], muo_eta[i], muo_phi[i]);
    
          TLorentzVector vec = m_SUSYObjDef.m_mu[index];
          cout << "after smearing : pt "<<vec.Pt()<<endl;  	  
	  
          cout <<"CosmicMuon:  z0_pv: " <<muo_z0[i] <<" d0_pv: " <<muo_d0[i]<<endl;
        }//end loop over muons  	
     
     }//end if n muons
     
     int n_ele_ini = m_sel->GetSizeByType("ELE");
     cout << "n initial electrons "<< n_ele_ini<<" (smearing only for preselected electrons, before OR)"<<endl;
     if (n_ele_ini>0) {
        for (unsigned int i = 0; i < n_ele_ini; i++){
          TLorentzVector vec = m_SUSYObjDef.m_el[i];
          cout << "pt "<<m_sel->GetValByType<float>("ELE","_pt", i)<<" after smearing : pt "<<vec.Pt()<<endl;  	       
        } 
     }
     
     cout << "n baseline electrons (after OR) "<< n_ele<<endl;  
     if (n_ele){
        for (unsigned int i = 0; i < n_ele; i++){
          cout << "electron "<< i<<" : pt "<<ele_pt[i]<<" eta "<< ele_eta[i]<<" phi "<< ele_phi[i]<<" charge "<< ele_charge[i]<<endl;  	  
          debugfile << "electron "<< i<<" : pt "<<ele_pt[i]<<" eta "<< ele_eta[i]<<" phi "<< ele_phi[i]<<" charge "<< ele_charge[i]<<endl;  	  
          int index = getIndex("ELE", ele_pt[i], ele_eta[i], ele_phi[i]);  //index in SUSYTools  
          cout <<"isSignalElectron "<< (m_SUSYObjDef.IsSignalElectron(index, ele_isEM[i], ele_ptcone20[i], EL_PT_CUT, EL_ISO_CUT)) <<endl;   
        }
     }  
     
     cout << "n initial jets "<< n_jet_ini<<endl;  
     if (n_jet_ini){
        for (unsigned int i = 0; i < n_jet_ini; i++){
          cout << "jet "<< i<<" : pt "<<m_sel->GetValByType<float>("JET","_pt", i)<< " after smearing "<<jetpt_smeared.at(i)<<" eta "<< jet_eta[i]<<" phi "<< jet_phi[i]<<endl;  	  
          
    
  	    float jet_emscale_eta = m_sel->GetValByType<float>("JET","_emscale_eta", i);
  	    float jet_sumPtTrk    = m_sel->GetValByType<float>("JET","_sumPtTrk", i);
  	    float jet_NegativeE   = m_sel->GetValByType<float>("JET","_NegativeE", i);
  	    float jet_Timing      = m_sel->GetValByType<float>("JET","_Timing", i);   
  	    float jet_LArQuality  = m_sel->GetValByType<float>("JET","_LArQuality", i);  
  	    float jet_HECQuality  = m_sel->GetValByType<float>("JET","_HECQuality", i);  
  	    float jet_emfrac      = m_sel->GetValByType<float>("JET","_emfrac",i);
  	    float jet_hecf        = m_sel->GetValByType<float>("JET","_hecf",i);
  	    float jet_fracSamplingMax = m_sel->GetValByType<float>("JET","_fracSamplingMax", i);
  	    float jet_AverageLArQF = m_sel->GetValByType<float>("JET","_AverageLArQF", i);
            
	    cout << "emscale_eta "<<jet_emscale_eta<<endl;        
            cout << "sumPtTrk "<<jet_sumPtTrk<<endl;	
            cout << "NegativeE "<<jet_NegativeE<<endl;	
            cout << "Timing "<<jet_Timing<<endl;	
            cout << "LArQuality "<<jet_LArQuality<<endl;  
            cout << "HECQuality "<<jet_HECQuality<<endl;  
            cout << "emfrac "<<jet_emfrac<<endl;	
            cout << "hecf "<<jet_hecf<<endl;	
            cout << "fracSamplingMax "<<jet_fracSamplingMax<<endl;
        
  	    bool isbadJet = JetID::isBadJet(JetID::VeryLooseBad, jet_emfrac, jet_hecf, jet_LArQuality, jet_HECQuality, jet_Timing, jet_sumPtTrk/1000., 
              jet_emscale_eta,jetpt_smeared.at(i)/1000., jet_fracSamplingMax, jet_NegativeE, jet_AverageLArQF);
            cout << "Bad Jet "<< isbadJet <<endl;
           
	    //look if there is an overlapping electron
            if ((n_ele) && isbadJet){
              for (unsigned int j = 0; j < n_ele; j++){
	  
	      //float dR = deltaR(ele_eta[j],ele_phi[j],jet_emscale_eta,jet_emscale_phi);
	      float dR = deltaR(ele_eta_smeared[j],ele_phi_smeared[j],jeteta_smeared.at(i),jetphi_smeared.at(i));
	      if (dR < 0.2) cout << "overlapping with electron"; // jet would be removed in OR
	      }
	    }  
             
       }          
     }  
     
     cout << "n baseline jets "<< n_jet<<endl;  
     if (n_jet){
        for (unsigned int i = 0; i < n_jet; i++){
          cout << "jet "<< i<<" : pt "<<jet_pt[i]<< " after smearing "<<jetpt_smeared.at(getIndex("JET", jet_pt[i], jet_eta[i], jet_phi[i]))<<" eta "<< jet_eta[i]<<" phi "<< jet_phi[i]<<endl;  	            	    
        
	}   
     }         
  }//end if debug
*/   
  //    ---------------------------------------
  //     CUT 0 --- no cut  -- APPLY PILEUP REWEIGHTING at this point!!!
  //    ---------------------------------------

  bin =0;
  double pileupEventWeight = 1.;
  float MET = -999.;
  
#ifdef PILEUP
  if (!isData){
    pileupEventWeight = m_tPileUp->GetCombinedWeight(runNumberPileUp,runNumber,averageIntPerXing);
    //cout << "run "<< runNumber<< " "<<runNumberPileUp<<" evt "<< eventNumber<< " PileUp weight "<< pileupEventWeight << " for mu = "<<averageIntPerXing<<endl;
  }   
#endif
  
  fill_histo(mc_evt_weight*pileupEventWeight, bin, MET);  
  runNumber_histo->Fill(runNumber,mc_evt_weight*pileupEventWeight); 
   
  //    ---------------------------------------
  //    CUT 1 - GRL from https://twiki.cern.ch/twiki/pub/AtlasProtected/GoodRunListSummer2010/  
  //    ---------------------------------------

#ifdef PILEUP
  if (!isData){
    mc_evt_weight = mc_evt_weight*pileupEventWeight;
  }   
#endif

  if (isData)
    if (!(m_goodRunsList.HasRunLumiBlock(runNumber, lumiBlock))) return ;    
  
  bin += 1;
  fill_histo(mc_evt_weight, bin, MET);  

  //    ---------------------------------------
  //    CUT 1-a - LAR error cut
  //    ---------------------------------------

  if (isData)
    if (!(larError == 0.)) return ;    
  
  bin += 1;
  fill_histo(mc_evt_weight, bin, MET); 
   
  //    ---------------------------------------
  //    CUT 1-b - LAR electron cut
  //    ---------------------------------------

  //OBSOLETE, applied in SUSYTools.isElectron
  //if (isLarElectron) return ;    
  
  //bin += 1;
  //fill_histo(mc_evt_weight, bin, MET);  
   
  //    ---------------------------------------
  //    CUT 1-c - LAR jet cut
  //    ---------------------------------------

  if (isLarJet) return ;    
  
  bin += 1;
  fill_histo(mc_evt_weight, bin, MET);  
  

//    ---------------------------------------
//    CUT 2 jet cleaning cuts --- 
//    also on MC, changed to  VeryLooseBad
//    ---------------------------------------

  bool badJet = false;    
  if (n_jet_ini){
    for (unsigned int i = 0; i < n_jet_ini; i++){
  
     if ( jetpt_smeared.at(i)>20000.){
    
  	float jet_emscale_eta = m_sel->GetValByType<float>("JET","_emscale_eta", i);
  	float jet_sumPtTrk    = m_sel->GetValByType<float>("JET","_sumPtTrk", i);
  	float jet_NegativeE   = m_sel->GetValByType<float>("JET","_NegativeE", i);
  	float jet_Timing      = m_sel->GetValByType<float>("JET","_Timing", i);   
  	float jet_LArQuality  = m_sel->GetValByType<float>("JET","_LArQuality", i);  
  	float jet_HECQuality  = m_sel->GetValByType<float>("JET","_HECQuality", i);  
  	float jet_emfrac      = m_sel->GetValByType<float>("JET","_emfrac",i);
  	float jet_hecf        = m_sel->GetValByType<float>("JET","_hecf",i);
  	float jet_fracSamplingMax = m_sel->GetValByType<float>("JET","_fracSamplingMax", i);
  	float jet_AverageLArQF = m_sel->GetValByType<float>("JET","_AverageLArQF", i);
        
  	badJet = JetID::isBadJet(JetID::VeryLooseBad, jet_emfrac, jet_hecf, jet_LArQuality, jet_HECQuality, jet_Timing, jet_sumPtTrk/1000., 
            jet_emscale_eta,jetpt_smeared.at(i)/1000., jet_fracSamplingMax, jet_NegativeE, jet_AverageLArQF);
    
        //look if there is an overlapping electron
        if ((n_ele) && badJet){
          for (unsigned int j = 0; j < n_ele; j++){
	  
	    //float dR = deltaR(ele_eta[j],ele_phi[j],jet_emscale_eta,jet_emscale_phi);
	    float dR = deltaR(ele_eta_smeared[j],ele_phi_smeared[j],jeteta_smeared.at(i),jetphi_smeared.at(i));
	    if (dR < 0.2) badJet = false; // jet would be removed in OR
	  }
	}  

	    
        if (badJet) return;

      }//end if jet_pt > 20 GeV, ANY ETA,  and BAD
    }//end loop over jets    
  }//end if n jets
  
  bin += 1;  
  
  if (!badJet) fill_histo(mc_evt_weight, bin, MET); //fill histo for MC 
  if (!badJet) debugfile << eventNumber<<" "<<endl; 

//    ---------------------------------------
//    CUT 3 Check there is a good vertex
//    ---------------------------------------

  std::vector<int>vx_nTracks = m_sel->GetRawVector< std::vector<int> >("vx_nTracks");  
  nGoodPV = 0;  
  for (unsigned int ivx = 0; ivx < vx_nTracks.size(); ivx++){
    if (vx_nTracks.at(ivx) > 4) {
      nGoodPV ++;  
    }
  }

  if (not(m_SUSYObjDef.IsGoodVertex(&vx_nTracks))) return;

  bin += 1;
  fill_histo(mc_evt_weight, bin, MET);    
   
//   ---------------------------------------
//   CUT 4 - Bad Muon cut
//   ---------------------------------------

  if (isBadMuon) return ;	 
  
  bin += 1;
  fill_histo(mc_evt_weight, bin, MET);  

//    ---------------------------------------
//    CUT 5 cosmic veto cut
//    ---------------------------------------
  
  if (n_muo)
     for (unsigned int i = 0; i < n_muo; i++)
 	if (m_SUSYObjDef.IsCosmicMuon(muo_z0[i], muo_d0[i], 1., 0.2)) return;  

  bin += 1;
  
  fill_histo(mc_evt_weight, bin, MET);  

//    ---------------------------------------
//    trigger cut
//    ---------------------------------------
  
  if (isData){
    L1_el = getTriggerElectron(runNumber);
    trgEl = m_sel->GetScalarVal<int>(L1_el);
    L1_mu = getTriggerMuon(runNumber);  
    trgMu = m_sel->GetScalarVal<int>(L1_mu);  
  //default for MC
  }else{
    trgEl = m_sel->GetScalarVal<int>("EF_e20_medium");
    trgMu = m_sel->GetScalarVal<int>("EF_mu18");
   }
   
    
#ifdef TRGSTUDY
  //int EF_e10_medium = m_sel->GetScalarVal<int>("EF_e10_medium");
  int EF_mu6 = m_sel->GetScalarVal<int>("EF_mu6");
  int trg_e_mu = m_sel->GetScalarVal<int>("EF_e10_medium_mu6");

  bin += 1;
  if (trg_e_mu) fill_histo(mc_evt_weight, bin, MET); 
  bin += 1;
  if (trg_e_mu || trgEl) fill_histo(mc_evt_weight, bin, MET); 
  bin += 1;
  if (trg_e_mu || trgMu) fill_histo(mc_evt_weight, bin, MET);	      
  bin += 1;
  if (trg_e_mu || trgEl || trgMu) fill_histo(mc_evt_weight, bin, MET); 
  bin += 1;
  if ( trgEl || trgMu) fill_histo(mc_evt_weight, bin, MET); 

#else

//if using trigger weights!!
#ifdef MC
#else

//require trigger matching in data

  std::vector<int> triggerChain_e_single;
  std::vector<int> triggerChain_e_double;
  std::vector<int> triggerChain_mu_single;
  std::vector<int> triggerChain_mu_double = m_sel->GetRawVector< std::vector<int> >("trig_EF_trigmuonef_EF_2mu10_loose");
  std::vector<int> triggerChain_e  = m_sel->GetRawVector< std::vector<int> >("trig_EF_el_EF_e10_medium");
  std::vector<int> triggerChain_mu = m_sel->GetRawVector< std::vector<int> >("trig_EF_trigmuonef_EF_mu6");

  std::vector<float> trig_EF_el_px = m_sel->GetRawVector< std::vector<float> > ("trig_EF_el_px"); 
  std::vector<float> trig_EF_el_py = m_sel->GetRawVector< std::vector<float> > ("trig_EF_el_py"); 
  std::vector<float> trig_EF_el_pz = m_sel->GetRawVector< std::vector<float> > ("trig_EF_el_pz"); 
  std::vector<float> trig_EF_el_E = m_sel->GetRawVector< std::vector<float> > ("trig_EF_el_E"); 
    
  std::vector< std::vector<float> > trig_EF_trigmuonef_track_CB_phi = m_sel->GetRawVector< std::vector< std::vector<float> > >("trig_EF_trigmuonef_track_CB_phi" );
  std::vector< std::vector<float> > trig_EF_trigmuonef_track_CB_eta = m_sel->GetRawVector< std::vector< std::vector<float> > >("trig_EF_trigmuonef_track_CB_eta" );

  if(runNumber>=177986 && runNumber<=186755) { //A-J
    triggerChain_e_single = m_sel->GetRawVector< std::vector<int> >("trig_EF_el_EF_e20_medium");
    triggerChain_e_double = m_sel->GetRawVector< std::vector<int> >("trig_EF_el_EF_2e12_medium");
  }
  else if(runNumber>=186873 && runNumber<=187815) { //K
    triggerChain_e_single = m_sel->GetRawVector< std::vector<int> >("trig_EF_el_EF_e22_medium");
    triggerChain_e_double = m_sel->GetRawVector< std::vector<int> >("trig_EF_el_EF_2e12T_medium");
  }
  else { //L-M
    triggerChain_e_single = m_sel->GetRawVector< std::vector<int> >("trig_EF_el_EF_e22vh_medium1");
    triggerChain_e_double = m_sel->GetRawVector< std::vector<int> >("trig_EF_el_EF_2e12Tvh_medium");
  }

  if(runNumber>=177986 && runNumber<=186755) {
    triggerChain_mu_single = m_sel->GetRawVector< std::vector<int> >("trig_EF_trigmuonef_EF_mu18");
  } else { 
    triggerChain_mu_single = m_sel->GetRawVector< std::vector<int> >("trig_EF_trigmuonef_EF_mu18_medium");
  }

#endif //MC

#endif //TRGSTUDY

//    ---------------------------------------

//     EE , EMU and MUMU definitions

//    ---------------------------------------
       
  // EXACTLY 2 leptons after event selection 
  if (!((n_ele +n_muo)==2)) return ;
  
  TLorentzVector vec1;
  TLorentzVector vec2;
  
  double myEventWeight = 1;
  bool ee = false;
  bool emu = false;
  bool mumu = false;
  bool isMll = false;
  int index_0, index_1;
  trg0 = false;
  trg1 = false;
          
  if (n_ele ==2) {                     // EE case  

#ifdef MUON
    return;
#endif
    
    isOS = -1;  
    if ((ele_charge[0]*ele_charge[1])==-1.) {
      OS = true; 
      isOS = 1;
    } 
    
    index_0 = getIndex("ELE", ele_pt[0], ele_eta[0], ele_phi[0]);
    index_1 = getIndex("ELE", ele_pt[1], ele_eta[1], ele_phi[1]);
    
    if (m_SUSYObjDef.IsSignalElectron(index_0, ele_isEM[0], ele_ptcone20[0], EL_PT_CUT, EL_ISO_CUT) &&
        m_SUSYObjDef.IsSignalElectron(index_1, ele_isEM[1], ele_ptcone20[1], EL_PT_CUT, EL_ISO_CUT)) isIsoEle = true;

    
    vec1 = m_SUSYObjDef.m_el[index_0];
    vec2 = m_SUSYObjDef.m_el[index_1];
  
    if (vec1.Pt()> EL_LEAD_PT_CUT) nLeadingEl++; 
    if (vec2.Pt()> EL_LEAD_PT_CUT) nLeadingEl++; 
  
// EVENT WEIGHT for selected ELECTRONS
    if (!isData) myEventWeight *= m_SUSYObjDef.GetSignalElecSF(ele_cl_eta[0], ele_cl_E[0]/cosh(ele_cl_eta[0]),7,6,0,0) 
     * m_SUSYObjDef.GetSignalElecSF(ele_cl_eta[1], ele_cl_E[1]/cosh(ele_cl_eta[1]),7,6,0,0);

#ifdef ELESFUP
    if (!isData) myEventWeight *= (m_SUSYObjDef.GetSignalElecSF(ele_cl_eta[0], ele_cl_E[0]/cosh(ele_cl_eta[0])) + m_SUSYObjDef.GetSignalElecSFUnc(ele_cl_eta[0], ele_cl_E[0]/cosh(ele_cl_eta[0])))
     * (m_SUSYObjDef.GetSignalElecSF(ele_cl_eta[1], ele_cl_E[1]/cosh(ele_cl_eta[1])) + m_SUSYObjDef.GetSignalElecSFUnc(ele_cl_eta[1], ele_cl_E[1]/cosh(ele_cl_eta[1])));
#endif
#ifdef ELESFDOWN
    if (!isData) myEventWeight *= (m_SUSYObjDef.GetSignalElecSF(ele_cl_eta[0], ele_cl_E[0]/cosh(ele_cl_eta[0])) - m_SUSYObjDef.GetSignalElecSFUnc(ele_cl_eta[0], ele_cl_E[0]/cosh(ele_cl_eta[0])))
     * (m_SUSYObjDef.GetSignalElecSF(ele_cl_eta[1], ele_cl_E[1]/cosh(ele_cl_eta[1])) - m_SUSYObjDef.GetSignalElecSFUnc(ele_cl_eta[1], ele_cl_E[1]/cosh(ele_cl_eta[1])));
#endif

#ifdef TRGWEIGHT
  if (!isData){
    double LumiFrac_185353_186755 = m_tPileUp->GetIntegratedLumiFraction(runNumberPileUp,185353,186755);
    double LumiFrac_186873_187815 = m_tPileUp->GetIntegratedLumiFraction(runNumberPileUp,186873,187815); 
    double triggerWeight = trgRWT->triggerReweightEE(runNumberPileUp, vec1.Pt(), vec1.Eta(), vec2.Pt(), vec2.Eta(), LumiFrac_185353_186755,  LumiFrac_186873_187815);
    mc_evt_weight = mc_evt_weight*triggerWeight;  
  }   
#endif
					  
    // EE  two isolated electrons (pt cut in trigger weight)
    ee = isIsoEle;
    
#ifdef TRGSTUDY
#else
#ifdef MC
#else
    if (isData){ //require trigger match
      bool triggermatch = false; 

      //first lepton in plateau of single electron trigger      
      if (vec1.Pt()> EL_LEAD_PT_CUT) {
        triggermatch = triggerMatchE(vec1,&trig_EF_el_px,&trig_EF_el_py,&trig_EF_el_pz,&trig_EF_el_E,&triggerChain_e_single);
      } 
      
      // also second lepton in plateau of single electron trigger
      if (vec2.Pt()> EL_LEAD_PT_CUT) {
        if (!triggermatch) triggermatch = triggerMatchE(vec2,&trig_EF_el_px,&trig_EF_el_py,&trig_EF_el_pz,&trig_EF_el_E,&triggerChain_e_single);
      }
      
      //both electrons in plateau of dielectron trigger but not in plateau of single lepton trigger
      if ((vec1.Pt()> 17000.)&& (vec2.Pt()> 17000.) && (nLeadingEl == 0)) triggermatch = triggerMatchEE(vec1,vec2,&trig_EF_el_px,&trig_EF_el_py,&trig_EF_el_pz,&trig_EF_el_E,&triggerChain_e_double);    
      ee = isIsoEle && triggermatch;
    }
#endif
#endif
    
    if (ee) dileptonfile <<"EE event nb: "<<eventNumber<<" run nb: "<<runNumber <<endl;
     
  } else if (n_muo ==2) {            // MUMU case

#ifdef ELECTRON
    return;
#endif
    index_0 = getIndex("MUO", muo_pt[0], muo_eta[0], muo_phi[0]);
    index_1 = getIndex("MUO", muo_pt[1], muo_eta[1], muo_phi[1]);
   
    isOS = -1;  
    if ((muo_charge[0]*muo_charge[1])==-1.) {
      OS = true; 
      isOS = 1;
    } 

    if (m_SUSYObjDef.IsSignalMuon(index_0, muo_ptcone20[0], MU_PT_CUT, MU_PTCONE20_CUT) &&
        m_SUSYObjDef.IsSignalMuon(index_1, muo_ptcone20[1], MU_PT_CUT, MU_PTCONE20_CUT)) isIsoMuo = true;
    
    vec1 = m_SUSYObjDef.m_mu[index_0];
    vec2 = m_SUSYObjDef.m_mu[index_1];

    if (vec1.Pt()> MU_LEAD_PT_CUT) nLeadingMu++; 
    if (vec2.Pt()> MU_LEAD_PT_CUT) nLeadingMu++; 

    if (!isData) myEventWeight *= m_SUSYObjDef.GetSignalMuonSF(index_0) * m_SUSYObjDef.GetSignalMuonSF(index_1);  
#ifdef MUOSFUP
    if (!isData) myEventWeight *= (m_SUSYObjDef.GetSignalMuonSF(index_0) + m_SUSYObjDef.GetSignalMuonSFUnc(index_0))* 
      (m_SUSYObjDef.GetSignalMuonSF(index_1) + m_SUSYObjDef.GetSignalMuonSFUnc(index_1));  
#endif
#ifdef MUOSFDOWN
    if (!isData) myEventWeight *= (m_SUSYObjDef.GetSignalMuonSF(index_0) - m_SUSYObjDef.GetSignalMuonSFUnc(index_0))* 
      (m_SUSYObjDef.GetSignalMuonSF(index_1) - m_SUSYObjDef.GetSignalMuonSFUnc(index_1));  
#endif
    
    // MUMU two isolated muons (pt cut in trigger weight)
    mumu = isIsoMuo;

#ifdef TRGSTUDY
#else
#ifdef MC
#else
    if (isData){ //require trigger match
      bool triggermatch = triggerMatchMU(vec1, vec2, &triggerChain_mu_single, &triggerChain_mu_double, &trig_EF_trigmuonef_track_CB_eta, &trig_EF_trigmuonef_track_CB_phi);
      mumu = isIsoMuo && triggermatch;
    }
#endif
#endif
    if (mumu) dileptonfile <<"MUMU event nb: "<<eventNumber<<" run nb: "<<runNumber <<endl;

     
#ifdef TRGWEIGHT
  if (!isData){
    double LumiFrac_185353_186493 = m_tPileUp->GetIntegratedLumiFraction(runNumberPileUp,185353,186493);
    double LumiFrac_186516_187815 = m_tPileUp->GetIntegratedLumiFraction(runNumberPileUp,186516,187815); 
    double triggerWeight = trgRWT->triggerReweightMM(runNumberPileUp, vec1.Pt(), vec1.Eta(),vec1.Phi(),isCom[0],muo_ptcone20[0],
                                                               vec2.Pt(), vec2.Eta(),vec2.Phi(),isCom[1],muo_ptcone20[1], 
                                                               LumiFrac_185353_186493, LumiFrac_186516_187815);     
    mc_evt_weight = mc_evt_weight*triggerWeight;  
  }   
#endif
  
  
  } else if ((n_muo == 1 ) &&(n_ele == 1) ) {          // EMU case
        
    isOS = -1;  
    if ((ele_charge[0]*muo_charge[0])==-1.) {
      OS = true; 
      isOS = 1;
    }   

    index_0 = getIndex("ELE", ele_pt[0], ele_eta[0], ele_phi[0]);
    index_1 = getIndex("MUO", muo_pt[0], muo_eta[0], muo_phi[0]);
    
    if (m_SUSYObjDef.IsSignalElectron(index_0, ele_isEM[0], ele_ptcone20[0], EL_PT_CUT, EL_ISO_CUT)) isIsoEle = true;
    if (m_SUSYObjDef.IsSignalMuon(index_1, muo_ptcone20[0], MU_PT_CUT, MU_PTCONE20_CUT)) isIsoMuo = true;
    
    if (!isData) myEventWeight *= m_SUSYObjDef.GetSignalElecSF(ele_cl_eta[0], ele_cl_E[0]/cosh(ele_cl_eta[0]),7,6,0,0) * m_SUSYObjDef.GetSignalMuonSF(index_1);  

#ifdef ELESFUP
    if (!isData) myEventWeight *= (m_SUSYObjDef.GetSignalElecSF(ele_cl_eta[0], ele_cl_E[0]/cosh(ele_cl_eta[0])) + m_SUSYObjDef.GetSignalElecSFUnc(ele_cl_eta[0], ele_cl_E[0]/cosh(ele_cl_eta[0])))
     * m_SUSYObjDef.GetSignalMuonSF(index_1);
#endif
#ifdef ELESFDOWN
    if (!isData) myEventWeight *= (m_SUSYObjDef.GetSignalElecSF(ele_cl_eta[0], ele_cl_E[0]/cosh(ele_cl_eta[0])) - m_SUSYObjDef.GetSignalElecSFUnc(ele_cl_eta[0], ele_cl_E[0]/cosh(ele_cl_eta[0])))
     * m_SUSYObjDef.GetSignalMuonSF(index_1);
#endif
#ifdef MUOSFUP
    if (!isData) myEventWeight *= m_SUSYObjDef.GetSignalElecSF(ele_cl_eta[0], ele_cl_E[0]/cosh(ele_cl_eta[0]))* 
      (m_SUSYObjDef.GetSignalMuonSF(index_1) + m_SUSYObjDef.GetSignalMuonSFUnc(index_1));  
#endif
#ifdef MUOSFDOWN
    if (!isData) myEventWeight *= m_SUSYObjDef.GetSignalElecSF(ele_cl_eta[0], ele_cl_E[0]/cosh(ele_cl_eta[0]))* 
      (m_SUSYObjDef.GetSignalMuonSF(index_1) - m_SUSYObjDef.GetSignalMuonSFUnc(index_1));  
#endif

    vec1 = m_SUSYObjDef.m_el[index_0];
    vec2 = m_SUSYObjDef.m_mu[index_1];

    if (vec1.Pt()> EL_LEAD_PT_CUT) nLeadingEl++; 
    if (vec2.Pt()> MU_LEAD_PT_CUT) nLeadingMu++; 

    
    // EMU one isolated electron and 1 muon with pt > 10GeV
    emu = isIsoEle && isIsoMuo;
       
#ifdef TRGSTUDY
#else
#ifdef MC
#else
    if (isData){ //require trigger match
      bool ele_match = false; 
      bool muo_match = false; 
      bool emu_match = false; 
      bool match = false; 

      //use single trigger if any in plateau
      if (nLeadingEl>0) ele_match = triggerMatchE(vec1,&trig_EF_el_px,&trig_EF_el_py,&trig_EF_el_pz,&trig_EF_el_E,&triggerChain_e_single);
      if (nLeadingMu>0) muo_match = triggerMatchM(vec2, &triggerChain_mu_single, &trig_EF_trigmuonef_track_CB_eta, &trig_EF_trigmuonef_track_CB_phi);

      //otherwise use dilepton trigger
      if ((nLeadingEl==0) && (nLeadingMu==0) && (vec1.Pt()> 15000.)&& (vec2.Pt()> 10000.)){
        ele_match = triggerMatchE(vec1,&trig_EF_el_px,&trig_EF_el_py,&trig_EF_el_pz,&trig_EF_el_E,&triggerChain_e);
        muo_match = triggerMatchM(vec2, &triggerChain_mu, &trig_EF_trigmuonef_track_CB_eta, &trig_EF_trigmuonef_track_CB_phi);
        emu_match = ele_match && muo_match;      
      }
//use mainly egamma stream for emu      
#ifdef ELECTRON
    match = emu_match || ele_match;
#endif
//recover events from Muon stream
#ifdef MUON
    match = muo_match && (!ele_match);
#endif
            
      emu = isIsoEle && isIsoMuo && match;
    }
#endif

#endif
    
#ifdef TRGWEIGHT
    if (!isData){
    double LumiFrac_185353_186493 = m_tPileUp->GetIntegratedLumiFraction(runNumberPileUp,185353,186493);
    double LumiFrac_186516_186755 = m_tPileUp->GetIntegratedLumiFraction(runNumberPileUp,186516,186755); 
    double LumiFrac_186873_187815 = m_tPileUp->GetIntegratedLumiFraction(runNumberPileUp,186873,187815); 
    double triggerWeight = trgRWT->triggerReweightEMU(runNumberPileUp,vec1.Pt(), vec1.Eta(), vec2.Pt(), vec2.Eta(),vec2.Phi(),isCom[0],muo_ptcone20[0],
                                                      LumiFrac_185353_186493, LumiFrac_186516_186755, LumiFrac_186873_187815); 
    mc_evt_weight = mc_evt_weight*triggerWeight;  
     	    
    }
    
#endif
    
    if (emu) dileptonfile <<"EMU event nb: "<<eventNumber<<" run nb: "<<runNumber <<endl;

  } else return ; //no dilepton event
  
  #ifdef EVTWEIGHT
  mc_evt_weight *=myEventWeight;
  #endif

  //------------------------------------------------------------------------
    
  //                 Variables for signal region definitions

  // vec1 = TLorentzVector -- leading lepton
  // vec2 = TLorentzVector -- 2nd leading lepton
    
  //--------------------------------------------------------------------------//


// INVARIANT MASS

  float inv_mass = -1;
  inv_mass = ((vec1)+(vec2)).M();  
    
  if (inv_mass >= MLL_CUT) isMll = true;  // dilepton mass > 5 GeV  
    
  float MET_x = met.X();
  float MET_y = met.Y();
  MET = sqrt(MET_x*MET_x + MET_y*MET_y);    

  if (verbose)   cout <<"event nb: "<<eventNumber<<" run nb: "<<runNumber << "    mll: "<< inv_mass<<  "    MET: "<<MET<<endl;

// MEFF, MT MASS
  
  float htmiss = 0.;
  float m_eff = MET;
  float m_T = -1;  
  
  m_eff += vec1.Pt()+vec2.Pt(); //to calculate meff
  htmiss += vec1.Pt()+vec2.Pt(); //to calculate meff
  
  if (vec1.Pt() >= vec2.Pt()) m_T = sqrt(2.*MET*vec1.Pt()*(1. - cos(vec1.Phi()-met.Phi())));
  else m_T = sqrt(2.*MET*vec2.Pt()*(1. - cos(vec2.Phi()-met.Phi())));
    
  
// count jets

  int nSignalJets =  0;
  int nBJets =  0;

  // 3 leading jets for top tagger
  vector<TLorentzVector> finaljets;

//b-tagging weights
#ifdef BWEIGHT
  std::vector<float> pt_btag;
  std::vector<float> eta_btag;
  std::vector<float> val_btag;
  std::vector<int> pdgid_btag;
#endif
    
  if (n_jet)    
    for (unsigned int iJet = 0; iJet < n_jet; iJet++)   { 
      int index = getIndex("JET", jet_pt[iJet], jet_eta[iJet], jet_phi[iJet]);
      TLorentzVector vec = m_SUSYObjDef.m_jet[index];
      
      //signal jets  (already smeared)    
      if ((vec.Pt()>  JET_LEAD_PT_CUT)&&((fabs(vec.Eta()) < JET_LEAD_ETA_CUT))&&(jet_jvtxf[iJet]>0.75)) {
        nSignalJets++;
	jet_isSignal.push_back(1);
	// 3 leading jets for top tagger
	if (nSignalJets <= 3) finaljets.push_back(vec);
	//B jets
	if (m_SUSYObjDef.IsBJet(jet_flavor_weight_xxx[iJet], "JetFitterCOMBNN" , -1.25)) nBJets++;      

#ifdef BWEIGHT
        pt_btag.push_back(vec.Pt()); //NB: this is the smeared jet pT
        eta_btag.push_back(vec.Eta());
        val_btag.push_back(jet_flavor_weight_xxx[iJet]);
        pdgid_btag.push_back(jet_flavor_truth_label[iJet]);
#endif


      } else 
        jet_isSignal.push_back(0);
      //m_eff += jetpt;
      //htmiss += jetpt;
    }//end loop over jets

#ifdef BWEIGHT
  std::pair<float,vector<float> > wgtbtag;                                                                                                                                  
  std::pair<float,vector<float> > wgtbtagUp;                                                                                                                                  
  std::pair<float,vector<float> > wgtbtagDown;                                                                                                                                  
  //if(m_systematic=="bup"  ) bloop=1;                                                                                                                                        
  //if(m_systematic=="bdown") bloop=2;                                                                                                                                        
  wgtbtag =
  BTagCalib::BTagCalibrationFunction(pt_btag,eta_btag,val_btag,pdgid_btag,0,"JetFitterCOMBNN","-1_25",-1.25,path+"/SUSYTools/data/BTagCalibration.env",path+"/SUSYTools/data/");                                                 
  wgtbtagUp =
  BTagCalib::BTagCalibrationFunction(pt_btag,eta_btag,val_btag,pdgid_btag,1,"JetFitterCOMBNN","-1_25",-1.25,path+"/SUSYTools/data/BTagCalibration.env",path+"/SUSYTools/data/");                                                 
  wgtbtagDown =
  BTagCalib::BTagCalibrationFunction(pt_btag,eta_btag,val_btag,pdgid_btag,2,"JetFitterCOMBNN","-1_25",-1.25,path+"/SUSYTools/data/BTagCalibration.env",path+"/SUSYTools/data/");                                                 
  double bweightUp = wgtbtagUp.first;     
  double bweightDown = wgtbtagDown.first;     
  double bweight = wgtbtag.first;
#endif

  // Z veto
  bool ZVeto = false;
  if ((inv_mass<=101200.)&&(inv_mass>=81200.)) ZVeto = true;

// MET rel

  float METRel = 0.;
  float dPhiMin = 99999;
  float dPhi = 0.;

  if (n_jet)    
    for (unsigned int iJet = 0; iJet < n_jet; iJet++)   { //Loop through jets
      if (jet_isSignal[iJet]>0) {
        int index = getIndex("JET", jet_pt[iJet], jet_eta[iJet], jet_phi[iJet]);
        TLorentzVector vec = m_SUSYObjDef.m_jet[index];
        dPhi = fabs(TVector2::Phi_mpi_pi( met.Phi() - vec.Phi() ));
        if( dPhi < dPhiMin ) dPhiMin = dPhi;         
      }
    } //End looping through jets
  
  // check 2 leading leptons
  dPhi = fabs(TVector2::Phi_mpi_pi( met.Phi() - vec1.Phi()));
  if( dPhi < dPhiMin ) dPhiMin = dPhi;
  dPhi = fabs(TVector2::Phi_mpi_pi( met.Phi() - vec2.Phi()));
  if( dPhi < dPhiMin ) dPhiMin = dPhi;  

  if( dPhiMin > PI/2 ) METRel = MET;
  else METRel = MET * sin(dPhiMin);

// Mct top tag

  bool MCTVeto = false;
  int nsolutions = -1;
  nsolutions = toptag(30000., 100000., 3, vec1, vec2, finaljets, met);
  if(nsolutions>0) MCTVeto = true;

// deltaPhi
  float dPhill = fabs(TVector2::Phi_mpi_pi( met.Phi() - (vec2+vec1).Phi() ));  
  float dPhi2l = fabs(TVector2::Phi_mpi_pi( met.Phi() - vec2.Phi() ));    

// MT2
 
  double pa[3] = { vec1.M(), vec1.Px(), vec1.Py() };
  double pb[3] = { vec2.M(), vec2.Px(), vec2.Py() };
  double pmiss[3] = { 0, met.X(), met.Y() };
  double mn = 0.;
  mt2_bisect::mt2 mt2_event;
  mt2_event.set_momenta(pa,pb,pmiss);
  mt2_event.set_mn(mn);
  double mt2 = mt2_event.get_mt2();
    
  //------------------------------------------------------------------------
    
  //                 Fill ee, emu, mumu  
  
  //--------------------------------------------------------------------------//
#ifdef TRGSTUDY
    
  bool Zee = false;
  bool Zmumu = false;
  float dRMin = 0.15;
  
  if (ee && OS &&  ((inv_mass<=106000.)&&(inv_mass>=76000.))){
    if (deltaR(ele_eta[0], ele_phi[0], ele_eta[1], ele_phi[1])>1.0) Zee = true;      
  }
  
  if (mumu && OS &&  ((inv_mass<=106000.)&&(inv_mass>=76000.))){
    if (deltaR(muo_eta[0], muo_phi[0], muo_eta[1], muo_phi[1])>1.0) Zmumu = true;      
  }

  int index_probe_0 = -1;
  int index_probe_1 = -1;
 
  //  EE
    
  int EFindex0;
  int EFindex1;
  int nEFObject = m_sel->GetScalarVal<int>("trig_EF_el_n");
  std::vector<float> EFetaVector = m_sel->GetRawVector< std::vector<float> > ("trig_EF_el_eta"); 
  std::vector<float> EFphiVector = m_sel->GetRawVector< std::vector<float> > ("trig_EF_el_phi"); 
  std::vector<float> EFptVector = m_sel->GetRawVector< std::vector<float> > ("trig_EF_el_pt"); 

// EMU  -- add pt cuts and trigger matching?
#ifdef ACCEPTANCE  
  bin += 1;
  if (isMll && emu ) {
    trg_pt  = ele_pt[0]; // assume leading lepton
    trg_eta = ele_eta[0]; 
    trg_phi = ele_phi[0];
    //if ((ele_pt[0]>= 15000.)&& (muo_pt[0]>= 10000.)) 
      fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS); 
  }

  bin += 1;
  if (isMll && emu && trg_e_mu) {
    //if ((ele_pt[0]>= 15000.)&& (muo_pt[0]>= 10000.)) 
      fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS); 
  }

  bin += 1;
  if (isMll && emu && (trg_e_mu || trgEl)) {
    //if ((ele_pt[0]>= 15000.)&& (muo_pt[0]>= 10000.)) 
      fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS); 
  }

  bin += 1;
  if (isMll && emu && (trg_e_mu || trgMu )) {
    //if ((ele_pt[0]>= 15000.)&& (muo_pt[0]>= 10000.)) 
      fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS); 
  }

  bin += 1;
  if (isMll && emu && (trg_e_mu || trgMu || trgEl)) {
    //if ((ele_pt[0]>= 15000.)&& (muo_pt[0]>= 10000.)) 
      fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS); 
  }

  bin += 1;
  if (isMll && emu && (trgMu || trgEl)) {
    //if ((ele_pt[0]>= 15000.)&& (muo_pt[0]>= 10000.)) 
      fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS); 
  }
#endif  

#ifdef TAGPROBE
  bin += 1;

#ifdef MC  
  L1_el = "EF_e20_medium";
  L1_mu = "EF_mu18";
  trgEl = m_sel->GetScalarVal<int>("EF_e20_medium");
  trgMu = m_sel->GetScalarVal<int>("EF_mu18");
#endif

  if (Zee && trgEl){ //&& EF_e10_medium ??

    std::vector<int>EFdecision = m_sel->GetRawVector< std::vector<int> >("trig_EF_el_"+L1_el);       
    trg0 = PassedTriggerEF(ele_tracketa[0], ele_trackphi[0], &EFdecision, EFindex0, nEFObject, &EFetaVector, &EFphiVector);
    trg1 = PassedTriggerEF(ele_tracketa[1], ele_trackphi[1], &EFdecision, EFindex1, nEFObject, &EFetaVector, &EFphiVector);
    
//    cout <<endl<< "Looking for tag"<<endl;
//    cout <<eventNumber << " EE trg0 "<<trg0<< " pt "<<ele_pt[0]<<endl;
//    cout <<eventNumber << " EE trg1 "<<trg1<< " pt "<<ele_pt[1]<<endl;
    
    if (trg0 && (ele_pt[0] > 25000.)) {          // Tag 0   
      index_probe_1 = 1;                         // Probe 1
      trg_pt  = ele_pt[1]; 
      trg_eta = ele_eta[1];
      trg_phi = ele_phi[1];
//      cout <<eventNumber << " EE Tag 0"<<endl;
      fill_histo(mc_evt_weight, bin); 
    }  

    if (trg1 && (ele_pt[1] > 25000.)) {          // Tag 1 
      index_probe_0 = 1;                         // Probe 0
      trg_pt  = ele_pt[0]; 
      trg_eta = ele_eta[0];
      trg_phi = ele_phi[0];
//      cout <<eventNumber << " EE Tag 1"<<endl;
      fill_histo(mc_evt_weight, bin); 
    }
    
    if ((index_probe_0>=0)||((index_probe_1>=0))) {
      fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS); 
    }  
  }   

  bin += 1;
  bool trg = false;
  
  // Tag 0, probe 1
  if ((index_probe_1>=0) && Zee){
      std::vector<int>EFdecision = m_sel->GetRawVector< std::vector<int> >("trig_EF_el_EF_e10_medium");       
      trg1 = PassedTriggerEF(ele_tracketa[1], ele_trackphi[1], &EFdecision, EFindex1, nEFObject, &EFetaVector, &EFphiVector);
      if (trg1) {
        trg = true;
        trg_pt  = ele_pt[1]; 
        trg_eta = ele_eta[1];
        trg_phi = ele_phi[1];
        fill_histo(mc_evt_weight, bin); 
//        cout <<eventNumber << " EE Probe 1"<<endl;
      }
    }

  // Tag 1, probe 0
  if ((index_probe_0>=0) && Zee){
      std::vector<int>EFdecision = m_sel->GetRawVector< std::vector<int> >("trig_EF_el_EF_e10_medium");       
      trg0 = PassedTriggerEF(ele_tracketa[0], ele_trackphi[0], &EFdecision, EFindex0, nEFObject, &EFetaVector, &EFphiVector);
      if (trg0) {
        trg = true;
        trg_pt  = ele_pt[0]; 
        trg_eta = ele_eta[0];
        trg_phi = ele_phi[0];
        fill_histo(mc_evt_weight, bin); 
//        cout <<eventNumber << " EE Probe 0"<<endl;
      }
    }
      
    if (trg) fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS); 	                  
  

  //  MUMU

  //calculate Mu trigger with trigger matching     
  int trig_EF_trigmuonef_n = m_sel->GetScalarVal<int>("trig_EF_trigmuonef_n");    
  std::vector<int>trig_EF_trigmuonef_track_n = m_sel->GetRawVector< std::vector<int> >("trig_EF_trigmuonef_track_n"); 
   
  std::vector< std::vector<float> > trig_EF_trigmuonef_track_CB_pt = m_sel->GetRawVector< std::vector< std::vector<float> > >("trig_EF_trigmuonef_track_CB_pt" );
  std::vector< std::vector<float> > trig_EF_trigmuonef_track_CB_eta = m_sel->GetRawVector< std::vector< std::vector<float> > >("trig_EF_trigmuonef_track_CB_eta" );
  std::vector< std::vector<float> > trig_EF_trigmuonef_track_CB_phi = m_sel->GetRawVector< std::vector< std::vector<float> > >("trig_EF_trigmuonef_track_CB_phi" );
  std::vector< std::vector<int> > trig_EF_trigmuonef_track_CB_hasCB = m_sel->GetRawVector< std::vector< std::vector<int> > >("trig_EF_trigmuonef_track_CB_hasCB" );
    
  //calculate Mu trigger with trigger matching at L2    
  int trig_L2_n = m_sel->GetScalarVal<int>("trig_L2_combmuonfeature_n");    
  std::vector<float> trig_L2_pt  = m_sel->GetRawVector< std::vector<float> >("trig_L2_combmuonfeature_pt" );
  std::vector<float> trig_L2_eta = m_sel->GetRawVector< std::vector<float> >("trig_L2_combmuonfeature_eta" );
  std::vector<float> trig_L2_phi = m_sel->GetRawVector< std::vector<float> >("trig_L2_combmuonfeature_phi" );

  bin += 1;
  index_probe_0 = -1;
  index_probe_1 = -1;
  trg1 = false;
  trg0 = false;
  
  if (Zmumu && trgMu){
     
    float trg0_dR = MuonHasTriggerMatch("trigmuonef_"+L1_mu, 0.15, trig_EF_trigmuonef_n, &trig_EF_trigmuonef_track_n, muo_pt[0], muo_eta[0], muo_phi[0], 
      &trig_EF_trigmuonef_track_CB_pt, &trig_EF_trigmuonef_track_CB_eta, &trig_EF_trigmuonef_track_CB_phi, &trig_EF_trigmuonef_track_CB_hasCB);

    float trg1_dR = MuonHasTriggerMatch("trigmuonef_"+L1_mu, 0.15, trig_EF_trigmuonef_n, &trig_EF_trigmuonef_track_n, muo_pt[1], muo_eta[1], muo_phi[1], 
      &trig_EF_trigmuonef_track_CB_pt, &trig_EF_trigmuonef_track_CB_eta, &trig_EF_trigmuonef_track_CB_phi, &trig_EF_trigmuonef_track_CB_hasCB);

    float trg0_float = trg0_dR; // -1 if no match was found
    float trg1_float = trg1_dR; // -1 if no match was found
        
    if ((trg0_dR < dRMin) && (trg0_dR>=0.)) {
      trg0 = true;
      trg0_float = 1.;    
    }  else    
      trg0_float = 0.;  
    if ((trg1_dR < dRMin) && (trg1_dR>=0.)) {
      trg1 = true;
      trg1_float = 1.;    
    }  else    
      trg1_float = 0.;  

    h_trg1	  ->Fill(trg0_float,      mc_evt_weight); 
    h_trg1_dR	  ->Fill(trg0_dR,         mc_evt_weight); 
    h_trg2	  ->Fill(trg1_float,      mc_evt_weight);
    h_trg2_dR	  ->Fill(trg1_dR,    mc_evt_weight); 

    if (trg0 && (muo_pt[0] > 20000.)) {          // Tag 0   
      index_probe_1 = 1;                         // Probe 1
      trg_pt  = muo_pt[1]; 
      trg_eta = muo_eta[1];
      trg_phi = muo_phi[1];
      //cout <<eventNumber << " MUMU Tag 0"<<endl;
      fill_histo(mc_evt_weight, bin); 
    }  

    if (trg1 && (muo_pt[1] > 20000.)) {          // Tag 1 
      index_probe_0 = 1;                         // Probe 0
      trg_pt  = muo_pt[0]; 
      trg_eta = muo_eta[0];
      trg_phi = muo_phi[0];
      //cout <<eventNumber << " MUMU Tag 1"<<endl;
      fill_histo(mc_evt_weight, bin); 
    }
    
    if ((index_probe_0>=0)||((index_probe_1>=0))) {
      fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS); 

    }        
  }  

  bin += 1;
  trg = false;
  
  // Tag 0, probe 1
  if ((index_probe_1>=0) && Zmumu && isResurrected){ /// ask for EF_mu6 which should be resurrected
      float trg_dR = MuonHasTriggerMatch("trigmuonef_EF_mu6", 0.15, trig_EF_trigmuonef_n, &trig_EF_trigmuonef_track_n, muo_pt[1], muo_eta[1], muo_phi[1], 
        &trig_EF_trigmuonef_track_CB_pt, &trig_EF_trigmuonef_track_CB_eta, &trig_EF_trigmuonef_track_CB_phi, &trig_EF_trigmuonef_track_CB_hasCB);
      //float trg_dR = MuonHasTriggerMatch_EFmu6(trig_EF_trigmuonef_n, &trig_EF_trigmuonef_track_n, muo_pt[1], muo_eta[1], muo_phi[1], 
      //  &trig_EF_trigmuonef_track_CB_pt, &trig_EF_trigmuonef_track_CB_eta, &trig_EF_trigmuonef_track_CB_phi, &trig_EF_trigmuonef_track_CB_hasCB);
      
      bool L1L2 = MuonHasL1L2TriggerMatch(6000., 0.15, trig_L2_n, muo_pt[1], muo_eta[1], muo_phi[1], &trig_L2_pt, &trig_L2_eta, &trig_L2_phi);
	
      if ((trg_dR < dRMin)  && (trg_dR >= 0.) ) {
        trg = true;
	trg1 = true; 
        trg_pt  = muo_pt[1]; 
        trg_eta = muo_eta[1];
        trg_phi = muo_phi[1];
        fill_histo(mc_evt_weight, bin); 
        //cout <<eventNumber << " MUMU Probe 1"<<endl;
      }
    }

  // Tag 1, probe 0
  if ((index_probe_0>=0) && Zmumu && isResurrected){
      float trg_dR = MuonHasTriggerMatch("trigmuonef_EF_mu6", 0.15, trig_EF_trigmuonef_n, &trig_EF_trigmuonef_track_n, muo_pt[0], muo_eta[0], muo_phi[0], 
        &trig_EF_trigmuonef_track_CB_pt, &trig_EF_trigmuonef_track_CB_eta, &trig_EF_trigmuonef_track_CB_phi, &trig_EF_trigmuonef_track_CB_hasCB);
      //float trg_dR = MuonHasTriggerMatch_EFmu6(trig_EF_trigmuonef_n, &trig_EF_trigmuonef_track_n, muo_pt[0], muo_eta[0], muo_phi[0], 
        //&trig_EF_trigmuonef_track_CB_pt, &trig_EF_trigmuonef_track_CB_eta, &trig_EF_trigmuonef_track_CB_phi, &trig_EF_trigmuonef_track_CB_hasCB);
      bool L1L2 = MuonHasL1L2TriggerMatch(6000., 0.15, trig_L2_n, muo_pt[0], muo_eta[0], muo_phi[0], &trig_L2_pt, &trig_L2_eta, &trig_L2_phi);
      
      if ((trg_dR < dRMin)  && (trg_dR >= 0.)) {
        trg = true;
	trg0 = true; 
        trg_pt  = muo_pt[0]; 
        trg_eta = muo_eta[0];
        trg_phi = muo_phi[0];
        fill_histo(mc_evt_weight, bin); 
        //cout <<eventNumber << " MUMU Probe 0"<<endl;
      }
    }
  
  if ((index_probe_0>=0)||((index_probe_1>=0))) {
      // from twiki ??TrigDefs::allowResurrectedDecision|TrigDefs::requireDecision|TrigDefs::enforceLogicalFlow
      int L1mu6 = m_sel->GetScalarVal<int>("L1_MU6");
      int L2mu6 = m_sel->GetScalarVal<int>("L2_mu6");
      
      cout << "Entry "<<entry<<" passed "<<isPassed<<" from D3PD "<< EF_mu6<< " L1 "<<L1mu6<< " L2 "<<L2mu6<<" isResurrected "<<isResurrected 
      <<" passedThrough "<< passedThrough<<" requireDecision "<< requireDecision;
      
      if (index_probe_0>=0) cout << " probe0 "<< trg0 ;
      if (index_probe_1>=0) cout << " probe1 "<< trg1 ;
      
      cout <<endl;
  }
  if (trg) fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS); 	                  

//bootstrap for electon

  bin += 1;
  trg = false;
  
  //well separated
  if (emu && isMll){
    if (deltaR(muo_eta[0], muo_phi[0], ele_eta[0], ele_phi[0])>0.5) {
      emu = true;      
    }   	 
  }

  if (isMll && emu){ 
      //match first EF_mu6
      float trg_dR = MuonHasTriggerMatch("trigmuonef_EF_mu6", 0.15, trig_EF_trigmuonef_n, &trig_EF_trigmuonef_track_n, muo_pt[0], muo_eta[0], muo_phi[0], 
      &trig_EF_trigmuonef_track_CB_pt, &trig_EF_trigmuonef_track_CB_eta, &trig_EF_trigmuonef_track_CB_phi, &trig_EF_trigmuonef_track_CB_hasCB);
      
      if ((trg_dR < dRMin)  && (trg_dR >= 0.)&&(muo_pt[0]>=10000.)) {
        trg = true;
        trg_pt  = ele_pt[0]; 
        trg_eta = ele_eta[0];
        trg_phi = ele_phi[0];
        fill_histo(mc_evt_weight, bin);
        fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS); 	                  
      }   	 
  }

  bin += 1;

  if (trg &&isMll && emu){ 
      //match to EF_e10_medium
      std::vector<int>EFdecision = m_sel->GetRawVector< std::vector<int> >("trig_EF_el_EF_e10_medium");       
      trg = PassedTriggerEF(ele_tracketa[0], ele_trackphi[0], &EFdecision, EFindex0, nEFObject, &EFetaVector, &EFphiVector);
      if (trg) {
         fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS); 	                  
         fill_histo(mc_evt_weight, bin);
      }   	 
  }  

//bootstrap for muon

  bin += 1;
  trg = false;

  if (isMll && emu){ 
      //match first EF_e10_medium
      std::vector<int>EFdecision = m_sel->GetRawVector< std::vector<int> >("trig_EF_el_EF_e10_medium");       
      trg = PassedTriggerEF(ele_tracketa[0], ele_trackphi[0], &EFdecision, EFindex0, nEFObject, &EFetaVector, &EFphiVector);
      if (trg && (ele_pt[0]>=15000.)) {
        trg=true;
        trg_pt  = muo_pt[0]; 
        trg_eta = muo_eta[0];
        trg_phi = muo_phi[0];
        fill_histo(mc_evt_weight, bin);
        fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS); 	                  
      } else {trg = false;}   	 
  }

  bin += 1;

  if (trg &&isMll && emu){ 
      //match to EF_mu6
      float trg_dR = MuonHasTriggerMatch("trigmuonef_EF_mu6", 0.15, trig_EF_trigmuonef_n, &trig_EF_trigmuonef_track_n, muo_pt[0], muo_eta[0], muo_phi[0], 
      &trig_EF_trigmuonef_track_CB_pt, &trig_EF_trigmuonef_track_CB_eta, &trig_EF_trigmuonef_track_CB_phi, &trig_EF_trigmuonef_track_CB_hasCB);
      
      if ((trg)&&(trg_dR < dRMin)  && (trg_dR >= 0.)) {
         fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS); 	                  
         fill_histo(mc_evt_weight, bin);
      }   	 
  }  
   
#endif 

#else


  // ----------------------------------------------------------------------
  // --------------             ee / mumu                     -------------
  // ----------------------------------------------------------------------

#ifdef MUON
  ee = mumu; //switch for muon stream
#endif

  
  bin += 1;
  if ( ee ) {
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);      
  }

  // ee && Mll
  bin += 1;
  if (isMll && ee ) {
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);      
  }

  // ee && Mll && OS cut
  bin += 1;
  if (isMll &&ee && OS) 
  {
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
  }

  // ----------------------------------------------------------------------
  // --------------             ee SR1                    -----------------
  // ----------------------------------------------------------------------
      
  // ee && Mll && OS cut && Jet Veto 
  bin += 1;
  if (isMll &&ee  && OS && (nSignalJets == 0.)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   

  // ee && Mll && OS cut && Jet Veto && Z veto 
  bin += 1;
  if (isMll &&ee  && OS && (nSignalJets == 0.) && (ZVeto == false)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);
 }   

  // ee && Mll && OS cut && Jet Veto && Z veto && METRel > 100 GeV
  bin += 1;
  if (isMll &&ee  && OS && (nSignalJets == 0.) && (ZVeto == false) && (METRel > 100000.)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   
 
  // ----------------------------------------------------------------------
  // --------------             ee SR3                    -----------------
  // ----------------------------------------------------------------------

  // ee && Mll && OS cut && Jet >= 2 
  bin += 1;
  if (isMll &&ee  && OS && (nSignalJets >= 2.)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   

  // ee && Mll && OS cut && Jet >= 2 && Z veto 
  bin += 1;
  if (isMll &&ee  && OS && (nSignalJets >= 2.) && (ZVeto == false)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   

  // ee && Mll && OS cut && Jet >= 2 && Z veto && Bjet veto
  bin += 1;
  if (isMll &&ee  && OS && (nSignalJets >= 2.) && (ZVeto == false) && (nBJets == 0.)) {  
#ifdef BWEIGHT
    //cout << bweight<< " "<< bweightUp<< " "<<bweightDown <<endl;
    fill_histo(mc_evt_weight*bweight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
#else
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
#endif
 }   

  // ee && Mll && OS cut && Jet >= 2 && Z veto && MCTVeto && Bjet veto
  bin += 1;
  if (isMll &&ee  && OS && (nSignalJets >= 2.) && (ZVeto == false) && (nBJets == 0.) && (MCTVeto == false)) {  
#ifdef BWEIGHT
    fill_histo(mc_evt_weight*bweight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
#else
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
#endif
    //cout << eventNumber << " met after MCTVeto "<< MET << " rel "<< METRel << endl;   
 }   
   
  // ee && Mll && OS cut && Jet >= 2 && Z veto && MCTVeto && Bjet veto && MetRel>50GeV
  bin += 1;
  if (isMll &&ee  && OS && (nSignalJets >= 2.) && (ZVeto == false) && (nBJets == 0.) && (MCTVeto == false) && (METRel > 50000.)) {  
#ifdef BWEIGHT
    fill_histo(mc_evt_weight*bweight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
#else
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
#endif
    //cout << eventNumber << " met "<< MET << " rel "<< METRel << endl;   
 }   

  // ----------------------------------------------------------------------
  // --------------             ee SR4                    -----------------
  // ----------------------------------------------------------------------

  // ee && Mll && OS cut && Jet Veto && Z veto && METRel > 40 GeV
  bin += 1;
  if (isMll &&ee  && OS && (nSignalJets == 0.) && (ZVeto == false) && (METRel > 40000.)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   
  
  // ee && Mll && OS cut && Jet Veto && Z veto && METRel > 40 GeV && Pt(l1) > 50 GeV
  bin += 1;
  if (isMll &&ee  && OS && (nSignalJets == 0.) && (ZVeto == false) && (METRel > 40000.) && (vec1.Pt() > 50000.)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   

  // ee && Mll && OS cut && Jet Veto && Z veto && METRel > 40 GeV && Pt(l1) > 50 GeV && Pt(l1+l2) > 100 GeV 
  bin += 1;
  if (isMll &&ee  && OS && (nSignalJets == 0.) && (ZVeto == false) && (METRel > 40000.) && (vec1.Pt() > 50000.)
      && ((vec1.Pt() +vec2.Pt())> 100000.)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   

  // ee && Mll && OS cut && Jet Veto && Z veto && METRel > 40 GeV && Pt(l1) > 50 GeV && Pt(l1+l2) > 100 GeV 
  bin += 1;
  if (isMll &&ee  && OS && (nSignalJets == 0.) && (ZVeto == false) && (METRel > 40000.) && (vec1.Pt() > 50000.)
      && ((vec1.Pt() +vec2.Pt())> 100000.) && (dPhill > 2.5)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   

  // ee && Mll && OS cut && Jet Veto && Z veto && METRel > 40 GeV && Pt(l1) > 50 GeV && Pt(l1+l2) > 100 GeV 
  bin += 1;
  if (isMll &&ee  && OS && (nSignalJets == 0.) && (ZVeto == false) && (METRel > 40000.) && (vec1.Pt() > 50000.)
      && ((vec1.Pt() +vec2.Pt())> 100000.) && (dPhill > 2.5) && (dPhi2l > 0.5)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   

  // ----------------------------------------------------------------------
  // --------------             ee SR5                    -----------------
  // ----------------------------------------------------------------------
  
  // ee && Mll && OS cut && Jet Veto && Z veto && METRel > 40 GeV && mt2 > 90 GeV
  bin += 1;
  if (isMll &&ee  && OS && (nSignalJets == 0.) && (ZVeto == false) && (METRel > 40000.) && (mt2 > 90000.)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   
  
  // ----------------------------------------------------------------------
  // --------------             ee SS SR2                    --------------
  // ----------------------------------------------------------------------

  // ee && Mll && SS cut
  bin += 1;
  if (isMll &&ee && (!OS)) 
  {
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
  }
  
  // ee && Mll && SS cut && Jet Veto 
  bin += 1;
  if (isMll &&ee  && (!OS) && (nSignalJets == 0.)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   

  // ee && Mll && SS cut && Jet Veto && METRel > 100 GeV 
  bin += 1;
  if (isMll &&ee  && (!OS) && (nSignalJets == 0.) && (METRel > 100000.)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   
  
  // ----------------------------------------------------------------------
  // --------------             emu                          --------------
  // ----------------------------------------------------------------------
      
  //  emu cut 
  bin += 1;
  if ( emu ) {
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);      
  }

  // emu && Mll
  bin += 1;
  if (isMll && emu ) {
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);      
  }

  // ee && Mll && OS cut
  bin += 1;
  if (isMll &&emu && OS) 
  {
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
  }

  // ----------------------------------------------------------------------
  // --------------             emu SR1                    -----------------
  // ----------------------------------------------------------------------
      
  // emu && Mll && OS cut && Jet Veto 
  bin += 1;
  if (isMll &&emu  && OS && (nSignalJets == 0.)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   

  // emu && Mll && OS cut && Jet Veto && Z veto 
  bin += 1;
  if (isMll &&emu  && OS && (nSignalJets == 0.) && (ZVeto == false)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);
 }   

  // emu && Mll && OS cut && Jet Veto && Z veto && METRel > 100 GeV
  bin += 1;
  if (isMll &&emu  && OS && (nSignalJets == 0.) && (ZVeto == false) && (METRel > 100000.)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   

  // ----------------------------------------------------------------------
  // --------------             emu SS SR2                    --------------
  // ----------------------------------------------------------------------

  // emu && Mll && SS cut
  bin += 1;
  if (isMll &&emu && (!OS)) 
  {
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
  }
  
  // ee && Mll && SS cut && Jet Veto 
  bin += 1;
  if (isMll &&emu  && (!OS) && (nSignalJets == 0.)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   

  // ee && Mll && SS cut && Jet Veto && METRel > 40 GeV 
  bin += 1;
  if (isMll &&emu  && (!OS) && (nSignalJets == 0.) && (METRel > 40000.)) {  
    fill_histo(mc_evt_weight, bin, MET, inv_mass, m_eff, m_T, htmiss, isOS);  
 }   
 
#endif

 // The END
 return;
}


void MyAnalysis::finalizeEvent(Long64_t entry)
{
  (void)entry;
  return;

}


/*static*/ void MyAnalysis::postAnalysis (TSelectorList* fOutput)
{
  // (void)fOutput; //avoid compiler warnings
 
  //This METhod is declared as static in the header file
  //Why?
  //This comes from the fact that PROOF calls the METhod Terminate (which then calls this METhod) on the master thread.
  //However, when running PROOF, the code above usually runs in Slave Threads. 
  //The master thread (which is running when the computer gets here), doesn't have acces to the member variables in the slave threads.
  
  //All you can do here is get Objects from fOutput-List and Draw them or save them to a file


  TString filename = "result";

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
#ifdef TRGSTUDY
  filename = "trigger";
#endif

  TH1D *cutflow = (TH1D*)fOutput->FindObject("cutflow_histo")->Clone();
  TH1D *runNumber = (TH1D*)fOutput->FindObject("runNumber_histo")->Clone();
 
  TH1F *trg1_histo        = (TH1F*)fOutput->FindObject("h_trg1")->Clone();
  TH1F *trg2_histo        = (TH1F*)fOutput->FindObject("h_trg2")->Clone();
  TH1F *trg1_dR_histo     = (TH1F*)fOutput->FindObject("h_trg1_dR")->Clone();
  TH1F *trg2_dR_histo     = (TH1F*)fOutput->FindObject("h_trg2_dR")->Clone();
  TH1F *trg1_d3pd_histo   = (TH1F*)fOutput->FindObject("h_trg1_d3pd")->Clone();
  TH1F *trg2_d3pd_histo   = (TH1F*)fOutput->FindObject("h_trg2_d3pd")->Clone();
  TH1F *trg1_d3pd_dR_histo= (TH1F*)fOutput->FindObject("h_trg1_d3pd_dR")->Clone();
  TH1F *trg2_d3pd_dR_histo= (TH1F*)fOutput->FindObject("h_trg2_d3pd_dR")->Clone();
  TH1F *trg1_deltaR_histo = (TH1F*)fOutput->FindObject("h_trg1_deltaR")->Clone();
  TH1F *trg2_deltaR_histo = (TH1F*)fOutput->FindObject("h_trg2_deltaR")->Clone();
  
  TH2F* cutflow_susy      = (TH2F*)fOutput->FindObject("h_cutflow_susy")->Clone();
  
  TH2F* e_nb_histo        = (TH2F*)fOutput->FindObject("h_e_nb")->Clone();
   
  TH2F* e_eta_histo       = (TH2F*)fOutput->FindObject("h_e_eta")->Clone();
  TH2F* e_pt_histo        = (TH2F*)fOutput->FindObject("h_e_pt")->Clone();
  TH2F* e_phi_histo       = (TH2F*)fOutput->FindObject("h_e_phi")->Clone();
  TH2F* e_ptcone20_histo  = (TH2F*)fOutput->FindObject("h_e_ptcone20")->Clone();
  TH2F* e_charge_histo    = (TH2F*)fOutput->FindObject("h_e_charge")->Clone();
  TH2F* el_eta_histo	  = (TH2F*)fOutput->FindObject("h_el_eta")->Clone();
  TH2F* el_phi_histo	  = (TH2F*)fOutput->FindObject("h_el_phi")->Clone();
  TH2F* el_pt_histo	  = (TH2F*)fOutput->FindObject("h_el_pt")->Clone();
  TH2F* e2l_eta_histo	  = (TH2F*)fOutput->FindObject("h_e2l_eta")->Clone();
  TH2F* e2l_phi_histo	  = (TH2F*)fOutput->FindObject("h_e2l_phi")->Clone();
  TH2F* e2l_pt_histo	  = (TH2F*)fOutput->FindObject("h_e2l_pt")->Clone();
  TH2F* el_trg_eta_histo  = (TH2F*)fOutput->FindObject("h_el_trg_eta")->Clone();
  TH2F* el_trg_phi_histo  = (TH2F*)fOutput->FindObject("h_el_trg_phi")->Clone();
  TH2F* el_trg_pt_histo	  = (TH2F*)fOutput->FindObject("h_el_trg_pt")->Clone();
   
  TH2F* mu_nb_histo       = (TH2F*)fOutput->FindObject("h_mu_nb")->Clone();
  TH2F* mu_eta_histo      = (TH2F*)fOutput->FindObject("h_mu_eta")->Clone();
  TH2F* mu_pt_histo       = (TH2F*)fOutput->FindObject("h_mu_pt")->Clone();
  TH2F* mu_phi_histo      = (TH2F*)fOutput->FindObject("h_mu_phi")->Clone();
  TH2F* mu_ptcone20_histo = (TH2F*)fOutput->FindObject("h_mu_ptcone20")->Clone();
  TH2F* mu_charge_histo   = (TH2F*)fOutput->FindObject("h_mu_charge")->Clone();
  TH2F* mul_eta_histo	  = (TH2F*)fOutput->FindObject("h_mul_eta")->Clone();
  TH2F* mul_phi_histo	  = (TH2F*)fOutput->FindObject("h_mul_phi")->Clone();
  TH2F* mul_pt_histo	  = (TH2F*)fOutput->FindObject("h_mul_pt")->Clone();
  TH2F* mu2l_eta_histo    = (TH2F*)fOutput->FindObject("h_mu2l_eta")->Clone();
  TH2F* mu2l_phi_histo    = (TH2F*)fOutput->FindObject("h_mu2l_phi")->Clone();
  TH2F* mu2l_pt_histo	  = (TH2F*)fOutput->FindObject("h_mu2l_pt")->Clone();
  TH2F* mu_trg_eta_histo  = (TH2F*)fOutput->FindObject("h_mu_trg_eta")->Clone();
  TH2F* mu_trg_phi_histo  = (TH2F*)fOutput->FindObject("h_mu_trg_phi")->Clone();
  TH2F* mu_trg_pt_histo	  = (TH2F*)fOutput->FindObject("h_mu_trg_pt")->Clone();
  TH2F* mu_trg_eta_barrel_histo = (TH2F*)fOutput->FindObject("h_mu_trg_eta_barrel")->Clone();
  TH2F* mu_trg_phi_barrel_histo = (TH2F*)fOutput->FindObject("h_mu_trg_phi_barrel")->Clone();
  TH2F* mu_trg_pt_barrel_histo	= (TH2F*)fOutput->FindObject("h_mu_trg_pt_barrel")->Clone();
  TH2F* mu_trg_eta_endcap_histo = (TH2F*)fOutput->FindObject("h_mu_trg_eta_endcap")->Clone();
  TH2F* mu_trg_phi_endcap_histo = (TH2F*)fOutput->FindObject("h_mu_trg_phi_endcap")->Clone();
  TH2F* mu_trg_pt_endcap_histo	= (TH2F*)fOutput->FindObject("h_mu_trg_pt_endcap")->Clone();

  TH3F* mu_trg_eta_phi_histo = (TH3F*)fOutput->FindObject("h_mu_trg_eta_phi")->Clone();
  TH3F* el_trg_eta_phi_histo = (TH3F*)fOutput->FindObject("h_el_trg_eta_phi")->Clone();
  TH3F* mu_trg_pt_eta_histo  = (TH3F*)fOutput->FindObject("h_mu_trg_pt_eta")->Clone();
  TH3F* el_trg_pt_eta_histo  = (TH3F*)fOutput->FindObject("h_el_trg_pt_eta")->Clone();

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
   
  float Nevents = (float)(runNumber ->Integral());
  std::cout << "Events after pileup reweight "<<Nevents << std::endl;
 
  filename += (TString)runNb;
  
  //int n_events =cutflow->GetBinContent(1);
  //std::cout << "Final Cutflow after "<<n_events<<" events for two lepton selection "  << std::endl;
  
  //electron stream
  #ifdef ELECTRON
  filename += "_electronStream";
  #endif
  #ifdef MUON
  filename += "_muonStream";
  #endif


// Opening files
  #ifdef GRID 
  cout << "Grid/local run"<<endl;
  TString filename_txt = path + "/"+filename +".txt";     
//  filename= path + "/"+filename ;
  filename= path + "/histos" ;

  #else
  cout << "PROOF run"<<endl;

  #ifdef SYST
  cout << "SYST "<< SYST <<endl;
  TString filename_txt = path + "/"+SYST+"_txt/"+filename +".txt";     
  filename= path + "/"+SYST+"_root/"+filename ;  	 
  #else
  TString filename_txt = path + "/txt/"+filename +".txt";     
  filename= path + "/root/"+filename ;  	 
  #endif

  #endif

//root file
  TFile* Target = new TFile( filename+".root", "RECREATE");
  cout << "Writing output to "<<filename<<".root,txt"<<endl;

//txt file
  const char* name_txtfile=filename_txt.Data(); 
  
  //cout << "Opening txt file "<<name_txtfile<<endl;
  myfile.open(name_txtfile);
  
  if (isData) {
    cout << "DATA"<<endl;
  }  else cout << "MC "<<endl;
  #ifdef ELECTRON 
  cout << "Egamma stream "<<L1_el<<endl;
  #endif
  #ifdef MUON 
  cout << "Muon stream "<<L1_mu<<endl;
  #endif
  
  cout << "ELECTRON leading pt cut " << EL_LEAD_PT_CUT<< " pt cut " << EL_PT_CUT<<" eta cut " <<EL_ETA_CUT<<endl; 
  cout << "MUON     leading pt cut " << MU_LEAD_PT_CUT<< " pt cut " << MU_PT_CUT<<" eta cut " <<MU_ETA_CUT<<endl; 
  cout << "JET      signal pt cut " <<JET_LEAD_PT_CUT<< " pt cut " <<JET_PT_CUT<<" eta cut " <<JET_ETA_CUT<<" signal eta cut " <<JET_LEAD_ETA_CUT<<endl; 
  cout << "MLL cut " <<MLL_CUT<<endl; 
  
  myfile << "Final Cutflow for run "<<run  << std::endl;
  std::cout << "Final Cutflow for run "<<run  << std::endl;
  
  #ifdef ELECTRON
  myfile << "Electron stream "<< std::endl ;
  #endif
  #ifdef MUON
  myfile << "Muon stream "<< std::endl ;
  #endif
    
  unsigned int size = sizeof name_cutflow / sizeof *name_cutflow;
  //cout << "size "<<  size << endl;
  
  for (unsigned int cf = 0; cf < size; cf++)  {
    Double_t nbin_content =cutflow->GetBinContent(cf+1);
    std::cout << "Cut " << cf <<" : " <<  (nbin_content)<<"		  "<< name_cutflow[cf]<<std::endl;
    myfile    << "Cut " << cf <<" : " <<  (nbin_content)<<"		  "<< name_cutflow[cf]<<std::endl; 
  }

  if (ndrellyan>0.)
    cout << "drellyan efficiency "<< 1.*ndrellyanNOT/ndrellyan<<endl;

  cutflow->Write();
  cutflow_susy->Write();
  runNumber->Write();
  
  trg1_histo->Write();        
  trg2_histo->Write();        
  trg1_dR_histo->Write();     
  trg2_dR_histo->Write();     
  trg1_d3pd_histo->Write();   
  trg2_d3pd_histo ->Write();  
  trg1_d3pd_dR_histo->Write();
  trg2_d3pd_dR_histo->Write();
  trg1_deltaR_histo->Write(); 
  trg2_deltaR_histo->Write();  
  
  e_nb_histo->Write();       
  e_eta_histo->Write();      
  e_pt_histo ->Write();      
  e_phi_histo->Write();      
  e_ptcone20_histo->Write(); 
  e_charge_histo->Write();
  el_eta_histo ->Write();
  el_phi_histo ->Write();
  el_pt_histo  ->Write();
  e2l_eta_histo ->Write();
  e2l_phi_histo ->Write();
  e2l_pt_histo  ->Write();
  el_trg_eta_histo ->Write();
  el_trg_phi_histo ->Write();
  el_trg_pt_histo  ->Write();
  el_trg_eta_phi_histo ->Write();
  el_trg_pt_eta_histo ->Write();

  mu_nb_histo ->Write();     
  mu_eta_histo ->Write();    
  mu_pt_histo ->Write();     
  mu_phi_histo ->Write();    
  mu_ptcone20_histo->Write();
  mu_charge_histo->Write();
  mul_eta_histo ->Write();
  mul_phi_histo ->Write();
  mul_pt_histo  ->Write();
  mu2l_eta_histo ->Write();
  mu2l_phi_histo ->Write();
  mu2l_pt_histo  ->Write();
  mu_trg_eta_histo ->Write();
  mu_trg_phi_histo ->Write();
  mu_trg_pt_histo  ->Write();
  mu_trg_eta_barrel_histo ->Write();
  mu_trg_phi_barrel_histo ->Write();
  mu_trg_pt_barrel_histo  ->Write();
  mu_trg_eta_endcap_histo ->Write();
  mu_trg_phi_endcap_histo ->Write();
  mu_trg_pt_endcap_histo  ->Write();
  mu_trg_eta_phi_histo ->Write();
  mu_trg_pt_eta_histo ->Write();

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

  delete trg1_histo;        
  delete trg2_histo;        
  delete trg1_dR_histo;     
  delete trg2_dR_histo;     
  delete trg1_d3pd_histo;   
  delete trg2_d3pd_histo;   
  delete trg1_d3pd_dR_histo;
  delete trg2_d3pd_dR_histo;
  delete trg1_deltaR_histo; 
  delete trg2_deltaR_histo;  
  delete cutflow;
  delete cutflow_susy;
  delete runNumber;
  delete e_nb_histo;      
  delete e_eta_histo;      
  delete e_pt_histo;       
  delete e_phi_histo;      
  delete e_ptcone20_histo; 
  delete e_charge_histo; 
  delete el_eta_histo;
  delete el_phi_histo;
  delete el_pt_histo;
  delete el_trg_eta_histo;
  delete el_trg_phi_histo;
  delete el_trg_pt_histo;
  delete el_trg_eta_phi_histo;
  delete el_trg_pt_eta_histo;
  delete e2l_eta_histo;
  delete e2l_phi_histo;
  delete e2l_pt_histo;
  delete mu_nb_histo;      
  delete mu_eta_histo;     
  delete mu_pt_histo;      
  delete mu_phi_histo;     
  delete mu_ptcone20_histo;
  delete mu_charge_histo; 
  delete mul_eta_histo;
  delete mul_phi_histo;
  delete mul_pt_histo;
  delete mu2l_eta_histo;
  delete mu2l_phi_histo;
  delete mu2l_pt_histo;
  delete mu_trg_eta_histo;
  delete mu_trg_phi_histo;
  delete mu_trg_pt_histo;
  delete mu_trg_eta_barrel_histo;
  delete mu_trg_phi_barrel_histo;
  delete mu_trg_pt_barrel_histo;
  delete mu_trg_eta_endcap_histo;
  delete mu_trg_phi_endcap_histo;
  delete mu_trg_pt_endcap_histo;
  delete mu_trg_eta_phi_histo;
  delete mu_trg_pt_eta_histo;
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
    
//  delete m_goodRunsListReader;
//  delete m_SUSYObjDef; 
         
//  std::cout << "returning from PostAnalysis   "<<std::endl;

  return;

}


