#ifndef EGAMMAEVENT_EGAMMAPIDDEFS_H
#define EGAMMAEVENT_EGAMMAPIDDEFS_H
/**
  @class egammaPIDdefs
     This file defines the bit-occupation of the isEM flag of egamma 
     and the enum definition of the identification results

     Three enums are defined
      BitDef : rather obsolete, defined for files reconstructed before rel 15.2.0
      BitDefElectron : definition of the 32 bits defined to identify an electron
      
      BitDefPhoton : definition of the 32 bits defined to identify a photon

      Note that the concrete use of the bits is done in 
	  egammaElectronCutIDTool.cxx : the cut-based selection for electrons
	  egammaElectronCutIDToolBase.py : cut thresholds which are applied for the different menus
	  egammaPhotonCutIDTool.cxx : the cut-based selection for photons
	  egammaPhotonCutIDToolBase.py : cut thresholds which are applied for the different menus
      In particular it means that even if a bit is defined and enters in the 
      definition of a selection level, it does not mean that the cut is applied in practice as its threshold could have a dummy value

   @author Dirk Zerwas
*/

namespace egammaPID { 
  
 /*! \enum Bitdefinitons for the egamma identification tools */
  enum PID {
    /** @brief cut-based identification for egamma objects (cluster and track-based) */
    IsEM		= 0,
    /** @brief loglikelihood identification */
    ElectronWeight,
    /** @brief loglikelihood identification */
    BgWeight,
    NeuralNet,
    Hmatrix,
    Hmatrix5,
    /** @brief cut-based identification for softe electrons in jets (for btag) */
    SofteIsEM,
    /** @brief loglikelihood identification */
    SofteElectronWeight,
    /** @brief loglikelihood identification */
    SofteBgWeight,
    SofteNeuralNet,
    /** @brief Isolation Likelihood for jet separation*/
    IsolationLikelihood_jets,
    /** @brief Isolation Likelihood for separation of electrons from heavy quark decays*/
    IsolationLikelihood_HQDelectrons,
    AdaBoost,
    /** @brief loglikelihood identification */
    PhotonWeight,
    /** @brief loglikelihood identification */
    BgPhotonWeight,
    FisherScore, 
    IsGoodOQ,
    LastEgammaPID
  };

  //const double EgPidUndefined = -999.;
  const double EgPidUndefined = 0.;

  /*! \enum Bitdefinitons for the egamma class, for the electron identification 
    see egammaParameters for info on the variable definitions */
  enum BitDefElectron {
    /** @brief cluster eta range */
    ClusterEtaRange_Electron	    =  0,

    /** @brief matching to photon (not necessarily conversion--the name is historical) */
    ConversionMatch_Electron	    =  1,

    /** @brief cluster leakage into the hadronic calorimeter */
    ClusterHadronicLeakage_Electron =  2,
    /** @brief energy in 2nd sampling (e.g E277>0) */
    ClusterMiddleEnergy_Electron    =  3, 
    /** @brief energy ratio in 2nd sampling (e.g E237/E277) */
    ClusterMiddleEratio37_Electron  =  4,
    /** @brief energy ratio in 2nd sampling (e.g E233/E237) */
    ClusterMiddleEratio33_Electron  =  5,
    /** @brief width in the second sampling (e.g Weta2) */
    ClusterMiddleWidth_Electron     =  6,

    /** @brief fraction of energy found in 1st sampling (NB: not used in fact for electrons)*/
    ClusterStripsEratio_Electron    =  8,
    /** @brief energy of 2nd maximum in 1st sampling ~e2tsts1/(1000+const_lumi*et) */
    ClusterStripsDeltaEmax2_Electron =  9,
    /** @brief difference between 2nd maximum and 1st minimum in strips (e2tsts1-emins1) */
    ClusterStripsDeltaE_Electron    = 10,
    /** @brief shower width in 1st sampling */
    ClusterStripsWtot_Electron      = 11,
    /** @brief shower shape in shower core 1st sampling */
    ClusterStripsFracm_Electron     = 12,
    /** @brief shower width weighted by distance from the maximum one */
    ClusterStripsWeta1c_Electron    = 13,

