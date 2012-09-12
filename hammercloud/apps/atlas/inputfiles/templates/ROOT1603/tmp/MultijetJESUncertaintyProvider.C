#include "MultijetJESUncertaintyProvider.h"

// Constructor
MultijetJESUncertaintyProvider::MultijetJESUncertaintyProvider(std::string CollectionName, std::string AnalysisFileName, std::string FileName):
JESUncertaintyProvider(CollectionName, FileName), m_analysisFileName(AnalysisFileName)
{
}

// Destructor
MultijetJESUncertaintyProvider::~MultijetJESUncertaintyProvider()
{
  // Close the file
  m_analysisInputFile->Close();
  delete m_analysisInputFile;
}


void MultijetJESUncertaintyProvider::init()
{

  // Prevent multiple initializations 
  if (m_isInit == false)
    {

    m_inputFile = 0;
    m_analysisInputFile = 0;

    // Uncertainty Provider input file
    m_inputFile = new TFile(m_fileName.c_str());
    // Analysis input file
    m_analysisInputFile = new TFile(m_analysisFileName.c_str());

    if(!m_inputFile)
      {
      std::cout << "ERROR: Input File " << m_fileName << " could not be found in the current directory" << std::endl;
      }
    if(!m_analysisInputFile)
      {
      std::cout << "ERROR: Input File " << m_analysisFileName << " could not be found in the current directory" << std::endl;
      }
    else 
      {
      // The flag will be set as initialized if everything goes right
      m_isInit = setInputCollection(m_collectionName);
      }
    }

}


