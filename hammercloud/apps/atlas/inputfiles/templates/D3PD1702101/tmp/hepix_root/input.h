// data  -- Open files

TString prefix = "result";

#ifdef DATA
#ifdef ELECTRON
  TFile* file_electronStream  = TFile::Open("root/"+prefix+"_electronStream.root");  
#endif  // endif ELECTRON

#ifdef MUON
  TFile* file_muonStream  = TFile::Open("root/"+prefix+"_muonStream.root");  
#endif // endif MUON
#endif // endif DATA


//MC  -- Open files  & get histograms
#ifdef MC                           //MC

#ifdef SU4                          //SU4
  TFile* file_106484  = TFile::Open("root/"+prefix+"_106484.root"); 
#endif //SU4

#ifdef MSUGRA                       //MSUGRA 
  TFile* file_robin  = TFile::Open("SignalUncertainties.root");  
  
  TFile* file_114013  = TFile::Open("root/"+prefix+"_114013.root");  
  TFile* file_114014  = TFile::Open("root/"+prefix+"_114014.root");  
  TFile* file_114015  = TFile::Open("root/"+prefix+"_114015.root"); 
  TFile* file_114016  = TFile::Open("root/"+prefix+"_114016.root"); 
  TFile* file_114017  = TFile::Open("root/"+prefix+"_114017.root"); 
  TFile* file_114018  = TFile::Open("root/"+prefix+"_114018.root"); 
  TFile* file_114019  = TFile::Open("root/"+prefix+"_114019.root"); 
  TFile* file_114020  = TFile::Open("root/"+prefix+"_114020.root"); 
  TFile* file_114021  = TFile::Open("root/"+prefix+"_114021.root"); 
  TFile* file_114022  = TFile::Open("root/"+prefix+"_114022.root"); 
  TFile* file_114023  = TFile::Open("root/"+prefix+"_114023.root"); 
  TFile* file_114024  = TFile::Open("root/"+prefix+"_114024.root"); 
  TFile* file_114025  = TFile::Open("root/"+prefix+"_114025.root"); 
  TFile* file_114026  = TFile::Open("root/"+prefix+"_114026.root"); 
  TFile* file_114027  = TFile::Open("root/"+prefix+"_114027.root"); 
  TFile* file_114028  = TFile::Open("root/"+prefix+"_114028.root"); 
  TFile* file_114029  = TFile::Open("root/"+prefix+"_114029.root"); 
  TFile* file_114030  = TFile::Open("root/"+prefix+"_114030.root"); 
  TFile* file_114031  = TFile::Open("root/"+prefix+"_114031.root"); 
  TFile* file_114032  = TFile::Open("root/"+prefix+"_114032.root"); 
  TFile* file_114033  = TFile::Open("root/"+prefix+"_114033.root"); 
  TFile* file_114034  = TFile::Open("root/"+prefix+"_114034.root"); 
  TFile* file_114035  = TFile::Open("root/"+prefix+"_114035.root"); 
  TFile* file_114036  = TFile::Open("root/"+prefix+"_114036.root"); 
  TFile* file_114037  = TFile::Open("root/"+prefix+"_114037.root"); 
  TFile* file_114038  = TFile::Open("root/"+prefix+"_114038.root"); 
  TFile* file_114039  = TFile::Open("root/"+prefix+"_114039.root"); 
  TFile* file_114040  = TFile::Open("root/"+prefix+"_114040.root"); 
  TFile* file_114041  = TFile::Open("root/"+prefix+"_114041.root"); 
  TFile* file_114042  = TFile::Open("root/"+prefix+"_114042.root");  
  TFile* file_114043  = TFile::Open("root/"+prefix+"_114043.root"); 
  TFile* file_114044  = TFile::Open("root/"+prefix+"_114044.root"); 
  TFile* file_114045  = TFile::Open("root/"+prefix+"_114045.root"); 
  TFile* file_114046  = TFile::Open("root/"+prefix+"_114046.root"); 
  TFile* file_114047  = TFile::Open("root/"+prefix+"_114047.root"); 
  TFile* file_114048  = TFile::Open("root/"+prefix+"_114048.root"); 
  TFile* file_114049  = TFile::Open("root/"+prefix+"_114049.root"); 
  TFile* file_114050  = TFile::Open("root/"+prefix+"_114050.root"); 
  TFile* file_114051  = TFile::Open("root/"+prefix+"_114051.root"); 
  TFile* file_114052  = TFile::Open("root/"+prefix+"_114052.root"); 
  TFile* file_114053  = TFile::Open("root/"+prefix+"_114053.root"); 
  TFile* file_114054  = TFile::Open("root/"+prefix+"_114054.root"); 
  TFile* file_114055  = TFile::Open("root/"+prefix+"_114055.root"); 
  TFile* file_114056  = TFile::Open("root/"+prefix+"_114056.root"); 
  TFile* file_114057  = TFile::Open("root/"+prefix+"_114057.root"); 
  TFile* file_114058  = TFile::Open("root/"+prefix+"_114058.root"); 
  TFile* file_114059  = TFile::Open("root/"+prefix+"_114059.root"); 
  TFile* file_114060  = TFile::Open("root/"+prefix+"_114060.root"); 
  TFile* file_114061  = TFile::Open("root/"+prefix+"_114061.root"); 
  TFile* file_114062  = TFile::Open("root/"+prefix+"_114062.root"); 
  TFile* file_114063  = TFile::Open("root/"+prefix+"_114063.root"); 
  TFile* file_114064  = TFile::Open("root/"+prefix+"_114064.root"); 
  TFile* file_114065  = TFile::Open("root/"+prefix+"_114065.root"); 
  TFile* file_114066  = TFile::Open("root/"+prefix+"_114066.root"); 
  TFile* file_114067  = TFile::Open("root/"+prefix+"_114067.root"); 
  TFile* file_114068  = TFile::Open("root/"+prefix+"_114068.root"); 
  TFile* file_114069  = TFile::Open("root/"+prefix+"_114069.root"); 
  TFile* file_114070  = TFile::Open("root/"+prefix+"_114070.root"); 
  TFile* file_114071  = TFile::Open("root/"+prefix+"_114071.root"); 
  TFile* file_114072  = TFile::Open("root/"+prefix+"_114072.root"); 
  TFile* file_114073  = TFile::Open("root/"+prefix+"_114073.root"); 
  TFile* file_114074  = TFile::Open("root/"+prefix+"_114074.root"); 
  TFile* file_114075  = TFile::Open("root/"+prefix+"_114075.root"); 
  TFile* file_114076  = TFile::Open("root/"+prefix+"_114076.root"); 
  TFile* file_114077  = TFile::Open("root/"+prefix+"_114077.root"); 
  TFile* file_114078  = TFile::Open("root/"+prefix+"_114078.root"); 
  TFile* file_114079  = TFile::Open("root/"+prefix+"_114079.root"); 
  TFile* file_114080  = TFile::Open("root/"+prefix+"_114080.root"); 
  TFile* file_114081  = TFile::Open("root/"+prefix+"_114081.root"); 
  TFile* file_114082  = TFile::Open("root/"+prefix+"_114082.root"); 
  TFile* file_114083  = TFile::Open("root/"+prefix+"_114083.root"); 
  TFile* file_114084  = TFile::Open("root/"+prefix+"_114084.root"); 
  TFile* file_114085  = TFile::Open("root/"+prefix+"_114085.root"); 
  TFile* file_114086  = TFile::Open("root/"+prefix+"_114086.root"); 
  TFile* file_114087  = TFile::Open("root/"+prefix+"_114087.root"); 
  TFile* file_114088  = TFile::Open("root/"+prefix+"_114088.root"); 
  TFile* file_114089  = TFile::Open("root/"+prefix+"_114089.root"); 
  TFile* file_114090  = TFile::Open("root/"+prefix+"_114090.root"); 
  TFile* file_114091  = TFile::Open("root/"+prefix+"_114091.root"); 
  TFile* file_114092  = TFile::Open("root/"+prefix+"_114092.root"); 
  TFile* file_114093  = TFile::Open("root/"+prefix+"_114093.root"); 
  TFile* file_114094  = TFile::Open("root/"+prefix+"_114094.root"); 
  TFile* file_114095  = TFile::Open("root/"+prefix+"_114095.root"); 
  TFile* file_114096  = TFile::Open("root/"+prefix+"_114096.root"); 
  TFile* file_114097  = TFile::Open("root/"+prefix+"_114097.root"); 
  TFile* file_114098  = TFile::Open("root/"+prefix+"_114098.root"); 
  TFile* file_114099  = TFile::Open("root/"+prefix+"_114099.root"); 
  TFile* file_114100  = TFile::Open("root/"+prefix+"_114100.root"); 
  TFile* file_114101  = TFile::Open("root/"+prefix+"_114101.root"); 
  TFile* file_114102  = TFile::Open("root/"+prefix+"_114102.root"); 
  TFile* file_114103  = TFile::Open("root/"+prefix+"_114103.root"); 
  TFile* file_114104  = TFile::Open("root/"+prefix+"_114104.root"); 
  TFile* file_114105  = TFile::Open("root/"+prefix+"_114105.root"); 
  TFile* file_114106  = TFile::Open("root/"+prefix+"_114106.root"); 
  TFile* file_114107  = TFile::Open("root/"+prefix+"_114107.root"); 
  TFile* file_114108  = TFile::Open("root/"+prefix+"_114108.root"); 
  TFile* file_114109  = TFile::Open("root/"+prefix+"_114109.root"); 
  TFile* file_114110  = TFile::Open("root/"+prefix+"_114110.root"); 
  TFile* file_114111  = TFile::Open("root/"+prefix+"_114111.root"); 
  TFile* file_114112  = TFile::Open("root/"+prefix+"_114112.root"); 
  TFile* file_114113  = TFile::Open("root/"+prefix+"_114113.root"); 
  TFile* file_114114  = TFile::Open("root/"+prefix+"_114114.root"); 
  TFile* file_114115  = TFile::Open("root/"+prefix+"_114115.root"); 
  TFile* file_114116  = TFile::Open("root/"+prefix+"_114116.root"); 
  TFile* file_114117  = TFile::Open("root/"+prefix+"_114117.root"); 
  TFile* file_114118  = TFile::Open("root/"+prefix+"_114118.root"); 
  TFile* file_114119  = TFile::Open("root/"+prefix+"_114119.root"); 
  TFile* file_114120  = TFile::Open("root/"+prefix+"_114120.root"); 
  TFile* file_114121  = TFile::Open("root/"+prefix+"_114121.root"); 
  TFile* file_114122  = TFile::Open("root/"+prefix+"_114122.root"); 
  TFile* file_114123  = TFile::Open("root/"+prefix+"_114123.root"); 
  TFile* file_114124  = TFile::Open("root/"+prefix+"_114124.root"); 
  TFile* file_114125  = TFile::Open("root/"+prefix+"_114125.root"); 
  TFile* file_114126  = TFile::Open("root/"+prefix+"_114126.root"); 
  TFile* file_114127  = TFile::Open("root/"+prefix+"_114127.root"); 
  TFile* file_114128  = TFile::Open("root/"+prefix+"_114128.root"); 
  TFile* file_114129  = TFile::Open("root/"+prefix+"_114129.root"); 
  TFile* file_114130  = TFile::Open("root/"+prefix+"_114130.root"); 
  TFile* file_114131  = TFile::Open("root/"+prefix+"_114131.root"); 
  TFile* file_114132  = TFile::Open("root/"+prefix+"_114132.root"); 
  TFile* file_114133  = TFile::Open("root/"+prefix+"_114133.root"); 
  TFile* file_114134  = TFile::Open("root/"+prefix+"_114134.root"); 
  TFile* file_114135  = TFile::Open("root/"+prefix+"_114135.root"); 
  TFile* file_114136  = TFile::Open("root/"+prefix+"_114136.root"); 
  TFile* file_114137  = TFile::Open("root/"+prefix+"_114137.root"); 
  TFile* file_114138  = TFile::Open("root/"+prefix+"_114138.root"); 
  TFile* file_114139  = TFile::Open("root/"+prefix+"_114139.root"); 
  TFile* file_114140  = TFile::Open("root/"+prefix+"_114140.root"); 
  TFile* file_114141  = TFile::Open("root/"+prefix+"_114141.root"); 
  TFile* file_114142  = TFile::Open("root/"+prefix+"_114142.root");  
  TFile* file_114143  = TFile::Open("root/"+prefix+"_114143.root"); 
  TFile* file_114144  = TFile::Open("root/"+prefix+"_114144.root"); 
  TFile* file_114145  = TFile::Open("root/"+prefix+"_114145.root"); 
  TFile* file_114146  = TFile::Open("root/"+prefix+"_114146.root"); 
  TFile* file_114147  = TFile::Open("root/"+prefix+"_114147.root"); 
  TFile* file_114148  = TFile::Open("root/"+prefix+"_114148.root"); 
  TFile* file_114149  = TFile::Open("root/"+prefix+"_114149.root"); 
  TFile* file_114150  = TFile::Open("root/"+prefix+"_114150.root"); 
  TFile* file_114151  = TFile::Open("root/"+prefix+"_114151.root"); 
  TFile* file_114152  = TFile::Open("root/"+prefix+"_114152.root"); 
  TFile* file_114153  = TFile::Open("root/"+prefix+"_114153.root"); 
  TFile* file_114154  = TFile::Open("root/"+prefix+"_114154.root"); 
  TFile* file_114155  = TFile::Open("root/"+prefix+"_114155.root"); 
  TFile* file_114156  = TFile::Open("root/"+prefix+"_114156.root"); 
  TFile* file_114157  = TFile::Open("root/"+prefix+"_114157.root"); 
  TFile* file_114158  = TFile::Open("root/"+prefix+"_114158.root"); 
  TFile* file_114159  = TFile::Open("root/"+prefix+"_114159.root"); 
  TFile* file_114160  = TFile::Open("root/"+prefix+"_114160.root"); 
  TFile* file_114161  = TFile::Open("root/"+prefix+"_114161.root"); 
  TFile* file_114162  = TFile::Open("root/"+prefix+"_114162.root"); 
  TFile* file_114163  = TFile::Open("root/"+prefix+"_114163.root"); 
  TFile* file_114164  = TFile::Open("root/"+prefix+"_114164.root"); 
  TFile* file_114165  = TFile::Open("root/"+prefix+"_114165.root"); 
  TFile* file_114166  = TFile::Open("root/"+prefix+"_114166.root"); 
  TFile* file_114167  = TFile::Open("root/"+prefix+"_114167.root"); 
  TFile* file_114168  = TFile::Open("root/"+prefix+"_114168.root"); 
  TFile* file_114169  = TFile::Open("root/"+prefix+"_114169.root"); 
  TFile* file_114170  = TFile::Open("root/"+prefix+"_114170.root"); 
  TFile* file_114171  = TFile::Open("root/"+prefix+"_114171.root"); 
  TFile* file_114172  = TFile::Open("root/"+prefix+"_114172.root"); 
  TFile* file_114173  = TFile::Open("root/"+prefix+"_114173.root"); 
  TFile* file_114174  = TFile::Open("root/"+prefix+"_114174.root"); 
  TFile* file_114175  = TFile::Open("root/"+prefix+"_114175.root"); 
  TFile* file_114176  = TFile::Open("root/"+prefix+"_114176.root"); 
  TFile* file_114177  = TFile::Open("root/"+prefix+"_114177.root"); 
  TFile* file_114178  = TFile::Open("root/"+prefix+"_114178.root"); 
  TFile* file_114179  = TFile::Open("root/"+prefix+"_114179.root"); 
  TFile* file_114180  = TFile::Open("root/"+prefix+"_114180.root"); 
  TFile* file_114181  = TFile::Open("root/"+prefix+"_114181.root"); 
  TFile* file_114182  = TFile::Open("root/"+prefix+"_114182.root"); 
  TFile* file_114183  = TFile::Open("root/"+prefix+"_114183.root"); 
  TFile* file_114184  = TFile::Open("root/"+prefix+"_114184.root"); 
  TFile* file_114185  = TFile::Open("root/"+prefix+"_114185.root"); 
  TFile* file_114186  = TFile::Open("root/"+prefix+"_114186.root"); 
  TFile* file_114187  = TFile::Open("root/"+prefix+"_114187.root"); 
  TFile* file_114188  = TFile::Open("root/"+prefix+"_114188.root"); 
  TFile* file_114189  = TFile::Open("root/"+prefix+"_114189.root"); 
  TFile* file_114190  = TFile::Open("root/"+prefix+"_114190.root"); 
  TFile* file_114191  = TFile::Open("root/"+prefix+"_114191.root"); 
  TFile* file_114192  = TFile::Open("root/"+prefix+"_114192.root"); 
  TFile* file_114193  = TFile::Open("root/"+prefix+"_114193.root"); 
  TFile* file_114194  = TFile::Open("root/"+prefix+"_114194.root"); 
  TFile* file_114195  = TFile::Open("root/"+prefix+"_114195.root"); 
  TFile* file_114196  = TFile::Open("root/"+prefix+"_114196.root"); 
  TFile* file_114197  = TFile::Open("root/"+prefix+"_114197.root"); 
  TFile* file_114198  = TFile::Open("root/"+prefix+"_114198.root"); 
  TFile* file_114199  = TFile::Open("root/"+prefix+"_114199.root"); 
  TFile* file_114200  = TFile::Open("root/"+prefix+"_114200.root"); 
  TFile* file_114201  = TFile::Open("root/"+prefix+"_114201.root"); 
  TFile* file_114202  = TFile::Open("root/"+prefix+"_114202.root"); 
  TFile* file_114203  = TFile::Open("root/"+prefix+"_114203.root"); 
  TFile* file_114204  = TFile::Open("root/"+prefix+"_114204.root"); 
  TFile* file_114205  = TFile::Open("root/"+prefix+"_114205.root"); 
  TFile* file_114206  = TFile::Open("root/"+prefix+"_114206.root"); 
  TFile* file_114207  = TFile::Open("root/"+prefix+"_114207.root"); 
  TFile* file_114208  = TFile::Open("root/"+prefix+"_114208.root"); 
  TFile* file_114209  = TFile::Open("root/"+prefix+"_114209.root"); 
  TFile* file_114210  = TFile::Open("root/"+prefix+"_114210.root"); 
  TFile* file_114211  = TFile::Open("root/"+prefix+"_114211.root"); 
  TFile* file_114212  = TFile::Open("root/"+prefix+"_114212.root"); 
  TFile* file_114213  = TFile::Open("root/"+prefix+"_114213.root"); 
  TFile* file_114214  = TFile::Open("root/"+prefix+"_114214.root"); 
  TFile* file_114215  = TFile::Open("root/"+prefix+"_114215.root"); 
  TFile* file_114216  = TFile::Open("root/"+prefix+"_114216.root"); 
