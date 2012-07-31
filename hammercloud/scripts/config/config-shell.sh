#!/bin/sh

#ARGUMENTS: <app>

echo '_  HC Django Shell'
echo ''

if [ -z $1 ]
then
    echo '  ERROR! Please, set application tag.'
    echo '  Use default = demo'
    echo ''
    export HC_SHELL_APP=demo
else
    export HC_SHELL_APP=$1
fi

#Get HCDIR from current installation.
HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`

source $HCDIR/scripts/config/config-main.sh $HC_SHELL_APP

cd $HCDIR/web/src/hc

python manage.py debugsqlshell

echo ''
echo '_ End  HC  Django Shell.'
echo ''

