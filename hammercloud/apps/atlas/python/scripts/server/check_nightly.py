from django.utils.timezone import now
from hc.atlas.models import GlobalOption
import logging
import os

"""Monitor of the Athena nightly on CVMFS.

This script monitors the deployment of new Athena nightlies on CVMFS and
updates the metadata for the nightly testing templates accordingly.
"""

NIGHTLY_DIR = '/cvmfs/atlas-nightlies.cern.ch/repo/sw/nightlies'


class CheckNightly(object):
    """Monitors the deployment for several nightly versions being tested."""

    def check_nightly(self, release, cmtconfig):
        """Checks the presence of a release and a platform."""
        try:
            rel_dir = os.readlink(os.path.join(NIGHTLY_DIR, cmtconfig,
                                               release, 'latest'))
        except OSError:
            logging.error('CMVFS path for nightly %s, %s, latest not found',
                          release, cmtconfig)
            return

        option_name = 'last_nightly_%s_%s' % release.replace('.', '')
        if GlobalOption.set_option(option_name % 'value', rel_dir):
            GlobalOption.set_option(option_name % 'change', now())
            logging.info('Athena CVMFS release for %s on %s changed to %s',
                         release, cmtconfig, rel_dir)
        else:
            logging.info('Athena CVMFS release for %s on %s not changed',
                         release, cmtconfig, rel_dir)

    def run(self):
        self.check_nightly("17.X.0", "x86_64-slc5-gcc43-opt")
        self.check_nightly("18.X.0", "x86_64-slc5-gcc43-opt")
        self.check_nightly("17.2.X", "i686-slc5-gcc43-opt")
        return True
