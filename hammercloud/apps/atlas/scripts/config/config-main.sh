#!/bin/bash

# Script that sets up the main environment for HammerCloud scripts for ATLAS.
# ARGUMENTS: -m <mode> (if not set, defaults to 'default').

echo 'Setting up HammerCloud ATLAS environment...'

# Parse the arguments to find the mode. Save the args to avoid collaterals.
export HC_MODE='default'
ARGS=$*
set -- `getopt -u -o m: --long doit,days: -- "$@"`

while [ $# -gt 0 ] ; do
    case $1 in
        -m) shift; export HC_MODE=$1; shift;;
        --doit) shift;;
        --days) shift; shift;;
        *) shift;;
    esac
done

# Restore the args (caller scripts might don't want to have them changed).
set -- $ARGS

# Validate the HC_MODE setup.
if [ "$HC_MODE" != default -a "$HC_MODE" != t3 -a "$HC_MODE" != prod -a "$HC_MODE" != experimental ] ; then
    echo ' ERROR: wrong mode selected.'
    exit
fi
echo ' HC_MODE='$HC_MODE

# Setup the proxies.
if [ "$HC_MODE" == prod ] ; then
    # Redefine the proxy for Production testing.
    export X509_USER_PROXY=$HCAPP/config/x509rprod
else
    # For the ATLAS case, the proxy is also different for other purposes.
    export X509_USER_PROXY=$HCAPP/config/x509rp
fi
echo ' X509_USER_PROXY='$X509_USER_PROXY

# Save the current paths, so we can restore them after sourcing PanDA tools.
HAMMERCLOUD_ORIGINAL_PYTHONPATH=$PYTHONPATH
HAMMERCLOUD_ORIGINAL_PATH=$PATH

# Source PanDA client from AFS.
echo 'Sourcing PanDA tools from AFS...'
source /afs/cern.ch/atlas/offline/external/GRID/DA/panda-client/latest/etc/panda/panda_setup.sh

# The DQ2 client is now installed locally.
echo 'Sourcing DQ2 client...'
source /opt/dq2/profile.d/dq2_common_env.sh
export DQ2_ENDUSER_SETUP=True
export RUCIO_ACCOUNT=gangarbt
export DQ2_LOCAL_SITE_ID=ROAMING
export PYTHONPATH=/opt/dq2/lib:$PYTHONPATH

# Restore the original paths, so we use our own Python and Ganga.
export PYTHONPATH=$HAMMERCLOUD_ORIGINAL_PYTHONPATH:$PYTHONPATH
export PATH=$HAMMERCLOUD_ORIGINAL_PATH:$PATH