// Read the plots from the chosen Jet Collection
bool MultijetJESUncertaintyProvider::setInputCollection(std::string CollectionName)
{
  // Jet Collection used
  std::string suffixName;

  if(CollectionName == "AntiKt6H1TopoJets" || CollectionName == "AntiKt6EMJESTopoJets")
    {
    suffixName = "_AntiKt6TopoJetsJES";
    }
    else if(CollectionName == "AntiKt4H1TopoJets" || CollectionName == "AntiKt4EMJESTopoJets")
    {
    suffixName = "_AntiKt4TopoJetsJES";
    }
  else
    {
    cout << "ERROR: Name not recognized, using default AntiKt6EMJESTopoJets" << std::endl;
    suffixName = "_AntiKt6TopoJetsJES";
    }


  std::string plotNames[m_nUncertainties] = {"DeadMaterial","PhysicsList","NoiseThresholds","Beamspot","PerugiaTune","ProfessorTune","AlpgenHerwigJimmy","TBEMScale","EtaIntercalibration", "MCIntercalibration", "PileUp", "NonClosure"};

  // Pull the correct global uncertainty graphs + flavor response uncertainty graphs
  for(unsigned int i=0; i<m_nUncertainties; i++)
   {

    // Global uncertainties
    std::string currentPlot = "";
    // Flavor response uncertainties light quarks
    std::string currentPlotLight="";
    // Flavor response uncertainties gluons
    std::string currentPlotGlu="";



    // Pileup plot (=10) is handled separately
    if (i!=10)  
      {
      // Combine names to get the right plots - CINT compatibility issue
      // Global uncertainties
      currentPlot = plotNames[i]+suffixName;
      // Flavor response uncertainties light quarks
      currentPlotLight = plotNames[i]+"_Light"+suffixName;
      // Flavor response uncertainties gluons
      currentPlotGlu = plotNames[i]+"_Glu"+suffixName;

      m_uncGraph[i] = (TH2D*)(m_inputFile->Get(currentPlot.c_str()));
      m_flavorRespGluGraph[i] = (TH2D*)(m_inputFile->Get(currentPlotGlu.c_str()));
      m_flavorRespLightGraph[i] = (TH2D*)(m_inputFile->Get(currentPlotLight.c_str()));
      }

    else 
      {
      // Default pile-up plot: no additional vertices (=empty)
      // Global uncertaintiy pile-up plots
      currentPlot = "PileUp"+suffixName+"_NPV_1";
      // Flavor response uncertainty light quarks pile-up plots
      currentPlotLight = "PileUp_Light"+suffixName+"_NPV_1";
      // Flavor response uncertainty gluons pile-up plots
      currentPlotGlu = "PileUp_Glu"+suffixName+"_NPV_1";

      m_uncGraph[i] = (TH2D*)(m_inputFile->Get(currentPlot.c_str()));
      m_flavorRespGluGraph[i] = (TH2D*)(m_inputFile->Get(currentPlotGlu.c_str()));
      m_flavorRespLightGraph[i] = (TH2D*)(m_inputFile->Get(currentPlotLight.c_str()));
      }

      if(!m_uncGraph[i]) 
        {
        std::cout << "ERROR: Problem finding Required Input Graph: " << currentPlot << std::endl;
        return false;
        }
      if(!m_flavorRespLightGraph[i])
        {
        std::cout << "ERROR: Problem finding Required Input Graph: " << currentPlotLight << std::endl;
        return false;
        }
      if(!m_flavorRespGluGraph[i])
        {
        std::cout << "ERROR: Problem finding Required Input Graph: " << currentPlotGlu << std::endl;
        return false;
        }
    }

  // Pull the correct vertex-dependent pileup graph
  for (unsigned int i=0; i<m_nVertices; i++) 
    {

    // Turn the index into a string for the number of vertices 
    std::ostringstream osstream;
    osstream << i+1;
    std::string string_i = osstream.str();

    // Combine names to get the right plots - CINT compatibility issue
    // Global uncertaintiy pile-up plots
    std::string currentPlot = "PileUp"+suffixName+"_NPV_"+string_i;
    // Flavor response uncertainty light quarks pile-up plots (remove?)
    std::string currentPlotLight = "PileUp_Light"+suffixName+"_NPV_"+string_i;
    // Flavor response uncertainty gluons pile-up plots (remove?)
    std::string currentPlotGlu = "PileUp_Glu"+suffixName+"_NPV_"+string_i;

    m_pileupUncGraph[i] = (TH2D*)(m_inputFile->Get(currentPlot.c_str()));
    m_pileupUncGluGraph[i] = (TH2D*)(m_inputFile->Get(currentPlotGlu.c_str()));
    m_pileupUncLightGraph[i] = (TH2D*)(m_inputFile->Get(currentPlotLight.c_str()));


    if(!m_pileupUncGraph[i]) 
       {
       std::cout << "ERROR: Problem finding Required Input Graph: " << currentPlot << std::endl;
       return false;
       }
    if(!m_pileupUncGluGraph[i]) 
      {
      std::cout << "ERROR: Problem finding Required Input Graph: " << currentPlotGlu << std::endl;
      return false;
      }
    if(!m_pileupUncLightGraph[i]) 
      {
      std::cout << "ERROR: Problem finding Required Input Graph: " << currentPlotLight << std::endl;
      return false;
      }

    }


  // Pull the correct flavor composition graph

  // Gluon flavor composition graph
  m_flavorCompGluGraph = (TH2D*)(m_inputFile->Get(("flavorCompGlu"+suffixName).c_str()));

  if(!m_flavorCompGluGraph) 
    {
    std::cout << "ERROR: Problem finding Required Input Graph: " << ("flavorCompGlu"+suffixName).c_str() << std::endl;
    return false;
    }

  // Light quark flavor composition graph
  m_flavorCompLightGraph = (TH2D*)(m_inputFile->Get(("flavorCompLight"+suffixName).c_str()));

  if(!m_flavorCompLightGraph) 
    {
    std::cout << "ERROR: Problem finding Required Input Graph: " << ("flavorCompLight"+suffixName).c_str() << std::endl;
    return false;
    }


  // Pull the correct deltaR graph
  m_deltaRGraph = (TH1D*)(m_inputFile->Get(("deltaR"+suffixName).c_str()));

  if(!m_deltaRGraph) 
    {
    std::cout << "ERROR: Problem finding Required Input Graph: " <<  ("deltaR"+suffixName).c_str() << std::endl;
    return false;
    }


  // Analysis sample graphs


  // Pull the correct gluon fraction graph
  m_gluonFraction = (TH2D*)(m_analysisInputFile->Get(("gluonFraction"+suffixName).c_str()));

  if(!m_gluonFraction) 
    {
    std::cout << "ERROR: Problem finding Required Input Graph: " <<  ("gluonFraction"+suffixName).c_str() << std::endl;
    }

  // Pull the correct gluon fraction error graph
  m_gluonFractionError= (TH2D*)(m_analysisInputFile->Get(("gluonFractionError"+suffixName).c_str()));

  if(!m_gluonFractionError)
    {
    std::cout << "ERROR: Problem finding Required Input Graph: " <<  ("gluonFractionError"+suffixName).c_str() << std::endl;
    }

  // If gluon fraction or gluon fraction error graph/s is/are missing -> use default gluonFraction and gluonFractionError graphs provided in input file "JESUncertainty.root" instead -> this will set gluon fraction = gluon fraction error = 0.5 resulting in alphaC=alphaR=1 when calling getAlphaC() and getAlphaR() later in the code
  if(!m_gluonFraction || !m_gluonFractionError)
    {
    std::cout << "ERROR: Provide graphs " << ("gluonFraction"+suffixName).c_str() << " and " << ("gluonFractionError"+suffixName).c_str() << " in input file " <<  m_analysisFileName.c_str() << "!" << std::endl;
    std::cout << "Not enough information available to calculate prefactors alphaC and alphaR: Setting alphaC = alphaR = 1!" << std::endl;

    m_gluonFraction = (TH2D*)(m_inputFile->Get(("gluonFractionDefault"+suffixName).c_str()));
    m_gluonFractionError= (TH2D*)(m_inputFile->Get(("gluonFractionErrorDefault"+suffixName).c_str()));

    }



  // Pull the correct response graph
  m_responseSample= (TH2D*)(m_analysisInputFile->Get(("responseSample"+suffixName).c_str()));


  // If the response graph is not available pull the default graph provided in input file "JESUncertainty.root" -> this will set r_avg = 1
  if(!m_responseSample) 
    {
    std::cout << "ERROR: Problem finding Required Input Graph: " <<  ("responseSample"+suffixName).c_str() << std::endl;
    std::cout << "Provide graph " << ("responseSample"+suffixName).c_str() << " in input file " <<  m_analysisFileName.c_str() << "! Setting average response = 1!" << std::endl;

    m_responseSample= (TH2D*)(m_inputFile->Get(("responseSampleDefault"+suffixName).c_str()));

    }


  return true;
}


