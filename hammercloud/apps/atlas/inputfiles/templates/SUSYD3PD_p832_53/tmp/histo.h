void fillHisto(){

//get histos from files

#ifdef DATA
#ifdef ELECTRON
#ifdef H1D
  h1_electronStream  = (TH1I*)file_electronStream->Get(histo_string);   
#endif
#ifdef H2D
  h2_electronStream = (TH2F*)file_electronStream ->Get(histo_string);   
  h1_electronStream = h2_electronStream->ProjectionY("h1_electronStream", binmin, binmax, "e");
#endif
#endif  // ELECTRON

#ifdef MUON
#ifdef H1D
  h1_muonStream  = (TH1I*)file_muonStream->Get(histo_string);   
#endif
#ifdef H2D
  h2_muonStream = (TH2F*)file_muonStream ->Get(histo_string);   
  h1_muonStream = h2_muonStream->ProjectionY("h1_muonStream", binmin, binmax, "e");
#endif
#endif // MUON
#endif // DATA


//  -- Open files  & get histograms
#ifdef MC                                           //MC

#ifdef SU4                                         //SU4
#ifdef H1D
  h1_106484  = (TH1I*)file_106484->Get(histo_string) ; 
#endif
#ifdef H2D
  h2_106484 = (TH2F*)file_106484 ->Get(histo_string);     
  h1_106484 = h2_106484->ProjectionY("h1_106484", binmin, binmax, "e");
#endif
#endif //SU4

#ifdef MSUGRA                                    //MSUGRA

#ifdef H1D

h1_123290  = (TH1I*)file_123290->Get(histo_string) ;
h1_123291  = (TH1I*)file_123291->Get(histo_string) ;
h1_123292  = (TH1I*)file_123292->Get(histo_string) ;
h1_123293  = (TH1I*)file_123293->Get(histo_string) ;
h1_123294  = (TH1I*)file_123294->Get(histo_string) ;
h1_123295  = (TH1I*)file_123295->Get(histo_string) ;
h1_123296  = (TH1I*)file_123296->Get(histo_string) ;
h1_123297  = (TH1I*)file_123297->Get(histo_string) ;
h1_123298  = (TH1I*)file_123298->Get(histo_string) ;
h1_123299  = (TH1I*)file_123299->Get(histo_string) ;
h1_123300  = (TH1I*)file_123300->Get(histo_string) ;
h1_123301  = (TH1I*)file_123301->Get(histo_string) ;
h1_123302  = (TH1I*)file_123302->Get(histo_string) ;
h1_123303  = (TH1I*)file_123303->Get(histo_string) ;
h1_123304  = (TH1I*)file_123304->Get(histo_string) ;
h1_123305  = (TH1I*)file_123305->Get(histo_string) ;
h1_123306  = (TH1I*)file_123306->Get(histo_string) ;
h1_123307  = (TH1I*)file_123307->Get(histo_string) ;
h1_123308  = (TH1I*)file_123308->Get(histo_string) ;
h1_123309  = (TH1I*)file_123309->Get(histo_string) ;
h1_123310  = (TH1I*)file_123310->Get(histo_string) ;
h1_123311  = (TH1I*)file_123311->Get(histo_string) ;
h1_123312  = (TH1I*)file_123312->Get(histo_string) ;
h1_123313  = (TH1I*)file_123313->Get(histo_string) ;
h1_123314  = (TH1I*)file_123314->Get(histo_string) ;
h1_123315  = (TH1I*)file_123315->Get(histo_string) ;
h1_123316  = (TH1I*)file_123316->Get(histo_string) ;
h1_123317  = (TH1I*)file_123317->Get(histo_string) ;
h1_123320  = (TH1I*)file_123320->Get(histo_string) ;
h1_123321  = (TH1I*)file_123321->Get(histo_string) ;
h1_123322  = (TH1I*)file_123322->Get(histo_string) ;
h1_123323  = (TH1I*)file_123323->Get(histo_string) ;
h1_123324  = (TH1I*)file_123324->Get(histo_string) ;
h1_123325  = (TH1I*)file_123325->Get(histo_string) ;
h1_123326  = (TH1I*)file_123326->Get(histo_string) ;
h1_123327  = (TH1I*)file_123327->Get(histo_string) ;
h1_123328  = (TH1I*)file_123328->Get(histo_string) ;
h1_123329  = (TH1I*)file_123329->Get(histo_string) ;
h1_123330  = (TH1I*)file_123330->Get(histo_string) ;
h1_123331  = (TH1I*)file_123331->Get(histo_string) ;
h1_123332  = (TH1I*)file_123332->Get(histo_string) ;
h1_123333  = (TH1I*)file_123333->Get(histo_string) ;
h1_123334  = (TH1I*)file_123334->Get(histo_string) ;
h1_123335  = (TH1I*)file_123335->Get(histo_string) ;
h1_123336  = (TH1I*)file_123336->Get(histo_string) ;
h1_123337  = (TH1I*)file_123337->Get(histo_string) ;
h1_123338  = (TH1I*)file_123338->Get(histo_string) ;
h1_123339  = (TH1I*)file_123339->Get(histo_string) ;
h1_123340  = (TH1I*)file_123340->Get(histo_string) ;
h1_123341  = (TH1I*)file_123341->Get(histo_string) ;
h1_123342  = (TH1I*)file_123342->Get(histo_string) ;
h1_123343  = (TH1I*)file_123343->Get(histo_string) ;
h1_123344  = (TH1I*)file_123344->Get(histo_string) ;
h1_123345  = (TH1I*)file_123345->Get(histo_string) ;
h1_123346  = (TH1I*)file_123346->Get(histo_string) ;
h1_123347  = (TH1I*)file_123347->Get(histo_string) ;
h1_123348  = (TH1I*)file_123348->Get(histo_string) ;
h1_123349  = (TH1I*)file_123349->Get(histo_string) ;
h1_123350  = (TH1I*)file_123350->Get(histo_string) ;
h1_123351  = (TH1I*)file_123351->Get(histo_string) ;
h1_123352  = (TH1I*)file_123352->Get(histo_string) ;
h1_123353  = (TH1I*)file_123353->Get(histo_string) ;
h1_123354  = (TH1I*)file_123354->Get(histo_string) ;
h1_123355  = (TH1I*)file_123355->Get(histo_string) ;
h1_123356  = (TH1I*)file_123356->Get(histo_string) ;
h1_123357  = (TH1I*)file_123357->Get(histo_string) ;
h1_123358  = (TH1I*)file_123358->Get(histo_string) ;
h1_123359  = (TH1I*)file_123359->Get(histo_string) ;
h1_123360  = (TH1I*)file_123360->Get(histo_string) ;
h1_123361  = (TH1I*)file_123361->Get(histo_string) ;
h1_123362  = (TH1I*)file_123362->Get(histo_string) ;
h1_123363  = (TH1I*)file_123363->Get(histo_string) ;
h1_123364  = (TH1I*)file_123364->Get(histo_string) ;
h1_123365  = (TH1I*)file_123365->Get(histo_string) ;
h1_123366  = (TH1I*)file_123366->Get(histo_string) ;
h1_123367  = (TH1I*)file_123367->Get(histo_string) ;
h1_123368  = (TH1I*)file_123368->Get(histo_string) ;
h1_123369  = (TH1I*)file_123369->Get(histo_string) ;
h1_123370  = (TH1I*)file_123370->Get(histo_string) ;
h1_123371  = (TH1I*)file_123371->Get(histo_string) ;
h1_123372  = (TH1I*)file_123372->Get(histo_string) ;
h1_123373  = (TH1I*)file_123373->Get(histo_string) ;
h1_123374  = (TH1I*)file_123374->Get(histo_string) ;
h1_123375  = (TH1I*)file_123375->Get(histo_string) ;
h1_123376  = (TH1I*)file_123376->Get(histo_string) ;
h1_123377  = (TH1I*)file_123377->Get(histo_string) ;
h1_123378  = (TH1I*)file_123378->Get(histo_string) ;
h1_123379  = (TH1I*)file_123379->Get(histo_string) ;
h1_123380  = (TH1I*)file_123380->Get(histo_string) ;
h1_123381  = (TH1I*)file_123381->Get(histo_string) ;
h1_123383  = (TH1I*)file_123383->Get(histo_string) ;
h1_123384  = (TH1I*)file_123384->Get(histo_string) ;
h1_123385  = (TH1I*)file_123385->Get(histo_string) ;
h1_123386  = (TH1I*)file_123386->Get(histo_string) ;
h1_123387  = (TH1I*)file_123387->Get(histo_string) ;
h1_123388  = (TH1I*)file_123388->Get(histo_string) ;
h1_123389  = (TH1I*)file_123389->Get(histo_string) ;
h1_123390  = (TH1I*)file_123390->Get(histo_string) ;
h1_123391  = (TH1I*)file_123391->Get(histo_string) ;
h1_123392  = (TH1I*)file_123392->Get(histo_string) ;
h1_123393  = (TH1I*)file_123393->Get(histo_string) ;
h1_123394  = (TH1I*)file_123394->Get(histo_string) ;
h1_123396  = (TH1I*)file_123396->Get(histo_string) ;
h1_123397  = (TH1I*)file_123397->Get(histo_string) ;
h1_123398  = (TH1I*)file_123398->Get(histo_string) ;
h1_123399  = (TH1I*)file_123399->Get(histo_string) ;
h1_123400  = (TH1I*)file_123400->Get(histo_string) ;
h1_123401  = (TH1I*)file_123401->Get(histo_string) ;
h1_123402  = (TH1I*)file_123402->Get(histo_string) ;
h1_123403  = (TH1I*)file_123403->Get(histo_string) ;
h1_123404  = (TH1I*)file_123404->Get(histo_string) ;
h1_123405  = (TH1I*)file_123405->Get(histo_string) ;
h1_123406  = (TH1I*)file_123406->Get(histo_string) ;
h1_123407  = (TH1I*)file_123407->Get(histo_string) ;
h1_123408  = (TH1I*)file_123408->Get(histo_string) ;
h1_123409  = (TH1I*)file_123409->Get(histo_string) ;
h1_123410  = (TH1I*)file_123410->Get(histo_string) ;
h1_123411  = (TH1I*)file_123411->Get(histo_string) ;
h1_123412  = (TH1I*)file_123412->Get(histo_string) ;
h1_123413  = (TH1I*)file_123413->Get(histo_string) ;
h1_123414  = (TH1I*)file_123414->Get(histo_string) ;
h1_123415  = (TH1I*)file_123415->Get(histo_string) ;
h1_123416  = (TH1I*)file_123416->Get(histo_string) ;
h1_123417  = (TH1I*)file_123417->Get(histo_string) ;
h1_123418  = (TH1I*)file_123418->Get(histo_string) ;
h1_123419  = (TH1I*)file_123419->Get(histo_string) ;
h1_123420  = (TH1I*)file_123420->Get(histo_string) ;
h1_123422  = (TH1I*)file_123422->Get(histo_string) ;
h1_123423  = (TH1I*)file_123423->Get(histo_string) ;
h1_123424  = (TH1I*)file_123424->Get(histo_string) ;
h1_123425  = (TH1I*)file_123425->Get(histo_string) ;
h1_123426  = (TH1I*)file_123426->Get(histo_string) ;
h1_123427  = (TH1I*)file_123427->Get(histo_string) ;
h1_123428  = (TH1I*)file_123428->Get(histo_string) ;
h1_123430  = (TH1I*)file_123430->Get(histo_string) ;
h1_123431  = (TH1I*)file_123431->Get(histo_string) ;
h1_123432  = (TH1I*)file_123432->Get(histo_string) ;
h1_123433  = (TH1I*)file_123433->Get(histo_string) ;
h1_123434  = (TH1I*)file_123434->Get(histo_string) ;
h1_123435  = (TH1I*)file_123435->Get(histo_string) ;
h1_123436  = (TH1I*)file_123436->Get(histo_string) ;
h1_123437  = (TH1I*)file_123437->Get(histo_string) ;
h1_123438  = (TH1I*)file_123438->Get(histo_string) ;
h1_123439  = (TH1I*)file_123439->Get(histo_string) ;
h1_123440  = (TH1I*)file_123440->Get(histo_string) ;
h1_123441  = (TH1I*)file_123441->Get(histo_string) ;
h1_123442  = (TH1I*)file_123442->Get(histo_string) ;
h1_123443  = (TH1I*)file_123443->Get(histo_string) ;
h1_123444  = (TH1I*)file_123444->Get(histo_string) ;
h1_123445  = (TH1I*)file_123445->Get(histo_string) ;
h1_123447  = (TH1I*)file_123447->Get(histo_string) ;
h1_123448  = (TH1I*)file_123448->Get(histo_string) ;
h1_123449  = (TH1I*)file_123449->Get(histo_string) ;
h1_123450  = (TH1I*)file_123450->Get(histo_string) ;
h1_123451  = (TH1I*)file_123451->Get(histo_string) ;
h1_123452  = (TH1I*)file_123452->Get(histo_string) ;
h1_123453  = (TH1I*)file_123453->Get(histo_string) ;
h1_123454  = (TH1I*)file_123454->Get(histo_string) ;
h1_123455  = (TH1I*)file_123455->Get(histo_string) ;
h1_123456  = (TH1I*)file_123456->Get(histo_string) ;
h1_123457  = (TH1I*)file_123457->Get(histo_string) ;
h1_123458  = (TH1I*)file_123458->Get(histo_string) ;
h1_123460  = (TH1I*)file_123460->Get(histo_string) ;
h1_123461  = (TH1I*)file_123461->Get(histo_string) ;
h1_123462  = (TH1I*)file_123462->Get(histo_string) ;
h1_123463  = (TH1I*)file_123463->Get(histo_string) ;
h1_123464  = (TH1I*)file_123464->Get(histo_string) ;
h1_123465  = (TH1I*)file_123465->Get(histo_string) ;
h1_123466  = (TH1I*)file_123466->Get(histo_string) ;
h1_123467  = (TH1I*)file_123467->Get(histo_string) ;
h1_123468  = (TH1I*)file_123468->Get(histo_string) ;
h1_123469  = (TH1I*)file_123469->Get(histo_string) ;
h1_123470  = (TH1I*)file_123470->Get(histo_string) ;
h1_123471  = (TH1I*)file_123471->Get(histo_string) ;
h1_123472  = (TH1I*)file_123472->Get(histo_string) ;
h1_123473  = (TH1I*)file_123473->Get(histo_string) ;
h1_123474  = (TH1I*)file_123474->Get(histo_string) ;
h1_123475  = (TH1I*)file_123475->Get(histo_string) ;
h1_123476  = (TH1I*)file_123476->Get(histo_string) ;
h1_123477  = (TH1I*)file_123477->Get(histo_string) ;
h1_123478  = (TH1I*)file_123478->Get(histo_string) ;
h1_123479  = (TH1I*)file_123479->Get(histo_string) ;
h1_123480  = (TH1I*)file_123480->Get(histo_string) ;
h1_123481  = (TH1I*)file_123481->Get(histo_string) ;
h1_123482  = (TH1I*)file_123482->Get(histo_string) ;
h1_123483  = (TH1I*)file_123483->Get(histo_string) ;
h1_123484  = (TH1I*)file_123484->Get(histo_string) ;
h1_123485  = (TH1I*)file_123485->Get(histo_string) ;
h1_123486  = (TH1I*)file_123486->Get(histo_string) ;
h1_123487  = (TH1I*)file_123487->Get(histo_string) ;
h1_123488  = (TH1I*)file_123488->Get(histo_string) ;
h1_123489  = (TH1I*)file_123489->Get(histo_string) ;
h1_123490  = (TH1I*)file_123490->Get(histo_string) ;
h1_123491  = (TH1I*)file_123491->Get(histo_string) ;
h1_123492  = (TH1I*)file_123492->Get(histo_string) ;
h1_123493  = (TH1I*)file_123493->Get(histo_string) ;
h1_123494  = (TH1I*)file_123494->Get(histo_string) ;
h1_123495  = (TH1I*)file_123495->Get(histo_string) ;
h1_123496  = (TH1I*)file_123496->Get(histo_string) ;
h1_123497  = (TH1I*)file_123497->Get(histo_string) ;
h1_123498  = (TH1I*)file_123498->Get(histo_string) ;
h1_123499  = (TH1I*)file_123499->Get(histo_string) ;
h1_123501  = (TH1I*)file_123501->Get(histo_string) ;
h1_123502  = (TH1I*)file_123502->Get(histo_string) ;
h1_123503  = (TH1I*)file_123503->Get(histo_string) ;
h1_123504  = (TH1I*)file_123504->Get(histo_string) ;
h1_123505  = (TH1I*)file_123505->Get(histo_string) ;
h1_123506  = (TH1I*)file_123506->Get(histo_string) ;
h1_123507  = (TH1I*)file_123507->Get(histo_string) ;
h1_123508  = (TH1I*)file_123508->Get(histo_string) ;
h1_123509  = (TH1I*)file_123509->Get(histo_string) ;
h1_123510  = (TH1I*)file_123510->Get(histo_string) ;
h1_123511  = (TH1I*)file_123511->Get(histo_string) ;
h1_123512  = (TH1I*)file_123512->Get(histo_string) ;
h1_123513  = (TH1I*)file_123513->Get(histo_string) ;
h1_123514  = (TH1I*)file_123514->Get(histo_string) ;
h1_123516  = (TH1I*)file_123516->Get(histo_string) ;
h1_123517  = (TH1I*)file_123517->Get(histo_string) ;
h1_123518  = (TH1I*)file_123518->Get(histo_string) ;
h1_123519  = (TH1I*)file_123519->Get(histo_string) ;
h1_123520  = (TH1I*)file_123520->Get(histo_string) ;
h1_123521  = (TH1I*)file_123521->Get(histo_string) ;
h1_123522  = (TH1I*)file_123522->Get(histo_string) ;
h1_123523  = (TH1I*)file_123523->Get(histo_string) ;
h1_123524  = (TH1I*)file_123524->Get(histo_string) ;
h1_123526  = (TH1I*)file_123526->Get(histo_string) ;
h1_123527  = (TH1I*)file_123527->Get(histo_string) ;
h1_123528  = (TH1I*)file_123528->Get(histo_string) ;
h1_123529  = (TH1I*)file_123529->Get(histo_string) ;
h1_123530  = (TH1I*)file_123530->Get(histo_string) ;
h1_123531  = (TH1I*)file_123531->Get(histo_string) ;
h1_123533  = (TH1I*)file_123533->Get(histo_string) ;
h1_123534  = (TH1I*)file_123534->Get(histo_string) ;
h1_123535  = (TH1I*)file_123535->Get(histo_string) ;
h1_123536  = (TH1I*)file_123536->Get(histo_string) ;
h1_123537  = (TH1I*)file_123537->Get(histo_string) ;
h1_123538  = (TH1I*)file_123538->Get(histo_string) ;
h1_123539  = (TH1I*)file_123539->Get(histo_string) ;
h1_123540  = (TH1I*)file_123540->Get(histo_string) ;
h1_123541  = (TH1I*)file_123541->Get(histo_string) ;
h1_123542  = (TH1I*)file_123542->Get(histo_string) ;
h1_123543  = (TH1I*)file_123543->Get(histo_string) ;
h1_123544  = (TH1I*)file_123544->Get(histo_string) ;
h1_123545  = (TH1I*)file_123545->Get(histo_string) ;
h1_123546  = (TH1I*)file_123546->Get(histo_string) ;
h1_123547  = (TH1I*)file_123547->Get(histo_string) ;
h1_123548  = (TH1I*)file_123548->Get(histo_string) ;
h1_123549  = (TH1I*)file_123549->Get(histo_string) ;
h1_123550  = (TH1I*)file_123550->Get(histo_string) ;
h1_123551  = (TH1I*)file_123551->Get(histo_string) ;
h1_123552  = (TH1I*)file_123552->Get(histo_string) ;
h1_123553  = (TH1I*)file_123553->Get(histo_string) ;
h1_123554  = (TH1I*)file_123554->Get(histo_string) ;
h1_123555  = (TH1I*)file_123555->Get(histo_string) ;
h1_123556  = (TH1I*)file_123556->Get(histo_string) ;
h1_123557  = (TH1I*)file_123557->Get(histo_string) ;
h1_123558  = (TH1I*)file_123558->Get(histo_string) ;
h1_123559  = (TH1I*)file_123559->Get(histo_string) ;
h1_123560  = (TH1I*)file_123560->Get(histo_string) ;
h1_123561  = (TH1I*)file_123561->Get(histo_string) ;
h1_123562  = (TH1I*)file_123562->Get(histo_string) ;
h1_123563  = (TH1I*)file_123563->Get(histo_string) ;
h1_123564  = (TH1I*)file_123564->Get(histo_string) ;
h1_123565  = (TH1I*)file_123565->Get(histo_string) ;
h1_123566  = (TH1I*)file_123566->Get(histo_string) ;
h1_123567  = (TH1I*)file_123567->Get(histo_string) ;
h1_123568  = (TH1I*)file_123568->Get(histo_string) ;
h1_123569  = (TH1I*)file_123569->Get(histo_string) ;
h1_123570  = (TH1I*)file_123570->Get(histo_string) ;
h1_123571  = (TH1I*)file_123571->Get(histo_string) ;
h1_123572  = (TH1I*)file_123572->Get(histo_string) ;
h1_123573  = (TH1I*)file_123573->Get(histo_string) ;
h1_123574  = (TH1I*)file_123574->Get(histo_string) ;
h1_123575  = (TH1I*)file_123575->Get(histo_string) ;
h1_123576  = (TH1I*)file_123576->Get(histo_string) ;
h1_123577  = (TH1I*)file_123577->Get(histo_string) ;
h1_123578  = (TH1I*)file_123578->Get(histo_string) ;
h1_123579  = (TH1I*)file_123579->Get(histo_string) ;
h1_123580  = (TH1I*)file_123580->Get(histo_string) ;
h1_123581  = (TH1I*)file_123581->Get(histo_string) ;
h1_123582  = (TH1I*)file_123582->Get(histo_string) ;
h1_123583  = (TH1I*)file_123583->Get(histo_string) ;
h1_123584  = (TH1I*)file_123584->Get(histo_string) ;
h1_123585  = (TH1I*)file_123585->Get(histo_string) ;
h1_123586  = (TH1I*)file_123586->Get(histo_string) ;
h1_123587  = (TH1I*)file_123587->Get(histo_string) ;
h1_123588  = (TH1I*)file_123588->Get(histo_string) ;
h1_123589  = (TH1I*)file_123589->Get(histo_string) ;
h1_123590  = (TH1I*)file_123590->Get(histo_string) ;
h1_123591  = (TH1I*)file_123591->Get(histo_string) ;
h1_123592  = (TH1I*)file_123592->Get(histo_string) ;
h1_123593  = (TH1I*)file_123593->Get(histo_string) ;
h1_123594  = (TH1I*)file_123594->Get(histo_string) ;
h1_123595  = (TH1I*)file_123595->Get(histo_string) ;
h1_123597  = (TH1I*)file_123597->Get(histo_string) ;
h1_123598  = (TH1I*)file_123598->Get(histo_string) ;
h1_123599  = (TH1I*)file_123599->Get(histo_string) ;
h1_123600  = (TH1I*)file_123600->Get(histo_string) ;
h1_123601  = (TH1I*)file_123601->Get(histo_string) ;
h1_123602  = (TH1I*)file_123602->Get(histo_string) ;
h1_123603  = (TH1I*)file_123603->Get(histo_string) ;
h1_123604  = (TH1I*)file_123604->Get(histo_string) ;
h1_123605  = (TH1I*)file_123605->Get(histo_string) ;
h1_123606  = (TH1I*)file_123606->Get(histo_string) ;
h1_123607  = (TH1I*)file_123607->Get(histo_string) ;
h1_123609  = (TH1I*)file_123609->Get(histo_string) ;
h1_123611  = (TH1I*)file_123611->Get(histo_string) ;
h1_123612  = (TH1I*)file_123612->Get(histo_string) ;
h1_123613  = (TH1I*)file_123613->Get(histo_string) ;
h1_123614  = (TH1I*)file_123614->Get(histo_string) ;
h1_123615  = (TH1I*)file_123615->Get(histo_string) ;
h1_123616  = (TH1I*)file_123616->Get(histo_string) ;
h1_123617  = (TH1I*)file_123617->Get(histo_string) ;
h1_123618  = (TH1I*)file_123618->Get(histo_string) ;
h1_123619  = (TH1I*)file_123619->Get(histo_string) ;
h1_123620  = (TH1I*)file_123620->Get(histo_string) ;
h1_123621  = (TH1I*)file_123621->Get(histo_string) ;
h1_123622  = (TH1I*)file_123622->Get(histo_string) ;
h1_123623  = (TH1I*)file_123623->Get(histo_string) ;
h1_123624  = (TH1I*)file_123624->Get(histo_string) ;
h1_123625  = (TH1I*)file_123625->Get(histo_string) ;
h1_123626  = (TH1I*)file_123626->Get(histo_string) ;
h1_123628  = (TH1I*)file_123628->Get(histo_string) ;
h1_123629  = (TH1I*)file_123629->Get(histo_string) ;
h1_123630  = (TH1I*)file_123630->Get(histo_string) ;
h1_123631  = (TH1I*)file_123631->Get(histo_string) ;
h1_123632  = (TH1I*)file_123632->Get(histo_string) ;
h1_123633  = (TH1I*)file_123633->Get(histo_string) ;
h1_123634  = (TH1I*)file_123634->Get(histo_string) ;
h1_123635  = (TH1I*)file_123635->Get(histo_string) ;
h1_123636  = (TH1I*)file_123636->Get(histo_string) ;
h1_123637  = (TH1I*)file_123637->Get(histo_string) ;
h1_123638  = (TH1I*)file_123638->Get(histo_string) ;
h1_123640  = (TH1I*)file_123640->Get(histo_string) ;
h1_123641  = (TH1I*)file_123641->Get(histo_string) ;
h1_123642  = (TH1I*)file_123642->Get(histo_string) ;
h1_123643  = (TH1I*)file_123643->Get(histo_string) ;
h1_123644  = (TH1I*)file_123644->Get(histo_string) ;
h1_123645  = (TH1I*)file_123645->Get(histo_string) ;
h1_123646  = (TH1I*)file_123646->Get(histo_string) ;
h1_123647  = (TH1I*)file_123647->Get(histo_string) ;
h1_123648  = (TH1I*)file_123648->Get(histo_string) ;
h1_123649  = (TH1I*)file_123649->Get(histo_string) ;
h1_123650  = (TH1I*)file_123650->Get(histo_string) ;
h1_123651  = (TH1I*)file_123651->Get(histo_string) ;
h1_123652  = (TH1I*)file_123652->Get(histo_string) ;
h1_123653  = (TH1I*)file_123653->Get(histo_string) ;
h1_123654  = (TH1I*)file_123654->Get(histo_string) ;
h1_123655  = (TH1I*)file_123655->Get(histo_string) ;
h1_123656  = (TH1I*)file_123656->Get(histo_string) ;
h1_123657  = (TH1I*)file_123657->Get(histo_string) ;
h1_123658  = (TH1I*)file_123658->Get(histo_string) ;
h1_123659  = (TH1I*)file_123659->Get(histo_string) ;
h1_123660  = (TH1I*)file_123660->Get(histo_string) ;
h1_123661  = (TH1I*)file_123661->Get(histo_string) ;
h1_123662  = (TH1I*)file_123662->Get(histo_string) ;
h1_123663  = (TH1I*)file_123663->Get(histo_string) ;
h1_123664  = (TH1I*)file_123664->Get(histo_string) ;
h1_123665  = (TH1I*)file_123665->Get(histo_string) ;
h1_123666  = (TH1I*)file_123666->Get(histo_string) ;
h1_123667  = (TH1I*)file_123667->Get(histo_string) ;
h1_123668  = (TH1I*)file_123668->Get(histo_string) ;
h1_123669  = (TH1I*)file_123669->Get(histo_string) ;
h1_123670  = (TH1I*)file_123670->Get(histo_string) ;
h1_123671  = (TH1I*)file_123671->Get(histo_string) ;
h1_123672  = (TH1I*)file_123672->Get(histo_string) ;
h1_123673  = (TH1I*)file_123673->Get(histo_string) ;
h1_123674  = (TH1I*)file_123674->Get(histo_string) ;
h1_123675  = (TH1I*)file_123675->Get(histo_string) ;
h1_123676  = (TH1I*)file_123676->Get(histo_string) ;
h1_123677  = (TH1I*)file_123677->Get(histo_string) ;
h1_123678  = (TH1I*)file_123678->Get(histo_string) ;
h1_123679  = (TH1I*)file_123679->Get(histo_string) ;
h1_123680  = (TH1I*)file_123680->Get(histo_string) ;
h1_123682  = (TH1I*)file_123682->Get(histo_string) ;
h1_123683  = (TH1I*)file_123683->Get(histo_string) ;
h1_123684  = (TH1I*)file_123684->Get(histo_string) ;
h1_123686  = (TH1I*)file_123686->Get(histo_string) ;
h1_123687  = (TH1I*)file_123687->Get(histo_string) ;
h1_123688  = (TH1I*)file_123688->Get(histo_string) ;
h1_123689  = (TH1I*)file_123689->Get(histo_string) ;
h1_123690  = (TH1I*)file_123690->Get(histo_string) ;


#endif
#ifdef H2D
h2_123290  = (TH2F*)file_123290->Get(histo_string) ;
h2_123291  = (TH2F*)file_123291->Get(histo_string) ;
h2_123292  = (TH2F*)file_123292->Get(histo_string) ;
h2_123293  = (TH2F*)file_123293->Get(histo_string) ;
h2_123294  = (TH2F*)file_123294->Get(histo_string) ;
h2_123295  = (TH2F*)file_123295->Get(histo_string) ;
h2_123296  = (TH2F*)file_123296->Get(histo_string) ;
h2_123297  = (TH2F*)file_123297->Get(histo_string) ;
h2_123298  = (TH2F*)file_123298->Get(histo_string) ;
h2_123299  = (TH2F*)file_123299->Get(histo_string) ;
h2_123300  = (TH2F*)file_123300->Get(histo_string) ;
h2_123301  = (TH2F*)file_123301->Get(histo_string) ;
h2_123302  = (TH2F*)file_123302->Get(histo_string) ;
h2_123303  = (TH2F*)file_123303->Get(histo_string) ;
h2_123304  = (TH2F*)file_123304->Get(histo_string) ;
h2_123305  = (TH2F*)file_123305->Get(histo_string) ;
h2_123306  = (TH2F*)file_123306->Get(histo_string) ;
h2_123307  = (TH2F*)file_123307->Get(histo_string) ;
h2_123308  = (TH2F*)file_123308->Get(histo_string) ;
h2_123309  = (TH2F*)file_123309->Get(histo_string) ;
h2_123310  = (TH2F*)file_123310->Get(histo_string) ;
h2_123311  = (TH2F*)file_123311->Get(histo_string) ;
h2_123312  = (TH2F*)file_123312->Get(histo_string) ;
h2_123313  = (TH2F*)file_123313->Get(histo_string) ;
h2_123314  = (TH2F*)file_123314->Get(histo_string) ;
h2_123315  = (TH2F*)file_123315->Get(histo_string) ;
h2_123316  = (TH2F*)file_123316->Get(histo_string) ;
h2_123317  = (TH2F*)file_123317->Get(histo_string) ;
h2_123320  = (TH2F*)file_123320->Get(histo_string) ;
h2_123321  = (TH2F*)file_123321->Get(histo_string) ;
h2_123322  = (TH2F*)file_123322->Get(histo_string) ;
h2_123323  = (TH2F*)file_123323->Get(histo_string) ;
h2_123324  = (TH2F*)file_123324->Get(histo_string) ;
h2_123325  = (TH2F*)file_123325->Get(histo_string) ;
h2_123326  = (TH2F*)file_123326->Get(histo_string) ;
h2_123327  = (TH2F*)file_123327->Get(histo_string) ;
h2_123328  = (TH2F*)file_123328->Get(histo_string) ;
h2_123329  = (TH2F*)file_123329->Get(histo_string) ;
h2_123330  = (TH2F*)file_123330->Get(histo_string) ;
h2_123331  = (TH2F*)file_123331->Get(histo_string) ;
h2_123332  = (TH2F*)file_123332->Get(histo_string) ;
h2_123333  = (TH2F*)file_123333->Get(histo_string) ;
h2_123334  = (TH2F*)file_123334->Get(histo_string) ;
h2_123335  = (TH2F*)file_123335->Get(histo_string) ;
h2_123336  = (TH2F*)file_123336->Get(histo_string) ;
h2_123337  = (TH2F*)file_123337->Get(histo_string) ;
h2_123338  = (TH2F*)file_123338->Get(histo_string) ;
h2_123339  = (TH2F*)file_123339->Get(histo_string) ;
h2_123340  = (TH2F*)file_123340->Get(histo_string) ;
h2_123341  = (TH2F*)file_123341->Get(histo_string) ;
h2_123342  = (TH2F*)file_123342->Get(histo_string) ;
h2_123343  = (TH2F*)file_123343->Get(histo_string) ;
h2_123344  = (TH2F*)file_123344->Get(histo_string) ;
h2_123345  = (TH2F*)file_123345->Get(histo_string) ;
h2_123346  = (TH2F*)file_123346->Get(histo_string) ;
h2_123347  = (TH2F*)file_123347->Get(histo_string) ;
h2_123348  = (TH2F*)file_123348->Get(histo_string) ;
h2_123349  = (TH2F*)file_123349->Get(histo_string) ;
h2_123350  = (TH2F*)file_123350->Get(histo_string) ;
h2_123351  = (TH2F*)file_123351->Get(histo_string) ;
h2_123352  = (TH2F*)file_123352->Get(histo_string) ;
h2_123353  = (TH2F*)file_123353->Get(histo_string) ;
h2_123354  = (TH2F*)file_123354->Get(histo_string) ;
h2_123355  = (TH2F*)file_123355->Get(histo_string) ;
h2_123356  = (TH2F*)file_123356->Get(histo_string) ;
h2_123357  = (TH2F*)file_123357->Get(histo_string) ;
h2_123358  = (TH2F*)file_123358->Get(histo_string) ;
h2_123359  = (TH2F*)file_123359->Get(histo_string) ;
h2_123360  = (TH2F*)file_123360->Get(histo_string) ;
h2_123361  = (TH2F*)file_123361->Get(histo_string) ;
h2_123362  = (TH2F*)file_123362->Get(histo_string) ;
h2_123363  = (TH2F*)file_123363->Get(histo_string) ;
h2_123364  = (TH2F*)file_123364->Get(histo_string) ;
h2_123365  = (TH2F*)file_123365->Get(histo_string) ;
h2_123366  = (TH2F*)file_123366->Get(histo_string) ;
h2_123367  = (TH2F*)file_123367->Get(histo_string) ;
h2_123368  = (TH2F*)file_123368->Get(histo_string) ;
h2_123369  = (TH2F*)file_123369->Get(histo_string) ;
h2_123370  = (TH2F*)file_123370->Get(histo_string) ;
h2_123371  = (TH2F*)file_123371->Get(histo_string) ;
h2_123372  = (TH2F*)file_123372->Get(histo_string) ;
h2_123373  = (TH2F*)file_123373->Get(histo_string) ;
h2_123374  = (TH2F*)file_123374->Get(histo_string) ;
h2_123375  = (TH2F*)file_123375->Get(histo_string) ;
h2_123376  = (TH2F*)file_123376->Get(histo_string) ;
h2_123377  = (TH2F*)file_123377->Get(histo_string) ;
h2_123378  = (TH2F*)file_123378->Get(histo_string) ;
h2_123379  = (TH2F*)file_123379->Get(histo_string) ;
h2_123380  = (TH2F*)file_123380->Get(histo_string) ;
h2_123381  = (TH2F*)file_123381->Get(histo_string) ;
h2_123383  = (TH2F*)file_123383->Get(histo_string) ;
h2_123384  = (TH2F*)file_123384->Get(histo_string) ;
h2_123385  = (TH2F*)file_123385->Get(histo_string) ;
h2_123386  = (TH2F*)file_123386->Get(histo_string) ;
h2_123387  = (TH2F*)file_123387->Get(histo_string) ;
h2_123388  = (TH2F*)file_123388->Get(histo_string) ;
h2_123389  = (TH2F*)file_123389->Get(histo_string) ;
h2_123390  = (TH2F*)file_123390->Get(histo_string) ;
h2_123391  = (TH2F*)file_123391->Get(histo_string) ;
h2_123392  = (TH2F*)file_123392->Get(histo_string) ;
h2_123393  = (TH2F*)file_123393->Get(histo_string) ;
h2_123394  = (TH2F*)file_123394->Get(histo_string) ;
h2_123396  = (TH2F*)file_123396->Get(histo_string) ;
h2_123397  = (TH2F*)file_123397->Get(histo_string) ;
h2_123398  = (TH2F*)file_123398->Get(histo_string) ;
h2_123399  = (TH2F*)file_123399->Get(histo_string) ;
h2_123400  = (TH2F*)file_123400->Get(histo_string) ;
h2_123401  = (TH2F*)file_123401->Get(histo_string) ;
h2_123402  = (TH2F*)file_123402->Get(histo_string) ;
h2_123403  = (TH2F*)file_123403->Get(histo_string) ;
h2_123404  = (TH2F*)file_123404->Get(histo_string) ;
h2_123405  = (TH2F*)file_123405->Get(histo_string) ;
h2_123406  = (TH2F*)file_123406->Get(histo_string) ;
h2_123407  = (TH2F*)file_123407->Get(histo_string) ;
h2_123408  = (TH2F*)file_123408->Get(histo_string) ;
h2_123409  = (TH2F*)file_123409->Get(histo_string) ;
h2_123410  = (TH2F*)file_123410->Get(histo_string) ;
h2_123411  = (TH2F*)file_123411->Get(histo_string) ;
h2_123412  = (TH2F*)file_123412->Get(histo_string) ;
h2_123413  = (TH2F*)file_123413->Get(histo_string) ;
h2_123414  = (TH2F*)file_123414->Get(histo_string) ;
h2_123415  = (TH2F*)file_123415->Get(histo_string) ;
h2_123416  = (TH2F*)file_123416->Get(histo_string) ;
h2_123417  = (TH2F*)file_123417->Get(histo_string) ;
h2_123418  = (TH2F*)file_123418->Get(histo_string) ;
h2_123419  = (TH2F*)file_123419->Get(histo_string) ;
h2_123420  = (TH2F*)file_123420->Get(histo_string) ;
h2_123422  = (TH2F*)file_123422->Get(histo_string) ;
h2_123423  = (TH2F*)file_123423->Get(histo_string) ;
h2_123424  = (TH2F*)file_123424->Get(histo_string) ;
h2_123425  = (TH2F*)file_123425->Get(histo_string) ;
h2_123426  = (TH2F*)file_123426->Get(histo_string) ;
h2_123427  = (TH2F*)file_123427->Get(histo_string) ;
h2_123428  = (TH2F*)file_123428->Get(histo_string) ;
h2_123430  = (TH2F*)file_123430->Get(histo_string) ;
h2_123431  = (TH2F*)file_123431->Get(histo_string) ;
h2_123432  = (TH2F*)file_123432->Get(histo_string) ;
h2_123433  = (TH2F*)file_123433->Get(histo_string) ;
h2_123434  = (TH2F*)file_123434->Get(histo_string) ;
h2_123435  = (TH2F*)file_123435->Get(histo_string) ;
h2_123436  = (TH2F*)file_123436->Get(histo_string) ;
h2_123437  = (TH2F*)file_123437->Get(histo_string) ;
h2_123438  = (TH2F*)file_123438->Get(histo_string) ;
h2_123439  = (TH2F*)file_123439->Get(histo_string) ;
h2_123440  = (TH2F*)file_123440->Get(histo_string) ;
h2_123441  = (TH2F*)file_123441->Get(histo_string) ;
h2_123442  = (TH2F*)file_123442->Get(histo_string) ;
h2_123443  = (TH2F*)file_123443->Get(histo_string) ;
h2_123444  = (TH2F*)file_123444->Get(histo_string) ;
h2_123445  = (TH2F*)file_123445->Get(histo_string) ;
h2_123447  = (TH2F*)file_123447->Get(histo_string) ;
h2_123448  = (TH2F*)file_123448->Get(histo_string) ;
h2_123449  = (TH2F*)file_123449->Get(histo_string) ;
h2_123450  = (TH2F*)file_123450->Get(histo_string) ;
h2_123451  = (TH2F*)file_123451->Get(histo_string) ;
h2_123452  = (TH2F*)file_123452->Get(histo_string) ;
h2_123453  = (TH2F*)file_123453->Get(histo_string) ;
h2_123454  = (TH2F*)file_123454->Get(histo_string) ;
h2_123455  = (TH2F*)file_123455->Get(histo_string) ;
h2_123456  = (TH2F*)file_123456->Get(histo_string) ;
h2_123457  = (TH2F*)file_123457->Get(histo_string) ;
h2_123458  = (TH2F*)file_123458->Get(histo_string) ;
h2_123460  = (TH2F*)file_123460->Get(histo_string) ;
h2_123461  = (TH2F*)file_123461->Get(histo_string) ;
h2_123462  = (TH2F*)file_123462->Get(histo_string) ;
h2_123463  = (TH2F*)file_123463->Get(histo_string) ;
h2_123464  = (TH2F*)file_123464->Get(histo_string) ;
h2_123465  = (TH2F*)file_123465->Get(histo_string) ;
h2_123466  = (TH2F*)file_123466->Get(histo_string) ;
h2_123467  = (TH2F*)file_123467->Get(histo_string) ;
h2_123468  = (TH2F*)file_123468->Get(histo_string) ;
h2_123469  = (TH2F*)file_123469->Get(histo_string) ;
h2_123470  = (TH2F*)file_123470->Get(histo_string) ;
h2_123471  = (TH2F*)file_123471->Get(histo_string) ;
h2_123472  = (TH2F*)file_123472->Get(histo_string) ;
h2_123473  = (TH2F*)file_123473->Get(histo_string) ;
h2_123474  = (TH2F*)file_123474->Get(histo_string) ;
h2_123475  = (TH2F*)file_123475->Get(histo_string) ;
h2_123476  = (TH2F*)file_123476->Get(histo_string) ;
h2_123477  = (TH2F*)file_123477->Get(histo_string) ;
h2_123478  = (TH2F*)file_123478->Get(histo_string) ;
h2_123479  = (TH2F*)file_123479->Get(histo_string) ;
h2_123480  = (TH2F*)file_123480->Get(histo_string) ;
h2_123481  = (TH2F*)file_123481->Get(histo_string) ;
h2_123482  = (TH2F*)file_123482->Get(histo_string) ;
h2_123483  = (TH2F*)file_123483->Get(histo_string) ;
h2_123484  = (TH2F*)file_123484->Get(histo_string) ;
h2_123485  = (TH2F*)file_123485->Get(histo_string) ;
h2_123486  = (TH2F*)file_123486->Get(histo_string) ;
h2_123487  = (TH2F*)file_123487->Get(histo_string) ;
h2_123488  = (TH2F*)file_123488->Get(histo_string) ;
h2_123489  = (TH2F*)file_123489->Get(histo_string) ;
h2_123490  = (TH2F*)file_123490->Get(histo_string) ;
h2_123491  = (TH2F*)file_123491->Get(histo_string) ;
h2_123492  = (TH2F*)file_123492->Get(histo_string) ;
h2_123493  = (TH2F*)file_123493->Get(histo_string) ;
h2_123494  = (TH2F*)file_123494->Get(histo_string) ;
h2_123495  = (TH2F*)file_123495->Get(histo_string) ;
h2_123496  = (TH2F*)file_123496->Get(histo_string) ;
h2_123497  = (TH2F*)file_123497->Get(histo_string) ;
h2_123498  = (TH2F*)file_123498->Get(histo_string) ;
h2_123499  = (TH2F*)file_123499->Get(histo_string) ;
h2_123501  = (TH2F*)file_123501->Get(histo_string) ;
h2_123502  = (TH2F*)file_123502->Get(histo_string) ;
h2_123503  = (TH2F*)file_123503->Get(histo_string) ;
h2_123504  = (TH2F*)file_123504->Get(histo_string) ;
h2_123505  = (TH2F*)file_123505->Get(histo_string) ;
h2_123506  = (TH2F*)file_123506->Get(histo_string) ;
h2_123507  = (TH2F*)file_123507->Get(histo_string) ;
h2_123508  = (TH2F*)file_123508->Get(histo_string) ;
h2_123509  = (TH2F*)file_123509->Get(histo_string) ;
h2_123510  = (TH2F*)file_123510->Get(histo_string) ;
h2_123511  = (TH2F*)file_123511->Get(histo_string) ;
h2_123512  = (TH2F*)file_123512->Get(histo_string) ;
h2_123513  = (TH2F*)file_123513->Get(histo_string) ;
h2_123514  = (TH2F*)file_123514->Get(histo_string) ;
h2_123516  = (TH2F*)file_123516->Get(histo_string) ;
h2_123517  = (TH2F*)file_123517->Get(histo_string) ;
h2_123518  = (TH2F*)file_123518->Get(histo_string) ;
h2_123519  = (TH2F*)file_123519->Get(histo_string) ;
h2_123520  = (TH2F*)file_123520->Get(histo_string) ;
h2_123521  = (TH2F*)file_123521->Get(histo_string) ;
h2_123522  = (TH2F*)file_123522->Get(histo_string) ;
h2_123523  = (TH2F*)file_123523->Get(histo_string) ;
h2_123524  = (TH2F*)file_123524->Get(histo_string) ;
h2_123526  = (TH2F*)file_123526->Get(histo_string) ;
h2_123527  = (TH2F*)file_123527->Get(histo_string) ;
h2_123528  = (TH2F*)file_123528->Get(histo_string) ;
h2_123529  = (TH2F*)file_123529->Get(histo_string) ;
h2_123530  = (TH2F*)file_123530->Get(histo_string) ;
h2_123531  = (TH2F*)file_123531->Get(histo_string) ;
h2_123533  = (TH2F*)file_123533->Get(histo_string) ;
h2_123534  = (TH2F*)file_123534->Get(histo_string) ;
h2_123535  = (TH2F*)file_123535->Get(histo_string) ;
h2_123536  = (TH2F*)file_123536->Get(histo_string) ;
h2_123537  = (TH2F*)file_123537->Get(histo_string) ;
h2_123538  = (TH2F*)file_123538->Get(histo_string) ;
h2_123539  = (TH2F*)file_123539->Get(histo_string) ;
h2_123540  = (TH2F*)file_123540->Get(histo_string) ;
h2_123541  = (TH2F*)file_123541->Get(histo_string) ;
h2_123542  = (TH2F*)file_123542->Get(histo_string) ;
h2_123543  = (TH2F*)file_123543->Get(histo_string) ;
h2_123544  = (TH2F*)file_123544->Get(histo_string) ;
h2_123545  = (TH2F*)file_123545->Get(histo_string) ;
h2_123546  = (TH2F*)file_123546->Get(histo_string) ;
h2_123547  = (TH2F*)file_123547->Get(histo_string) ;
h2_123548  = (TH2F*)file_123548->Get(histo_string) ;
h2_123549  = (TH2F*)file_123549->Get(histo_string) ;
h2_123550  = (TH2F*)file_123550->Get(histo_string) ;
h2_123551  = (TH2F*)file_123551->Get(histo_string) ;
h2_123552  = (TH2F*)file_123552->Get(histo_string) ;
h2_123553  = (TH2F*)file_123553->Get(histo_string) ;
h2_123554  = (TH2F*)file_123554->Get(histo_string) ;
h2_123555  = (TH2F*)file_123555->Get(histo_string) ;
h2_123556  = (TH2F*)file_123556->Get(histo_string) ;
h2_123557  = (TH2F*)file_123557->Get(histo_string) ;
h2_123558  = (TH2F*)file_123558->Get(histo_string) ;
h2_123559  = (TH2F*)file_123559->Get(histo_string) ;
h2_123560  = (TH2F*)file_123560->Get(histo_string) ;
h2_123561  = (TH2F*)file_123561->Get(histo_string) ;
h2_123562  = (TH2F*)file_123562->Get(histo_string) ;
h2_123563  = (TH2F*)file_123563->Get(histo_string) ;
h2_123564  = (TH2F*)file_123564->Get(histo_string) ;
h2_123565  = (TH2F*)file_123565->Get(histo_string) ;
h2_123566  = (TH2F*)file_123566->Get(histo_string) ;
h2_123567  = (TH2F*)file_123567->Get(histo_string) ;
h2_123568  = (TH2F*)file_123568->Get(histo_string) ;
h2_123569  = (TH2F*)file_123569->Get(histo_string) ;
h2_123570  = (TH2F*)file_123570->Get(histo_string) ;
h2_123571  = (TH2F*)file_123571->Get(histo_string) ;
h2_123572  = (TH2F*)file_123572->Get(histo_string) ;
h2_123573  = (TH2F*)file_123573->Get(histo_string) ;
h2_123574  = (TH2F*)file_123574->Get(histo_string) ;
h2_123575  = (TH2F*)file_123575->Get(histo_string) ;
h2_123576  = (TH2F*)file_123576->Get(histo_string) ;
h2_123577  = (TH2F*)file_123577->Get(histo_string) ;
h2_123578  = (TH2F*)file_123578->Get(histo_string) ;
h2_123579  = (TH2F*)file_123579->Get(histo_string) ;
h2_123580  = (TH2F*)file_123580->Get(histo_string) ;
h2_123581  = (TH2F*)file_123581->Get(histo_string) ;
h2_123582  = (TH2F*)file_123582->Get(histo_string) ;
h2_123583  = (TH2F*)file_123583->Get(histo_string) ;
h2_123584  = (TH2F*)file_123584->Get(histo_string) ;
h2_123585  = (TH2F*)file_123585->Get(histo_string) ;
h2_123586  = (TH2F*)file_123586->Get(histo_string) ;
h2_123587  = (TH2F*)file_123587->Get(histo_string) ;
h2_123588  = (TH2F*)file_123588->Get(histo_string) ;
h2_123589  = (TH2F*)file_123589->Get(histo_string) ;
h2_123590  = (TH2F*)file_123590->Get(histo_string) ;
h2_123591  = (TH2F*)file_123591->Get(histo_string) ;
h2_123592  = (TH2F*)file_123592->Get(histo_string) ;
h2_123593  = (TH2F*)file_123593->Get(histo_string) ;
h2_123594  = (TH2F*)file_123594->Get(histo_string) ;
h2_123595  = (TH2F*)file_123595->Get(histo_string) ;
h2_123597  = (TH2F*)file_123597->Get(histo_string) ;
h2_123598  = (TH2F*)file_123598->Get(histo_string) ;
h2_123599  = (TH2F*)file_123599->Get(histo_string) ;
h2_123600  = (TH2F*)file_123600->Get(histo_string) ;
h2_123601  = (TH2F*)file_123601->Get(histo_string) ;
h2_123602  = (TH2F*)file_123602->Get(histo_string) ;
h2_123603  = (TH2F*)file_123603->Get(histo_string) ;
h2_123604  = (TH2F*)file_123604->Get(histo_string) ;
h2_123605  = (TH2F*)file_123605->Get(histo_string) ;
h2_123606  = (TH2F*)file_123606->Get(histo_string) ;
h2_123607  = (TH2F*)file_123607->Get(histo_string) ;
h2_123609  = (TH2F*)file_123609->Get(histo_string) ;
h2_123611  = (TH2F*)file_123611->Get(histo_string) ;
h2_123612  = (TH2F*)file_123612->Get(histo_string) ;
h2_123613  = (TH2F*)file_123613->Get(histo_string) ;
h2_123614  = (TH2F*)file_123614->Get(histo_string) ;
h2_123615  = (TH2F*)file_123615->Get(histo_string) ;
h2_123616  = (TH2F*)file_123616->Get(histo_string) ;
h2_123617  = (TH2F*)file_123617->Get(histo_string) ;
h2_123618  = (TH2F*)file_123618->Get(histo_string) ;
h2_123619  = (TH2F*)file_123619->Get(histo_string) ;
h2_123620  = (TH2F*)file_123620->Get(histo_string) ;
h2_123621  = (TH2F*)file_123621->Get(histo_string) ;
h2_123622  = (TH2F*)file_123622->Get(histo_string) ;
h2_123623  = (TH2F*)file_123623->Get(histo_string) ;
h2_123624  = (TH2F*)file_123624->Get(histo_string) ;
h2_123625  = (TH2F*)file_123625->Get(histo_string) ;
h2_123626  = (TH2F*)file_123626->Get(histo_string) ;
h2_123628  = (TH2F*)file_123628->Get(histo_string) ;
h2_123629  = (TH2F*)file_123629->Get(histo_string) ;
h2_123630  = (TH2F*)file_123630->Get(histo_string) ;
h2_123631  = (TH2F*)file_123631->Get(histo_string) ;
h2_123632  = (TH2F*)file_123632->Get(histo_string) ;
h2_123633  = (TH2F*)file_123633->Get(histo_string) ;
h2_123634  = (TH2F*)file_123634->Get(histo_string) ;
h2_123635  = (TH2F*)file_123635->Get(histo_string) ;
h2_123636  = (TH2F*)file_123636->Get(histo_string) ;
h2_123637  = (TH2F*)file_123637->Get(histo_string) ;
h2_123638  = (TH2F*)file_123638->Get(histo_string) ;
h2_123640  = (TH2F*)file_123640->Get(histo_string) ;
h2_123641  = (TH2F*)file_123641->Get(histo_string) ;
h2_123642  = (TH2F*)file_123642->Get(histo_string) ;
h2_123643  = (TH2F*)file_123643->Get(histo_string) ;
h2_123644  = (TH2F*)file_123644->Get(histo_string) ;
h2_123645  = (TH2F*)file_123645->Get(histo_string) ;
h2_123646  = (TH2F*)file_123646->Get(histo_string) ;
h2_123647  = (TH2F*)file_123647->Get(histo_string) ;
h2_123648  = (TH2F*)file_123648->Get(histo_string) ;
h2_123649  = (TH2F*)file_123649->Get(histo_string) ;
h2_123650  = (TH2F*)file_123650->Get(histo_string) ;
h2_123651  = (TH2F*)file_123651->Get(histo_string) ;
h2_123652  = (TH2F*)file_123652->Get(histo_string) ;
h2_123653  = (TH2F*)file_123653->Get(histo_string) ;
h2_123654  = (TH2F*)file_123654->Get(histo_string) ;
h2_123655  = (TH2F*)file_123655->Get(histo_string) ;
h2_123656  = (TH2F*)file_123656->Get(histo_string) ;
h2_123657  = (TH2F*)file_123657->Get(histo_string) ;
h2_123658  = (TH2F*)file_123658->Get(histo_string) ;
h2_123659  = (TH2F*)file_123659->Get(histo_string) ;
h2_123660  = (TH2F*)file_123660->Get(histo_string) ;
h2_123661  = (TH2F*)file_123661->Get(histo_string) ;
h2_123662  = (TH2F*)file_123662->Get(histo_string) ;
h2_123663  = (TH2F*)file_123663->Get(histo_string) ;
h2_123664  = (TH2F*)file_123664->Get(histo_string) ;
h2_123665  = (TH2F*)file_123665->Get(histo_string) ;
h2_123666  = (TH2F*)file_123666->Get(histo_string) ;
h2_123667  = (TH2F*)file_123667->Get(histo_string) ;
h2_123668  = (TH2F*)file_123668->Get(histo_string) ;
h2_123669  = (TH2F*)file_123669->Get(histo_string) ;
h2_123670  = (TH2F*)file_123670->Get(histo_string) ;
h2_123671  = (TH2F*)file_123671->Get(histo_string) ;
h2_123672  = (TH2F*)file_123672->Get(histo_string) ;
h2_123673  = (TH2F*)file_123673->Get(histo_string) ;
h2_123674  = (TH2F*)file_123674->Get(histo_string) ;
h2_123675  = (TH2F*)file_123675->Get(histo_string) ;
h2_123676  = (TH2F*)file_123676->Get(histo_string) ;
h2_123677  = (TH2F*)file_123677->Get(histo_string) ;
h2_123678  = (TH2F*)file_123678->Get(histo_string) ;
h2_123679  = (TH2F*)file_123679->Get(histo_string) ;
h2_123680  = (TH2F*)file_123680->Get(histo_string) ;
h2_123682  = (TH2F*)file_123682->Get(histo_string) ;
h2_123683  = (TH2F*)file_123683->Get(histo_string) ;
h2_123684  = (TH2F*)file_123684->Get(histo_string) ;
h2_123686  = (TH2F*)file_123686->Get(histo_string) ;
h2_123687  = (TH2F*)file_123687->Get(histo_string) ;
h2_123688  = (TH2F*)file_123688->Get(histo_string) ;
h2_123689  = (TH2F*)file_123689->Get(histo_string) ;
h2_123690  = (TH2F*)file_123690->Get(histo_string) ;


  h1_123290 = h2_123290->ProjectionX("h1_123290", binmin, binmax, "e");
  h1_123291 = h2_123291->ProjectionX("h1_123291", binmin, binmax, "e");
  h1_123292 = h2_123292->ProjectionX("h1_123292", binmin, binmax, "e");
  h1_123293 = h2_123293->ProjectionX("h1_123293", binmin, binmax, "e");
  h1_123294 = h2_123294->ProjectionX("h1_123294", binmin, binmax, "e");
  h1_123295 = h2_123295->ProjectionX("h1_123295", binmin, binmax, "e");
  h1_123296 = h2_123296->ProjectionX("h1_123296", binmin, binmax, "e");
  h1_123297 = h2_123297->ProjectionX("h1_123297", binmin, binmax, "e");
  h1_123298 = h2_123298->ProjectionX("h1_123298", binmin, binmax, "e");
  h1_123299 = h2_123299->ProjectionX("h1_123299", binmin, binmax, "e");
  h1_123300 = h2_123300->ProjectionX("h1_123300", binmin, binmax, "e");
  h1_123301 = h2_123301->ProjectionX("h1_123301", binmin, binmax, "e");
  h1_123302 = h2_123302->ProjectionX("h1_123302", binmin, binmax, "e");
  h1_123303 = h2_123303->ProjectionX("h1_123303", binmin, binmax, "e");
  h1_123304 = h2_123304->ProjectionX("h1_123304", binmin, binmax, "e");
  h1_123305 = h2_123305->ProjectionX("h1_123305", binmin, binmax, "e");
  h1_123306 = h2_123306->ProjectionX("h1_123306", binmin, binmax, "e");
  h1_123307 = h2_123307->ProjectionX("h1_123307", binmin, binmax, "e");
  h1_123308 = h2_123308->ProjectionX("h1_123308", binmin, binmax, "e");
  h1_123309 = h2_123309->ProjectionX("h1_123309", binmin, binmax, "e");
  h1_123310 = h2_123310->ProjectionX("h1_123310", binmin, binmax, "e");
  h1_123311 = h2_123311->ProjectionX("h1_123311", binmin, binmax, "e");
  h1_123312 = h2_123312->ProjectionX("h1_123312", binmin, binmax, "e");
  h1_123313 = h2_123313->ProjectionX("h1_123313", binmin, binmax, "e");
  h1_123314 = h2_123314->ProjectionX("h1_123314", binmin, binmax, "e");
  h1_123315 = h2_123315->ProjectionX("h1_123315", binmin, binmax, "e");
  h1_123316 = h2_123316->ProjectionX("h1_123316", binmin, binmax, "e");
  h1_123317 = h2_123317->ProjectionX("h1_123317", binmin, binmax, "e");
  h1_123320 = h2_123320->ProjectionX("h1_123320", binmin, binmax, "e");
  h1_123321 = h2_123321->ProjectionX("h1_123321", binmin, binmax, "e");
  h1_123322 = h2_123322->ProjectionX("h1_123322", binmin, binmax, "e");
  h1_123323 = h2_123323->ProjectionX("h1_123323", binmin, binmax, "e");
  h1_123324 = h2_123324->ProjectionX("h1_123324", binmin, binmax, "e");
  h1_123325 = h2_123325->ProjectionX("h1_123325", binmin, binmax, "e");
  h1_123326 = h2_123326->ProjectionX("h1_123326", binmin, binmax, "e");
  h1_123327 = h2_123327->ProjectionX("h1_123327", binmin, binmax, "e");
  h1_123328 = h2_123328->ProjectionX("h1_123328", binmin, binmax, "e");
  h1_123329 = h2_123329->ProjectionX("h1_123329", binmin, binmax, "e");
  h1_123330 = h2_123330->ProjectionX("h1_123330", binmin, binmax, "e");
  h1_123331 = h2_123331->ProjectionX("h1_123331", binmin, binmax, "e");
  h1_123332 = h2_123332->ProjectionX("h1_123332", binmin, binmax, "e");
  h1_123333 = h2_123333->ProjectionX("h1_123333", binmin, binmax, "e");
  h1_123334 = h2_123334->ProjectionX("h1_123334", binmin, binmax, "e");
  h1_123335 = h2_123335->ProjectionX("h1_123335", binmin, binmax, "e");
  h1_123336 = h2_123336->ProjectionX("h1_123336", binmin, binmax, "e");
  h1_123337 = h2_123337->ProjectionX("h1_123337", binmin, binmax, "e");
  h1_123338 = h2_123338->ProjectionX("h1_123338", binmin, binmax, "e");
  h1_123339 = h2_123339->ProjectionX("h1_123339", binmin, binmax, "e");
  h1_123340 = h2_123340->ProjectionX("h1_123340", binmin, binmax, "e");
  h1_123341 = h2_123341->ProjectionX("h1_123341", binmin, binmax, "e");
  h1_123342 = h2_123342->ProjectionX("h1_123342", binmin, binmax, "e");
  h1_123343 = h2_123343->ProjectionX("h1_123343", binmin, binmax, "e");
  h1_123344 = h2_123344->ProjectionX("h1_123344", binmin, binmax, "e");
  h1_123345 = h2_123345->ProjectionX("h1_123345", binmin, binmax, "e");
  h1_123346 = h2_123346->ProjectionX("h1_123346", binmin, binmax, "e");
  h1_123347 = h2_123347->ProjectionX("h1_123347", binmin, binmax, "e");
  h1_123348 = h2_123348->ProjectionX("h1_123348", binmin, binmax, "e");
  h1_123349 = h2_123349->ProjectionX("h1_123349", binmin, binmax, "e");
  h1_123350 = h2_123350->ProjectionX("h1_123350", binmin, binmax, "e");
  h1_123351 = h2_123351->ProjectionX("h1_123351", binmin, binmax, "e");
  h1_123352 = h2_123352->ProjectionX("h1_123352", binmin, binmax, "e");
  h1_123353 = h2_123353->ProjectionX("h1_123353", binmin, binmax, "e");
  h1_123354 = h2_123354->ProjectionX("h1_123354", binmin, binmax, "e");
  h1_123355 = h2_123355->ProjectionX("h1_123355", binmin, binmax, "e");
  h1_123356 = h2_123356->ProjectionX("h1_123356", binmin, binmax, "e");
  h1_123357 = h2_123357->ProjectionX("h1_123357", binmin, binmax, "e");
  h1_123358 = h2_123358->ProjectionX("h1_123358", binmin, binmax, "e");
  h1_123359 = h2_123359->ProjectionX("h1_123359", binmin, binmax, "e");
  h1_123360 = h2_123360->ProjectionX("h1_123360", binmin, binmax, "e");
  h1_123361 = h2_123361->ProjectionX("h1_123361", binmin, binmax, "e");
  h1_123362 = h2_123362->ProjectionX("h1_123362", binmin, binmax, "e");
  h1_123363 = h2_123363->ProjectionX("h1_123363", binmin, binmax, "e");
  h1_123364 = h2_123364->ProjectionX("h1_123364", binmin, binmax, "e");
  h1_123365 = h2_123365->ProjectionX("h1_123365", binmin, binmax, "e");
  h1_123366 = h2_123366->ProjectionX("h1_123366", binmin, binmax, "e");
  h1_123367 = h2_123367->ProjectionX("h1_123367", binmin, binmax, "e");
  h1_123368 = h2_123368->ProjectionX("h1_123368", binmin, binmax, "e");
  h1_123369 = h2_123369->ProjectionX("h1_123369", binmin, binmax, "e");
  h1_123370 = h2_123370->ProjectionX("h1_123370", binmin, binmax, "e");
  h1_123371 = h2_123371->ProjectionX("h1_123371", binmin, binmax, "e");
  h1_123372 = h2_123372->ProjectionX("h1_123372", binmin, binmax, "e");
  h1_123373 = h2_123373->ProjectionX("h1_123373", binmin, binmax, "e");
  h1_123374 = h2_123374->ProjectionX("h1_123374", binmin, binmax, "e");
  h1_123375 = h2_123375->ProjectionX("h1_123375", binmin, binmax, "e");
  h1_123376 = h2_123376->ProjectionX("h1_123376", binmin, binmax, "e");
  h1_123377 = h2_123377->ProjectionX("h1_123377", binmin, binmax, "e");
  h1_123378 = h2_123378->ProjectionX("h1_123378", binmin, binmax, "e");
  h1_123379 = h2_123379->ProjectionX("h1_123379", binmin, binmax, "e");
  h1_123380 = h2_123380->ProjectionX("h1_123380", binmin, binmax, "e");
  h1_123381 = h2_123381->ProjectionX("h1_123381", binmin, binmax, "e");
  h1_123383 = h2_123383->ProjectionX("h1_123383", binmin, binmax, "e");
  h1_123384 = h2_123384->ProjectionX("h1_123384", binmin, binmax, "e");
  h1_123385 = h2_123385->ProjectionX("h1_123385", binmin, binmax, "e");
  h1_123386 = h2_123386->ProjectionX("h1_123386", binmin, binmax, "e");
  h1_123387 = h2_123387->ProjectionX("h1_123387", binmin, binmax, "e");
  h1_123388 = h2_123388->ProjectionX("h1_123388", binmin, binmax, "e");
  h1_123389 = h2_123389->ProjectionX("h1_123389", binmin, binmax, "e");
  h1_123390 = h2_123390->ProjectionX("h1_123390", binmin, binmax, "e");
  h1_123391 = h2_123391->ProjectionX("h1_123391", binmin, binmax, "e");
  h1_123392 = h2_123392->ProjectionX("h1_123392", binmin, binmax, "e");
  h1_123393 = h2_123393->ProjectionX("h1_123393", binmin, binmax, "e");
  h1_123394 = h2_123394->ProjectionX("h1_123394", binmin, binmax, "e");
  h1_123396 = h2_123396->ProjectionX("h1_123396", binmin, binmax, "e");
  h1_123397 = h2_123397->ProjectionX("h1_123397", binmin, binmax, "e");
  h1_123398 = h2_123398->ProjectionX("h1_123398", binmin, binmax, "e");
  h1_123399 = h2_123399->ProjectionX("h1_123399", binmin, binmax, "e");
  h1_123400 = h2_123400->ProjectionX("h1_123400", binmin, binmax, "e");
  h1_123401 = h2_123401->ProjectionX("h1_123401", binmin, binmax, "e");
  h1_123402 = h2_123402->ProjectionX("h1_123402", binmin, binmax, "e");
  h1_123403 = h2_123403->ProjectionX("h1_123403", binmin, binmax, "e");
  h1_123404 = h2_123404->ProjectionX("h1_123404", binmin, binmax, "e");
  h1_123405 = h2_123405->ProjectionX("h1_123405", binmin, binmax, "e");
  h1_123406 = h2_123406->ProjectionX("h1_123406", binmin, binmax, "e");
  h1_123407 = h2_123407->ProjectionX("h1_123407", binmin, binmax, "e");
  h1_123408 = h2_123408->ProjectionX("h1_123408", binmin, binmax, "e");
  h1_123409 = h2_123409->ProjectionX("h1_123409", binmin, binmax, "e");
  h1_123410 = h2_123410->ProjectionX("h1_123410", binmin, binmax, "e");
  h1_123411 = h2_123411->ProjectionX("h1_123411", binmin, binmax, "e");
  h1_123412 = h2_123412->ProjectionX("h1_123412", binmin, binmax, "e");
  h1_123413 = h2_123413->ProjectionX("h1_123413", binmin, binmax, "e");
  h1_123414 = h2_123414->ProjectionX("h1_123414", binmin, binmax, "e");
  h1_123415 = h2_123415->ProjectionX("h1_123415", binmin, binmax, "e");
  h1_123416 = h2_123416->ProjectionX("h1_123416", binmin, binmax, "e");
  h1_123417 = h2_123417->ProjectionX("h1_123417", binmin, binmax, "e");
  h1_123418 = h2_123418->ProjectionX("h1_123418", binmin, binmax, "e");
  h1_123419 = h2_123419->ProjectionX("h1_123419", binmin, binmax, "e");
  h1_123420 = h2_123420->ProjectionX("h1_123420", binmin, binmax, "e");
  h1_123422 = h2_123422->ProjectionX("h1_123422", binmin, binmax, "e");
  h1_123423 = h2_123423->ProjectionX("h1_123423", binmin, binmax, "e");
  h1_123424 = h2_123424->ProjectionX("h1_123424", binmin, binmax, "e");
  h1_123425 = h2_123425->ProjectionX("h1_123425", binmin, binmax, "e");
  h1_123426 = h2_123426->ProjectionX("h1_123426", binmin, binmax, "e");
  h1_123427 = h2_123427->ProjectionX("h1_123427", binmin, binmax, "e");
  h1_123428 = h2_123428->ProjectionX("h1_123428", binmin, binmax, "e");
  h1_123430 = h2_123430->ProjectionX("h1_123430", binmin, binmax, "e");
  h1_123431 = h2_123431->ProjectionX("h1_123431", binmin, binmax, "e");
  h1_123432 = h2_123432->ProjectionX("h1_123432", binmin, binmax, "e");
  h1_123433 = h2_123433->ProjectionX("h1_123433", binmin, binmax, "e");
  h1_123434 = h2_123434->ProjectionX("h1_123434", binmin, binmax, "e");
  h1_123435 = h2_123435->ProjectionX("h1_123435", binmin, binmax, "e");
  h1_123436 = h2_123436->ProjectionX("h1_123436", binmin, binmax, "e");
  h1_123437 = h2_123437->ProjectionX("h1_123437", binmin, binmax, "e");
  h1_123438 = h2_123438->ProjectionX("h1_123438", binmin, binmax, "e");
  h1_123439 = h2_123439->ProjectionX("h1_123439", binmin, binmax, "e");
  h1_123440 = h2_123440->ProjectionX("h1_123440", binmin, binmax, "e");
  h1_123441 = h2_123441->ProjectionX("h1_123441", binmin, binmax, "e");
  h1_123442 = h2_123442->ProjectionX("h1_123442", binmin, binmax, "e");
  h1_123443 = h2_123443->ProjectionX("h1_123443", binmin, binmax, "e");
  h1_123444 = h2_123444->ProjectionX("h1_123444", binmin, binmax, "e");
  h1_123445 = h2_123445->ProjectionX("h1_123445", binmin, binmax, "e");
  h1_123447 = h2_123447->ProjectionX("h1_123447", binmin, binmax, "e");
  h1_123448 = h2_123448->ProjectionX("h1_123448", binmin, binmax, "e");
  h1_123449 = h2_123449->ProjectionX("h1_123449", binmin, binmax, "e");
  h1_123450 = h2_123450->ProjectionX("h1_123450", binmin, binmax, "e");
  h1_123451 = h2_123451->ProjectionX("h1_123451", binmin, binmax, "e");
  h1_123452 = h2_123452->ProjectionX("h1_123452", binmin, binmax, "e");
  h1_123453 = h2_123453->ProjectionX("h1_123453", binmin, binmax, "e");
  h1_123454 = h2_123454->ProjectionX("h1_123454", binmin, binmax, "e");
  h1_123455 = h2_123455->ProjectionX("h1_123455", binmin, binmax, "e");
  h1_123456 = h2_123456->ProjectionX("h1_123456", binmin, binmax, "e");
  h1_123457 = h2_123457->ProjectionX("h1_123457", binmin, binmax, "e");
  h1_123458 = h2_123458->ProjectionX("h1_123458", binmin, binmax, "e");
  h1_123460 = h2_123460->ProjectionX("h1_123460", binmin, binmax, "e");
  h1_123461 = h2_123461->ProjectionX("h1_123461", binmin, binmax, "e");
  h1_123462 = h2_123462->ProjectionX("h1_123462", binmin, binmax, "e");
  h1_123463 = h2_123463->ProjectionX("h1_123463", binmin, binmax, "e");
  h1_123464 = h2_123464->ProjectionX("h1_123464", binmin, binmax, "e");
  h1_123465 = h2_123465->ProjectionX("h1_123465", binmin, binmax, "e");
  h1_123466 = h2_123466->ProjectionX("h1_123466", binmin, binmax, "e");
  h1_123467 = h2_123467->ProjectionX("h1_123467", binmin, binmax, "e");
  h1_123468 = h2_123468->ProjectionX("h1_123468", binmin, binmax, "e");
  h1_123469 = h2_123469->ProjectionX("h1_123469", binmin, binmax, "e");
  h1_123470 = h2_123470->ProjectionX("h1_123470", binmin, binmax, "e");
  h1_123471 = h2_123471->ProjectionX("h1_123471", binmin, binmax, "e");
  h1_123472 = h2_123472->ProjectionX("h1_123472", binmin, binmax, "e");
  h1_123473 = h2_123473->ProjectionX("h1_123473", binmin, binmax, "e");
  h1_123474 = h2_123474->ProjectionX("h1_123474", binmin, binmax, "e");
  h1_123475 = h2_123475->ProjectionX("h1_123475", binmin, binmax, "e");
  h1_123476 = h2_123476->ProjectionX("h1_123476", binmin, binmax, "e");
  h1_123477 = h2_123477->ProjectionX("h1_123477", binmin, binmax, "e");
  h1_123478 = h2_123478->ProjectionX("h1_123478", binmin, binmax, "e");
  h1_123479 = h2_123479->ProjectionX("h1_123479", binmin, binmax, "e");
  h1_123480 = h2_123480->ProjectionX("h1_123480", binmin, binmax, "e");
  h1_123481 = h2_123481->ProjectionX("h1_123481", binmin, binmax, "e");
  h1_123482 = h2_123482->ProjectionX("h1_123482", binmin, binmax, "e");
  h1_123483 = h2_123483->ProjectionX("h1_123483", binmin, binmax, "e");
  h1_123484 = h2_123484->ProjectionX("h1_123484", binmin, binmax, "e");
  h1_123485 = h2_123485->ProjectionX("h1_123485", binmin, binmax, "e");
  h1_123486 = h2_123486->ProjectionX("h1_123486", binmin, binmax, "e");
  h1_123487 = h2_123487->ProjectionX("h1_123487", binmin, binmax, "e");
  h1_123488 = h2_123488->ProjectionX("h1_123488", binmin, binmax, "e");
  h1_123489 = h2_123489->ProjectionX("h1_123489", binmin, binmax, "e");
  h1_123490 = h2_123490->ProjectionX("h1_123490", binmin, binmax, "e");
  h1_123491 = h2_123491->ProjectionX("h1_123491", binmin, binmax, "e");
  h1_123492 = h2_123492->ProjectionX("h1_123492", binmin, binmax, "e");
  h1_123493 = h2_123493->ProjectionX("h1_123493", binmin, binmax, "e");
  h1_123494 = h2_123494->ProjectionX("h1_123494", binmin, binmax, "e");
  h1_123495 = h2_123495->ProjectionX("h1_123495", binmin, binmax, "e");
  h1_123496 = h2_123496->ProjectionX("h1_123496", binmin, binmax, "e");
  h1_123497 = h2_123497->ProjectionX("h1_123497", binmin, binmax, "e");
  h1_123498 = h2_123498->ProjectionX("h1_123498", binmin, binmax, "e");
  h1_123499 = h2_123499->ProjectionX("h1_123499", binmin, binmax, "e");
  h1_123501 = h2_123501->ProjectionX("h1_123501", binmin, binmax, "e");
  h1_123502 = h2_123502->ProjectionX("h1_123502", binmin, binmax, "e");
  h1_123503 = h2_123503->ProjectionX("h1_123503", binmin, binmax, "e");
  h1_123504 = h2_123504->ProjectionX("h1_123504", binmin, binmax, "e");
  h1_123505 = h2_123505->ProjectionX("h1_123505", binmin, binmax, "e");
  h1_123506 = h2_123506->ProjectionX("h1_123506", binmin, binmax, "e");
  h1_123507 = h2_123507->ProjectionX("h1_123507", binmin, binmax, "e");
  h1_123508 = h2_123508->ProjectionX("h1_123508", binmin, binmax, "e");
  h1_123509 = h2_123509->ProjectionX("h1_123509", binmin, binmax, "e");
  h1_123510 = h2_123510->ProjectionX("h1_123510", binmin, binmax, "e");
  h1_123511 = h2_123511->ProjectionX("h1_123511", binmin, binmax, "e");
  h1_123512 = h2_123512->ProjectionX("h1_123512", binmin, binmax, "e");
  h1_123513 = h2_123513->ProjectionX("h1_123513", binmin, binmax, "e");
  h1_123514 = h2_123514->ProjectionX("h1_123514", binmin, binmax, "e");
  h1_123516 = h2_123516->ProjectionX("h1_123516", binmin, binmax, "e");
  h1_123517 = h2_123517->ProjectionX("h1_123517", binmin, binmax, "e");
  h1_123518 = h2_123518->ProjectionX("h1_123518", binmin, binmax, "e");
  h1_123519 = h2_123519->ProjectionX("h1_123519", binmin, binmax, "e");
  h1_123520 = h2_123520->ProjectionX("h1_123520", binmin, binmax, "e");
  h1_123521 = h2_123521->ProjectionX("h1_123521", binmin, binmax, "e");
  h1_123522 = h2_123522->ProjectionX("h1_123522", binmin, binmax, "e");
  h1_123523 = h2_123523->ProjectionX("h1_123523", binmin, binmax, "e");
  h1_123524 = h2_123524->ProjectionX("h1_123524", binmin, binmax, "e");
  h1_123526 = h2_123526->ProjectionX("h1_123526", binmin, binmax, "e");
  h1_123527 = h2_123527->ProjectionX("h1_123527", binmin, binmax, "e");
  h1_123528 = h2_123528->ProjectionX("h1_123528", binmin, binmax, "e");
  h1_123529 = h2_123529->ProjectionX("h1_123529", binmin, binmax, "e");
  h1_123530 = h2_123530->ProjectionX("h1_123530", binmin, binmax, "e");
  h1_123531 = h2_123531->ProjectionX("h1_123531", binmin, binmax, "e");
  h1_123533 = h2_123533->ProjectionX("h1_123533", binmin, binmax, "e");
  h1_123534 = h2_123534->ProjectionX("h1_123534", binmin, binmax, "e");
  h1_123535 = h2_123535->ProjectionX("h1_123535", binmin, binmax, "e");
  h1_123536 = h2_123536->ProjectionX("h1_123536", binmin, binmax, "e");
  h1_123537 = h2_123537->ProjectionX("h1_123537", binmin, binmax, "e");
  h1_123538 = h2_123538->ProjectionX("h1_123538", binmin, binmax, "e");
  h1_123539 = h2_123539->ProjectionX("h1_123539", binmin, binmax, "e");
  h1_123540 = h2_123540->ProjectionX("h1_123540", binmin, binmax, "e");
  h1_123541 = h2_123541->ProjectionX("h1_123541", binmin, binmax, "e");
  h1_123542 = h2_123542->ProjectionX("h1_123542", binmin, binmax, "e");
  h1_123543 = h2_123543->ProjectionX("h1_123543", binmin, binmax, "e");
  h1_123544 = h2_123544->ProjectionX("h1_123544", binmin, binmax, "e");
  h1_123545 = h2_123545->ProjectionX("h1_123545", binmin, binmax, "e");
  h1_123546 = h2_123546->ProjectionX("h1_123546", binmin, binmax, "e");
  h1_123547 = h2_123547->ProjectionX("h1_123547", binmin, binmax, "e");
  h1_123548 = h2_123548->ProjectionX("h1_123548", binmin, binmax, "e");
  h1_123549 = h2_123549->ProjectionX("h1_123549", binmin, binmax, "e");
  h1_123550 = h2_123550->ProjectionX("h1_123550", binmin, binmax, "e");
  h1_123551 = h2_123551->ProjectionX("h1_123551", binmin, binmax, "e");
  h1_123552 = h2_123552->ProjectionX("h1_123552", binmin, binmax, "e");
  h1_123553 = h2_123553->ProjectionX("h1_123553", binmin, binmax, "e");
  h1_123554 = h2_123554->ProjectionX("h1_123554", binmin, binmax, "e");
  h1_123555 = h2_123555->ProjectionX("h1_123555", binmin, binmax, "e");
  h1_123556 = h2_123556->ProjectionX("h1_123556", binmin, binmax, "e");
  h1_123557 = h2_123557->ProjectionX("h1_123557", binmin, binmax, "e");
  h1_123558 = h2_123558->ProjectionX("h1_123558", binmin, binmax, "e");
  h1_123559 = h2_123559->ProjectionX("h1_123559", binmin, binmax, "e");
  h1_123560 = h2_123560->ProjectionX("h1_123560", binmin, binmax, "e");
  h1_123561 = h2_123561->ProjectionX("h1_123561", binmin, binmax, "e");
  h1_123562 = h2_123562->ProjectionX("h1_123562", binmin, binmax, "e");
  h1_123563 = h2_123563->ProjectionX("h1_123563", binmin, binmax, "e");
  h1_123564 = h2_123564->ProjectionX("h1_123564", binmin, binmax, "e");
  h1_123565 = h2_123565->ProjectionX("h1_123565", binmin, binmax, "e");
  h1_123566 = h2_123566->ProjectionX("h1_123566", binmin, binmax, "e");
  h1_123567 = h2_123567->ProjectionX("h1_123567", binmin, binmax, "e");
  h1_123568 = h2_123568->ProjectionX("h1_123568", binmin, binmax, "e");
  h1_123569 = h2_123569->ProjectionX("h1_123569", binmin, binmax, "e");
  h1_123570 = h2_123570->ProjectionX("h1_123570", binmin, binmax, "e");
  h1_123571 = h2_123571->ProjectionX("h1_123571", binmin, binmax, "e");
  h1_123572 = h2_123572->ProjectionX("h1_123572", binmin, binmax, "e");
  h1_123573 = h2_123573->ProjectionX("h1_123573", binmin, binmax, "e");
  h1_123574 = h2_123574->ProjectionX("h1_123574", binmin, binmax, "e");
  h1_123575 = h2_123575->ProjectionX("h1_123575", binmin, binmax, "e");
  h1_123576 = h2_123576->ProjectionX("h1_123576", binmin, binmax, "e");
  h1_123577 = h2_123577->ProjectionX("h1_123577", binmin, binmax, "e");
  h1_123578 = h2_123578->ProjectionX("h1_123578", binmin, binmax, "e");
  h1_123579 = h2_123579->ProjectionX("h1_123579", binmin, binmax, "e");
  h1_123580 = h2_123580->ProjectionX("h1_123580", binmin, binmax, "e");
  h1_123581 = h2_123581->ProjectionX("h1_123581", binmin, binmax, "e");
  h1_123582 = h2_123582->ProjectionX("h1_123582", binmin, binmax, "e");
  h1_123583 = h2_123583->ProjectionX("h1_123583", binmin, binmax, "e");
  h1_123584 = h2_123584->ProjectionX("h1_123584", binmin, binmax, "e");
  h1_123585 = h2_123585->ProjectionX("h1_123585", binmin, binmax, "e");
  h1_123586 = h2_123586->ProjectionX("h1_123586", binmin, binmax, "e");
  h1_123587 = h2_123587->ProjectionX("h1_123587", binmin, binmax, "e");
  h1_123588 = h2_123588->ProjectionX("h1_123588", binmin, binmax, "e");
  h1_123589 = h2_123589->ProjectionX("h1_123589", binmin, binmax, "e");
  h1_123590 = h2_123590->ProjectionX("h1_123590", binmin, binmax, "e");
  h1_123591 = h2_123591->ProjectionX("h1_123591", binmin, binmax, "e");
  h1_123592 = h2_123592->ProjectionX("h1_123592", binmin, binmax, "e");
  h1_123593 = h2_123593->ProjectionX("h1_123593", binmin, binmax, "e");
  h1_123594 = h2_123594->ProjectionX("h1_123594", binmin, binmax, "e");
  h1_123595 = h2_123595->ProjectionX("h1_123595", binmin, binmax, "e");
  h1_123597 = h2_123597->ProjectionX("h1_123597", binmin, binmax, "e");
  h1_123598 = h2_123598->ProjectionX("h1_123598", binmin, binmax, "e");
  h1_123599 = h2_123599->ProjectionX("h1_123599", binmin, binmax, "e");
  h1_123600 = h2_123600->ProjectionX("h1_123600", binmin, binmax, "e");
  h1_123601 = h2_123601->ProjectionX("h1_123601", binmin, binmax, "e");
  h1_123602 = h2_123602->ProjectionX("h1_123602", binmin, binmax, "e");
  h1_123603 = h2_123603->ProjectionX("h1_123603", binmin, binmax, "e");
  h1_123604 = h2_123604->ProjectionX("h1_123604", binmin, binmax, "e");
  h1_123605 = h2_123605->ProjectionX("h1_123605", binmin, binmax, "e");
  h1_123606 = h2_123606->ProjectionX("h1_123606", binmin, binmax, "e");
  h1_123607 = h2_123607->ProjectionX("h1_123607", binmin, binmax, "e");
  h1_123609 = h2_123609->ProjectionX("h1_123609", binmin, binmax, "e");
  h1_123611 = h2_123611->ProjectionX("h1_123611", binmin, binmax, "e");
  h1_123612 = h2_123612->ProjectionX("h1_123612", binmin, binmax, "e");
  h1_123613 = h2_123613->ProjectionX("h1_123613", binmin, binmax, "e");
  h1_123614 = h2_123614->ProjectionX("h1_123614", binmin, binmax, "e");
  h1_123615 = h2_123615->ProjectionX("h1_123615", binmin, binmax, "e");
  h1_123616 = h2_123616->ProjectionX("h1_123616", binmin, binmax, "e");
  h1_123617 = h2_123617->ProjectionX("h1_123617", binmin, binmax, "e");
  h1_123618 = h2_123618->ProjectionX("h1_123618", binmin, binmax, "e");
  h1_123619 = h2_123619->ProjectionX("h1_123619", binmin, binmax, "e");
  h1_123620 = h2_123620->ProjectionX("h1_123620", binmin, binmax, "e");
  h1_123621 = h2_123621->ProjectionX("h1_123621", binmin, binmax, "e");
  h1_123622 = h2_123622->ProjectionX("h1_123622", binmin, binmax, "e");
  h1_123623 = h2_123623->ProjectionX("h1_123623", binmin, binmax, "e");
  h1_123624 = h2_123624->ProjectionX("h1_123624", binmin, binmax, "e");
  h1_123625 = h2_123625->ProjectionX("h1_123625", binmin, binmax, "e");
  h1_123626 = h2_123626->ProjectionX("h1_123626", binmin, binmax, "e");
  h1_123628 = h2_123628->ProjectionX("h1_123628", binmin, binmax, "e");
  h1_123629 = h2_123629->ProjectionX("h1_123629", binmin, binmax, "e");
  h1_123630 = h2_123630->ProjectionX("h1_123630", binmin, binmax, "e");
  h1_123631 = h2_123631->ProjectionX("h1_123631", binmin, binmax, "e");
  h1_123632 = h2_123632->ProjectionX("h1_123632", binmin, binmax, "e");
  h1_123633 = h2_123633->ProjectionX("h1_123633", binmin, binmax, "e");
  h1_123634 = h2_123634->ProjectionX("h1_123634", binmin, binmax, "e");
  h1_123635 = h2_123635->ProjectionX("h1_123635", binmin, binmax, "e");
  h1_123636 = h2_123636->ProjectionX("h1_123636", binmin, binmax, "e");
  h1_123637 = h2_123637->ProjectionX("h1_123637", binmin, binmax, "e");
  h1_123638 = h2_123638->ProjectionX("h1_123638", binmin, binmax, "e");
  h1_123640 = h2_123640->ProjectionX("h1_123640", binmin, binmax, "e");
  h1_123641 = h2_123641->ProjectionX("h1_123641", binmin, binmax, "e");
  h1_123642 = h2_123642->ProjectionX("h1_123642", binmin, binmax, "e");
  h1_123643 = h2_123643->ProjectionX("h1_123643", binmin, binmax, "e");
  h1_123644 = h2_123644->ProjectionX("h1_123644", binmin, binmax, "e");
  h1_123645 = h2_123645->ProjectionX("h1_123645", binmin, binmax, "e");
  h1_123646 = h2_123646->ProjectionX("h1_123646", binmin, binmax, "e");
  h1_123647 = h2_123647->ProjectionX("h1_123647", binmin, binmax, "e");
  h1_123648 = h2_123648->ProjectionX("h1_123648", binmin, binmax, "e");
  h1_123649 = h2_123649->ProjectionX("h1_123649", binmin, binmax, "e");
  h1_123650 = h2_123650->ProjectionX("h1_123650", binmin, binmax, "e");
  h1_123651 = h2_123651->ProjectionX("h1_123651", binmin, binmax, "e");
  h1_123652 = h2_123652->ProjectionX("h1_123652", binmin, binmax, "e");
  h1_123653 = h2_123653->ProjectionX("h1_123653", binmin, binmax, "e");
  h1_123654 = h2_123654->ProjectionX("h1_123654", binmin, binmax, "e");
  h1_123655 = h2_123655->ProjectionX("h1_123655", binmin, binmax, "e");
  h1_123656 = h2_123656->ProjectionX("h1_123656", binmin, binmax, "e");
  h1_123657 = h2_123657->ProjectionX("h1_123657", binmin, binmax, "e");
  h1_123658 = h2_123658->ProjectionX("h1_123658", binmin, binmax, "e");
  h1_123659 = h2_123659->ProjectionX("h1_123659", binmin, binmax, "e");
  h1_123660 = h2_123660->ProjectionX("h1_123660", binmin, binmax, "e");
  h1_123661 = h2_123661->ProjectionX("h1_123661", binmin, binmax, "e");
  h1_123662 = h2_123662->ProjectionX("h1_123662", binmin, binmax, "e");
  h1_123663 = h2_123663->ProjectionX("h1_123663", binmin, binmax, "e");
  h1_123664 = h2_123664->ProjectionX("h1_123664", binmin, binmax, "e");
  h1_123665 = h2_123665->ProjectionX("h1_123665", binmin, binmax, "e");
  h1_123666 = h2_123666->ProjectionX("h1_123666", binmin, binmax, "e");
  h1_123667 = h2_123667->ProjectionX("h1_123667", binmin, binmax, "e");
  h1_123668 = h2_123668->ProjectionX("h1_123668", binmin, binmax, "e");
  h1_123669 = h2_123669->ProjectionX("h1_123669", binmin, binmax, "e");
  h1_123670 = h2_123670->ProjectionX("h1_123670", binmin, binmax, "e");
  h1_123671 = h2_123671->ProjectionX("h1_123671", binmin, binmax, "e");
  h1_123672 = h2_123672->ProjectionX("h1_123672", binmin, binmax, "e");
  h1_123673 = h2_123673->ProjectionX("h1_123673", binmin, binmax, "e");
  h1_123674 = h2_123674->ProjectionX("h1_123674", binmin, binmax, "e");
  h1_123675 = h2_123675->ProjectionX("h1_123675", binmin, binmax, "e");
  h1_123676 = h2_123676->ProjectionX("h1_123676", binmin, binmax, "e");
  h1_123677 = h2_123677->ProjectionX("h1_123677", binmin, binmax, "e");
  h1_123678 = h2_123678->ProjectionX("h1_123678", binmin, binmax, "e");
  h1_123679 = h2_123679->ProjectionX("h1_123679", binmin, binmax, "e");
  h1_123680 = h2_123680->ProjectionX("h1_123680", binmin, binmax, "e");
  h1_123682 = h2_123682->ProjectionX("h1_123682", binmin, binmax, "e");
  h1_123683 = h2_123683->ProjectionX("h1_123683", binmin, binmax, "e");
  h1_123684 = h2_123684->ProjectionX("h1_123684", binmin, binmax, "e");
  h1_123686 = h2_123686->ProjectionX("h1_123686", binmin, binmax, "e");
  h1_123687 = h2_123687->ProjectionX("h1_123687", binmin, binmax, "e");
  h1_123688 = h2_123688->ProjectionX("h1_123688", binmin, binmax, "e");
  h1_123689 = h2_123689->ProjectionX("h1_123689", binmin, binmax, "e");
  h1_123690 = h2_123690->ProjectionX("h1_123690", binmin, binmax, "e");

#ifdef  NORM  
  cout << "Normalizing histo"<<endl;
  getHistoNorm(h1_123290, h2_123290, 123290);
  getHistoNorm(h1_123291, h2_123291, 123291);
  getHistoNorm(h1_123292, h2_123292, 123292);
  getHistoNorm(h1_123293, h2_123293, 123293);
  getHistoNorm(h1_123294, h2_123294, 123294);
  getHistoNorm(h1_123295, h2_123295, 123295);
  getHistoNorm(h1_123296, h2_123296, 123296);
  getHistoNorm(h1_123297, h2_123297, 123297);
  getHistoNorm(h1_123298, h2_123298, 123298);
  getHistoNorm(h1_123299, h2_123299, 123299);
  getHistoNorm(h1_123300, h2_123300, 123300);
  getHistoNorm(h1_123301, h2_123301, 123301);
  getHistoNorm(h1_123302, h2_123302, 123302);
  getHistoNorm(h1_123303, h2_123303, 123303);
  getHistoNorm(h1_123304, h2_123304, 123304);
  getHistoNorm(h1_123305, h2_123305, 123305);
  getHistoNorm(h1_123306, h2_123306, 123306);
  getHistoNorm(h1_123307, h2_123307, 123307);
  getHistoNorm(h1_123308, h2_123308, 123308);
  getHistoNorm(h1_123309, h2_123309, 123309);
  getHistoNorm(h1_123310, h2_123310, 123310);
  getHistoNorm(h1_123311, h2_123311, 123311);
  getHistoNorm(h1_123312, h2_123312, 123312);
  getHistoNorm(h1_123313, h2_123313, 123313);
  getHistoNorm(h1_123314, h2_123314, 123314);
  getHistoNorm(h1_123315, h2_123315, 123315);
  getHistoNorm(h1_123316, h2_123316, 123316);
  getHistoNorm(h1_123317, h2_123317, 123317);
  getHistoNorm(h1_123320, h2_123320, 123320);
  getHistoNorm(h1_123321, h2_123321, 123321);
  getHistoNorm(h1_123322, h2_123322, 123322);
  getHistoNorm(h1_123323, h2_123323, 123323);
  getHistoNorm(h1_123324, h2_123324, 123324);
  getHistoNorm(h1_123325, h2_123325, 123325);
  getHistoNorm(h1_123326, h2_123326, 123326);
  getHistoNorm(h1_123327, h2_123327, 123327);
  getHistoNorm(h1_123328, h2_123328, 123328);
  getHistoNorm(h1_123329, h2_123329, 123329);
  getHistoNorm(h1_123330, h2_123330, 123330);
  getHistoNorm(h1_123331, h2_123331, 123331);
  getHistoNorm(h1_123332, h2_123332, 123332);
  getHistoNorm(h1_123333, h2_123333, 123333);
  getHistoNorm(h1_123334, h2_123334, 123334);
  getHistoNorm(h1_123335, h2_123335, 123335);
  getHistoNorm(h1_123336, h2_123336, 123336);
  getHistoNorm(h1_123337, h2_123337, 123337);
  getHistoNorm(h1_123338, h2_123338, 123338);
  getHistoNorm(h1_123339, h2_123339, 123339);
  getHistoNorm(h1_123340, h2_123340, 123340);
  getHistoNorm(h1_123341, h2_123341, 123341);
  getHistoNorm(h1_123342, h2_123342, 123342);
  getHistoNorm(h1_123343, h2_123343, 123343);
  getHistoNorm(h1_123344, h2_123344, 123344);
  getHistoNorm(h1_123345, h2_123345, 123345);
  getHistoNorm(h1_123346, h2_123346, 123346);
  getHistoNorm(h1_123347, h2_123347, 123347);
  getHistoNorm(h1_123348, h2_123348, 123348);
  getHistoNorm(h1_123349, h2_123349, 123349);
  getHistoNorm(h1_123350, h2_123350, 123350);
  getHistoNorm(h1_123351, h2_123351, 123351);
  getHistoNorm(h1_123352, h2_123352, 123352);
  getHistoNorm(h1_123353, h2_123353, 123353);
  getHistoNorm(h1_123354, h2_123354, 123354);
  getHistoNorm(h1_123355, h2_123355, 123355);
  getHistoNorm(h1_123356, h2_123356, 123356);
  getHistoNorm(h1_123357, h2_123357, 123357);
  getHistoNorm(h1_123358, h2_123358, 123358);
  getHistoNorm(h1_123359, h2_123359, 123359);
  getHistoNorm(h1_123360, h2_123360, 123360);
  getHistoNorm(h1_123361, h2_123361, 123361);
  getHistoNorm(h1_123362, h2_123362, 123362);
  getHistoNorm(h1_123363, h2_123363, 123363);
  getHistoNorm(h1_123364, h2_123364, 123364);
  getHistoNorm(h1_123365, h2_123365, 123365);
  getHistoNorm(h1_123366, h2_123366, 123366);
  getHistoNorm(h1_123367, h2_123367, 123367);
  getHistoNorm(h1_123368, h2_123368, 123368);
  getHistoNorm(h1_123369, h2_123369, 123369);
  getHistoNorm(h1_123370, h2_123370, 123370);
  getHistoNorm(h1_123371, h2_123371, 123371);
  getHistoNorm(h1_123372, h2_123372, 123372);
  getHistoNorm(h1_123373, h2_123373, 123373);
  getHistoNorm(h1_123374, h2_123374, 123374);
  getHistoNorm(h1_123375, h2_123375, 123375);
  getHistoNorm(h1_123376, h2_123376, 123376);
  getHistoNorm(h1_123377, h2_123377, 123377);
  getHistoNorm(h1_123378, h2_123378, 123378);
  getHistoNorm(h1_123379, h2_123379, 123379);
  getHistoNorm(h1_123380, h2_123380, 123380);
  getHistoNorm(h1_123381, h2_123381, 123381);
  getHistoNorm(h1_123383, h2_123383, 123383);
  getHistoNorm(h1_123384, h2_123384, 123384);
  getHistoNorm(h1_123385, h2_123385, 123385);
  getHistoNorm(h1_123386, h2_123386, 123386);
  getHistoNorm(h1_123387, h2_123387, 123387);
  getHistoNorm(h1_123388, h2_123388, 123388);
  getHistoNorm(h1_123389, h2_123389, 123389);
  getHistoNorm(h1_123390, h2_123390, 123390);
  getHistoNorm(h1_123391, h2_123391, 123391);
  getHistoNorm(h1_123392, h2_123392, 123392);
  getHistoNorm(h1_123393, h2_123393, 123393);
  getHistoNorm(h1_123394, h2_123394, 123394);
  getHistoNorm(h1_123396, h2_123396, 123396);
  getHistoNorm(h1_123397, h2_123397, 123397);
  getHistoNorm(h1_123398, h2_123398, 123398);
  getHistoNorm(h1_123399, h2_123399, 123399);
  getHistoNorm(h1_123400, h2_123400, 123400);
  getHistoNorm(h1_123401, h2_123401, 123401);
  getHistoNorm(h1_123402, h2_123402, 123402);
  getHistoNorm(h1_123403, h2_123403, 123403);
  getHistoNorm(h1_123404, h2_123404, 123404);
  getHistoNorm(h1_123405, h2_123405, 123405);
  getHistoNorm(h1_123406, h2_123406, 123406);
  getHistoNorm(h1_123407, h2_123407, 123407);
  getHistoNorm(h1_123408, h2_123408, 123408);
  getHistoNorm(h1_123409, h2_123409, 123409);
  getHistoNorm(h1_123410, h2_123410, 123410);
  getHistoNorm(h1_123411, h2_123411, 123411);
  getHistoNorm(h1_123412, h2_123412, 123412);
  getHistoNorm(h1_123413, h2_123413, 123413);
  getHistoNorm(h1_123414, h2_123414, 123414);
  getHistoNorm(h1_123415, h2_123415, 123415);
  getHistoNorm(h1_123416, h2_123416, 123416);
  getHistoNorm(h1_123417, h2_123417, 123417);
  getHistoNorm(h1_123418, h2_123418, 123418);
  getHistoNorm(h1_123419, h2_123419, 123419);
  getHistoNorm(h1_123420, h2_123420, 123420);
  getHistoNorm(h1_123422, h2_123422, 123422);
  getHistoNorm(h1_123423, h2_123423, 123423);
  getHistoNorm(h1_123424, h2_123424, 123424);
  getHistoNorm(h1_123425, h2_123425, 123425);
  getHistoNorm(h1_123426, h2_123426, 123426);
  getHistoNorm(h1_123427, h2_123427, 123427);
  getHistoNorm(h1_123428, h2_123428, 123428);
  getHistoNorm(h1_123430, h2_123430, 123430);
  getHistoNorm(h1_123431, h2_123431, 123431);
  getHistoNorm(h1_123432, h2_123432, 123432);
  getHistoNorm(h1_123433, h2_123433, 123433);
  getHistoNorm(h1_123434, h2_123434, 123434);
  getHistoNorm(h1_123435, h2_123435, 123435);
  getHistoNorm(h1_123436, h2_123436, 123436);
  getHistoNorm(h1_123437, h2_123437, 123437);
  getHistoNorm(h1_123438, h2_123438, 123438);
  getHistoNorm(h1_123439, h2_123439, 123439);
  getHistoNorm(h1_123440, h2_123440, 123440);
  getHistoNorm(h1_123441, h2_123441, 123441);
  getHistoNorm(h1_123442, h2_123442, 123442);
  getHistoNorm(h1_123443, h2_123443, 123443);
  getHistoNorm(h1_123444, h2_123444, 123444);
  getHistoNorm(h1_123445, h2_123445, 123445);
  getHistoNorm(h1_123447, h2_123447, 123447);
  getHistoNorm(h1_123448, h2_123448, 123448);
  getHistoNorm(h1_123449, h2_123449, 123449);
  getHistoNorm(h1_123450, h2_123450, 123450);
  getHistoNorm(h1_123451, h2_123451, 123451);
  getHistoNorm(h1_123452, h2_123452, 123452);
  getHistoNorm(h1_123453, h2_123453, 123453);
  getHistoNorm(h1_123454, h2_123454, 123454);
  getHistoNorm(h1_123455, h2_123455, 123455);
  getHistoNorm(h1_123456, h2_123456, 123456);
  getHistoNorm(h1_123457, h2_123457, 123457);
  getHistoNorm(h1_123458, h2_123458, 123458);
  getHistoNorm(h1_123460, h2_123460, 123460);
  getHistoNorm(h1_123461, h2_123461, 123461);
  getHistoNorm(h1_123462, h2_123462, 123462);
  getHistoNorm(h1_123463, h2_123463, 123463);
  getHistoNorm(h1_123464, h2_123464, 123464);
  getHistoNorm(h1_123465, h2_123465, 123465);
  getHistoNorm(h1_123466, h2_123466, 123466);
  getHistoNorm(h1_123467, h2_123467, 123467);
  getHistoNorm(h1_123468, h2_123468, 123468);
  getHistoNorm(h1_123469, h2_123469, 123469);
  getHistoNorm(h1_123470, h2_123470, 123470);
  getHistoNorm(h1_123471, h2_123471, 123471);
  getHistoNorm(h1_123472, h2_123472, 123472);
  getHistoNorm(h1_123473, h2_123473, 123473);
  getHistoNorm(h1_123474, h2_123474, 123474);
  getHistoNorm(h1_123475, h2_123475, 123475);
  getHistoNorm(h1_123476, h2_123476, 123476);
  getHistoNorm(h1_123477, h2_123477, 123477);
  getHistoNorm(h1_123478, h2_123478, 123478);
  getHistoNorm(h1_123479, h2_123479, 123479);
  getHistoNorm(h1_123480, h2_123480, 123480);
  getHistoNorm(h1_123481, h2_123481, 123481);
  getHistoNorm(h1_123482, h2_123482, 123482);
  getHistoNorm(h1_123483, h2_123483, 123483);
  getHistoNorm(h1_123484, h2_123484, 123484);
  getHistoNorm(h1_123485, h2_123485, 123485);
  getHistoNorm(h1_123486, h2_123486, 123486);
  getHistoNorm(h1_123487, h2_123487, 123487);
  getHistoNorm(h1_123488, h2_123488, 123488);
  getHistoNorm(h1_123489, h2_123489, 123489);
  getHistoNorm(h1_123490, h2_123490, 123490);
  getHistoNorm(h1_123491, h2_123491, 123491);
  getHistoNorm(h1_123492, h2_123492, 123492);
  getHistoNorm(h1_123493, h2_123493, 123493);
  getHistoNorm(h1_123494, h2_123494, 123494);
  getHistoNorm(h1_123495, h2_123495, 123495);
  getHistoNorm(h1_123496, h2_123496, 123496);
  getHistoNorm(h1_123497, h2_123497, 123497);
  getHistoNorm(h1_123498, h2_123498, 123498);
  getHistoNorm(h1_123499, h2_123499, 123499);
  getHistoNorm(h1_123501, h2_123501, 123501);
  getHistoNorm(h1_123502, h2_123502, 123502);
  getHistoNorm(h1_123503, h2_123503, 123503);
  getHistoNorm(h1_123504, h2_123504, 123504);
  getHistoNorm(h1_123505, h2_123505, 123505);
  getHistoNorm(h1_123506, h2_123506, 123506);
  getHistoNorm(h1_123507, h2_123507, 123507);
  getHistoNorm(h1_123508, h2_123508, 123508);
  getHistoNorm(h1_123509, h2_123509, 123509);
  getHistoNorm(h1_123510, h2_123510, 123510);
  getHistoNorm(h1_123511, h2_123511, 123511);
  getHistoNorm(h1_123512, h2_123512, 123512);
  getHistoNorm(h1_123513, h2_123513, 123513);
  getHistoNorm(h1_123514, h2_123514, 123514);
  getHistoNorm(h1_123516, h2_123516, 123516);
  getHistoNorm(h1_123517, h2_123517, 123517);
  getHistoNorm(h1_123518, h2_123518, 123518);
  getHistoNorm(h1_123519, h2_123519, 123519);
  getHistoNorm(h1_123520, h2_123520, 123520);
  getHistoNorm(h1_123521, h2_123521, 123521);
  getHistoNorm(h1_123522, h2_123522, 123522);
  getHistoNorm(h1_123523, h2_123523, 123523);
  getHistoNorm(h1_123524, h2_123524, 123524);
  getHistoNorm(h1_123526, h2_123526, 123526);
  getHistoNorm(h1_123527, h2_123527, 123527);
  getHistoNorm(h1_123528, h2_123528, 123528);
  getHistoNorm(h1_123529, h2_123529, 123529);
  getHistoNorm(h1_123530, h2_123530, 123530);
  getHistoNorm(h1_123531, h2_123531, 123531);
  getHistoNorm(h1_123533, h2_123533, 123533);
  getHistoNorm(h1_123534, h2_123534, 123534);
  getHistoNorm(h1_123535, h2_123535, 123535);
  getHistoNorm(h1_123536, h2_123536, 123536);
  getHistoNorm(h1_123537, h2_123537, 123537);
  getHistoNorm(h1_123538, h2_123538, 123538);
  getHistoNorm(h1_123539, h2_123539, 123539);
  getHistoNorm(h1_123540, h2_123540, 123540);
  getHistoNorm(h1_123541, h2_123541, 123541);
  getHistoNorm(h1_123542, h2_123542, 123542);
  getHistoNorm(h1_123543, h2_123543, 123543);
  getHistoNorm(h1_123544, h2_123544, 123544);
  getHistoNorm(h1_123545, h2_123545, 123545);
  getHistoNorm(h1_123546, h2_123546, 123546);
  getHistoNorm(h1_123547, h2_123547, 123547);
  getHistoNorm(h1_123548, h2_123548, 123548);
  getHistoNorm(h1_123549, h2_123549, 123549);
  getHistoNorm(h1_123550, h2_123550, 123550);
  getHistoNorm(h1_123551, h2_123551, 123551);
  getHistoNorm(h1_123552, h2_123552, 123552);
  getHistoNorm(h1_123553, h2_123553, 123553);
  getHistoNorm(h1_123554, h2_123554, 123554);
  getHistoNorm(h1_123555, h2_123555, 123555);
  getHistoNorm(h1_123556, h2_123556, 123556);
  getHistoNorm(h1_123557, h2_123557, 123557);
  getHistoNorm(h1_123558, h2_123558, 123558);
  getHistoNorm(h1_123559, h2_123559, 123559);
  getHistoNorm(h1_123560, h2_123560, 123560);
  getHistoNorm(h1_123561, h2_123561, 123561);
  getHistoNorm(h1_123562, h2_123562, 123562);
  getHistoNorm(h1_123563, h2_123563, 123563);
  getHistoNorm(h1_123564, h2_123564, 123564);
  getHistoNorm(h1_123565, h2_123565, 123565);
  getHistoNorm(h1_123566, h2_123566, 123566);
  getHistoNorm(h1_123567, h2_123567, 123567);
  getHistoNorm(h1_123568, h2_123568, 123568);
  getHistoNorm(h1_123569, h2_123569, 123569);
  getHistoNorm(h1_123570, h2_123570, 123570);
  getHistoNorm(h1_123571, h2_123571, 123571);
  getHistoNorm(h1_123572, h2_123572, 123572);
  getHistoNorm(h1_123573, h2_123573, 123573);
  getHistoNorm(h1_123574, h2_123574, 123574);
  getHistoNorm(h1_123575, h2_123575, 123575);
  getHistoNorm(h1_123576, h2_123576, 123576);
  getHistoNorm(h1_123577, h2_123577, 123577);
  getHistoNorm(h1_123578, h2_123578, 123578);
  getHistoNorm(h1_123579, h2_123579, 123579);
  getHistoNorm(h1_123580, h2_123580, 123580);
  getHistoNorm(h1_123581, h2_123581, 123581);
  getHistoNorm(h1_123582, h2_123582, 123582);
  getHistoNorm(h1_123583, h2_123583, 123583);
  getHistoNorm(h1_123584, h2_123584, 123584);
  getHistoNorm(h1_123585, h2_123585, 123585);
  getHistoNorm(h1_123586, h2_123586, 123586);
  getHistoNorm(h1_123587, h2_123587, 123587);
  getHistoNorm(h1_123588, h2_123588, 123588);
  getHistoNorm(h1_123589, h2_123589, 123589);
  getHistoNorm(h1_123590, h2_123590, 123590);
  getHistoNorm(h1_123591, h2_123591, 123591);
  getHistoNorm(h1_123592, h2_123592, 123592);
  getHistoNorm(h1_123593, h2_123593, 123593);
  getHistoNorm(h1_123594, h2_123594, 123594);
  getHistoNorm(h1_123595, h2_123595, 123595);
  getHistoNorm(h1_123597, h2_123597, 123597);
  getHistoNorm(h1_123598, h2_123598, 123598);
  getHistoNorm(h1_123599, h2_123599, 123599);
  getHistoNorm(h1_123600, h2_123600, 123600);
  getHistoNorm(h1_123601, h2_123601, 123601);
  getHistoNorm(h1_123602, h2_123602, 123602);
  getHistoNorm(h1_123603, h2_123603, 123603);
  getHistoNorm(h1_123604, h2_123604, 123604);
  getHistoNorm(h1_123605, h2_123605, 123605);
  getHistoNorm(h1_123606, h2_123606, 123606);
  getHistoNorm(h1_123607, h2_123607, 123607);
  getHistoNorm(h1_123609, h2_123609, 123609);
  getHistoNorm(h1_123611, h2_123611, 123611);
  getHistoNorm(h1_123612, h2_123612, 123612);
  getHistoNorm(h1_123613, h2_123613, 123613);
  getHistoNorm(h1_123614, h2_123614, 123614);
  getHistoNorm(h1_123615, h2_123615, 123615);
  getHistoNorm(h1_123616, h2_123616, 123616);
  getHistoNorm(h1_123617, h2_123617, 123617);
  getHistoNorm(h1_123618, h2_123618, 123618);
  getHistoNorm(h1_123619, h2_123619, 123619);
  getHistoNorm(h1_123620, h2_123620, 123620);
  getHistoNorm(h1_123621, h2_123621, 123621);
  getHistoNorm(h1_123622, h2_123622, 123622);
  getHistoNorm(h1_123623, h2_123623, 123623);
  getHistoNorm(h1_123624, h2_123624, 123624);
  getHistoNorm(h1_123625, h2_123625, 123625);
  getHistoNorm(h1_123626, h2_123626, 123626);
  getHistoNorm(h1_123628, h2_123628, 123628);
  getHistoNorm(h1_123629, h2_123629, 123629);
  getHistoNorm(h1_123630, h2_123630, 123630);
  getHistoNorm(h1_123631, h2_123631, 123631);
  getHistoNorm(h1_123632, h2_123632, 123632);
  getHistoNorm(h1_123633, h2_123633, 123633);
  getHistoNorm(h1_123634, h2_123634, 123634);
  getHistoNorm(h1_123635, h2_123635, 123635);
  getHistoNorm(h1_123636, h2_123636, 123636);
  getHistoNorm(h1_123637, h2_123637, 123637);
  getHistoNorm(h1_123638, h2_123638, 123638);
  getHistoNorm(h1_123640, h2_123640, 123640);
  getHistoNorm(h1_123641, h2_123641, 123641);
  getHistoNorm(h1_123642, h2_123642, 123642);
  getHistoNorm(h1_123643, h2_123643, 123643);
  getHistoNorm(h1_123644, h2_123644, 123644);
  getHistoNorm(h1_123645, h2_123645, 123645);
  getHistoNorm(h1_123646, h2_123646, 123646);
  getHistoNorm(h1_123647, h2_123647, 123647);
  getHistoNorm(h1_123648, h2_123648, 123648);
  getHistoNorm(h1_123649, h2_123649, 123649);
  getHistoNorm(h1_123650, h2_123650, 123650);
  getHistoNorm(h1_123651, h2_123651, 123651);
  getHistoNorm(h1_123652, h2_123652, 123652);
  getHistoNorm(h1_123653, h2_123653, 123653);
  getHistoNorm(h1_123654, h2_123654, 123654);
  getHistoNorm(h1_123655, h2_123655, 123655);
  getHistoNorm(h1_123656, h2_123656, 123656);
  getHistoNorm(h1_123657, h2_123657, 123657);
  getHistoNorm(h1_123658, h2_123658, 123658);
  getHistoNorm(h1_123659, h2_123659, 123659);
  getHistoNorm(h1_123660, h2_123660, 123660);
  getHistoNorm(h1_123661, h2_123661, 123661);
  getHistoNorm(h1_123662, h2_123662, 123662);
  getHistoNorm(h1_123663, h2_123663, 123663);
  getHistoNorm(h1_123664, h2_123664, 123664);
  getHistoNorm(h1_123665, h2_123665, 123665);
  getHistoNorm(h1_123666, h2_123666, 123666);
  getHistoNorm(h1_123667, h2_123667, 123667);
  getHistoNorm(h1_123668, h2_123668, 123668);
  getHistoNorm(h1_123669, h2_123669, 123669);
  getHistoNorm(h1_123670, h2_123670, 123670);
  getHistoNorm(h1_123671, h2_123671, 123671);
  getHistoNorm(h1_123672, h2_123672, 123672);
  getHistoNorm(h1_123673, h2_123673, 123673);
  getHistoNorm(h1_123674, h2_123674, 123674);
  getHistoNorm(h1_123675, h2_123675, 123675);
  getHistoNorm(h1_123676, h2_123676, 123676);
  getHistoNorm(h1_123677, h2_123677, 123677);
  getHistoNorm(h1_123678, h2_123678, 123678);
  getHistoNorm(h1_123679, h2_123679, 123679);
  getHistoNorm(h1_123680, h2_123680, 123680);
  getHistoNorm(h1_123682, h2_123682, 123682);
  getHistoNorm(h1_123683, h2_123683, 123683);
  getHistoNorm(h1_123684, h2_123684, 123684);
  getHistoNorm(h1_123686, h2_123686, 123686);
  getHistoNorm(h1_123687, h2_123687, 123687);
  getHistoNorm(h1_123688, h2_123688, 123688);
  getHistoNorm(h1_123689, h2_123689, 123689);
  getHistoNorm(h1_123690, h2_123690, 123690);
#else
 cout << "NORMALIZATION SWITCHED OFF: no good results for physics!!!"<<endl;
#endif // NORM
#endif //H2D
#endif //MSUGRA


#ifdef PHENO                                    //PHENO

#ifdef H1D
  h1_114901  = (TH1I*)file_114901->Get(histo_string) ; 
  h1_114902  = (TH1I*)file_114902->Get(histo_string) ;
  h1_114903  = (TH1I*)file_114903->Get(histo_string) ;
  h1_114904  = (TH1I*)file_114904->Get(histo_string) ;
  h1_114905  = (TH1I*)file_114905->Get(histo_string) ;
  h1_114906  = (TH1I*)file_114906->Get(histo_string) ;
  h1_114907  = (TH1I*)file_114907->Get(histo_string) ;
  h1_114908  = (TH1I*)file_114908->Get(histo_string) ;
  h1_114909  = (TH1I*)file_114909->Get(histo_string) ;
  h1_114910  = (TH1I*)file_114910->Get(histo_string) ;
  h1_114911  = (TH1I*)file_114911->Get(histo_string) ;
  h1_114912  = (TH1I*)file_114912->Get(histo_string) ;
  h1_114913  = (TH1I*)file_114913->Get(histo_string) ;
  h1_114914  = (TH1I*)file_114914->Get(histo_string) ;
  h1_114915  = (TH1I*)file_114915->Get(histo_string) ;
  h1_114916  = (TH1I*)file_114916->Get(histo_string) ;
  h1_114917  = (TH1I*)file_114917->Get(histo_string) ;
  h1_114918  = (TH1I*)file_114918->Get(histo_string) ;
  h1_114919  = (TH1I*)file_114919->Get(histo_string) ;
  h1_114920  = (TH1I*)file_114920->Get(histo_string) ;
  h1_114921  = (TH1I*)file_114921->Get(histo_string) ;
  h1_114922  = (TH1I*)file_114922->Get(histo_string) ;
  h1_114923  = (TH1I*)file_114923->Get(histo_string) ;
  h1_114924  = (TH1I*)file_114924->Get(histo_string) ;
  h1_114925  = (TH1I*)file_114925->Get(histo_string) ;
  h1_114926  = (TH1I*)file_114926->Get(histo_string) ;
  h1_114927  = (TH1I*)file_114927->Get(histo_string) ;
  h1_114928  = (TH1I*)file_114928->Get(histo_string) ;
  h1_114929  = (TH1I*)file_114929->Get(histo_string) ;
  h1_114930  = (TH1I*)file_114930->Get(histo_string) ;
  h1_114931  = (TH1I*)file_114931->Get(histo_string) ;
  h1_114932  = (TH1I*)file_114932->Get(histo_string) ;
  h1_114933  = (TH1I*)file_114933->Get(histo_string) ;
  h1_114934  = (TH1I*)file_114934->Get(histo_string) ;
  h1_114935  = (TH1I*)file_114935->Get(histo_string) ;
  h1_114936  = (TH1I*)file_114936->Get(histo_string) ;
  h1_114937  = (TH1I*)file_114937->Get(histo_string) ;
  h1_114938  = (TH1I*)file_114938->Get(histo_string) ;
  h1_114939  = (TH1I*)file_114939->Get(histo_string) ;
  h1_114940  = (TH1I*)file_114940->Get(histo_string) ;
  h1_114941  = (TH1I*)file_114941->Get(histo_string) ;
  h1_114942  = (TH1I*)file_114942->Get(histo_string) ;
  h1_114943  = (TH1I*)file_114943->Get(histo_string) ;
  h1_114944  = (TH1I*)file_114944->Get(histo_string) ;
  h1_114945  = (TH1I*)file_114945->Get(histo_string) ;
  h1_114946  = (TH1I*)file_114946->Get(histo_string) ;
  h1_114947  = (TH1I*)file_114947->Get(histo_string) ;
  h1_114948  = (TH1I*)file_114948->Get(histo_string) ;
  h1_114949  = (TH1I*)file_114949->Get(histo_string) ;
  h1_114950  = (TH1I*)file_114950->Get(histo_string) ;
  h1_114951  = (TH1I*)file_114951->Get(histo_string) ;
  h1_114952  = (TH1I*)file_114952->Get(histo_string) ;
  h1_114953  = (TH1I*)file_114953->Get(histo_string) ;
  h1_114954  = (TH1I*)file_114954->Get(histo_string) ;
  h1_114955  = (TH1I*)file_114955->Get(histo_string) ;
  h1_114956  = (TH1I*)file_114956->Get(histo_string) ;
  h1_114957  = (TH1I*)file_114957->Get(histo_string) ;
  h1_114958  = (TH1I*)file_114958->Get(histo_string) ;
  h1_114959  = (TH1I*)file_114959->Get(histo_string) ;
  h1_114960  = (TH1I*)file_114960->Get(histo_string) ;
  h1_114961  = (TH1I*)file_114961->Get(histo_string) ;
  h1_114962  = (TH1I*)file_114962->Get(histo_string) ;
  h1_114963  = (TH1I*)file_114963->Get(histo_string) ;
  h1_114964  = (TH1I*)file_114964->Get(histo_string) ;
  h1_114965  = (TH1I*)file_114965->Get(histo_string) ;
  h1_114966  = (TH1I*)file_114966->Get(histo_string) ;
  h1_114967  = (TH1I*)file_114967->Get(histo_string) ;
  h1_114968  = (TH1I*)file_114968->Get(histo_string) ;
  h1_114969  = (TH1I*)file_114969->Get(histo_string) ;
  h1_114970  = (TH1I*)file_114970->Get(histo_string) ;
  h1_114971  = (TH1I*)file_114971->Get(histo_string) ;
  h1_114972  = (TH1I*)file_114972->Get(histo_string) ;
  h1_114973  = (TH1I*)file_114973->Get(histo_string) ;
  h1_114974  = (TH1I*)file_114974->Get(histo_string) ;
  h1_114975  = (TH1I*)file_114975->Get(histo_string) ;
  h1_114976  = (TH1I*)file_114976->Get(histo_string) ;
  h1_114977  = (TH1I*)file_114977->Get(histo_string) ;
  h1_114978  = (TH1I*)file_114978->Get(histo_string) ;
  h1_114979  = (TH1I*)file_114979->Get(histo_string) ;
  h1_114980  = (TH1I*)file_114980->Get(histo_string) ;
  h1_114981  = (TH1I*)file_114981->Get(histo_string) ;
  h1_114982  = (TH1I*)file_114982->Get(histo_string) ;
  h1_114983  = (TH1I*)file_114983->Get(histo_string) ;
  h1_114984  = (TH1I*)file_114984->Get(histo_string) ;
  h1_114985  = (TH1I*)file_114985->Get(histo_string) ;
  h1_114986  = (TH1I*)file_114986->Get(histo_string) ;
  h1_114987  = (TH1I*)file_114987->Get(histo_string) ;
  h1_114988  = (TH1I*)file_114988->Get(histo_string) ;
  h1_114989  = (TH1I*)file_114989->Get(histo_string) ;
  h1_114990  = (TH1I*)file_114990->Get(histo_string) ;
  h1_114991  = (TH1I*)file_114991->Get(histo_string) ;
  h1_114992  = (TH1I*)file_114992->Get(histo_string) ;
  h1_114993  = (TH1I*)file_114993->Get(histo_string) ;
  h1_114994  = (TH1I*)file_114994->Get(histo_string) ;
  h1_114995  = (TH1I*)file_114995->Get(histo_string) ;
  h1_114996  = (TH1I*)file_114996->Get(histo_string) ;
#endif
#ifdef H2D
  h2_114901  = (TH2F*)file_114901->Get(histo_string) ; 
  h2_114902  = (TH2F*)file_114902->Get(histo_string) ;
  h2_114903  = (TH2F*)file_114903->Get(histo_string) ;
  h2_114904  = (TH2F*)file_114904->Get(histo_string) ;
  h2_114905  = (TH2F*)file_114905->Get(histo_string) ;
  h2_114906  = (TH2F*)file_114906->Get(histo_string) ;
  h2_114907  = (TH2F*)file_114907->Get(histo_string) ;
  h2_114908  = (TH2F*)file_114908->Get(histo_string) ;
  h2_114909  = (TH2F*)file_114909->Get(histo_string) ;
  h2_114910  = (TH2F*)file_114910->Get(histo_string) ;
  h2_114911  = (TH2F*)file_114911->Get(histo_string) ;
  h2_114912  = (TH2F*)file_114912->Get(histo_string) ;
  h2_114913  = (TH2F*)file_114913->Get(histo_string) ;
  h2_114914  = (TH2F*)file_114914->Get(histo_string) ;
  h2_114915  = (TH2F*)file_114915->Get(histo_string) ;
  h2_114916  = (TH2F*)file_114916->Get(histo_string) ;
  h2_114917  = (TH2F*)file_114917->Get(histo_string) ;
  h2_114918  = (TH2F*)file_114918->Get(histo_string) ;
  h2_114919  = (TH2F*)file_114919->Get(histo_string) ;
  h2_114920  = (TH2F*)file_114920->Get(histo_string) ;
  h2_114921  = (TH2F*)file_114921->Get(histo_string) ;
  h2_114922  = (TH2F*)file_114922->Get(histo_string) ;
  h2_114923  = (TH2F*)file_114923->Get(histo_string) ;
  h2_114924  = (TH2F*)file_114924->Get(histo_string) ;
  h2_114925  = (TH2F*)file_114925->Get(histo_string) ;
  h2_114926  = (TH2F*)file_114926->Get(histo_string) ;
  h2_114927  = (TH2F*)file_114927->Get(histo_string) ;
  h2_114928  = (TH2F*)file_114928->Get(histo_string) ;
  h2_114929  = (TH2F*)file_114929->Get(histo_string) ;
  h2_114930  = (TH2F*)file_114930->Get(histo_string) ;
  h2_114931  = (TH2F*)file_114931->Get(histo_string) ;
  h2_114932  = (TH2F*)file_114932->Get(histo_string) ;
  h2_114933  = (TH2F*)file_114933->Get(histo_string) ;
  h2_114934  = (TH2F*)file_114934->Get(histo_string) ;
  h2_114935  = (TH2F*)file_114935->Get(histo_string) ;
  h2_114936  = (TH2F*)file_114936->Get(histo_string) ;
  h2_114937  = (TH2F*)file_114937->Get(histo_string) ;
  h2_114938  = (TH2F*)file_114938->Get(histo_string) ;
  h2_114939  = (TH2F*)file_114939->Get(histo_string) ;
  h2_114940  = (TH2F*)file_114940->Get(histo_string) ;
  h2_114941  = (TH2F*)file_114941->Get(histo_string) ;
  h2_114942  = (TH2F*)file_114942->Get(histo_string) ;
  h2_114943  = (TH2F*)file_114943->Get(histo_string) ;
  h2_114944  = (TH2F*)file_114944->Get(histo_string) ;
  h2_114945  = (TH2F*)file_114945->Get(histo_string) ;
  h2_114946  = (TH2F*)file_114946->Get(histo_string) ;
  h2_114947  = (TH2F*)file_114947->Get(histo_string) ;
  h2_114948  = (TH2F*)file_114948->Get(histo_string) ;
  h2_114949  = (TH2F*)file_114949->Get(histo_string) ;
  h2_114950  = (TH2F*)file_114950->Get(histo_string) ;
  h2_114951  = (TH2F*)file_114951->Get(histo_string) ;
  h2_114952  = (TH2F*)file_114952->Get(histo_string) ;
  h2_114953  = (TH2F*)file_114953->Get(histo_string) ;
  h2_114954  = (TH2F*)file_114954->Get(histo_string) ;
  h2_114955  = (TH2F*)file_114955->Get(histo_string) ;
  h2_114956  = (TH2F*)file_114956->Get(histo_string) ;
  h2_114957  = (TH2F*)file_114957->Get(histo_string) ;
  h2_114958  = (TH2F*)file_114958->Get(histo_string) ;
  h2_114959  = (TH2F*)file_114959->Get(histo_string) ;
  h2_114960  = (TH2F*)file_114960->Get(histo_string) ;
  h2_114961  = (TH2F*)file_114961->Get(histo_string) ;
  h2_114962  = (TH2F*)file_114962->Get(histo_string) ;
  h2_114963  = (TH2F*)file_114963->Get(histo_string) ;
  h2_114964  = (TH2F*)file_114964->Get(histo_string) ;
  h2_114965  = (TH2F*)file_114965->Get(histo_string) ;
  h2_114966  = (TH2F*)file_114966->Get(histo_string) ;
  h2_114967  = (TH2F*)file_114967->Get(histo_string) ;
  h2_114968  = (TH2F*)file_114968->Get(histo_string) ;
  h2_114969  = (TH2F*)file_114969->Get(histo_string) ;
  h2_114970  = (TH2F*)file_114970->Get(histo_string) ;
  h2_114971  = (TH2F*)file_114971->Get(histo_string) ;
  h2_114972  = (TH2F*)file_114972->Get(histo_string) ;
  h2_114973  = (TH2F*)file_114973->Get(histo_string) ;
  h2_114974  = (TH2F*)file_114974->Get(histo_string) ;
  h2_114975  = (TH2F*)file_114975->Get(histo_string) ;
  h2_114976  = (TH2F*)file_114976->Get(histo_string) ;
  h2_114977  = (TH2F*)file_114977->Get(histo_string) ;
  h2_114978  = (TH2F*)file_114978->Get(histo_string) ;
  h2_114979  = (TH2F*)file_114979->Get(histo_string) ;
  h2_114980  = (TH2F*)file_114980->Get(histo_string) ;
  h2_114981  = (TH2F*)file_114981->Get(histo_string) ;
  h2_114982  = (TH2F*)file_114982->Get(histo_string) ;
  h2_114983  = (TH2F*)file_114983->Get(histo_string) ;
  h2_114984  = (TH2F*)file_114984->Get(histo_string) ;
  h2_114985  = (TH2F*)file_114985->Get(histo_string) ;
  h2_114986  = (TH2F*)file_114986->Get(histo_string) ;
  h2_114987  = (TH2F*)file_114987->Get(histo_string) ;
  h2_114988  = (TH2F*)file_114988->Get(histo_string) ;
  h2_114989  = (TH2F*)file_114989->Get(histo_string) ;
  h2_114990  = (TH2F*)file_114990->Get(histo_string) ;
  h2_114991  = (TH2F*)file_114991->Get(histo_string) ;
  h2_114992  = (TH2F*)file_114992->Get(histo_string) ;
  h2_114993  = (TH2F*)file_114993->Get(histo_string) ;
  h2_114994  = (TH2F*)file_114994->Get(histo_string) ;
  h2_114995  = (TH2F*)file_114995->Get(histo_string) ;
  h2_114996  = (TH2F*)file_114996->Get(histo_string) ;
  
  h1_114901  = h2_114901->ProjectionX("h1_114901", binmin, binmax, "e");  
  h1_114902  = h2_114902->ProjectionX("h1_114902", binmin, binmax, "e"); 
  h1_114903  = h2_114903->ProjectionX("h1_114903", binmin, binmax, "e"); 
  h1_114904  = h2_114904->ProjectionX("h1_114904", binmin, binmax, "e");
  h1_114905  = h2_114905->ProjectionX("h1_114905", binmin, binmax, "e");
  h1_114906  = h2_114906->ProjectionX("h1_114906", binmin, binmax, "e");
  h1_114907  = h2_114907->ProjectionX("h1_114907", binmin, binmax, "e");
  h1_114908  = h2_114908->ProjectionX("h1_114908", binmin, binmax, "e");
  h1_114909  = h2_114909->ProjectionX("h1_114909", binmin, binmax, "e");
  h1_114910  = h2_114910->ProjectionX("h1_114910", binmin, binmax, "e");
  h1_114911  = h2_114911->ProjectionX("h1_114911", binmin, binmax, "e");
  h1_114912  = h2_114912->ProjectionX("h1_114912", binmin, binmax, "e");
  h1_114913  = h2_114913->ProjectionX("h1_114913", binmin, binmax, "e");
  h1_114914  = h2_114914->ProjectionX("h1_114914", binmin, binmax, "e");
  h1_114915  = h2_114915->ProjectionX("h1_114915", binmin, binmax, "e");
  h1_114916  = h2_114916->ProjectionX("h1_114916", binmin, binmax, "e");
  h1_114917  = h2_114917->ProjectionX("h1_114917", binmin, binmax, "e");
  h1_114918  = h2_114918->ProjectionX("h1_114918", binmin, binmax, "e");
  h1_114919  = h2_114919->ProjectionX("h1_114919", binmin, binmax, "e");
  h1_114920  = h2_114920->ProjectionX("h1_114920", binmin, binmax, "e");
  h1_114921  = h2_114921->ProjectionX("h1_114921", binmin, binmax, "e");
  h1_114922  = h2_114922->ProjectionX("h1_114922", binmin, binmax, "e");
  h1_114923  = h2_114923->ProjectionX("h1_114923", binmin, binmax, "e");
  h1_114924  = h2_114924->ProjectionX("h1_114924", binmin, binmax, "e");
  h1_114925  = h2_114925->ProjectionX("h1_114925", binmin, binmax, "e");
  h1_114926  = h2_114926->ProjectionX("h1_114926", binmin, binmax, "e");
  h1_114927  = h2_114927->ProjectionX("h1_114927", binmin, binmax, "e");
  h1_114928  = h2_114928->ProjectionX("h1_114928", binmin, binmax, "e");
  h1_114929  = h2_114929->ProjectionX("h1_114929", binmin, binmax, "e");
  h1_114930  = h2_114930->ProjectionX("h1_114930", binmin, binmax, "e");
  h1_114931  = h2_114931->ProjectionX("h1_114931", binmin, binmax, "e");
  h1_114932  = h2_114932->ProjectionX("h1_114932", binmin, binmax, "e");
  h1_114933  = h2_114933->ProjectionX("h1_114933", binmin, binmax, "e");
  h1_114934  = h2_114934->ProjectionX("h1_114934", binmin, binmax, "e");
  h1_114935  = h2_114935->ProjectionX("h1_114935", binmin, binmax, "e");
  h1_114936  = h2_114936->ProjectionX("h1_114936", binmin, binmax, "e");
  h1_114937  = h2_114937->ProjectionX("h1_114937", binmin, binmax, "e");
  h1_114938  = h2_114938->ProjectionX("h1_114938", binmin, binmax, "e");
  h1_114939  = h2_114939->ProjectionX("h1_114939", binmin, binmax, "e");
  h1_114940  = h2_114940->ProjectionX("h1_114940", binmin, binmax, "e");
  h1_114941  = h2_114941->ProjectionX("h1_114941", binmin, binmax, "e");
  h1_114942  = h2_114942->ProjectionX("h1_114942", binmin, binmax, "e");
  h1_114943  = h2_114943->ProjectionX("h1_114943", binmin, binmax, "e");
  h1_114944  = h2_114944->ProjectionX("h1_114944", binmin, binmax, "e");
  h1_114945  = h2_114945->ProjectionX("h1_114945", binmin, binmax, "e");
  h1_114946  = h2_114946->ProjectionX("h1_114946", binmin, binmax, "e");
  h1_114947  = h2_114947->ProjectionX("h1_114947", binmin, binmax, "e");
  h1_114948  = h2_114948->ProjectionX("h1_114948", binmin, binmax, "e");
  h1_114949  = h2_114949->ProjectionX("h1_114949", binmin, binmax, "e");
  h1_114950  = h2_114950->ProjectionX("h1_114950", binmin, binmax, "e");
  h1_114951  = h2_114951->ProjectionX("h1_114951", binmin, binmax, "e");
  h1_114952  = h2_114952->ProjectionX("h1_114952", binmin, binmax, "e");
  h1_114953  = h2_114953->ProjectionX("h1_114953", binmin, binmax, "e");
  h1_114954  = h2_114954->ProjectionX("h1_114954", binmin, binmax, "e");
  h1_114955  = h2_114955->ProjectionX("h1_114955", binmin, binmax, "e");
  h1_114956  = h2_114956->ProjectionX("h1_114956", binmin, binmax, "e");
  h1_114957  = h2_114957->ProjectionX("h1_114957", binmin, binmax, "e");
  h1_114958  = h2_114958->ProjectionX("h1_114958", binmin, binmax, "e");
  h1_114959  = h2_114959->ProjectionX("h1_114959", binmin, binmax, "e");
  h1_114960  = h2_114960->ProjectionX("h1_114960", binmin, binmax, "e");
  h1_114961  = h2_114961->ProjectionX("h1_114961", binmin, binmax, "e");
  h1_114962  = h2_114962->ProjectionX("h1_114962", binmin, binmax, "e");
  h1_114963  = h2_114963->ProjectionX("h1_114963", binmin, binmax, "e");
  h1_114964  = h2_114964->ProjectionX("h1_114964", binmin, binmax, "e");
  h1_114965  = h2_114965->ProjectionX("h1_114965", binmin, binmax, "e");
  h1_114966  = h2_114966->ProjectionX("h1_114966", binmin, binmax, "e");
  h1_114967  = h2_114967->ProjectionX("h1_114967", binmin, binmax, "e");
  h1_114968  = h2_114968->ProjectionX("h1_114968", binmin, binmax, "e");
  h1_114969  = h2_114969->ProjectionX("h1_114969", binmin, binmax, "e");
  h1_114970  = h2_114970->ProjectionX("h1_114970", binmin, binmax, "e");
  h1_114971  = h2_114971->ProjectionX("h1_114971", binmin, binmax, "e");
  h1_114972  = h2_114972->ProjectionX("h1_114972", binmin, binmax, "e");
  h1_114973  = h2_114973->ProjectionX("h1_114973", binmin, binmax, "e");
  h1_114974  = h2_114974->ProjectionX("h1_114974", binmin, binmax, "e");
  h1_114975  = h2_114975->ProjectionX("h1_114975", binmin, binmax, "e");
  h1_114976  = h2_114976->ProjectionX("h1_114976", binmin, binmax, "e");
  h1_114977  = h2_114977->ProjectionX("h1_114977", binmin, binmax, "e");
  h1_114978  = h2_114978->ProjectionX("h1_114978", binmin, binmax, "e");
  h1_114979  = h2_114979->ProjectionX("h1_114979", binmin, binmax, "e");
  h1_114980  = h2_114980->ProjectionX("h1_114980", binmin, binmax, "e");
  h1_114981  = h2_114981->ProjectionX("h1_114981", binmin, binmax, "e");
  h1_114982  = h2_114982->ProjectionX("h1_114982", binmin, binmax, "e");
  h1_114983  = h2_114983->ProjectionX("h1_114983", binmin, binmax, "e");
  h1_114984  = h2_114984->ProjectionX("h1_114984", binmin, binmax, "e");
  h1_114985  = h2_114985->ProjectionX("h1_114985", binmin, binmax, "e");
  h1_114986  = h2_114986->ProjectionX("h1_114986", binmin, binmax, "e");
  h1_114987  = h2_114987->ProjectionX("h1_114987", binmin, binmax, "e");
  h1_114988  = h2_114988->ProjectionX("h1_114988", binmin, binmax, "e");
  h1_114989  = h2_114989->ProjectionX("h1_114989", binmin, binmax, "e");
  h1_114990  = h2_114990->ProjectionX("h1_114990", binmin, binmax, "e");
  h1_114991  = h2_114991->ProjectionX("h1_114991", binmin, binmax, "e");
  h1_114992  = h2_114992->ProjectionX("h1_114992", binmin, binmax, "e");
  h1_114993  = h2_114993->ProjectionX("h1_114993", binmin, binmax, "e");
  h1_114994  = h2_114994->ProjectionX("h1_114994", binmin, binmax, "e");
  h1_114995  = h2_114995->ProjectionX("h1_114995", binmin, binmax, "e");
  h1_114996  = h2_114996->ProjectionX("h1_114996", binmin, binmax, "e");  
#ifdef  NORM  
  cout << "Normalizing histo"<<endl;
  getHistoNorm(h1_114901, h2_114901, 114901);  
  getHistoNorm(h1_114902, h2_114902, 114902); 
  getHistoNorm(h1_114903, h2_114903, 114903); 
  getHistoNorm(h1_114904, h2_114904, 114904);
  getHistoNorm(h1_114905, h2_114905, 114905);
  getHistoNorm(h1_114906, h2_114906, 114906);
  getHistoNorm(h1_114907, h2_114907, 114907);
  getHistoNorm(h1_114908, h2_114908, 114908);
  getHistoNorm(h1_114909, h2_114909, 114909);
  getHistoNorm(h1_114910, h2_114910, 114910);
  getHistoNorm(h1_114911, h2_114911, 114911);
  getHistoNorm(h1_114912, h2_114912, 114912);
  getHistoNorm(h1_114913, h2_114913, 114913);
  getHistoNorm(h1_114914, h2_114914, 114914);
  getHistoNorm(h1_114915, h2_114915, 114915);
  getHistoNorm(h1_114916, h2_114916, 114916);
  getHistoNorm(h1_114917, h2_114917, 114917);
  getHistoNorm(h1_114918, h2_114918, 114918);
  getHistoNorm(h1_114919, h2_114919, 114919);
  getHistoNorm(h1_114920, h2_114920, 114920);
  getHistoNorm(h1_114921, h2_114921, 114921);
  getHistoNorm(h1_114922, h2_114922, 114922);
  getHistoNorm(h1_114923, h2_114923, 114923);
  getHistoNorm(h1_114924, h2_114924, 114924);
  getHistoNorm(h1_114925, h2_114925, 114925);
  getHistoNorm(h1_114926, h2_114926, 114926);
  getHistoNorm(h1_114927, h2_114927, 114927);
  getHistoNorm(h1_114928, h2_114928, 114928);
  getHistoNorm(h1_114929, h2_114929, 114929);
  getHistoNorm(h1_114930, h2_114930, 114930);
  getHistoNorm(h1_114931, h2_114931, 114931);
  getHistoNorm(h1_114932, h2_114932, 114932);
  getHistoNorm(h1_114933, h2_114933, 114933);
  getHistoNorm(h1_114934, h2_114934, 114934);
  getHistoNorm(h1_114935, h2_114935, 114935);
  getHistoNorm(h1_114936, h2_114936, 114936);
  getHistoNorm(h1_114937, h2_114937, 114937);
  getHistoNorm(h1_114938, h2_114938, 114938);
  getHistoNorm(h1_114939, h2_114939, 114939);
  getHistoNorm(h1_114940, h2_114940, 114940);
  getHistoNorm(h1_114941, h2_114941, 114941);
  getHistoNorm(h1_114942, h2_114942, 114942);
  getHistoNorm(h1_114943, h2_114943, 114943);
  getHistoNorm(h1_114944, h2_114944, 114944);
  getHistoNorm(h1_114945, h2_114945, 114945);
  getHistoNorm(h1_114946, h2_114946, 114946);
  getHistoNorm(h1_114947, h2_114947, 114947);
  getHistoNorm(h1_114948, h2_114948, 114948);
  getHistoNorm(h1_114949, h2_114949, 114949);
  getHistoNorm(h1_114950, h2_114950, 114950);
  getHistoNorm(h1_114951, h2_114951, 114951);
  getHistoNorm(h1_114952, h2_114952, 114952);
  getHistoNorm(h1_114953, h2_114953, 114953);
  getHistoNorm(h1_114954, h2_114954, 114954);
  getHistoNorm(h1_114955, h2_114955, 114955);
  getHistoNorm(h1_114956, h2_114956, 114956);
  getHistoNorm(h1_114957, h2_114957, 114957);
  getHistoNorm(h1_114958, h2_114958, 114958);
  getHistoNorm(h1_114959, h2_114959, 114959);
  getHistoNorm(h1_114960, h2_114960, 114960);
  getHistoNorm(h1_114961, h2_114961, 114961);
  getHistoNorm(h1_114962, h2_114962, 114962);
  getHistoNorm(h1_114963, h2_114963, 114963);
  getHistoNorm(h1_114964, h2_114964, 114964);
  getHistoNorm(h1_114965, h2_114965, 114965);
  getHistoNorm(h1_114966, h2_114966, 114966);
  getHistoNorm(h1_114967, h2_114967, 114967);
  getHistoNorm(h1_114968, h2_114968, 114968);
  getHistoNorm(h1_114969, h2_114969, 114969);
  getHistoNorm(h1_114970, h2_114970, 114970);
  getHistoNorm(h1_114971, h2_114971, 114971);
  getHistoNorm(h1_114972, h2_114972, 114972);
  getHistoNorm(h1_114973, h2_114973, 114973);
  getHistoNorm(h1_114974, h2_114974, 114974);
  getHistoNorm(h1_114975, h2_114975, 114975);
  getHistoNorm(h1_114976, h2_114976, 114976);
  getHistoNorm(h1_114977, h2_114977, 114977);
  getHistoNorm(h1_114978, h2_114978, 114978);
  getHistoNorm(h1_114979, h2_114979, 114979);
  getHistoNorm(h1_114980, h2_114980, 114980);
  getHistoNorm(h1_114981, h2_114981, 114981);
  getHistoNorm(h1_114982, h2_114982, 114982);
  getHistoNorm(h1_114983, h2_114983, 114983);
  getHistoNorm(h1_114984, h2_114984, 114984);
  getHistoNorm(h1_114985, h2_114985, 114985);
  getHistoNorm(h1_114986, h2_114986, 114986);
  getHistoNorm(h1_114987, h2_114987, 114987);
  getHistoNorm(h1_114988, h2_114988, 114988);
  getHistoNorm(h1_114989, h2_114989, 114989);
  getHistoNorm(h1_114990, h2_114990, 114990);
  getHistoNorm(h1_114991, h2_114991, 114991);
  getHistoNorm(h1_114992, h2_114992, 114992);
  getHistoNorm(h1_114993, h2_114993, 114993);
  getHistoNorm(h1_114994, h2_114994, 114994);
  getHistoNorm(h1_114995, h2_114995, 114995);
  getHistoNorm(h1_114996, h2_114996, 114996); 

#endif // NORM
#endif //H2D
#endif //PHENO

#ifdef TTBAR                                       //ttbar 
 
#ifdef H1D
  h1_105200  = (TH1I*)file_105200->Get(histo_string) ; 
  h1_105204  = (TH1I*)file_105204->Get(histo_string) ; 
#endif

#ifdef H2D
  h2_105200  = (TH2F*)file_105200 ->Get(histo_string); 
  h2_105204  = (TH2F*)file_105204 ->Get(histo_string); 
    
  h1_105200 = h2_105200->ProjectionY("h1_105200", binmin, binmax, "e");
  h1_105204 = h2_105204->ProjectionY("h1_105204", binmin, binmax, "e");
#endif
#endif //end if TTBAR

#ifdef DIBOSON                                   //Diboson
  
#ifdef H1D
  h1_105985  = (TH1I*)file_105985->Get(histo_string) ; 
  h1_105986  = (TH1I*)file_105986->Get(histo_string) ; 
  h1_105987  = (TH1I*)file_105987->Get(histo_string) ; 
#endif

#ifdef H2D
  h2_105985  = (TH2F*)file_105985 ->Get(histo_string); 
  h2_105986  = (TH2F*)file_105986 ->Get(histo_string); 
  h2_105987  = (TH2F*)file_105987 ->Get(histo_string); 
    
  h1_105985 = h2_105985 ->ProjectionY("h1_105985 ", binmin, binmax, "e");
  h1_105986 = h2_105986 ->ProjectionY("h1_105986 ", binmin, binmax, "e");
  h1_105987 = h2_105987 ->ProjectionY("h1_105987 ", binmin, binmax, "e");
#endif
#endif //end if DIBOSON

#ifdef QCDEE                                    //QCD EE

#ifdef H1D
  h1_108326  = (TH1I*)file_108326->Get(histo_string) ; 
//  h1_105759  = (TH1I*)file_105759->Get(histo_string) ; 
#endif
#ifdef H2D
  h2_108326  = (TH2F*)file_108326->Get(histo_string) ; 
  h1_108326 = h2_108326 ->ProjectionY("h1_108326 ", binmin, binmax, "e");
//  h2_105759  = (TH2F*)file_105759->Get(histo_string) ; 
//  h1_105759 = h2_105759 ->ProjectionY("h1_105759 ", binmin, binmax, "e");
#endif //QCDEE
#endif


#ifdef JX                                         //QCD JX
  
#ifdef H1D
  h1_105009  = (TH1I*)file_105009->Get(histo_string) ; 
  h1_105010  = (TH1I*)file_105010->Get(histo_string) ;
  h1_105011  = (TH1I*)file_105011->Get(histo_string) ;
  h1_105012  = (TH1I*)file_105012->Get(histo_string) ;
  h1_105013  = (TH1I*)file_105013->Get(histo_string) ;
  h1_105014  = (TH1I*)file_105014->Get(histo_string) ;
  h1_105015  = (TH1I*)file_105015->Get(histo_string) ;
#endif
#ifdef H2D
  h2_105009  = (TH2F*)file_105009->Get(histo_string) ; 
  h2_105010  = (TH2F*)file_105010->Get(histo_string) ;
  h2_105011  = (TH2F*)file_105011->Get(histo_string) ;
  h2_105012  = (TH2F*)file_105012->Get(histo_string) ;
  h2_105013  = (TH2F*)file_105013->Get(histo_string) ;
  h2_105014  = (TH2F*)file_105014->Get(histo_string) ;
  h2_105015  = (TH2F*)file_105015->Get(histo_string) ;

  h1_105009 = h2_105009->ProjectionY("h1_105009", binmin, binmax, "e"); 
  h1_105010 = h2_105010->ProjectionY("h1_105010", binmin, binmax, "e");
  h1_105011 = h2_105011->ProjectionY("h1_105011", binmin, binmax, "e");
  h1_105012 = h2_105012->ProjectionY("h1_105012", binmin, binmax, "e");
  h1_105013 = h2_105013->ProjectionY("h1_105013", binmin, binmax, "e");
  h1_105014 = h2_105014->ProjectionY("h1_105014", binmin, binmax, "e");
  h1_105015 = h2_105015->ProjectionY("h1_105015", binmin, binmax, "e");
#endif
#endif //JX

#ifdef JXMUON                        //QCD muon filtered
  
#ifdef H1D
  h1_109276  = (TH1I*)file_109276 ->Get(histo_string) ; 
  h1_109277  = (TH1I*)file_109277 ->Get(histo_string) ;
  h1_109278  = (TH1I*)file_109278 ->Get(histo_string) ;
  h1_109279  = (TH1I*)file_109279 ->Get(histo_string) ;
  h1_109280  = (TH1I*)file_109280 ->Get(histo_string) ;
  h1_109281  = (TH1I*)file_109281 ->Get(histo_string) ;
//  h1_209435  = (TH1I*)file_209435 ->Get(histo_string) ;
#endif

#ifdef H2D
  h2_109276  = (TH2F*)file_109276->Get(histo_string) ; 
  h2_109277  = (TH2F*)file_109277->Get(histo_string) ;
  h2_109278  = (TH2F*)file_109278->Get(histo_string) ;
  h2_109279  = (TH2F*)file_109279->Get(histo_string) ;
  h2_109280  = (TH2F*)file_109280->Get(histo_string) ;
  h2_109281  = (TH2F*)file_109281->Get(histo_string) ;
//  h2_209435  = (TH2F*)file_209435->Get(histo_string) ;

  h1_109276 = h2_109276->ProjectionY("h1_109276", binmin, binmax, "e"); 
  h1_109277 = h2_109277->ProjectionY("h1_109277", binmin, binmax, "e");
  h1_109278 = h2_109278->ProjectionY("h1_109278", binmin, binmax, "e");
  h1_109279 = h2_109279->ProjectionY("h1_109279", binmin, binmax, "e");
  h1_109280 = h2_109280->ProjectionY("h1_109280", binmin, binmax, "e");
  h1_109281 = h2_109281->ProjectionY("h1_109281", binmin, binmax, "e");
//  h1_209435 = h2_209435->ProjectionY("h1_209435", binmin, binmax, "e");
#endif
#endif //JXMUON


#ifdef ZJETS                                 //Zjets

#ifdef H1D
  h1_107650  = (TH1I*)file_107650->Get(histo_string) ; 
  h1_107651  = (TH1I*)file_107651->Get(histo_string) ;
  h1_107652  = (TH1I*)file_107652->Get(histo_string) ;
  h1_107653  = (TH1I*)file_107653->Get(histo_string) ;
  h1_107654  = (TH1I*)file_107654->Get(histo_string) ;
  h1_107655  = (TH1I*)file_107655->Get(histo_string) ;
  h1_107660  = (TH1I*)file_107660->Get(histo_string) ; 
  h1_107661  = (TH1I*)file_107661->Get(histo_string) ;
  h1_107662  = (TH1I*)file_107662->Get(histo_string) ;
  h1_107663  = (TH1I*)file_107663->Get(histo_string) ;
  h1_107664  = (TH1I*)file_107664->Get(histo_string) ;
  h1_107665  = (TH1I*)file_107665->Get(histo_string) ;
  h1_107670  = (TH1I*)file_107670->Get(histo_string) ; 
  h1_107671  = (TH1I*)file_107671->Get(histo_string) ;
  h1_107672  = (TH1I*)file_107672->Get(histo_string) ;
  h1_107673  = (TH1I*)file_107673->Get(histo_string) ;
  h1_107674  = (TH1I*)file_107674->Get(histo_string) ;
  h1_107675  = (TH1I*)file_107675->Get(histo_string) ;
#endif

#ifdef H2D
  h2_107650  = (TH2F*)file_107650->Get(histo_string) ; 
  h2_107651  = (TH2F*)file_107651->Get(histo_string) ;
  h2_107652  = (TH2F*)file_107652->Get(histo_string) ;
  h2_107653  = (TH2F*)file_107653->Get(histo_string) ;
  h2_107654  = (TH2F*)file_107654->Get(histo_string) ;
  h2_107655  = (TH2F*)file_107655->Get(histo_string) ;
  h2_107660  = (TH2F*)file_107660->Get(histo_string) ; 
  h2_107661  = (TH2F*)file_107661->Get(histo_string) ;
  h2_107662  = (TH2F*)file_107662->Get(histo_string) ;
  h2_107663  = (TH2F*)file_107663->Get(histo_string) ;
  h2_107664  = (TH2F*)file_107664->Get(histo_string) ;
  h2_107665  = (TH2F*)file_107665->Get(histo_string) ;
  h2_107670  = (TH2F*)file_107670->Get(histo_string) ; 
  h2_107671  = (TH2F*)file_107671->Get(histo_string) ;
  h2_107672  = (TH2F*)file_107672->Get(histo_string) ;
  h2_107673  = (TH2F*)file_107673->Get(histo_string) ;
  h2_107674  = (TH2F*)file_107674->Get(histo_string) ;
  h2_107675  = (TH2F*)file_107675->Get(histo_string) ;

  h1_107650 = h2_107650->ProjectionY("h1_107650", binmin, binmax, "e"); 
  h1_107651 = h2_107651->ProjectionY("h1_107651", binmin, binmax, "e");
  h1_107652 = h2_107652->ProjectionY("h1_107652", binmin, binmax, "e");
  h1_107653 = h2_107653->ProjectionY("h1_107653", binmin, binmax, "e");
  h1_107654 = h2_107654->ProjectionY("h1_107654", binmin, binmax, "e");
  h1_107655 = h2_107655->ProjectionY("h1_107655", binmin, binmax, "e");
  h1_107660 = h2_107660->ProjectionY("h1_107660", binmin, binmax, "e"); 
  h1_107661 = h2_107661->ProjectionY("h1_107661", binmin, binmax, "e");
  h1_107662 = h2_107662->ProjectionY("h1_107662", binmin, binmax, "e");
  h1_107663 = h2_107663->ProjectionY("h1_107663", binmin, binmax, "e");
  h1_107664 = h2_107664->ProjectionY("h1_107664", binmin, binmax, "e");
  h1_107665 = h2_107665->ProjectionY("h1_107665", binmin, binmax, "e");
  h1_107670 = h2_107670->ProjectionY("h1_107670", binmin, binmax, "e"); 
  h1_107671 = h2_107671->ProjectionY("h1_107671", binmin, binmax, "e");
  h1_107672 = h2_107672->ProjectionY("h1_107672", binmin, binmax, "e");
  h1_107673 = h2_107673->ProjectionY("h1_107673", binmin, binmax, "e");
  h1_107674 = h2_107674->ProjectionY("h1_107674", binmin, binmax, "e");
  h1_107675 = h2_107675->ProjectionY("h1_107675", binmin, binmax, "e");
#endif

#endif //ZJETS

#ifdef WJETS                             //Wjets

#ifdef H1D
  h1_107680  = (TH1I*)file_107680->Get(histo_string) ; 
  h1_107681  = (TH1I*)file_107681->Get(histo_string) ;
  h1_107682  = (TH1I*)file_107682->Get(histo_string) ;
  h1_107683  = (TH1I*)file_107683->Get(histo_string) ;
  h1_107684  = (TH1I*)file_107684->Get(histo_string) ;
  h1_107685  = (TH1I*)file_107685->Get(histo_string) ;

  h1_107690  = (TH1I*)file_107690->Get(histo_string) ; 
  h1_107691  = (TH1I*)file_107691->Get(histo_string) ;
  h1_107692  = (TH1I*)file_107692->Get(histo_string) ;
  h1_107693  = (TH1I*)file_107693->Get(histo_string) ;
  h1_107694  = (TH1I*)file_107694->Get(histo_string) ;
  h1_107695  = (TH1I*)file_107695->Get(histo_string) ;

  h1_107700  = (TH1I*)file_107700->Get(histo_string) ; 
  h1_107701  = (TH1I*)file_107701->Get(histo_string) ;
  h1_107702  = (TH1I*)file_107702->Get(histo_string) ;
  h1_107703  = (TH1I*)file_107703->Get(histo_string) ;
  h1_107704  = (TH1I*)file_107704->Get(histo_string) ;
  h1_107705  = (TH1I*)file_107705->Get(histo_string) ;

#ifdef WBB                             //WBB
  h1_106280  = (TH1I*)file_106280->Get(histo_string) ; 
  h1_106281  = (TH1I*)file_106281->Get(histo_string) ; 
  h1_106282  = (TH1I*)file_106282->Get(histo_string) ; 
  h1_106283  = (TH1I*)file_106283->Get(histo_string) ; 
#endif

#endif

#ifdef H2D

  h2_107680  = (TH2F*)file_107680->Get(histo_string) ; 
  h2_107681  = (TH2F*)file_107681->Get(histo_string) ;
  h2_107682  = (TH2F*)file_107682->Get(histo_string) ;
  h2_107683  = (TH2F*)file_107683->Get(histo_string) ;
  h2_107684  = (TH2F*)file_107684->Get(histo_string) ;
  h2_107685  = (TH2F*)file_107685->Get(histo_string) ;

  h2_107690  = (TH2F*)file_107690->Get(histo_string) ; 
  h2_107691  = (TH2F*)file_107691->Get(histo_string) ;
  h2_107692  = (TH2F*)file_107692->Get(histo_string) ;
  h2_107693  = (TH2F*)file_107693->Get(histo_string) ;
  h2_107694  = (TH2F*)file_107694->Get(histo_string) ;
  h2_107695  = (TH2F*)file_107695->Get(histo_string) ;

  h2_107700  = (TH2F*)file_107700->Get(histo_string) ; 
  h2_107701  = (TH2F*)file_107701->Get(histo_string) ;
  h2_107702  = (TH2F*)file_107702->Get(histo_string) ;
  h2_107703  = (TH2F*)file_107703->Get(histo_string) ;
  h2_107704  = (TH2F*)file_107704->Get(histo_string) ;
  h2_107705  = (TH2F*)file_107705->Get(histo_string) ;

  h1_107680 = h2_107680->ProjectionY("h1_107680", binmin, binmax, "e"); 
  h1_107681 = h2_107681->ProjectionY("h1_107681", binmin, binmax, "e");
  h1_107682 = h2_107682->ProjectionY("h1_107682", binmin, binmax, "e");
  h1_107683 = h2_107683->ProjectionY("h1_107683", binmin, binmax, "e");
  h1_107684 = h2_107684->ProjectionY("h1_107684", binmin, binmax, "e");
  h1_107685 = h2_107685->ProjectionY("h1_107685", binmin, binmax, "e");

  h1_107690 = h2_107690->ProjectionY("h1_107690", binmin, binmax, "e"); 
  h1_107691 = h2_107691->ProjectionY("h1_107691", binmin, binmax, "e");
  h1_107692 = h2_107692->ProjectionY("h1_107692", binmin, binmax, "e");
  h1_107693 = h2_107693->ProjectionY("h1_107693", binmin, binmax, "e");
  h1_107694 = h2_107694->ProjectionY("h1_107694", binmin, binmax, "e");
  h1_107695 = h2_107695->ProjectionY("h1_107695", binmin, binmax, "e");

  h1_107700 = h2_107700->ProjectionY("h1_107700", binmin, binmax, "e"); 
  h1_107701 = h2_107701->ProjectionY("h1_107701", binmin, binmax, "e");
  h1_107702 = h2_107702->ProjectionY("h1_107702", binmin, binmax, "e");
  h1_107703 = h2_107703->ProjectionY("h1_107703", binmin, binmax, "e");
  h1_107704 = h2_107704->ProjectionY("h1_107704", binmin, binmax, "e");
  h1_107705 = h2_107705->ProjectionY("h1_107705", binmin, binmax, "e");

//Wbb

#ifdef WBB                             //WBB
  h2_106280  = (TH2F*)file_106280->Get(histo_string) ; 
  h2_106281  = (TH2F*)file_106281->Get(histo_string) ;
  h2_106282  = (TH2F*)file_106282->Get(histo_string) ;
  h2_106283  = (TH2F*)file_106283->Get(histo_string) ;

  h1_106280 = h2_106280->ProjectionY("h1_106280", binmin, binmax, "e"); 
  h1_106281 = h2_106281->ProjectionY("h1_106281", binmin, binmax, "e");
  h1_106282 = h2_106282->ProjectionY("h1_106282", binmin, binmax, "e");
  h1_106283 = h2_106283->ProjectionY("h1_106283", binmin, binmax, "e");
#endif

#endif
#endif //WJETS


#ifdef DY                                  //Drell yan

#ifdef H1D
  h1_108319  = (TH1I*)file_108319->Get(histo_string) ;
  h1_108320  = (TH1I*)file_108320->Get(histo_string) ;
  h1_108321  = (TH1I*)file_108321->Get(histo_string) ;
  h1_108322  = (TH1I*)file_108322->Get(histo_string) ;
#endif


#ifdef H2D
  h2_108319  = (TH2F*)file_108319->Get(histo_string) ; 
  h2_108320  = (TH2F*)file_108320->Get(histo_string) ;
  h2_108321  = (TH2F*)file_108321->Get(histo_string) ;
  h2_108322  = (TH2F*)file_108322->Get(histo_string) ;

  h1_108319 = h2_108319->ProjectionY("h1_108319", binmin, binmax, "e"); 
  h1_108320 = h2_108320->ProjectionY("h1_108320", binmin, binmax, "e");
  h1_108321 = h2_108321->ProjectionY("h1_108321", binmin, binmax, "e");
  h1_108322 = h2_108322->ProjectionY("h1_108322", binmin, binmax, "e");
#endif

#endif //DY

#endif //MC

/*---------------------------------*/
/*           combine data          */
/*---------------------------------*/

#ifdef DATA

//add electron stream
#ifdef ELECTRON  
  histo_data = (TH1D*)h1_electronStream->Clone("histo_data");
#endif

//add muon stream
#ifdef MUON
  histo_data = (TH1D*)h1_muonStream->Clone("histo_data");

//Add if both muon and electron stream!
#ifdef ELECTRON  
  histo_data->Add(h1_electronStream);
#endif

#endif  //endif MUON

#endif //end if DATA


/*---------------------------------*/
/*           combine MC         */
/*---------------------------------*/


#ifdef MC
cout << "adding mc"<<endl;

#ifdef WJETS
cout << "adding wjets"<<endl;

  histo_wjets = (TH1D*)h1_107680->Clone("histo_wjets");
  histo_wjets->Reset();

  h1_107680->Scale( Normalize(107680, lumi, file_107680));
  h1_107681->Scale( Normalize(107681, lumi, file_107681));
  h1_107682->Scale( Normalize(107682, lumi, file_107682));
  h1_107683->Scale( Normalize(107683, lumi, file_107683));
  h1_107684->Scale( Normalize(107684, lumi, file_107684));
  h1_107685->Scale( Normalize(107685, lumi, file_107685));

  h1_107690->Scale( Normalize(107690, lumi, file_107690));
  h1_107691->Scale( Normalize(107691, lumi, file_107691));
  h1_107692->Scale( Normalize(107692, lumi, file_107692));
  h1_107693->Scale( Normalize(107693, lumi, file_107693));
  h1_107694->Scale( Normalize(107694, lumi, file_107694));
  h1_107695->Scale( Normalize(107695, lumi, file_107695));

  h1_107700->Scale( Normalize(107700, lumi, file_107700));
  h1_107701->Scale( Normalize(107701, lumi, file_107701));
  h1_107702->Scale( Normalize(107702, lumi, file_107702));
  h1_107703->Scale( Normalize(107703, lumi, file_107703));
  h1_107704->Scale( Normalize(107704, lumi, file_107704));
  h1_107705->Scale( Normalize(107705, lumi, file_107705));

  histo_wjets ->Add(h1_107680);
  histo_wjets ->Add(h1_107681);
  histo_wjets ->Add(h1_107682);
  histo_wjets ->Add(h1_107683);
  histo_wjets ->Add(h1_107684);
  histo_wjets ->Add(h1_107685);

  histo_wjets ->Add(h1_107690);
  histo_wjets ->Add(h1_107691);
  histo_wjets ->Add(h1_107692);
  histo_wjets ->Add(h1_107693);
  histo_wjets ->Add(h1_107694);
  histo_wjets ->Add(h1_107695);

  histo_wjets ->Add(h1_107700);
  histo_wjets ->Add(h1_107701);
  histo_wjets ->Add(h1_107702);
  histo_wjets ->Add(h1_107703);
  histo_wjets ->Add(h1_107704);
  histo_wjets ->Add(h1_107705);
#endif // Wjets

#ifdef WBB
  cout << "adding wbb"<<endl;

  h1_106280->Scale( Normalize(106280, lumi, file_106280)); 
  h1_106281->Scale( Normalize(106281, lumi, file_106281));
  h1_106282->Scale( Normalize(106282, lumi, file_106282));
  h1_106283->Scale( Normalize(106283, lumi, file_106283));

  histo_wjets ->Add(h1_106280);  // Wbb
  histo_wjets ->Add(h1_106281);
  histo_wjets ->Add(h1_106282);
  histo_wjets ->Add(h1_106283);
#endif // WBB

#ifdef ZJETS
  cout << "adding zjets"<<endl;

  histo_zjets = (TH1D*)h1_107651->Clone("histo_zjets");
  histo_zjets->Reset();

  h1_107650->Scale( Normalize(107650, lumi, file_107650));
  h1_107651->Scale( Normalize(107651, lumi, file_107651));
  h1_107652->Scale( Normalize(107652, lumi, file_107652));
  h1_107653->Scale( Normalize(107653, lumi, file_107653));
  h1_107654->Scale( Normalize(107654, lumi, file_107654));
  h1_107655->Scale( Normalize(107655, lumi, file_107655));
  h1_107660->Scale( Normalize(107660, lumi, file_107660));
  h1_107661->Scale( Normalize(107661, lumi, file_107661));
  h1_107662->Scale( Normalize(107662, lumi, file_107662));
  h1_107663->Scale( Normalize(107663, lumi, file_107663));
  h1_107664->Scale( Normalize(107664, lumi, file_107664));
  h1_107665->Scale( Normalize(107665, lumi, file_107665));
  h1_107670->Scale( Normalize(107670, lumi, file_107670));
  h1_107671->Scale( Normalize(107671, lumi, file_107671));
  h1_107672->Scale( Normalize(107672, lumi, file_107672));
  h1_107673->Scale( Normalize(107673, lumi, file_107673));
  h1_107674->Scale( Normalize(107674, lumi, file_107674));
  h1_107675->Scale( Normalize(107675, lumi, file_107675));

  histo_zjets	->Add(h1_107650);
  histo_zjets	->Add(h1_107651);
  histo_zjets	->Add(h1_107652);
  histo_zjets	->Add(h1_107653);
  histo_zjets	->Add(h1_107654);
  histo_zjets	->Add(h1_107655);
  histo_zjets	->Add(h1_107660);
  histo_zjets	->Add(h1_107661);
  histo_zjets	->Add(h1_107662);
  histo_zjets	->Add(h1_107663);
  histo_zjets	->Add(h1_107664);
  histo_zjets	->Add(h1_107665);
  histo_zjets	->Add(h1_107670);
  histo_zjets	->Add(h1_107671);
  histo_zjets	->Add(h1_107672);
  histo_zjets	->Add(h1_107673);
  histo_zjets	->Add(h1_107674);
  histo_zjets	->Add(h1_107675);
#endif // Zjets

#ifdef DY

cout << "adding drellyan"<<endl;

  histo_drellyan = (TH1D*)h1_108319->Clone("histo_drellyan");

  histo_drellyan->Reset();

  h1_108319->Scale( Normalize(108319, lumi, file_108319));
  h1_108320->Scale( Normalize(108320, lumi, file_108320));
  h1_108321->Scale( Normalize(108321, lumi, file_108321));
  h1_108322->Scale( Normalize(108322, lumi, file_108322));

  histo_drellyan ->Add(h1_108319);
  histo_drellyan ->Add(h1_108320);
  histo_drellyan ->Add(h1_108321);
  histo_drellyan ->Add(h1_108322);
#endif // DY

#ifdef DIBOSON

cout << "adding diboson"<<endl;

  histo_diboson = (TH1D*)h1_105985->Clone("histo_diboson");

  histo_diboson->Reset();

  h1_105985->Scale( Normalize(105985, lumi, file_105985));
  h1_105986->Scale( Normalize(105986, lumi, file_105986));
  h1_105987->Scale( Normalize(105987, lumi, file_105987));

  histo_diboson  ->Add(h1_105985);
  histo_diboson  ->Add(h1_105986);
  histo_diboson  ->Add(h1_105987);
#endif // DIBOSON

#ifdef TTBAR

cout << "adding ttbar"<<endl;

  histo_ttbar = (TH1D*)h1_105200->Clone("histo_ttbar");
  histo_ttbar->Reset();
  
  h1_105200->Scale(Normalize(105200, lumi, file_105200));
  h1_105204->Scale(Normalize(105204, lumi, file_105204));

  histo_ttbar	->Add(h1_105200);
  histo_ttbar	->Add(h1_105204);
#endif //TTBAR

#ifdef SU4
cout << "adding su4"<<endl;

  histo_su4 = (TH1D*)h1_106484->Clone("histo_su4");
  histo_su4->Reset();
  h1_106484->Scale(Normalize(106484, lumi, file_106484));
  histo_su4->Add(h1_106484);
#endif //SU4

#ifdef QCDEE
cout << "adding qcd ee"<<endl;

  histo_qcd = (TH1D*)h1_108326->Clone("histo_qcd");
  histo_qcd->Reset();
  
  h1_108326->Scale(Normalize(108326, lumi, file_108326)); 
   
  histo_qcd->Add(h1_108326);
  histo_qcd_total = (TH1D*)histo_qcd->Clone("histo_qcd_total");

  cout << "QCD : ee      " <<(histo_qcd->Integral())<<endl; 
#endif //QCDEE

#ifdef JX
cout << "adding qcd"<<endl;

  histo_qcd = (TH1D*)h1_105009->Clone("histo_qcd");
  
  //get number of events for normalization
  histo_qcd->Scale(Normalize(105009, lumi, file_105009));
 
  histo_qcd	->Add(h1_105010, Normalize(105010, lumi, file_105010));
  histo_qcd	->Add(h1_105011, Normalize(105011, lumi, file_105011));
  histo_qcd	->Add(h1_105012, Normalize(105012, lumi, file_105012));
  histo_qcd	->Add(h1_105013, Normalize(105013, lumi, file_105013));
  histo_qcd	->Add(h1_105014, Normalize(105014, lumi, file_105014));
  histo_qcd	->Add(h1_105015, Normalize(105015, lumi, file_105015));

  histo_qcd_total = (TH1D*)histo_qcd->Clone("histo_qcd_total");

//add also QCD muon filtered samples (only for emu and mumu??)
  histo_qcd_total->Reset();

#ifdef ELECTRON

  float qcd_el_scale= 1.;
#ifdef NORM
  float qcd_el_scale= 1.;
#endif

  histo_qcd   ->Scale(qcd_el_scale);
  cout << "QCD : Jx      " <<(histo_qcd->Integral())<<endl; 
#endif //ELECTRON
   
  histo_qcd_total ->Add(histo_qcd);

#endif //JX

#ifdef JXMUON

  histo_qcd_mu = (TH1D*)h1_109276->Clone("histo_qcd_mu");
  histo_qcd_mu->Reset();

  h1_109276->Scale( Normalize(109276, lumi, file_109276));
  h1_109277->Scale( Normalize(109277, lumi, file_109277));
  h1_109278->Scale( Normalize(109278, lumi, file_109278));
  h1_109279->Scale( Normalize(109279, lumi, file_109279));
  h1_109280->Scale( Normalize(109280, lumi, file_109280));
  h1_109281->Scale( Normalize(109281, lumi, file_109281));
//  h1_209435->Scale( Normalize(209435, lumi, file_209435));

  histo_qcd_mu	->Add(h1_109276);
  histo_qcd_mu  ->Add(h1_109277);
  histo_qcd_mu  ->Add(h1_109278);
  histo_qcd_mu  ->Add(h1_109279);
  histo_qcd_mu  ->Add(h1_109280);
  histo_qcd_mu  ->Add(h1_109281);
//  histo_qcd_mu  ->Add(h1_209435);

  float qcd_mu_scale= 1.;  
#ifdef NORMMU
  qcd_mu_scale= .2;
#endif
  histo_qcd_mu->Scale(qcd_mu_scale);

  cout << "QCD : Jx muon filtered      " <<(histo_qcd_mu->Integral())<< " scale factor "<< qcd_mu_scale<<endl;  
#ifdef QCDEE  
  histo_qcd_total ->Add(histo_qcd_mu);
#else
  histo_qcd_total = (TH1D*)histo_qcd_mu->Clone("histo_qcd_total");
#endif
#endif //JXMUON 


#endif // MC

// STYLE

//data

#ifdef DATA
  histo_data->SetXTitle(x_string);
  histo_data->SetYTitle(y_string);
  histo_data->SetMarkerStyle(20);
  histo_data->SetMarkerSize(1.2);  
#endif
  
#ifdef MC

#ifdef JX  
  histo_qcd_total->SetXTitle(x_string);
  histo_qcd_total->SetYTitle(y_string);
  histo_qcd_total->SetFillColor(kWhite);
  histo_qcd_total->SetLineColor(kBlack);
//  histo_qcd_total->SetFillColor(kGray+2);//2D
#endif

#ifdef WJETS
  histo_wjets->SetXTitle(x_string);
  histo_wjets->SetYTitle(y_string);
  histo_wjets->SetLineColor(kBlack);
  histo_wjets->SetFillColor(kGray);  //2D
//  histo_wjets->SetLineColor(kBlue+3);  //2D
#endif

#ifdef ZJETS
  histo_zjets->SetXTitle(x_string);
  histo_zjets->SetYTitle(y_string);
  histo_zjets->SetFillColor(kBlue+3);
//  histo_zjets->SetFillColor(kWhite);
//  histo_zjets->SetFillStyle(3004);
//  histo_zjets->SetFillStyle(3354);
//  gStyle->SetHatchesLineWidth(3);
  histo_zjets->SetFillColor(kAzure+1);
#endif

#ifdef DIBOSON
  histo_diboson->SetXTitle(x_string);
  histo_diboson->SetYTitle(y_string);
  histo_diboson->SetFillColor(9);
#endif

#ifdef TTBAR
  histo_ttbar->SetXTitle(x_string);
  histo_ttbar->SetYTitle(y_string);
  histo_ttbar->SetFillColor(kGreen-9);
#endif

#ifdef DY
  histo_drellyan->SetXTitle(x_string);
  histo_drellyan->SetYTitle(y_string);
  histo_drellyan->SetFillColor(kPink+1);
#endif

#ifdef SU4
  double su4_scale = 1.;
  histo_su4->Scale(su4_scale);
  cout << "SU4 x " <<su4_scale<<endl;
  
  histo_su4->SetXTitle(x_string);
  histo_su4->SetYTitle(y_string);
  histo_su4->SetLineWidth(4);
#endif

#ifdef MSUGRA
#ifdef CUTFLOW
#else
#ifdef SYST
#else
  cout << "Filling in MSUGRA grid"<<endl;

  grid = new TH2D("grid", "grid", gridXbins, gridStartX, gridStopX, gridYbins, gridStartY, gridStopY);
  
  Get_m0_m12(file_123290, grid, h1_123290, nCut, nCutRef, eff);  
  Get_m0_m12(file_123291, grid, h1_123291, nCut, nCutRef, eff);  
  Get_m0_m12(file_123292, grid, h1_123292, nCut, nCutRef, eff);  
  Get_m0_m12(file_123293, grid, h1_123293, nCut, nCutRef, eff);  
  Get_m0_m12(file_123294, grid, h1_123294, nCut, nCutRef, eff);  
  Get_m0_m12(file_123295, grid, h1_123295, nCut, nCutRef, eff);  
  Get_m0_m12(file_123296, grid, h1_123296, nCut, nCutRef, eff);  
  Get_m0_m12(file_123297, grid, h1_123297, nCut, nCutRef, eff);  
  Get_m0_m12(file_123298, grid, h1_123298, nCut, nCutRef, eff);  
  Get_m0_m12(file_123299, grid, h1_123299, nCut, nCutRef, eff);  
  Get_m0_m12(file_123300, grid, h1_123300, nCut, nCutRef, eff);  
  Get_m0_m12(file_123301, grid, h1_123301, nCut, nCutRef, eff);  
  Get_m0_m12(file_123302, grid, h1_123302, nCut, nCutRef, eff);  
  Get_m0_m12(file_123303, grid, h1_123303, nCut, nCutRef, eff);  
  Get_m0_m12(file_123304, grid, h1_123304, nCut, nCutRef, eff);  
  Get_m0_m12(file_123305, grid, h1_123305, nCut, nCutRef, eff);  
  Get_m0_m12(file_123306, grid, h1_123306, nCut, nCutRef, eff);  
  Get_m0_m12(file_123307, grid, h1_123307, nCut, nCutRef, eff);  
  Get_m0_m12(file_123308, grid, h1_123308, nCut, nCutRef, eff);  
  Get_m0_m12(file_123309, grid, h1_123309, nCut, nCutRef, eff);  
  Get_m0_m12(file_123310, grid, h1_123310, nCut, nCutRef, eff);  
  Get_m0_m12(file_123311, grid, h1_123311, nCut, nCutRef, eff);  
  Get_m0_m12(file_123312, grid, h1_123312, nCut, nCutRef, eff);  
  Get_m0_m12(file_123313, grid, h1_123313, nCut, nCutRef, eff);  
  Get_m0_m12(file_123314, grid, h1_123314, nCut, nCutRef, eff);  
  Get_m0_m12(file_123315, grid, h1_123315, nCut, nCutRef, eff);  
  Get_m0_m12(file_123316, grid, h1_123316, nCut, nCutRef, eff);  
  Get_m0_m12(file_123317, grid, h1_123317, nCut, nCutRef, eff);  
  Get_m0_m12(file_123320, grid, h1_123320, nCut, nCutRef, eff);  
  Get_m0_m12(file_123321, grid, h1_123321, nCut, nCutRef, eff);  
  Get_m0_m12(file_123322, grid, h1_123322, nCut, nCutRef, eff);  
  Get_m0_m12(file_123323, grid, h1_123323, nCut, nCutRef, eff);  
  Get_m0_m12(file_123324, grid, h1_123324, nCut, nCutRef, eff);  
  Get_m0_m12(file_123325, grid, h1_123325, nCut, nCutRef, eff);  
  Get_m0_m12(file_123326, grid, h1_123326, nCut, nCutRef, eff);  
  Get_m0_m12(file_123327, grid, h1_123327, nCut, nCutRef, eff);  
  Get_m0_m12(file_123328, grid, h1_123328, nCut, nCutRef, eff);  
  Get_m0_m12(file_123329, grid, h1_123329, nCut, nCutRef, eff);  
  Get_m0_m12(file_123330, grid, h1_123330, nCut, nCutRef, eff);  
  Get_m0_m12(file_123331, grid, h1_123331, nCut, nCutRef, eff);  
  Get_m0_m12(file_123332, grid, h1_123332, nCut, nCutRef, eff);  
  Get_m0_m12(file_123333, grid, h1_123333, nCut, nCutRef, eff);  
  Get_m0_m12(file_123334, grid, h1_123334, nCut, nCutRef, eff);  
  Get_m0_m12(file_123335, grid, h1_123335, nCut, nCutRef, eff);  
  Get_m0_m12(file_123336, grid, h1_123336, nCut, nCutRef, eff);  
  Get_m0_m12(file_123337, grid, h1_123337, nCut, nCutRef, eff);  
  Get_m0_m12(file_123338, grid, h1_123338, nCut, nCutRef, eff);  
  Get_m0_m12(file_123339, grid, h1_123339, nCut, nCutRef, eff);  
  Get_m0_m12(file_123340, grid, h1_123340, nCut, nCutRef, eff);  
  Get_m0_m12(file_123341, grid, h1_123341, nCut, nCutRef, eff);  
  Get_m0_m12(file_123342, grid, h1_123342, nCut, nCutRef, eff);  
  Get_m0_m12(file_123343, grid, h1_123343, nCut, nCutRef, eff);  
  Get_m0_m12(file_123344, grid, h1_123344, nCut, nCutRef, eff);  
  Get_m0_m12(file_123345, grid, h1_123345, nCut, nCutRef, eff);  
  Get_m0_m12(file_123346, grid, h1_123346, nCut, nCutRef, eff);  
  Get_m0_m12(file_123347, grid, h1_123347, nCut, nCutRef, eff);  
  Get_m0_m12(file_123348, grid, h1_123348, nCut, nCutRef, eff);  
  Get_m0_m12(file_123349, grid, h1_123349, nCut, nCutRef, eff);  
  Get_m0_m12(file_123350, grid, h1_123350, nCut, nCutRef, eff);  
  Get_m0_m12(file_123351, grid, h1_123351, nCut, nCutRef, eff);  
  Get_m0_m12(file_123352, grid, h1_123352, nCut, nCutRef, eff);  
  Get_m0_m12(file_123353, grid, h1_123353, nCut, nCutRef, eff);  
  Get_m0_m12(file_123354, grid, h1_123354, nCut, nCutRef, eff);  
  Get_m0_m12(file_123355, grid, h1_123355, nCut, nCutRef, eff);  
  Get_m0_m12(file_123356, grid, h1_123356, nCut, nCutRef, eff);  
  Get_m0_m12(file_123357, grid, h1_123357, nCut, nCutRef, eff);  
  Get_m0_m12(file_123358, grid, h1_123358, nCut, nCutRef, eff);  
  Get_m0_m12(file_123359, grid, h1_123359, nCut, nCutRef, eff);  
  Get_m0_m12(file_123360, grid, h1_123360, nCut, nCutRef, eff);  
  Get_m0_m12(file_123361, grid, h1_123361, nCut, nCutRef, eff);  
  Get_m0_m12(file_123362, grid, h1_123362, nCut, nCutRef, eff);  
  Get_m0_m12(file_123363, grid, h1_123363, nCut, nCutRef, eff);  
  Get_m0_m12(file_123364, grid, h1_123364, nCut, nCutRef, eff);  
  Get_m0_m12(file_123365, grid, h1_123365, nCut, nCutRef, eff);  
  Get_m0_m12(file_123366, grid, h1_123366, nCut, nCutRef, eff);  
  Get_m0_m12(file_123367, grid, h1_123367, nCut, nCutRef, eff);  
  Get_m0_m12(file_123368, grid, h1_123368, nCut, nCutRef, eff);  
  Get_m0_m12(file_123369, grid, h1_123369, nCut, nCutRef, eff);  
  Get_m0_m12(file_123370, grid, h1_123370, nCut, nCutRef, eff);  
  Get_m0_m12(file_123371, grid, h1_123371, nCut, nCutRef, eff);  
  Get_m0_m12(file_123372, grid, h1_123372, nCut, nCutRef, eff);  
  Get_m0_m12(file_123373, grid, h1_123373, nCut, nCutRef, eff);  
  Get_m0_m12(file_123374, grid, h1_123374, nCut, nCutRef, eff);  
  Get_m0_m12(file_123375, grid, h1_123375, nCut, nCutRef, eff);  
  Get_m0_m12(file_123376, grid, h1_123376, nCut, nCutRef, eff);  
  Get_m0_m12(file_123377, grid, h1_123377, nCut, nCutRef, eff);  
  Get_m0_m12(file_123378, grid, h1_123378, nCut, nCutRef, eff);  
  Get_m0_m12(file_123379, grid, h1_123379, nCut, nCutRef, eff);  
  Get_m0_m12(file_123380, grid, h1_123380, nCut, nCutRef, eff);  
  Get_m0_m12(file_123381, grid, h1_123381, nCut, nCutRef, eff);  
  Get_m0_m12(file_123383, grid, h1_123383, nCut, nCutRef, eff);  
  Get_m0_m12(file_123384, grid, h1_123384, nCut, nCutRef, eff);  
  Get_m0_m12(file_123385, grid, h1_123385, nCut, nCutRef, eff);  
  Get_m0_m12(file_123386, grid, h1_123386, nCut, nCutRef, eff);  
  Get_m0_m12(file_123387, grid, h1_123387, nCut, nCutRef, eff);  
  Get_m0_m12(file_123388, grid, h1_123388, nCut, nCutRef, eff);  
  Get_m0_m12(file_123389, grid, h1_123389, nCut, nCutRef, eff);  
  Get_m0_m12(file_123390, grid, h1_123390, nCut, nCutRef, eff);  
  Get_m0_m12(file_123391, grid, h1_123391, nCut, nCutRef, eff);  
  Get_m0_m12(file_123392, grid, h1_123392, nCut, nCutRef, eff);  
  Get_m0_m12(file_123393, grid, h1_123393, nCut, nCutRef, eff);  
  Get_m0_m12(file_123394, grid, h1_123394, nCut, nCutRef, eff);  
  Get_m0_m12(file_123396, grid, h1_123396, nCut, nCutRef, eff);  
  Get_m0_m12(file_123397, grid, h1_123397, nCut, nCutRef, eff);  
  Get_m0_m12(file_123398, grid, h1_123398, nCut, nCutRef, eff);  
  Get_m0_m12(file_123399, grid, h1_123399, nCut, nCutRef, eff);  
  Get_m0_m12(file_123400, grid, h1_123400, nCut, nCutRef, eff);  
  Get_m0_m12(file_123401, grid, h1_123401, nCut, nCutRef, eff);  
  Get_m0_m12(file_123402, grid, h1_123402, nCut, nCutRef, eff);  
  Get_m0_m12(file_123403, grid, h1_123403, nCut, nCutRef, eff);  
  Get_m0_m12(file_123404, grid, h1_123404, nCut, nCutRef, eff);  
  Get_m0_m12(file_123405, grid, h1_123405, nCut, nCutRef, eff);  
  Get_m0_m12(file_123406, grid, h1_123406, nCut, nCutRef, eff);  
  Get_m0_m12(file_123407, grid, h1_123407, nCut, nCutRef, eff);  
  Get_m0_m12(file_123408, grid, h1_123408, nCut, nCutRef, eff);  
  Get_m0_m12(file_123409, grid, h1_123409, nCut, nCutRef, eff);  
  Get_m0_m12(file_123410, grid, h1_123410, nCut, nCutRef, eff);  
  Get_m0_m12(file_123411, grid, h1_123411, nCut, nCutRef, eff);  
  Get_m0_m12(file_123412, grid, h1_123412, nCut, nCutRef, eff);  
  Get_m0_m12(file_123413, grid, h1_123413, nCut, nCutRef, eff);  
  Get_m0_m12(file_123414, grid, h1_123414, nCut, nCutRef, eff);  
  Get_m0_m12(file_123415, grid, h1_123415, nCut, nCutRef, eff);  
  Get_m0_m12(file_123416, grid, h1_123416, nCut, nCutRef, eff);  
  Get_m0_m12(file_123417, grid, h1_123417, nCut, nCutRef, eff);  
  Get_m0_m12(file_123418, grid, h1_123418, nCut, nCutRef, eff);  
  Get_m0_m12(file_123419, grid, h1_123419, nCut, nCutRef, eff);  
  Get_m0_m12(file_123420, grid, h1_123420, nCut, nCutRef, eff);  
  Get_m0_m12(file_123422, grid, h1_123422, nCut, nCutRef, eff);  
  Get_m0_m12(file_123423, grid, h1_123423, nCut, nCutRef, eff);  
  Get_m0_m12(file_123424, grid, h1_123424, nCut, nCutRef, eff);  
  Get_m0_m12(file_123425, grid, h1_123425, nCut, nCutRef, eff);  
  Get_m0_m12(file_123426, grid, h1_123426, nCut, nCutRef, eff);  
  Get_m0_m12(file_123427, grid, h1_123427, nCut, nCutRef, eff);  
  Get_m0_m12(file_123428, grid, h1_123428, nCut, nCutRef, eff);  
  Get_m0_m12(file_123430, grid, h1_123430, nCut, nCutRef, eff);  
  Get_m0_m12(file_123431, grid, h1_123431, nCut, nCutRef, eff);  
  Get_m0_m12(file_123432, grid, h1_123432, nCut, nCutRef, eff);  
  Get_m0_m12(file_123433, grid, h1_123433, nCut, nCutRef, eff);  
  Get_m0_m12(file_123434, grid, h1_123434, nCut, nCutRef, eff);  
  Get_m0_m12(file_123435, grid, h1_123435, nCut, nCutRef, eff);  
  Get_m0_m12(file_123436, grid, h1_123436, nCut, nCutRef, eff);  
  Get_m0_m12(file_123437, grid, h1_123437, nCut, nCutRef, eff);  
  Get_m0_m12(file_123438, grid, h1_123438, nCut, nCutRef, eff);  
  Get_m0_m12(file_123439, grid, h1_123439, nCut, nCutRef, eff);  
  Get_m0_m12(file_123440, grid, h1_123440, nCut, nCutRef, eff);  
  Get_m0_m12(file_123441, grid, h1_123441, nCut, nCutRef, eff);  
  Get_m0_m12(file_123442, grid, h1_123442, nCut, nCutRef, eff);  
  Get_m0_m12(file_123443, grid, h1_123443, nCut, nCutRef, eff);  
  Get_m0_m12(file_123444, grid, h1_123444, nCut, nCutRef, eff);  
  Get_m0_m12(file_123445, grid, h1_123445, nCut, nCutRef, eff);  
  Get_m0_m12(file_123447, grid, h1_123447, nCut, nCutRef, eff);  
  Get_m0_m12(file_123448, grid, h1_123448, nCut, nCutRef, eff);  
  Get_m0_m12(file_123449, grid, h1_123449, nCut, nCutRef, eff);  
  Get_m0_m12(file_123450, grid, h1_123450, nCut, nCutRef, eff);  
  Get_m0_m12(file_123451, grid, h1_123451, nCut, nCutRef, eff);  
  Get_m0_m12(file_123452, grid, h1_123452, nCut, nCutRef, eff);  
  Get_m0_m12(file_123453, grid, h1_123453, nCut, nCutRef, eff);  
  Get_m0_m12(file_123454, grid, h1_123454, nCut, nCutRef, eff);  
  Get_m0_m12(file_123455, grid, h1_123455, nCut, nCutRef, eff);  
  Get_m0_m12(file_123456, grid, h1_123456, nCut, nCutRef, eff);  
  Get_m0_m12(file_123457, grid, h1_123457, nCut, nCutRef, eff);  
  Get_m0_m12(file_123458, grid, h1_123458, nCut, nCutRef, eff);  
  Get_m0_m12(file_123460, grid, h1_123460, nCut, nCutRef, eff);  
  Get_m0_m12(file_123461, grid, h1_123461, nCut, nCutRef, eff);  
  Get_m0_m12(file_123462, grid, h1_123462, nCut, nCutRef, eff);  
  Get_m0_m12(file_123463, grid, h1_123463, nCut, nCutRef, eff);  
  Get_m0_m12(file_123464, grid, h1_123464, nCut, nCutRef, eff);  
  Get_m0_m12(file_123465, grid, h1_123465, nCut, nCutRef, eff);  
  Get_m0_m12(file_123466, grid, h1_123466, nCut, nCutRef, eff);  
  Get_m0_m12(file_123467, grid, h1_123467, nCut, nCutRef, eff);  
  Get_m0_m12(file_123468, grid, h1_123468, nCut, nCutRef, eff);  
  Get_m0_m12(file_123469, grid, h1_123469, nCut, nCutRef, eff);  
  Get_m0_m12(file_123470, grid, h1_123470, nCut, nCutRef, eff);  
  Get_m0_m12(file_123471, grid, h1_123471, nCut, nCutRef, eff);  
  Get_m0_m12(file_123472, grid, h1_123472, nCut, nCutRef, eff);  
  Get_m0_m12(file_123473, grid, h1_123473, nCut, nCutRef, eff);  
  Get_m0_m12(file_123474, grid, h1_123474, nCut, nCutRef, eff);  
  Get_m0_m12(file_123475, grid, h1_123475, nCut, nCutRef, eff);  
  Get_m0_m12(file_123476, grid, h1_123476, nCut, nCutRef, eff);  
  Get_m0_m12(file_123477, grid, h1_123477, nCut, nCutRef, eff);  
  Get_m0_m12(file_123478, grid, h1_123478, nCut, nCutRef, eff);  
  Get_m0_m12(file_123479, grid, h1_123479, nCut, nCutRef, eff);  
  Get_m0_m12(file_123480, grid, h1_123480, nCut, nCutRef, eff);  
  Get_m0_m12(file_123481, grid, h1_123481, nCut, nCutRef, eff);  
  Get_m0_m12(file_123482, grid, h1_123482, nCut, nCutRef, eff);  
  Get_m0_m12(file_123483, grid, h1_123483, nCut, nCutRef, eff);  
  Get_m0_m12(file_123484, grid, h1_123484, nCut, nCutRef, eff);  
  Get_m0_m12(file_123485, grid, h1_123485, nCut, nCutRef, eff);  
  Get_m0_m12(file_123486, grid, h1_123486, nCut, nCutRef, eff);  
  Get_m0_m12(file_123487, grid, h1_123487, nCut, nCutRef, eff);  
  Get_m0_m12(file_123488, grid, h1_123488, nCut, nCutRef, eff);  
  Get_m0_m12(file_123489, grid, h1_123489, nCut, nCutRef, eff);  
  Get_m0_m12(file_123490, grid, h1_123490, nCut, nCutRef, eff);  
  Get_m0_m12(file_123491, grid, h1_123491, nCut, nCutRef, eff);  
  Get_m0_m12(file_123492, grid, h1_123492, nCut, nCutRef, eff);  
  Get_m0_m12(file_123493, grid, h1_123493, nCut, nCutRef, eff);  
  Get_m0_m12(file_123494, grid, h1_123494, nCut, nCutRef, eff);  
  Get_m0_m12(file_123495, grid, h1_123495, nCut, nCutRef, eff);  
  Get_m0_m12(file_123496, grid, h1_123496, nCut, nCutRef, eff);  
  Get_m0_m12(file_123497, grid, h1_123497, nCut, nCutRef, eff);  
  Get_m0_m12(file_123498, grid, h1_123498, nCut, nCutRef, eff);  
  Get_m0_m12(file_123499, grid, h1_123499, nCut, nCutRef, eff);  
  Get_m0_m12(file_123501, grid, h1_123501, nCut, nCutRef, eff);  
  Get_m0_m12(file_123502, grid, h1_123502, nCut, nCutRef, eff);  
  Get_m0_m12(file_123503, grid, h1_123503, nCut, nCutRef, eff);  
  Get_m0_m12(file_123504, grid, h1_123504, nCut, nCutRef, eff);  
  Get_m0_m12(file_123505, grid, h1_123505, nCut, nCutRef, eff);  
  Get_m0_m12(file_123506, grid, h1_123506, nCut, nCutRef, eff);  
  Get_m0_m12(file_123507, grid, h1_123507, nCut, nCutRef, eff);  
  Get_m0_m12(file_123508, grid, h1_123508, nCut, nCutRef, eff);  
  Get_m0_m12(file_123509, grid, h1_123509, nCut, nCutRef, eff);  
  Get_m0_m12(file_123510, grid, h1_123510, nCut, nCutRef, eff);  
  Get_m0_m12(file_123511, grid, h1_123511, nCut, nCutRef, eff);  
  Get_m0_m12(file_123512, grid, h1_123512, nCut, nCutRef, eff);  
  Get_m0_m12(file_123513, grid, h1_123513, nCut, nCutRef, eff);  
  Get_m0_m12(file_123514, grid, h1_123514, nCut, nCutRef, eff);  
  Get_m0_m12(file_123516, grid, h1_123516, nCut, nCutRef, eff);  
  Get_m0_m12(file_123517, grid, h1_123517, nCut, nCutRef, eff);  
  Get_m0_m12(file_123518, grid, h1_123518, nCut, nCutRef, eff);  
  Get_m0_m12(file_123519, grid, h1_123519, nCut, nCutRef, eff);  
  Get_m0_m12(file_123520, grid, h1_123520, nCut, nCutRef, eff);  
  Get_m0_m12(file_123521, grid, h1_123521, nCut, nCutRef, eff);  
  Get_m0_m12(file_123522, grid, h1_123522, nCut, nCutRef, eff);  
  Get_m0_m12(file_123523, grid, h1_123523, nCut, nCutRef, eff);  
  Get_m0_m12(file_123524, grid, h1_123524, nCut, nCutRef, eff);  
  Get_m0_m12(file_123526, grid, h1_123526, nCut, nCutRef, eff);  
  Get_m0_m12(file_123527, grid, h1_123527, nCut, nCutRef, eff);  
  Get_m0_m12(file_123528, grid, h1_123528, nCut, nCutRef, eff);  
  Get_m0_m12(file_123529, grid, h1_123529, nCut, nCutRef, eff);  
  Get_m0_m12(file_123530, grid, h1_123530, nCut, nCutRef, eff);  
  Get_m0_m12(file_123531, grid, h1_123531, nCut, nCutRef, eff);  
  Get_m0_m12(file_123533, grid, h1_123533, nCut, nCutRef, eff);  
  Get_m0_m12(file_123534, grid, h1_123534, nCut, nCutRef, eff);  
  Get_m0_m12(file_123535, grid, h1_123535, nCut, nCutRef, eff);  
  Get_m0_m12(file_123536, grid, h1_123536, nCut, nCutRef, eff);  
  Get_m0_m12(file_123537, grid, h1_123537, nCut, nCutRef, eff);  
  Get_m0_m12(file_123538, grid, h1_123538, nCut, nCutRef, eff);  
  Get_m0_m12(file_123539, grid, h1_123539, nCut, nCutRef, eff);  
  Get_m0_m12(file_123540, grid, h1_123540, nCut, nCutRef, eff);  
  Get_m0_m12(file_123541, grid, h1_123541, nCut, nCutRef, eff);  
  Get_m0_m12(file_123542, grid, h1_123542, nCut, nCutRef, eff);  
  Get_m0_m12(file_123543, grid, h1_123543, nCut, nCutRef, eff);  
  Get_m0_m12(file_123544, grid, h1_123544, nCut, nCutRef, eff);  
  Get_m0_m12(file_123545, grid, h1_123545, nCut, nCutRef, eff);  
  Get_m0_m12(file_123546, grid, h1_123546, nCut, nCutRef, eff);  
  Get_m0_m12(file_123547, grid, h1_123547, nCut, nCutRef, eff);  
  Get_m0_m12(file_123548, grid, h1_123548, nCut, nCutRef, eff);  
  Get_m0_m12(file_123549, grid, h1_123549, nCut, nCutRef, eff);  
  Get_m0_m12(file_123550, grid, h1_123550, nCut, nCutRef, eff);  
  Get_m0_m12(file_123551, grid, h1_123551, nCut, nCutRef, eff);  
  Get_m0_m12(file_123552, grid, h1_123552, nCut, nCutRef, eff);  
  Get_m0_m12(file_123553, grid, h1_123553, nCut, nCutRef, eff);  
  Get_m0_m12(file_123554, grid, h1_123554, nCut, nCutRef, eff);  
  Get_m0_m12(file_123555, grid, h1_123555, nCut, nCutRef, eff);  
  Get_m0_m12(file_123556, grid, h1_123556, nCut, nCutRef, eff);  
  Get_m0_m12(file_123557, grid, h1_123557, nCut, nCutRef, eff);  
  Get_m0_m12(file_123558, grid, h1_123558, nCut, nCutRef, eff);  
  Get_m0_m12(file_123559, grid, h1_123559, nCut, nCutRef, eff);  
  Get_m0_m12(file_123560, grid, h1_123560, nCut, nCutRef, eff);  
  Get_m0_m12(file_123561, grid, h1_123561, nCut, nCutRef, eff);  
  Get_m0_m12(file_123562, grid, h1_123562, nCut, nCutRef, eff);  
  Get_m0_m12(file_123563, grid, h1_123563, nCut, nCutRef, eff);  
  Get_m0_m12(file_123564, grid, h1_123564, nCut, nCutRef, eff);  
  Get_m0_m12(file_123565, grid, h1_123565, nCut, nCutRef, eff);  
  Get_m0_m12(file_123566, grid, h1_123566, nCut, nCutRef, eff);  
  Get_m0_m12(file_123567, grid, h1_123567, nCut, nCutRef, eff);  
  Get_m0_m12(file_123568, grid, h1_123568, nCut, nCutRef, eff);  
  Get_m0_m12(file_123569, grid, h1_123569, nCut, nCutRef, eff);  
  Get_m0_m12(file_123570, grid, h1_123570, nCut, nCutRef, eff);  
  Get_m0_m12(file_123571, grid, h1_123571, nCut, nCutRef, eff);  
  Get_m0_m12(file_123572, grid, h1_123572, nCut, nCutRef, eff);  
  Get_m0_m12(file_123573, grid, h1_123573, nCut, nCutRef, eff);  
  Get_m0_m12(file_123574, grid, h1_123574, nCut, nCutRef, eff);  
  Get_m0_m12(file_123575, grid, h1_123575, nCut, nCutRef, eff);  
  Get_m0_m12(file_123576, grid, h1_123576, nCut, nCutRef, eff);  
  Get_m0_m12(file_123577, grid, h1_123577, nCut, nCutRef, eff);  
  Get_m0_m12(file_123578, grid, h1_123578, nCut, nCutRef, eff);  
  Get_m0_m12(file_123579, grid, h1_123579, nCut, nCutRef, eff);  
  Get_m0_m12(file_123580, grid, h1_123580, nCut, nCutRef, eff);  
  Get_m0_m12(file_123581, grid, h1_123581, nCut, nCutRef, eff);  
  Get_m0_m12(file_123582, grid, h1_123582, nCut, nCutRef, eff);  
  Get_m0_m12(file_123583, grid, h1_123583, nCut, nCutRef, eff);  
  Get_m0_m12(file_123584, grid, h1_123584, nCut, nCutRef, eff);  
  Get_m0_m12(file_123585, grid, h1_123585, nCut, nCutRef, eff);  
  Get_m0_m12(file_123586, grid, h1_123586, nCut, nCutRef, eff);  
  Get_m0_m12(file_123587, grid, h1_123587, nCut, nCutRef, eff);  
  Get_m0_m12(file_123588, grid, h1_123588, nCut, nCutRef, eff);  
  Get_m0_m12(file_123589, grid, h1_123589, nCut, nCutRef, eff);  
  Get_m0_m12(file_123590, grid, h1_123590, nCut, nCutRef, eff);  
  Get_m0_m12(file_123591, grid, h1_123591, nCut, nCutRef, eff);  
  Get_m0_m12(file_123592, grid, h1_123592, nCut, nCutRef, eff);  
  Get_m0_m12(file_123593, grid, h1_123593, nCut, nCutRef, eff);  
  Get_m0_m12(file_123594, grid, h1_123594, nCut, nCutRef, eff);  
  Get_m0_m12(file_123595, grid, h1_123595, nCut, nCutRef, eff);  
  Get_m0_m12(file_123597, grid, h1_123597, nCut, nCutRef, eff);  
  Get_m0_m12(file_123598, grid, h1_123598, nCut, nCutRef, eff);  
  Get_m0_m12(file_123599, grid, h1_123599, nCut, nCutRef, eff);  
  Get_m0_m12(file_123600, grid, h1_123600, nCut, nCutRef, eff);  
  Get_m0_m12(file_123601, grid, h1_123601, nCut, nCutRef, eff);  
  Get_m0_m12(file_123602, grid, h1_123602, nCut, nCutRef, eff);  
  Get_m0_m12(file_123603, grid, h1_123603, nCut, nCutRef, eff);  
  Get_m0_m12(file_123604, grid, h1_123604, nCut, nCutRef, eff);  
  Get_m0_m12(file_123605, grid, h1_123605, nCut, nCutRef, eff);  
  Get_m0_m12(file_123606, grid, h1_123606, nCut, nCutRef, eff);  
  Get_m0_m12(file_123607, grid, h1_123607, nCut, nCutRef, eff);  
  Get_m0_m12(file_123609, grid, h1_123609, nCut, nCutRef, eff);  
  Get_m0_m12(file_123611, grid, h1_123611, nCut, nCutRef, eff);  
  Get_m0_m12(file_123612, grid, h1_123612, nCut, nCutRef, eff);  
  Get_m0_m12(file_123613, grid, h1_123613, nCut, nCutRef, eff);  
  Get_m0_m12(file_123614, grid, h1_123614, nCut, nCutRef, eff);  
  Get_m0_m12(file_123615, grid, h1_123615, nCut, nCutRef, eff);  
  Get_m0_m12(file_123616, grid, h1_123616, nCut, nCutRef, eff);  
  Get_m0_m12(file_123617, grid, h1_123617, nCut, nCutRef, eff);  
  Get_m0_m12(file_123618, grid, h1_123618, nCut, nCutRef, eff);  
  Get_m0_m12(file_123619, grid, h1_123619, nCut, nCutRef, eff);  
  Get_m0_m12(file_123620, grid, h1_123620, nCut, nCutRef, eff);  
  Get_m0_m12(file_123621, grid, h1_123621, nCut, nCutRef, eff);  
  Get_m0_m12(file_123622, grid, h1_123622, nCut, nCutRef, eff);  
  Get_m0_m12(file_123623, grid, h1_123623, nCut, nCutRef, eff);  
  Get_m0_m12(file_123624, grid, h1_123624, nCut, nCutRef, eff);  
  Get_m0_m12(file_123625, grid, h1_123625, nCut, nCutRef, eff);  
  Get_m0_m12(file_123626, grid, h1_123626, nCut, nCutRef, eff);  
  Get_m0_m12(file_123628, grid, h1_123628, nCut, nCutRef, eff);  
  Get_m0_m12(file_123629, grid, h1_123629, nCut, nCutRef, eff);  
  Get_m0_m12(file_123630, grid, h1_123630, nCut, nCutRef, eff);  
  Get_m0_m12(file_123631, grid, h1_123631, nCut, nCutRef, eff);  
  Get_m0_m12(file_123632, grid, h1_123632, nCut, nCutRef, eff);  
  Get_m0_m12(file_123633, grid, h1_123633, nCut, nCutRef, eff);  
  Get_m0_m12(file_123634, grid, h1_123634, nCut, nCutRef, eff);  
  Get_m0_m12(file_123635, grid, h1_123635, nCut, nCutRef, eff);  
  Get_m0_m12(file_123636, grid, h1_123636, nCut, nCutRef, eff);  
  Get_m0_m12(file_123637, grid, h1_123637, nCut, nCutRef, eff);  
  Get_m0_m12(file_123638, grid, h1_123638, nCut, nCutRef, eff);  
  Get_m0_m12(file_123640, grid, h1_123640, nCut, nCutRef, eff);  
  Get_m0_m12(file_123641, grid, h1_123641, nCut, nCutRef, eff);  
  Get_m0_m12(file_123642, grid, h1_123642, nCut, nCutRef, eff);  
  Get_m0_m12(file_123643, grid, h1_123643, nCut, nCutRef, eff);  
  Get_m0_m12(file_123644, grid, h1_123644, nCut, nCutRef, eff);  
  Get_m0_m12(file_123645, grid, h1_123645, nCut, nCutRef, eff);  
  Get_m0_m12(file_123646, grid, h1_123646, nCut, nCutRef, eff);  
  Get_m0_m12(file_123647, grid, h1_123647, nCut, nCutRef, eff);  
  Get_m0_m12(file_123648, grid, h1_123648, nCut, nCutRef, eff);  
  Get_m0_m12(file_123649, grid, h1_123649, nCut, nCutRef, eff);  
  Get_m0_m12(file_123650, grid, h1_123650, nCut, nCutRef, eff);  
  Get_m0_m12(file_123651, grid, h1_123651, nCut, nCutRef, eff);  
  Get_m0_m12(file_123652, grid, h1_123652, nCut, nCutRef, eff);  
  Get_m0_m12(file_123653, grid, h1_123653, nCut, nCutRef, eff);  
  Get_m0_m12(file_123654, grid, h1_123654, nCut, nCutRef, eff);  
  Get_m0_m12(file_123655, grid, h1_123655, nCut, nCutRef, eff);  
  Get_m0_m12(file_123656, grid, h1_123656, nCut, nCutRef, eff);  
  Get_m0_m12(file_123657, grid, h1_123657, nCut, nCutRef, eff);  
  Get_m0_m12(file_123658, grid, h1_123658, nCut, nCutRef, eff);  
  Get_m0_m12(file_123659, grid, h1_123659, nCut, nCutRef, eff);  
  Get_m0_m12(file_123660, grid, h1_123660, nCut, nCutRef, eff);  
  Get_m0_m12(file_123661, grid, h1_123661, nCut, nCutRef, eff);  
  Get_m0_m12(file_123662, grid, h1_123662, nCut, nCutRef, eff);  
  Get_m0_m12(file_123663, grid, h1_123663, nCut, nCutRef, eff);  
  Get_m0_m12(file_123664, grid, h1_123664, nCut, nCutRef, eff);  
  Get_m0_m12(file_123665, grid, h1_123665, nCut, nCutRef, eff);  
  Get_m0_m12(file_123666, grid, h1_123666, nCut, nCutRef, eff);  
  Get_m0_m12(file_123667, grid, h1_123667, nCut, nCutRef, eff);  
  Get_m0_m12(file_123668, grid, h1_123668, nCut, nCutRef, eff);  
  Get_m0_m12(file_123669, grid, h1_123669, nCut, nCutRef, eff);  
  Get_m0_m12(file_123670, grid, h1_123670, nCut, nCutRef, eff);  
  Get_m0_m12(file_123671, grid, h1_123671, nCut, nCutRef, eff);  
  Get_m0_m12(file_123672, grid, h1_123672, nCut, nCutRef, eff);  
  Get_m0_m12(file_123673, grid, h1_123673, nCut, nCutRef, eff);  
  Get_m0_m12(file_123674, grid, h1_123674, nCut, nCutRef, eff);  
  Get_m0_m12(file_123675, grid, h1_123675, nCut, nCutRef, eff);  
  Get_m0_m12(file_123676, grid, h1_123676, nCut, nCutRef, eff);  
  Get_m0_m12(file_123677, grid, h1_123677, nCut, nCutRef, eff);  
  Get_m0_m12(file_123678, grid, h1_123678, nCut, nCutRef, eff);  
  Get_m0_m12(file_123679, grid, h1_123679, nCut, nCutRef, eff);  
  Get_m0_m12(file_123680, grid, h1_123680, nCut, nCutRef, eff);  
  Get_m0_m12(file_123682, grid, h1_123682, nCut, nCutRef, eff);  
  Get_m0_m12(file_123683, grid, h1_123683, nCut, nCutRef, eff);  
  Get_m0_m12(file_123684, grid, h1_123684, nCut, nCutRef, eff);  
  Get_m0_m12(file_123686, grid, h1_123686, nCut, nCutRef, eff);  
  Get_m0_m12(file_123687, grid, h1_123687, nCut, nCutRef, eff);  
  Get_m0_m12(file_123688, grid, h1_123688, nCut, nCutRef, eff);  
  Get_m0_m12(file_123689, grid, h1_123689, nCut, nCutRef, eff);  
  Get_m0_m12(file_123690, grid, h1_123690, nCut, nCutRef, eff);  
#endif //syst
    
#endif //cutflow

#endif //MSUGRA 

#ifdef PHENO
#ifdef CUTFLOW
#else
  cout << "Filling in PHENO grid"<<endl;

  grid_odd = new TH2D("grid_odd", "grid_odd", 30, -20., 1180, 40, 2.5., 702.5);
  grid_even = new TH2D("grid_even", "grid_even", 30, -20., 1180, 40, 2.5., 702.5);
 
#ifdef GRID3         //Phenogrid 3
  Get_m0_m12(file_114901, grid_odd, h1_114901, nCut, nCutRef, eff); 
  Get_m0_m12(file_114902, grid_even, h1_114902, nCut, nCutRef, eff); 
  Get_m0_m12(file_114903, grid_odd, h1_114903, nCut, nCutRef, eff); 
  Get_m0_m12(file_114904, grid_even, h1_114904, nCut, nCutRef, eff); 
  Get_m0_m12(file_114905, grid_odd, h1_114905, nCut, nCutRef, eff); 
  Get_m0_m12(file_114906, grid_even, h1_114906, nCut, nCutRef, eff); 
  Get_m0_m12(file_114907, grid_odd, h1_114907, nCut, nCutRef, eff); 
  Get_m0_m12(file_114908, grid_even, h1_114908, nCut, nCutRef, eff); 
  Get_m0_m12(file_114909, grid_odd, h1_114909, nCut, nCutRef, eff); 
  Get_m0_m12(file_114910, grid_even, h1_114910, nCut, nCutRef, eff); 
  Get_m0_m12(file_114911, grid_odd, h1_114911, nCut, nCutRef, eff); 
  Get_m0_m12(file_114912, grid_even, h1_114912, nCut, nCutRef, eff); 
  Get_m0_m12(file_114913, grid_odd, h1_114913, nCut, nCutRef, eff); 
  Get_m0_m12(file_114914, grid_even, h1_114914, nCut, nCutRef, eff); 
  Get_m0_m12(file_114915, grid_odd, h1_114915, nCut, nCutRef, eff); 
  Get_m0_m12(file_114916, grid_even, h1_114916, nCut, nCutRef, eff); 
  Get_m0_m12(file_114917, grid_odd, h1_114917, nCut, nCutRef, eff); 
  Get_m0_m12(file_114918, grid_even, h1_114918, nCut, nCutRef, eff); 
  Get_m0_m12(file_114919, grid_odd, h1_114919, nCut, nCutRef, eff); 
  Get_m0_m12(file_114920, grid_even, h1_114920, nCut, nCutRef, eff); 
  Get_m0_m12(file_114921, grid_odd, h1_114921, nCut, nCutRef, eff); 
  Get_m0_m12(file_114922, grid_even, h1_114922, nCut, nCutRef, eff); 
  Get_m0_m12(file_114923, grid_odd, h1_114923, nCut, nCutRef, eff); 
  Get_m0_m12(file_114924, grid_even, h1_114924, nCut, nCutRef, eff); 
  Get_m0_m12(file_114925, grid_odd, h1_114925, nCut, nCutRef, eff); 
  Get_m0_m12(file_114926, grid_even, h1_114926, nCut, nCutRef, eff); 
  Get_m0_m12(file_114927, grid_odd, h1_114927, nCut, nCutRef, eff); 
  Get_m0_m12(file_114928, grid_even, h1_114928, nCut, nCutRef, eff); 
  Get_m0_m12(file_114929, grid_odd, h1_114929, nCut, nCutRef, eff); 
  Get_m0_m12(file_114930, grid_even, h1_114930, nCut, nCutRef, eff); 
  Get_m0_m12(file_114931, grid_odd, h1_114931, nCut, nCutRef, eff); 
  Get_m0_m12(file_114932, grid_even, h1_114932, nCut, nCutRef, eff); 
#endif
#ifdef GRID2         //Phenogrid 2
  Get_m0_m12(file_114933, grid_odd, h1_114933, nCut, nCutRef, eff); 
  Get_m0_m12(file_114934, grid_even, h1_114934, nCut, nCutRef, eff); 
  Get_m0_m12(file_114935, grid_odd, h1_114935, nCut, nCutRef, eff); 
  Get_m0_m12(file_114936, grid_even, h1_114936, nCut, nCutRef, eff); 
  Get_m0_m12(file_114937, grid_odd, h1_114937, nCut, nCutRef, eff); 
  Get_m0_m12(file_114938, grid_even, h1_114938, nCut, nCutRef, eff); 
  Get_m0_m12(file_114939, grid_odd, h1_114939, nCut, nCutRef, eff); 
  Get_m0_m12(file_114940, grid_even, h1_114940, nCut, nCutRef, eff); 
  Get_m0_m12(file_114941, grid_odd, h1_114941, nCut, nCutRef, eff); 
  Get_m0_m12(file_114942, grid_even, h1_114942, nCut, nCutRef, eff);  
  Get_m0_m12(file_114943, grid_odd, h1_114943, nCut, nCutRef, eff); 
  Get_m0_m12(file_114944, grid_even, h1_114944, nCut, nCutRef, eff); 
  Get_m0_m12(file_114945, grid_odd, h1_114945, nCut, nCutRef, eff); 
  Get_m0_m12(file_114946, grid_even, h1_114946, nCut, nCutRef, eff); 
  Get_m0_m12(file_114947, grid_odd, h1_114947, nCut, nCutRef, eff); 
  Get_m0_m12(file_114948, grid_even, h1_114948, nCut, nCutRef, eff); 
  Get_m0_m12(file_114949, grid_odd, h1_114949, nCut, nCutRef, eff); 
  Get_m0_m12(file_114950, grid_even, h1_114950, nCut, nCutRef, eff); 
  Get_m0_m12(file_114951, grid_odd, h1_114951, nCut, nCutRef, eff); 
  Get_m0_m12(file_114952, grid_even, h1_114952, nCut, nCutRef, eff); 
  Get_m0_m12(file_114953, grid_odd, h1_114953, nCut, nCutRef, eff); 
  Get_m0_m12(file_114954, grid_even, h1_114954, nCut, nCutRef, eff); 
  Get_m0_m12(file_114955, grid_odd, h1_114955, nCut, nCutRef, eff); 
  Get_m0_m12(file_114956, grid_even, h1_114956, nCut, nCutRef, eff); 
  Get_m0_m12(file_114957, grid_odd, h1_114957, nCut, nCutRef, eff); 
  Get_m0_m12(file_114958, grid_even, h1_114958, nCut, nCutRef, eff); 
  Get_m0_m12(file_114959, grid_odd, h1_114959, nCut, nCutRef, eff); 
  Get_m0_m12(file_114960, grid_even, h1_114960, nCut, nCutRef, eff); 
  Get_m0_m12(file_114961, grid_odd, h1_114961, nCut, nCutRef, eff); 
  Get_m0_m12(file_114962, grid_even, h1_114962, nCut, nCutRef, eff); 
  Get_m0_m12(file_114963, grid_odd, h1_114963, nCut, nCutRef, eff); 
  Get_m0_m12(file_114964, grid_even, h1_114964, nCut, nCutRef, eff); 
#endif
#ifdef GRID1         //Phenogrid 1
  Get_m0_m12(file_114965, grid_odd, h1_114965, nCut, nCutRef, eff); 
  Get_m0_m12(file_114966, grid_even, h1_114966, nCut, nCutRef, eff); 
  Get_m0_m12(file_114967, grid_odd, h1_114967, nCut, nCutRef, eff); 
  Get_m0_m12(file_114968, grid_even, h1_114968, nCut, nCutRef, eff); 
  Get_m0_m12(file_114969, grid_odd, h1_114969, nCut, nCutRef, eff); 
  Get_m0_m12(file_114970, grid_even, h1_114970, nCut, nCutRef, eff); 
  Get_m0_m12(file_114971, grid_odd, h1_114971, nCut, nCutRef, eff); 
  Get_m0_m12(file_114972, grid_even, h1_114972, nCut, nCutRef, eff); 
  Get_m0_m12(file_114973, grid_odd, h1_114973, nCut, nCutRef, eff); 
  Get_m0_m12(file_114974, grid_even, h1_114974, nCut, nCutRef, eff); 
  Get_m0_m12(file_114975, grid_odd, h1_114975, nCut, nCutRef, eff); 
  Get_m0_m12(file_114976, grid_even, h1_114976, nCut, nCutRef, eff); 
  Get_m0_m12(file_114977, grid_odd, h1_114977, nCut, nCutRef, eff); 
  Get_m0_m12(file_114978, grid_even, h1_114978, nCut, nCutRef, eff); 
  Get_m0_m12(file_114979, grid_odd, h1_114979, nCut, nCutRef, eff); 
  Get_m0_m12(file_114980, grid_even, h1_114980, nCut, nCutRef, eff); 
  Get_m0_m12(file_114981, grid_odd, h1_114981, nCut, nCutRef, eff); 
  Get_m0_m12(file_114982, grid_even, h1_114982, nCut, nCutRef, eff); 
  Get_m0_m12(file_114983, grid_odd, h1_114983, nCut, nCutRef, eff); 
  Get_m0_m12(file_114984, grid_even, h1_114984, nCut, nCutRef, eff); 
  Get_m0_m12(file_114985, grid_odd, h1_114985, nCut, nCutRef, eff); 
  Get_m0_m12(file_114986, grid_even, h1_114986, nCut, nCutRef, eff); 
  Get_m0_m12(file_114987, grid_odd, h1_114987, nCut, nCutRef, eff); 
  Get_m0_m12(file_114988, grid_even, h1_114988, nCut, nCutRef, eff); 
  Get_m0_m12(file_114989, grid_odd, h1_114989, nCut, nCutRef, eff); 
  Get_m0_m12(file_114990, grid_even, h1_114990, nCut, nCutRef, eff); 
  Get_m0_m12(file_114991, grid_odd, h1_114991, nCut, nCutRef, eff); 
  Get_m0_m12(file_114992, grid_even, h1_114992, nCut, nCutRef, eff); 
  Get_m0_m12(file_114993, grid_odd, h1_114993, nCut, nCutRef, eff); 
  Get_m0_m12(file_114994, grid_even, h1_114994, nCut, nCutRef, eff); 
  Get_m0_m12(file_114995, grid_odd, h1_114995, nCut, nCutRef, eff); 
  Get_m0_m12(file_114996, grid_even, h1_114996, nCut, nCutRef, eff); 
#endif

#endif //cutflow

#endif //PHENO
#endif //MC
#endif

  return;
}



