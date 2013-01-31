#!/bin/sh

echo ''
echo '_ Synch APP.'
echo ''

if [ -z $1 ]
then
    echo '  ERROR! Please, set application tag.'
    echo ''
    echo '_ End Synch APP.'
    echo ''
    exit
fi

if [ -f /tmp/synch-app_$1.running ]
then
    echo '  ERROR! Script 'synch-app_$1 already running.
    echo ''
    echo '_ End Synch APP.'
    echo ''
    exit
fi

touch /tmp/synch-app_$1.running
echo '  Lock written: '/tmp/synch-app_$1.running

#Get HCDIR from current installation.
HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`

echo ''
source $HCDIR/scripts/config/config-main.sh $1 $HCDIR
echo ''

if [ "$1" == "cms" ]
then
    echo 'Synch CMS'
    echo '--------- vocms207 --------'
    rsync -av /data/hc/ --exclude '*.pyc*' --exclude 'web/src/hc/settings.py*' --exclude '*testdirs*' --exclude '*logs*' --exclude '*.jdl' --exclude '*.log' --exclude 'glite_list_match_*' --exclude 'glite_*' vocms207:/data/hc/
    echo '-------- vocms228 -------'
    rsync -av /data/hc/ --exclude '*.pyc*' --exclude 'web/src/hc/settings.py*' --exclude '*testdirs*' --exclude '*logs*' --exclude '*.jdl' --exclude '*.log' --exclude 'glite_list_match_*' --exclude 'glite_*' --exclude 'python/scripts/submit/create_at_job.py*' --exclude 'external/cms/crab/scripts/CMSSW_generic.sh*' --exclude 'scripts/submit/submit-main.sh*'  vocms228:/data/hc/
fi

if [ "$1" == "atlas" ]
then
    echo 'Synch ATLAS'
    echo '-------- voatlas65 -------'
    rsync -av /data/hc/ --exclude '*.pyc*' --exclude 'web/src/hc/settings.py*' --exclude '*testdirs*' --exclude '*logs*' voatlas65:/data/hc/
    echo '-------- voatlas167 -------'
    rsync -av /data/hc/ --exclude '*.pyc*' --exclude 'web/src/hc/settings.py*' --exclude '*testdirs*' --exclude '*logs*' voatlas167:/data/hc/
    echo '-------- voatlas284 -------'
    rsync -av /data/hc/ --exclude '*.pyc*' --exclude 'web/src/hc/settings.py*' --exclude '*testdirs*' --exclude '*logs*' --exclude 'scripts/submit/delete_old_test_dirs.sh*' --exclude 'scripts/config/config-main.sh*' --exclude 'apps/atlas/config/GangaAtlas.ini.50*' --exclude 'python/scripts/submit/create_at_job.py*' voatlas284:/data/hc/
    echo '-------- voatlas285 -------'
    rsync -av /data/hc/ --exclude '*.pyc*' --exclude 'web/src/hc/settings.py*' --exclude '*testdirs*' --exclude '*logs*' --exclude 'scripts/submit/delete_old_test_dirs.sh*' --exclude 'scripts/config/config-main.sh*' --exclude 'apps/atlas/config/GangaAtlas.ini.50*' --exclude 'python/scripts/submit/create_at_job.py*' voatlas285:/data/hc/
fi

rm -f /tmp/synch-app_$1.running

echo '  Lock released: '/tmp/synch-app_$1.running
echo ''
echo '_ End Synch APP.'
echo ''

