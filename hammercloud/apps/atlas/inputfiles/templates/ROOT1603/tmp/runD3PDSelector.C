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
void runD3PDSelector(int mode) {


  bool proof = false ; // mode == 1
  
  if (mode == 1) {
    cout << "Proof enabled" <<endl;
    proof = true;
  } 


  std::vector<TString> filename; 

  TString path = "/data/etp4/flegger/data/";

//SU4
  filename.push_back("mc10_7TeV.105802.JF17_pythia_jet_filter.merge.NTUP_SUSY.e577_s933_s946_r1831_r2040_p428_tid281327_00/*.root");

   
   TChain* c; 

  cout << "Processing files: "<<filename.size()<<endl;

  
for (int i = 0; i < filename.size() ; i++){
    
  c = new TChain("susy");
    
  cout << "Opening "<<path+filename[i]<<endl;
  c->Add(path+filename[i]);


/********** PROOF *********/
  if (proof){  
    p = TProof::Open(""); 
//    p->SetParallel(4);
    c->SetProof();
  }

//  c->Add(filename[i]);
  c->Process("D3PDSelector.C+O");
  c->Delete();

  cout << "done processing file "<<(i+1)<<endl;
}//end loop over all files
 
  
cout << "All done!"<<endl;
 
}



