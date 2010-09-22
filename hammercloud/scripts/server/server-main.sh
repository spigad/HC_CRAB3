#!/bin/sh

echo '_._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
echo '_                                                                 _'
echo '_                           Server Main                           _'
echo '_._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
echo '_'
echo '_'


if [ -z $1 ]
then
    echo '_  ERROR! Please, set application tag.'
    echo '_'
    echo '_                         End Server Main                         _'
    echo '_._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
    echo '_'
    exit
fi

if [ -f /tmp/server-main_$2.running ]
then
    echo '_  ERROR! Script 'server-main_$2 already running.
    echo '_'
    echo '_                         End Server Main                         _'
    echo '_._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
    echo '_'
    exit
fi

touch /tmp/server-main_$1.running
echo '_  Lock written: '/tmp/server-main_$1.running

#Get HCDIR from current installation.
HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`

echo '_'
source $HCDIR/scripts/config/config-main.sh $1 $HCDIR
echo '_'

cd $HCDIR

echo '_ CODE: python' python/scripts/cron_dispatcher.py -a $1 -f create_functional_tests
echo '_'
python2.5 python/scripts/cron_dispatcher.py -a $1 -f create_functional_tests
echo '_'
echo '_ END CODE'
rm -f /tmp/server-main_$1.running

echo '_  Lock released: '/tmp/server-main_$1.running
echo '_'
echo '_                         End Server Main                         _'
echo '_._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
echo '_'
