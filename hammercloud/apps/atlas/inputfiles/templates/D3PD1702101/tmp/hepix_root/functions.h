// HEC fraction

float Analysis::HECF(unsigned int iJet,
                 std::vector<float>* jet_AntiKt4H1Topo_emscale_E,
                 std::vector<float>* jet_AntiKt4H1Topo_e_HEC0,
                 std::vector<float>* jet_AntiKt4H1Topo_e_HEC1,
                 std::vector<float>* jet_AntiKt4H1Topo_e_HEC2,
                 std::vector<float>* jet_AntiKt4H1Topo_e_HEC3)
{
  if (jet_AntiKt4H1Topo_emscale_E->at(iJet) == 0.) return -999.;
  float hecF = (jet_AntiKt4H1Topo_e_HEC0->at(iJet) +
		jet_AntiKt4H1Topo_e_HEC1->at(iJet) +
		jet_AntiKt4H1Topo_e_HEC2->at(iJet) +
		jet_AntiKt4H1Topo_e_HEC3->at(iJet))/jet_AntiKt4H1Topo_emscale_E->at(iJet); 
  return hecF;
}
         

// Tile Gap layer 3 fraction

float Analysis::TileGap3F(unsigned int iJet,
		std::vector<float>* jet_AntiKt4H1Topo_emscale_E,
		std::vector<float>* jet_AntiKt4H1Topo_e_TileGap3)
{
  if (jet_AntiKt4H1Topo_emscale_E->at(iJet) == 0.) return -999.;
  float tileGap3F = jet_AntiKt4H1Topo_e_TileGap3->at(iJet)/jet_AntiKt4H1Topo_emscale_E->at(iJet); 
  return tileGap3F;
}
         

// "bad" jet definition

bool Analysis::IsBad(unsigned int iJet,
	   float hecF,
	   std::vector<float>* jet_AntiKt4H1Topo_n90,
	   std::vector<float>* jet_AntiKt4H1Topo_timing,
	   std::vector<float>* jet_AntiKt4H1Topo_quality,
	   std::vector<float>* jet_AntiKt4H1Topo_emfrac)
{
  if (hecF > 0.8 && jet_AntiKt4H1Topo_n90->at(iJet) <= 5) return true;
  if (jet_AntiKt4H1Topo_emfrac->at(iJet) > 0.95 && 
      fabs(jet_AntiKt4H1Topo_quality->at(iJet)) > 0.8) return true;
  if (fabs(jet_AntiKt4H1Topo_timing->at(iJet)) >= 50.) return true;
  if (hecF >= (1. - fabs(jet_AntiKt4H1Topo_quality->at(iJet)))) return true; 
  return false;
}
   

// "ugly" jet definition

bool Analysis::IsUgly(unsigned int iJet,
	    float tileGap3F,
	    std::vector<float>* jet_AntiKt4H1Topo_BCH_CORR_CELL)
{
  if (jet_AntiKt4H1Topo_BCH_CORR_CELL->at(iJet) > 0.5) return true;
  if (tileGap3F > 0.5) return true;
  return false;
}

//Selected muons (no isolation cut, no overlap removal)
float Analysis::IsSelMuo(unsigned int iMuo){
  
  float MuEta = m_sel->GetValByType<float> ("MUO","_eta", iMuo);
  float Pt  = m_sel->GetValByType<float> ("MUO","_pt", iMuo);       
    
  int isComMuo = m_sel->GetValByType<int> ("MUO","_isCombinedMuon", iMuo);
  int isLowPt  = m_sel->GetValByType<int> ("MUO","_isLowPtReconstructedMuon", iMuo);
  
  if (!(isComMuo || isLowPt)) return -1.;

  // Inner detector track
  int nPixelHits   = m_sel->GetValByType<int> ("MUO","_nPixHits", iMuo);
  int nSCTHits     = m_sel->GetValByType<int> ("MUO","_nSCTHits", iMuo);
  int nTRTHits     = m_sel->GetValByType<int> ("MUO","_nTRTHits", iMuo);
  int nTRTOutliers = m_sel->GetValByType<int> ("MUO","_nTRTOutliers", iMuo);
  int n =  nTRTOutliers +nTRTHits;
      
  if ((nPixelHits < 1) || (nSCTHits < 6)) return -1.;
  
  // below is fabs(pTID-pTMS)/pTID < 0.5 cut --- pt for me and id not in D3PD, have to use qoverp
  float me_qoverp = m_sel->GetValByType<float>("MUO","_me_qoverp_exPV", iMuo);
  float id_qoverp = m_sel->GetValByType<float>("MUO","_id_qoverp_exPV", iMuo);
  float id_theta  = m_sel->GetValByType<float>("MUO","_id_theta_exPV", iMuo);
  float me_theta  = m_sel->GetValByType<float>("MUO","_me_theta_exPV", iMuo);

  if (isComMuo && me_qoverp != 0. && sin(id_theta) != 0. && (fabs(sin(me_theta)/me_qoverp) < 50000.) && (id_qoverp/me_qoverp - 1. <= -0.4)) return -1.;
  
  float trackEta = -log(tan(id_theta/2));
  if (fabs(trackEta) < 1.9 && n <= 5) return -1.;
  if (n > 5 && nTRTOutliers >= 0.9*n) return -1.;
  
  float matchchi2 = m_sel->GetValByType<float>("MUO","_matchchi2", iMuo);

  if (isComMuo && matchchi2 > 150.) return -1.;
  
  // Do this on MC only ! 
  float mypt = Pt;
  
  if ((runNumber <= 150000)||(runNumber >= 200000)){ 
 
 /** Use the MC event number to set seed so that the random numbers are reproducible by different analyzers **/
        float ptcb = mypt;
        float ptid = (id_qoverp != 0.) ? fabs(sin(id_theta)/id_qoverp) : 0.;
        float ptms = (me_qoverp != 0.) ? fabs(sin(me_theta)/me_qoverp) : 0.;
        mcp_smear.SetSeed(eventNumber, iMuo);
        mcp_smear.Event(ptms,ptid,ptcb,MuEta); 
        double pTCB_smeared = mcp_smear.pTCB();
        double pTMS_smeared = mcp_smear.pTMS();
        double pTID_smeared = mcp_smear.pTID(); 
#ifdef MUOSPLUS      
        mcp_smear.PTVar(pTMS_smeared, pTID_smeared, pTCB_smeared, "MSUP");
#endif
#ifdef MUOSMINUS      
        mcp_smear.PTVar(pTMS_smeared, pTID_smeared, pTCB_smeared, "MSLOW");
#endif
  
        if (isComMuo)
          mypt = mcp_smear.pTCB();
        else
          mypt = mcp_smear.pTID();
  
// mypt = mypt; // Overwrite muon pt for later use in analysis
// mypx = mypt*cos(phi); // Used to recompute MEx
// mypy = mypt*sin(phi); // Used to recompute MEy

      }

  if (( fabs(MuEta) >= 2.4 ) || ( mypt <= 20000. )) return -1.;
  
  //cout << "MET: mu "<<iMuo<<" pt "<<mypt<<endl;
  return mypt;
}

