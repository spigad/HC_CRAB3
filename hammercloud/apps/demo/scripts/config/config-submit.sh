#!/bin/sh

echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
echo '    _                                                                 _'
echo '    _                         DEMO Configuration                      _'
echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._' 
echo '    _'
echo '    _'

#if [ -z $1 ]
#then
#    echo '    _  ERROR! Please, set DEMO_PARAM.'
#    echo '    _'
#    echo '    _                      End  DEMO  Configuration                   _'
#    echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
#    exit
#fi

# Possible options are:
#   p (param): DEMO_PARAM wanted
#

args=`getopt -o p: -- "$@"`
eval set -- "$args"

for i
do
  case "$i" in
        -pr) shift;echo '    _ param '$1;DEMO_PARAM=$1;shift;;
  esac
done

if [ -z $DEMO_PARAM ]
then
    echo '    _  ERROR! Please, set DEMO_PARAM.'
    echo '    _'
    echo '    _                     End  DEMO  Configuration                    _'
    echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
    exit
fi

if [ "$DEMO_PARAM" != dp -a "$DEMO_PARAM" != dp1 ]
then
    echo '    _ Wrong demo_param, '$DEMO_PARAM
    echo '    _ Using default demo_param=dp'
    DEMO_PARAM="dp"
fi

export X509_USER_PROXY=$HCAPP/config/x509up_$ROLE
echo '  X509_USER_PROXY='$X509_USER_PROXY

export DEMO_PARAM=$DEMO_PARAM
echo '  DEMO_PARAM='$DEMO_PARAM

echo '    _'
echo '    _                     End  DEMO  Configuration                    _'
echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
