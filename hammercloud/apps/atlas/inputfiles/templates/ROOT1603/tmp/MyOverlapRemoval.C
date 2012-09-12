#include <math.h>

#define KEEP_BOTH 0 
#define KEEP_FIRST 2
#define KEEP_SECOND 1
#define REJECT_FIRST 1
#define REJECT_SECOND 2
#define REJECT_BOTH 3


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


class MyOverlapRemoval : public OverlapRemoval
{
 public:
  //Constructor, Mandatory
  MyOverlapRemoval(D3PDSelector* inst) : OverlapRemoval(inst) {};  

 
  void overlapRemovalOrder()
  {
    //In this method, we may define the order in which the OR is done
    //we can have multiple iterations, indicated by the parameter

    do_Electron_Jet(1); //First do Electron vs Jet
    do_Muon_Jet(1); // Then do muon vs jet
    do_Electron_Jet(2); // Again do Electron vs Jet
    
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
    float ele_eta = ele->GetValue<float>("_eta");
    float ele_phi = ele->GetValue<float>("_phi");
    
    //float ele_pt = ele->GetValue<float>("_pt");
    //if (ele_pt < 10000.) cout << "ERROR electron pt during overlap removal "<<ele_pt <<endl;
    
    //float jet_eta = jet->GetValue<float>("_eta");
    //float jet_phi = jet->GetValue<float>("_phi");
    float jet_eta = jet->GetValue<float>("_emscale_eta");
    float jet_phi = jet->GetValue<float>("_emscale_phi");
/*
    float jet_pt = ( jet->GetValue<float>("_emscale_pt")); 
    float jes = jet->GetValue<float>("_EMJES");
    
    //fix jes
    EMJESFixer jetEMJESfixer;
    if (jes ==0.) jes = jetEMJESfixer.fixAntiKt4H1Topo(jet_pt,jet_eta);;      
    jet_pt = jes *jet_pt;
    
    if (jet_pt < 20000.) cout << "ERROR jet pt during overlap removal "<<jet_pt <<endl;
    if (jet_eta > 2.5)   cout << "ERROR jet eta during overlap removal "<<jet_eta <<endl;
*/
       
    //calculating deltaR
    float dR = deltaR(ele_eta,ele_phi,jet_eta,jet_phi);

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
    float muo_eta = muo->GetValue<float>("_eta");
    float muo_phi = muo->GetValue<float>("_phi");

    //float jet_eta = jet->GetValue<float>("_eta");
    //float jet_phi = jet->GetValue<float>("_phi");
    float jet_eta = jet->GetValue<float>("_emscale_eta");
    float jet_phi = jet->GetValue<float>("_emscale_phi");
    
    float dR = deltaR(muo_eta,muo_phi,jet_eta,jet_phi);
    
    //float muo_pt = muo->GetValue<float>("_pt");
    //if (muo_pt < 10000.) cout << "ERROR muon pt during overlap removal "<<muo_pt <<endl;
    
    //std::cout << " mu_jet dR " << dR << std::endl;

    if (dR < 0.4 ) return REJECT_FIRST;   // --> KEEP JET, REJECT MUON
    
    
    return KEEP_BOTH;
  }
   
  
  

};
