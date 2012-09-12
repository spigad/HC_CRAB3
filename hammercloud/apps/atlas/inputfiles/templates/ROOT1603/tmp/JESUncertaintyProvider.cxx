#include "JESUncertaintyProvider.h"

// Constructor
JESUncertaintyProvider::JESUncertaintyProvider(std::string CollectionName, std::string FileName):
  m_GeV(1000.0), m_collectionName(CollectionName), m_fileName(FileName), m_isInit(false)
{
}


// Destructor
JESUncertaintyProvider::~JESUncertaintyProvider()
{
  // Close the file
  m_inputFile->Close();
  delete m_inputFile;
}


void JESUncertaintyProvider::init()
{

  //prevent multiple initializations
  if (m_isInit == false) {
       
    m_inputFile = 0;

    openInputFile(m_fileName);

    if(!m_inputFile)
      {
        std::cout << "ERROR: Input File " << m_fileName << " could not be found in the current directory" << std::endl;
      } else {
        //the flag will be set as initialized if everything goes right
        m_isInit = setInputCollection(m_collectionName);
      }
       
  }
 
}

// Open the file
void JESUncertaintyProvider::openInputFile(std::string FileName)
{
  // Open Input File
  // The ROOT file containing the uncertainty plots must be placed in the current directory for the standalone version
  m_inputFile = new TFile(FileName.c_str());
}



// Read the plots from the chosen Jet Collection
bool JESUncertaintyProvider::setInputCollection(std::string CollectionName)
{
  // Jet Collection used
  std::string suffixName;
 
  if(CollectionName == "AntiKt6H1TopoJets" || CollectionName == "AntiKt6EMJESTopoJets")
    suffixName = "_AntiKt6TopoJetsJES";
  else if(CollectionName == "AntiKt4H1TopoJets" || CollectionName == "AntiKt4EMJESTopoJets")
    suffixName = "_AntiKt4TopoJetsJES";
  else
    {
      cout << "ERROR: Name not recognized, using default AntiKt6EMJESTopoJets" << std::endl;
      suffixName = "_AntiKt6TopoJetsJES";
    }

//   std::string plotNames[m_nUncertainties] = {"DeadMaterial","PhysicsList","NoiseThresholds","Beamspot","PerugiaTune","ProfessorTune","AlpgenHerwigJimmy","TBEMScale","EtaIntercalibration", "DataMCRelResponseDifference", "PileUp","NonClosure"};

  std::string plotNames[m_nUncertainties] = {"DeadMaterial","PhysicsList","NoiseThresholds","Beamspot","PerugiaTune","ProfessorTune","AlpgenHerwigJimmy","TBEMScale","EtaIntercalibration", "MCIntercalibration", "PileUp", "NonClosure"};

  // Pull the correct uncertainty graphs
  for(unsigned int i=0; i<m_nUncertainties; i++)
    {
     
      std::string currentPlot = "";
     
      // Pileup plot (=10) is handled separately
      if (i!=10) 
        {
          // Combine names to get the right plots - CINT compatibility issue
          currentPlot = plotNames[i]+suffixName;
          m_uncGraph[i] = (TH2D*)(m_inputFile->Get(currentPlot.c_str()));
        }
     
      else 
        {
          // Default pile-up plot: no additional vertices (=empty)
          currentPlot = "PileUp"+suffixName+"_NPV_1";
          m_uncGraph[i] = (TH2D*)(m_inputFile->Get(currentPlot.c_str()));
        }
       
      if(!m_uncGraph[i])
        {
          std::cout << "ERROR: Problem finding Required Input Graph: " << currentPlot << std::endl;
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
      std::string currentPlot = "PileUp"+suffixName+"_NPV_"+string_i;
     
      m_pileupUncGraph[i] = (TH2D*)(m_inputFile->Get(currentPlot.c_str()));
     
      if(!m_pileupUncGraph[i])
        {
          std::cout << "ERROR: Problem finding Required Input Graph: " << currentPlot << std::endl;
          return false;
        }
           
    }
   
  return true;
 
}

// Absolute Uncertainty
double JESUncertaintyProvider::getAbsUncert(double pT, double Eta, Components UncertComps, unsigned int nVtx)
{
  return getRelUncert(pT, Eta, UncertComps, nVtx)*pT;
}

// Relative Uncertainty
double JESUncertaintyProvider::getRelUncert(double pT, double Eta, Components UncertComps, unsigned int nVtx)
{
  // Convert units
  pT /= m_GeV;
 
  // Protect against jets in the wrong range
  if(pT < 15 || pT > 7000)
    {
      std::cout << "ERROR: pT outside of covered range (15-7000): Returning -1" << std::endl;
      return -1;
    }
 
  // Protect against jets in the wrong region
  if(fabs(Eta) > 4.5)
    {
      std::cout << "ERROR: Eta outside of covered range (0.0-4.5): Returning -1" << std::endl;
      return -1;
    }

  // Use the last filled value in the histogram
  if(pT > 1000)
    pT = 999.;
 
  // Find the bin with the given pT, Eta value

  int currentBin = m_uncGraph[0]->FindBin(pT, fabs(Eta));
  // add uncertainties in the proper way
  return getComponents(currentBin, UncertComps, nVtx);
}

// Get a copy of the 2D Graph containing the Uncertainties
TH2D* JESUncertaintyProvider::getUncGraphCopy(Components UncertComps, unsigned int nVtx)
{
  TH2D* myPlot = (TH2D*)m_uncGraph[0]->Clone();
  myPlot->Reset("ICE");
  int nBinsX = myPlot->GetNbinsX();
  int nBinsY = myPlot->GetNbinsY();
 
  for(int g=0; g<nBinsX; g++)
    {
      for(int h=0; h<nBinsY; h++)
        {
          // Follow the math highlighted in the TH2D class
          int currentBin = (g+1)+(nBinsX+2)*(h+1);
          myPlot->SetBinContent(currentBin, getComponents(currentBin, UncertComps, nVtx));
        }
    }
  return myPlot;
}

// Construct the uncertainty from a set of components
double JESUncertaintyProvider::getComponents(int currentBin, Components UncertComps, unsigned int nVtx)
{
  // Terms which will be added in quadrature
  double quadrature(0);
  double linear(0);

  // Initialize the bitmask
  // Use int multiplication to avoid potential machine
  // precision mismatches when using the pow function
  int bitmask = 1;
 
  // Take care of picking up the right pileup contribution first: 

  // check we have enough vertices stored (return 7 if there are more vertices in the event)
  if (nVtx > m_nVertices) nVtx=7;

  // substitute the plot on the fly
  m_uncGraph[10] = m_pileupUncGraph[nVtx-1];
 
  //Loop on the uncertainties
  for(unsigned int i=0; i<m_nUncertainties; i++)
   
    {
      double currentComponent = 0;
     
      // Check if current component is requested
      if(int(UncertComps) & bitmask)
        currentComponent = m_uncGraph[i]->GetBinContent(currentBin);
     
      // Check whether uncertainties should be added in quadrature
      if(i != 11)
        quadrature += currentComponent*currentComponent;
      else
        linear += currentComponent;
     
      // Prepare the bitmask for the next iteration
      bitmask *=2;
    }
   
  return sqrt(quadrature) + linear;
 
}