#endif //MSUGRA

#ifdef PHENO                          //pheno
  TFile* file_robin  = TFile::Open("SignalUncertaintiesPheno.root");  
  
  TFile* file_114901  = TFile::Open("root/"+prefix+"_114901.root");  
  TFile* file_114902  = TFile::Open("root/"+prefix+"_114902.root"); 
  TFile* file_114903  = TFile::Open("root/"+prefix+"_114903.root"); 
  TFile* file_114904  = TFile::Open("root/"+prefix+"_114904.root");
  TFile* file_114905  = TFile::Open("root/"+prefix+"_114905.root");
  TFile* file_114906  = TFile::Open("root/"+prefix+"_114906.root");
  TFile* file_114907  = TFile::Open("root/"+prefix+"_114907.root");
  TFile* file_114908  = TFile::Open("root/"+prefix+"_114908.root");
  TFile* file_114909  = TFile::Open("root/"+prefix+"_114909.root");
  TFile* file_114910  = TFile::Open("root/"+prefix+"_114910.root");
  TFile* file_114911  = TFile::Open("root/"+prefix+"_114911.root");
  TFile* file_114912  = TFile::Open("root/"+prefix+"_114912.root");
  TFile* file_114913  = TFile::Open("root/"+prefix+"_114913.root");
  TFile* file_114914  = TFile::Open("root/"+prefix+"_114914.root");
  TFile* file_114915  = TFile::Open("root/"+prefix+"_114915.root");
  TFile* file_114916  = TFile::Open("root/"+prefix+"_114916.root");
  TFile* file_114917  = TFile::Open("root/"+prefix+"_114917.root");
  TFile* file_114918  = TFile::Open("root/"+prefix+"_114918.root");
  TFile* file_114919  = TFile::Open("root/"+prefix+"_114919.root");
  TFile* file_114920  = TFile::Open("root/"+prefix+"_114920.root");
  TFile* file_114921  = TFile::Open("root/"+prefix+"_114921.root");
  TFile* file_114922  = TFile::Open("root/"+prefix+"_114922.root");
  TFile* file_114923  = TFile::Open("root/"+prefix+"_114923.root");
  TFile* file_114924  = TFile::Open("root/"+prefix+"_114924.root");
  TFile* file_114925  = TFile::Open("root/"+prefix+"_114925.root");
  TFile* file_114926  = TFile::Open("root/"+prefix+"_114926.root");
  TFile* file_114927  = TFile::Open("root/"+prefix+"_114927.root");
  TFile* file_114928  = TFile::Open("root/"+prefix+"_114928.root");
  TFile* file_114929  = TFile::Open("root/"+prefix+"_114929.root");
  TFile* file_114930  = TFile::Open("root/"+prefix+"_114930.root");
  TFile* file_114931  = TFile::Open("root/"+prefix+"_114931.root");
  TFile* file_114932  = TFile::Open("root/"+prefix+"_114932.root");
  TFile* file_114933  = TFile::Open("root/"+prefix+"_114933.root");
  TFile* file_114934  = TFile::Open("root/"+prefix+"_114934.root");
  TFile* file_114935  = TFile::Open("root/"+prefix+"_114935.root");
  TFile* file_114936  = TFile::Open("root/"+prefix+"_114936.root");
  TFile* file_114937  = TFile::Open("root/"+prefix+"_114937.root");
  TFile* file_114938  = TFile::Open("root/"+prefix+"_114938.root");
  TFile* file_114939  = TFile::Open("root/"+prefix+"_114939.root");
  TFile* file_114940  = TFile::Open("root/"+prefix+"_114940.root");
  TFile* file_114941  = TFile::Open("root/"+prefix+"_114941.root");
  TFile* file_114942  = TFile::Open("root/"+prefix+"_114942.root");
  TFile* file_114943  = TFile::Open("root/"+prefix+"_114943.root");
  TFile* file_114944  = TFile::Open("root/"+prefix+"_114944.root");
  TFile* file_114945  = TFile::Open("root/"+prefix+"_114945.root");
  TFile* file_114946  = TFile::Open("root/"+prefix+"_114946.root");
  TFile* file_114947  = TFile::Open("root/"+prefix+"_114947.root");
  TFile* file_114948  = TFile::Open("root/"+prefix+"_114948.root");
  TFile* file_114949  = TFile::Open("root/"+prefix+"_114949.root");
  TFile* file_114950  = TFile::Open("root/"+prefix+"_114950.root");
  TFile* file_114951  = TFile::Open("root/"+prefix+"_114951.root");
  TFile* file_114952  = TFile::Open("root/"+prefix+"_114952.root");
  TFile* file_114953  = TFile::Open("root/"+prefix+"_114953.root");
  TFile* file_114954  = TFile::Open("root/"+prefix+"_114954.root");
  TFile* file_114955  = TFile::Open("root/"+prefix+"_114955.root");
  TFile* file_114956  = TFile::Open("root/"+prefix+"_114956.root");
  TFile* file_114957  = TFile::Open("root/"+prefix+"_114957.root");
  TFile* file_114958  = TFile::Open("root/"+prefix+"_114958.root");
  TFile* file_114959  = TFile::Open("root/"+prefix+"_114959.root");
  TFile* file_114960  = TFile::Open("root/"+prefix+"_114960.root");
  TFile* file_114961  = TFile::Open("root/"+prefix+"_114961.root");
  TFile* file_114962  = TFile::Open("root/"+prefix+"_114962.root");
  TFile* file_114963  = TFile::Open("root/"+prefix+"_114963.root");
  TFile* file_114964  = TFile::Open("root/"+prefix+"_114964.root");
  TFile* file_114965  = TFile::Open("root/"+prefix+"_114965.root");
  TFile* file_114966  = TFile::Open("root/"+prefix+"_114966.root");
  TFile* file_114967  = TFile::Open("root/"+prefix+"_114967.root");
  TFile* file_114968  = TFile::Open("root/"+prefix+"_114968.root");
  TFile* file_114969  = TFile::Open("root/"+prefix+"_114969.root");
  TFile* file_114970  = TFile::Open("root/"+prefix+"_114970.root");
  TFile* file_114971  = TFile::Open("root/"+prefix+"_114971.root");
  TFile* file_114972  = TFile::Open("root/"+prefix+"_114972.root");
  TFile* file_114973  = TFile::Open("root/"+prefix+"_114973.root");
  TFile* file_114974  = TFile::Open("root/"+prefix+"_114974.root");
  TFile* file_114975  = TFile::Open("root/"+prefix+"_114975.root");
  TFile* file_114976  = TFile::Open("root/"+prefix+"_114976.root");
  TFile* file_114977  = TFile::Open("root/"+prefix+"_114977.root");
  TFile* file_114978  = TFile::Open("root/"+prefix+"_114978.root");
  TFile* file_114979  = TFile::Open("root/"+prefix+"_114979.root");
  TFile* file_114980  = TFile::Open("root/"+prefix+"_114980.root");
  TFile* file_114981  = TFile::Open("root/"+prefix+"_114981.root");
  TFile* file_114982  = TFile::Open("root/"+prefix+"_114982.root");
  TFile* file_114983  = TFile::Open("root/"+prefix+"_114983.root");
  TFile* file_114984  = TFile::Open("root/"+prefix+"_114984.root");
  TFile* file_114985  = TFile::Open("root/"+prefix+"_114985.root");
  TFile* file_114986  = TFile::Open("root/"+prefix+"_114986.root");
  TFile* file_114987  = TFile::Open("root/"+prefix+"_114987.root");
  TFile* file_114988  = TFile::Open("root/"+prefix+"_114988.root");
  TFile* file_114989  = TFile::Open("root/"+prefix+"_114989.root");
  TFile* file_114990  = TFile::Open("root/"+prefix+"_114990.root");
  TFile* file_114991  = TFile::Open("root/"+prefix+"_114991.root");
  TFile* file_114992  = TFile::Open("root/"+prefix+"_114992.root");
  TFile* file_114993  = TFile::Open("root/"+prefix+"_114993.root");
  TFile* file_114994  = TFile::Open("root/"+prefix+"_114994.root");
  TFile* file_114995  = TFile::Open("root/"+prefix+"_114995.root");
  TFile* file_114996  = TFile::Open("root/"+prefix+"_114996.root");
