#define DATA
#define ELECTRON
//#define MUON

//#define MC
//#define QCDEE
//#define JXMUON
#define QCD
#define ZJETS
#define WJETS
#define DY
#define TOP
#define SU4
#define DIBOSON
#define TTBAR
#define WBB

#define H2D

  double lumi         = 1035040; //pb	 MUON STREAM
  TString lumi_string = "1035.18"; //nb	
/*
Cut 0 : 1.1541e+07		  no cut - with Pileup reweight
Cut 1 : 1.15715e+07		  no cut
Cut 2 : 1.15715e+07		  Lar error cut
Cut 3 : 1.14754e+07		  Lar veto electron
Cut 4 : 1.05981e+07		  Lar veto jet
Cut 5 : 1.05981e+07		  trigger cut (trgEl || trgMu)
Cut 6 : 1.05981e+07		  jet cleaning (disabled on MC)
Cut 7 : 1.05685e+07		  >= 1 vertex with > 4 tracks
Cut 8 : 1.05341e+07		  Cosmic veto
Cut 9 : 488536		  MUMU + EE + EMU
Cut 10 : 88140.9		  EE
Cut 11 : 87662		   && mll cut
Cut 12 : 86046.4		   && OS 
Cut 13 : 3620.1		   && OS && MET cut > 150 GeV 
Cut 14 : 247.825		   [SR1] && OS && MET cut > 250 GeV 
Cut 15 : 266.635		   && OS && 4 jets 100, 70, 70, 70 GeV
Cut 16 : 91.4819		   [SR2] && OS && MET cut > 100 GeV + 4 jets 100, 70, 70, 70 GeV
Cut 17 : 13111		   && OS && 3 jets 80, 40, 40 GeV
Cut 18 : 212.131		   [SR3] && OS && MET cut > 220 GeV + 3 jets 80, 40, 40 GeV
Cut 19 : 1615.69		   && SS 
Cut 20 : 200.905		   [SR1] && SS && MET cut > 100 GeV 
Cut 21 : 726.565		   && SS && 2 jets 50, 50 GeV
Cut 22 : 176.782		   [SR2] && SS && MET cut > 80 GeV + 2 jets 50, 50 GeV
Cut 23 : 244541		  EMU 
Cut 24 : 242328		   && mll cut
Cut 25 : 238139		   && OS 
Cut 26 : 9790.02		   && OS && MET cut > 150 GeV 
Cut 27 : 654.602		   [SR1] && OS && MET cut > 250 GeV 
Cut 28 : 914.878		   && OS && 4 jets 100, 70, 70, 70 GeV
Cut 29 : 276.474		   [SR2] && OS && MET cut > 100 GeV + 4 jets 100, 70, 70, 70 GeV
Cut 30 : 35542.8		   && OS && 3 jets 80, 40, 40 GeV
Cut 31 : 549.559		   [SR3] && OS && MET cut > 220 GeV + 3 jets 80, 40, 40 GeV
Cut 32 : 4189.56		   && SS 
Cut 33 : 855.516		   [SR1] && SS && MET cut > 100 GeV 
Cut 34 : 2159.64		   && SS && 2 jets 50, 50 GeV
Cut 35 : 765.309		   [SR2] && SS && MET cut > 80 GeV + 2 jets 50, 50 GeV
Cut 36 : 160228		  MUMU 
Cut 37 : 158551		   && mll cut
Cut 38 : 156515		   && OS 
Cut 39 : 6535.88		   && OS && MET cut > 150 GeV 
Cut 40 : 400.933		   [SR1] && OS && MET cut > 250 GeV 
Cut 41 : 562.196		   && OS && 4 jets 100, 70, 70, 70 GeV
Cut 42 : 176.603		   [SR2] && OS && MET cut > 100 GeV + 4 jets 100, 70, 70, 70 GeV
Cut 43 : 22639.1		   && OS && 3 jets 80, 40, 40 GeV
Cut 44 : 342.926		   [SR3] && OS && MET cut > 220 GeV + 3 jets 80, 40, 40 GeV
Cut 45 : 2036.2		   && SS 
Cut 46 : 327.996		   [SR1] && SS && MET cut > 100 GeV 
Cut 47 : 1202		   && SS && 2 jets 50, 50 GeV
Cut 48 : 368.922		   [SR2] && SS && MET cut > 80 GeV + 2 jets 50, 50 GeV
*/

