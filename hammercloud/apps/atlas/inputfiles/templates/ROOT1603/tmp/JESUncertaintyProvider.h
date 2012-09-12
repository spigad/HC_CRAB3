///***********************************************************************
///
/// JESUncertaintyProvider
/// Main author: P.O. DeViveiros
/// Contributing authors: C. Doglioni
/// Plots by: Caterina Doglioni, David Miller, Frederik Ruehr, James Robinson
///
/// Provide a Monte Carlo based uncertainty on the Jet Energy Scale.
/// Each unique component of the uncertainty can be accessed separately.
///
/// See the Components enum below for a list of components of the JES
/// which can be accessed separately.
///
///#### Basic usage:
///#### More detailed instructions on this twiki:
///#### https://twiki.cern.ch/twiki/bin/view/AtlasProtected/JESUncertaintyProvider
///
/// 1) Include as a header in a C++ based analysis
/// 2) Create an instance, ie:
///	  JESUncertaintyProvider myJES;
/// 3) Initialize it:
///	  myJES.init() 
/// 3) Call one of the functions
///	  myJES.getRelUncert(myPt, myEta);
/// 4) By default, one gets uncertainties without
///    the pile-up term.
///
///#### Using separate terms
///
/// One can use the Components enum to access different components of the
/// JES or different combinations.
///
/// 1) Create the list of components
///	JESUncertaintyProvider::Components myComps =
///	   JESUncertaintyProvider::Components(
///	   JESUncertaintyProvider::DEADMATERIAL +
///	   JESUncertaintyProvider::PHYSICSLIST )
/// 2) Pass the list as a last parameter:
///	myJES.getRelUncert(myPt, myEta, myComps);
/// 3) One can also used pre-defined combinations
///	myJES.getRelUncert(myPt, myEta,
///	   JESUncertaintyProvider::NOPILEUP)
///
///#### Obtaining the 2D plots
///
/// Calling getUncGraphCopy will return a copy of a plot with all
/// uncertainties in pT, Eta bins. One can pass the components requested
/// as an argument.
///
///***********************************************************************
#ifndef _JESUNCERTAINTYPROVIDER_
#define _JESUNCERTAINTYPROVIDER_


#include "TFile.h"
#include "TH2D.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
using std::cout;

class JESUncertaintyProvider
{

public:

  enum Components {
    // Basic components
    DEADMATERIAL = 1,		       // Dead Material
    PHYSICSLIST = 2,		       // Physics List, QGSP & FTFP_BERT
    NOISETHRESHOLDS = 4,	       // Vary cluster thresholds by 10%
    BEAMSPOT = 8,		       // Vary nominal beamspot
    PERUGIATUNE = 16,		       // Perugia Uncerlying Event tune
    PROFESSORTUNE = 32, 	       // Professor Fragmentation tune
    HERWIGJIMMY = 64,		       // Herwig Jimmy
    EMSCALE = 128,		       // Uncertainty in Test Beam EM Scale
    ETAINTERCALIBRATION = 256,         // Uncertainty due to intercalibration (endcap wrt central region)
    MCINTERCALIBRATION = 512,	       // Uncertainty due to data/MC discrepancy or MC comparison from eta intercalibration results
    PILEUP = 1024,		       // Uncertainty due to in-time pile-up
    CLOSURE = 2048,		       // Non-closure of numerical inversion constants
   
    // Suggested combinations
    NOCLOSURE = 2047,		       // Allow users to include their own non-closure
    NOPILEUP = 3071,		       // For data with no pile-up
    NOPILEUPNOCLOSURE = 1023,	       // Data with no pile-up, no non-closure
    ALL = 4095  		       // Everything
  };
 

  // Constructors, destructor
  JESUncertaintyProvider(std::string CollectionName="AntiKt6H1TopoJets", std::string FileName="JESUncertainty.root");
   ~JESUncertaintyProvider();
 
  // Read the uncertainties off of the graph - By default, no Pile-Up term!
  double getRelUncert(double pT, double Eta, Components UncertComps = JESUncertaintyProvider::NOPILEUP, unsigned int nVtx=1);
  double getAbsUncert(double pT, double Eta, Components UncertComps = JESUncertaintyProvider::NOPILEUP, unsigned int nVtx=1);
 
  // Pass a pointer to the correct graph
  TH2D* getUncGraphCopy(Components UncertComps = JESUncertaintyProvider::NOPILEUP, unsigned int nVtx=1);

  // Initialize the provider
  virtual void init();

  // Open input file
  virtual void openInputFile(std::string FileName = "JESUncertainty.root");
 

 

 protected:

  // Change the inputCollection
  bool setInputCollection(std::string CollectionName);
 
  // Maximum number of components - does not include pileup
  static const unsigned int m_nUncertainties = 12;
 
  // Maximum number of vertices available
  static const unsigned int m_nVertices = 7;
 
  // For standalone compatibility
  const double m_GeV;
 
  // Pointers to the uncertainty histograms
  TH2D*  m_uncGraph[m_nUncertainties];

  // Pointers to the pileup histograms
  TH2D*  m_pileupUncGraph[m_nVertices];

  // Input File
  TFile* m_inputFile;

  // Helper function to check requested components
  double getComponents(int currentBin, Components UncertComps, unsigned int nVtx = 1);
 
  // Name of jet collection
  std::string m_collectionName;

  // Name of file
  std::string m_fileName;

  // Initialization flag
  bool m_isInit;
 
};


#endif
