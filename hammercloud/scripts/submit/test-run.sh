#!/bin/sh

#ARGUMETNS: <app><gangabin><testid><...>

echo '_ Test  Run.'
echo ''

if [ -z $1 ]
then
    echo '  ERROR! Please, set application tag.'
    echo ''
    echo '_ End Test Run'
    echo ''
    exit
else
    APP=$1
    shift
fi

if [ -z $1 ]
then
    echo '  ERROR! Please, set gangabin.'
    echo ''
    echo '_ End Test Run.'
    echo ''
    exit
else
    GANGABIN=$1
    shift
fi

if [ -z $1 ]
then
    echo '  ERROR! Please, set test ID.'
    echo ''
    echo '_ End Test Run.'
    echo ''
    exit
else
    TESTID=$1
    shift
fi

if [ -f /tmp/test-run_$APP_$TESTID.running ]
then
    echo '  ERROR! Script 'test-run_$APP_$TESTID already running.
    echo ''
    echo '_ End Test Run Main.'
    echo ''
    exit
fi

#Get HCDIR from current installation.
HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`

touch /tmp/test-run-$APP_$TESTID.running
echo '  Lock written: /tmp/test-run-'$APP_$TESTID.running

echo ''
source $HCDIR/scripts/config/config-main.sh $APP
echo ''

echo ''
source $HCDIR/scripts/config/config-submit.sh $GANGABIN $*
echo ''

cd $HCDIR

##GENERATE
echo '  CODE: 'python python/scripts/dispatcher.py -f test_generate -t $TESTID -m $HC_MODE
echo ''
python python/scripts/dispatcher.py -f test_generate -t $TESTID -m $HC_MODE

##SUBMIT
echo '  CODE: 'python python/scripts/dispatcher.py -f test_submit -t $TESTID -m $HC_MODE
echo ''
python python/scripts/dispatcher.py -f test_submit -t $TESTID -m $HC_MODE

##REPORT
echo '  CODE: 'python python/scripts/dispatcher.py -f test_report -t $TESTID -m $HC_MODE
echo ''
python python/scripts/dispatcher.py -f test_report -t $TESTID -m $HC_MODE

##POST_MORTEM STATISTICS
#echo '  CODE: 'python python/scripts/dispatcher.py -f test_summary -o 'psef' -t $TESTID
#echo ''
#python python/scripts/dispatcher.py -f test_summary -o 'psef' -t $TESTID

rm -f /tmp/test-run-$APP_$TESTID.running

echo '  Lock released: /tmp/test-run-'$APP_$TESTID.running
echo ''
echo '_ End Test Run Main.'
echo ''
