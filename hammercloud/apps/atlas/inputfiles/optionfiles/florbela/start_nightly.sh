#!/bin/bash
cd /afs/cern.ch/user/f/fjriegas/public/HC/

if test ! "`echo $PATH | egrep POOL`" ; then
    source pool_setup_nightly.sh
 fi
python /afs/cern.ch/user/f/fjriegas/public/HC/start_eventLookup_CollFileList.py
