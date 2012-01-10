#include <cstring>
#include <iostream>
#include <stdio.h>
#include <TROOT.h>
#include <math.h>
#include "TRandom3.h"


class SmearingClass{
 public:
  /*Constructors*/
  SmearingClass() {Initialize();}
 
 
  /************/
  /* Methods */   
  /**********/
 
  /** internal use only **/
  void Initialize() {	
    detType="";
    GeV=1000;
    gRand = new TRandom3();
    gRand->SetSeed(0);     // later we will call SetSeed(int offset, int evtn, int muon_index) to reset seed for each muon
    useTan2=true;
    ptms=0;
    ptid=0;
    ptcb=0;
    eta=0;
  }
 
  /** configure smearing **/
 
  void SetSeed(int seed) {gRand->SetSeed(seed);}
  void SetSeed(int evtnum, int muon_index, int offset=680049) {gRand->SetSeed(offset + evtnum + muon_index*100);}
  void UseTan2(bool U) {useTan2=U;}/* use pT/tan(theta)^2 parameterization for CSC region */ 
  void UseGeV() {GeV=1;}  /* if input momenta are in GeV */
  void UseScale(bool applyScale) {useScale=applyScale;}  /* also use momentum scale, set as default */
 
  /* MS or ID smearing only. DetType="MS","ID"*/
  void Event(double Pt, double Eta2,std::string DetType)
  {	  
    ptms=0;
    ptid=0;
    ptcb=0;
   
    if (DetType=="MS")      ptms = Pt;
    else if (DetType=="ID") ptid = Pt;
    else std::cout<<"SmearingClass ERROR: wrong DetType in input "<<DetType<<std::endl;
    eta=Eta2;   
    detType=DetType;
    Event();
  }
 
  /* For full MS ID and CB smearing */
  void Event(double PtMS, double PtID, double PtCB, double Eta1)
  {
    detType="All";
    ptms=PtMS;
    ptid=PtID;
    ptcb=PtCB;
    eta=Eta1;
    Event();
  } 
 
  void  Event()  {
    smearMS=0;
    smearID=0;
    smearCB=0;
   
    /* Detector Region */
    if (fabs(eta)<1.05)     detRegion=0;
    else if (fabs(eta)<1.7) detRegion=1;
    else if (fabs(eta)<2.0) detRegion=2;
    else if (fabs(eta)<2.5) detRegion=3;
    else detRegion=-1;
   
    g1 = gRand->Gaus(0,1); 
    g2 = gRand->Gaus(0,1);
    g3 = gRand->Gaus(0,1);
    g4 = gRand->Gaus(0,1);
   
    /** Definition: pT'=pT(1+smear) **/   
    smearMS=Smearing("MS");
    smearID=Smearing("ID");
    if (detType=="All") smearCB=Combine(smearMS,smearID);
       
    ErrorMatrix();   
  }
 

  double Smearing(std::string DetType) {
   
    if (detRegion<0||detRegion>3) return 0;
   
    if (DetType=="MS") {return (MS_MS[detRegion]*g1+MS_AL[detRegion]*g2*ptms/GeV);}
    else if(DetType=="ID")
      {
	if (useTan2&&detRegion==3) {return (ID_MS[detRegion]*g4+ID_ALTAN[detRegion]*g3*ptid/GeV*sinh(eta)*sinh(eta));}
   	else {return (ID_MS[detRegion]*g4+ID_AL[detRegion]*g3*ptid/GeV);}
      }
    else std::cout<<"Error:: DetType not defined "<<DetType<<std::endl;
    return 0;
  }
 
