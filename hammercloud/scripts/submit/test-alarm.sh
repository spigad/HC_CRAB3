#!/bin/sh

echo ''
echo '_ Test Alarm Main.'
echo ''


if [ -z $1 ]
then
    echo '  ERROR! Please, set application tag.'
    echo ''
    echo '_ End Test Alarm Main.'
    echo ''
    exit
fi

# WARNING !
# This script can run in more than one machine
if [ -f /tmp/test-alarm_$1_$HOST.running ]
then
    echo '  ERROR! Script 'test-alarm_$1_$HOST already running.
    echo ''
    echo '_ End Test Alarm Main.'
    echo ''
    exit
fi

touch /tmp/test-alarm_$1_$HOST.running
echo '  Lock written: '/tmp/test-alarm_$1_$HOST.running

#Get HCDIR from current installation.
HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`

echo ''
source $HCDIR/scripts/config/config-main.sh $1 $HCDIR
echo ''

cd $HCDIR

echo '  CODE: python python/scripts/dispatcher.py -f test_alarm'
echo ''
python python/scripts/dispatcher.py -f test_alarm
echo ''
echo '  END CODE'
rm -f /tmp/test-alarm_$1_$HOST.running

echo '  Lock released: '/tmp/test-alarm_$1_$HOST.running
echo ''
echo '_ End Test Alarm Main.'
echo ''
