#!/bin/bash

# Little script to detect where HammerCloud is installed.
# ARGUMENTS: none.

# Get HCDIR from current installation.
HCDIR=`which $0 | sed 's/\/scripts/ /g' | awk '{print $1}'`
