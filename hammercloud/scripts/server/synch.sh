#!/bin/bash

# Sync script, propagates the code to other machines.
# ARGUMENTS: <app> (must be set)

# Check the presence of an application on the arguments.
if [ -z $1 ] ; then
    echo ' ERROR: application argument not set.'
    exit
else
    export APP=$1
    shift
fi

# Get HCDIR from current installation.
HCDIR=`which $0 | sed 's/\/scripts/ /g' | awk '{print $1}'`

# Obtain a lock to continue running.
source $HCDIR/scripts/config/locks.sh
if ! exlock_now ; then
    echo " WARNING: the lock $LOCKFILE was taken. Exiting."
    exit
fi

# Set up the core environment.
source $HCDIR/scripts/config/config-main.sh $APP

# Common sync procedure.
function sync {
    echo "------- $1 -------"
    rsync -n -av $HCDIR/ --exclude '*.pyc*' --exclude '*.pyo*' --exclude '*testdirs*' --exclude '*.log' --exclude '*logs*' $2 $1:$HCDIR/
}

# Sync the machines per app.
# TODO(rmedrano): This should come from the hosts table.
case "$APP" in
    atlas)
        echo 'Synchronizing ATLAS...'
        sync voatlas65
        sync voatlas167
        sync voatlas284 "--exclude 'scripts/submit/delete_old_test_dirs.sh*' --exclude 'scripts/config/config-main.sh*' --exclude 'apps/atlas/config/GangaAtlas.ini.50*' --exclude 'python/scripts/submit/create_at_job.py*'"
        sync voatlas285 "--exclude 'scripts/submit/delete_old_test_dirs.sh*' --exclude 'scripts/config/config-main.sh*' --exclude 'apps/atlas/config/GangaAtlas.ini.50*' --exclude 'python/scripts/submit/create_at_job.py*'"
        ;;
    cms)
        echo 'Synchronizing CMS...'
        sync vocms207 "--exclude '*.jdl' --exclude 'glite_list_match_*' --exclude 'glite_*'"
        sync vocms228 "--exclude '*.jdl' --exclude 'glite_list_match_*' --exclude 'glite_*'"
        ;;
    lhcb)
        echo 'Synchronizing CMS...'
        # Currently, just one host.
        ;;
    *)
        echo ' ERROR: invalid application code.';;
esac

# Unlock the lockfile.
unlock
