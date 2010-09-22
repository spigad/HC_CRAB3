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
else
    APP=$1
    shift
fi

if [ -f /tmp/submit-main_$APP.running ]
then
    echo '_  ERROR! Script 'submit-main_$1 already running.
    echo '_'
    echo '_                         End Server Main                         _'
    echo '_._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
    echo '_'
    exit
fi

#Get HCDIR from current installation.
HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`

touch /tmp/submit-main_$APP.running
echo '_  Lock written: '/tmp/submit-main_$APP.running

echo '_'
source $HCDIR/scripts/config/config-main.sh $APP
echo '_'

cd $HCDIR

echo '_ CODE: 'python/scripts/cron_dispatcher.py -a $APP -f register_host
echo '_'
./python/scripts/cron_dispatcher.py -a $APP -f register_host
echo '_'
echo '_ CODE: 'python/scripts/cron_dispatcher.py -a $APP -f create_at_job
echo '_'
./python/scripts/cron_dispatcher.py -a $APP -f create_at_job
echo '_'
echo '_ END CODE'
rm -f /tmp/submit-main_$APP.running

echo '_  Lock released: '/tmp/submit-main_$APP.running
echo '_'
echo '_                         End Server Main                         _'
echo '_._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
echo '_'
