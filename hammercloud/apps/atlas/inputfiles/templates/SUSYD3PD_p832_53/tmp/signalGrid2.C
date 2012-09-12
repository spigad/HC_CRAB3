#define MC
#define MSUGRA
#define H2D

#define NORM

#define SYST

  double lumi         = 163.5; //pb	
  TString lumi_string = "163.5"; //pb	
  TString histo_string, histo_syst_string;
  int nCut, nCutRef, binmin, binmax, eff;
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
TString syst = "pileup";
#include "input_syst.h"
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
// Cut 10   && OS && MET  > 150 GeV 
// Cut 11   && OS && MET  > 250 GeV 
// Cut 12   && OS && 4 jets 100, 70, 70, 70 GeV
// Cut 13   && OS && MET  > 100 GeV + 4 jets 100, 70, 70, 70 GeV
// Cut 14   && OS && 3 jets 80, 40, 40 GeV
// Cut 15   && OS && MET  > 220 GeV + 3 jets 80, 40, 40 GeV
// Cut 16   && SS 
// Cut 17   && SS && MET  > 100 GeV 
// Cut 18   && SS && 2 jets 50, 50 GeV
// Cut 19   && SS && MET  > 80 GeV + 2 jets 50, 50 GeV
// Cut 20  	EMU 
// Cut 21  	 && mll > 5 GeV
// Cut 22  	 && OS 
// Cut 23   && OS && MET  > 150 GeV 
// Cut 24   && OS && MET  > 250 GeV 
// Cut 25   && OS && 4 jets 100, 70, 70, 70 GeV
// Cut 26   && OS && MET  > 100 GeV + 4 jets 100, 70, 70, 70 GeV
// Cut 27  	 && OS && 3 jets 80, 40, 40 GeV
// Cut 28   && OS && MET  > 220 GeV + 3 jets 80, 40, 40 GeV
// Cut 29  	 && SS 
// Cut 30  	 && SS && MET  > 100 GeV 
// Cut 31  	 && SS && 2 jets 50, 50 GeV
// Cut 32  	 && SS && MET  > 80 GeV + 2 jets 50, 50 GeV
// Cut 33  	MUMU 
// Cut 34  	 && mll > 5 GeV
// Cut 35  	 && OS 
// Cut 36   && OS && MET  > 150 GeV 
// Cut 37   && OS && MET  > 250 GeV 
// Cut 38   && OS && 4 jets 100, 70, 70, 70 GeV
// Cut 39   && OS && MET  > 100 GeV + 4 jets 100, 70, 70, 70 GeV
// Cut 40   && OS && 3 jets 80, 40, 40 GeV
// Cut 41   && OS && MET  > 220 GeV + 3 jets 80, 40, 40 GeV
// Cut 42  	 && SS 
// Cut 43   && SS && MET  > 100 GeV 
// Cut 44  	 && SS && 2 jets 50, 50 GeV
// Cut 45   && SS && MET  > 80 GeV + 2 jets 50, 50 GeV

char const*  name_cutflow[]={
  "no cut",
  "GRL cut",
  "trigger cut (trgEl || trgMu)",
  "jet cleaning (disabled on MC)",
  ">= 1 vertex with > 4 tracks",
  "Event veto (crack + cosmics)",
  "MUMU + EE + EMU", 

  "EE", 
  "EE, mll > 5 GeV",
  "EE, OS ",
//  ", OS,  TightIso",
  "EE, OS, MET > 150 GeV ",
  "EE, OS, MET > 250 GeV ",
  "EE, OS, 4 jets 100, 70, 70, 70 GeV",
  "EE, OS, MET > 100 GeV + 4 jets 100, 70, 70, 70 GeV",
  "EE, OS, 3 jets 80, 40, 40 GeV",
  "EE, OS, MET > 220 GeV + 3 jets 80, 40, 40 GeV",
  "EE, SS ",
  "EE, SS, MET > 100 GeV ",
  "EE, SS, 2 jets 50, 50 GeV",
  "EE, SS, MET > 80 GeV + 2 jets 50, 50 GeV",
    
  "EMU ", 
  "EMU,  mll > 5 GeV",
  "EMU,  OS ",
//  ",  OS,  TightIso",
  "EMU, OS, MET > 150 GeV ",
  "EMU, OS, MET > 250 GeV ",
  "EMU, OS, 4 jets 100, 70, 70, 70 GeV",
  "EMU, OS, MET > 100 GeV + 4 jets 100, 70, 70, 70 GeV",
  "EMU, OS, 3 jets 80, 40, 40 GeV",
  "EMU, OS, MET > 220 GeV + 3 jets 80, 40, 40 GeV",
  "EMU, SS ",
  "EMU, SS, MET > 100 GeV ",
  "EMU, SS, 2 jets 50, 50 GeV",
  "EMU, SS, MET > 80 GeV + 2 jets 50, 50 GeV",

  "MUMU ", 
  "MUMU, mll > 5 GeV", 
  "MUMU, OS ",
  "MUMU, OS, MET > 150 GeV ",
  "MUMU, OS, MET > 250 GeV ",
  "MUMU, OS, 4 jets 100, 70, 70, 70 GeV",
  "MUMU, OS, MET > 100 GeV + 4 jets 100, 70, 70, 70 GeV",
  "MUMU, OS, 3 jets 80, 40, 40 GeV",
  "MUMU, OS, MET > 220 GeV + 3 jets 80, 40, 40 GeV",
  "MUMU, SS ",
  "MUMU, SS, MET > 100 GeV ",
  "MUMU, SS, 2 jets 50, 50 GeV",
  "MUMU, SS, MET > 80 GeV + 2 jets 50, 50 GeV",
  };

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