#endif //PHENO

#ifdef TTBAR                          //ttbar
  TFile* file_105200  = TFile::Open("root/"+prefix+"_105200.root"); 
  TFile* file_105204  = TFile::Open("root/"+prefix+"_105204.root"); 
#endif //end if TTBAR

#ifdef DIBOSON                        //Diboson
  TFile* file_105985  = TFile::Open("root/"+prefix+"_105985.root"); 
  TFile* file_105986  = TFile::Open("root/"+prefix+"_105986.root"); 
  TFile* file_105987  = TFile::Open("root/"+prefix+"_105987.root");   
#endif //end if DIBOSON

#ifdef QCDEE                         //QCD EE
  TFile* file_108326  = TFile::Open("root/"+prefix+"_108326.root"); 
#endif //QCDEE

#ifdef JX           //QCD JX
  TFile* file_105009  = TFile::Open("root/"+prefix+"_105009.root"); 
  TFile* file_105010  = TFile::Open("root/"+prefix+"_105010.root");
  TFile* file_105011  = TFile::Open("root/"+prefix+"_105011.root");
  TFile* file_105012  = TFile::Open("root/"+prefix+"_105012.root");
  TFile* file_105013  = TFile::Open("root/"+prefix+"_105013.root");
  TFile* file_105014  = TFile::Open("root/"+prefix+"_105014.root");
  TFile* file_105015  = TFile::Open("root/"+prefix+"_105015.root");
