#define KEEP 0
#define REJECT 1
#define PRE_SKIP_EVENT 2
#define SUSY_ATHENA 1

//#include "JESUncertaintyProvider.cxx"
//#include "MultijetJESUncertaintyProvider.cxx"
//#include "SuSyJERProvider.C"
#include "MuonMomentumCorrections/SmearingClass.h"
#include "egammaAnalysisUtils/egammaSFclass.h"
#include "egammaAnalysisUtils/EnergyRescaler.h"
#include "MuonEfficiencyCorrections/EtaPhiBinning.h"
#include "MuonEfficiencyCorrections/MuonEfficiencyScaleFactor.h"
#include "MuonEfficiencyCorrections/AnalysisMuonEfficiencyScaleFactors.h"
#include "SUSYTools/JetID.hpp"
#include "egammaAnalysisUtils/checkOQ.h"
#include "SUSYTools/SUSYObjDef.h"
#include "SUSYTools/FakeMetEstimator.h" 
#include "SUSYTools/BTagCalib.h"
#include "PileupReweighting/TPileupReweighting.h"

#include "GoodRunsLists/TGoodRun.h"
#include "GoodRunsLists/StrUtil.h"
#include "GoodRunsLists/TMsgLogger.h"
#include "GoodRunsLists/TGRLCollection.h"
#include "GoodRunsLists/TGoodRunsListReader.h" // Good runs list checker
#include "GoodRunsLists/TGoodRunsList.h"
#include "GoodRunsLists/TUniqueGRLString.h"
#include "GoodRunsLists/TLumiBlockRange.h"

#include "egammaAnalysisUtils/egammaTriggerMatching.h"
#include "egammaAnalysisUtils/egammaTriggerMatching.h"
#include "TrigRootAnalysis/TrigDecisionToolD3PD.h"
#include "DGTriggerReweight/triggerReweight.h"

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

//select stream

#define ELECTRON 1
//#define MUON 1
//#define PILEUP 1
//#define EVTWEIGHT // (lepton Scale factors -- SF)
//#define TRGWEIGHT // (Reweighting -- needs pile up tool)
//#define BWEIGHT //b weight
//#define MC 1
//#define TRGSTUDY
//#define ACCEPTANCE
//#define TAGPROBE

//#define SYST "MSLOW"
//#define SYST "MSUP"
//#define SYST "IDLOW"
//#define SYST "IDUP"
//#define SYST "ELESFUP"
//#define SYST "ELESFDOWN"
//#define SYST "MUOSFUP"
//#define SYST "MUOSFDOWN"
//#define SYST "JER"
//#define SYST "JESUP"
//#define SYST "JESDOWN"

#define GRID   // works with local (but doesn't save outputs in root/ and txt/), Turn OFF to run PROOF

#ifdef MC
bool isData = false;
#else
bool isData = true;
#endif

#define ELETRG "EF_e22_medium" 
#define MUOTRG "EF_mu18" 

#define GeV (1000)

#ifdef TRGSTUDY

  #define EL_PT_CUT (10 * GeV)
  #define EL_LEAD_PT_CUT (10 * GeV)  //to measure rates

  #define MU_LEAD_PT_CUT (10 * GeV)  //to measure rates
  #define MU_PT_CUT (6 * GeV)  // to be lowered to 10

#else

  #define EL_PT_CUT (10 * GeV)
  #define EL_LEAD_PT_CUT (25 * GeV)  // 25 to be in trigger plateau

  #define MU_LEAD_PT_CUT (20 * GeV)
  #define MU_PT_CUT (10 * GeV)  // to be lowered to 10

#endif

#define MU_ETA_CUT (2.4)
#define MU_PTCONE20_CUT (1.8 * GeV)

#define EL_ETA_CUT (2.47)
#define EL_ISO_CUT (0.10) // 

#define JET_PT_CUT (20 * GeV)
#define JET_ETA_CUT (4.5)  
#define JET_LEAD_PT_CUT (30 * GeV)
#define JET_LEAD_ETA_CUT (2.5)  

