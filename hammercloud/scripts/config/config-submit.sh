#!/bin/sh

#ARGUMENTS: <gangabin><...>

echo ''
echo '_ Submit  Configuration.'
echo ''

if [ -z $1 ]
then
    echo '  ERROR! Please, set GangaBin.'
    echo ''
    echo '_ End  Submit  Configuration.'
    echo ''
    exit
else
    GANGABIN=$1
    shift
fi

#Set PROXY
export X509_USER_PROXY=$HCAPP/config/x509up
echo '  X509_USER_PROXY='$X509_USER_PROXY

#Set GangaBin
export GANGABIN=$GANGABIN
echo '  GANGABIN='$GANGABIN

echo '  Looking for app specific config script in '$HCAPP/scripts/config/config-submit.sh

if [ -e $HCAPP/scripts/config/config-submit.sh ]
then
    echo '   found: config-submit.sh'
    echo '   Sourced '$HCAPP/scripts/config/config-submit.sh $*    
    source $HCAPP/scripts/config/config-submit.sh $*
else
    echo '   not found. Skipping.'

fi

echo ''
echo '_ End  Submit  Configuration.'
echo ''
