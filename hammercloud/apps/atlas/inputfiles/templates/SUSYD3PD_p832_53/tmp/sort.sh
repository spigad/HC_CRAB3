#!/bin/bash
# Shell program to sort numbers in file in ascending order
# --------------------------------------------------------------------
# This is a free shell script under GNU GPL version 2.0 or above
# Copyright (C) 2005 nixCraft project.
# Feedback/comment/suggestions : http://cyberciti.biz/fb/
# -------------------------------------------------------------------------
# This script is part of nixCraft shell script collection (NSSC)
# Visit http://bash.cyberciti.biz/ for more information.
# -------------------------------------------------------------------------
 
file=""
echo -n "Enter Filename : "
read file
 
if [ ! -f $file ]
then
	echo "$file not a file!"
	exit 1
fi
 
sort -n $file
