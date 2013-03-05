#!/bin/bash

# Script to clean the summaries tables on the DB to make things faster.
# ARGUMENTS: <app> (must be set)

# Check the presence of an application on the arguments.
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
    echo " WARNING: the lock $LOCKFILE was taken. Exiting."
    exit
fi

# Set up the core environment.
source $HCDIR/scripts/config/config-main.sh $APP

# Launch the compress_summary_table to cleanup things in the DB.
echo 'Launching the compress_summary_table action...'
python $HCDIR/python/scripts/dispatcher.py -f compress_summary_table -o 'd'

# Unlock the lockfile.
unlock
