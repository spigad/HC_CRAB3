#!/bin/bash

# Script that sets up the main environment for HammerCloud scripts.
# ARGUMENTS: <app> (by default, core).

echo 'Setting up HammerCloud core environment...'

# Get HCDIR from current installation.
export HCDIR=`which $0 | sed 's/\/scripts/ /g' | awk '{print $1}'`
echo ' HCDIR'=$HCDIR

# Set HCDIR and HCAPP.
export APP=${1:-core}
echo ' APP='$APP
export HCAPP=$HCDIR/apps/$APP
echo ' HCAPP='$HCAPP

# Detect which RedHat are we running on.
export SL_RELEASE=`sed -rn 's/.*([0-9])\.[0-9].*/\1/p' /etc/redhat-release`
echo ' SL_RELEASE='$SL_RELEASE

# Import the GCC from AFS (Python is compiled with this one).
source /afs/cern.ch/sw/lcg/external/gcc/4.7/x86_64-slc$SL_RELEASE/setup.sh /afs/cern.ch/sw/lcg/contrib

# Activate the HammerCloud virtualenv.
source $HCDIR/external/venvs/sl$SL_RELEASE/bin/activate
echo ' PATH='$PATH
echo ' LD_LIBRARY_PATH='$LD_LIBRARY_PATH
echo " * Running on `python --version 2>&1`"
echo " * Running on GCC `gcc --version | grep ^gcc | sed 's/^.* //g' | sed 's/-.*/ /g'`"

# Export HammerCloud python zone.
export PYTHONPATH=$HCDIR/python:$HCDIR/apps:$HCDIR/web/src:$PYTHONPATH
echo ' PYTHONPATH='$PYTHONPATH

# Export HammerCloud settings.
export DJANGO_SETTINGS_MODULE='hc.settings'
echo ' DJANGO_SETTINGS_MODULE='$DJANGO_SETTINGS_MODULE

# Security config for Python 2.6.8+
# http://www.ocert.org/advisories/ocert-2011-003.html
export PYTHONHASHSEED=random

# Look for app specific settings.
if [ -e $HCAPP/scripts/config/config-main.sh ] ; then
    source $HCAPP/scripts/config/config-main.sh $*
fi
