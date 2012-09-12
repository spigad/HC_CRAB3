// Ask me if you have questions/problems. Thomas M.
// Version 0.1.5
// Start with root runSelector.C
// please read all comments with // !!! up to line 115
// You have to make some changes at various places
#include <TH2.h>
#include <map>
#include <TColor.h>
#include <TH1.h>
#include <TTree.h>
#include <TNtuple.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TStyle.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sys/stat.h> 
#include <iostream>
#include <math.h>
#include "string.h"
#include "TSystem.h"
#include "TProof.h"
#include "TChain.h"
#include "TDSet.h"
#include "TROOT.h"
#include "TError.h"
void throwException(string str){
	// necessary because cint does not handle thrown errors correctly
	cout <<"Exception raised "<< str<<endl;
	throw(str);
	abort();
}; 


void runPoD() {
 try {
  //gDebug = 4;
  std::vector<TString> filename; 
  string path = "";
  string ending ="";
  vector<TString> fileLists;
  
  TString localUserName = "Federica.Legger";   // !!! enter your local login name here. (you need this to use DataSets)
  TString lrzUserName = "ri32biv"; // !!! enter your lrz login name here. Leave blank if you dont use lrz.
  TString selectorName = "D3PDSelector"; // !!! enter the name of your Selector (without _C.so)
  TString localSelectorPath = "/data/etp4/flegger/susy/D3PDReader_p832_52/";  // !!! the path to your compiled _C.so on the etp cluster
  TString lrzSelectorPath = "/home/grid/lcg/home/lmu40699/PROOF/D3PDReader_614/"; // !!! the location of your compiled _C.so at lrz
  TString treeName = "susy"; // !!! the name of the tree that should be processed
  vector<TString> other_files_to_load;

gSystem->AddIncludePath("-I/data/etp4/flegger/susy/D3PDReader_p832_52/RootCore/include");
gSystem->Load("libHist");
gSystem->Load("libTree");
gSystem->Load("libTreePlayer");
gSystem->Load("libXMLParser");
gSystem->Load("libXMLIO");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_52/RootCore/lib/libMuonMomentumCorrections.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_52/RootCore/lib/libCalibrationDataInterface.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_52/RootCore/lib/libMuonEfficiencyCorrections.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_52/RootCore/lib/libegammaAnalysisUtils.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_52/RootCore/lib/libObjectSelectorCore.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_52/RootCore/lib/libJetSelectorTools.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_52/RootCore/lib/libJetResolution.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_52/RootCore/lib/libJetUncertainties.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_52/RootCore/lib/libMissingETUtility.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_52/RootCore/lib/libReweightUtils.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_52/RootCore/lib/libPileupReweighting.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_52/RootCore/lib/libegammaEvent.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_52/RootCore/lib/libGoodRunsLists.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_52/RootCore/lib/libSUSYTools.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_52/RootCore/lib/libTrigRootAnalysis.so");
gSystem->Load("/data/etp4/flegger/susy/D3PDReader_p832_52/RootCore/lib/libDGTriggerReweight.so");

  // !!! you can change those values, but the defaults should be ok as well:
  int minCpusLRZ = 28; // dont start the analysis until at least xx CPUs are ready if running at LRZ
  bool restartProofAfterEachDataSet = false; // if set to true, proof will restart after each processed dataset. This takes a few seconds, but new PoD Slave nodes will be added.
  bool failIfFileNotFound = true; // if true the script will terminate if a file/dataset does not exist
  string mode = "auto"; /*  possible modes:
				root	:	no Proof at all
				proof	:	only proof lite
				pod	: 	Proof on Demand
				auto	: 	Proof on Demand if available, Proof Lite if not.
				*/

  bool LRZ; // set to true if you want to run at LRZ. Will be determined automatically by username.
  if (getenv("USER")==localUserName) LRZ=false;
  if (getenv("USER")==lrzUserName) LRZ=true;
  if ((getenv("USER")!=lrzUserName) && (getenv("USER")!=localUserName)) throwException ("Your username does neither match your lrzUserName nor your localUserName");
  
/* **********************
 * List all DataSets    *
 ********************** */

if (LRZ) path="/default/"+lrzUserName+"/";
if (!LRZ) path = "/default/"+localUserName+"/";
ending ="#"+treeName; //If you process a dataset with McAtNlo_Jimmy.merge.AOD.e510_s765_s767_r1302_r1306.V1#susy the tree susy is processed

//filename.push_back(path + "group10.phys-susy.SUSYD3PD.mc09_7TeV.114036.SU_1160_250_0_3_herwigpp_susy.merge.AOD.e542_s765_s767_r1302_r1306.000614.V1" + ending);
// !!! you can process more datasets by uncommenting those lines:
//filename.push_back(path + "uuser.markh5od.SUSYD3PD.mc09_7TeV.105200.T1_McAtNlo_Jimmy.merge.AOD.e510_s765_s767_r1302_r1306.V1" + ending);
//filename.push_back(path + "group10.phys-susy.SUSYD3PD.mc09_7TeV.114152.SU_440_310_0_3_herwigpp_susy.merge.AOD.e542_s765_s767_r1302_r1306.000614.V1" +ending);
//filename.push_back(path + "user.ctopfel.SUSYD3PD.mc09_7TeV.114153.SU_440_340_0_3_herwigpp_susy.merge.AOD.e542_s765_s767_r1302_r1306.000614.V1" +ending);
//filename.push_back(path + "user.ctopfel.SUSYD3PD.mc09_7TeV.114154.SU_520_100_0_3_herwigpp_susy.merge.AOD.e542_s765_s767_r1302_r1306.000614.V1" +ending);

fileLists.push_back("mc.txt");
//fileLists.push_back("egamma.txt");
//fileLists.push_back("muon.txt");
//fileLists.push_back("tmp.txt"); 
	/* !!! all files in fileLists will be opened, and all datasets in those files will be processed.
	  mSugrarid.txt should contain one dataset per line and no whitespaces at the end of lines */

	// process all files in fileLists:
for (int iFileList=0; iFileList<fileLists.size(); iFileList++)
{
	ifstream inputfile (fileLists[iFileList]);
	if (inputfile.is_open())
	{
		string line;
		while ( inputfile.good() )
		{
			std::getline (inputfile,line);
			cout <<"read from file: " <<  line << endl;
			filename.push_back(path + line +ending);
			if (line.size()==0) filename.pop_back();
		}
		inputfile.close();
	}
}
  //  GD use TTreeCache (disabled by default in ROOT5.28)
  //c->SetCacheSize(100000000);

/* ********************************************
 * !!! List all Files that dont have a DataSet*
 * (you should create a Dataset for all files *
 *  so this is only a temporary solution      *
 ******************************************** */

if (!LRZ) //dont try to access /data/etp from LRZ
{
//         path = "/data/etp1/SUSYD3PD/SUSYProdSys_p305/";
//         ending = "/*.root*";
        //path = "~/tmp/";
//      path = "/data/etp/thomas.andreas.mueller/data/D3PD/";
//      ending = "/*.root*";

//         filename.push_back("/data/etp4/flegger/data/mc10_7TeV.106484.SU4_herwigpp_susy.merge.NTUP_SUSY.e598_s933_s946_r2302_r2300_p563_tid363676_00/*root*");

//         filename.push_back("/nobackup/etp2/degraat/datasets/mc10_7TeV.106484.SU4_herwigpp_susy.merge.NTUP_SUSY.e598_s933_s946_r2302_r2300_p575_tid367132_00/*");
//         filename.push_back("/nobackup/etp2/degraat/datasets/mc10_7TeV.106484.SU4_herwigpp_susy.merge.NTUP_SUSY.e598_s933_s946_r2302_r2300_p601_tid424600_00/*");

//         filename.push_back("/nobackup/etp2/degraat/datasets/T1_p575/*root*");

//         filename.push_back("/nobackup/etp2/degraat/datasets/data11_7TeV.00178044.physics_Egamma.merge.NTUP_SUSY.r2276_p516_p523_p576_tid375885_00/*root*");
//         filename.push_back("/nobackup/etp2/degraat/datasets/data11_7TeV.00178109.physics_Egamma.merge.NTUP_SUSY.r2276_p516_p523_p576_tid375887_00/*root*");
//         filename.push_back("/nobackup/etp2/degraat/datasets/data11_7TeV.Egamma.periodB.p576/*root*");

//         filename.push_back("/nobackup/etp2/degraat/datasets/mc10_7TeV.107650.AlpgenJimmyZeeNp0_pt20.merge.NTUP_SUSY.e737_s933_s946_r2302_r2300_p575_tid372302_00/*root*");
//         filename.push_back("/nobackup/etp2/degraat/datasets/mc10_7TeV.107651.AlpgenJimmyZeeNp1_pt20.merge.NTUP_SUSY.e737_s933_s946_r2302_r2300_p575_tid372303_00/*root*");
//         filename.push_back("/nobackup/etp2/degraat/datasets/mc10_7TeV.107652.AlpgenJimmyZeeNp2_pt20.merge.NTUP_SUSY.e737_s933_s946_r2302_r2300_p575_tid372304_00/*root*");
//         filename.push_back("/nobackup/etp2/degraat/datasets/mc10_7TeV.107653.AlpgenJimmyZeeNp3_pt20.merge.NTUP_SUSY.e737_s933_s946_r2302_r2300_p575_tid372305_00/*root*");
//         filename.push_back("/nobackup/etp2/degraat/datasets/mc10_7TeV.107654.AlpgenJimmyZeeNp4_pt20.merge.NTUP_SUSY.e737_s933_s946_r2302_r2300_p575_tid372306_00/*root*");
//         filename.push_back("/nobackup/etp2/degraat/datasets/mc10_7TeV.107655.AlpgenJimmyZeeNp5_pt20.merge.NTUP_SUSY.e737_s933_s946_r2302_r2300_p575_tid372307_00/*root*");

        //filename.push_back(path + "mc09_7TeV.114948.PhenoGrid2_16_jimmy_susy.merge.NTUP_SUSY.e624_s765_s767_r1302_r1306_p305_tid209070_00" +ending);
        //filename.push_back(path + "mc09_7TeV.114996.PhenoGrid1_32_jimmy_susy.merge.NTUP_SUSY.e624_s765_s767_r1302_r1306_p305_tid209118_00" +ending);
//      filename.push_back(path + "mc09_7TeV.114909.PhenoGrid3_9_jimmy_susy.merge.NTUP_SUSY.e624_s765_s767_r1302_r1306_p305_tid209031_00" +ending);

//      path = "/data/etp1/SUSYD3PD/someOtherPath";
//      filename.push_back(path + "someOtherDataSets" +ending);

}

bool iHaveReadAndUnderstoodTheCodeAbove=true; // !!! Set to true, if you have read the code above and made all necessary changes.

/* ********************************************************************************
 * !!! You should probably not change anything below this line                    *
 * unless you know exactly what you are doing                                     *
 * You don't have to read the rest of the code                                    *
 * ============================================================================== *
 ******************************************************************************** */


	TString localSelectorName = localSelectorPath + selectorName + "_C.so";
	TString lrzSelectorName = localSelectorPath + selectorName + "_C.so";

	bool USEPROOF; 
	bool USEPOD; 
	if (!(mode=="pod" || mode=="root" || mode=="proof" || mode=="auto")) throwException("Invalid mode given");
	if (mode=="root")   { USEPROOF = false; USEPOD = false;};
	if (mode=="proof")  { USEPROOF = true; USEPOD = false;};
	if (mode=="pod")    { USEPROOF = true; USEPOD = true;};
	if (mode=="auto")   
	{
		if (gSystem->GetFromPipe("pod-info -c")=="") { USEPROOF = true; USEPOD = false;}
		else { USEPROOF = true; USEPOD = true;};
	};

	if (USEPOD && !USEPROOF) { throwException ("If you use POD you have to use PROOF");};
	if (LRZ && !USEPOD)	{ throwException ( "You must use PoD at LRZ");};
	if (localUserName==lrzUserName) throwException ( "Your localUserName and lrzUserName should not be identical");
	if (iHaveReadAndUnderstoodTheCodeAbove==false) throwException ( "Please read all comments in the code and make the necessary changes");
	

	cout << "Processing files: " << filename.size() << endl;
	TProof * p;
	
 
	for (int i = 0; i < filename.size() ; i++)
	{
		TChain *ch;
		TDSet *set;
		
		if (restartProofAfterEachDataSet || i==0)
		{
			if (USEPROOF)
			{
				if (i>0) p->Close();
				bool PoDready=false;
				while (PoDready==false)
				{
					cout << "checking if PoD cluster is ready"<<endl;
					string podConnectString=  "";
					if (USEPOD) podConnectString = gSystem->GetFromPipe("pod-info -c");
					if (LRZ && podConnectString=="")	throwException ( "pod-info -c was empty on LRZ. YOU SHALL NOT RUN PROOF LITE ON THE LRZ LOGIN NODE.");
					if (USEPOD && !LRZ && podConnectString=="")	throwException ( "pod-info -c was empty. To start a PoD Cluster use source /data/etp6/Common/PoD/setup.sh && PoD_Start");
					p = TProof::Open(podConnectString.c_str());
// 					p->SetParameter( "PROOF_UseTreeCache", ( Int_t ) 0 ); // NOTE: This line is needed for MC10b (should be fixed now)
					int cpus = p->GetParallel();
					int waitingtime=10000; // milliseconds to wait before trying to connect to proof again.
					if ((!LRZ) || ( cpus >= minCpusLRZ)) PoDready=true;
					else 
					{
						p->Close();
						cout << "only " << cpus << " CPUs ready, waiting until " << minCpusLRZ << " CPUs are ready." << endl;
						gSystem->Sleep (waitingtime);
						waitingtime+=1000;
					}
				}
			}
			TString processLine = ".L "+selectorName+".C+g";
			TString execLine;

			gROOT->ProcessLine(processLine); // need to add this, or PoD at LRZ will not be able to load the .so
			// load other files:
			if (USEPROOF && LRZ) execLine = "gSystem->Load(\""+lrzSelectorName+"\")";
			if (USEPROOF && !LRZ) execLine = "gSystem->Load(\""+localSelectorName+"\")";
			
			
			if (USEPROOF) gProof->Exec(execLine);
/*
			for (int unsigned iOF=0; iOF<other_files_to_load.size(); iOF++)
			{
			  processLine = ".L " + other_files_to_load[iOF] +"+";
			  cout << processLine << endl;
			  gROOT->ProcessLine(processLine); 
			  
			  string otherSO;
			  // otherSO 
			  otherSO="TMHisto_cxx.so";
			  //if (USEPROOF && LRZ) execLine = "gSystem->Load(\""+lrzSelectorPath+  otherSO+  "\")";
			  //if (USEPROOF && !LRZ) execLine = "gSystem->Load(\""+localSelectorPath+ otherSO+   "\")";
			  //if (USEPROOF) cout << execLine << endl;
			  //if (USEPROOF) gProof->Exec(execLine);
			  
			}
*/			
			
		}
		
		bool isDataSet=false; // true if the current filename[i] is a registered Dataset in proof
		bool isValidSource=false; // true if the given source is valid (i.e. a registered dataset or a nonempty file). 
		if (USEPROOF)
		{
			if (p->GetDataSet(filename[i])==0) isDataSet=false;
			else
			{ 
				isDataSet=true; 
				isValidSource=true;
			}
		}
		
		if (!isDataSet) //if its not a Dataset create a TDset
		{
			ch = new TChain(treeName);
			ch->Add(filename[i]);
			isValidSource=true;
			cout << ch->GetEntries() <<endl; //without this root will crash here.
			if (ch->GetEntries()==0) isValidSource=false;
			set = new TDSet(*ch);
		}
		if (isValidSource) // only process if it is a valid source
		{
			//		gProof->Exec("gSystem->Load(\"/data/etp/thomas.andreas.mueller/PROOF/D3PDReader_614/D3PDSelector_C.so\")");
			if (USEPROOF & isDataSet) p->Process(filename[i],selectorName); // run on the DataSet
			if (USEPROOF & !isDataSet) p->Process(set,selectorName); // run on the TDSet
			cout << "start "<<filename[i] <<endl;
			if (!USEPROOF) ch->Process(selectorName+".C+g");
			cout << "done processing file "<<filename[i] <<endl;
		}
		else
		{
			cout << "Did not process file "<<filename[i]<<endl;
			if (failIfFileNotFound) {throwException ( "File not processed");}
		}
		if (ch) {delete ch; ch=0;}
		if (set) {delete set; set=0;}
	}//end loop over all files
 
 
  
	cout << "All done!"<<endl;
	if (USEPROOF) p->Close();
	if (USEPROOF) delete p;
	cout << "******************************************************"<<endl;
	cout << "*Please execute PoD_End if you started a PoD Session *"<<endl;
	cout << "******************************************************"<<endl;
	}
	catch ( char const* str )
	{
		cout << "Exception raised: " << str << '\n';
	}
	catch ( const string str )
	{
		cout << "Exception raised: " << str << '\n';
	}
//abort();
}
