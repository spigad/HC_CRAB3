//This macro prints the cutflow for the 1-muon channel and for the 1-electron channel
//It refers to the SUSYObjDef class
//author: Jeanette Lorenz (jeanette.miriam.lorenz@cern.ch)

#define Reco_dpd2_cxx
#include "SUSYTools/Reco_dpd2.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include<iostream>
#include <TMatrixD.h>
#include <TVectorD.h>
#include <TH1F.h>
#include <TLorentzVector.h>
#include <TVector2.h>
#include <TSystem.h>
#include <TChain.h>
#include <TString.h>
#include <TTree.h>
#include <TLegend.h>
#include <TRandom2.h>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <exception>
#include "egammaAnalysisUtils/checkOQ.h"
//#include "SUSYTools/SmearingClass.h"
//#include "StacoCBScaleEffFactors.h" 
//#include "egammaSFclass.h"
#include "SUSYTools/SUSYObjDef.h"
#include "SUSYTools/JetID.hpp"
//#include "/pclmu8_home/jlorenz/SUSYTools3/AnalysisCommon/PileupReweighting/PileupReweighting/TPileupReweighting.h"
//#include "data11_7TeV.periodAllYear_DetStatus-v21-pro08-06_CoolRunQuery-00-03-98_Susy.h"


using namespace std;
//using namespace SUSY;

//gROOT->Reset();
/*
  int main(){
  Reco_dpd2 t;
  t.Loop();

  return EXIT_SUCCESS;
  }
*/


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//main program
/*
BE CAREFUL: You need a GRL xml-file to run it!
In order to take into account the different directory structure on the Grid and local, path to ROOTCORE level (== where all your packages are) and to SUSYTools directory are hardcoded
trgwgt: use reweighting method for muon triggers instead of scale factors
DATA: set true if you want to run over data
QCD_loose: set to true if you want to use the loose definition in order to fake and real efficiencies - NOTE: ONLY implemented for MUON channel
QCDestimate: flag in order to fill the QCD weights coming from the FakeLeptBkg in histogram for a QCDestimate from data (needs FakeLeptBkg package, therefore commented by default) 
- don't forget to add a Link in the Makefile in the SUSYTools when using it! - NOTE: ONLY implemented for MUON channel!
JESUP,JESDOWN,JER: activates jet systematics
muonsmearing: not yet implemented correctly -> still to come
 */

