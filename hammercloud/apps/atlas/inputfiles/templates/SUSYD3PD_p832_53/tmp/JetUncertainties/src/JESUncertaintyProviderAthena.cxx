#include "JetUncertainties/JESUncertaintyProviderAthena.h"

// Constructor
JESUncertaintyProviderAthena::JESUncertaintyProviderAthena(std::string CollectionName, std::string FileName) : 
JESUncertaintyProvider(CollectionName, FileName) 
{
}

// Destructor
JESUncertaintyProviderAthena::~JESUncertaintyProviderAthena()
{
//we don't own anything anymore now!
}

TFile* JESUncertaintyProviderAthena::openInputFile(std::string FileName)
{
  // This ensures we are looking in the right place (->InstallArea)
  std::string pathToFile = PathResolver::find_file (FileName, "DATAPATH");

  // Now we open the file the usual way
  return JESUncertaintyProvider::openInputFile(pathToFile);
}