#define MLL_CUT (20. * GeV)  

#ifdef GRID
  string path = ".";
#else
  string path = "/data/etp4/flegger/susy/D3PDReader_p832_53";
#endif

/// Class used to get SUSYObjDefs
SUSYObjDef m_SUSYObjDef;
FakeMetEstimator fakeMetEst;
D3PD::TrigDecisionToolD3PD* m_triggerTool;
triggerReweight*  trgRWT;

bool isCosmic = false;
bool isLarElectron = false;
bool isLarJet = false;
bool checkOQ = false;

std::vector<float> jetpt_smeared, jeteta_smeared, jetphi_smeared, jetE_smeared;  //jet vectors to be smeared

// getting INITIAL index
int getIndex(D3PDSelector * m_selector, std::string contname, float pt, float eta, float phi){

  unsigned int n = m_selector->GetSizeByType(contname); //initial objects 
  int index = -1;
  
  for (unsigned int i = 0; i < n; i++){   
  
    float ini_eta = m_selector->GetValByType<float>(contname,"_eta", i);
    float ini_phi = m_selector->GetValByType<float>(contname,"_phi", i);
    float ini_pt  = m_selector->GetValByType<float>(contname,"_pt", i);
    
    if ((ini_eta == eta) &&(ini_phi == phi) &&(ini_pt == pt)){
      if (index < 0) index = i;
      else {
        cout << "ERROR "<< contname << " two matches found for pt "<< pt << ": "<< index << " and "<< i <<endl;
        return -1;
      }
    } 
  }//end loop over initial objects
   
  if (index < 0)  cout << "ERROR "<< contname << " no match found for pt "<< pt << endl;
  return index; 
}

//helper function
float deltaR(float eta1, float phi1, float eta2, float phi2)
{
  //float diffphi = phi1 - phi2;
  double diffphi = phi1 - phi2;
  double diffeta = eta1 - eta2;
  
  while (fabs(diffphi) > M_PI) diffphi += ( diffphi > 0 ) ? -2*M_PI : 2*M_PI;
  
  double tmp = pow(diffeta ,2) + pow(diffphi ,2);
  float delta_R = pow(tmp, 0.5); 
  return delta_R;
}

class MyObjectPreSelection : public ObjectPreSelection
{

  public:

    MyObjectPreSelection(D3PDSelector* inst) : ObjectPreSelection(inst) {};
    //Mandatory
 
    void objectPreSelectionOrder()
    {
      //In this method which is called by the D3PD Selector, we define the order of how to execute 
      //the Object Preselection
      
      //We can do multiple iterations by giving an integer argument to the method.
      //This can later be reused to differentiate between the iterations
      index_mu=0;      
      index_ele=0;      
      index_jet=0;      
      
      do_Electron(1);
      do_Muon(1);
      do_Jet(1);
      //do_Photon(1);
 
    }

    unsigned int Electron_OPS(ObjAccess* ele, unsigned int  iteration)
    {
      (void)iteration; //avoid compiler warnings

      Int_t EventNumber = m_selector->GetScalarVal<Int_t>("EventNumber"); 
      #ifdef MC
      Int_t RunNumber = m_selector->GetScalarVal<int>("mc_channel_number");  
      #else
      Int_t RunNumber = m_selector->GetScalarVal<Int_t>("RunNumber"); 
      #endif
      
      //check if new event
      if (!(myEleEventNumber==EventNumber)){
         myEleEventNumber=EventNumber;
	 index_ele = 0;
      }
      
      int iEle = index_ele;      
      index_ele++; //update index 

      int author = ele->GetValue<int>("_author");
      float cl_eta = ele->GetValue<float>("_cl_eta");
      float cl_phi = ele->GetValue<float>("_cl_phi");
      float tracketa = ele->GetValue<float>("_tracketa");
      float trackphi = ele->GetValue<float>("_trackphi");
      unsigned int mediumPP = ele->GetValue<unsigned int>("_mediumPP");
      unsigned int OQ = ele->GetValue<unsigned int>("_OQ");
      float cl_E  = ele->GetValue<float>("_cl_E");
      int nPixHits = ele->GetValue<int>("_nPixHits");
      int nSCTHits = ele->GetValue<int>("_nSCTHits");
      
      std::vector< std::vector<float> > wet = m_selector->GetRawVector< std::vector< std::vector<float> > >( "el_MET_Simplified20_wet" );

      //isolation applied later
      bool isEle = m_SUSYObjDef.IsElectron(iEle, RunNumber, cl_eta, cl_phi, cl_E, tracketa, trackphi, author, mediumPP, OQ, nPixHits, nSCTHits, (wet.at(iEle)).at(0), isData, EL_PT_CUT,
      EL_ETA_CUT, checkOQ, 0);
      if (!isEle) return REJECT;
                      
      return KEEP;
    }

