#!/bin/sh

pkg=$1
name=`basename $pkg`

ln -sf $pkg/$name $ROOTCOREDIR/include/
test -d $pkg/python && ln -sf $pkg/python $ROOTCOREDIR/python/$name
test -d $pkg/scripts && ln -sf $pkg/scripts $ROOTCOREDIR/user_scripts/$name
(test -d $pkg/data && ln -sf $pkg/data $ROOTCOREDIR/data/$name) || (test -d $pkg/share && ln -sf $pkg/share $ROOTCOREDIR/data/$name)
ln -sf $pkg/StandAlone/lib${name}.so $ROOTCOREDIR/lib/
if test -d $pkg/bin
then
    for file in $pkg/bin/*
    do
	test -f $file && ln -sf $file $ROOTCOREDIR/bin/
    done
fi
