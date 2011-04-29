#!/bin/bash

cd /afs/cern.ch/user/f/fjriegas/public/HC/
if test ! "`echo $PATH | egrep POOL`" ; then
    source pool_setup.sh
fi
python start_eventLookup_CollFileList.py