//void Reco_dpd2::Loop(const std::string &argStr)
void Reco_dpd2::Loop(const std::string &argStr, string path_to_Rootcore, string path_to_SUSYTools, bool trgwgt, bool DATA, bool QCD_loose, bool QCDestimate, bool JESUP, bool JESDOWN, bool JER, string muonsmearing)
{

  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  //First part: Read in file list
  /*
  std::string argStr;

  char buf[256+1];
  unsigned int delpos;
  std::ifstream ifs("input.txt");
  while (true)
    {
      ifs.read(buf,256);
      if (ifs.eof())
        {
          if (ifs.gcount() == 0) break;
          delpos = ifs.gcount()-1;
        }
      else
        {
          delpos = ifs.gcount();
        }
      buf[delpos] = 0x00;
      argStr += buf;
    }
  */

  //std::cin >> argStr;

  // split by ','
  std::vector<std::string> fileList;
  for (size_t i=0,n; i <= argStr.length(); i=n+1)
    {
      n = argStr.find_first_of(',',i);
      if (n == string::npos)
        n = argStr.length();
      std::string tmp = argStr.substr(i,n-i);
      std::string ttmp;
      for(unsigned int j=0; j<tmp.size(); j++)
	{
	  //if job is Grid job: filelist may not contain any additional '\n' as this would results in problems while trying to open the files
	  if(tmp[j]==' ' || tmp[j]=='\n') continue;
	  ttmp+=tmp[j];
	}
      fileList.push_back(ttmp);
    }

  // open input files
  TChain * chain = new TChain("susy","");
  int success = 0;
  for (unsigned int iFile=0; iFile<fileList.size(); ++iFile)
    {
      //fileList[iFile] = "../../"+fileList[iFile];
      std::cout << "open " << fileList[iFile].c_str() << std::endl;
      success = chain->AddFile(fileList[iFile].c_str(),-1);
      if (success == 0) cerr << "File " << fileList[iFile].c_str() << " could not be opened!" << endl;
    }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  //Init tree

  TTree *tree;
  tree = chain;
  Init(tree);

#ifdef USEPILEUP
  //pileup reweighting tool
  int pileup = 1; //if you want to apply reweighting pileup = 1
  if ( pileup == 1 ){ //&& gSystem->Load("../../../AnalysisCommon/PileupReweighting/StandAlone/libPileupReweighting.so") == 0){

    bool tool_failure = false;

    elPileUpTool = new Root::TPileupReweighting( "elPileUpTool" );
    elPileUpTool->AddConfigFile(path_to_Rootcore+"PileupReweighting/share/mc11b_defaults.prw.root");
    elPileUpTool->AddLumiCalcFile(path_to_SUSYTools+"data/susy_1Electron_avgintperbx.root");
    elPileUpTool->SetUnrepresentedDataAction(2);
    tool_failure = elPileUpTool->Initialize();
    if (tool_failure) cout << "El PileUpTool failed to initialise!" << endl;

    muPileUpTool = new Root::TPileupReweighting( "muPileUpTool" );
    muPileUpTool->AddConfigFile(path_to_Rootcore+"PileupReweighting/share/mc11b_defaults.prw.root");
    muPileUpTool->AddLumiCalcFile(path_to_SUSYTools+"data/susy_1Muon_avgintperbx.root");
    muPileUpTool->SetUnrepresentedDataAction(2);
    tool_failure = muPileUpTool->Initialize();
    if (tool_failure) cout << "Muon PileUpTool failed to initialise!" << endl;
   
  }
#endif

  std::string curr_file;
  int filecount(0);

  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  ///////////////////////////////////////////////////////////////////////////////////////////
  //Second part: Definitions: output file

  TString two="output.root";
  if (DATA && !QCD_loose) two="output_DATA.root";  
  if (!DATA && QCD_loose) two="output_loose.root";
  if (DATA && QCD_loose) two="output_looseDATA.root";  
  if (QCDestimate) two="output_QCD.root";  
  if (JESUP) two="outputJESUP.root";
  if (JESDOWN) two="outputJESDOWN.root";
  if (JER) two="outputJER.root";
  if (muonsmearing=="MSLOW") two="outputMSLOW.root";
  if (muonsmearing=="MSUP") two="outputMSUP.root";
  if (muonsmearing=="IDLOW") two="outputIDLOW.root";
  if (muonsmearing=="IDUP") two="outputIDUP.root";    
  TFile outputfile(two,"recreate");
  std::ofstream ofs("output2.txt");
  cout << "Create output file " << two << endl;

  //cutflow histogram...

  TH1F *histo_cutflow_muon = new TH1F("cutflow_muon","cutflow_muon", 15, 0., 15.);
  TH1F *histo_cutflow_elec = new TH1F("cutflow_elec","cutflow_elec", 15, 0., 15.);

  //matrix method histograms

  TH2D *histo_metd0Sig = new TH2D("metd0Sig","metd0Sig", 100, 0., 2., 300, 0., 300000.);
  TH1F *histo_d0sig = new TH1F("d0sig","d0sig", 100, 0., 2.);
  TH2D *histo_mtmet = new TH2D("mtmet","mtmet", 300, 0., 300000., 300, 0., 300000.);
  TH2D *histo_mtmet_afterd0 = new TH2D("mtmet_afterd0","mtmet_afterd0", 300, 0., 300000., 300, 0., 300000.);
  TH1F *histo_met = new TH1F("met","met",10, 0., 100000.);
  TH1F *histo_mt = new TH1F("mt","mt",300, 0., 300000.);
  TH1F *histo_pt = new TH1F("pt","pt",300, 0., 300000.);
  TH1F *histo_meff = new TH1F("meff","meff",1800, 0., 1800000.);
  TH1F* hist_njets = new TH1F("njets","njets", 10, 0., 10.);
  TH1F* hist_eta_afterd0 = new TH1F("eta_afterd0","eta_afterd0", 10,-2.5,2.5);
  TH1F* hist_eta_lowMET = new TH1F("eta_lowMET","eta_lowMET", 10,-2.5,2.5);
  TH1F* hist_eta_WT = new TH1F("eta_WT","eta_WT", 10,-2.5,2.5);
  TH1F* hist_eta_WTSR = new TH1F("eta_WTSR","eta_WTSR", 10,-2.5,2.5);
  TH1F* hist_eta_SR = new TH1F("eta_SR","eta_SR", 10,-2.5,2.5);
  TH1F* hist_eta_fSR = new TH1F("eta_fSR","eta_fSR", 10,-2.5,2.5);
  TH2D *hist_eta_pt = new TH2D("eta_pt", "eta_pt", 10, -2.5,2.5, 60, 0., 300000.);
  TH1F *hist_etcone30 = new TH1F("etcone30","etcone30",300, 0., 150000.);


  //histograms for muons

  TH1F *hist_njets_leptoncut_muon = new TH1F("njets_leptoncut_muon","njets_leptoncut_muon",12,0.,12.);
  TH1F *hist_njets_signalcut_muon = new TH1F("njets_signalcut_muon","njets_signalcut_muon",12,0.,12.);

  TH1F *hist_jet1pt_leptoncut_muon = new TH1F("jet1pt_leptoncut_muon","jet1pt_leptoncut_muon",100,0.,1000000.);
  TH1F *hist_jet2pt_leptoncut_muon = new TH1F("jet2pt_leptoncut_muon","jet2pt_leptoncut_muon",100,0.,1000000.);
  TH1F *hist_jet3pt_leptoncut_muon = new TH1F("jet3pt_leptoncut_muon","jet3pt_leptoncut_muon",100,0.,1000000.);

  TH1F *hist_muonpt_leptoncut_muon = new TH1F("muonpt_leptoncut_muon","muonpt_leptoncut_muon",100,0.,1000000.);

  TH1F *hist_met_leptoncut_muon = new TH1F("met_leptoncut_muon","met_leptoncut_muon",50,0.,500000.);
  TH1F *hist_met_jetcut_muon = new TH1F("met_jetcut_muon","met_jetcut_muon",50,0.,500000.);
  TH1F *hist_met_mtcut_muon = new TH1F("met_mtcut_muon","met_mtcut_muon",50,0.,500000.);
  TH1F *hist_met_signalcut_muon = new TH1F("met_signalcut_muon","met_signalcut_muon",50,0.,500000.);

  TH1F *hist_mt_leptoncut_muon = new TH1F("mt_leptoncut_muon","mt_leptoncut_muon",25,0.,250000.);
  TH1F *hist_mt_jetcut_muon = new TH1F("mt_jetcut_muon","mt_jetcut_muon",25,0.,250000.);
  TH1F *hist_mt_metcut_muon = new TH1F("mt_metcut_muon","mt_metcut_muon",25,0.,250000.);
  TH1F *hist_mt_signalcut_muon = new TH1F("mt_signalcut_muon","mt_signalcut_muon",25,0.,250000.);

  TH1F *hist_meff_leptoncut_muon = new TH1F("meff_leptoncut_muon","meff_leptoncut_muon",100,0.,2000000.);
  TH1F *hist_meff_jetcut_muon = new TH1F("meff_jetcut_muon","meff_jetcut_muon",100,0.,2000000.);
  TH1F *hist_meff_mtcut_muon = new TH1F("meff_mtcut_muon","meff_mtcut_muon",100,0.,2000000.);
  TH1F *hist_meff_metcut_muon = new TH1F("meff_metcut_muon","meff_metcut_muon",100,0.,2000000.);
  TH1F *hist_meff_signalcut_muon = new TH1F("meff_signalcut_muon","meff_signalcut_muon",100,0.,2000000.);

  //histograms for electrons

  TH1F *hist_njets_leptoncut_electron = new TH1F("njets_leptoncut_electron","njets_leptoncut_electron",12,0.,12.);
  TH1F *hist_njets_signalcut_electron = new TH1F("njets_signalcut_electron","njets_signalcut_electron",12,0.,12.);

  TH1F *hist_jet1pt_leptoncut_electron = new TH1F("jet1pt_leptoncut_electron","jet1pt_leptoncut_electron",100,0.,1000000.);
  TH1F *hist_jet2pt_leptoncut_electron = new TH1F("jet2pt_leptoncut_electron","jet2pt_leptoncut_electron",100,0.,1000000.);
  TH1F *hist_jet3pt_leptoncut_electron = new TH1F("jet3pt_leptoncut_electron","jet3pt_leptoncut_electron",100,0.,1000000.);

  TH1F *hist_electronpt_leptoncut_electron = new TH1F("electronpt_leptoncut_electron","electronpt_leptoncut_electron",100,0.,1000000.);

  TH1F *hist_met_leptoncut_electron = new TH1F("met_leptoncut_electron","met_leptoncut_electron",50,0.,500000.);
  TH1F *hist_met_jetcut_electron = new TH1F("met_jetcut_electron","met_jetcut_electron",50,0.,500000.);
  TH1F *hist_met_mtcut_electron = new TH1F("met_mtcut_electron","met_mtcut_electron",50,0.,500000.);
  TH1F *hist_met_signalcut_electron = new TH1F("met_signalcut_electron","met_signalcut_electron",50,0.,500000.);

  TH1F *hist_mt_leptoncut_electron = new TH1F("mt_leptoncut_electron","mt_leptoncut_electron",25,0.,250000.);
  TH1F *hist_mt_jetcut_electron = new TH1F("mt_jetcut_electron","mt_jetcut_electron",25,0.,250000.);
  TH1F *hist_mt_metcut_electron = new TH1F("mt_metcut_electron","mt_metcut_electron",25,0.,250000.);
  TH1F *hist_mt_signalcut_electron = new TH1F("mt_signalcut_electron","mt_signalcut_electron",25,0.,250000.);

  TH1F *hist_meff_leptoncut_electron = new TH1F("meff_leptoncut_electron","meff_leptoncut_electron",100,0.,2000000.);
  TH1F *hist_meff_jetcut_electron = new TH1F("meff_jetcut_electron","meff_jetcut_electron",100,0.,2000000.);
  TH1F *hist_meff_mtcut_electron = new TH1F("meff_mtcut_electron","meff_mtcut_electron",100,0.,2000000.);
  TH1F *hist_meff_metcut_electron = new TH1F("meff_metcut_electron","meff_metcut_electron",100,0.,2000000.);
  TH1F *hist_meff_signalcut_electron = new TH1F("meff_signalcut_electron","meff_signalcut_electron",100,0.,2000000.);

  //counters
  double count_muon[15] = {0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
  double count_elec[15] = {0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};

  int count = 0;

  //initializing of some classes

  //egammaOQ myOQ;
  TDirectory *pwd=gDirectory;
  susyobj.initialize(path_to_Rootcore+"MuonMomentumCorrections/share/",
		     path_to_Rootcore+"MuonEfficiencyCorrections/share/",
		     "STACO_CB_plus_ST",
		     path_to_Rootcore+"JetUncertainties/share/JESUncertainty.root",
		     path_to_Rootcore+"JetUncertainties/analysisPlots/MJESttbarSemi_rel16Example.root",
		     path_to_Rootcore+"JetUncertainties/share/MJESUncertainty.root",
		     path_to_Rootcore+"JetResolution/share/JERProviderPlots.root",
		     path_to_Rootcore+"JetSelectorTools/python/ConfiguredTJetCleaningTools.py",
		     "ConfiguredTJetCleaningTool_Loose()");

  pwd->cd();//reset correct directory  
  fakeMetEst.initialize(path_to_SUSYTools+"data/fest_periodF_v1.root");
  //fakeMetEst.initialize("fest_periodF_v1.root");
  
  pwd->cd();

  muTrgSFTool.initialize(path_to_SUSYTools+"data/trigger/SF_for_EPS.root",path_to_SUSYTools+"data/trigger/SF_barrel_ptdep.root");
  pwd->cd();//reset correct directory  

  /*  
      myJES.init();
      pwd->cd(); 
      myJER.init();
      pwd->cd();  
  */
  //egammaSFclass egammaSFclass; // Class used to correct MC electron reco efficiencies
  //EnergyRescaler geRescale; // Class used to rescale electron energy in data and smear electron energy in MC
  //geRescale.useDefaultCalibConstants();
  //Analysis::StacoCBScaleEffFactors gStacoCBSCF; // Class used to rescale MC muon reco efficiencies

  
  //For trigger rescaling
  string reweight_file_name = path_to_SUSYTools+"data/EF_mu18.root";
  TFile reweight_file(reweight_file_name.c_str(), "OPEN");    //Open root file holding the two histogram
  //TFile reweight_file("EF_mu18.root", "OPEN");    //Open root file holding the two histogram
  THnSparseD* trig_numerator_hist = (THnSparseD*) reweight_file.Get("passes");    //Get the numerator histogram
  THnSparseD* trig_denominator_hist = (THnSparseD*) reweight_file.Get("trials");    //Get the denominator histogram

  TrigWeighter = new APReweightND(trig_denominator_hist, trig_numerator_hist, true);    //Instantiate the trigger weighter

  delete trig_denominator_hist;    //Cleanup input numerator histogram (not needed anymore)
  delete trig_numerator_hist;    //Cleanup input denominator histogram (not needed anymore)
  reweight_file.Close();    //Close input file (not needed anymore)

  pwd->cd();//reset correct directory  

  Root::TGoodRunsListReader* grl_reader = new Root::TGoodRunsListReader("data11_7TeV.periodAllYear_DetStatus-v36-pro10_CoolRunQuery-00-04-08_Susy.xml");
  grl_reader->AddXMLFile("data11_7TeV.periodAllYear_DetStatus-v36-pro10_CoolRunQuery-00-04-08_Susy.xml");
  grl_reader->Interpret();
  const Root::TGRLCollection goodrunslist = grl_reader->GetMergedGRLCollection();
  //goodrunslist.Summary(true);
  
  pwd->cd();//reset correct directory 


  double lumi_Period1 = 178.388;
  double lumi_Period2 = 948.666;
  double lumi_Period3 = 753.288;
  //double lumi_Period4 = 2320.72;
  double lumi_Period4 = 2832.74;
  susyobj.GetegammaOQ().setLumiVec(lumi_Period1,lumi_Period2,lumi_Period3,lumi_Period4);

  
  //data kIsData =1; MC kIsData=0;
  int kIsData = 0;  
  if (DATA) kIsData = 1;

  JetErr::Syste whichsyste = JetErr::NONE;

  if (JESUP) whichsyste = JetErr::JESUP;
  if (JESDOWN) whichsyste = JetErr::JESDOWN;
  if (JER) whichsyste = JetErr::JER;

  //TTree *newtree = fChain->CloneTree(0);

  //Loop over all events  

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    if (curr_file!=chain->GetFile()->GetName())
      {
	std::cout<<"New File: "<<chain->GetFile()->GetName()<<std::endl;
	curr_file=chain->GetFile()->GetName();
	filecount++;
      }
    
    //Clear arrays 
    susyobj.Reset();
    
    float weight = 0.;
    int myRunNumber;
    //MC:
    if (kIsData==0) {
      if (mcevt_weight->size() > 0 && mcevt_weight->at(0).size() > 0) weight =   mcevt_weight->at(0).at(0);
      else weight = 0.;
      myRunNumber = 180614;
    }
    //data:
    else {
      weight = 1.;
      myRunNumber = RunNumber;
    }

    //if (kIsData==0) weight*=susyobj.GetegammaOQ().getOQWeight(RunNumber);

    double weight_electron = weight;

    count += int(weight);
    if(count%10000==0) std::cout<<count<<std::endl;

#ifdef USEPILEUP
    if(kIsData==0){
      //electrons:
      float pileupEventWeight = 0;
      //float mu=actualIntPerXing;
      
      if(!elPileUpTool) cout << "no pileup tool!" << endl;
      pileupEventWeight = elPileUpTool->GetCombinedWeight(RunNumber,mc_channel_number,averageIntPerXing);
      //if(kIsData==0) weight_electron*=pileupEventWeight; 

      //muons:
      float pileupEventWeight_mu = 0;
      
      if(!muPileUpTool) cout << "no pileup tool!" << endl;
      pileupEventWeight_mu = muPileUpTool->GetCombinedWeight(RunNumber,mc_channel_number,averageIntPerXing);
      //if(kIsData==0) weight*=pileupEventWeight_mu; 
      //else cout << "Do not apply pileup reweighting!" << endl;
    }
#endif

    //newtree->Fill();

    count_muon[0] += weight;
    count_elec[0] += weight;

    histo_cutflow_muon->Fill(0.,weight);
    histo_cutflow_elec->Fill(0.,weight);

    if (kIsData == 1 && !(goodrunslist.HasRunLumiBlock(RunNumber, lbn))) continue; //(data11_7TeVGetGoodRunLumi(RunNumber, lbn) == 1))) continue;

    count_muon[1] += weight;
    count_elec[1] += weight;

    //Jet smearing
    /*
      susyobj.SmearJets(jet_AntiKt4TopoNewEM_pt,
      jet_AntiKt4TopoNewEM_eta,
      jet_AntiKt4TopoNewEM_phi,
      jet_AntiKt4TopoNewEM_E);
    */


    //get muons, electrons and jets - define vector of indices of good muons, jets and electrons

    vector<int> elec_index_noiso;
    vector<int> elec_index_met;
    vector<int> elec_index_met2;
    vector<int> elec_index_triggermatch;
    vector<int> muon_index_noiso;
    vector<int> jet_index;
    vector<int> jet_index_signal;
    vector<int> elec_index;
    vector<int> muon_index;
    vector<int> muon_index_triggermatch;    
    vector<int> muon_index_iso;
    vector<int> muon_index_cosmics;
    vector<int> muon_index_bad;	
    vector<int> elec_index_iso;

    histo_cutflow_muon->Fill(1.,weight);
    histo_cutflow_elec->Fill(1.,weight);

    bool trigger_muon = false;
    bool trigger_elec = false;

    int elTrigSet = 10;
    int elTrigmatch = 0;//1: trig_EF_el_EF_e20_medium;

    //trigger
    
    if ((!kIsData && trgwgt) || (!kIsData && !trgwgt && EF_mu18) || (kIsData && (EF_mu18 || EF_mu18_L1J10)))  trigger_muon = true;  //apply the trigger decision only to data - uncomment if you want to apply trigger reweighting
    //if (EF_mu18) trigger_muon = true; //MC and data the same at the moment - comment if you want to apply trigger reweighting
    if ( ( (!kIsData && RunNumber < 188902) || (kIsData && RunNumber <= 186755) ) && EF_e20_medium){
      trigger_elec = true; 
      elTrigmatch = 1; //1: trig_EF_el_EF_e20_medium
    }
    else if ((kIsData && RunNumber >= 186873 && RunNumber <= 187815) && EF_e22_medium) {
      trigger_elec = true;    
      elTrigSet = 14;         
      elTrigmatch = 2; //2: trig_EF_el_EF_e22_medium
    }
    else if ((RunNumber >= 188902) && (EF_e22vh_medium1 || EF_e45_medium1)) {
      trigger_elec = true;    
      elTrigSet = 18;
      elTrigmatch = 3; //3: trig_EF_el_EF_e22vh_medium1 or trig_EF_el_EF_e45_medium1
    }
    if (trigger_muon || trigger_elec) {

      //get electrons
      elec_index_met=get_good_electron_index(myRunNumber, kIsData);

      //Get electrons for MET calculation
      elec_index_met2=get_good_electron_index_met();

      //electrons matched to a trigger object
      if (trigger_elec) elec_index_triggermatch=get_good_electron_index_triggermatch(elTrigmatch);

	
	
      //MET and jet variables
      int badjet=0;
      int LArjet=0;
	
      vector<double> jetptemjes;
      float met = 0.;
      float metx = 0.;
      float mety = 0.;
      
      //elec_index_noiso=get_overlap_electron_index(elec_index_met);	
	
      std::vector<TLorentzVector> jetlv(jet_AntiKt4TopoNewEM_n);

      for (int i = 0; i < jet_AntiKt4TopoNewEM_n; ++i){
	jetlv[i].SetPtEtaPhiE(jet_AntiKt4TopoNewEM_pt->at(i), jet_AntiKt4TopoNewEM_eta->at(i), jet_AntiKt4TopoNewEM_phi->at(i), jet_AntiKt4TopoNewEM_E->at(i)); 
      }

      //get jets - jets too close to electrons (Delta R < 0.2) are already rejected
      jet_index=get_good_jet_index(jetlv, elec_index_met.size(),elec_index_met, kIsData, whichsyste); // HAVE TO MAKE OVERLAP REMOVAL BY HAND!!
	

      //if jet p_t was corrected, then the jets must be sorted again according to their pt - keep relation to eta and phi of the jet - use a container for this
      vector<Container> jet; 
	
      for (unsigned int i=0; i<jet_index.size(); i++)
	{
	  Container x;
	  x.pt=jet_AntiKt4TopoNewEM_pt->at(jet_index[i]);
	  x.phi=jet_AntiKt4TopoNewEM_phi->at(jet_index[i]);
	  x.eta=jet_AntiKt4TopoNewEM_eta->at(jet_index[i]);
	  x.index=jet_index[i];
	  jet.push_back(x);
	}
	
      //and sort them
	
      if (jet_index.size()>0) {
	std::sort(jet.begin(),jet.end());
	std::reverse(jet.begin(),jet.end());		
	  
      }

      //reject jets from pileup vetices

      jet_index_signal=get_signal_jet_index(jet);	
	
	

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //Recalculation of MET
	
      //Get muons for recalculation of MET
      muon_index_noiso=get_good_muon_index2(kIsData,muonsmearing);
		
      //new MET definition (29.06.2011)
      TVector2 SimplifiedRefFinal;

      SimplifiedRefFinal = susyobj.GetMET(jet_AntiKt4TopoNewEM_pt,
					  jet_AntiKt4TopoNewEM_eta,
					  jet_AntiKt4TopoNewEM_phi,
					  jet_AntiKt4TopoNewEM_E,
					  jet_AntiKt4TopoNewEM_MET_Simplified20_wet,
					  jet_AntiKt4TopoNewEM_MET_Simplified20_wpx,
					  jet_AntiKt4TopoNewEM_MET_Simplified20_wpy,
					  jet_AntiKt4TopoNewEM_MET_Simplified20_statusWord,
					  elec_index_met2,
					  el_MET_Simplified20_wet,
					  el_MET_Simplified20_wpx,
					  el_MET_Simplified20_wpy,
					  el_MET_Simplified20_statusWord,
					  MET_Simplified20_CellOut_etx,
					  MET_Simplified20_CellOut_ety,
					  MET_Simplified20_CellOut_sumet,
					  MET_Simplified20_RefGamma_etx,
					  MET_Simplified20_RefGamma_ety,
					  MET_Simplified20_RefGamma_sumet,
					  muon_index_noiso,
					  mu_staco_ms_qoverp, 
					  mu_staco_ms_theta, 
					  mu_staco_ms_phi, 
					  mu_staco_charge,
					  whichsyste);

	
      metx = SimplifiedRefFinal.X();
      mety = SimplifiedRefFinal.Y();
	
      met=sqrt(metx*metx+mety*mety);

      //Get isolated electrons and muons - final analysis objects
	
      muon_index=get_good_muon_index(jet_index.size(),jet_index, muon_index_noiso/*, kIsData*/);
      muon_index_iso=get_good_muon_index_iso(muon_index);
      muon_index_cosmics = get_muon_cosmics(muon_index);
      muon_index_bad = get_muon_bad(muon_index_noiso);
      muon_index_triggermatch = get_muon_triggermatch();      
      elec_index=get_iso_electron_index(jet_index.size(),jet_index, elec_index_met/*, kIsData*/);
      elec_index_iso=get_signal_electron_index(elec_index);

      //get muons matched to trigger object

      bool match_to_signal_muon = false;
      if (kIsData == 0 && !trgwgt){
	if (muon_index_triggermatch.size() > 0) {
	  int triggerindex = -1;
	  if (muon_index.size()>0){
	    for (unsigned int i_trig = 0; i_trig < muon_index_triggermatch.size(); i_trig++){
	      if (muon_index[0] == muon_index_triggermatch[i_trig]) triggerindex = muon_index[0];
	      if (muon_index[0] == muon_index_triggermatch[i_trig]) match_to_signal_muon = true;
	    }
	    if (triggerindex != muon_index[0]) 
	      triggerindex = muon_index_triggermatch[0];
	  }
	  else triggerindex = muon_index_triggermatch[0];		
	  if (triggerindex != -1) weight = weight*muTrgSFTool.GetScaleFactor(mu_staco_eta->at(triggerindex),
									     mu_staco_phi->at(triggerindex),
									     mu_staco_pt->at(triggerindex)/1000.);
	}
	//else cout << "Error by obtaining trigger scale factors for muons" << endl;
      }

      //electron trigger scale factors
      if (kIsData == 0 && elec_index.size() > 0) weight_electron *= susyobj.GetTrigElecSF(el_cl_eta->at(elec_index[0]),el_cl_E->at(elec_index[0])/cosh(el_tracketa->at(elec_index[0])),elTrigSet);
	
      if (trigger_muon) histo_cutflow_muon->Fill(2.,weight);
      if (trigger_elec) histo_cutflow_elec->Fill(2.,weight_electron);
      if (trigger_muon) count_muon[2] += weight;
      if (trigger_elec) count_elec[2] += weight_electron;
	
      //remove events with bad jets
      for(int k=0;k<jet_AntiKt4TopoNewEM_n;k++) {	  
	if ( jet_AntiKt4TopoNewEM_pt->at(k)>20000. &&  
	     JetID::isBadJet(JetID::VeryLooseBad,jet_AntiKt4TopoNewEM_emfrac->at(k),jet_AntiKt4TopoNewEM_hecf->at(k),
			     jet_AntiKt4TopoNewEM_LArQuality->at(k),jet_AntiKt4TopoNewEM_HECQuality->at(k),
			     jet_AntiKt4TopoNewEM_Timing->at(k),jet_AntiKt4TopoNewEM_sumPtTrk->at(k)/1000.,
			     jet_AntiKt4TopoNewEM_emscale_eta->at(k),jet_AntiKt4TopoNewEM_pt->at(k)/1000.,
			     jet_AntiKt4TopoNewEM_fracSamplingMax->at(k),jet_AntiKt4TopoNewEM_NegativeE->at(k),jet_AntiKt4TopoNewEM_AverageLArQF->at(k))){

	  badjet++;
	} 
	  
	//smart LAr hole veto
	if (susyobj.IsLArHole(jet_AntiKt4TopoNewEM_eta->at(k),jet_AntiKt4TopoNewEM_phi->at(k))) {

	  if ( fakeMetEst.isBad(jet_AntiKt4TopoNewEM_pt->at(k),
				jet_AntiKt4TopoNewEM_BCH_CORR_JET->at(k),
				jet_AntiKt4TopoNewEM_BCH_CORR_CELL->at(k),
				jet_AntiKt4TopoNewEM_BCH_CORR_DOTX->at(k),
				jet_AntiKt4TopoNewEM_phi->at(k),metx,mety,10000.,10.,-1.,-1.)) LArjet++;
	}	  
      }	

      if ( LArjet>0 ) continue; //reject events with jets falling in the LAr hole
	
      if((kIsData == 1 && badjet==0 && larError==0) || (kIsData == 0 && badjet==0)){ //jet cleaning

	if (trigger_muon) count_muon[3] += weight;
	if (trigger_elec) count_elec[3] += weight_electron;
	if (trigger_muon) histo_cutflow_muon->Fill(3.,weight);
	if (trigger_elec) histo_cutflow_elec->Fill(3.,weight_electron);
	  
	//vertex-cut
	int vtxfound=0;

	if(susyobj.IsGoodVertex(vx_nTracks)) vtxfound+=1;

	if(vtxfound>0){
	    
	  if (trigger_muon) histo_cutflow_muon->Fill(4.,weight);
	  if (trigger_elec) histo_cutflow_elec->Fill(4.,weight_electron);
	  if (trigger_muon) count_muon[4] += weight;
	  if (trigger_elec) count_elec[4] += weight_electron;

	  int vetocrack=0;	    
	    
	  if(vetocrack==0) {


	    ///////////////////////////////////////////////////////////////

            //cosmic and bad muon veto	      
	    if (muon_index_cosmics.size() == 0 && muon_index_bad.size() == 0 ) {
		
	      if (trigger_muon) count_muon[5] += weight;
	      if (trigger_elec) count_elec[5] += weight_electron;	
	      
	      
	      
	      //1-lepton cut: 1-muon channel
	      bool leptoncut = false;
	      
	      //want to obtain QCD fake and real efficiencies?
	      if (QCD_loose){
		
		if (trigger_muon && elec_index.size()==0 && muon_index.size()== 1 && susyobj.GetMuonTLV(muon_index[0]).Pt() > 20000.) 
		  leptoncut = true;
		
	        //remind that you have to run with loose cuts in order to get the QCD estimate on data
	        //event is tight?
		if (QCDestimate) {
		  
		  bool isTight = false;
		  
		  if (trigger_muon && elec_index.size()==0 && muon_index_iso.size()== 1  && muon_index.size()== 1 ) isTight = true;

		  //activiate QCD weights here and instances in header file in order to use FakeLeptBkg package
		  //if (kIsData == 0) cout <<"Stop! - Matrix method is data-driven - do not run on MC!" << endl;
		  //std::pair<float, float > v_real = myMuonMM.GetRealEfficiency_muons(susyobj.GetMuonTLV(muon_index[0]).Eta()); 
		  //std::pair<float, float > v_fake = myMuonMM.GetFakeEfficiency_muons(susyobj.GetMuonTLV(muon_index[0]).Eta());
		  //float event_weight =  myMM.GetNfake(v_fake.first, v_real.first, isTight);
		  //weight = weight*event_weight;
		}
	      
	      }
	      else{
	      
		if(trigger_muon && elec_index.size()==0 && muon_index_iso.size()== 1  && muon_index.size()== 1 ) leptoncut = true;
	      
	      }
	      

	      if(leptoncut){

		bool SFUNC = false;
		//scale event:
		if (kIsData==0) {
		  weight *= susyobj.GetSignalMuonSF(muon_index[0]);
		  //still to implement: systematics for muons
		  if (SFUNC) weight *= (1+susyobj.GetSignalMuonSFUnc(muon_index[0]));

		}
		

		//Trigger matching
		bool trigger_passed = false;
		//if (!kIsData || susyobj.MuonHasTriggerMatchOld(muon_index[0],mu_staco_n,trig_EF_trigmuonef_n,trig_EF_trigmuonef_track_n,mu_staco_pt,mu_staco_eta, mu_staco_phi,trig_EF_trigmuonef_track_CB_pt,trig_EF_trigmuonef_track_CB_eta,trig_EF_trigmuonef_track_CB_phi, trig_EF_trigmuonef_track_CB_hasCB)) {
		  
		//bool trigger_passed = true;

		if (!kIsData){
		  if(trgwgt){ // Use trigger reweighting instead of the MC trigger simulation for muons
		    trigger_passed = true;
		    APEvtWeight weight_muon(APEvtWeight::kMuon);    //Creates and event weight instance for muons with the chosen map
		    double value_array[5] = {(*mu_staco_pt)[muon_index[0]], (*mu_staco_eta)[muon_index[0]], (*mu_staco_phi)[muon_index[0]], (*mu_staco_ptcone20)[muon_index[0]], (double) ((*mu_staco_isCombinedMuon)[muon_index[0]] == true)};    //Combine the 5D object information into a temporary field
		    weight_muon.AddWeightToEvt( TrigWeighter->GetWeight(value_array) );    //Add the Weight associated with the parameters of the current object to the sum of weights for the current event
		    weight*= weight_muon.GetWeight(); //uncomment if you want to use trigger reweighting!

		  }
		  else {
		    if (match_to_signal_muon) trigger_passed = true;
		  }
		}
		else{
		  // if(kIsData && susyobj.MuonHasTriggerMatchOld(muon_index[0],mu_staco_n,trig_EF_trigmuonef_n,trig_EF_trigmuonef_track_n,mu_staco_pt,mu_staco_eta, mu_staco_phi,trig_EF_trigmuonef_track_CB_pt,trig_EF_trigmuonef_track_CB_eta,trig_EF_trigmuonef_track_CB_phi, trig_EF_trigmuonef_track_CB_hasCB)) trigger_passed = true;
		  int EFindex = -1;
		  int EFtrackindex = -1;
		  if(kIsData && susyobj.MuonHasTriggerMatch((*mu_staco_eta)[muon_index[0]],(*mu_staco_phi)[muon_index[0]],trig_EF_trigmuonef_EF_mu18,EFindex,EFtrackindex,trig_EF_trigmuonef_n,trig_EF_trigmuonef_track_CB_eta,trig_EF_trigmuonef_track_CB_phi,trig_EF_trigmuonef_track_CB_hasCB)) trigger_passed = true;
		}
		  
		if (trigger_passed){

		  count_muon[6] += weight;
		  histo_cutflow_muon->Fill(5.,weight);


		  //now get some histograms in order to obatin fake and real efficiencies for matrix method - different  control regions
		  int high_pt_jet = 0;

		  for (unsigned int jet_it=0; jet_it < jet_index_signal.size(); jet_it++){
		    if (susyobj.GetJetTLV(jet_index_signal[jet_it]).Pt() > 25000.) high_pt_jet++;
		  }

		  //Get M_T and M_eff
		    
		  double meff = calculate_meff(jet_index_signal, elec_index.size(), muon_index.size(), elec_index, muon_index, met);

		  double mt = calculate_mt_1lepton(elec_index.size(), muon_index.size(), elec_index, muon_index, metx, mety, met);

		  for (double met_it = 10000.; met_it < 100000.; met_it+= 10000.){
		    if (met < met_it) histo_met->Fill(met_it,weight);
		  }

		  //set to 30000. for PLHC and move control histograms from high d0sign region to this control region
		  if (met<30000. && jet_index_signal.size() >= 1 && susyobj.GetJetTLV(jet_index_signal[0]).Pt()>=60000.) {
		    histo_cutflow_muon->Fill(12.,weight);
		    hist_eta_lowMET->Fill(susyobj.GetMuonTLV(muon_index[0]).Eta(),weight);
		    hist_eta_pt->Fill(mu_staco_eta->at(muon_index[0]),susyobj.GetMuonTLV(muon_index[0]).Pt(), weight);
		    //histo_met->Fill(met,weight);
		    histo_mt->Fill(mt,weight);
		    histo_pt->Fill(susyobj.GetMuonTLV(muon_index[0]).Pt(),weight);



		    hist_njets->Fill(high_pt_jet,weight);
		  }
		    
		  if (met<30000. && jet_index_signal.size() >= 2 && susyobj.GetJetTLV(jet_index_signal[0]).Pt()>=60000. && susyobj.GetJetTLV(jet_index_signal[1]).Pt()>=25000.) {
		    hist_eta_WTSR->Fill(mu_staco_eta->at(muon_index[0]),weight);
		  }


		  hist_njets_leptoncut_muon->Fill(high_pt_jet,weight);
		  hist_muonpt_leptoncut_muon->Fill(susyobj.GetMuonTLV(muon_index[0]).Pt(),weight);
		  if (jet_index_signal.size() > 0) hist_jet1pt_leptoncut_muon->Fill(susyobj.GetJetTLV(jet_index_signal[0]).Pt(),weight);
		  if (jet_index_signal.size() > 1) hist_jet2pt_leptoncut_muon->Fill(susyobj.GetJetTLV(jet_index_signal[1]).Pt(),weight);
		  if (jet_index_signal.size() > 2) hist_jet3pt_leptoncut_muon->Fill(susyobj.GetJetTLV(jet_index_signal[2]).Pt(),weight);
		  hist_met_leptoncut_muon->Fill(met,weight);		    
		  hist_mt_leptoncut_muon->Fill(mt,weight);
		  hist_meff_leptoncut_muon->Fill(meff,weight);

		  hist_etcone30->Fill(mu_staco_etcone30->at(muon_index[0]), weight);

		    
		  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		  //jet cuts

		  if (jet_index_signal.size() >= 3) {
		    //if (jet[0].pt>=60000. && jet[2].pt>=25000.) {
		    if (susyobj.GetJetTLV(jet_index_signal[0]).Pt()>=100000. && susyobj.GetJetTLV(jet_index_signal[2]).Pt()>=25000.) { 

		      bool fourth_jet_veto = true;

		      if (jet_index_signal.size() >= 4 && susyobj.GetJetTLV(jet_index_signal[3]).Pt()>=80000.){
			fourth_jet_veto = false;
		      }	
			
		      if (fourth_jet_veto){


			hist_met_jetcut_muon->Fill(met,weight);		    
			hist_mt_jetcut_muon->Fill(mt,weight);
			hist_meff_jetcut_muon->Fill(meff,weight);

			histo_cutflow_muon->Fill(6.,weight);
			count_muon[7] += weight;

			//Delta phi(MET, jet_i) > 0.2 cut
			double phi_met = TMath::ATan2(mety,metx);

			double dphi1 = fabs(jet[0].phi-phi_met);
			double dphi2 = fabs(jet[1].phi-phi_met);
			double dphi3 = fabs(jet[2].phi-phi_met);

			if (dphi1 > 3.141592653) dphi1 = fabs(dphi1 - (2.*3.141592653));
			if (dphi2 > 3.141592653) dphi2 = fabs(dphi2 - (2.*3.141592653));
			if (dphi3 > 3.141592653) dphi3 = fabs(dphi3 - (2.*3.141592653));
			//deactivate Delta phi cut
			//if(dphi1 > 0.2 && dphi2 > 0.2 && dphi3 > 0.2) {

			count_muon[8] += weight;
			histo_cutflow_muon->Fill(7.,weight);

			histo_mtmet->Fill(met, mt, weight);
			histo_meff->Fill(meff,weight);


                        //d0sig control region
			double d0sig = -100.;
			if (mu_staco_cov_d0_exPV->at(muon_index[0]) > 0) d0sig = fabs(mu_staco_d0_exPV->at(muon_index[0])/sqrt(mu_staco_cov_d0_exPV->at(muon_index[0])));
			d0sig = fabs(mu_staco_d0_exPV->at(muon_index[0]));
			histo_d0sig->Fill(d0sig, weight);
			histo_metd0Sig->Fill(d0sig, met, weight);




			if ( d0sig > 5) {
			  histo_cutflow_muon->Fill(13.,weight);
			  histo_mtmet_afterd0->Fill(met, mt, weight);

			  hist_eta_afterd0->Fill(susyobj.GetMuonTLV(muon_index[0]).Eta(),weight);
			} //d0


			  //eta distribtuion in W/T CR & SR:

			if (met < 40000. && mt < 40000.) hist_eta_SR->Fill(susyobj.GetMuonTLV(muon_index[0]).Eta(),weight);

			//eta distribtuion in W/T CR:
			if (met < 30000. && met < 80000. && mt > 40000. && mt < 80000.) hist_eta_WT->Fill(susyobj.GetMuonTLV(muon_index[0]).Eta(),weight);


			if (mt > 100000.) hist_met_mtcut_muon->Fill(met,weight);

			//MET cut
			if (met > 250000.) {
			  histo_cutflow_muon->Fill(8.,weight);
			  count_muon[9] += weight;
	    
			  hist_mt_metcut_muon->Fill(mt,weight);
			  hist_meff_metcut_muon->Fill(meff,weight);

			  //M_T cut
			  if(mt > 100000.) {
			    histo_cutflow_muon->Fill(9.,weight);
			    count_muon[10] += weight;
			    hist_meff_mtcut_muon->Fill(meff,weight);
			      
			    //MET>0.3 M_eff cut
			    //for this cut we only consider the three leading signal jets - be careful, this is different from the meff definition at other places
			    double meff_exclusive = calculate_meff(jet_index_signal, elec_index.size(), muon_index.size(), elec_index, muon_index, met, false);
			    if (met > 0.3 *meff_exclusive) {
			      histo_cutflow_muon->Fill(10.,weight);
			      count_muon[11] += weight;
			      hist_meff_signalcut_muon->Fill(meff,weight);
			      //M_eff cut
			      if (meff > 1200000.) {
				histo_cutflow_muon->Fill(11.,weight);
				count_muon[12] += weight;
				hist_eta_fSR->Fill(susyobj.GetMuonTLV(muon_index[0]).Eta(),weight);
				hist_njets_signalcut_muon->Fill(high_pt_jet,weight);
				hist_met_signalcut_muon->Fill(met,weight);		    
				hist_mt_signalcut_muon->Fill(mt,weight);

			      }
			    }
			  }
			}
			  
			//}//dphi
		      }//fourth jet veto
		    } //jet_pt		 
		  } //jet size
		}// trigger
		//} //met
		//} // mu_z0
		//} //otx-veto
		//} //currently end of veto on crack region
		//} //end trigger matching
	      } // end of cut 1 lepton

	      if(trigger_elec && elec_index.size()==1 && elec_index_iso.size()==1  && muon_index.size()== 0 ){

                //electron trigger matching
		bool trigger_match_elec = false;

		for (unsigned int telm = 0; telm < elec_index_triggermatch.size(); telm++){
		  if (elec_index_triggermatch[telm] == elec_index[0]){
		    trigger_match_elec = true;
		  }
		}


		if (trigger_match_elec){
		  //&& susyobj.GetMuonTLV(muon_index[0]).Pt() > 20000.) {
		
		  //scale event:
		  if (kIsData==0) weight_electron *= susyobj.GetSignalElecSF(el_cl_eta->at( elec_index_iso[0]),el_cl_E->at(elec_index_iso[0])/cosh(el_tracketa->at(elec_index_iso[0])));

		  count_elec[6] += weight_electron;
		  histo_cutflow_elec->Fill(5.,weight_electron);

			  
		  //Get M_T and M_eff
		  double mt_elec = calculate_mt_1lepton(elec_index_iso.size(), muon_index.size(), elec_index_iso, muon_index, metx, mety, met);
		  double meff_elec = calculate_meff(jet_index_signal, elec_index_iso.size(), muon_index.size(), elec_index_iso, muon_index, met);


		  int high_pt_jet_elec = 0;

		  for (unsigned int jet_it_elec=0; jet_it_elec < jet_index_signal.size(); jet_it_elec++){
		    if (susyobj.GetJetTLV(jet_index_signal[jet_it_elec]).Pt() > 25000.) high_pt_jet_elec++;
		  }

		  hist_njets_leptoncut_electron->Fill(high_pt_jet_elec,weight_electron);
		  hist_electronpt_leptoncut_electron->Fill(susyobj.GetElecTLV(elec_index[0]).Pt(),weight_electron);
		  if (jet_index_signal.size() > 0) hist_jet1pt_leptoncut_electron->Fill(susyobj.GetJetTLV(jet_index_signal[0]).Pt(),weight_electron);
		  if (jet_index_signal.size() > 1) hist_jet2pt_leptoncut_electron->Fill(susyobj.GetJetTLV(jet_index_signal[1]).Pt(),weight_electron);
		  if (jet_index_signal.size() > 2) hist_jet3pt_leptoncut_electron->Fill(susyobj.GetJetTLV(jet_index_signal[2]).Pt(),weight_electron);
		  hist_met_leptoncut_electron->Fill(met,weight_electron);		    
		  hist_mt_leptoncut_electron->Fill(mt_elec,weight_electron);
		  hist_meff_leptoncut_electron->Fill(meff_elec,weight_electron);

		  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		  //jet cuts
		  if (jet_index_signal.size() >= 3) {
		    //if (jet[0].pt>=60000. && jet[2].pt>=25000.) {
		    if (susyobj.GetJetTLV(jet_index_signal[0]).Pt()>=100000. && susyobj.GetJetTLV(jet_index_signal[2]).Pt()>=25000.) { 

		      bool fourth_jet_veto2 = true;

		      if (jet_index_signal.size() >= 4 && susyobj.GetJetTLV(jet_index_signal[3]).Pt()>=80000.){
			fourth_jet_veto2 = false;
		      }	
			
		      if (fourth_jet_veto2){


			hist_met_jetcut_electron->Fill(met,weight_electron);		    
			hist_mt_jetcut_electron->Fill(mt_elec,weight_electron);
			hist_meff_jetcut_electron->Fill(meff_elec,weight_electron);


			histo_cutflow_elec->Fill(6.,weight_electron);
			count_elec[7] += weight_electron;

			//Delta phi(MET, jet_i) > 0.2 cut
			double phi_met_elec = TMath::ATan2(mety,metx);

			double dphi1_elec = fabs(jet[0].phi-phi_met_elec);
			double dphi2_elec = fabs(jet[1].phi-phi_met_elec);
			double dphi3_elec = fabs(jet[2].phi-phi_met_elec);

			if (dphi1_elec > 3.141592653) dphi1_elec = fabs(dphi1_elec - (2.*3.141592653));
			if (dphi2_elec > 3.141592653) dphi2_elec = fabs(dphi2_elec - (2.*3.141592653));
			if (dphi3_elec > 3.141592653) dphi3_elec = fabs(dphi3_elec - (2.*3.141592653));

			//deactivate Delta phi cut
			//if(dphi1_elec > 0.2 && dphi2_elec > 0.2 && dphi3_elec > 0.2) {

			count_elec[8] += weight_electron;
			histo_cutflow_elec->Fill(7.,weight_electron);


			if (mt_elec > 100000.) hist_met_mtcut_electron->Fill(met,weight_electron);

			//MET cut
			if (met > 250000.) {
			  histo_cutflow_elec->Fill(8.,weight_electron);
			  count_elec[9] += weight_electron;
			  hist_mt_metcut_electron->Fill(mt_elec,weight_electron);
			  hist_meff_metcut_electron->Fill(meff_elec,weight_electron);

			  //M_T cut
			  if(mt_elec > 100000.) {
			    histo_cutflow_elec->Fill(9.,weight_electron);
			    count_elec[10] += weight_electron;
			    hist_meff_mtcut_electron->Fill(meff_elec,weight_electron);

			    //MET>0.3 M_eff cut
			    //for this cut we only consider the three leading signal jets - be careful, this is different from the meff definition at other places
			    double meff_exclusive_elec = calculate_meff(jet_index_signal, elec_index_iso.size(), muon_index.size(), elec_index_iso, muon_index, met, false);
			    if (met > 0.3 *meff_exclusive_elec) {
			      histo_cutflow_elec->Fill(10.,weight_electron);
			      count_elec[11] += weight_electron;
			      hist_meff_signalcut_electron->Fill(meff_elec,weight_electron);
			      //M_eff cut
			      if (meff_elec > 1200000.) {
				histo_cutflow_elec->Fill(11.,weight_electron);
				count_elec[12] += weight_electron;
				hist_njets_signalcut_electron->Fill(high_pt_jet_elec,weight_electron);
				hist_met_signalcut_electron->Fill(met,weight_electron);		    
				hist_mt_signalcut_electron->Fill(mt_elec,weight_electron);
			      }
			    }
			  }
			}
			  
			//}//dphi
		      }//fourth jet veto
		    } //jet_pt		 
		  } //jet size
		  //} //met
		  //} // mu_z0
		  //} //otx-veto
		  //} //currently end of veto on crack region
		}//test with signal electron matched to trigger object
	      } // end of cut 1 lepton

	    }//cosmics veto
	  } //veto on crack region	      
	} //nvertix - or - end of veto on crack region
      } //first jet quality cut     
    }//trigger
    //} //lbn
  } //end of loop
  
  pwd->cd(); 
  //newtree->Print();
  //newtree->AutoSave();
  //newtree->Write();
  cout << endl;
  std::cout<<"************* cutflow (1-muon+3jets): **************"<<std::endl;
  cout << "Events in file: " << count << endl;
  cout << "Pileup-reweighting: " << count_muon[0] << endl;  
  cout << "GRL: " << count_muon[1] << endl;  
  cout << "Trigger: " << count_muon[2] << endl;  
  cout << "Jet cleaning: " << count_muon[3] << endl;  
  cout << "Vertex cut: " << count_muon[4] << endl;   
  //cout << "Veto on events with electrons in the crack region: " << count_vetocrack << endl; 
  cout << "cosmics veto: " << count_muon[5] << endl;    
  cout << "1-lepton cut: " << count_muon[6] << endl; 
  cout << ">=3 jets(100,25,25): " << count_muon[7] << endl;  
  cout << "Delta phi: " << count_muon[8] << endl;  
  cout << "MET > 250 GeV: " << count_muon[9] << endl; 
  cout << "M_T > 100 GeV: " << count_muon[10] << endl; 
  cout << "MET > 0.3 Meff: " << count_muon[11] << endl;  
  cout << "Meff > 1200 GeV: " << count_muon[12] << endl;   

  histo_cutflow_muon->Write();
  histo_metd0Sig->Write();
  histo_d0sig->Write();
  histo_mtmet->Write();
  histo_mtmet_afterd0->Write();
  histo_met->Write();
  histo_mt->Write();
  histo_meff->Write();
  histo_pt->Write();
  hist_njets->Write();
  hist_eta_afterd0->Write();
  hist_eta_lowMET->Write();
  hist_eta_WT->Write();
  hist_eta_WTSR->Write();
  hist_eta_SR->Write();
  hist_eta_fSR->Write();
  hist_eta_pt->Write();
  hist_etcone30->Write();

  hist_njets_leptoncut_muon->Write();
  hist_njets_signalcut_muon->Write();

  hist_jet1pt_leptoncut_muon->Write();
  hist_jet2pt_leptoncut_muon->Write();
  hist_jet3pt_leptoncut_muon->Write();

  hist_muonpt_leptoncut_muon->Write();

  hist_met_leptoncut_muon->Write();
  hist_met_jetcut_muon->Write();
  hist_met_mtcut_muon->Write();
  hist_met_signalcut_muon->Write();

  hist_mt_leptoncut_muon->Write();
  hist_mt_jetcut_muon->Write();
  hist_mt_metcut_muon->Write();
  hist_mt_signalcut_muon->Write();

  hist_meff_leptoncut_muon->Write();
  hist_meff_jetcut_muon->Write();
  hist_meff_mtcut_muon->Write();
  hist_meff_metcut_muon->Write();
  hist_meff_signalcut_muon->Write();

  cout << endl;
  std::cout<<"************* cutflow (1-elec+3jets): **************"<<std::endl;
  cout << "Events in file: " << count << endl;
  cout << "Pileup-reweighting: " << count_elec[0] << endl; 
  cout << "GRL: " << count_elec[1] << endl; 
  cout << "Trigger: " << count_elec[2] << endl;  
  cout << "Jet cleaning: " << count_elec[3] << endl;  
  cout << "Vertex cut: " << count_elec[4] << endl;   
  //cout << "Veto on events with electrons in the crack region: " << count_vetocrack << endl; 
  cout << "cosmics veto: " << count_elec[5] << endl;    
  cout << "1-lepton cut: " << count_elec[6] << endl; 
  cout << ">=3 jets(100,25,25): " << count_elec[7] << endl;  
  cout << "Delta phi: " << count_elec[8] << endl;  
  cout << "MET > 250 GeV: " << count_elec[9] << endl; 
  cout << "M_T > 100 GeV: " << count_elec[10] << endl; 
  cout << "MET > 0.3 Meff: " << count_elec[11] << endl;  
  cout << "Meff > 1200 GeV: " << count_elec[12] << endl;   

  histo_cutflow_elec->Write();

  hist_njets_leptoncut_electron->Write();
  hist_njets_signalcut_electron->Write();

  hist_jet1pt_leptoncut_electron->Write();
  hist_jet2pt_leptoncut_electron->Write();
  hist_jet3pt_leptoncut_electron->Write();

  hist_electronpt_leptoncut_electron->Write();

  hist_met_leptoncut_electron->Write();
  hist_met_jetcut_electron->Write();
  hist_met_mtcut_electron->Write();
  hist_met_signalcut_electron->Write();

  hist_mt_leptoncut_electron->Write();
  hist_mt_jetcut_electron->Write();
  hist_mt_metcut_electron->Write();
  hist_mt_signalcut_electron->Write();

  hist_meff_leptoncut_electron->Write();
  hist_meff_jetcut_electron->Write();
  hist_meff_mtcut_electron->Write();
  hist_meff_metcut_electron->Write();
  hist_meff_signalcut_electron->Write();

  outputfile.Close();

  //check if all files have been read 
  if(static_cast<int>(fileList.size())!=filecount)
    {
      std::cerr<<"Not all files read!"<<std::endl;
      //exit(1);
    }
  else
    cout << "All ok." << endl;

#ifdef USEPILEUP
  delete elPileUpTool;
  delete muPileUpTool;
#endif

} // end of Reco_dpd2::Loop