#include "AtlasStyle.C"
#include "input2.h"
#include "histo2.h"

#ifdef DATA
TH1D  *histo_data; 
TH1D *histo_egamma, *histo_muon, *histo_top, *histo_qcd_data, TGraphAsymmErrors* graph_data;
#endif
#ifdef MC
TH1D *histo_drellyan, *histo_diboson, *histo_qcd, *histo_qcd_mu, *histo_qcd_total,*histo_wjets, *histo_zjets, *histo_ttbar, *histo_su4;
#endif
  
  int binmin, binmax;
  TString x_string, y_string, title, title2, title3, title4, histo_string, filename;
  bool rebin = false;
   
//#include "histo.h"
#include "error.h"

void makePlots3() {
// plot 
  
  gROOT->SetStyle("ATLAS");
  SetAtlasStyle();
  gROOT->ForceStyle();

  TCanvas *c1 = new TCanvas("canvas1","canvas1", 200,10,800,600);  // 1D histo
  TCanvas *c2 = new TCanvas("canvas2","canvas2", 200,10,800,600);  // 1D histo
  TCanvas *c3 = new TCanvas("canvas3","canvas3", 200,10,800,600);  // 1D histo
  TCanvas *c4 = new TCanvas("canvas4","canvas4", 200,10,800,600);  // 1D histo
  TCanvas *c5 = new TCanvas("canvas5","canvas5", 200,10,800,600);  // 1D histo
  TCanvas *c6 = new TCanvas("canvas6","canvas6", 200,10,800,600);  // 1D histo
/*  TCanvas *c7 = new TCanvas("canvas7","canvas7", 200,10,800,600);  // 1D histo
  TCanvas *c8 = new TCanvas("canvas8","canvas8", 200,10,800,600);  // 1D histo
  TCanvas *c9 = new TCanvas("canvas9","canvas9", 200,10,800,600);  // 1D histo
  TCanvas *c10 = new TCanvas("canvas10","canvas10", 200,10,800,600);  // 1D histo
  TCanvas *c11 = new TCanvas("canvas11","canvas11", 200,10,800,600);  // 1D histo
  TCanvas *c12 = new TCanvas("canvas12","canvas12", 200,10,800,600);  // 1D histo
  TCanvas *c13 = new TCanvas("canvas13","canvas13", 200,10,800,600);  // 1D histo
  TCanvas *c14 = new TCanvas("canvas14","canvas14", 200,10,800,600);  // 1D histo
  TCanvas *c15 = new TCanvas("canvas15","canvas15", 200,10,800,600);  // 1D histo
*/
   makePlots (c1, 0,0,0,0,1); // first time to avoid crashes
   
   int variable;
   
   
//   variable = 0;// Jet Pt
//   variable = 1;// nGoodPV 
//   variable = 2;// transverse mass
   variable = 3;// MET
//   variable = 4;// inv mass
   
   makePlots (c1, 0,0,variable,0,0); // EE OS
   makePlots (c2, 0,1,variable,0,0); // EE SS
   makePlots (c3, 1,0,variable,0,0); // EMU OS
   makePlots (c4, 1,1,variable,0,0); // EMU SS
   makePlots (c5, 2,0,variable,0,0); // MUMU OS
   makePlots (c6, 2,1,variable,0,0); // MUMU SS
/*
   // rnd 4 jets 100,70,70,70  -- OS
   makePlots (c7, 0,0,variable,1,0); // EE OS
   makePlots (c8, 1,0,variable,1,0); // EMU OS
   makePlots (c9, 2,0,variable,1,0); // MUMU OS

   // rnd 3 jets 80,40,40  -- OS
   makePlots (c10, 0,0,variable,2,0); // EE OS
   makePlots (c11, 1,0,variable,2,0); // EMU OS
   makePlots (c12, 2,0,variable,2,0); // MUMU OS
   
   // rnd 2 jets 50,50  -- SS
   makePlots (c13, 0,1,variable,3,0); // EE SS
   makePlots (c14, 1,1,variable,3,0); // EMU SS
   makePlots (c15, 2,1,variable,3,0); // MUMU SS
  */
}
 
