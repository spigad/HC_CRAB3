#!/bin/bash

echo ''
echo '_ Query DQ2 datasets.'
echo ''

if [ -f /tmp/datasetLookup.running ]
then
    echo '  ERROR! Script dataset already running.'
    echo ''
    echo '_ End Query DQ2 datasets.'
    echo ''
    exit
fi

touch /tmp/datasetLookup.running
echo '  Lock written: '/tmp/datasetLookup.running

#Get HCDIR from current installation.
#HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`
HCDIR=/data/hc
SCRIPTDIR=/data/hc/apps/atlas/python/scripts/submit

echo ''
source $SCRIPTDIR/config-main-je.sh atlas $HCDIR
echo ''

python $SCRIPTDIR/datasetLookup.py $SCRIPTDIR/datasetCache.pickle

rm -f /tmp/datasetLookup.running

echo '  Lock released: '/tmp/datasetLookup.running
echo ''
echo '_ End Query DQ2 datasets.'
echo ''
