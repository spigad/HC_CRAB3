/*========================================

 PRODUCE emu.dat, electron.dat, muon.dat
 with number of events/nGoodPV/sample

=========================================*/

#define DATA
#define ELECTRON
//#define MUON
//#define EMU

#define MC

#ifdef ELECTRON
#define QCDEE
#endif

#ifdef MUON
#define JXMUON
#endif

#ifdef EMU
#define JXMUON
#endif

#define ZJETS
#define WJETS
#define DY
#define SU4  //should not be added to MC to calculate pile-up!!
#define DIBOSON
#define TTBAR

#define PV

#define H2D

//avoid root crash fist time that the macro runs...
//#define FIRSTROOT


  double lumi         = 34300.; //nb	
  TString lumi_string = "34.3 pb-1"; //nb	

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


#ifdef PV
  TString x_string = "nGoodPV";
  TString y_string = "Events";
  TString title = title2 + " SS+OS";    
  TString histo_string = "h_nGoodPV";
  Double_t x_min = 0.;
  Double_t x_max = 15;
  Double_t y_max = 5000.;
#endif


//Axis labels:

//y-axis labels: Entries / x Units (x = bin width, Units = e.g. GeV)
//x-axis labels: Quantity [Unit] (Quantity = e.g. M_{eff}, Units = e.g. GeV)
    
//int binmin = 7;//    "MUMU + EE + EMU", 
#ifdef ELECTRON
 int binmin = 8;  //"EE", 
