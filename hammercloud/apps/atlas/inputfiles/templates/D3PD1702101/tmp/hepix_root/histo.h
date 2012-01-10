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

h1_114013  = (TH1I*)file_114013->Get(histo_string) ; 
h1_114014  = (TH1I*)file_114014->Get(histo_string) ; 
h1_114015  = (TH1I*)file_114015->Get(histo_string) ;
h1_114016  = (TH1I*)file_114016->Get(histo_string) ;
h1_114017  = (TH1I*)file_114017->Get(histo_string) ;
h1_114018  = (TH1I*)file_114018->Get(histo_string) ;
h1_114019  = (TH1I*)file_114019->Get(histo_string) ;
h1_114020  = (TH1I*)file_114020->Get(histo_string) ;
h1_114021  = (TH1I*)file_114021->Get(histo_string) ;
h1_114022  = (TH1I*)file_114022->Get(histo_string) ;
h1_114023  = (TH1I*)file_114023->Get(histo_string) ;
h1_114024  = (TH1I*)file_114024->Get(histo_string) ;
h1_114025  = (TH1I*)file_114025->Get(histo_string) ;
h1_114026  = (TH1I*)file_114026->Get(histo_string) ;
h1_114027  = (TH1I*)file_114027->Get(histo_string) ;
h1_114028  = (TH1I*)file_114028->Get(histo_string) ;
h1_114029  = (TH1I*)file_114029->Get(histo_string) ;
h1_114030  = (TH1I*)file_114030->Get(histo_string) ;
h1_114031  = (TH1I*)file_114031->Get(histo_string) ;
h1_114032  = (TH1I*)file_114032->Get(histo_string) ;
h1_114033  = (TH1I*)file_114033->Get(histo_string) ;
h1_114034  = (TH1I*)file_114034->Get(histo_string) ;
h1_114035  = (TH1I*)file_114035->Get(histo_string) ;
h1_114036  = (TH1I*)file_114036->Get(histo_string) ;
h1_114037  = (TH1I*)file_114037->Get(histo_string) ;
h1_114038  = (TH1I*)file_114038->Get(histo_string) ;
h1_114039  = (TH1I*)file_114039->Get(histo_string) ;
h1_114040  = (TH1I*)file_114040->Get(histo_string) ;
h1_114041  = (TH1I*)file_114041->Get(histo_string) ;
h1_114042  = (TH1I*)file_114042->Get(histo_string) ; 
h1_114043  = (TH1I*)file_114043->Get(histo_string) ;
h1_114044  = (TH1I*)file_114044->Get(histo_string) ;
h1_114045  = (TH1I*)file_114045->Get(histo_string) ;
h1_114046  = (TH1I*)file_114046->Get(histo_string) ;
h1_114047  = (TH1I*)file_114047->Get(histo_string) ;
h1_114048  = (TH1I*)file_114048->Get(histo_string) ;
h1_114049  = (TH1I*)file_114049->Get(histo_string) ;
h1_114050  = (TH1I*)file_114050->Get(histo_string) ;
h1_114051  = (TH1I*)file_114051->Get(histo_string) ;
h1_114052  = (TH1I*)file_114052->Get(histo_string) ;
h1_114053  = (TH1I*)file_114053->Get(histo_string) ;
h1_114054  = (TH1I*)file_114054->Get(histo_string) ;
h1_114055  = (TH1I*)file_114055->Get(histo_string) ;
h1_114056  = (TH1I*)file_114056->Get(histo_string) ;
h1_114057  = (TH1I*)file_114057->Get(histo_string) ;
h1_114058  = (TH1I*)file_114058->Get(histo_string) ;
h1_114059  = (TH1I*)file_114059->Get(histo_string) ;
h1_114060  = (TH1I*)file_114060->Get(histo_string) ;
h1_114061  = (TH1I*)file_114061->Get(histo_string) ;
h1_114062  = (TH1I*)file_114062->Get(histo_string) ;
h1_114063  = (TH1I*)file_114063->Get(histo_string) ;
h1_114064  = (TH1I*)file_114064->Get(histo_string) ;
h1_114065  = (TH1I*)file_114065->Get(histo_string) ;
h1_114066  = (TH1I*)file_114066->Get(histo_string) ;
h1_114067  = (TH1I*)file_114067->Get(histo_string) ;
h1_114068  = (TH1I*)file_114068->Get(histo_string) ;
h1_114069  = (TH1I*)file_114069->Get(histo_string) ;
h1_114070  = (TH1I*)file_114070->Get(histo_string) ;
h1_114071  = (TH1I*)file_114071->Get(histo_string) ;
h1_114072  = (TH1I*)file_114072->Get(histo_string) ;
h1_114073  = (TH1I*)file_114073->Get(histo_string) ;
h1_114074  = (TH1I*)file_114074->Get(histo_string) ;
h1_114075  = (TH1I*)file_114075->Get(histo_string) ;
h1_114076  = (TH1I*)file_114076->Get(histo_string) ;
h1_114077  = (TH1I*)file_114077->Get(histo_string) ;
h1_114078  = (TH1I*)file_114078->Get(histo_string) ;
h1_114079  = (TH1I*)file_114079->Get(histo_string) ;
h1_114080  = (TH1I*)file_114080->Get(histo_string) ;
h1_114081  = (TH1I*)file_114081->Get(histo_string) ;
h1_114082  = (TH1I*)file_114082->Get(histo_string) ;
h1_114083  = (TH1I*)file_114083->Get(histo_string) ;
h1_114084  = (TH1I*)file_114084->Get(histo_string) ;
h1_114085  = (TH1I*)file_114085->Get(histo_string) ;
h1_114086  = (TH1I*)file_114086->Get(histo_string) ;
h1_114087  = (TH1I*)file_114087->Get(histo_string) ;
h1_114088  = (TH1I*)file_114088->Get(histo_string) ;
h1_114089  = (TH1I*)file_114089->Get(histo_string) ;
h1_114090  = (TH1I*)file_114090->Get(histo_string) ;
h1_114091  = (TH1I*)file_114091->Get(histo_string) ;
h1_114092  = (TH1I*)file_114092->Get(histo_string) ;
h1_114093  = (TH1I*)file_114093->Get(histo_string) ;
h1_114094  = (TH1I*)file_114094->Get(histo_string) ;
h1_114095  = (TH1I*)file_114095->Get(histo_string) ;
h1_114096  = (TH1I*)file_114096->Get(histo_string) ;
h1_114097  = (TH1I*)file_114097->Get(histo_string) ;
h1_114098  = (TH1I*)file_114098->Get(histo_string) ;
h1_114099  = (TH1I*)file_114099->Get(histo_string) ;
h1_114100  = (TH1I*)file_114100->Get(histo_string) ;
h1_114101  = (TH1I*)file_114101->Get(histo_string) ;
h1_114102  = (TH1I*)file_114102->Get(histo_string) ;
h1_114103  = (TH1I*)file_114103->Get(histo_string) ;
h1_114104  = (TH1I*)file_114104->Get(histo_string) ;
h1_114105  = (TH1I*)file_114105->Get(histo_string) ;
h1_114106  = (TH1I*)file_114106->Get(histo_string) ;
h1_114107  = (TH1I*)file_114107->Get(histo_string) ;
h1_114108  = (TH1I*)file_114108->Get(histo_string) ;
h1_114109  = (TH1I*)file_114109->Get(histo_string) ;
h1_114110  = (TH1I*)file_114110->Get(histo_string) ;
h1_114111  = (TH1I*)file_114111->Get(histo_string) ;
h1_114112  = (TH1I*)file_114112->Get(histo_string) ;
h1_114113  = (TH1I*)file_114113->Get(histo_string) ;
h1_114114  = (TH1I*)file_114114->Get(histo_string) ;
h1_114115  = (TH1I*)file_114115->Get(histo_string) ;
h1_114116  = (TH1I*)file_114116->Get(histo_string) ;
h1_114117  = (TH1I*)file_114117->Get(histo_string) ;
h1_114118  = (TH1I*)file_114118->Get(histo_string) ;
h1_114119  = (TH1I*)file_114119->Get(histo_string) ;
h1_114120  = (TH1I*)file_114120->Get(histo_string) ;
h1_114121  = (TH1I*)file_114121->Get(histo_string) ;
h1_114122  = (TH1I*)file_114122->Get(histo_string) ;
h1_114123  = (TH1I*)file_114123->Get(histo_string) ;
h1_114124  = (TH1I*)file_114124->Get(histo_string) ;
h1_114125  = (TH1I*)file_114125->Get(histo_string) ;
h1_114126  = (TH1I*)file_114126->Get(histo_string) ;
h1_114127  = (TH1I*)file_114127->Get(histo_string) ;
h1_114128  = (TH1I*)file_114128->Get(histo_string) ;
h1_114129  = (TH1I*)file_114129->Get(histo_string) ;
h1_114130  = (TH1I*)file_114130->Get(histo_string) ;
h1_114131  = (TH1I*)file_114131->Get(histo_string) ;
h1_114132  = (TH1I*)file_114132->Get(histo_string) ;
h1_114133  = (TH1I*)file_114133->Get(histo_string) ;
h1_114134  = (TH1I*)file_114134->Get(histo_string) ;
h1_114135  = (TH1I*)file_114135->Get(histo_string) ;
h1_114136  = (TH1I*)file_114136->Get(histo_string) ;
h1_114137  = (TH1I*)file_114137->Get(histo_string) ;
h1_114138  = (TH1I*)file_114138->Get(histo_string) ;
h1_114139  = (TH1I*)file_114139->Get(histo_string) ;
h1_114140  = (TH1I*)file_114140->Get(histo_string) ;
h1_114141  = (TH1I*)file_114141->Get(histo_string) ;
h1_114142  = (TH1I*)file_114142->Get(histo_string) ; 
h1_114143  = (TH1I*)file_114143->Get(histo_string) ;
h1_114144  = (TH1I*)file_114144->Get(histo_string) ;
h1_114145  = (TH1I*)file_114145->Get(histo_string) ;
h1_114146  = (TH1I*)file_114146->Get(histo_string) ;
h1_114147  = (TH1I*)file_114147->Get(histo_string) ;
h1_114148  = (TH1I*)file_114148->Get(histo_string) ;
h1_114149  = (TH1I*)file_114149->Get(histo_string) ;
h1_114150  = (TH1I*)file_114150->Get(histo_string) ;
h1_114151  = (TH1I*)file_114151->Get(histo_string) ;
h1_114152  = (TH1I*)file_114152->Get(histo_string) ;
h1_114153  = (TH1I*)file_114153->Get(histo_string) ;
h1_114154  = (TH1I*)file_114154->Get(histo_string) ;
h1_114155  = (TH1I*)file_114155->Get(histo_string) ;
h1_114156  = (TH1I*)file_114156->Get(histo_string) ;
h1_114157  = (TH1I*)file_114157->Get(histo_string) ;
h1_114158  = (TH1I*)file_114158->Get(histo_string) ;
h1_114159  = (TH1I*)file_114159->Get(histo_string) ;
h1_114160  = (TH1I*)file_114160->Get(histo_string) ;
h1_114161  = (TH1I*)file_114161->Get(histo_string) ;
h1_114162  = (TH1I*)file_114162->Get(histo_string) ;
h1_114163  = (TH1I*)file_114163->Get(histo_string) ;
h1_114164  = (TH1I*)file_114164->Get(histo_string) ;
h1_114165  = (TH1I*)file_114165->Get(histo_string) ;
h1_114166  = (TH1I*)file_114166->Get(histo_string) ;
h1_114167  = (TH1I*)file_114167->Get(histo_string) ;
h1_114168  = (TH1I*)file_114168->Get(histo_string) ;
h1_114169  = (TH1I*)file_114169->Get(histo_string) ;
h1_114170  = (TH1I*)file_114170->Get(histo_string) ;
h1_114171  = (TH1I*)file_114171->Get(histo_string) ;
h1_114172  = (TH1I*)file_114172->Get(histo_string) ;
h1_114173  = (TH1I*)file_114173->Get(histo_string) ;
h1_114174  = (TH1I*)file_114174->Get(histo_string) ;
h1_114175  = (TH1I*)file_114175->Get(histo_string) ;
h1_114176  = (TH1I*)file_114176->Get(histo_string) ;
h1_114177  = (TH1I*)file_114177->Get(histo_string) ;
h1_114178  = (TH1I*)file_114178->Get(histo_string) ;
h1_114179  = (TH1I*)file_114179->Get(histo_string) ;
h1_114180  = (TH1I*)file_114180->Get(histo_string) ;
h1_114181  = (TH1I*)file_114181->Get(histo_string) ;
h1_114182  = (TH1I*)file_114182->Get(histo_string) ;
h1_114183  = (TH1I*)file_114183->Get(histo_string) ;
h1_114184  = (TH1I*)file_114184->Get(histo_string) ;
h1_114185  = (TH1I*)file_114185->Get(histo_string) ;
h1_114186  = (TH1I*)file_114186->Get(histo_string) ;
h1_114187  = (TH1I*)file_114187->Get(histo_string) ;
h1_114188  = (TH1I*)file_114188->Get(histo_string) ;
h1_114189  = (TH1I*)file_114189->Get(histo_string) ;
h1_114190  = (TH1I*)file_114190->Get(histo_string) ;
h1_114191  = (TH1I*)file_114191->Get(histo_string) ;
h1_114192  = (TH1I*)file_114192->Get(histo_string) ;
h1_114193  = (TH1I*)file_114193->Get(histo_string) ;
h1_114194  = (TH1I*)file_114194->Get(histo_string) ;
h1_114195  = (TH1I*)file_114195->Get(histo_string) ;
h1_114196  = (TH1I*)file_114196->Get(histo_string) ;
h1_114197  = (TH1I*)file_114197->Get(histo_string) ;
h1_114198  = (TH1I*)file_114198->Get(histo_string) ;
h1_114199  = (TH1I*)file_114199->Get(histo_string) ;
h1_114200  = (TH1I*)file_114200->Get(histo_string) ;
h1_114201  = (TH1I*)file_114201->Get(histo_string) ;
h1_114202  = (TH1I*)file_114202->Get(histo_string) ;
h1_114203  = (TH1I*)file_114203->Get(histo_string) ;
h1_114204  = (TH1I*)file_114204->Get(histo_string) ;
h1_114205  = (TH1I*)file_114205->Get(histo_string) ;
h1_114206  = (TH1I*)file_114206->Get(histo_string) ;
h1_114207  = (TH1I*)file_114207->Get(histo_string) ;
h1_114208  = (TH1I*)file_114208->Get(histo_string) ;
h1_114209  = (TH1I*)file_114209->Get(histo_string) ;
h1_114210  = (TH1I*)file_114210->Get(histo_string) ;
h1_114211  = (TH1I*)file_114211->Get(histo_string) ;
h1_114212  = (TH1I*)file_114212->Get(histo_string) ;
h1_114213  = (TH1I*)file_114213->Get(histo_string) ;
h1_114214  = (TH1I*)file_114214->Get(histo_string) ;
h1_114215  = (TH1I*)file_114215->Get(histo_string) ;
h1_114216  = (TH1I*)file_114216->Get(histo_string) ;
#endif
#ifdef H2D
  h2_114013 = (TH2F*)file_114013->Get(histo_string);   
  h2_114014 = (TH2F*)file_114014->Get(histo_string);   
  h2_114015 = (TH2F*)file_114015->Get(histo_string);   
  h2_114016 = (TH2F*)file_114016->Get(histo_string);   
  h2_114017 = (TH2F*)file_114017->Get(histo_string);   
  h2_114018 = (TH2F*)file_114018->Get(histo_string);   
  h2_114019 = (TH2F*)file_114019->Get(histo_string);    
  h2_114020 = (TH2F*)file_114020->Get(histo_string);    
  h2_114021 = (TH2F*)file_114021->Get(histo_string);    
  h2_114022 = (TH2F*)file_114022->Get(histo_string);    
  h2_114023 = (TH2F*)file_114023->Get(histo_string);   
  h2_114024 = (TH2F*)file_114024->Get(histo_string);   
  h2_114025 = (TH2F*)file_114025->Get(histo_string);     
  h2_114026 = (TH2F*)file_114026->Get(histo_string);     
  h2_114027 = (TH2F*)file_114027->Get(histo_string);     
  h2_114028 = (TH2F*)file_114028->Get(histo_string);     
  h2_114029 = (TH2F*)file_114029->Get(histo_string);     
  h2_114030 = (TH2F*)file_114030->Get(histo_string);     
  h2_114031 = (TH2F*)file_114031->Get(histo_string);    
  h2_114032 = (TH2F*)file_114032->Get(histo_string);     
  h2_114033 = (TH2F*)file_114033->Get(histo_string);     
  h2_114034 = (TH2F*)file_114034->Get(histo_string);   
  h2_114035 = (TH2F*)file_114035->Get(histo_string);     
  h2_114036 = (TH2F*)file_114036->Get(histo_string);    
  h2_114037 = (TH2F*)file_114037->Get(histo_string);   
  h2_114038 = (TH2F*)file_114038->Get(histo_string);   
  h2_114039 = (TH2F*)file_114039->Get(histo_string);   
  h2_114040 = (TH2F*)file_114040->Get(histo_string);   
  h2_114041 = (TH2F*)file_114041->Get(histo_string);   
  h2_114042 = (TH2F*)file_114042->Get(histo_string);     
  h2_114043 = (TH2F*)file_114043->Get(histo_string);   
  h2_114044 = (TH2F*)file_114044->Get(histo_string);   
  h2_114045 = (TH2F*)file_114045->Get(histo_string);   
  h2_114046 = (TH2F*)file_114046->Get(histo_string);   
  h2_114047 = (TH2F*)file_114047->Get(histo_string);   
  h2_114048 = (TH2F*)file_114048->Get(histo_string);   
  h2_114049 = (TH2F*)file_114049->Get(histo_string);   
  h2_114050 = (TH2F*)file_114050->Get(histo_string);   
  h2_114051 = (TH2F*)file_114051->Get(histo_string);   
  h2_114052 = (TH2F*)file_114052->Get(histo_string);   
  h2_114053 = (TH2F*)file_114053->Get(histo_string);   
  h2_114054 = (TH2F*)file_114054->Get(histo_string);   
  h2_114055 = (TH2F*)file_114055->Get(histo_string);   
  h2_114056 = (TH2F*)file_114056->Get(histo_string);   
  h2_114057 = (TH2F*)file_114057->Get(histo_string);   
  h2_114058 = (TH2F*)file_114058->Get(histo_string);   
  h2_114059 = (TH2F*)file_114059->Get(histo_string);    
  h2_114060 = (TH2F*)file_114060->Get(histo_string);    
  h2_114061 = (TH2F*)file_114061->Get(histo_string);    
  h2_114062 = (TH2F*)file_114062->Get(histo_string);    
  h2_114063 = (TH2F*)file_114063->Get(histo_string);    
  h2_114064 = (TH2F*)file_114064->Get(histo_string);    
  h2_114065 = (TH2F*)file_114065->Get(histo_string);    
  h2_114066 = (TH2F*)file_114066->Get(histo_string);    
  h2_114067 = (TH2F*)file_114067->Get(histo_string);    
  h2_114068 = (TH2F*)file_114068->Get(histo_string);    
  h2_114069 = (TH2F*)file_114069->Get(histo_string);    
  h2_114070 = (TH2F*)file_114070->Get(histo_string);    
  h2_114071 = (TH2F*)file_114071->Get(histo_string);    
  h2_114072 = (TH2F*)file_114072->Get(histo_string);    
  h2_114073 = (TH2F*)file_114073->Get(histo_string);    
  h2_114074 = (TH2F*)file_114074->Get(histo_string);    
  h2_114075 = (TH2F*)file_114075->Get(histo_string);    
  h2_114076 = (TH2F*)file_114076->Get(histo_string);    
  h2_114077 = (TH2F*)file_114077->Get(histo_string);    
  h2_114078 = (TH2F*)file_114078->Get(histo_string);    
  h2_114079 = (TH2F*)file_114079->Get(histo_string);    
  h2_114080 = (TH2F*)file_114080->Get(histo_string);    
  h2_114081 = (TH2F*)file_114081->Get(histo_string);    
  h2_114082 = (TH2F*)file_114082->Get(histo_string);    
  h2_114083 = (TH2F*)file_114083->Get(histo_string);    
  h2_114084 = (TH2F*)file_114084->Get(histo_string);    
  h2_114085 = (TH2F*)file_114085->Get(histo_string);     
  h2_114086 = (TH2F*)file_114086->Get(histo_string);    
  h2_114087 = (TH2F*)file_114087->Get(histo_string);     
  h2_114088 = (TH2F*)file_114088->Get(histo_string);     
  h2_114089 = (TH2F*)file_114089->Get(histo_string);     
  h2_114090 = (TH2F*)file_114090->Get(histo_string);     
  h2_114091 = (TH2F*)file_114091->Get(histo_string);       
  h2_114092 = (TH2F*)file_114092->Get(histo_string);       
  h2_114093 = (TH2F*)file_114093->Get(histo_string);       
  h2_114094 = (TH2F*)file_114094->Get(histo_string);       
  h2_114095 = (TH2F*)file_114095->Get(histo_string);       
  h2_114096 = (TH2F*)file_114096->Get(histo_string);       
  h2_114097 = (TH2F*)file_114097->Get(histo_string);       
  h2_114098 = (TH2F*)file_114098->Get(histo_string);       
  h2_114099 = (TH2F*)file_114099->Get(histo_string);       
  h2_114100 = (TH2F*)file_114100->Get(histo_string);       
  h2_114101 = (TH2F*)file_114101->Get(histo_string);       
  h2_114102 = (TH2F*)file_114102->Get(histo_string);      
  h2_114103 = (TH2F*)file_114103->Get(histo_string);       
  h2_114104 = (TH2F*)file_114104->Get(histo_string);       
  h2_114105 = (TH2F*)file_114105->Get(histo_string);       
  h2_114106 = (TH2F*)file_114106->Get(histo_string);       
  h2_114107 = (TH2F*)file_114107->Get(histo_string);       
  h2_114108 = (TH2F*)file_114108->Get(histo_string);       
  h2_114109 = (TH2F*)file_114109->Get(histo_string);       
  h2_114110 = (TH2F*)file_114110->Get(histo_string);       
  h2_114111 = (TH2F*)file_114111->Get(histo_string);       
  h2_114112 = (TH2F*)file_114112->Get(histo_string);       
  h2_114113 = (TH2F*)file_114113->Get(histo_string);       
  h2_114114 = (TH2F*)file_114114->Get(histo_string);       
  h2_114115 = (TH2F*)file_114115->Get(histo_string);       
  h2_114116 = (TH2F*)file_114116->Get(histo_string);       
  h2_114117 = (TH2F*)file_114117->Get(histo_string);       
  h2_114118 = (TH2F*)file_114118->Get(histo_string);       
  h2_114119 = (TH2F*)file_114119->Get(histo_string);       
  h2_114120 = (TH2F*)file_114120->Get(histo_string);       
  h2_114121 = (TH2F*)file_114121->Get(histo_string);       
  h2_114122 = (TH2F*)file_114122->Get(histo_string);       
  h2_114123 = (TH2F*)file_114123->Get(histo_string);       
  h2_114124 = (TH2F*)file_114124->Get(histo_string);       
  h2_114125 = (TH2F*)file_114125->Get(histo_string);       
  h2_114126 = (TH2F*)file_114126->Get(histo_string);       
  h2_114127 = (TH2F*)file_114127->Get(histo_string);       
  h2_114128 = (TH2F*)file_114128->Get(histo_string);       
  h2_114129 = (TH2F*)file_114129->Get(histo_string);       
  h2_114130 = (TH2F*)file_114130->Get(histo_string);       
  h2_114131 = (TH2F*)file_114131->Get(histo_string);       
  h2_114132 = (TH2F*)file_114132->Get(histo_string);       
  h2_114133 = (TH2F*)file_114133->Get(histo_string);       
  h2_114134 = (TH2F*)file_114134->Get(histo_string);       
  h2_114135 = (TH2F*)file_114135->Get(histo_string);       
  h2_114136 = (TH2F*)file_114136->Get(histo_string);       
  h2_114137 = (TH2F*)file_114137->Get(histo_string);       
  h2_114138 = (TH2F*)file_114138->Get(histo_string);       
  h2_114139 = (TH2F*)file_114139->Get(histo_string);       
  h2_114140 = (TH2F*)file_114140->Get(histo_string);       
  h2_114141 = (TH2F*)file_114141->Get(histo_string);       
  h2_114142 = (TH2F*)file_114142->Get(histo_string);       
  h2_114143 = (TH2F*)file_114143->Get(histo_string);       
  h2_114144 = (TH2F*)file_114144->Get(histo_string);       
  h2_114145 = (TH2F*)file_114145->Get(histo_string);       
  h2_114146 = (TH2F*)file_114146->Get(histo_string);       
  h2_114147 = (TH2F*)file_114147->Get(histo_string);       
  h2_114148 = (TH2F*)file_114148->Get(histo_string);       
  h2_114149 = (TH2F*)file_114149->Get(histo_string);	
  h2_114150 = (TH2F*)file_114150->Get(histo_string);	
  h2_114151 = (TH2F*)file_114151->Get(histo_string);	
  h2_114152 = (TH2F*)file_114152->Get(histo_string);	
  h2_114153 = (TH2F*)file_114153->Get(histo_string);	
  h2_114154 = (TH2F*)file_114154->Get(histo_string);	
  h2_114155 = (TH2F*)file_114155->Get(histo_string);     
  h2_114156 = (TH2F*)file_114156->Get(histo_string);	
  h2_114157 = (TH2F*)file_114157->Get(histo_string);     
  h2_114158 = (TH2F*)file_114158->Get(histo_string);	
  h2_114159 = (TH2F*)file_114159->Get(histo_string);     
  h2_114160 = (TH2F*)file_114160->Get(histo_string);	
  h2_114161 = (TH2F*)file_114161->Get(histo_string);	
  h2_114162 = (TH2F*)file_114162->Get(histo_string);	
  h2_114163 = (TH2F*)file_114163->Get(histo_string);	
  h2_114164 = (TH2F*)file_114164->Get(histo_string);	
  h2_114165 = (TH2F*)file_114165->Get(histo_string);	
  h2_114166 = (TH2F*)file_114166->Get(histo_string);	
  h2_114167 = (TH2F*)file_114167->Get(histo_string);	
  h2_114168 = (TH2F*)file_114168->Get(histo_string);	
  h2_114169 = (TH2F*)file_114169->Get(histo_string);	
  h2_114170 = (TH2F*)file_114170->Get(histo_string);	
  h2_114171 = (TH2F*)file_114171->Get(histo_string);	
  h2_114172 = (TH2F*)file_114172->Get(histo_string);	
  h2_114173 = (TH2F*)file_114173->Get(histo_string);	
  h2_114174 = (TH2F*)file_114174->Get(histo_string);	
  h2_114175 = (TH2F*)file_114175->Get(histo_string);	
  h2_114176 = (TH2F*)file_114176->Get(histo_string);	
  h2_114177 = (TH2F*)file_114177->Get(histo_string);	
  h2_114178 = (TH2F*)file_114178->Get(histo_string);	
  h2_114179 = (TH2F*)file_114179->Get(histo_string);       
  h2_114180 = (TH2F*)file_114180->Get(histo_string);       
  h2_114181 = (TH2F*)file_114181->Get(histo_string);       
  h2_114182 = (TH2F*)file_114182->Get(histo_string);       
  h2_114183 = (TH2F*)file_114183->Get(histo_string);       
  h2_114184 = (TH2F*)file_114184->Get(histo_string);       
  h2_114185 = (TH2F*)file_114185->Get(histo_string);       
  h2_114186 = (TH2F*)file_114186->Get(histo_string);       
  h2_114187 = (TH2F*)file_114187->Get(histo_string);       
  h2_114188 = (TH2F*)file_114188->Get(histo_string);       
  h2_114189 = (TH2F*)file_114189->Get(histo_string);   
  h2_114190 = (TH2F*)file_114190->Get(histo_string);   
  h2_114191 = (TH2F*)file_114191->Get(histo_string);   
  h2_114192 = (TH2F*)file_114192->Get(histo_string);   
  h2_114193 = (TH2F*)file_114193->Get(histo_string);   
  h2_114194 = (TH2F*)file_114194->Get(histo_string);   
  h2_114195 = (TH2F*)file_114195->Get(histo_string);   
  h2_114196 = (TH2F*)file_114196->Get(histo_string);   
  h2_114197 = (TH2F*)file_114197->Get(histo_string);   
  h2_114198 = (TH2F*)file_114198->Get(histo_string);   
  h2_114199 = (TH2F*)file_114199->Get(histo_string);   
  h2_114200 = (TH2F*)file_114200->Get(histo_string);   
  h2_114201 = (TH2F*)file_114201->Get(histo_string);   
  h2_114202 = (TH2F*)file_114202->Get(histo_string);  
  h2_114203 = (TH2F*)file_114203->Get(histo_string);   
  h2_114204 = (TH2F*)file_114204->Get(histo_string);   
  h2_114205 = (TH2F*)file_114205->Get(histo_string);   
  h2_114206 = (TH2F*)file_114206->Get(histo_string);   
  h2_114207 = (TH2F*)file_114207->Get(histo_string);   
  h2_114208 = (TH2F*)file_114208->Get(histo_string);  
  h2_114209 = (TH2F*)file_114209->Get(histo_string);  
  h2_114210 = (TH2F*)file_114210->Get(histo_string);  
  h2_114211 = (TH2F*)file_114211->Get(histo_string);  
  h2_114212 = (TH2F*)file_114212->Get(histo_string);  
  h2_114213 = (TH2F*)file_114213->Get(histo_string);  
  h2_114214 = (TH2F*)file_114214->Get(histo_string);   
  h2_114215 = (TH2F*)file_114215->Get(histo_string);  
  h2_114216 = (TH2F*)file_114216->Get(histo_string);  

  h1_114013 = h2_114013->ProjectionX("h1_114013", binmin, binmax, "e");
  h1_114014 = h2_114014->ProjectionX("h1_114014", binmin, binmax, "e");
  h1_114015 = h2_114015->ProjectionX("h1_114015", binmin, binmax, "e");
  h1_114016 = h2_114016->ProjectionX("h1_114016", binmin, binmax, "e");
  h1_114017 = h2_114017->ProjectionX("h1_114017", binmin, binmax, "e");
  h1_114018 = h2_114018->ProjectionX("h1_114018", binmin, binmax, "e");
  h1_114019 = h2_114019->ProjectionX("h1_114019", binmin, binmax, "e");
  h1_114020 = h2_114020->ProjectionX("h1_114020", binmin, binmax, "e");
  h1_114021 = h2_114021->ProjectionX("h1_114021", binmin, binmax, "e");
  h1_114022 = h2_114022->ProjectionX("h1_114022", binmin, binmax, "e");
  h1_114023 = h2_114023->ProjectionX("h1_114023", binmin, binmax, "e");
  h1_114024 = h2_114024->ProjectionX("h1_114024", binmin, binmax, "e");
  h1_114025 = h2_114025->ProjectionX("h1_114025", binmin, binmax, "e");
  h1_114026 = h2_114026->ProjectionX("h1_114026", binmin, binmax, "e");
  h1_114027 = h2_114027->ProjectionX("h1_114027", binmin, binmax, "e");
  h1_114028 = h2_114028->ProjectionX("h1_114028", binmin, binmax, "e");
  h1_114029 = h2_114029->ProjectionX("h1_114029", binmin, binmax, "e");
  h1_114030 = h2_114030->ProjectionX("h1_114030", binmin, binmax, "e");
  h1_114031 = h2_114031->ProjectionX("h1_114031", binmin, binmax, "e");
  h1_114032 = h2_114032->ProjectionX("h1_114032", binmin, binmax, "e");
  h1_114033 = h2_114033->ProjectionX("h1_114033", binmin, binmax, "e");
  h1_114034 = h2_114034->ProjectionX("h1_114034", binmin, binmax, "e");
  h1_114035 = h2_114035->ProjectionX("h1_114035", binmin, binmax, "e");
  h1_114036 = h2_114036->ProjectionX("h1_114036", binmin, binmax, "e");
  h1_114037 = h2_114037->ProjectionX("h1_114037", binmin, binmax, "e");
  h1_114038 = h2_114038->ProjectionX("h1_114038", binmin, binmax, "e");
  h1_114039 = h2_114039->ProjectionX("h1_114039", binmin, binmax, "e");
  h1_114040 = h2_114040->ProjectionX("h1_114040", binmin, binmax, "e");
  h1_114041 = h2_114041->ProjectionX("h1_114041", binmin, binmax, "e");
  h1_114042 = h2_114042->ProjectionX("h1_114042", binmin, binmax, "e");
  h1_114043 = h2_114043->ProjectionX("h1_114043", binmin, binmax, "e");
  h1_114044 = h2_114044->ProjectionX("h1_114044", binmin, binmax, "e");
  h1_114045 = h2_114045->ProjectionX("h1_114045", binmin, binmax, "e");
  h1_114046 = h2_114046->ProjectionX("h1_114046", binmin, binmax, "e");
  h1_114047 = h2_114047->ProjectionX("h1_114047", binmin, binmax, "e");
  h1_114048 = h2_114048->ProjectionX("h1_114048", binmin, binmax, "e");
  h1_114049 = h2_114049->ProjectionX("h1_114049", binmin, binmax, "e");
  h1_114050 = h2_114050->ProjectionX("h1_114050", binmin, binmax, "e");
  h1_114051 = h2_114051->ProjectionX("h1_114051", binmin, binmax, "e");
  h1_114052 = h2_114052->ProjectionX("h1_114052", binmin, binmax, "e");
  h1_114053 = h2_114053->ProjectionX("h1_114053", binmin, binmax, "e");
  h1_114054 = h2_114054->ProjectionX("h1_114054", binmin, binmax, "e");
  h1_114055 = h2_114055->ProjectionX("h1_114055", binmin, binmax, "e");
  h1_114056 = h2_114056->ProjectionX("h1_114056", binmin, binmax, "e");
  h1_114057 = h2_114057->ProjectionX("h1_114057", binmin, binmax, "e");
  h1_114058 = h2_114058->ProjectionX("h1_114058", binmin, binmax, "e");
  h1_114059 = h2_114059->ProjectionX("h1_114059", binmin, binmax, "e");
  h1_114060 = h2_114060->ProjectionX("h1_114060", binmin, binmax, "e");
  h1_114061 = h2_114061->ProjectionX("h1_114061", binmin, binmax, "e");
  h1_114062 = h2_114062->ProjectionX("h1_114062", binmin, binmax, "e");
  h1_114063 = h2_114063->ProjectionX("h1_114063", binmin, binmax, "e");
  h1_114064 = h2_114064->ProjectionX("h1_114064", binmin, binmax, "e");
  h1_114065 = h2_114065->ProjectionX("h1_114065", binmin, binmax, "e");
  h1_114066 = h2_114066->ProjectionX("h1_114066", binmin, binmax, "e");
  h1_114067 = h2_114067->ProjectionX("h1_114067", binmin, binmax, "e");
  h1_114068 = h2_114068->ProjectionX("h1_114068", binmin, binmax, "e");
  h1_114069 = h2_114069->ProjectionX("h1_114069", binmin, binmax, "e");
  h1_114070 = h2_114070->ProjectionX("h1_114070", binmin, binmax, "e");
  h1_114071 = h2_114071->ProjectionX("h1_114071", binmin, binmax, "e");
  h1_114072 = h2_114072->ProjectionX("h1_114072", binmin, binmax, "e");
  h1_114073 = h2_114073->ProjectionX("h1_114073", binmin, binmax, "e");
  h1_114074 = h2_114074->ProjectionX("h1_114074", binmin, binmax, "e");
  h1_114075 = h2_114075->ProjectionX("h1_114075", binmin, binmax, "e");
  h1_114076 = h2_114076->ProjectionX("h1_114076", binmin, binmax, "e");
  h1_114077 = h2_114077->ProjectionX("h1_114077", binmin, binmax, "e");
  h1_114078 = h2_114078->ProjectionX("h1_114078", binmin, binmax, "e");
  h1_114079 = h2_114079->ProjectionX("h1_114079", binmin, binmax, "e");
  h1_114080 = h2_114080->ProjectionX("h1_114080", binmin, binmax, "e");
  h1_114081 = h2_114081->ProjectionX("h1_114081", binmin, binmax, "e");
  h1_114082 = h2_114082->ProjectionX("h1_114082", binmin, binmax, "e");
  h1_114083 = h2_114083->ProjectionX("h1_114083", binmin, binmax, "e");
  h1_114084 = h2_114084->ProjectionX("h1_114084", binmin, binmax, "e");
  h1_114085 = h2_114085->ProjectionX("h1_114085", binmin, binmax, "e");
  h1_114086 = h2_114086->ProjectionX("h1_114086", binmin, binmax, "e");
  h1_114087 = h2_114087->ProjectionX("h1_114087", binmin, binmax, "e");
  h1_114088 = h2_114088->ProjectionX("h1_114088", binmin, binmax, "e");
  h1_114089 = h2_114089->ProjectionX("h1_114089", binmin, binmax, "e");
  h1_114090 = h2_114090->ProjectionX("h1_114090", binmin, binmax, "e");
  h1_114091 = h2_114091->ProjectionX("h1_114091", binmin, binmax, "e");
  h1_114092 = h2_114092->ProjectionX("h1_114092", binmin, binmax, "e");
  h1_114093 = h2_114093->ProjectionX("h1_114093", binmin, binmax, "e");
  h1_114094 = h2_114094->ProjectionX("h1_114094", binmin, binmax, "e");
  h1_114095 = h2_114095->ProjectionX("h1_114095", binmin, binmax, "e");
  h1_114096 = h2_114096->ProjectionX("h1_114096", binmin, binmax, "e");
  h1_114097 = h2_114097->ProjectionX("h1_114097", binmin, binmax, "e");
  h1_114098 = h2_114098->ProjectionX("h1_114098", binmin, binmax, "e");
  h1_114099 = h2_114099->ProjectionX("h1_114099", binmin, binmax, "e");
  h1_114100 = h2_114100->ProjectionX("h1_114100", binmin, binmax, "e");
  h1_114101 = h2_114101->ProjectionX("h1_114101", binmin, binmax, "e");
  h1_114102 = h2_114102->ProjectionX("h1_114102", binmin, binmax, "e");
  h1_114103 = h2_114103->ProjectionX("h1_114103", binmin, binmax, "e");
  h1_114104 = h2_114104->ProjectionX("h1_114104", binmin, binmax, "e");
  h1_114105 = h2_114105->ProjectionX("h1_114105", binmin, binmax, "e");
  h1_114106 = h2_114106->ProjectionX("h1_114106", binmin, binmax, "e");
  h1_114107 = h2_114107->ProjectionX("h1_114107", binmin, binmax, "e");
  h1_114108 = h2_114108->ProjectionX("h1_114108", binmin, binmax, "e");
  h1_114109 = h2_114109->ProjectionX("h1_114109", binmin, binmax, "e");
  h1_114110 = h2_114110->ProjectionX("h1_114110", binmin, binmax, "e");
  h1_114111 = h2_114111->ProjectionX("h1_114111", binmin, binmax, "e");
  h1_114112 = h2_114112->ProjectionX("h1_114112", binmin, binmax, "e");
  h1_114113 = h2_114113->ProjectionX("h1_114113", binmin, binmax, "e");
  h1_114114 = h2_114114->ProjectionX("h1_114114", binmin, binmax, "e");
  h1_114115 = h2_114115->ProjectionX("h1_114115", binmin, binmax, "e");
  h1_114116 = h2_114116->ProjectionX("h1_114116", binmin, binmax, "e");
  h1_114117 = h2_114117->ProjectionX("h1_114117", binmin, binmax, "e");
  h1_114118 = h2_114118->ProjectionX("h1_114118", binmin, binmax, "e");
  h1_114119 = h2_114119->ProjectionX("h1_114119", binmin, binmax, "e");
  h1_114120 = h2_114120->ProjectionX("h1_114120", binmin, binmax, "e");
  h1_114121 = h2_114121->ProjectionX("h1_114121", binmin, binmax, "e");
  h1_114122 = h2_114122->ProjectionX("h1_114122", binmin, binmax, "e");
  h1_114123 = h2_114123->ProjectionX("h1_114123", binmin, binmax, "e");
  h1_114124 = h2_114124->ProjectionX("h1_114124", binmin, binmax, "e");
  h1_114125 = h2_114125->ProjectionX("h1_114125", binmin, binmax, "e");
  h1_114126 = h2_114126->ProjectionX("h1_114126", binmin, binmax, "e");
  h1_114127 = h2_114127->ProjectionX("h1_114127", binmin, binmax, "e");
  h1_114128 = h2_114128->ProjectionX("h1_114128", binmin, binmax, "e");
  h1_114129 = h2_114129->ProjectionX("h1_114129", binmin, binmax, "e");
  h1_114130 = h2_114130->ProjectionX("h1_114130", binmin, binmax, "e");
  h1_114131 = h2_114131->ProjectionX("h1_114131", binmin, binmax, "e");
  h1_114132 = h2_114132->ProjectionX("h1_114132", binmin, binmax, "e");
  h1_114133 = h2_114133->ProjectionX("h1_114133", binmin, binmax, "e");
  h1_114134 = h2_114134->ProjectionX("h1_114134", binmin, binmax, "e");
  h1_114135 = h2_114135->ProjectionX("h1_114135", binmin, binmax, "e");
  h1_114136 = h2_114136->ProjectionX("h1_114136", binmin, binmax, "e");
  h1_114137 = h2_114137->ProjectionX("h1_114137", binmin, binmax, "e");
  h1_114138 = h2_114138->ProjectionX("h1_114138", binmin, binmax, "e");
  h1_114139 = h2_114139->ProjectionX("h1_114139", binmin, binmax, "e");
  h1_114140 = h2_114140->ProjectionX("h1_114140", binmin, binmax, "e");
  h1_114141 = h2_114141->ProjectionX("h1_114141", binmin, binmax, "e");
  h1_114142 = h2_114142->ProjectionX("h1_114142", binmin, binmax, "e");
  h1_114143 = h2_114143->ProjectionX("h1_114143", binmin, binmax, "e");
  h1_114144 = h2_114144->ProjectionX("h1_114144", binmin, binmax, "e");
  h1_114145 = h2_114145->ProjectionX("h1_114145", binmin, binmax, "e");
  h1_114146 = h2_114146->ProjectionX("h1_114146", binmin, binmax, "e");
  h1_114147 = h2_114147->ProjectionX("h1_114147", binmin, binmax, "e");
  h1_114148 = h2_114148->ProjectionX("h1_114148", binmin, binmax, "e");
  h1_114149 = h2_114149->ProjectionX("h1_114149", binmin, binmax, "e");
  h1_114150 = h2_114150->ProjectionX("h1_114150", binmin, binmax, "e");
  h1_114151 = h2_114151->ProjectionX("h1_114151", binmin, binmax, "e");
  h1_114152 = h2_114152->ProjectionX("h1_114152", binmin, binmax, "e");
  h1_114153 = h2_114153->ProjectionX("h1_114153", binmin, binmax, "e");
  h1_114154 = h2_114154->ProjectionX("h1_114154", binmin, binmax, "e");
  h1_114155 = h2_114155->ProjectionX("h1_114155", binmin, binmax, "e");
  h1_114156 = h2_114156->ProjectionX("h1_114156", binmin, binmax, "e");
  h1_114157 = h2_114157->ProjectionX("h1_114157", binmin, binmax, "e");
  h1_114158 = h2_114158->ProjectionX("h1_114158", binmin, binmax, "e");
  h1_114159 = h2_114159->ProjectionX("h1_114159", binmin, binmax, "e");
  h1_114160 = h2_114160->ProjectionX("h1_114160", binmin, binmax, "e");
  h1_114161 = h2_114161->ProjectionX("h1_114161", binmin, binmax, "e");
  h1_114162 = h2_114162->ProjectionX("h1_114162", binmin, binmax, "e");
  h1_114163 = h2_114163->ProjectionX("h1_114163", binmin, binmax, "e");
  h1_114164 = h2_114164->ProjectionX("h1_114164", binmin, binmax, "e");
  h1_114165 = h2_114165->ProjectionX("h1_114165", binmin, binmax, "e");
  h1_114166 = h2_114166->ProjectionX("h1_114166", binmin, binmax, "e");
  h1_114167 = h2_114167->ProjectionX("h1_114167", binmin, binmax, "e");
  h1_114168 = h2_114168->ProjectionX("h1_114168", binmin, binmax, "e");
  h1_114169 = h2_114169->ProjectionX("h1_114169", binmin, binmax, "e");
  h1_114170 = h2_114170->ProjectionX("h1_114170", binmin, binmax, "e");
  h1_114171 = h2_114171->ProjectionX("h1_114171", binmin, binmax, "e");
  h1_114172 = h2_114172->ProjectionX("h1_114172", binmin, binmax, "e");
  h1_114173 = h2_114173->ProjectionX("h1_114173", binmin, binmax, "e");
  h1_114174 = h2_114174->ProjectionX("h1_114174", binmin, binmax, "e");
  h1_114175 = h2_114175->ProjectionX("h1_114175", binmin, binmax, "e");
  h1_114176 = h2_114176->ProjectionX("h1_114176", binmin, binmax, "e");
  h1_114177 = h2_114177->ProjectionX("h1_114177", binmin, binmax, "e");
  h1_114178 = h2_114178->ProjectionX("h1_114178", binmin, binmax, "e");
  h1_114179 = h2_114179->ProjectionX("h1_114179", binmin, binmax, "e");
  h1_114180 = h2_114180->ProjectionX("h1_114180", binmin, binmax, "e");
  h1_114181 = h2_114181->ProjectionX("h1_114181", binmin, binmax, "e");
  h1_114182 = h2_114182->ProjectionX("h1_114182", binmin, binmax, "e");
  h1_114183 = h2_114183->ProjectionX("h1_114183", binmin, binmax, "e");
  h1_114184 = h2_114184->ProjectionX("h1_114184", binmin, binmax, "e");
  h1_114185 = h2_114185->ProjectionX("h1_114185", binmin, binmax, "e");
  h1_114186 = h2_114186->ProjectionX("h1_114186", binmin, binmax, "e");
  h1_114187 = h2_114187->ProjectionX("h1_114187", binmin, binmax, "e");
  h1_114188 = h2_114188->ProjectionX("h1_114188", binmin, binmax, "e");
  h1_114189 = h2_114189->ProjectionX("h1_114189", binmin, binmax, "e");
  h1_114190 = h2_114190->ProjectionX("h1_114190", binmin, binmax, "e");
  h1_114191 = h2_114191->ProjectionX("h1_114191", binmin, binmax, "e");
  h1_114192 = h2_114192->ProjectionX("h1_114192", binmin, binmax, "e");
  h1_114193 = h2_114193->ProjectionX("h1_114193", binmin, binmax, "e");
  h1_114194 = h2_114194->ProjectionX("h1_114194", binmin, binmax, "e");
  h1_114195 = h2_114195->ProjectionX("h1_114195", binmin, binmax, "e");
  h1_114196 = h2_114196->ProjectionX("h1_114196", binmin, binmax, "e");
  h1_114197 = h2_114197->ProjectionX("h1_114197", binmin, binmax, "e");
  h1_114198 = h2_114198->ProjectionX("h1_114198", binmin, binmax, "e");
  h1_114199 = h2_114199->ProjectionX("h1_114199", binmin, binmax, "e");
  h1_114200 = h2_114200->ProjectionX("h1_114200", binmin, binmax, "e");
  h1_114201 = h2_114201->ProjectionX("h1_114201", binmin, binmax, "e");
  h1_114202 = h2_114202->ProjectionX("h1_114202", binmin, binmax, "e");
  h1_114203 = h2_114203->ProjectionX("h1_114203", binmin, binmax, "e");
  h1_114204 = h2_114204->ProjectionX("h1_114204", binmin, binmax, "e");
  h1_114205 = h2_114205->ProjectionX("h1_114205", binmin, binmax, "e");
  h1_114206 = h2_114206->ProjectionX("h1_114206", binmin, binmax, "e");
  h1_114207 = h2_114207->ProjectionX("h1_114207", binmin, binmax, "e");
  h1_114208 = h2_114208->ProjectionX("h1_114208", binmin, binmax, "e");
  h1_114209 = h2_114209->ProjectionX("h1_114209", binmin, binmax, "e");
  h1_114210 = h2_114210->ProjectionX("h1_114210", binmin, binmax, "e");
  h1_114211 = h2_114211->ProjectionX("h1_114211", binmin, binmax, "e");
  h1_114212 = h2_114212->ProjectionX("h1_114212", binmin, binmax, "e");
  h1_114213 = h2_114213->ProjectionX("h1_114213", binmin, binmax, "e");
  h1_114214 = h2_114214->ProjectionX("h1_114214", binmin, binmax, "e");
  h1_114215 = h2_114215->ProjectionX("h1_114215", binmin, binmax, "e");
  h1_114216 = h2_114216->ProjectionX("h1_114216", binmin, binmax, "e");
