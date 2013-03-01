#!/bin/sh

echo ''
echo '_ Update proxy.'
echo ''


if [ -z $1 ]
then
    echo '  ERROR! Please, set application tag.'
    echo ''
    echo '_ End Server Main.'
    echo ''
    exit
fi

if [ -f /tmp/update-proxy_$1.running ]
then
    echo '  ERROR! Script 'update-proxy_$1 already running.
    echo ''
    echo '_ End Server Main.'
    echo ''
    exit
fi

touch /tmp/update-proxy_$1.running
echo '  Lock written: '/tmp/update-proxy_$1.running

#Get HCDIR from current installation.
HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`

echo ''
source $HCDIR/scripts/config/config-main.sh $1 $HCDIR
echo ''


#The proxy x509up cannot have permissions different than 600, so the 
#proxy
#is copied as x509up_new by ubeda, so it cannot be read by gangarbt.
#This script copies it into something readable.

#The proxy is copied at 10,18 and at 02 hrs. So, five minutes before,
#the script accepts the new proxy.

if [ "$1" != cms ]
then
  chown gangarbt:cg $HCDIR/apps/$1/config/x509up_new
  mv $HCDIR/apps/$1/config/x509up_new $HCDIR/apps/$1/config/x509up
fi

if [ "$1" = cms ]
then
  #USER
  chown gangarbt:cg $HCDIR/apps/$1/config/x509up_user_new
  mv $HCDIR/apps/$1/config/x509up_user_new $HCDIR/apps/$1/config/x509up_user
  chmod 600 $HCDIR/apps/$1/config/x509up_user
  #PRODUCTION
  chown gangarbt:cg $HCDIR/apps/$1/config/x509up_production_new
  mv $HCDIR/apps/$1/config/x509up_production_new $HCDIR/apps/$1/config/x509up_production
  chmod 600 $HCDIR/apps/$1/config/x509up_production
  chown gangarbt:cg $HCDIR/apps/$1/config/x509up_production2_new
  mv $HCDIR/apps/$1/config/x509up_production2_new $HCDIR/apps/$1/config/x509up_production2
  chmod 600 $HCDIR/apps/$1/config/x509up_production2
  chown gangarbt:cg $HCDIR/apps/$1/config/x509up_user2_new
  mv $HCDIR/apps/$1/config/x509up_user2_new $HCDIR/apps/$1/config/x509up_user2
  chmod 600 $HCDIR/apps/$1/config/x509up_user2
fi

rm -f /tmp/update-proxy_$1.running

echo '  Lock released: '/tmp/update-proxy_$1.running
echo ''
echo '_ End Server Main.'
echo ''
