#!/bin/sh

#'Clear' environment to avoid problems with PATH&PYTHONPATH
unset PYTHONPATH
export PATH=/afs/cern.ch/user/g/gangarbt/bin:/usr/sue/bin:/usr/kerberos/bin:/usr/local/bin:/bin:/usr/bin

export SCRAM_ARCH=slc5_ia32_gcc434

CMSSW_VERSION=$1
CMSSWHOME=/data/hc/external/cms/crab
echo $1 | grep CMSSW_4
if [ $? -eq 0 ] ; then
  export SCRAM_ARCH=slc5_amd64_gcc434
fi
echo $1 | grep CMSSW_5
if [ $? -eq 0 ] ; then
  export SCRAM_ARCH=slc5_amd64_gcc462
fi
cd ${CMSSWHOME}/${CMSSW_VERSION}/src

source /afs/cern.ch/cms/LCG/LCG-2/UI/cms_ui_env.sh
export GLITE_WMS_CLIENT_CONFIG=/afs/cern.ch/cms/LCG/LCG-2/UI/conf/glite_wms_HC.conf
source ${CMSSWHOME}/scripts/cmsset_default.sh
cmsenv
source ${CMSSWHOME}/CRAB/$2/crab.sh
