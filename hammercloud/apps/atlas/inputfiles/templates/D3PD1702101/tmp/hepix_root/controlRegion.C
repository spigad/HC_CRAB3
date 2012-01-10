
//select if you want to calculate QCD normalization
//#define NORM

//#define DATA

//#define ELECTRON   //defined as electron trigger
//#define MUON     //defined as muon trigger
//#define QCDFROMDATA

#define MC
#define JX
#define MUON
#define ZJETS
#define WJETS
#define DY
#define SU4
#define DIBOSON
#define TTBAR
//#define MSUGRA

//#define CONTROLREGION
//#define SIGNALREGION
#define CUTFLOW

#define H1D


  double lumi         = 15653.; //nb	
  TString lumi_string = "15653"; //nb	

const char *name_cutflow[]={
  "no cut",
  "GRL cut",
  "trigger cut ( L1Calo && TrgEl) || (MuonswBeam && TrgMu) || ( MC && (trgEl || trgMu))",
  "jet cleaning",
  " >= 1 vertex with >4 tracks (No cut on vertex type!!)",
  "crack + cosmic veto",
  "1-lepton cut (>= 1 lepton  - pt > 10 GeV)", 
  "1-lepton cut (== 1 lepton  - pt > 20 GeV -- not applied)", 
  "2-lepton cut (>= 2 leptons - pt > 10 GeV)", 
  "at least 1 lepton pt > 20 GeV -- ((L1Calo || MC) && trgEl && Elpt20) || ( (MuonswBeam || MC) && trgMu && Mupt20)", 
  "== 2 leptons ", 
//  "crack veto   (not isolated e before OR)",
//  "OTX veto     (not isolated e before OR)",
//  "z0 muon veto (selected mu)",
  "EE || MUMU || EMU (see below for definition)", 
  "dilepton mass > 5 GeV  -- not applied",
//  "1 jet pt > 50 GeV  -- not applied",
  "EE -- (L1Calo || MC) && trgEl && 2 electrons  -- not applied", 
  "EE && OS (not applied)",
  "EE && MET cut > 100 GeV (not applied)",
  "EE && MET && Mll > 70 GeV (not applied)",
//  "EE && MET && jet cut (not applied) ",
  "EMU -- ((L1Calo || MC) && TrgEl && elPt20) || ((MuonStream || MC) && (TrgMu && Mu20)&&!(TrgEl&&El20)) -- not applied", 
  "EMU && OS (not applied)",
//  "EMU && 1 jet pt > 50 GeV (not applied)",
  "EMU && MET cut > 100 GeV (not applied)",
  "EMU && MET && Mll > 70 GeV (not applied) ",
  "MUMU -- (MuonswBeam || MC) && trgMu && 2 muons  -- not applied", 
  "MUMU && OS (not applied)",
//  "MUMU && 1 jet pt > 50 GeV (not applied)",
  "MUMU && MET cut > 100 GeV (not applied)",
  "MUMU && MET && Mll > 70 GeV (not applied) "
  };
  

const char *name_controlregion[]={
 "MET<20 GeV, !(60<Mll<80 GeV), SS", "MET<20 GeV, !(60<Mll<80 GeV)","MET<20 GeV, !(60<Mll<80 GeV), 1 jet pt>50 GeV",  //QCD
 "MET<30 GeV, !(60<Mll<80 GeV), SS", "MET<30 GeV, !(60<Mll<80 GeV)","MET<30 GeV, !(60<Mll<80 GeV), 1 jet pt>50 GeV",
 "MET<40 GeV, !(60<Mll<80 GeV), SS", "MET<40 GeV, !(60<Mll<80 GeV)","MET<40 GeV, !(60<Mll<80 GeV), 1 jet pt>50 GeV",
 "MET<20 GeV, 80<Mll<100 GeV, OS","MET<30 GeV, 80<Mll<100 GeV, OS", "MET<40 GeV, 80<Mll<100 GeV, OS", // Z jets
 "30<MET<50 GeV, 40<MT<80 GeV", "40<MET<60 GeV, 40<MT<80 GeV", "40<MET<60 GeV, 60<MT<80" // W jets 
 };

const char *name_signalregion[]={
 "MET>20 GeV, 1 jet pt>20 GeV, MT>40 GeV", "MET>40 GeV, 1 jet pt>20 GeV, MT>40 GeV", "MET>60 GeV, 1 jet pt>20 GeV, MT>40 GeV",  
 "MET>20 GeV, 1 jet pt>30 GeV, MT>40 GeV", "MET>20 GeV, 1 jet pt>40 GeV, MT>40 GeV", "MET>20 GeV, 1 jet pt>50 GeV, MT>40 GeV",  
 "MET>60 GeV, 1 jet pt>20 GeV, MT>60 GeV", "MET>60 GeV, 1 jet pt>40 GeV, MT>80 GeV", "MET>60 GeV, 1 jet pt>20 GeV, MT>100 GeV",  
 "MET>40 GeV, 1 jet pt>30 GeV, MT>40 GeV", "MET>40 GeV, 1 jet pt>40 GeV, MT>40 GeV", "MET>40 GeV, 1 jet pt>50 GeV, MT>40 GeV",  
 "MET>60 GeV, 1 jet pt>30 GeV, MT>80 GeV", "MET>60 GeV, 1 jet pt>40 GeV, MT>80 GeV", "MET>60 GeV, 1 jet pt>50 GeV, MT>80 GeV"  
 };


