#!/bin/bash

# Script that sets up the main environment for HammerCloud scripts for LHCb.
# ARGUMENTS: -r <role> (proxy role {production, user}).
#            -m <mode> (if not set, defaults to 'default').

echo 'Setting up HammerCloud LHCb environment...'

# Parse the arguments to find the mode. Save the args to avoid collaterals.
HC_MODE='default'
HC_ROLE='user'
ARGS=$*
set -- `getopt -u -o r:v:m: -- $@`

while [ $# -gt 0 ] ; do
    case $1 in
        -r) shift; export HC_ROLE=$1; shift;;
        -m) shift; export HC_MODE=$1; shift;;
        *) shift;;
    esac
done

# Restore the args (caller scripts might don't want to have them changed).
set -- $ARGS

# Validate the HC_ROLE setup.
if [ "$HC_ROLE" != user -a "$HC_ROLE" != production ] ; then
    echo ' ERROR: wrong role selected.'
    exit
fi
echo ' HC_ROLE='$HC_ROLE

# Validate the HC_MODE setup.
if [ "$HC_MODE" != default -a "$HC_MODE" != site ] ; then
    echo ' ERROR: wrong mode selected.'
    exit
fi
echo ' HC_MODE='$HC_MODE

# Setup the proxies.
HCAPP=`which $0 | sed 's/\/scripts/ /g' | awk '{print $1}'`
export X509_USER_PROXY=$HCAPP/config/x509up_$HC_ROLE
echo ' X509_USER_PROXY='$X509_USER_PROXY

# Save the current paths, so we can restore them after sourcing PanDA tools.
HAMMERCLOUD_ORIGINAL_PYTHONPATH=$PYTHONPATH
HAMMERCLOUD_ORIGINAL_PATH=$PATH

# Source the LHCbDIRAC tools.
echo 'Sourcing LHCbDIRAC...'
source /opt/dirac/bashrc

echo 'Sourcing Grid Environment from AFS...'
source /afs/cern.ch/project/gd/LCG-share/sl4/etc/profile.d/grid-env.sh

echo 'Sourcing LbLogin from AFS...'
source /afs/cern.ch/lhcb/software/releases/LBSCRIPTS/LBSCRIPTS_v5r1/InstallArea/scripts/LbLogin.sh

echo 'SetupProject Ganga...'
SetupProject Ganga

# Restore the original paths, so we use our own Python and Ganga.
export PYTHONPATH=$HAMMERCLOUD_ORIGINAL_PYTHONPATH:$PYTHONPATH
export PATH=$HAMMERCLOUD_ORIGINAL_PATH:$PATH