vector<int> Reco_dpd2::get_good_electron_index(int myRunNumber, int kIsData){
  vector<int> elec_index;
  for(int ielec=0;ielec<el_n;ielec++){
    if (susyobj.IsElectron(ielec,myRunNumber, 
			   el_cl_eta->at(ielec), el_cl_phi->at(ielec), el_cl_E->at(ielec), el_tracketa->at(ielec), el_trackphi->at(ielec),
			   el_author->at(ielec), el_mediumPP->at(ielec), el_OQ->at(ielec), el_nPixHits->at(ielec), el_nSCTHits->at(ielec),
			   el_MET_Simplified20_wet->at(ielec).at(0),
			   kIsData,10000.)) {
      elec_index.push_back(ielec);
    }
  }
  return elec_index;
}

vector<int> Reco_dpd2::get_good_electron_index_met(){
  vector<int> elec_index;
  for(int ielec=0;ielec<el_n;ielec++){
    if (el_MET_Simplified20_wet->at(ielec).at(0) != 0)
      elec_index.push_back(ielec);
  }
  return elec_index;
}

vector<int> Reco_dpd2::get_good_electron_index_triggermatch(int elTrigmatch){

  vector<int> elec_index;
  vector<int> *elTrigmatch2;
  if (elTrigmatch == 1) elTrigmatch2 = trig_EF_el_EF_e20_medium;
  if (elTrigmatch == 2) elTrigmatch2 = trig_EF_el_EF_e22_medium;
  if (elTrigmatch == 1 || elTrigmatch == 2){
    for(int ielec=0;ielec<el_n;ielec++){
      int EFindex = -1;
      if (PassedTriggerEF(el_tracketa->at(ielec),el_trackphi->at(ielec),trig_EF_el_EF_e20_medium,
			  EFindex,trig_EF_el_n,trig_EF_el_eta,trig_EF_el_phi))
	elec_index.push_back(ielec);
    }
  }

  if (elTrigmatch == 3){
    for(int ielec2=0;ielec2<el_n;ielec2++){
      int EFindex2 = -1;
      int EFindex3 = -1;
      if (PassedTriggerEF(el_tracketa->at(ielec2),el_trackphi->at(ielec2),trig_EF_el_EF_e22vh_medium1,
			  EFindex2,trig_EF_el_n,trig_EF_el_eta,trig_EF_el_phi) || 
	  PassedTriggerEF(el_tracketa->at(ielec2),el_trackphi->at(ielec2),trig_EF_el_EF_e45_medium1,
			  EFindex3,trig_EF_el_n,trig_EF_el_eta,trig_EF_el_phi)
	  )
	elec_index.push_back(ielec2);
    }
  }

  return elec_index;
}

