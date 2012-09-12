#include "TLorentzVector.h"

bool triggerMatchEE(TLorentzVector el1, TLorentzVector el2, std::vector<float> *trig_el_px, std::vector<float> *trig_el_py, std::vector<float> *trig_el_pz, std::vector<float> *trig_el_E, std::vector<int> *triggerchain) {

  int matchfirst=0;
  int matchsecond=0;
  bool match1=false;
  double preDeltaR=0.02;

  for(int i=0;i<triggerchain->size();i++){
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

  for(int i=0;i<triggerchain->size();i++){
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
  
