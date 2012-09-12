#!/bin/bash

test "x$ROOTCOREDIR" = "x" && echo "ROOTCOREDIR not set, please source setup.sh" && exit 1

test -f $PKGFILE || `dirname $0`/find_packages.sh

DIR=/tmp/RootCoreBuild-$$
MYDIR=$DIR/RootCore

rm -rf $DIR
mkdir -p $MYDIR
for package in `cat $ROOTCOREDIR/packages`
do
    echo using package $package
    ln -s $package $MYDIR/
    basename $package >>$MYDIR/packages
done
ln -sf $ROOTCOREDIR $MYDIR/

cd $DIR
ln -s RootCore/PROOF-INF RootCore/PROOF-INF

tar -czhf `dirname $ROOTCOREDIR`/RootCore.par --exclude RootCore/include/* --exclude \*/obj/\* --exclude \*/StandAlone/\* --exclude \*.so --exclude \*.d --exclude \*.o --exclude \*.lo --exclude \*~ --exclude .svn RootCore

rm -rf $DIR
