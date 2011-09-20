#!/bin/sh

echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
echo '    _                                                                 _'
echo '    _                        ATLAS Configuration                      _'
echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._' 
echo '    _'
echo '    _'


# Possible options are:
#   m (mode): type of test_generate and runtest.py
#

args=`getopt -o m: -- "$@"`
eval set -- "$args"

for i
do
  case "$i" in
        -m) shift;echo '    _ HC_MODE: '$1;HC_MODE=$1;shift;;
        --) shift
  esac
done

if [ -z $HC_MODE ]
then
    echo '    _ No MODE provided'
    echo '    _ Using default HC_MODE=default'
    HC_MODE="default"
fi

if [ "$HC_MODE" != default -a "$HC_MODE" != t3 -a "$HC_MODE" != prod ]
then
    echo '    _ Wrong mode, '$HC_MODE
    echo '    _ Using default HC_MODE=default'
    HC_MODE="default"
fi

export HC_MODE=$HC_MODE
echo '  HC_MODE='$HC_MODE

if [ "$HC_MODE" == prod ]
then
    #Set PROXY for Production testing
    export X509_USER_PROXY=$HCAPP/config/x509prod
    echo '  X509_USER_PROXY='$X509_USER_PROXY
fi

HAMMERCLOUD_ORIGINAL_PYTHONPATH=$PYTHONPATH:$HCDIR/external/ganga/install/HEAD/python
HAMMERCLOUD_ORIGINAL_PATH=$PATH

# Handle test job generation (starttime <= now and generated==0)
#   creates testdirs/test_N/jobs
source /afs/cern.ch/atlas/offline/external/GRID/ddm/DQ2Clients/setup.sh
echo '  Sourced DQ2 Client.'

#Dirty hack to use our own Ganga, but with our environment
export PYTHONPATH=$HAMMERCLOUD_ORIGINAL_PYTHONPATH:$PYTHONPATH
export PATH=$HAMMERCLOUD_ORIGINAL_PATH:$PATH

echo '    _'
echo '    _                    End  ATLAS  Configuration                    _'
echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
