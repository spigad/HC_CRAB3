#include <math.h>

#define KEEP_BOTH 0 
#define KEEP_FIRST 2
#define KEEP_SECOND 1
#define REJECT_FIRST 1
#define REJECT_SECOND 2
#define REJECT_BOTH 3

class MyOverlapRemoval : public OverlapRemoval
{
 public:
  //Constructor, Mandatory
  MyOverlapRemoval(D3PDSelector* inst) : OverlapRemoval(inst) {};  

 
  void overlapRemovalOrder()
  {
    //In this method, we may define the order in which the OR is done
    //we can have multiple iterations, indicated by the parameter

    do_Electron_Electron(1); //First do Electron vs Jet
    do_Electron_Jet(1); //First do Electron vs Jet
    do_Electron_Jet(2); // Again do Electron vs Jet
    do_Muon_Jet(1); // Then do muon vs jet
    do_Muon_Electron(1); // do Electron vs Muon
    
    //Available:

    /*    
    do_Electron_Jet(unsigned int iteration);
    do_Muon_Jet(unsigned int  iteration);
    do_Photon_Jet(unsigned int  iteration);
    do_Muon_Electron(unsigned int  iteration);
    do_Photon_Electron(unsigned int  iteration);
    do_Photon_Muon(unsigned int  iteration);
    */
    
    
  }
 
 
 
 //the actualy overlap removal methods
 //availabel are:
 
 /*
     //--VS Jet
    unsigned int ElectronJet_OR(ObjAccess* ele, ObjAccess* jet, unsigned int iteration);  
    unsigned int MuonJet_OR(ObjAccess* muo, ObjAccess* jet, unsigned int iteration);
    unsigned int PhotonJet_OR(ObjAccess* pho, ObjAccess* jet, unsigned int iteration);
  
    //--VS Electron
    unsigned int MuonElectron_OR(ObjAccess* muo, ObjAccess* ele,  unsigned int iteration);
    unsigned int PhotonElectron_OR(ObjAccess* pho, ObjAccess* ele,  unsigned int iteration);
    
    //--VS Muon
    unsigned int PhotonMuon_OR(ObjAccess* pho, ObjAccess* muo,  unsigned int iteration);

 */
 
  unsigned int ElectronJet_OR(ObjAccess* ele, ObjAccess* jet, unsigned int iteration)
  {
    //Example Electron vs Jet
  
    
    //First Getting eta and phi of electron and jet
    float ele_pt = ele->GetValue<float>("_pt");
    float ele_phi = ele->GetValue<float>("_phi");
    float ele_eta = ele->GetValue<float>("_eta");
    int index_ele = getIndex(m_selector, "ELE", ele_pt, ele_eta, ele_phi);      
    TLorentzVector vec = m_SUSYObjDef.m_el[index_ele];
    
    //float ele_pt = ele->GetValue<float>("_pt");
    //if (ele_pt < 10000.) cout << "ERROR electron pt during overlap removal "<<ele_pt <<endl;
    
    float jet_pt = jet->GetValue<float>("_pt");
    float jet_eta = jet->GetValue<float>("_eta");
    float jet_phi = jet->GetValue<float>("_phi");
    int index_jet = getIndex(m_selector, "JET", jet_pt, jet_eta, jet_phi);      
       
    //calculating deltaR using smeared quantities
    //float dR = deltaR(ele_eta,ele_phi,jet_eta,jet_phi);
    float dR = deltaR(vec.Eta(),vec.Phi(),jeteta_smeared.at(index_jet),jetphi_smeared.at(index_jet));

    //cout << "overlap removal electron jet "<<endl;
    //Iteration 1 handinlig
    if (iteration == 1)
    {
      if (dR < 0.2) 
      {
        // First and Second refer to the order in the method name. Here, first means Electron, second means Jet
        
        //cout << "dR = "<<dR<<" < 0.2 keep electron pt "<<ele_pt<<" and remove jet pt "<<jet_pt<<endl;
	
	return KEEP_FIRST; // OR return REJECT_SECOND --> KEEP ELECTRON, REJECT JET
      } 
    }
    
    //Iteration 2 handling
    if (iteration == 2)
    {
      if (dR > 0.2 && dR < 0.4) 
      {
        //cout << "0.2 <dR = "<<dR<<" < 0.4 remove electron pt "<<ele_pt<<" keep jet pt "<<jet_pt<<endl;
        return KEEP_SECOND;// OR return REJECT_FIRST  --> KEEP JET, REJECT ELECTRON
      }
    }
    
    return KEEP_BOTH; //keep both if nothing happened
  }
 
 
 
