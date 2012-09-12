
  
  int binmin, binmax;
  TString x_string, y_string, title, title2, title3, title4, histo_string, filename;
  bool rebin = false;

#define ELECTRON
#define TAGPROBE
//#define BOOTSTRAP   
//#define MUON 

#define ALL
//#define PERIOD1 // DF-G-H-I
//#define PERIOD2   // J-K-L-M

#define MC   
//#define ETA
#define PT  
//#define PHI  
//#define ETAPHI
//#define PTETA  
//#define H2D  
#define ZOOM
//#define PTETA
//#define BARREL
//#define ENDCAP 

#ifdef H2D
#include "AtlasStyle2D.C"
#else
#include "AtlasStyle.C"
#endif  

  int binmin, binmax;
  TString x_string, y_string, title, title2, title3, title4, histo_string, filename;
  bool rebin = false;

void triggerPlots() {

// plot 
  TString filename = "trigger_";
  
#ifdef ALL
  filename += "all_";
#endif
#ifdef PERIOD1
  filename += "DtoI_";
#endif
#ifdef PERIOD2
  filename += "JtoM_";
#endif

#ifdef ELECTRON
  filename += "el_";
#endif
#ifdef MUON
  filename += "mu_";
#endif

#ifdef PT
  filename += "pt_";
#endif
#ifdef PTETA
  filename += "pt_eta_";
#endif
#ifdef ETAPHI
  filename += "eta_phi_";
#endif
#ifdef ZOOM
  filename += "zoom_";
#endif
#ifdef ETA
  filename += "eta_";
#endif
#ifdef PHI
  filename += "phi_";
#endif
#ifdef BARREL
  filename += "barrel_";
#endif
#ifdef ENDCAP
  filename += "endcap_";
#endif
#ifdef MC
  filename += "mc_";
#endif

#ifdef TAGPROBE
  filename += "TP";
#endif
#ifdef BOOTSTRAP
  filename += "BS";
#endif
  
  gROOT->SetStyle("ATLAS");
  SetAtlasStyle();
  gROOT->ForceStyle();
  
// TFile* file_electronStream  = TFile::Open("root/trigger_107650_electronStream.root");
// TFile* file_electronStream  = TFile::Open("root/trigger_190878_electronStream.root");
// TFile* file_electronStream  = TFile::Open("root/trigger_D_electronStream.root");
// TFile* file_electronStream  = TFile::Open("root/trigger_107652_electronStream.root");
// TFile* file_electronStream  = TFile::Open("root/trigger_107660_muonStream.root");

#ifdef PERIOD2
#ifdef ELECTRON
 TFile* file_electronStream0  = TFile::Open("root/trigger_J_electronStream.root");
 TFile* file_electronStream1  = TFile::Open("root/trigger_K_electronStream.root");
 TFile* file_electronStream2  = TFile::Open("root/trigger_L_electronStream.root");
 TFile* file_electronStream3  = TFile::Open("root/trigger_M_electronStream.root");
#endif
#ifdef MUON
 TFile* file_electronStream0  = TFile::Open("root/trigger_J_muonStream.root");
 TFile* file_electronStream1  = TFile::Open("root/trigger_K_muonStream.root");
 TFile* file_electronStream2  = TFile::Open("root/trigger_L_muonStream.root");
 TFile* file_electronStream3  = TFile::Open("root/trigger_M_muonStream.root");
#endif

#endif

#ifdef PERIOD1
#ifdef ELECTRON
 TFile* file_electronStream0  = TFile::Open("root/trigger_DEF_electronStream.root");
 TFile* file_electronStream1  = TFile::Open("root/trigger_G_electronStream.root");
 TFile* file_electronStream2  = TFile::Open("root/trigger_H_electronStream.root");
 TFile* file_electronStream3  = TFile::Open("root/trigger_I_electronStream.root");
#endif
#ifdef MUON
 TFile* file_electronStream0  = TFile::Open("root/trigger_G_muonStream.root");
 TFile* file_electronStream1  = TFile::Open("root/trigger_H_muonStream.root");
 TFile* file_electronStream2  = TFile::Open("root/trigger_I_muonStream.root");
 TFile* file_electronStream3  = TFile::Open("root/trigger_I_muonStream.root"); //dummy, don't plot
#endif
#endif

#ifdef ALL
// TFile* file_electronStream0  = TFile::Open("root/trigger_muonStream.root"); // my matching
// TFile* file_electronStream0  = TFile::Open("root/trigger_107660.root");
// TFile* file_electronStream0  = TFile::Open("root/trigger_190933_muonStream.root");
// TFile* file_electronStream0  = TFile::Open("root/trigger_107650_electronStream.root");//Zee
// TFile* file_electronStream0  = TFile::Open("root/trigger_106484_electronStream.root");
#ifdef ELECTRON
 TFile* file_electronStream0  = TFile::Open("root/trigger_electronStream.root"); //matching from d3pd
#endif
#ifdef MUON
 TFile* file_electronStream0  = TFile::Open("root/trigger_muonStream.root"); //matching from d3pd
#endif
#endif
#ifdef MC
#ifdef ELECTRON
 TFile* file_electronStream_mc  = TFile::Open("root/trigger_107650.root");//Zee
#endif
#ifdef MUON
 TFile* file_electronStream_mc  = TFile::Open("root/trigger_107660.root");//Zmumu
#endif
#endif

#ifdef ELECTRON
 histo_string = "h_el_trg_";
#endif
#ifdef MUON
 histo_string = "h_mu_trg_";
#endif
 
#ifdef PT
  histo_string += "pt"; //leading electron pt
#endif
#ifdef ETA
  histo_string += "eta"; 
#endif
#ifdef PHI
  histo_string += "phi"; 
#endif
#endif
#ifdef PTETA
  histo_string += "pt_eta"; //leading electron eta
#endif
#ifdef ETAPHI
  histo_string += "eta_phi"; 
#endif


#ifdef BARREL
  histo_string += "_barrel";
#endif
#ifdef ENDCAP
  histo_string += "_endcap";
#endif

#endif
  
#ifdef ALL
  TH2F *h2_ds0; 
  TH1D *h1_ds0, *h1_ds0_bs;
  TH1D *h1_ds0_total, *h1_ds0_bs_total;
#ifdef H2D
  TH3F *h3_ds0; 
#endif
#ifdef MC
  TH2F *h2_ds0_mc; 
  TH1D *h1_ds0_mc_total,*h1_ds0_mc;
#endif
#else
  TH2F *h2_ds0, *h2_ds1, *h2_ds2, *h2_ds3, *h2_ds4; 
  TH1D *h1_ds0, *h1_ds1, *h1_ds2, *h1_ds3, *h1_ds4;
  TH1D *h1_ds0_total, *h1_ds1_total, *h1_ds2_total, *h1_ds3_total, *h1_ds4_total;
#endif  

  cout << "retrieving "<<histo_string <<endl;

#ifdef H2D
  h3_ds0 = (TH3F*)file_electronStream0 ->Get(histo_string); 
#else  

#ifdef ALL
  h2_ds0 = (TH2F*)file_electronStream0 ->Get(histo_string); 
#else   
  h2_ds0 = (TH2F*)file_electronStream0 ->Get(histo_string); 
  h2_ds1 = (TH2F*)file_electronStream1 ->Get(histo_string); 
  h2_ds2 = (TH2F*)file_electronStream2 ->Get(histo_string); 
  h2_ds3 = (TH2F*)file_electronStream3 ->Get(histo_string); 
  //h2_ds4 = (TH2F*)file_electronStream4 ->Get(histo_string); 
#endif
#endif  

#endif

#ifdef MC
  h2_ds0_mc = (TH2F*)file_electronStream_mc ->Get(histo_string); 
#endif
  
#ifdef ELECTRON
  binmin = 14;//after EEcut
#endif
  
#ifdef MUON
  binmin = 16;//after MUMUcut
#endif
  binmax = binmin;

#ifdef BOOTSTRAP
  binmin +=4;
  binmax +=4;
#endif
    
  cout << "total bin "<<binmin<<endl; 

#ifdef H2D
  h3_ds0 = (TH3F*)file_electronStream0 ->Get(histo_string);

  int nbinsy = h3_ds0->GetYaxis()->GetNbins(); 
  int nbinsz = h3_ds0->GetZaxis()->GetNbins(); 

  TH2F* h2_ds0_total  = new TH2F("h2_ds0_total","h2_ds0_total",  
      h3_ds0->GetZaxis()->GetNbins(), h3_ds0->GetZaxis()->GetXmin(), h3_ds0->GetZaxis()->GetXmax(), 
      h3_ds0->GetYaxis()->GetNbins(), h3_ds0->GetYaxis()->GetXmin(), h3_ds0->GetYaxis()->GetXmax());
  
  TH2F* h2_ds0  = new TH2F("h2_ds0","h2_ds0",  
      h3_ds0->GetZaxis()->GetNbins(), h3_ds0->GetZaxis()->GetXmin(), h3_ds0->GetZaxis()->GetXmax(), 
      h3_ds0->GetYaxis()->GetNbins(), h3_ds0->GetYaxis()->GetXmin(), h3_ds0->GetYaxis()->GetXmax());
  cout << " "<<h3_ds0->GetZaxis()->GetNbins() << " "<< h3_ds0->GetZaxis()->GetXmin()<<  " "<< h3_ds0->GetZaxis()->GetXmax()<<  " "<< 
      h3_ds0->GetYaxis()->GetNbins()<<  " "<< h3_ds0->GetYaxis()->GetXmin() << " "<< h3_ds0->GetYaxis()->GetXmax()<<endl;

  for (int i = 0; i <= nbinsy; i++){
    for (int j = 0; j <= nbinsz; j++){
      double bin_total = h3_ds0->GetBinContent(binmin,i,j);
      double bin_pass = h3_ds0->GetBinContent(binmin+1,i,j);
      h2_ds0_total->SetBinContent(j,i,bin_total);
      h2_ds0->SetBinContent(j,i,bin_pass);
      //if (bin_pass>bin_total)
      //if (bin_total>0) cout << "pass "<<bin_pass<<" total "<<bin_total<< " (x,y) "<<i<<","<<j<<endl;
    }
  }
  
#else  

#ifdef ALL

  h1_ds0_total = h2_ds0->ProjectionY("h1_ds0_total", binmin, binmax, "e");
  #ifdef MC
  h1_ds0_mc_total = h2_ds0_mc->ProjectionY("h1_ds0_mc_total", binmin, binmax, "e"); 
  #endif

  
#else   

  h1_ds0_total = h2_ds0->ProjectionY("h1_ds0_total", binmin, binmax, "e");
  h1_ds1_total = h2_ds1->ProjectionY("h1_ds1_total", binmin, binmax, "e");
  h1_ds2_total = h2_ds2->ProjectionY("h1_ds2_total", binmin, binmax, "e");
  h1_ds3_total = h2_ds3->ProjectionY("h1_ds3_total", binmin, binmax, "e");
//  h1_ds4_total = h2_ds4->ProjectionY("h1_ds4_total", binmin, binmax, "e");

#endif //All 

#endif  //H2D

  binmin +=1;
  binmax = binmin;
  
  cout << "passed bin "<<binmin<<endl; 

#ifdef H2D

#else  
    
#ifdef ALL
  Double_t err=0.;

  h1_ds0   = h2_ds0->ProjectionY("h1_ds0", binmin, binmax, "e");

  h1_ds0->Sumw2();
  h1_ds0_total->Sumw2();

  cout <<endl<< "Entries trigger 0                : " << (h1_ds0_total->IntegralAndError(0, (h1_ds0_total->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 
  cout << "after Tag & Probe                : " << (h1_ds0->IntegralAndError(0, (h1_ds0->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 

  #ifdef MC
  h1_ds0_mc = h2_ds0_mc->ProjectionY("h1_ds0_mc", binmin, binmax, "e"); 
  h1_ds0_mc->Sumw2();
  h1_ds0_mc_total->Sumw2();
  h1_ds0_mc->SetLineColor(kRed);
  h1_ds0_mc->SetMarkerColor(kRed);

  cout <<endl<< "Entries trigger 0                : " << (h1_ds0_mc_total->IntegralAndError(0, (h1_ds0_mc_total->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 
  cout << "after Tag & Probe                : " << (h1_ds0_mc->IntegralAndError(0, (h1_ds0->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 
  #endif

#else   

  h1_ds0 = h2_ds0->ProjectionY("h1_ds0", binmin, binmax, "e");
  h1_ds1 = h2_ds1->ProjectionY("h1_ds1", binmin, binmax, "e");
  h1_ds2 = h2_ds2->ProjectionY("h1_ds2", binmin, binmax, "e");
  h1_ds3 = h2_ds3->ProjectionY("h1_ds3", binmin, binmax, "e");
//  h1_ds4 = h2_ds4->ProjectionY("h1_ds4", binmin, binmax, "e");


  h1_ds1->SetLineColor(kRed);
  h1_ds1->SetMarkerColor(kRed);
  h1_ds2->SetLineColor(kBlue);
  h1_ds2->SetMarkerColor(kBlue);
  h1_ds3->SetLineColor(kGreen);
  h1_ds3->SetMarkerColor(kGreen);
//  h1_ds4->SetLineColor(kGreen);
//  h1_ds4->SetMarkerColor(kGreen);

  
  h1_ds0->Sumw2();
  h1_ds1->Sumw2();
  h1_ds2->Sumw2();
  h1_ds3->Sumw2();
//  h1_ds4->Sumw2();

  h1_ds0_total ->Sumw2();
  h1_ds1_total->Sumw2();
  h1_ds2_total->Sumw2();
  h1_ds3_total->Sumw2();
//  h1_ds4_total->Sumw2();
    
  Double_t err=0.;
  cout <<endl<< "Entries trigger 0                : " << (h1_ds0_total->IntegralAndError(0, (h1_ds0_total->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 
  cout << "after Tag & Probe / BS           : " << (h1_ds0->IntegralAndError(0, (h1_ds0->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 
  cout <<endl<< "Entries trigger 1                : " << (h1_ds1_total->IntegralAndError(0, (h1_ds1_total->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 
  cout << "after Tag & Probe / BS           : " << (h1_ds1->IntegralAndError(0, (h1_ds1->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 
  cout <<endl<< "Entries trigger 2                : " << (h1_ds2_total->IntegralAndError(0, (h1_ds2_total->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 
  cout << "after Tag & Probe / BS           : " << (h1_ds2->IntegralAndError(0, (h1_ds2->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 
  cout <<endl<< "Entries trigger 3                : " << (h1_ds3_total->IntegralAndError(0, (h1_ds3_total->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 
  cout << "after Tag & Probe / BS           : " << (h1_ds3->IntegralAndError(0, (h1_ds3->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 
//  cout <<endl<< "Entries trigger 4                : " << (h1_ds4_total->IntegralAndError(0, (h1_ds4_total->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 
//  cout << "after Tag & Probe / BS           : " << (h1_ds4->IntegralAndError(0, (h1_ds4->GetNbinsX()+1), err)) <<" +/- " <<err<< endl; 
#endif //ALL

#endif //H2D

// Using Tefficiency

#ifdef H2D
  //h_trg_2d_yz->Draw();
  //h_trg_2d_yz_pass->Draw();
  const TH2& pass  = *h2_ds0;
  const TH2& total = *h2_ds0_total;

  TEfficiency* pEff0 = 0;

  TCanvas *c2 = new TCanvas("canvas2","canvas2", 200,10,900,800);  // 1D histo
  
  c2->cd();

  if(TEfficiency::CheckConsistency(pass,total)){
    pEff0 = new TEfficiency(pass,total);

#ifdef ETAPHI
//   pass.GetXaxis()->SetRangeUser(10.,100.);  //inv mass
    pass.GetYaxis()->SetRangeUser(-2.4,2.4);  //inv mass
    pass.GetXaxis()->SetTitle("Phi");  //inv mass
    pass.GetYaxis()->SetTitle("Eta");  //inv mass
#endif
#ifdef PTETA
    pass.GetYaxis()->SetRangeUser(10.,100.);  //inv mass
    pass.GetXaxis()->SetRangeUser(-2.4,2.4);  //inv mass
    pass.GetYaxis()->SetTitle("Pt [GeV]");  //inv mass
    pass.GetXaxis()->SetTitle("Eta");  //inv mass
#endif
    pass.Draw("AXIS");
    pEff0->Draw("COLZ same");
   //pass.Draw();
  }
  //h3_ds0->Draw();
  //h2_ds0_total->Draw();
#else

#ifdef ALL
  TEfficiency* pEff0 = 0;
  
  #ifdef MC
  TEfficiency* pEff0_mc = 0;
  const TH1& pass_mc  = *h1_ds0_mc;
  const TH1& total_mc = *h1_ds0_mc_total;
  if(TEfficiency::CheckConsistency(pass_mc,total_mc)){
   pEff0_mc = new TEfficiency(pass_mc,total_mc);
   pEff0_mc->SetLineColor(kRed);
   pEff0_mc->SetMarkerColor(kRed);
   pEff0_mc->SetMarkerSize(1);
  }
  #endif

  const TH1& pass     = *h1_ds0;
  const TH1& total    = *h1_ds0_total;
  
  if(TEfficiency::CheckConsistency(pass,total)){
   pEff0 = new TEfficiency(pass,total);
   //pEff0->SetStatisticOption(TEfficiency::kFCP);
 }


#else  //all 

  TEfficiency* pEff0 = 0;
  TEfficiency* pEff1 = 0;
  TEfficiency* pEff2 = 0;
  TEfficiency* pEff3 = 0;
//  TEfficiency* pEff4 = 0;
  
  //h_pass and h_total are valid and consistent histograms
  const TH1& pass0  = *h1_ds0;
  const TH1& pass1  = *h1_ds1;
  const TH1& pass2  = *h1_ds2;
  const TH1& pass3  = *h1_ds3;
//  const TH1& pass4  = *h1_ds4;
  
  const TH1& total0 = *h1_ds0_total;
  const TH1& total1 = *h1_ds1_total;
  const TH1& total2 = *h1_ds2_total;
  const TH1& total3 = *h1_ds3_total;
//  const TH1& total4 = *h1_ds4_total;
  
  if(TEfficiency::CheckConsistency(pass0,total0)){
   pEff0 = new TEfficiency(pass0,total0);
   //pEff0->SetStatisticOption(TEfficiency::kFCP);
 }

  if(TEfficiency::CheckConsistency(pass1,total1)){
   pEff1 = new TEfficiency(pass1,total1);
   pEff1->SetLineColor(kRed);
   pEff1->SetMarkerColor(kRed);
   pEff1->SetMarkerSize(1);
 }

  if(TEfficiency::CheckConsistency(pass2,total2)){
   pEff2 = new TEfficiency(pass2,total2);
   pEff2->SetLineColor(kBlue);
   pEff2->SetMarkerColor(kBlue);
   pEff2->SetMarkerSize(1);
 }

  if(TEfficiency::CheckConsistency(pass3,total3)){
   pEff3 = new TEfficiency(pass3,total3);
   pEff3->SetLineColor(kGreen);
   pEff3->SetMarkerColor(kGreen);
   pEff3->SetMarkerSize(1);
 }

//  if(TEfficiency::CheckConsistency(pass4,total4)){
//   pEff4 = new TEfficiency(pass4,total4);
//   pEff4->SetLineColor(kGreen);
//   pEff4->SetMarkerColor(kGreen);
//   pEff4->SetMarkerSize(1);
// }

#endif  //ALL 

#endif  //H2D

//Efficiency
#ifdef PT

#ifdef ELECTRON
int binPlateau = 12;  // bin 0: 0-1 GeV; bin 1: 1-2 GeV; ...;
#endif
#ifdef MUON
int binPlateau = 8;  // bin 0: 0-5 GeV; bin 1: 5-10 GeV; bin 2: 10-15 GeV; bin 3: 15-20 GeV; bin 4: 20-25 GeV; bin 5: 25-30 GeV;
#endif

//#ifdef ALL
//#else
int nTotal0 = h1_ds0_total->IntegralAndError(binPlateau, (h1_ds0_total->GetNbinsX()+1), err);
int nds0 = h1_ds0->IntegralAndError(binPlateau, (h1_ds0->GetNbinsX()+1), err);

  cout <<  endl; 
  cout << "Plateau bin "<< binPlateau  <<" : "<< nTotal0 << endl; 
  cout << " trigger0   : "<< nds0 << " efficiency "<< 1.*nds0/nTotal0<<endl; 

  cout <<  endl;
  binPlateau+=3; 

  nTotal0 = h1_ds0_total->IntegralAndError(binPlateau, (h1_ds0_total->GetNbinsX()+1), err);
  nds0 = h1_ds0->IntegralAndError(binPlateau, (h1_ds0->GetNbinsX()+1), err);

  cout << "Plateau bin "<< binPlateau  <<" : "<< nTotal0 << endl; 
  cout << " trigger0   : "<< nds0 << " efficiency "<< 1.*nds0/nTotal0<<endl; 
//#endif

#endif
/*
  TCanvas *c1 = new TCanvas("canvas1","canvas1", 200,10,1000,800);  // 1D histo
  c1->cd();
//  h1_ds0->Rebin(2);
//  h1_ds0_total->Rebin(2);
  h1_ds0->Draw();
  h1_ds0_total->Draw("same");

*/

#ifdef H2D
#else

  h1_ds0->SetMaximum(1.1);
  h1_ds0->SetMinimum(0.);
#ifdef PT
  h1_ds0->GetXaxis()->SetRangeUser(10.,100.);  //inv mass
#ifdef MUON
  h1_ds0->GetXaxis()->SetRangeUser(0.,100.);  //inv mass
#endif
  h1_ds0->GetXaxis()->SetTitle("Pt [GeV]");  //inv mass
#ifdef ZOOM
  h1_ds0->GetXaxis()->SetRangeUser(10.,50.);  //inv mass
  h1_ds0->GetXaxis()->SetTitle("Pt [GeV]");  //inv mass
  h1_ds0->SetMaximum(1.);
  h1_ds0->SetMinimum(0.8);  
#ifdef MUON
  h1_ds0->GetXaxis()->SetRangeUser(0.5,50.);  //inv mass
  h1_ds0->SetMinimum(0.);  
#endif
#endif  
#endif
#ifdef ETA
  h1_ds0->GetXaxis()->SetRangeUser(-2.5,2.5);  //inv mass
  h1_ds0->GetXaxis()->SetTitle("Eta");  //inv mass
#ifdef BARREL
  h1_ds0->GetXaxis()->SetRangeUser(-1.05,1.05);  //inv mass
#endif
#endif
#ifdef PHI
  h1_ds0->GetXaxis()->SetRangeUser(-3.14,3.14);  //inv mass
  h1_ds0->GetXaxis()->SetTitle("Phi");  //inv mass
#endif


  TLegend *legend = new TLegend(0.50,0.25,0.90,0.54);
  legend->SetBorderSize(0);
  legend->SetTextFont(42);
  legend->SetTextSize(0.04);
  legend->SetFillColor(0);
  legend->SetLineColor(0);
  

#ifdef ALL
  #ifdef MUON
  legend->SetHeader("EF_mu6"); 
  #else
  legend->SetHeader("EF_e10_medium"); 
  #endif
  #ifdef TAGPROBE
  legend->AddEntry(h1_ds0,   "Tag&Probe - data","flp");// 
  #ifdef MC
  legend->AddEntry(h1_ds0_mc,   "Tag&Probe - MC Z","flp");// 
  #endif
  #endif
  #ifdef BOOTSTRAP
  legend->AddEntry(h1_ds0,"Bootstrap - data","flp");// 
  #ifdef MC
  legend->AddEntry(h1_ds0_mc,   "Bootstrap - ttbar","flp");// 
   pEff0_mc->SetLineColor(kBlack);
   pEff0_mc->SetMarkerColor(kBlack);
  #endif
  #endif
#else

  #ifdef MUON
    #ifdef TAGPROBE
      legend->SetHeader("EF_mu6 - Tag&Probe"); 
    #else
      legend->SetHeader("EF_mu6 - Bootstrap");
    #endif   
  #else
    #ifdef TAGPROBE
      legend->SetHeader("EF_e10_medium - Tag&Probe"); 
    #else
      legend->SetHeader("EF_e10_medium - Bootstrap");
    #endif 
  #endif       
#endif


#ifdef PERIOD1
#ifdef ELECTRON
  legend->AddEntry(h1_ds0," period D-F","flp");// 
  legend->AddEntry(h1_ds1," period G","flp");// 
  legend->AddEntry(h1_ds2," period H","flp");// 
  legend->AddEntry(h1_ds3," period I","flp");// 
#endif
#ifdef MUON
  legend->AddEntry(h1_ds0," period G","flp");// 
  legend->AddEntry(h1_ds1," period H","flp");// 
  legend->AddEntry(h1_ds2," period I","flp");// 
#endif
#endif

#ifdef PERIOD2
  legend->AddEntry(h1_ds0," period J","flp");// 
  legend->AddEntry(h1_ds1," period K","flp");// 
  legend->AddEntry(h1_ds2," period L","flp");// 
  legend->AddEntry(h1_ds3," period M","flp");// 
#endif


//  legend->Draw();

  TCanvas *c2 = new TCanvas("canvas2","canvas2", 200,10,1000,800);  // 1D histo
  
  c2->cd();
  
//  pEff2->SetStatisticOption(TEfficiency::kFCP);  //DEFAULT
//  pEff2->SetStatisticOption(TEfficiency::kFNormal);
 // pEff2->SetStatisticOption(TEfficiency::kFWilson);
//  pEff2->SetStatisticOption(TEfficiency::kFAC);
//  pEff2->SetStatisticOption(TEfficiency::kFFC);
//  pEff2->SetStatisticOption(TEfficiency::kBJeffrey);
//  pEff2->SetStatisticOption(TEfficiency::kBUniform);
//  pEff2->SetStatisticOption(TEfficiency::kBBayesian);
  h1_ds0->GetYaxis()->SetTitle("Efficiency");  //inv mass
  h1_ds0->Draw("AXIS"); // I need this to be able to zoom the graph
  pEff0->Draw("P same");
#ifdef ALL
  #ifdef MC
  pEff0_mc->Draw("P same");
  #endif
#else
  pEff1->Draw("P same");
  pEff2->Draw("P same");
#ifdef PERIOD2
  pEff3->Draw("P same");
#endif
#ifdef PERIOD1
#ifdef ELECTRON
  pEff3->Draw("P same");
#endif
#endif
//  pEff4->Draw("P same");
#endif
  legend->Draw();

#endif
  c2->Print("plots/"+filename+".eps"); 
    
}
 
