#!/bin/bash

# SLS monitor for HC.

# Get HCDIR from current installation.
HCDIR=`which $0 | sed 's/\/scripts/ /g' | awk '{print $1}'`

# Obtain a lock to continue running.
source $HCDIR/scripts/config/locks.sh
if ! exlock_now ; then
    echo " WARNING: the lock $LOCKFILE was taken. Exiting."
    exit
fi

# Set up the core environment directly for core.
source $HCDIR/scripts/config/config-main.sh

# Launch the SLS monitor.
echo 'Launching the sls_sensor action...'
python $HCDIR/python/scripts/dispatcher.py -f sls_sensor

# Unlock the lockfile.
unlock
