/**
 Authors
 Nikola Makovec <makovec@cern.ch>
 Nils Ruthmann <nils.ruthmann@cern.ch>
 Justin Keung <jkeung@cern.ch>

 Purpose: define the jet identification criteria

 - Version 3.0
    implements the rel 17 cleaning at four working points.

**/


#include "SUSYTools/JetID.hpp"
#include <cmath>
#include <iostream>
namespace JetID
{
 bool isBadJet(BadJetCategory criteria,
		double emf,
		double hecf,
		double larq,
		double hecq,
		double time,     //in ns
		double sumpttrk, //in MeV, same as sumpttrk
		double eta,      //emscale Eta  
		double pt,       //in GeV, same as sumpttrk
		double fmax,
		double negE ,     //in MeV
		double AverageLArQF,
		double jvf
		)
 {  
   double chf=sumpttrk/pt;

//    if(jvf>0)
//       chf=chf/jvf;
//     else jvf=0;
   //include <iostream>
   //    std::cout<<chf<<std::endl;

   //=============================================================
   //VeryLoose cuts
   //=============================================================
   //Non-collision background & cosmics
   if(emf<0.05 && chf<0.05 && fabs(eta)<2)            return true;
   if(emf<0.05 && fabs(eta)>=2)                       return true;
   if(fmax>0.99 && fabs(eta)<2)                       return true;
   //HEC spike
   if(fabs(negE/1000.)>60)                            return true;
   if(hecf>0.5 && fabs(hecq)>0.5 && AverageLArQF/65535>=0.8)                     return true;  
   //EM calo noise
   if(emf>0.95 && fabs(larq)>0.8 && fabs(eta)<2.8 && AverageLArQF/65535>=0.8)    return true;

  //=============================================================
   //Loose cuts
   //=============================================================
   if(criteria>=LooseBad){
     //Non-collision background & cosmics
     if(fabs(time)>25)                                  return true;
     //HEC spike
     if(hecf>0.5 && fabs(hecq)>0.5)                     return true;  
     //EM calo noise
     if(emf>0.95 && fabs(larq)>0.8 && fabs(eta)<2.8)    return true;
   }
   //=============================================================
   //Additionnal medium cuts
   //=============================================================
   if(criteria>=MediumBad){

     //Non-collision background & cosmics
     if(fabs(time)>10)                                return true;
     if(emf<0.05 && chf<0.1  && fabs(eta)<2)          return true;  
     if(emf>0.95 && chf<0.05 && fabs(eta)<2)          return true;
     //HEC spike
     if(hecf>1-fabs(hecq))                            return true;
   //EM calo noise
     if(emf>0.9 && fabs(larq)>0.8 && fabs(eta)<2.8)   return true;
   }
   //=============================================================
   //Additionnal tight cuts
   //=============================================================
   if(criteria>=TightBad){
     //Non-collision background & cosmics
     if(emf<0.1 && chf<0.2  && fabs(eta)<2)           return true; 
     if(emf<0.1 && fabs(eta)>=2 )                     return true;    
     if(emf>0.9 && chf<0.02 && fabs(eta)<2)           return true;
     //EM calo noise
     if(fabs(larq)>0.95)                              return true;
     if(emf>0.98 && fabs(larq)>0.05)                  return true;
   }

  //=============================================================
   //Additionnal newtight cuts
   //=============================================================
   if(criteria>=NewTightBad){  

     //Non-collision background & cosmics
     if(chf<0.01 && fabs(eta)<2.5 )                     return true;    
     if(emf>0.9 && chf<0.10 && fabs(eta)<2.5)           return true;
   }

   return false;
 }
}
