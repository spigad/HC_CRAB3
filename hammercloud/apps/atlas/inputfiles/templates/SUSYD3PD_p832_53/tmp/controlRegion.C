#include <iostream>
#include <stdio.h> 
#include <string.h>

//select if you want to calculate QCD normalization
//#define NORM

#define DATA

//#define ELECTRON   //defined as electron trigger
#define MUON     //defined as muon trigger
//#define QCDFROMDATA

//#define MC
//#define JX
//#define QCDEE
//#define JXMUON
//#define ZJETS
//#define WJETS
//#define DY
//#define SU4
//#define DIBOSON
//#define TTBAR
//#define MSUGRA
//#define PILEUP

//#define CONTROLREGION
//#define SIGNALREGION
#define CUTFLOW

#define H1D


//  double lumi         = 1035180; //nb	 ELECTRON STREAM
  double lumi         = 1035040; //nb	 MUON STREAM
  TString lumi_string = "1035.18"; //nb	
  
char const*  name_cutflow[]={
#ifdef MC  
  "no cut - with Pileup reweight",
  "no cut",
#else 
  "no cut",
  "GRL cut",
#endif
  "Lar error cut",
//  "Lar veto electron", //OBSOLETE
  "Lar veto jet",
  "jet cleaning",
  ">= 1 vertex with > 4 tracks",
  "Bad muon veto",
  "Cosmic veto",

#ifdef ELECTRON
  "EE", 
#endif
#ifdef MUON
  "MUMU", 
#endif
  " && mll cut",
  " && OS ",
//  " && OS && TightIso",
  " && OS && Jet veto ",
  " && OS && Jet veto && Z veto ",
  " [SR1] && Jet veto && Z veto && METRel > 100 GeV",
  " && OS && nJet >= 2",
  " && OS && nJet >= 2 && Z veto",
  " && OS && nJet >= 2 && Z veto && Bjet veto",
  " && OS && nJet >= 2 && Z veto && Bjet veto && MCT Veto",
  " [SR3] && nJet >= 2 && Z veto && Bjet veto && MCT Veto && METRel > 50 GeV",
  " && OS && Jet veto && Z veto && METRel > 40 GeV",
  " && OS && Jet veto && Z veto && METRel > 40 GeV && Pt(l1) > 50 GeV",
  " && OS && Jet veto && Z veto && METRel > 40 GeV && Pt(l1) > 50 GeV && Pt(l1)+Pt(l2) > 100 GeV",
  " && OS && Jet veto && Z veto && METRel > 40 GeV && Pt(l1) > 50 GeV && Pt(l1)+Pt(l2) > 100 GeV && dPhi(MET,ll) > 2.5",
  " [SR4] && Jet veto && Z veto && METRel > 40 GeV && Pt(l1) > 50 GeV && Pt(l1)+Pt(l2) > 100 GeV && dPhi(MET,ll) > 2.5 && dPhi(MET,l2) > 0.5",
  " [SR5] && Jet veto && Z veto && METRel > 40 GeV && mT2 > 90 GeV",
  " && SS ",
  " && SS && Jet veto",
  " [SR2] && Jet veto && METRel > 100 GeV",
    
  "EMU ", 
  " && mll cut", 
  " && OS ",
  " && OS && Jet veto ",
  " && OS && Jet veto && Z veto ",
  " [SR1] && Jet veto && Z veto && METRel > 100 GeV",
  " && SS ",
  " && SS && Jet veto",
  " [SR2] && Jet veto && METRel > 100 GeV",
  };
  

  TString histo_string = "cutflow_histo";
  TString x_string = "cutflow";
  TString y_string = "entries";
 
  
#include "AtlasStyle.C"
#include "input.h"
TH1D  *histo_data, *histo_drellyan, *histo_diboson, *histo_qcd_data, *histo_qcd, *histo_qcd_mu, *histo_qcd_total,*histo_wjets, *histo_zjets, *histo_ttbar, *histo_su4;
#include "histo.h"
 
using namespace std;
 
