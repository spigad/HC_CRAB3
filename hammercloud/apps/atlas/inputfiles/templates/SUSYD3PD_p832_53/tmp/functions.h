// from egammaAnalysisUtils/Root/egammaTriggerMatching.cxx
const double m_triggerDrMatchingCut=0.15;

double GetDPhi(double phi1, double phi2) {
  double deltaPhi=fabs(phi1-phi2);
  if (deltaPhi>M_PI) deltaPhi=2*M_PI-deltaPhi;
  return deltaPhi;
}

// getting INITIAL index
int MyAnalysis::getIndex(std::string contname, float pt, float eta, float phi){

  unsigned int n = m_sel->GetSizeByType(contname); //initial objects 
  int index = -1;
  
  for (unsigned int i = 0; i < n; i++){   
  
    float ini_eta = m_sel->GetValByType<float>(contname,"_eta", i);
    float ini_phi = m_sel->GetValByType<float>(contname,"_phi", i);
    float ini_pt  = m_sel->GetValByType<float>(contname,"_pt", i);
    
    if ((ini_eta == eta) &&(ini_phi == phi) &&(ini_pt == pt)){
      if (index < 0) index = i;
      else {
        cout << "ERROR "<< contname << " two matches found for pt "<< pt << ": "<< index << " and "<< i <<endl;
        return -1;
      }
    } 
  }//end loop over initial objects
   
  if (index < 0)  cout << "ERROR "<< contname << " no match found for pt "<< pt << endl;
  return index; 
}

bool  MyAnalysis::PassedTriggerL1(double etaOff, double phiOff, int &EFindex, 
                      unsigned int nEFObject, std::vector<float> *EFetaVector, std::vector<float> *EFphiVector) {
  if (nEFObject==0) {
    //std::cout << "No EF object to be tested" << std::endl;
    return false;
  }
 
  if (EFetaVector==0) {
    std::cout << "ERROR: empty pointer provided for EFeta .... returning false" << std::endl;
    return false;
  }
  if (EFetaVector->size()!=nEFObject) {
    std::cout << "ERROR: mismatch in the size of the EFeta vector: " << EFetaVector->size() << "  --> expected: " <<  nEFObject << std::endl;
    return false;
  }

  if (EFphiVector==0) {
    std::cout << "ERROR: empty pointer provided for EFphi .... returning false" << std::endl;
    return false;
  }
  if (EFphiVector->size()!=nEFObject) {
    std::cout << "ERROR: mismatch in the size of the EFphi vector: " << EFphiVector->size() << "  --> expected: " <<  nEFObject << std::endl;
    return false;
  }
 
  double dRMax=100;
  EFindex=-1;
 
  for (unsigned int j=0;j<nEFObject;j++) {
    double etaEF=EFetaVector->at(j);
    double phiEF=EFphiVector->at(j);
    double deltaR=sqrt(pow(GetDPhi(phiEF,phiOff),2)+pow(etaOff-etaEF,2));   
    if ( deltaR<dRMax ) {
      dRMax=deltaR;
      EFindex=j;
    }
  }
  //std::cout <<  "  minimum deltaR is: " << dRMax << std::endl;
 
  if ( dRMax<=m_triggerDrMatchingCut ) {
    //std::cout << "offline object matched with EFobject: " << EFindex << " passing the trigger selection" << std::endl;
    return true;
  } 
  EFindex=-1;
  return false;
}

double MyAnalysis::getMuonTriggerWeight(int i) { 

  Double_t MyMuonValue[5];

  MyMuonValue[0] = m_sel->GetValByType<float>("MUO","_pt", i);
  MyMuonValue[1] = m_sel->GetValByType<float>("MUO","_eta", i);
  MyMuonValue[2] = m_sel->GetValByType<float>("MUO","_phi", i);
  MyMuonValue[3] = m_sel->GetValByType<float>("MUO","_ptcone20", i);
  MyMuonValue[4] = ((m_sel->GetValByType<int>("MUO","_isCombinedMuon", i))? 1. : 0.);

  Long64_t bin_pass = m_passes->GetBin(MyMuonValue);
  Long64_t bin_trial= m_trials->GetBin(MyMuonValue);
  Double_t content_pass = m_passes->GetBinContent(bin_pass);
  Double_t content_trial = m_trials->GetBinContent(bin_trial);

// cout << " content_pass = "<< content_pass << endl;
// cout << " content_trial = "<< content_trial << endl;
  if(content_trial<0.0000001){
    //cout << "MyAnalysis::GetMuonTriggerWeight : denominator for muon trigger weight is negative!! "<< endl;
    return 0;
  }
  return (content_pass/content_trial);
}

double MyAnalysis::getMuonTriggerWeight(float pt, float eta, float phi, float ptcone20, int isCom) { 

  Double_t MyMuonValue[5];

  MyMuonValue[0] = pt;
  MyMuonValue[1] = eta;
  MyMuonValue[2] = phi;
  MyMuonValue[3] = ptcone20;
  MyMuonValue[4] = ((isCom)? 1. : 0.);

  Long64_t bin_pass = m_passes->GetBin(MyMuonValue);
  Long64_t bin_trial= m_trials->GetBin(MyMuonValue);
  Double_t content_pass = m_passes->GetBinContent(bin_pass);
  Double_t content_trial = m_trials->GetBinContent(bin_trial);

// cout << " content_pass = "<< content_pass << endl;
// cout << " content_trial = "<< content_trial << endl;
  if(content_trial<0.0000001){
    //cout << "MyAnalysis::GetMuonTriggerWeight : denominator for muon trigger weight is negative!! "<< endl;
    return 0;
  }
  return (content_pass/content_trial);
}

bool MyAnalysis::passEM16VH(float eta, float Et, float VH) {
  
  bool pass = true;
  
  if (VH > 1000.) return false;
  if (fabs(eta)<0.4)                             { if (Et < 18000.) return false; } 
  else if ((fabs(eta)>=0.4) && (fabs(eta)<0.8))  { if (Et < 18000.) return false; } 
  else if ((fabs(eta)>=0.8) && (fabs(eta)<1.2))  { if (Et < 17000.) return false; } 
  else if ((fabs(eta)>=1.2) && (fabs(eta)<1.6))  { if (Et < 16000.) return false; } 
  else if ((fabs(eta)>=1.6) && (fabs(eta)<2.0))  { if (Et < 17000.) return false; } 
  else if ((fabs(eta)>=2.0) && (fabs(eta)<2.4))  { if (Et < 18000.) return false; } 
  else if ((fabs(eta)>=2.4) && (fabs(eta)<2.5))  { if (Et < 18000.) return false; } 

  return pass;
} 

bool MyAnalysis::passEM18VH(float eta, float Et, float VH) {
  
  bool pass = true;

  if (VH > 1000.) return false;
  if (fabs(eta)<0.4)                             { if (Et < 20000.) return false; } 
  else if ((fabs(eta)>=0.4) && (fabs(eta)<0.8))  { if (Et < 20000.) return false; } 
  else if ((fabs(eta)>=0.8) && (fabs(eta)<1.2))  { if (Et < 19000.) return false; } 
  else if ((fabs(eta)>=1.2) && (fabs(eta)<1.6))  { if (Et < 18000.) return false; } 
  else if ((fabs(eta)>=1.6) && (fabs(eta)<2.0))  { if (Et < 19000.) return false; } 
  else if ((fabs(eta)>=2.0) && (fabs(eta)<2.4))  { if (Et < 20000.) return false; } 
  else if ((fabs(eta)>=2.4) && (fabs(eta)<2.5))  { if (Et < 20000.) return false; } 

  return pass;
} 