#ifdef  NORM  
  cout << "Normalizing histo"<<endl;
  getHistoNorm(h1_114013 ,h2_114013, 114013);
  getHistoNorm(h1_114014 ,h2_114014, 114014);
  getHistoNorm(h1_114015 ,h2_114015, 114015);
  getHistoNorm(h1_114016 ,h2_114016, 114016);
  getHistoNorm(h1_114017 ,h2_114017, 114017);
  getHistoNorm(h1_114018 ,h2_114018, 114018);
  getHistoNorm(h1_114019 ,h2_114019, 114019);
  getHistoNorm(h1_114020 ,h2_114020, 114020);
  getHistoNorm(h1_114021 ,h2_114021, 114021);
  getHistoNorm(h1_114022 ,h2_114022, 114022);
  getHistoNorm(h1_114023 ,h2_114023, 114023);
  getHistoNorm(h1_114024 ,h2_114024, 114024);
  getHistoNorm(h1_114025 ,h2_114025, 114025);
  getHistoNorm(h1_114026 ,h2_114026, 114026);
  getHistoNorm(h1_114027 ,h2_114027, 114027);
  getHistoNorm(h1_114028 ,h2_114028, 114028);
  getHistoNorm(h1_114029 ,h2_114029, 114029);
  getHistoNorm(h1_114030 ,h2_114030, 114030);
  getHistoNorm(h1_114031 ,h2_114031, 114031);
  getHistoNorm(h1_114032 ,h2_114032, 114032);
  getHistoNorm(h1_114033 ,h2_114033, 114033);
  getHistoNorm(h1_114034 ,h2_114034, 114034);
  getHistoNorm(h1_114035 ,h2_114035, 114035);
  getHistoNorm(h1_114036 ,h2_114036, 114036);
  getHistoNorm(h1_114037 ,h2_114037, 114037);
  getHistoNorm(h1_114038 ,h2_114038, 114038);
  getHistoNorm(h1_114039 ,h2_114039, 114039);
  getHistoNorm(h1_114040 ,h2_114040, 114040);
  getHistoNorm(h1_114041 ,h2_114041, 114041);
  getHistoNorm(h1_114042 ,h2_114042, 114042);
  getHistoNorm(h1_114043 ,h2_114043, 114043);
  getHistoNorm(h1_114044 ,h2_114044, 114044);
  getHistoNorm(h1_114045 ,h2_114045, 114045);
  getHistoNorm(h1_114046 ,h2_114046, 114046);
  getHistoNorm(h1_114047 ,h2_114047, 114047);
  getHistoNorm(h1_114048 ,h2_114048, 114048);
  getHistoNorm(h1_114049 ,h2_114049, 114049);
  getHistoNorm(h1_114050 ,h2_114050, 114050);
  getHistoNorm(h1_114051 ,h2_114051, 114051);
  getHistoNorm(h1_114052 ,h2_114052, 114052);
  getHistoNorm(h1_114053 ,h2_114053, 114053);
  getHistoNorm(h1_114054 ,h2_114054, 114054);
  getHistoNorm(h1_114055 ,h2_114055, 114055);
  getHistoNorm(h1_114056 ,h2_114056, 114056);
  getHistoNorm(h1_114057 ,h2_114057, 114057);
  getHistoNorm(h1_114058 ,h2_114058, 114058);
  getHistoNorm(h1_114059 ,h2_114059, 114059);
  getHistoNorm(h1_114060 ,h2_114060, 114060);
  getHistoNorm(h1_114061 ,h2_114061, 114061);
  getHistoNorm(h1_114062 ,h2_114062, 114062);
  getHistoNorm(h1_114063 ,h2_114063, 114063);
  getHistoNorm(h1_114064 ,h2_114064, 114064);
  getHistoNorm(h1_114065 ,h2_114065, 114065);
  getHistoNorm(h1_114066 ,h2_114066, 114066);
  getHistoNorm(h1_114067 ,h2_114067, 114067);
  getHistoNorm(h1_114068 ,h2_114068, 114068);
  getHistoNorm(h1_114069 ,h2_114069, 114069);
  getHistoNorm(h1_114070 ,h2_114070, 114070);
  getHistoNorm(h1_114071 ,h2_114071, 114071);
  getHistoNorm(h1_114072 ,h2_114072, 114072);
  getHistoNorm(h1_114073 ,h2_114073, 114073);
  getHistoNorm(h1_114074 ,h2_114074, 114074);
  getHistoNorm(h1_114075 ,h2_114075, 114075);
  getHistoNorm(h1_114076 ,h2_114076, 114076);
  getHistoNorm(h1_114077 ,h2_114077, 114077);
  getHistoNorm(h1_114078 ,h2_114078, 114078);
  getHistoNorm(h1_114079 ,h2_114079, 114079);
  getHistoNorm(h1_114080 ,h2_114080, 114080);
  getHistoNorm(h1_114081 ,h2_114081, 114081);
  getHistoNorm(h1_114082 ,h2_114082, 114082);
  getHistoNorm(h1_114083 ,h2_114083, 114083);
  getHistoNorm(h1_114084 ,h2_114084, 114084);
  getHistoNorm(h1_114085 ,h2_114085, 114085);
  getHistoNorm(h1_114086 ,h2_114086, 114086);
  getHistoNorm(h1_114087 ,h2_114087, 114087);
  getHistoNorm(h1_114088 ,h2_114088, 114088);
  getHistoNorm(h1_114089 ,h2_114089, 114089);
  getHistoNorm(h1_114090 ,h2_114090, 114090);
  getHistoNorm(h1_114091 ,h2_114091, 114091);
  getHistoNorm(h1_114092 ,h2_114092, 114092);
  getHistoNorm(h1_114093 ,h2_114093, 114093);
  getHistoNorm(h1_114094 ,h2_114094, 114094);
  getHistoNorm(h1_114095 ,h2_114095, 114095);
  getHistoNorm(h1_114096 ,h2_114096, 114096);
  getHistoNorm(h1_114097 ,h2_114097, 114097);
  getHistoNorm(h1_114098 ,h2_114098, 114098);
  getHistoNorm(h1_114099 ,h2_114099, 114099);
  getHistoNorm(h1_114100 ,h2_114100, 114100);
  getHistoNorm(h1_114101 ,h2_114101, 114101);
  getHistoNorm(h1_114102 ,h2_114102, 114102);
  getHistoNorm(h1_114103 ,h2_114103, 114103);
  getHistoNorm(h1_114104 ,h2_114104, 114104);
  getHistoNorm(h1_114105 ,h2_114105, 114105);
  getHistoNorm(h1_114106 ,h2_114106, 114106);
  getHistoNorm(h1_114107 ,h2_114107, 114107);
  getHistoNorm(h1_114108 ,h2_114108, 114108);
  getHistoNorm(h1_114109 ,h2_114109, 114109);
  getHistoNorm(h1_114110 ,h2_114110, 114110);
  getHistoNorm(h1_114111 ,h2_114111, 114111);
  getHistoNorm(h1_114112 ,h2_114112, 114112);
  getHistoNorm(h1_114113 ,h2_114113, 114113);
  getHistoNorm(h1_114114 ,h2_114114, 114114);
  getHistoNorm(h1_114115 ,h2_114115, 114115);
  getHistoNorm(h1_114116 ,h2_114116, 114116);
  getHistoNorm(h1_114117 ,h2_114117, 114117);
  getHistoNorm(h1_114118 ,h2_114118, 114118);
  getHistoNorm(h1_114119 ,h2_114119, 114119);
  getHistoNorm(h1_114120 ,h2_114120, 114120);
  getHistoNorm(h1_114121 ,h2_114121, 114121);
  getHistoNorm(h1_114122 ,h2_114122, 114122);
  getHistoNorm(h1_114123 ,h2_114123, 114123);
  getHistoNorm(h1_114124 ,h2_114124, 114124);
  getHistoNorm(h1_114125 ,h2_114125, 114125);
  getHistoNorm(h1_114126 ,h2_114126, 114126);
  getHistoNorm(h1_114127 ,h2_114127, 114127);
  getHistoNorm(h1_114128 ,h2_114128, 114128);
  getHistoNorm(h1_114129 ,h2_114129, 114129);
  getHistoNorm(h1_114130 ,h2_114130, 114130);
  getHistoNorm(h1_114131 ,h2_114131, 114131);
  getHistoNorm(h1_114132 ,h2_114132, 114132);
  getHistoNorm(h1_114133 ,h2_114133, 114133);
  getHistoNorm(h1_114134 ,h2_114134, 114134);
  getHistoNorm(h1_114135 ,h2_114135, 114135);
  getHistoNorm(h1_114136 ,h2_114136, 114136);
  getHistoNorm(h1_114137 ,h2_114137, 114137);
  getHistoNorm(h1_114138 ,h2_114138, 114138);
  getHistoNorm(h1_114139 ,h2_114139, 114139);
  getHistoNorm(h1_114140 ,h2_114140, 114140);
  getHistoNorm(h1_114141 ,h2_114141, 114141);
  getHistoNorm(h1_114142 ,h2_114142, 114142);
  getHistoNorm(h1_114143 ,h2_114143, 114143);
  getHistoNorm(h1_114144 ,h2_114144, 114144);
  getHistoNorm(h1_114145 ,h2_114145, 114145);
  getHistoNorm(h1_114146 ,h2_114146, 114146);
  getHistoNorm(h1_114147 ,h2_114147, 114147);
  getHistoNorm(h1_114148 ,h2_114148, 114148);
  getHistoNorm(h1_114149 ,h2_114149, 114149);
  getHistoNorm(h1_114150 ,h2_114150, 114150);
  getHistoNorm(h1_114151 ,h2_114151, 114151);
  getHistoNorm(h1_114152 ,h2_114152, 114152);
  getHistoNorm(h1_114153 ,h2_114153, 114153);
  getHistoNorm(h1_114154 ,h2_114154, 114154);
  getHistoNorm(h1_114155 ,h2_114155, 114155);
  getHistoNorm(h1_114156 ,h2_114156, 114156);
  getHistoNorm(h1_114157 ,h2_114157, 114157);
  getHistoNorm(h1_114158 ,h2_114158, 114158);
  getHistoNorm(h1_114159 ,h2_114159, 114159);
  getHistoNorm(h1_114160 ,h2_114160, 114160);
  getHistoNorm(h1_114161 ,h2_114161, 114161);
  getHistoNorm(h1_114162 ,h2_114162, 114162);
  getHistoNorm(h1_114163 ,h2_114163, 114163);
  getHistoNorm(h1_114164 ,h2_114164, 114164);
  getHistoNorm(h1_114165 ,h2_114165, 114165);
  getHistoNorm(h1_114166 ,h2_114166, 114166);
  getHistoNorm(h1_114167 ,h2_114167, 114167);
  getHistoNorm(h1_114168 ,h2_114168, 114168);
  getHistoNorm(h1_114169 ,h2_114169, 114169);
  getHistoNorm(h1_114170 ,h2_114170, 114170);
  getHistoNorm(h1_114171 ,h2_114171, 114171);
  getHistoNorm(h1_114172 ,h2_114172, 114172);
  getHistoNorm(h1_114173 ,h2_114173, 114173);
  getHistoNorm(h1_114174 ,h2_114174, 114174);
  getHistoNorm(h1_114175 ,h2_114175, 114175);
  getHistoNorm(h1_114176 ,h2_114176, 114176);
  getHistoNorm(h1_114177 ,h2_114177, 114177);
  getHistoNorm(h1_114178 ,h2_114178, 114178);
  getHistoNorm(h1_114179 ,h2_114179, 114179);
  getHistoNorm(h1_114180 ,h2_114180, 114180);
  getHistoNorm(h1_114181 ,h2_114181, 114181);
  getHistoNorm(h1_114182 ,h2_114182, 114182);
  getHistoNorm(h1_114183 ,h2_114183, 114183);
  getHistoNorm(h1_114184 ,h2_114184, 114184);
  getHistoNorm(h1_114185 ,h2_114185, 114185);
  getHistoNorm(h1_114186 ,h2_114186, 114186);
  getHistoNorm(h1_114187 ,h2_114187, 114187);
  getHistoNorm(h1_114188 ,h2_114188, 114188);
  getHistoNorm(h1_114189 ,h2_114189, 114189);
  getHistoNorm(h1_114190 ,h2_114190, 114190);
  getHistoNorm(h1_114191 ,h2_114191, 114191);
  getHistoNorm(h1_114192 ,h2_114192, 114192);
  getHistoNorm(h1_114193 ,h2_114193, 114193);
  getHistoNorm(h1_114194 ,h2_114194, 114194);
  getHistoNorm(h1_114195 ,h2_114195, 114195);
  getHistoNorm(h1_114196 ,h2_114196, 114196);
  getHistoNorm(h1_114197 ,h2_114197, 114197);
  getHistoNorm(h1_114198 ,h2_114198, 114198);
  getHistoNorm(h1_114199 ,h2_114199, 114199);
  getHistoNorm(h1_114200 ,h2_114200, 114200);
  getHistoNorm(h1_114201 ,h2_114201, 114201);
  getHistoNorm(h1_114202 ,h2_114202, 114202);
  getHistoNorm(h1_114203 ,h2_114203, 114203);
  getHistoNorm(h1_114204 ,h2_114204, 114204);
  getHistoNorm(h1_114205 ,h2_114205, 114205);
  getHistoNorm(h1_114206 ,h2_114206, 114206);
  getHistoNorm(h1_114207 ,h2_114207, 114207);
  getHistoNorm(h1_114208 ,h2_114208, 114208);
  getHistoNorm(h1_114209 ,h2_114209, 114209);
  getHistoNorm(h1_114210 ,h2_114210, 114210);
  getHistoNorm(h1_114211 ,h2_114211, 114211);
  getHistoNorm(h1_114212 ,h2_114212, 114212);
  getHistoNorm(h1_114213 ,h2_114213, 114213);
  getHistoNorm(h1_114214 ,h2_114214, 114214);
  getHistoNorm(h1_114215 ,h2_114215, 114215);
  getHistoNorm(h1_114216 ,h2_114216, 114216);

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
  h1_105986 = h2_105985 ->ProjectionY("h1_105986 ", binmin, binmax, "e");
  h1_105987 = h2_105985 ->ProjectionY("h1_105987 ", binmin, binmax, "e");
