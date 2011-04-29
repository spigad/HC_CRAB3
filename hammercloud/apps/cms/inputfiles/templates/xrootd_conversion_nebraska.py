#!/bin/sh

exec python - "$@" << EOF
import os
import sys
import pset

runtime = os.environ['RUNTIME_AREA']
njob = os.environ['NJob']
fjr = os.path.join(runtime, "crab_fjr_%s.xml" % njob)

print "Argv passed to python script:", sys.argv
site = "T2_US_Nebraska"
prefix = 'root://xrootd-itb.unl.edu//store/test/xrootd/%s' % site

alt_names = [prefix + i for i in pset.process.source.fileNames]
pset.process.source.fileNames = alt_names

results = pset.process.dumpPython()
fd = open("pset_alt.py", "w")
fd.write(results)
fd.close()

os.execvp("cmsRun", ["cmsRun", "-j", fjr, "-p", "pset_alt.py"])
EOF

