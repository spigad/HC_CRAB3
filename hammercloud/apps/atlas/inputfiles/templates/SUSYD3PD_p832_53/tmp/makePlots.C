#define DATA
#define ELECTRON
#define MUON

#define MC
#define QCDEE
#define JXMUON
#define QCD
#define ZJETS
#define WJETS
#define DY
#define SU4
#define DIBOSON
#define TTBAR
#define WBB

#define OS
//#define SS

//#define MET
#define MLL
//#define JETPT
//#define MT
//#define PV

//#define EE
//#define EMU
#define MUMU

//#define REBIN
#define H2D

//#define RDJET1  // 4 jets, 100, 70,70,70 
//#define RDJET2  // 3 jets, 80, 40,40
//#define RDJET3  // 2 jets, 50,50

//avoid root crash fist time that the macro runs...
//#define FIRSTROOT


  double lumi         = 174000.; //nb	
  TString lumi_string = "174 pb-1"; //nb	

#ifdef ELECTRON
  TString title2 = "Dielectron channel";
#ifdef MUON
  TString title2 = "Dilepton channel";
#endif
#endif

#ifdef EE
  TString title2 = "ee";
#endif
#ifdef EMU
  TString title2 = "e#mu";
#endif
#ifdef MUMU
  TString title2 = "#mu#mu";
#endif

//#ifdef MUON
//  TString title2 = "Dimuon channel";
//#ifdef ELECTRON
//  TString title2 = "Dilepton channel";
//#endif
//#endif

#ifdef JETPT
  TString x_string = "Leading jet pt [GeV]";
  TString title = title2 + " SS+OS";    
  TString histo_string = "h_jetl_pt";
  Double_t x_min = 20.;
  Double_t x_max = 500;
#endif

#ifdef PV
  TString x_string = "nGoodPV";
  TString title = title2 + " SS+OS";    
  TString histo_string = "h_nGoodPV";
  Double_t x_min = 0.;
  Double_t x_max = 20;
#endif

#ifdef MT
  TString x_string = "Transverse mass [GeV]";
  TString title = title2 + " SS+OS";    
  TString histo_string = "h_mt";
  Double_t x_min = 20.;
  Double_t x_max = 500;
#endif

#ifdef MET
  TString x_string = "E_{T,miss} [GeV]";
  TString title = title2 +" SS+OS";
  TString histo_string = "h_met";
  Double_t x_min = 0.;
  Double_t x_max = 500;
#ifdef OS
  TString histo_string = "h_met_OS";
  TString title = title2 + " OS";
#endif
#ifdef SS
  TString histo_string = "h_met_SS";
  TString title = title2 + " SS";
#endif
#endif

#ifdef MLL
  Double_t x_min = 5.;
  Double_t x_max = 500;
  TString title = title2 + " SS+OS";
  TString histo_string = "h_invmass";
  TString x_string = "Dilepton mass [GeV]";
#ifdef OS
  TString histo_string = "h_invmass_OS";
  TString title = title2 + " OS";
#endif
#ifdef SS
  TString histo_string = "h_invmass_SS";
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
    
int binmin = 7;//  "EE + EMU + MUMU", 

#ifdef EE
#ifdef OS
binmin = 10;//   OS
#else
binmin = 17;//  SS
#endif
#endif

#ifdef EMU
#ifdef OS
binmin = 23;//  OS
#else
binmin = 30;//  SS
#endif
#endif

#ifdef MUMU
#ifdef OS
binmin = 36;//  OS
#else
binmin = 43;//  SS
#endif
#endif

#ifdef RDJET1
binmin += 3;
#endif
#ifdef RDJET2
binmin += 5;
#endif
#ifdef RDJET3
binmin += 2;
#endif

