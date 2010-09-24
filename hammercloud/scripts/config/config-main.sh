#!/bin/sh

#ARGUMENTS: <app>

echo '_  Main  Configuration'
echo ''

if [ -z $1 ]
then
    echo '  ERROR! Please, set application tag.'
    echo ''
    echo '_  End  Main  Configuration'
    echo ''
    exit
fi

#Get HCDIR from current installation.
HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`

#Set HCDIR and HCAPP. Used in the other scripts.
export HCDIR=$HCDIR
export HCAPP=$HCDIR/apps/$1
echo '  HCDIR='$HCDIR
echo '  HCAPP='$HCAPP

export APP=$1
echo '  APP='$APP

echo '  Looking for newest Django intalled version in '$HCDIR/external/django/

#Get the newest installed version of Django in $HCDIR/external/django/
vals=`ls -F $HCDIR/external/django/ | grep 'Django' | sort -r`
if [ -z "$vals" ]
then
  echo '   ERROR! No Django instance found.'
  echo ''
  echo '_ End  Main  Configuration'
  echo ''
  exit
fi

echo '   found: '$vals

version=`echo $vals|cut -d' ' -f1`
echo '  Using '$version

#Export hammercloud python zone.
export PYTHONPATH=$HCDIR/python

#Export Django & HammerCloud.
export PYTHONPATH=$PYTHONPATH:$HCDIR/external/$version:$HCDIR/web/src/

#Export apps zones
export PYTHONPATH=$PYTHONPATH:$HCDIR/apps

#export PYTHONPATH=$PYTHONPATH:/usr/lib64/python2.5/site-packages/

#Export HammerCloud settings.
export DJANGO_SETTINGS_MODULE=hc.settings

echo '  Looking for app specific config script in '$HCAPP/scripts/config/config-main.sh

if [ -e $HCAPP/scripts/config/config-main.sh ]
then
    echo '   found: config-main.sh'
    echo '  Sourced '$HCAPP/scripts/config/config-main.sh    
    source $HCAPP/scripts/config/config-main.sh
else
    echo '   not found. Skipping.'

fi

echo ''
echo '_ End  Main  Configuration.'
echo ''
