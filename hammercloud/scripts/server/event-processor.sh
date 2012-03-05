#!/bin/sh

echo ''
echo '_ Event Queue Processor.'
echo ''


if [ -z $1 ]
then
    echo '  ERROR! Please, set application tag.'
    echo ''
    echo '_ End Event Queue Processor.'
    echo ''
    exit
fi

if [ -f /tmp/event-processor_$1.running ]
then
    echo '  ERROR! Script 'event-processor_$1 already running.
    echo ''
    echo '_ End Event Queue Processor.'
    echo ''
    exit
fi

touch /tmp/event-processor_$1.running
echo '  Lock written: '/tmp/event-processor_$1.running

#Get HCDIR from current installation.
HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`

echo ''
source $HCDIR/scripts/config/config-main.sh $1 $HCDIR
echo ''

cd $HCDIR

echo '  CODE: python python/scripts/dispatcher.py -f event_processor'
echo ''
python python/scripts/dispatcher.py -f event_processor
echo ''

rm -f /tmp/event-processor_$1.running

echo '  Lock released: '/tmp/event-processor_$1.running
echo ''
echo '_ End Event Queue Processor.'
echo ''
