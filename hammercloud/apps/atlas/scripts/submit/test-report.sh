#!/bin/sh

# Script for the test submission.
#ARGUMETNS: <testid><...>

if [ -z $1 ]
then
    echo 'ERROR: not test ID provided.'
    exit
fi

# Start GangaRobot
# TODO(rmedrano): remove the AFS Ganga dependency here.
if [ -e /afs/cern.ch/sw/ganga/install/etc/setup-atlas.sh ]
then
    source /afs/cern.ch/sw/ganga/install/etc/setup-atlas.sh latest
fi

export GANGA_CONFIG_PATH=$GANGA_CONFIG_PATH:GangaAtlas/Atlas.ini:$HCAPP/config/GangaAtlas.ini.50

# Start Ganga.
$GANGABIN --config=$HCAPP/config/$APP-ROBOT.INI.50 -o[Logging]_format='VERBOSE' -o[Configuration]gangadir=$HCAPP/testdirs/test_$1/gangadir -o[Logging]_logfile=$HCAPP/testdirs/test_$1/ganga.log -o[Panda]processingType=hammercloud -o[LCG]JobLogHandler=DQ2 -o[MonitoringServices]Athena/LCG=Ganga.Lib.MonitoringServices.Dashboard.LCGAthenaMS.LCGAthenaMS -o[DQ2]OUTPUTDATASET_LIFETIME='2_days' $2 $HCAPP/python/scripts/runtest_$HC_MODE.py $1