    /** @brief difference between max and 2nd max in strips */
    ClusterStripsDEmaxs1_Electron   = 15,
    /** @brief B layer hit */
    TrackBlayer_Electron	    = 16,
    /** @brief number of Pixel hits */
    TrackPixel_Electron 	    = 17,
    /** @brief number of Pixel and SCT hits */
    TrackSi_Electron		    = 18,
    /** @brief distance of closet approach */
    TrackA0_Electron		    = 19,
    /** @brief eta difference between cluster and extrapolated track in the 1st sampling */
    TrackMatchEta_Electron	    = 20,
    /** @brief phi difference between cluster and extrapolated track in the 2nd sampling */
    TrackMatchPhi_Electron	    = 21,
    /** @brief energy-momentum match */
    TrackMatchEoverP_Electron	    = 22,
    /** @brief number of TRT hits */
    TrackTRThits_Electron	    = 24,
    /** @brief ratio of high to all TRT hits for isolated electrons */
    TrackTRTratio_Electron	    = 25,
    /** @brief ratio of high to all TRT hits for non-isolated electrons */    
    TrackTRTratio90_Electron	    = 26,

    /** @brief distance of closet approach for tight selection */
    TrackA0Tight_Electron	    = 27,
    /** @brief eta difference between cluster and extrapolated track in the 1st sampling for tight selection */
    TrackMatchEtaTight_Electron     = 28,

    /** @brief isolation */
    Isolation_Electron  	    = 29,
    /** @brief calorimetric isolation */
    ClusterIsolation_Electron	    = 30,
    /** @brief tracker isolation */
    TrackIsolation_Electron	    = 31
  };

  /*! \enum Bitdefinitons for the egamma class for photon identification
    see egammaParameters for info on the variable definitions */
  enum BitDefPhoton {
    /** @brief cluster eta range */
    ClusterEtaRange_Photon	  =  0,
    /** @brief cluster eta range */
    ClusterEtaRange_PhotonLoose   =  1,

    // selection for Loose photons
    /** @brief cluster leakage into the hadronic calorimeter */
    ClusterHadronicLeakage_PhotonLoose =  2,
    /** @brief energy in 2nd sampling (e277) */
    ClusterMiddleEnergy_PhotonLoose    =  3, 
    /** @brief energy ratio in 2nd sampling */
    ClusterMiddleEratio37_PhotonLoose  =  4,
    /** @brief energy ratio in 2nd sampling */
    ClusterMiddleEratio33_PhotonLoose  =  5,
    /** @brief width in the second sampling */
    ClusterMiddleWidth_PhotonLoose     =  6,

    // selection for tight photons
    /** @brief cluster leakage into the hadronic calorimeter */
    ClusterHadronicLeakage_Photon =  10,
    /** @brief energy in 2nd sampling (e277) */
    ClusterMiddleEnergy_Photon    =  11, 
    /** @brief energy ratio in 2nd sampling */
    ClusterMiddleEratio37_Photon  =  12,
    /** @brief energy ratio in 2nd sampling for photons */
    ClusterMiddleEratio33_Photon  =  13,
    /** @brief width in the second sampling */
    ClusterMiddleWidth_Photon	  =  14,

    /** @brief fraction of energy found in 1st sampling */
    ClusterStripsEratio_Photon    =  15,
    /** @brief energy of 2nd maximum in 1st sampling ~e2tsts1/(1000+const_lumi*et) */
    ClusterStripsDeltaEmax2_Photon =  16,
    /** @brief difference between 2nd maximum and 1st minimum in strips (e2tsts1-emins1) */
    ClusterStripsDeltaE_Photon    = 17,
    /** @brief shower width in 1st sampling */
    ClusterStripsWtot_Photon	  = 18,
    /** @brief shower shape in shower core 1st sampling */
    ClusterStripsFracm_Photon	  = 19,
    /** @brief shower width weighted by distance from the maximum one */
    ClusterStripsWeta1c_Photon    = 20,
    /** @brief difference between max and 2nd max in strips */
    ClusterStripsDEmaxs1_Photon  = 21,

    /** @brief energy-momentum match for photon selection*/
    TrackMatchEoverP_Photon	  = 22,
    
    /** @brief ambiguity resolution for photon (vs electron) */
    AmbiguityResolution_Photon    = 23,

