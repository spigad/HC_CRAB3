#!/usr/bin/env python

"""Maps PanDA queue names to CE hostnames easily

This module loads the topology from ATLAS services and allows to get the list
of CE hostnames and meta information for a PanDA queue.
"""

import getopt
import sys
import unittest
import urllib

try:
    import simplejson as json
except ImportError:
    import json


__author__ = 'Ramon Medrano Llamas'
__email__ = 'ramon.medrano.llamas@cern.ch'
__credits__ = 'Alessandro Di Girolamo'
__version__ = '0.1'

ATLAS_SITES_URL = 'http://adc-ssb.cern.ch/SITE_EXCLUSION/ATLAS_sites.json'
CE_MAPPINGS_URL = 'http://grid-monitoring.cern.ch/mywlcg/sam-pi/services_defined_in_groups?vo_name=atlas&output=json&group_type=ATLAS_Site'


class ATLASTopologyException(Exception):
    """Errors related with this module will use this type."""

    def __init__(self, msg):
        super(ATLASTopologyException, self).__init__()
        self.msg = msg


class ATLASTopology(object):
    """Wrapper to perform topology queries for ATLAS

    Loads and stores the ATLAS topology from ATLAS services and allows to
    perform queries in a simple way.
    """

    def __init__(self):
        super(ATLASTopology, self).__init__()
        self.__load_atlas_sites__()
        self.__load_ce_mappings__()

    def get_ces_for_panda_queue(self, panda_queue, flavour=None):
        """Returns a list of CEs for the given PanDA queue."""
        return self.get_ces_for_site(self.get_site_of_panda_queue(panda_queue),
                                     flavour)

    def get_ces_for_site(self, site, flavour=None):
        """Returns a list of CEs for the given ATLAS site."""
        ces = filter(lambda x: x['type'] == 'CE',
                     self.get_services_for_site(site))
        if flavour is not None:
            ces = filter(lambda x: x['flavour'] == flavour, ces)
        return map(lambda x: x['hostname'], ces)

    def get_site_of_panda_queue(self, panda_queue):
        """Returns the site name of a PanDA queue."""
        # This can be done with nested map() / filter() but is more readable
        # like this (and slower, if perfomance is not enough, should be changed
        # to the native map() / filter()).
        for (site_name, site_data) in self.__atlas_sites__.iteritems():
            for (_, resources) in site_data['processing_resources'].iteritems():
                for queue_type in ('analysis', 'production', 'special'):
                    if panda_queue in resources[queue_type].keys():
                        return site_name
        return None

    def get_site_id_of_panda_queue(self, panda_queue, _site_type=None):
        """Returns the SiteID name of a PanDA queue."""
        # This can be done with nested map() / filter() but is more readable
        # like this (and slower, if perfomance is not enough, should be changed
        # to the native map() / filter()).
        for (_, site_data) in self.__atlas_sites__.iteritems():
            for (site_id, resources) in site_data['processing_resources'].iteritems():
                for queue_type in ('analysis', 'production', 'special'):
                    if panda_queue in resources[queue_type].keys():
                        return site_id
        return None

    def get_services_for_site(self, site):
        """Returns a list of services for a site, including CEs, SRMs..."""
        try:
            return filter(lambda x: x['name'] == site,
                          filter(lambda x: x['name'] == 'ATLAS_Site',
                                 filter(lambda x: x['name'] == 'atlas',
                                        self.__ce_mappings__)[0]['group_types'])
                          [0]['groups'])[0]['services']
        except IndexError:
            return []

    def __load_atlas_sites__(self):
        """Loads the ATLAS site topology from SSB and parses it."""
        setattr_from_remote_json(self, '__atlas_sites__', ATLAS_SITES_URL)

    def __load_ce_mappings__(self):
        """Loads the ATLAS CE mappings from SAM and parses it."""
        setattr_from_remote_json(self, '__ce_mappings__', CE_MAPPINGS_URL)


def setattr_from_remote_json(obj, attr, url):
    """Loads a remote JSON file and sets an attrbute to an object from it."""
    try:
        setattr(obj, attr, json.load(urllib.urlopen(url)))
    except IOError, (_, msg):
        raise ATLASTopologyException(msg)
    except ValueError, ve:
        raise ATLASTopologyException(str(ve))


class TestATLASToplogy(unittest.TestCase):
    """Class with the unit tests for this module."""

    pass


def main(argv=None):
    """Entry point for this program. Parses argumens and launches the rest.

    argv -- The argument list. Can be overriden if launched from interpreter.
    """
    # Get arguments.
    if argv is None:
        argv = sys.argv
    # Parse command line options.
    try:
        try:
            opts, args = getopt.getopt(argv[1:], 'h', ['help'])
        except getopt.error, msg:
            raise ATLASTopologyException(msg)
        # Process options.
        for (opt, _) in opts:
            if opt in ('-h', '--help'):
                print __doc__
                return 0
        # Process arguments.
        if len(args) > 0:
            raise ATLASTopologyException("This program doesn't allow argument")
        # Launch unit tests for this module here.
        unittest.main()
    except ATLASTopologyException, err:
        print >> sys.stderr, err.msg
        print >> sys.stderr, 'for help use --help'
        return -1


if __name__ == '__main__':
    sys.exit(main())