// Cut 0   no cut
// Cut 1   GRL cut
// Cut 2   trigger cut (trgEl || trgMu)
// Cut 3   jet cleaning (disabled on MC)
// Cut 4   >= 1 vertex with > 4 tracks
// Cut 5   Event veto (crack + cosmics)
// Cut 6   MUMU + EE + EMU
// Cut 7   EE
// Cut 8    && mll > 5 GeV
// Cut 9    && OS 
// Cut 10   && OS && MET cut > 150 GeV 
// Cut 11   && OS && MET cut > 250 GeV 
// Cut 12   && OS && 4 jets 100, 70, 70, 70 GeV
// Cut 13   && OS && MET cut > 100 GeV + 4 jets 100, 70, 70, 70 GeV
// Cut 14   && OS && 3 jets 80, 40, 40 GeV
// Cut 15   && OS && MET cut > 220 GeV + 3 jets 80, 40, 40 GeV
// Cut 16   && SS 
// Cut 17   && SS && MET cut > 100 GeV 
// Cut 18   && SS && 2 jets 50, 50 GeV
// Cut 19   && SS && MET cut > 80 GeV + 2 jets 50, 50 GeV
// Cut 20  	EMU 
// Cut 21  	 && mll > 5 GeV
// Cut 22  	 && OS 
// Cut 23   && OS && MET cut > 150 GeV 
// Cut 24   && OS && MET cut > 250 GeV 
// Cut 25   && OS && 4 jets 100, 70, 70, 70 GeV
// Cut 26   && OS && MET cut > 100 GeV + 4 jets 100, 70, 70, 70 GeV
// Cut 27  	 && OS && 3 jets 80, 40, 40 GeV
// Cut 28   && OS && MET cut > 220 GeV + 3 jets 80, 40, 40 GeV
// Cut 29  	 && SS 
// Cut 30  	 && SS && MET cut > 100 GeV 
// Cut 31  	 && SS && 2 jets 50, 50 GeV
// Cut 32  	 && SS && MET cut > 80 GeV + 2 jets 50, 50 GeV
// Cut 33  	MUMU 
// Cut 34  	 && mll > 5 GeV
// Cut 35  	 && OS 
// Cut 36   && OS && MET cut > 150 GeV 
// Cut 37   && OS && MET cut > 250 GeV 
// Cut 38   && OS && 4 jets 100, 70, 70, 70 GeV
// Cut 39   && OS && MET cut > 100 GeV + 4 jets 100, 70, 70, 70 GeV
// Cut 40   && OS && 3 jets 80, 40, 40 GeV
// Cut 41   && OS && MET cut > 220 GeV + 3 jets 80, 40, 40 GeV
// Cut 42  	 && SS 
// Cut 43   && SS && MET cut > 100 GeV 
// Cut 44  	 && SS && 2 jets 50, 50 GeV
// Cut 45   && SS && MET cut > 80 GeV + 2 jets 50, 50 GeV

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
  
  gROOT->SetStyle("ATLAS");
  SetAtlasStyle();
  gROOT->ForceStyle();

  ///  Draw */
  
//  TCanvas *c1 = new TCanvas("canvas","canvas", 200,10,800,600);  // 1D histo
//  TCanvas *c1 = new TCanvas("canvas","canvas", 200,10,600,600);  // 2D histo
//To plot residuals:

TCanvas *canvas_residual = new TCanvas("canvas_residual","canvas_residual",200,10,800,800);
canvas_residual->cd(1);

TPad *pad1 = new TPad("pad1","pad1",0.0,0.3,1.0,1.0,21);
TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.3,22); 
pad1->Draw();
pad1->SetLogy(1);
pad1->SetRightMargin(0.1);
pad2->SetRightMargin(0.1);
pad2->Draw();
pad1->SetFillColor(kWhite);
pad2->SetFillColor(kWhite);
pad1->SetBottomMargin(0.01);
pad2->SetTopMargin(0.05);
pad2->SetBottomMargin(0.5);

pad1->cd();

  fillHisto(); // combine samples 
    
  Double_t err=0.;
  
#ifdef DATA
#ifdef REBIN
  histo_data->Rebin(2);