void signalGrid2() {

// plot 
  std::cout << "lumi " << lumi <<" pb-1"<< std::endl;  
  std::cout << "Opening files " << prefix << std::endl;  
  
  gROOT->SetStyle("ATLAS");
  SetAtlasStyle();
  gROOT->ForceStyle();

  TCanvas *c1  = new TCanvas("canvas1","canvas1", 200,10,1500,1000);  // 1D histo
  TCanvas *c2  = new TCanvas("canvas2","canvas2", 200,10,1500,1000);  // 1D histo
  TCanvas *c3  = new TCanvas("canvas3","canvas3", 200,10,1500,1000);  // 1D histo
  TCanvas *c4  = new TCanvas("canvas4","canvas4", 200,10,1500,1000);  // 1D histo
  TCanvas *c5  = new TCanvas("canvas5","canvas5", 200,10,1500,1000);  // 1D histo
  TCanvas *c6  = new TCanvas("canvas6","canvas6", 200,10,1500,1000);  // 1D histo
  TCanvas *c7  = new TCanvas("canvas7","canvas7", 200,10,1500,1000);  // 1D histo
  TCanvas *c8  = new TCanvas("canvas8","canvas8", 200,10,1500,1000);  // 1D histo
  TCanvas *c9  = new TCanvas("canvas9","canvas9", 200,10,1500,1000);  // 1D histo
  TCanvas *c10 = new TCanvas("canvas10","canvas10", 200,10,1500,1000);  // 1D histo
  TCanvas *c11 = new TCanvas("canvas11","canvas11", 200,10,1500,1000);  // 1D histo
  TCanvas *c12 = new TCanvas("canvas12","canvas12", 200,10,1500,1000);  // 1D histo
  TCanvas *c13 = new TCanvas("canvas13","canvas13", 200,10,1500,1000);  // 1D histo
  TCanvas *c14 = new TCanvas("canvas14","canvas14", 200,10,1500,1000);  // 1D histo
  TCanvas *c15 = new TCanvas("canvas15","canvas15", 200,10,1500,1000);  // 1D histo

/******************************************

    INPUTS TO BE CHOSEN : efficiency, number of events, process

********************************************/


//   int efficiency = 1;   // plot efficiency
   int efficiency = 0;  //plot number of events

   // choose process below:

   //all
   TString process = "";
   int proc_min = 0;
   int proc_max = 90;
/*   //gluino-squark
   TString process = "_gq";
   int proc_min = 2;
   int proc_max = 2;
*//*   //gluino-gluino
   TString process = "_gg";
   int proc_min = 3;
   int proc_max = 3;
*//*   //squark-squark
   TString process = "_qq";
   int proc_min = 4;
   int proc_max = 4;
   //squark-antisquark
   TString process = "_qaq";
   int proc_min = 5;
   int proc_max = 5;*/
/* 
   //stop
   TString process = "_tt";
   int proc_min = 52;
   int proc_max = 53;

   //sbottom
   TString process = "_bb";
   int proc_min = 62;
   int proc_max = 63;

   // chi gluino
   TString process = "_gchi";
   int proc_min = 72;
   int proc_max = 79;

   // chi squark-squark
   TString process = "_qqchi";
   int proc_min = 82;
   int proc_max = 89;
*/
//   signalGrid(c1, 1, 10, proc_min, proc_max, efficiency, process); //eff ee OS to compare with Andreas  

   signalGrid(c1, 1, 12, proc_min, proc_max, efficiency, process); //eff ee OS MET  250 GeV
/*   signalGrid(c2, 1, 14, proc_min, proc_max, efficiency, process); //eff ee OS 4 jets 100, 70, 70, 70 GeV + MET > 100 GeV
   signalGrid(c3, 1, 16, proc_min, proc_max, efficiency, process); //eff ee OS 3 jets 80, 40, 40 GeV + MET > 220 GeV
   signalGrid(c4, 1, 18, proc_min, proc_max, efficiency, process); //eff ee SS MET > 100 GeV
   signalGrid(c5, 1, 20, proc_min, proc_max, efficiency, process); //eff ee SS 2 jets 50, 50 GeV + MET > 80 GeV
   
   signalGrid(c6,  1, 12 + 13, proc_min, proc_max, efficiency, process); //eff emu OS MET  250 GeV
   signalGrid(c7,  1, 14 + 13, proc_min, proc_max, efficiency, process); //eff emu OS 4 jets 100, 70, 70, 70 GeV + MET > 100 GeV
   signalGrid(c8,  1, 16 + 13, proc_min, proc_max, efficiency, process); //eff emu OS 3 jets 80, 40, 40 GeV + MET > 220 GeV
   signalGrid(c9,  1, 18 + 13, proc_min, proc_max, efficiency, process); //eff emu SS MET > 100 GeV
   signalGrid(c10, 1, 20 + 13, proc_min, proc_max, efficiency, process); //eff emu SS 2 jets 50, 50 GeV + MET > 80 GeV

   signalGrid(c11, 1, 12 + 13*2, proc_min, proc_max, efficiency, process); //eff mumu OS MET  250 GeV
   signalGrid(c12, 1, 14 + 13*2, proc_min, proc_max, efficiency, process); //eff mumu OS 4 jets 100, 70, 70, 70 GeV + MET > 100 GeV
   signalGrid(c13, 1, 16 + 13*2, proc_min, proc_max, efficiency, process); //eff mumu OS 3 jets 80, 40, 40 GeV + MET > 220 GeV
   signalGrid(c14, 1, 18 + 13*2, proc_min, proc_max, efficiency, process); //eff mumu SS MET > 100 GeV
   signalGrid(c15, 1, 20 + 13*2, proc_min, proc_max, efficiency, process); //eff mumu SS 2 jets 50, 50 GeV + MET > 80 GeV
*/   
}