    /** @brief isolation */
    Isolation_Photon		  = 29,
    /** @brief calorimetric isolation for photon selection */
    ClusterIsolation_Photon	  = 30,
    /** @brief tracker isolation for photon selection */
    TrackIsolation_Photon	  = 31
  };


  //
  // cut definition for electrons
  //
  /** @brief cuts of hadronic leakage*/
  const unsigned int HADLEAKETA_ELECTRON = 
    0x1 << ClusterEtaRange_Electron	   | 
    0x1 << ClusterHadronicLeakage_Electron;
  /** @brief old cuts in strips (without ClusterStripsDEmaxs1)*/
  const unsigned int CALOSTRIPSOLD_ELECTRON =
    0x1 << ClusterStripsEratio_Electron     |
    0x1 << ClusterStripsDeltaEmax2_Electron |
    0x1 << ClusterStripsDeltaE_Electron     |
    0x1 << ClusterStripsWtot_Electron	    |
    0x1 << ClusterStripsFracm_Electron      |
    0x1 << ClusterStripsWeta1c_Electron     ;
  /** @brief cuts in strips (with ClusterStripsDEmaxs1)*/
  const unsigned int CALOSTRIPS_ELECTRON =
    0x1 << ClusterStripsEratio_Electron     |
    0x1 << ClusterStripsDeltaEmax2_Electron |
    0x1 << ClusterStripsDeltaE_Electron     |
    0x1 << ClusterStripsWtot_Electron	    |
    0x1 << ClusterStripsFracm_Electron      |
    0x1 << ClusterStripsWeta1c_Electron     |
    0x1 << ClusterStripsDEmaxs1_Electron    ;
  /** @brief cuts in middle sampling*/
  const unsigned int CALOMIDDLE_ELECTRON =    
    0x1 << ClusterMiddleEnergy_Electron     |
    0x1 << ClusterMiddleEratio37_Electron   |
    0x1 << ClusterMiddleWidth_Electron     ;
  /** @brief calorimeter isolation*/
  const unsigned int CALORIMETRICISOLATION_ELECTRON = 
    0x1 << ClusterIsolation_Electron ;

  /** @brief "old" all cuts in calorimeter (except isolation) without ClusterStripsDEmaxs1 */
  const unsigned int CALONOISOOLD_ELECTRON = HADLEAKETA_ELECTRON | CALOSTRIPSOLD_ELECTRON | CALOMIDDLE_ELECTRON ;
  /** @brief "old" all cuts in calorimeter (including isolation) without ClusterStripsDEmaxs1 */
  const unsigned int CALOOLD_ELECTRON = CALONOISOOLD_ELECTRON | CALORIMETRICISOLATION_ELECTRON;
  /** @brief all cuts in calorimeter (except isolation)*/
  const unsigned int CALO_ELECTRON = HADLEAKETA_ELECTRON | CALOSTRIPS_ELECTRON | CALOMIDDLE_ELECTRON ;

  /** @brief Track quality cuts except b-layer for electrons*/
  const unsigned int TRACKINGNOBLAYER_ELECTRON =     
    0x1 << TrackPixel_Electron   |
    0x1 << TrackSi_Electron	 |
    0x1 << TrackA0_Electron;
  /** @brief Track quality cuts for electrons*/
  const unsigned int TRACKING_ELECTRON = 
    TRACKINGNOBLAYER_ELECTRON |  
    0x1 << TrackBlayer_Electron;
  /** @brief Track cluster matching in eta for electrons*/
  const unsigned int TRACKMATCHDETA_ELECTRON =
    0x1 << TrackMatchEta_Electron;
  /** @brief Track cluster matching in eta, phi for electrons*/
  const unsigned int TRACKMATCHNOEOVERP_ELECTRON =
    0x1 << TrackMatchEta_Electron      |
    0x1 << TrackMatchPhi_Electron;
  /** @brief Track cluster matching in eta, phi, E/p for electrons*/
  const unsigned int TRACKMATCH_ELECTRON =
    0x1 << TrackMatchEta_Electron      |
    0x1 << TrackMatchPhi_Electron      |
    0x1 << TrackMatchEoverP_Electron  ;
  /** @brief Tight Track cluster matching */
  const unsigned int TRACKMATCHTIGHT_ELECTRON =
    0x1 << TrackMatchEtaTight_Electron      |
    0x1 << TrackA0Tight_Electron;
  /** @brief Tight conversion matching */
  const unsigned int CONVMATCH_ELECTRON =
    0x1 << ConversionMatch_Electron;