  double Combine(double SmearMS,double SmearID) {
    /** do the average with the EXPECTED resolutions **/

    if (detRegion<0||detRegion>3) return 0;
    if (ptcb==0) {std::cout<<"Warning: ptcb==0"<<std::endl;return 0;}

    double SigmaMS=pow(
   		       pow(MC_MS_CALO[detRegion]/ptcb*GeV,2)+
   		       pow(MC_MS_MS[detRegion],2)+
   		       pow(MC_MS_AL[detRegion]*ptcb/GeV,2),0.5);

    double SigmaID=pow(
   		       pow(MC_ID_MS[detRegion],2)+
   		       pow(MC_ID_AL[detRegion]*ptcb/GeV,2),0.5);

    if (detRegion==3&&useTan2) {
      SigmaID=pow(
   		  pow(MC_ID_MS[detRegion],2)+
   		  pow(MC_ID_ALTAN[detRegion]*ptcb/GeV*sinh(eta)*sinh(eta),2),0.5);
    }


    wMS=1./SigmaMS/SigmaMS;
    wID=1./SigmaID/SigmaID;
    return (SmearMS*wMS+SmearID*wID)/(wMS+wID);
  }
 
  void ErrorMatrix() {

    vms=0;
    vid=0;
    corr=0;

    if (detRegion<0||detRegion>3) return;


    if (!useTan2||detRegion!=3){
      double s1=pow(E_MS_MS[detRegion]*E_MS_MS[detRegion]+S_MS_MS[detRegion]*S_MS_MS[detRegion],0.5);
      double s2=pow(E_MS_AL[detRegion]*E_MS_AL[detRegion]+S_MS_AL[detRegion]*S_MS_AL[detRegion],0.5);
      double s3=pow(E_ID_AL[detRegion]*E_ID_AL[detRegion]+S_ID_AL[detRegion]*S_ID_AL[detRegion],0.5);
      vms=g1*g1*s1*s1+
   	g2*g2*ptms/GeV*ptms/GeV*s2*s2+
   	2.*g1*g2*ptms/GeV*s1*s2*CorrMat[detRegion][0];
      vms=pow(vms,0.5);
      vid=g3*g3*ptid/GeV*ptid/GeV*s3*s3;
      vid=pow(vid,0.5);
      if (vms*vid!=0)
   	corr=(g1*g3*s1*s3*ptid/GeV*CorrMat[detRegion][1]+g2*g3*ptms/GeV*ptid/GeV*s2*s3*CorrMat[detRegion][2])/vms/vid;
    } else {
      double s1=pow(E_MS_MS[detRegion]*E_MS_MS[detRegion]+S_MS_MS[detRegion]*S_MS_MS[detRegion],0.5);
      double s2=pow(E_MS_AL[detRegion]*E_MS_AL[detRegion]+S_MS_AL[detRegion]*S_MS_AL[detRegion],0.5);
      double s3=pow(E_ID_ALTAN[detRegion]*E_ID_ALTAN[detRegion]+S_ID_ALTAN[detRegion]*S_ID_ALTAN[detRegion],0.5);
      vms=g1*g1*s1*s1+
   	g2*g2*ptms/GeV*ptms/GeV*s2*s2+
   	2.*g1*g2*ptms/GeV*s1*s2*CorrMatTan[detRegion][0];
      vms=pow(vms,0.5);
      vid=g3*g3*ptid/GeV*ptid/GeV*s3*s3*sinh(eta)*sinh(eta)*sinh(eta)*sinh(eta);
      vid=pow(vid,0.5);
      if (vms*vid!=0)
   	corr=(g1*g3*s1*s3*ptid/GeV*sinh(eta)*sinh(eta)*CorrMatTan[detRegion][1]+
   	      g2*g3*ptms/GeV*sinh(eta)*sinh(eta)*ptid/GeV*s2*s3*CorrMatTan[detRegion][2])/vms/vid;
    }

  }
 
 
  double pTMS() {return ptms*(1+smearMS);} /* smeared muon spectrometer pT */
  double pTMS(double SmearMS) {return ptms*(1+SmearMS);} /* smeared muon spectrometer pT */
 
  double pTID() {return ptid*(1+smearID);}  /* smeared inner detector pT */
  double pTID(double SmearID) {return ptid*(1+SmearID);}  /* smeared inner detector pT */
 
  double pTCB() {
   	if(useScale) return scale_CB[detRegion]*ptcb*(1+smearCB);
   	else return ptcb*(1+smearCB);
  }  /* smeared combined pT*/
 
