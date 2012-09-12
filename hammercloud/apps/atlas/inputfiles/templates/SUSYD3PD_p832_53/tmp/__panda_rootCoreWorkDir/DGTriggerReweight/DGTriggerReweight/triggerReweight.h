#ifndef _TRIGGERREWEIGHT_H_
#define _TRIGGERREWEIGHT_H_

//ReweightUtils includes 
#include "ReweightUtils/APEvtWeight.h"
#include "ReweightUtils/APReweightND.h"

//Root includes 
#include "THnSparse.h"
#include "TFile.h"
#include "TMath.h"


//Standard includes
#include <iostream>
#include <string>

/** @brief A class to hold the trigger reweighting  
    @author Brokk Toggerson - brokk.koen.toggerson@cern.ch
    @author University of California, Irvine
    @author Anders Savonen Floderus - anders.savonen.floderus@cern.ch
    @author Lund University 
    @date First Written: 24 January 2012
    @date Last Modified: 30 January 2012
    
    The goal is to make a RootCore aware class for doing the direct 
    gaugino trigger reweighting for Moriond 2012
    
    Based off of a function by Sky French <a href="https://twiki.cern.ch/twiki/pub/AtlasProtected/SUSYTwoLeptonMoriond2012/triggerReweightEE.cxx">On the 2-lepton DG TWiki</a>
    
    Another advantage is that this will only open files once for speed. 
*/ 
class triggerReweight{ 

 public: 

  /** @brief Blank constructor, needed for root */ 
  triggerReweight(){}; 

  /** @brief Destructor cleans up memory */ 
  ~triggerReweight(); 

  /** @brief initialize the ee triggers */ 
  bool initalizeEE(std::string filename){ 
    return initalizeEE(filename.c_str()); } 

  /** @brief initialize the ee triggers */ 
  bool initalizeEE(const char* filename);

  /** @brief initialize the mumu triggers */ 
  bool initalizeMM(std::string filename){ 
    return initalizeMM(filename.c_str()); } 
	
  /** @brief initialize the mumu triggers */ 
  bool initalizeMM(const char* filename);
	
  /** @brief initialize the emu triggers */ 
  bool initalizeEMU(std::string elecFilename, std::string muonFilename){ 
    return initalizeEMU(elecFilename.c_str(), muonFilename.c_str()); } 
	
  /** @brief initialize the emu triggers */ 
  bool initalizeEMU(const char* elecFilename, const char* muonFilename);
	


  /** @brief get the trigger weight for ee triggers in MC 
      @param[in] RunNumber 
      @param[in] elpt1 The leading electron pT in MEV
      @param[in] eleta1 The leading electron eta 
      @param[in] elpt2 The sub-leading electron pT in MEV
      @param[in] eleta2 The sub-leading electron eta 
      @param[in] LumiFrac_185353_186755 The fraction of lumi 
      between runs 185353_186755. Obtained via 
      m_pileupTool->GetIntegratedLumiFraction(RunNumber,185353,186755); 
      @param[in] LumiFrac_186873_187815 The fraction of lumi 
      between runs 186873_187815. Obtained via 
      m_pileupTool->GetIntegratedLumiFraction(RunNumber,186873,187815); 
			
      As per <a href="https://espace.cern.ch/atlas-susy-etmiss/2leptonchannel/Lists/2%20lepton%20channel%20discussion%20board/DispForm.aspx?ID=2094">https://espace.cern.ch/atlas-susy-etmiss/2leptonchannel/Lists/2%20lepton%20channel%20discussion%20board/DispForm.aspx?ID=2094</a> we are using the smeared pT and 
      the SUSY pT's and eta's
  */      
  double triggerReweightEE(int RunNumber, 
			   double elpt1, double eleta1, 
			   double elpt2, double eleta2, 
			   double LumiFrac_185353_186755, 
			   double LumiFrac_186873_187815); 

  /** @brief get the trigger weight for mumu triggers in MC 
      @param[in] RunNumber 
      @param[in] mu_staco_pt1 The leading muon pT in MEV
      @param[in] mu_staco_eta1 The leading muon eta 
      @param[in] mu_staco_phi1 The leading muon phi 
      @param[in] mu_staco_isCombinedMuon1 True if the leading muon is a combined muon
      @param[in] mu_staco_ptcone201 The leading muon ptcone20
      @param[in] mu_staco_pt1 The sub-leading muon pT in MEV
      @param[in] mu_staco_eta1 The sub-leading muon eta 
      @param[in] mu_staco_phi1 The sub-leading muon phi 
      @param[in] mu_staco_isCombinedMuon1 True if the sub-leading muon is a combined muon
      @param[in] mu_staco_ptcone201 The sub-leading muon ptcone20
      @param[in] lumifrac_185353_186493 The fraction of lumi 
      between runs 185353_186493. Obtained via 
      m_pileupTool->GetIntegratedLumiFraction(RunNumber,185353,186493); 
      @param[in] lumifrac_186516_187815 The fraction of lumi 
      between runs 186516_187815. Obtained via 
      m_pileupTool->GetIntegratedLumiFraction(RunNumber,186516,187815); 
			
      As per <a href="https://espace.cern.ch/atlas-susy-etmiss/2leptonchannel/Lists/2%20lepton%20channel%20discussion%20board/DispForm.aspx?ID=2094">https://espace.cern.ch/atlas-susy-etmiss/2leptonchannel/Lists/2%20lepton%20channel%20discussion%20board/DispForm.aspx?ID=2094</a> we are using the smeared pT and 
      the SUSY pT's and eta's
  */  
  double triggerReweightMM(int RunNumber, 
			   double mu_staco_pt1, double mu_staco_eta1, double mu_staco_phi1, 
			   int mu_staco_isCombinedMuon1, double mu_staco_ptcone201, 
			   double mu_staco_pt2, double mu_staco_eta2, double mu_staco_phi2, 
			   int mu_staco_isCombinedMuon2, double mu_staco_ptcone202,
			   double lumifrac_185353_186493, double lumifrac_186516_187815); 
	
