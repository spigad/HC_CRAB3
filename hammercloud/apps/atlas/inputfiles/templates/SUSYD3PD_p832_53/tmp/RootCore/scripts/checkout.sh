#!/bin/bash

test \! -f "$1" && echo could not find list file $1 && exit 1

for package in `grep -v '^#' $1`
do
    package=`echo $package | sed 's/^atlas/svn+ssh:\/\/svn.cern.ch\/reps\/atlas/'`
    if test "x$CERN_USER" != "x"
    then
	package=`echo $package | sed "s/svn.cern.ch/${CERN_USER}@svn.cern.ch/"`
    fi
    name=`echo $package | sed 's/\/trunk//' | sed 's/\/tags\/.*//' | sed 's/.*\///'`
    if test \! -d $name
    then
	echo svn co $package $name
	svn co $package $name
    fi
done