bool MyAnalysis::passEM10VH(float eta, float Et, float VH) {

  bool pass = true;

  if (VH > 1000.) return false;
  if (fabs(eta)<0.4)                             { if (Et < 11000.) return false; }                            
  else if ((fabs(eta)>=0.4) && (fabs(eta)<0.8))  { if (Et < 11000.) return false; } 
  else if ((fabs(eta)>=0.8) && (fabs(eta)<1.2))  { if (Et < 10000.) return false; } 
  else if ((fabs(eta)>=1.2) && (fabs(eta)<1.6))  { if (Et < 10000.) return false; } 
  else if ((fabs(eta)>=1.6) && (fabs(eta)<2.0))  { if (Et < 10000.) return false; } 
  else if ((fabs(eta)>=2.0) && (fabs(eta)<2.4))  { if (Et < 11000.) return false; } 
  else if ((fabs(eta)>=2.4) && (fabs(eta)<2.5))  { if (Et < 11000.) return false; } 

  return pass;
} 

//works for EF_mu6!!! Hardcoded thresholds

float MyAnalysis::MuonHasTriggerMatch_EFmu6(int trig_EF_trigmuonef_n, vector<int> *trig_EF_trigmuonef_track_n, float mu_staco_pt, float mu_staco_eta, float mu_staco_phi, vector<vector<float> > *trig_EF_trigmuonef_track_CB_pt, vector<vector<float> > *trig_EF_trigmuonef_track_CB_eta, vector<vector<float> > *trig_EF_trigmuonef_track_CB_phi, vector<vector<int> > *trig_EF_trigmuonef_track_CB_hasCB){


  // found match for object?
  bool muonHasTriggerMatch = false;
  TLorentzVector onl;
  TLorentzVector ofl;

  // minimal DeltaR found
  float DeltaRMin = 0.15;

  // the trigger thresholds: needed to check if a TE has actually passed the trigger Hypothesis. 
  float trigPtCutsEF_mu6[] = { 5880.,  5810.,  5780.,  5760. };
  float trigEtaBinsEF_mu6[] = {0. , 1.05 , 1.5 , 2. , 9.9 };


  // offline variables used for matching
  float ofl_eta = mu_staco_eta ;
  float ofl_phi = mu_staco_phi ;
  float ofl_pt = mu_staco_pt ;
  ofl.SetPtEtaPhiE(ofl_pt,ofl_eta,ofl_phi,ofl_pt*cosh(ofl_eta));
  
  //cout << "Try match with pt,eta,phi "<<ofl_pt<<" "<<ofl_eta<<" "<<ofl_phi<<endl;

  // loop over all trigger elements and find the best matching one
  for( int trigItr = 0; trigItr != trig_EF_trigmuonef_n; ++trigItr ) {

    //cout << "testing trigger element "<<trigItr<<endl;

    // loop over all tracks associated to the trigger element;
    for( int trackItr = 0; trackItr != trig_EF_trigmuonef_track_n -> at(trigItr); ++trackItr ) {

      // do only use combined tracks
      if( !trig_EF_trigmuonef_track_CB_hasCB -> at(trigItr).at(trackItr) ) continue;

      float onl_eta = trig_EF_trigmuonef_track_CB_eta -> at(trigItr).at(trackItr);
      float onl_phi = trig_EF_trigmuonef_track_CB_phi -> at(trigItr).at(trackItr);
      float onl_pt = trig_EF_trigmuonef_track_CB_pt -> at(trigItr).at(trackItr);
      float th = 1.e12;
      onl.SetPtEtaPhiE(onl_pt,onl_eta,onl_phi,onl_pt*cosh(onl_eta));

      //cout << "  combined track "<<trackItr<< " onl pt,eta,phi "<<onl_pt<<" "<<onl_eta<<" "<<onl_phi<<endl;

      // set trigger threshold
      for( int i = 0; i < 4; ++i ) {
        if( fabs(onl_eta) >= trigEtaBinsEF_mu6[i] && fabs(onl_eta) < trigEtaBinsEF_mu6[i+1] ) th = trigPtCutsEF_mu6[i];
      }

      // check DeltaR
      if( ofl.DeltaR(onl) < DeltaRMin ) {

        DeltaRMin = ofl.DeltaR(onl);

        // check part of trigger hypothesis by hand
        if( onl_pt > th ) {
          muonHasTriggerMatch = true;
          //cout << "  trigger passed, return dR "<<DeltaRMin<<endl;
	  
	  return DeltaRMin;
        }
      }
    }
  }

  return -1.;
}

//works for any trigger based on  trig_EF_trigmuonef_EF_mu_xx

float MyAnalysis::MuonHasTriggerMatch(string trig_name_mu, float DeltaRMin, int trig_EF_trigmuonef_n, vector<int> *trig_EF_trigmuonef_track_n, 
  float mu_staco_pt, float mu_staco_eta, float mu_staco_phi, vector<vector<float> > *trig_EF_trigmuonef_track_CB_pt, 
  vector<vector<float> > *trig_EF_trigmuonef_track_CB_eta, vector<vector<float> > *trig_EF_trigmuonef_track_CB_phi, vector<vector<int> > *trig_EF_trigmuonef_track_CB_hasCB)
{          

  // found match for object?
  bool muonHasTriggerMatch = false;
  TLorentzVector onl;
  TLorentzVector ofl;

  // offline variables used for matching
  float ofl_eta = mu_staco_eta;
  float ofl_phi = mu_staco_phi;
  float ofl_pt  = mu_staco_pt;
  ofl.SetPtEtaPhiE(ofl_pt,ofl_eta,ofl_phi,ofl_pt);
  DeltaRMin = 100;
  
  // loop over all trigger elements and find the best matching one
  int triggered = 0;
  string trig_name_test = "trig_EF_" + trig_name_mu;
  
  for( int trigItr = 0; trigItr != trig_EF_trigmuonef_n; ++trigItr ) {
 
    //require matching to trigger chain
    triggered = m_sel->GetRawVector< std::vector<int> > (trig_name_test.c_str()).at(trigItr);
 
    if( !(triggered) ) continue;
 
    // loop over all tracks associated to the trigger element;
    for( int trackItr = 0; trackItr != trig_EF_trigmuonef_track_n -> at(trigItr); ++trackItr ) {


      // do only use combined tracks
      if( !trig_EF_trigmuonef_track_CB_hasCB -> at(trigItr).at(trackItr) ) continue;

      float onl_eta = trig_EF_trigmuonef_track_CB_eta -> at(trigItr).at(trackItr);
      float onl_phi = trig_EF_trigmuonef_track_CB_phi -> at(trigItr).at(trackItr);
      float onl_pt = trig_EF_trigmuonef_track_CB_pt -> at(trigItr).at(trackItr);      
      onl.SetPtEtaPhiE(onl_pt,onl_eta,onl_phi,onl_pt);

  
      if( !(triggered) ) continue;
      // check DeltaR
      if( ofl.DeltaR(onl) < DeltaRMin ) {

        muonHasTriggerMatch = true;
        DeltaRMin = ofl.DeltaR(onl);

      }
    }
  }

//  return muonHasTriggerMatch;
  if (muonHasTriggerMatch)
    return DeltaRMin;
  else
    return -1.;
}

// Uses EFCB_index and dR variables

float MyAnalysis::getMuonTriggerMatch(int muo_off_index, string trig_name_mu, float DeltaRMin) { 

  // trigger matching

  string trig_name_test = "trig_EF_" + trig_name_mu;
  //cout << "testing "<< trig_name_test<<endl;
  
  int mun  = m_sel->GetFinValByType<int>("MUO","_EFCB_index", muo_off_index);
  float deltaR = m_sel->GetFinValByType<float>("MUO","_EFCB_dr", muo_off_index);

  bool matched = false;
  int triggered = 0;
  
  if (mun>=0) {
    
    triggered = m_sel->GetRawVector< std::vector<int> > (trig_name_test.c_str()).at(mun);    
     
    if (triggered)
      if (fabs(deltaR) < DeltaRMin) matched = true;
  }     
  
//  return  (triggered && matched) ;
  
    if (triggered)
      return  (fabs(deltaR)) ;
    else 
      return -1;  
}

// Uses EFCB_index and dR variables

