#include "TLorentzVector.h"

bool triggerMatchE(TLorentzVector el, std::vector<float> *trig_el_px, std::vector<float> *trig_el_py, std::vector<float> *trig_el_pz, std::vector<float> *trig_el_E, std::vector<int> *triggerchain) {

  bool match = false;

  double preDeltaR=0.02;

  for(unsigned int i=0;i<triggerchain->size();i++){
    TLorentzVector trigel;
    trigel.SetPxPyPzE(trig_el_px->at(i),trig_el_py->at(i),trig_el_pz->at(i),trig_el_E->at(i));
    if(el.DeltaR(trigel)<preDeltaR){
      if(triggerchain->at(i)>0){ match = true;
	preDeltaR = el.DeltaR(trigel);
      }
      else match = false;
    } 
  }
  
  return match;

}

bool triggerMatchM(TLorentzVector muon1, std::vector<int> *triggerchain_single, 
     std::vector< std::vector<float> > *trig_EF_trigmuonef_track_CB_eta,  std::vector< std::vector<float> > *trig_EF_trigmuonef_track_CB_phi )
{
  int nMuonsPass = 0;
  
  for(unsigned int trigItr=0;trigItr<trig_EF_trigmuonef_track_CB_eta->size();trigItr++){
    if( triggerchain_single->at(trigItr) > 0.5 ) {
      for( unsigned int trackItr = 0; trackItr < trig_EF_trigmuonef_track_CB_eta->at(trigItr).size();trackItr++){
   	double onl_eta = trig_EF_trigmuonef_track_CB_eta->at(trigItr).at(trackItr);
   	double onl_phi = trig_EF_trigmuonef_track_CB_phi->at(trigItr).at(trackItr);

   	double off_eta = muon1.Eta();
   	double off_phi = muon1.Phi();
   	if( deltaR( onl_eta, onl_phi, off_eta, off_phi ) < 0.15 ) { 
   	  nMuonsPass += 1;
   	  break;
   	}
   	if(nMuonsPass >= 1 ){break;}
      }if(nMuonsPass >= 1 ){break;}
    }if(nMuonsPass >= 1 ){break;}
  }
  bool muonmatch=false;
  if( nMuonsPass >= 1 ) {muonmatch = true;}

  return muonmatch;

}
  
bool triggerMatchMU(TLorentzVector muon1,TLorentzVector muon2,std::vector<int> *triggerchain_single, std::vector<int> *triggerchain_double,
     std::vector< std::vector<float> > *trig_EF_trigmuonef_track_CB_eta,  std::vector< std::vector<float> > *trig_EF_trigmuonef_track_CB_phi )
{

    bool match = false;

    int nMuonsPassEF_single = 0; 
    int nMuonsPassEF_double = 0;  

      
      for(unsigned int trigItr=0;trigItr<trig_EF_trigmuonef_track_CB_eta->size();trigItr++){
        
        if( triggerchain_single->at(trigItr) > 0.5 || triggerchain_double->at(trigItr) > 0.5 ) {
          
          for( unsigned int trackItr = 0; trackItr < trig_EF_trigmuonef_track_CB_eta->at(trigItr).size();trackItr++){
            
            double onl_eta = trig_EF_trigmuonef_track_CB_eta->at(trigItr).at(trackItr); 
            double onl_phi = trig_EF_trigmuonef_track_CB_phi->at(trigItr).at(trackItr);
            
            for(int ip=0;ip<2;ip++){
              double off_eta;
              double off_phi;
              double muonpt;
              if(ip==0){
        	off_eta = muon1.Eta();  off_phi =muon1.Phi(); muonpt= muon1.Pt();
              }
              else if(ip==1){
        	off_eta = muon2.Eta();  off_phi =muon2.Phi(); muonpt=muon2.Pt();
              }
              if( deltaR( onl_eta, onl_phi, off_eta, off_phi ) < 0.15 && muonpt > 20000. && triggerchain_single->at(trigItr) > 0.5 ) {
	        nMuonsPassEF_single += 1;
        	break;
              }
              
              if( deltaR( onl_eta, onl_phi, off_eta, off_phi ) < 0.15 && muonpt > 12000. && triggerchain_double->at(trigItr) > 0.5) {
	        nMuonsPassEF_double += 1;
              }
              if(nMuonsPassEF_single >= 1 || nMuonsPassEF_double >= 2){break;}
            }if(nMuonsPassEF_single >= 1 || nMuonsPassEF_double >= 2){break;}
          }if(nMuonsPassEF_single >= 1 || nMuonsPassEF_double >= 2){break;}
        }if(nMuonsPassEF_single >= 1 || nMuonsPassEF_double >= 2){break;}
      }
      
      if( nMuonsPassEF_single >= 1 || nMuonsPassEF_double >= 2) match = true;
    

    return match;
   
}

bool triggerMatchEE(TLorentzVector el1, TLorentzVector el2, std::vector<float> *trig_el_px, std::vector<float> *trig_el_py, std::vector<float> *trig_el_pz, std::vector<float> *trig_el_E, std::vector<int> *triggerchain) {

  int matchfirst=0;
  int matchsecond=0;
  bool match1=false;
  double preDeltaR=0.02;

  for( unsigned int i=0;i<triggerchain->size();i++){
    TLorentzVector trigel;
    trigel.SetPxPyPzE(trig_el_px->at(i),trig_el_py->at(i),trig_el_pz->at(i),trig_el_E->at(i));
    
    if(el1.DeltaR(trigel)<preDeltaR) {
      if(triggerchain->at(i)>0) {
	match1 = true;
	preDeltaR = el1.DeltaR(trigel);
	matchfirst=i;
      } 
      else match1 = false;
    }
  }

  bool match2=false;
  preDeltaR = 0.02;

  for( unsigned int i=0;i<triggerchain->size();i++){
    TLorentzVector trigel;
    trigel.SetPxPyPzE(trig_el_px->at(i),trig_el_py->at(i),trig_el_pz->at(i),trig_el_E->at(i));
    if(el2.DeltaR(trigel)<preDeltaR){
      if(triggerchain->at(i)>0){ match2 = true;
	preDeltaR = el2.DeltaR(trigel);
	matchsecond=i;
      }
      else match2 = false;
    }
  }

  bool match= match1 && match2 && (matchfirst!=matchsecond);

  return match;

}
  
