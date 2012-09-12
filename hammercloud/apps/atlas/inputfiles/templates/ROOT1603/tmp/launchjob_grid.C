{

std::string argStr;

std::ifstream ifs("input.txt");
std::getline(ifs,argStr);

// split by ','
std::vector<std::string> fileList;
for (size_t i=0,n; i <= argStr.length(); i=n+1)
  {
    n = argStr.find_first_of(',',i);
    if (n == string::npos)
      n = argStr.length();
    std::string tmp = argStr.substr(i,n-i);
    fileList.push_back(tmp);
  }

  // open input files
  TProof* proof = TProof::Open("") ;
  proof->SetParallel(1);

  TDSet *set = new TDSet("TTree", "susy") ;
  for (int iFile=0; iFile<fileList.size(); ++iFile)
    {
      std::cout << "open " << fileList[iFile].c_str() << std::endl;
      set->Add(fileList[iFile].c_str());
    }

   set->Process("D3PDSelector.C+O");  
   
   if(set->GetListOfElements()->GetSize()!=fileList.size()){
       std::cerr<<"Not all files read!"<<std::endl;
       exit(1);
  }
   
/*
    TFile* output_file = new TFile("output.root", "recreate") ;

    // Retrieve objects                                                         
    TList* list = proof->GetOutputList() ;
    TIter next_object((TList*) list);
    TObject* obj ;
    cout << "-- Retrieved objects:" << endl ;
    output_file->cd() ;
    while ((obj = next_object())) { TString objname = obj->GetName() ; cout << " " << objname << endl ; obj->Write() ; }

    // Write output file
    output_file->Write() ;
*/
    // get proof manager (if not already available)
    TProofMgr* mgr = proof->GetManager() ;

    // get proof logs                                                           
    TProofLog *log = mgr->GetSessionLogs() ;

    // log file name (set prefix)                                               
    TString log_file_name = "log_all-workersT1.txt" ;

    // save log                                                             
    int flag = log->Save("*", log_file_name) ;

    //quit root
    gApplication->Terminate();
}
