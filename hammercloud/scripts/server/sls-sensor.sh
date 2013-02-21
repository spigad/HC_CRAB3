#!/bin/sh

echo ''
echo '_ Server Main.'
echo ''

if [ -f /tmp/sls-sensor.running ]
then
    echo '  ERROR! Script 'sls-sensor already running.
    echo ''
    echo '_ End Server Main.'
    echo ''
    exit
fi

touch /tmp/sls-sensor.running
echo '  Lock written: '/tmp/sls-sensor.running

#Get HCDIR from current installation.
HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`

echo ''
source $HCDIR/scripts/config/config-main.sh core $HCDIR
echo ''

cd $HCDIR

export APP='core'

echo '  CODE: python python/scripts/dispatcher.py -f sls_sensor'
echo ''
python python/scripts/dispatcher.py -f sls_sensor
echo ''

rm -f /tmp/sls-sensor.running

echo '  Lock released: '/tmp/sls-sensor.running
echo ''
echo '_ End Server Main.'
echo ''
