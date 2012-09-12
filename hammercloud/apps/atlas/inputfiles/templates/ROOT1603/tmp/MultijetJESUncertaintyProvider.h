#ifndef _MULTIJETJESUNCERTAINTYPROVIDER_
#define _MULTIJETJESUNCERTAINTYPROVIDER_


#include "JESUncertaintyProvider.h"


class MultijetJESUncertaintyProvider : public JESUncertaintyProvider{

 public:

  // Constructors, destructor
  MultijetJESUncertaintyProvider(std::string CollectionName="AntiKt6H1TopoJets", std::string AnalysisFileName="analysis.root", std::string FileName="JESUncertainty.root");
   ~MultijetJESUncertaintyProvider();
 

  // Initialize the provider
  virtual void init();

  // Open input file
  virtual void openInputFile(std::string FileName);




  // Relative positive uncertainty - by default no pile-up term, no close-by jets systematic (dR = 3.0)
  double getRelPosUncert(double pT, double Eta, Components UncertComps = JESUncertaintyProvider::NOPILEUP, unsigned int nVtx=1, double dRmin=3.0);
  // Absolute positive uncertainty - by default no pile-up term, no close-by jets systematic (dR = 3.0)
  double getAbsPosUncert(double pT, double Eta, Components UncertComps = JESUncertaintyProvider::NOPILEUP, unsigned int nVtx=1, double dRmin=3.0);
  // Relative negative uncertainty - by default no pile-up term, no close-by jets systematic (dR = 3.0)
  double getRelNegUncert(double pT, double Eta, Components UncertComps = JESUncertaintyProvider::NOPILEUP, unsigned int nVtx=1, double dRmin=3.0);
  // Absolute negative uncertainty - by default no pile-up term, no close-by jets systematic (dR = 3.0)
  double getAbsNegUncert(double pT, double Eta, Components UncertComps = JESUncertaintyProvider::NOPILEUP, unsigned int nVtx=1, double dRmin=3.0);

  // Relative uncertainty - by default no pile-up term, no close-by jets systematic (dR = 3.0)
  // isUp = true if relative positive uncertainty is requested
  // isUp = false if relative negative uncertainty is requested
  double getRelUncert(double pT, double Eta, bool isUp, Components UncertComps = JESUncertaintyProvider::NOPILEUP, unsigned int nVtx=1, double dRmin=3.0);

  // Get a copy of the 2D Graph containing the Uncertainties
  // isUp = true if relative positive uncertainty is requested
  // isUp = false if relative negative uncertainty is requested
  // to be implemented
  TH2D* getUncGraphCopy(bool isUp, Components UncertComps, unsigned int nVtx, double dRmin);




  private:

    // Flavor response graphs
/*
  // Maximum number of flavor response components
  static const unsigned int m_nFlavorResponseUncertainties = 11;

  // Pointer to the flavor response histograms
  TH2D*  m_flavorRespGluGraph[m_nFlavorResponseUncertainties];
  TH2D*  m_flavorRespLightGraph[m_nFlavorResponseUncertainties];

  // Pointers to the pileup histograms
  TH2D*  m_pileupUncGluGraph[m_nVertices];
  TH2D*  m_pileupUncLightGraph[m_nVertices];
*/
  
  //Pointers to the flavor composition histograms
  TH2D*  m_flavorCompGluGraph;
  TH2D*  m_flavorCompLightGraph;

  //Pointer to the deltaR histogram
  TH1D*  m_deltaRGraph;

  //Pointers to the sample related histograms
  //Pointer to the gluon fraction histogram
  TH2D*  m_gluonFraction;
  //Pointer to the gluon fraction error histogram
  TH2D*  m_gluonFractionError;
  //Pointer to the response histogram
  TH2D*  m_responseSample;


  // Input File with sample related histograms(gluon fraction, gluon fraction error, sample response)
  TFile* m_analysisInputFile;

  // Name of analysis file
  std::string m_analysisFileName;
  

  

  // Count how often error message is printed
  static int m_counter;

  // Helper function to increment m_counter
  static void incrementCounter(){
  m_counter++;
 }

  // Change the inputCollection
  virtual bool setInputCollection(std::string CollectionName);

  // Helper function to check requested components (global uncertainty/flavor response uncertainty) and add up flavor composition + clpse-by jet systematic
  double getComponents(int currentBin, bool isUp, Components UncertComps, unsigned int nVtx, double dRmin);

  // Helper function to calculate prefactor alphaC
  double getAlphaC(int currentBin, bool isUp);

  // Helper function to calculate prefactor alphaR
  double getAlphaR(int currentBin, bool isUp, double alphaC, double avgResponse);

  // Helper funtion to return average response - protect against r_avg>1+Delta+ and r_avg < 1-Delta-
  double getAvgResponse(int currentBin);




};



#endif
