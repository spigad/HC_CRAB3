//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Aug  3 19:15:46 2011 by ROOT version 5.28/00d
// from TTree matrix/Output from matrix method
// found on file: root/D4PDmatrix_july28.root
//////////////////////////////////////////////////////////

#ifndef matrix_h
#define matrix_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class matrix {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           RunNumber;
   Int_t           EventNumber;
   Int_t           Egamma;
   Int_t           Muon;
   Int_t           prim_vtx_n;
   vector<float>   *d0_wrtPV;
   Int_t           TT;
   Int_t           Tl;
   Int_t           lT;
   Int_t           ll;
   Int_t           EE;
   Int_t           MM;
   Int_t           EM;
   Int_t           ME;
   Int_t           OS;
   Int_t           SS;
   Float_t         lep_mll;
   vector<float>   *lep_pt;
   vector<float>   *lep_eta;
   vector<float>   *lep_phi;
   vector<int>     *lep_id;
   vector<int>     *lep_T;
   vector<int>     *lep_l;
   vector<float>   *lep_iso;
   vector<float>   *lep_etcone30;
   vector<int>     *lep_isconv;
   vector<int>     *lep_convFlag;
   Float_t         w_rr;
   Float_t         w_rf;
   Float_t         w_fr;
   Float_t         w_ff;
   Float_t         w_rr_min;
   Float_t         w_rf_min;
   Float_t         w_fr_min;
   Float_t         w_ff_min;
   Float_t         w_rr_max;
   Float_t         w_rf_max;
   Float_t         w_fr_max;
   Float_t         w_ff_max;
   Float_t         MET;
   Float_t         METx;
   Float_t         METy;
   Int_t           jet_n;
   vector<float>   *jet_pt;
   vector<float>   *jet_eta;
   vector<float>   *jet_phi;
   vector<float>   *jet_e;
   vector<float>   *jet_sv0;
   vector<float>   *lep_jet_dr;
   vector<float>   *lep_jetAll_dr;
   Float_t         lep_dphi;
   vector<int>     *region;
   vector<string>  *regionT;
   Float_t         arrw_rr[2];
   Float_t         arrw_rf[2];
   Float_t         arrw_fr[2];
   Float_t         arrw_ff[2];
   Float_t         arrw_rr_errUp[2];
   Float_t         arrw_rf_errUp[2];
   Float_t         arrw_fr_errUp[2];
   Float_t         arrw_ff_errUp[2];
   Float_t         arrw_rr_errDown[2];
   Float_t         arrw_rf_errDown[2];
   Float_t         arrw_fr_errDown[2];
   Float_t         arrw_ff_errDown[2];
   Float_t         arrw_rr_max[2];
   Float_t         arrw_rf_max[2];
   Float_t         arrw_fr_max[2];
   Float_t         arrw_ff_max[2];
   Float_t         arrw_rr_min[2];
   Float_t         arrw_rf_min[2];
   Float_t         arrw_fr_min[2];
   Float_t         arrw_ff_min[2];

   // List of branches
   TBranch        *b_RunNumber;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_Egamma;   //!
   TBranch        *b_Muon;   //!
   TBranch        *b_prim_vtx_n;   //!
   TBranch        *b_d0_wrtPV;   //!
   TBranch        *b_TT;   //!
   TBranch        *b_Tl;   //!
   TBranch        *b_lT;   //!
   TBranch        *b_ll;   //!
   TBranch        *b_EE;   //!
   TBranch        *b_MM;   //!
   TBranch        *b_EM;   //!
   TBranch        *b_ME;   //!
   TBranch        *b_OS;   //!
   TBranch        *b_SS;   //!
   TBranch        *b_lep_mll;   //!
   TBranch        *b_lep_pt;   //!
   TBranch        *b_lep_eta;   //!
   TBranch        *b_lep_phi;   //!
   TBranch        *b_lep_id;   //!
   TBranch        *b_lep_T;   //!
   TBranch        *b_lep_l;   //!
   TBranch        *b_lep_iso;   //!
   TBranch        *b_lep_etcone30;   //!
   TBranch        *b_lep_isconv;   //!
   TBranch        *b_lep_convFlag;   //!
   TBranch        *b_w_rr;   //!
   TBranch        *b_w_rf;   //!
   TBranch        *b_w_fr;   //!
   TBranch        *b_w_ff;   //!
   TBranch        *b_w_rr_min;   //!
   TBranch        *b_w_rf_min;   //!
   TBranch        *b_w_fr_min;   //!
   TBranch        *b_w_ff_min;   //!
   TBranch        *b_w_rr_max;   //!
   TBranch        *b_w_rf_max;   //!
   TBranch        *b_w_fr_max;   //!
   TBranch        *b_w_ff_max;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_METx;   //!
   TBranch        *b_METy;   //!
   TBranch        *b_jet_n;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_e;   //!
   TBranch        *b_jet_sv0;   //!
   TBranch        *b_lep_jet_dr;   //!
   TBranch        *b_lep_jetAll_dr;   //!
   TBranch        *b_lep_dphi;   //!
   TBranch        *b_region;   //!
   TBranch        *b_regionT;   //!
   TBranch        *b_w_rr;   //!
   TBranch        *b_w_rf;   //!
   TBranch        *b_w_fr;   //!
   TBranch        *b_w_ff;   //!
   TBranch        *b_w_rr_errUp;   //!
   TBranch        *b_w_rf_errUp;   //!
   TBranch        *b_w_fr_errUp;   //!
   TBranch        *b_w_ff_errUp;   //!
   TBranch        *b_w_rr_errDown;   //!
   TBranch        *b_w_rf_errDown;   //!
   TBranch        *b_w_fr_errDown;   //!
   TBranch        *b_w_ff_errDown;   //!
   TBranch        *b_w_rr_max;   //!
   TBranch        *b_w_rf_max;   //!
   TBranch        *b_w_fr_max;   //!
   TBranch        *b_w_ff_max;   //!
   TBranch        *b_w_rr_min;   //!
   TBranch        *b_w_rf_min;   //!
   TBranch        *b_w_fr_min;   //!
   TBranch        *b_w_ff_min;   //!

   matrix(TTree *tree=0);
   virtual ~matrix();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef matrix_cxx
