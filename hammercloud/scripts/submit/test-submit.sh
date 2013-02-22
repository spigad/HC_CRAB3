#!/bin/bash

# Wrapper for GangaRobot at submission stage.
# ARGUMENTS: <testid> (test number to run).
#            <extraargs> (extra arguments to pass to Ganga).
# NOTES: the env X509_USER_PROXY, APP, HCAPP and GANGABIN must be set properly.

if [ -z $1 ] ; then
    echo ' ERROR: no test ID provided.'
    exit
fi

# List the jobs to be submitted.
echo "Submitting test $1 with jobs in $HCAPP/testdirs/test_$1/jobs:"
ls $HCAPP/testdirs/test_$1/jobs/*

echo "Cleaning $HCAPP/testdirs/test_$1/gangadir"
rm -rf $HCAPP/testdirs/test_$1/gangadir

echo 'Launching Ganga for submission...'
$GANGABIN --config=$HCAPP/config/$APP-ROBOTStart.INI.50 -o[Logging]_format=VERBOSE -o[Configuration]gangadir=$HCAPP/testdirs/test_$1/gangadir -o[Logging]_logfile=$HCAPP/testdirs/test_$1/ganga.log $2 robot run $HCAPP/testdirs/test_$1/jobs/*
