export PATH=/afs/cern.ch/cms/common:/afs/cern.ch/cms/bin:$PATH

if [ ! $SCRAM_ARCH ]
then
    SCRAM_ARCH=`/afs/cern.ch/cms/common/cmsarch`
    export SCRAM_ARCH
fi

here=/afs/cern.ch/cms

if [ ! $CMS_PATH ]
then
    export CMS_PATH=$here
fi

# aliases
alias cmsenv='eval `scramv1 runtime -sh`'
alias cmsrel='scramv1 project CMSSW'

if [ -f $CMS_PATH/SITECONF/local/JobConfig/cmsset_local.sh ]; then
        . $CMS_PATH/SITECONF/local/JobConfig/cmsset_local.sh
fi

if [ ! $CVSROOT ]
then
    CVSROOT=:gserver:cmscvs.cern.ch:/cvs_server/repositories/CMSSW
    export CVSROOT
fi