  double pTCB(double SmearCB) {
   	if(useScale) return scale_CB[detRegion]*ptcb*(1+SmearCB);
   	else return ptcb*(1+SmearCB);
  }  /* smeared combined pT*/
 
 
  double SMS() {return smearMS;}
  double SID() {return smearID;}
  double SCB() {return smearCB;}
 
  double VMS()  {return vms;}  /* error smearMS */
  double VID()  {return vid;}  /* error smearID */
  double Corr() {return corr;} /* correlation between smearMS and smearID */
 
 
  void MSUP(double &PtMS) {
    double SmearMS=smearMS+vms;
    PtMS=pTMS(SmearMS);
  }
 
  void MSUP(double &PtMS,double &PtID,double &PtCB) {
    double SmearMS=smearMS+vms;
    double SmearID=smearID+vid*corr;

    PtMS=pTMS(SmearMS);
    PtID=pTID(SmearID);
    if (detType=="All") {
      double SmearCB=Combine(SmearMS,SmearID);
      PtCB=pTCB(SmearCB);
    }
  }
 
  void MSLOW(double &PtMS) {
    double SmearMS=smearMS-vms;
    PtMS=pTMS(SmearMS);
  }
 
  void MSLOW(double &PtMS,double &PtID,double &PtCB) {
    double SmearMS=smearMS-vms;
    double SmearID=smearID-vid*corr;

    PtMS=pTMS(SmearMS);
    PtID=pTID(SmearID);
    if (detType=="All") {
      double SmearCB=Combine(SmearMS,SmearID);
      PtCB=pTCB(SmearCB);
    }
  }


  void IDUP(double &PtID) {
    double SmearID=smearID+vid;
    PtID=pTID(SmearID);
  }
 
  void IDUP(double &PtMS,double &PtID,double &PtCB) {
    double SmearMS=smearMS+vms*corr;
    double SmearID=smearID+vid;

    PtMS=pTMS(SmearMS);
    PtID=pTID(SmearID);
    if (detType=="All") {
      double SmearCB=Combine(SmearMS,SmearID);
      PtCB=pTCB(SmearCB);
    }
  }

  void IDLOW(double &PtID) {
    double SmearID=smearID-vid;
    PtID=pTID(SmearID);
  }
 
  void IDLOW(double &PtMS,double &PtID,double &PtCB) {
    double SmearMS=smearMS-vms*corr;
    double SmearID=smearID-vid;

    PtMS=pTMS(SmearMS);
    PtID=pTID(SmearID);
    if (detType=="All") {
      double SmearCB=Combine(SmearMS,SmearID);
      PtCB=pTCB(SmearCB);
    }
  }
 


  void PTVar(double &Pt,std::string fun) {
    if (fun=="IDUP") IDUP(Pt);
    else if (fun=="IDLOW") IDLOW(Pt);
    else if (fun=="MSUP") MSUP(Pt);
    else if (fun=="MSLOW") MSLOW(Pt);
  }
 
  void PTVar(double &PtMS,double &PtID,double &PtCB,std::string fun) {
    if (fun=="IDUP") IDUP(PtMS,PtID,PtCB);
    else if (fun=="IDLOW") IDLOW(PtMS,PtID,PtCB);
    else if (fun=="MSUP") MSUP(PtMS,PtID,PtCB);
    else if (fun=="MSLOW") MSLOW(PtMS,PtID,PtCB);
  }
 



  /** simple methods for retrieving input values (not needed since all members are public) **/
     
  double ptms_orig() {return ptms;}
  double ptid_orig() {return ptid;}
  double ptcb_orig() {return ptcb;}
  double Eta() {return eta;} 
  int DetRegion() {return detRegion;}


  /*members*/
  TRandom3* gRand;
  double ptms,ptid,ptcb,eta;
  double vms,vid,corr;
  double smearMS,smearID,smearCB;
  bool   useTan2;
  std::string detType;
  int detRegion;
  double GeV;
  double g1,g2,g3,g4;
  double wMS,wID;
  bool useScale;
 
  static const double scale_CB[4];   
  static const double scaleSyst_CB[4];   

