#define matrix_cxx
#include "matrix.h"
#include <TH2.h>
#include <TH1.h>
#include <TMath.h>
#include <TStyle.h>
#include <TCanvas.h>


/*

                TO RUN IN ROOT:
		--------------
		
		.L matrix.C
		matrix t; t.Loop(); 

*/


void matrix::Loop()
{
  int ncut = 60;
    
  TH1F* cutflow_histo  = new TH1F("cutflow_histo","cutflow_histo",ncut+1,0,ncut);    
  TH1F* runNumber_histo = new TH1F("runNumber_histo","runNumber_histo",200001,100000,300000);   

  TH2F* h_jetl_pt     = new TH2F("h_jetl_pt",  "h_jetl_pt",    ncut+1, 0, ncut, 120,     0, 600.);
  TH2F* h_met         = new TH2F("h_met",        "h_met",	     ncut+1, 0, ncut, 120, 0, 600.);
  TH2F* h_mt          = new TH2F("h_mt",         "h_mt",         ncut+1, 0, ncut, 120, 0, 600.);
  TH2F* h_invmass     = new TH2F("h_invmass",    "h_invmass",    ncut+1, 0, ncut, 120, 0, 600.);
  TH2F* h_nGoodPV     = new TH2F("h_nGoodPV",    "h_nGoodPV",    ncut+1, 0, ncut, 20, 0, 19.);
  
  
//   In a ROOT session, you can do:
//      Root > .L matrix.C
//      Root > matrix t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   //nentries = 10000;
   int nbin = 0;
   int offset = 0;
   Long64_t nbytes = 0, nb = 0;
   
    fChain->SetBranchStatus("*",0);  // disable all branches
    fChain->SetBranchStatus("jet_n",1);  // activate branchname
    fChain->SetBranchStatus("jet_pt",1);  // activate branchname
    fChain->SetBranchStatus("MET",1);  // activate branchname
    fChain->SetBranchStatus("METx",1);  // activate branchname
    fChain->SetBranchStatus("METy",1);  // activate branchname
    fChain->SetBranchStatus("lep_pt",1);  // activate branchname
    fChain->SetBranchStatus("lep_phi",1);  // activate branchname
    fChain->SetBranchStatus("arrw_ff",1);  // activate branchname
    fChain->SetBranchStatus("EE",1);  // activate branchname
    fChain->SetBranchStatus("EM",1);  // activate branchname
    fChain->SetBranchStatus("ME",1);  // activate branchname
    fChain->SetBranchStatus("MM",1);  // activate branchname
    fChain->SetBranchStatus("OS",1);  // activate branchname
    fChain->SetBranchStatus("SS",1);  // activate branchname
   
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
   
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
   
      nb = fChain->GetEntry(jentry);   
      nbytes += nb;
      Float_t mc_event_weight = arrw_ff[0];
      
      if (jentry % 1000 == 0) cout << "reading event "<<jentry<<" weight "<< mc_event_weight <<endl;
      
      nbin = 1;
      runNumber_histo->Fill(105000);
      
      //signal regions

      int nJet100 =  0;
      int nJet80 =  0;
      int nJet70 =  0;
      int nJet50 =  0;
      int nJet40 =  0;
      float GeV = 1000.;
      
      //cout << "total jets: "<<jet_n <<endl;       
      
      if (jet_n)    
        for (unsigned int iJet = 0; iJet < jet_n; iJet++)   { 
	
        //  cout << "jet " << iJet << " pt " << jet_pt[iJet] <<endl;
	  float pt =  jet_pt->at(0);
         // cout << "jet " << iJet  << " pt " << pt<<endl; 
        
	  if (jet_pt->at(iJet)> 100 * GeV) nJet100++;	   
          if (jet_pt->at(iJet)>  80 * GeV) nJet80++;	  
          if (jet_pt->at(iJet)>  70 * GeV) nJet70++;	  
          if (jet_pt->at(iJet)>  50 * GeV) nJet50++;	  
          if (jet_pt->at(iJet)>  40 * GeV) nJet40++;	  
      }//end loop over jets

      //transverse mass
      float metPhi = atan2(-METy,-METx);
      float m_T = -1;
      if (lep_mll>0.){
        float l_pt = lep_pt->at(0);
        float l_phi = lep_phi->at(0);
        m_T = sqrt(2.*MET*l_pt*(1. - cos(l_phi-metPhi)));      
      }
      
      
      cutflow_histo ->Fill(nbin+offset,             mc_event_weight);
      h_met         ->Fill(nbin+offset, MET/1000.,  mc_event_weight);
      h_invmass     ->Fill(nbin+offset, lep_mll,    mc_event_weight);
      h_nGoodPV     ->Fill(nbin+offset, prim_vtx_n, mc_event_weight);
      h_mt          ->Fill(nbin+offset, m_T/1000.,  mc_event_weight);
      h_jetl_pt	    ->Fill(nbin+offset, pt/1000., mc_event_weight);
      
           
      if( (EE) ){                                                     // EE case 
        if (OS)  {
	  
	  nbin = 12;
	  offset = 0;
	  
	  //cout << "EE OS"<<endl;
	  
          cutflow_histo ->Fill(nbin+offset,             mc_event_weight);
          h_met         ->Fill(nbin+offset, MET/1000.,  mc_event_weight);
          h_invmass     ->Fill(nbin+offset, lep_mll,    mc_event_weight);
          h_nGoodPV     ->Fill(nbin+offset, prim_vtx_n, mc_event_weight);
          h_mt          ->Fill(nbin+offset, m_T/1000.,  mc_event_weight);
          h_jetl_pt	->Fill(nbin+offset, pt/1000.,   mc_event_weight);
          
	  
	  if ((nJet100>=1)&&(nJet70>=4)){
	  
	    offset = 3;

            cutflow_histo ->Fill(nbin+offset,             mc_event_weight);
            h_met         ->Fill(nbin+offset, MET/1000.,  mc_event_weight);
            h_invmass     ->Fill(nbin+offset, lep_mll,    mc_event_weight);
            h_nGoodPV     ->Fill(nbin+offset, prim_vtx_n, mc_event_weight);
            h_mt          ->Fill(nbin+offset, m_T/1000.,  mc_event_weight);
            h_jetl_pt	  ->Fill(nbin+offset, pt/1000.,   mc_event_weight);
          	  
	  }	  
	  if ((nJet80>=1)&&(nJet40>=3)){
	  
	    offset = 5;

            cutflow_histo ->Fill(nbin+offset,             mc_event_weight);
            h_met         ->Fill(nbin+offset, MET/1000.,  mc_event_weight);
            h_invmass     ->Fill(nbin+offset, lep_mll,    mc_event_weight);
            h_nGoodPV     ->Fill(nbin+offset, prim_vtx_n, mc_event_weight);
            h_mt          ->Fill(nbin+offset, m_T/1000.,  mc_event_weight);
            h_jetl_pt	  ->Fill(nbin+offset, pt/1000.,   mc_event_weight);
	  
	  }        
	
	} else {                                                    // EE SS
	
	  nbin = 19;
	  offset = 0;

          cutflow_histo ->Fill(nbin+offset,             mc_event_weight);
          h_met         ->Fill(nbin+offset, MET/1000.,  mc_event_weight);
          h_invmass     ->Fill(nbin+offset, lep_mll,    mc_event_weight);
          h_nGoodPV     ->Fill(nbin+offset, prim_vtx_n, mc_event_weight);
          h_mt          ->Fill(nbin+offset, m_T/1000.,  mc_event_weight);
          h_jetl_pt	->Fill(nbin+offset, pt/1000.,   mc_event_weight);
	  
	  if (nJet50>=2){
	  
	    offset = 2;

            cutflow_histo ->Fill(nbin+offset,             mc_event_weight);
            h_met         ->Fill(nbin+offset, MET/1000.,  mc_event_weight);
            h_invmass     ->Fill(nbin+offset, lep_mll,    mc_event_weight);
            h_nGoodPV     ->Fill(nbin+offset, prim_vtx_n, mc_event_weight);
            h_mt          ->Fill(nbin+offset, m_T/1000.,  mc_event_weight);
            h_jetl_pt	  ->Fill(nbin+offset, pt/1000.,   mc_event_weight);
	  
	  }        
	
	}
      }
      
      if( (EM||ME) ){                                                   // EMU case
        if (OS)  {
	
	  nbin = 25;
	  offset = 0;

          cutflow_histo ->Fill(nbin+offset,             mc_event_weight);
          h_met         ->Fill(nbin+offset, MET/1000.,  mc_event_weight);
          h_invmass     ->Fill(nbin+offset, lep_mll,    mc_event_weight);
          h_nGoodPV     ->Fill(nbin+offset, prim_vtx_n, mc_event_weight);
          h_mt          ->Fill(nbin+offset, m_T/1000.,  mc_event_weight);
          h_jetl_pt	->Fill(nbin+offset, pt/1000.,   mc_event_weight);

	  if ((nJet100>=1)&&(nJet70>=4)){
	  
	    offset = 3;

            cutflow_histo ->Fill(nbin+offset,             mc_event_weight);
            h_met         ->Fill(nbin+offset, MET/1000.,  mc_event_weight);
            h_invmass     ->Fill(nbin+offset, lep_mll,    mc_event_weight);
            h_nGoodPV     ->Fill(nbin+offset, prim_vtx_n, mc_event_weight);
            h_mt          ->Fill(nbin+offset, m_T/1000.,  mc_event_weight);
            h_jetl_pt	  ->Fill(nbin+offset, pt/1000.,   mc_event_weight);
          	  
	  }	  
	  if ((nJet80>=1)&&(nJet40>=3)){
	  
	    offset = 5;

            cutflow_histo ->Fill(nbin+offset,             mc_event_weight);
            h_met         ->Fill(nbin+offset, MET/1000.,  mc_event_weight);
            h_invmass     ->Fill(nbin+offset, lep_mll,    mc_event_weight);
            h_nGoodPV     ->Fill(nbin+offset, prim_vtx_n, mc_event_weight);
            h_mt          ->Fill(nbin+offset, m_T/1000.,  mc_event_weight);
            h_jetl_pt	  ->Fill(nbin+offset, pt/1000.,   mc_event_weight);
	  
	  }        

        } else {                                                  // EMU SS

	  nbin = 32;	  
	  offset = 0;

          cutflow_histo ->Fill(nbin+offset,             mc_event_weight);
          h_met         ->Fill(nbin+offset, MET/1000.,  mc_event_weight);
          h_invmass     ->Fill(nbin+offset, lep_mll,    mc_event_weight);
          h_nGoodPV     ->Fill(nbin+offset, prim_vtx_n, mc_event_weight);
          h_mt          ->Fill(nbin+offset, m_T/1000.,  mc_event_weight);
          h_jetl_pt	->Fill(nbin+offset, pt/1000.,   mc_event_weight);

	  
	  if (nJet50>=2){
	  
	    offset = 2;

            cutflow_histo ->Fill(nbin+offset,             mc_event_weight);
            h_met         ->Fill(nbin+offset, MET/1000.,  mc_event_weight);
            h_invmass     ->Fill(nbin+offset, lep_mll,    mc_event_weight);
            h_nGoodPV     ->Fill(nbin+offset, prim_vtx_n, mc_event_weight);
            h_mt          ->Fill(nbin+offset, m_T/1000.,  mc_event_weight);
            h_jetl_pt     ->Fill(nbin+offset, pt/1000.,   mc_event_weight);
	  
	  }        
	
	}
      }
      
      if( (MM) ){                                                  // MUMU case
        if (OS)  {

	  nbin = 38;
	  offset = 0;

          cutflow_histo ->Fill(nbin+offset,             mc_event_weight);
          h_met         ->Fill(nbin+offset, MET/1000.,  mc_event_weight);
          h_invmass     ->Fill(nbin+offset, lep_mll,    mc_event_weight);
          h_nGoodPV     ->Fill(nbin+offset, prim_vtx_n, mc_event_weight);
          h_mt          ->Fill(nbin+offset, m_T/1000.,  mc_event_weight);
          h_jetl_pt	->Fill(nbin+offset, pt/1000.,   mc_event_weight);

	  if ((nJet100>=1)&&(nJet70>=4)){
	  
	    offset = 3;

            cutflow_histo ->Fill(nbin+offset,             mc_event_weight);
            h_met         ->Fill(nbin+offset, MET/1000.,  mc_event_weight);
            h_invmass     ->Fill(nbin+offset, lep_mll,    mc_event_weight);
            h_nGoodPV     ->Fill(nbin+offset, prim_vtx_n, mc_event_weight);
            h_mt          ->Fill(nbin+offset, m_T/1000.,  mc_event_weight);
            h_jetl_pt	  ->Fill(nbin+offset, pt/1000.,   mc_event_weight);
          	  
	  }	  
	  if ((nJet80>=1)&&(nJet40>=3)){
	  
	    offset = 5;

            cutflow_histo ->Fill(nbin+offset,             mc_event_weight);
            h_met         ->Fill(nbin+offset, MET/1000.,  mc_event_weight);
            h_invmass     ->Fill(nbin+offset, lep_mll,    mc_event_weight);
            h_nGoodPV     ->Fill(nbin+offset, prim_vtx_n, mc_event_weight);
            h_mt          ->Fill(nbin+offset, m_T/1000.,  mc_event_weight);
            h_jetl_pt	  ->Fill(nbin+offset, pt/1000.,   mc_event_weight);
	  
	  }        

        } else {                                                  // MUMU SS

	  nbin = 45;
	  offset = 0;

          cutflow_histo ->Fill(nbin+offset,             mc_event_weight);
          h_met         ->Fill(nbin+offset, MET/1000.,  mc_event_weight);
          h_invmass     ->Fill(nbin+offset, lep_mll,    mc_event_weight);
          h_nGoodPV     ->Fill(nbin+offset, prim_vtx_n, mc_event_weight);
          h_mt          ->Fill(nbin+offset, m_T/1000.,  mc_event_weight);
          h_jetl_pt	->Fill(nbin+offset, pt/1000.,   mc_event_weight);
	  
	  if (nJet50>=2){
	  
	    offset = 2;

            cutflow_histo ->Fill(nbin+offset,             mc_event_weight);
            h_met         ->Fill(nbin+offset, MET/1000.,  mc_event_weight);
            h_invmass     ->Fill(nbin+offset, lep_mll,    mc_event_weight);
            h_nGoodPV     ->Fill(nbin+offset, prim_vtx_n, mc_event_weight);
            h_mt          ->Fill(nbin+offset, m_T/1000.,  mc_event_weight);
            h_jetl_pt	  ->Fill(nbin+offset, pt/1000.,   mc_event_weight);
	  
	  }        
	
	}
      }


      // if (Cut(ientry) < 0) continue;
   }

  TFile* Target = new TFile("root/result_105000.root", "RECREATE");

  h_nGoodPV   ->Write(); 
  cutflow_histo->Write();
  runNumber_histo->Write();
  h_jetl_pt->Write();
  h_met->Write();
  h_invmass->Write();
  h_mt->Write();
  
  Target->Close();
  h_met->Draw();
   
}