#endif
#endif //end if DIBOSON

#ifdef QCDEE                                    //QCD EE

#ifdef H1D
  h1_108326  = (TH1I*)file_108326->Get(histo_string) ; 
#endif
#ifdef H2D
  h2_108326  = (TH2F*)file_108326->Get(histo_string) ; 
  h1_108326 = h2_108326 ->ProjectionY("h1_108326 ", binmin, binmax, "e");
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
  h1_209435  = (TH1I*)file_209435 ->Get(histo_string) ;
#endif

#ifdef H2D
  h2_109276  = (TH2F*)file_109276->Get(histo_string) ; 
  h2_109277  = (TH2F*)file_109277->Get(histo_string) ;
  h2_109278  = (TH2F*)file_109278->Get(histo_string) ;
  h2_109279  = (TH2F*)file_109279->Get(histo_string) ;
  h2_109280  = (TH2F*)file_109280->Get(histo_string) ;
  h2_109281  = (TH2F*)file_109281->Get(histo_string) ;
  h2_209435  = (TH2F*)file_209435->Get(histo_string) ;

  h1_109276 = h2_109276->ProjectionY("h1_109276", binmin, binmax, "e"); 
  h1_109277 = h2_109277->ProjectionY("h1_109277", binmin, binmax, "e");
  h1_109278 = h2_109278->ProjectionY("h1_109278", binmin, binmax, "e");
  h1_109279 = h2_109279->ProjectionY("h1_109279", binmin, binmax, "e");
  h1_109280 = h2_109280->ProjectionY("h1_109280", binmin, binmax, "e");
  h1_109281 = h2_109281->ProjectionY("h1_109281", binmin, binmax, "e");
  h1_209435 = h2_209435->ProjectionY("h1_209435", binmin, binmax, "e");
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

  h1_106280  = (TH1I*)file_106280->Get(histo_string) ; 
  h1_106281  = (TH1I*)file_106281->Get(histo_string) ; 
  h1_106282  = (TH1I*)file_106282->Get(histo_string) ; 
  h1_106283  = (TH1I*)file_106283->Get(histo_string) ; 
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

  h2_106280  = (TH2F*)file_106280->Get(histo_string) ; 
  h2_106281  = (TH2F*)file_106281->Get(histo_string) ;
  h2_106282  = (TH2F*)file_106282->Get(histo_string) ;
  h2_106283  = (TH2F*)file_106283->Get(histo_string) ;

  h1_106280 = h2_106280->ProjectionY("h1_106280", binmin, binmax, "e"); 
  h1_106281 = h2_106281->ProjectionY("h1_106281", binmin, binmax, "e");
  h1_106282 = h2_106282->ProjectionY("h1_106282", binmin, binmax, "e");
  h1_106283 = h2_106283->ProjectionY("h1_106283", binmin, binmax, "e");

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
  
  histo_wjets ->Add(h1_107680, Normalize(107680, lumi, file_107680));
  histo_wjets ->Add(h1_107681, Normalize(107681, lumi, file_107681));
  histo_wjets ->Add(h1_107682, Normalize(107682, lumi, file_107682));
  histo_wjets ->Add(h1_107683, Normalize(107683, lumi, file_107683));
  histo_wjets ->Add(h1_107684, Normalize(107684, lumi, file_107684));
  histo_wjets ->Add(h1_107685, Normalize(107685, lumi, file_107685));

  histo_wjets ->Add(h1_107690, Normalize(107690, lumi, file_107690));
  histo_wjets ->Add(h1_107691, Normalize(107691, lumi, file_107691));
  histo_wjets ->Add(h1_107692, Normalize(107692, lumi, file_107692));
  histo_wjets ->Add(h1_107693, Normalize(107693, lumi, file_107693));
  histo_wjets ->Add(h1_107694, Normalize(107694, lumi, file_107694));
  histo_wjets ->Add(h1_107695, Normalize(107695, lumi, file_107695));

  histo_wjets ->Add(h1_107700, Normalize(107700, lumi, file_107700));
  histo_wjets ->Add(h1_107701, Normalize(107701, lumi, file_107701));
  histo_wjets ->Add(h1_107702, Normalize(107702, lumi, file_107702));
  histo_wjets ->Add(h1_107703, Normalize(107703, lumi, file_107703));
  histo_wjets ->Add(h1_107704, Normalize(107704, lumi, file_107704));
  histo_wjets ->Add(h1_107705, Normalize(107705, lumi, file_107705));

  histo_wjets ->Add(h1_106280, Normalize(106280, lumi, file_106280));  // Wbb
  histo_wjets ->Add(h1_106281, Normalize(106281, lumi, file_106281));
  histo_wjets ->Add(h1_106282, Normalize(106282, lumi, file_106282));
  histo_wjets ->Add(h1_106283, Normalize(106283, lumi, file_106283));

