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
  while (std::getline(ifs,argStr)) {
    for (size_t i=0,n; i <= argStr.length(); i=n+1) {
      n = argStr.find_first_of(',',i);
      if (n == std::string::npos)
        n = argStr.length();
      TString tmp = argStr.substr(i,n-i);//std::string
      cout << "Adding file "<<tmp<<endl;
      c->Add(tmp);
    }
  }

  std::cout << "Total number of entries in chain (after all the files) " <<  c->GetEntries() << std::endl;

  //c->SetProof();
  c->Process("D3PDSelector.C+O");
  c->Delete();
  
  cout << "All done, quitting ROOT..."<<endl;
  
  //quit root
  gApplication->Terminate();

  } 