#endif //JX

#ifdef JXMUON       //QCD muon filtered
  TFile* file_109276  = TFile::Open("root/"+prefix+"_109276.root"); 
  TFile* file_109277  = TFile::Open("root/"+prefix+"_109277.root"); 
  TFile* file_109278  = TFile::Open("root/"+prefix+"_109278.root"); 
  TFile* file_109279  = TFile::Open("root/"+prefix+"_109279.root"); 
  TFile* file_109280  = TFile::Open("root/"+prefix+"_109280.root");
  TFile* file_109281  = TFile::Open("root/"+prefix+"_109281.root");
  TFile* file_209435  = TFile::Open("root/"+prefix+"_209435.root");  
#endif //JXMUON

#ifdef ZJETS         //Zjets
  TFile* file_107650  = TFile::Open("root/"+prefix+"_107650.root");
  TFile* file_107651  = TFile::Open("root/"+prefix+"_107651.root");
  TFile* file_107652  = TFile::Open("root/"+prefix+"_107652.root");
  TFile* file_107653  = TFile::Open("root/"+prefix+"_107653.root");
  TFile* file_107654  = TFile::Open("root/"+prefix+"_107654.root");
  TFile* file_107655  = TFile::Open("root/"+prefix+"_107655.root");
  TFile* file_107660  = TFile::Open("root/"+prefix+"_107660.root");
  TFile* file_107661  = TFile::Open("root/"+prefix+"_107661.root");
  TFile* file_107662  = TFile::Open("root/"+prefix+"_107662.root");
  TFile* file_107663  = TFile::Open("root/"+prefix+"_107663.root");
  TFile* file_107664  = TFile::Open("root/"+prefix+"_107664.root");
  TFile* file_107665  = TFile::Open("root/"+prefix+"_107665.root");
  TFile* file_107670  = TFile::Open("root/"+prefix+"_107670.root");
  TFile* file_107671  = TFile::Open("root/"+prefix+"_107671.root");
  TFile* file_107672  = TFile::Open("root/"+prefix+"_107672.root");
  TFile* file_107673  = TFile::Open("root/"+prefix+"_107673.root");
  TFile* file_107674  = TFile::Open("root/"+prefix+"_107674.root");
  TFile* file_107675  = TFile::Open("root/"+prefix+"_107675.root");
#endif //ZJETS

#ifdef WJETS            //Wjets
  TFile* file_107680  = TFile::Open("root/"+prefix+"_107680.root");
  TFile* file_107681  = TFile::Open("root/"+prefix+"_107681.root");
  TFile* file_107682  = TFile::Open("root/"+prefix+"_107682.root");
  TFile* file_107683  = TFile::Open("root/"+prefix+"_107683.root");
  TFile* file_107684  = TFile::Open("root/"+prefix+"_107684.root");
  TFile* file_107685  = TFile::Open("root/"+prefix+"_107685.root");
  TFile* file_107690  = TFile::Open("root/"+prefix+"_107690.root");
  TFile* file_107691  = TFile::Open("root/"+prefix+"_107691.root");
  TFile* file_107692  = TFile::Open("root/"+prefix+"_107692.root");
  TFile* file_107693  = TFile::Open("root/"+prefix+"_107693.root");
  TFile* file_107694  = TFile::Open("root/"+prefix+"_107694.root");
  TFile* file_107695  = TFile::Open("root/"+prefix+"_107695.root");
  TFile* file_107700  = TFile::Open("root/"+prefix+"_107700.root");
  TFile* file_107701  = TFile::Open("root/"+prefix+"_107701.root");
  TFile* file_107702  = TFile::Open("root/"+prefix+"_107702.root");
  TFile* file_107703  = TFile::Open("root/"+prefix+"_107703.root");
  TFile* file_107704  = TFile::Open("root/"+prefix+"_107704.root");
  TFile* file_107705  = TFile::Open("root/"+prefix+"_107705.root");

                         //Wbb
  TFile* file_106280  = TFile::Open("root/"+prefix+"_106280.root");
  TFile* file_106281  = TFile::Open("root/"+prefix+"_106281.root");
  TFile* file_106282  = TFile::Open("root/"+prefix+"_106282.root");
  TFile* file_106283  = TFile::Open("root/"+prefix+"_106283.root");    
#endif //WJETS

#ifdef DY          //Drell yan
  TFile* file_108319  = TFile::Open("root/"+prefix+"_108319.root"); 
  TFile* file_108320  = TFile::Open("root/"+prefix+"_108320.root"); 
  TFile* file_108321  = TFile::Open("root/"+prefix+"_108321.root"); 
  TFile* file_108322  = TFile::Open("root/"+prefix+"_108322.root"); 
#endif //DY

#endif // MC

 // Declare histograms
  TH1D  *histo_data, *histo_qcd_data, *histo_qcd, *histo_qcd_mu, *histo_qcd_total,*histo_wjets, *histo_zjets, *histo_ttbar, *histo_su4;
  TH2D *grid, *grid_odd, *grid_even;

#ifdef DATA
#ifdef ELECTRON
#ifdef H1D
  TH1I* h1_electronStream;   
#endif
#ifdef H2D
  TH2F* h2_electronStream;   
  TH1D* h1_electronStream;
#endif
#endif  // ELECTRON

#ifdef MUON
#ifdef H1D
  TH1I* h1_muonStream;   
#endif
#ifdef H2D
  TH2F* h2_muonStream;   
  TH1D* h1_muonStream;
#endif
#endif // MUON
#endif // DATA


#ifdef MC                                           //MC

#ifdef SU4                                         //SU4
#ifdef H1D
  TH1I* h1_106484; 
#endif
#ifdef H2D
  TH2F* h2_106484;     
  TH1D* h1_106484;
#endif
#endif //SU4

#ifdef MSUGRA                                    //MSUGRA

#ifdef H1D

