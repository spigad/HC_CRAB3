///***********************************************************************
///
/// JESUncertaintyProviderAthena
/// Authors: P.O. DeViveiros, C. Doglioni
///
/// JESUncertaintyProvider-derived class, for use in ATHENA
///
///#### Usage:
///
///
///***********************************************************************

#ifndef _JESUNCERTAINTYPROVIDERATHENA_
#define _JESUNCERTAINTYPROVIDERATHENA_


#include "JetUncertainties/JESUncertaintyProvider.h"
#include "PathResolver/PathResolver.h"

#include "TFile.h"
#include "TH2D.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
using std::cout;

class JESUncertaintyProviderAthena : public JESUncertaintyProvider {

public:
  
  // Constructors, destructor
  JESUncertaintyProviderAthena(std::string CollectionName="AntiKt6H1TopoJets", std::string FileName="JESUncertainty.root");
  virtual ~JESUncertaintyProviderAthena();
   
  // Open input file
  virtual TFile* openInputFile(std::string FileName = "JESUncertainty.root");

  
 private:  
      
};


#endif
