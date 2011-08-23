#!/bin/sh

echo ''
echo '_ SLS updater.'
echo ''

if [ -f /tmp/sls-update.running ]
then
    echo '  ERROR! Script 'sls-update already running.
    echo ''
    echo '_ End SLS updater.'
    echo ''
    exit
fi

touch /tmp/sls-update.running
echo '  Lock written: '/tmp/sls-update.running

#Get HCDIR from current installation.
HCDIR=/data/hc
echo ''
#source $HCDIR/scripts/config/config-main.sh $1 $HCDIR
echo ''

#Export python to environment
export PATH=/afs/cern.ch/sw/lcg/external/Python/2.5.4p2/x86_64-slc5-gcc43-opt/bin/:$PATH

#Export MySQLdb packages for python2.5
export PYTHONPATH=/afs/cern.ch/sw/lcg/external/mysql_python/1.2.2-mysql5.0.18-python2.5/x86_64-slc5-gcc43-opt/lib/python2.5/site-packages/:$PYTHONPATH

#Export custom site-packages
export PATH=$PATH:$HCDIR/external/bin/
export PYTHONPATH=$PYTHONPATH:$HCDIR/external/lib/python2.5/site-packages:$HCDIR/external/lib64/python2.5/site-packages

#Export hammercloud python zone.
export PYTHONPATH=$PYTHONPATH:$HCDIR/python

vals=`ls -F $HCDIR/external/django/ | grep 'Django' | sort -r`
version=`echo $vals|cut -d'/' -f1`
#Export Django & HammerCloud.
export PYTHONPATH=$PYTHONPATH:$HCDIR/external/django/$version:$HCDIR/web/src

#Export apps zones
export PYTHONPATH=$PYTHONPATH:$HCDIR/apps

echo '  PATH='$PATH
echo '  PYTHONPATH='$PYTHONPATH

#Export HammerCloud settings.
export DJANGO_SETTINGS_MODULE=hc.settings
echo '  DJANGO_SETTINGS_MODULE=hc.settings'

source /afs/cern.ch/atlas/offline/external/GRID/DA/panda-client/latest/etc/panda/panda_setup.sh

cd $HCDIR/sls

echo '  CODE: ./hc-sls-update $*'
echo ''
./hc-sls-update $*
echo ''

rm -f /tmp/sls-update.running

echo '  Lock released: '/tmp/sls-update.running
echo ''
echo '_ End SLS updater.'
echo ''
