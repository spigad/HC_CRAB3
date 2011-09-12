#!/bin/sh

echo ''
echo '_ Synch APP.'
echo ''

if [ -z $1 ]
then
    echo '  ERROR! Please, set application tag.'
    echo ''
    echo '_ End Synch APP.'
    echo ''
    exit
fi

if [ -f /tmp/synch-app_$1.running ]
then
    echo '  ERROR! Script 'synch-app_$1 already running.
    echo ''
    echo '_ End Synch APP.'
    echo ''
    exit
fi

touch /tmp/synch-app_$1.running
echo '  Lock written: '/tmp/synch-app_$1.running

#Get HCDIR from current installation.
HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`

echo ''
source $HCDIR/scripts/config/config-main.sh $1 $HCDIR
echo ''

if [ "$1" == "cms" ]
then
    echo 'Synch CMS'
    echo '--------- vocms06 --------'
    rsync -av /data/hc/ --exclude '*testdirs*' --exclude '*logs*' vocms06:/data/hc/
fi

if [ "$1" == "atlas" ]
then
    echo 'Synch ATLAS'
    echo '-------- voatlas65 -------'
    rsync -av /data/hc/ --exclude '*testdirs*' --exclude '*logs*' voatlas65:/data/hc/
fi

rm -f /tmp/synch-app_$1.running

echo '  Lock released: '/tmp/synch-app_$1.running
echo ''
echo '_ End Synch APP.'
echo ''

