#!/bin/sh

echo ''
echo '_ Add site to FT.'
echo ''


if [ -z $1 ]
then
    echo '  ERROR! Please, at least one site name and the app tag.'
    echo ''
    echo '_ End Add site to FT'
    echo ''
    exit
fi

if [ -f /tmp/add-site-to-ft_$1.running ]
then
    echo '  ERROR! Script add-site-to-ft_'$1 already running.
    echo ''
    echo '_ End Add site to FT.'
    echo ''
    exit
fi

touch /tmp/add-site-to-ft_$1.running
echo '  Lock written: '/tmp/add-site-to-ft_$1.running

#Get HCDIR from current installation.
HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`

echo ''
source $HCDIR/scripts/config/config-main.sh $1 $HCDIR
echo ''

cd $HCDIR

echo '  CODE: python python/scripts/dispatcher.py -f add_site_to_ft' $*
echo ''
python python/scripts/dispatcher.py -f add_site_to_ft $*
echo ''

rm -f /tmp/add-site-to-ft_$1.running

echo '  Lock released: '/tmp/add-site-to-ft_$1.running
echo ''
echo '_ End Add site to FT.'
echo ''