  unsigned int MuonJet_OR(ObjAccess* muo, ObjAccess* jet, unsigned int /*iteration*/)
  {
    float muo_pt = muo->GetValue<float>("_pt");
    float muo_eta = muo->GetValue<float>("_eta");
    float muo_phi = muo->GetValue<float>("_phi");
    int index_muo = getIndex(m_selector, "MUO", muo_pt, muo_eta, muo_phi);      
    TLorentzVector vec = m_SUSYObjDef.m_mu[index_muo];

    float jet_pt = jet->GetValue<float>("_pt");
    float jet_eta = jet->GetValue<float>("_eta");
    float jet_phi = jet->GetValue<float>("_phi");
    int index_jet = getIndex(m_selector, "JET", jet_pt, jet_eta, jet_phi);      
    
    //float dR = deltaR(muo_eta,muo_phi,jet_eta,jet_phi);
    //calculating deltaR using smeared quantities
    float dR = deltaR(vec.Eta(),vec.Phi(),jeteta_smeared.at(index_jet),jetphi_smeared.at(index_jet));
    
    //float muo_pt = muo->GetValue<float>("_pt");
    //if (muo_pt < 10000.) cout << "ERROR muon pt during overlap removal "<<muo_pt <<endl;
    
    //std::cout << " mu_jet dR " << dR << std::endl;
/*      Int_t EventNumber = m_selector->GetScalarVal<Int_t>("EventNumber"); 
    if ((EventNumber == 7544)&&(dR < 0.4 )){
          cout << "OR: muon eta "<< muo_eta<<" phi "<< muo_phi<<endl;  	  
          cout << "OR: jet eta "<< jet_eta<<" phi "<< jet_phi<<endl;  	  

        }*/ 	

    if (dR < 0.4 ) return REJECT_FIRST;   // --> KEEP JET, REJECT MUON
    
    
    return KEEP_BOTH;
  }
   
  
  unsigned int MuonElectron_OR(ObjAccess* muo, ObjAccess* ele, unsigned int /*iteration*/)
  {
    float muo_eta = muo->GetValue<float>("_eta");
    float muo_phi = muo->GetValue<float>("_phi");
    float muo_pt = muo->GetValue<float>("_pt");
    
    int index_muo = getIndex(m_selector, "MUO", muo_pt, muo_eta, muo_phi);      
    TLorentzVector vecMuo = m_SUSYObjDef.m_mu[index_muo];

    float ele_pt = ele->GetValue<float>("_pt");
    float ele_eta = ele->GetValue<float>("_eta");
    float ele_phi = ele->GetValue<float>("_phi");
    int index_ele = getIndex(m_selector, "ELE", ele_pt, ele_eta, ele_phi);      
    TLorentzVector vecEle = m_SUSYObjDef.m_el[index_ele];
    
//    float dR = deltaR(muo_eta,muo_phi,ele_eta,ele_phi);
    float dR = deltaR(vecMuo.Eta(),vecMuo.Phi(),vecEle.Eta(),vecEle.Phi());
    
    if (dR < 0.1 ) return REJECT_BOTH;   // --> REJECT MUON AND ELECTRON
    
    
    return KEEP_BOTH;
  }
  
   unsigned int ElectronElectron_OR(ObjAccess* ele1, ObjAccess* ele2, unsigned int /*iteration*/)
   {
     float ele1_eta = ele1->GetValue<float>("_eta");
     float ele1_phi = ele1->GetValue<float>("_phi");
     float ele1_pt  = ele1->GetValue<float>("_pt");
     int index_ele1 = getIndex(m_selector, "ELE", ele1_pt, ele1_eta, ele1_phi);      
     TLorentzVector vecEle1 = m_SUSYObjDef.m_el[index_ele1];

     float ele2_eta = ele2->GetValue<float>("_eta");
     float ele2_phi = ele2->GetValue<float>("_phi");
     float ele2_pt  = ele2->GetValue<float>("_pt");
     int index_ele2 = getIndex(m_selector, "ELE", ele2_pt, ele2_eta, ele2_phi);      
     TLorentzVector vecEle2 = m_SUSYObjDef.m_el[index_ele2];
     
     float dR = deltaR(vecEle1.Eta(),vecEle1.Phi(),vecEle2.Eta(),vecEle2.Phi());
     if (dR < 0.1 ) {
       if (vecEle1.Pt() > vecEle2.Pt()) return REJECT_SECOND;   
       if (vecEle1.Pt() < vecEle2.Pt()) return REJECT_FIRST;	
     }
     
     return KEEP_BOTH;
   }  

};
