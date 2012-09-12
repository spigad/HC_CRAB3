#define MC
#define MSUGRA
//#define H1D
#define H2D

#define ONE
//#define CHANNEL // Divide histo per channel
//#define PROCESS // Divide histo per process
//#define XIMO // Divide histo per channel

//#define JESPLUS  // systematics
//#define JESMINUS
//#define JER
//#define ELERECO
//#define MUORECO
//#define SYST
//#define OS
//#define SS

#define EFF  // efficiencies

//#define OLD

//#define NORM

//#define MASS  // plot in squark/sgluino mass plane

//#define EVENTS  // plot number of evts after xx pb-1
//#define RATE    // plot rate of single process with respect to sum
//#define BEFORE  // before cuts
//#define AFTER   // after cuts

  double lumi         = 163.5; //pb	
  TString lumi_string = "163.5"; //pb	
  TString histo_string, histo_syst_string;
  int nCut, nCutRef, binmin, binmax;
  TH2D* grid_allprocesses;   
  TString prefix = "result";
  bool divide = false;

  int gridXbins = 152;
  int gridYbins = 42;
  double gridStartX = -10.;  //m0
  double gridStopX = 3030;
  double gridStartY = -15;   // m1/2
  double gridStopY = 615; 
   
  
#include "AtlasStyle2D.C"
#include "input.h"
#include "histo.h"

#ifdef MSUGRA
#include "msugra.h"
#include "Robin.h"
#endif

#ifdef SYST
#include "input_syst.h"
TH2F *SystError_grid_MET60_SS; 
TH2F *SystError_grid_MET80_SS; 
TH2F *SystError_grid_MET100_SS; 
TH2F *SystError_grid_MET100_OS; 
TH2F *SystError_grid_MET125_OS; 
TH2F *SystError_grid_MET150_OS; 
 
TH2F *SystError_grid_MET60_ee_SS; 
TH2F *SystError_grid_MET80_ee_SS; 
TH2F *SystError_grid_MET100_ee_SS; 
TH2F *SystError_grid_MET100_ee_OS; 
TH2F *SystError_grid_MET125_ee_OS; 
TH2F *SystError_grid_MET150_ee_OS; 
 
TH2F *SystError_grid_MET60_emu_SS; 
TH2F *SystError_grid_MET80_emu_SS; 
TH2F *SystError_grid_MET100_emu_SS; 
TH2F *SystError_grid_MET100_emu_OS; 
TH2F *SystError_grid_MET125_emu_OS; 
TH2F *SystError_grid_MET150_emu_OS; 
 
TH2F *SystError_grid_MET60_mumu_SS; 
TH2F *SystError_grid_MET80_mumu_SS; 
TH2F *SystError_grid_MET100_mumu_SS; 
TH2F *SystError_grid_MET100_mumu_OS; 
TH2F *SystError_grid_MET125_mumu_OS; 
TH2F *SystError_grid_MET150_mumu_OS; 
#include "histo_syst.h"
#endif

