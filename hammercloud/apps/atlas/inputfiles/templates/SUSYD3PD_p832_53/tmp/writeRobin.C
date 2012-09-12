#define MC
#define MSUGRA
//#define H1D
#define H2D

  double lumi         = 20000.; //nb	
  TString lumi_string = "20000"; //nb	
  TString histo_string, histo_syst_string;
  int nCut, nCutRef, binmin, binmax;
     
  TString prefix = "result";
  
  int gridXbins = 152;
  int gridYbins = 42;
  double gridStartX = -10.;  //m0
  double gridStopX = 3030;
  double gridStartY = -15;   // m1/2
  double gridStopY = 615; 
   
#include "AtlasStyle2D.C"
#include "input.h"
#include "histo.h"
#include "msugra.h"

  ofstream myfile;
  TH2D *grid_cs, *grid_gq, *grid_gg, *grid_qq, *grid_qaq, *grid_tt, *grid_bb, *grid_gchi, *grid_qqchi ;
   
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


void writeRobin() {

  std::cout << "lumi " << lumi <<" nb-1"<< std::endl;  
  std::cout << "Opening files " << prefix << std::endl;  
     
  gROOT->SetStyle("ATLAS");
  SetAtlasStyle();
  gROOT->ForceStyle();

  myfile.open("./robin.h");
  
  grid_cs    = new TH2D("grid_cs", "grid_cs",       gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  grid_gq    = new TH2D("grid_gq", "grid_gq",       gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  grid_gg    = new TH2D("grid_gg", "grid_gg",       gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  grid_qq    = new TH2D("grid_qq", "grid_qq",       gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  grid_qaq   = new TH2D("grid_qaq", "grid_qaq",     gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  grid_tt    = new TH2D("grid_tt", "grid_tt",       gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  grid_bb    = new TH2D("grid_bb", "grid_bb",       gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  grid_gchi  = new TH2D("grid_gchi", "grid_gchi",     gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  grid_qqchi = new TH2D("grid_qqchi", "grid_qqchi", gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);

  myfile << "void get_cs(double run,  double *xsection , double *xsection_process, int channel){"<<endl;

  Get_m0_m12_robin(file_123290);  
  Get_m0_m12_robin(file_123291);  
  Get_m0_m12_robin(file_123292);  
  Get_m0_m12_robin(file_123293);  
  Get_m0_m12_robin(file_123294);  
  Get_m0_m12_robin(file_123295);  
  Get_m0_m12_robin(file_123296);  
  Get_m0_m12_robin(file_123297);  
  Get_m0_m12_robin(file_123298);  
  Get_m0_m12_robin(file_123299);  
  Get_m0_m12_robin(file_123300);  
  Get_m0_m12_robin(file_123301);  
  Get_m0_m12_robin(file_123302);  
  Get_m0_m12_robin(file_123303);  
  Get_m0_m12_robin(file_123304);  
  Get_m0_m12_robin(file_123305);  
  Get_m0_m12_robin(file_123306);  
  Get_m0_m12_robin(file_123307);  
  Get_m0_m12_robin(file_123308);  
  Get_m0_m12_robin(file_123309);  
  Get_m0_m12_robin(file_123310);  
  Get_m0_m12_robin(file_123311);  
  Get_m0_m12_robin(file_123312);  
  Get_m0_m12_robin(file_123313);  
  Get_m0_m12_robin(file_123314);  
  Get_m0_m12_robin(file_123315);  
  Get_m0_m12_robin(file_123316);  
  Get_m0_m12_robin(file_123317);  
  Get_m0_m12_robin(file_123320);  
  Get_m0_m12_robin(file_123321);  
  Get_m0_m12_robin(file_123322);  
  Get_m0_m12_robin(file_123323);  
  Get_m0_m12_robin(file_123324);  
  Get_m0_m12_robin(file_123325);  
  Get_m0_m12_robin(file_123326);  
  Get_m0_m12_robin(file_123327);  
  Get_m0_m12_robin(file_123328);  
  Get_m0_m12_robin(file_123329);  
  Get_m0_m12_robin(file_123330);  
  Get_m0_m12_robin(file_123331);  
  Get_m0_m12_robin(file_123332);  
  Get_m0_m12_robin(file_123333);  
  Get_m0_m12_robin(file_123334);  
  Get_m0_m12_robin(file_123335);  
  Get_m0_m12_robin(file_123336);  
  Get_m0_m12_robin(file_123337);  
  Get_m0_m12_robin(file_123338);  
  Get_m0_m12_robin(file_123339);  
  Get_m0_m12_robin(file_123340);  
  Get_m0_m12_robin(file_123341);  
  Get_m0_m12_robin(file_123342);  
  Get_m0_m12_robin(file_123343);  
  Get_m0_m12_robin(file_123344);  
  Get_m0_m12_robin(file_123345);  
  Get_m0_m12_robin(file_123346);  
  Get_m0_m12_robin(file_123347);  
  Get_m0_m12_robin(file_123348);  
  Get_m0_m12_robin(file_123349);  
  Get_m0_m12_robin(file_123350);  
  Get_m0_m12_robin(file_123351);  
  Get_m0_m12_robin(file_123352);  
  Get_m0_m12_robin(file_123353);  
  Get_m0_m12_robin(file_123354);  
  Get_m0_m12_robin(file_123355);  
  Get_m0_m12_robin(file_123356);  
  Get_m0_m12_robin(file_123357);  
  Get_m0_m12_robin(file_123358);  
  Get_m0_m12_robin(file_123359);  
  Get_m0_m12_robin(file_123360);  
  Get_m0_m12_robin(file_123361);  
  Get_m0_m12_robin(file_123362);  
  Get_m0_m12_robin(file_123363);  
  Get_m0_m12_robin(file_123364);  
  Get_m0_m12_robin(file_123365);  
  Get_m0_m12_robin(file_123366);  
  Get_m0_m12_robin(file_123367);  
  Get_m0_m12_robin(file_123368);  
  Get_m0_m12_robin(file_123369);  
  Get_m0_m12_robin(file_123370);  
  Get_m0_m12_robin(file_123371);  
  Get_m0_m12_robin(file_123372);  
  Get_m0_m12_robin(file_123373);  
  Get_m0_m12_robin(file_123374);  
  Get_m0_m12_robin(file_123375);  
  Get_m0_m12_robin(file_123376);  
  Get_m0_m12_robin(file_123377);  
  Get_m0_m12_robin(file_123378);  
  Get_m0_m12_robin(file_123379);  
  Get_m0_m12_robin(file_123380);  
  Get_m0_m12_robin(file_123381);  
  Get_m0_m12_robin(file_123383);  
  Get_m0_m12_robin(file_123384);  
  Get_m0_m12_robin(file_123385);  
  Get_m0_m12_robin(file_123386);  
  Get_m0_m12_robin(file_123387);  
  Get_m0_m12_robin(file_123388);  
  Get_m0_m12_robin(file_123389);  
  Get_m0_m12_robin(file_123390);  
  Get_m0_m12_robin(file_123391);  
  Get_m0_m12_robin(file_123392);  
  Get_m0_m12_robin(file_123393);  
  Get_m0_m12_robin(file_123394);  
  Get_m0_m12_robin(file_123396);  
  Get_m0_m12_robin(file_123397);  
  Get_m0_m12_robin(file_123398);  
  Get_m0_m12_robin(file_123399);  
  Get_m0_m12_robin(file_123400);  
  Get_m0_m12_robin(file_123401);  
  Get_m0_m12_robin(file_123402);  
  Get_m0_m12_robin(file_123403);  
  Get_m0_m12_robin(file_123404);  
  Get_m0_m12_robin(file_123405);  
  Get_m0_m12_robin(file_123406);  
  Get_m0_m12_robin(file_123407);  
  Get_m0_m12_robin(file_123408);  
  Get_m0_m12_robin(file_123409);  
  Get_m0_m12_robin(file_123410);  
  Get_m0_m12_robin(file_123411);  
  Get_m0_m12_robin(file_123412);  
  Get_m0_m12_robin(file_123413);  
  Get_m0_m12_robin(file_123414);  
  Get_m0_m12_robin(file_123415);  
  Get_m0_m12_robin(file_123416);  
  Get_m0_m12_robin(file_123417);  
  Get_m0_m12_robin(file_123418);  
  Get_m0_m12_robin(file_123419);  
  Get_m0_m12_robin(file_123420);  
  Get_m0_m12_robin(file_123422);  
  Get_m0_m12_robin(file_123423);  
  Get_m0_m12_robin(file_123424);  
  Get_m0_m12_robin(file_123425);  
  Get_m0_m12_robin(file_123426);  
  Get_m0_m12_robin(file_123427);  
  Get_m0_m12_robin(file_123428);  
  Get_m0_m12_robin(file_123430);  
  Get_m0_m12_robin(file_123431);  
  Get_m0_m12_robin(file_123432);  
  Get_m0_m12_robin(file_123433);  
  Get_m0_m12_robin(file_123434);  
  Get_m0_m12_robin(file_123435);  
  Get_m0_m12_robin(file_123436);  
  Get_m0_m12_robin(file_123437);  
  Get_m0_m12_robin(file_123438);  
  Get_m0_m12_robin(file_123439);  
  Get_m0_m12_robin(file_123440);  
  Get_m0_m12_robin(file_123441);  
  Get_m0_m12_robin(file_123442);  
  Get_m0_m12_robin(file_123443);  
  Get_m0_m12_robin(file_123444);  
  Get_m0_m12_robin(file_123445);  
  Get_m0_m12_robin(file_123447);  
  Get_m0_m12_robin(file_123448);  
  Get_m0_m12_robin(file_123449);  
  Get_m0_m12_robin(file_123450);  
  Get_m0_m12_robin(file_123451);  
  Get_m0_m12_robin(file_123452);  
  Get_m0_m12_robin(file_123453);  
  Get_m0_m12_robin(file_123454);  
  Get_m0_m12_robin(file_123455);  
  Get_m0_m12_robin(file_123456);  
  Get_m0_m12_robin(file_123457);  
  Get_m0_m12_robin(file_123458);  
  Get_m0_m12_robin(file_123460);  
  Get_m0_m12_robin(file_123461);  
  Get_m0_m12_robin(file_123462);  
  Get_m0_m12_robin(file_123463);  
  Get_m0_m12_robin(file_123464);  
  Get_m0_m12_robin(file_123465);  
  Get_m0_m12_robin(file_123466);  
  Get_m0_m12_robin(file_123467);  
  Get_m0_m12_robin(file_123468);  
  Get_m0_m12_robin(file_123469);  
  Get_m0_m12_robin(file_123470);  
  Get_m0_m12_robin(file_123471);  
  Get_m0_m12_robin(file_123472);  
  Get_m0_m12_robin(file_123473);  
  Get_m0_m12_robin(file_123474);  
  Get_m0_m12_robin(file_123475);  
  Get_m0_m12_robin(file_123476);  
  Get_m0_m12_robin(file_123477);  
  Get_m0_m12_robin(file_123478);  
  Get_m0_m12_robin(file_123479);  
  Get_m0_m12_robin(file_123480);  
  Get_m0_m12_robin(file_123481);  
  Get_m0_m12_robin(file_123482);  
  Get_m0_m12_robin(file_123483);  
  Get_m0_m12_robin(file_123484);  
  Get_m0_m12_robin(file_123485);  
  Get_m0_m12_robin(file_123486);  
  Get_m0_m12_robin(file_123487);  
  Get_m0_m12_robin(file_123488);  
  Get_m0_m12_robin(file_123489);  
  Get_m0_m12_robin(file_123490);  
  Get_m0_m12_robin(file_123491);  
  Get_m0_m12_robin(file_123492);  
  Get_m0_m12_robin(file_123493);  
  Get_m0_m12_robin(file_123494);  
  Get_m0_m12_robin(file_123495);  
  Get_m0_m12_robin(file_123496);  
  Get_m0_m12_robin(file_123497);  
  Get_m0_m12_robin(file_123498);  
  Get_m0_m12_robin(file_123499);  
  Get_m0_m12_robin(file_123501);  
  Get_m0_m12_robin(file_123502);  
  Get_m0_m12_robin(file_123503);  
  Get_m0_m12_robin(file_123504);  
  Get_m0_m12_robin(file_123505);  
  Get_m0_m12_robin(file_123506);  
  Get_m0_m12_robin(file_123507);  
  Get_m0_m12_robin(file_123508);  
  Get_m0_m12_robin(file_123509);  
  Get_m0_m12_robin(file_123510);  
  Get_m0_m12_robin(file_123511);  
  Get_m0_m12_robin(file_123512);  
  Get_m0_m12_robin(file_123513);  
  Get_m0_m12_robin(file_123514);  
  Get_m0_m12_robin(file_123516);  
  Get_m0_m12_robin(file_123517);  
  Get_m0_m12_robin(file_123518);  
  Get_m0_m12_robin(file_123519);  
  Get_m0_m12_robin(file_123520);  
  Get_m0_m12_robin(file_123521);  
  Get_m0_m12_robin(file_123522);  
  Get_m0_m12_robin(file_123523);  
  Get_m0_m12_robin(file_123524);  
  Get_m0_m12_robin(file_123526);  
  Get_m0_m12_robin(file_123527);  
  Get_m0_m12_robin(file_123528);  
  Get_m0_m12_robin(file_123529);  
  Get_m0_m12_robin(file_123530);  
  Get_m0_m12_robin(file_123531);  
  Get_m0_m12_robin(file_123533);  
  Get_m0_m12_robin(file_123534);  
  Get_m0_m12_robin(file_123535);  
  Get_m0_m12_robin(file_123536);  
  Get_m0_m12_robin(file_123537);  
  Get_m0_m12_robin(file_123538);  
  Get_m0_m12_robin(file_123539);  
  Get_m0_m12_robin(file_123540);  
  Get_m0_m12_robin(file_123541);  
  Get_m0_m12_robin(file_123542);  
  Get_m0_m12_robin(file_123543);  
  Get_m0_m12_robin(file_123544);  
  Get_m0_m12_robin(file_123545);  
  Get_m0_m12_robin(file_123546);  
  Get_m0_m12_robin(file_123547);  
  Get_m0_m12_robin(file_123548);  
  Get_m0_m12_robin(file_123549);  
  Get_m0_m12_robin(file_123550);  
  Get_m0_m12_robin(file_123551);  
  Get_m0_m12_robin(file_123552);  
  Get_m0_m12_robin(file_123553);  
  Get_m0_m12_robin(file_123554);  
  Get_m0_m12_robin(file_123555);  
  Get_m0_m12_robin(file_123556);  
  Get_m0_m12_robin(file_123557);  
  Get_m0_m12_robin(file_123558);  
  Get_m0_m12_robin(file_123559);  
  Get_m0_m12_robin(file_123560);  
  Get_m0_m12_robin(file_123561);  
  Get_m0_m12_robin(file_123562);  
  Get_m0_m12_robin(file_123563);  
  Get_m0_m12_robin(file_123564);  
  Get_m0_m12_robin(file_123565);  
  Get_m0_m12_robin(file_123566);  
  Get_m0_m12_robin(file_123567);  
  Get_m0_m12_robin(file_123568);  
  Get_m0_m12_robin(file_123569);  
  Get_m0_m12_robin(file_123570);  
  Get_m0_m12_robin(file_123571);  
  Get_m0_m12_robin(file_123572);  
  Get_m0_m12_robin(file_123573);  
  Get_m0_m12_robin(file_123574);  
  Get_m0_m12_robin(file_123575);  
  Get_m0_m12_robin(file_123576);  
  Get_m0_m12_robin(file_123577);  
  Get_m0_m12_robin(file_123578);  
  Get_m0_m12_robin(file_123579);  
  Get_m0_m12_robin(file_123580);  
  Get_m0_m12_robin(file_123581);  
  Get_m0_m12_robin(file_123582);  
  Get_m0_m12_robin(file_123583);  
  Get_m0_m12_robin(file_123584);  
  Get_m0_m12_robin(file_123585);  
  Get_m0_m12_robin(file_123586);  
  Get_m0_m12_robin(file_123587);  
  Get_m0_m12_robin(file_123588);  
  Get_m0_m12_robin(file_123589);  
  Get_m0_m12_robin(file_123590);  
  Get_m0_m12_robin(file_123591);  
  Get_m0_m12_robin(file_123592);  
  Get_m0_m12_robin(file_123593);  
  Get_m0_m12_robin(file_123594);  
  Get_m0_m12_robin(file_123595);  
  Get_m0_m12_robin(file_123597);  
  Get_m0_m12_robin(file_123598);  
  Get_m0_m12_robin(file_123599);  
  Get_m0_m12_robin(file_123600);  
  Get_m0_m12_robin(file_123601);  
  Get_m0_m12_robin(file_123602);  
  Get_m0_m12_robin(file_123603);  
  Get_m0_m12_robin(file_123604);  
  Get_m0_m12_robin(file_123605);  
  Get_m0_m12_robin(file_123606);  
  Get_m0_m12_robin(file_123607);  
  Get_m0_m12_robin(file_123609);  
  Get_m0_m12_robin(file_123611);  
  Get_m0_m12_robin(file_123612);  
  Get_m0_m12_robin(file_123613);  
  Get_m0_m12_robin(file_123614);  
  Get_m0_m12_robin(file_123615);  
  Get_m0_m12_robin(file_123616);  
  Get_m0_m12_robin(file_123617);  
  Get_m0_m12_robin(file_123618);  
  Get_m0_m12_robin(file_123619);  
  Get_m0_m12_robin(file_123620);  
  Get_m0_m12_robin(file_123621);  
  Get_m0_m12_robin(file_123622);  
  Get_m0_m12_robin(file_123623);  
  Get_m0_m12_robin(file_123624);  
  Get_m0_m12_robin(file_123625);  
  Get_m0_m12_robin(file_123626);  
  Get_m0_m12_robin(file_123628);  
  Get_m0_m12_robin(file_123629);  
  Get_m0_m12_robin(file_123630);  
  Get_m0_m12_robin(file_123631);  
  Get_m0_m12_robin(file_123632);  
  Get_m0_m12_robin(file_123633);  
  Get_m0_m12_robin(file_123634);  
  Get_m0_m12_robin(file_123635);  
  Get_m0_m12_robin(file_123636);  
  Get_m0_m12_robin(file_123637);  
  Get_m0_m12_robin(file_123638);  
  Get_m0_m12_robin(file_123640);  
  Get_m0_m12_robin(file_123641);  
  Get_m0_m12_robin(file_123642);  
  Get_m0_m12_robin(file_123643);  
  Get_m0_m12_robin(file_123644);  
  Get_m0_m12_robin(file_123645);  
  Get_m0_m12_robin(file_123646);  
  Get_m0_m12_robin(file_123647);  
  Get_m0_m12_robin(file_123648);  
  Get_m0_m12_robin(file_123649);  
  Get_m0_m12_robin(file_123650);  
  Get_m0_m12_robin(file_123651);  
  Get_m0_m12_robin(file_123652);  
  Get_m0_m12_robin(file_123653);  
  Get_m0_m12_robin(file_123654);  
  Get_m0_m12_robin(file_123655);  
  Get_m0_m12_robin(file_123656);  
  Get_m0_m12_robin(file_123657);  
  Get_m0_m12_robin(file_123658);  
  Get_m0_m12_robin(file_123659);  
  Get_m0_m12_robin(file_123660);  
  Get_m0_m12_robin(file_123661);  
  Get_m0_m12_robin(file_123662);  
  Get_m0_m12_robin(file_123663);  
  Get_m0_m12_robin(file_123664);  
  Get_m0_m12_robin(file_123665);  
  Get_m0_m12_robin(file_123666);  
  Get_m0_m12_robin(file_123667);  
  Get_m0_m12_robin(file_123668);  
  Get_m0_m12_robin(file_123669);  
  Get_m0_m12_robin(file_123670);  
  Get_m0_m12_robin(file_123671);  
  Get_m0_m12_robin(file_123672);  
  Get_m0_m12_robin(file_123673);  
  Get_m0_m12_robin(file_123674);  
  Get_m0_m12_robin(file_123675);  
  Get_m0_m12_robin(file_123676);  
  Get_m0_m12_robin(file_123677);  
  Get_m0_m12_robin(file_123678);  
  Get_m0_m12_robin(file_123679);  
  Get_m0_m12_robin(file_123680);  
  Get_m0_m12_robin(file_123682);  
  Get_m0_m12_robin(file_123683);  
  Get_m0_m12_robin(file_123684);  
  Get_m0_m12_robin(file_123686);  
  Get_m0_m12_robin(file_123687);  
  Get_m0_m12_robin(file_123688);  
  Get_m0_m12_robin(file_123689);  
  Get_m0_m12_robin(file_123690);  
    

  TString filename = "plots/";
  
  filename+= "NLO_xsection";
  float max = .5;

// ALL PROCESSES

  TCanvas *c2 = new TCanvas("canvas2","canvas2", 200,10,1500,1000);  // 1D histo
  TCanvas *c3 = new TCanvas("canvas3","canvas3", 200,10,1500,1000);  // 1D histo
  TCanvas *c4 = new TCanvas("canvas4","canvas4", 200,10,1500,1000);  // 1D histo
  TCanvas *c5 = new TCanvas("canvas5","canvas5", 200,10,1500,1000);  // 1D histo
  TCanvas *c6 = new TCanvas("canvas6","canvas6", 200,10,1500,1000);  // 1D histo
  TCanvas *c7 = new TCanvas("canvas7","canvas7", 200,10,1500,1000);  // 1D histo
  TCanvas *c8 = new TCanvas("canvas8","canvas8", 200,10,1500,1000);  // 1D histo
  TCanvas *c9 = new TCanvas("canvas9","canvas9", 200,10,1500,1000);  // 1D histo
  TCanvas *c1 = new TCanvas("canvas1","canvas1", 200,10,1500,1000);  // 1D histo
  
  c2->SetLogz();
  c1->SetLogz();
  c3->SetLogz();
  c4->SetLogz();
  c5->SetLogz();
  c6->SetLogz();
  c7->SetLogz();
  c8->SetLogz();
  c9->SetLogz();

  c2->cd(); 
  draw(grid_gq, max, "#sigma_{NLO} #tilde{g}#tilde{q}"); // 1 gluino + 1 squark
 
  c3->cd(); 
  draw(grid_gg, max, "#sigma_{NLO} #tilde{g}#tilde{g}"); // 2 gluinos

  c4->cd(); 
  draw(grid_qq, max, "#sigma_{NLO} #tilde{q}#tilde{q}"); // 2 squarks

  c5->cd();
  draw(grid_qaq, max, "#sigma_{NLO} #tilde{q}#bar{#tilde{q}}"); // 1 squark 1 antisquark

  c6->cd();
  draw(grid_tt, max, "#sigma_{NLO} #tilde{t}#bar{#tilde{t}}"); // 1 stop antistop

  c7->cd();
  draw(grid_bb, max, "#sigma_{NLO} #tilde{b}#bar{#tilde{b}}"); // 1 sbottom antisbottom

  c8->cd();
  draw(grid_gchi, max, "#sigma_{NLO} #tilde{g}#chi"); // 1 gluino + chi

  c9->cd();
  draw(grid_qqchi, max, "#sigma_{NLO} #tilde{q}#bar{#tilde{q}}#chi"); // 1 squark 1 antisquark + chi

  c1->cd();
  draw(grid_cs, max, "#sigma_{NLO} All"); 

  c1->Print(filename+".pdf");
  c1->Print(filename+".eps"); 
  c2->Print(filename+"_gq.eps"); 
  c3->Print(filename+"_gg.eps"); 
  c4->Print(filename+"_qq.eps"); 
  c5->Print(filename+"_qaq.eps"); 
  c6->Print(filename+"_tt.eps"); 
  c7->Print(filename+"_bb.eps"); 
  c8->Print(filename+"_gchi.eps"); 
  c9->Print(filename+"_qaqchi.eps"); 
  
  myfile << "  return;"<<endl;
  myfile << "}"<<endl;
  myfile.close();
   
}

void draw(TH2D* h_grid, float max, TString text) 
{
  
  h_grid->SetMinimum(0.001);
  h_grid->SetXTitle("M_{0} [GeV]");
  h_grid->SetYTitle("M_{1/2} [GeV]    ");
  h_grid->GetYaxis()->SetRangeUser(0,620);  
//  h_grid->Draw("COLZ TEXT"); 
//  h_grid->Draw("COLZ"); 
  h_grid->SetMarkerSize(0.9);
  h_grid->Draw("text45colz");

  TLatex n;
  n.SetNDC();
  n.SetTextFont(42);
  n.SetTextColor(kBlack);
  n.DrawLatex(0.60,0.25,text);
  
}
// where channel is the processname and valuename can be anything from: K, crossSection, PDFUncertainty, ScaleUncertainty2Q or ScaleUncertainty12Q
// needs a pointer to the already opened SignalUncertainties File from Robin found on the susy-MET sharepoint

double getUncertaintyValue(double m0,double m12, int channel, string valuename, TFile * input)
{
  bool DEBUGuncertaintyValue=false;
/*
  string buffer = doubletostr(m0)+doubletostr(m12)+inttostr(channel)+valuename;
  map <std::string, double>::iterator iter;
  iter=UncertaintyValueBuffer.find(buffer);
  if (bufferValue && iter!=UncertaintyValueBuffer.end()) return iter->second;
*/
  double returnvalue2 ;
  double min=-10;
  double max=+10;

  //cout << "v" ;
  string leaveName="";
  if (valuename=="K") leaveName="K";
  if (valuename=="crossSection") {leaveName="crossSection"; min=0; max=100000;};
  if (valuename=="PDFUncertainty") leaveName="relUncPDF";
  if (valuename=="ScaleUncertainty2Q") leaveName="relScaleUnc2Q";
  if (valuename=="ScaleUncertainty12Q") leaveName="relScaleUncHalfQ";
  if (leaveName=="") throw "no leave found for that value";

  string commandstring=leaveName+">>h1";
  string conditionstring= "finalState>" + doubletostr(channel-0.1)  +"&& finalState<"+ doubletostr(channel+0.1) +"&& m0>" + doubletostr(m0-0.5) + " && m0<"+doubletostr(m0+0.5) +" && m12>" + doubletostr(m12-0.5) + " && m12<"+doubletostr(m12+0.5);

  if (DEBUGuncertaintyValue){
  	  cout << "	 commandstring " << commandstring << endl;
  	  cout << "	 conditionstring " << conditionstring << endl;
  	  cout << "	 leaveName " << leaveName << endl;
  	  cout << "	 valuename :" << valuename << " channel: " << channel << " m0: " << m0 << " m12: " << m12   << endl;
  	  }

  TNtuple *ntuple = (TNtuple*)file_robin->Get("SignalUncertainties");
  if (ntuple==0) throw "Ntuple not found";

  if (DEBUGuncertaintyValue) cout << "(min,max) "<<min << " "<<max<<endl;
  TH1F * h1 = new TH1F("h1","h1",100000,min,max);
  ntuple->Draw(commandstring.c_str(),conditionstring.c_str());

  if (DEBUGuncertaintyValue) cout << "mean " << h1->GetMean()<<endl;
  
  returnvalue2 = fabs (h1->GetMean());
//  UncertaintyValueBuffer[buffer]=returnvalue2;
  
  delete h1;

  return returnvalue2;
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

int isChannel(int channel)
{
if (channel==1)	 return 1;
if (channel==2)	 return 1;
if (channel==3)	 return 1;
if (channel==4)	 return 1;
if (channel==51) return 1;
if (channel==52) return 1;
if (channel==61) return 1;
if (channel==62) return 1;
if (channel==71) return 1;
if (channel==72) return 1;
if (channel==73) return 1;
if (channel==74) return 1;
if (channel==75) return 1;
if (channel==76) return 1;
if (channel==77) return 1;
if (channel==78) return 1;
if (channel==81) return 1;
if (channel==82) return 1;
if (channel==83) return 1;
if (channel==84) return 1;
if (channel==85) return 1;
if (channel==86) return 1;
if (channel==87) return 1;
if (channel==88) return 1;
if (channel==90) return 0; 
if (channel==9)  return 0;
/*
        - 1 for sq-gl
        - 2 for gl-gl
        - 3 for sq-sq
        - 4 for sq-antisq
        - 51 for sbottom pair 1
        - 52 for sbottom pair 2
        - 61 for stop-antistop 1
        - 62 for stop-antistop 2
        - 71, 72, 73, 74 = chi^{0}_{1,2,3,4} - gluino
        - 75, 76 = chi^{+}_{1, 2} - gluino
        - 77, 78 = chi^{-}_{1, 2}  -gluino
        - 81, 82, 83, 84 = chi^{0}_{1,2,3,4} -squark
        - 85, 86 = chi^{+}_{1, 2} - squark
        - 87, 88 = chi^{-}_{1, 2}  -squark*/
return 0;
}

//  myfile << "void get_cs(double run,  double *xsection , double *xsection_process, int channel){"<<endl;

void Get_m0_m12_robin(TFile *file){

  TH1I* runNumber  = (TH1I*)(file ->Get("runNumber_histo")) ;  
//  int Nevents = (int)(runNumber ->Integral());
  double run = (runNumber ->GetMean());

  double m0=0.;
  double m12=0.;
  
  get_m0_m12(run, &m0, &m12);

  myfile << "  if (run=="<<run<<") {"<<endl;
  
// GET NLO XSECTION  

  double NLOcrossSection = 0.;
  double NLOcrossSection_cs = 0.;
  double NLOcrossSection_gq = 0.;
  double NLOcrossSection_gg= 0.; 
  double NLOcrossSection_qq= 0.; 
  double NLOcrossSection_qaq= 0.;
  double NLOcrossSection_tt = 0.;
  double NLOcrossSection_bb = 0.;
  double NLOcrossSection_gchi= 0.;
  double NLOcrossSection_qqchi= 0.;

  int maxchannels=91;

  for(int i = 0; i < maxchannels;i++){
    if (isChannel(i)){
    //cout << i << endl;
      double thisCrossSection = getUncertaintyValue(m0,m12, i, "crossSection", file_robin);
      NLOcrossSection +=thisCrossSection;
      
      if (i==1) NLOcrossSection_gq  +=thisCrossSection;
      if (i==2) NLOcrossSection_gg  +=thisCrossSection;
      if (i==3) NLOcrossSection_qq  +=thisCrossSection;
      if (i==4) NLOcrossSection_qaq +=thisCrossSection;
      if (i==51) NLOcrossSection_tt +=thisCrossSection;
      if (i==52) NLOcrossSection_tt +=thisCrossSection;
      if (i==61) NLOcrossSection_bb +=thisCrossSection;
      if (i==62) NLOcrossSection_bb +=thisCrossSection;
      if ((i>=71)&&(i<=78)) NLOcrossSection_gchi  +=thisCrossSection;
      if ((i>=81)&&(i<=88)) NLOcrossSection_qqchi +=thisCrossSection;
     
      myfile << "    if (channel=="<<i<<") {*xsection_process ="<<thisCrossSection<<";}"<<endl;
    }
  }
  
  myfile << "    *xsection = "<<NLOcrossSection<<";"<<endl;
  myfile << "  }"<<endl;
  
  cout << "  run "<<run<<" m0 "<<m0<<" m12 "<<m12<<" x-section "<<NLOcrossSection<<endl;
  
  grid_cs ->Fill(m0, m12, NLOcrossSection);
  grid_gq ->Fill(m0, m12, NLOcrossSection_gq);
  grid_gg ->Fill(m0, m12, NLOcrossSection_gg);
  grid_qq ->Fill(m0, m12, NLOcrossSection_qq);
  grid_qaq->Fill(m0, m12, NLOcrossSection_qaq);
  grid_tt ->Fill(m0, m12, NLOcrossSection_tt);
  grid_bb ->Fill(m0, m12, NLOcrossSection_bb);
  grid_gchi->Fill(m0, m12, NLOcrossSection_gchi); 
  grid_qqchi->Fill(m0, m12, NLOcrossSection_qqchi);  


}
