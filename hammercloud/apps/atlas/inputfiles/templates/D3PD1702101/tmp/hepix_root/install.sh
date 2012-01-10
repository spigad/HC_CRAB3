# genereated by GANGA4
# Install a user area
#
# ATLAS/ARDA

if [ $SITEROOT != '/afs/cern.ch' ] && [ $CMTSITE != 'CERN' ]
then
  if [ ! -z `echo $ATLAS_RELEASE | grep 11.` ]
  then
      source $SITEROOT/dist/$ATLAS_RELEASE/AtlasRelease/*/cmt/setup.sh
  elif ( [ ! -z `echo $ATLAS_RELEASE | grep 12.` ] || [ ! -z `echo $ATLAS_RELEASE | grep 13.` ] || [ ! -z `echo $ATLAS_RELEASE | grep 14.` ] || [ ! -z `echo $ATLAS_RELEASE | grep 15.` ] || [ ! -z `echo $ATLAS_RELEASE | grep 16.` ] ) && ( [ -z $ATLAS_PRODUCTION_ARCHIVE ] )
  then
      if [ -z $ATLAS_PROJECT ]
      then
          source $SITEROOT/AtlasOffline/$ATLAS_RELEASE/AtlasOfflineRunTime/cmt/setup.sh
      elif [ ! -z $ATLAS_PROJECT ]
      then
          source $SITEROOT/${ATLAS_PROJECT}/$ATLAS_PRODUCTION/${ATLAS_PROJECT}RunTime/cmt/setup.sh
      fi
  fi
else
  if [ ! -z `echo $ATLAS_RELEASE | grep 11.` ]
  then
      source $SITEROOT/software/dist/$ATLAS_RELEASE/Control/AthenaRunTime/*/cmt/setup.sh
  elif ( [ ! -z `echo $ATLAS_RELEASE | grep 12.` ] || [ ! -z `echo $ATLAS_RELEASE | grep 13.` ] ) && [ -z $ATLAS_PRODUCTION_ARCHIVE ]
  then
      source $ATLAS_SOFTWARE/$ATLAS_RELEASE/cmtsite/setup.sh 
      export ATLASOFFLINE=`cmt show path | grep AtlasOffline | sed -e ""s:.*path\ ::"" | sed -e ""s:\ from.*::""`
      source $ATLASOFFLINE/AtlasOfflineRunTime/cmt/setup.sh
      RHREL=`cat /etc/redhat-release`
      SC4=`echo $RHREL | grep -c 'Scientific Linux CERN SLC release 4'`
      if [ $SC4 -gt 0 ]; then
        export PATH=/afs/cern.ch/atlas/offline/external/slc3compat/1.0.0/bin/i686-slc3-gcc323/:$PATH
        export LD_LIBRARY_PATH=/afs/cern.ch/atlas/offline/external/slc3compat/1.0.0/bin/i686-slc3-gcc323/:$LD_LIBRARY_PATH
      fi
  elif ( [ ! -z `echo $ATLAS_RELEASE | grep 14.` ] || [ ! -z `echo $ATLAS_RELEASE | grep 14.` ] ) && [ -z $ATLAS_PRODUCTION_ARCHIVE ]
  then
      source $ATLAS_SOFTWARE/$ATLAS_RELEASE/cmtsite/setup.sh -tag=$ATLAS_RELEASE,32
      source $ATLAS_SOFTWARE/$ATLAS_RELEASE/AtlasOffline/$ATLAS_RELEASE/AtlasOfflineRunTime/cmt/setup.sh
  fi
fi

export CMTPATH=$PWD:$CMTPATH
dum=`echo $LD_LIBRARY_PATH | tr ':' '
' | egrep -v '^/lib' | egrep -v '^/usr/lib' | tr '
' ':' `
export LD_LIBRARY_PATH=$dum

echo '**********************************************************'
echo 'CMTPATH = ' $CMTPATH
echo 'PYTHONPATH = '$PYTHONPATH
echo '**********************************************************'

cmt config
cmt broadcast source setup.sh
cmt broadcast cmt config
source setup.sh

echo '**********************************************************'
echo 'CMTPATH = ' $CMTPATH
echo 'PYTHONPATH = '$PYTHONPATH
echo '**********************************************************'

if [ 'False' = 'True' ]
then
    echo '==========================='
    echo 'GCC =' `which gcc`
    echo `gcc --version`
    echo 'PATH =' $PATH
    echo 'LD_LIBRARY_PATH =' $LD_LIBRARY_PATH
    echo '==========================='
    cmt broadcast gmake -s

    cmt config
    cmt broadcast source setup.sh
    cmt broadcast cmt config
    source setup.sh

fi
echo '**********************************************************'
echo 'CMTPATH = ' $CMTPATH
echo 'PYTHONPATH = '$PYTHONPATH
echo '**********************************************************'

