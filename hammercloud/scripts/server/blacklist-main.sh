#!/bin/sh

echo ''
echo '_ Blacklist Main.'
echo ''


if [ -z $1 ]
then
    echo '  ERROR! Please, set application tag.'
    echo ''
    echo '_ End Blacklist Main.'
    echo ''
    exit
fi

if [ -f /tmp/blacklist-main_$1.running ]
then
    echo '  ERROR! Script 'blacklist-main_$1 already running.
    echo ''
    echo '_ End Blacklist Main.'
    echo ''
    exit
fi

touch /tmp/blacklist-main_$1.running
echo '  Lock written: '/tmp/blacklist-main_$1.running

#Get HCDIR from current installation.
HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`

echo ''
source $HCDIR/scripts/config/config-main.sh $1 $HCDIR
echo ''

cd $HCDIR

echo '  CODE: python python/scripts/dispatcher.py -f blacklist'
echo ''
python python/scripts/dispatcher.py -f blacklist
echo ''

rm -f /tmp/blacklist-main_$1.running

echo '  Lock released: '/tmp/blacklist-main_$1.running
echo ''
echo '_ End Blacklist Main.'
echo ''