// Cut 0   no cut
// Cut 1   GRL cut
// Cut 2   trigger cut (trgEl || trgMu)
// Cut 3   jet cleaning (disabled on MC)
// Cut 4   >= 1 vertex with > 4 tracks
// Cut 5   Event veto (crack + cosmics)
// Cut 6   MUMU + EE + EMU
// Cut 7   EE
// Cut 8    && mll > 5 GeV
// Cut 9    && OS 
// Cut 10   && OS && MET cut > 150 GeV 
// Cut 11   && OS && MET cut > 250 GeV 
// Cut 12   && OS && 4 jets 100, 70, 70, 70 GeV
// Cut 13   && OS && MET cut > 100 GeV + 4 jets 100, 70, 70, 70 GeV
// Cut 14   && OS && 3 jets 80, 40, 40 GeV
// Cut 15   && OS && MET cut > 220 GeV + 3 jets 80, 40, 40 GeV
// Cut 16   && SS 
// Cut 17   && SS && MET cut > 100 GeV 
// Cut 18   && SS && 2 jets 50, 50 GeV
// Cut 19   && SS && MET cut > 80 GeV + 2 jets 50, 50 GeV
// Cut 20  	EMU 
// Cut 21  	 && mll > 5 GeV
// Cut 22  	 && OS 
// Cut 23   && OS && MET cut > 150 GeV 
// Cut 24   && OS && MET cut > 250 GeV 
// Cut 25   && OS && 4 jets 100, 70, 70, 70 GeV
// Cut 26   && OS && MET cut > 100 GeV + 4 jets 100, 70, 70, 70 GeV
// Cut 27  	 && OS && 3 jets 80, 40, 40 GeV
// Cut 28   && OS && MET cut > 220 GeV + 3 jets 80, 40, 40 GeV
// Cut 29  	 && SS 
// Cut 30  	 && SS && MET cut > 100 GeV 
// Cut 31  	 && SS && 2 jets 50, 50 GeV
// Cut 32  	 && SS && MET cut > 80 GeV + 2 jets 50, 50 GeV
// Cut 33  	MUMU 
// Cut 34  	 && mll > 5 GeV
// Cut 35  	 && OS 
// Cut 36   && OS && MET cut > 150 GeV 
// Cut 37   && OS && MET cut > 250 GeV 
// Cut 38   && OS && 4 jets 100, 70, 70, 70 GeV
// Cut 39   && OS && MET cut > 100 GeV + 4 jets 100, 70, 70, 70 GeV
// Cut 40   && OS && 3 jets 80, 40, 40 GeV
// Cut 41   && OS && MET cut > 220 GeV + 3 jets 80, 40, 40 GeV
// Cut 42  	 && SS 
// Cut 43   && SS && MET cut > 100 GeV 
// Cut 44  	 && SS && 2 jets 50, 50 GeV
// Cut 45   && SS && MET cut > 80 GeV + 2 jets 50, 50 GeV

//Processes (bin - sparticletype)
// bin 0  // -1 // underflow bin (-1 not assigned)
// bin 1  // 0  //not assigned
// bin 2  // 1  // 1 gluino + 1 squark or antisquark
// bin 3  // 2  // 2 gluinos
// bin 4  // 3  // 2 squark or 2 antisquark
// bin 5  // 4  // 1 squark + 1 antisquark
// bin 52 // 51 // 2 sbottom1
// bin 53 // 52 // 2 sbottom2
// bin 62 // 61 // 2 stop1
// bin 63 // 62 // 2 stop2
// bin 72 // 71 // 1 gluino + chi01	      
// bin 73 // 72 // 1 gluino + chi02  
// bin 74 // 73 // 1 gluino + chi03  
// bin 75 // 74 // 1 gluino + chi04  
// bin 76 // 75 // 1 gluino + chi+1  
// bin 77 // 76 // 1 gluino + chi+2  
// bin 78 // 77 // 1 gluino + chi-1  
// bin 79 // 78 // 1 gluino + chi-2    
// bin 82 // 81 // 1 squark + 1 antisquark + chi01
// bin 83 // 82 // 1 squark + 1 antisquark + chi02
// bin 84 // 83 // 1 squark + 1 antisquark + chi03
// bin 85 // 84 // 1 squark + 1 antisquark + chi04
// bin 86 // 85 // 1 squark + 1 antisquark + chi+1
// bin 87 // 86 // 1 squark + 1 antisquark + chi+2
// bin 88 // 87 // 1 squark + 1 antisquark + chi-1
// bin 89 // 88 // 1 squark + 1 antisquark + chi-2 