//Selected electrons (before overlap removal, passing RobustMedium)
bool Analysis::IsSelEle(unsigned int iEle){
  
  float EleEta = m_sel->GetValByType<float> ("ELE","_cl_eta", iEle);
  float Pt  = m_sel->GetValByType<float> ("ELE","_pt", iEle);       
  //float Phi = m_sel->GetValByType<float> ("ELE","_cl_phi", iEle);       

#ifdef ELESPLUS      
      float scale = 0.03;
      Pt = Pt * (1 + scale);
#endif
#ifdef ELESMINUS      
      float scale = 0.03;
      Pt = Pt * (1 - scale);
#endif
  
  if (( fabs(EleEta) >= 2.47 ) || ( Pt <= 10000. )) return false;

#ifdef ELER      
float cl_e0 = m_sel->GetValByType<float> ("ELE","_cl_E", iEle);
double S=0.1; // sampling term
double C=0.007; // constant
double S_er=0.2; //error on the sampling term
double C_er_B=1; //error on the constant in barrel
double C_er_EC=4.; //error on the constant in EC
double C_er0=C_er_EC;
if(fabs(EleEta)<1.37)C_er0=C_er_B;
double sigma0 = std::sqrt( std::pow(S*(1+S_er)*std::sqrt(cl_e0),2)+ std::pow(C*(1+C_er0)*cl_e0,2)- std::pow(S*std::sqrt(cl_e0),2)- std::pow(C*cl_e0,2));
double DeltaE0 = gRandom->Gaus(0,sigma0);
double cor0=(cl_e0+DeltaE0)/cl_e0;
Pt=Pt*cor0;
#endif

  int author = m_sel->GetValByType<int>("ELE","_author", iEle);
  if (!(author == 1 || author == 3)) return false;

/*   //B-layer          
   float expHitBLayer = ele->GetValue<float>("_expectHitInBLayer");
   int nBLHits = ele->GetValue<int>("_nBLHits");
   if (expHitBLayer ==1. && nBLHits == 0) return false;   */
      
   //isRobustMedium	      
   int isEM    = m_sel->GetValByType<int>("ELE","_isEM", iEle);
   float cl_E  = m_sel->GetValByType<float> ("ELE","_cl_E", iEle);
   float etas2 = m_sel->GetValByType<float> ("ELE","_etas2", iEle);
   float Reta  = m_sel->GetValByType<float> ("ELE","_reta", iEle);
   float w2    = m_sel->GetValByType<float> ("ELE","_weta2", iEle);	   
   float eT    = cl_E / cosh(etas2);

   if (!(isRobustMedium( isEM,  etas2,  eT,  Reta, w2 ))) return false;      
/*
   //float expHitBLayer = ele->GetValue<float>("_expectHitInBLayer");
   //if (!(isRobusterTight( isEM, expHitBLayer, Eta,  eT,  Reta, w2 ))) return false;	   

   //otx veto
   Int_t RunNumber = m_sel->GetScalarVal<Int_t>("RunNumber"); // NO OTX check!
   
   if ((RunNumber <= 150000)||(RunNumber >= 200000)){ 
     RunNumber = 167521; // only for cutflow comparison, use latest OTX map!!
   }

   if (egammaOQ::checkOQClusterElectron(RunNumber, Eta, Phi)==3) return false;
*/   	  
   //isolation
   //float etcone20 = m_sel->GetValByType<float> ("ELE","_Etcone20", iEle);
   //if (etcone20/Pt >= 0.15) return false; // Do not apply this cut for the electrons used in crack veto
   
   return true;
      
}

//use on preselected electrons!!!!
bool Analysis::IsRobusterTight(unsigned int iEle){
  
  float EleEta = m_sel->GetFinValByType<float> ("ELE","_cl_eta", iEle);
  
  int isEM    = m_sel->GetFinValByType<int>("ELE","_isEM", iEle);
  float cl_E  = m_sel->GetFinValByType<float> ("ELE","_cl_E", iEle);
  float etas2 = m_sel->GetFinValByType<float> ("ELE","_etas2", iEle);
  float Reta  = m_sel->GetFinValByType<float> ("ELE","_reta", iEle);
  float w2    = m_sel->GetFinValByType<float> ("ELE","_weta2", iEle);	  
  float eT    = cl_E / cosh(etas2);

  float expHitBLayer = m_sel->GetFinValByType<float>("ELE","_expectHitInBLayer", iEle);
  if (!(isRobusterTight( isEM, expHitBLayer, EleEta,  eT,  Reta, w2 ))) return false;	  
  
  return true;      
}

//use on preselected electrons!!!!
bool Analysis::IsIsolated(unsigned int iEle){
    
  float etcone20 = m_sel->GetFinValByType<float>("ELE", "_Etcone20", iEle);
  float Pt  = m_sel->GetFinValByType<float> ("ELE","_pt", iEle);       
  if (etcone20/Pt >= 0.15) return false; 
  
  return true;      
}
std::string Analysis::getTriggerElectron(int run){

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
  
  cout << "ERROR no defined trigger for run "<< run <<endl;
  return "error, no defined trigger";
}

std::string Analysis::getTriggerMuon(int run){

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
  
  cout << "ERROR no defined trigger for run "<< run <<endl;
  return "error, no defined trigger";
}

