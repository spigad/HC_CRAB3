#include "DGTriggerReweight/triggerReweight.h"

using namespace std;

triggerReweight::~triggerReweight(){

  /** Clean up ee */ 
  if( ths_e12_medium_num    ) delete ths_e12_medium_num;   
  if( ths_e12_medium_den    ) delete ths_e12_medium_den;   
  if( ths_e12T_medium_num   ) delete ths_e12T_medium_num;  
  if( ths_e12T_medium_den   ) delete ths_e12T_medium_den;  
  if( ths_e12Tvh_medium_num ) delete ths_e12Tvh_medium_num;
  if( ths_e12Tvh_medium_den ) delete ths_e12Tvh_medium_den;
  if( ths_e22_medium_num    ) delete ths_e22_medium_num;   
  if( ths_e22_medium_den    ) delete ths_e22_medium_den;   
  if( ths_e20_medium_num    ) delete ths_e20_medium_num;   
  if( ths_e20_medium_den    ) delete ths_e20_medium_den;   
  if( ths_e22vh_medium1_num ) delete ths_e22vh_medium1_num;
  if( ths_e22vh_medium1_den ) delete ths_e22vh_medium1_den;

  if( rew_e12_medium    ) delete rew_e12_medium;   
  if( rew_e12T_medium   ) delete rew_e12T_medium;  
  if( rew_e12Tvh_medium ) delete rew_e12Tvh_medium;
  if( rew_e20_medium    ) delete rew_e20_medium;   
  if( rew_e22_medium    ) delete rew_e22_medium;   
  if( rew_e22vh_medium1 ) delete rew_e22vh_medium1;

  if( electronmaps ){
    if( electronmaps->IsOpen() ) electronmaps->Close(); 
    delete electronmaps; 
  }
	
  /** Clean up mumu */ 
  if( ths_mu18_num ) delete ths_mu18_num;  
  if( ths_mu18_den ) delete ths_mu18_den;  
  if( ths_mu18_medium_num ) delete ths_mu18_medium_num;
  if( ths_mu18_medium_den ) delete ths_mu18_medium_den;
  if( ths_notmu18_mu10_loose_num ) delete ths_notmu18_mu10_loose_num;   
  if( ths_notmu18_mu10_loose_den ) delete ths_notmu18_mu10_loose_den;   
  if( ths_notmu18_medium_mu10_loose_num ) delete ths_notmu18_medium_mu10_loose_num;   
  if( ths_notmu18_medium_mu10_loose_den ) delete ths_notmu18_medium_mu10_loose_den;   
	
  if( rew_mu18 ) delete rew_mu18;   
  if( rew_mu18_medium ) delete rew_mu18_medium;  
  if( rew_notmu18_mu10_loose ) delete rew_notmu18_mu10_loose;
  if( rew_notmu18_medium_mu10_loose ) delete rew_notmu18_medium_mu10_loose;   
	
  if( muonmaps ){
    if( muonmaps->IsOpen() ) muonmaps->Close(); 
    delete muonmaps; 
  }
	
  /** Clean up emu */ 
  if( ths_mu18_num ) delete ths_e10_medium_num;  
  if( ths_mu18_den ) delete ths_e10_medium_den;  
  if( ths_mu18_medium_num ) delete ths_mu6_num;
  if( ths_mu18_medium_den ) delete ths_mu6_den;
	
  if( rew_mu18 ) delete rew_e10_medium;   
  if( rew_mu18_medium ) delete rew_mu6; 

}//End destructor 

//-----------------------------------------------------------------------------

