#!/bin/sh

#ARGUMENTS: <app>

echo '_  HC Django Shell'
echo ''

#Get HCDIR from current installation.
HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`

source $HCDIR/scripts/config/config-main.sh demo

cd $HCDIR/web/src/hc

python2.5 manage.py shell

echo ''
echo '_ End  HC  Django Shell.'
echo ''

