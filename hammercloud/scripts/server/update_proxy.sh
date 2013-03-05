#!/bin/bash

# Proxy renewal script.
# NOTE: this script must be run as root and have a precreated proxy by the user
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
HCAPP=$HCDIR/apps/$APP

# Obtain a lock to continue running.
source $HCDIR/scripts/config/locks.sh
if ! exlock_now ; then
    echo " WARNING: the lock $LOCKFILE was taken. Exiting."
    exit
fi

# The proxy x509up cannot have permissions different than 600, so the proxy
# is copied as x509up_new by ubeda, so it cannot be read by gangarbt.
# The proxy is copied at 10, 18 and at 02 hrs. So, five minutes before,
# the script accepts the new proxy.

# Common update procedure.
function update {
    echo "------- x509up$1 -------"
    chown gangarbt:cg $HCAPP/config/x509up$1_new
    mv $HCAPP/config/x509up$1_new $HCAPP/config/x509up$1
    chmod 600 $HCAPP/config/x509up$1
    echo 'Done.'
}

case "$APP" in
    cms)
        # Regular proxies.
        update '_user'
        update '_production'
        # Proxies registered in cmsweb (CRAB 2.8.5+)
        update '_user2'
        update '_production2'
        ;;
    *)
        update
        ;;
esac

# Unlock the lockfile.
unlock