void makePlots(TCanvas *c1, int channel, int sign, int variable, int rnd, int first) {

// channel     0: EE, 1: EMU, 2: MUMU
// sign        0: OS, 1: SS

// variable    0: Leading jet pt 
// variable    1: nGoodPV 
// variable    2: transverse mass
// variable    3: MET
// variable    4: inv mass

// rnd         0: no rnd cuts
// rnd         1: 4 jets 100,70,70,70  -- OS
// rnd         2: 3 jets, 80,40,40     -- OS
// rnd         3: 2 jets 50,50         -- SS


  Double_t x_min, x_max, y_max = 100000;

if (channel == 0) { //#ifdef EE

  title2 = "ee";
  title3 = "ee";

  if (sign == 0) { //#ifdef OS     
     binmin = 13;//   OS
     title = title2 + " OS";      
  }else{     
     binmin = 20;//  SS
     title = title2 + " SS";      
  }  
}

if (channel == 1) { //#ifdef EMU

  title2 = "e#mu";
  title3 = "emu";

  if (sign == 0) { //#ifdef OS     
     binmin = 26;//   OS
     title = title2 + " OS";      
  }else{     
     binmin = 33;//  SS
     title = title2 + " SS";      
  }
}

if (channel == 2) { //#ifdef MUMU

  title2 = "#mu#mu";
  title3 = "mumu";

  if (sign == 0) { //#ifdef OS
     binmin = 39;//   OS
     title = title2 + " OS";    
  }else{
     binmin = 46;//  SS
     title = title2 + " SS";    
  }
}

if (variable == 0){

  x_string = "Leading jet pt [GeV]";
  histo_string = "h_jetl_pt";
  x_min = 20.;
  x_max = 500;
  y_max = 1000;
  
} else if (variable == 1){

  x_string = "nGoodPV";
  histo_string = "h_nGoodPV";
  x_min = 0.;
  x_max = 20;

} else if (variable == 2){

  x_string = "Transverse mass [GeV]";
  histo_string = "h_mt";
  x_min = 20.;
  x_max = 500;

} else if (variable == 3){

  x_string = "E_{T,miss} [GeV]";
  histo_string = "h_met";
  x_min = 0.;
  x_max = 500;

} else if (variable == 4){
  x_min = 5.;
  x_max = 500;
  histo_string = "h_invmass";
  x_string = "Dilepton mass [GeV]";
}
  
  y_string = "Entries / 5 GeV";
  if (rebin) y_string = "Entries / 10 GeV";

if (rnd == 1) binmin += 3;
if (rnd == 2) binmin += 5;
if (rnd == 3) binmin += 2;
if (rnd == 1) title4 = "4 jets 100,70,70,70";
if (rnd == 2) title4 = "3 jets, 80,40,40";
if (rnd == 3) title4 = "2 jets 50,50";

   binmax =binmin;

  if (!(variable == 0))  c1->SetLogy();
  c1->cd();
  
  cout << "BINMIN "<<binmin<<endl;

//  fillHisto(); // combine samples

  Double_t err=0.;

//Legend

  TLegend *legend = new TLegend(0.60,0.65,0.80,0.94);
  legend->SetBorderSize(0);
  legend->SetTextFont(42);
  legend->SetTextSize(0.04);
  legend->SetFillColor(0);
  legend->SetLineColor(0);
  
#ifdef DATA
  fillData();
  
  suffix = "";

  
  cout << "data  : " << (int)(histo_data->IntegralAndError(0, (histo_data->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;

  graph_data = TH1TOTGraphAsymNoerrorx(histo_data, 1.);  
  graph_data->SetMarkerStyle(20);
  graph_data->SetMarkerSize(1.2);  
  graph_data->SetLineWidth(3.);
  
  legend->AddEntry(histo_data,"Data 2011 (#sqrt{s} = 7 TeV)","p");
#endif

#ifdef MC
 // addErrors();
  
#ifdef WJETS
  histo_wjets =  fillHisto(ds_wjets());    
  
  //at least histo_wjets MUST be defined
  TH1D* histo_mc = histo_wjets->Clone("histo_mc");
  histo_mc	->Reset();
  legend->AddEntry(histo_mc,"Monte Carlo","flp");// <== NB: omit this entry for 2D histogram
  
  histo_mc	->Add(histo_wjets, 1.);

  legend->AddEntry(histo_wjets,"W+jets","f"); 

  cout << "Wjets   : " << (histo_wjets    ->IntegralAndError(0, (histo_wjets->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;    
#endif

#ifdef QCD
  histo_qcd_total =  fillHisto(ds_qcd());    
  histo_mc	->Add(histo_qcd_total, 1.);
  legend->AddEntry(histo_qcd_total,"QCD","f");
  cout << "QCD     : " << (histo_qcd_total->IntegralAndError(0, (histo_qcd_total->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;
#endif

#ifdef DY
  histo_drellyan =  fillHisto(ds_drellyan());     
  histo_mc	->Add(histo_drellyan, 1.);
  legend->AddEntry(histo_drellyan,"Drell-Yan","f");// <== NB: omit this entry for 2D histogram
  cout << "DY      : " << (histo_drellyan ->IntegralAndError(0, (histo_drellyan->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 
#endif

#ifdef TTBAR
  histo_ttbar =  fillHisto(ds_ttbar());  
  histo_mc	->Add(histo_ttbar, 1.);
  legend->AddEntry(histo_ttbar,"t#bar{t}","f");// <== NB: omit this entry for 2D histogram
  cout << "ttbar   : " << (histo_ttbar    ->IntegralAndError(0, (histo_ttbar->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;    
#endif

#ifdef TOP
  histo_top =  fillHisto(ds_top());  
  histo_mc	->Add(histo_top, 1.);
  legend->AddEntry(histo_top,"single top","f");// <== NB: omit this entry for 2D histogram
  cout << "top   : " << (histo_top    ->IntegralAndError(0, (histo_top->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;    
#endif

#ifdef ZJETS
  histo_zjets =  fillHisto(ds_zjets());    
  legend->AddEntry(histo_zjets,"Z+jets","f");// <== NB: omit this entry for 2D histogram
  histo_mc	->Add(histo_zjets, 1.);  
  cout << "Zjets   : " << (histo_zjets    ->IntegralAndError(0, (histo_zjets->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;    
#endif

#ifdef DIBOSON
  histo_diboson =  fillHisto(ds_diboson());   
  histo_mc	->Add(histo_diboson, 1.);  
  legend->AddEntry(histo_diboson,"diboson","f");// <== NB: omit this entry for 2D histogram
  cout << "diboson : " << (histo_diboson  ->IntegralAndError(0, (histo_diboson->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;      
#endif

#ifdef SU4  
  histo_su4 =  fillHisto(ds_su4());  
  histo_su4->SetLineStyle(2);  
  
  TH1D* histo_su4_clone = histo_su4->Clone("histo_su4_clone");
  histo_su4_clone->SetLineColor(kBlack);
  histo_su4_clone->SetLineStyle(2);  
  
  cout << "su4     : " << (histo_su4      ->IntegralAndError(0, (histo_su4->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;      
  legend->AddEntry(histo_su4_clone,"SU4","l"); //<== NB: omit this entry for 2D histogram
#endif

  histo_mc->SetXTitle(x_string);
  histo_mc->SetYTitle(y_string);
  histo_mc->SetFillColor(kWhite);
  histo_mc->SetLineColor(kRed);

  cout <<endl<<endl<< "MC      : " << (histo_mc       ->IntegralAndError(0, (histo_mc->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 

  THStack* histo_stack  = new THStack();
  
  
#ifdef TOP
  histo_stack->Add(histo_top);
  cout << "top   : " << (histo_top    ->IntegralAndError(0, (histo_top->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;    
#endif
#ifdef TTBAR
  histo_stack->Add(histo_ttbar);
  cout << "ttbar   : " << (histo_ttbar    ->IntegralAndError(0, (histo_ttbar->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;    
#endif
#ifdef WJETS
  cout << "Wjets   : " << (histo_wjets    ->IntegralAndError(0, (histo_wjets->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;    
  histo_stack->Add(histo_wjets);
#endif
#ifdef DY
  histo_stack->Add(histo_drellyan);
  cout << "DY      : " << (histo_drellyan ->IntegralAndError(0, (histo_drellyan->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 
#endif
#ifdef DIBOSON
  cout << "diboson : " << (histo_diboson  ->IntegralAndError(0, (histo_diboson->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;      
  histo_stack->Add(histo_diboson);
#endif
#ifdef ZJETS
  histo_stack->Add(histo_zjets);
  cout << "Zjets   : " << (histo_zjets    ->IntegralAndError(0, (histo_zjets->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;    
#endif
#ifdef QCD
  histo_stack->Add(histo_qcd_total);
  cout << "QCD     : " << (histo_qcd_total->IntegralAndError(0, (histo_qcd_total->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;
#endif
#ifdef SU4  
  histo_stack->Add(histo_su4);
  cout << "su4     : " << (histo_su4      ->IntegralAndError(0, (histo_su4->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;      
#endif  


  TH1D* histo_mc_clone = histo_mc->Clone("histo_mc_clone"); // <== cloned MC
  
  histo_mc->SetFillColor(kYellow);
  histo_mc->SetFillStyle(3002); 
  histo_mc->SetMarkerSize(0);  

#ifdef DATA
  cout << "data  : " << (int)(histo_data->IntegralAndError(0, (histo_data->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;
#else //allow plotting also without data
  TH1D*  histo_data = histo_wjets->Clone("histo_data");
  histo_data->Reset();
#endif

#endif
  
// start drawing
  c1->cd(1);
  SetStyle();

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
  
  histo_data->SetMinimum(0.01); 
  histo_data->SetMaximum(y_max);
  histo_data->GetXaxis()->SetRangeUser(x_min,x_max);  //inv mass
  histo_data->Draw("AXIS"); //draws only the axis


#ifdef MC

 if (!first)  histo_stack->Draw("hist same ][");
  
 histo_mc->Draw("e2 same");
 histo_mc_clone->Draw("hist same");
#endif
 
 histo_mc_clone->Draw("hist same ][");// ROOT CRASHES!!

#ifdef DATA
  graph_data->Draw("zp same");
#endif
  histo_data->Draw("AXIS same"); //draws only the axis



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
  n.DrawLatex(0.30,0.85,title);
  n.DrawLatex(0.30,0.75,title4);
  

/*******************
*** Residuals: ****
*******************/

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
  hs->Add(histo_mc);

  pad2->cd();

TH1F *stack_resid = histo_data->Clone("stack_resid");
TH1F *stack_resid_DOWN = hs_min->Clone("stack_resid_DOWN");
TH1F *stack_resid_UP = hs_max->Clone("stack_resid_UP");

stack_resid->GetYaxis()->SetNdivisions(404);
stack_resid->GetYaxis()->SetTitle("Data/MC");
stack_resid->GetYaxis()->SetTitleOffset(1.3);
stack_resid->GetXaxis()->SetTitleSize(0.12);
stack_resid->GetXaxis()->SetLabelSize(0.12);
stack_resid->GetYaxis()->SetTitleSize(0.12);
stack_resid->GetYaxis()->SetLabelSize(0.12);

pad2->cd();
pad2->cd()->SetGridy(1);
pad2->cd()->Update();

stack_resid->Divide(histo_mc); // total MC
stack_resid_UP->Divide(histo_mc); // total MC
stack_resid_DOWN->Divide(histo_mc); // total MC

//stack_resid->SetMaximum(10.);	
//stack_resid->SetMinimum(0);
stack_resid->GetYaxis()->SetTitle("Data/MC");
stack_resid->GetYaxis()->SetTitleOffset(0.5);
stack_resid->GetYaxis()->SetTitleSize(0.12);
stack_resid->GetYaxis()->SetTitle("Data/MC");
stack_resid->Draw("pe");

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

/*******************
*** Write to file: ****
*******************/

  TString filename = "plots/"+histo_string+"_"+title3;  
  if (sign == 0) filename += "_OS";    
  else filename += "_SS";    
  
  if (rnd == 1) filename += "_rnd1";
  if (rnd == 2) filename += "_rnd2";
  if (rnd == 3) filename += "_rnd3";
  
  c1->Print(filename+".eps","eps");
}