TH1I* h1_114013 ; 
TH1I* h1_114014 ; 
TH1I* h1_114015 ;
TH1I* h1_114016 ;
TH1I* h1_114017 ;
TH1I* h1_114018 ;
TH1I* h1_114019 ;
TH1I* h1_114020 ;
TH1I* h1_114021 ;
TH1I* h1_114022 ;
TH1I* h1_114023 ;
TH1I* h1_114024 ;
TH1I* h1_114025 ;
TH1I* h1_114026 ;
TH1I* h1_114027 ;
TH1I* h1_114028 ;
TH1I* h1_114029 ;
TH1I* h1_114030 ;
TH1I* h1_114031 ;
TH1I* h1_114032 ;
TH1I* h1_114033 ;
TH1I* h1_114034 ;
TH1I* h1_114035 ;
TH1I* h1_114036 ;
TH1I* h1_114037 ;
TH1I* h1_114038 ;
TH1I* h1_114039 ;
TH1I* h1_114040 ;
TH1I* h1_114041 ;
TH1I* h1_114042 ; 
TH1I* h1_114043 ;
TH1I* h1_114044 ;
TH1I* h1_114045 ;
TH1I* h1_114046 ;
TH1I* h1_114047 ;
TH1I* h1_114048 ;
TH1I* h1_114049 ;
TH1I* h1_114050 ;
TH1I* h1_114051 ;
TH1I* h1_114052 ;
TH1I* h1_114053 ;
TH1I* h1_114054 ;
TH1I* h1_114055 ;
TH1I* h1_114056 ;
TH1I* h1_114057 ;
TH1I* h1_114058 ;
TH1I* h1_114059 ;
TH1I* h1_114060 ;
TH1I* h1_114061 ;
TH1I* h1_114062 ;
TH1I* h1_114063 ;
TH1I* h1_114064 ;
TH1I* h1_114065 ;
TH1I* h1_114066 ;
TH1I* h1_114067 ;
TH1I* h1_114068 ;
TH1I* h1_114069 ;
TH1I* h1_114070 ;
TH1I* h1_114071 ;
TH1I* h1_114072 ;
TH1I* h1_114073 ;
TH1I* h1_114074 ;
TH1I* h1_114075 ;
TH1I* h1_114076 ;
TH1I* h1_114077 ;
TH1I* h1_114078 ;
TH1I* h1_114079 ;
TH1I* h1_114080 ;
TH1I* h1_114081 ;
TH1I* h1_114082 ;
TH1I* h1_114083 ;
TH1I* h1_114084 ;
TH1I* h1_114085 ;
TH1I* h1_114086 ;
TH1I* h1_114087 ;
TH1I* h1_114088 ;
TH1I* h1_114089 ;
TH1I* h1_114090 ;
TH1I* h1_114091 ;
TH1I* h1_114092 ;
TH1I* h1_114093 ;
TH1I* h1_114094 ;
TH1I* h1_114095 ;
TH1I* h1_114096 ;
TH1I* h1_114097 ;
TH1I* h1_114098 ;
TH1I* h1_114099 ;
TH1I* h1_114100 ;
TH1I* h1_114101 ;
TH1I* h1_114102 ;
TH1I* h1_114103 ;
TH1I* h1_114104 ;
TH1I* h1_114105 ;
TH1I* h1_114106 ;
TH1I* h1_114107 ;
TH1I* h1_114108 ;
TH1I* h1_114109 ;
TH1I* h1_114110 ;
TH1I* h1_114111 ;
TH1I* h1_114112 ;
TH1I* h1_114113 ;
TH1I* h1_114114 ;
TH1I* h1_114115 ;
TH1I* h1_114116 ;
TH1I* h1_114117 ;
TH1I* h1_114118 ;
TH1I* h1_114119 ;
TH1I* h1_114120 ;
TH1I* h1_114121 ;
TH1I* h1_114122 ;
TH1I* h1_114123 ;
TH1I* h1_114124 ;
TH1I* h1_114125 ;
TH1I* h1_114126 ;
TH1I* h1_114127 ;
TH1I* h1_114128 ;
TH1I* h1_114129 ;
TH1I* h1_114130 ;
TH1I* h1_114131 ;
TH1I* h1_114132 ;
TH1I* h1_114133 ;
TH1I* h1_114134 ;
TH1I* h1_114135 ;
TH1I* h1_114136 ;
TH1I* h1_114137 ;
TH1I* h1_114138 ;
TH1I* h1_114139 ;
TH1I* h1_114140 ;
TH1I* h1_114141 ;
TH1I* h1_114142 ; 
TH1I* h1_114143 ;
TH1I* h1_114144 ;
TH1I* h1_114145 ;
TH1I* h1_114146 ;
TH1I* h1_114147 ;
TH1I* h1_114148 ;
TH1I* h1_114149 ;
TH1I* h1_114150 ;
TH1I* h1_114151 ;
TH1I* h1_114152 ;
TH1I* h1_114153 ;
TH1I* h1_114154 ;
TH1I* h1_114155 ;
TH1I* h1_114156 ;
TH1I* h1_114157 ;
TH1I* h1_114158 ;
TH1I* h1_114159 ;
TH1I* h1_114160 ;
TH1I* h1_114161 ;
TH1I* h1_114162 ;
TH1I* h1_114163 ;
TH1I* h1_114164 ;
TH1I* h1_114165 ;
TH1I* h1_114166 ;
TH1I* h1_114167 ;
TH1I* h1_114168 ;
TH1I* h1_114169 ;
TH1I* h1_114170 ;
TH1I* h1_114171 ;
TH1I* h1_114172 ;
TH1I* h1_114173 ;
TH1I* h1_114174 ;
TH1I* h1_114175 ;
TH1I* h1_114176 ;
TH1I* h1_114177 ;
TH1I* h1_114178 ;
TH1I* h1_114179 ;
TH1I* h1_114180 ;
TH1I* h1_114181 ;
TH1I* h1_114182 ;
TH1I* h1_114183 ;
TH1I* h1_114184 ;
TH1I* h1_114185 ;
TH1I* h1_114186 ;
TH1I* h1_114187 ;
TH1I* h1_114188 ;
TH1I* h1_114189 ;
TH1I* h1_114190 ;
TH1I* h1_114191 ;
TH1I* h1_114192 ;
TH1I* h1_114193 ;
TH1I* h1_114194 ;
TH1I* h1_114195 ;
TH1I* h1_114196 ;
TH1I* h1_114197 ;
TH1I* h1_114198 ;
TH1I* h1_114199 ;
TH1I* h1_114200 ;
TH1I* h1_114201 ;
TH1I* h1_114202 ;
TH1I* h1_114203 ;
TH1I* h1_114204 ;
TH1I* h1_114205 ;
TH1I* h1_114206 ;
TH1I* h1_114207 ;
TH1I* h1_114208 ;
TH1I* h1_114209 ;
TH1I* h1_114210 ;
TH1I* h1_114211 ;
TH1I* h1_114212 ;
TH1I* h1_114213 ;
TH1I* h1_114214 ;
TH1I* h1_114215 ;
TH1I* h1_114216 ;
#endif
#ifdef H2D
  TH2F* h2_114013;   
  TH2F* h2_114014;   
  TH2F* h2_114015;   
  TH2F* h2_114016;   
  TH2F* h2_114017;   
  TH2F* h2_114018;   
  TH2F* h2_114019;    
  TH2F* h2_114020;    
  TH2F* h2_114021;    
  TH2F* h2_114022;    
  TH2F* h2_114023;   
  TH2F* h2_114024;   
  TH2F* h2_114025;     
  TH2F* h2_114026;     
  TH2F* h2_114027;     
  TH2F* h2_114028;     
  TH2F* h2_114029;     
  TH2F* h2_114030;     
  TH2F* h2_114031;    
  TH2F* h2_114032;     
  TH2F* h2_114033;     
  TH2F* h2_114034;   
  TH2F* h2_114035;     
  TH2F* h2_114036;    
  TH2F* h2_114037;   
  TH2F* h2_114038;   
  TH2F* h2_114039;   
  TH2F* h2_114040;   
  TH2F* h2_114041;   
  TH2F* h2_114042;     
  TH2F* h2_114043;   
  TH2F* h2_114044;   
  TH2F* h2_114045;   
  TH2F* h2_114046;   
  TH2F* h2_114047;   
  TH2F* h2_114048;   
  TH2F* h2_114049;   
  TH2F* h2_114050;   
  TH2F* h2_114051;   
  TH2F* h2_114052;   
  TH2F* h2_114053;   
  TH2F* h2_114054;   
  TH2F* h2_114055;   
  TH2F* h2_114056;   
  TH2F* h2_114057;   
  TH2F* h2_114058;   
  TH2F* h2_114059;    
  TH2F* h2_114060;    
  TH2F* h2_114061;    
  TH2F* h2_114062;    
  TH2F* h2_114063;    
  TH2F* h2_114064;    
  TH2F* h2_114065;    
  TH2F* h2_114066;    
  TH2F* h2_114067;    
  TH2F* h2_114068;    
  TH2F* h2_114069;    
  TH2F* h2_114070;    
  TH2F* h2_114071;    
  TH2F* h2_114072;    
  TH2F* h2_114073;    
  TH2F* h2_114074;    
  TH2F* h2_114075;    
  TH2F* h2_114076;    
  TH2F* h2_114077;    
  TH2F* h2_114078;    
  TH2F* h2_114079;    
  TH2F* h2_114080;    
  TH2F* h2_114081;    
  TH2F* h2_114082;    
  TH2F* h2_114083;    
  TH2F* h2_114084;    
  TH2F* h2_114085;     
  TH2F* h2_114086;    
  TH2F* h2_114087;     
  TH2F* h2_114088;     
  TH2F* h2_114089;     
  TH2F* h2_114090;     
  TH2F* h2_114091;       
  TH2F* h2_114092;       
  TH2F* h2_114093;       
  TH2F* h2_114094;       
  TH2F* h2_114095;       
  TH2F* h2_114096;       
  TH2F* h2_114097;       
  TH2F* h2_114098;       
  TH2F* h2_114099;       
  TH2F* h2_114100;       
  TH2F* h2_114101;       
  TH2F* h2_114102;      
  TH2F* h2_114103;       
  TH2F* h2_114104;       
  TH2F* h2_114105;       
  TH2F* h2_114106;       
  TH2F* h2_114107;       
  TH2F* h2_114108;       
  TH2F* h2_114109;       
  TH2F* h2_114110;       
  TH2F* h2_114111;       
  TH2F* h2_114112;       
  TH2F* h2_114113;       
  TH2F* h2_114114;       
  TH2F* h2_114115;       
  TH2F* h2_114116;       
  TH2F* h2_114117;       
  TH2F* h2_114118;       
  TH2F* h2_114119;       
  TH2F* h2_114120;       
  TH2F* h2_114121;       
  TH2F* h2_114122;       
  TH2F* h2_114123;       
  TH2F* h2_114124;       
  TH2F* h2_114125;       
  TH2F* h2_114126;       
  TH2F* h2_114127;       
  TH2F* h2_114128;       
  TH2F* h2_114129;       
  TH2F* h2_114130;       
  TH2F* h2_114131;       
  TH2F* h2_114132;       
  TH2F* h2_114133;       
  TH2F* h2_114134;       
  TH2F* h2_114135;       
  TH2F* h2_114136;       
  TH2F* h2_114137;       
  TH2F* h2_114138;       
  TH2F* h2_114139;       
  TH2F* h2_114140;       
  TH2F* h2_114141;       
  TH2F* h2_114142;       
  TH2F* h2_114143;       
  TH2F* h2_114144;       
  TH2F* h2_114145;       
  TH2F* h2_114146;       
  TH2F* h2_114147;       
  TH2F* h2_114148;       
  TH2F* h2_114149;       
  TH2F* h2_114150;       
  TH2F* h2_114151;       
  TH2F* h2_114152;       
  TH2F* h2_114153;       
  TH2F* h2_114154;       
  TH2F* h2_114155;     
  TH2F* h2_114156;       
  TH2F* h2_114157;     
  TH2F* h2_114158;       
  TH2F* h2_114159;     
  TH2F* h2_114160;       
  TH2F* h2_114161;       
  TH2F* h2_114162;       
  TH2F* h2_114163;       
  TH2F* h2_114164;       
  TH2F* h2_114165;       
  TH2F* h2_114166;       
  TH2F* h2_114167;       
  TH2F* h2_114168;       
  TH2F* h2_114169;       
  TH2F* h2_114170;       
  TH2F* h2_114171;       
  TH2F* h2_114172;       
  TH2F* h2_114173;       
  TH2F* h2_114174;       
  TH2F* h2_114175;       
  TH2F* h2_114176;       
  TH2F* h2_114177;       
  TH2F* h2_114178;       
  TH2F* h2_114179;       
  TH2F* h2_114180;       
  TH2F* h2_114181;       
  TH2F* h2_114182;       
  TH2F* h2_114183;       
  TH2F* h2_114184;       
  TH2F* h2_114185;       
  TH2F* h2_114186;       
  TH2F* h2_114187;       
  TH2F* h2_114188;       
  TH2F* h2_114189;   
  TH2F* h2_114190;   
  TH2F* h2_114191;   
  TH2F* h2_114192;   
  TH2F* h2_114193;   
  TH2F* h2_114194;   
  TH2F* h2_114195;   
  TH2F* h2_114196;   
  TH2F* h2_114197;   
  TH2F* h2_114198;   
  TH2F* h2_114199;   
  TH2F* h2_114200;   
  TH2F* h2_114201;   
  TH2F* h2_114202;  
  TH2F* h2_114203;   
  TH2F* h2_114204;   
  TH2F* h2_114205;   
  TH2F* h2_114206;   
  TH2F* h2_114207;   
  TH2F* h2_114208;  
  TH2F* h2_114209;  
  TH2F* h2_114210;  
  TH2F* h2_114211;  
  TH2F* h2_114212;  
  TH2F* h2_114213;  
  TH2F* h2_114214;   
  TH2F* h2_114215;  
  TH2F* h2_114216;  

  TH1D* h1_114013;
  TH1D* h1_114014;
  TH1D* h1_114015;
  TH1D* h1_114016;
  TH1D* h1_114017;
  TH1D* h1_114018;
  TH1D* h1_114019;
  TH1D* h1_114020;
  TH1D* h1_114021;
  TH1D* h1_114022;
  TH1D* h1_114023;
  TH1D* h1_114024;
  TH1D* h1_114025;
  TH1D* h1_114026;
  TH1D* h1_114027;
  TH1D* h1_114028;
  TH1D* h1_114029;
  TH1D* h1_114030;
  TH1D* h1_114031;
  TH1D* h1_114032;
  TH1D* h1_114033;
  TH1D* h1_114034;
  TH1D* h1_114035;
  TH1D* h1_114036;
  TH1D* h1_114037;
  TH1D* h1_114038;
  TH1D* h1_114039;
  TH1D* h1_114040;
  TH1D* h1_114041;
  TH1D* h1_114042;
  TH1D* h1_114043;
  TH1D* h1_114044;
  TH1D* h1_114045;
  TH1D* h1_114046;
  TH1D* h1_114047;
  TH1D* h1_114048;
  TH1D* h1_114049;
  TH1D* h1_114050;
  TH1D* h1_114051;
  TH1D* h1_114052;
  TH1D* h1_114053;
  TH1D* h1_114054;
  TH1D* h1_114055;
  TH1D* h1_114056;
  TH1D* h1_114057;
  TH1D* h1_114058;
  TH1D* h1_114059;
  TH1D* h1_114060;
  TH1D* h1_114061;
  TH1D* h1_114062;
  TH1D* h1_114063;
  TH1D* h1_114064;
  TH1D* h1_114065;
  TH1D* h1_114066;
  TH1D* h1_114067;
  TH1D* h1_114068;
  TH1D* h1_114069;
  TH1D* h1_114070;
  TH1D* h1_114071;
  TH1D* h1_114072;
  TH1D* h1_114073;
  TH1D* h1_114074;
  TH1D* h1_114075;
  TH1D* h1_114076;
  TH1D* h1_114077;
  TH1D* h1_114078;
  TH1D* h1_114079;
  TH1D* h1_114080;
  TH1D* h1_114081;
  TH1D* h1_114082;
  TH1D* h1_114083;
  TH1D* h1_114084;
  TH1D* h1_114085;
  TH1D* h1_114086;
  TH1D* h1_114087;
  TH1D* h1_114088;
  TH1D* h1_114089;
  TH1D* h1_114090;
  TH1D* h1_114091;
  TH1D* h1_114092;
  TH1D* h1_114093;
  TH1D* h1_114094;
  TH1D* h1_114095;
  TH1D* h1_114096;
  TH1D* h1_114097;
  TH1D* h1_114098;
  TH1D* h1_114099;
  TH1D* h1_114100;
  TH1D* h1_114101;
  TH1D* h1_114102;
  TH1D* h1_114103;
  TH1D* h1_114104;
  TH1D* h1_114105;
  TH1D* h1_114106;
  TH1D* h1_114107;
  TH1D* h1_114108;
  TH1D* h1_114109;
  TH1D* h1_114110;
  TH1D* h1_114111;
  TH1D* h1_114112;
  TH1D* h1_114113;
  TH1D* h1_114114;
  TH1D* h1_114115;
  TH1D* h1_114116;
  TH1D* h1_114117;
  TH1D* h1_114118;
  TH1D* h1_114119;
  TH1D* h1_114120;
  TH1D* h1_114121;
  TH1D* h1_114122;
  TH1D* h1_114123;
  TH1D* h1_114124;
  TH1D* h1_114125;
  TH1D* h1_114126;
  TH1D* h1_114127;
  TH1D* h1_114128;
  TH1D* h1_114129;
  TH1D* h1_114130;
  TH1D* h1_114131;
  TH1D* h1_114132;
  TH1D* h1_114133;
  TH1D* h1_114134;
  TH1D* h1_114135;
  TH1D* h1_114136;
  TH1D* h1_114137;
  TH1D* h1_114138;
  TH1D* h1_114139;
  TH1D* h1_114140;
  TH1D* h1_114141;
  TH1D* h1_114142;
  TH1D* h1_114143;
  TH1D* h1_114144;
  TH1D* h1_114145;
  TH1D* h1_114146;
  TH1D* h1_114147;
  TH1D* h1_114148;
  TH1D* h1_114149;
  TH1D* h1_114150;
  TH1D* h1_114151;
  TH1D* h1_114152;
  TH1D* h1_114153;
  TH1D* h1_114154;
  TH1D* h1_114155;
  TH1D* h1_114156;
  TH1D* h1_114157;
  TH1D* h1_114158;
  TH1D* h1_114159;
  TH1D* h1_114160;
  TH1D* h1_114161;
  TH1D* h1_114162;
  TH1D* h1_114163;
  TH1D* h1_114164;
  TH1D* h1_114165;
  TH1D* h1_114166;
  TH1D* h1_114167;
  TH1D* h1_114168;
  TH1D* h1_114169;
  TH1D* h1_114170;
  TH1D* h1_114171;
  TH1D* h1_114172;
  TH1D* h1_114173;
  TH1D* h1_114174;
  TH1D* h1_114175;
  TH1D* h1_114176;
  TH1D* h1_114177;
  TH1D* h1_114178;
  TH1D* h1_114179;
  TH1D* h1_114180;
  TH1D* h1_114181;
  TH1D* h1_114182;
  TH1D* h1_114183;
  TH1D* h1_114184;
  TH1D* h1_114185;
  TH1D* h1_114186;
  TH1D* h1_114187;
  TH1D* h1_114188;
  TH1D* h1_114189;
  TH1D* h1_114190;
  TH1D* h1_114191;
  TH1D* h1_114192;
  TH1D* h1_114193;
  TH1D* h1_114194;
  TH1D* h1_114195;
  TH1D* h1_114196;
  TH1D* h1_114197;
  TH1D* h1_114198;
  TH1D* h1_114199;
  TH1D* h1_114200;
  TH1D* h1_114201;
  TH1D* h1_114202;
  TH1D* h1_114203;
  TH1D* h1_114204;
  TH1D* h1_114205;
  TH1D* h1_114206;
  TH1D* h1_114207;
  TH1D* h1_114208;
  TH1D* h1_114209;
  TH1D* h1_114210;
  TH1D* h1_114211;
  TH1D* h1_114212;
  TH1D* h1_114213;
  TH1D* h1_114214;
  TH1D* h1_114215;
  TH1D* h1_114216;
