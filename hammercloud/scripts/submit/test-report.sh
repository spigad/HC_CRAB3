#!/bin/bash

# Wrapper for GangaRobot at reporting stage.
# ARGUMENTS: <testid> (test number to run).
#            <extraargs> (extra arguments to pass to Ganga).
# NOTES: the env X509_USER_PROXY, APP, HCAPP, HC_MODE and GANGABIN must be set
#        properly.

if [ -z $1 ] ; then
    echo ' ERROR: no test ID provided.'
    exit
fi

# Minilog information for test status change.
echo "Reading $HCAPP/testdirs/test_$1/gangadir"

echo 'Launching Ganga for reporting...'
umask 022
$GANGABIN --config=$HCAPP/config/$APP-ROBOT.INI.50 -o[Logging]_format=VERBOSE -o[Configuration]gangadir=$HCAPP/testdirs/test_$1/gangadir -o[Logging]_logfile=$HCAPP/testdirs/test_$1/ganga.log $2 $HCAPP/python/scripts/runtest_$HC_MODE.py $1
