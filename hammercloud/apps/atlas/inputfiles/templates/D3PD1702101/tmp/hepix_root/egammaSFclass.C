//Efficiency scale factors macro
//Date: 11/01/2010
//Author: Olivier Arnaez <olivier.arnaez@cern.ch>
//
//Returns the combined (W/Z) scale factor and uncertainty vs eta for the egamma
//standard sets of cuts RobustLoose (set=0), RobustMedium (set=1), RobusterTight (set=2)
//in release 15 (rel=0) / release 16 (rel=1) measured with 
//probes in the 20-50 GeV range (range=0) or 30-50 GeV (range=1)
//

#include "egammaSFclass.h"

egammaSFclass::egammaSFclass()
{
  //Definition of the eta binning
  netabins=10;
  etabins.push_back(-2.47);
  etabins.push_back(-2.01); 
  etabins.push_back(-1.52); 
  etabins.push_back(-1.37); 
  etabins.push_back(-0.8); 
  etabins.push_back(0); 
  etabins.push_back(0.8); 
  etabins.push_back(1.37); 
  etabins.push_back(1.52); 
  etabins.push_back(2.01); 
  etabins.push_back(2.47);

  //For the scale factors of the standard egamma cuts 
  //Probes between 30 and 50 GeV (plateau region)
  //Loose
  efficienciesLoose3050.push_back(98.1); 
  efficienciesLoose3050.push_back(99.0); 
  efficienciesLoose3050.push_back(0.); 
  efficienciesLoose3050.push_back(98.6); 
  efficienciesLoose3050.push_back(99.5); 
  efficienciesLoose3050.push_back(99.1); 
  efficienciesLoose3050.push_back(98.8); 
  efficienciesLoose3050.push_back(0.); 
  efficienciesLoose3050.push_back(99.9); 
  efficienciesLoose3050.push_back(98.2);
  uncertaintyLoose3050.push_back(1.6); 
  uncertaintyLoose3050.push_back( 1.5); 
  uncertaintyLoose3050.push_back(0.); 
  uncertaintyLoose3050.push_back( 1.5); 
  uncertaintyLoose3050.push_back( 1.5); 
  uncertaintyLoose3050.push_back( 1.5); 
  uncertaintyLoose3050.push_back( 1.5); 
  uncertaintyLoose3050.push_back(0.); 
  uncertaintyLoose3050.push_back( 1.5); 
  uncertaintyLoose3050.push_back( 1.6);
  //Medium
  efficienciesMedium3050.push_back(95.4); 
  efficienciesMedium3050.push_back(98.7);
  efficienciesMedium3050.push_back(0.); 
  efficienciesMedium3050.push_back(97.9);
  efficienciesMedium3050.push_back(98.1);
  efficienciesMedium3050.push_back(97.7); 
  efficienciesMedium3050.push_back(97.9); 
  efficienciesMedium3050.push_back(0.); 
  efficienciesMedium3050.push_back(99.9); 
  efficienciesMedium3050.push_back(97.4);
  uncertaintyMedium3050.push_back(1.7);
  uncertaintyMedium3050.push_back( 1.6);
  uncertaintyMedium3050.push_back(0.); 
  uncertaintyMedium3050.push_back( 1.6);
  uncertaintyMedium3050.push_back( 1.5); 
  uncertaintyMedium3050.push_back( 1.5); 
  uncertaintyMedium3050.push_back( 1.5); 
  uncertaintyMedium3050.push_back(0.); 
  uncertaintyMedium3050.push_back( 1.6);
  uncertaintyMedium3050.push_back( 1.7);
  //Tight
  efficienciesTight3050.push_back(92.3); 
  efficienciesTight3050.push_back(99.2); 
  efficienciesTight3050.push_back(0.);
  efficienciesTight3050.push_back(101.5); 
  efficienciesTight3050.push_back(98.9); 
  efficienciesTight3050.push_back(99.9);
  efficienciesTight3050.push_back(104.2); 
  efficienciesTight3050.push_back(0.);
  efficienciesTight3050.push_back(102.6); 
  efficienciesTight3050.push_back(95.5);
  uncertaintyTight3050.push_back(3.3);
  uncertaintyTight3050.push_back( 2.3); 
  uncertaintyTight3050.push_back(0.);
  uncertaintyTight3050.push_back( 2.0); 
  uncertaintyTight3050.push_back( 1.8); 
  uncertaintyTight3050.push_back( 1.8);
  uncertaintyTight3050.push_back( 2.5); 
  uncertaintyTight3050.push_back(0.); 
  uncertaintyTight3050.push_back( 5.0); 
  uncertaintyTight3050.push_back( 3.2);

  //Probes between 20 and 50 GeV
  //Loose
  efficienciesLoose2050.push_back(97.6); 
  efficienciesLoose2050.push_back(99.0); 
  efficienciesLoose2050.push_back(0.); 
  efficienciesLoose2050.push_back(98.2); 
  efficienciesLoose2050.push_back(99.1); 
  efficienciesLoose2050.push_back(98.8); 
  efficienciesLoose2050.push_back(98.2); 
  efficienciesLoose2050.push_back(0.); 
  efficienciesLoose2050.push_back(99.6); 
  efficienciesLoose2050.push_back(97.4);
  uncertaintyLoose2050.push_back(1.6); 
  uncertaintyLoose2050.push_back(1.5); 
  uncertaintyLoose2050.push_back(0.); 
  uncertaintyLoose2050.push_back( 1.5); 
  uncertaintyLoose2050.push_back( 1.5); 
  uncertaintyLoose2050.push_back( 1.5); 
  uncertaintyLoose2050.push_back( 1.5); 
  uncertaintyLoose2050.push_back(0.); 
  uncertaintyLoose2050.push_back( 1.5); 
  uncertaintyLoose2050.push_back( 1.6);
  //Medium
  efficienciesMedium2050.push_back(94.5); 
  efficienciesMedium2050.push_back(98.8);
  efficienciesMedium2050.push_back(0.); 
  efficienciesMedium2050.push_back(97.2);
  efficienciesMedium2050.push_back(97.4);
  efficienciesMedium2050.push_back(97.2); 
  efficienciesMedium2050.push_back(96.7); 
  efficienciesMedium2050.push_back(0.); 
  efficienciesMedium2050.push_back(99.5); 
  efficienciesMedium2050.push_back(96.1);
  uncertaintyMedium2050.push_back(1.7);
  uncertaintyMedium2050.push_back( 1.6);
  uncertaintyMedium2050.push_back(0.); 
  uncertaintyMedium2050.push_back( 1.6);
  uncertaintyMedium2050.push_back( 1.5); 
  uncertaintyMedium2050.push_back( 1.5); 
  uncertaintyMedium2050.push_back( 1.5); 
  uncertaintyMedium2050.push_back(0.); 
  uncertaintyMedium2050.push_back( 2.9);
  uncertaintyMedium2050.push_back( 1.7);
  //Tight
  efficienciesTight2050.push_back(92.5); 
  efficienciesTight2050.push_back(99.5); 
  efficienciesTight2050.push_back(0.);
  efficienciesTight2050.push_back(100.6); 
  efficienciesTight2050.push_back(98.2); 
  efficienciesTight2050.push_back(98.7);
  efficienciesTight2050.push_back(103.3); 
  efficienciesTight2050.push_back(0.);
  efficienciesTight2050.push_back(102.8); 
  efficienciesTight2050.push_back(93.6);
  uncertaintyTight2050.push_back(3.4);
  uncertaintyTight2050.push_back( 2.4); 
  uncertaintyTight2050.push_back(0.);
  uncertaintyTight2050.push_back( 2.1); 
  uncertaintyTight2050.push_back( 1.8); 
  uncertaintyTight2050.push_back( 1.8);
  uncertaintyTight2050.push_back( 2.5); 
  uncertaintyTight2050.push_back(0.); 
  uncertaintyTight2050.push_back( 4.5); 
  uncertaintyTight2050.push_back( 3.4);

}


