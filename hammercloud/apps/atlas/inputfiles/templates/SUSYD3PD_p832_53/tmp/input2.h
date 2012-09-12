TString prefix = "result";
TString suffix = "";

std::vector <int> ds_egamma(){

  std::vector <int> ds;
  
  ds.push_back(178080); 
  ds.push_back(180183); 
  ds.push_back(180658); 
  ds.push_back(182423);
  ds.push_back(183134);
  ds.push_back(183942);
  
  return ds;

}

std::vector <int> ds_muon(){

  std::vector <int> ds;
  
  ds.push_back(178080); 
  ds.push_back(182425);
  ds.push_back(180188); 
  ds.push_back(183137);
  ds.push_back(180659); 
  ds.push_back(183940);
  
  return ds;
}

std::vector <int> ds_qcd(){

  std::vector <int> ds;
  
  ds.push_back(105000); 
  
  return ds;
}

std::vector <int> ds_wjets(){

  std::vector <int> ds;
  
  ds.push_back(107680);
  ds.push_back(107681);
  ds.push_back(107682);
  ds.push_back(107683);
  ds.push_back(107684);
  ds.push_back(107685);
  ds.push_back(107690);
  ds.push_back(107691);
  ds.push_back(107692);
  ds.push_back(107693);
  ds.push_back(107694);
  ds.push_back(107695);
  ds.push_back(107700);
  ds.push_back(107701);
  ds.push_back(107702);
  ds.push_back(107703);
  ds.push_back(107704);
  ds.push_back(107705);

#ifdef WBB                         //Wbb  
  ds.push_back(106280);
  ds.push_back(106281);
  ds.push_back(106282);
  ds.push_back(106283);
#endif  
  
  return ds;

}

std::vector <int> ds_zjets(){

  std::vector <int> ds;
  
  ds.push_back(107650);
  ds.push_back(107651);
  ds.push_back(107652);
  ds.push_back(107653);
  ds.push_back(107654);
  ds.push_back(107655);
  ds.push_back(107660);
  ds.push_back(107661);
  ds.push_back(107662);
  ds.push_back(107663);
  ds.push_back(107664);
  ds.push_back(107665);
  ds.push_back(107670);
  ds.push_back(107671);
  ds.push_back(107672);
  ds.push_back(107673);
  ds.push_back(107674);
  ds.push_back(107675);
  
  return ds;

}

std::vector <int> ds_ttbar(){

  std::vector <int> ds;
  
  ds.push_back(105200); 
  ds.push_back(105204); 
  
  return ds;

}
std::vector <int> ds_top(){

  std::vector <int> ds;
  
  ds.push_back(108340);
  ds.push_back(108341);
  ds.push_back(108342);
  ds.push_back(108343);
  ds.push_back(108344);
  ds.push_back(108345);
  ds.push_back(108346);
  
  return ds;

}

std::vector <int> ds_diboson(){

  std::vector <int> ds;
  
  ds.push_back(105985); 
  ds.push_back(105986); 
  ds.push_back(105987);   
  
  return ds;

}

std::vector <int> ds_su4(){

  std::vector <int> ds;
  
  ds.push_back(106484); 
  
  return ds;

}

std::vector <int> ds_drellyan(){

  std::vector <int> ds;
  
  ds.push_back(116250);
  ds.push_back(116251);
  ds.push_back(116252);
  ds.push_back(116253);
  ds.push_back(116254);
  ds.push_back(116255);
  ds.push_back(116260);
  ds.push_back(116261);
  ds.push_back(116262);
  ds.push_back(116263);
  ds.push_back(116264);
  ds.push_back(116265);
  ds.push_back(116270);
  ds.push_back(116271);
  ds.push_back(116272);
  ds.push_back(116273);
  ds.push_back(116274);
  ds.push_back(116275);
  
  return ds;

}

