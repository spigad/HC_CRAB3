#!/bin/bash

# Wrapper to start up a Django shell with the HC environment set.
# ARGUMENTS: <command> (a Django CLI command, by default shell)

COMMAND=$1
shift

# Setup HammerCloud.
HCDIR=`which $0 | sed 's/\/scripts/ /g' | awk '{print $1}'`
source $HCDIR/scripts/config/config-main.sh

# Launch the Django CLI.
python $HCDIR/web/src/hc/manage.py ${COMMAND:-shell}