#endif
#endif //MSUGRA

#ifdef PHENO                                   //PHENO

#ifdef H1D
  TH1I* h1_114901;  
  TH1I* h1_114902; 
  TH1I* h1_114903; 
  TH1I* h1_114904;
  TH1I* h1_114905;
  TH1I* h1_114906;
  TH1I* h1_114907;
  TH1I* h1_114908;
  TH1I* h1_114909;
  TH1I* h1_114910;
  TH1I* h1_114911;
  TH1I* h1_114912;
  TH1I* h1_114913;
  TH1I* h1_114914;
  TH1I* h1_114915;
  TH1I* h1_114916;
  TH1I* h1_114917;
  TH1I* h1_114918;
  TH1I* h1_114919;
  TH1I* h1_114920;
  TH1I* h1_114921;
  TH1I* h1_114922;
  TH1I* h1_114923;
  TH1I* h1_114924;
  TH1I* h1_114925;
  TH1I* h1_114926;
  TH1I* h1_114927;
  TH1I* h1_114928;
  TH1I* h1_114929;
  TH1I* h1_114930;
  TH1I* h1_114931;
  TH1I* h1_114932;
  TH1I* h1_114933;
  TH1I* h1_114934;
  TH1I* h1_114935;
  TH1I* h1_114936;
  TH1I* h1_114937;
  TH1I* h1_114938;
  TH1I* h1_114939;
  TH1I* h1_114940;
  TH1I* h1_114941;
  TH1I* h1_114942;
  TH1I* h1_114943;
  TH1I* h1_114944;
  TH1I* h1_114945;
  TH1I* h1_114946;
  TH1I* h1_114947;
  TH1I* h1_114948;
  TH1I* h1_114949;
  TH1I* h1_114950;
  TH1I* h1_114951;
  TH1I* h1_114952;
  TH1I* h1_114953;
  TH1I* h1_114954;
  TH1I* h1_114955;
  TH1I* h1_114956;
  TH1I* h1_114957;
  TH1I* h1_114958;
  TH1I* h1_114959;
  TH1I* h1_114960;
  TH1I* h1_114961;
  TH1I* h1_114962;
  TH1I* h1_114963;
  TH1I* h1_114964;
  TH1I* h1_114965;
  TH1I* h1_114966;
  TH1I* h1_114967;
  TH1I* h1_114968;
  TH1I* h1_114969;
  TH1I* h1_114970;
  TH1I* h1_114971;
  TH1I* h1_114972;
  TH1I* h1_114973;
  TH1I* h1_114974;
  TH1I* h1_114975;
  TH1I* h1_114976;
  TH1I* h1_114977;
  TH1I* h1_114978;
  TH1I* h1_114979;
  TH1I* h1_114980;
  TH1I* h1_114981;
  TH1I* h1_114982;
  TH1I* h1_114983;
  TH1I* h1_114984;
  TH1I* h1_114985;
  TH1I* h1_114986;
  TH1I* h1_114987;
  TH1I* h1_114988;
  TH1I* h1_114989;
  TH1I* h1_114990;
  TH1I* h1_114991;
  TH1I* h1_114992;
  TH1I* h1_114993;
  TH1I* h1_114994;
  TH1I* h1_114995;
  TH1I* h1_114996;
  
