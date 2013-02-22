#!/bin/bash

# Configuration script for the submission role of a machine.
# ARGUMENTS: <app> (must be set)

# Check the presence of a gangabin on the arguments.
if [ -z $1 ] ; then
    echo ' ERROR: application argument not set.'
    exit
else
    export APP=$1
    shift
fi

# Get HCDIR from current installation.
HCDIR=`which $0 | sed 's/\/scripts/ /g' | awk '{print $1}'`

# Obtain a lock to continue running.
source $HCDIR/scripts/config/locks.sh
if ! exlock_now ; then
    echo ' WARNING: the lock $LOCKFILE was taken. Exiting.'
    exit
fi

# Set up the core environment.
source $HCDIR/scripts/config/config-main.sh $APP

# Launch the test_alarm script to update loads.
echo 'Launching the test_alarm action...'
python $HCDIR/python/scripts/dispatcher.py -f test_alarm

# Unlock the lockfile.
unlock
