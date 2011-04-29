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
echo DEMO_PARAM=$DEMO_PARAM


echo `date -u` Reading $HCAPP/testdirs/test_$1/gangadir

echo `date -u` ganga runtest

echo $GANGABIN --config=$HCAPP/config/DEMO_ROBOT.INI.50 -o[Configuration]gangadir=$HCAPP/testdirs/test_$1/gangadir -o[DEMO]DEMO_PARAM=$DEMO_PARAM -o[Logging]_logfile=$HCAPP/testdirs/test_$1/ganga.log $2 $HCAPP/python/scripts/runtest.py $1
$GANGABIN --config=$HCAPP/config/DEMO_ROBOT.INI.50 -o[Configuration]gangadir=$HCAPP/testdirs/test_$1/gangadir -o[DEMO]DEMO_PARAM=$DEMO_PARAM -o[Logging]_logfile=$HCAPP/testdirs/test_$1/ganga.log $2 $HCAPP/python/scripts/runtest.py $1

