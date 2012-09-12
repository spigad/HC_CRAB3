#!/bin/bash

fulldep=""

function add_dep {
    for mydep in $fulldep
    do
	if test "$1" = "$mydep"
	then
	    return 0
	fi
    done

    dir=`grep \/$1\$ $ROOTCOREDIR/packages`
    if test "$dir" = ""
    then
	echo package $1 not known 1>&2
	return -1
    fi
    dep=`grep -hE '^[ \t]*PACKAGE_DEP[ \t]*=' $dir/cmt/Makefile.RootCore | sed 's/^[ \t]*PACKAGE_DEP[ \t]*=//'`
    for mydep in $dep
    do
	add_dep $mydep || exit $?
    done

    for mydep in $fulldep
    do
	if test "$1" = "$mydep"
	then
	    echo package $1 has cyclical dependency 1>&2
	    return -1
	fi
    done

    fulldep="$fulldep $1"
    return 0
}



for package in $*
do
    add_dep $package || exit $?
done

echo $fulldep
