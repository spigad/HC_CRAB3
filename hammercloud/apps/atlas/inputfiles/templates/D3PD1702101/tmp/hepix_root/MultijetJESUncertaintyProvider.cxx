#include "MultijetJESUncertaintyProvider.h"

int MultijetJESUncertaintyProvider::m_counter=0;



// Constructor
MultijetJESUncertaintyProvider::MultijetJESUncertaintyProvider(std::string CollectionName, std::string AnalysisFileName, std::string FileName):
JESUncertaintyProvider(CollectionName, FileName), m_analysisFileName(AnalysisFileName)
{
}

// Destructor
MultijetJESUncertaintyProvider::~MultijetJESUncertaintyProvider()
{
  // Close the files
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
    JESUncertaintyProvider::openInputFile(m_fileName);
    // Analysis input file
    openInputFile(m_analysisFileName);

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



// Open the analysis file 
void MultijetJESUncertaintyProvider::openInputFile(std::string FileName)
{
  // Open Input File
  // The ROOT file containing the uncertainty plots must be placed in the current directory for the standalone version
  m_analysisInputFile = new TFile(FileName.c_str());
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
 


  //set JESUncertaintyProvider input collection...and continue with multijet plots if everything goes right
  if(!(JESUncertaintyProvider::setInputCollection(CollectionName))) return false;

  // Flavor response uncertainty graphs - flavor response uncertainty currently removed in getComponents() (leave the code in for the moment in case flavor response uncertainty should be readded)
  
/*  
    std::string plotNames[m_nFlavorResponseUncertainties] = {"DeadMaterial","NoiseThresholds","Beamspot","PerugiaTune","ProfessorTune","AlpgenHerwigJimmy","EtaIntercalibration", "MCIntercalibration", "PileUp", "NonClosure","PhysicsList"};
  
  for(unsigned int i=0; i<m_nFlavorResponseUncertainties; i++)
   {

    // Flavor response uncertainties light quarks
    std::string currentPlotLight="";
    // Flavor response uncertainties gluons
    std::string currentPlotGlu="";



    // Pileup plot (=8) is handled separately
    if (i!=8)  
      {
      // Combine names to get the right plots - CINT compatibility issue

      // Flavor response uncertainties light quarks
      currentPlotLight = plotNames[i]+"_Light"+suffixName;
      // Flavor response uncertainties gluons
      currentPlotGlu = plotNames[i]+"_Glu"+suffixName;


      m_flavorRespGluGraph[i] = (TH2D*)(m_inputFile->Get(currentPlotGlu.c_str()));
      m_flavorRespLightGraph[i] = (TH2D*)(m_inputFile->Get(currentPlotLight.c_str()));
      }

    else 
      {
      // Default pile-up plot: no additional vertices (=empty)

      // Flavor response uncertainty light quarks pile-up plots
      currentPlotLight = "PileUp_Light"+suffixName+"_NPV_1";
      // Flavor response uncertainty gluons pile-up plots
      currentPlotGlu = "PileUp_Glu"+suffixName+"_NPV_1";


      m_flavorRespGluGraph[i] = (TH2D*)(m_inputFile->Get(currentPlotGlu.c_str()));
      m_flavorRespLightGraph[i] = (TH2D*)(m_inputFile->Get(currentPlotLight.c_str()));
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

    // Flavor response uncertainty light quarks pile-up plots (remove?)
    std::string currentPlotLight = "PileUp_Light"+suffixName+"_NPV_"+string_i;
    // Flavor response uncertainty gluons pile-up plots (remove?)
    std::string currentPlotGlu = "PileUp_Glu"+suffixName+"_NPV_"+string_i;


    m_pileupUncGluGraph[i] = (TH2D*)(m_inputFile->Get(currentPlotGlu.c_str()));
    m_pileupUncLightGraph[i] = (TH2D*)(m_inputFile->Get(currentPlotLight.c_str()));



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
*/

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
    std::cout << "ERROR: Problem finding Required Input Graph: " <<  ("gluonFraction"+suffixName).c_str() <<  " in input file " <<  m_analysisFileName.c_str() << std::endl;
    }

  // Pull the correct gluon fraction error graph
  m_gluonFractionError= (TH2D*)(m_analysisInputFile->Get(("gluonFractionError"+suffixName).c_str()));

  if(!m_gluonFractionError)
    {
    std::cout << "ERROR: Problem finding Required Input Graph: " <<  ("gluonFractionError"+suffixName).c_str() << " in input file " <<  m_analysisFileName.c_str() << std::endl;
    }

  // If gluon fraction or gluon fraction error graph/s is/are missing -> use default gluonFraction and gluonFractionError graphs provided in input file "JESUncertainty.root" instead -> this will set gluon fraction = gluon fraction error = 0.5 resulting in alphaC=alphaR=1 when calling getAlphaC() and getAlphaR() later in the code
  if(!m_gluonFraction || !m_gluonFractionError)
    {

    std::cout << "Not enough information to calculate prefactors alphaC and alphaR: Setting alphaC = alphaR = 1!" << std::endl;

    m_gluonFraction = (TH2D*)(m_inputFile->Get(("gluonFractionDefault"+suffixName).c_str()));
    m_gluonFractionError= (TH2D*)(m_inputFile->Get(("gluonFractionErrorDefault"+suffixName).c_str()));


    }



  // Pull the correct response graph
  m_responseSample= (TH2D*)(m_analysisInputFile->Get(("responseSample"+suffixName).c_str()));


  // If the response graph is not available pull the default graph provided in input file "JESUncertainty.root" -> this will set r_avg = 1
  if(!m_responseSample) 
    {
    std::cout << "ERROR: Problem finding Required Input Graph: " <<  ("responseSample"+suffixName).c_str() <<  " in input file " <<  m_analysisFileName.c_str() << "! Setting average response = 1!" << std::endl;

    // Use default response graph
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
  //NOTE: for pT < 20 GeV the MultijetJESUncertaintyProvider takes the corresponding flavor composition uncertainties from the 20GeV<pT<30GeV bin (see flavor composition graphs in JESUncertainty.root)
  if(pT < 15 || pT > 7000)
    {
    std::cout << "ERROR: pT outside of covered range (20GeV-7000GeV): Returning -1" << std::endl;
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

  
  std::cout << "ERROR: function not implemented. Returning empty graph!" << std::endl;

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

  // Prefactor alphaC (->flavor composition uncertainty)
  double alphaC = getAlphaC(currentBin, isUp);


  // Pick up base uncertainty from JESUncertaintyProvider
  globalUnc = JESUncertaintyProvider::getComponents(currentBin, UncertComps, nVtx);

  // Flavor composition uncertainty 

  // Choose the correct sign (+1 if positive error is requested, -1 if negative error is requested)
  int plusMinus = isUp ? 1  : -1;

  // Choose the correct flavor composition graph (light quark flavor composition graph if positive uncertainty (isUp) is requested, else choose gluon composition graph)
  TH2D* flavorCompGraph = isUp ? m_flavorCompLightGraph  : m_flavorCompGluGraph;

  flavComp = alphaC*(flavorCompGraph->GetBinContent(currentBin)+plusMinus*(1-avgResponse))/avgResponse;


  // Close-by jet uncertainty

  closeBy = m_deltaRGraph->Interpolate(dRmin);


  // Add the uncertainties in quadrature
  return sqrt(pow(globalUnc,2)+pow(flavComp,2)+pow(closeBy,2));


}


// Prefactor alphaC
double MultijetJESUncertaintyProvider::getAlphaC(int currentBin, bool isUp){

  // Get the correct light quark (isUp) or gluon (!isUp) fraction
  double fraction = isUp ? (1-m_gluonFraction->GetBinContent(currentBin)) : m_gluonFraction->GetBinContent(currentBin);
  // Get the correct fraction error
  double fracUnc = m_gluonFractionError->GetBinContent(currentBin);


  // Make sure (1-fraction) != 0 -> avoid division by zero by setting alphaC=1
  if((1-fraction)==0){
    std::cout << "WARNING: gluon fraction = " << m_gluonFraction->GetBinContent(currentBin) << "in pt/eta-bin " << currentBin << ": setting alphaC = 1 to avoid division by zero!" << std::endl;
    return 1;
  }

  // Make sure fracUnc <= (1-fraction) (otherwise alphaC > 1!)
  if(fracUnc > (1-fraction))
    {
    fracUnc = (1-fraction);
    }

    return fracUnc/(1-fraction);


}

// Prefactor alphaR (->flavor response uncertainty)
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
    if (m_counter < 10)
      {
      std::cout << "WARNING: average response > light quark jet response in pt/eta-bin " << currentBin << ": setting average response = light quark jet response" << std::endl;
      std::cout << "--> Check input graph responseSample in file " <<  m_analysisFileName.c_str() << "!" << std::endl;
      }
    if (m_counter == 10)
      {
      std::cout << "WARNING: average response > light quark jet response in pt/eta-bin " << currentBin << ": setting average response = light quark jet response" << std::endl;
      std::cout << "--> Check input graph responseSample in file " <<  m_analysisFileName.c_str() << "! (last message)" << std::endl;
      }
    incrementCounter();
    avgResponse =  1+m_flavorCompLightGraph->GetBinContent(currentBin);
    }


  // Protect against avgerage response < gluon jet response (=1-Delta-)
  else if(avgResponse < 1-m_flavorCompGluGraph->GetBinContent(currentBin))
    {
    if (m_counter < 10)
      {
      std::cout << "WARNING: average response < gluon jet response in pt/eta-bin " << currentBin << ": setting average response = gluon jet response" << std::endl;
      std::cout << "--> Check input graph responseSample in file " <<  m_analysisFileName.c_str() << "!" << std::endl;
      }
    if (m_counter == 10)
      {
      std::cout << "WARNING: average response < gluon jet response in pt/eta-bin " << currentBin << ": setting average response = gluon jet response" << std::endl;
      std::cout << "--> Check input graph responseSample in file " <<  m_analysisFileName.c_str() << "! (last message)" << std::endl;
      }
    incrementCounter();
    avgResponse =  1-m_flavorCompGluGraph->GetBinContent(currentBin);
    }

  return avgResponse;

}


