#define DATA
#define ELECTRON
#define MUON

#define MC
#define JX
#define MUON
#define ZJETS
#define WJETS
#define DY
#define SU4
#define DIBOSON
#define TTBAR

//#define QCDFROMDATA // qcd from data
#define NORM // subtract MC SM contributions and normalize
#define NORMMU // subtract MC SM contributions and normalize


//#define OS
#define SS

//#define MET
#define MLL
//#define JETPT
//#define MT

//#define REBIN
#define H2D

//avoid root crash fist time that the macro runs...
#define FIRSTROOT


  double lumi         = 15653.; //nb	
  TString lumi_string = "15.7 pb-1"; //nb	

#ifdef ELECTRON
  TString title2 = "Dielectron channel";
#ifdef MUON
  TString title2 = "Dilepton channel";
#endif
#endif

#ifdef MUON
  TString title2 = "Dimuon channel";
#ifdef ELECTRON
  TString title2 = "Dilepton channel";
#endif
#endif

#ifdef JETPT
  TString x_string = "Leading jet pt [GeV]";
  TString title = title2 + " SS+OS";    
  TString histo_string = "jetl_pt";
  Double_t x_min = 20.;
  Double_t x_max = 400;
#endif

#ifdef MT
  TString x_string = "Transverse mass [GeV]";
  TString title = title2 + " SS+OS";    
  TString histo_string = "mt";
  Double_t x_min = 20.;
  Double_t x_max = 400;
#endif

#ifdef MET
  TString x_string = "E_{T,miss} [GeV]";
  TString title = title2 +" SS+OS";
  TString histo_string = "met_mu";
  Double_t x_min = 0.;
  Double_t x_max = 200;
#ifdef OS
  TString histo_string = "met_OS";
  TString title = title2 + " OS";
#endif
#ifdef SS
  TString histo_string = "met_SS";
  TString title = title2 + " SS";
#endif
#endif

#ifdef MLL
  Double_t x_min = 5.;
  Double_t x_max = 200;
  TString title = title2 + " SS+OS";
  TString histo_string = "invmass";
  TString x_string = "Dilepton mass [GeV]";
#ifdef OS
  TString histo_string = "invmass_OS";
  TString title = title2 + " OS";
#endif
#ifdef SS
  TString histo_string = "invmass_SS";
  TString title = title2 + " SS";
#endif
#endif

  TString y_string = "Entries / 5 GeV";
#ifdef REBIN
  y_string = "Entries / 10 GeV";
#endif

#ifdef ELECTRON
  TString title2 = "Dielectron channel";
#ifdef MUON
  TString title2 = "";
#endif
#endif

#ifdef ELECTRON
  TString title2 = "Dimuon channel";
#ifdef MUON
  TString title2 = "";
#endif
#endif


//Axis labels:

//y-axis labels: Entries / x Units (x = bin width, Units = e.g. GeV)
//x-axis labels: Quantity [Unit] (Quantity = e.g. M_{eff}, Units = e.g. GeV)
    
//int binmin = 1;       //   "no cut",
//int binmin = 2;       //   "GRL cut",
//int binmin = 3;       //   "trigger cut ( L1Calo && EF_g10_loose) || (MuonswBeam && L1_MU6) || ( MC && (EF_g10_loose || L1_MU6))",
//int binmin = 4;       //   "jet cleaning",
//int binmin = 5;       //   " >= 1 vertex with >4 tracks (No cut on vertex type!!)",
//int binmin = 6;       //   "1-lepton cut (>= 1 lepton  - pt > 10 GeV)", 
//int binmin = 7;       //  "1-lepton cut (== 1 lepton  - pt > 20 GeV -- not applied)", 
//int binmin = 8;       //  "2-lepton cut (>= 2 leptons - pt > 10 GeV)", 
//int binmin = 9;       //  "at least 1 lepton pt > 20 GeV -- ((L1Calo || MC) && trgEl && Elpt20) || ( (MuonswBeam || MC) && trgMu && Mupt20)", 
//int binmin = 10;       //  "== 2 leptons ", 
//int binmin = 11;       //  "crack veto   (not isolated e before OR)",
//int binmin = 12;       //  "OTX veto     (not isolated e before OR)",
//int binmin = 13;       //  "z0 muon veto (selected mu)",
int binmin = 14;       //  "EE || MUMU || EMU (see below for definition)", 
//int binmin = 15;       //  "dilepton mass > 5 GeV",
//int binmin = 16;         // "1 jet pt > 20 GeV  -- not applied",
//int binmin = 17;       //  "EE -- (L1Calo || MC) && trgEl && 2 electrons  -- not applied", 
//int binmin = 18;       //  "EE && OS (not applied)",
//int binmin = 19;       //  "EE && 1 jet pt > 20 GeV (not applied)",
//int binmin = 20;       //  "EE && MET cut > 20 GeV (not applied)",
//int binmin = 21;       //  "EE && MET && jet cut (not applied) ",
//int binmin = 22;       //  "EMU -- ((L1Calo || MC) && TrgEl && elPt20) || ((MuonStream || MC) && (TrgMu && Mu20)&&!(TrgEl&&El20)) -- not applied", 
//int binmin = 23;       //  "EMU && OS (not applied)",
//int binmin = 24;       //  "EMU && 1 jet pt > 20 GeV (not applied)",
//int binmin = 25;       //  "EMU && MET cut > 20 GeV (not applied)",
//int binmin = 26;       //  "EMU && MET && jet cut (not applied) ",
//int binmin = 27;       //  "MUMU -- (MuonswBeam || MC) && trgMu && 2 muons  -- not applied", 
//int binmin = 28;       //  "MUMU && OS (not applied)",
//int binmin = 29;       //  "MUMU && 1 jet pt > 20 GeV (not applied)",
//int binmin = 30;       //  "MUMU && MET cut > 20 GeV (not applied)",
//int binmin = 31;       //  "MUMU && MET && jet cut (not applied) "
  