bool triggerReweight::initalizeEE(const char* filename){

  if( filename == 0x0 ){
    cout<<"<triggerReweight::initalizeEE(0x0)> ERROR: "
	<<"NULL filename!"
	<<endl;
    return false; 
  }

  electronmaps = new TFile(filename);
  if( !electronmaps->IsOpen() ){
    cout<<"<triggerReweight::initalizeEE("<<filename<<")> ERROR: "
	<<"Could not open "
	<<filename
	<<endl;
    return false; 
  }

  ths_e12_medium_den=(THnSparseD*)electronmaps->Get("ths_e12_medium_den")->Clone();
  ths_e12_medium_num=(THnSparseD*)electronmaps->Get("ths_e12_medium_num")->Clone();
  ths_e12T_medium_den=(THnSparseD*)electronmaps->Get("ths_e12T_medium_den")->Clone();
  ths_e12T_medium_num=(THnSparseD*)electronmaps->Get("ths_e12T_medium_num")->Clone();
  ths_e12Tvh_medium_den=(THnSparseD*)electronmaps->Get("ths_e12Tvh_medium_den")->Clone();
  ths_e12Tvh_medium_num=(THnSparseD*)electronmaps->Get("ths_e12Tvh_medium_num")->Clone();
  ths_e22_medium_den=(THnSparseD*)electronmaps->Get("ths_e22_medium_den")->Clone();
  ths_e22_medium_num=(THnSparseD*)electronmaps->Get("ths_e22_medium_num")->Clone();
  ths_e20_medium_den=(THnSparseD*)electronmaps->Get("ths_e20_medium_den")->Clone();
  ths_e20_medium_num=(THnSparseD*)electronmaps->Get("ths_e20_medium_num")->Clone();
  ths_e22vh_medium1_den=(THnSparseD*)electronmaps->Get("ths_e22vh_medium1_den")->Clone();
  ths_e22vh_medium1_num=(THnSparseD*)electronmaps->Get("ths_e22vh_medium1_num")->Clone();

  electronmaps->Close();

  rew_e12_medium=new APReweightND(ths_e12_medium_den,ths_e12_medium_num,true);
  rew_e12T_medium=new APReweightND(ths_e12T_medium_den,ths_e12T_medium_num,true);
  rew_e12Tvh_medium=new APReweightND(ths_e12Tvh_medium_den,ths_e12Tvh_medium_num,true);
  rew_e20_medium=new APReweightND(ths_e20_medium_den,ths_e20_medium_num,true);
  rew_e22_medium=new APReweightND(ths_e22_medium_den,ths_e22_medium_num,true);
  rew_e22vh_medium1=new APReweightND(ths_e22vh_medium1_den,ths_e22vh_medium1_num,true);

  return true;


}//End initailizeEE
	
bool triggerReweight::initalizeMM(const char* filename){
	
  if( filename == 0x0 ){
    cout<<"<triggerReweight::initalizeMM(0x0)> ERROR: "
	<<"NULL filename!"
	<<endl;
    return false; 
  }

  muonmaps = new TFile(filename);
  if( !muonmaps->IsOpen() ){
    cout<<"<triggerReweight::initalizeMM("<<filename<<")> ERROR: "
	<<"Could not open "
	<<filename
	<<endl;
    return false; 
  }
	
  ths_mu18_den=(THnSparseD*)muonmaps->Get("ths_mu18_den")->Clone();
  ths_mu18_num=(THnSparseD*)muonmaps->Get("ths_mu18_nom")->Clone();
  ths_mu18_medium_den=(THnSparseD*)muonmaps->Get("ths_mu18_medium_den")->Clone();
  ths_mu18_medium_num=(THnSparseD*)muonmaps->Get("ths_mu18_medium_nom")->Clone();
  ths_notmu18_mu10_loose_den=(THnSparseD*)muonmaps->Get("ths_notmu18_mu10_loose_den")->Clone();
  ths_notmu18_mu10_loose_num=(THnSparseD*)muonmaps->Get("ths_notmu18_mu10_loose_nom")->Clone();
  ths_notmu18_medium_mu10_loose_den=(THnSparseD*)muonmaps->Get("ths_notmu18_medium_mu10_loose_den")->Clone();
  ths_notmu18_medium_mu10_loose_num=(THnSparseD*)muonmaps->Get("ths_notmu18_medium_mu10_loose_nom")->Clone();

  muonmaps->Close();
	
  rew_mu18=new APReweightND(ths_mu18_den,ths_mu18_num,true);
  rew_mu18_medium=new APReweightND(ths_mu18_medium_den,ths_mu18_medium_num,true);
  rew_notmu18_mu10_loose=new APReweightND(ths_notmu18_mu10_loose_den,ths_notmu18_mu10_loose_num,true);
  rew_notmu18_medium_mu10_loose=new APReweightND(ths_notmu18_medium_mu10_loose_den,ths_notmu18_medium_mu10_loose_num,true);

  return true;


}//End initailizeMM
	
