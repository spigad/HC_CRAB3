#!/bin/bash

echo ''
echo '_ Query DQ2 datasets.'
echo ''

if [ -f /tmp/datasetRead.running ]
then
    echo '  ERROR! Script dataset already running.'
    echo ''
    echo '_ End Query DQ2 datasets.'
    echo ''
    exit
fi

touch /tmp/datasetRead.running
echo '  Lock written: '/tmp/datasetRead.running

#Get HCDIR from current installation.
#HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`
HCDIR=/data/hc
SCRIPTDIR=/data/hc/apps/atlas/python/scripts/submit

echo ''
source $SCRIPTDIR/config-main-je.sh atlas $HCDIR
echo ''

python $SCRIPTDIR/datasetRead.py $SCRIPTDIR/datasetCache.pickle 'mc11_7TeV*merge*AOD*r27*'

rm -f /tmp/datasetRead.running

echo '  Lock released: '/tmp/datasetRead.running
echo ''
echo '_ End Query DQ2 datasets.'
echo ''