#endif
  cout << "data  : " << (int)(histo_data->IntegralAndError(0, (histo_data->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;

  graph_data = TH1TOTGraphAsymNoerrorx(histo_data, 1.);  
  graph_data->SetMarkerStyle(20);
  graph_data->SetMarkerSize(1.2);  
  graph_data->SetLineWidth(3.);
#else //allow plotting also without data
  TH1D*  histo_data = histo_wjets->Clone("histo_data");
  histo_data->Reset();
#endif
#ifdef MC
  addErrors();


  TH1D* histo_mc = histo_wjets->Clone("histo_mc");
  histo_mc	->Reset();
  histo_mc	->Add(histo_wjets, 1.);
#ifdef QCD
  histo_mc	->Add(histo_qcd_total, 1.);
#endif
  histo_mc	->Add(histo_drellyan, 1.);
  histo_mc	->Add(histo_ttbar, 1.);
  histo_mc	->Add(histo_zjets, 1.);  
  histo_mc	->Add(histo_diboson, 1.);  

  histo_mc->SetXTitle(x_string);
  histo_mc->SetYTitle(y_string);
  histo_mc->SetFillColor(kWhite);
  histo_mc->SetLineColor(kRed);

  cout << "MC      : " << (histo_mc       ->IntegralAndError(0, (histo_mc->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 
#ifdef QCD
  cout << "QCD     : " << (histo_qcd_total->IntegralAndError(0, (histo_qcd_total->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;
#endif
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
#ifdef QCD
  histo_qcd_total->Rebin(2);
#endif
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
  histo_data->SetMaximum(100000.);
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
#ifdef DATA
  graph_data->Draw("zp same");
#endif
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

/*******************
*** Residuals: ****
*******************/

//NB: 
//(1) - histo_stack is the THStack of backgrounds
//(2) - hs is the error band
  THStack *hs = new THStack("hs","band");

  TH1F* hs_max = histo_mc->Clone("hs_max"); // <== cloned MC
  TH1F* hs_min = histo_mc->Clone("hs_min"); // <== cloned MC
  unsigned int nbin = histo_mc->GetNbinsX();
  for (unsigned int i = 0; i < (nbin+1); i++){
    float error = histo_mc->GetBinError(i);
    float content = histo_mc->GetBinContent(i);
    hs_max->SetBinContent(i, content+error); 
    hs_min->SetBinContent(i, content-error); 
  }
  
  hs_max->SetLineColor(kYellow); // maximum total MC line (i.e. MC line + uncertainty)
  hs_min->SetLineColor(kYellow); // minimum total MC line (i.e. MC line - uncertainty)
  hs_max->SetFillColor(kYellow); 
  hs_min->SetFillColor(10);
  hs->Add(hs_max);
  hs->Add(hs_min);
//variable_plot[1][i]->SetLineColor(kRed);
//variable_plot[1][i]->SetFillColor(0);
//hs->Add(variable_plot[1][i]); // MC line
  hs->Add(histo_mc);
//(3) - lowerline is the bottom of the yellow uncertainty band
  TH1 *lowerline = (TH1F*)hs_min->Clone("lowerline");
  lowerline->SetLineColor(kYellow);
  lowerline->SetFillColor(0);


pad2->cd();

TH1F *stack_resid_UP   = hs_max->Clone("stack_resid_UP");
TH1F *stack_resid_DOWN = hs_min->Clone("stack_resid_DOWN");
TH1F *stack_resid = histo_data->Clone("stack_resid");
stack_resid->GetYaxis()->SetNdivisions(404);
stack_resid->GetYaxis()->SetTitle("Data/MC");
stack_resid->GetYaxis()->SetTitleOffset(1.3);
stack_resid->GetXaxis()->SetTitleSize(0.12);
stack_resid->GetXaxis()->SetLabelSize(0.12);
stack_resid->GetYaxis()->SetTitleSize(0.12);
stack_resid->GetYaxis()->SetLabelSize(0.12);

pad2->cd();
stack_resid->GetYaxis()->SetNdivisions(404);
pad2->cd()->SetGridy(1);
pad2->cd()->Update();
//stack_resid->GetXaxis()->SetTitle(xplottitle); 
stack_resid->GetYaxis()->SetTitle("Data/MC");

stack_resid->Divide(histo_mc); // total MC
stack_resid_UP->Divide(histo_mc); // total MC
stack_resid_DOWN->Divide(histo_mc); // total MC

stack_resid->SetMaximum(2.);	
stack_resid->SetMinimum(0);
stack_resid->GetYaxis()->SetTitle("Data/MC");
stack_resid->GetYaxis()->SetTitleOffset(0.5);
stack_resid->GetYaxis()->SetTitleSize(0.12);
stack_resid->GetYaxis()->SetTitle("Data/MC");

double uncertainty_range;
if(fabs(1-stack_resid_UP->GetMaximum())>fabs(1-stack_resid_DOWN->GetMinimum())) { // <== this will ensure all the error band is all drawn, but it won't ensure all the points are shown
    uncertainty_range = 1.05*stack_resid_UP->GetMaximum();
}
    else uncertainty_range = 1.05*stack_resid_DOWN->GetMaximum();
if(fabs(uncertainty_range-TMath::Ceil(uncertainty_range))<0.5) uncertainty_range = TMath::Ceil(uncertainty_range);                                              
stack_resid->SetMaximum(uncertainty_range);	
if((2-uncertainty_range)>0) stack_resid->SetMinimum(2-uncertainty_range);
else stack_resid->SetMinimum(0);

stack_resid->Draw("pe");
stack_resid_UP->SetLineStyle(kDashed);
stack_resid_UP->SetLineColor(kBlack);
stack_resid_UP->SetFillColor(kYellow);
stack_resid_DOWN->SetLineStyle(kDashed);
stack_resid_DOWN->SetLineColor(kBlack);
stack_resid_DOWN->SetFillColor(10);
stack_resid_UP->Draw("hist][ same");
stack_resid_DOWN->Draw("hist][ same");
stack_resid->Draw("pe same");
stack_resid->Draw("axis same");
stack_resid->Draw("axiG same");


//  c1->Print("fig/MET.resimulation.1l.3j.soft_7TeV_200pb_test.eps","eps");
}
//58.19496 +76.09244 +4.69852 +90.6869 +47.40916 +16.8286 +8.107157