bool triggerReweight::initalizeEMU(const char* elecFilename, const char* muonFilename){
	
  if( elecFilename == 0x0 || muonFilename == 0x0 ){
    cout<<"<triggerReweight::initalizeEMU(0x0)> ERROR: "
	<<"NULL filename!"
	<<endl;
    return false; 
  }
	
  electronmaps = new TFile(elecFilename);
  if( !electronmaps->IsOpen() ){
    cout<<"<triggerReweight::initalizeEMU("<<elecFilename<<")> ERROR: "
	<<"Could not open "
	<<elecFilename
	<<endl;
    return false; 
  }
	
  muonmaps = new TFile(muonFilename);
  if( !muonmaps->IsOpen() ){
    cout<<"<triggerReweight::initalizeEMU("<<muonFilename<<")> ERROR: "
	<<"Could not open "
	<<muonFilename
	<<endl;
    return false; 
  }

  ths_e10_medium_den=(THnSparseD*)electronmaps->Get("ths_e10_medium_den")->Clone();
  ths_e10_medium_num=(THnSparseD*)electronmaps->Get("ths_e10_medium_num")->Clone();
  ths_mu6_den=(THnSparseD*)muonmaps->Get("ths_mu6_den")->Clone();
  ths_mu6_num=(THnSparseD*)muonmaps->Get("ths_mu6_nom")->Clone();
  ths_mu18_den=(THnSparseD*)muonmaps->Get("ths_mu18_den")->Clone();
  ths_mu18_num=(THnSparseD*)muonmaps->Get("ths_mu18_nom")->Clone();
  ths_mu18_medium_den=(THnSparseD*)muonmaps->Get("ths_mu18_medium_den")->Clone();
  ths_mu18_medium_num=(THnSparseD*)muonmaps->Get("ths_mu18_medium_nom")->Clone();
  ths_e20_medium_den=(THnSparseD*)electronmaps->Get("ths_e20_medium_den")->Clone();
  ths_e20_medium_num=(THnSparseD*)electronmaps->Get("ths_e20_medium_num")->Clone();
  ths_e22vh_medium1_den=(THnSparseD*)electronmaps->Get("ths_e22vh_medium1_den")->Clone();
  ths_e22vh_medium1_num=(THnSparseD*)electronmaps->Get("ths_e22vh_medium1_num")->Clone();
  ths_e22_medium_den=(THnSparseD*)electronmaps->Get("ths_e22_medium_den")->Clone();
  ths_e22_medium_num=(THnSparseD*)electronmaps->Get("ths_e22_medium_num")->Clone();

  electronmaps->Close();
  muonmaps->Close();
	
  rew_e10_medium=new APReweightND(ths_e10_medium_den,ths_e10_medium_num,true);
  rew_mu6=new APReweightND(ths_mu6_den,ths_mu6_num,true);
  rew_mu18=new APReweightND(ths_mu18_den,ths_mu18_num,true);
  rew_mu18_medium=new APReweightND(ths_mu18_medium_den,ths_mu18_medium_num,true);
  rew_e20_medium=new APReweightND(ths_e20_medium_den,ths_e20_medium_num,true);
  rew_e22vh_medium1=new APReweightND(ths_e22vh_medium1_den,ths_e22vh_medium1_num,true);
  rew_e22_medium=new APReweightND(ths_e22_medium_den,ths_e22_medium_num,true);

  return true;


}//End initailizeEMU

//-----------------------------------------------------------------------------

