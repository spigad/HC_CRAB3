#!/bin/sh

echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
echo '    _                                                                 _'
echo '    _                         CMS Configuration                       _'
echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._' 
echo '    _'
echo '    _'

#if [ -z $1 ]
#then
#    echo '    _  ERROR! Please, set CMSSW_VERSION.'
#    echo '    _'
#    echo '    _                      End  CMS  Configuration                    _'
#    echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
#    exit
#fi

# Possible options are:
#   v (version): CMSSW_VERSION wanted
#   r (role)   : proxy role, values accepted are production,user.
#   m (mode)   : type of test_generate and runtest.py
#

args=`getopt -o r:v:m: -- "$@"`
eval set -- "$args"

for i
do
  case "$i" in
        -r) shift;echo '    _ HC_ROLE '$1;HC_ROLE=$1;shift;;
        -v) shift;echo '    _ CMSSW_VERSION: '$1;CMSSW_VERSION=$1;shift;;
        -m) shift;echo '    _ HC_MODE: '$1;HC_MODE=$1;shift;;
  esac
done

if [ -z $CMSSW_VERSION ]
then
    echo '    _  ERROR! Please, set CMSSW_VERSION.'
    echo '    _'
    echo '    _                      End  CMS  Configuration                    _'
    echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
    exit
fi

if [ -z $HC_ROLE ]
then
    echo '    _ No HC_ROLE provided'
    echo '    _ Using default HC_ROLE=user'
    HC_ROLE="user"
fi

if [ "$HC_ROLE" != user -a "$HC_ROLE" != production ]
then
    echo '    _ Wrong role, '$HC_ROLE
    echo '    _ Using default HC_ROLE=user'
    HC_ROLE="user"
fi

if [ -z $HC_MODE ]
then
    echo '    _ No MODE provided'
    echo '    _ Using default HC_MODE=default'
    HC_MODE="default"
fi

if [ "$HC_MODE" != default -a "$HC_MODE" != site ]
then
    echo '    _ Wrong mode, '$HC_MODE
    echo '    _ Using default HC_MODE=default'
    HC_MODE="default"
fi

export HC_MODE=$HC_MODE
echo '  HC_MODE='$HC_MODE

export X509_USER_PROXY=$HCAPP/config/x509up_$HC_ROLE
echo '  X509_USER_PROXY='$X509_USER_PROXY

#Set TMPDIR
export TMPDIR=/tmp
echo '    _ TMPDIR='/tmp

#Set CMS_SITEDB_CACHE_DIR
export CMS_SITEDB_CACHE_DIR=/tmp
echo '    _ CMS_SITEDB_CACHE_DIR=/tmp'

#Set CMS_CRAB_CACHE_DIR
export CMS_CRAB_CACHE_DIR=/tmp
echo '    _ CMS_CRAB_CACHE_DIR=/tmp'

#Set CMSSW_VERSION
export CMSSW_VERSION=$CMSSW_VERSION
echo '    _ CMSSW_VERSION='$CMSSW_VERSION

echo '    _'
echo '    _                     End  CMS  Configuration                     _'
echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