// NO PILEUP
double Normalize(int run, double lumi, TFile *file){

  TH1I* runNumber  = (TH1I*)(file ->Get("runNumber_histo")) ;  
  float Nevents = (float)(runNumber ->Integral());
  double mean = (runNumber ->GetMean());
  double norm = 1.;

// cross-sections from https://twiki.cern.ch/twiki/bin/view/AtlasProtected/TopMC2009

  double nb = 1.;
  double pb = 0.001;

// *lumi/Nevents
/*
if (run==107660){
 cout << "mean "<<mean <<endl;
 cout << " Nevents "<<Nevents<<endl;
}*/

double norm = -1;

//QCD 
if (run==108326) norm = (     75126.6 *pb*lumi/Nevents); 

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

//DIBOSON 
if (run==105985) norm = ( 44.9*0.3884 *pb *lumi/Nevents); 
if (run==105986) norm = ( 5.96*0.2123 *pb *lumi/Nevents); 
if (run==105987) norm = ( 18.0*0.3085 *pb * lumi/Nevents); 


//SU4 

if (run==106484) cout << "SU4 cross section (pb) 59.95"<<endl;
if (run==106484) norm = (59.95*pb *lumi/Nevents);//check
if (run==106480) norm = (52.8*pb *lumi/Nevents);

//T1
// ttbar with leptons
if (run==105200) norm = (160.79*0.556*pb *lumi/Nevents);// was 80.201*pb * 1.09
//fully hadronic ttbar
if (run==105204) norm = (160.79*0.444*pb *lumi/Nevents);//

 if (norm == -1.) {
   cout << "WARNING run "<<run<<" not in the list, returning 1"<<endl;
   norm = 1;
 }
 
 double norm1 = norm/lumi;
 //cout << "if (run=="<<run<<") norm = "<<norm1<<";"<<endl; 
 return norm;
}