#endif // Wjets

#ifdef ZJETS
  cout << "adding zjets"<<endl;

  histo_zjets = (TH1D*)h1_107650->Clone("histo_zjets");
  histo_zjets->Scale(Normalize(107650, lumi, file_107650));

  histo_zjets	->Add(h1_107651, Normalize(107651, lumi, file_107651));
  histo_zjets	->Add(h1_107652, Normalize(107652, lumi, file_107652));
  histo_zjets	->Add(h1_107653, Normalize(107653, lumi, file_107653));
  histo_zjets	->Add(h1_107654, Normalize(107654, lumi, file_107654));
  histo_zjets	->Add(h1_107655, Normalize(107655, lumi, file_107655));
  histo_zjets	->Add(h1_107660, Normalize(107660, lumi, file_107660));
  histo_zjets	->Add(h1_107661, Normalize(107661, lumi, file_107661));
  histo_zjets	->Add(h1_107662, Normalize(107662, lumi, file_107662));
  histo_zjets	->Add(h1_107663, Normalize(107663, lumi, file_107663));
  histo_zjets	->Add(h1_107664, Normalize(107664, lumi, file_107664));
  histo_zjets	->Add(h1_107665, Normalize(107665, lumi, file_107665));
  histo_zjets	->Add(h1_107670, Normalize(107670, lumi, file_107670));
  histo_zjets	->Add(h1_107671, Normalize(107671, lumi, file_107671));
  histo_zjets	->Add(h1_107672, Normalize(107672, lumi, file_107672));
  histo_zjets	->Add(h1_107673, Normalize(107673, lumi, file_107673));
  histo_zjets	->Add(h1_107674, Normalize(107674, lumi, file_107674));
  histo_zjets	->Add(h1_107675, Normalize(107675, lumi, file_107675));