double triggerReweight::triggerReweightEE(int RunNumber, 
					  double elpt1, double eleta1, 
					  double elpt2, double eleta2, 
					  double LumiFrac_185353_186755, 
					  double LumiFrac_186873_187815){

  /** The maps only go up to pT 100, reset to 100 for above that */ 
  if( elpt1 > 100000. ) elpt1 = 100000.; 
  if( elpt2 > 100000. ) elpt2 = 100000.;

  APEvtWeight DiElectronWeight( APEvtWeight::kDiElectron );
  APEvtWeight DiElectronWeight2( APEvtWeight::kDiElectron );

  APEvtWeight SingleElectronWeight( APEvtWeight::kElectron );
  APEvtWeight SingleElectronWeight2( APEvtWeight::kElectron );

  double eleta1bin=1.0,eleta2bin=1.0;
  if(fabs(eleta1)>0 && fabs(eleta1)<=0.6){
    eleta1bin=1.0;
  }
  else if(fabs(eleta1)>0.6 && fabs(eleta1)<=0.8){
    eleta1bin=2.0;
  }
  else if(fabs(eleta1)>0.8 && fabs(eleta1)<=1.15){
    eleta1bin=3.0;
  }
  else if(fabs(eleta1)>1.15 && fabs(eleta1)<=1.37){
    eleta1bin=4.0;
  }
  else if(fabs(eleta1)>1.37 && fabs(eleta1)<=1.52){
    eleta1bin=5.0;
  }
  else if(fabs(eleta1)>1.52 && fabs(eleta1)<=1.81){
    eleta1bin=6.0;
  }
  else if(fabs(eleta1)>1.81 && fabs(eleta1)<=2.01){
    eleta1bin=7.0;
  }
  else if(fabs(eleta1)>2.01 && fabs(eleta1)<=2.37){
    eleta1bin=8.0;
  }
  else if(fabs(eleta1)>2.37 && fabs(eleta1)<=2.47){
    eleta1bin=9.0;
  }

  if(fabs(eleta2)>0 && fabs(eleta2)<=0.6){
    eleta2bin=1.0;
  }
  else if(fabs(eleta2)>0.6 && fabs(eleta2)<=0.8){
    eleta2bin=2.0;
  }
  else if(fabs(eleta2)>0.8 && fabs(eleta2)<=1.15){
    eleta2bin=3.0;
  }
  else if(fabs(eleta2)>1.15 && fabs(eleta2)<=1.37){
    eleta2bin=4.0;
  }
  else if(fabs(eleta2)>1.37 && fabs(eleta2)<=1.52){
    eleta2bin=5.0;
  }
  else if(fabs(eleta2)>1.52 && fabs(eleta2)<=1.81){
    eleta2bin=6.0;
  }
  else if(fabs(eleta2)>1.81 && fabs(eleta2)<=2.01){
    eleta2bin=7.0;
  }
  else if(fabs(eleta2)>2.01 && fabs(eleta2)<=2.37){
    eleta2bin=8.0;
  }
  else if(fabs(eleta2)>2.37 && fabs(eleta2)<=2.47){
    eleta2bin=9.0;
  }


  double triggerweight=1.0;

  //APEvtWeight FullWeight=new APEvtWeight();
  //APEvtWeight FullWeight2=new APEvtWeight();


  double leadpt=max(elpt1,elpt2);
  double subpt=min(elpt1,elpt2);
  double leadelpt,leadeletabin,subleadelpt,subleadeletabin;
  if(leadpt==elpt1){
    leadelpt=elpt1;
    leadeletabin=eleta1bin;
    subleadelpt=elpt2;
    subleadeletabin=eleta2bin;
  }
  else{
    leadelpt=elpt2;
    leadeletabin=eleta2bin;
    subleadelpt=elpt1;
    subleadeletabin=eleta1bin;

  }


  double el1[]={leadeletabin,leadelpt/1000.};
  double el2[]={subleadeletabin,subleadelpt/1000.};

  if(leadpt>25000.){


    if(RunNumber<=184169){

      SingleElectronWeight.AddWeightToEvt( rew_e20_medium->GetWeight( el1 ) );
      SingleElectronWeight.AddWeightToEvt( rew_e20_medium->GetWeight( el2 ) );
      APEvtWeight FullWeight = SingleElectronWeight;
      triggerweight=FullWeight.GetWeight();

      //triggerweight=double((int)(e20_medium||_2e12_medium));}
    }
    else if(RunNumber==189751){
      SingleElectronWeight.AddWeightToEvt( rew_e22vh_medium1->GetWeight( el1 ) );
      SingleElectronWeight.AddWeightToEvt( rew_e22vh_medium1->GetWeight( el2 ) );
      APEvtWeight FullWeight= SingleElectronWeight;
      triggerweight=FullWeight.GetWeight();


    }

    else if(RunNumber==186169){
      SingleElectronWeight.AddWeightToEvt( rew_e20_medium->GetWeight( el1 ) );
      SingleElectronWeight.AddWeightToEvt( rew_e20_medium->GetWeight( el2 ) );
      SingleElectronWeight2.AddWeightToEvt( rew_e22_medium->GetWeight( el1 ) );
      SingleElectronWeight2.AddWeightToEvt( rew_e22_medium->GetWeight( el2 ) );
      APEvtWeight FullWeight= SingleElectronWeight;
      APEvtWeight FullWeight2= SingleElectronWeight2;

      triggerweight=(FullWeight.GetWeight()*LumiFrac_185353_186755)+(FullWeight2.GetWeight()*LumiFrac_186873_187815);


    }
  }
  else if(leadpt<=25000. &&  subpt>17000.){


    if(RunNumber<=184169){

      DiElectronWeight.AddWeightToEvt( rew_e12_medium->GetWeight( el1 ) );
      DiElectronWeight.AddWeightToEvt( rew_e12_medium->GetWeight( el2 ) );
      APEvtWeight FullWeight = DiElectronWeight;
      triggerweight=FullWeight.GetWeight();

      //triggerweight=double((int)(e20_medium||_2e12_medium));}
    }
    else if(RunNumber==189751){
      DiElectronWeight.AddWeightToEvt( rew_e12Tvh_medium->GetWeight( el1 ) );
      DiElectronWeight.AddWeightToEvt( rew_e12Tvh_medium->GetWeight( el2 ) );
      APEvtWeight FullWeight= DiElectronWeight;
      triggerweight=FullWeight.GetWeight();


    }

    else if(RunNumber==186169){
      DiElectronWeight.AddWeightToEvt( rew_e12_medium->GetWeight( el1 ) );
      DiElectronWeight.AddWeightToEvt( rew_e12_medium->GetWeight( el2 ) );
      DiElectronWeight2.AddWeightToEvt( rew_e12T_medium->GetWeight( el1 ) );
      DiElectronWeight2.AddWeightToEvt( rew_e12T_medium->GetWeight( el2 ) );
      APEvtWeight FullWeight= DiElectronWeight;
      APEvtWeight FullWeight2= DiElectronWeight2;

      triggerweight=(FullWeight.GetWeight()*LumiFrac_185353_186755)+(FullWeight2.GetWeight()*LumiFrac_186873_187815);

    }
  }

  else{triggerweight=0.0;}

  return triggerweight;

}//End triggerReweightEE

