#!/bin/bash

# Script that sets up the environment for the submission of a new test.
#ARGUMENTS: <gangabin> (full path to Ganga)

echo 'Setting up HammerCloud submission environment...'

# Check the presence of a gangabin on the arguments.
if [ -z $1 ] ; then
    echo ' INFO: gangabin argument not set.'
else
    export GANGABIN=$1
    echo ' GANGABIN='$GANGABIN
    shift
fi

# Look for app specific settings.
if [ -e $HCAPP/scripts/config/config-submit.sh ] ; then
    source $HCAPP/scripts/config/config-submit.sh
fi
