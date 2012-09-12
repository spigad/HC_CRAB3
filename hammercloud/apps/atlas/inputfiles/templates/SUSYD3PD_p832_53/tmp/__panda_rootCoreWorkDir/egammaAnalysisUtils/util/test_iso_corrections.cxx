#include <iostream>

#include "egammaAnalysisUtils/CaloIsoCorrection.h"

using namespace std;
using namespace CaloIsoCorrection;

int main(int /* argc */, char** /* argv */){

  float clusterEnergy = 100000.;
  float etaCluster = .8;
  float etaPointing = .85;
  float etaS2 = .78;
  float radius = .40;
  bool isConversion = false;
  float EtCone_val = 5000.;
  
  unsigned int nPV = 5;
  bool is_mc = false;
  
  float Etcone40 = 5000.;
  float Etcone40_ED_corrected = 4500.;


  cout << __LINE__ << "\t" << GetNPVCorrectedIsolation(nPV,
                                                       etaS2,
                                                       radius,
                                                       is_mc,
                                                       EtCone_val,
                                                       PHOTON) << endl;

  cout << __LINE__ << "\t" << GetNPVCorrectedIsolationError(nPV,
                                                       etaS2,
                                                       radius,
                                                       is_mc,
                                                       PHOTON) << endl;

  cout << __LINE__ << "\t" << GetEDCorrectedIsolation(Etcone40,
                                                      Etcone40_ED_corrected,
                                                      radius,
                                                      EtCone_val,
                                                      PHOTON) << endl;

  cout << __LINE__ << "\t" << GetPtCorrectedIsolation(clusterEnergy,
                                                      etaS2,
                                                      etaPointing,
                                                      etaCluster,
                                                      radius,
                                                      is_mc,
                                                      EtCone_val,
                                                      isConversion,
                                                      ELECTRON) << endl;

  cout << __LINE__ << "\t" << GetPtCorrectedTopoIsolation(clusterEnergy,
                                                          etaS2,
                                                          etaPointing,
                                                          etaCluster,
                                                          radius,
                                                          is_mc,
                                                          EtCone_val,
                                                          isConversion,
                                                          ELECTRON) << endl;

  cout << __LINE__ << "\t" << GetPtCorrectedIsolationError(clusterEnergy,
                                                           etaS2,
                                                           etaPointing,
                                                           etaCluster,
                                                           radius,
                                                           is_mc,
                                                           PHOTON) << endl;


  return 0;


}