#endif // Zjets

#ifdef DY

cout << "adding drellyan"<<endl;

  histo_drellyan = (TH1D*)h1_108319->Clone("histo_drellyan");

  histo_drellyan->Scale(Normalize(108319, lumi, file_108319));

  histo_drellyan	->Add(h1_108320, Normalize(108320, lumi, file_108320));
  histo_drellyan	->Add(h1_108321, Normalize(108321, lumi, file_108321));
  histo_drellyan	->Add(h1_108322, Normalize(108322, lumi, file_108322));
#endif // DY

#ifdef DIBOSON

cout << "adding diboson"<<endl;

  histo_diboson = (TH1D*)h1_105985->Clone("histo_diboson");

  histo_diboson->Scale(Normalize(105985, lumi, file_105985));

  histo_diboson  ->Add(h1_105986, Normalize(105986, lumi, file_105986));
  histo_diboson  ->Add(h1_105987, Normalize(105987, lumi, file_105987));
#endif // DIBOSON

#ifdef TTBAR

cout << "adding ttbar"<<endl;

  histo_ttbar = (TH1D*)h1_105200->Clone("histo_ttbar");

//  cout << "ttbar leptonic before norm "<<(h1_105200->Integral())<<endl;
//  cout << "ttbar hadronic before norm "<<(h1_105204->Integral())<<endl;
  
  histo_ttbar->Scale(Normalize(105200, lumi, file_105200));