Int_t Analysis::CheckGRL(Int_t run, Int_t lb) {

  // Period A+B
  
  if (run==155160) {
    if (lb>=242 && lb<=503) return 1;
    return 0;
  }
  if (run==155116) {
    if (lb>=9 && lb<=26) return 1;
    if (lb>=28 && lb<=44) return 1;
    if (lb>=46 && lb<=54) return 1;
    if (lb>=61 && lb<=93) return 1;
    return 0;
  }
  if (run==155112) {
    if (lb>=127 && lb<=166) return 1;
    if (lb>=186 && lb<=215) return 1;
    if (lb>=217 && lb<=322) return 1;
    if (lb>=324 && lb<=493) return 1;
    if (lb>=495 && lb<=592) return 1;
    if (lb>=594 && lb<=609) return 1;
    if (lb>=612 && lb<=625) return 1;
    return 0;
  }
  if (run==155073) {
    if (lb>=88 && lb<=200) return 1;
    if (lb>=202 && lb<=247) return 1;
    if (lb>=249 && lb<=272) return 1;
    if (lb>=274 && lb<=394) return 1;
    if (lb>=397 && lb<=407) return 1;
    return 0;
  }
  if (run==154817) {
    if (lb>=9 && lb<=287) return 1;
    return 0;
  }
  if (run==154815) {
    if (lb>=9 && lb<=38) return 1;
    return 0;
  }
  if (run==154813) {
    if (lb>=8 && lb<=17) return 1;
    if (lb>=83 && lb<=187) return 1;
    return 0;
  }
  if (run==154810) {
    if (lb>=159 && lb<=220) return 1;
    return 0;
  }
  if (run==153565) {
    if (lb>=258 && lb<=269) return 1;
    if (lb>=281 && lb<=305) return 1;
    if (lb>=311 && lb<=355) return 1;
    if (lb>=361 && lb<=400) return 1;
    if (lb>=406 && lb<=410) return 1;
    if (lb>=416 && lb<=825) return 1;
    if (lb>=831 && lb<=953) return 1;
    return 0;
  }
  if (run==153159) {
    if (lb>=88 && lb<=104) return 1;
    if (lb>=126 && lb<=176) return 1;
    return 0;
  }
  if (run==153030) {
    if (lb>=120 && lb<=135) return 1;
    if (lb>=141 && lb<=164) return 1;
    if (lb>=186 && lb<=202) return 1;
    return 0;
  }
  if (run==152994) {
    if (lb>=294 && lb<=352) return 1;
    return 0;
  }
  if (run==152933) {
    if (lb>=46 && lb<=172) return 1;
    return 0;
  }
  if (run==152878) {
    if (lb>=100 && lb<=159) return 1;
    if (lb>=191 && lb<=213) return 1;
    return 0;
  }
  if (run==152845) {
    if (lb>=111 && lb<=134) return 1;
    if (lb>=145 && lb<=169) return 1;
    if (lb>=186 && lb<=349) return 1;
    return 0;
  }
  if (run==152844) {
    if (lb>=195 && lb<=233) return 1;
    return 0;
  }
  if (run==152777) {
    if (lb>=81 && lb<=299) return 1;
    if (lb>=321 && lb<=329) return 1;
    return 0;
  }
  if (run==152508) {
    if (lb>=196 && lb<=204) return 1;
    if (lb>=241 && lb<=261) return 1;
    return 0;
  }
  if (run==152441) {
    if (lb>=317 && lb<=370) return 1;
    if (lb>=372 && lb<=405) return 1;
    if (lb>=411 && lb<=671) return 1;
    return 0;
  }
  if (run==152409) {
    if (lb>=128 && lb<=209) return 1;
    if (lb>=286 && lb<=716) return 1;
    return 0;
  }
  if (run==152345) {
    if (lb>=128 && lb<=207) return 1;
    return 0;
  }
  if (run==152221) {
    if (lb>=5 && lb<=167) return 1;
    return 0;
  }
  if (run==152214) {
    if (lb>=159 && lb<=201) return 1;
    return 0;
  }
  if (run==152166) {
    if (lb>=254 && lb<=300) return 1;
    return 0;
  }

  // Period C
  
  if (run==156682) {
    if (lb>=406 && lb<=475) return 1;
    if (lb>=477 && lb<=507) return 1;
    if (lb>=509 && lb<=512) return 1;
    return 0;
  }
  if (run==155697) {
    if (lb>=264 && lb<=266) return 1;
    if (lb>=268 && lb<=334) return 1;
    if (lb>=336 && lb<=352) return 1;
    if (lb>=354 && lb<=506) return 1;
    return 0;
  }
  if (run==155678) {
    if (lb>=241 && lb<=308) return 1;
    return 0;
  }
  if (run==155669) {
    if (lb>=264 && lb<=311) return 1;
    return 0;
  }
  if (run==155634) {
    if (lb>=147 && lb<=147) return 1;
    if (lb>=149 && lb<=333) return 1;
    return 0;
  }
  if (run==155569) {
    if (lb>=228 && lb<=467) return 1;
    return 0;
  }
  if (run==155280) {
    if (lb>=360 && lb<=375) return 1;
    return 0;
  }
  if (run==155228) {
    if (lb>=133 && lb<=148) return 1;
    return 0;
  }
  
  //period D
  
  if (run==159224) {
    if (lb>=249 && lb <=278) return 1;
    if (lb>=280 && lb <=282) return 1;
    if (lb>=284 && lb <=298) return 1;
    if (lb>=300 && lb <=368) return 1;
    if (lb>=370 && lb <=385) return 1;
    if (lb>=388 && lb <=412) return 1;
    if (lb>=416 && lb <=423) return 1;
    if (lb>=425 && lb <=430) return 1;
    if (lb>=448 && lb <=537) return 1;
    if (lb>=539 && lb <=612) return 1;
    if (lb>=614 && lb <=666) return 1;
    if (lb>=668 && lb <=773) return 1;
    if (lb>=775 && lb <=796) return 1;
    if (lb>=798 && lb <=813) return 1;
    return 0;
  }

  if (run==159203) {
    if (lb>=3 && lb <=58) return 1;
    if (lb>=60 && lb <=82) return 1;
    return 0;
  }

  if (run==159202) {
    if (lb>=187 && lb <=203) return 1;
    if (lb>=205 && lb <=225) return 1;
    if (lb>=227 && lb <=269) return 1;
    return 0;
  }

  if (run==159179) {
    if (lb>=222 && lb <=223) return 1;
    if (lb>=225 && lb <=251) return 1;
    if (lb>=253 && lb <=282) return 1;
    if (lb>=284 && lb <=306) return 1;
    if (lb>=308 && lb <=312) return 1;
    if (lb>=314 && lb <=334) return 1;
    return 0;
  }

  if (run==159113) {
    if (lb>=261 && lb <=276) return 1;
    if (lb>=278 && lb <=384) return 1;
    if (lb>=386 && lb <=476) return 1;
    if (lb>=478 && lb <=519) return 1;
    return 0;
  }

  if (run==159086) {
    if (lb>=117 && lb <=140) return 1;
    if (lb>=142 && lb <=165) return 1;
    if (lb>=167 && lb <=168) return 1;
    if (lb>=179 && lb <=207) return 1;
    if (lb>=209 && lb <=227) return 1;
    if (lb>=235 && lb <=250) return 1;
    if (lb>=252 && lb <=252) return 1;
    if (lb>=254 && lb <=285) return 1;
    if (lb>=287 && lb <=313) return 1;
    if (lb>=315 && lb <=324) return 1;
    if (lb>=326 && lb <=362) return 1;
    if (lb>=364 && lb <=406) return 1;
    if (lb>=408 && lb <=421) return 1;
    if (lb>=423 && lb <=456) return 1;
    if (lb>=458 && lb <=480) return 1;
    if (lb>=486 && lb <=490) return 1;
    if (lb>=492 && lb <=515) return 1;
    if (lb>=522 && lb <=556) return 1;
    return 0;
  }

  if (run==159041) {
    if (lb>=106 && lb <=117) return 1;
    if (lb>=119 && lb <=143) return 1;
    if (lb>=164 && lb <=196) return 1;
    if (lb>=198 && lb <=200) return 1;
    if (lb>=202 && lb <=207) return 1;
    if (lb>=209 && lb <=238) return 1;
    if (lb>=240 && lb <=240) return 1;
    if (lb>=242 && lb <=244) return 1;
    if (lb>=246 && lb <=247) return 1;
    if (lb>=249 && lb <=377) return 1;
    if (lb>=379 && lb <=379) return 1;
    if (lb>=381 && lb <=392) return 1;
    return 0;
  }

  if (run==158975) {
    if (lb>=105 && lb <=157) return 1;
    if (lb>=159 && lb <=161) return 1;
    if (lb>=164 && lb <=220) return 1;
    if (lb>=222 && lb <=234) return 1;
    if (lb>=237 && lb <=244) return 1;
    if (lb>=253 && lb <=276) return 1;
    if (lb>=278 && lb <=282) return 1;
    if (lb>=315 && lb <=335) return 1;
    if (lb>=337 && lb <=352) return 1;
    return 0;
  }

  if (run==158801) {
    if (lb>=135 && lb <=311) return 1;
    return 0;
  }

  if (run==158632) {
    if (lb>=163 && lb <=166) return 1;
    if (lb>=168 && lb <=178) return 1;
    if (lb>=182 && lb <=205) return 1;
    if (lb>=207 && lb <=210) return 1;
    if (lb>=212 && lb <=252) return 1;
    if (lb>=254 && lb <=262) return 1;
    if (lb>=264 && lb <=268) return 1;
    if (lb>=270 && lb <=272) return 1;
    return 0;
  }

  if (run==158582) {
    if (lb>=56 && lb <=64) return 1;
    if (lb>=66 && lb <=74) return 1;
    if (lb>=77 && lb <=81) return 1;
    if (lb>=83 && lb <=148) return 1;
    if (lb>=150 && lb <=203) return 1;
    if (lb>=205 && lb <=300) return 1;
    if (lb>=303 && lb <=341) return 1;
    if (lb>=343 && lb <=355) return 1;
    if (lb>=357 && lb <=360) return 1;
    if (lb>=362 && lb <=372) return 1;
    return 0;
  }

  if (run==158548) {
    if (lb>=111 && lb <=111) return 1;
    if (lb>=113 && lb <=115) return 1;
    if (lb>=117 && lb <=117) return 1;
    if (lb>=119 && lb <=126) return 1;
    if (lb>=128 && lb <=140) return 1;
    if (lb>=142 && lb <=147) return 1;
    if (lb>=149 && lb <=163) return 1;
    if (lb>=165 && lb <=177) return 1;
    if (lb>=179 && lb <=196) return 1;
    if (lb>=198 && lb <=228) return 1;
    if (lb>=230 && lb <=245) return 1;
    if (lb>=247 && lb <=249) return 1;
    if (lb>=251 && lb <=257) return 1;
    if (lb>=260 && lb <=275) return 1;
    if (lb>=277 && lb <=285) return 1;
    if (lb>=287 && lb <=294) return 1;
    if (lb>=296 && lb <=303) return 1;
    return 0;
  }

  if (run==158545) {
    if (lb>=237 && lb <=237) return 1;
    if (lb>=239 && lb <=255) return 1;
    if (lb>=257 && lb <=261) return 1;
    return 0;
  }

  if (run==158466) {
    if (lb>=265 && lb <=268) return 1;
    if (lb>=273 && lb <=277) return 1;
    return 0;
  }

  if (run==158443) {
    if (lb>=210 && lb <=213) return 1;
    if (lb>=216 && lb <=230) return 1;
    return 0;
  }

  if (run==158392) {
    if (lb>=218 && lb <=224) return 1;
    if (lb>=236 && lb <=243) return 1;
    if (lb>=247 && lb <=281) return 1;
    if (lb>=283 && lb <=325) return 1;
    if (lb>=337 && lb <=340) return 1;
    if (lb>=358 && lb <=358) return 1;
    if (lb>=367 && lb <=434) return 1;
    if (lb>=440 && lb <=447) return 1;
    return 0;
  }

  if (run==158299) {
    if (lb>=378 && lb <=395) return 1;
    if (lb>=402 && lb <=434) return 1;
    return 0;
  }

  if (run==158269) {
    if (lb>=6 && lb <=41) return 1;
    if (lb>=43 && lb <=45) return 1;
    if (lb>=47 && lb <=59) return 1;
    if (lb>=68 && lb <=76) return 1;
    if (lb>=78 && lb <=80) return 1;
    return 0;
  }

  if (run==158116) {
    if (lb>=121 && lb <=138) return 1;
    if (lb>=140 && lb <=155) return 1;
    if (lb>=161 && lb <=165) return 1;
    if (lb>=167 && lb <=169) return 1;
    if (lb>=185 && lb <=189) return 1;
    if (lb>=191 && lb <=231) return 1;
    if (lb>=233 && lb <=260) return 1;
    if (lb>=262 && lb <=264) return 1;
    if (lb>=266 && lb <=268) return 1;
    if (lb>=270 && lb <=290) return 1;
    if (lb>=331 && lb <=356) return 1;
    if (lb>=358 && lb <=552) return 1;
    if (lb>=554 && lb <=554) return 1;
    return 0;
  }

  if (run==158045) {
    if (lb>=117 && lb <=177) return 1;
    return 0;
  }  

  //period E
  
  if (run==161948){
    if (lb>=349 && lb <=410) return 1;
    if (lb>=412 && lb <=495) return 1;
    if (lb>=502 && lb <=701) return 1;
    return 0;
}

  if (run==161562) {
    if (lb>=41 && lb <=259) return 1;
    return 0;
}

  if (run==161520) {
    if (lb>=136 && lb <=463) return 1;
    if (lb>=465 && lb <=467) return 1;
    if (lb>=479 && lb <=498) return 1;
    return 0;
}

  if (run==161407) {
    if (lb>=75 && lb <=139) return 1;
    if (lb>=141 && lb <=164) return 1;
    if (lb>=166 && lb <=175) return 1;
    return 0;
}

  if (run==161379) {
    if (lb>=118 && lb <=140) return 1;
    if (lb>=143 && lb <=147) return 1;
    if (lb>=154 && lb <=267) return 1;
    if (lb>=269 && lb <=292) return 1;
    if (lb>=294 && lb <=306) return 1;
    if (lb>=308 && lb <=308) return 1;
    if (lb>=324 && lb <=423) return 1;
    if (lb>=425 && lb <=500) return 1;
    return 0;
}

  if (run==161118) {
    if (lb>=7 && lb <=103) return 1;
    return 0;
}

  if (run==160980) {
    if (lb>=10 && lb <=39) return 1;
    return 0;
}

  if (run==160975) {
    if (lb>=85 && lb <=98) return 1;
    return 0;
}

  if (run==160963) {
    if (lb>=3 && lb <=15) return 1;
    return 0;
}

  if (run==160958) {
    if (lb>=3 && lb <=10) return 1;
    if (lb>=12 && lb <=12) return 1;
    if (lb>=14 && lb <=26) return 1;
    if (lb>=135 && lb <=177) return 1;
    if (lb>=191 && lb <=214) return 1;
    return 0;
}

  if (run==160954) {
    if (lb>=111 && lb <=129) return 1;
    if (lb>=131 && lb <=133) return 1;
    if (lb>=135 && lb <=136) return 1;
    return 0;
}

  if (run==160953) {
    if (lb>=202 && lb <=205) return 1;
    if (lb>=208 && lb <=210) return 1;
    if (lb>=214 && lb <=253) return 1;
    if (lb>=255 && lb <=260) return 1;
    return 0;
}

  if (run==160899) {
    if (lb>=114 && lb <=128) return 1;
    return 0;
}

  if (run==160879) {
    if (lb>=113 && lb <=184) return 1;
    if (lb>=194 && lb <=254) return 1;
    if (lb>=267 && lb <=268) return 1;
    if (lb>=290 && lb <=563) return 1;
    return 0;
}

  if (run==160801) {
    if (lb>=3 && lb <=29) return 1;
    if (lb>=31 && lb <=96) return 1;
    if (lb>=98 && lb <=105) return 1;
    if (lb>=112 && lb <=112) return 1;
    if (lb>=167 && lb <=274) return 1;
    return 0;
}

  if (run==160800) {
    if (lb>=3 && lb <=24) return 1;
    if (lb>=37 && lb <=37) return 1;
    if (lb>=40 && lb <=41) return 1;
    return 0;
}

  if (run==160736) {
    if (lb>=206 && lb <=263) return 1;
    return 0;
}

  if (run==160613) {
    if (lb>=109 && lb <=125) return 1;
    if (lb>=127 && lb <=179) return 1;
    if (lb>=194 && lb <=226) return 1;
    if (lb>=238 && lb <=269) return 1;
    if (lb>=272 && lb <=322) return 1;
    return 0;
}

  if (run==160530) {
    if (lb>=188 && lb <=201) return 1;
    if (lb>=203 && lb <=297) return 1;
    if (lb>=301 && lb <=358) return 1;
    if (lb>=372 && lb <=460) return 1;
    if (lb>=466 && lb <=625) return 1;
    return 0;
}

  if (run==160479) {
    if (lb>=296 && lb <=320) return 1;
    return 0;
}

  if (run==160472) {
    if (lb>=140 && lb <=177) return 1;
    if (lb>=179 && lb <=186) return 1;
    if (lb>=188 && lb <=196) return 1;
    if (lb>=198 && lb <=205) return 1;
    if (lb>=207 && lb <=254) return 1;
    if (lb>=256 && lb <=325) return 1;
    if (lb>=337 && lb <=380) return 1;
    if (lb>=382 && lb <=521) return 1;
    return 0;  
}    
  if (run==160387) { 
    if (lb>=155 && lb <=158) return 1;
    if (lb>=160 && lb <=173) return 1;
    if (lb>=175 && lb <=293) return 1;
    if (lb>=295 && lb <=306) return 1;
    if (lb>=308 && lb <=336) return 1;
    if (lb>=338 && lb <=381) return 1;
    if (lb>=383 && lb <=394) return 1;
    return 0;
}

// period F

  if (run==162882) {
    if (lb>=122 && lb <=126) return 1;
    if (lb>=128 && lb <=148) return 1;
    if (lb>=150 && lb <=172) return 1;
    if (lb>=174 && lb <=176) return 1;
    if (lb>=178 && lb <=180) return 1;
    if (lb>=232 && lb <=289) return 1;
    if (lb>=291 && lb <=330) return 1;
    if (lb>=332 && lb <=392) return 1;
    if (lb>=394 && lb <=448) return 1;
    return 0;
}

  if (run==162843) {
    if (lb>=114 && lb <=137) return 1;
    if (lb>=139 && lb <=161) return 1;
    if (lb>=163 && lb <=163) return 1;
    if (lb>=165 && lb <=165) return 1;
    if (lb>=167 && lb <=210) return 1;
    if (lb>=212 && lb <=254) return 1;
    if (lb>=256 && lb <=258) return 1;
    if (lb>=260 && lb <=263) return 1;
    if (lb>=278 && lb <=288) return 1;
    if (lb>=290 && lb <=333) return 1;
    if (lb>=335 && lb <=409) return 1;
    if (lb>=411 && lb <=448) return 1;
    if (lb>=450 && lb <=462) return 1;
    if (lb>=464 && lb <=517) return 1;
    return 0;
}

  if (run==162764) {
    if (lb>=138 && lb <=141) return 1;
    if (lb>=143 && lb <=146) return 1;
    if (lb>=148 && lb <=163) return 1;
    if (lb>=165 && lb <=172) return 1;
    if (lb>=194 && lb <=237) return 1;
    return 0;
}

  if (run==162690) {
    if (lb>=264 && lb <=273) return 1;
    if (lb>=276 && lb <=276) return 1;
    if (lb>=278 && lb <=285) return 1;
    if (lb>=287 && lb <=288) return 1;
    if (lb>=290 && lb <=310) return 1;
    if (lb>=313 && lb <=325) return 1;
    if (lb>=342 && lb <=344) return 1;
    if (lb>=346 && lb <=347) return 1;
    if (lb>=349 && lb <=349) return 1;
    if (lb>=351 && lb <=399) return 1;
    if (lb>=401 && lb <=403) return 1;
    if (lb>=405 && lb <=406) return 1;
    if (lb>=415 && lb <=418) return 1;
    if (lb>=429 && lb <=469) return 1;
    if (lb>=471 && lb <=573) return 1;
    if (lb>=575 && lb <=617) return 1;
    if (lb>=620 && lb <=630) return 1;
    if (lb>=632 && lb <=634) return 1;
    if (lb>=636 && lb <=642) return 1;
    return 0;
}

  if (run==162623) {
    if (lb>=4 && lb <=75) return 1;
    if (lb>=83 && lb <=113) return 1;
    if (lb>=115 && lb <=135) return 1;
    if (lb>=137 && lb <=154) return 1;
    if (lb>=156 && lb <=191) return 1;
    if (lb>=193 && lb <=198) return 1;
    if (lb>=200 && lb <=263) return 1;
    if (lb>=265 && lb <=273) return 1;
    if (lb>=275 && lb <=281) return 1;
    if (lb>=283 && lb <=315) return 1;
    if (lb>=317 && lb <=338) return 1;
    return 0;
}

  if (run==162620) {
    if (lb>=166 && lb <=185) return 1;
    if (lb>=187 && lb <=191) return 1;
    if (lb>=193 && lb <=203) return 1;
    if (lb>=225 && lb <=226) return 1;
    if (lb>=228 && lb <=234) return 1;
    return 0;
}

  if (run==162577) {
    if (lb>=4 && lb <=12) return 1;
    return 0;
}

  if (run==162576) {
    if (lb>=3 && lb <=10) return 1;
    if (lb>=12 && lb <=14) return 1;
    if (lb>=30 && lb <=65) return 1;
    return 0;
}

  if (run==162526) {
    if (lb>=118 && lb <=123) return 1;
    if (lb>=125 && lb <=128) return 1;
    if (lb>=130 && lb <=130) return 1;
    if (lb>=143 && lb <=148) return 1;
    if (lb>=150 && lb <=189) return 1;
    if (lb>=191 && lb <=320) return 1;
    if (lb>=322 && lb <=366) return 1;
    if (lb>=371 && lb <=381) return 1;
    if (lb>=383 && lb <=386) return 1;
    if (lb>=391 && lb <=399) return 1;
    if (lb>=401 && lb <=403) return 1;
    if (lb>=405 && lb <=427) return 1;
    if (lb>=432 && lb <=439) return 1;
    if (lb>=441 && lb <=501) return 1;
    return 0;
}

  if (run==162347) {
    if (lb>=119 && lb <=192) return 1;
    if (lb>=195 && lb <=199) return 1;
    if (lb>=205 && lb <=275) return 1;
    if (lb>=277 && lb <=280) return 1;
    if (lb>=290 && lb <=301) return 1;
    if (lb>=303 && lb <=350) return 1;
    if (lb>=352 && lb <=488) return 1;
    if (lb>=490 && lb <=546) return 1;
    return 0;
}
// G1-G5
  if (run==165591) {
    if (lb>=73 && lb <=87) return 1;      
    if (lb>=89 && lb <=135) return 1;
    if (lb>=147 && lb <=184) return 1;
    if (lb>=187 && lb <=207) return 1;
    if (lb>=210 && lb <=210) return 1;      
    if (lb>=212 && lb <=216) return 1;
    if (lb>=219 && lb <=289) return 1;
    if (lb>=291 && lb <=383) return 1;
    if (lb>=385 && lb <=389) return 1;      
    if (lb>=391 && lb <=392) return 1;
    if (lb>=394 && lb <=401) return 1;
    if (lb>=403 && lb <=410) return 1;
    if (lb>=412 && lb <=433) return 1;      
    if (lb>=435 && lb <=466) return 1;
    return 0;
} 

  if (run==165632) {
    if (lb>=186 && lb <=187) return 1;      
    if (lb>=191 && lb <=198) return 1;
    if (lb>=200 && lb <=200) return 1;
    if (lb>=202 && lb <=213) return 1;
    if (lb>=215 && lb <=222) return 1;      
    if (lb>=224 && lb <=234) return 1;
    if (lb>=236 && lb <=251) return 1;
    if (lb>=253 && lb <=253) return 1;
    if (lb>=255 && lb <=271) return 1;      
    if (lb>=273 && lb <=278) return 1;
    if (lb>=280 && lb <=280) return 1;
    if (lb>=282 && lb <=283) return 1;
    if (lb>=285 && lb <=289) return 1;      
    if (lb>=291 && lb <=304) return 1;
    if (lb>=306 && lb <=307) return 1;
    if (lb>=309 && lb <=321) return 1;
    if (lb>=323 && lb <=329) return 1;      
    if (lb>=331 && lb <=335) return 1;
    if (lb>=338 && lb <=372) return 1;
    if (lb>=374 && lb <=392) return 1;
    if (lb>=394 && lb <=399) return 1;      
    if (lb>=414 && lb <=436) return 1;
    if (lb>=438 && lb <=440) return 1;
    if (lb>=442 && lb <=468) return 1;
    if (lb>=470 && lb <=471) return 1;      
    if (lb>=473 && lb <=473) return 1;
    if (lb>=476 && lb <=480) return 1;
    if (lb>=482 && lb <=532) return 1;
    if (lb>=534 && lb <=554) return 1;      
    if (lb>=556 && lb <=557) return 1;
    if (lb>=559 && lb <=563) return 1;
    if (lb>=576 && lb <=607) return 1;
    return 0;
}

  if (run==165703) {
    if (lb>=105 && lb <=146) return 1;
    return 0;
}

  if (run==165732) {
    if (lb>=91 && lb <=97) return 1;      
    if (lb>=99 && lb <=100) return 1;
    if (lb>=102 && lb <=102) return 1;
    if (lb>=116 && lb <=123) return 1;
    if (lb>=125 && lb <=125) return 1;      
    if (lb>=127 && lb <=128) return 1;
    if (lb>=130 && lb <=130) return 1;
    if (lb>=132 && lb <=134) return 1;
    if (lb>=136 && lb <=138) return 1;      
    if (lb>=140 && lb <=144) return 1;
    if (lb>=146 && lb <=146) return 1;
    if (lb>=148 && lb <=155) return 1;
    if (lb>=161 && lb <=163) return 1;      
    if (lb>=165 && lb <=187) return 1;
    if (lb>=189 && lb <=192) return 1;
    if (lb>=194 && lb <=196) return 1;
    if (lb>=198 && lb <=205) return 1;      
    if (lb>=207 && lb <=210) return 1;
    if (lb>=212 && lb <=214) return 1;
    if (lb>=228 && lb <=265) return 1;
    if (lb>=268 && lb <=289) return 1;      
    if (lb>=297 && lb <=302) return 1;
    if (lb>=304 && lb <=336) return 1;
    if (lb>=338 && lb <=340) return 1;
    if (lb>=342 && lb <=356) return 1;      
    if (lb>=358 && lb <=391) return 1;
    if (lb>=393 && lb <=401) return 1;
    if (lb>=408 && lb <=416) return 1;
    if (lb>=418 && lb <=422) return 1;      
    if (lb>=424 && lb <=430) return 1;
    if (lb>=432 && lb <=444) return 1;
    if (lb>=446 && lb <=499) return 1;
    if (lb>=549 && lb <=564) return 1;
    return 0;
}

  if (run==165767) {
    if (lb>=210 && lb <=220) return 1;      
    if (lb>=222 && lb <=225) return 1;
    if (lb>=227 && lb <=233) return 1;
    if (lb>=236 && lb <=249) return 1;
    if (lb>=251 && lb <=255) return 1;      
    if (lb>=257 && lb <=269) return 1;
    if (lb>=272 && lb <=275) return 1;
    if (lb>=280 && lb <=286) return 1;
    if (lb>=295 && lb <=303) return 1;      
    if (lb>=305 && lb <=307) return 1;
    if (lb>=309 && lb <=309) return 1;
    if (lb>=311 && lb <=316) return 1;
    if (lb>=319 && lb <=320) return 1;
    if (lb>=326 && lb <=329) return 1;      
    if (lb>=331 && lb <=340) return 1;
    if (lb>=346 && lb <=351) return 1;
    if (lb>=353 && lb <=381) return 1;
    if (lb>=383 && lb <=422) return 1;      
    if (lb>=424 && lb <=431) return 1;
    if (lb>=433 && lb <=486) return 1;
    if (lb>=488 && lb <=489) return 1;
    if (lb>=491 && lb <=500) return 1;      
    if (lb>=502 && lb <=519) return 1;
    if (lb>=521 && lb <=533) return 1;
    if (lb>=535 && lb <=574) return 1;
    return 0;
}

  if (run==165815) {
    if (lb>= 123&& lb <=128) return 1;
    if (lb>= 130&& lb <=134) return 1;  
    if (lb>= 136&& lb <=139) return 1;  
    if (lb>= 141&& lb <=141) return 1;  
    if (lb>= 143&& lb <=147) return 1;      
    if (lb>= 149&& lb <=150) return 1;
    if (lb>= 153&& lb <=153) return 1;
    if (lb>= 155&& lb <=161) return 1;
    if (lb>= 163&& lb <=165) return 1;
    return 0;
}

  if (run==165817) {
    if (lb>= 3&& lb <=3) return 1;
    if (lb>= 5&& lb <=5) return 1;
    return 0;
}

  if (run==165818) {
    if (lb>= 3&& lb <=3) return 1;      
    if (lb>= 18&& lb <=34) return 1;
    if (lb>= 46&& lb <=65) return 1;
    if (lb>= 68&& lb <=73) return 1;
    if (lb>= 75&& lb <=80) return 1;      
    if (lb>= 82&& lb <=94) return 1;
    return 0;
}

  if (run==165821) {
    if (lb>=3 && lb <=21) return 1;      
    if (lb>=23 && lb <=30) return 1;      
    if (lb>=42 && lb <=63) return 1;      
    if (lb>=65 && lb <=76) return 1;      
    if (lb>=78 && lb <=82) return 1;      
    if (lb>=84 && lb <=89) return 1;      
    return 0;
}

  if (run==165954) {
    if (lb>=121 && lb <=124) return 1;      
    if (lb>=126 && lb <=130) return 1;      
    if (lb>=132 && lb <=138) return 1;      
    if (lb>=140 && lb <=142) return 1;      
    if (lb>=144 && lb <=145) return 1;      
    if (lb>=147 && lb <=153) return 1;      
    if (lb>=155 && lb <=155) return 1;      
    if (lb>=158 && lb <=164) return 1;      
    return 0;
}

  if (run==165956) {
    if (lb>=4 && lb <=6) return 1;      
    if (lb>=8 && lb <=11) return 1;      
    if (lb>=13 && lb <=23) return 1;      
    return 0;
}

  if (run==166097) {
    if (lb>=150 && lb <=164) return 1;      
    if (lb>=166 && lb <=169) return 1;      
    if (lb>=171 && lb <=173) return 1;      
    if (lb>=185 && lb <=185) return 1;      
    if (lb>=187 && lb <=187) return 1;      
    if (lb>=189 && lb <=196) return 1;      
    if (lb>=198 && lb <=201) return 1;      
    if (lb>=203 && lb <=214) return 1;      
    return 0;
}

  if (run==166142) {
    if (lb>=136 && lb <=141) return 1;      
    if (lb>=143 && lb <=146) return 1;      
    if (lb>=148 && lb <=151) return 1;      
    if (lb>=153 && lb <=153) return 1;      
    if (lb>=155 && lb <=162) return 1;      
    if (lb>=164 && lb <=168) return 1;      
    if (lb>=170 && lb <=171) return 1;      
    if (lb>=174 && lb <=176) return 1;      
    if (lb>=183 && lb <=184) return 1;      
    if (lb>=186 && lb <=193) return 1;      
    if (lb>=196 && lb <=219) return 1;      
    if (lb>=221 && lb <=221) return 1;      
    if (lb>=223 && lb <=234) return 1;      
    if (lb>=236 && lb <=262) return 1;      
    if (lb>=264 && lb <=277) return 1;      
    if (lb>=279 && lb <=285) return 1;      
    if (lb>=288 && lb <=295) return 1;      
    return 0;
}

  if (run==166143) {
    if (lb>=4 && lb <=48) return 1;      
    if (lb>=50 && lb <=52) return 1;      
    if (lb>=54 && lb <=62) return 1;      
    return 0;
}
  if (run==166198) {
    if (lb>=93 && lb <=95) return 1;      
    if (lb>=118 && lb <=125) return 1;      
    if (lb>=131 && lb <=133) return 1;      
    if (lb>=135 && lb <=136) return 1;      
    if (lb>=146 && lb <=157) return 1;      
    if (lb>=291 && lb <=296) return 1;      
    if (lb>=298 && lb <=299) return 1;      
    if (lb>=301 && lb <=309) return 1;      
    if (lb>=311 && lb <=352) return 1;      
    if (lb>=363 && lb <=370) return 1;      
    if (lb>=376 && lb <=426) return 1;      
    if (lb>=428 && lb <=429) return 1;      
    if (lb>=438 && lb <=466) return 1;      
    if (lb>=468 && lb <=499) return 1;      
    if (lb>=501 && lb <=510) return 1;      
    if (lb>=513 && lb <=520) return 1;      
    return 0;
  }
// period H
  if (run==166964) {
    if (lb>=319 && lb <=322) return 1;   
    if (lb>=326 && lb <=327) return 1;  
    if (lb>=329 && lb <=333) return 1;  
    return 0;
}
  if (run==166927) {
    if (lb>=7 && lb <=11) return 1;
    if (lb>=13 && lb <=19) return 1;
    if (lb>=21 && lb <=63) return 1;
    if (lb>=65 && lb <=74) return 1;
    if (lb>=76 && lb <=93) return 1;
    if (lb>=95 && lb <=102) return 1;
    return 0;
}
  if (run==166924) {
    if (lb>=51 && lb <=51) return 1;
    if (lb>=53 && lb <=60) return 1;
    if (lb>=62 && lb <=86) return 1;
    if (lb>=88 && lb <=117) return 1;
    if (lb>=119 && lb <=154) return 1;
    if (lb>=156 && lb <=176) return 1;
    if (lb>=178 && lb <=200) return 1;
    return 0;
}
  if (run==166856) {
    if (lb>=142 && lb <=142) return 1;
    if (lb>=144 && lb <=145) return 1;
    if (lb>=147 && lb <=155) return 1;
    if (lb>=157 && lb <=158) return 1;
    if (lb>=160 && lb <=164) return 1;
    return 0;
}
  if (run==166850) {
    if (lb>=146 && lb <=190) return 1;
    if (lb>=226 && lb <=250) return 1;
    if (lb>=266 && lb <=270) return 1;
    if (lb>=272 && lb <=310) return 1;
    return 0;
}
  if (run==166786) {
    if (lb>=267 && lb <=267) return 1;
    if (lb>=269 && lb <=276) return 1;
    if (lb>=279 && lb <=279) return 1;
    if (lb>=281 && lb <=281) return 1;
    if (lb>=283 && lb <=286) return 1;
    if (lb>=288 && lb <=288) return 1;
    if (lb>=290 && lb <=310) return 1;
    if (lb>=316 && lb <=316) return 1;
    if (lb>=326 && lb <=334) return 1;
    if (lb>=336 && lb <=339) return 1;
    if (lb>=359 && lb <=371) return 1;
    if (lb>=373 && lb <=373) return 1;
    if (lb>=375 && lb <=378) return 1;
    if (lb>=380 && lb <=430) return 1;
    if (lb>=432 && lb <=476) return 1;
    if (lb>=478 && lb <=487) return 1;
    if (lb>=490 && lb <=516) return 1;
    if (lb>=528 && lb <=528) return 1;
    if (lb>=530 && lb <=536) return 1;
    if (lb>=538 && lb <=540) return 1;
    return 0;
}
  if (run==166658) {
    if (lb>=144 && lb <=155) return 1;
    if (lb>=162 && lb <=163) return 1;
    if (lb>=165 && lb <=176) return 1;
    if (lb>=179 && lb <=181) return 1;
    if (lb>=183 && lb <=203) return 1;
    if (lb>=207 && lb <=207) return 1;
    if (lb>=209 && lb <=231) return 1;
    if (lb>=233 && lb <=236) return 1;
    if (lb>=238 && lb <=256) return 1;
    if (lb>=258 && lb <=263) return 1;
    if (lb>=267 && lb <=270) return 1;
    if (lb>=272 && lb <=275) return 1;
    if (lb>=281 && lb <=284) return 1;
    if (lb>=286 && lb <=288) return 1;
    if (lb>=290 && lb <=304) return 1;
    if (lb>=314 && lb <=319) return 1;
    if (lb>=321 && lb <=323) return 1;
    if (lb>=325 && lb <=334) return 1;
    if (lb>=337 && lb <=353) return 1;
    if (lb>=355 && lb <=363) return 1;
    if (lb>=365 && lb <=383) return 1;
    if (lb>=385 && lb <=385) return 1;
    if (lb>=387 && lb <=414) return 1;
    if (lb>=416 && lb <=429) return 1;
    return 0;
}
  if (run==166466) {
    if (lb>=81 && lb <=81) return 1;
    if (lb>=83 && lb <=95) return 1;
    if (lb>=118 && lb <=120) return 1;
    if (lb>=126 && lb <=138) return 1;
    if (lb>=141 && lb <=145) return 1;
    if (lb>=147 && lb <=159) return 1;
    if (lb>=163 && lb <=163) return 1;
    if (lb>=165 && lb <=181) return 1;
    if (lb>=184 && lb <=189) return 1;
    if (lb>=191 && lb <=213) return 1;
    if (lb>=215 && lb <=215) return 1;
    if (lb>=217 && lb <=244) return 1;
    if (lb>=247 && lb <=247) return 1;
    if (lb>=249 && lb <=252) return 1;
    if (lb>=256 && lb <=257) return 1;
    if (lb>=259 && lb <=269) return 1;
    if (lb>=271 && lb <=276) return 1;
    return 0;
}

// Period I

  if (run==167776) {
    if (lb>=124 && lb <=125) return 1;
    if (lb>=127 && lb <=127) return 1;
    if (lb>=132 && lb <=204) return 1;
    if (lb>=206 && lb <=242) return 1;
    if (lb>=253 && lb <=280) return 1;
    if (lb>=286 && lb <=332) return 1;
    if (lb>=334 && lb <=512) return 1;
    if (lb>=514 && lb <=546) return 1;
    return 0;
}

  if (run==167680) {
    if (lb>=33 && lb <=48) return 1;
    if (lb>=53 && lb <=84) return 1;
    if (lb>=86 && lb <=129) return 1;
    if (lb>=131 && lb <=139) return 1;
    if (lb>=142 && lb <=223) return 1;
    if (lb>=226 && lb <=249) return 1;
    if (lb>=251 && lb <=266) return 1;
    return 0;
}

  if (run==167661) {
    if (lb>=372 && lb <=382) return 1;
    if (lb>=386 && lb <=439) return 1;
    return 0;
}

  if (run==167607) {
    if (lb>=86 && lb <=103) return 1;
    if (lb>=105 && lb <=112) return 1;
    if (lb>=117 && lb <=134) return 1;
    if (lb>=141 && lb <=143) return 1;
    if (lb>=146 && lb <=146) return 1;
    if (lb>=148 && lb <=183) return 1;
    if (lb>=186 && lb <=216) return 1;
    if (lb>=218 && lb <=247) return 1;
    if (lb>=253 && lb <=327) return 1;
    if (lb>=331 && lb <=386) return 1;
    if (lb>=390 && lb <=391) return 1;
    if (lb>=394 && lb <=426) return 1;
    if (lb>=430 && lb <=430) return 1;
    return 0;
}

  if (run==167576) {
    if (lb>=8 && lb <=14) return 1;
    if (lb>=16 && lb <=31) return 1;
    if (lb>=33 && lb <=67) return 1;
    if (lb>=70 && lb <=70) return 1;
    if (lb>=74 && lb <=100) return 1;
    if (lb>=106 && lb <=191) return 1;
    if (lb>=196 && lb <=222) return 1;
    if (lb>=226 && lb <=263) return 1;
    if (lb>=265 && lb <=293) return 1;
    return 0;
}

  if (run==167575) {
    if (lb>=125 && lb <=132) return 1;
    return 0;
}

  printf("NBNB  CheckGRL:  runnumber %i not found\n",run); 

  return 0;
}

