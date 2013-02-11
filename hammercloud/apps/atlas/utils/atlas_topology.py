#!/usr/bin/env python

"""Maps PanDA queue names to CE hostnames easily

This module loads the topology from ATLAS services (namely AGIS) and allows to
get the list of CE hostnames and meta information for a PanDA queue.
"""

import datetime
import getopt
import logging
import sys
import unittest
import urllib

try:
    import simplejson as json
except ImportError:
    import json


__author__ = 'Ramon Medrano Llamas <ramon.medrano.llamas@cern.ch>'
__credits__ = 'Alessandro Di Girolamo <alessandro.di.girolamo@cern.ch>'
__version__ = '0.2'

AGIS_SOURCE = 'http://atlas-agis-api.cern.ch/request/pandaqueue/query/list/?json&preset=schedconf.all'
REBUS_SOURCE = 'http://gstat-wlcg.cern.ch/apps/capacities/sites/ALL/' + datetime.date.today().strftime('%Y') + '/' + datetime.date.today().strftime('%m') + '/json'


class ATLASTopologyError(Exception):
    """Errors related with this module will use this type."""

    def __init__(self, msg):
        super(ATLASTopologyError, self).__init__()
        self.msg = msg

    def __unicode__(self):
        return self.msg

    def __str__(self):
        return unicode(self).encode('utf-8')


class ATLASTopology(object):
    """Wrapper to perform topology queries for ATLAS

    Loads and stores the ATLAS topology from ATLAS services and allows to
    perform queries in a simple way.
    """

    def __init__(self):
        super(ATLASTopology, self).__init__()
        setattr_from_remote_json(self, '__schedconfig__', AGIS_SOURCE)
        setattr_from_remote_json(self, '__rebus__', REBUS_SOURCE)

    def get_ces_from_siteid(self, panda_siteid):
        """Returns a list of CEs for the given ATLAS site."""
        return map(lambda q: q['ce_endpoint'].split(':')[0],
                   filter(lambda q: q['ce_state'] == 'ACTIVE',
                          self._get_field_from_siteid(panda_siteid, 'queues')))

    def get_total_hepspec_from_siteid(self, panda_siteid):
        """Returns the total HEPSPEC06 count declared in REBUS data."""
        return self._get_rebus_field_from_siteid(panda_siteid, 'HEPSPEC06')

    def get_hepspec_from_siteid(self, panda_siteid):
        """Returns the HEPSPEC/jobslot for this site."""
        try:
            return (float(self.get_total_hepspec_from_siteid(panda_siteid)) /
                    float(self.get_jobslots_from_siteid(panda_siteid)))
        except ZeroDivisionError:
            raise ATLASTopologyError(('REBUS info not consistent for %s' %
                                      panda_siteid))

    def get_jobslots_from_siteid(self, panda_siteid):
        """Returns the total jobslots count declared in REBUS data."""
        return self._get_rebus_field_from_siteid(panda_siteid, 'LogicalCPUs')

    def get_site_from_siteid(self, panda_siteid):
        """Returns the site name of a PanDA queue."""
        return self._get_field_from_siteid(panda_siteid, 'atlas_site')

    def get_ddm_from_siteid(self, panda_siteid):
        """Returns the site name of a PanDA queue."""
        return self._get_field_from_siteid(panda_siteid, 'ddm')

    def get_email_from_siteid(self, panda_siteid):
        """Returns the site name of a PanDA queue."""
        return self._get_field_from_siteid(panda_siteid, 'email')

    def _get_field_from_siteid(self, panda_siteid, field):
        """Returns one of the multiple fields from AGIS for that siteid."""
        return self._get_all_from_siteid(panda_siteid)[field]

    def _get_all_from_siteid(self, panda_siteid):
        """Returns all the information for a given PanDA siteid.

        panda_siteid -- (str) the siteid of the site to lookup.

        Returns:
          A dict with all the AGIS information. Raises an ATLASTopologyError if
          the siteid is not found.
        """
        try:
            return filter(lambda s: s['panda_resource'] == panda_siteid,
                          self.__schedconfig__.itervalues())[0]
        except IndexError:
            raise ATLASTopologyError(('The PanDA siteid "%s" does not exist' %
                                      panda_siteid))

    def _get_rebus_field_from_siteid(self, panda_siteid, field):
        """Returns a particular field from REBUS."""
        try:
            return filter(lambda s: (s['Site'] ==
                                     self._get_field_from_siteid(panda_siteid,
                                                                 'rc_site')),
                          self.__rebus__)[0][field]
        except IndexError:
            raise ATLASTopologyError(('No information in REBUS for "%s"' %
                                      panda_siteid))


def setattr_from_remote_json(obj, attr, url):
    """Loads a remote JSON file and sets an attrbute to an object from it."""
    try:
        logging.debug('Downloading JSON source at %s', url)
        setattr(obj, attr, json.load(urllib.urlopen(url)))
    except IOError, (_, msg):  # pylint: disable=E211
        logging.exception('Could not parse the source at %s', url)
        raise ATLASTopologyError(msg)
    except ValueError, ve:
        logging.exception('Could not parse the source at %s', url)
        raise ATLASTopologyError(str(ve))


class TestATLASToplogy(unittest.TestCase):
    """Class with the unit tests for this module."""
    # TODO(rmedrano): Add tests to this.


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
            raise ATLASTopologyError(msg)
        # Process options.
        for (opt, _) in opts:
            if opt in ('-h', '--help'):
                print __doc__
                return 0
        # Process arguments.
        if len(args) > 0:
            raise ATLASTopologyError("This program doesn't allow arguments")
        # Launch unit tests for this module here.
        unittest.main()
    except ATLASTopologyError, err:
        print >> sys.stderr, err.msg
        print >> sys.stderr, 'for help use --help'
        return -1


if __name__ == '__main__':
    sys.exit(main())