float MyAnalysis::getElectronTriggerMatch(int ele_off_index, string trig_name_ele, float DeltaRMin) { 

  // trigger matching

  string trig_name_test = trig_name_ele;
  //cout << "testing "<< trig_name_test<<endl;
  
  int mun  = m_sel->GetFinValByType<int>("ELE","_EF_index", ele_off_index);
  float deltaR = m_sel->GetFinValByType<float>("ELE","_EF_dr", ele_off_index);

  bool matched = false;
  int triggered = 0;  
  
  if (mun>=0) {
    
    triggered = m_sel->GetRawVector< std::vector<int> > (trig_name_test.c_str()).at(mun);
    
    if (triggered)
      if (fabs(deltaR) < DeltaRMin) matched = true;
  }     
  
//  return  (triggered && matched) ;
    if (triggered)
      return  (fabs(deltaR)) ;
    else 
      return -1;  
}

bool MyAnalysis::MuonHasL1L2TriggerMatch(float Pt, float DeltaRMin, int trig_onl_mu_n, float mu_staco_pt, float mu_staco_eta, 
float mu_staco_phi, vector<float> *trig_onl_mu_pt, vector<float> *trig_onl_mu_eta, vector<float> *trig_onl_mu_phi)
{          

  // found match for object?
  bool muonHasTriggerMatch = false;
  TLorentzVector onl;
  TLorentzVector ofl;
  
  // offline variables used for matching
  float ofl_eta = mu_staco_eta;
  float ofl_phi = mu_staco_phi;
  float ofl_pt = mu_staco_pt;
  ofl.SetPtEtaPhiE(ofl_pt,ofl_eta,ofl_phi,ofl_pt);

  // loop over all trigger elements and find the best matching one
  for( int trigItr = 0; trigItr != trig_onl_mu_n; ++trigItr ) {

      float onl_eta = trig_onl_mu_eta -> at(trigItr);
      float onl_phi = trig_onl_mu_phi -> at(trigItr);
      float onl_pt  = fabs(trig_onl_mu_pt -> at(trigItr));
      if (onl_pt <= 0.) continue; 

      onl.SetPtEtaPhiE(onl_pt,onl_eta,onl_phi,onl_pt);
      
      // check DeltaR
      if( ofl.DeltaR(onl) < DeltaRMin ) {

        DeltaRMin = ofl.DeltaR(onl);

        // check part of trigger hypothesis by hand
        if( onl_pt > Pt ) {
          muonHasTriggerMatch = true;
          
        }
      }
    }

  return muonHasTriggerMatch;

}



std::string MyAnalysis::getTriggerElectron(int run){

//period A-D
  if (run >= 152166 && run <= 159224) {
    return "EF_e10_loose";
  }

//period E
  if (run >= 160387 && run <= 161948) {
    return "EF_g17_etcut";
  }

//period F
  if (run >= 162347 && run <= 162882) {
    return "EF_e15_medium";
  }

//period G-H
  if (run >= 165591 && run <= 166964) {
    return "EF_e15_medium";
  }
  
//period I
  if (run >= 167575 && run <= 167844) {
    return "EF_e15_medium";
   
  }

//period 2011
  if (run > 167844 && run <= 186755) {

    return "EF_e20_medium";
   
  }

  if (run > 186755 && run <= 187763) {

    return "EF_e22_medium";
   
  }

  if (run > 187763 ) {

    return "EF_e22vh_medium1";
   
  }
  
  cout << "ERROR no defined trigger for run "<< run <<endl;
  return "error, no defined trigger";
}

std::string MyAnalysis::getTriggerMuon(int run){

//period A-D
  if (run >= 152166 && run <= 159224) {
    return "L1_MU6";
  }

//period E
  if (run >= 160387 && run <= 161948) {
    return "EF_mu10_MSonly";
  }

//period F
  if (run >= 162347 && run <= 162882) {
    return "EF_mu10_MSonly";
  }

//period G-H
  if (run >= 165591 && run <= 166964) {
    return "EF_mu13";
  }
  
//period I
  if (run >= 167575 && run <= 167844) {

    return "EF_mu13_tight";
   
  }

//period 2011
  if (run > 167844 && run <= 186493) {

    return "EF_mu18";
   
  }

  if (run > 186493 ) {

    return "EF_mu18_medium";
   
  }
  
  cout << "ERROR no defined trigger for run "<< run <<endl;
  return "error, no defined trigger";
}


double MyAnalysis::getPileUpWeightElectron(int nPV)
{
/* 2010 data
  if (nPV==0) return 0.;
  if (nPV==1) return 1.6336;
  if (nPV==2) return 1.11107;
  if (nPV==3) return 0.834308;
  if (nPV==4) return 0.676119;
  if (nPV==5) return 0.647882;
  if (nPV==6) return 0.521563;
  if (nPV==7) return 0.598444;
  if (nPV>=8) return 0.346462; 
*/
  
  if (nPV==0) return 0.;
  if (nPV==1) return 0.;
  if (nPV==2) return 0.00218437;
  if (nPV==3) return 0.258861  ;
  if (nPV==4) return 3.1242    ;
  if (nPV==5) return 4.71067   ;
  if (nPV==6) return 3.16552   ;
  if (nPV==7) return 1.37379   ;
  if (nPV==8) return 0.13261   ; 
  if (nPV>=9) return 0.; 
  cout << "Error in assigning weight for nGoodPV "<<nPV<<endl;
  return -1.;
}


double MyAnalysis::getPileUpWeightMuon(int nPV)
{
 
  if (nPV==0) return 0.;
  if (nPV==1) return 0.;
  if (nPV==2) return 0.;
  if (nPV==2) return 0.00218467;
  if (nPV==3) return 0.258897  ;
  if (nPV==4) return 3.12463   ;
  if (nPV==5) return 4.71132   ;
  if (nPV==6) return 3.16595   ;
  if (nPV==7) return 1.37384   ;
  if (nPV==8) return 0.131571  ; 
  if (nPV>=9) return 0.;

  cout << "Error in assigning weight for nGoodPV "<<nPV<<endl;
  return -1.;
}

// not the quickest sorting algorithm...
void MyAnalysis::sort(float *lep_pt, float *lep_px, float *lep_py, float *lep_pz, float *lep_e, float *lep_isMuon, float *lep_charge, unsigned int n_leptons)
{
  float tmp_pt, tmp_px, tmp_py, tmp_pz, tmp_e, tmp_isMuon, tmp_charge;
  
  for(unsigned int i=0;i<n_leptons;i++){
    for(unsigned int j=i+1;j<n_leptons;j++){
      if(lep_pt[i]<lep_pt[j]){
        
	//swap
	tmp_pt = lep_pt[i];
        tmp_px = lep_px[i];
        tmp_py = lep_py[i];
        tmp_pz = lep_pz[i];
        tmp_e  = lep_e[i];
	tmp_isMuon = lep_isMuon[i];
	tmp_charge = lep_charge[i];
	
        lep_pt[i] = lep_pt[j];
        lep_px[i] = lep_px[j];
        lep_py[i] = lep_py[j];
        lep_pz[i] = lep_pz[j];
        lep_e[i]  = lep_e[j];
	lep_isMuon[i] = lep_isMuon[j];
	lep_charge[i] = lep_charge[j];
	
        lep_pt[j] = tmp_pt;
        lep_px[j] = tmp_px;
        lep_py[j] = tmp_py;
        lep_pz[j] = tmp_pz;
        lep_e[j]  = tmp_e;
	lep_isMuon[j] = tmp_isMuon;
	lep_charge[j] = tmp_charge;
      }
    }
  }   
}