// Relative positive uncertainty
double MultijetJESUncertaintyProvider::getRelPosUncert(double pT, double Eta, Components UncertComps, unsigned int nVtx, double dRmin)
{
  return getRelUncert(pT, Eta, true, UncertComps, nVtx, dRmin);
}

// Absolute positive uncertainty 
double MultijetJESUncertaintyProvider::getAbsPosUncert(double pT, double Eta, Components UncertComps, unsigned int nVtx, double dRmin)
{
  return getRelPosUncert(pT, Eta, UncertComps, nVtx, dRmin)*pT;
}

// Relative negative uncertainty
double MultijetJESUncertaintyProvider::getRelNegUncert(double pT, double Eta, Components UncertComps, unsigned int nVtx, double dRmin)
{
  return getRelUncert(pT, Eta, false, UncertComps, nVtx, dRmin);
}

// Absolute negative uncertainty
double MultijetJESUncertaintyProvider::getAbsNegUncert(double pT, double Eta, Components UncertComps, unsigned int nVtx, double dRmin)
{
  return getRelNegUncert(pT, Eta, UncertComps, nVtx, dRmin)*pT;
}



// Relative Uncertainty (returns relative positive/negative uncertainty according to updown=true/false)
double MultijetJESUncertaintyProvider::getRelUncert(double pT, double Eta, bool isUp, Components UncertComps, unsigned int nVtx, double dRmin)
{


  // Convert units
  pT /= m_GeV;

  // Protect against jets in the wrong range
  if(pT < 20 || pT > 7000)
    {
    std::cout << "ERROR: pT outside of covered range (20-7000): Returning -1" << std::endl;
    return -1;
    }

	// Protect against jets in the wrong region
  if(fabs(Eta) > 2.9)
    {
    std::cout << "ERROR: Eta outside of covered range (0.0-2.9): Returning -1" << std::endl;
    return -1;
    }

  // Use the last filled value in the histogram
  if(pT > 500)
  pT = 499.;
  if(fabs(Eta)>2.8)
  Eta=2.79;

  // Find the bin with the given pT, Eta value
  int currentBin = m_uncGraph[0]->FindBin(pT, fabs(Eta));

  return getComponents(currentBin, isUp, UncertComps, nVtx, dRmin);

}



