#!/bin/sh 
source /afs/cern.ch/sw/ganga/install/etc/setup-atlas.sh 
asetup 17.0.2 --single --testarea $PWD 
ganga -o[Configuration]RUNTIME_PATH=/data/etp1/elmsheus/Ganga/GangaAtlas /data/etp1/elmsheus/Ganga/GangaAtlas/scripts/athena \
  --inDS data11_7TeV.00191635.physics_Egamma.merge.NTUP_SUSYSKIM.f414_m1025_p832_tid607689_00 --cloud DE --outputdata  \
  trigger_191635_electronStream.root,trigger_191635_electronStream.txt  --user_area tarball.tar.gz  --athena_release 17.0.2 \
  --useRootCore --panda --cloud DE --excludedSite=ANALY_CERN,ANALY_CERN_XROOTD,ANALY_INFN-NAPOLI,ANALY_CSCS --split 2 \
  --athena_exe EXE --outDS _191635_electronStream.M.090212.1 \
  --inputsandbox iLumiCalc/data11_7TeV.periodAllYear_DetStatus-v36-pro10_CoolRunQuery-00-04-08_Susy.xml:iLumiCalc/ilumicalc_histograms_EF_e20_medium_178044-184169.root:iLumiCalc/ilumicalc_histograms_EF_mu18_178044-184169.root:iLumiCalc/fest_periodF_v1.root:iLumiCalc/PileUp101111Run3.root runGanga.sh