#endif
#ifdef H2D  
  TH2F* h2_114901;  
  TH2F* h2_114902; 
  TH2F* h2_114903; 
  TH2F* h2_114904;
  TH2F* h2_114905;
  TH2F* h2_114906;
  TH2F* h2_114907;
  TH2F* h2_114908;
  TH2F* h2_114909;
  TH2F* h2_114910;
  TH2F* h2_114911;
  TH2F* h2_114912;
  TH2F* h2_114913;
  TH2F* h2_114914;
  TH2F* h2_114915;
  TH2F* h2_114916;
  TH2F* h2_114917;
  TH2F* h2_114918;
  TH2F* h2_114919;
  TH2F* h2_114920;
  TH2F* h2_114921;
  TH2F* h2_114922;
  TH2F* h2_114923;
  TH2F* h2_114924;
  TH2F* h2_114925;
  TH2F* h2_114926;
  TH2F* h2_114927;
  TH2F* h2_114928;
  TH2F* h2_114929;
  TH2F* h2_114930;
  TH2F* h2_114931;
  TH2F* h2_114932;
  TH2F* h2_114933;
  TH2F* h2_114934;
  TH2F* h2_114935;
  TH2F* h2_114936;
  TH2F* h2_114937;
  TH2F* h2_114938;
  TH2F* h2_114939;
  TH2F* h2_114940;
  TH2F* h2_114941;
  TH2F* h2_114942;
  TH2F* h2_114943;
  TH2F* h2_114944;
  TH2F* h2_114945;
  TH2F* h2_114946;
  TH2F* h2_114947;
  TH2F* h2_114948;
  TH2F* h2_114949;
  TH2F* h2_114950;
  TH2F* h2_114951;
  TH2F* h2_114952;
  TH2F* h2_114953;
  TH2F* h2_114954;
  TH2F* h2_114955;
  TH2F* h2_114956;
  TH2F* h2_114957;
  TH2F* h2_114958;
  TH2F* h2_114959;
  TH2F* h2_114960;
  TH2F* h2_114961;
  TH2F* h2_114962;
  TH2F* h2_114963;
  TH2F* h2_114964;
  TH2F* h2_114965;
  TH2F* h2_114966;
  TH2F* h2_114967;
  TH2F* h2_114968;
  TH2F* h2_114969;
  TH2F* h2_114970;
  TH2F* h2_114971;
  TH2F* h2_114972;
  TH2F* h2_114973;
  TH2F* h2_114974;
  TH2F* h2_114975;
  TH2F* h2_114976;
  TH2F* h2_114977;
  TH2F* h2_114978;
  TH2F* h2_114979;
  TH2F* h2_114980;
  TH2F* h2_114981;
  TH2F* h2_114982;
  TH2F* h2_114983;
  TH2F* h2_114984;
  TH2F* h2_114985;
  TH2F* h2_114986;
  TH2F* h2_114987;
  TH2F* h2_114988;
  TH2F* h2_114989;
  TH2F* h2_114990;
  TH2F* h2_114991;
  TH2F* h2_114992;
  TH2F* h2_114993;
  TH2F* h2_114994;
  TH2F* h2_114995;
  TH2F* h2_114996;
  
  TH1D* h1_114901;  
  TH1D* h1_114902; 
  TH1D* h1_114903; 
  TH1D* h1_114904;
  TH1D* h1_114905;
  TH1D* h1_114906;
  TH1D* h1_114907;
  TH1D* h1_114908;
  TH1D* h1_114909;
  TH1D* h1_114910;
  TH1D* h1_114911;
  TH1D* h1_114912;
  TH1D* h1_114913;
  TH1D* h1_114914;
  TH1D* h1_114915;
  TH1D* h1_114916;
  TH1D* h1_114917;
  TH1D* h1_114918;
  TH1D* h1_114919;
  TH1D* h1_114920;
  TH1D* h1_114921;
  TH1D* h1_114922;
  TH1D* h1_114923;
  TH1D* h1_114924;
  TH1D* h1_114925;
  TH1D* h1_114926;
  TH1D* h1_114927;
  TH1D* h1_114928;
  TH1D* h1_114929;
  TH1D* h1_114930;
  TH1D* h1_114931;
  TH1D* h1_114932;
  TH1D* h1_114933;
  TH1D* h1_114934;
  TH1D* h1_114935;
  TH1D* h1_114936;
  TH1D* h1_114937;
  TH1D* h1_114938;
  TH1D* h1_114939;
  TH1D* h1_114940;
  TH1D* h1_114941;
  TH1D* h1_114942;
  TH1D* h1_114943;
  TH1D* h1_114944;
  TH1D* h1_114945;
  TH1D* h1_114946;
  TH1D* h1_114947;
  TH1D* h1_114948;
  TH1D* h1_114949;
  TH1D* h1_114950;
  TH1D* h1_114951;
  TH1D* h1_114952;
  TH1D* h1_114953;
  TH1D* h1_114954;
  TH1D* h1_114955;
  TH1D* h1_114956;
  TH1D* h1_114957;
  TH1D* h1_114958;
  TH1D* h1_114959;
  TH1D* h1_114960;
  TH1D* h1_114961;
  TH1D* h1_114962;
  TH1D* h1_114963;
  TH1D* h1_114964;
  TH1D* h1_114965;
  TH1D* h1_114966;
  TH1D* h1_114967;
  TH1D* h1_114968;
  TH1D* h1_114969;
  TH1D* h1_114970;
  TH1D* h1_114971;
  TH1D* h1_114972;
  TH1D* h1_114973;
  TH1D* h1_114974;
  TH1D* h1_114975;
  TH1D* h1_114976;
  TH1D* h1_114977;
  TH1D* h1_114978;
  TH1D* h1_114979;
  TH1D* h1_114980;
  TH1D* h1_114981;
  TH1D* h1_114982;
  TH1D* h1_114983;
  TH1D* h1_114984;
  TH1D* h1_114985;
  TH1D* h1_114986;
  TH1D* h1_114987;
  TH1D* h1_114988;
  TH1D* h1_114989;
  TH1D* h1_114990;
  TH1D* h1_114991;
  TH1D* h1_114992;
  TH1D* h1_114993;
  TH1D* h1_114994;
  TH1D* h1_114995;
  TH1D* h1_114996;