  static const double ID_MS[4];   
  static const double ID_AL[4];   
  static const double ID_ALTAN[4];
  static const double MS_MS[4];   
  static const double MS_AL[4];   

  static const double E_ID_MS[4];   
  static const double E_ID_AL[4];   
  static const double E_ID_ALTAN[4];
  static const double E_MS_MS[4];   
  static const double E_MS_AL[4];   
 
  static const double S_ID_MS[4];   
  static const double S_ID_AL[4];   
  static const double S_ID_ALTAN[4];
  static const double S_MS_MS[4];   
  static const double S_MS_AL[4];   

  static const double MC_ID_MS[4];   
  static const double MC_ID_AL[4];   
  static const double MC_ID_ALTAN[4];
  static const double MC_MS_CALO[4];
  static const double MC_MS_MS[4];   
  static const double MC_MS_AL[4];   
 
  static const double CorrMat[4][3];
  static const double CorrMatTan[4][3];
 
};

/** scale parameters rel 15 **/
const double SmearingClass::scale_CB[4] = {1-0.0007, 1-0.001, 1+0.012, 1+0.005};
const double SmearingClass::scaleSyst_CB[4] = {0.0008 , 0.003, 0.004, 0.004};

/** Smearing Parameters rel.15 (Muid) **/
const double SmearingClass::ID_MS[4]	   = {0,0,0,0};
const double SmearingClass::ID_AL[4]	   = {0.000403,0.000913,0.001273,0.002667};
const double SmearingClass::ID_ALTAN[4]    = {0,0,0,0.0001344};
const double SmearingClass::MS_MS[4]	   = {0.02619,0.067,0.0377,0.0324};
const double SmearingClass::MS_AL[4]	   = {0.00018,0.00018,0.00018,0.0005};
/** Error for Smearing Parameters rel.15 (Muid) **/
const double SmearingClass::E_ID_MS[4]       = {0,0,0,0};
const double SmearingClass::E_ID_AL[4]       = {0.000038,0.000039,0.000074,0.000050};
const double SmearingClass::E_ID_ALTAN[4]    = {0,0,0,0.0000060};
const double SmearingClass::E_MS_MS[4]       = {0.00087,0.0013,0.0027,0.0099};
const double SmearingClass::E_MS_AL[4]       = {0.00004,0.00018,0.00018,0.0002};
/** sist error **/
const double SmearingClass::S_ID_MS[4]       = {0,0,0,0};
const double SmearingClass::S_ID_AL[4]       = {0.000016,0.000047,0.000011,0.000001};
const double SmearingClass::S_ID_ALTAN[4]    = {0,0,0,0};
const double SmearingClass::S_MS_MS[4]       = {0.0004,0.00259,0.00036,0.00188};
const double SmearingClass::S_MS_AL[4]       = {0.,0.,0.,0.};

/** MC Parameters rel.15 (Muid) **/
const double SmearingClass::MC_ID_MS[4]    = {0.016,0.026,0.034,0.048};
const double SmearingClass::MC_ID_AL[4]    = {0.00029,0.0003,0.00042,0.00094};
const double SmearingClass::MC_ID_ALTAN[4] = {0,0,0,0.000063};
const double SmearingClass::MC_MS_CALO[4]  = {0.23,0,0,0.17};
const double SmearingClass::MC_MS_MS[4]    = {0.027,0.054,0.033,0.027};
const double SmearingClass::MC_MS_AL[4]    = {0.00013,0.00023,0.000093,0.000074};
/***********************************/
/** Correlations   p1p2,p1p3,p2p3 **/ 
const double SmearingClass::CorrMat[4][3] = { {0.248,-0.878,-0.493},
   					      {-0.698,-0.157,-0.200},
   					      {-0.299,-0.732,-0.024},
   					      {-0.818,-0.421,-0.051}};

const double SmearingClass::CorrMatTan[4][3] = { {0.248,-0.878,-0.493},
   						 {-0.698,-0.157,-0.200},
   						 {-0.299,-0.732,-0.024},
   						 {-0.747,-0.294,-0.159}};