  /** @brief TRT hits and TR ratio for electrons*/
  const unsigned int TRT_ELECTRON = 
    0x1 << TrackTRThits_Electron   |
    0x1 << TrackTRTratio_Electron;
  /** @brief TRT hits and TR ratio (@90% eff) for electrons*/
  const unsigned int TRT90_ELECTRON = 
    0x1 << TrackTRThits_Electron   |
    0x1 << TrackTRTratio90_Electron;

  /** @brief isolation by tracker */
  const unsigned int TRACKINGISOLATION_ELECTRON = 
    0x1 << TrackIsolation_Electron;
  /** @brief isolation for electrons is combination of calo and tracker */
  const unsigned int ISOLATION_ELECTRON = 
    0x1 << Isolation_Electron ;
  /** @brief isolation for electrons is combination of calo and tracker */
  const unsigned int CALOTRACKISOLATION_ELECTRON = 
    CALORIMETRICISOLATION_ELECTRON | TRACKINGISOLATION_ELECTRON;

  /** @brief all cuts except TRT for electrons*/
  const unsigned int ALLNOTRT_ELECTRON = 
    TRACKING_ELECTRON | TRACKMATCH_ELECTRON | CALO_ELECTRON;
  /** @brief all cuts except TRT for electrons(old way)*/
  const unsigned int ALLNOTRTOLD_ELECTRON = 
    TRACKING_ELECTRON | TRACKMATCH_ELECTRON | CALOOLD_ELECTRON;
  /** @brief all cuts for electrons*/
  const unsigned int ALL_ELECTRON = 
    ALLNOTRT_ELECTRON | TRT_ELECTRON;
  /** @brief all cuts fo electrons (old way)*/
  const unsigned int ALLOLD_ELECTRON = 
    ALLNOTRTOLD_ELECTRON | TRT_ELECTRON;

  // old definitions of cuts as in rel<15.2.0
  const unsigned int ElectronLooseOLD = 
    CALOMIDDLE_ELECTRON | HADLEAKETA_ELECTRON;
  const unsigned int ElectronMediumOLD = 
    CALOOLD_ELECTRON | TRACKINGNOBLAYER_ELECTRON | TRACKMATCHDETA_ELECTRON;
  const unsigned int ElectronMediumNoIsoOLD = 
    CALONOISOOLD_ELECTRON | TRACKINGNOBLAYER_ELECTRON | TRACKMATCHDETA_ELECTRON;
  const unsigned int ElectronTightOLD = 
    ALLOLD_ELECTRON;
  const unsigned int ElectronTightTRTNoIsoOLD = 
    TRACKING_ELECTRON | TRACKMATCH_ELECTRON | CALONOISOOLD_ELECTRON | TRT90_ELECTRON ;
  const unsigned int ElectronTightNoIsolationOLD = ElectronTightTRTNoIsoOLD;


