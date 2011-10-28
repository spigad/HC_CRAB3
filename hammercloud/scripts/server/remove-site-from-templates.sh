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

if [ -f /tmp/remove-site-from-templates_$1.running ]
then
    echo '  ERROR! Script remove-site-from-templates_'$1 already running.
    echo ''
    echo '_ End Add site to FT.'
    echo ''
    exit
fi

touch /tmp/remove-site-from-templates_$1.running
echo '  Lock written: '/tmp/remove-site-from-templates_$1.running

#Get HCDIR from current installation.
HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`

echo ''
source $HCDIR/scripts/config/config-main.sh $1 $HCDIR
echo ''

cd $HCDIR

echo '  CODE: python python/scripts/dispatcher.py -f remove_site_from_templates'
echo ''
python python/scripts/dispatcher.py -f remove_site_from_templates
echo ''

rm -f /tmp/remove-site-from-templates_$1.running

echo '  Lock released: '/tmp/remove-site-from-templates_$1.running
echo ''
echo '_ End Add site to FT.'
echo ''
