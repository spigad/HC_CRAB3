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
void runGanga() {

   cout << "Grid run" <<endl;
   
   char *rpath  = getenv( "PWD" );
   std::string filename = "./input.txt";

   if (!( rpath == 0 )) { // if ENV-var not set use default
     std::string path(rpath);
     filename =  path+"/input.txt";
   }

  cout << "Reading input file "<<filename<<endl;
  
  
  TChain *c = new TChain("susy");

//  TFileCollection* fc = new TFileCollection("mylist", "mylist",filename);
//  c->AddFileInfoList((TCollection*)fc->GetList());
  

  std::string argStr;

  char *filechar = filename.c_str(); 
   
  std::ifstream ifs(filechar);

  std::vector<std::string> fileList;

  // split by '\n'
  int nfiles = 0;
  while (std::getline(ifs,argStr)) {
    for (size_t i=0,n; i <= argStr.length(); i=n+1) {
      n = argStr.find_first_of('\n',i);
      if (n == std::string::npos)
        n = argStr.length();
      TString tmp = argStr.substr(i,n-i);//std::string
      nfiles++;
      cout << "Adding file "<<tmp<<" nb "<<nfiles<<endl;
      c->Add(tmp);
    }
  }

   int nentries = c->GetEntries();
   std::cout << "Total number of entries in chain (after all the files) " <<  c->GetEntries() << std::endl;

  //c->SetProof();
  c->Process("D3PDSelector.C+O");
 
  // Create AthSummary.txt for the pilot
  ofstream outf("AthSummary.txt"); 
//  outf << "Files read: " << fc->GetNFiles() << std::endl; 
  outf << "Files read: " << nfiles << std::endl; 
  outf << "Events Read: " << nentries << std::endl; 
  outf << "{ \"events\":{\"read\":" << nentries << "} "  << "}" << std::endl;
  outf.close();
  system("cp AthSummary.txt ..");
  
  c->Delete();

  cout << "All done, quitting ROOT..."<<endl;
  
  //quit root
  gApplication->Terminate();

  } 