double Normalize(int run, double lumi, TFile *file){

  TH1I* runNumber  = (TH1I*)(file ->Get("runNumber_histo")) ;  
  float Nevents = (float)(runNumber ->Integral());
  double mean = (runNumber ->GetMean());
  double norm = 1.;

// cross-sections from https://twiki.cern.ch/twiki/bin/view/AtlasProtected/TopMC2009

  double nb = 1.;
  double pb = 0.001;

/*
if (run==107660){
 cout << "mean "<<mean <<endl;
 cout << " Nevents "<<Nevents<<endl;
}*/

double norm = -1;

//data
if ((run>=150000)&&(run<=200000)) norm = 1.; 

//QCD 
if (run==108326) norm = (     75126.6 *pb*lumi/Nevents); 

if (run==105000) norm = (     1. *nb*lumi/Nevents); 

if (run==105000) cout << "norm "<<norm<< " nevents "<<Nevents <<endl;
 
//QCD Jx
if (run==105009) norm = (     9752970.      *nb *lumi/Nevents); 
if (run==105010) norm = (      673020.      *nb *lumi/Nevents); 
if (run==105011) norm = (       41194.7     *nb *lumi/Nevents); 
if (run==105012) norm = (        2193.25    *nb *lumi/Nevents); 
if (run==105013) norm = (         87.8487   *nb *lumi/Nevents); 
if (run==105014) norm = (	  2.332856  *nb *lumi/Nevents); 
if (run==105015) norm = (         0.0338461 *nb *lumi/Nevents); 

//QCD Muon filtered
if (run==109276) norm = ( 843.782706 *nb *lumi/Nevents); 
if (run==109277) norm = ( 821.174244 *nb *lumi/Nevents); 
if (run==109278) norm = ( 222.497208 *nb *lumi/Nevents); 
if (run==109279) norm = ( 28.6195379 *nb *lumi/Nevents); 
if (run==109280) norm = ( 1.959926405 *nb *lumi/Nevents); 
if (run==109281) norm = ( 0.071004224 *nb *lumi/Nevents); 
if (run==209435) norm = ( 0.00115 *nb *lumi/Nevents); //check

//Wjets -- use the same cs for e/mu/tau
if (run==107680) norm = (6.9133*1.19887 *nb *lumi/Nevents); 
if (run==107681) norm = (1.293 *1.19887 *nb *lumi/Nevents); 
if (run==107682) norm = (0.3771*1.19887 *nb *lumi/Nevents); 
if (run==107683) norm = (0.1009*1.19887 *nb *lumi/Nevents); 
if (run==107684) norm = (0.0253*1.19887 *nb *lumi/Nevents); 
if (run==107685) norm = (0.0069*1.19887 *nb *lumi/Nevents); 
if (run==107690) norm = (6.9133*1.19887 *nb *lumi/Nevents); 
if (run==107691) norm = (1.293 *1.19887 *nb *lumi/Nevents); 
if (run==107692) norm = (0.3771*1.19887 *nb *lumi/Nevents); 
if (run==107693) norm = (0.1009*1.19887 *nb *lumi/Nevents); 
if (run==107694) norm = (0.0253*1.19887 *nb *lumi/Nevents); 
if (run==107695) norm = (0.0069*1.19887 *nb *lumi/Nevents); 
if (run==107700) norm = (6.9133*1.19887 *nb *lumi/Nevents); 
if (run==107701) norm = (1.293 *1.19887 *nb *lumi/Nevents); 
if (run==107702) norm = (0.3771*1.19887 *nb *lumi/Nevents); 
if (run==107703) norm = (0.1009*1.19887 *nb *lumi/Nevents); 
if (run==107704) norm = (0.0253*1.19887 *nb *lumi/Nevents); 
if (run==107705) norm = (0.0069*1.19887 *nb *lumi/Nevents); 

//Wbb
if (run==106280) norm = (3.3072 * pb * 1.*lumi/Nevents); 
if (run==106281) norm = (2.6756 * pb * 1.*lumi/Nevents); 
if (run==106282) norm = (1.3763 * pb * 1.*lumi/Nevents); 
if (run==106283) norm = (0.65689* pb * 1.*lumi/Nevents); 

//Zjets -- use the same cs for e/mu/tau - no k factor for the moment
if (run==107650) norm = (0.830125   *nb *lumi/Nevents); 
if (run==107651) norm = (0.1662375  *nb *lumi/Nevents); 
if (run==107652) norm = (0.0502825  *nb *lumi/Nevents); 
if (run==107653) norm = (0.0139225  *nb *lumi/Nevents); 
if (run==107654) norm = (.003615625 *nb *lumi/Nevents); 
if (run==107655) norm = (.0009417875*nb *lumi/Nevents);
if (run==107660) norm = (0.830125   *nb *lumi/Nevents); 
if (run==107661) norm = (0.1662375  *nb *lumi/Nevents); 
if (run==107662) norm = (0.0502825  *nb *lumi/Nevents); 
if (run==107663) norm = (0.0139225  *nb *lumi/Nevents); 
if (run==107664) norm = (.003615625 *nb *lumi/Nevents); 
if (run==107665) norm = (.0009417875*nb *lumi/Nevents);
if (run==107670) norm = (0.830125   *nb *lumi/Nevents); 
if (run==107671) norm = (0.1662375  *nb *lumi/Nevents); 
if (run==107672) norm = (0.0502825  *nb *lumi/Nevents); 
if (run==107673) norm = (0.0139225  *nb *lumi/Nevents); 
if (run==107674) norm = (.003615625 *nb *lumi/Nevents); 
if (run==107675) norm = (.0009417875*nb *lumi/Nevents);
 
//low Drell yan
if (run==108319) norm = (1.2529*nb *0.944665 *lumi/Nevents);  //0.95 efficiency: filter to cut off true mll > 40 GeV (numbers from Borge)
if (run==108320) norm = (1.2530*nb *0.944674 *lumi/Nevents); //check
if (run==108321) norm = (4.4070*nb *0.51 *lumi/Nevents);
if (run==108322) norm = (4.4061*nb *0.50 *lumi/Nevents);

if (run==116250) norm = ( 3.0   *nb *lumi/Nevents);
if (run==116251) norm = ( 84.91 *pb *lumi/Nevents); 
if (run==116252) norm = ( 41.19 *pb *lumi/Nevents); 
if (run==116253) norm = ( 8.35  *pb *lumi/Nevents); 
if (run==116254) norm = ( 1.85  *pb *lumi/Nevents); 
if (run==116255) norm = ( 0.46  *pb *lumi/Nevents); 
if (run==116260) norm = ( 3.0   *nb *lumi/Nevents);
if (run==116261) norm = ( 84.78 *pb *lumi/Nevents); 
if (run==116262) norm = ( 41.13 *pb *lumi/Nevents); 
if (run==116263) norm = ( 8.34  *pb *lumi/Nevents); 
if (run==116264) norm = ( 1.87  *pb *lumi/Nevents); 
if (run==116265) norm = ( 0.46  *pb *lumi/Nevents); 
if (run==116270) norm = ( 3.0   *nb *lumi/Nevents);
if (run==116271) norm = ( 84.88 *pb *lumi/Nevents); 
if (run==116272) norm = ( 41.28 *pb *lumi/Nevents); 
if (run==116273) norm = ( 8.35  *pb *lumi/Nevents); 
if (run==116274) norm = ( 1.83  *pb *lumi/Nevents); 
if (run==116275) norm = ( 0.46  *pb *lumi/Nevents); 

//DIBOSON 
if (run==105985) norm = ( 44.9*0.3884 *pb *lumi/Nevents); 
if (run==105986) norm = ( 5.96*0.2123 *pb *lumi/Nevents); 
if (run==105987) norm = ( 18.0*0.3085 *pb * lumi/Nevents); 

//SINGLE TOP 
if (run==108340) norm = (  7.0 *pb * lumi/Nevents); 
if (run==108341) norm = (  7.0 *pb * lumi/Nevents); 
if (run==108342) norm = (  7.0 *pb * lumi/Nevents); 
if (run==108343) norm = (  4.7*0.1 *pb * lumi/Nevents); 
if (run==108344) norm = (  4.7*0.1 *pb * lumi/Nevents); 
if (run==108345) norm = (  4.7*0.1 *pb * lumi/Nevents); 
if (run==108346) norm = (  1.3*10 *pb * lumi/Nevents); 

//SU4 

if (run==106484) cout << "SU4 cross section (pb) 59.95"<<endl;
if (run==106484) norm = (59.95*pb *lumi/Nevents);//check
if (run==106480) norm = (52.8*pb *lumi/Nevents);

//T1
// ttbar with leptons
if (run==105200) norm = (160.79*0.556*pb *lumi/Nevents);// was 80.201*pb * 1.09
//fully hadronic ttbar
if (run==105204) norm = (160.79*0.444*pb *lumi/Nevents);//


// Grids                    
if (run==127001) norm = (1.6989E-01 * 6.8663E-01*nb *lumi/Nevents); 
if (run==127002) norm = (1.6506E-01 * 4.6808E-01*nb *lumi/Nevents); 
if (run==127003) norm = (9.7721E-02 * 6.2555E-01*nb *lumi/Nevents); 
if (run==127004) norm = (9.4767E-02 * 2.5236E-01*nb *lumi/Nevents); 
if (run==127005) norm = (6.5929E-02 * 5.7850E-01*nb *lumi/Nevents); 
if (run==127006) norm = (6.3097E-02 * 2.0566E-01*nb *lumi/Nevents); 
if (run==127007) norm = (5.1581E-02 * 5.5947E-01*nb *lumi/Nevents); 
if (run==127008) norm = (4.9471E-02 * 1.8179E-01*nb *lumi/Nevents); 
if (run==127009) norm = (4.5069E-02 * 5.4891E-01*nb *lumi/Nevents); 
if (run==127010) norm = (4.3050E-02 * 1.7508E-01*nb *lumi/Nevents); 
if (run==127011) norm = (4.1927E-02 * 5.3967E-01*nb *lumi/Nevents); 
if (run==127012) norm = (3.9964E-02 * 1.6426E-01*nb *lumi/Nevents); 
if (run==127013) norm = (4.0729E-02 * 5.3769E-01*nb *lumi/Nevents); 
if (run==127014) norm = (3.8460E-02 * 1.6512E-01*nb *lumi/Nevents); 
if (run==127015) norm = (3.9894E-02 * 5.4042E-01*nb *lumi/Nevents); 
if (run==127016) norm = (3.7868E-02 * 1.5884E-01*nb *lumi/Nevents); 
if (run==127017) norm = (3.9738E-02 * 5.3522E-01*nb *lumi/Nevents); 
if (run==127018) norm = (3.7175E-02 * 1.5930E-01*nb *lumi/Nevents); 
if (run==127019) norm = (4.0643E-02 * 5.2073E-01*nb *lumi/Nevents); 
if (run==127020) norm = (3.8561E-02 * 1.7977E-01*nb *lumi/Nevents); 
if (run==127021) norm = (1.6820E-01 * 6.2321E-01*nb *lumi/Nevents); 
if (run==127022) norm = (1.6360E-01 * 6.2633E-01*nb *lumi/Nevents); 
if (run==127023) norm = (8.4238E-02 * 6.0916E-01*nb *lumi/Nevents); 
if (run==127024) norm = (8.0461E-02 * 6.0132E-01*nb *lumi/Nevents); 
if (run==127025) norm = (3.4017E-02 * 5.7650E-01*nb *lumi/Nevents); 
if (run==127026) norm = (3.1587E-02 * 4.8714E-01*nb *lumi/Nevents); 
if (run==127027) norm = (1.9971E-02 * 4.2622E-01*nb *lumi/Nevents); 
if (run==127028) norm = (1.8344E-02 * 2.6284E-01*nb *lumi/Nevents); 
if (run==127029) norm = (1.2781E-02 * 3.5446E-01*nb *lumi/Nevents); 
if (run==127030) norm = (1.1756E-02 * 2.1434E-01*nb *lumi/Nevents); 
if (run==127031) norm = (9.3924E-03 * 3.2200E-01*nb *lumi/Nevents); 
if (run==127032) norm = (8.6160E-03 * 1.9623E-01*nb *lumi/Nevents); 
if (run==127033) norm = (7.6913E-03 * 3.0650E-01*nb *lumi/Nevents); 
if (run==127034) norm = (6.9981E-03 * 1.8292E-01*nb *lumi/Nevents); 
if (run==127035) norm = (6.7574E-03 * 2.9523E-01*nb *lumi/Nevents); 
if (run==127036) norm = (6.2056E-03 * 1.7453E-01*nb *lumi/Nevents); 
if (run==127037) norm = (6.3822E-03 * 2.8809E-01*nb *lumi/Nevents); 
if (run==127038) norm = (5.7908E-03 * 1.6370E-01*nb *lumi/Nevents); 
if (run==127039) norm = (6.1371E-03 * 2.8850E-01*nb *lumi/Nevents); 
if (run==127040) norm = (5.5958E-03 * 1.6105E-01*nb *lumi/Nevents); 
if (run==127041) norm = (6.3509E-03 * 2.9659E-01*nb *lumi/Nevents); 
if (run==127042) norm = (5.7615E-03 * 1.6858E-01*nb *lumi/Nevents); 
if (run==127043) norm = (3.3790E-02 * 6.3646E-01*nb *lumi/Nevents); 
if (run==127044) norm = (3.1548E-02 * 6.1028E-01*nb *lumi/Nevents); 
if (run==127045) norm = (5.1730E-02 * 6.0850E-01*nb *lumi/Nevents); 
if (run==127046) norm = (4.9720E-02 * 6.0577E-01*nb *lumi/Nevents); 
if (run==127047) norm = (2.0109E-02 * 6.3251E-01*nb *lumi/Nevents); 
if (run==127048) norm = (1.8172E-02 * 6.0783E-01*nb *lumi/Nevents); 
if (run==127049) norm = (8.9228E-03 * 5.2938E-01*nb *lumi/Nevents); 
if (run==127050) norm = (7.9371E-03 * 4.9761E-01*nb *lumi/Nevents); 
if (run==127051) norm = (5.2400E-03 * 3.4478E-01*nb *lumi/Nevents); 
if (run==127052) norm = (4.7178E-03 * 2.6687E-01*nb *lumi/Nevents); 
if (run==127053) norm = (3.2797E-03 * 2.9920E-01*nb *lumi/Nevents); 
if (run==127054) norm = (2.9416E-03 * 2.1991E-01*nb *lumi/Nevents); 
if (run==127055) norm = (2.2868E-03 * 2.6535E-01*nb *lumi/Nevents); 
if (run==127056) norm = (2.0307E-03 * 1.9857E-01*nb *lumi/Nevents); 
if (run==127057) norm = (1.7757E-03 * 2.5082E-01*nb *lumi/Nevents); 
if (run==127058) norm = (1.5801E-03 * 1.8859E-01*nb *lumi/Nevents); 
if (run==127059) norm = (1.5107E-03 * 2.4084E-01*nb *lumi/Nevents); 
if (run==127060) norm = (1.3251E-03 * 1.7260E-01*nb *lumi/Nevents); 
if (run==127061) norm = (1.3644E-03 * 2.3519E-01*nb *lumi/Nevents); 
if (run==127062) norm = (1.1962E-03 * 1.6176E-01*nb *lumi/Nevents); 
if (run==127063) norm = (1.3273E-03 * 2.5551E-01*nb *lumi/Nevents); 
if (run==127064) norm = (1.1736E-03 * 1.6536E-01*nb *lumi/Nevents); 
if (run==127065) norm = (8.9753E-03 * 6.2649E-01*nb *lumi/Nevents); 
if (run==127066) norm = (8.0463E-03 * 6.1805E-01*nb *lumi/Nevents); 
if (run==127067) norm = (3.7926E-02 * 5.9959E-01*nb *lumi/Nevents); 
if (run==127068) norm = (3.5874E-02 * 5.9340E-01*nb *lumi/Nevents); 
if (run==127069) norm = (1.3228E-02 * 6.1035E-01*nb *lumi/Nevents); 
if (run==127070) norm = (1.2307E-02 * 6.0894E-01*nb *lumi/Nevents); 
if (run==127071) norm = (5.7969E-03 * 6.0717E-01*nb *lumi/Nevents); 
if (run==127072) norm = (5.2808E-03 * 6.0096E-01*nb *lumi/Nevents); 
if (run==127073) norm = (2.7325E-03 * 4.9692E-01*nb *lumi/Nevents); 
if (run==127074) norm = (2.3919E-03 * 4.9097E-01*nb *lumi/Nevents); 
if (run==127075) norm = (1.6259E-03 * 3.3049E-01*nb *lumi/Nevents); 
if (run==127076) norm = (1.4250E-03 * 2.8000E-01*nb *lumi/Nevents); 
if (run==127077) norm = (9.9729E-04 * 2.8619E-01*nb *lumi/Nevents); 
if (run==127078) norm = (8.6925E-04 * 2.3373E-01*nb *lumi/Nevents); 
if (run==127079) norm = (6.7591E-04 * 2.6114E-01*nb *lumi/Nevents); 
if (run==127080) norm = (5.8596E-04 * 2.1073E-01*nb *lumi/Nevents); 
if (run==127081) norm = (5.0060E-04 * 2.4553E-01*nb *lumi/Nevents); 
if (run==127082) norm = (4.3285E-04 * 1.9648E-01*nb *lumi/Nevents); 
if (run==127083) norm = (4.0595E-04 * 2.4219E-01*nb *lumi/Nevents); 
if (run==127084) norm = (3.4643E-04 * 1.7703E-01*nb *lumi/Nevents); 
if (run==127085) norm = (3.4258E-04 * 2.8855E-01*nb *lumi/Nevents); 
if (run==127086) norm = (2.9680E-04 * 1.6650E-01*nb *lumi/Nevents); 
if (run==127087) norm = (2.7834E-03 * 6.0717E-01*nb *lumi/Nevents); 
if (run==127088) norm = (2.4389E-03 * 5.9616E-01*nb *lumi/Nevents); 
if (run==127089) norm = (3.0570E-02 * 5.9787E-01*nb *lumi/Nevents); 
if (run==127090) norm = (2.8958E-02 * 5.8140E-01*nb *lumi/Nevents); 
if (run==127091) norm = (9.9740E-03 * 6.0805E-01*nb *lumi/Nevents); 
if (run==127092) norm = (9.2624E-03 * 5.9923E-01*nb *lumi/Nevents); 
if (run==127093) norm = (4.1512E-03 * 6.0872E-01*nb *lumi/Nevents); 
if (run==127094) norm = (3.7211E-03 * 5.9186E-01*nb *lumi/Nevents); 
if (run==127095) norm = (1.9355E-03 * 5.9902E-01*nb *lumi/Nevents); 
if (run==127096) norm = (1.7111E-03 * 5.9531E-01*nb *lumi/Nevents); 
if (run==127097) norm = (9.3852E-04 * 4.8881E-01*nb *lumi/Nevents); 
if (run==127098) norm = (8.2284E-04 * 5.0156E-01*nb *lumi/Nevents); 
if (run==127099) norm = (5.6388E-04 * 3.4083E-01*nb *lumi/Nevents); 
if (run==127100) norm = (4.8574E-04 * 2.8785E-01*nb *lumi/Nevents); 
if (run==127101) norm = (3.4337E-04 * 2.9414E-01*nb *lumi/Nevents); 
if (run==127102) norm = (2.9268E-04 * 2.4040E-01*nb *lumi/Nevents); 
if (run==127103) norm = (2.2604E-04 * 2.8122E-01*nb *lumi/Nevents); 
if (run==127104) norm = (1.9065E-04 * 2.1582E-01*nb *lumi/Nevents); 
if (run==127105) norm = (1.6207E-04 * 2.6770E-01*nb *lumi/Nevents); 
if (run==127106) norm = (1.3398E-04 * 2.0246E-01*nb *lumi/Nevents); 
if (run==127107) norm = (1.0282E-04 * 3.4249E-01*nb *lumi/Nevents); 
if (run==127108) norm = (8.4673E-05 * 1.6766E-01*nb *lumi/Nevents); 
if (run==127109) norm = (9.6352E-04 * 5.7657E-01*nb *lumi/Nevents); 
if (run==127110) norm = (8.3353E-04 * 5.9666E-01*nb *lumi/Nevents); 
if (run==127111) norm = (2.6057E-02 * 6.0002E-01*nb *lumi/Nevents); 
if (run==127112) norm = (2.4444E-02 * 5.8173E-01*nb *lumi/Nevents); 
if (run==127113) norm = (8.1587E-03 * 6.0118E-01*nb *lumi/Nevents); 
if (run==127114) norm = (7.4371E-03 * 5.9046E-01*nb *lumi/Nevents); 
if (run==127115) norm = (3.2108E-03 * 5.9630E-01*nb *lumi/Nevents); 
if (run==127116) norm = (2.8889E-03 * 5.8480E-01*nb *lumi/Nevents); 
if (run==127117) norm = (1.4724E-03 * 5.9609E-01*nb *lumi/Nevents); 
if (run==127118) norm = (1.2848E-03 * 5.8255E-01*nb *lumi/Nevents); 
if (run==127119) norm = (7.1920E-04 * 5.8500E-01*nb *lumi/Nevents); 
if (run==127120) norm = (6.2379E-04 * 5.8748E-01*nb *lumi/Nevents); 
if (run==127121) norm = (3.5726E-04 * 4.7810E-01*nb *lumi/Nevents); 
if (run==127122) norm = (3.0182E-04 * 5.0261E-01*nb *lumi/Nevents); 
if (run==127123) norm = (2.1294E-04 * 3.5199E-01*nb *lumi/Nevents); 
if (run==127124) norm = (1.7998E-04 * 2.9117E-01*nb *lumi/Nevents); 
if (run==127125) norm = (1.2786E-04 * 3.0547E-01*nb *lumi/Nevents); 
if (run==127126) norm = (1.0631E-04 * 2.4899E-01*nb *lumi/Nevents); 
if (run==127127) norm = (8.2840E-05 * 2.9185E-01*nb *lumi/Nevents); 
if (run==127128) norm = (6.7456E-05 * 2.2222E-01*nb *lumi/Nevents); 
if (run==127129) norm = (3.3833E-05 * 3.8464E-01*nb *lumi/Nevents); 
if (run==127130) norm = (2.7225E-05 * 1.6345E-01*nb *lumi/Nevents); 
if (run==127131) norm = (3.6595E-04 * 5.6041E-01*nb *lumi/Nevents); 
if (run==127132) norm = (3.0839E-04 * 5.8761E-01*nb *lumi/Nevents); 
if (run==127133) norm = (2.3165E-02 * 5.9453E-01*nb *lumi/Nevents); 
if (run==127134) norm = (2.1499E-02 * 5.7837E-01*nb *lumi/Nevents); 
if (run==127135) norm = (6.8528E-03 * 5.9895E-01*nb *lumi/Nevents); 
if (run==127136) norm = (6.2695E-03 * 5.8493E-01*nb *lumi/Nevents); 
if (run==127137) norm = (2.6619E-03 * 5.8596E-01*nb *lumi/Nevents); 
if (run==127138) norm = (2.4058E-03 * 5.8514E-01*nb *lumi/Nevents); 
if (run==127139) norm = (1.1747E-03 * 5.8865E-01*nb *lumi/Nevents); 
if (run==127140) norm = (1.0284E-03 * 5.9228E-01*nb *lumi/Nevents); 
if (run==127141) norm = (5.6735E-04 * 5.6786E-01*nb *lumi/Nevents); 
if (run==127142) norm = (4.8625E-04 * 5.8079E-01*nb *lumi/Nevents); 
if (run==127143) norm = (2.8696E-04 * 5.4591E-01*nb *lumi/Nevents); 
if (run==127144) norm = (2.4172E-04 * 5.8153E-01*nb *lumi/Nevents); 
if (run==127145) norm = (1.4343E-04 * 4.6378E-01*nb *lumi/Nevents); 
if (run==127146) norm = (1.1718E-04 * 5.0638E-01*nb *lumi/Nevents); 
if (run==127147) norm = (8.5628E-05 * 3.4809E-01*nb *lumi/Nevents); 
if (run==127148) norm = (7.0299E-05 * 2.9901E-01*nb *lumi/Nevents); 
if (run==127149) norm = (5.0727E-05 * 3.1017E-01*nb *lumi/Nevents); 
if (run==127150) norm = (4.1303E-05 * 2.5364E-01*nb *lumi/Nevents); 
if (run==127151) norm = (1.2422E-05 * 4.3174E-01*nb *lumi/Nevents); 
if (run==127152) norm = (9.3081E-06 * 1.6879E-01*nb *lumi/Nevents); 
if (run==127153) norm = (1.4713E-04 * 5.3271E-01*nb *lumi/Nevents); 
if (run==127154) norm = (1.2336E-04 * 5.8404E-01*nb *lumi/Nevents); 
if (run==127155) norm = (2.1107E-02 * 5.8692E-01*nb *lumi/Nevents); 
if (run==127156) norm = (1.9175E-02 * 5.7790E-01*nb *lumi/Nevents); 
if (run==127157) norm = (6.0856E-03 * 5.9496E-01*nb *lumi/Nevents); 
if (run==127158) norm = (5.4773E-03 * 5.8336E-01*nb *lumi/Nevents); 
if (run==127159) norm = (2.2845E-03 * 5.9375E-01*nb *lumi/Nevents); 
if (run==127160) norm = (2.0512E-03 * 5.7392E-01*nb *lumi/Nevents); 
if (run==127161) norm = (9.9239E-04 * 5.6889E-01*nb *lumi/Nevents); 
if (run==127162) norm = (8.8001E-04 * 5.7904E-01*nb *lumi/Nevents); 
if (run==127163) norm = (4.7064E-04 * 5.5935E-01*nb *lumi/Nevents); 
if (run==127164) norm = (4.0654E-04 * 5.7657E-01*nb *lumi/Nevents); 
if (run==127165) norm = (2.3377E-04 * 5.5860E-01*nb *lumi/Nevents); 
if (run==127166) norm = (1.9698E-04 * 5.7359E-01*nb *lumi/Nevents); 
if (run==127167) norm = (1.1869E-04 * 5.3482E-01*nb *lumi/Nevents); 
if (run==127168) norm = (9.9160E-05 * 5.7412E-01*nb *lumi/Nevents); 
if (run==127169) norm = (5.9791E-05 * 4.5110E-01*nb *lumi/Nevents); 
if (run==127170) norm = (4.8872E-05 * 5.0829E-01*nb *lumi/Nevents); 
if (run==127171) norm = (3.6383E-05 * 3.5276E-01*nb *lumi/Nevents); 
if (run==127172) norm = (2.8703E-05 * 2.9758E-01*nb *lumi/Nevents); 
if (run==127173) norm = (4.7747E-06 * 4.7349E-01*nb *lumi/Nevents); 
if (run==127174) norm = (3.3444E-06 * 1.6804E-01*nb *lumi/Nevents); 
if (run==127175) norm = (6.2053E-05 * 5.1451E-01*nb *lumi/Nevents); 
if (run==127176) norm = (5.1446E-05 * 5.7372E-01*nb *lumi/Nevents); 
if (run==127177) norm = (1.9414E-02 * 5.8837E-01*nb *lumi/Nevents); 
if (run==127178) norm = (1.7953E-02 * 5.6211E-01*nb *lumi/Nevents); 
if (run==127179) norm = (5.4410E-03 * 5.8534E-01*nb *lumi/Nevents); 
if (run==127180) norm = (4.8894E-03 * 5.7850E-01*nb *lumi/Nevents); 
if (run==127181) norm = (2.0443E-03 * 5.8817E-01*nb *lumi/Nevents); 
if (run==127182) norm = (1.8087E-03 * 5.6142E-01*nb *lumi/Nevents); 
if (run==127183) norm = (8.8349E-04 * 5.7991E-01*nb *lumi/Nevents); 
if (run==127184) norm = (7.7258E-04 * 5.7452E-01*nb *lumi/Nevents); 
if (run==127185) norm = (4.0587E-04 * 5.6484E-01*nb *lumi/Nevents); 
if (run==127186) norm = (3.4863E-04 * 5.6313E-01*nb *lumi/Nevents); 
if (run==127187) norm = (1.9694E-04 * 5.5445E-01*nb *lumi/Nevents); 
if (run==127188) norm = (1.6851E-04 * 5.7228E-01*nb *lumi/Nevents); 
if (run==127189) norm = (9.9416E-05 * 5.2877E-01*nb *lumi/Nevents); 
if (run==127190) norm = (8.3733E-05 * 5.6974E-01*nb *lumi/Nevents); 
if (run==127191) norm = (5.2108E-05 * 5.1722E-01*nb *lumi/Nevents); 
if (run==127192) norm = (4.2232E-05 * 5.7637E-01*nb *lumi/Nevents); 
if (run==127193) norm = (2.6329E-05 * 4.4283E-01*nb *lumi/Nevents); 
if (run==127194) norm = (2.0770E-05 * 5.1319E-01*nb *lumi/Nevents); 
if (run==127195) norm = (1.9703E-06 * 5.1193E-01*nb *lumi/Nevents); 
if (run==127196) norm = (1.2339E-06 * 1.6703E-01*nb *lumi/Nevents); 
if (run==127197) norm = (2.7126E-05 * 4.9471E-01*nb *lumi/Nevents); 
if (run==127198) norm = (2.1613E-05 * 5.6896E-01*nb *lumi/Nevents); 
if (run==127199) norm = (1.1996E-02 * 5.8844E-01*nb *lumi/Nevents); 
if (run==127200) norm = (1.0549E-02 * 5.5267E-01*nb *lumi/Nevents); 
if (run==127201) norm = (2.5803E-03 * 5.8754E-01*nb *lumi/Nevents); 
if (run==127202) norm = (2.1786E-03 * 5.6174E-01*nb *lumi/Nevents); 
if (run==127203) norm = (7.8842E-04 * 5.6268E-01*nb *lumi/Nevents); 
if (run==127204) norm = (6.3054E-04 * 5.7071E-01*nb *lumi/Nevents); 
if (run==127205) norm = (2.9875E-04 * 5.5060E-01*nb *lumi/Nevents); 
if (run==127206) norm = (2.3715E-04 * 5.6754E-01*nb *lumi/Nevents); 
if (run==127207) norm = (1.3086E-04 * 5.2604E-01*nb *lumi/Nevents); 
if (run==127208) norm = (1.0237E-04 * 5.5916E-01*nb *lumi/Nevents); 
if (run==127209) norm = (6.2554E-05 * 5.0592E-01*nb *lumi/Nevents); 
if (run==127210) norm = (4.7916E-05 * 5.3642E-01*nb *lumi/Nevents); 
if (run==127211) norm = (3.1153E-05 * 4.9087E-01*nb *lumi/Nevents); 
if (run==127212) norm = (2.3755E-05 * 5.3723E-01*nb *lumi/Nevents); 
if (run==127213) norm = (1.6117E-05 * 4.6694E-01*nb *lumi/Nevents); 
if (run==127214) norm = (1.1848E-05 * 5.3833E-01*nb *lumi/Nevents); 
if (run==127215) norm = (8.4557E-06 * 4.4338E-01*nb *lumi/Nevents); 
if (run==127216) norm = (6.0484E-06 * 5.2593E-01*nb *lumi/Nevents); 
if (run==138274) norm = (2.6192E+00 * 4.4785E-04*nb *lumi/Nevents); 
if (run==138275) norm = (3.0060E-01 * 2.2723E-03*nb *lumi/Nevents); 
if (run==138276) norm = (1.5065E-01 * 3.5096E-03*nb *lumi/Nevents); 
if (run==138277) norm = (7.4863E-02 * 4.5425E-03*nb *lumi/Nevents); 
if (run==138278) norm = (5.0341E-02 * 4.6012E-03*nb *lumi/Nevents); 
if (run==138279) norm = (3.8609E-02 * 4.2080E-03*nb *lumi/Nevents); 
if (run==138280) norm = (2.3754E-02 * 2.0598E-03*nb *lumi/Nevents); 
if (run==138281) norm = (3.2062E-01 * 2.8639E-03*nb *lumi/Nevents); 
if (run==138282) norm = (1.3643E-01 * 5.1106E-03*nb *lumi/Nevents); 
if (run==138283) norm = (8.3122E-02 * 6.6824E-03*nb *lumi/Nevents); 
if (run==138284) norm = (4.6510E-02 * 8.2226E-03*nb *lumi/Nevents); 
if (run==138285) norm = (3.2496E-02 * 8.9814E-03*nb *lumi/Nevents); 
if (run==138286) norm = (2.5307E-02 * 8.4751E-03*nb *lumi/Nevents); 
if (run==138287) norm = (1.5910E-02 * 5.6688E-03*nb *lumi/Nevents); 
if (run==138288) norm = (1.5681E-01 * 5.3605E-03*nb *lumi/Nevents); 
if (run==138289) norm = (8.0254E-02 * 8.6019E-03*nb *lumi/Nevents); 
if (run==138290) norm = (5.3888E-02 * 1.0613E-02*nb *lumi/Nevents); 
if (run==138291) norm = (3.1717E-02 * 1.3841E-02*nb *lumi/Nevents); 
if (run==138292) norm = (2.2465E-02 * 1.5384E-02*nb *lumi/Nevents); 
if (run==138293) norm = (1.7611E-02 * 1.6353E-02*nb *lumi/Nevents); 
if (run==138294) norm = (1.1151E-02 * 1.3747E-02*nb *lumi/Nevents); 
if (run==138295) norm = (6.4737E-02 * 1.2307E-02*nb *lumi/Nevents); 
if (run==138296) norm = (4.0362E-02 * 1.6923E-02*nb *lumi/Nevents); 
if (run==138297) norm = (2.8566E-02 * 2.0304E-02*nb *lumi/Nevents); 
if (run==138298) norm = (1.7410E-02 * 2.8547E-02*nb *lumi/Nevents); 
if (run==138299) norm = (1.2409E-02 * 3.3820E-02*nb *lumi/Nevents); 
if (run==138300) norm = (9.7092E-03 * 3.8065E-02*nb *lumi/Nevents); 
if (run==138301) norm = (6.0641E-03 * 4.6638E-02*nb *lumi/Nevents); 
if (run==138302) norm = (3.8601E-02 * 1.9518E-02*nb *lumi/Nevents); 
if (run==138303) norm = (2.5383E-02 * 2.4952E-02*nb *lumi/Nevents); 
if (run==138304) norm = (1.8222E-02 * 3.0429E-02*nb *lumi/Nevents); 
if (run==138305) norm = (1.1112E-02 * 4.3283E-02*nb *lumi/Nevents); 
if (run==138306) norm = (7.7878E-03 * 5.1524E-02*nb *lumi/Nevents); 
if (run==138307) norm = (6.0404E-03 * 5.8618E-02*nb *lumi/Nevents); 
if (run==138308) norm = (3.6316E-03 * 7.3216E-02*nb *lumi/Nevents); 
if (run==138309) norm = (2.7131E-02 * 2.4965E-02*nb *lumi/Nevents); 
if (run==138310) norm = (1.8160E-02 * 3.2324E-02*nb *lumi/Nevents); 
if (run==138311) norm = (1.3069E-02 * 4.0731E-02*nb *lumi/Nevents); 
if (run==138312) norm = (7.8569E-03 * 5.4852E-02*nb *lumi/Nevents); 
if (run==138313) norm = (5.4003E-03 * 6.7445E-02*nb *lumi/Nevents); 
if (run==138314) norm = (4.0917E-03 * 7.0965E-02*nb *lumi/Nevents); 
if (run==138315) norm = (2.3262E-03 * 9.1436E-02*nb *lumi/Nevents); 
if (run==138316) norm = (1.3974E-02 * 3.6709E-02*nb *lumi/Nevents); 
if (run==138317) norm = (9.4258E-03 * 4.4888E-02*nb *lumi/Nevents); 
if (run==138318) norm = (6.7169E-03 * 5.4389E-02*nb *lumi/Nevents); 
if (run==138319) norm = (3.8298E-03 * 6.9910E-02*nb *lumi/Nevents); 
if (run==138320) norm = (2.4535E-03 * 8.4283E-02*nb *lumi/Nevents); 
if (run==138321) norm = (1.7054E-03 * 9.9621E-02*nb *lumi/Nevents); 
if (run==138322) norm = (7.6060E-04 * 1.2496E-01*nb *lumi/Nevents); 
if (run==138323) norm = (1.3779E+00 * 3.9589E-04*nb *lumi/Nevents); 
if (run==138324) norm = (2.5648E-01 * 1.4579E-03*nb *lumi/Nevents); 
if (run==138325) norm = (1.3922E-01 * 1.9737E-03*nb *lumi/Nevents); 
if (run==138326) norm = (7.2525E-02 * 2.1416E-03*nb *lumi/Nevents); 
if (run==138327) norm = (4.9410E-02 * 2.1207E-03*nb *lumi/Nevents); 
if (run==138328) norm = (3.8101E-02 * 1.9347E-03*nb *lumi/Nevents); 
if (run==138329) norm = (2.3545E-02 * 1.0862E-03*nb *lumi/Nevents); 
if (run==138330) norm = (2.5822E-01 * 1.9783E-03*nb *lumi/Nevents); 
if (run==138331) norm = (1.2216E-01 * 3.0512E-03*nb *lumi/Nevents); 
if (run==138332) norm = (7.8997E-02 * 3.7813E-03*nb *lumi/Nevents); 
if (run==138333) norm = (4.5371E-02 * 3.5733E-03*nb *lumi/Nevents); 
if (run==138334) norm = (3.1945E-02 * 3.4042E-03*nb *lumi/Nevents); 
if (run==138335) norm = (2.5032E-02 * 3.0182E-03*nb *lumi/Nevents); 
if (run==138336) norm = (1.5794E-02 * 1.6003E-03*nb *lumi/Nevents); 
if (run==138337) norm = (1.3097E-01 * 3.7728E-03*nb *lumi/Nevents); 
if (run==138338) norm = (7.5097E-02 * 5.0780E-03*nb *lumi/Nevents); 
if (run==138339) norm = (5.1653E-02 * 5.8142E-03*nb *lumi/Nevents); 
if (run==138340) norm = (3.1028E-02 * 5.9329E-03*nb *lumi/Nevents); 
if (run==138341) norm = (2.2141E-02 * 5.2429E-03*nb *lumi/Nevents); 
if (run==138342) norm = (1.7458E-02 * 4.7211E-03*nb *lumi/Nevents); 
if (run==138343) norm = (1.1086E-02 * 2.3362E-03*nb *lumi/Nevents); 
if (run==138344) norm = (5.9467E-02 * 8.2674E-03*nb *lumi/Nevents); 
if (run==138345) norm = (3.8570E-02 * 9.9065E-03*nb *lumi/Nevents); 
if (run==138346) norm = (2.7717E-02 * 1.0953E-02*nb *lumi/Nevents); 
if (run==138347) norm = (1.7097E-02 * 1.1748E-02*nb *lumi/Nevents); 
if (run==138348) norm = (1.2248E-02 * 1.2032E-02*nb *lumi/Nevents); 
if (run==138349) norm = (9.6182E-03 * 1.1479E-02*nb *lumi/Nevents); 
if (run==138350) norm = (6.0285E-03 * 6.2631E-03*nb *lumi/Nevents); 
if (run==138351) norm = (3.6429E-02 * 1.2698E-02*nb *lumi/Nevents); 
if (run==138352) norm = (2.4339E-02 * 1.5361E-02*nb *lumi/Nevents); 
if (run==138353) norm = (1.7736E-02 * 1.6695E-02*nb *lumi/Nevents); 
if (run==138354) norm = (1.0941E-02 * 1.9693E-02*nb *lumi/Nevents); 
if (run==138355) norm = (7.7355E-03 * 2.1716E-02*nb *lumi/Nevents); 
if (run==138356) norm = (5.9745E-03 * 2.3359E-02*nb *lumi/Nevents); 
if (run==138357) norm = (3.6144E-03 * 2.0726E-02*nb *lumi/Nevents); 
if (run==138358) norm = (2.5840E-02 * 1.6932E-02*nb *lumi/Nevents); 
if (run==138359) norm = (1.7544E-02 * 2.0030E-02*nb *lumi/Nevents); 
if (run==138360) norm = (1.2741E-02 * 2.2635E-02*nb *lumi/Nevents); 
if (run==138361) norm = (7.7679E-03 * 2.8826E-02*nb *lumi/Nevents); 
if (run==138362) norm = (5.3634E-03 * 3.4889E-02*nb *lumi/Nevents); 
if (run==138363) norm = (4.0620E-03 * 4.0545E-02*nb *lumi/Nevents); 
if (run==138364) norm = (2.3366E-03 * 4.7749E-02*nb *lumi/Nevents); 
if (run==138365) norm = (1.3466E-02 * 2.4701E-02*nb *lumi/Nevents); 
if (run==138366) norm = (9.1665E-03 * 3.0427E-02*nb *lumi/Nevents); 
if (run==138367) norm = (6.5826E-03 * 3.5000E-02*nb *lumi/Nevents); 
if (run==138368) norm = (3.7748E-03 * 4.8525E-02*nb *lumi/Nevents); 
if (run==138369) norm = (2.4235E-03 * 6.5467E-02*nb *lumi/Nevents); 
if (run==138370) norm = (1.6958E-03 * 8.0171E-02*nb *lumi/Nevents); 
if (run==138371) norm = (7.5905E-04 * 1.1024E-01*nb *lumi/Nevents); 
if (run==138372) norm = (1.1100E+00 * 3.1111E-04*nb *lumi/Nevents); 
if (run==138373) norm = (2.2813E-01 * 1.0489E-03*nb *lumi/Nevents); 
if (run==138374) norm = (1.3109E-01 * 1.3657E-03*nb *lumi/Nevents); 
if (run==138375) norm = (7.0294E-02 * 1.5652E-03*nb *lumi/Nevents); 
if (run==138376) norm = (4.8396E-02 * 1.6204E-03*nb *lumi/Nevents); 
if (run==138377) norm = (3.7540E-02 * 1.5269E-03*nb *lumi/Nevents); 
if (run==138378) norm = (2.3384E-02 * 9.0598E-04*nb *lumi/Nevents); 
if (run==138379) norm = (2.2018E-01 * 1.4841E-03*nb *lumi/Nevents); 
if (run==138380) norm = (1.1372E-01 * 2.1213E-03*nb *lumi/Nevents); 
if (run==138381) norm = (7.5371E-02 * 2.3756E-03*nb *lumi/Nevents); 
if (run==138382) norm = (4.4200E-02 * 2.3874E-03*nb *lumi/Nevents); 
if (run==138383) norm = (3.1393E-02 * 2.3421E-03*nb *lumi/Nevents); 
if (run==138384) norm = (2.4712E-02 * 2.3353E-03*nb *lumi/Nevents); 
if (run==138385) norm = (1.5692E-02 * 1.3721E-03*nb *lumi/Nevents); 
if (run==138386) norm = (1.1789E-01 * 2.6616E-03*nb *lumi/Nevents); 
if (run==138387) norm = (7.1030E-02 * 3.3709E-03*nb *lumi/Nevents); 
if (run==138388) norm = (4.9608E-02 * 3.5756E-03*nb *lumi/Nevents); 
if (run==138389) norm = (3.0306E-02 * 3.4748E-03*nb *lumi/Nevents); 
if (run==138390) norm = (2.1813E-02 * 3.1787E-03*nb *lumi/Nevents); 
if (run==138391) norm = (1.7253E-02 * 3.1029E-03*nb *lumi/Nevents); 
if (run==138392) norm = (1.1016E-02 * 1.8836E-03*nb *lumi/Nevents); 
if (run==138393) norm = (5.5663E-02 * 5.3725E-03*nb *lumi/Nevents); 
if (run==138394) norm = (3.6825E-02 * 6.2049E-03*nb *lumi/Nevents); 
if (run==138395) norm = (2.6769E-02 * 6.5461E-03*nb *lumi/Nevents); 
if (run==138396) norm = (1.6767E-02 * 6.5702E-03*nb *lumi/Nevents); 
if (run==138397) norm = (1.2078E-02 * 5.9740E-03*nb *lumi/Nevents); 
if (run==138398) norm = (9.5315E-03 * 4.9670E-03*nb *lumi/Nevents); 
if (run==138399) norm = (5.9951E-03 * 3.0928E-03*nb *lumi/Nevents); 
if (run==138400) norm = (3.4436E-02 * 8.4015E-03*nb *lumi/Nevents); 
if (run==138401) norm = (2.3438E-02 * 9.5772E-03*nb *lumi/Nevents); 
if (run==138402) norm = (1.7203E-02 * 1.0150E-02*nb *lumi/Nevents); 
if (run==138403) norm = (1.0714E-02 * 1.0210E-02*nb *lumi/Nevents); 
if (run==138404) norm = (7.6257E-03 * 9.4436E-03*nb *lumi/Nevents); 
if (run==138405) norm = (5.9175E-03 * 8.3252E-03*nb *lumi/Nevents); 
if (run==138406) norm = (3.5922E-03 * 5.0144E-03*nb *lumi/Nevents); 
if (run==138407) norm = (2.4558E-02 * 1.1308E-02*nb *lumi/Nevents); 
if (run==138408) norm = (1.6867E-02 * 1.2516E-02*nb *lumi/Nevents); 
if (run==138409) norm = (1.2367E-02 * 1.3521E-02*nb *lumi/Nevents); 
if (run==138410) norm = (7.5798E-03 * 1.3843E-02*nb *lumi/Nevents); 
if (run==138411) norm = (5.2911E-03 * 1.3676E-02*nb *lumi/Nevents); 
if (run==138412) norm = (4.0105E-03 * 1.2167E-02*nb *lumi/Nevents); 
if (run==138413) norm = (2.3162E-03 * 7.2668E-03*nb *lumi/Nevents); 
if (run==138414) norm = (1.2912E-02 * 1.5928E-02*nb *lumi/Nevents); 
if (run==138415) norm = (8.8653E-03 * 1.7476E-02*nb *lumi/Nevents); 
if (run==138416) norm = (6.3933E-03 * 1.9981E-02*nb *lumi/Nevents); 
if (run==138417) norm = (3.7016E-03 * 2.3480E-02*nb *lumi/Nevents); 
if (run==138418) norm = (2.3911E-03 * 2.6721E-02*nb *lumi/Nevents); 
if (run==138419) norm = (1.6758E-03 * 2.9238E-02*nb *lumi/Nevents); 
if (run==138420) norm = (7.5211E-04 * 2.6889E-02*nb *lumi/Nevents); 


 if (norm == -1.) {
   cout << "WARNING run "<<run<<" not in the list, returning 1"<<endl;
   norm = 1;
 }
 
 double norm1 = norm/lumi;
 //cout << "if (run=="<<run<<") norm = "<<norm1<<";"<<endl; 
 return norm;
}
