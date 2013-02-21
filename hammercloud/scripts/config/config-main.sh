#!/bin/bash

# Script that sets up the main environment for HammerCloud scripts.
# ARGUMENTS: <app> (by default, core).

echo 'Setting up HammerCloud core environment...'

# Save current configuration for other scripts.
export HC_ORIGINAL_PATH=$PATH
export HC_ORIGINAL_PYTHONPATH=$PYTHONPATH

# Get HCDIR from current installation.
export HCDIR=`which $0 | sed 's/\/scripts/ /g' | awk '{print $1}'`
echo ' HCDIR'=$HCDIR

# Set HCDIR and HCAPP.
export APP=${1:-core}
echo ' APP='$APP
export HCAPP=$HCDIR/apps/$APP
echo ' HCAPP='$HCAPP

# Activate the HammerCloud virtualenv.
source $HCDIR/external/bin/activate
echo ' PATH='$PATH

# Export HammerCloud python zone.
export PYTHONPATH=$HCDIR/python:$HCDIR/apps:$HCDIR/web/src
echo ' PYTHONPATH='$PYTHONPATH

# Export HammerCloud settings.
export DJANGO_SETTINGS_MODULE='hc.settings'
echo ' DJANGO_SETTINGS_MODULE'$DJANGO_SETTINGS_MODULE

# Look for app specific settings.
if [ -e $HCAPP/scripts/config/config-main.sh ] ; then
    source $HCAPP/scripts/config/config-main.sh
fi