//-----------------------------------------------------------------------------

double triggerReweight::triggerReweightMM(int RunNumber, 
					  double mu_staco_pt1, double mu_staco_eta1, double mu_staco_phi1, 
					  int mu_staco_isCombinedMuon1, double mu_staco_ptcone201, 
					  double mu_staco_pt2, double mu_staco_eta2, double mu_staco_phi2, 
					  int mu_staco_isCombinedMuon2, double mu_staco_ptcone202,
					  double lumifrac_185353_186493, double lumifrac_186516_187815) {
  APEvtWeight wsm( APEvtWeight::kMuon );
  APEvtWeight wdm( APEvtWeight::kDiMuon );
  APEvtWeight wsm_early( APEvtWeight::kMuon );
  APEvtWeight wsm_late( APEvtWeight::kMuon );
  APEvtWeight wdm_early( APEvtWeight::kDiMuon );
  APEvtWeight wdm_late( APEvtWeight::kDiMuon );

  double properties1[]={ mu_staco_pt1, mu_staco_eta1,  mu_staco_phi1,  mu_staco_isCombinedMuon1,  mu_staco_ptcone201};
  double properties2[]={ mu_staco_pt2, mu_staco_eta2,  mu_staco_phi2,  mu_staco_isCombinedMuon2,  mu_staco_ptcone202};
  
  double weight = 1.0;

  if(RunNumber<=184169) {

    if(properties1[0]>20000.){wsm.AddWeightToEvt( rew_mu18 -> GetWeight( properties1 ) );}

    if(properties2[0]>20000.){wsm.AddWeightToEvt( rew_mu18 -> GetWeight( properties2 ) );}

    if(properties1[0]>12000.){wdm.AddWeightToEvt( rew_notmu18_mu10_loose -> GetWeight( properties1 ) );}
    if(properties2[0]>12000.){wdm.AddWeightToEvt( rew_notmu18_mu10_loose -> GetWeight( properties2 ) );}
     
    APEvtWeight FinalWeight = wdm || wsm;
    weight=FinalWeight.GetWeight();

  }

  else if (RunNumber==189751) {
    
    if(properties1[0]>20000.){wsm.AddWeightToEvt( rew_mu18_medium -> GetWeight( properties1 ) );}
    
    if(properties2[0]>20000.){wsm.AddWeightToEvt( rew_mu18_medium -> GetWeight( properties2 ) );}
    
    if(properties1[0]>12000.){wdm.AddWeightToEvt( rew_notmu18_medium_mu10_loose -> GetWeight( properties1 ) );}
    if(properties2[0]>12000.){wdm.AddWeightToEvt( rew_notmu18_medium_mu10_loose -> GetWeight( properties2 ) );}
    
    APEvtWeight FinalWeight = wdm || wsm;
    weight=FinalWeight.GetWeight();

  }

  else if (RunNumber==186169) {

    
    if(properties1[0]>20000.){wsm_early.AddWeightToEvt( rew_mu18 -> GetWeight( properties1 ) );}

    if(properties2[0]>20000.){wsm_early.AddWeightToEvt( rew_mu18 -> GetWeight( properties2 ) );}

    if(properties1[0]>12000.){wdm_early.AddWeightToEvt( rew_notmu18_mu10_loose -> GetWeight( properties1 ) );}
    if(properties2[0]>12000.){wdm_early.AddWeightToEvt( rew_notmu18_mu10_loose -> GetWeight( properties2 ) );}
     
    APEvtWeight FinalWeight_early = wdm_early || wsm_early;
    double weight_early=FinalWeight_early.GetWeight();

    if(properties1[0]>20000.){wsm_late.AddWeightToEvt( rew_mu18_medium -> GetWeight( properties1 ) );}

    if(properties2[0]>20000.){wsm_late.AddWeightToEvt( rew_mu18_medium -> GetWeight( properties2 ) );}

    if(properties1[0]>12000.){wdm_late.AddWeightToEvt( rew_notmu18_medium_mu10_loose -> GetWeight( properties1 ) );}
    if(properties2[0]>12000.){wdm_late.AddWeightToEvt( rew_notmu18_medium_mu10_loose -> GetWeight( properties2 ) );}
     
    APEvtWeight FinalWeight_late = wdm_late || wsm_late;
    double weight_late=FinalWeight_late.GetWeight();

    weight = weight_early*lumifrac_185353_186493 + weight_late*lumifrac_186516_187815;
    
  }


  return weight;
}

