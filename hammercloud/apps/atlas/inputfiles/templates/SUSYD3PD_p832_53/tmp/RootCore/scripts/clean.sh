#!/bin/bash

test "x$ROOTCOREDIR" = "x" && echo "ROOTCOREDIR not set, please source setup.sh" && exit 1

PKGFILE=`dirname $0 | xargs dirname`/packages

test -f $PKGFILE || `dirname $0`/find_packages.sh

for pkg in `cat $PKGFILE`
do
    echo cleaning $pkg
    if cd $pkg/cmt
    then
	true
    else
	echo "failed to enter package $pkg"
	exit 2
    fi
    if make -f Makefile.RootCore $* clean
    then
	true
    else
	echo "failed to clean package $pkg"
	exit 3
    fi
done
