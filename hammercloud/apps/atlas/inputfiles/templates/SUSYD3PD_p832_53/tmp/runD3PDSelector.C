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


//to run in ROOT: .x runD3PDSelector.C
void runD3PDSelector(int mode) {

//  gSystem->Macro("load_packages.C+");
//  gSystem->ProcessLine("x load_packages.C+");
  
  bool proof = false ; // mode == 1
  
  if (mode == 1) {
    cout << "Proof enabled" <<endl;
    proof = true;
  } 

gSystem->AddIncludePath("-I/data/etp4/flegger/susy/D3PDReader_p832_53/RootCore/include");
gSystem->Load("libHist");
gSystem->Load("libTree");
gSystem->Load("libTreePlayer");
gSystem->Load("libXMLParser");
gSystem->Load("libXMLIO");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_53/RootCore/lib/libMuonMomentumCorrections.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_53/RootCore/lib/libCalibrationDataInterface.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_53/RootCore/lib/libMuonEfficiencyCorrections.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_53/RootCore/lib/libegammaAnalysisUtils.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_53/RootCore/lib/libObjectSelectorCore.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_53/RootCore/lib/libJetSelectorTools.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_53/RootCore/lib/libJetResolution.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_53/RootCore/lib/libJetUncertainties.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_53/RootCore/lib/libMissingETUtility.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_53/RootCore/lib/libReweightUtils.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_53/RootCore/lib/libPileupReweighting.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_53/RootCore/lib/libegammaEvent.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_53/RootCore/lib/libGoodRunsLists.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_53/RootCore/lib/libSUSYTools.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_53/RootCore/lib/libTrigRootAnalysis.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_53/RootCore/lib/libDGTriggerReweight.so");
  std::vector<TString> filename; 

//SU4

  TString path = "/data/etp6/flegger/";       
//  filename.push_back("mc11_7TeV.106484.SU4_herwigpp_susy.merge.NTUP_SUSY.e835_s1310_s1300_r3043_r2993_p832_tid655440_00/*.root*"); //MC11c
//  filename.push_back("data11_7TeV.00178044.physics_Egamma.merge.NTUP_SUSYSKIM.r2603_p659_p832_tid607456_00/*root*");
//  filename.push_back("data11_7TeV.00178047.physics_Egamma.merge.NTUP_SUSYSKIM.r2603_p659_p832_tid607457_00/*root*");
  filename.push_back("data11_7TeV.00178109.physics_Egamma.merge.NTUP_SUSYSKIM.r2603_p659_p832_tid607458_00/*root*");
//  filename.push_back("data11_7TeV.00178109.physics_Muons.merge.NTUP_SUSYSKIM.r2603_p659_p832_tid607700_00/*root*");
//  filename.push_back("data11_7TeV.00178044.physics_Muons.merge.NTUP_SUSYSKIM.r2603_p659_p832_tid607698_00/*root*");
//  filename.push_back("data11_7TeV.00178047.physics_Muons.merge.NTUP_SUSYSKIM.r2603_p659_p832_tid607699_00/*root*");
  
    
//example dcap
//  TString path = "dcap://lcg-lrz-dc41.grid.lrz-muenchen.de:22125//pnfs/lrz-muenchen.de/data/atlas/dq2/atlaslocalgroupdisk/mc10_7TeV/NTUP_SUSY/e598_s933_s946_r1831_r2040_p428/";
//  filename.push_back("mc10_7TeV.106484.SU4_herwigpp_susy.merge.NTUP_SUSY.e598_s933_s946_r1831_r2040_p428_tid277252_00/NTUP_SUSY.277252._000009.root.1");
//  path = "dcap://lcg-lrz-dcache.grid.lrz-muenchen.de/pnfs/lrz-muenchen.de/data/atlas/dq2/atlaslocalgroupdisk/data11_7TeV/NTUP_SUSY/r2603_p659_p697/";
//  filename.push_back("data11_7TeV.00180776.physics_Egamma.merge.NTUP_SUSY.r2603_p659_p697_tid511695_00/NTUP_SUSY.511695._000001.root.1");
//  filename.push_back("data11_7TeV.00180776.physics_Muons.merge.NTUP_SUSY.r2603_p659_p697_tid511782_00/NTUP_SUSY.511782._000001.root.1");

  TChain* c; 
  TChain* cTrig;
  
  cout << "Processing datasets: "<<filename.size()<<endl;

for (int i = 0; i < filename.size() ; i++){
    
  c = new TChain("susy");
  cTrig = new TChain("susyMeta/TrigConfTree");
//  c = new TChain("egamma");

  TString tmp = path+filename[i];
  
  cout << "Opening "<<tmp<<endl;
  c->Add(tmp);
  cTrig->Add(tmp);

//  c->AddFriend("egammaMeta/TrigConfTree", path+filename[i]);
// c->AddFriend("susyMeta/TrigConfTree", tmp);  // THIS DOES NOT WORK WITH PROOF
    
/********** PROOF *********/
  if (proof){  
    p = TProof::Open(""); 
//    p->SetParallel(4);
    c->SetProof();
    cTrig->SetProof();
    //gProof->SetLogLevel(2);
  }
   
  c->AddFriend(cTrig);

  Long64_t nentries = c->GetEntries();    
  cout << "Event tree has "<<nentries<<" entries"<<endl;

  TTree * fChainConf = c->GetFriend("susyMeta/TrigConfTree");
  nentries = fChainConf->GetEntries(); 
  cout << "Trigger info tree has "<<nentries<<" entries"<<endl;
    

  c->Process("D3PDSelector.C+O");
  c->Delete();

  cout << "done processing file "<<(i+1)<<endl;
}//end loop over all files
 
   
  cout << "All done!"<<endl;
  //gApplication->Terminate();
 
}


