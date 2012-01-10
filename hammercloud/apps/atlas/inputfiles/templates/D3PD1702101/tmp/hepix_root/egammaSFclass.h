//Efficiency scale factors macro
//Date: 11/01/2010
//Author: Olivier Arnaez <olivier.arnaez@cern.ch>
//
//float myscalefactortoapply = objsf->scaleFactor(η(cluster), set, range, rel) 
//returns the combined (W/Z) scale factor and uncertainty vs eta for the egamma
//standard sets of cuts RobustLoose (set=0), RobustMedium (set=1) and 
//RobusterTight (set=2) in release 15 (rel=0) / release 16 (rel=1) measured with 
//probes in the 20-50 GeV range (range=0) or 30-50 GeV (range=1)
//
//The first number returned is the efficiency scale factor while the second number is
//its uncertainty
//

#ifndef egammaSFclass_h
#define egammaSFclass_h

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class egammaSFclass {

public:

  egammaSFclass();
  ~egammaSFclass() {};

  std::pair<float,float> scaleFactor(float eta, int set, int range=0, int rel=0);
  std::pair<float,float> scaleFactorLoose(float eta, int range=0, int rel=0) { return scaleFactor(eta, 0, range, rel); };
  std::pair<float,float> scaleFactorMedium(float eta, int range=0, int rel=0) { return scaleFactor(eta, 1, range, rel); };
  std::pair<float,float> scaleFactorTight(float eta, int range=0, int rel=0) { return scaleFactor(eta, 2, range, rel); };

  //For the binning
  int netabins;
  std::vector<float> etabins;

  //For the scale factors of the standard egamma cuts 
  //Probes between 30 and 50 GeV (plateau region)
  std::vector<float> efficienciesLoose3050;
  std::vector<float> uncertaintyLoose3050;
  std::vector<float> efficienciesMedium3050;
  std::vector<float> uncertaintyMedium3050;
  std::vector<float> efficienciesTight3050;
  std::vector<float> uncertaintyTight3050;
  //Probes between 20 and 50 GeV
  std::vector<float> efficienciesLoose2050;
  std::vector<float> uncertaintyLoose2050;
  std::vector<float> efficienciesMedium2050;
  std::vector<float> uncertaintyMedium2050;
  std::vector<float> efficienciesTight2050;
  std::vector<float> uncertaintyTight2050;

};

#endif


