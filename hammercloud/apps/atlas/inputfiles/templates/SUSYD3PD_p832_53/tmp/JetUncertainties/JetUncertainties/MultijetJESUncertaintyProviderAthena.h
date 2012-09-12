///***********************************************************************
///
/// MultijetJESUncertaintyProviderAthena
/// Authors: P.O. DeViveiros, C. Doglioni
///
/// MultijetJESUncertaintyProvider-derived class, for use in ATHENA
///
///#### Usage:
///
///
///***********************************************************************

#ifndef _MULTIJETJESUNCERTAINTYPROVIDERATHENA_
#define _MULTIJETJESUNCERTAINTYPROVIDERATHENA_


#include "JetUncertainties/MultijetJESUncertaintyProvider.h"
#include "PathResolver/PathResolver.h"

#include "TFile.h"
#include "TH2D.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
using std::cout;

class MultijetJESUncertaintyProviderAthena : public MultijetJESUncertaintyProvider {

public:
  
  // Constructors, destructor
  MultijetJESUncertaintyProviderAthena(std::string CollectionName="AntiKt6TopoJetsEM", std::string AnalysisFileName="MJESUncertainty.root", std::string MJESFileName="MJESUncertainty.root", std::string FileName="JESUncertainty.root");
  ~MultijetJESUncertaintyProviderAthena();
   
  // Open input file
  virtual TFile* openInputFile(std::string FileName = "JESUncertainty.root");
  
 private:  
      
};


#endif
