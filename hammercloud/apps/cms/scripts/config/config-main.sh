#!/bin/bash

# Script that sets up the main environment for HammerCloud scripts for CMS.
# ARGUMENTS: -v <version> (CMSSW_VERSION wanted).
#            -r <role> (proxy role {production, user}).
#            -m <mode> (if not set, defaults to 'default').

echo 'Setting up HammerCloud CMS environment...'

# Parse the arguments to find the mode. Save the args to avoid collaterals.
export HC_MODE='default'
export HC_ROLE='user'
ARGS=$*
set -- `getopt -u -o r:v:m: -- $@`

while [ $# -gt 0 ] ; do
    case $1 in
        -r) shift; export HC_ROLE=$1; shift;;
        -v) shift; export CMSSW_VERSION=$1; shift;;
        -m) shift; export HC_MODE=$1; shift;;
        *) shift;;
    esac
done

# Restore the args (caller scripts might don't want to have them changed).
set -- $ARGS

# Validate the CMSSW_VERSION setup.
if [ -z $CMSSW_VERSION ] ; then
    echo ' WARNING: no CMSSW version provided (-v).'
fi
echo ' CMSSW_VERSION='$CMSSW_VERSION

# Validate the HC_ROLE setup.
if [ "$HC_ROLE" != user -a "$HC_ROLE" != production -a "$HC_ROLE" != production2 -a "$HC_ROLE" != user2 ] ; then
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
export X509_USER_PROXY=$HCAPP/config/x509up_$HC_ROLE
echo ' X509_USER_PROXY='$X509_USER_PROXY

# Set some options for CRAB/CMSSW.
export TMPDIR=/tmp
export CMS_SITEDB_CACHE_DIR=$TMPDIR
export CMS_CRAB_CACHE_DIR=$TMPDIR
echo ' TMPDIR='$TMPDIR
echo ' CMS_SITEDB_CACHE_DIR='$CMS_SITEDB_CACHE_DIR
echo ' CMS_CRAB_CACHE_DIR='$CMS_CRAB_CACHE_DIR
