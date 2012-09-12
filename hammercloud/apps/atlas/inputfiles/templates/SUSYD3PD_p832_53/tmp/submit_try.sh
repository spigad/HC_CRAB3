#!/bin/sh

#source /afs/cern.ch/sw/ganga/install/etc/setup-atlas.sh 
#asetup 17.0.2 --single --testarea $PWD 
#source RootCore/scripts/setup.sh 

#first submission:

#ganga -o[Configuration]RUNTIME_PATH=/data/etp1/elmsheus/Ganga/GangaAtlas /data/etp1/elmsheus/Ganga/GangaAtlas/scripts/athena --inDS data11_7TeV.00191676.physics_Muons.merge.NTUP_SUSYSKIM.f414_m1025_p832_tid607933_00 --cloud DE --outputdata trigger_191676_muonStream.root,trigger_191676_muonStream.txt --user_area_path /data/etp4/flegger/gangadir/tarball --athena_release 17.0.2 --useRootCore --panda --split 2 --athena_exe EXE --inputsandbox grl/data11_7TeV.periodAllYear_DetStatus-v36-pro10_CoolRunQuery-00-04-08_Susy.xml:iLumiCalc/ilumicalc_histograms_EF_e20_medium_178044-184169.root:iLumiCalc/ilumicalc_histograms_EF_mu18_178044-184169.root:EF_mu18.root:SUSYTools/data/fest_periodF_v1.root:iLumiCalc/PileUp101111Run3.root runGanga.sh

FILES=/data/etp4/flegger/gangadir/tarball/job*.tar.gz
for f in $FILES
do
  echo "Submitting tarball $f ..."
done

echo ${FILES[0]}

ganga -o[Configuration]RUNTIME_PATH=/data/etp1/elmsheus/Ganga/GangaAtlas /data/etp1/elmsheus/Ganga/GangaAtlas/scripts/athena --inDS data11_7TeV.00191676.physics_Muons.merge.NTUP_SUSYSKIM.f414_m1025_p832_tid607933_00 --cloud DE --outputdata trigger_191676_muonStream.root,trigger_191676_muonStream.txt --user_area ${FILES[0]} --athena_release 17.0.2 --useRootCore --panda --split 2 --athena_exe EXE --inputsandbox grl/data11_7TeV.periodAllYear_DetStatus-v36-pro10_CoolRunQuery-00-04-08_Susy.xml:iLumiCalc/ilumicalc_histograms_EF_e20_medium_178044-184169.root:iLumiCalc/ilumicalc_histograms_EF_mu18_178044-184169.root:EF_mu18.root:SUSYTools/data/fest_periodF_v1.root:iLumiCalc/PileUp101111Run3.root runGanga.sh
 