// plot 
void controlRegion() {
  
  fillHisto();

  std::cout << "lumi " << lumi <<" nb-1"<< std::endl;  

 //unsigned int size = sizeof name_cutflow / sizeof *name_cutflow;
 unsigned int size = 37;

 
#ifdef CUTFLOW
  
#ifdef DATA  
  cout << endl<<" DATA "<<endl<<endl; 
  for (int cf = 0; cf < size; cf++)
  {
    Double_t nbin_content = histo_data->GetBinContent(cf+1);
    std::cout << "cut "<< cf <<" :     " <<  (int)nbin_content<< "       "<< name_cutflow[cf]<<std::endl;    
  }
#endif     

#ifdef MC  
  cout << endl<<" MC "<< " lumi " << lumi<<endl<<endl;   
  std::cout<<   fixed ;      
  cout.precision(2);      

#ifdef JX 
  cout << endl<<" qcd Jx "<< " lumi (nb-1): " << lumi<<endl<<endl;   
  for (int cf = 0; cf < size; cf++)
  {
    Double_t nbin_content = histo_qcd->GetBinContent(cf+1);
    std::cout << "cut "<< cf <<" :     " <<  nbin_content<< "       "<< name_cutflow[cf]<<std::endl;    
  }
#endif     
#ifdef QCDEE 
  cout << endl<<" qcd (ee) "<< " lumi (nb-1): " << lumi<<endl<<endl;
  for (int cf = 0; cf < size; cf++)
  {
    Double_t nbin_content = histo_qcd->GetBinContent(cf+1);    std::cout << "cut "<< cf <<" :     " <<  nbin_content<< "       "<< name_cutflow[cf]<<std::endl;  }
#endif
  
#ifdef JXMUON 
  cout << endl<<" qcd Jx muon "<< " lumi (nb-1): " << lumi<<endl<<endl;   
  for (int cf = 0; cf < size; cf++)
  {
    Double_t nbin_content = histo_qcd_mu->GetBinContent(cf+1);
    std::cout << "cut "<< cf <<" :     " <<  nbin_content<< "       "<< name_cutflow[cf]<<std::endl;    
  }
#endif     

#ifdef WJETS 
  cout << endl<<" Wjets "<< " lumi (nb-1):" << lumi<<endl<<endl;   
  for (int cf = 0; cf < size; cf++)
  {
    Double_t nbin_content = histo_wjets->GetBinContent(cf+1);
    std::cout << "cut "<< cf <<" :     " <<  nbin_content<< "       "<< name_cutflow[cf]<<std::endl;    
  }
#endif     

#ifdef ZJETS 
  cout << endl<<" Zjets "<< " lumi (nb-1):" << lumi<<endl<<endl;   
  for (int cf = 0; cf < size; cf++)
  {
    Double_t nbin_content = histo_zjets->GetBinContent(cf+1);
    std::cout << "cut "<< cf <<" :     " <<  nbin_content<< "       "<< name_cutflow[cf]<<std::endl;    
  }
#endif     

#ifdef TTBAR 
  cout << endl<<" ttbar "<< " lumi (nb-1): " << lumi<<endl<<endl;   
  for (int cf = 0; cf < size; cf++)
  {
    Double_t nbin_content = histo_ttbar->GetBinContent(cf+1);
    std::cout << "cut "<< cf <<" :     " <<  nbin_content<< "       "<< name_cutflow[cf]<<std::endl;    
  }
#endif     

#ifdef DIBOSON 
  cout << endl<<" diboson"<< " lumi (nb-1): " << lumi<<endl<<endl;   
  for (int cf = 0; cf < size; cf++)
  {
    Double_t nbin_content = histo_diboson->GetBinContent(cf+1);
    std::cout << "cut "<< cf <<" :     " <<  nbin_content<< "       "<< name_cutflow[cf]<<std::endl;    
  }
#endif     

#ifdef SU4 
  cout << endl<<" SU4 "<< " lumi (nb-1): " << lumi<<endl<<endl;   
  for (int cf = 0; cf < size; cf++)
  {
    Double_t nbin_content = histo_su4->GetBinContent(cf+1);
    std::cout << "cut "<< cf <<" :     " <<  nbin_content<< "       "<< name_cutflow[cf]<<std::endl;    
  }
#endif     

#ifdef MSUGRA 
  cout << endl<<" MSUGRA "<< " lumi (nb-1): " << lumi<<endl<<endl;   
  for (int cf = 0; cf < size; cf++)
  {
    Double_t nbin_content = h1_114013->GetBinContent(cf+1);
    std::cout << "cut "<< cf <<" :     " <<  nbin_content<< "       "<< name_cutflow[cf]<<std::endl;    
  }
#endif     

#endif     
#endif 

}
