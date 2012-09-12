#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <TSystem.h>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TBranch.h"
#include "TFileCollection.h"

// first run .x load_packages.C+ to get the list of include and loads
//  gSystem->Macro("load_packages.C+");


//to run in ROOT: .x runTrigger.C
void readTrigger() {

//  gSystem->Macro("load_packages.C+");
//  gSystem->ProcessLine("x load_packages.C+");
  

gSystem->AddIncludePath("-I/data/etp4/flegger/susy/D3PDReader_p832_51/RootCore/include");
gSystem->Load("libHist");
gSystem->Load("libTree");
gSystem->Load("libTreePlayer");
gSystem->Load("libXMLParser");
gSystem->Load("libXMLIO");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_51/RootCore/lib/libMuonMomentumCorrections.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_51/RootCore/lib/libCalibrationDataInterface.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_51/RootCore/lib/libMuonEfficiencyCorrections.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_51/RootCore/lib/libegammaAnalysisUtils.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_51/RootCore/lib/libObjectSelectorCore.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_51/RootCore/lib/libJetSelectorTools.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_51/RootCore/lib/libJetResolution.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_51/RootCore/lib/libJetUncertainties.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_51/RootCore/lib/libMissingETUtility.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_51/RootCore/lib/libReweightUtils.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_51/RootCore/lib/libPileupReweighting.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_51/RootCore/lib/libegammaEvent.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_51/RootCore/lib/libGoodRunsLists.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_51/RootCore/lib/libSUSYTools.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_51/RootCore/lib/libTrigRootAnalysis.so");

  std::vector<TString> filename; 

//SU4

  TString path = "/data/etp6/flegger/";       
  //filename.push_back("mc11_7TeV.106484.SU4_herwigpp_susy.merge.NTUP_SUSY.e835_s1310_s1300_r2730_r2700_p756_tid536861_00/*.root*");
  //filename.push_back("mc11_7TeV.107650.AlpgenJimmyZeeNp0_pt20.merge.NTUP_SUSY.e835_s1299_s1300_r2730_r2700_p756_tid537153_00/*.root*");  
  //filename.push_back("mc11_7TeV.105987.WZ_Herwig.merge.NTUP_SUSY.e825_s1310_s1300_r2730_r2700_p756_tid537133_00/*.root*");
  //filename.push_back("mc11_7TeV.106484.SU4_herwigpp_susy.merge.NTUP_SUSY.e835_s1310_s1300_r2730_r2700_p756_tid536861_00/NTUP_SUSY.536861._000001.root.1"); 
  filename.push_back("data11_7TeV.00190295.physics_Egamma.merge.NTUP_EGAMMA.f408_m1007_p768_tid564472_00/d3pd_egamma.root");

   TChain *c, *c2; 
  
  cout << "Processing files: "<<filename.size()<<endl;

for (int i = 0; i < filename.size() ; i++){
    
//  c = new TChain("susy");
//  c2 = new TChain("susyMeta/TrigConfTree");
  c = new TChain("egamma");
  c2 = new TChain("egammaMeta/TrigConfTree");
    
  cout << "Opening "<<path+filename[i]<<endl;
  c->Add(path+filename[i]);
  c2->Add(path+filename[i]);

  Long64_t nentries = c->GetEntries();	 
  cout << "Getting tree with "<<nentries<<" entries"<<endl;

  nentries = c2->GetEntries();	 
  cout << "Getting conf tree with "<<nentries<<" entries"<<endl;
  
  unsigned int EF_mu6;
  c->SetBranchAddress("EF_mu18_L1J10", &EF_mu6);
  
  for (Int_t j = 0; j < (Int_t)(c->GetEntries()); j++) {      
    c->GetEntry(j);
    if (EF_mu6) cout << EF_mu6 <<endl;  
  }
  
  c->Delete();
  c2->Delete();

  cout << "done processing file "<<(i+1)<<endl;
}//end loop over all files
 
   
  cout << "All done!"<<endl;
  //gApplication->Terminate();
 
}


