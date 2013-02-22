#!/bin/bash

# Script that sets up the main environment for HammerCloud scripts for CMS.
# ARGUMENTS: -v <version> (CMSSW_VERSION wanted).
#            -r <role> (proxy role {production, user}).
#            -m <mode> (if not set, defaults to 'default').

echo 'Setting up HammerCloud CMS submit environment...'

# Custom configurations for submission may follow.
