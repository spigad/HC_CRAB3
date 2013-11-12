#!/bin/bash

# Wrapper to start up a Django shell with the HC environment set.
# ARGUMENTS: <app> (the HammerCloud app name)
#            <command> (a Django CLI command, by default shell)

APP=$1
COMMAND=$*

# Setup HammerCloud.
HCDIR=`which $0 | sed 's/\/scripts/ /g' | awk '{print $1}'`
source $HCDIR/scripts/config/config-main.sh

# Launch the Django CLI (remove the app name).
shift
python $HCDIR/web/src/hc/manage.py ${COMMAND:-shell}