vector<int> Reco_dpd2::get_overlap_electron_index(vector<int> elec_index_met){
  vector<int> elec_index;
  int n_elec = elec_index_met.size();
  for(int ielec=0;ielec<n_elec;ielec++){
    if (susyobj.GetElecTLV(elec_index_met[ielec]).Pt() > 20000.) elec_index.push_back(elec_index_met[ielec]); 
  }
  return elec_index;
}



vector<int> Reco_dpd2::get_iso_electron_index(int n_jet,vector<int> jet_index, vector<int> elec_index_noiso /*, int kIsData*/){
  vector<int> elec_index;
  int n_elec = elec_index_noiso.size();
  for(int ielec=0;ielec<n_elec;ielec++){
    int overlap_removal = 0;
    for(int jeti = 0; jeti<n_jet; jeti++){
      if (susyobj.GetElecTLV(elec_index_noiso[ielec]).DeltaR(susyobj.GetJetTLV(jet_index[jeti])) <= 0.4) overlap_removal+=1;
    }
    //if (El_JetinDR04(elec_index_noiso[ielec],n_jet,jet_index) == 0)  elec_index.push_back(elec_index_noiso[ielec]); 
    if (overlap_removal == 0) elec_index.push_back(elec_index_noiso[ielec]); 
  }
  return elec_index;
}

