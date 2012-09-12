
//combine histo from several datasets
TH1D* fillHisto(std::vector <int> ds){

  int size = ds.size();

  cout << "input files: "<<size << " "<<histo_string<<endl;
  
  TH1D* first_histo = fillHisto(ds[0]);
  
  //add more histograms
  for (int i = 1; i < size; i++)
    first_histo->Add(fillHisto(ds[i])); 
  
  return first_histo;
}


// Open file and fill histo for ONE dataset
TH1D* fillHisto(int ds){

  TFile* file;
#ifdef H1D
  TH1I* h1_ds; 
#endif
#ifdef H2D
  TH2F* h2_ds; 
  TH1D* h1_ds; 
#endif

  TString dsname = inttoTstr(ds) ;
    
  TString fileName = "root/"+prefix+"_"+dsname+suffix+".root";
  file  = TFile::Open(fileName); 
  cout << "opening file "<<fileName<<endl;

#ifdef H1D
  h1_ds  = (TH1I*)file->Get(histo_string) ; 
#endif
    
#ifdef H2D
  h2_ds = (TH2F*)file->Get(histo_string);     
  h1_ds = h2_ds->ProjectionY("h1_ds", binmin, binmax, "e");
#endif

  h1_ds->Scale( Normalize(ds, lumi, file)); 
      
  return h1_ds;
}

// Open file and fill histo for ONE dataset
void fillData(){

#ifdef ELECTRON
  TFile* file_electronStream  = TFile::Open("root/"+prefix+"_electronStream.root");  
//  TFile* file_electronStream  = TFile::Open("root/I_electronStream.root");  
#ifdef H1D
  h1_electronStream  = (TH1I*)file_electronStream->Get(histo_string);   
#endif
#ifdef H2D
  h2_electronStream = (TH2F*)file_electronStream ->Get(histo_string);   
  h1_electronStream = h2_electronStream->ProjectionY("h1_electronStream", binmin, binmax, "e");
#endif

//add electron stream
  histo_data = (TH1D*)h1_electronStream->Clone("histo_data");
#endif  // endif ELECTRON

#ifdef MUON
  TFile* file_muonStream  = TFile::Open("root/"+prefix+"_muonStream.root");  
//  TFile* file_muonStream  = TFile::Open("root/I_muonStream.root");  

#ifdef H1D
  h1_muonStream  = (TH1I*)file_muonStream->Get(histo_string);   
#endif
#ifdef H2D
  h2_muonStream = (TH2F*)file_muonStream ->Get(histo_string);   
  h1_muonStream = h2_muonStream->ProjectionY("h1_muonStream", binmin, binmax, "e");
#endif

//add muon stream
  histo_data = (TH1D*)h1_muonStream->Clone("histo_data");

//Add if both muon and electron stream!
#ifdef ELECTRON  
  histo_data->Add(h1_electronStream);
#endif

#endif // endif MUON

}

TString inttoTstr ( int integer )
{
	std::string s;
	std::stringstream out;
	out << integer;
	TString Tout(out.str());
	return  Tout;
}

std::string inttostr ( int integer )
{
	std::string s;
	std::stringstream out;
	out << integer;
	return  out.str();
}


void SetStyle(){

#ifdef DATA
  histo_data->SetXTitle(x_string);
  histo_data->SetYTitle(y_string);
  histo_data->SetMarkerStyle(20);
  histo_data->SetMarkerSize(1.2);  
#endif
  
#ifdef MC

#ifdef QCD  
  histo_qcd_total->SetXTitle(x_string);
  histo_qcd_total->SetYTitle(y_string);
  histo_qcd_total->SetFillColor(kWhite);
  histo_qcd_total->SetLineColor(kBlack);
//  histo_qcd_total->SetFillColor(kGray+2);//2D
#endif

#ifdef TOP  
  histo_top->SetXTitle(x_string);
  histo_top->SetYTitle(y_string);
  histo_top->SetFillColor(kGreen+3);
#endif

#ifdef WJETS
  histo_wjets->SetXTitle(x_string);
  histo_wjets->SetYTitle(y_string);
  histo_wjets->SetLineColor(kBlack);
  histo_wjets->SetFillColor(kGray);  //2D
//  histo_wjets->SetLineColor(kBlue+3);  //2D
#endif

#ifdef ZJETS
  histo_zjets->SetXTitle(x_string);
  histo_zjets->SetYTitle(y_string);
  histo_zjets->SetFillColor(kBlue+3);
//  histo_zjets->SetFillColor(kWhite);
//  histo_zjets->SetFillStyle(3004);
//  histo_zjets->SetFillStyle(3354);
//  gStyle->SetHatchesLineWidth(3);
  histo_zjets->SetFillColor(kAzure+1);
#endif

#ifdef DIBOSON
  histo_diboson->SetXTitle(x_string);
  histo_diboson->SetYTitle(y_string);
  histo_diboson->SetFillColor(9);
#endif

#ifdef TTBAR
  histo_ttbar->SetXTitle(x_string);
  histo_ttbar->SetYTitle(y_string);
  histo_ttbar->SetFillColor(kGreen-9);
#endif

#ifdef DY
  histo_drellyan->SetXTitle(x_string);
  histo_drellyan->SetYTitle(y_string);
  histo_drellyan->SetFillColor(kPink+1);
#endif

#ifdef SU4
  double su4_scale = 1.;
  histo_su4->Scale(su4_scale);
  cout << "SU4 x " <<su4_scale<<endl;
  
  histo_su4->SetXTitle(x_string);
  histo_su4->SetYTitle(y_string);
  histo_su4->SetLineWidth(4);
#endif

}

