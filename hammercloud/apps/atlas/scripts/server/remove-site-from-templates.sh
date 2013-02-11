#!/bin/sh

# Script to remove a set of sites from the functional tests templates.

if [ -z $1 ]
then
    echo 'ERROR: no site name provided.'
    exit
fi

if [ -f /tmp/remove-site-from-templates_atlas.running ]
then
    echo 'ERROR: script already running.'
    exit
fi

touch /tmp/remove-site-from-templates_atlas.running

#Get HCDIR from current installation.
#HCDIR=`which $0|sed 's/\/apps/ /g'|awk '{print $1}'`
export HCDIR=/data/hc

source $HCDIR/scripts/config/config-main.sh atlas $HCDIR

cd $HCDIR

python apps/atlas/python/scripts/server/remove_site_from_templates.py $*

rm -f /tmp/remove-site-from-templates_atlas.running