vector<int> Reco_dpd2::get_signal_electron_index(vector<int> elec_index){
  vector<int> elec_index_iso;
  int n_elec_iso = elec_index.size();
  for(int ielec_iso=0;ielec_iso<n_elec_iso;ielec_iso++){
    if (susyobj.IsSignalElectron(elec_index[ielec_iso],el_tightPP->at(elec_index[ielec_iso]),
				 el_ptcone20->at(elec_index[ielec_iso]),25000.)) 
      elec_index_iso.push_back(elec_index[ielec_iso]); 
  }
  return elec_index_iso;
}


vector<int> Reco_dpd2::get_good_muon_index(int n_jet,vector<int> jet_index, vector<int> muon_index2 /*, int kIsData*/){
  vector<int> muon_index;
  //int overlap_removal = 0;
  int n_muon = muon_index2.size();
  for(int imuon=0;imuon<n_muon;imuon++){
    //if (mu_staco_ptcone20->at(muon_index2[imuon]) < 1800. && susyobj.IsSignalMuon(mu_staco_z0_exPV->at(muon_index2[imuon])) && Mu_JetinDR04(muon_index2[imuon],n_jet,jet_index) == 0) {
    //if (Mu_JetinDR04(muon_index2[imuon],n_jet,jet_index) == 0  && susyobj.GetMuonTLV(muon_index2[imuon]).Pt() > 20000.) {
    if (Mu_JetinDR04(muon_index2[imuon],n_jet,jet_index) == 0) {
      //for(int jeti = 0; jeti<n_jet; jeti++){
      //	 if (susyobj.GetMuonTLV(muon_index2[imuon]).DeltaR(susyobj.GetJetTLV(jet_index[jeti])) <= 0.4) overlap_removal+=1;
      //}
      //if (overlap_removal == 0) muon_index.push_back(muon_index2[imuon]); 
      muon_index.push_back(muon_index2[imuon]);
    }
  }
  return muon_index;
}

