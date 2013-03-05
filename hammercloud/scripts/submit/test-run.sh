#!/bin/bash

# Main runner for the HammerCloud tests.
# ARGUMENTS: <app> (app tag to use {atlas, cms, lhcb}).
#            <gangabin> (relative path of the Ganga binary).
#            <testid> (test number to run).
#            ... (remainders are passed to the config scripts).

echo 'Starting up HammerCloud test run'

if [ -z $1 ] ; then
    echo ' ERROR: app tag not set.'
    exit
else
    APP=$1
    shift
fi

if [ -z $1 ] ; then
    echo ' ERROR: Ganga binary not set.'
    exit
else
    GANGABIN=$1
    shift
fi

if [ -z $1 ] ; then
    echo 'ERROR: test ID not provided.'
    exit
else
    TESTID=$1
    shift
fi

# Get HCDIR from current installation.
HCDIR=`which $0 | sed 's/\/scripts/ /g' | awk '{print $1}'`

# Obtain a lock to continue running.
source $HCDIR/scripts/config/locks.sh $TESTID
if ! exlock_now ; then
    echo " WARNING: the test $TESTID is already running. Exiting."
    exit
fi

# Set up the core environment.
source $HCDIR/scripts/config/config-main.sh $APP $*

# Set up the submission environment.
source $HCDIR/scripts/config/config-submit.sh $GANGABIN $*

# Launch the test_generate action.
echo 'Launching the test_generate action...'
python $HCDIR/python/scripts/dispatcher.py -f test_generate -t $TESTID -m $HC_MODE

# Launch the test_submit action.
echo 'Launching the test_submit action...'
python $HCDIR/python/scripts/dispatcher.py -f test_submit -t $TESTID -m $HC_MODE

# Launch the test_report action.
echo 'Launching the test_report action...'
python $HCDIR/python/scripts/dispatcher.py -f test_report -t $TESTID -m $HC_MODE

# Unlock the lockfile.
unlock