double triggerReweight::triggerReweightEMU(int RunNumber, 
					   double elpt1, double eleta1, 
					   double mu_staco_pt1, double mu_staco_eta1, double mu_staco_phi1, int mu_staco_isCombinedMuon1, double mu_staco_ptcone20_1,
					   double LumiFrac_185353_186493, double LumiFrac_186516_186755, double LumiFrac_186873_187815) {
	
  /** The maps only go up to pT 100, reset to 100 for above that */ 
  if( elpt1 > 100000. ) elpt1 = 100000.; 

  APEvtWeight SingleMuonWeightBtoI( APEvtWeight::kMuon );
  APEvtWeight SingleMuonWeightJtoM( APEvtWeight::kMuon );
  
  APEvtWeight SingleElectronWeightBtoJ( APEvtWeight::kElectron );
  APEvtWeight SingleElectronWeightK( APEvtWeight::kElectron );
  APEvtWeight SingleElectronWeightLtoM( APEvtWeight::kElectron );
  
  APEvtWeight ElectronWeightEmu( APEvtWeight::kElectron );
  APEvtWeight MuonWeightEmu( APEvtWeight::kMuon );

  double eleta1bin=1.0;
  if(fabs(eleta1)>0 && fabs(eleta1)<=0.6){
    eleta1bin=1.0;
  }
  else if(fabs(eleta1)>0.6 && fabs(eleta1)<=0.8){
    eleta1bin=2.0;
  }
  else if(fabs(eleta1)>0.8 && fabs(eleta1)<=1.15){
    eleta1bin=3.0;
  }
  else if(fabs(eleta1)>1.15 && fabs(eleta1)<=1.37){
    eleta1bin=4.0;
  }
  else if(fabs(eleta1)>1.37 && fabs(eleta1)<=1.52){
    eleta1bin=5.0;
  }
  else if(fabs(eleta1)>1.52 && fabs(eleta1)<=1.81){
    eleta1bin=6.0;
  }
  else if(fabs(eleta1)>1.81 && fabs(eleta1)<=2.01){
    eleta1bin=7.0;
  }
  else if(fabs(eleta1)>2.01 && fabs(eleta1)<=2.37){
    eleta1bin=8.0;
  }
  else if(fabs(eleta1)>2.37 && fabs(eleta1)<=2.47){
    eleta1bin=9.0;
  }
  
  double triggerweight=1.0;

  double leadpt=elpt1;
  
  double el1[]={eleta1bin,leadpt/1000.};
  double muon1[]={ mu_staco_pt1, mu_staco_eta1,  mu_staco_phi1,  mu_staco_isCombinedMuon1,  mu_staco_ptcone20_1};
  
  if(muon1[0]>20000.){
    SingleMuonWeightBtoI.AddWeightToEvt( rew_mu18 -> GetWeight( muon1 ) );
    SingleMuonWeightJtoM.AddWeightToEvt( rew_mu18_medium -> GetWeight( muon1 ));
  }

  if(leadpt>25000.){
    SingleElectronWeightBtoJ.AddWeightToEvt( rew_e20_medium -> GetWeight( el1 ) );
    SingleElectronWeightLtoM.AddWeightToEvt( rew_e22vh_medium1 -> GetWeight( el1 ) );
    SingleElectronWeightK.AddWeightToEvt( rew_e22_medium -> GetWeight( el1 ) );
  }
  
  ElectronWeightEmu.AddWeightToEvt( rew_e10_medium -> GetWeight( el1 ) );
  MuonWeightEmu.AddWeightToEvt( rew_mu6 -> GetWeight( muon1 ) );
  
  APEvtWeight EMutrigger=ElectronWeightEmu && MuonWeightEmu;

  if(leadpt>25000. || mu_staco_pt1>20000.){
    
    APEvtWeight SingleElorSingleMuBtoI = SingleElectronWeightBtoJ || SingleMuonWeightBtoI;
    APEvtWeight SingleElorSingleMuJ = SingleElectronWeightBtoJ || SingleMuonWeightJtoM;
    APEvtWeight SingleElorSingleMuK = SingleElectronWeightK || SingleMuonWeightJtoM;
    APEvtWeight SingleElorSingleMuLtoM =SingleElectronWeightLtoM || SingleMuonWeightJtoM;

    if(RunNumber<=184169){
      triggerweight=SingleElorSingleMuBtoI.GetWeight();
    }
    
    else if(RunNumber==189751){
      triggerweight=SingleElorSingleMuLtoM.GetWeight();
    }
    else if(RunNumber==186169){
      
      triggerweight=((LumiFrac_185353_186493*SingleElorSingleMuBtoI.GetWeight())+(LumiFrac_186516_186755*SingleElorSingleMuJ.GetWeight())+(LumiFrac_186873_187815*SingleElorSingleMuK.GetWeight()));
      
    }

  }
  else{
    APEvtWeight SingleMuorEmu= EMutrigger;
    triggerweight=SingleMuorEmu.GetWeight();
  }

  return triggerweight;
	
}
