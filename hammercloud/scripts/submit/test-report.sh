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

echo `date -u` Reading $HCAPP/testdirs/test_$1/gangadir

echo `date -u` ganga runtest

echo $GANGABIN --config=$HCAPP/config/$APP-ROBOT.INI.50 -o[Configuration]gangadir=$HCAPP/testdirs/test_$1/gangadir -o[Logging]_logfile=$HCAPP/testdirs/test_$1/ganga.log $2 $HCAPP/python/scripts/runtest_$HC_MODE.py $1
$GANGABIN --config=$HCAPP/config/$APP-ROBOT.INI.50 -o[Configuration]gangadir=$HCAPP/testdirs/test_$1/gangadir -o[Logging]_logfile=$HCAPP/testdirs/test_$1/ganga.log $2 $HCAPP/python/scripts/runtest_$HC_MODE.py $1