std::pair<float,float> egammaSFclass::scaleFactor(float eta, int set, int range, int rel) {

   int ietabin=-1;
   while (ietabin<netabins && eta>=etabins[ietabin+1]) ietabin++;
   if (ietabin<0 || ietabin>=netabins) {
     std::cout << "ERROR : given eta value outside range of existing scale factors" << std::endl;
     return make_pair(-1.,-1.);
   }

   std::vector<float> * vectEff=0;
   std::vector<float> * vectUnc=0;

   if (rel>0) {
     std::cout << "ERROR : only release 15 scale factors exist" << std::endl;
     return make_pair(-1.,-1.);
   }
   else { //release 15 numbers
     if (range==0) { //20-50 GeV region
       if (set==0) {//Loose
	 vectEff = &efficienciesLoose2050;
	 vectUnc = &uncertaintyLoose2050;
       }
       else if (set==1) {//Medium
	 vectEff = &efficienciesMedium2050;
	 vectUnc = &uncertaintyMedium2050;
       }
       else if (set==2) {//Tight
	 vectEff = &efficienciesTight2050;
	 vectUnc = &uncertaintyTight2050;
       }
     }//endif 20-50 GeV
     else if (range==1) { //30-50 GeV region
       if (set==0) {//Loose
	 vectEff = &efficienciesLoose3050;
	 vectUnc = &uncertaintyLoose3050;
       }
       else if (set==1) {//Medium
	 vectEff = &efficienciesMedium3050;
	 vectUnc = &uncertaintyMedium3050;
       }
       else if (set==2) {//Tight
	 vectEff = &efficienciesTight3050;
	 vectUnc = &uncertaintyTight3050;
       }
     }//endif 30-50 GeV
   }//endif rel15

   float eff = vectEff->at(ietabin)/100.;
   float unc = vectUnc->at(ietabin)/100.;

   return make_pair(eff,unc);
}