matrix::matrix(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("root/D4PDmatrix_july28.root");
      if (!f) {
         f = new TFile("root/D4PDmatrix_july28.root");
      }
      tree = (TTree*)gDirectory->Get("matrix");

   }
   Init(tree);
}

matrix::~matrix()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t matrix::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t matrix::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void matrix::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   d0_wrtPV = 0;
   lep_pt = 0;
   lep_eta = 0;
   lep_phi = 0;
   lep_id = 0;
   lep_T = 0;
   lep_l = 0;
   lep_iso = 0;
   lep_etcone30 = 0;
   lep_isconv = 0;
   lep_convFlag = 0;
   jet_pt = 0;
   jet_eta = 0;
   jet_phi = 0;
   jet_e = 0;
   jet_sv0 = 0;
   lep_jet_dr = 0;
   lep_jetAll_dr = 0;
   region = 0;
   regionT = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("Egamma", &Egamma, &b_Egamma);
   fChain->SetBranchAddress("Muon", &Muon, &b_Muon);
   fChain->SetBranchAddress("prim_vtx_n", &prim_vtx_n, &b_prim_vtx_n);
   fChain->SetBranchAddress("d0_wrtPV", &d0_wrtPV, &b_d0_wrtPV);
   fChain->SetBranchAddress("TT", &TT, &b_TT);
   fChain->SetBranchAddress("Tl", &Tl, &b_Tl);
   fChain->SetBranchAddress("lT", &lT, &b_lT);
   fChain->SetBranchAddress("ll", &ll, &b_ll);
   fChain->SetBranchAddress("EE", &EE, &b_EE);
   fChain->SetBranchAddress("MM", &MM, &b_MM);
   fChain->SetBranchAddress("EM", &EM, &b_EM);
   fChain->SetBranchAddress("ME", &ME, &b_ME);
   fChain->SetBranchAddress("OS", &OS, &b_OS);
   fChain->SetBranchAddress("SS", &SS, &b_SS);
   fChain->SetBranchAddress("lep_mll", &lep_mll, &b_lep_mll);
   fChain->SetBranchAddress("lep_pt", &lep_pt, &b_lep_pt);
   fChain->SetBranchAddress("lep_eta", &lep_eta, &b_lep_eta);
   fChain->SetBranchAddress("lep_phi", &lep_phi, &b_lep_phi);
   fChain->SetBranchAddress("lep_id", &lep_id, &b_lep_id);
   fChain->SetBranchAddress("lep_T", &lep_T, &b_lep_T);
   fChain->SetBranchAddress("lep_l", &lep_l, &b_lep_l);
   fChain->SetBranchAddress("lep_iso", &lep_iso, &b_lep_iso);
   fChain->SetBranchAddress("lep_etcone30", &lep_etcone30, &b_lep_etcone30);
   fChain->SetBranchAddress("lep_isconv", &lep_isconv, &b_lep_isconv);
   fChain->SetBranchAddress("lep_convFlag", &lep_convFlag, &b_lep_convFlag);
   fChain->SetBranchAddress("w_rr", &w_rr, &b_w_rr);
   fChain->SetBranchAddress("w_rf", &w_rf, &b_w_rf);
   fChain->SetBranchAddress("w_fr", &w_fr, &b_w_fr);
   fChain->SetBranchAddress("w_ff", &w_ff, &b_w_ff);
   fChain->SetBranchAddress("w_rr_min", &w_rr_min, &b_w_rr_min);
   fChain->SetBranchAddress("w_rf_min", &w_rf_min, &b_w_rf_min);
   fChain->SetBranchAddress("w_fr_min", &w_fr_min, &b_w_fr_min);
   fChain->SetBranchAddress("w_ff_min", &w_ff_min, &b_w_ff_min);
   fChain->SetBranchAddress("w_rr_max", &w_rr_max, &b_w_rr_max);
   fChain->SetBranchAddress("w_rf_max", &w_rf_max, &b_w_rf_max);
   fChain->SetBranchAddress("w_fr_max", &w_fr_max, &b_w_fr_max);
   fChain->SetBranchAddress("w_ff_max", &w_ff_max, &b_w_ff_max);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("METx", &METx, &b_METx);
   fChain->SetBranchAddress("METy", &METy, &b_METy);
   fChain->SetBranchAddress("jet_n", &jet_n, &b_jet_n);
   fChain->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
   fChain->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
   fChain->SetBranchAddress("jet_phi", &jet_phi, &b_jet_phi);
   fChain->SetBranchAddress("jet_e", &jet_e, &b_jet_e);
   fChain->SetBranchAddress("jet_sv0", &jet_sv0, &b_jet_sv0);
   fChain->SetBranchAddress("lep_jet_dr", &lep_jet_dr, &b_lep_jet_dr);
   fChain->SetBranchAddress("lep_jetAll_dr", &lep_jetAll_dr, &b_lep_jetAll_dr);
   fChain->SetBranchAddress("lep_dphi", &lep_dphi, &b_lep_dphi);
   fChain->SetBranchAddress("region", &region, &b_region);
   fChain->SetBranchAddress("regionT", &regionT, &b_regionT);
   fChain->SetBranchAddress("arrw_rr", arrw_rr, &b_w_rr);
   fChain->SetBranchAddress("arrw_rf", arrw_rf, &b_w_rf);
   fChain->SetBranchAddress("arrw_fr", arrw_fr, &b_w_fr);
   fChain->SetBranchAddress("arrw_ff", arrw_ff, &b_w_ff);
   fChain->SetBranchAddress("arrw_rr_errUp", arrw_rr_errUp, &b_w_rr_errUp);
   fChain->SetBranchAddress("arrw_rf_errUp", arrw_rf_errUp, &b_w_rf_errUp);
   fChain->SetBranchAddress("arrw_fr_errUp", arrw_fr_errUp, &b_w_fr_errUp);
   fChain->SetBranchAddress("arrw_ff_errUp", arrw_ff_errUp, &b_w_ff_errUp);
   fChain->SetBranchAddress("arrw_rr_errDown", arrw_rr_errDown, &b_w_rr_errDown);
   fChain->SetBranchAddress("arrw_rf_errDown", arrw_rf_errDown, &b_w_rf_errDown);
   fChain->SetBranchAddress("arrw_fr_errDown", arrw_fr_errDown, &b_w_fr_errDown);
   fChain->SetBranchAddress("arrw_ff_errDown", arrw_ff_errDown, &b_w_ff_errDown);
   fChain->SetBranchAddress("arrw_rr_max", arrw_rr_max, &b_w_rr_max);
   fChain->SetBranchAddress("arrw_rf_max", arrw_rf_max, &b_w_rf_max);
   fChain->SetBranchAddress("arrw_fr_max", arrw_fr_max, &b_w_fr_max);
   fChain->SetBranchAddress("arrw_ff_max", arrw_ff_max, &b_w_ff_max);
   fChain->SetBranchAddress("arrw_rr_min", arrw_rr_min, &b_w_rr_min);
   fChain->SetBranchAddress("arrw_rf_min", arrw_rf_min, &b_w_rf_min);
   fChain->SetBranchAddress("arrw_fr_min", arrw_fr_min, &b_w_fr_min);
   fChain->SetBranchAddress("arrw_ff_min", arrw_ff_min, &b_w_ff_min);
   Notify();
}

Bool_t matrix::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void matrix::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t matrix::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef matrix_cxx
