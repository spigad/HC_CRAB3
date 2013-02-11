#!/bin/sh

# Wrapper to start up a Django shell with the HC environment set.
# ARGUMENTS: <command>

# Get HCDIR from current installation.
# TODO(rmedrano): This makes mandatory to run this script with the full path.
HCDIR=`which $0|sed 's/\/scripts/ /g' | awk '{print $1}'`

# Setup the virtualenv of HammerCloud
source $HCDIR/external/bin/activate
export PYTHONPATH=$HCDIR/python:$HCDIR/apps:$HCDIR/web/src

# debugsqlshell needs django-toolbar installed.
python $HCDIR/web/src/hc/manage.py ${1:-shell}
