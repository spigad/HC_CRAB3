#!/bin/sh

#ARGUMENTS: <app><gangabin><...>

echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
echo '    _                                                                 _'
echo '    _                      Submit  Configuration                      _'
echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._' 
echo '    _'
echo '    _'

if [ -z $1 ]
then
    echo '    _  ERROR! Please, set application tag.'
    echo '    _'
    echo '    _                    End  Submit  Configuration                   _'
    echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
    exit
else
    APP=$1
    shift
fi

if [ -z $1 ]
then
    echo '    _  ERROR! Please, set GangaBin.'
    echo '    _'
    echo '    _                    End  Submit  Configuration                   _'
    echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
    exit
else
    GANGABIN=$1
    shift
fi

#Set PROXY
export X509_USER_PROXY=$HCAPP/config/x509up
echo '    _  X509_USER_PROXY='$X509_USER_PROXY

#Set GangaBin
export GANGABIN=$GANGABIN
echo '    _  GANGABIN='$GANGABIN

echo '    _  Looking for app specific config script in '$HCAPP/scripts/config/config-submit.sh

if [ -e $HCAPP/scripts/config/config-submit.sh ]
then
    echo '    _    found: config-submit.sh'
    echo '    _  Sourced '$HCAPP/scripts/config/config-submit.sh $*    
    source $HCAPP/scripts/config/config-submit.sh $*
else
    echo '    _  Not found. Skipping.'

fi

echo '    _'
echo '    _                    End  Submit  Configuration                   _'
echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