  // new definitions of cuts as in rel>=15.2.0
  // since 15.7.0 also Tight selection contains 
  //	 TRACKMATCHTIGHT_ELECTRON 
  //	 CONVMATCH_ELECTRON
  /** @brief Loose electron selection */
  const unsigned int ElectronLoose = 
    CALOMIDDLE_ELECTRON | HADLEAKETA_ELECTRON;
  /** @brief Medium electron selection */
  const unsigned int ElectronMedium = 
    CALO_ELECTRON | TRACKINGNOBLAYER_ELECTRON | TRACKMATCHDETA_ELECTRON;
  /** @brief Medium electron selection with isolation requirement */
  const unsigned int ElectronMediumIso = 
    CALO_ELECTRON | TRACKINGNOBLAYER_ELECTRON | TRACKMATCHDETA_ELECTRON | 
    ISOLATION_ELECTRON;
  /** @brief obsolete - kept not crash clients */
  const unsigned int ElectronMediumNoIso = ElectronMedium;
  /** @brief Tight electron (NB: was Tight robust in 15.X) */
  const unsigned int ElectronTight = 
    CALO_ELECTRON | 
    TRACKING_ELECTRON | 
    0x1 << TrackMatchEoverP_Electron | 
    0x1 << TrackA0Tight_Electron |
    CONVMATCH_ELECTRON | 
    TRT_ELECTRON ;
  /** @brief Tight without conversion requirement (NB: was Tight robust in 15.X) */
  const unsigned int ElectronTight_NoConvCut = 
    CALO_ELECTRON | 
    TRACKING_ELECTRON | 
    0x1 << TrackMatchEoverP_Electron | 
    0x1 << TrackA0Tight_Electron |
    egammaPID::TRT_ELECTRON ;
  /** @brief Tight electron (NB: kept for backward compatibility) */
  const unsigned int ElectronTightRobust = ElectronTight;
  /** @brief Tight electron selection (NB: was Tight in 15.X)*/
  const unsigned int ElectronTight_WithTrackMatch = 
    CALO_ELECTRON | TRACKING_ELECTRON | TRACKMATCH_ELECTRON | 
    TRACKMATCHTIGHT_ELECTRON | CONVMATCH_ELECTRON | TRT_ELECTRON ;
  /** @brief obsolete - kept not to crash clients */
  const unsigned int ElectronTightTRTNoIso = ElectronTight;
  /** @brief obsolete - kept not to crash clients */
  const unsigned int ElectronTightNoIsolation = ElectronTight;
  /** @brief Tight electron selection with isolation requirement */
  const unsigned int ElectronTightIso = 
    ElectronTight | 
    ISOLATION_ELECTRON;

  //
  // for photon selection
  //
  /** @brief cuts of hadronic leakage (for Loose selection)*/
  const unsigned int HADLEAKETA_PHOTONLOOSE = 
    0x1 << ClusterEtaRange_PhotonLoose  | 
    0x1 << ClusterHadronicLeakage_PhotonLoose;
  /** @brief cuts of hadronic leakage*/
  const unsigned int HADLEAKETA_PHOTON = 
    0x1 << ClusterEtaRange_Photon	 | 
    0x1 << ClusterHadronicLeakage_Photon;
  /** @brief cuts in middle sampling (for Loose selection)*/
  const unsigned int CALOMIDDLE_PHOTONLOOSE=	
    0x1 << ClusterMiddleEnergy_PhotonLoose     |
    0x1 << ClusterMiddleEratio37_PhotonLoose   |
    0x1 << ClusterMiddleEratio33_PhotonLoose   |
    0x1 << ClusterMiddleWidth_PhotonLoose     ;
  /** @brief cuts in middle sampling*/
  const unsigned int CALOMIDDLE_PHOTON =    
    0x1 << ClusterMiddleEnergy_Photon	  |
    0x1 << ClusterMiddleEratio37_Photon   |
    0x1 << ClusterMiddleEratio33_Photon   |
    0x1 << ClusterMiddleWidth_Photon	 ;
  /** @brief old cuts in strips (without ClusterStripsDEmaxs1)*/
  const unsigned int CALOSTRIPSOLD_PHOTON =
    0x1 << ClusterStripsEratio_Photon	  |
    0x1 << ClusterStripsDeltaEmax2_Photon |
    0x1 << ClusterStripsDeltaE_Photon	  |
    0x1 << ClusterStripsWtot_Photon	  |
    0x1 << ClusterStripsFracm_Photon	  |
    0x1 << ClusterStripsWeta1c_Photon	  ;
  /** @brief cuts in strips (with ClusterStripsDEmaxs1)*/
  const unsigned int CALOSTRIPS_PHOTON =
    0x1 << ClusterStripsEratio_Photon	  |
    0x1 << ClusterStripsDeltaEmax2_Photon |
    0x1 << ClusterStripsDeltaE_Photon	  |
    0x1 << ClusterStripsWtot_Photon	  |
    0x1 << ClusterStripsFracm_Photon	  |
    0x1 << ClusterStripsWeta1c_Photon	  |
    0x1 << ClusterStripsDEmaxs1_Photon    ;

