#!/bin/sh
echo Running the LCG UTILS HC Test 0.1
echo 
echo Staging in the test from AFS...
cp /afs/cern.ch/sw/lcg/app/spi/grid-test/LCG_56g.tar.bz2 .
cp /afs/cern.ch/sw/lcg/app/spi/grid-test/run_lcg_tests.sh .
echo Running the test...
sh run_lcg_tests.sh
echo Output:
ls -l
ls -l testresults