void signalGrid(TCanvas *c1, int nCutRef, int nCut, int process_min, int process_max, int efficiency, TString process) {

  eff = efficiency;
       
  histo_string = "h_cutflow_susy";
  histo_syst_string = "h_cutflow_susy";
  TString filename = "TM_msugra_";

  if (eff){
     filename += "eff";  
     cout << "Calculating efficiency"<<endl;
     float max = .5;
  } else {
#ifdef SYST
     filename += syst;
     cout << "Calculating systematics "<<syst<<endl;    
#else
     filename += "evt";
     c1->SetLogz();  
     cout << "Calculating # events"<<endl;    
#endif
     float max = .5;
  }
  
  c1->cd();

  filename += "_" +inttostr(nCutRef) + "_"+inttostr(nCut);  

  TH2D* grid1 = new TH2D(filename, filename, gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  add(process_min, process_max, histo_string, histo_syst_string, nCut, nCutRef, grid1); 
  draw(grid1, max, name_cutflow[nCut-1]); 

  TFile* Target = new TFile("plots/"+filename+".root", "RECREATE");
  grid1->Write();
  Target->Close();
 
  c1->Print("plots/"+filename+process+".eps"); 
  c1->Print("plots/"+filename+process+".pdf"); 
}


void draw(TH2D* h_grid, float max, TString text) 
{
  
//  grid->SetMaximum(max);
  if (divide) h_grid->Divide(grid_allprocesses);
  h_grid->SetXTitle("M_{0} [GeV]");
  h_grid->SetYTitle("M_{1/2} [GeV]    ");
  h_grid->GetYaxis()->SetRangeUser(0,700);  
//  h_grid->Draw("COLZ TEXT"); 
//  h_grid->Draw("COLZ"); 
  h_grid->SetMarkerSize(0.9);
  h_grid->Draw("text45colz");

  TLatex n;
  n.SetNDC();
  n.SetTextFont(42);
  n.SetTextSize(.04);
  n.SetTextColor(kBlack);
  n.DrawLatex(0.02,0.95,text);
  
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
  
  if (eff) cout << " ref. cut: "<< nCutRef << " "<<name_cutflow[nCutRef-1]<< endl;
  cout << " cut : "<< nCut << " "<<name_cutflow[nCut-1]<<endl;
  cout << " process : "<< bin_min-1 <<"  "<< binmax-1 << endl;

  fillHisto();
#ifdef SYST
  fillHisto_syst();
  grid_all->Add(grid_syst);
#else
  grid_all->Add(grid);
#endif
  
}
std::string inttostr ( int integer )
{
	std::string s;
	std::stringstream out;
	out << integer;
	return  out.str();
}

std::string doubletostr ( double integer )
{
	std::string s;
	std::stringstream out;
	out << integer;
	return  out.str();
}
