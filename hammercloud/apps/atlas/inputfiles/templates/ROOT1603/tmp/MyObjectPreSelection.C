#define KEEP 0
#define REJECT 1
#define PRE_SKIP_EVENT 2

#define GRID

#include "checkOQ.C"
#include "JESUncertaintyProvider.cxx"
#include "MultijetJESUncertaintyProvider.cxx"
#include "SuSyJERProvider.C"
#include <math.h>
#include "TRandom3.h"
TRandom3* gRand;

//#define QCDBG
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
      
      do_Electron(1);
      index_mu=0;      
      do_Muon(1);
      do_Jet(1);
      //do_Photon(1);
      
    }

    unsigned int Electron_OPS(ObjAccess* ele, unsigned int  iteration)
    {
      (void)iteration; //avoid compiler warnings
      
       //see https://twiki.cern.ch/twiki/bin/view/AtlasProtected/SusyObjectDefintions
      //Int_t eventNumber = m_selector->GetScalarVal<Int_t>("EventNumber"); 

      int author = ele->GetValue<int>("_author");
      if (!(author == 1 || author == 3)) return REJECT;

      float pt  = ele->GetValue<float>("_pt");
      
#ifdef ELESPLUS      
      float scale = 0.03;
      pt = pt * (1 + scale);
#endif
#ifdef ELESMINUS      
      float scale = 0.03;
      pt = pt * (1 - scale);
#endif
      float eta = ele->GetValue<float>("_cl_eta");
      float phi = ele->GetValue<float>("_cl_phi");
      
#ifdef ELER      
float cl_e0 = ele->GetValue<float>("_cl_E");
double S=0.1; // sampling term
double C=0.007; // constant
double S_er=0.2; //error on the sampling term
double C_er_B=1; //error on the constant in barrel
double C_er_EC=4.; //error on the constant in EC
double C_er0=C_er_EC;
if(fabs(eta)<1.37)C_er0=C_er_B;
double sigma0 = std::sqrt( std::pow(S*(1+S_er)*std::sqrt(cl_e0),2)+ std::pow(C*(1+C_er0)*cl_e0,2)- std::pow(S*std::sqrt(cl_e0),2)- std::pow(C*cl_e0,2));
double DeltaE0 = gRandom->Gaus(0,sigma0);
double cor0=(cl_e0+DeltaE0)/cl_e0;
pt=pt*cor0;
#endif

      if (pt <= 20000. || fabs(eta) >= 2.47) return REJECT;            

      //B-layer       
      /*
      float expHitBLayer = ele->GetValue<float>("_expectHitInBLayer");
      int nBLHits = ele->GetValue<int>("_nBLHits");
      if (expHitBLayer ==1. && nBLHits == 0) return REJECT;
      */
      
     //isRobustMedium            
      int isEM    = ele->GetValue<int>("_isEM");
      float cl_E  = ele->GetValue<float>("_cl_E");
      float etas2 = ele->GetValue<float>("_etas2");
      float Reta  = ele->GetValue<float>("_reta");
      float w2    = ele->GetValue<float>("_weta2");      
      float eT    = cl_E / cosh(etas2);

#ifdef QCDBG
      if (!(isRobustLoose( isEM,  etas2,  eT,  Reta, w2 ))) return REJECT;      
#else 
      if (!(isRobustMedium( isEM,  etas2,  eT,  Reta, w2 ))) return REJECT;      
//      float expHitBLayer = ele->GetValue<float>("_expectHitInBLayer");
//      if (!(isRobusterTight( isEM, expHitBLayer, eta,  eT,  Reta, w2 ))) return REJECT;      
#endif

      //otx veto
      Int_t RunNumber = m_selector->GetScalarVal<Int_t>("RunNumber"); 
      
      if ((RunNumber <= 150000)||(RunNumber >= 200000)){ 
        RunNumber = 167521; // only for cutflow comparison, use latest OTX map!!
      }

      if (egammaOQ::checkOQClusterElectron(RunNumber, eta, phi)==3) return REJECT;
       
// apply in Between_OPS_and_OR
      if (fabs(eta) > 1.37 &&  fabs(eta) < 1.52) return PRE_SKIP_EVENT; //electron crack veto
      
      //NO isolation cut at Object selection level
      //float etcone20 = ele->GetValue<float>("_Etcone20");
      //if (etcone20/pt >= 0.15) return REJECT; // Do not apply this cut for the electrons used in crack veto
    
      #ifdef ELERECO
      gRand = new TRandom3();
      Int_t EventNumber = m_selector->GetScalarVal<Int_t>("EventNumber"); 
      //check if new event
      if (!(myEventNumber==EventNumber)){
         myEventNumber=EventNumber;
	 index_ele = 0;
      }
      int iEle = index_ele;
      gRand->SetSeed(0); 
      gRand->SetSeed(680049 + EventNumber + iEle*100);  
      double eff = gRand->Uniform(0.,1.);
      if (eff < 0.05) return REJECT;
      #endif
          
      return KEEP;
    }

    unsigned int Muon_OPS(ObjAccess* muo, unsigned int  iteration)
    {
      (void)iteration; //avoid compiler warnings
      Int_t RunNumber = m_selector->GetScalarVal<Int_t>("RunNumber"); 
      Int_t EventNumber = m_selector->GetScalarVal<Int_t>("EventNumber"); 
      
      //check if new event
      if (!(myEventNumber==EventNumber)){
         myEventNumber=EventNumber;
	 index_mu = 0;
      }
      
      int iMu = index_mu;
      //int index = muo->getIndex();
      //cout << myEventNumber << "   "<<EventNumber<<" index "<<index<< " my index"<<iMu<<endl;
      
      index_mu++; //update index of muon
      float eta = muo->GetValue<float>("_eta");
      float pt = muo->GetValue<float>("_pt");      
            
      int isComMuo = muo->GetValue<int>("_isCombinedMuon");
      int isLowPt  = muo->GetValue<int>("_isLowPtReconstructedMuon");
      
      if (!(isComMuo || isLowPt)) return REJECT;

      // Inner detector track
      int nPixelHits = muo->GetValue<int>("_nPixHits");
      int nSCTHits = muo->GetValue<int>("_nSCTHits");
      int nTRTHits = muo->GetValue<int>("_nTRTHits");
      int nTRTOutliers = muo->GetValue<int>("_nTRTOutliers");
      int n =  nTRTOutliers +nTRTHits;
          
      if ((nPixelHits < 1) || (nSCTHits < 6)) return REJECT;

      // below is fabs(pTID-pTMS)/pTID < 0.5 cut --- pt for me and id not in D3PD, have to use qoverp
      float me_qoverp = muo->GetValue<float>("_me_qoverp_exPV");
      float id_qoverp = muo->GetValue<float>("_id_qoverp_exPV");
      float id_theta  = muo->GetValue<float>("_id_theta_exPV");
      float me_theta  = muo->GetValue<float>("_me_theta_exPV");

      if (isComMuo && me_qoverp != 0. && sin(id_theta) != 0. && (fabs(sin(me_theta)/me_qoverp) < 50000.) && (id_qoverp/me_qoverp - 1. <= -0.4)) return REJECT;
      
      float trackEta = -log(tan(id_theta/2));
      if (fabs(trackEta) < 1.9 && n <= 5) return REJECT;
      if (n > 5 && nTRTOutliers >= 0.9*n) return REJECT;
      
      float matchchi2 = muo->GetValue<float>("_matchchi2");

      if (isComMuo && matchchi2 > 150.) return REJECT;
      
      float ptcone20 = muo->GetValue<float>("_ptcone20");  //isolation not to be applied to MET recalculation!
      if ( ptcone20 >= 1800. ) return REJECT;

      float mypt = pt;
      
      // Do this on MC only ! 
      if ((RunNumber <= 150000)||(RunNumber >= 200000)){ 
 
 /** Use the MC event number to set seed so that the random numbers are reproducible by different analyzers **/
        double ptcb = mypt;
        double ptid = (id_qoverp != 0.) ? fabs(sin(id_theta)/id_qoverp) : 0.;
        double ptms = (me_qoverp != 0.) ? fabs(sin(me_theta)/me_qoverp) : 0.;
        mcp_smear.SetSeed(EventNumber, iMu);
        mcp_smear.Event(ptms,ptid,ptcb,eta); 

//change the Pts UP or DOWN (ID or MS)
//Valid values for "THESTRING": {"MSLOW", "MSUP", "IDLOW", "IDUP"}
//Get Smeared Pts

        double pTCB_smeared = mcp_smear.pTCB();
        double pTMS_smeared = mcp_smear.pTMS();
        double pTID_smeared = mcp_smear.pTID(); 
#ifdef MUOSPLUS      
        mcp_smear.PTVar(pTMS_smeared, pTID_smeared, pTCB_smeared, "MSUP");
#endif
#ifdef MUOSMINUS      
        mcp_smear.PTVar(pTMS_smeared, pTID_smeared, pTCB_smeared, "MSLOW");
#endif
  
        if (isComMuo)
          mypt = mcp_smear.pTCB();
        else
          mypt = mcp_smear.pTID();
  
// mypt = mypt; // Overwrite muon pt for later use in analysis
// mypx = mypt*cos(phi); // Used to recompute MEx
// mypy = mypt*sin(phi); // Used to recompute MEy


      }
  
 
      if (( fabs(eta) >= 2.4 ) || ( mypt <= 20000. )) return REJECT;

 // cout << "OPS: mu "<<iMu<<" pt "<<mypt<<endl;
      
      //Veto evts with cosmic muons

      float z0 = muo->GetValue<float>("_z0_exPV");
      if (fabs(z0) >= 10.)  return PRE_SKIP_EVENT;
//      float cov_d0 = muo->GetValue<float>("_cov_d0_exPV");
//      float d0 = muo->GetValue<float>("_d0_exPV");
//      if ((fabs(z0) >= 10.) || (cov_d0 > 0. && fabs(d0/sqrt(cov_d0)) >= 5.)) return PRE_SKIP_EVENT;

      #ifdef MUORECO
      gRand = new TRandom3();
      gRand->SetSeed(0); 
      gRand->SetSeed(680049 + EventNumber + iMu*100);  
      double eff = gRand->Uniform(0.,1.);
      if (eff < 0.05) return REJECT;
      #endif
       
      return KEEP;    
    }

    unsigned int Jet_OPS(ObjAccess* jet, unsigned int  iteration)
    {
      (void)iteration; //avoid compiler warnings

      float eta = jet->GetValue<float>("_emscale_eta");
      float jes = jet->GetValue<float>("_EMJES");
      float pt = (jet->GetValue<float>("_emscale_pt"));      

      if ( fabs(eta) >= 2.5 ) return REJECT;

      //jes
/*      EMJESFixer jetEMJESfixer;
      std::string filename = "JESUncertainty.root";
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
      float JESUncertainty = 0;
      if (jes ==0.) jes = jetEMJESfixer.fixAntiKt4H1Topo(pt,eta);      
      if ((fabs(jes*pt) > 15000.)&& (fabs(eta)<4.5)) JESUncertainty = myJES.getRelUncert(jes*pt, eta, JESUncertaintyProvider::NOPILEUP);
#ifdef JESPLUS      
      jes = jes* (1 + JESUncertainty);
#endif
#ifdef JESMINUS      
      jes = jes * (1 - JESUncertainty);
#endif
#ifdef JER 
      //rescale jes by jer
      double cor=getSmearingCor(jes *pt/1000.); 
      jes =  jes * cor ;
#endif
  */          
      pt = jes *pt;
      
      if ( fabs(pt) <= 20000. ) return REJECT;
   
       return KEEP;    
    }


/*
    unsigned int Photon_OPS(ObjAccess* pho, unsigned int  iteration)
    {
        
      return KEEP;
    }
*/



};

