#!/bin/bash

test "x$ROOTCOREDIR" = "x" && echo "ROOTCOREDIR not set, please source setup.sh" && exit 1

test "x$1" = "$1" && echo "no path argument supplied" && exit 1
test -e "$1" && echo "path $1 already exists" && exit 1

PKGFILE=`dirname $0 | xargs dirname`/packages

test -f $PKGFILE || `dirname $0`/find_packages.sh

DIR=$1

mkdir -p $DIR
echo copying RootCore
rsync -a --exclude lib/* --exclude include/* --exclude python/* --exclude user_scripts/* `dirname $0 | xargs dirname`/. $DIR/RootCore

rm -f $DIR/RootCore/grid_packages
touch $DIR/RootCore/grid_packages

for pkg in `cat $PKGFILE`
do
    name=`basename $pkg`
    echo copying $pkg
    rsync -a --exclude obj/* $pkg/. $DIR/$name
    echo $name >>$DIR/RootCore/grid_packages
done