#ifdef CUTFLOW
  TString histo_string = "cutflow_histo";
  TString x_string = "cutflow";
  TString y_string = "entries";
#endif
#ifdef CONTROLREGION
  TString histo_string = "controlregion_histo";
  TString x_string = "control region";
  TString y_string = "entries";
#endif
#ifdef SIGNALREGION
  histo_string = "signalregion_histo";
  x_string = "signal region";
  y_string = "entries";
#endif
 
  
#include "AtlasStyle.C"
#include "input.h"
TH1D  *histo_data, *histo_drellyan, *histo_diboson, *histo_qcd_data, *histo_qcd, *histo_qcd_mu, *histo_qcd_total,*histo_wjets, *histo_zjets, *histo_ttbar, *histo_su4;
#include "histo.h"
 
 
// plot 
void controlRegion() {
  
  fillHisto();

  std::cout << "lumi " << lumi <<" nb-1"<< std::endl;  

  // number of events
  
#ifdef CONTROLREGION
#ifdef DATA
  cout << "TOTAL data contribution:  " << histo_data->Integral() << endl;
#endif
  cout << "TOTAL QCD contribution:   " << histo_qcd_total->Integral() << endl;

    Double_t nbin_content     = 0;
    Double_t nbin_content_data_qcd  = 0;

    std::cout <<"CR : data : data qcd : ";
    
#ifdef JX
    std::cout <<"qcd :";
#endif
#ifdef WJETS
    std::cout <<"wjets :";
#endif
#ifdef ZJETS
    std::cout <<" zjets :";
#endif
#ifdef DY
    std::cout <<" drellyan :";
#endif
#ifdef SU4
    std::cout <<" su4: ";
#endif
#ifdef TTBAR
    std::cout <<" ttbar:";
#endif
#ifdef DIBOSON
    std::cout <<" diboson:";
#endif

#ifdef SIGNALREGION 
    std::cout <<"S/sqrt(B)"<<std::endl;
#else  
    std::cout <<"NORM"<<std::endl;
#endif  

  for (int cf = 0; cf < 15; cf++)
  {

#ifdef DATA
    nbin_content     = histo_data      ->GetBinContent(cf+1);
#endif
#ifdef QCDFROMDATA
    nbin_content_data_qcd     = histo_qcd_data      ->GetBinContent(cf+1);
#endif

Double_t nbin_mc = 0;

#ifdef JX
    Double_t nbin_content_qcd = histo_qcd_total ->GetBinContent(cf+1);
    nbin_mc += nbin_content_qcd;
#endif
#ifdef WJETS
    Double_t nbin_content_wjets = histo_wjets ->GetBinContent(cf+1);
    nbin_mc += nbin_content_wjets;
#endif
#ifdef ZJETS
    Double_t nbin_content_zjets = histo_zjets ->GetBinContent(cf+1);
    nbin_mc += nbin_content_zjets;
#endif
#ifdef DY
    Double_t nbin_content_drellyan = histo_drellyan ->GetBinContent(cf+1);
    nbin_mc += nbin_content_drellyan;
#endif
#ifdef SU4
    Double_t nbin_content_su4 = histo_su4 ->GetBinContent(cf+1);
    nbin_mc += nbin_content_su4;
#endif
#ifdef TTBAR
    Double_t nbin_content_ttbar = histo_ttbar ->GetBinContent(cf+1);
    nbin_mc += nbin_content_ttbar;
#endif
#ifdef DIBOSON
    Double_t nbin_content_diboson = histo_diboson ->GetBinContent(cf+1);
    nbin_mc += nbin_content_diboson;
#endif

    std::cout << cf 
    
      << " : " <<  (int)nbin_content
      << " : " <<  (int)nbin_content_data_qcd;
    
    if (nbin_mc == 0.) nbin_mc = 0.000000000000001;
      
#ifdef JX
      std::cout<< " : " <<  nbin_content_qcd<< " (" << 100.*nbin_content_qcd/nbin_mc <<" %)";
#endif
#ifdef WJETS
      std::cout<< " : " <<  nbin_content_wjets  << " (" << 100.*nbin_content_wjets/nbin_mc <<" %)";
#endif
#ifdef ZJETS
      std::cout<< " : " <<  nbin_content_zjets  << " (" << 100.*nbin_content_zjets/nbin_mc <<" %)";
#endif
#ifdef DY
      std::cout<< " : " <<  nbin_content_drellyan  << " (" << 100.*nbin_content_drellyan/nbin_mc <<" %)";
#endif
#ifdef TTBAR
      std::cout<< " : " <<  nbin_content_ttbar << " (" << 100.*nbin_content_ttbar/nbin_mc <<" %)";
#endif
#ifdef SU4
      std::cout<< " : " <<  nbin_content_su4	  << " (" << 100.*nbin_content_su4/nbin_mc <<" %)";     
#endif
#ifdef DIBOSON
      std::cout<< " : " <<  nbin_content_diboson  << " (" << 100.*nbin_content_diboson/nbin_mc <<" %)";     
#endif

#ifdef SIGNALREGION 
      double sign = nbin_content_su4/sqrt(nbin_mc); 
      std::cout << " : "<< sign;
      std::cout << "                    : "<< name_signalregion[cf];
#else  
      Double_t norm = nbin_content/nbin_content_data_qcd;
      Double_t norm_err = sqrt( nbin_content /nbin_content_data_qcd /nbin_content_data_qcd  + nbin_content *nbin_content/nbin_content_data_qcd/nbin_content_data_qcd/nbin_content_data_qcd ); 
      std::cout << " : "<<norm <<" +/- "<<norm_err<<std::endl;
      std::cout << "                    : "<< name_controlregion[cf];
#endif  
      std::cout<<std::endl;
  }
#endif
 
#ifdef CUTFLOW
  
#ifdef DATA  
  cout << endl<<" DATA "<<endl<<endl;   
  for (int cf = 0; cf < 25; cf++)
  {
    Double_t nbin_content = histo_data->GetBinContent(cf+1);
    std::cout << "cut "<< cf <<" :     " <<  (int)nbin_content<< "       "<< name_cutflow[cf]<<std::endl;    
  }
#endif     

#ifdef MC  
  cout << endl<<" MC "<< " lumi " << lumi<<endl<<endl;   

#ifdef JX 
  cout << endl<<" qcd Jx "<< " lumi (nb-1): " << lumi<<endl<<endl;   
  for (int cf = 0; cf < 25; cf++)
  {
    Double_t nbin_content = histo_qcd->GetBinContent(cf+1);
    std::cout << "cut "<< cf <<" :     " <<  nbin_content<< "       "<< name_cutflow[cf]<<std::endl;    
  }
#endif     
  
#ifdef JXMUON 
  cout << endl<<" qcd Jx muon "<< " lumi (nb-1): " << lumi<<endl<<endl;   
  for (int cf = 0; cf < 25; cf++)
  {
    Double_t nbin_content = histo_qcd_mu->GetBinContent(cf+1);
    std::cout << "cut "<< cf <<" :     " <<  nbin_content<< "       "<< name_cutflow[cf]<<std::endl;    
  }
#endif     

#ifdef WJETS 
  cout << endl<<" Wjets "<< " lumi (nb-1):" << lumi<<endl<<endl;   
  for (int cf = 0; cf < 25; cf++)
  {
    Double_t nbin_content = histo_wjets->GetBinContent(cf+1);
    std::cout << "cut "<< cf <<" :     " <<  nbin_content<< "       "<< name_cutflow[cf]<<std::endl;    
  }
#endif     

#ifdef ZJETS 
  cout << endl<<" Zjets "<< " lumi (nb-1):" << lumi<<endl<<endl;   
  for (int cf = 0; cf < 25; cf++)
  {
    Double_t nbin_content = histo_zjets->GetBinContent(cf+1);
    std::cout << "cut "<< cf <<" :     " <<  nbin_content<< "       "<< name_cutflow[cf]<<std::endl;    
  }
#endif     

#ifdef TTBAR 
  cout << endl<<" ttbar "<< " lumi (nb-1): " << lumi<<endl<<endl;   
  for (int cf = 0; cf < 25; cf++)
  {
    Double_t nbin_content = histo_ttbar->GetBinContent(cf+1);
    std::cout << "cut "<< cf <<" :     " <<  nbin_content<< "       "<< name_cutflow[cf]<<std::endl;    
  }
#endif     

#ifdef DIBOSON 
  cout << endl<<" diboson"<< " lumi (nb-1): " << lumi<<endl<<endl;   
  for (int cf = 0; cf < 25; cf++)
  {
    Double_t nbin_content = histo_diboson->GetBinContent(cf+1);
    std::cout << "cut "<< cf <<" :     " <<  nbin_content<< "       "<< name_cutflow[cf]<<std::endl;    
  }
#endif     

#ifdef SU4 
  cout << endl<<" SU4 "<< " lumi (nb-1): " << lumi<<endl<<endl;   
  for (int cf = 0; cf < 25; cf++)
  {
    Double_t nbin_content = histo_su4->GetBinContent(cf+1);
    std::cout << "cut "<< cf <<" :     " <<  nbin_content<< "       "<< name_cutflow[cf]<<std::endl;    
  }
#endif     

#ifdef MSUGRA 
  cout << endl<<" MSUGRA "<< " lumi (nb-1): " << lumi<<endl<<endl;   
  for (int cf = 0; cf < 25; cf++)
  {
    Double_t nbin_content = h1_114013->GetBinContent(cf+1);
    std::cout << "cut "<< cf <<" :     " <<  nbin_content<< "       "<< name_cutflow[cf]<<std::endl;    
  }
#endif     

#endif     
#endif 

}
