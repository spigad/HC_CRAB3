#!/bin/bash

dependency=`$ROOTCOREDIR/scripts/get_dependency.sh $*` || exit $?

result="-L$ROOTCOREDIR/lib"
for dep in $dependency
do
    if pkg=`grep -E /$dep\$ $ROOTCOREDIR/packages`
    then
	true
    else
	error=$?
	echo failed to find package $dep
	exit $error
    fi
    lib=`grep -E '^[ \t]*PACKAGE_BINFLAGS[ \t]*=' $pkg/cmt/Makefile.RootCore | sed 's/^[ \t]*PACKAGE_BINFLAGS[ \t]*=//'`
    name=`basename $pkg`
    result="$result -l$name $lib"
    for preload in `grep -E '^[ \t]*PACKAGE_PRELOAD[ \t]*=' $pkg/cmt/Makefile.RootCore | sed 's/^[ \t]*PACKAGE_PRELOAD[ \t]*=//'`
    do
	result="$result -l$preload"
    done
done
echo $result
