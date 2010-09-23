#!/bin/sh

#ARGUMENTS: <app>

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

#Get HCDIR from current installation.
HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`

#Set HCDIR and HCAPP. Used in the other scripts.
export HCDIR=$HCDIR
export HCAPP=$HCDIR/apps/$1
echo '    _  HCDIR='$HCDIR
echo '    _  HCAPP='$HCAPP

#Set PROXY
#export X509_USER_PROXY=$HCAPP/config/x509up
#echo '    _  X509_USER_PROXY='$X509_USER_PROXY

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

#Export apps zones
export PYTHONPATH=$PYTHONPATH:$HCDIR/apps

#export PYTHONPATH=$PYTHONPATH:/usr/lib64/python2.5/site-packages/

#Export HammerCloud settings.
export DJANGO_SETTINGS_MODULE=hc.settings

echo '    _  Looking for app specific config script in '$HCAPP/scripts/config/config-main.sh

if [ -e $HCAPP/scripts/config/config-main.sh ]
then
    echo '    _    found: config-main.sh'
    echo '    _  Sourced '$HCAPP/scripts/config/config-main.sh    
    source $HCAPP/scripts/config/config-main.sh
else
    echo '    _  Not found. Skipping.'

fi

echo '    _'
echo '    _                     End  Main  Configuration                    _'
echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
