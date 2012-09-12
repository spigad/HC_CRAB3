#!/bin/bash

unset ROOTCOREDIR

cd RootCore
./configure
cd ..
source RootCore/scripts/setup.sh

rm -f RootCore/packages
for pkg in `cat packages`
do
    echo `pwd`/$pkg >>RootCore/packages
done

if [ "$1" == "clean" ]
then
    exec $ROOTCOREDIR/scripts/clean.sh
fi

exec $ROOTCOREDIR/scripts/compile.sh
