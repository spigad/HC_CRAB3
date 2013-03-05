#!/bin/bash

# Add a site to the functional tests templates.
# ARGUMENTS: <app> (must be set)
#            <site> (site name on HC, must be set)
#            <...> (options for the script)

# Check the presence of a gangabin on the arguments.
if [ -z $1 ] ; then
    echo ' ERROR: application target and site name must be set.'
    exit
else
    export APP=$1
fi

# Get HCDIR from current installation.
HCDIR=`which $0 | sed 's/\/scripts/ /g' | awk '{print $1}'`

# Set up the core environment.
source $HCDIR/scripts/config/config-main.sh $APP

# Launch the add_site_to_ft script to add the site to the FTs.
# The arguments are passed as a single string to be correctly parsed.
echo 'Launching the add_site_to_ft action...'
python $HCDIR/python/scripts/dispatcher.py -f add_site_to_ft $@
