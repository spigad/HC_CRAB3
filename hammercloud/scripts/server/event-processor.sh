#!/bin/bash

# Wrapper for the event processor process, that publish stuff from the queue.
# If this is launched in a cronjob, please append to the logfile.
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

# Launch the event processor, which is not running.
echo 'Launching the event_processor action...'
python $HCDIR/python/scripts/dispatcher.py -f event_processor

# Unlock the lockfile.
unlock
