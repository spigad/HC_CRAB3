#include "JetUncertainties/MultijetJESUncertaintyProviderAthena.h"

// Constructor
MultijetJESUncertaintyProviderAthena::MultijetJESUncertaintyProviderAthena(std::string CollectionName, std::string AnalysisFileName, std::string MJESFileName, std::string FileName):
MultijetJESUncertaintyProvider(CollectionName, AnalysisFileName, MJESFileName, FileName)
{
}

// Destructor
MultijetJESUncertaintyProviderAthena::~MultijetJESUncertaintyProviderAthena()
{
}

TFile* MultijetJESUncertaintyProviderAthena::openInputFile(std::string FileName)
{
  // This ensures we are looking in the right place (->InstallArea)
  std::string pathToFile = PathResolver::find_file (FileName, "DATAPATH");

  // Now we open the file the usual way
  return JESUncertaintyProvider::openInputFile(pathToFile);
}


