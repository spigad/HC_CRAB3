# Set the HammerCloud dir.
export HCDIR=/data/hc

# Set the execution path.
export PATH=$HCDIR/external/bin:/afs/cern.ch/sw/lcg/external/Python/2.5.4p2/x86_64-slc5-gcc43-opt/bin:$PATH

# Set the Python path.
export PYTHONPATH=$HCDIR/apps:$HCDIR/external/django/Django-1.2.3:$HCDIR/external/lib/python2.5/site-packages:$HCDIR/web/src:/afs/cern.ch/sw/lcg/external/mysql_python/1.2.2-mysql5.0.18-python2.5/x86_64-slc5-gcc43-opt/lib/python2.5/site-packages:$PYTHONPATH:/usr/lib/python2.5/site-packages

export DJANGO_SETTINGS_MODULE='hc.settings'

# Run copy script.
python $HCDIR/python/scripts/submit/delete_old_test_dirs.py $*

