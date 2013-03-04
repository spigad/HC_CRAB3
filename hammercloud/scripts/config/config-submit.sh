#!/bin/bash

# Script that sets up the environment for the submission of a new test.
#ARGUMENTS: <gangabin> (full path to Ganga)

echo 'Setting up HammerCloud submission environment...'

# Check the presence of a gangabin on the arguments.
if [ -z $1 ] ; then
    echo ' WARNING: gangabin argument not set.'
else
    export GANGABIN=$1
    echo ' GANGABIN='$GANGABIN
    shift
fi

# Set the proxy to be used.
export X509_USER_PROXY=$HCAPP/config/x509up
echo ' X509_USER_PROXY='$X509_USER_PROXY

# Look for app specific settings.
if [ -e $HCAPP/scripts/config/config-submit.sh ] ; then
    source $HCAPP/scripts/config/config-submit.sh $*
fi