double Analysis::getPileUpWeight(int nPV)
{
  if (nPV==0) return 0.;
  if (nPV==1) return 1.6336;
  if (nPV==2) return 1.11107;
  if (nPV==3) return 0.834308;
  if (nPV==4) return 0.676119;
  if (nPV==5) return 0.647882;
  if (nPV==6) return 0.521563;
  if (nPV==7) return 0.598444;
  if (nPV>=8) return 0.346462; 

  cout << "Error in assigning weight for nGoodPV "<<nPV<<endl;
  return -1.;
}

// not the quickest sorting algorithm...
void Analysis::sort(float *lep_pt, float *lep_px, float *lep_py, float *lep_pz, float *lep_e, float *lep_isMuon, float *lep_charge, unsigned int n_leptons)
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

double Analysis::CalcTranSphericity(double sumpx2,double sumpy2,double sumpxpy){
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

int Analysis::doGenCutDrellYan(Long64_t entry) {

 (void)entry;
 
 //int mc_n = m_sel->GetScalarVal<int>("mc_n");
 std::vector<int> mc_pdgId = m_sel->GetRawVector< std::vector<int> >("mc_pdgId");
 std::vector<float> mc_m = m_sel->GetRawVector< std::vector<float> >("mc_m");
 float mll = mc_m[7];  // The 'Z' mass

 if ((mll > 15000.) && (mll < 40000.)) return 1;
 else return 0;

}

int Analysis::getProcess(Long64_t entry) {

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

void Analysis::fill_histo(double mc_event_weight, unsigned int nbin, float MET){

  h_met->Fill(nbin, MET/1000.,mc_event_weight);

  cutflow_histo->Fill(nbin, mc_event_weight);
  h_cutflow_susy->Fill(nbin, susyprocess, mc_event_weight);
  h_nGoodPV    ->Fill(nbin, nGoodPV,mc_event_weight);

  return;
} 

void Analysis::fill_histo(double mc_event_weight, unsigned int nbin, float MET, float inv_mass, float m_eff, float m_t, float htmiss, int isOS){

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
      h_e_etcone20 ->Fill(nbin, ele_etcone20[i]/1000. , mc_event_weight);
      h_e_charge   ->Fill(nbin, ele_charge[i],          mc_event_weight);
    }
  }

  //muons
  
  h_mu_nb->Fill(bin,  n_muo, mc_event_weight);
  if (n_muo >0) {
    for (unsigned int i = 0; i < n_muo; i++){
      h_mu_eta      ->Fill(nbin, muo_eta[i],             mc_event_weight);
      h_mu_pt       ->Fill(nbin, muo_pt[i]/1000.,        mc_event_weight);
      h_mu_phi      ->Fill(nbin, muo_phi[i],             mc_event_weight);
      h_mu_etcone20 ->Fill(nbin, muo_etcone20[i]/1000. , mc_event_weight);
      h_mu_charge   ->Fill(nbin, muo_charge[i],          mc_event_weight);
    }
  }

  //jets
  
  h_jet_nb->Fill(bin,  n_jet, mc_event_weight);
  if (n_jet >0) {
    float jetpt; 
    for (unsigned int i = 0; i < n_jet; i++){
      
      jetpt = (jet_pt.at(i))*(jet_jes.at(i));
      if (jet_jes.at(i) == 0.) jetpt = jet_pt.at(i);      
      
      h_jet_eta      ->Fill(nbin, jet_eta[i],  	   mc_event_weight);
      h_jet_pt       ->Fill(nbin, jetpt/1000.,	   mc_event_weight);
      h_jet_phi      ->Fill(nbin, jet_phi[i],  	   mc_event_weight);
    }//end loop over jets
    
    //leading jet
    jetpt = (jet_pt.at(0))*(jet_jes.at(0));
    if (jet_jes.at(0) == 0.) jetpt = jet_pt.at(0);	
    h_jetl_eta      ->Fill(nbin, jet_eta[0],  	   mc_event_weight);
    h_jetl_pt       ->Fill(nbin, jetpt/1000.,	   mc_event_weight);
    h_jetl_phi      ->Fill(nbin, jet_phi[0],  	   mc_event_weight);
    
    //2nd leading jet
    if (n_jet >1) {
      jetpt = (jet_pt.at(1))*(jet_jes.at(1));
      if (jet_jes.at(1) == 0.) jetpt = jet_pt.at(1);	
      h_jet2l_eta      ->Fill(nbin, jet_eta[1],  	   mc_event_weight);
      h_jet2l_pt       ->Fill(nbin, jetpt/1000.,	   mc_event_weight);
      h_jet2l_phi      ->Fill(nbin, jet_phi[1],  	   mc_event_weight);
    }//end if at least 2 jets
  }//end if jets >0
  
  return;  
}

