#!/bin/sh

#ARGUMETNS: <testid><...>

if [ -z $1 ]
then
    echo '_  ERROR! Please, set test ID.'
    exit
fi

echo X509_USER_PROXY=$X509_USER_PROXY
echo HCAPP=$HCAPP
echo APP=$APP
echo GANGABIN=$GANGABIN
echo PYTHONPATH=$PYTHONPATH

echo Submitting test $1 with jobs in $HCAPP/testdirs/test_$1/jobs:
ls $HCAPP/testdirs/test_$1/jobs/*

echo Cleaning $HCAPP/testdirs/test_$1/gangadir
rm -rf $HCAPP/testdirs/test_$1/gangadir

# Start GangaRobot
if [ -e /afs/cern.ch/sw/ganga/install/etc/setup-atlas.sh ]
then
    source /afs/cern.ch/sw/ganga/install/etc/setup-atlas.sh latest
fi
export GANGA_CONFIG_PATH=$GANGA_CONFIG_PATH:GangaAtlas/Atlas.ini:$HCAPP/config/GangaAtlas.ini.50

echo $GANGABIN --config=$HCAPP/config/$APP-ROBOTStart.INI.50 -o[Configuration]gangadir=$HCAPP/testdirs/test_$1/gangadir -o[Logging]_logfile=$HCAPP/testdirs/test_$1/ganga.log -o[Panda]processingType=hammercloud -o[LCG]JobLogHandler=DQ2 -o[MonitoringServices]Athena/LCG=Ganga.Lib.MonitoringServices.Dashboard.LCGAthenaMS.LCGAthenaMS -o[DQ2]OUTPUTDATASET_LIFETIME='2_days' $2 robot run $HCAPP/testdirs/test_$1/jobs/*
$GANGABIN --config=$HCAPP/config/$APP-ROBOTStart.INI.50 -o[Configuration]gangadir=$HCAPP/testdirs/test_$1/gangadir -o[Logging]_logfile=$HCAPP/testdirs/test_$1/ganga.log -o[Panda]processingType=hammercloud -o[LCG]JobLogHandler=DQ2 -o[MonitoringServices]Athena/LCG=Ganga.Lib.MonitoringServices.Dashboard.LCGAthenaMS.LCGAthenaMS -o[DQ2]OUTPUTDATASET_LIFETIME='2_days' $2 robot run $HCAPP/testdirs/test_$1/jobs/*



