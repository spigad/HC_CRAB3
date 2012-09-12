#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TBranch.h"
#include "TFileCollection.h"

#include <fstream> 


//to run in ROOT: .x runD3PDSelector.C
void runPanda() {

   cout << "Grid run" <<endl;

   gSystem->AddIncludePath("-I__panda_rootCoreWorkDir/RootCore/include");
   gSystem->Load("libHist");
   gSystem->Load("libTree");
   gSystem->Load("libTreePlayer");
   gSystem->Load("libXMLParser");
   gSystem->Load("libXMLIO");
   gSystem->Load("__panda_rootCoreWorkDir/RootCore/lib/libMuonMomentumCorrections.so");
   gSystem->Load("__panda_rootCoreWorkDir/RootCore/lib/libCalibrationDataInterface.so");
   gSystem->Load("__panda_rootCoreWorkDir/RootCore/lib/libMuonEfficiencyCorrections.so");
   gSystem->Load("__panda_rootCoreWorkDir/RootCore/lib/libegammaAnalysisUtils.so");
   gSystem->Load("__panda_rootCoreWorkDir/RootCore/lib/libObjectSelectorCore.so");
   gSystem->Load("__panda_rootCoreWorkDir/RootCore/lib/libJetSelectorTools.so");
   gSystem->Load("__panda_rootCoreWorkDir/RootCore/lib/libJetResolution.so");
   gSystem->Load("__panda_rootCoreWorkDir/RootCore/lib/libJetUncertainties.so");
   gSystem->Load("__panda_rootCoreWorkDir/RootCore/lib/libMissingETUtility.so");
   gSystem->Load("__panda_rootCoreWorkDir/RootCore/lib/libReweightUtils.so");
   gSystem->Load("__panda_rootCoreWorkDir/RootCore/lib/libPileupReweighting.so");
   gSystem->Load("__panda_rootCoreWorkDir/RootCore/lib/libegammaEvent.so");
   gSystem->Load("__panda_rootCoreWorkDir/RootCore/lib/libGoodRunsLists.so");
   gSystem->Load("__panda_rootCoreWorkDir/RootCore/lib/libSUSYTools.so");
   gSystem->Load("__panda_rootCoreWorkDir/RootCore/lib/libTrigRootAnalysis.so");
   
   char *rpath  = getenv( "PWD" );
   std::string filename = "./input.txt";

   if (!( rpath == 0 )) { // if ENV-var not set use default
     std::string path(rpath);
     filename =  path+"/input.txt";
   }

  cout << "Reading input file "<<filename<<endl;
  
  
  TChain *c = new TChain("susy");
  TChain* cTrig = new TChain("susyMeta/TrigConfTree");
  
//  TFileCollection* fc = new TFileCollection("mylist", "mylist",filename);
//  c->AddFileInfoList((TCollection*)fc->GetList());
  
  std::string argStr;

  char *filechar = filename.c_str(); 
   
  std::ifstream ifs(filechar);

  std::vector<std::string> fileList;

  // split by '\n'
  while (std::getline(ifs,argStr)) {
    for (size_t i=0,n; i <= argStr.length(); i=n+1) {
      n = argStr.find_first_of(',',i);
      if (n == std::string::npos)
        n = argStr.length();
      TString tmp = argStr.substr(i,n-i);//std::string
      cout << "Adding file "<<tmp<<endl;
      c->Add(tmp);
      //c->AddFriend("susyMeta/TrigConfTree", tmp);
      cTrig->Add(tmp);
    }
  }

  std::cout << "Total number of entries in chain (after all the files) " <<  c->GetEntries() << std::endl;

  //c->SetProof();
  c->AddFriend(cTrig);
  
  Long64_t nentries = c->GetEntries();    
  cout << "Getting Event tree with "<<nentries<<" entries"<<endl;

  TTree * fChainConf = c->GetFriend("susyMeta/TrigConfTree");
  nentries = fChainConf->GetEntries(); 
  cout << "Getting Trigger info tree with "<<nentries<<" entries"<<endl;
  
  //c->Process("D3PDSelector.C+O");
  c->Delete();
  
  cout << "All done, quitting ROOT..."<<endl;
  
  //quit root
  gApplication->Terminate();

  } 