//  cout << "ttbar after norm "<<(histo_ttbar->Integral())<<endl;

  histo_ttbar	->Add(h1_105204, Normalize(105204, lumi, file_105204));
#endif //TTBAR

#ifdef SU4
cout << "adding su4"<<endl;

  histo_su4 = (TH1D*)h1_106484->Clone("histo_su4");
//  cout << "su4 before norm "<<(histo_su4->Integral())<<endl;
  histo_su4->Scale(Normalize(106484, lumi, file_106484));
//  cout << "su4 after norm "<<(histo_su4->Integral())<<endl;
#endif //SU4

#ifdef QCDEE
cout << "adding qcd ee"<<endl;

  histo_qcd = (TH1D*)h1_108326->Clone("histo_qcd");
  histo_qcd->Scale(Normalize(108326, lumi, file_108326));
  histo_qcd_total = (TH1D*)histo_qcd->Clone("histo_qcd_total");

  cout << "QCD : Jx      " <<(histo_qcd->Integral())<<endl; 
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
   
#ifdef QCDFROMDATA  
  histo_qcd_total ->Add(histo_qcd_data);
#else
  histo_qcd_total ->Add(histo_qcd);
#endif 

#endif //JX

#ifdef JXMUON

  histo_qcd_mu = (TH1D*)h1_109276->Clone("histo_qcd_mu");
  histo_qcd_mu->Reset();

  histo_qcd_mu	->Add(h1_109276, Normalize(109276, lumi, file_109276));
  histo_qcd_mu  ->Add(h1_109277, Normalize(109277, lumi, file_109277));
  histo_qcd_mu  ->Add(h1_109278, Normalize(109278, lumi, file_109278));
  histo_qcd_mu  ->Add(h1_109279, Normalize(109279, lumi, file_109279));
  histo_qcd_mu  ->Add(h1_109280, Normalize(109280, lumi, file_109280));
  histo_qcd_mu  ->Add(h1_109281, Normalize(109281, lumi, file_109281));
  histo_qcd_mu  ->Add(h1_209435, Normalize(209435, lumi, file_209435));

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
  histo_wjets->SetFillColor(kAzure+1);
  histo_wjets->SetLineColor(kBlack);
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
  histo_zjets->SetFillColor(kGray);  //2D
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
  cout << "Filling in MSUGRA grid"<<endl;

  grid = new TH2D("grid", "grid", 30, -20., 1180, 40, 2.5., 602.5);
    
  Get_m0_m12(file_114013, grid, h1_114013, nCut, nCutRef);  
  Get_m0_m12(file_114014, grid, h1_114014, nCut, nCutRef);  
  Get_m0_m12(file_114015, grid, h1_114015, nCut, nCutRef); 
  Get_m0_m12(file_114016, grid, h1_114016, nCut, nCutRef); 
  Get_m0_m12(file_114017, grid, h1_114017, nCut, nCutRef); 
  Get_m0_m12(file_114018, grid, h1_114018, nCut, nCutRef); 
  Get_m0_m12(file_114019, grid, h1_114019, nCut, nCutRef); 
  Get_m0_m12(file_114020, grid, h1_114020, nCut, nCutRef); 
  Get_m0_m12(file_114021, grid, h1_114021, nCut, nCutRef); 
  Get_m0_m12(file_114022, grid, h1_114022, nCut, nCutRef); 
  Get_m0_m12(file_114023, grid, h1_114023, nCut, nCutRef); 
  Get_m0_m12(file_114024, grid, h1_114024, nCut, nCutRef); 
  Get_m0_m12(file_114025, grid, h1_114025, nCut, nCutRef); 
  Get_m0_m12(file_114026, grid, h1_114026, nCut, nCutRef); 
  Get_m0_m12(file_114027, grid, h1_114027, nCut, nCutRef); 
  Get_m0_m12(file_114028, grid, h1_114028, nCut, nCutRef); 
  Get_m0_m12(file_114029, grid, h1_114029, nCut, nCutRef); 
  Get_m0_m12(file_114030, grid, h1_114030, nCut, nCutRef); 
  Get_m0_m12(file_114031, grid, h1_114031, nCut, nCutRef); 
  Get_m0_m12(file_114032, grid, h1_114032, nCut, nCutRef); 
  Get_m0_m12(file_114033, grid, h1_114033, nCut, nCutRef); 
  Get_m0_m12(file_114034, grid, h1_114034, nCut, nCutRef); 
  Get_m0_m12(file_114035, grid, h1_114035, nCut, nCutRef); 
  Get_m0_m12(file_114036, grid, h1_114036, nCut, nCutRef); 
  Get_m0_m12(file_114037, grid, h1_114037, nCut, nCutRef); 
  Get_m0_m12(file_114038, grid, h1_114038, nCut, nCutRef); 
  Get_m0_m12(file_114039, grid, h1_114039, nCut, nCutRef); 
  Get_m0_m12(file_114040, grid, h1_114040, nCut, nCutRef); 
  Get_m0_m12(file_114041, grid, h1_114041, nCut, nCutRef); 
  Get_m0_m12(file_114042, grid, h1_114042, nCut, nCutRef);  
  Get_m0_m12(file_114043, grid, h1_114043, nCut, nCutRef); 
  Get_m0_m12(file_114044, grid, h1_114044, nCut, nCutRef); 
  Get_m0_m12(file_114045, grid, h1_114045, nCut, nCutRef); 
  Get_m0_m12(file_114046, grid, h1_114046, nCut, nCutRef); 
  Get_m0_m12(file_114047, grid, h1_114047, nCut, nCutRef); 
  Get_m0_m12(file_114048, grid, h1_114048, nCut, nCutRef); 
  Get_m0_m12(file_114049, grid, h1_114049, nCut, nCutRef); 
  Get_m0_m12(file_114050, grid, h1_114050, nCut, nCutRef); 
  Get_m0_m12(file_114051, grid, h1_114051, nCut, nCutRef); 
  Get_m0_m12(file_114052, grid, h1_114052, nCut, nCutRef); 
  Get_m0_m12(file_114053, grid, h1_114053, nCut, nCutRef); 
  Get_m0_m12(file_114054, grid, h1_114054, nCut, nCutRef); 
  Get_m0_m12(file_114055, grid, h1_114055, nCut, nCutRef); 
  Get_m0_m12(file_114056, grid, h1_114056, nCut, nCutRef); 
  Get_m0_m12(file_114057, grid, h1_114057, nCut, nCutRef); 
  Get_m0_m12(file_114058, grid, h1_114058, nCut, nCutRef); 
  Get_m0_m12(file_114059, grid, h1_114059, nCut, nCutRef); 
  Get_m0_m12(file_114060, grid, h1_114060, nCut, nCutRef); 
  Get_m0_m12(file_114061, grid, h1_114061, nCut, nCutRef); 
  Get_m0_m12(file_114062, grid, h1_114062, nCut, nCutRef); 
  Get_m0_m12(file_114063, grid, h1_114063, nCut, nCutRef); 
  Get_m0_m12(file_114064, grid, h1_114064, nCut, nCutRef); 
  Get_m0_m12(file_114065, grid, h1_114065, nCut, nCutRef); 
  Get_m0_m12(file_114066, grid, h1_114066, nCut, nCutRef); 
  Get_m0_m12(file_114067, grid, h1_114067, nCut, nCutRef); 
  Get_m0_m12(file_114068, grid, h1_114068, nCut, nCutRef); 
  Get_m0_m12(file_114069, grid, h1_114069, nCut, nCutRef); 
  Get_m0_m12(file_114070, grid, h1_114070, nCut, nCutRef); 
  Get_m0_m12(file_114071, grid, h1_114071, nCut, nCutRef); 
  Get_m0_m12(file_114072, grid, h1_114072, nCut, nCutRef); 
  Get_m0_m12(file_114073, grid, h1_114073, nCut, nCutRef); 
  Get_m0_m12(file_114074, grid, h1_114074, nCut, nCutRef); 
  Get_m0_m12(file_114075, grid, h1_114075, nCut, nCutRef); 
  Get_m0_m12(file_114076, grid, h1_114076, nCut, nCutRef); 
  Get_m0_m12(file_114077, grid, h1_114077, nCut, nCutRef); 
  Get_m0_m12(file_114078, grid, h1_114078, nCut, nCutRef); 
  Get_m0_m12(file_114079, grid, h1_114079, nCut, nCutRef); 
  Get_m0_m12(file_114080, grid, h1_114080, nCut, nCutRef); 
  Get_m0_m12(file_114081, grid, h1_114081, nCut, nCutRef); 
  Get_m0_m12(file_114082, grid, h1_114082, nCut, nCutRef); 
  Get_m0_m12(file_114083, grid, h1_114083, nCut, nCutRef); 
  Get_m0_m12(file_114084, grid, h1_114084, nCut, nCutRef); 
  Get_m0_m12(file_114085, grid, h1_114085, nCut, nCutRef); 
  Get_m0_m12(file_114086, grid, h1_114086, nCut, nCutRef); 
  Get_m0_m12(file_114087, grid, h1_114087, nCut, nCutRef); 
  Get_m0_m12(file_114088, grid, h1_114088, nCut, nCutRef); 
  Get_m0_m12(file_114089, grid, h1_114089, nCut, nCutRef); 
  Get_m0_m12(file_114090, grid, h1_114090, nCut, nCutRef); 
  Get_m0_m12(file_114091, grid, h1_114091, nCut, nCutRef); 
  Get_m0_m12(file_114092, grid, h1_114092, nCut, nCutRef); 
  Get_m0_m12(file_114093, grid, h1_114093, nCut, nCutRef); 
  Get_m0_m12(file_114094, grid, h1_114094, nCut, nCutRef); 
  Get_m0_m12(file_114095, grid, h1_114095, nCut, nCutRef); 
  Get_m0_m12(file_114096, grid, h1_114096, nCut, nCutRef); 
  Get_m0_m12(file_114097, grid, h1_114097, nCut, nCutRef); 
  Get_m0_m12(file_114098, grid, h1_114098, nCut, nCutRef); 
  Get_m0_m12(file_114099, grid, h1_114099, nCut, nCutRef); 
  Get_m0_m12(file_114100, grid, h1_114100, nCut, nCutRef); 
  Get_m0_m12(file_114101, grid, h1_114101, nCut, nCutRef); 
  Get_m0_m12(file_114102, grid, h1_114102, nCut, nCutRef); 
  Get_m0_m12(file_114103, grid, h1_114103, nCut, nCutRef); 
  Get_m0_m12(file_114104, grid, h1_114104, nCut, nCutRef); 
  Get_m0_m12(file_114105, grid, h1_114105, nCut, nCutRef); 
  Get_m0_m12(file_114106, grid, h1_114106, nCut, nCutRef); 
  Get_m0_m12(file_114107, grid, h1_114107, nCut, nCutRef); 
  Get_m0_m12(file_114108, grid, h1_114108, nCut, nCutRef); 
  Get_m0_m12(file_114109, grid, h1_114109, nCut, nCutRef); 
  Get_m0_m12(file_114110, grid, h1_114110, nCut, nCutRef); 
  Get_m0_m12(file_114111, grid, h1_114111, nCut, nCutRef); 
  Get_m0_m12(file_114112, grid, h1_114112, nCut, nCutRef); 
  Get_m0_m12(file_114113, grid, h1_114113, nCut, nCutRef); 
  Get_m0_m12(file_114114, grid, h1_114114, nCut, nCutRef); 
  Get_m0_m12(file_114115, grid, h1_114115, nCut, nCutRef); 
  Get_m0_m12(file_114116, grid, h1_114116, nCut, nCutRef); 
  Get_m0_m12(file_114117, grid, h1_114117, nCut, nCutRef); 
  Get_m0_m12(file_114118, grid, h1_114118, nCut, nCutRef); 
  Get_m0_m12(file_114119, grid, h1_114119, nCut, nCutRef); 
  Get_m0_m12(file_114120, grid, h1_114120, nCut, nCutRef); 
  Get_m0_m12(file_114121, grid, h1_114121, nCut, nCutRef); 
  Get_m0_m12(file_114122, grid, h1_114122, nCut, nCutRef); 
  Get_m0_m12(file_114123, grid, h1_114123, nCut, nCutRef); 
  Get_m0_m12(file_114124, grid, h1_114124, nCut, nCutRef); 
  Get_m0_m12(file_114125, grid, h1_114125, nCut, nCutRef); 
  Get_m0_m12(file_114126, grid, h1_114126, nCut, nCutRef); 
  Get_m0_m12(file_114127, grid, h1_114127, nCut, nCutRef); 
  Get_m0_m12(file_114128, grid, h1_114128, nCut, nCutRef); 
  Get_m0_m12(file_114129, grid, h1_114129, nCut, nCutRef); 
  Get_m0_m12(file_114130, grid, h1_114130, nCut, nCutRef); 
  Get_m0_m12(file_114131, grid, h1_114131, nCut, nCutRef); 
  Get_m0_m12(file_114132, grid, h1_114132, nCut, nCutRef); 
  Get_m0_m12(file_114133, grid, h1_114133, nCut, nCutRef); 
  Get_m0_m12(file_114134, grid, h1_114134, nCut, nCutRef); 
  Get_m0_m12(file_114135, grid, h1_114135, nCut, nCutRef); 
  Get_m0_m12(file_114136, grid, h1_114136, nCut, nCutRef); 
  Get_m0_m12(file_114137, grid, h1_114137, nCut, nCutRef); 
  Get_m0_m12(file_114138, grid, h1_114138, nCut, nCutRef); 
  Get_m0_m12(file_114139, grid, h1_114139, nCut, nCutRef); 
  Get_m0_m12(file_114140, grid, h1_114140, nCut, nCutRef); 
  Get_m0_m12(file_114141, grid, h1_114141, nCut, nCutRef); 
  Get_m0_m12(file_114142, grid, h1_114142, nCut, nCutRef);  
  Get_m0_m12(file_114143, grid, h1_114143, nCut, nCutRef); 
  Get_m0_m12(file_114144, grid, h1_114144, nCut, nCutRef); 
  Get_m0_m12(file_114145, grid, h1_114145, nCut, nCutRef); 
  Get_m0_m12(file_114146, grid, h1_114146, nCut, nCutRef); 
  Get_m0_m12(file_114147, grid, h1_114147, nCut, nCutRef); 
  Get_m0_m12(file_114148, grid, h1_114148, nCut, nCutRef); 
  Get_m0_m12(file_114149, grid, h1_114149, nCut, nCutRef); 
  Get_m0_m12(file_114150, grid, h1_114150, nCut, nCutRef); 
  Get_m0_m12(file_114151, grid, h1_114151, nCut, nCutRef); 
  Get_m0_m12(file_114152, grid, h1_114152, nCut, nCutRef); 
  Get_m0_m12(file_114153, grid, h1_114153, nCut, nCutRef); 
  Get_m0_m12(file_114154, grid, h1_114154, nCut, nCutRef); 
  Get_m0_m12(file_114155, grid, h1_114155, nCut, nCutRef); 
  Get_m0_m12(file_114156, grid, h1_114156, nCut, nCutRef); 
  Get_m0_m12(file_114157, grid, h1_114157, nCut, nCutRef); 
  Get_m0_m12(file_114158, grid, h1_114158, nCut, nCutRef); 
  Get_m0_m12(file_114159, grid, h1_114159, nCut, nCutRef); 
  Get_m0_m12(file_114160, grid, h1_114160, nCut, nCutRef); 
  Get_m0_m12(file_114161, grid, h1_114161, nCut, nCutRef); 
  Get_m0_m12(file_114162, grid, h1_114162, nCut, nCutRef); 
  Get_m0_m12(file_114163, grid, h1_114163, nCut, nCutRef); 
  Get_m0_m12(file_114164, grid, h1_114164, nCut, nCutRef); 
  Get_m0_m12(file_114165, grid, h1_114165, nCut, nCutRef); 
  Get_m0_m12(file_114166, grid, h1_114166, nCut, nCutRef); 
  Get_m0_m12(file_114167, grid, h1_114167, nCut, nCutRef); 
  Get_m0_m12(file_114168, grid, h1_114168, nCut, nCutRef); 
  Get_m0_m12(file_114169, grid, h1_114169, nCut, nCutRef); 
  Get_m0_m12(file_114170, grid, h1_114170, nCut, nCutRef); 
  Get_m0_m12(file_114171, grid, h1_114171, nCut, nCutRef); 
  Get_m0_m12(file_114172, grid, h1_114172, nCut, nCutRef); 
  Get_m0_m12(file_114173, grid, h1_114173, nCut, nCutRef); 
  Get_m0_m12(file_114174, grid, h1_114174, nCut, nCutRef); 
  Get_m0_m12(file_114175, grid, h1_114175, nCut, nCutRef); 
  Get_m0_m12(file_114176, grid, h1_114176, nCut, nCutRef); 
  Get_m0_m12(file_114177, grid, h1_114177, nCut, nCutRef); 
  Get_m0_m12(file_114178, grid, h1_114178, nCut, nCutRef); 
  Get_m0_m12(file_114179, grid, h1_114179, nCut, nCutRef); 
  Get_m0_m12(file_114180, grid, h1_114180, nCut, nCutRef); 
  Get_m0_m12(file_114181, grid, h1_114181, nCut, nCutRef); 
  Get_m0_m12(file_114182, grid, h1_114182, nCut, nCutRef); 
  Get_m0_m12(file_114183, grid, h1_114183, nCut, nCutRef); 
  Get_m0_m12(file_114184, grid, h1_114184, nCut, nCutRef); 
  Get_m0_m12(file_114185, grid, h1_114185, nCut, nCutRef); 
  Get_m0_m12(file_114186, grid, h1_114186, nCut, nCutRef); 
  Get_m0_m12(file_114187, grid, h1_114187, nCut, nCutRef); 
  Get_m0_m12(file_114188, grid, h1_114188, nCut, nCutRef); 
  Get_m0_m12(file_114189, grid, h1_114189, nCut, nCutRef); 
  Get_m0_m12(file_114190, grid, h1_114190, nCut, nCutRef); 
  Get_m0_m12(file_114191, grid, h1_114191, nCut, nCutRef); 
  Get_m0_m12(file_114192, grid, h1_114192, nCut, nCutRef); 
  Get_m0_m12(file_114193, grid, h1_114193, nCut, nCutRef); 
  Get_m0_m12(file_114194, grid, h1_114194, nCut, nCutRef); 
  Get_m0_m12(file_114195, grid, h1_114195, nCut, nCutRef); 
  Get_m0_m12(file_114196, grid, h1_114196, nCut, nCutRef); 
  Get_m0_m12(file_114197, grid, h1_114197, nCut, nCutRef); 
  Get_m0_m12(file_114198, grid, h1_114198, nCut, nCutRef); 
  Get_m0_m12(file_114199, grid, h1_114199, nCut, nCutRef); 
  Get_m0_m12(file_114200, grid, h1_114200, nCut, nCutRef); 
  Get_m0_m12(file_114201, grid, h1_114201, nCut, nCutRef); 
  Get_m0_m12(file_114202, grid, h1_114202, nCut, nCutRef); 
  Get_m0_m12(file_114203, grid, h1_114203, nCut, nCutRef); 
  Get_m0_m12(file_114204, grid, h1_114204, nCut, nCutRef); 
  Get_m0_m12(file_114205, grid, h1_114205, nCut, nCutRef); 
  Get_m0_m12(file_114206, grid, h1_114206, nCut, nCutRef); 
  Get_m0_m12(file_114207, grid, h1_114207, nCut, nCutRef); 
  Get_m0_m12(file_114208, grid, h1_114208, nCut, nCutRef); 
  Get_m0_m12(file_114209, grid, h1_114209, nCut, nCutRef); 
  Get_m0_m12(file_114210, grid, h1_114210, nCut, nCutRef); 
  Get_m0_m12(file_114211, grid, h1_114211, nCut, nCutRef); 
  Get_m0_m12(file_114212, grid, h1_114212, nCut, nCutRef); 
  Get_m0_m12(file_114213, grid, h1_114213, nCut, nCutRef); 
  Get_m0_m12(file_114214, grid, h1_114214, nCut, nCutRef); 
  Get_m0_m12(file_114215, grid, h1_114215, nCut, nCutRef); 
  Get_m0_m12(file_114216, grid, h1_114216, nCut, nCutRef); 
