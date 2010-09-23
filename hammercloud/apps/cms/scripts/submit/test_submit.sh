#!/bin/sh

#ARGUMETNS: <testid><...>

if [ -z $1 ]
then
    echo '_  ERROR! Please, set test ID.'
    exit
fi

echo X509_USER_PROXY=$X509_USER_PROXY
echo HCAPP=$HCAPP
echo GANGABIN=$GANGABIN
echo PYTHONPATH=$PYTHONPATH
echo CMS_SITEDB_CACHE_DIR=$CMS_SITEDB_CACHE_DIR
echo CMS_CRAB_CACHE_DIR=$CMS_CRAB_CACHE_DIR
echo CMSSW_VERSION=$CMSSW_VERSION

echo Submitting test $1 with jobs in $HCAPP/testdirs/test_$1/jobs:
ls $HCAPP/testdirs/test_$1/jobs/*

echo Cleaning $HCAPP/testdirs/test_$1/gangadir
rm -rf $HCAPP/testdirs/test_$1/gangadir

echo $GANGABIN --config=$HCAPP/config/CMS_ROBOTStart.INI.50 -o[Configuration]gangadir=$HCAPP/testdirs/test_$1/gangadir -o[CMSSW]CMSSW_VERSION=$CMSSW_VERSION -o[Logging]_logfile=$HCAPP/testdirs/test_$1/ganga.log $3 robot run $HCAPP/testdirs/test_$1/jobs/*
$GANGABIN --config=$HCAPP/config/CMS_ROBOTStart.INI.50 -o[Configuration]gangadir=$HCAPP/testdirs/test_$1/gangadir -o[CMSSW]CMSSW_VERSION=$CMSSW_VERSION -o[Logging]_logfile=$HCAPP/testdirs/test_$1/ganga.log $3 robot run $HCAPP/testdirs/test_$1/jobs/*