#endif

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
void pileUp() {
  
  gROOT->SetStyle("ATLAS");
  SetAtlasStyle();
  gROOT->ForceStyle();

  
  fillHisto(); // combine samples 
    
  Double_t err=0.;
  
#ifdef MC
//  addErrors();

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

  
  // before reweighting
  cout << endl << "BEFORE REWEIGHTING"<<endl<<endl;

  cout << "MC      : " << (histo_mc       ->IntegralAndError(0, (histo_mc->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 
  cout << "QCD     : " << (histo_qcd_total->IntegralAndError(0, (histo_qcd_total->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;
  cout << "Wjets   : " << (histo_wjets    ->IntegralAndError(0, (histo_wjets->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;    
  cout << "Zjets   : " << (histo_zjets    ->IntegralAndError(0, (histo_zjets->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;    
  cout << "DY      : " << (histo_drellyan ->IntegralAndError(0, (histo_drellyan->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 
  cout << "ttbar   : " << (histo_ttbar    ->IntegralAndError(0, (histo_ttbar->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;    
#ifdef SU4
  cout << "su4     : " << (histo_su4      ->IntegralAndError(0, (histo_su4->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;      
#endif  
  cout << "diboson : " << (histo_diboson  ->IntegralAndError(0, (histo_diboson->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;      

  THStack* histo_stack  = new THStack();
  histo_stack->Add(histo_zjets);
  histo_stack->Add(histo_ttbar);
  histo_stack->Add(histo_drellyan);
  histo_stack->Add(histo_diboson);
  histo_stack->Add(histo_wjets);
  histo_stack->Add(histo_qcd_total);
  TH1D* histo_mc_clone = histo_mc->Clone("histo_mc_clone"); // <== cloned MC
  
  histo_mc->SetFillColor(kYellow);
  histo_mc->SetFillStyle(3002); 
  histo_mc->SetMarkerSize(0);  

#endif

#ifdef DATA

  cout << "data  : " << (int)(histo_data->IntegralAndError(0, (histo_data->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;

//normalize data to MC 
  double nentries = histo_mc->Integral()/histo_data->Integral();
  histo_data->Scale(nentries);
  cout << "data (renormalized to "<<nentries<<") : " << histo_data->Integral() << endl;

  graph_data = TH1TOTGraphAsymNoerrorx(histo_data, 1.);  
  graph_data->SetMarkerStyle(20);
  graph_data->SetMarkerSize(1.2);  
  graph_data->SetLineWidth(3.);
#else //allow plotting also without data
  TH1D*  histo_data = histo_wjets->Clone("histo_data");
  histo_data->Reset();
#endif
  
// start drawing
  
  TCanvas *c1 = new TCanvas("c1","c1", 200,10,1200,1000);  // 1D histo
  c1->Divide(2,2);
  c1->cd(1);
  
  histo_data->SetMinimum(0.); 
  histo_data->SetMaximum(y_max);
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
#endif
  histo_data->Draw("AXIS same"); //draws only the axis


//Legend

  TLegend *legend = new TLegend(0.60,0.2,0.80,0.5);
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
  n.DrawLatex(0.20,0.75,"BEFORE NORMALIZING");
  
//  TCanvas *c2 = new TCanvas("c2","c2", 200,10,800,600);  // 1D histo
  c1->cd(2);
  
  TH1D*  histo_data_clone = histo_data->Clone("histo_data_clone");
  histo_data_clone->Divide(histo_data, histo_mc);
  histo_data_clone->SetMinimum(0.); 
  histo_data_clone->SetMaximum(2.);
  histo_data_clone->SetYTitle("Weights");
  histo_data_clone->Draw();
//  n.DrawLatex(0.20,0.85,"WEIGHTS");
 
  int nbins = histo_data_clone->GetNbinsX();

  // create new histos for all mc samples
  double nsample_old_area[60];
  double nsample_new_area[60];
  double nsample_old_area_norm[60];
  double nsample_new_area_norm[60];  
  double nsample_ratio[60];
  
  //TH1D *histo_weighted_drellyan, *histo_weighted_diboson, *histo_weighted_qcd, *histo_weighted_qcd_mu, *histo_weighted_qcd_total,*histo_weighted_wjets, *histo_weighted_zjets, *histo_weighted_ttbar, *histo_weighted_su4;  
  TH1D*  histo_weighted_drellyan = histo_drellyan->Clone("histo_weighted_drellyan");
#ifdef SU4
  TH1D*  histo_weighted_su4 = histo_su4->Clone("histo_weighted_su4");  
#endif 
  TH1D*  histo_weighted_diboson = histo_diboson->Clone("histo_weighted_diboson");
  TH1D*  histo_weighted_ttbar = histo_ttbar->Clone("histo_weighted_ttbar");
  TH1D*  histo_weighted_wjets = histo_wjets->Clone("histo_weighted_wjets");
  TH1D*  histo_weighted_zjets = histo_zjets->Clone("histo_weighted_zjets");
  TH1D*  histo_weighted_qcd = histo_qcd->Clone("histo_weighted_qcd");
  TH1D*  histo_weighted_mc = histo_mc->Clone("histo_weighted_mc");
#ifdef JXMUON  
  TH1D*  histo_weighted_qcd_mu = histo_qcd_mu->Clone("histo_weighted_qcd_mu");
#endif  
  TH1D*  histo_weighted_qcd_total = histo_qcd_total->Clone("histo_weighted_qcd_total");

  
  for (int i = 0; i < 60; i++)  {  
    nsample_old_area[i] = 0;
    nsample_new_area[i] = 0;
    nsample_old_area_norm[i] = 0;
    nsample_new_area_norm[i] = 0;    
    nsample_ratio[i] = 0;  
  }

// REWEIGHTING

  cout << endl;
  for (int i = 1; i < 10; i++)  {
    double weight= histo_data_clone->GetBinContent(i+1);
    cout << "Weight nPV("<<i<<") : " << weight << endl;
    
    double ndata = histo_data->GetBinContent(i+1);
    double nmc = histo_mc->GetBinContent(i+1);

    //get #events per sample
    double nsample[60];
    
    //weight = 1; // debug
    
    nsample[ 0] = h1_105200->GetBinContent(i+1)*weight; 
    nsample[ 1] = h1_105204->GetBinContent(i+1)*weight; 
    
    histo_weighted_ttbar->SetBinContent(i+1,nsample[ 0]+nsample[1]);
    
    nsample[ 2] = h1_105985->GetBinContent(i+1)*weight; 
    nsample[ 3] = h1_105986->GetBinContent(i+1)*weight; 
    nsample[ 4] = h1_105987->GetBinContent(i+1)*weight; 
    
    histo_weighted_diboson->SetBinContent(i+1,nsample[ 2]+nsample[3]+nsample[4]);

    #ifdef QCDEE                                    //QCD EE
    nsample[ 5] = h1_108326->GetBinContent(i+1)*weight; 
#else
    nsample[ 5] = 0; 
#endif
    histo_weighted_qcd->SetBinContent(i+1,nsample[ 5]);

#ifdef JXMUON                        //QCD muon filtered
  
    nsample[ 6] = h1_109276->GetBinContent(i+1)*weight; 
    nsample[ 7] = h1_109277->GetBinContent(i+1)*weight;
    nsample[ 8] = h1_109278->GetBinContent(i+1)*weight;
    nsample[ 9] = h1_109279->GetBinContent(i+1)*weight;
    nsample[10] = h1_109280->GetBinContent(i+1)*weight;
    nsample[11] = h1_109281->GetBinContent(i+1)*weight.;
//    nsample[12] = h1_209435->GetBinContent(i+1)*0.;
    nsample[12] = 0; 
    histo_weighted_qcd_mu->SetBinContent(i+1,nsample[ 7]+nsample[ 8]+nsample[ 9]+nsample[ 10]+nsample[ 11]+nsample[ 12]);
#else
    nsample[ 6] = 0; 
    nsample[ 7] = 0; 
    nsample[ 8] = 0; 
    nsample[ 9] = 0; 
    nsample[10] = 0; 
    nsample[11] = 0; 
    nsample[12] = 0; 
#endif
    
#endif //JXMUON

    nsample[13] = h1_107650->GetBinContent(i+1)*weight; 
    nsample[14] = h1_107651->GetBinContent(i+1)*weight;
    nsample[15] = h1_107652->GetBinContent(i+1)*weight;
    nsample[16] = h1_107653->GetBinContent(i+1)*weight;
    nsample[17] = h1_107654->GetBinContent(i+1)*weight;
    nsample[18] = h1_107655->GetBinContent(i+1)*weight;
    nsample[19] = h1_107660->GetBinContent(i+1)*weight; 
    nsample[20] = h1_107661->GetBinContent(i+1)*weight;
    nsample[21] = h1_107662->GetBinContent(i+1)*weight;
    nsample[22] = h1_107663->GetBinContent(i+1)*weight;
    nsample[23] = h1_107664->GetBinContent(i+1)*weight;
    nsample[24] = h1_107665->GetBinContent(i+1)*weight;
    nsample[25] = h1_107670->GetBinContent(i+1)*weight; 
    nsample[26] = h1_107671->GetBinContent(i+1)*weight;
    nsample[27] = h1_107672->GetBinContent(i+1)*weight;
    nsample[28] = h1_107673->GetBinContent(i+1)*weight;
    nsample[29] = h1_107674->GetBinContent(i+1)*weight;
    nsample[30] = h1_107675->GetBinContent(i+1)*weight;
    
    double total = 0;
    for (int k = 13; k < 31; k++) total += nsample[k];  
    histo_weighted_zjets->SetBinContent(i+1,total);
					
    nsample[31] = h1_107680->GetBinContent(i+1)*weight; 
    nsample[32] = h1_107681->GetBinContent(i+1)*weight;
    nsample[33] = h1_107682->GetBinContent(i+1)*weight;
    nsample[34] = h1_107683->GetBinContent(i+1)*weight;
    nsample[35] = h1_107684->GetBinContent(i+1)*weight;
    nsample[36] = h1_107685->GetBinContent(i+1)*weight;

    nsample[37] = h1_107690->GetBinContent(i+1)*weight; 
    nsample[38] = h1_107691->GetBinContent(i+1)*weight;
    nsample[39] = h1_107692->GetBinContent(i+1)*weight;
    nsample[40] = h1_107693->GetBinContent(i+1)*weight;
    nsample[41] = h1_107694->GetBinContent(i+1)*weight;
    nsample[42] = h1_107695->GetBinContent(i+1)*weight;

    nsample[43] = h1_107700->GetBinContent(i+1)*weight; 
    nsample[44] = h1_107701->GetBinContent(i+1)*weight;
    nsample[45] = h1_107702->GetBinContent(i+1)*weight;
    nsample[46] = h1_107703->GetBinContent(i+1)*weight;
    nsample[47] = h1_107704->GetBinContent(i+1)*weight;
    nsample[48] = h1_107705->GetBinContent(i+1)*weight;

    nsample[49] = h1_106280->GetBinContent(i+1)*weight; 
    nsample[50] = h1_106281->GetBinContent(i+1)*weight; 
    nsample[51] = h1_106282->GetBinContent(i+1)*weight; 
    nsample[52] = h1_106283->GetBinContent(i+1)*weight; 

    total = 0;
    for (int k = 31; k < 53; k++) total += nsample[k];  
    histo_weighted_wjets->SetBinContent(i+1,total);

    nsample[53] = h1_108319->GetBinContent(i+1)*weight;
    nsample[54] = h1_108320->GetBinContent(i+1)*weight;
    nsample[55] = h1_108321->GetBinContent(i+1)*weight;
    nsample[56] = h1_108322->GetBinContent(i+1)*weight;
    
    total = 0;
    for (int k = 53; k < 57; k++) total += nsample[k];  
    histo_weighted_drellyan->SetBinContent(i+1,total);
    
#ifdef SU4    
    nsample[57] = h1_106484->GetBinContent(i+1)*weight;       
#endif 

    for (int k = 0; k < 58; k++) {
      nsample_new_area[k] += nsample[k];  
      if (weight > 0.) nsample_old_area[k] += nsample[k]/weight;
    }
  }    
  
  histo_weighted_qcd_total->Reset();
  histo_weighted_mc->Reset();
  
  histo_weighted_qcd_total->Add(histo_weighted_qcd, 1.);
#ifdef JXMUON
  histo_weighted_qcd_total->Add(histo_weighted_qcd_mu, 1.);
#endif  
  histo_weighted_mc	->Add(histo_weighted_qcd_total, 1.);
  histo_weighted_mc	->Add(histo_weighted_wjets, 1.);
  histo_weighted_mc	->Add(histo_weighted_drellyan, 1.);
  histo_weighted_mc	->Add(histo_weighted_ttbar, 1.);
  histo_weighted_mc	->Add(histo_weighted_zjets, 1.);  
  histo_weighted_mc	->Add(histo_weighted_diboson, 1.);  

  c1->cd(3);
  histo_data->GetXaxis()->SetRangeUser(x_min,x_max);  //inv mass
  histo_data->Draw("AXIS"); //draws only the axis
  histo_data->Draw("zp same");
  histo_weighted_mc->Draw("hist same ][");// ROOT CRASHES!!

  THStack* histo_weighted_stack  = new THStack();
  histo_weighted_stack->Add(histo_weighted_zjets);
  histo_weighted_stack->Add(histo_weighted_ttbar);
  histo_weighted_stack->Add(histo_weighted_drellyan);
  histo_weighted_stack->Add(histo_weighted_diboson);
  histo_weighted_stack->Add(histo_weighted_wjets);
  histo_weighted_stack->Add(histo_weighted_qcd_total);
   
#ifdef FIRSTROOT
#else
  histo_weighted_stack->Draw("hist same");
#endif  

#ifdef MC
  histo_weighted_mc->SetFillColor(kWhite);
  histo_weighted_mc->SetLineColor(kRed);
//  histo_mc->Draw("e2 same");
  histo_weighted_mc->Draw("hist same");
#endif  

  legend->Draw();
  n.DrawLatex(0.20,0.85,title);
  n.DrawLatex(0.20,0.75,"AFTER REWEIGHTING");

  // after reweighting
  
  cout << endl << "AFTER REWEIGHTING"<<endl<<endl;
  
  cout << "MC      : " << (histo_weighted_mc       ->IntegralAndError(0, (histo_weighted_mc->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 
  cout << "QCD     : " << (histo_weighted_qcd_total->IntegralAndError(0, (histo_weighted_qcd_total->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;
  cout << "Wjets   : " << (histo_weighted_wjets    ->IntegralAndError(0, (histo_weighted_wjets->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;    
  cout << "Zjets   : " << (histo_weighted_zjets    ->IntegralAndError(0, (histo_weighted_zjets->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;    
  cout << "DY      : " << (histo_weighted_drellyan ->IntegralAndError(0, (histo_weighted_drellyan->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 
  cout << "ttbar   : " << (histo_weighted_ttbar    ->IntegralAndError(0, (histo_weighted_ttbar->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;    
#ifdef SU4
  cout << "su4     : " << (histo_weighted_su4      ->IntegralAndError(0, (histo_weighted_su4->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;      
#endif  
  cout << "diboson : " << (histo_weighted_diboson  ->IntegralAndError(0, (histo_weighted_diboson->GetNbinsX()+1), err)) <<" +/- " <<err<< endl<< endl;      

  for  (int k = 0; k < 58; k++) {
      //cout << "sample "<< k << " new area: "<<nsample_new_area[k] <<" old area "<<  nsample_old_area[k] <<endl;
      if (nsample_new_area[k] > 0.) nsample_ratio[k] = nsample_old_area[k]/nsample_new_area[k];      
  }   
  
cout <<"if (run=="<<105200<<") weight ="<< nsample_ratio[ 0] << ";"<<endl;
cout <<"if (run=="<<105204<<") weight ="<< nsample_ratio[ 1] << ";"<<endl;
cout <<"if (run=="<<105985<<") weight ="<< nsample_ratio[ 2] << ";"<<endl;
cout <<"if (run=="<<105986<<") weight ="<< nsample_ratio[ 3] << ";"<<endl;
cout <<"if (run=="<<105987<<") weight ="<< nsample_ratio[ 4] << ";"<<endl;  
#ifdef QCDEE      
cout <<"if (run=="<<108326<<") weight ="<< nsample_ratio[ 5] << ";"<<endl;
#endif
#ifdef JXMUON     
cout <<"if (run=="<<109276<<") weight ="<< nsample_ratio[ 6] << ";"<<endl;
cout <<"if (run=="<<109277<<") weight ="<< nsample_ratio[ 7] << ";"<<endl;
cout <<"if (run=="<<109278<<") weight ="<< nsample_ratio[ 8] << ";"<<endl;
cout <<"if (run=="<<109279<<") weight ="<< nsample_ratio[ 9] << ";"<<endl;
cout <<"if (run=="<<109280<<") weight ="<< nsample_ratio[10] << ";"<<endl;
cout <<"if (run=="<<109281<<") weight ="<< nsample_ratio[11] << ";"<<endl;
//cout <<"if (run=="<<209435<<") weight ="<< nsample_ratio[12] << ";"<<endl;
#endif
cout <<"if (run=="<<107650<<") weight ="<< nsample_ratio[13] << ";"<<endl;
cout <<"if (run=="<<107651<<") weight ="<< nsample_ratio[14] << ";"<<endl;
cout <<"if (run=="<<107652<<") weight ="<< nsample_ratio[15] << ";"<<endl;
cout <<"if (run=="<<107653<<") weight ="<< nsample_ratio[16] << ";"<<endl;
cout <<"if (run=="<<107654<<") weight ="<< nsample_ratio[17] << ";"<<endl;
cout <<"if (run=="<<107655<<") weight ="<< nsample_ratio[18] << ";"<<endl;
cout <<"if (run=="<<107660<<") weight ="<< nsample_ratio[19] << ";"<<endl;
cout <<"if (run=="<<107661<<") weight ="<< nsample_ratio[20] << ";"<<endl;
cout <<"if (run=="<<107662<<") weight ="<< nsample_ratio[21] << ";"<<endl;
cout <<"if (run=="<<107663<<") weight ="<< nsample_ratio[22] << ";"<<endl;
cout <<"if (run=="<<107664<<") weight ="<< nsample_ratio[23] << ";"<<endl;
cout <<"if (run=="<<107665<<") weight ="<< nsample_ratio[24] << ";"<<endl;
cout <<"if (run=="<<107670<<") weight ="<< nsample_ratio[25] << ";"<<endl;
cout <<"if (run=="<<107671<<") weight ="<< nsample_ratio[26] << ";"<<endl;
cout <<"if (run=="<<107672<<") weight ="<< nsample_ratio[27] << ";"<<endl;
cout <<"if (run=="<<107673<<") weight ="<< nsample_ratio[28] << ";"<<endl;
cout <<"if (run=="<<107674<<") weight ="<< nsample_ratio[29] << ";"<<endl;
cout <<"if (run=="<<107675<<") weight ="<< nsample_ratio[30] << ";"<<endl;
cout <<"if (run=="<<107680<<") weight ="<< nsample_ratio[31] << ";"<<endl;
cout <<"if (run=="<<107681<<") weight ="<< nsample_ratio[32] << ";"<<endl;
cout <<"if (run=="<<107682<<") weight ="<< nsample_ratio[33] << ";"<<endl;
cout <<"if (run=="<<107683<<") weight ="<< nsample_ratio[34] << ";"<<endl;
cout <<"if (run=="<<107684<<") weight ="<< nsample_ratio[35] << ";"<<endl;
cout <<"if (run=="<<107685<<") weight ="<< nsample_ratio[36] << ";"<<endl;
cout <<"if (run=="<<107690<<") weight ="<< nsample_ratio[37] << ";"<<endl;
cout <<"if (run=="<<107691<<") weight ="<< nsample_ratio[38] << ";"<<endl;
cout <<"if (run=="<<107692<<") weight ="<< nsample_ratio[39] << ";"<<endl;
cout <<"if (run=="<<107693<<") weight ="<< nsample_ratio[40] << ";"<<endl;
cout <<"if (run=="<<107694<<") weight ="<< nsample_ratio[41] << ";"<<endl;
cout <<"if (run=="<<107695<<") weight ="<< nsample_ratio[42] << ";"<<endl;
cout <<"if (run=="<<107700<<") weight ="<< nsample_ratio[43] << ";"<<endl;
cout <<"if (run=="<<107701<<") weight ="<< nsample_ratio[44] << ";"<<endl;
cout <<"if (run=="<<107702<<") weight ="<< nsample_ratio[45] << ";"<<endl;
cout <<"if (run=="<<107703<<") weight ="<< nsample_ratio[46] << ";"<<endl;
cout <<"if (run=="<<107704<<") weight ="<< nsample_ratio[47] << ";"<<endl;
cout <<"if (run=="<<107705<<") weight ="<< nsample_ratio[48] << ";"<<endl;
cout <<"if (run=="<<106280<<") weight ="<< nsample_ratio[49] << ";"<<endl;
cout <<"if (run=="<<106281<<") weight ="<< nsample_ratio[50] << ";"<<endl;
cout <<"if (run=="<<106282<<") weight ="<< nsample_ratio[51] << ";"<<endl;
cout <<"if (run=="<<106283<<") weight ="<< nsample_ratio[52] << ";"<<endl;
cout <<"if (run=="<<108319<<") weight ="<< nsample_ratio[53] << ";"<<endl;
cout <<"if (run=="<<108320<<") weight ="<< nsample_ratio[54] << ";"<<endl;
cout <<"if (run=="<<108321<<") weight ="<< nsample_ratio[55] << ";"<<endl;
cout <<"if (run=="<<108322<<") weight ="<< nsample_ratio[56] << ";"<<endl;
#ifdef SU4
cout <<"if (run=="<<106484<<") weight ="<< nsample_ratio[57] << ";"<<endl;   
#endif    
    
  //RENORMALIZING
  TH1D*  histo_normalized_drellyan = histo_drellyan->Clone("histo_normalized_drellyan");
#ifdef SU4
  TH1D*  histo_normalized_su4 = histo_su4->Clone("histo_normalized_su4");  
#endif 
  TH1D*  histo_normalized_diboson = histo_diboson->Clone("histo_normalized_diboson");
  TH1D*  histo_normalized_ttbar = histo_ttbar->Clone("histo_normalized_ttbar");
  TH1D*  histo_normalized_wjets = histo_wjets->Clone("histo_normalized_wjets");
  TH1D*  histo_normalized_zjets = histo_zjets->Clone("histo_normalized_zjets");
#ifdef QCDEE
  TH1D*  histo_normalized_qcd = histo_qcd->Clone("histo_normalized_qcd");
#endif
  TH1D*  histo_normalized_mc = histo_mc->Clone("histo_normalized_mc");
#ifdef JXMUON  
  TH1D*  histo_normalized_qcd_mu = histo_qcd_mu->Clone("histo_normalized_qcd_mu");
#endif  
  TH1D*  histo_normalized_qcd_total = histo_qcd_total->Clone("histo_normalized_qcd_total");

  
  for (int i = 1; i < 10; i++)  {
    double weight= histo_data_clone->GetBinContent(i+1);
    
    //get #events per sample
    double nsample[60];
    
    //weight = 1; // debug
    
    nsample[ 0] = h1_105200->GetBinContent(i+1)*weight; 
    nsample[ 1] = h1_105204->GetBinContent(i+1)*weight;    
    
    nsample[ 2] = h1_105985->GetBinContent(i+1)*weight; 
    nsample[ 3] = h1_105986->GetBinContent(i+1)*weight; 
    nsample[ 4] = h1_105987->GetBinContent(i+1)*weight; 
    
#ifdef QCDEE                                    //QCD EE
    nsample[ 5] = h1_108326->GetBinContent(i+1)*weight; 
#else
    nsample[ 5] = 0; 
#endif

#ifdef JXMUON                        //QCD muon filtered  
    nsample[ 6] = h1_109276->GetBinContent(i+1)*weight; 
    nsample[ 7] = h1_109277->GetBinContent(i+1)*weight;
    nsample[ 8] = h1_109278->GetBinContent(i+1)*weight;
    nsample[ 9] = h1_109279->GetBinContent(i+1)*weight;
    nsample[10] = h1_109280->GetBinContent(i+1)*weight;
    nsample[11] = h1_109281->GetBinContent(i+1)*weight;
//    nsample[12] = h1_209435->GetBinContent(i+1)*weight;
    nsample[12] = 0; 
#else
    nsample[ 6] = 0; 
    nsample[ 7] = 0; 
    nsample[ 8] = 0; 
    nsample[ 9] = 0; 
    nsample[10] = 0; 
    nsample[11] = 0; 
    nsample[12] = 0; 
#endif
    
#endif //JXMUON

    nsample[13] = h1_107650->GetBinContent(i+1)*weight; 
    nsample[14] = h1_107651->GetBinContent(i+1)*weight;
    nsample[15] = h1_107652->GetBinContent(i+1)*weight;
    nsample[16] = h1_107653->GetBinContent(i+1)*weight;
    nsample[17] = h1_107654->GetBinContent(i+1)*weight;
    nsample[18] = h1_107655->GetBinContent(i+1)*weight;
    nsample[19] = h1_107660->GetBinContent(i+1)*weight; 
    nsample[20] = h1_107661->GetBinContent(i+1)*weight;
    nsample[21] = h1_107662->GetBinContent(i+1)*weight;
    nsample[22] = h1_107663->GetBinContent(i+1)*weight;
    nsample[23] = h1_107664->GetBinContent(i+1)*weight;
    nsample[24] = h1_107665->GetBinContent(i+1)*weight;
    nsample[25] = h1_107670->GetBinContent(i+1)*weight; 
    nsample[26] = h1_107671->GetBinContent(i+1)*weight;
    nsample[27] = h1_107672->GetBinContent(i+1)*weight;
    nsample[28] = h1_107673->GetBinContent(i+1)*weight;
    nsample[29] = h1_107674->GetBinContent(i+1)*weight;
    nsample[30] = h1_107675->GetBinContent(i+1)*weight;
					
    nsample[31] = h1_107680->GetBinContent(i+1)*weight; 
    nsample[32] = h1_107681->GetBinContent(i+1)*weight;
    nsample[33] = h1_107682->GetBinContent(i+1)*weight;
    nsample[34] = h1_107683->GetBinContent(i+1)*weight;
    nsample[35] = h1_107684->GetBinContent(i+1)*weight;
    nsample[36] = h1_107685->GetBinContent(i+1)*weight;

    nsample[37] = h1_107690->GetBinContent(i+1)*weight; 
    nsample[38] = h1_107691->GetBinContent(i+1)*weight;
    nsample[39] = h1_107692->GetBinContent(i+1)*weight;
    nsample[40] = h1_107693->GetBinContent(i+1)*weight;
    nsample[41] = h1_107694->GetBinContent(i+1)*weight;
    nsample[42] = h1_107695->GetBinContent(i+1)*weight;

    nsample[43] = h1_107700->GetBinContent(i+1)*weight; 
    nsample[44] = h1_107701->GetBinContent(i+1)*weight;
    nsample[45] = h1_107702->GetBinContent(i+1)*weight;
    nsample[46] = h1_107703->GetBinContent(i+1)*weight;
    nsample[47] = h1_107704->GetBinContent(i+1)*weight;
    nsample[48] = h1_107705->GetBinContent(i+1)*weight;

    nsample[49] = h1_106280->GetBinContent(i+1)*weight; 
    nsample[50] = h1_106281->GetBinContent(i+1)*weight; 
    nsample[51] = h1_106282->GetBinContent(i+1)*weight; 
    nsample[52] = h1_106283->GetBinContent(i+1)*weight; 

    nsample[53] = h1_108319->GetBinContent(i+1)*weight;
    nsample[54] = h1_108320->GetBinContent(i+1)*weight;
    nsample[55] = h1_108321->GetBinContent(i+1)*weight;
    nsample[56] = h1_108322->GetBinContent(i+1)*weight;
 
#ifdef SU4   
    nsample[57] = h1_106484->GetBinContent(i+1)*weight;
#else
    nsample[57] = 0;
#endif

    // normalize new areas!!!
    
    for (int k = 0; k < 58; k++) nsample[k] = nsample[k]*nsample_ratio[k];    
    
    //combine samples
    
#ifdef SU4   
    histo_normalized_su4->SetBinContent(i+1,nsample[ 57]);
#endif

    double total = 0;
    for (int k = 13; k < 31; k++) total += nsample[k];  
    histo_normalized_zjets->SetBinContent(i+1,total);
    
    total = 0;
    for (int k = 31; k < 53; k++) total += nsample[k];  
    histo_normalized_wjets->SetBinContent(i+1,total);

    total = 0;
    for (int k = 53; k < 57; k++) total += nsample[k];  
    histo_normalized_drellyan->SetBinContent(i+1,total);

    
    histo_normalized_ttbar->SetBinContent(i+1,nsample[ 0]+nsample[1]);
    histo_normalized_diboson->SetBinContent(i+1,nsample[ 2]+nsample[3]+nsample[4]);
#ifdef QCDEE                                    //QCD EE
    histo_normalized_qcd->SetBinContent(i+1,nsample[ 5]);
#endif
#ifdef JXMUON                        //QCD muon filtered
    histo_normalized_qcd_mu->SetBinContent(i+1,nsample[ 7]+nsample[ 8]+nsample[ 9]+nsample[ 10]+nsample[ 11]+nsample[ 12]);

#endif
    
    for (int k = 0; k < 58; k++) {
      nsample_new_area_norm[k] += nsample[k];  
      nsample_old_area_norm[k] += nsample[k]/weight;
    }
  }    
  
  histo_normalized_qcd_total->Reset();
  histo_normalized_mc->Reset();
#ifdef QCDEE  
  histo_normalized_qcd_total->Add(histo_normalized_qcd, 1.);
#endif
#ifdef JXMUON
  histo_normalized_qcd_total->Add(histo_normalized_qcd_mu, 1.);
#endif  
  histo_normalized_mc	->Add(histo_normalized_qcd_total, 1.);
  histo_normalized_mc	->Add(histo_normalized_wjets, 1.);
  histo_normalized_mc	->Add(histo_normalized_drellyan, 1.);
  histo_normalized_mc	->Add(histo_normalized_ttbar, 1.);
  histo_normalized_mc	->Add(histo_normalized_zjets, 1.);  
  histo_normalized_mc	->Add(histo_normalized_diboson, 1.);  

  // after renormalizing
  
  cout << endl << "AFTER RENORMALIZING"<<endl<<endl;
  
  cout << "MC      : " << (histo_normalized_mc       ->IntegralAndError(0, (histo_normalized_mc->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 
  cout << "QCD     : " << (histo_normalized_qcd_total->IntegralAndError(0, (histo_normalized_qcd_total->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;
  cout << "Wjets   : " << (histo_normalized_wjets    ->IntegralAndError(0, (histo_normalized_wjets->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;    
  cout << "Zjets   : " << (histo_normalized_zjets    ->IntegralAndError(0, (histo_normalized_zjets->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;    
  cout << "DY      : " << (histo_normalized_drellyan ->IntegralAndError(0, (histo_normalized_drellyan->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 
  cout << "ttbar   : " << (histo_normalized_ttbar    ->IntegralAndError(0, (histo_normalized_ttbar->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;    
#ifdef SU4
  cout << "su4     : " << (histo_normalized_su4      ->IntegralAndError(0, (histo_normalized_su4->GetNbinsX()+1), err)) <<" +/- " <<err<< endl;      
#endif  
  cout << "diboson : " << (histo_normalized_diboson  ->IntegralAndError(0, (histo_normalized_diboson->GetNbinsX()+1), err)) <<" +/- " <<err<< endl<< endl;      

/*  for  (int k = 0; k < 57; k++) {
      cout << "sample "<< k << " new area: "<<nsample_new_area_norm[k] <<" old area "<<  nsample_old_area_norm[k] <<endl;
  }   
  */
  c1->cd(4);
  histo_data->GetXaxis()->SetRangeUser(x_min,x_max);  //inv mass
  histo_data->Draw("AXIS"); //draws only the axis
  histo_data->Draw("zp same");
  histo_normalized_mc->Draw("hist same ][");// ROOT CRASHES!!

  THStack* histo_normalized_stack  = new THStack();
  histo_normalized_stack->Add(histo_normalized_zjets);
  histo_normalized_stack->Add(histo_normalized_ttbar);
  histo_normalized_stack->Add(histo_normalized_drellyan);
  histo_normalized_stack->Add(histo_normalized_diboson);
  histo_normalized_stack->Add(histo_normalized_wjets);
  histo_normalized_stack->Add(histo_normalized_qcd_total);
   
#ifdef FIRSTROOT
#else
  histo_normalized_stack->Draw("hist same");
#endif  
#ifdef MC
  histo_normalized_mc->SetFillColor(kWhite);
  histo_normalized_mc->SetLineColor(kRed);
  histo_normalized_mc->Draw("hist same");
#endif  

  legend->Draw();
  n.DrawLatex(0.20,0.85,title);
  n.DrawLatex(0.20,0.75,"AFTER RENORMALIZING");
  
  return;
  }
        
