{
  TStopwatch timer;

  // gSystem->Load("libPhysics");

  Bool_t runProof = kFALSE;
  const char* server = "";
  Int_t nworkers = 0;

  TString runMode = "NonProof"; // "NonProof","Proof", "ProofLite"

  if (runMode == "Proof") {
    // case-1: PROOF server
    // ====================
    runProof = kTRUE;
    server = "acas1010";
    nworkers = 24;

  } else if (runMode == "ProofLite") {
    // case-2: PROOF-Lite
    // ====================
    runProof = kTRUE;
    server = "";
    nworkers = 3;

  } else if (runMode == "NonProof") {
    // case-3: Non-Proof
    // ====================
    runProof = kFALSE;
    server = "";
    nworkers = -1;
  } else {
    cout << "Unknown runMode=" << runMode << ", exit now" << endl;
    gSystem->Exit(1);
  }

  TProof* proof = 0;

  TString fout = TString::Format("%s/myOutput.root", gSystem->WorkingDirectory());
  gSystem->Setenv("OutFilename",fout.Data());

  const char* Cuts_Filename = "BaseTree_ttbar/ttbarSel-Cuts.txt";
  gSystem->Setenv("Cuts_Filename",Cuts_Filename);

  TChain* chain = new TChain("physics");
  TString workDir(gSystem->WorkingDirectory());
  TFileCollection fc("fc","list of input root files","input.txt");
  chain->AddFileInfoList(fc.GetList());

  chain->MakeSelector("BaseTree_ttbar");
  gSystem->Exec("mv BaseTree_ttbar.h BaseTree_ttbar.C BaseTree_ttbar/");

  // chain->Add("root://xrd//data/user.hma.data10_7TeV.00159086.physics_L1Calo.merge.NTUP_JETMET.f275_p191.slimmed.V5.4/user.hma.data10_7TeV.00159086.physics_L1Calo.merge.NTUP_JETMET.f275_p191.slimmed.V5.4._00001.output.root.1");

  gROOT->LoadMacro("BaseTree_ttbar/BaseTree_ttbar.C+");
  if (runProof) {

    // force proof server uses the same ROOT version as client
    if (server != "") {
      // TString rootVer_dir = gSystem->Exec("echo $ROOTSYS | sed 's%.*root/\\([0-9].*\\)/.*/root%\\1%'");
      char *rootVer_dir = gSystem->BaseName( gSystem->DirName( gSystem->DirName(gSystem->Getenv("ROOTSYS"))));
      TProof::AddEnvVar("PROOF_INITCMD", TString::Format("%s %s","echo source /usatlas/u/yesw2000/bin/root_set-slc5.sh",rootVer_dir) );
    }

    TProof::AddEnvVar("OutFilename",fout.Data());
    TProof::AddEnvVar("Cuts_Filename",Cuts_Filename);
    TString str_server(server);
    Bool_t IsProofLite = kFALSE;
    if (str_server.Length() == 0) {
       IsProofLite = kTRUE;
       if (nworkers>0) {
          str_server = TString::Format("workers=%d",nworkers);
       }
    }
    proof = TProof::Open(str_server.Data());
    if (!IsProofLite && nworkers>0) proof->SetParallel(nworkers);

    // for Proof-Lite
    if (IsProofLite) proof->SetParameter("PROOF_Packetizer","TPacketizer");

    //+Option: sub-mergers
    // you may like to enable sub-mergers in case that the merging process
    // takes a long time, set to Zero for dynamic setting number of sub-mergers.

    // proof->SetParameter("PROOF_UseMergers", 0);
    // proof->SetParameter("PROOF_UseMergers", 2);

    //-Option: sub-mergers

    // proof->Exec(".!hostname; echo ROOTSYS=$ROOTSYS");

    gSystem->Exec("gtar cfz BaseTree_ttbar.par BaseTree_ttbar/");
    proof->UploadPackage("BaseTree_ttbar.par");
    proof->EnablePackage("BaseTree_ttbar.par",kTRUE);

  }

  timer.Start();
  if (runProof) chain->SetProof();
  // you can use the option to control the printout in your code
  // and writing out the old tree for selected events.
  // chain->Process("ttbarSel.C+","Debug nPrint=1 No_selTree",5);
  // chain->Process("ttbarSel.C+","nPrint=200 No_selTree",20001);
  chain->Process("ttbarSel.C+","nPrint=500 No_selTree");
  timer.Stop(); timer.Print();

  // write out log file on Proof master/worker nodes
  if (runProof) {
    TProofLog *pl = proof->GetManager()->GetSessionLogs();
    pl->Save("*", "file_with_all_logs.txt");
  }

  TFile outFile(fout.Data(),"UPDATE");

  // the parameters for event selection criteria are 
  // writen into the same output root file
  TPaveText cutText(0.1,0.1,0.9,0.9,"NDC");
  cutText->SetName("cutText");
  cutText.ReadFile(Cuts_Filename);
  cutText.Write();

  gSystem->Exit(0);
}