// Get a copy of the 2D Graph containing the Uncertainties - to be implemented
TH2D* MultijetJESUncertaintyProvider::getUncGraphCopy(bool isUp, Components UncertComps, unsigned int nVtx, double dRmin)
{
  TH2D* myPlot = (TH2D*)m_uncGraph[0]->Clone();
  myPlot->Reset("ICE");

  std::cout << "ERROR: TH2D* MultijetJESUncertaintyProvider::getUncGraphCopy(bool isUp, Components UncertComps, unsigned int nVtx, double dRmin) not implemented. Returning empty graph!" << std::endl;

  return myPlot;
}


// Check requested components (global uncertainty/flavor response uncertainty) and add up flavor composition + close-by jet systematic
double MultijetJESUncertaintyProvider::getComponents(int currentBin, bool isUp, Components UncertComps, unsigned int nVtx, double dRmin)
{

  // Uncertainty components to be added
  double globalUnc(0);
  double flavComp(0);
  double closeBy(0);

  // Average response in analysis sample
  double avgResponse =  getAvgResponse(currentBin);

  // Prefactors alphaC and alphaR -> need them for flavor composition uncertainty and flavor response uncertainty
  double alphaC = getAlphaC(currentBin, isUp);
  double alphaR = getAlphaR(currentBin, isUp, alphaC, avgResponse);




  // Global uncertainty + flavor response uncertainty

  // Choose the correct flavor response graph (light quark response uncertainty graph if positive uncertainty (isUp) is requested, else choose gluon response uncertainty graph)
  TH2D** flavorResponseGraph = isUp ? m_flavorRespLightGraph  : m_flavorRespGluGraph;

  // Terms which will be added in quadrature
  double quadrature(0);
  // Terms which will be added linearly
  double linear(0);

  // Initialize the bitmask 
  // Use int multiplication to avoid potential machine 
  // precision mismatches when using the pow function
  int bitmask = 1;


  // Take care of picking up the right pileup contribution first:  

  // Check we have enough vertices stored (return 7 if there are more vertices in the event)
  if (nVtx > m_nVertices) nVtx=7;

  // Substitute the plot on the fly
  // not implemented for response uncertainty pile-up plots so far (empty pile-up graphs for nVtx1-7)
  m_uncGraph[10] = m_pileupUncGraph[nVtx-1];


  //Loop on the uncertainties
  for(unsigned int i=0; i<m_nUncertainties; i++)
    {
    double currentComponent = 0;

    // Check if current component is requested
    if(int(UncertComps) & bitmask)

    // Combine global and flavor response uncertainties
    currentComponent = m_uncGraph[i]->GetBinContent(currentBin)+alphaR*flavorResponseGraph[i]->GetBinContent(currentBin);

    // Check whether uncertainties should be added in quadrature
    if(i != 11)
    quadrature += currentComponent*currentComponent;
    else
    linear += currentComponent;

    // Prepare the bitmask for the next iteration
    bitmask *=2;
    }

  globalUnc =  sqrt(quadrature) + linear;

  // Flavor composition uncertainty 

  // Choose the correct sign (+1 if positive error is requested, -1 if negative error is requested)
  int plusMinus = isUp ? 1  : -1;

  // Choose the correct flavor composition graph (light quark flavor composition graph if positive uncertainty (isUp) is requested, else choose gluon composition graph)
  TH2D* flavorCompGraph = isUp ? m_flavorCompLightGraph  : m_flavorCompGluGraph;

  flavComp = alphaC*(flavorCompGraph->GetBinContent(currentBin)+plusMinus*(1-avgResponse))/avgResponse;



  // Close-by jet uncertainty

  closeBy = m_deltaRGraph->Interpolate(dRmin);

//  std::cout << globalUnc << " " << closeBy << " " << flavComp <<  " " << alphaC << " " << alphaR << " " << sqrt(pow(globalUnc,2)+pow(flavComp,2)+pow(closeBy,2)) << std::endl;


  // Add the uncertainties in quadrature
  return sqrt(pow(globalUnc,2)+pow(flavComp,2)+pow(closeBy,2));


}