    unsigned int Muon_OPS(ObjAccess* muo, unsigned int  iteration)
    {
      (void)iteration; //avoid compiler warnings
      
      Int_t EventNumber = m_selector->GetScalarVal<Int_t>("EventNumber"); 
      
      //check if new event
      if (!(myMuoEventNumber==EventNumber)){
         myMuoEventNumber=EventNumber;
	 index_mu = 0;
      }
      
      int iMu = index_mu;
      //int index = muo->getIndex();
      //cout << myEventNumber << "   "<<EventNumber<<" index "<<index<< " my index "<<iMu<<endl;
     
      index_mu++; //update index of muon
      float eta = muo->GetValue<float>("_eta");
      float phi = muo->GetValue<float>("_phi");
      float E  = muo->GetValue<float>("_E");
      float pt = muo->GetValue<float>("_pt");      
      float me_qoverp_exPV = muo->GetValue<float>("_me_qoverp_exPV");
      float id_qoverp_exPV = muo->GetValue<float>("_id_qoverp_exPV");
      float id_theta_exPV  = muo->GetValue<float>("_id_theta_exPV");
      float me_theta_exPV  = muo->GetValue<float>("_me_theta_exPV");
      float id_theta  = muo->GetValue<float>("_id_theta");
      //float ptcone20 = muo->GetValue<float>("_ptcone20");  //isolation not to be applied to MET recalculation!            
      int isComMuo = muo->GetValue<int>("_isCombinedMuon");
      //int tight  = muo->GetValue<int>("_tight");
      int loose  = muo->GetValue<int>("_loose");

      //int isLowPt  = muo->GetValue<int>("_isLowPtReconstructedMuon");
      int isSegmentTagged  = muo->GetValue<int>("_isSegmentTaggedMuon");

      // Inner detector track
      int expectBLayerHit = muo->GetValue<int>("_expectBLayerHit");
      int nPixelDeadSensors = muo->GetValue<int>("_nPixelDeadSensors");
      int nSCTDeadSensors = muo->GetValue<int>("_nSCTDeadSensors");
      int nBLHits = muo->GetValue<int>("_nBLHits");
      int nPixHits = muo->GetValue<int>("_nPixHits");
      int nPixHoles = muo->GetValue<int>("_nPixHoles");
      int nSCTHits = muo->GetValue<int>("_nSCTHits");
      int nSCTHoles = muo->GetValue<int>("_nSCTHoles");
      int nTRTHits = muo->GetValue<int>("_nTRTHits");
      int nTRTOutliers = muo->GetValue<int>("_nTRTOutliers");
  
      #ifdef SYST
      std::string TheString = SYST; 
      #else
      std::string TheString = "";       
      #endif
      
      bool isMuo = m_SUSYObjDef.IsMuon(iMu, pt, eta, phi, E, me_qoverp_exPV, id_qoverp_exPV, me_theta_exPV, id_theta_exPV, id_theta, isComMuo, isSegmentTagged,
             loose, expectBLayerHit, nBLHits, nPixHits, nPixelDeadSensors, nPixHoles, nSCTHits, nSCTDeadSensors, nSCTHoles,
	      nTRTHits, nTRTOutliers, isData, MU_PT_CUT, MU_ETA_CUT, TheString);      
      if (!isMuo) return REJECT;
      
      //Veto evts with cosmic muons  - done later
      //float z0_exPV = muo->GetValue<float>("_z0_exPV");
      //float d0_exPV = muo->GetValue<float>("_d0_exPV");
      
      
      // APPLY after OR
      //if ( !(m_SUSYObjDef.IsSignalMuon(z0_exPV)) ) return PRE_SKIP_EVENT;
      //if (fabs(d0_exPV) > 2.)  isCosmic = true;
      //if (fabs(z0_exPV) > 5.)  isCosmic = true;
/*    if (EventNumber == 7544){
          cout << "muon "<< iMu<<" : pt "<<pt<<" eta "<< eta<<" phi "<< phi<<endl;  	  
         cout <<"CosmicMuon: "<<m_SUSYObjDef.IsCosmicMuon(muo->GetValue<float>("_z0_exPV"), muo->GetValue<float>("_d0_exPV"), 1., 0.2)<<" z0_pv: " << muo->GetValue<float>("_z0_exPV") 
	   <<" d0_pv: " <<muo->GetValue<float>("_d0_exPV")<<endl;
        }//end loop over muons  	
     
*/
      return KEEP;    
    }

