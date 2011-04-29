#!/bin/sh

echo ''
echo '_ Test Summary Main.'
echo ''


if [ -z $1 ]
then
    echo '  ERROR! Please, set application tag.'
    echo ''
    echo '_ End Test Summary Main.'
    echo ''
    exit
fi

# WARNING !
# This script can run in more than one machine
if [ -f /tmp/test-summary_$1_$HOST.running ]
then
    echo '  ERROR! Script 'test-summary_$1_$HOST already running.
    echo ''
    echo '_ End Test Summary Main.'
    echo ''
    exit
fi

touch /tmp/test-summary_$1_$HOST.running
echo '  Lock written: '/tmp/test-summary_$1_$HOST.running

#Get HCDIR from current installation.
HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`

echo ''
source $HCDIR/scripts/config/config-main.sh $1 $HCDIR
echo ''

cd $HCDIR

echo '  CODE: python python/scripts/dispatcher.py -f test_summary'
echo ''
python python/scripts/dispatcher.py -f test_summary -o 'pse'
echo ''
echo '  END CODE'
rm -f /tmp/test-summary_$1_$HOST.running

echo '  Lock released: '/tmp/test-summary_$1_$HOST.running
echo ''
echo '_ End Test Summary Main.'
echo ''
