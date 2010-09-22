#!/bin/bash

if [ -z $1 ]
then
  echo 'set Frequency'
  exit
fi

if ! echo $1 | grep "^[0-9]*$" >> /dev/null
then
  echo 'Dont be ugly. Insert integers.'
  exit
fi

if [ -z $2 ]
then
  echo 'Please, set HCDIR'
  exit
fi

HCDIR=$2

#Get the newest installed version of Django in $HCDIR/external

vals=`ls -F $HCDIR/external/ | grep 'Django' | sort -r`
if [ -z "$vals" ]
then
  echo No Django instance in $HCDIR/external/
  exit
fi

version=`echo $vals|cut -d' ' -f1`

export PYTHONPATH=$PYTHONPATH:$HCDIR/external/$version:$HCDIR/htdocs/src/
export DJANGO_SETTINGS_MODULE=hc.settings

python2.5 $HCDIR/htdocs/src/hc/core/crontab/scheduler.py $1
