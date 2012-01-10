#!/bin/sh

echo ''
echo '_ Remove sites frm templates'
echo ''


if [ -z $1 ]
then
    echo '  ERROR! Please, at least one site name.'
    echo ''
    echo '_ Remove sites frm templates'
    echo ''
    exit
fi

if [ -f /tmp/remove-site-from-templates_atlas.running ]
then
    echo '  ERROR! Script remove-site-from-templates_atlas already running.'
    echo ''
    echo '_ End Remove sites frm templates'
    echo ''
    exit
fi

touch /tmp/remove-site-from-templates_atlas.running
echo '  Lock written: '/tmp/remove-site-from-templates_atlas.running

#Get HCDIR from current installation.
#HCDIR=`which $0|sed 's/\/apps/ /g'|awk '{print $1}'`
export HCDIR=/data/hc
echo ''
source $HCDIR/scripts/config/config-main.sh atlas $HCDIR
echo ''

cd $HCDIR

echo '  CODE: python apps/atlas/python/scripts/server/remove_site_from_templates.py' $*
echo ''
python apps/atlas/python/scripts/server/remove_site_from_templates.py $*
echo ''

rm -f /tmp/remove-site-from-templates_atlas.running

echo '  Lock released: '/tmp/remove-site-from-templates_atlas.running
echo ''
echo '_ End Remove sites frm templates'
echo ''