  /** @brief get the trigger weight for mumu triggers in MC 
      @param[in] RunNumber 
      @param[in] elpt1 The electron pT in MEV
      @param[in] eleta1 The electron eta 
      @param[in] mu_staco_pt1 The muon pT in MEV
      @param[in] mu_staco_eta1 The muon eta 
      @param[in] mu_staco_phi1 The muon phi 
      @param[in] mu_staco_isCombinedMuon1 True if the muon is a combined muon
      @param[in] mu_staco_ptcone20_1 The muon ptcone20
      @param[in] LumiFrac_185353_186493 The fraction of lumi 
      between runs 185353_186493. Obtained via 
      m_pileupTool->GetIntegratedLumiFraction(RunNumber,185353,186493); 
      @param[in] LumiFrac_186516_186755 The fraction of lumi 
      between runs 186516_186755. Obtained via 
      m_pileupTool->GetIntegratedLumiFraction(RunNumber,186516,186755); 
      @param[in] LumiFrac_186873_187815 The fraction of lumi 
      between runs 186873_187815. Obtained via 
      m_pileupTool->GetIntegratedLumiFraction(RunNumber,186873,187815); 
			
      As per <a href="https://espace.cern.ch/atlas-susy-etmiss/2leptonchannel/Lists/2%20lepton%20channel%20discussion%20board/DispForm.aspx?ID=2094">https://espace.cern.ch/atlas-susy-etmiss/2leptonchannel/Lists/2%20lepton%20channel%20discussion%20board/DispForm.aspx?ID=2094</a> we are using the smeared pT and 
      the SUSY pT's and eta's
  */ 
  double triggerReweightEMU(int RunNumber, 
			    double elpt1, double eleta1, 
			    double mu_staco_pt1, double mu_staco_eta1, double mu_staco_phi1, 
			    int mu_staco_isCombinedMuon1, double mu_staco_ptcone20_1,
			    double LumiFrac_185353_186493, double LumiFrac_186516_186755, double LumiFrac_186873_187815); 

  ClassDef(triggerReweight, 2); 

 private: 
	
  //Electron weights 
  TFile* electronmaps; 

  THnSparseD *ths_e12_medium_num;
  THnSparseD *ths_e12_medium_den;
  THnSparseD *ths_e12T_medium_num;
  THnSparseD *ths_e12T_medium_den;
  THnSparseD *ths_e12Tvh_medium_num;
  THnSparseD *ths_e12Tvh_medium_den;
  THnSparseD *ths_e22_medium_num;
  THnSparseD *ths_e22_medium_den;
  THnSparseD *ths_e20_medium_num;
  THnSparseD *ths_e20_medium_den;
  THnSparseD *ths_e22vh_medium1_num;
  THnSparseD *ths_e22vh_medium1_den;

  APReweightND *rew_e12_medium;
  APReweightND *rew_e12T_medium;
  APReweightND *rew_e12Tvh_medium;
  APReweightND *rew_e20_medium;
  APReweightND *rew_e22_medium;
  APReweightND *rew_e22vh_medium1;
	
  //Muon weights
  TFile* muonmaps;
	
  THnSparseD *ths_mu18_num;
  THnSparseD *ths_mu18_den;
  THnSparseD *ths_mu18_medium_num;
  THnSparseD *ths_mu18_medium_den;
  THnSparseD *ths_notmu18_mu10_loose_num;
  THnSparseD *ths_notmu18_mu10_loose_den;
  THnSparseD *ths_notmu18_medium_mu10_loose_num;
  THnSparseD *ths_notmu18_medium_mu10_loose_den;
	
  APReweightND *rew_mu18;
  APReweightND *rew_mu18_medium;
  APReweightND *rew_notmu18_mu10_loose;
  APReweightND *rew_notmu18_medium_mu10_loose;
	
  //Emu weights
  THnSparseD *ths_e10_medium_num;
  THnSparseD *ths_e10_medium_den;
  THnSparseD *ths_mu6_num;
  THnSparseD *ths_mu6_den;
	
  APReweightND *rew_e10_medium;
  APReweightND *rew_mu6;


}; /* End class triggerReweight */ 

#endif /* #ifndef _TRIGGERREWEIGHT_H_ */