vector<int> Reco_dpd2::get_muon_cosmics(vector<int> muon_index){
  vector<int> muon_index_cosmics;
  int n_muon = muon_index.size();
  for(int imuon=0;imuon<n_muon;imuon++){
    if (susyobj.IsCosmicMuon(mu_staco_z0_exPV->at(muon_index[imuon]),mu_staco_d0_exPV->at(muon_index[imuon]),5.,2.)) {
      muon_index_cosmics.push_back(muon_index[imuon]);
    }
  }
  return muon_index_cosmics;
}

vector<int> Reco_dpd2::get_muon_bad(vector<int> muon_index){
  vector<int> muon_index_bad;
  int n_muon = muon_index.size();
  for(int imuon=0;imuon<n_muon;imuon++){
    //test for cosmic muons or bad muons on the same time
    if (susyobj.IsBadMuon(mu_staco_qoverp_exPV->at(muon_index[imuon]),mu_staco_cov_qoverp_exPV->at(muon_index[imuon]))) {
      muon_index_bad.push_back(muon_index[imuon]);
    }
  }
  return muon_index_bad;
}


vector<int> Reco_dpd2::get_muon_triggermatch(){
  vector<int> muon_index_triggermatch;
  for(int imuon=0;imuon<mu_staco_n;imuon++){
    //test for cosmic muons or bad muons on the same time
    int EFindex = -1;
    int EFtrackindex = -1;
    if(susyobj.MuonHasTriggerMatch((*mu_staco_eta)[imuon],(*mu_staco_phi)[imuon],trig_EF_trigmuonef_EF_mu18,EFindex,EFtrackindex,trig_EF_trigmuonef_n,trig_EF_trigmuonef_track_CB_eta,trig_EF_trigmuonef_track_CB_phi,trig_EF_trigmuonef_track_CB_hasCB)) {
//     if (susyobj.MuonHasTriggerMatch(imuon,mu_staco_n,trig_EF_trigmuonef_n,trig_EF_trigmuonef_track_n,mu_staco_pt,mu_staco_eta, mu_staco_phi,trig_EF_trigmuonef_track_CB_pt,trig_EF_trigmuonef_track_CB_eta,trig_EF_trigmuonef_track_CB_phi, trig_EF_trigmuonef_track_CB_hasCB)) {
      muon_index_triggermatch.push_back(imuon);
    }
  }
  return muon_index_triggermatch;
}


