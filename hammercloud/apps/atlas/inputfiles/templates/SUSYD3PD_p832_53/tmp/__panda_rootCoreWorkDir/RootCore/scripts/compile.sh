#!/bin/bash

test "x$ROOTCOREDIR" = "x" && echo "ROOTCOREDIR not set, please source setup.sh" && exit 1

PKGFILE=`dirname $0 | xargs dirname`/packages

test -f $PKGFILE || `dirname $0`/find_packages.sh

rm -rf $ROOTCOREDIR/bin
mkdir $ROOTCOREDIR/bin
rm -rf $ROOTCOREDIR/include
mkdir $ROOTCOREDIR/include
rm -rf $ROOTCOREDIR/python
mkdir $ROOTCOREDIR/python
rm -rf $ROOTCOREDIR/user_scripts
mkdir $ROOTCOREDIR/user_scripts
rm -rf $ROOTCOREDIR/data
mkdir $ROOTCOREDIR/data
rm -rf $ROOTCOREDIR/lib
mkdir $ROOTCOREDIR/lib

rm -f $ROOTCOREDIR/preload
touch $ROOTCOREDIR/preload

for pkg in `cat $PKGFILE`
do
    name=`basename $pkg`
    echo compiling $pkg
    if cd $pkg/cmt
    then
	true
    else
	echo "failed to enter package $pkg"
	exit 2
    fi
    if make -f Makefile.RootCore $*
    then
	true
    else
	echo "failed to compile package $pkg"
	exit 3
    fi
    $ROOTCOREDIR/scripts/link_package.sh $pkg
    for lib in `grep '^PACKAGE_PRELOAD[ 	]*=' Makefile.RootCore | tail -n 1 | sed 's/^PACKAGE_PRELOAD[ 	]*=//'`
    do
	echo lib$lib >>$ROOTCOREDIR/preload
    done
done

if test "x$ROOTCOREGRID" != "x1"
then
    if root -l -b -q $ROOTCOREDIR/scripts/load_packages.C+
    then
	true
    else
	echo "failed to test load libraries"
	exit 4
    fi
fi
