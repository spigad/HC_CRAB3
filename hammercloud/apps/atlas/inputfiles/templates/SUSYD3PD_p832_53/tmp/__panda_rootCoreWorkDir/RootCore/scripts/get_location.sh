#!/bin/bash

for package in $*
do
    dir=`grep \/$package\$ $ROOTCOREDIR/packages`
    if test "$dir" = ""
    then
	echo package $package not known 1>&2
	exit -1
    fi
    echo $dir
done
