/**
   Author Nikola Makovec <makovec@cern.ch>
   
  Purpose: Apply JER uncertainties based on ATLAS-CONF-2010-054
           
  - Version 1.0 (11 November 2010):  

  - Usage:
    double pt = jet pt in GeV
    double cor=getSmearingCor(pt);
    double smeared_e=cor*jet_e;
    double smeared_pt=cor*jet_pt;
    						 
   
*/

#include <TRandom.h>
#include <cmath>

double getSmearingCor( double pt)
{
  static double N= 4.6;
  static double S=0.846; 
  static double C=0.064;

  if(pt<=0) return -999;      
  double sigma_mc = sqrt(N*N/pt/pt + S*S/pt + C*C);
  //sqrt(1.14*1.14 - 1.*1. )=0.55
  double delta_sigma=0.55*sigma_mc;      
  return 1+ gRandom->Gaus(0,delta_sigma);



}