vector<int> Reco_dpd2::get_good_muon_index_iso(vector<int> muon_index){
  vector<int> muon_index_iso;
  int n_muon = muon_index.size();
  for(int imuon=0;imuon<n_muon;imuon++){
    if (susyobj.IsSignalMuon(muon_index[imuon],mu_staco_ptcone20->at(muon_index[imuon]))) {
      muon_index_iso.push_back(muon_index[imuon]);
    }
  }
  return muon_index_iso;
}


vector<int> Reco_dpd2::get_good_muon_index2(int kIsData, string muonsmearing){
  vector<int> muon_index2;
  for(int imuon=0;imuon<mu_staco_n;imuon++){
    if (susyobj.IsMuon(imuon,// EventNumber,
		       mu_staco_pt->at(imuon), mu_staco_eta->at(imuon), mu_staco_phi->at(imuon), mu_staco_E->at(imuon),
		       //mu_staco_qoverp_exPV->at(imuon), mu_staco_cov_qoverp_exPV->at(imuon),
		       mu_staco_me_qoverp_exPV->at(imuon), mu_staco_id_qoverp_exPV->at(imuon),
		       mu_staco_me_theta_exPV->at(imuon), mu_staco_id_theta_exPV->at(imuon),  mu_staco_id_theta->at(imuon),
		       mu_staco_isCombinedMuon->at(imuon), mu_staco_isSegmentTaggedMuon->at(imuon),
		       mu_staco_loose->at(imuon),
		       mu_staco_expectBLayerHit->at(imuon), mu_staco_nBLHits->at(imuon), mu_staco_nPixHits->at(imuon),
		       mu_staco_nPixelDeadSensors->at(imuon), mu_staco_nPixHoles->at(imuon), mu_staco_nSCTHits->at(imuon),
		       mu_staco_nSCTDeadSensors->at(imuon), mu_staco_nSCTHoles->at(imuon), mu_staco_nTRTHits->at(imuon), 
		       mu_staco_nTRTOutliers->at(imuon),
		       kIsData,10000.,2.4, muonsmearing)) muon_index2.push_back(imuon);
  }
  return muon_index2;
}

