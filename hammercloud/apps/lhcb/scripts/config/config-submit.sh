#!/bin/sh

echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
echo '    _                                                                 _'
echo '    _                        LHCb Configuration                       _'
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
#   r (role)   : proxy role, values accepted are production,user.  
#   m (mode): type of test_generate and runtest.py
#

args=`getopt -o r:m: -- "$@"`
eval set -- "$args"

for i
do
  case "$i" in
        -r) shift;echo '    _ HC_ROLE '$1;HC_ROLE=$1;shift;;
        -m) shift;echo '    _ HC_MODE: '$1;HC_MODE=$1;shift;;
  esac
done

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
    ROLE="user"
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

HAMMERCLOUD_ORIGINAL_PYTHONPATH=$PYTHONPATH:$HCDIR/external/ganga/install/HEAD/python
HAMMERCLOUD_ORIGINAL_PATH=$PATH 

#export HOME=$HCDIR/external/$APP
#Done this to avoid recurrent problem with .rhosts...
#echo '    _ HOME='$HCDIR/external/$APP

echo '    _  Sourced GridEnvironment'
source /afs/cern.ch/project/gd/LCG-share/sl4/etc/profile.d/grid-env.sh

echo '    _  Sourced LbLogin'
source /afs/cern.ch/lhcb/software/releases/LBSCRIPTS/LBSCRIPTS_v5r1/InstallArea/scripts/LbLogin.sh

echo '    _  SetupProject Ganga'
SetupProject Ganga

#Dirty hack to use our own Ganga, but with our environment
export PYTHONPATH=$HAMMERCLOUD_ORIGINAL_PYTHONPATH:$PYTHONPATH
export PATH=$HAMMERCLOUD_ORIGINAL_PATH:$PATH


echo '    _'
echo '    _                    End  LHCb  Configuration                     _'
echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
