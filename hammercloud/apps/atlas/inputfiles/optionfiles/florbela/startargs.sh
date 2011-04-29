#!/bin/bash

echo Running startargs:
echo arg 1 $1
echo arg 2 $2

cd /afs/cern.ch/user/f/fjriegas/public/HC/

if test ! "`echo $PATH | egrep POOL`" ; then
    source pool_setup.sh
 fi
python /afs/cern.ch/user/f/fjriegas/public/HC/start_eventLookup_CollFileList_args.py $1 $2