// Prefactor alphaC
double MultijetJESUncertaintyProvider::getAlphaC(int currentBin, bool isUp){

  // Get the correct gluon fraction
  double gluonFrac = m_gluonFraction->GetBinContent(currentBin);
  // Get the correct gluon fraction error
  double gluonFracUnc = m_gluonFractionError->GetBinContent(currentBin);


  // Protect against gluon fraction error > gluon fraction
  if(gluonFracUnc > gluonFrac)
    {
    gluonFracUnc=gluonFrac;
    std::cout << "WARNING: gluon fraction error > gluon fraction in pt/eta-bin " << currentBin << ": setting gluon fraction error = gluon fraction" << std::endl;
    std::cout << "--> Check TH2D gluonFraction and TH2D gluonFractionError in input file " <<  m_analysisFileName.c_str() << "!" << std::endl;
    }


  // Make sure gluon fraction != 1,0 -> avoid division by zero by setting alphaC=1
  if(gluonFrac == 1 || gluonFrac ==0){
    std::cout << "WARNING: gluon fraction = " << gluonFrac << "in pt/eta-bin " << currentBin << ": setting alphaC = 1 to avoid division by zero!" << std::endl;
    return 1;
  }

  // Check if positive alphaC (isUp) is requested
  if(isUp){return gluonFracUnc/gluonFrac;}

  // Else return negative alphaC (!isUp)
  else return gluonFracUnc/(1-gluonFrac);

}

// Prefactor alphaR
double MultijetJESUncertaintyProvider::getAlphaR(int currentBin, bool isUp, double alphaC, double avgResponse){


  double alphaR = alphaC;


  // Modify alphaR if average response >= 1 and positive error is requested (isUp)
  if(avgResponse >=1 && isUp)
    {
    alphaR=alphaR+(1-alphaR)*(avgResponse-1)/(m_flavorCompLightGraph->GetBinContent(currentBin));
    }

  // Modify alphaR if average response <= 1 and negative error is requested (!isUp)
  else if(avgResponse <=1 && !isUp)
    {
    alphaR=alphaR+(1-alphaR)*(1-avgResponse)/(m_flavorCompGluGraph->GetBinContent(currentBin));
    }	

  return alphaR;

}

// Average response in analysis sample
double MultijetJESUncertaintyProvider::getAvgResponse(int currentBin){

  double avgResponse =  m_responseSample->GetBinContent(currentBin);

  // Protect against avgerage response > light quark jet response (=1+Delta+)
  if(avgResponse > 1+m_flavorCompLightGraph->GetBinContent(currentBin))
    {
    std::cout << "WARNING: average response > light quark jet response in pt/eta-bin " << currentBin << ": settint average response = light quark jet response" << std::endl;
    std::cout << "--> Check TH2D responseSample in input file " <<  m_analysisFileName.c_str() << "!" << std::endl;
    avgResponse =  1+m_flavorCompLightGraph->GetBinContent(currentBin);
    }


  // Protect against avgerage response < gluon jet response (=1-Delta-)
  else if(avgResponse < 1-m_flavorCompGluGraph->GetBinContent(currentBin))
    {
    std::cout << "WARNING: average response < gluon jet response in pt/eta-bin " << currentBin << ": settint average response = gluon jet response" << std::endl;
    std::cout << "--> Check TH2D responseSample in input file " <<  m_analysisFileName.c_str() << "!" << std::endl;
    avgResponse =  1-m_flavorCompGluGraph->GetBinContent(currentBin);
    }

  return avgResponse;

}
