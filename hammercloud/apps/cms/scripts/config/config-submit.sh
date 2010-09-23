#!/bin/sh

echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
echo '    _                                                                 _'
echo '    _                         CMS Configuration                       _'
echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._' 
echo '    _'
echo '    _'

if [ -z $1 ]
then
    echo '    _  ERROR! Please, set CMSSW_VERSION.'
    echo '    _'
    echo '    _                      End  CMS  Configuration                    _'
    echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
    exit
fi

#Set TMPDIR
export TMPDIR=/tmp
echo '    _  TMPDIR='/tmp

#Set CMS_SITEDB_CACHE_DIR
export CMS_SITEDB_CACHE_DIR=/tmp
echo '    _ CMS_SITEDB_CACHE_DIR=/tmp'

#Set CMS_CRAB_CACHE_DIR
export CMS_CRAB_CACHE_DIR=/tmp
echo '    _ CMS_CRAB_CACHE_DIR=/tmp'

#Set CMSSW_VERSION
export CMSSW_VERSION=$1
echo '    _ CMSSW_VERSION='$1

echo '    _'
echo '    _                     End  CMS  Configuration                     _'
echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