  /** @brief calorimeter isolation*/
  const unsigned int CALORIMETRICISOLATION_PHOTON = 
    0x1 << ClusterIsolation_Photon;
  /** @brief "old" all cuts in calorimeter (except isolation) without ClusterStripsDEmaxs1 */
  const unsigned int CALONOISOOLD_PHOTON = 
    HADLEAKETA_PHOTON | CALOSTRIPSOLD_PHOTON | CALOMIDDLE_PHOTON ;
  /** @brief all cuts in calorimeter (except isolation)*/
  const unsigned int CALO_PHOTON = 
    HADLEAKETA_PHOTON | CALOSTRIPS_PHOTON | CALOMIDDLE_PHOTON;

  /** @brief isolation by tracker */
  const unsigned int TRACKINGISOLATION_PHOTON = 
    0x1 << TrackIsolation_Photon;
  /** @brief isolation for photons is combination of calo and tracker */
  const unsigned int ISOLATION_PHOTON = 
    0x1 << Isolation_Photon ;
  /** @brief isolation for photons is combination of calo and tracker */
  const unsigned int CALOTRACKISOLATION_PHOTON = 
    CALORIMETRICISOLATION_PHOTON | TRACKINGISOLATION_PHOTON;

  /** @brief Track cluster matching E/p for photons*/
  const unsigned int TRACKMATCH_PHOTON =
    0x1 << TrackMatchEoverP_Photon  ;

  /** @brief Ambigiuty resolve for photons */
  const unsigned int AMBIGUITYRESOLVE_PHOTON =
    0x1 << AmbiguityResolution_Photon;

  /** @brief Loose photon selection */
  const unsigned int PhotonLoose = 
    CALOMIDDLE_PHOTONLOOSE | HADLEAKETA_PHOTONLOOSE | AMBIGUITYRESOLVE_PHOTON;
  /** @brief Tight photon selection */
  const unsigned int PhotonTight = CALO_PHOTON | TRACKMATCH_PHOTON | AMBIGUITYRESOLVE_PHOTON;
  /** @brief Loose photon selection */
  const unsigned int PhotonLooseNoAR = 
    CALOMIDDLE_PHOTONLOOSE | HADLEAKETA_PHOTONLOOSE;
  /** @brief Tight photon selection */
  const unsigned int PhotonTightNoAR = CALO_PHOTON | TRACKMATCH_PHOTON ;
  /** @brief Tight photon selection with isolation*/
  const unsigned int PhotonTightIso = PhotonTight | ISOLATION_PHOTON;
  /** @brief Tight photon (old definition) */
  const unsigned int PhotonTightOLD = 
    CALONOISOOLD_PHOTON | CALORIMETRICISOLATION_PHOTON;




  /**@brief forward electron flavours */
  /*
    --variables:

    ["FIRST_ENG_DENS"] =1;
    ["ENG_FRAC_MAX"]   =2;
    ["LONGITUDINAL"]   =4;
    ["SECOND_LAMBDA"]  =8;
    ["LATERAL"]        =16;
    ["SECOND_R"]       =32;
    ["CENTER_LAMBDA"]  =64;
    
    --Flavors
    Tight: All avriables except First_ENG_DENS
    Loose: SECOND_LAMBDA, SECOND_R, CENTER_LAMBDA 
  */
  
  const unsigned int frwdElectronTight = 126;
  const unsigned int frwdElectronLoose = 104;

  //
  //
  //	BEWARE 
  //	OBSOLETE only kept 
  //	not to crash users who have not changed their code accordingly)
  //	see egammaParameters for info on the variable definitions
  //
  //
  