#endif
#endif //PHENO

#ifdef TTBAR                                       //ttbar 
 
#ifdef H1D
  TH1I* h1_105200; 
  TH1I* h1_105204; 
#endif

#ifdef H2D
  TH2F* h2_105200; 
  TH2F* h2_105204; 
    
  TH1D* h1_105200;
  TH1D* h1_105204;
#endif
#endif //end if TTBAR

#ifdef DIBOSON                                   //Diboson
  
#ifdef H1D
  TH1I* h1_105985; 
  TH1I* h1_105986; 
  TH1I* h1_105987; 
#endif

#ifdef H2D
  TH2F* h2_105985; 
  TH2F* h2_105986; 
  TH2F* h2_105987; 
    
  TH1D* h1_105985;
  TH1D* h1_105986;
  TH1D* h1_105987;
#endif
#endif //end if DIBOSON

#ifdef QCDEE                                    //QCD EE

#ifdef H1D
  TH1I* h1_108326; 
#endif
#ifdef H2D
  TH2F* h2_108326; 
  TH1D* h1_108326;
#endif 
#endif //QCDEE


#ifdef JX                                         //QCD JX
  
#ifdef H1D
  TH1I* h1_105009; 
  TH1I* h1_105010;
  TH1I* h1_105011;
  TH1I* h1_105012;
  TH1I* h1_105013;
  TH1I* h1_105014;
  TH1I* h1_105015;
#endif
#ifdef H2D
  TH2F* h2_105009; 
  TH2F* h2_105010;
  TH2F* h2_105011;
  TH2F* h2_105012;
  TH2F* h2_105013;
  TH2F* h2_105014;
  TH2F* h2_105015;

  TH1D* h1_105009; 
  TH1D* h1_105010;
  TH1D* h1_105011;
  TH1D* h1_105012;
  TH1D* h1_105013;
  TH1D* h1_105014;
  TH1D* h1_105015;
#endif
#endif //JX

#ifdef JXMUON                        //QCD muon filtered
  
#ifdef H1D
  TH1I* h1_109276; 
  TH1I* h1_109277;
  TH1I* h1_109278;
  TH1I* h1_109279;
  TH1I* h1_109280;
  TH1I* h1_109281;
  TH1I* h1_209435;
#endif

#ifdef H2D
  TH2F* h2_109276; 
  TH2F* h2_109277;
  TH2F* h2_109278;
  TH2F* h2_109279;
  TH2F* h2_109280;
  TH2F* h2_109281;
  TH2F* h2_209435;

  TH1D* h1_109276; 
  TH1D* h1_109277;
  TH1D* h1_109278;
  TH1D* h1_109279;
  TH1D* h1_109280;
  TH1D* h1_109281;
  TH1D* h1_209435;
#endif
#endif //JXMUON


#ifdef ZJETS                                 //Zjets

#ifdef H1D
  TH1I* h1_107650; 
  TH1I* h1_107651;
  TH1I* h1_107652;
  TH1I* h1_107653;
  TH1I* h1_107654;
  TH1I* h1_107655;
  TH1I* h1_107660; 
  TH1I* h1_107661;
  TH1I* h1_107662;
  TH1I* h1_107663;
  TH1I* h1_107664;
  TH1I* h1_107665;
  TH1I* h1_107670; 
  TH1I* h1_107671;
  TH1I* h1_107672;
  TH1I* h1_107673;
  TH1I* h1_107674;
  TH1I* h1_107675;
#endif

#ifdef H2D
  TH2F* h2_107650; 
  TH2F* h2_107651;
  TH2F* h2_107652;
  TH2F* h2_107653;
  TH2F* h2_107654;
  TH2F* h2_107655;
  TH2F* h2_107660; 
  TH2F* h2_107661;
  TH2F* h2_107662;
  TH2F* h2_107663;
  TH2F* h2_107664;
  TH2F* h2_107665;
  TH2F* h2_107670; 
  TH2F* h2_107671;
  TH2F* h2_107672;
  TH2F* h2_107673;
  TH2F* h2_107674;
  TH2F* h2_107675;

  TH1D* h1_107650; 
  TH1D* h1_107651;
  TH1D* h1_107652;
  TH1D* h1_107653;
  TH1D* h1_107654;
  TH1D* h1_107655;
  TH1D* h1_107660; 
  TH1D* h1_107661;
  TH1D* h1_107662;
  TH1D* h1_107663;
  TH1D* h1_107664;
  TH1D* h1_107665;
  TH1D* h1_107670; 
  TH1D* h1_107671;
  TH1D* h1_107672;
  TH1D* h1_107673;
  TH1D* h1_107674;
  TH1D* h1_107675;
#endif

#endif //ZJETS

#ifdef WJETS                             //Wjets

#ifdef H1D
  TH1I* h1_107680; 
  TH1I* h1_107681;
  TH1I* h1_107682;
  TH1I* h1_107683;
  TH1I* h1_107684;
  TH1I* h1_107685;

  TH1I* h1_107690; 
  TH1I* h1_107691;
  TH1I* h1_107692;
  TH1I* h1_107693;
  TH1I* h1_107694;
  TH1I* h1_107695;

  TH1I* h1_107700; 
  TH1I* h1_107701;
  TH1I* h1_107702;
  TH1I* h1_107703;
  TH1I* h1_107704;
  TH1I* h1_107705;

  TH1I* h1_106280; 
  TH1I* h1_106281; 
  TH1I* h1_106282; 
  TH1I* h1_106283; 
#endif

#ifdef H2D

  TH2F* h2_107680; 
  TH2F* h2_107681;
  TH2F* h2_107682;
  TH2F* h2_107683;
  TH2F* h2_107684;
  TH2F* h2_107685;

  TH2F* h2_107690; 
  TH2F* h2_107691;
  TH2F* h2_107692;
  TH2F* h2_107693;
  TH2F* h2_107694;
  TH2F* h2_107695;

  TH2F* h2_107700; 
  TH2F* h2_107701;
  TH2F* h2_107702;
  TH2F* h2_107703;
  TH2F* h2_107704;
  TH2F* h2_107705;

  TH1D* h1_107680; 
  TH1D* h1_107681;
  TH1D* h1_107682;
  TH1D* h1_107683;
  TH1D* h1_107684;
  TH1D* h1_107685;

  TH1D* h1_107690; 
  TH1D* h1_107691;
  TH1D* h1_107692;
  TH1D* h1_107693;
  TH1D* h1_107694;
  TH1D* h1_107695;

  TH1D* h1_107700; 
  TH1D* h1_107701;
  TH1D* h1_107702;
  TH1D* h1_107703;
  TH1D* h1_107704;
  TH1D* h1_107705;

//Wbb

  TH2F* h2_106280; 
  TH2F* h2_106281;
  TH2F* h2_106282;
  TH2F* h2_106283;

  TH1D* h1_106280; 
  TH1D* h1_106281;
  TH1D* h1_106282;
  TH1D* h1_106283;

#endif
#endif //WJETS


#ifdef DY                                  //Drell yan

#ifdef H1D
  TH1I* h1_108319;
  TH1I* h1_108320;
  TH1I* h1_108321;
  TH1I* h1_108322;
#endif

#ifdef H2D
  TH2F* h2_108319; 
  TH2F* h2_108320;
  TH2F* h2_108321;
  TH2F* h2_108322;

  TH1D* h1_108319; 
  TH1D* h1_108320;
  TH1D* h1_108321;
  TH1D* h1_108322;
#endif

#endif //DY

#endif