#ifdef MSUGRA

void getHistoNorm(TH1D* h1, TH2F* h2, int run){

  double pb = 1.;
  //cout << "In histo.h:getHistoNorm lumi = "<<lumi<<" !!!!!!!! CHECK !!!!!!!   run "<<run<< endl; 
  double xsection=0.;
  double xsection_process=0.;
  
  h1->Reset();

  for(int i = binmin; i < binmax+1;i++){
    if (isChannel(i-1)){ // channel (or process)  = bin - 1

      TH1D* h1tmp = h2->ProjectionX("h1tmp", i, i, "e");
      Double_t nbin_content_ref  = h1tmp->GetBinContent(1); //get events in the first bin
      //cout << "nbin_content_ref "<<nbin_content_ref<<endl;
      get_cs(run,  &xsection , &xsection_process, i-1);   
      
      //h1->Add(h1tmp, xsection_process*pb*lumi/nbin_content_ref);
      double norm = 0;
      if (nbin_content_ref) norm = xsection_process*pb*lumi/nbin_content_ref;
      //cout << "i "<<i<<" xs "<<xsection_process<<" norm "<<norm<<endl;
      h1->Add(h1tmp, norm);
    }
  }
//  cout << h1->GetBinContent(1)<<endl; //get events in the first bin
  
  return;
}
#endif //MSUGRA

#ifdef PHENO

void getHistoNorm(TH1D* h1, TH2F* h2, int run){

  double pb = 1.;

  double xsection=0.;
  double xsection_process=0.;
  
  h1->Reset();

  for(int i = binmin; i < binmax+1;i++){
    if (isChannel(i-1)){ // channel (or process)  = bin - 1

      TH1D* h1tmp = h2->ProjectionX("h1tmp", i, i, "e");
      Double_t nbin_content_ref  = h1tmp->GetBinContent(1); //get events in the first bin
      
      get_cs(run,  &xsection , &xsection_process, i-1);   
      
      //h1->Add(h1tmp, xsection_process*pb*lumi/nbin_content_ref);
      double norm = 0;
      if (nbin_content_ref) norm = xsection_process*pb*lumi/nbin_content_ref;
      //if (i==5) cout << "i "<<i<<" xs "<<xsection_process<<" norm "<<norm<<endl;
      h1->Add(h1tmp, norm);
    }
  }
//  cout << h1->GetBinContent(1)<<endl; //get events in the first bin
  
  return;
}
#endif //PHENO