double MyAnalysis::CalcTranSphericity(double sumpx2,double sumpy2,double sumpxpy){
   double marray[4];
   for(int i=0;i<4;i++){
     marray[i]=0;
   }
   marray[0]=sumpx2;
   marray[1]=sumpxpy;
   marray[2]=sumpxpy;
   marray[3]=sumpy2;
      
   // use root matrix to find eigenvalues...
   TMatrixDSym matrix(2);  
   matrix.SetMatrixArray(marray);
   
   TMatrixDSymEigen eigen(matrix); 
   TVectorD E = eigen.GetEigenValues();   
  
   // from the babar sphericity code...
   double lambda1 = 0;
   double lambda2 = 0;
   
   if(E[0] < E[1]){
     lambda1 = E[0];
     lambda2 = E[1];
   }else{
     lambda1 = E[1];
     lambda2 = E[0];
   }
 
   double ST = 0;
   ST = 2*lambda1/( lambda1 + lambda2);
   return ST;
 }

int MyAnalysis::doGenCutDrellYan(Long64_t entry) {

 (void)entry;
 
 //int mc_n = m_sel->GetScalarVal<int>("mc_n");
 std::vector<int> mc_pdgId = m_sel->GetRawVector< std::vector<int> >("mc_pdgId");
 std::vector<float> mc_m = m_sel->GetRawVector< std::vector<float> >("mc_m");
 float mll = mc_m[7];  // The 'Z' mass

 if ((mll > 15000.) && (mll < 40000.)) return 1;
 else return 0;

}

int MyAnalysis::getProcess(Long64_t entry) {

 (void)entry; 
  
  int mc_n = m_sel->GetScalarVal<int>("mc_n");
  int sparticletyp=9;
  
  if (mc_n){
  std::vector<int> mc_pdgId = m_sel->GetRawVector< std::vector<int> >("mc_pdgId");
  std::vector<int> mc_barcode = m_sel->GetRawVector< std::vector<int> >("mc_barcode");
  std::vector < std::vector<int> > mc_parents = m_sel->GetRawVector< std::vector< std::vector<int> > >("mc_parents");
  std::vector < std::vector<int> > mc_children = m_sel->GetRawVector< std::vector< std::vector<int> > >("mc_children");

  int first=0;
  int firstsp=0;//first parent
  int secondsp=0;//second parent
  int ngluino=0;
  int nsquark=0;
  int nantisquark=0;
  int nlsp=0;
  int nchi01=0;
  int nchi02=0;
  int nchi03=0;
  int nchi04=0;
  int nchip1=0;
  int nchip2=0;
  int nchin1=0;
  int nchin2=0;
  int nsb1=0;
  int nst1=0;
  int nsb2=0;
  int nst2=0;
  int nother=0;
  //int other=0;
  
  for(int par=0; par<mc_n;par++){
    if(fabs(mc_pdgId.at(par))>1000000) {
      //Loop to find the parents
      for(int c=0; c<mc_n;c++){
    	if(mc_parents.at(par).size()>0 && mc_parents.at(par).at(0)==mc_barcode.at(c)) {
    	  if(fabs(mc_pdgId.at(c))<1000000) {
    	    if(first==0) {
    	      firstsp=par;
    	      first=1;
    	    }
    	    else secondsp=par;
    	  }
    	}
      }
    }
  }
  //The two initial particles have been found. Now check that neither of them it is a propagator (meaning that there is only a child and has different pdgId)
  if(mc_children.at(firstsp).size()==1){ 
    for(int par=0; par<mc_n;par++){
      if(mc_barcode.at(par)==mc_children.at(firstsp).at(0) && mc_pdgId.at(par)!=mc_pdgId.at(firstsp)){
    	firstsp=par; //change the firstsp (the previous was a propagator)
    	break;
      }
    }
  }
  if(mc_children.at(secondsp).size()==1){ 
    for(int par=0; par<mc_n;par++){
      if(mc_barcode.at(par)==mc_children.at(secondsp).at(0) && mc_pdgId.at(par)!=mc_pdgId.at(secondsp)){
    	secondsp=par; //change the firstsp (the previous was a propagator)
    	break;
      }
    }
  }

  //Classification of the event follows (gg, sq...):
  if(fabs(mc_pdgId.at(firstsp))==1000021) 
    ngluino++;
  else if(fabs(mc_pdgId.at(firstsp))<=1000004 || (fabs(mc_pdgId.at(firstsp))>2000000 && fabs(mc_pdgId.at(firstsp))<=2000004)) {
    if(mc_pdgId.at(firstsp)>0) nsquark++;
    else nantisquark++;
  }
  else if(fabs(mc_pdgId.at(firstsp))==1000005)  nsb1++;
  else if(fabs(mc_pdgId.at(firstsp))==1000006)  nst1++;
  else if(fabs(mc_pdgId.at(firstsp))==2000005)  nsb2++;
  else if(fabs(mc_pdgId.at(firstsp))==2000006)  nst2++;
  else if(fabs(mc_pdgId.at(firstsp))==1000022)  nlsp++;
  else if(fabs(mc_pdgId.at(firstsp))==1000023) nchi02++;
  else if(fabs(mc_pdgId.at(firstsp))==1000025) nchi03++;
  else if(fabs(mc_pdgId.at(firstsp))==1000035) nchi04++;
  else if(mc_pdgId.at(firstsp)==1000024)       nchip1++;
  else if(mc_pdgId.at(firstsp)==1000037)       nchip2++;
  else if(mc_pdgId.at(firstsp)==-1000024)      nchin1++;
  else if(mc_pdgId.at(firstsp)==-1000037)      nchin2++;

  else
    nother++;

  
  if(fabs(mc_pdgId.at(secondsp))==1000021) ngluino++;
  else if(fabs(mc_pdgId.at(secondsp))<=1000004 || (fabs(mc_pdgId.at(secondsp))>2000000 && fabs(mc_pdgId.at(secondsp))<=2000004)) {
    if(mc_pdgId.at(secondsp)>0) nsquark++;
    else nantisquark++;
  }
  else if(fabs(mc_pdgId.at(secondsp))==1000005)    nsb1++;
  else if(fabs(mc_pdgId.at(secondsp))==1000006)    nst1++;
  else if(fabs(mc_pdgId.at(secondsp))==2000005)    nsb2++;
  else if(fabs(mc_pdgId.at(secondsp))==2000006)    nst2++;
  else if(fabs(mc_pdgId.at(secondsp))==1000022)    nlsp++;
  else if(fabs(mc_pdgId.at(secondsp))==1000023)    nchi02++;
  else if(fabs(mc_pdgId.at(secondsp))==1000025) nchi03++;
  else if(fabs(mc_pdgId.at(secondsp))==1000035) nchi04++;
  else if(mc_pdgId.at(secondsp)==1000024)       nchip1++;
  else if(mc_pdgId.at(secondsp)==1000037)       nchip2++;
  else if(mc_pdgId.at(secondsp)==-1000024)      nchin1++;
  else if(mc_pdgId.at(secondsp)==-1000037)      nchin2++;
  else
    nother++;

  if(ngluino==2) sparticletyp=2;                                     // 2 gluinos
  else if(ngluino==1 && ((nantisquark+nsquark)==1 )) sparticletyp=1; // 1 gluino + 1 squark or antisquark
  else if(nsquark==2 || nantisquark==2) sparticletyp=3; 	     // 2 squark or 2 antisquark
  else if(nsquark==1 && nantisquark==1) sparticletyp=4; 	     // 1 squark + 1 antisquark
  else if(nsb1==2) sparticletyp=51;				     // 2 sbottom1
  else if(nsb2==2) sparticletyp=52;				     // 2 sbottom2
  else if(nst1==2) sparticletyp=61;				     // 2 stop1
  else if(nst2==2) sparticletyp=62;				     // 2 stop2
  else if(ngluino==1 && nchi01) sparticletyp=71;		     // 1 gluino + chi01	     
  else if(ngluino==1 && nchi02) sparticletyp=72;		     // 1 gluino + chi02  
  else if(ngluino==1 && nchi03) sparticletyp=73;		     // 1 gluino + chi03  
  else if(ngluino==1 && nchi04) sparticletyp=74;		     // 1 gluino + chi04  
  else if(ngluino==1 && nchip1) sparticletyp=75;		     // 1 gluino + chi+1  
  else if(ngluino==1 && nchip2) sparticletyp=76;		     // 1 gluino + chi+2  
  else if(ngluino==1 && nchin1) sparticletyp=77;		     // 1 gluino + chi-1  
  else if(ngluino==1 && nchin2) sparticletyp=78;		     // 1 gluino + chi-2    
  else if( (nsquark+nantisquark)==1 && nchi01 ) sparticletyp=81;     // 1 squark + 1 antisquark + chi01
  else if( (nsquark+nantisquark)==1 && nchi02 ) sparticletyp=82;     // 1 squark + 1 antisquark + chi02
  else if( (nsquark+nantisquark)==1 && nchi03 ) sparticletyp=83;     // 1 squark + 1 antisquark + chi03
  else if( (nsquark+nantisquark)==1 && nchi04 ) sparticletyp=84;     // 1 squark + 1 antisquark + chi04
  else if( (nsquark+nantisquark)==1 && nchip1 ) sparticletyp=85;     // 1 squark + 1 antisquark + chi+1
  else if( (nsquark+nantisquark)==1 && nchip2 ) sparticletyp=86;     // 1 squark + 1 antisquark + chi+2
  else if( (nsquark+nantisquark)==1 && nchin1 ) sparticletyp=87;     // 1 squark + 1 antisquark + chi-1
  else if( (nsquark+nantisquark)==1 && nchin2 ) sparticletyp=88;     // 1 squark + 1 antisquark + chi-2
  } //end if mc_n
  else sparticletyp=-1;
  
  //if (sparticletyp==9) cout << "other: " << mc_pdgId.at(firstsp) << " and " << mc_pdgId.at(secondsp) << endl;
  return sparticletyp;  
}

