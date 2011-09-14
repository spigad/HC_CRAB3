#!/bin/sh

echo ''
echo '_ External Queue Update.'
echo ''


if [ -z $1 ]
then
    echo '  ERROR! Please, set application tag.'
    echo ''
    echo '_ End External Queue Update.'
    echo ''
    exit
fi

if [ -f /tmp/external-queue-update_$1.running ]
then
    echo '  ERROR! Script 'external-queue-update_$1 already running.
    echo ''
    echo '_ End External Queue Update.'
    echo ''
    exit
fi

touch /tmp/external-queue-update_$1.running
echo '  Lock written: '/tmp/external-queue-update_$1.running

#Get HCDIR from current installation.
HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`

echo ''
source $HCDIR/scripts/config/config-main.sh $1 $HCDIR
echo ''

cd $HCDIR

echo '  CODE: python python/scripts/dispatcher.py -f external_queue_update'
echo ''
python python/scripts/dispatcher.py -f external_queue_update
echo ''

rm -f /tmp/external-queue-update_$1.running

echo '  Lock released: '/tmp/external-queue-update_$1.running
echo ''
echo '_ End External Queue Update.'
echo ''
