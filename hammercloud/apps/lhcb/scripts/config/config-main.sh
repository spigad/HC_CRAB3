#!/bin/sh

echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
echo '    _                                                                 _'
echo '    _                     LHCb MAIN Configuration                     _'
echo '    _._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._' 
echo '    _'
echo '    _'

echo '    Restore the original PATH and PYTHONPATH'

export PATH=$HC_ORIGINAL_PATH
export PYTHONPATH=$HC_ORIGINAL_PYTHONPATH

echo '    Source /opt/dirac/bashrc'

source /opt/dirac/bashrc

#Export custom site-packages
export PATH=$PATH:$HCDIR/external/bin/
export PYTHONPATH=$PYTHONPATH:$HCDIR/external/lib/python2.5/site-packages:$HCDIR/external/lib64/python2.5/site-packages

#Export hammercloud python zone.
export PYTHONPATH=$PYTHONPATH:$HCDIR/python

#Export Django & HammerCloud.
export PYTHONPATH=$PYTHONPATH:$HCDIR/external/django/$version:$HCDIR/web/src

#Export apps zones
export PYTHONPATH=$PYTHONPATH:$HCDIR/apps

echo '  PATH='$PATH
echo '  PYTHONPATH='$PYTHONPATH

echo ''
echo '    _ End  LHCb Main  Configuration.'
echo ''