    unsigned int Jet_OPS(ObjAccess* jet, unsigned int  iteration)
    {
      (void)iteration; //avoid compiler warnings

      Int_t EventNumber = m_selector->GetScalarVal<Int_t>("EventNumber"); 
      
      //check if new event
      if (!(myJetEventNumber==EventNumber)){
         myJetEventNumber=EventNumber;
	 index_jet = 0;
      }
      
      int iJet = index_jet;      
      index_jet++; //update index of jet     

      //float pt  = jet->GetValue<float>("_pt");
      //float eta = jet->GetValue<float>("_eta");
      //float phi = jet->GetValue<float>("_phi");
      //float E		= jet->GetValue<float>("_E");
      float pt  = jetpt_smeared.at(iJet);
      float eta = jeteta_smeared.at(iJet);
      float phi = jetphi_smeared.at(iJet);      
      float E	= jetE_smeared.at(iJet);   
      float sumPtTrk	= jet->GetValue<float>("_sumPtTrk");
      float NegativeE	= jet->GetValue<float>("_NegativeE");
      float Timing	= jet->GetValue<float>("_Timing");	
      float LArQuality  = jet->GetValue<float>("_LArQuality");  
      float HECQuality  = jet->GetValue<float>("_HECQuality");  
      float emfrac	= jet->GetValue<float>("_emfrac");
      float emscale_eta	= jet->GetValue<float>("_emscale_eta");
      float hecf	= jet->GetValue<float>("_hecf");
      float fracSamplingMax = jet->GetValue<float>("_fracSamplingMax");
      float AverageLArQF = jet->GetValue<float>("_AverageLArQF");   
#ifdef MC
      int flavor = jet->GetValue<int>("_flavor_truth_label");     
#else 
      int flavor = 0;
#endif          
      //necessary to call method to create jet vector  
      bool isJet = m_SUSYObjDef.IsJet(iJet, pt, eta, phi, E, emscale_eta, emfrac, hecf, LArQuality, HECQuality, AverageLArQF, Timing, sumPtTrk, fracSamplingMax, NegativeE, 
      flavor, isData, JET_PT_CUT, JET_ETA_CUT, JetID::VeryLooseBad, JetErr::NONE);
      //if (!isJet) return REJECT;

      if (E <= 0) return REJECT;
      if (pt <= JET_PT_CUT) return REJECT;
      if (fabs(eta) >= JET_ETA_CUT) return REJECT;
      
      return KEEP;    
    }


/*
    unsigned int Photon_OPS(ObjAccess* pho, unsigned int  iteration)
    {
        
      return KEEP;
    }
*/



};