vector<int> Reco_dpd2::get_good_jet_index(const std::vector<TLorentzVector> & jetlv, int n_elec,vector<int> elec_index, int kIsData, JetErr::Syste whichsyste){

  vector<int> jet_index;
  for(int ijet=0;ijet<jet_AntiKt4TopoNewEM_n;ijet++){
    if (get_jet(ijet, jetlv[ijet], n_elec,elec_index, kIsData, whichsyste)==1) jet_index.push_back(ijet);
  }
  return jet_index;
}

vector<int> Reco_dpd2::get_signal_jet_index(vector<Container> jet){
  vector<int> jet_index_signal;
  int n_jet = jet.size();
  for(int ijet=0;ijet<n_jet;ijet++){
    if (jet_AntiKt4TopoNewEM_jvtxf->at(jet[ijet].index) > 0.75 && jet[ijet].pt > 25000. && fabs(jet[ijet].eta) < 2.5) jet_index_signal.push_back(jet[ijet].index);
  }
  return jet_index_signal;
}

int Reco_dpd2::Mu_JetinDR04(int imuon,int n_jet,vector<int> jet_index){ 

  double dr_jet;
  double diff_phi;
  vector<double> jetptemjes;
  for(int ijet=0;ijet<n_jet;ijet++){
    diff_phi=fabs((*jet_AntiKt4TopoNewEM_phi)[jet_index[ijet]]-((*mu_staco_phi)[imuon]));
    if(diff_phi>3.141592653){
      diff_phi=diff_phi-(2.*3.141592653);
    }
    dr_jet=sqrt(pow(((*jet_AntiKt4TopoNewEM_eta)[jet_index[ijet]]-((*mu_staco_eta)[imuon])),2)+pow(diff_phi,2)); 
    if(dr_jet<=0.4) return 1;	
  }
  return 0;
}

int Reco_dpd2::El_JetinDR04(int ielec,int n_jet,vector<int> jet_index){ 
  
  double dr_jet;
  double diff_phi;
  vector<double> jetptemjes;
  
  for(int ijet=0;ijet<n_jet;ijet++){
    diff_phi=fabs((*jet_AntiKt4TopoNewEM_phi)[jet_index[ijet]]-((*el_phi)[ielec]));
    if(diff_phi>3.141592653){
      diff_phi=diff_phi-(2.*3.141592653);
    }
    dr_jet=sqrt(pow(((*jet_AntiKt4TopoNewEM_eta)[jet_index[ijet]]-((*el_eta)[ielec])),2)+pow(diff_phi,2));
    if(dr_jet<=0.4 && dr_jet>0.2) return 1;
    
  }
  return 0;
}


int Reco_dpd2::get_jet(int ijet, TLorentzVector jetlv, int n_elec, vector<int> elec_index, int kIsData, JetErr::Syste whichsyste){

  int truth_label = 0;
  if(!kIsData) truth_label = jet_AntiKt4TopoNewEM_flavor_truth_label->at(ijet);

  if (susyobj.IsJet(ijet, jetlv.Pt(), jetlv.Eta(), jetlv.Phi(),
		    jetlv.E(), jet_AntiKt4TopoNewEM_emscale_eta->at(ijet), jet_AntiKt4TopoNewEM_emfrac->at(ijet), 
		    jet_AntiKt4TopoNewEM_hecf->at(ijet), jet_AntiKt4TopoNewEM_LArQuality->at(ijet), jet_AntiKt4TopoNewEM_HECQuality->at(ijet), 
		    jet_AntiKt4TopoNewEM_AverageLArQF->at(ijet),
		    jet_AntiKt4TopoNewEM_Timing->at(ijet), jet_AntiKt4TopoNewEM_sumPtTrk->at(ijet), jet_AntiKt4TopoNewEM_fracSamplingMax->at(ijet),
		    jet_AntiKt4TopoNewEM_NegativeE->at(ijet),
		    truth_label,
		    kIsData,20000.,10., JetID::VeryLooseBad, whichsyste) 
      && susyobj.GetJetTLV(ijet).Pt() > 20000. && fabs(susyobj.GetJetTLV(ijet).Eta()) < 2.8) {	    
    double dr_jet;
    double diff_phi;
    for(int iele=0;iele<n_elec;iele++){
      diff_phi=fabs(jetlv.Phi()-susyobj.GetElecTLV(elec_index[iele]).Phi());
      if(diff_phi>3.141592653){
	diff_phi=diff_phi-(2.*3.141592653);
      }
      dr_jet=sqrt(pow((jetlv.Eta()-susyobj.GetElecTLV(elec_index[iele]).Eta()),2)+pow(diff_phi,2));
      if(dr_jet<=0.2) return 0;
    }
    
    return 1;
  }
  return 0;
}


double Reco_dpd2::calculate_meff(vector<int> jet, int n_elec, int n_muon, vector<int> elec_index, vector<int> muon_index, double met, bool inclusive){

  double meff=met;
  int maxjet;
  if (inclusive) maxjet=jet.size();
  else {
    if(jet.size()>=3) maxjet=3;
    else maxjet=jet.size();
  }
  for(int jet0=0;jet0<maxjet;jet0++) {
    TLorentzVector tljet = susyobj.GetJetTLV(jet[jet0]);
    meff+= tljet.Pt();
  }
  for(int el=0;el<n_elec;el++) {
    TLorentzVector tlelec = susyobj.GetElecTLV(elec_index[el]);
    meff += tlelec.Pt();
  }
  for(int mu=0;mu<n_muon;mu++) {
    TLorentzVector tlmuon = susyobj.GetMuonTLV(muon_index[mu]);
    meff += tlmuon.Pt();
  }
  return meff;
}




double Reco_dpd2::calculate_mt_1lepton(int n_elec, int n_muon, vector<int> elec_index, vector<int> muon_index, double metx, double mety, double met){
  
  double mt=0.; 
  if(n_muon==1) {
    TLorentzVector tlmuon = susyobj.GetMuonTLV(muon_index[0]);
    double p1p2=( (tlmuon.Px())*metx+(tlmuon.Py())*mety );
    double cosphi=p1p2/(tlmuon.Pt()*met);
    mt=sqrt(2*tlmuon.Pt()*met*(1-cosphi));
  }
  else if(n_elec==1) {
    TLorentzVector tlelec = susyobj.GetElecTLV(elec_index[0]);
    double p1p2=( (tlelec.Px())*metx+(tlelec.Py())*mety );
    double cosphi=p1p2/(tlelec.Pt()*met);
    mt=sqrt(2*tlelec.Pt()*met*(1-cosphi));	  
  }
  else std::cout << "ERROR !!! The number of lepton is incorrect in MT calculation!" <<std::endl;
  
  return mt;
}