int binmax =binmin;
  
#include "AtlasStyle.C"
#include "input.h"
#ifdef DATA
TH1D  *histo_data, *histo_qcd_data, TGraphAsymmErrors* graph_data;
#endif
#ifdef MC
TH1D *histo_drellyan, *histo_diboson, *histo_qcd, *histo_qcd_mu, *histo_qcd_total,*histo_wjets, *histo_zjets, *histo_ttbar, *histo_su4;
#endif

#include "histo.h"
#include "error.h"
 
 
// plot 
void makePlots() {

  ///  Draw */
  
  TCanvas *c1 = new TCanvas("canvas","canvas", 200,10,800,600);  // 1D histo
//  TCanvas *c1 = new TCanvas("canvas","canvas", 200,10,600,600);  // 2D histo
  
  gROOT->SetStyle("ATLAS");
  SetAtlasStyle();
  gROOT->ForceStyle();

  c1->SetLogy();

  fillHisto(); // combine samples 
    
  Double_t err=0.;
  
#ifdef DATA
  cout << "data  : " << (int)(histo_data->IntegralAndError(0, (histo_data->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;

  graph_data = TH1TOTGraphAsymNoerrorx(histo_data, 1.);  
  graph_data->SetMarkerStyle(20);
  graph_data->SetMarkerSize(1.2);  
  graph_data->SetLineWidth(3.);
#else //allow plotting also without data
  TH1D*  histo_data = histo_wjets->Clone("histo_data");
  histo_data->Reset();
#endif
#ifdef REBIN
  histo_data->Rebin(2);
#endif
#ifdef MC
  addErrors();

#ifdef QCDFROMDATA
  cout << "QCD from data  : " << (histo_qcd_data->IntegralAndError(0, (histo_qcd_data->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;
  cout << "QCD from Jx  : " << (histo_qcd->IntegralAndError(0, (histo_qcd->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;
#endif

  TH1D* histo_mc = histo_qcd_total->Clone("histo_mc");

  histo_mc	->Add(histo_wjets, 1.);
  histo_mc	->Add(histo_drellyan, 1.);
  histo_mc	->Add(histo_ttbar, 1.);
  histo_mc	->Add(histo_zjets, 1.);  
  histo_mc	->Add(histo_diboson, 1.);  

  histo_mc->SetXTitle(x_string);
  histo_mc->SetYTitle(y_string);
  histo_mc->SetFillColor(kWhite);
  histo_mc->SetLineColor(kRed);

  cout << "MC      : " << (histo_mc       ->IntegralAndError(0, (histo_mc->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 
  cout << "QCD     : " << (histo_qcd_total->IntegralAndError(0, (histo_qcd_total->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;
  cout << "Wjets   : " << (histo_wjets    ->IntegralAndError(0, (histo_wjets->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;    
  cout << "Zjets   : " << (histo_zjets    ->IntegralAndError(0, (histo_zjets->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;    
  cout << "DY      : " << (histo_drellyan ->IntegralAndError(0, (histo_drellyan->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 
  cout << "ttbar   : " << (histo_ttbar    ->IntegralAndError(0, (histo_ttbar->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;    
  cout << "su4     : " << (histo_su4      ->IntegralAndError(0, (histo_su4->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;      
  cout << "diboson : " << (histo_diboson  ->IntegralAndError(0, (histo_diboson->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;      

#ifdef REBIN
  histo_ttbar->Rebin(2);
  histo_wjets->Rebin(2);
  histo_drellyan->Rebin(2);
  histo_zjets->Rebin(2);
  histo_qcd_total->Rebin(2);
  histo_su4->Rebin(2);
  histo_diboson->Rebin(2);
  histo_mc->Rebin(2);
#endif

  THStack* histo_stack  = new THStack();
  histo_stack->Add(histo_ttbar);
  histo_stack->Add(histo_drellyan);
  histo_stack->Add(histo_diboson);
  histo_stack->Add(histo_zjets);
  histo_stack->Add(histo_wjets);
  histo_stack->Add(histo_qcd_total);
  histo_stack->Add(histo_su4);
  
  TH1D* histo_mc_clone = histo_mc->Clone("histo_mc_clone"); // <== cloned MC
  
  histo_mc->SetFillColor(kYellow);
  histo_mc->SetFillStyle(3002); 
  histo_mc->SetMarkerSize(0);  

#endif

  
// start drawing
  
  histo_data->SetMinimum(0.01); 
  histo_data->SetMaximum(20000.);
#endif
//  histo_data->GetXaxis()->SetRangeUser(0.,100.); //MET
  histo_data->GetXaxis()->SetRangeUser(x_min,x_max);  //inv mass
  histo_data->Draw("AXIS"); //draws only the axis
#ifdef MC

#ifdef FIRSTROOT
#else
  histo_stack->Draw("hist same");
#endif
  
#ifdef MC
  histo_mc->Draw("e2 same");
  histo_mc_clone->Draw("hist same");
#endif


  histo_mc_clone->Draw("hist same ][");// ROOT CRASHES!!
/*
  histo_qcd->Draw("hist bar same");
  histo_zjets->Draw("hist same bar");
  //histo_data->Draw("pe same");*/
  //histo_wjets->Draw("hist same bar");
  graph_data->Draw("zp same");
#ifdef QCDFROMDATA
//  histo_qcd_data->SetLineColor(kBlue);
//  histo_qcd_data->Draw("hist same");
#endif
//  histo_qcd_total->Draw("hist same");
//  histo_su4->SetLineColor(kWhite);
  histo_su4->SetLineStyle(2);  
//  histo_su4->Draw("hist same");
  TH1D* histo_su4_clone = histo_su4->Clone("histo_su4_clone");
  histo_su4_clone->SetLineColor(kBlack);
  histo_su4_clone->SetLineStyle(2);  
//  histo_su4_clone->Draw("hist same");
#endif
  histo_data->Draw("AXIS same"); //draws only the axis


//Legend

  TLegend *legend = new TLegend(0.60,0.65,0.80,0.94);
  legend->SetBorderSize(0);
  legend->SetTextFont(42);
  legend->SetTextSize(0.04);
  legend->SetFillColor(0);
  legend->SetLineColor(0);
  
#ifdef DATA
  legend->AddEntry(histo_data,"Data 2010 (#sqrt{s} = 7 TeV)","p");
#endif

#ifdef MC
  legend->AddEntry(histo_mc,"Monte Carlo","flp");// <== NB: omit this entry for 2D histogram
  legend->AddEntry(histo_qcd_total,"QCD","f");
//  legend->AddEntry(histo_qcd_data,"QCD from data ","flp");
  legend->AddEntry(histo_wjets,"W+jets","f"); 
  legend->AddEntry(histo_zjets,"Z+jets","f");// <== NB: omit this entry for 2D histogram
  legend->AddEntry(histo_diboson,"diboson","f");// <== NB: omit this entry for 2D histogram
  legend->AddEntry(histo_drellyan,"Drell-Yan","f");// <== NB: omit this entry for 2D histogram
  legend->AddEntry(histo_ttbar,"t#bar{t}","f");// <== NB: omit this entry for 2D histogram
  legend->AddEntry(histo_su4_clone,"SU4","l"); //<== NB: omit this entry for 2D histogram
#endif

  legend->Draw();

//Luminosity label:

  TLatex n;
  n.SetNDC();
  n.SetTextFont(42);
  n.SetTextColor(kBlack);
  n.DrawLatex(0.60,0.55,"#intL dt ~ "+lumi_string);

  TLatex n1;
  n.SetNDC();
  n.SetTextFont(42);
  n.SetTextColor(kBlack);
  n.DrawLatex(0.20,0.85,title);

//  c1->Print("fig/MET.resimulation.1l.3j.soft_7TeV_200pb_test.eps","eps");
}
//58.19496 +76.09244 +4.69852 +90.6869 +47.40916 +16.8286 +8.107157
