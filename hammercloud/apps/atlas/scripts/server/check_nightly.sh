#!/bin/sh

echo ''
echo '_ Check Nightly.'
echo ''


if [ -z $1 ]
then
    echo '  ERROR! Please, set application tag.'
    echo ''
    echo '_ End Check Nightly.'
    echo ''
    exit
fi

if [ -f /tmp/check_nightly_$1.running ]
then
    echo '  ERROR! Script 'check_nightly_$1 already running.
    echo ''
    echo '_ End Check Nightly.'
    echo ''
    exit
fi

touch /tmp/check_nightly_$1.running
echo '  Lock written: '/tmp/check_nightly_$1.running

#Get HCDIR from current installation.
#HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`
HCDIR='/data/hc'

echo ''
source /data/hc/apps/atlas/inputfiles/templates/nightlies_files/config-main-je-SLC6.sh $1
#source $HCDIR/scripts/config/config-main.sh $1
echo ''

#cd $HCDIR

echo '  CODE: python check_nightly.py'
echo ''
python /data/hc/apps/atlas/inputfiles/templates/nightlies_files/check_nightly.py
echo ''
echo '  END CODE'
rm -f /tmp/check_nightly_$1.running

echo '  Lock released: '/tmp/check_nightly_$1.running
echo ''
echo '_ End Robot Main.'
echo ''
