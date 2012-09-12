addErrors(){
  
  unsigned int nbin = histo_wjets->GetNbinsX();
  //cout << "Error on drellyan? JES? "<<endl;
  for (unsigned int i = 0; i < (nbin+1); i++){

  // get statistical error
      
    float stat_err_w = histo_wjets->GetBinError(i);
    float stat_err_z = histo_zjets->GetBinError(i);
#ifdef QCD
    float stat_err_q = histo_qcd_total  ->GetBinError(i);
#endif
    float stat_err_t = histo_ttbar->GetBinError(i);
    float stat_err_s = histo_su4  ->GetBinError(i);
//    float stat_err_d = histo_drellyan->GetBinError(i);
    
  
  // add luminosity error (3.7%)
  // dlumi = 0.2 * lumi
  // nevts_renorm = nevts * lumi
  // d_nevts_renorm = nevts * dlumi + dnevts * lumi

    float dlumi = 0.037; //because I have here already renormalized events...

    float lumi_err_w = dlumi * histo_wjets->GetBinContent(i);
    float lumi_err_z = dlumi * histo_zjets->GetBinContent(i);
#ifdef QCD
    float lumi_err_q = dlumi * histo_qcd_total  ->GetBinContent(i);
#endif
    float lumi_err_t = dlumi * histo_ttbar->GetBinContent(i);
    float lumi_err_s = dlumi * histo_su4  ->GetBinContent(i);
//    float lumi_err_d = dlumi * histo_drellyan->GetBinContent(i);
    

  // add MC error (30% for W and Z)

    float mc_err_w = .3 * histo_wjets->GetBinContent(i);
    float mc_err_z = .3 * histo_zjets->GetBinContent(i);
#ifdef QCD
    float mc_err_q = .1 * histo_qcd_total  ->GetBinContent(i);  //10% normalization and JES
#endif
    float mc_err_t = 0. * histo_ttbar->GetBinContent(i);
    float mc_err_s = 0. * histo_su4  ->GetBinContent(i);
//    float mc_err_d = 0. * histo_drellyan->GetBinContent(i);   //what error for Drell-yan?


    float err_w = sqrt(stat_err_w*stat_err_w + lumi_err_w*lumi_err_w + mc_err_w*mc_err_w);
    float err_z = sqrt(stat_err_z*stat_err_z + lumi_err_z*lumi_err_z + mc_err_z*mc_err_z);
#ifdef QCD
    float err_q = sqrt(stat_err_q*stat_err_q + lumi_err_q*lumi_err_q + mc_err_q*mc_err_q);
#endif
    float err_t = sqrt(stat_err_t*stat_err_t + lumi_err_t*lumi_err_t + mc_err_t*mc_err_t);
    float err_s = sqrt(stat_err_s*stat_err_s + lumi_err_s*lumi_err_s + mc_err_s*mc_err_s);
//    float err_d = sqrt(stat_err_d*stat_err_d + lumi_err_d*lumi_err_d + mc_err_d*mc_err_d);
    
 //   cout << "bin: "<< i<<" bin content: "<<histo_su4  ->GetBinContent(i)<< "  error from sumw2: "<< stat_err_s<< " error from lumi: "<< lumi_err_s<< " total error: "<< err_s<<endl;

#ifdef WJETS
    histo_wjets->SetBinError(i, err_w);
#endif
#ifdef ZJETS
    histo_zjets->SetBinError(i, err_z);
#endif
#ifdef QCD
    histo_qcd_total->SetBinError(i, err_q);
#endif
 #ifdef TTBAR
   histo_ttbar->SetBinError(i, err_t);
#endif
#ifdef SU4
    histo_su4  ->SetBinError(i, err_s);     
#endif
//    histo_drellyan->SetBinError(i, err_d);
    }
}

TGraphAsymmErrors* TH1TOTGraphAsymNoerrorx(TH1 *h1, double scale){


if (!h1) cout << "TH1TOTGraph: histogram not found !" << endl;

TGraphAsymmErrors* g1= new TGraphAsymmErrors();

Double_t x, y, ex, eylow, eyhigh;
for (Int_t i=1; i<=h1->GetNbinsX(); i++) {
  y=h1->GetBinContent(i);
//  ey=h1->GetBinError(i);
  x=h1->GetBinCenter(i);
 ex=h1->GetBinWidth(i)/2.;
 if(y==0.) eyhigh=0.;
 else eyhigh=calcPoissonCLUpper(0.68,y)-y;
 eylow=y-calcPoissonCLLower(0.68,y);


  //cout << i<<" x,y = " << x << " " << y << " ex,ey = " << ex << " " << ey << " scale = "  << scale <<endl;

  g1->SetPoint((i-1),x,y*scale);
  g1->SetPointError((i-1),0.,0.,eylow*scale,eyhigh*scale);

}
//g1->Print();

return g1;
}


// Calculate lower confidence limit
//   e.g. to calculate the 68% lower limit for 2 observed events:
//      calcPoissonCLLower(0.68, 2.)

double calcPoissonCLLower(Double_t q, Double_t obs) {

 Double_t LL = 0.;

 if (obs >= 0.) {
   Double_t a = (1. - q) / 2.; // = 0.025 for 95% confidence interval
   LL = TMath::ChisquareQuantile(a, 2.*obs) / 2.;
 }

 return LL;

}

// Calculate upper confidence limit
//   e.g. to calculate the 68% upper limit for 2 observed events:
//      calcPoissonCLUpper(0.68, 2.)

double calcPoissonCLUpper(Double_t q, Double_t obs) {

 Double_t UL = 0.;

 if (obs >= 0.) {
   Double_t a = 1. - (1. - q) / 2.; // = 0.025 for 95% confidence interval
   UL = TMath::ChisquareQuantile(a, 2.* (obs + 1.)) / 2.;
 }

 return UL;

} 