#endif //cutflow

#endif //MSUGRA 

#ifdef PHENO
#ifdef CUTFLOW
#else
  cout << "Filling in PHENO grid"<<endl;

  grid_odd = new TH2D("grid_odd", "grid_odd", 30, -20., 1180, 40, 2.5., 702.5);
  grid_even = new TH2D("grid_even", "grid_even", 30, -20., 1180, 40, 2.5., 702.5);
 
#ifdef GRID3         //Phenogrid 3
  Get_m0_m12(file_114901, grid_odd, h1_114901, nCut, nCutRef); 
  Get_m0_m12(file_114902, grid_even, h1_114902, nCut, nCutRef); 
  Get_m0_m12(file_114903, grid_odd, h1_114903, nCut, nCutRef); 
  Get_m0_m12(file_114904, grid_even, h1_114904, nCut, nCutRef); 
  Get_m0_m12(file_114905, grid_odd, h1_114905, nCut, nCutRef); 
  Get_m0_m12(file_114906, grid_even, h1_114906, nCut, nCutRef); 
  Get_m0_m12(file_114907, grid_odd, h1_114907, nCut, nCutRef); 
  Get_m0_m12(file_114908, grid_even, h1_114908, nCut, nCutRef); 
  Get_m0_m12(file_114909, grid_odd, h1_114909, nCut, nCutRef); 
  Get_m0_m12(file_114910, grid_even, h1_114910, nCut, nCutRef); 
  Get_m0_m12(file_114911, grid_odd, h1_114911, nCut, nCutRef); 
  Get_m0_m12(file_114912, grid_even, h1_114912, nCut, nCutRef); 
  Get_m0_m12(file_114913, grid_odd, h1_114913, nCut, nCutRef); 
  Get_m0_m12(file_114914, grid_even, h1_114914, nCut, nCutRef); 
  Get_m0_m12(file_114915, grid_odd, h1_114915, nCut, nCutRef); 
  Get_m0_m12(file_114916, grid_even, h1_114916, nCut, nCutRef); 
  Get_m0_m12(file_114917, grid_odd, h1_114917, nCut, nCutRef); 
  Get_m0_m12(file_114918, grid_even, h1_114918, nCut, nCutRef); 
  Get_m0_m12(file_114919, grid_odd, h1_114919, nCut, nCutRef); 
  Get_m0_m12(file_114920, grid_even, h1_114920, nCut, nCutRef); 
  Get_m0_m12(file_114921, grid_odd, h1_114921, nCut, nCutRef); 
  Get_m0_m12(file_114922, grid_even, h1_114922, nCut, nCutRef); 
  Get_m0_m12(file_114923, grid_odd, h1_114923, nCut, nCutRef); 
  Get_m0_m12(file_114924, grid_even, h1_114924, nCut, nCutRef); 
  Get_m0_m12(file_114925, grid_odd, h1_114925, nCut, nCutRef); 
  Get_m0_m12(file_114926, grid_even, h1_114926, nCut, nCutRef); 
  Get_m0_m12(file_114927, grid_odd, h1_114927, nCut, nCutRef); 
  Get_m0_m12(file_114928, grid_even, h1_114928, nCut, nCutRef); 
  Get_m0_m12(file_114929, grid_odd, h1_114929, nCut, nCutRef); 
  Get_m0_m12(file_114930, grid_even, h1_114930, nCut, nCutRef); 
  Get_m0_m12(file_114931, grid_odd, h1_114931, nCut, nCutRef); 
  Get_m0_m12(file_114932, grid_even, h1_114932, nCut, nCutRef); 
