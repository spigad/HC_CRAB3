#!/bin/sh

echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
echo '    _                                                                 _'
echo '    _                       Main  Configuration                       _'
echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._' 
echo '    _'
echo '    _'

if [ -z $1 ]
then
    echo '    _  ERROR! Please, set application tag.'
    echo '    _'
    echo '    _                     End  Main  Configuration                    _'
    echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
    exit
fi

if [ -z $2 ]
then
    echo ' _  No HCDIR provided. Using HCDIR=/data/hammercloud'
    HCDIR=/data/hammercloud
else
    HCDIR=$2
fi

#Set HCDIR and HCAPP. Used in the other scripts.
export HCDIR=$HCDIR
export HCAPP=$HCDIR/apps/$1
echo '    _  HCDIR='$HCDIR
echo '    _  HCAPP='$HCAPP

#Set PROXY
export X509_USER_PROXY=$HCAPP/config/x509up
echo '    _  X509_USER_PROXY='$X509_USER_PROXY

echo '    _  Looking for newest Django intalled version in '$HCDIR/external

#Get the newest installed version of Django in $HCDIR/external
vals=`ls -F $HCDIR/external/ | grep 'Django' | sort -r`
if [ -z "$vals" ]
then
  echo '    _ ERROR! No Django instance found.'
  echo '    _'
  echo '    _                     End  Main  Configuration                    _'
  echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
  exit
fi

echo '    _    found: '$vals

version=`echo $vals|cut -d' ' -f1`
echo '    _  Using '$version

#Export hammercloud python zone.
export PYTHONPATH=$HCDIR/python

#Export Django & HammerCloud.
export PYTHONPATH=$PYTHONPATH:$HCDIR/external/$version:$HCDIR/web/src/

#Export HammerCloud settings.
export DJANGO_SETTINGS_MODULE=hc.settings

echo '    _  Looking for app specific config script in '$HCDIR/apps/$1/scripts/config

if [ -e $HCDIR/apps/$1/scripts/config/config-main.sh ]
then
    echo '    _    found: config-main.sh'
    echo '    _  Sourced '$HCDIR/apps/$1/scripts/config/config-main.sh    
    source $HCDIR/apps/$1/scripts/config/config-main.sh
fi

echo '    _'
echo '    _                     End  Main  Configuration                    _'
echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
