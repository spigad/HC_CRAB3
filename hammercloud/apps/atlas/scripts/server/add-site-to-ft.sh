#!/bin/sh

echo ''
echo '_ Add site to FT.'
echo ''


if [ -z $1 ]
then
    echo '  ERROR! Please, at least one site name.'
    echo ''
    echo '_ End Add site to FT'
    echo ''
    exit
fi

if [ -f /tmp/add-site-to-ft_atlas.running ]
then
    echo '  ERROR! Script add-site-to-ft_atlas already running.'
    echo ''
    echo '_ End Add site to FT.'
    echo ''
    exit
fi

touch /tmp/add-site-to-ft_atlas.running
echo '  Lock written: '/tmp/add-site-to-ft_atlas.running

#Get HCDIR from current installation.
HCDIR=`which $0|sed 's/\/apps/ /g'|awk '{print $1}'`

echo ''
source $HCDIR/scripts/config/config-main.sh atlas $HCDIR
echo ''

cd $HCDIR

echo '  CODE: python apps/atlas/python/scripts/server/add_site_to_ft.py' $*
echo ''
python apps/atlas/python/scripts/server/add_site_to_ft.py $*
echo ''

rm -f /tmp/add-site-to-ft_atlas.running

echo '  Lock released: '/tmp/add-site-to-ft_atlas.running
echo ''
echo '_ End Add site to FT.'
echo ''