  /*! \enum Bitdefinitons for the egamma class */
  enum BitDef {
    // Cluster based egamma
    /** @brief cluster eta range */
    ClusterEtaRange	   =  0,
    /** @brief cluster leakage into the hadronic calorimeter */
    ClusterHadronicLeakage =  1,
    /** @brief energy in 2nd sampling (e277) */
    ClusterMiddleEnergy    =  4, 
    /** @brief energy ratio in 2nd sampling (e237/e277) */
    ClusterMiddleEratio37  =  5,
    /** @brief energy ratio in 2nd sampling (e233/e237) for photons */
    ClusterMiddleEratio33  =  6,
    /** @brief width in the second sampling (weta2) */
    ClusterMiddleWidth     =  7,
    /** @brief fraction of energy found in 1st sampling (f1) */
    ClusterStripsEratio    =  8,
    /** @brief energy of 2nd maximum in 1st sampling ~e2tsts1/(1000+const_lumi*et) */
    ClusterStripsDeltaEmax2=  9,
    /** @brief difference between 2nd maximum and 1st minimum in strips (e2tsts1-emins1) */
    ClusterStripsDeltaE    = 10,
    /** @brief shower width in 1st sampling (wtots1) */
    ClusterStripsWtot	   = 11,
    /** @brief shower shape in shower core 1st sampling (fracs1) */
    ClusterStripsFracm     = 12,
    /** @brief shower width weighted by distance from the maximum one (weta1) */
    ClusterStripsWeta1c    = 13,
    /** @brief calorimetric isolation (etcone20) */
    ClusterIsolation	   = 14,
    /** @brief difference between max and 2nd max in strips */
    ClusterStripsDEmaxs1  = 15,
    //Track based egamma
    /** @brief B layer hit */
    TrackBlayer 	   = 16,
    /** @brief number of Pixel hits */
    TrackPixel  	   = 17,
    /** @brief number of Pixel and SCT hits */
    TrackSi		   = 18,
    /** @brief distance of closet approach */
    TrackA0		   = 19,
    /** @brief eta difference between cluster and extrapolated track in the 1st sampling */
    TrackMatchEta	   = 20,
    /** @brief phi difference between cluster and extrapolated track in the 2nd sampling */
    TrackMatchPhi	   = 21,
    /** @brief energy-momentum match */
    TrackMatchEoverP	   = 22,
    /** @brief number of TRT hits */
    TrackTRThits	   = 24,
    /** @brief ratio of high to all TRT hits for isolated electrons */
    TrackTRTratio	   = 25,
    /** @brief ratio of high to all TRT hits for non-isolated electrons */    
    TrackTRTratio90	   = 26,
    /** @brief tracker isolation (ptcone30) */
    TrackIsolation	 = 27
  };
  //
  // old definition of cut bits, kept only not break codes 
  // It has to be used on "old" AODs produced with "rel 14"
  //
  /** @brief cuts of hadronic leakage*/
  const unsigned int HADLEAKETA = 
    0x1 << ClusterEtaRange	  | 
    0x1 << ClusterHadronicLeakage;
  /** @brief old cuts in strips (without ClusterStripsDEmaxs1)*/
  const unsigned int CALOSTRIPSOLD=
    0x1 << ClusterStripsEratio     |
    0x1 << ClusterStripsDeltaEmax2 |
    0x1 << ClusterStripsDeltaE     |
    0x1 << ClusterStripsWtot	   |
    0x1 << ClusterStripsFracm	   |
    0x1 << ClusterStripsWeta1c     ;
  /** @brief cuts in strips (with ClusterStripsDEmaxs1)*/
  const unsigned int CALOSTRIPS=
    0x1 << ClusterStripsEratio     |
    0x1 << ClusterStripsDeltaEmax2 |
    0x1 << ClusterStripsDeltaE     |
    0x1 << ClusterStripsWtot	   |
    0x1 << ClusterStripsFracm	   |
    0x1 << ClusterStripsWeta1c     |
    0x1 << ClusterStripsDEmaxs1    ;
  /** @brief cuts in middle sampling*/
  const unsigned int CALOMIDDLE=    
    0x1 << ClusterMiddleEnergy     |
    0x1 << ClusterMiddleEratio37   |
    0x1 << ClusterMiddleEratio33   |
    0x1 << ClusterMiddleWidth	  ;
  /** @brief calorimeter isolation*/
  const unsigned int CALOISO = 0x1 << ClusterIsolation ;
  /** @brief "old" all cuts in calorimeter (except isolation) without ClusterStripsDEmaxs1 */
  const unsigned int CALONOISOOLD = HADLEAKETA | CALOSTRIPSOLD | CALOMIDDLE ;
  /** @brief all cuts in calorimeter (except isolation)*/
  const unsigned int CALONOISO = HADLEAKETA | CALOSTRIPS | CALOMIDDLE ;
  /** @brief all cuts in calorimeter (including isolation) without ClusterStripsDEmaxs1 */
  const unsigned int CALOOLD = CALONOISOOLD | CALOISO ;
  /** @brief all cuts in calorimeter (including isolation) */
  const unsigned int CALO = CALONOISO | CALOISO ;

