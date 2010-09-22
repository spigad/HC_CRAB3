#!/bin/sh

echo '_._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
echo '_                                                                 _'
echo '_                           Submit Main                           _'
echo '_._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
echo '_'
echo '_'


if [ -z $1 ]
then
    echo '_  ERROR! Please, set application tag.'
    echo '_'
    echo '_                         End Submit Main                         _'
    echo '_._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
    echo '_'
    exit
fi

if [ -z $2 ]
then
    echo '_  No HCDIR provided. Using HCDIR=/data/hammercloud'
    HCDIR=/data/hammercloud
else
    HCDIR=$2
fi


if [ -f /tmp/submit-main_$2.running ]
then
    echo '_  ERROR! Script 'submit-main_$2.running already running.
    echo '_'
    echo '_                         End Server Main                         _'
    echo '_._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
    echo '_'
    exit
fi

touch /tmp/submit-main_$1.running
echo '_  Lock written: '/tmp/submit-main_$1.running

echo '_'
source $HCDIR/scripts/config/config-main.sh $1 $HCDIR
echo '_'

cd $HCDIR

echo '_ CODE: 'python/scripts/cron_dispatcher.py -a $1 -f register_host
echo '_'
python python/scripts/cron_dispatcher.py -a $1 -f register_host
echo '_'
echo '_ CODE: 'python/scripts/cron_dispatcher.py -a $1 -f create_at_job
echo '_'
python python/scripts/cron_dispatcher.py -a $1 -f create_at_job
echo '_'
echo '_ END CODE'
rm -f /tmp/submit-main_$1.running

echo '_  Lock released: '/tmp/submit-main_$1.running
echo '_'
echo '_                         End Server Main                         _'
echo '_._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
echo '_'
