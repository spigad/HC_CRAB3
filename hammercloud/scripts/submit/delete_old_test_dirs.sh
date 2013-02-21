#!/bin/bash

# Script to clean up the old directories of tests in HammerCloud.
# ARGUMENTS: all of them passed to the action.

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

# Run copy script.
echo 'Launching the cleanup action...'
python $HCDIR/python/scripts/submit/delete_old_test_dirs.py $*

# Unlock the lockfile.
unlock