#endif
#ifdef GRID2         //Phenogrid 2
  Get_m0_m12(file_114933, grid_odd, h1_114933, nCut, nCutRef); 
  Get_m0_m12(file_114934, grid_even, h1_114934, nCut, nCutRef); 
  Get_m0_m12(file_114935, grid_odd, h1_114935, nCut, nCutRef); 
  Get_m0_m12(file_114936, grid_even, h1_114936, nCut, nCutRef); 
  Get_m0_m12(file_114937, grid_odd, h1_114937, nCut, nCutRef); 
  Get_m0_m12(file_114938, grid_even, h1_114938, nCut, nCutRef); 
  Get_m0_m12(file_114939, grid_odd, h1_114939, nCut, nCutRef); 
  Get_m0_m12(file_114940, grid_even, h1_114940, nCut, nCutRef); 
  Get_m0_m12(file_114941, grid_odd, h1_114941, nCut, nCutRef); 
  Get_m0_m12(file_114942, grid_even, h1_114942, nCut, nCutRef);  
  Get_m0_m12(file_114943, grid_odd, h1_114943, nCut, nCutRef); 
  Get_m0_m12(file_114944, grid_even, h1_114944, nCut, nCutRef); 
  Get_m0_m12(file_114945, grid_odd, h1_114945, nCut, nCutRef); 
  Get_m0_m12(file_114946, grid_even, h1_114946, nCut, nCutRef); 
  Get_m0_m12(file_114947, grid_odd, h1_114947, nCut, nCutRef); 
  Get_m0_m12(file_114948, grid_even, h1_114948, nCut, nCutRef); 
  Get_m0_m12(file_114949, grid_odd, h1_114949, nCut, nCutRef); 
  Get_m0_m12(file_114950, grid_even, h1_114950, nCut, nCutRef); 
  Get_m0_m12(file_114951, grid_odd, h1_114951, nCut, nCutRef); 
  Get_m0_m12(file_114952, grid_even, h1_114952, nCut, nCutRef); 
  Get_m0_m12(file_114953, grid_odd, h1_114953, nCut, nCutRef); 
  Get_m0_m12(file_114954, grid_even, h1_114954, nCut, nCutRef); 
  Get_m0_m12(file_114955, grid_odd, h1_114955, nCut, nCutRef); 
  Get_m0_m12(file_114956, grid_even, h1_114956, nCut, nCutRef); 
  Get_m0_m12(file_114957, grid_odd, h1_114957, nCut, nCutRef); 
  Get_m0_m12(file_114958, grid_even, h1_114958, nCut, nCutRef); 
  Get_m0_m12(file_114959, grid_odd, h1_114959, nCut, nCutRef); 
  Get_m0_m12(file_114960, grid_even, h1_114960, nCut, nCutRef); 
  Get_m0_m12(file_114961, grid_odd, h1_114961, nCut, nCutRef); 
  Get_m0_m12(file_114962, grid_even, h1_114962, nCut, nCutRef); 
  Get_m0_m12(file_114963, grid_odd, h1_114963, nCut, nCutRef); 
  Get_m0_m12(file_114964, grid_even, h1_114964, nCut, nCutRef); 
#endif
#ifdef GRID1         //Phenogrid 1
  Get_m0_m12(file_114965, grid_odd, h1_114965, nCut, nCutRef); 
  Get_m0_m12(file_114966, grid_even, h1_114966, nCut, nCutRef); 
  Get_m0_m12(file_114967, grid_odd, h1_114967, nCut, nCutRef); 
  Get_m0_m12(file_114968, grid_even, h1_114968, nCut, nCutRef); 
  Get_m0_m12(file_114969, grid_odd, h1_114969, nCut, nCutRef); 
  Get_m0_m12(file_114970, grid_even, h1_114970, nCut, nCutRef); 
  Get_m0_m12(file_114971, grid_odd, h1_114971, nCut, nCutRef); 
  Get_m0_m12(file_114972, grid_even, h1_114972, nCut, nCutRef); 
  Get_m0_m12(file_114973, grid_odd, h1_114973, nCut, nCutRef); 
  Get_m0_m12(file_114974, grid_even, h1_114974, nCut, nCutRef); 
  Get_m0_m12(file_114975, grid_odd, h1_114975, nCut, nCutRef); 
  Get_m0_m12(file_114976, grid_even, h1_114976, nCut, nCutRef); 
  Get_m0_m12(file_114977, grid_odd, h1_114977, nCut, nCutRef); 
  Get_m0_m12(file_114978, grid_even, h1_114978, nCut, nCutRef); 
  Get_m0_m12(file_114979, grid_odd, h1_114979, nCut, nCutRef); 
  Get_m0_m12(file_114980, grid_even, h1_114980, nCut, nCutRef); 
  Get_m0_m12(file_114981, grid_odd, h1_114981, nCut, nCutRef); 
  Get_m0_m12(file_114982, grid_even, h1_114982, nCut, nCutRef); 
  Get_m0_m12(file_114983, grid_odd, h1_114983, nCut, nCutRef); 
  Get_m0_m12(file_114984, grid_even, h1_114984, nCut, nCutRef); 
  Get_m0_m12(file_114985, grid_odd, h1_114985, nCut, nCutRef); 
  Get_m0_m12(file_114986, grid_even, h1_114986, nCut, nCutRef); 
  Get_m0_m12(file_114987, grid_odd, h1_114987, nCut, nCutRef); 
  Get_m0_m12(file_114988, grid_even, h1_114988, nCut, nCutRef); 
  Get_m0_m12(file_114989, grid_odd, h1_114989, nCut, nCutRef); 
  Get_m0_m12(file_114990, grid_even, h1_114990, nCut, nCutRef); 
  Get_m0_m12(file_114991, grid_odd, h1_114991, nCut, nCutRef); 
  Get_m0_m12(file_114992, grid_even, h1_114992, nCut, nCutRef); 
  Get_m0_m12(file_114993, grid_odd, h1_114993, nCut, nCutRef); 
  Get_m0_m12(file_114994, grid_even, h1_114994, nCut, nCutRef); 
  Get_m0_m12(file_114995, grid_odd, h1_114995, nCut, nCutRef); 
  Get_m0_m12(file_114996, grid_even, h1_114996, nCut, nCutRef); 
#endif

#endif //cutflow

#endif //PHENO
#endif //MC
#endif

  return;
}

double Normalize(int run, double lumi, TFile *file){


  TH1I* runNumber  = (TH1I*)(file ->Get("runNumber_histo")) ;  
  int Nevents = (int)(runNumber ->Integral());
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

  
//QCD 
if (run==108326) return (     75126.6 *pb*lumi/Nevents); 

//QCD Jx
if (run==105009) return (     9752970.      *nb *lumi/Nevents); 
if (run==105010) return (      673020.      *nb *lumi/Nevents); 
if (run==105011) return (       41194.7     *nb *lumi/Nevents); 
if (run==105012) return (        2193.25    *nb *lumi/Nevents); 
if (run==105013) return (         87.8487   *nb *lumi/Nevents); 
if (run==105014) return (	  2.332856  *nb *lumi/Nevents); 
if (run==105015) return (         0.0338461 *nb *lumi/Nevents); 

//QCD Muon filtered
if (run==109276) return ( 843.782706 *nb *lumi/Nevents); 
if (run==109277) return ( 821.174244 *nb *lumi/Nevents); 
if (run==109278) return ( 222.497208 *nb *lumi/Nevents); 
if (run==109279) return ( 28.6195379 *nb *lumi/Nevents); 
if (run==109280) return ( 1.959926405 *nb *lumi/Nevents); 
if (run==109281) return ( 0.071004224 *nb *lumi/Nevents); 
if (run==209435) return ( 0.00115 *nb *lumi/Nevents); //check

//Wjets -- use the same cs for e/mu/tau
if (run==107680) return (6.9133*1.19887 *nb *lumi/Nevents); 
if (run==107681) return (1.293 *1.19887 *nb *lumi/Nevents); 
if (run==107682) return (0.3771*1.19887 *nb *lumi/Nevents); 
if (run==107683) return (0.1009*1.19887 *nb *lumi/Nevents); 
if (run==107684) return (0.0253*1.19887 *nb *lumi/Nevents); 
if (run==107685) return (0.0069*1.19887 *nb *lumi/Nevents); 
if (run==107690) return (6.9133*1.19887 *nb *lumi/Nevents); 
if (run==107691) return (1.293 *1.19887 *nb *lumi/Nevents); 
if (run==107692) return (0.3771*1.19887 *nb *lumi/Nevents); 
if (run==107693) return (0.1009*1.19887 *nb *lumi/Nevents); 
if (run==107694) return (0.0253*1.19887 *nb *lumi/Nevents); 
if (run==107695) return (0.0069*1.19887 *nb *lumi/Nevents); 
if (run==107700) return (6.9133*1.19887 *nb *lumi/Nevents); 
if (run==107701) return (1.293 *1.19887 *nb *lumi/Nevents); 
if (run==107702) return (0.3771*1.19887 *nb *lumi/Nevents); 
if (run==107703) return (0.1009*1.19887 *nb *lumi/Nevents); 
if (run==107704) return (0.0253*1.19887 *nb *lumi/Nevents); 
if (run==107705) return (0.0069*1.19887 *nb *lumi/Nevents); 

//Wbb
if (run==106280) return (3.3072 * pb * 1.*lumi/Nevents); 
if (run==106281) return (2.6756 * pb * 1.*lumi/Nevents); 
if (run==106282) return (1.3763 * pb * 1.*lumi/Nevents); 
if (run==106283) return (0.65689* pb * 1.*lumi/Nevents); 


//Zjets -- use the same cs for e/mu/tau - no k factor for the moment
if (run==107650) return (0.830125   *nb *lumi/Nevents); 
if (run==107651) return (0.1662375  *nb *lumi/Nevents); 
if (run==107652) return (0.0502825  *nb *lumi/Nevents); 
if (run==107653) return (0.0139225  *nb *lumi/Nevents); 
if (run==107654) return (.003615625 *nb *lumi/Nevents); 
if (run==107655) return (.0009417875*nb *lumi/Nevents);
if (run==107660) return (0.830125   *nb *lumi/Nevents); 
if (run==107661) return (0.1662375  *nb *lumi/Nevents); 
if (run==107662) return (0.0502825  *nb *lumi/Nevents); 
if (run==107663) return (0.0139225  *nb *lumi/Nevents); 
if (run==107664) return (.003615625 *nb *lumi/Nevents); 
if (run==107665) return (.0009417875*nb *lumi/Nevents);
if (run==107670) return (0.830125   *nb *lumi/Nevents); 
if (run==107671) return (0.1662375  *nb *lumi/Nevents); 
if (run==107672) return (0.0502825  *nb *lumi/Nevents); 
if (run==107673) return (0.0139225  *nb *lumi/Nevents); 
if (run==107674) return (.003615625 *nb *lumi/Nevents); 
if (run==107675) return (.0009417875*nb *lumi/Nevents);
 
//low Drell yan
if (run==108319) return (1.2529*nb *0.944665 *lumi/Nevents);  //0.95 efficiency: filter to cut off true mll > 40 GeV (numbers from Borge)
if (run==108320) return (1.2530*nb *0.944674 *lumi/Nevents); //check
if (run==108321) return (4.4070*nb *0.51 *lumi/Nevents);
if (run==108322) return (4.4061*nb *0.50 *lumi/Nevents);

//DIBOSON 
if (run==105985) return ( 44.9*0.3884 *pb *lumi/Nevents); 
if (run==105986) return ( 5.96*0.2123 *pb *lumi/Nevents); 
if (run==105987) return ( 18.0*0.3085 *pb * lumi/Nevents); 


//SU4 

if (run==106484) cout << "SU4 cross section (pb) "<<59.95<<endl;
if (run==106484) return (59.95*pb *lumi/Nevents);//check
if (run==106480) return (52.8*pb *lumi/Nevents);

//T1
// ttbar with leptons
if (run==105200) return (160.79*0.556*pb *lumi/Nevents);// was 80.201*pb * 1.09
//fully hadronic ttbar
if (run==105204) return (160.79*0.444*pb *lumi/Nevents);//

 cout << "WARNING run "<<run<<" not in the list, returning 1"<<endl;
 
 return norm;
}


#ifdef MSUGRA

void getHistoNorm(TH1D* h1, TH2F* h2, int run){

  double lumi = 20.;
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
#endif //MSUGRA

#ifdef PHENO

void getHistoNorm(TH1D* h1, TH2F* h2, int run){

  double lumi = 20.;
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
