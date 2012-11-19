#!/bin/sh

# Wrapper to start up a Django shell with the HC environment set.
# ARGUMENTS: <app>

echo '# HammerCloud Django Shell'

if [ -z $1 ]
then
    echo '  WARNING: using default app demo'
    export HC_SHELL_APP=demo
else
    export HC_SHELL_APP=$1
fi

# Get HCDIR from current installation.
# TODO(rmedrano): This makes mandatory to run this script with the full path.
HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`

# Do the config_main, for PATH and PYTHONPATH.
source $HCDIR/scripts/config/config-main.sh $HC_SHELL_APP

cd $HCDIR/web/src/hc

# debugsqlshell needs django-toolbar installed.
python manage.py debugsqlshell
