#!/bin/bash

echo ''
echo '_ Set ANALY queues online.'
echo ''

if [ -z $1 ]
then
    echo '  ERROR! Please, provide a text file with list of sites to set online.'
    echo ''
    echo '_ End ANALY queues online.'
    echo ''
    exit
fi

if [ -f /tmp/setonline_$1.running ]
then
    echo '  ERROR! Script add-site-to-ft_'$1 already running.
    echo ''
    echo '_ End Add site to FT.'
    echo ''
    exit
fi

touch /tmp/setonline_$1.running
echo '  Lock written: '/tmp/setonline_$1.running

#Get HCDIR from current installation.
HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`

echo ''
source $HCDIR/scripts/config/config-main.sh atlas $HCDIR
echo ''

echo $X509_USER_PROXY

cat $1 | while read sites
do
    for site in $sites
    do
	if [[ $site != \#* ]]; then
	    curl -s -k --cert $X509_USER_PROXY 'https://panda.cern.ch:25943/server/controller/query?tpmes=setmanual&queue='${site}'&comment=HC.Blacklist.set.manual'
	    curl -s -k --cert $X509_USER_PROXY 'https://panda.cern.ch:25943/server/controller/query?tpmes=setonline&queue='${site}'&comment=HC.Blacklist.set.online'
	fi
    done
done

rm -f /tmp/setonline_$1.running

echo '  Lock released: '/tmp/setonline_$1.running
echo ''
echo '_ End Set ANALY queues online.'
echo ''
