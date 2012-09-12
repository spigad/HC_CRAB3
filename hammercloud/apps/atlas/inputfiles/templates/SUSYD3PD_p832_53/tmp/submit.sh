#!/bin/sh 
source /afs/cern.ch/sw/ganga/install/etc/setup-atlas.sh 
asetup 17.0.2 --single --testarea $PWD 
source RootCore/scripts/setup.sh 
ganga -o[Configuration]RUNTIME_PATH=/data/etp1/elmsheus/Ganga/GangaAtlas /data/etp1/elmsheus/Ganga/GangaAtlas/scripts/athena \
--inDS data11_7TeV.00180225.physics_Egamma.merge.NTUP_SUSYSKIM.r2603_p659_p832_tid607475_00 --cloud DE --outputdata histos.root \
 --user_area_path ./ --athena_release 17.0.2 --useRootCore --panda --cloud DE --excludedSite=ANALY_CERN,ANALY_CERN_XROOTD,ANALY_INFN-NAPOLI,ANALY_CSCS --split 2 --athena_exe EXE  --inputsandbox grl/data11_7TeV.periodAllYear_DetStatus-v36-pro10_CoolRunQuery-00-04-08_Susy.xml:iLumiCalc/ilumicalc_histograms_EF_e20_medium_178044-184169.root:iLumiCalc/ilumicalc_histograms_EF_mu18_178044-184169.root:SUSYTools/data/fest_periodF_v1.root:iLumiCalc/PileUp101111Run3.root runGanga.sh
