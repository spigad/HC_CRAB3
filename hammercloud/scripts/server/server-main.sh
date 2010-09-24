#!/bin/sh

echo ''
echo '_ Server Main.'
echo ''


if [ -z $1 ]
then
    echo '  ERROR! Please, set application tag.'
    echo ''
    echo '_ End Server Main.'
    echo ''
    exit
fi

if [ -f /tmp/server-main_$2.running ]
then
    echo '  ERROR! Script 'server-main_$2 already running.
    echo ''
    echo '_ End Server Main.'
    echo ''
    exit
fi

touch /tmp/server-main_$1.running
echo '  Lock written: '/tmp/server-main_$1.running

#Get HCDIR from current installation.
HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`

echo ''
source $HCDIR/scripts/config/config-main.sh $1 $HCDIR
echo ''

cd $HCDIR

echo '  CODE: ./python/scripts/dispatcher.py -f create_functional_tests'
echo ''
./python/scripts/dispatcher.py -f create_functional_tests
echo ''
echo '  END CODE'
rm -f /tmp/server-main_$1.running

echo '  Lock released: '/tmp/server-main_$1.running
echo ''
echo '_ End Server Main.'
echo ''