  /** @brief */
  const unsigned int TRACKINGNOBLAYER =     
    0x1 << TrackPixel	|
    0x1 << TrackSi	|
    0x1 << TrackA0     ;
  const unsigned int TRACKING = TRACKINGNOBLAYER |  0x1 << TrackBlayer;
  const unsigned int TRACKMATCHDETA =
    0x1 << TrackMatchEta;
  const unsigned int TRACKMATCH =
    0x1 << TrackMatchEta      |
    0x1 << TrackMatchPhi      |
    0x1 << TrackMatchEoverP  ;
  const unsigned int TRACKMATCHNOEOVERP =
    0x1 << TrackMatchEta      |
    0x1 << TrackMatchPhi     ;
  const unsigned int TRT = 
    0x1 << TrackTRThits   |
    0x1 << TrackTRTratio ;
  const unsigned int TRT90 = 
    0x1 << TrackTRThits   |
    0x1 << TrackTRTratio90 ;
  /** @brief isolation by tracker */
  const unsigned int TRACKISO = 0x1 << TrackIsolation;
  /** @brief */
  const unsigned int ALLNOTRT= TRACKING | TRACKMATCH | CALO;
  /** @brief */
  const unsigned int ALLNOTRTOLD= TRACKING | TRACKMATCH | CALOOLD;
  /** @brief all cuts*/
  //const unsigned int ALL= ALLNOTRT | TRT;
  const unsigned int ALL= 0xFFFFFFFF;
  /** @brief all cuts (old way)*/
  const unsigned int ALLOLD= ALLNOTRTOLD | TRT;

  // old definitions of cuts as for AODS in rel<15.2.0
  const unsigned int ElectronLooseOLDRel = CALOMIDDLE | HADLEAKETA;
  const unsigned int ElectronMediumOLDRel = CALOOLD | TRACKINGNOBLAYER | TRACKMATCHDETA;
  const unsigned int ElectronMediumNoIsoOLDRel = CALONOISOOLD | TRACKINGNOBLAYER | TRACKMATCHDETA ;
  const unsigned int ElectronTightOLDRel = ALLOLD;
  const unsigned int ElectronTightTRTNoIsoOLDRel = TRACKING | TRACKMATCH | CALONOISOOLD | TRT90 ;
  const unsigned int ElectronTightNoIsolationOLDRel = ElectronTightTRTNoIsoOLDRel;

  const unsigned int PhotonTightOLDRel = CALOOLD;

  //
  // for object quality flags
  //

  enum BitDefOQ {
    DeadHVPS = 0,
    DeadHVS1S2S3 = 1,
    NonNominalHVPS = 2,
    NonNominalHVS1S2S3 = 3,
    MaskedCellCore = 4,
    MaskedCellEdge = 5,
    SporadicNoiseLowQCore = 6,
    SporadicNoiseLowQEdge = 7,
    HighQCore = 8,
    HighQEdge = 9,
    AffectedCellCore = 10,
    AffectedCellEdge = 11,
    HECHighQ = 12,
    OutTime =13
  };

  /** @brief */
  const unsigned int AFFECTEDCORE = 
    0x1 << MaskedCellCore | 
    0x1 << SporadicNoiseLowQCore | 
    0x1 << HighQCore | 
    0x1 << AffectedCellCore ; 

  const unsigned int AFFECTEDEDGE = 
    0x1 << MaskedCellEdge | 
    0x1 << SporadicNoiseLowQEdge | 
    0x1 << HighQEdge | 
    0x1 << AffectedCellEdge ; 

  const unsigned int BADCLUS = 
    0x1 << MaskedCellCore | 
    0x1 << DeadHVS1S2S3 ; 

  const unsigned int ALLOQ= 0xFFFFFFFF;

}
#endif // EGAMMAREC_EGAMMAPIDDEFS_H