Analysis::Analysis(D3PDSelector * inst)
{
  //Constructor. The constructor is called from SlaveBegin in the D3PDSelector
  
  m_sel = inst; //MANDATORY. The D3PDSelector Object must be known to the Analysis Class.
 
  //The selector class needs to know which are the prefixes for the particles objects.
  m_sel->SetElectronContainerPrefix("el");
  m_sel->SetMuonContainerPrefix("mu_staco");
  m_sel->SetJetContainerPrefix("jet_AntiKt4H1Topo");
  //m_sel->SetPhotonContainerPrefix("ph");
  
  // Let's create a histogram and register it with the D3PD Class
  some_histo = new TH1F("some_histo","some_histo",50,0,100);
  
  int ncut = 60;
  int nCR = 15;
  int nSR = 15;
    
  cutflow_histo  = new TH1F("cutflow_histo","cutflow_histo",ncut+1,0,ncut);    
  runNumber_histo = new TH1F("runNumber_histo","runNumber_histo",200001,100000,300000);   
  controlregion_histo = new TH1F("controlregion_histo","controlregion_histo",nCR+1,0,nCR);  
  signalregion_histo = new TH1F("signalregion_histo","signalregion_histo",nSR+1,0,nSR);  

  h_cutflow_susy = new TH2F("h_cutflow_susy","h_cutflow_susy",ncut+1, 0, ncut,  100, 0,  99);

  h_e_nb       = new TH2F("h_e_nb",       "h_e_nb",       ncut+1, 0, ncut,  10,     0,    9);
  h_e_eta      = new TH2F("h_e_eta",      "h_e_eta",      ncut+1, 0, ncut, 100,    -5,    5);
  h_e_phi      = new TH2F("h_e_phi",      "h_e_phi",      ncut+1, 0, ncut,  40, -3.14, 3.14);
  h_e_pt       = new TH2F("h_e_pt",       "h_e_pt",       ncut+1, 0, ncut, 200,     0, 200.);
  h_e_etcone20 = new TH2F("h_e_etcone20", "h_e_etcone20", ncut+1, 0, ncut, 200,     0, 200.);
  h_e_charge   = new TH2F("h_e_charge",   "h_e_charge",   ncut+1, 0, ncut,   3,   -1.,   1.);

  h_mu_nb       = new TH2F("h_mu_nb",     "h_mu_nb",      ncut+1, 0, ncut,  10,     0,    9);
  h_mu_eta      = new TH2F("h_mu_eta",    "h_mu_eta",     ncut+1, 0, ncut, 100,    -5,    5);
  h_mu_phi      = new TH2F("h_mu_phi",    "h_mu_phi",     ncut+1, 0, ncut,  40, -3.14, 3.14);
  h_mu_pt       = new TH2F("h_mu_pt",     "h_mu_pt",      ncut+1, 0, ncut, 120,     0,  600);
  h_mu_etcone20 = new TH2F("h_mu_etcone20","h_mu_etcone20",ncut+1,0, ncut, 120,     0,  600);
  h_mu_charge   = new TH2F("h_mu_charge", "h_mu_charge",  ncut+1, 0, ncut,   3,   -1.,   1.);

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
  m_sel->AddTObject(controlregion_histo); 
  m_sel->AddTObject(signalregion_histo); 
  
  m_sel->AddTObject(h_e_nb );      
  m_sel->AddTObject(h_e_eta);      
  m_sel->AddTObject(h_e_phi);      
  m_sel->AddTObject(h_e_pt );      
  m_sel->AddTObject(h_e_etcone20); 
  m_sel->AddTObject(h_e_charge);

  m_sel->AddTObject(h_mu_nb );     
  m_sel->AddTObject(h_mu_eta);     
  m_sel->AddTObject(h_mu_phi);     
  m_sel->AddTObject(h_mu_pt );     
  m_sel->AddTObject(h_mu_etcone20);
  m_sel->AddTObject(h_mu_charge);

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
  
#ifdef HISTO
  cout << "saving histos to file"<<endl;
#endif

  debugfile.open("/data/etp4/flegger/susy/D3PDReader_pod/debug.txt", ios::app);
#ifdef ELECTRON
  dileptonfile.open("dilepton_electronStream.txt", ios::app);
#endif
#ifdef MUON
  dileptonfile.open("dilepton_muonStream.txt",ios::app);
#endif
#ifdef MC
  dileptonfile.open("dilepton_mc.txt",ios::app);
#endif
#ifdef QCDBG
  cout << "=========================================================================="<<endl;  
  cout << "==                                                                      =="<<endl;  
  cout << "==                QCD estimation: have you changed OPS??                =="<<endl;  
  cout << "==                                                                      =="<<endl;  
  cout << "=========================================================================="<<endl;
#endif    
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


/** do muon scale correction as well,values are based on MCP Twikipage **/

  mcp_smear.UseScale(1);   


}
