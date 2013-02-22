#!/bin/bash

# Script that sets up the main environment for HammerCloud scripts for ATLAS.
# ARGUMENTS: -m <mode> (if not set, defaults to 'default').

echo 'Setting up HammerCloud ATLAS submission environment...'

# Source the config-main script.
HCAPP=`which $0 | sed 's/\/scripts/ /g' | awk '{print $1}'`
if [ -e $HCAPP/scripts/config/config-main.sh ] ; then
    source $HCAPP/scripts/config/config-main.sh $*
else
    echo ' ERROR: app config-main.sh not found!'
    exit
fi

# Custom configurations for submission may follow.
