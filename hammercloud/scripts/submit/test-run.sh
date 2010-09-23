#!/bin/sh

#ARGUMETNS: <app><gangabin><testid><...>

echo '_._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
echo '_                                                                 _'
echo '_                             Test  Run                           _'
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

if [ -z $1 ]
then
    echo '_  ERROR! Please, set gangabin.'
    echo '_'
    echo '_                         End Submit Main                         _'
    echo '_._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
    echo '_'
    exit
else
    GANGABIN=$1
    shift
fi

if [ -z $1 ]
then
    echo '_  ERROR! Please, set test ID.'
    echo '_'
    echo '_                         End Submit Main                         _'
    echo '_._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
    echo '_'
    exit
else
    TESTID=$1
    shift
fi


if [ -f /tmp/test-run_$APP.running ]
then
    echo '_  ERROR! Script 'test-run_$APP already running.
    echo '_'
    echo '_                         End Server Main                         _'
    echo '_._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
    echo '_'
    exit
fi

#Get HCDIR from current installation.
HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`

touch /tmp/test-run_$APP.running
echo '_  Lock written: '/tmp/test-run_$APP.running

echo '_'
source $HCDIR/scripts/config/config-main.sh $APP
echo '_'

echo '_'
source $HCDIR/scripts/config/config-submit.sh $APP $GANGABIN $*
echo '_'

cd $HCDIR

echo '_ CODE: 'python/scripts/cron_dispatcher.py -a $APP -f test_generate -t $TESTID -o [$*]
echo '_'

./python/scripts/cron_dispatcher.py -a $APP -f test_generate -t $TESTID -o [$*]

# Handle test job submission (generated==1 and submitted==0)
#   creates testdirs/test_N/gangadir
#   runs separate gangarobot on each test_N directory
./python/scripts/cron_dispatcher.py -a $APP -f test_submit -t $TESTID -o [$*]

# Handle test cleanup (submitted==1 and endtime<=now)
#   creates www/sitetests/test_N
#./scripts/test-report $APP $TESTID $*


#echo '_ CODE: 'python/scripts/cron_dispatcher.py -a $APP -f register_host
#echo '_'
#python python/scripts/cron_dispatcher.py -a $APP -f register_host
#echo '_'
#echo '_ CODE: 'python/scripts/cron_dispatcher.py -a $APP -f create_at_job
#echo '_'
#python python/scripts/cron_dispatcher.py -a $APP -f create_at_job
#echo '_'
#echo '_ END CODE'

rm -f /tmp/test-run_$APP.running

echo '_  Lock released: '/tmp/test-run_$APP.running
echo '_'
echo '_                         End Server Main                         _'
echo '_._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
echo '_'