void MyAnalysis::fill_histo(double mc_event_weight, unsigned int nbin, float MET){

  h_met->Fill(nbin, MET/1000.,mc_event_weight);

  cutflow_histo->Fill(nbin, mc_event_weight);
  h_cutflow_susy->Fill(nbin, susyprocess, mc_event_weight);
  h_nGoodPV    ->Fill(nbin, nGoodPV,mc_event_weight);

  return;
} 

//for trigger study
void MyAnalysis::fill_histo(double mc_event_weight, unsigned int nbin){

  if (n_ele >0) {
    h_el_trg_eta    ->Fill(nbin, trg_eta,	 mc_event_weight);
    h_el_trg_pt     ->Fill(nbin, trg_pt/1000., mc_event_weight);
    h_el_trg_phi    ->Fill(nbin, trg_phi,	 mc_event_weight);   
    h_el_trg_eta_phi->Fill(nbin, trg_eta, trg_phi, mc_event_weight);
    h_el_trg_pt_eta ->Fill(nbin, trg_pt/1000., trg_eta, mc_event_weight);

  }
  if (n_muo >0) {
    h_mu_trg_eta    ->Fill(nbin, trg_eta,	mc_event_weight);
    h_mu_trg_pt     ->Fill(nbin, trg_pt/1000., mc_event_weight);
    h_mu_trg_phi    ->Fill(nbin, trg_phi,	  mc_event_weight);
    h_mu_trg_eta_phi->Fill(nbin, trg_eta, trg_phi, mc_event_weight);
    h_mu_trg_pt_eta ->Fill(nbin, trg_pt/1000., trg_eta, mc_event_weight);
    
    if (fabs(trg_eta)<1.05){
      h_mu_trg_eta_barrel    ->Fill(nbin, trg_eta,	mc_event_weight);
      h_mu_trg_pt_barrel     ->Fill(nbin, trg_pt/1000., mc_event_weight);
      h_mu_trg_phi_barrel    ->Fill(nbin, trg_phi,	  mc_event_weight);
    }else{
      h_mu_trg_eta_endcap    ->Fill(nbin, trg_eta,	mc_event_weight);
      h_mu_trg_pt_endcap     ->Fill(nbin, trg_pt/1000., mc_event_weight);
      h_mu_trg_phi_endcap    ->Fill(nbin, trg_phi,	  mc_event_weight);
    }
  }

  return;
}
  
void MyAnalysis::fill_histo(double mc_event_weight, unsigned int nbin, float MET, float inv_mass, float m_eff, float m_t, float htmiss, int isOS){

  cutflow_histo->Fill(nbin, mc_event_weight);
  h_cutflow_susy->Fill(nbin, susyprocess, mc_event_weight);
 
  //met
  h_met->Fill(nbin, MET/1000.,mc_event_weight);
  
  if (isOS==1.){
    h_invmass_OS ->Fill(nbin, inv_mass/1000.,mc_event_weight);
    h_met_OS ->Fill(nbin, MET/1000.,mc_event_weight);
    h_htmiss_OS ->Fill(nbin, htmiss/1000.,mc_event_weight);
  }else if (isOS == -1.){
    h_invmass_SS ->Fill(nbin, inv_mass/1000.,mc_event_weight);
    h_met_SS ->Fill(nbin, MET/1000.,mc_event_weight);
    h_htmiss_SS ->Fill(nbin, htmiss/1000.,mc_event_weight);
  }  
  
  h_invmass    ->Fill(nbin, inv_mass/1000.,mc_event_weight);
  h_meff       ->Fill(nbin, m_eff/1000.,mc_event_weight);
  h_mt         ->Fill(nbin, m_t/1000.,mc_event_weight);
  h_nGoodPV    ->Fill(nbin, nGoodPV,mc_event_weight);

  //electrons	
 
  h_e_nb->Fill(bin,  n_ele, mc_event_weight);
  if (n_ele >0) {
    for (unsigned int i = 0; i < n_ele; i++){
      h_e_eta      ->Fill(nbin, ele_eta[i],             mc_event_weight);
      h_e_pt       ->Fill(nbin, ele_pt[i]/1000.,        mc_event_weight);
      h_e_phi      ->Fill(nbin, ele_phi[i],             mc_event_weight);
      h_e_ptcone20 ->Fill(nbin, ele_ptcone20[i]/1000. , mc_event_weight);
      h_e_charge   ->Fill(nbin, ele_charge[i],          mc_event_weight);
    }
    //leading electron
    h_el_eta    ->Fill(nbin, ele_eta[0],	  mc_event_weight);
    h_el_pt     ->Fill(nbin, ele_pt[0]/1000., mc_event_weight);
    h_el_phi    ->Fill(nbin, ele_phi[0],	  mc_event_weight);
    
    //2nd leading electron
    if (n_ele >1) {
      h_e2l_eta      ->Fill(nbin, ele_eta[1],    mc_event_weight);
      h_e2l_pt	     ->Fill(nbin, ele_pt[1]/1000., mc_event_weight);
      h_e2l_phi      ->Fill(nbin, ele_phi[1],   mc_event_weight);
    }//end if at least 2 electrons
         
  }//end if electrons >0
  
  //muons  
  h_mu_nb->Fill(bin,  n_muo, mc_event_weight);
  if (n_muo >0) {
    for (unsigned int i = 0; i < n_muo; i++){
      h_mu_eta      ->Fill(nbin, muo_eta[i],             mc_event_weight);
      h_mu_pt       ->Fill(nbin, muo_pt[i]/1000.,        mc_event_weight);
      h_mu_phi      ->Fill(nbin, muo_phi[i],             mc_event_weight);
      h_mu_ptcone20 ->Fill(nbin, muo_ptcone20[i]/1000. , mc_event_weight);
      h_mu_charge   ->Fill(nbin, muo_charge[i],          mc_event_weight);
    }
    
    //leading muon
    h_mul_eta	 ->Fill(nbin, muo_eta[0],      mc_event_weight);
    h_mul_pt	 ->Fill(nbin, muo_pt[0]/1000., mc_event_weight);
    h_mul_phi	 ->Fill(nbin, muo_phi[0],      mc_event_weight);
    
    //2nd leading muon
    if (n_muo >1) {
      h_mu2l_eta      ->Fill(nbin, muo_eta[1],    mc_event_weight);
      h_mu2l_pt       ->Fill(nbin, muo_pt[1]/1000., mc_event_weight);
      h_mu2l_phi      ->Fill(nbin, muo_phi[1],   mc_event_weight);
    }//end if at least 2 muons
        
  }//end if muons >0
  

  //jets  
  h_jet_nb->Fill(bin,  n_jet, mc_event_weight);
  if (n_jet >0) {
    for (unsigned int i = 0; i < n_jet; i++){
      
      h_jet_eta      ->Fill(nbin, jet_eta[i],  	   mc_event_weight);
      h_jet_pt       ->Fill(nbin, jet_pt[i]/1000., mc_event_weight);
      h_jet_phi      ->Fill(nbin, jet_phi[i],  	   mc_event_weight);
    }//end loop over jets
    
    //leading jet
    h_jetl_eta      ->Fill(nbin, jet_eta[0],	  mc_event_weight);
    h_jetl_pt	    ->Fill(nbin, jet_pt[0]/1000., mc_event_weight);
    h_jetl_phi      ->Fill(nbin, jet_phi[0],	  mc_event_weight);
    
    //2nd leading jet
    if (n_jet >1) {
      h_jet2l_eta      ->Fill(nbin, jet_eta[1],    mc_event_weight);
      h_jet2l_pt       ->Fill(nbin, jet_pt[1]/1000., mc_event_weight);
      h_jet2l_phi      ->Fill(nbin, jet_phi[1],   mc_event_weight);
    }//end if at least 2 jets
  }//end if jets >0
  
  return;  
}

