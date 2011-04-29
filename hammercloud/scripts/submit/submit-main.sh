#!/bin/sh
	
echo ''
echo '_ Submit Main.'
echo ''

if [ -z $1 ]
then
    echo '  ERROR! Please, set application tag.'
    echo ''
    echo '_ End Submit Main.'
    echo ''
    exit
else
    APP=$1
    shift
fi

if [ -f /tmp/submit-main_$APP.running ]
then
    echo '  ERROR! Script 'submit-main_$1 already running.
    echo ''
    echo '_ End Server Main.'
    echo ''
    exit
fi

#Get HCDIR from current installation.
HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`

touch /tmp/submit-main_$APP.running
echo '  Lock written: '/tmp/submit-main_$APP.running

echo ''
source $HCDIR/scripts/config/config-main.sh $APP
echo ''

cd $HCDIR

echo ' CODE: python python/scripts/dispatcher.py -f register_host'
echo ''
python python/scripts/dispatcher.py -f register_host

echo ' CODE: python python/scripts/dispatcher.py -f create_at_job'
echo ''
python python/scripts/dispatcher.py -f create_at_job
echo ''

rm -f /tmp/submit-main_$APP.running

echo '  Lock released: '/tmp/submit-main_$APP.running
echo ''
echo '_ End Server Main'
echo ''