void signalGrid() {

  std::cout << "lumi " << lumi <<" pb-1"<< std::endl;  
  std::cout << "Opening files " << prefix << std::endl;  
     
  gROOT->SetStyle("ATLAS");
  SetAtlasStyle();
  gROOT->ForceStyle();
  
  histo_string = "h_cutflow_susy";
//  histo_string = "h_e_pt";
  histo_syst_string = "h_cutflow_susy";
  TString filename = "plots/TM_msugra_";

  nCutRef = 1;
  nCut = 1;
  
  //all plots
#ifdef CHANNEL  
   
  TCanvas *c1 = new TCanvas("canvas","canvas", 200,10,2000,1000);  // 1D histo

  TH2D* grid_ee_OS   = new TH2D("grid_ee_OS",   "grid_ee_OS",   gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  TH2D* grid_emu_OS  = new TH2D("grid_emu_OS",  "grid_emu_OS",  gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  TH2D* grid_mumu_OS = new TH2D("grid_mumu_OS", "grid_mumu_OS", gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  TH2D* grid_ee_SS   = new TH2D("grid_ee_SS",   "grid_ee_SS",   gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  TH2D* grid_emu_SS  = new TH2D("grid_emu_SS",  "grid_emu_SS",  gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  TH2D* grid_mumu_SS = new TH2D("grid_mumu_SS", "grid_mumu_SS", gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
 
  float max = .5;
#ifdef EFF
  filename += "eff";  
  cout << "Calculating efficiency"<<endl;
#endif
#ifdef EVENTS  
  filename += "evts";  
#endif
#ifdef RATE  
  filename += "rate";  
#endif
#ifdef BEFORE
  filename += "_beforecuts";  
  nCut = 1;
#endif
#ifdef AFTER
  filename += "_aftercuts";  
  nCut = -1;
#endif
  c1->Divide(3,2);

  c1->cd(1);

  cout << "EE OS after MET > 150 GeV cut  " << endl;
  add(0, 90, histo_string, histo_syst_string, 22, nCutRef, grid_ee_OS); 
#ifdef MASS
  draw_mass(grid_ee_OS, max, "ee OS"); 
  filename += "_mass_channel";
#else
  draw(grid_ee_OS, max, "ee OS"); 
#endif

  c1->cd(2);

  cout << "EMU OS after MET > 150 GeV cut  " << endl;
  add(0, 90, histo_string, histo_syst_string, 41, nCutRef, grid_emu_OS); 
#ifdef MASS
  draw_mass(grid_emu_OS, max, "e#mu OS"); 
#else
  draw(grid_emu_OS, max, "e#mu OS"); 
#endif

  c1->cd(3);
  
  cout << "MUMU OS after MET > 150 GeV cut  " << endl;
  add(0, 90, histo_string, histo_syst_string, 50, nCutRef, grid_mumu_OS); 
#ifdef MASS
  draw_mass(grid_mumu_OS, max, "#mu#mu OS"); 
#else
  draw(grid_mumu_OS, max, "#mu#mu OS"); 
#endif

  c1->cd(4);

  cout << "EE SS after MET > 100 GeV cut  " << endl;
  add(0, 90, histo_string, histo_syst_string, 25, nCutRef, grid_ee_SS); 
#ifdef MASS
  draw_mass(grid_ee_SS, max, "ee SS"); 
#else
  draw(grid_ee_SS, max, "ee SS"); 
#endif

  c1->cd(5);

  cout << "EMU SS after MET > 100 GeV cut  " << endl;
  add(0, 90, histo_string, histo_syst_string, 44, nCutRef, grid_emu_SS); 
#ifdef MASS
  draw_mass(grid_emu_SS, max, "e#mu SS"); 
#else
  draw(grid_emu_SS, max, "e#mu SS"); 
#endif

  c1->cd(6);
  
  cout << "MUMU SS after MET > 100 GeV cut  " << endl;
  add(0, 90, histo_string, histo_syst_string, 53, nCutRef, grid_mumu_SS); 
#ifdef MASS
  draw_mass(grid_mumu_SS, max, "#mu#mu SS"); 
#else
  draw(grid_mumu_SS, max, "#mu#mu SS"); 
#endif

#endif

#ifdef XIMO  
   
  TCanvas *c1 = new TCanvas("canvas","canvas", 200,10,1500,1500);  // 1D histo

  TH2D* grid_MET100_OS = new TH2D("grid_MET100_OS", "grid_MET100_OS",   gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  TH2D* grid_MET100_SS = new TH2D("grid_MET100_SS", "grid_MET100_SS",  gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  TH2D* grid_MET150_OS = new TH2D("grid_MET150_OS", "grid_MET150_OS", gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);

  TH2D* grid_MET100_ee_OS = new TH2D("grid_MET100_ee_OS", "grid_MET100_ee_OS",   gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  TH2D* grid_MET100_ee_SS = new TH2D("grid_MET100_ee_SS", "grid_MET100_ee_SS",  gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  TH2D* grid_MET100_em_OS = new TH2D("grid_MET100_em_OS", "grid_MET100_em_OS",   gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  TH2D* grid_MET100_em_SS = new TH2D("grid_MET100_em_SS", "grid_MET100_em_SS",  gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  TH2D* grid_MET100_mm_OS = new TH2D("grid_MET100_mm_OS", "grid_MET100_mm_OS",   gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  TH2D* grid_MET100_mm_SS = new TH2D("grid_MET100_mm_SS", "grid_MET100_mm_SS",  gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
 
  float max = .5;
#ifdef EFF
  filename += "eff";  
  cout << "Calculating efficiency"<<endl;
#endif
#ifdef EVENTS  
  filename += "evts";  
#endif
#ifdef RATE  
  filename += "rate";  
#endif
#ifdef BEFORE
  filename += "_beforecuts";  
  nCut = 1;
#endif
#ifdef AFTER
  filename += "_aftercuts";  
  nCut = -1;
#endif
  c1->Divide(3,3);

  c1->cd(1);

  cout << "OS after MET > 100 GeV cut  " << endl;
  add(0, 90, histo_string, histo_syst_string, -4, nCutRef, grid_MET100_OS); 
  draw(grid_MET100_OS, max, "OS MET > 100"); 

  c1->cd(2);

  cout << "OS after MET > 150 GeV cut  " << endl;
  add(0, 90, histo_string, histo_syst_string, -2, nCutRef, grid_MET150_OS); 
  draw(grid_MET150_OS, max, "OS MET > 150"); 

  c1->cd(3);
  
  cout << "SS after MET > 100 GeV cut  " << endl;
  add(0, 90, histo_string, histo_syst_string, -3, nCutRef, grid_MET100_SS); 
  draw(grid_MET100_SS, max, "SS MET > 100"); 

  c1->cd(4);

  cout << "ee OS after MET > 100 GeV cut  " << endl;
  add(0, 90, histo_string, histo_syst_string, 20, nCutRef, grid_MET100_ee_OS); 
  draw(grid_MET100_ee_OS, max, "ee OS MET > 100"); 

  c1->cd(7);

  cout << "ee SS after MET > 100 GeV cut  " << endl;
  add(0, 90, histo_string, histo_syst_string, 25, nCutRef, grid_MET100_ee_SS); 
  draw(grid_MET100_ee_SS, max, "ee SS MET > 100"); 

  c1->cd(5);
  
  cout << "emu OS after MET > 100 GeV cut  " << endl;
  add(0, 90, histo_string, histo_syst_string, 39, nCutRef, grid_MET100_em_OS); 
  draw(grid_MET100_em_OS, max, "emu OS MET > 100"); 

  c1->cd(8);
  
  cout << "emu SS after MET > 100 GeV cut  " << endl;
  add(0, 90, histo_string, histo_syst_string, 44, nCutRef, grid_MET100_em_SS); 
  draw(grid_MET100_em_SS, max, "emu SS MET > 100"); 

  c1->cd(6);
  
  cout << "mumu OS after MET > 100 GeV cut  " << endl;
  add(0, 90, histo_string, histo_syst_string, 48, nCutRef, grid_MET100_mm_OS); 
  draw(grid_MET100_mm_OS, max, "mumu OS MET > 100"); 

  c1->cd(9);
  
  cout << "mumu SS after MET > 100 GeV cut  " << endl;
  add(0, 90, histo_string, histo_syst_string, 53, nCutRef, grid_MET100_mm_SS); 
  draw(grid_MET100_mm_SS, max, "mumu SS MET > 100"); 

  TFile* Target = new TFile(filename+".root", "RECREATE");

  grid_MET100_SS->Write();
  grid_MET100_OS->Write();
  grid_MET150_OS->Write();
  grid_MET100_ee_OS->Write();
  grid_MET100_ee_SS->Write();
  grid_MET100_em_OS->Write();
  grid_MET100_em_SS->Write();
  grid_MET100_mm_OS->Write();
  grid_MET100_mm_SS->Write();

  Target->Close();
#endif

#ifdef ONE  
  //only one plot  
  TCanvas *c1 = new TCanvas("canvas","canvas", 200,10,800,600);  // 1D histo
  c1->cd();

  float max = .5;
  nCut = 1;
  nCutRef = 1;
//  draw(0, 90, histo_string, histo_syst_string, nCut, nCutRef, max, ""); //all processes
  TH2D* grid_all = new TH2D("grid_all", "grid_all", gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  add(0, 90, histo_string, histo_syst_string, nCut, nCutRef, grid_all); 
  draw(grid_all, max, ""); 
#endif

#ifdef SYST 
  filename = "syst/TM_msugra_error";  
#ifdef OS
  filename += "_OS"; 
#endif
#ifdef SS
  filename += "_SS"; 
#endif
#ifdef JESMINUS 
  filename += "_jesminus"; 
#endif
#ifdef JER
  filename += "_jer"; 
#endif
#ifdef JESPLUS 
  filename += "_jesplus"; 
#endif
#ifdef ELERECO 
  filename += "_elereco"; 
#endif
#ifdef MUORECO 
  filename += "_muoreco"; 
#endif
  TFile* Target = new TFile(filename+".root", "RECREATE");
  SystError_grid_MET60_SS->Write();
  SystError_grid_MET80_SS->Write();
  SystError_grid_MET100_SS->Write();
  SystError_grid_MET100_OS->Write();
  SystError_grid_MET125_OS->Write();
  SystError_grid_MET150_OS->Write();

  SystError_grid_MET60_ee_SS->Write();
  SystError_grid_MET80_ee_SS->Write();
  SystError_grid_MET100_ee_SS->Write();
  SystError_grid_MET100_ee_OS->Write();
  SystError_grid_MET125_ee_OS->Write();
  SystError_grid_MET150_ee_OS->Write();

  SystError_grid_MET60_emu_SS->Write();
  SystError_grid_MET80_emu_SS->Write();
  SystError_grid_MET100_emu_SS->Write();
  SystError_grid_MET100_emu_OS->Write();
  SystError_grid_MET125_emu_OS->Write();
  SystError_grid_MET150_emu_OS->Write();

  SystError_grid_MET60_mumu_SS->Write();
  SystError_grid_MET80_mumu_SS->Write();
  SystError_grid_MET100_mumu_SS->Write();
  SystError_grid_MET100_mumu_OS->Write();
  SystError_grid_MET125_mumu_OS->Write();
  SystError_grid_MET150_mumu_OS->Write();
  Target->Close();
#else
  filename += "one";
#endif

#endif

/*  Divide by processes */
//  nCut = 19;
//  filename += "total_ee_OS_MET100_eff.pdf";    
//  nCut = 24;
//  filename += "total_ee_SS_MET100_eff.pdf";    

//  nCut = 38;
//  filename += "total_emu_OS_MET100_eff.pdf";    
//  nCut = 43;
//  filename += "total_emu_SS_MET100_eff.pdf";    
  
//  nCut = 47;
//  filename += "total_mumu_OS_MET100_eff.pdf";    
//  nCut = 52;
//  filename += "total_mumu_SS_MET100_eff.pdf";    

#ifdef PROCESS  
  float max = 1.5;
  nCut = 1;
#ifdef EFF
  filename += "eff";  
  cout << "Calculating efficiency"<<endl;
#endif
  
#ifdef EVENTS  
  filename += "evts";  
#endif
#ifdef RATE  
  filename += "rate";  
#endif
#ifdef BEFORE
  filename += "_beforecuts";  
  nCut = 1;
#endif
#ifdef AFTER
  filename += "_aftercuts";  
  nCut = -1;
#endif

  TCanvas *c1 = new TCanvas("canvas","canvas", 200,10,1500,1000);  // 1D histo
  c1->Divide(3,3);

  TH2D* grid_all = new TH2D("grid_all", "grid_all", gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  
  c1->cd(1);
  
// ALL PROCESSES
  TH2D* grid_all = new TH2D("grid_all", "grid_all", gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  add(0, 90, histo_string, histo_syst_string, nCut, nCutRef, grid_all); 
#ifdef MASS
  draw_mass(grid_all, max, "All"); 
  filename += "_mass";
#else
  filename += "_process";
  draw(grid_all, max, "All"); 
#endif

#ifdef RATE  
  grid_allprocesses = (TH2D*)grid->Clone("grid_allprocesses");
  divide = true;
#endif
  
  c1->cd(2);
  TH2D* grid_gq = new TH2D("grid_gq", "grid_gq", gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  add(2, 2, histo_string, histo_syst_string, nCut, nCutRef, grid_gq); 
#ifdef MASS
  draw_mass(grid_gq, max, "#tilde{g}#tilde{q}"); 
#else
  draw(grid_gq, max, "#tilde{g}#tilde{q}"); // 1 gluino + 1 squark
#endif
 
  c1->cd(3);
  TH2D* grid_gg = new TH2D("grid_gg", "grid_gg", gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  add(3, 3, histo_string, histo_syst_string, nCut, nCutRef, grid_gg); 
#ifdef MASS
  draw_mass(grid_gg, max, "#tilde{g}#tilde{g}"); 
#else
  draw(grid_gg, max, "#tilde{g}#tilde{g}"); // 2 gluinos
#endif

  c1->cd(4);
  TH2D* grid_qq = new TH2D("grid_qq", "grid_qq", gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  add(4, 4, histo_string, histo_syst_string, nCut, nCutRef, grid_qq); 
#ifdef MASS
  draw_mass(grid_qq, max, "#tilde{q}#tilde{q}"); 
#else
  draw(grid_qq, max, "#tilde{q}#tilde{q}"); // 2 squarks
#endif

  c1->cd(5);
  TH2D* grid_qaq = new TH2D("grid_qaq", "grid_qaq", gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  add(5, 5, histo_string, histo_syst_string, nCut, nCutRef, grid_qaq); 
#ifdef MASS
  draw_mass(grid_qaq, max, "#tilde{q}#bar{#tilde{q}}"); 
#else
  draw(grid_qaq, max, "#tilde{q}#bar{#tilde{q}}"); // 1 squark 1 antisquark
#endif

  c1->cd(6);
  TH2D* grid_tt = new TH2D("grid_tt", "grid_tt", gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  add(52, 53, histo_string, histo_syst_string, nCut, nCutRef, grid_tt); 
#ifdef MASS
  draw_mass(grid_tt, max, "#tilde{t}#bar{#tilde{t}}"); 
#else
  draw(grid_tt, max, "#tilde{t}#bar{#tilde{t}}"); // 1 stop antistop
#endif

  c1->cd(7);
  TH2D* grid_bb = new TH2D("grid_bb", "grid_bb", gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  add(62, 63, histo_string, histo_syst_string, nCut, nCutRef, grid_bb); 
#ifdef MASS
  draw_mass(grid_bb, max, "#tilde{b}#bar{#tilde{b}}"); 
#else
  draw(grid_bb, max, "#tilde{b}#bar{#tilde{b}}"); // 1 sbottom antisbottom
#endif

  c1->cd(8);
  TH2D* grid_gchi = new TH2D("grid_gq", "grid_gchi", gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  add(72, 79, histo_string, histo_syst_string, nCut, nCutRef, grid_gchi); 
#ifdef MASS
  draw_mass(grid_gchi, max, "#tilde{g}#chi"); 
#else
  draw(grid_gchi, max, "#tilde{g}#chi"); // 1 gluino + chi
#endif

  c1->cd(9);
  TH2D* grid_qqchi = new TH2D("grid_qqchi", "grid_qqchi", gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  add(82, 89, histo_string, histo_syst_string, nCut, nCutRef, grid_qqchi); 
#ifdef MASS
  draw_mass(grid_qqchi, max, "#tilde{q}#bar{#tilde{q}}#chi"); 
#else
  draw(grid_qqchi, max, "#tilde{q}#bar{#tilde{q}}#chi"); // 1 squark 1 antisquark + chi
#endif

#endif
 
  c1->Print(filename+".eps"); 
  c1->Print(filename+".pdf"); 
}

void draw(int bin_min, int bin_max, TString hstring, TString hstring_syst, int n_cut, int n_cut_ref, float max, TString text) 
{
  
  histo_string = hstring; 
  histo_syst_string = hstring_syst;
  
  TString x_string = "cutflow";
  TString y_string = "entries";
  
  binmin = bin_min;  // all processes
  binmax = bin_max;
  nCut = n_cut;
  nCutRef = n_cut_ref;

  fillHisto();
#ifdef SYST
  fillHisto_syst();
//  grid_syst->SetMaximum(max);
//  grid_syst->SetMinimum(-0.01);
  grid_syst->SetXTitle("M_{0} [GeV]");
  grid_syst->SetYTitle("M_{1/2} [GeV]    ");
  grid_syst->GetYaxis()->SetRangeUser(80,600);  
//  grid_syst->Draw("COLZ TEXT"); 
  grid_syst->Draw("COLZ"); 
#else
//  grid->SetMaximum(max);
  if (divide) grid->Divide(grid_allprocesses);
  grid->SetXTitle("M_{0} [GeV]");
  grid->SetYTitle("M_{1/2} [GeV]    ");
  grid->GetYaxis()->SetRangeUser(80,400);  
//  grid->Draw("COLZ TEXT"); 
  grid->Draw("COLZ"); 
#endif
  TLatex n;
  n.SetNDC();
  n.SetTextFont(42);
  n.SetTextColor(kBlack);
  n.DrawLatex(0.30,0.85,text);
  
}
void draw(TH2D* h_grid, float max, TString text) 
{
  
//  grid->SetMaximum(max);
  if (divide) h_grid->Divide(grid_allprocesses);
  h_grid->SetXTitle("M_{0} [GeV]");
  h_grid->SetYTitle("M_{1/2} [GeV]    ");
  h_grid->GetYaxis()->SetRangeUser(80,600);  
//  h_grid->Draw("COLZ TEXT"); 
  h_grid->Draw("COLZ"); 

  TLatex n;
  n.SetNDC();
  n.SetTextFont(42);
  n.SetTextColor(kBlack);
  n.DrawLatex(0.30,0.85,text);
  
}

void draw_mass(TH2D* h_grid, float max, TString text) 
{
  
//  grid->SetMaximum(max);
  if (divide) h_grid->Divide(grid_allprocesses);
  
  int nbinx = 30;
  int nbiny = 40;
  double binx_min = -20.;
  double binx_max = 1180.;  
  double biny_min = 2.5.;
  double biny_max = 602.5;
    
  TH2D* grid_mass = new TH2D("grid_mass", "grid_mass", 120, 200., 1400., 80, 200., 1000.);
  
  for (int i = 1; i<nbinx+1; i++){
    
    double m0 = h_grid->GetXaxis()->GetBinCenter(i);
      //cout << "m0 " << m0 << endl;
    for (int j = 1; j<nbiny+1; j++){
      double m12 = h_grid->GetYaxis()->GetBinCenter(j);
      //cout << "m12 " << m12 << endl;
      double content = h_grid->GetBinContent(i,j);
      double msq=0.;
      double mg=0.;
      get_msq_mg(m0 , m12, &msq , &mg);
      grid_mass ->Fill(msq, mg, content);
      
    }
  }
  
  grid_mass->SetXTitle("M_{#tilde{q}} [GeV]");
  grid_mass->SetYTitle("M_{g} [GeV]	 ");
//  grid_mass->GetYaxis()->SetRangeUser(80,400);  
//grid_mass->Draw("COLZ TEXT"); 
  grid_mass->Draw("COLZ"); 

  TLatex n;
  n.SetNDC();
  n.SetTextFont(42);
  n.SetTextColor(kBlack);
  n.DrawLatex(0.60,0.85,text);
  
}

void add(int bin_min, int bin_max, TString hstring, TString hstring_syst, int n_cut, int n_cut_ref, TH2D* grid_all) 
{
  
  histo_string = hstring; 
  histo_syst_string = hstring_syst;
  
  TString x_string = "cutflow";
  TString y_string = "entries";
  
  binmin = bin_min;  // all processes
  binmax = bin_max;
  nCut = n_cut;
  nCutRef = n_cut_ref;
  
  cout << " Adding... cut : "<< nCut <<" ref. cut: "<< nCutRef << endl;
  cout << " process : "<< bin_min-1 <<"  "<< binmax-1 << endl;

  fillHisto();
#ifdef SYST
  fillHisto_syst();
  grid_all->Add(grid_syst);
#else
  grid_all->Add(grid);
#endif
  
}
