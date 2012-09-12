#!/bin/bash

test "x$ROOTCOREDIR" = "x" && echo "ROOTCOREDIR not set, please source setup.sh" && exit 1

DIR=`pwd`
echo looking for packages in $DIR
PACKAGES=
for file in `find -L $DIR -type f -name Makefile.RootCore | grep cmt/Makefile.RootCore$`
do
    PACKAGES="`dirname $file | xargs dirname` $PACKAGES"
done

PKGFILE=`dirname $0 | xargs dirname`/packages
rm -f $PKGFILE
touch $PKGFILE

for pkg in $PACKAGES
do
    echo $pkg >>$PKGFILE
done

echo packages found:
cat $PKGFILE

echo
echo sorted packages:
list=`sed 's/.*\///' < $PKGFILE` || exit $?
list=`$ROOTCOREDIR/scripts/get_dependency.sh $list` || exit $?
list=`$ROOTCOREDIR/scripts/get_location.sh $list` || exit $?
rm -f $PKGFILE
touch $PKGFILE
for pkg in $list
do
    echo $pkg >>$PKGFILE
done
cat $PKGFILE