MyAnalysis::MyAnalysis(D3PDSelector * inst)
{
  //Constructor. The constructor is called from SlaveBegin in the D3PDSelector
  
  m_sel = inst; //MANDATORY. The D3PDSelector Object must be known to the Analysis Class.
 
  //The selector class needs to know which are the prefixes for the particles objects.
  m_sel->SetElectronContainerPrefix("el");
  m_sel->SetMuonContainerPrefix("mu_staco");
  m_sel->SetJetContainerPrefix("jet_AntiKt4TopoNewEM");
  //m_sel->SetPhotonContainerPrefix("ph");
  
  // Let's create a histogram and register it with the D3PD Class
  some_histo = new TH1F("some_histo","some_histo",50,0,100);
  
  int ncut = 60;
    
  cutflow_histo  = new TH1D("cutflow_histo","cutflow_histo",ncut+1,0,ncut);    
  runNumber_histo = new TH1D("runNumber_histo","runNumber_histo",200001,100000,300000);   
  h_cutflow_susy = new TH2D("h_cutflow_susy","h_cutflow_susy",ncut+1, 0, ncut,  100, 0,  99);
  
  h_trg1        = new TH1F("h_trg1",        "h_trg1",             5,-2.,2.);
  h_trg1_dR     = new TH1F("h_trg1_dR",     "h_trg1_dR",      10000,-2.,5.);
  h_trg1_d3pd   = new TH1F("h_trg1_d3pd",   "h_trg1_d3pd",        5,-2.,2.);
  h_trg1_d3pd_dR= new TH1F("h_trg1_d3pd_dR","h_trg1_d3pd_dR", 10000,-2.,5.);
  h_trg1_deltaR = new TH1F("h_trg1_deltaR", "h_trg1_deltaR",  20000,-1.,1.);
  h_trg2        = new TH1F("h_trg2",        "h_trg2",             5,-2.,2.);
  h_trg2_dR     = new TH1F("h_trg2_dR",     "h_trg2_dR",      10000,-2.,5.);
  h_trg2_d3pd   = new TH1F("h_trg2_d3pd",   "h_trg2_d3pd",        5,-2.,2.);
  h_trg2_d3pd_dR= new TH1F("h_trg2_d3pd_dR","h_trg2_d3pd_dR", 10000,-2.,5.);
  h_trg2_deltaR = new TH1F("h_trg2_deltaR", "h_trg2_deltaR",  20000,-1.,1.);
  
  h_e_nb       = new TH2F("h_e_nb",       "h_e_nb",       ncut+1, 0, ncut,  10,     0,    9);
  h_e_eta      = new TH2F("h_e_eta",      "h_e_eta",      ncut+1, 0, ncut, 100,    -5,    5);
  h_e_phi      = new TH2F("h_e_phi",      "h_e_phi",      ncut+1, 0, ncut,  40, -3.14, 3.14);
  h_e_pt       = new TH2F("h_e_pt",       "h_e_pt",       ncut+1, 0, ncut, 600,     0, 600.);
  h_e_ptcone20 = new TH2F("h_e_ptcone20", "h_e_ptcone20", ncut+1, 0, ncut, 200,     0, 200.);
  h_e_charge   = new TH2F("h_e_charge",   "h_e_charge",   ncut+1, 0, ncut,   3,   -1.,   1.);

  h_el_eta     = new TH2F("h_el_eta", "h_el_eta",   ncut+1, 0, ncut, 100,    -5,    5);
  h_el_phi     = new TH2F("h_el_phi", "h_el_phi",   ncut+1, 0, ncut,  40, -3.14, 3.14);
  h_el_pt      = new TH2F("h_el_pt",  "h_el_pt",    ncut+1, 0, ncut, 600,     0, 600.);
    
  h_e2l_eta    = new TH2F("h_e2l_eta","h_e2l_eta",  ncut+1, 0, ncut, 100,    -5,    5);
  h_e2l_phi    = new TH2F("h_e2l_phi","h_e2l_phi",  ncut+1, 0, ncut,  40, -3.14, 3.14);
  h_e2l_pt     = new TH2F("h_e2l_pt", "h_e2l_pt",   ncut+1, 0, ncut, 600,     0, 600.);

  h_el_trg_eta  = new TH2F("h_el_trg_eta", "h_el_trg_eta",   ncut+1, 0, ncut, 100,    -5,    5);
  h_el_trg_phi  = new TH2F("h_el_trg_phi", "h_el_trg_phi",   ncut+1, 0, ncut,  40, -3.14, 3.14);
  h_el_trg_pt   = new TH2F("h_el_trg_pt",  "h_el_trg_pt",    ncut+1, 0, ncut, 600,     0, 600.);

  h_mu_nb       = new TH2F("h_mu_nb",     "h_mu_nb",      ncut+1, 0, ncut,  10,     0,    9);
  h_mu_eta      = new TH2F("h_mu_eta",    "h_mu_eta",     ncut+1, 0, ncut, 100,    -5,    5);
  h_mu_phi      = new TH2F("h_mu_phi",    "h_mu_phi",     ncut+1, 0, ncut,  40, -3.14, 3.14);
  h_mu_pt       = new TH2F("h_mu_pt",     "h_mu_pt",      ncut+1, 0, ncut, 120,     0,  600);
  h_mu_ptcone20 = new TH2F("h_mu_ptcone20","h_mu_ptcone20",ncut+1,0, ncut, 120,     0,  600);
  h_mu_charge   = new TH2F("h_mu_charge", "h_mu_charge",  ncut+1, 0, ncut,   3,   -1.,   1.);

  h_mul_eta     = new TH2F("h_mul_eta", "h_mul_eta",	ncut+1, 0, ncut, 100,	 -5,	5);
  h_mul_phi     = new TH2F("h_mul_phi", "h_mul_phi",	ncut+1, 0, ncut,  40, -3.14, 3.14);
  h_mul_pt      = new TH2F("h_mul_pt",  "h_mul_pt",	ncut+1, 0, ncut, 600,	  0, 600.);
    
  h_mu2l_eta    = new TH2F("h_mu2l_eta","h_mu2l_eta",  ncut+1, 0, ncut, 100,	 -5,	5);
  h_mu2l_phi    = new TH2F("h_mu2l_phi","h_mu2l_phi",  ncut+1, 0, ncut,  40, -3.14, 3.14);
  h_mu2l_pt     = new TH2F("h_mu2l_pt", "h_mu2l_pt",	ncut+1, 0, ncut, 600,	  0, 600.);

  h_mu_trg_eta  = new TH2F("h_mu_trg_eta", "h_mu_trg_eta", ncut+1, 0, ncut, 100,    -5,    5);
  h_mu_trg_phi  = new TH2F("h_mu_trg_phi", "h_mu_trg_phi", ncut+1, 0, ncut,  40, -3.14, 3.14);
  h_mu_trg_pt   = new TH2F("h_mu_trg_pt",  "h_mu_trg_pt",  ncut+1, 0, ncut, 600,     0, 600.);

  h_el_trg_eta_phi = new TH3F("h_el_trg_eta_phi", "h_el_trg_eta_phi", ncut+1, 0, ncut, 100,    -5,    5,  40, -3.14, 3.14);
  h_mu_trg_eta_phi = new TH3F("h_mu_trg_eta_phi", "h_mu_trg_eta_phi", ncut+1, 0, ncut, 100,    -5,    5,  40, -3.14, 3.14);
  h_el_trg_pt_eta  = new TH3F("h_el_trg_pt_eta", "h_el_trg_pt_eta", ncut+1, 0, ncut, 600,     0, 600., 100,    -5,    5);
  h_mu_trg_pt_eta  = new TH3F("h_mu_trg_pt_eta", "h_mu_trg_pt_eta", ncut+1, 0, ncut, 600,     0, 600., 100,    -5,    5);

  h_mu_trg_eta_barrel  = new TH2F("h_mu_trg_eta_barrel", "h_mu_trg_eta_barrel", ncut+1, 0, ncut, 100,    -5,    5);
  h_mu_trg_phi_barrel  = new TH2F("h_mu_trg_phi_barrel", "h_mu_trg_phi_barrel", ncut+1, 0, ncut,  40, -3.14, 3.14);
  h_mu_trg_pt_barrel   = new TH2F("h_mu_trg_pt_barrel",  "h_mu_trg_pt_barrel",  ncut+1, 0, ncut, 600,     0, 600.);

  h_mu_trg_eta_endcap  = new TH2F("h_mu_trg_eta_endcap", "h_mu_trg_eta_endcap", ncut+1, 0, ncut, 100,    -5,    5);
  h_mu_trg_phi_endcap  = new TH2F("h_mu_trg_phi_endcap", "h_mu_trg_phi_endcap", ncut+1, 0, ncut,  40, -3.14, 3.14);
  h_mu_trg_pt_endcap   = new TH2F("h_mu_trg_pt_endcap",  "h_mu_trg_pt_endcap",  ncut+1, 0, ncut, 600,     0, 600.);


  h_jet_nb      = new TH2F("h_jet_nb",   "h_jet_nb",     ncut+1, 0, ncut,  10,     0,    9);
  h_jet_eta     = new TH2F("h_jet_eta",  "h_jet_eta",    ncut+1, 0, ncut, 100,    -5,    5);
  h_jet_phi     = new TH2F("h_jet_phi",  "h_jet_phi",    ncut+1, 0, ncut,  40, -3.14, 3.14);
  h_jet_pt      = new TH2F("h_jet_pt",   "h_jet_pt",     ncut+1, 0, ncut, 120,     0, 600);

  h_jetl_eta    = new TH2F("h_jetl_eta", "h_jetl_eta",   ncut+1, 0, ncut, 100,    -5,    5);
  h_jetl_phi    = new TH2F("h_jetl_phi", "h_jetl_phi",   ncut+1, 0, ncut,  40, -3.14, 3.14);
  h_jetl_pt     = new TH2F("h_jetl_pt",  "h_jetl_pt",    ncut+1, 0, ncut, 120,     0, 600.);
    
  h_jet2l_eta   = new TH2F("h_jet2l_eta","h_jet2l_eta",  ncut+1, 0, ncut, 100,    -5,    5);
  h_jet2l_phi   = new TH2F("h_jet2l_phi","h_jet2l_phi",  ncut+1, 0, ncut,  40, -3.14, 3.14);
  h_jet2l_pt    = new TH2F("h_jet2l_pt", "h_jet2l_pt",   ncut+1, 0, ncut, 120,     0, 600.);
    
  h_met         = new TH2F("h_met",        "h_met",	     ncut+1, 0, ncut, 120, 0, 600.);
  h_met_OS      = new TH2F("h_met_OS",     "h_met_OS",     ncut+1, 0, ncut, 120, 0, 600.);
  h_met_SS      = new TH2F("h_met_SS",     "h_met_SS",     ncut+1, 0, ncut, 120, 0, 600.);

  h_meff        = new TH2F("h_meff",       "h_meff",       ncut+1, 0, ncut, 120, 0, 600.);
  h_mt          = new TH2F("h_mt",         "h_mt",         ncut+1, 0, ncut, 120, 0, 600.);
  h_invmass     = new TH2F("h_invmass",    "h_invmass",    ncut+1, 0, ncut, 120, 0, 600.);
  h_invmass_OS  = new TH2F("h_invmass_OS", "h_invmass_OS", ncut+1, 0, ncut, 120, 0, 600.);
  h_invmass_SS  = new TH2F("h_invmass_SS", "h_invmass_SS", ncut+1, 0, ncut, 120, 0, 600.);
  h_htmiss_OS   = new TH2F("h_htmiss_OS",  "h_htmiss_OS",  ncut+1, 0, ncut, 120, 0, 600.);
  h_htmiss_SS   = new TH2F("h_htmiss_SS",  "h_htmiss_SS",  ncut+1, 0, ncut, 120, 0, 600.);
  h_nGoodPV     = new TH2F("h_nGoodPV",    "h_nGoodPV",    ncut+1, 0, ncut, 20, 0, 19.);
    
  //Creating the histogram. Remember the name you give it, you will later retrieve it in the static method postAnalysis(TSelectorList* fOutput)
  //Registering the histogram with the D3PDSelector
  // WHY?
  // When using Proof, the D3PD Selecter adds this Object to the OutputList
  // Proof automatically merges these Objects at the end, and you get the Ouput list in the static method   postAnalysis(TSelectorList* fOutput)
  
  m_sel->AddTObject(some_histo); 
  m_sel->AddTObject(cutflow_histo);
  m_sel->AddTObject(h_cutflow_susy);
  m_sel->AddTObject(runNumber_histo);
  m_sel->AddTObject(h_trg1);
  m_sel->AddTObject(h_trg1_dR);
  m_sel->AddTObject(h_trg1_d3pd);
  m_sel->AddTObject(h_trg1_d3pd_dR);
  m_sel->AddTObject(h_trg1_deltaR);
  m_sel->AddTObject(h_trg2);
  m_sel->AddTObject(h_trg2_dR);
  m_sel->AddTObject(h_trg2_d3pd);
  m_sel->AddTObject(h_trg2_d3pd_dR);
  m_sel->AddTObject(h_trg2_deltaR);
      
  m_sel->AddTObject(h_e_nb );      
  m_sel->AddTObject(h_e_eta);      
  m_sel->AddTObject(h_e_phi);      
  m_sel->AddTObject(h_e_pt );      
  m_sel->AddTObject(h_e_ptcone20); 
  m_sel->AddTObject(h_e_charge);
  m_sel->AddTObject(h_el_eta);    
  m_sel->AddTObject(h_el_phi);    
  m_sel->AddTObject(h_el_pt );    
  m_sel->AddTObject(h_e2l_eta);    
  m_sel->AddTObject(h_e2l_phi);    
  m_sel->AddTObject(h_e2l_pt );    
  m_sel->AddTObject(h_el_trg_eta);    
  m_sel->AddTObject(h_el_trg_phi);    
  m_sel->AddTObject(h_el_trg_pt );    
  m_sel->AddTObject(h_el_trg_eta_phi );    
  m_sel->AddTObject(h_el_trg_pt_eta );  
  
  m_sel->AddTObject(h_mu_nb );     
  m_sel->AddTObject(h_mu_eta);     
  m_sel->AddTObject(h_mu_phi);     
  m_sel->AddTObject(h_mu_pt );     
  m_sel->AddTObject(h_mu_ptcone20);
  m_sel->AddTObject(h_mu_charge);
  m_sel->AddTObject(h_mul_eta);    
  m_sel->AddTObject(h_mul_phi);    
  m_sel->AddTObject(h_mul_pt );    
  m_sel->AddTObject(h_mu2l_eta);    
  m_sel->AddTObject(h_mu2l_phi);    
  m_sel->AddTObject(h_mu2l_pt );    
  m_sel->AddTObject(h_mu_trg_eta);    
  m_sel->AddTObject(h_mu_trg_phi);    
  m_sel->AddTObject(h_mu_trg_pt );    
  m_sel->AddTObject(h_mu_trg_eta_barrel);    
  m_sel->AddTObject(h_mu_trg_phi_barrel);    
  m_sel->AddTObject(h_mu_trg_pt_barrel );    
  m_sel->AddTObject(h_mu_trg_eta_endcap);    
  m_sel->AddTObject(h_mu_trg_phi_endcap);    
  m_sel->AddTObject(h_mu_trg_pt_endcap );    
  m_sel->AddTObject(h_mu_trg_eta_phi );    
  m_sel->AddTObject(h_mu_trg_pt_eta );    

  m_sel->AddTObject(h_jet_nb );    
  m_sel->AddTObject(h_jet_eta);    
  m_sel->AddTObject(h_jet_phi);    
  m_sel->AddTObject(h_jet_pt );    
  m_sel->AddTObject(h_jetl_eta);    
  m_sel->AddTObject(h_jetl_phi);    
  m_sel->AddTObject(h_jetl_pt );    
  m_sel->AddTObject(h_jet2l_eta);    
  m_sel->AddTObject(h_jet2l_phi);    
  m_sel->AddTObject(h_jet2l_pt );    
    
  m_sel->AddTObject(h_met);   
  m_sel->AddTObject(h_met_OS );    
  m_sel->AddTObject(h_met_SS );    
  m_sel->AddTObject(h_meff);       
  m_sel->AddTObject(h_mt);       
  m_sel->AddTObject(h_invmass);      
  m_sel->AddTObject(h_invmass_SS);      
  m_sel->AddTObject(h_invmass_OS);      
  m_sel->AddTObject(h_htmiss_SS);      
  m_sel->AddTObject(h_htmiss_OS);      
  m_sel->AddTObject(h_nGoodPV);      


  //resetting cutflow variables
  for (int cf = 0; cf < ncut ; cf++) m_cutflow[cf] = 0;  

  ndrellyan=0;
  ndrellyanNOT=0;
  
  std::string filename = path+"/debug.txt";
  debugfile.open(filename.c_str(), ios::app);
  if (!isData){
    filename = path+"/dilepton_mc.txt";
    dileptonfile.open(filename.c_str(),ios::app);
  } else {
#ifdef ELECTRON
  filename = path+"/dilepton_electronStream.txt";
  dileptonfile.open(filename.c_str(), ios::app);
#endif
#ifdef MUON
  filename = path+"/dilepton_muonStream.txt";
  dileptonfile.open(filename.c_str(),ios::app);
#endif  
  }  

#ifdef JESPLUS
  cout << "=========================================================================="<<endl;  
  cout << "==                                                                      =="<<endl;  
  cout << "==                JES estimation: have you changed OPS??                =="<<endl;  
  cout << "==                                                                      =="<<endl;  
  cout << "=========================================================================="<<endl;
#endif    
#ifdef JESMINUS
  cout << "=========================================================================="<<endl;  
  cout << "==                                                                      =="<<endl;  
  cout << "==                JES estimation: have you changed OPS??                =="<<endl;  
  cout << "==                                                                      =="<<endl;  
  cout << "=========================================================================="<<endl;
#endif    
#ifdef JER
  cout << "=========================================================================="<<endl;  
  cout << "==                                                                      =="<<endl;  
  cout << "==                JER estimation: have you changed OPS??                =="<<endl;  
  cout << "==                                                                      =="<<endl;  
  cout << "=========================================================================="<<endl;
#endif    
#ifdef PILEUP
  cout << "================================================"<<endl;
  cout << "==                PILE-UP Sample              =="<<endl;  
  cout << "================================================"<<endl;
#endif  


  //GRL reader
  
  if (isData){
      string pathGRL;       
//#ifdef GRID
//      pathGRL = path+"/"; 
//#else      
      pathGRL = path+"/grl/"; 
//#endif            
  //4.7 fb-1  
    m_goodRunsListReader.AddXMLFile(pathGRL + "data11_7TeV.periodAllYear_DetStatus-v36-pro10_CoolRunQuery-00-04-08_Susy.xml");
    m_goodRunsListReader.Interpret();
    m_goodRunsList = m_goodRunsListReader.GetMergedGoodRunsList();
    //m_goodRunsList.Summary(kTRUE);
  }
  

   // PileUp reweighting  
   std::vector<double> muon_sf_int_lum;
  if (!isData){
      string pathPU;       
//#ifdef GRID
//      pathPU = path+"/"; 
//#else      
      pathPU = path+"/iLumiCalc/"; 
//#endif            

   m_tPileUp = new Root::TPileupReweighting( "MyPileupReweightingTool" );
   TString filePileUpData ="";
   
#ifdef ELECTRON
   filePileUpData = "ilumicalc_histograms_EF_e20_medium_178044-184169.root";
#endif
#ifdef MUON
   filePileUpData = "ilumicalc_histograms_EF_mu18_178044-184169.root";
#endif   
   TString filePileUpMC = "mc11cpileup2201.root";  //mc11c
   filePileUpData = "ilumicalc_histograms_None_178044-191933.root";      

#ifdef TRGSTUDY
   filePileUpMC = "PileUp101111Run3.root";  //mc11a/b
   filePileUpData = "ilumicalc_histograms_EF_mu18_178044-184169.root";
#else
   //m_tPileUp->SetDataScaleFactors(0.9); //explore 10% systematic on this number
#endif
   m_tPileUp->AddConfigFile(pathPU +filePileUpMC);
   m_tPileUp->AddLumiCalcFile(pathPU +filePileUpData);   
   m_tPileUp->SetDefaultChannel(105200);
   m_tPileUp->SetUnrepresentedDataAction(2);
   int pup = m_tPileUp->initialize();
                          
   cout << "Initializing PileUp tool "<< pup <<endl;
   cout << "using "<< pathPU +filePileUpData << " and "<< pathPU +filePileUpMC<< endl;
   
   //get lumi vector for muon scale factors
   muon_sf_int_lum = m_tPileUp->getIntegratedLumiVector();
  } 


#ifdef TRGWEIGHT
    
  TString pathEleRW = path + "/DGTriggerReweight/data/"+"electron_maps.root";
  TString pathMuoRW = path + "/DGTriggerReweight/data/"+"muon_triggermaps.root";
  
  cout << "Trigger reweighting: using maps "<<pathEleRW<<" and "<< pathMuoRW<<endl;  
  trgRWT = new triggerReweight();
  trgRWT->initalizeEE(pathEleRW);
  trgRWT->initalizeMM(pathMuoRW);
  trgRWT->initalizeEMU(pathEleRW,pathMuoRW);  

#endif


// Initialize SUSY tools

#ifdef MC      
  m_SUSYObjDef.initialize(muon_sf_int_lum); // initialize SUSY tools
#else
  m_SUSYObjDef.initialize(); // initialize SUSY tools
#endif
  fakeMetEst.initialize(path+"/SUSYTools/data/fest_periodF_v1.root");
}
