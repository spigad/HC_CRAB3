from datetime import timedelta
from django.utils.timezone import now
from hc.core.utils.generic.class_func import custom_import
import glob
import logging
import os
import shutil

"""Removes the old test directories to make free space.

This script removes the old test directories to make free space on the AFS
workspace.
"""


class DeleteOldTestDirs(object):
    """Cleans the old test directories for the given days."""

    def run(self, app, dic):
        """Method to be run by the cron dispatcher."""
        try:
            days_to_keep = int(dic['--days'])
        except KeyError:
            days_to_keep = 14
            logging.info('Defaulting to %d days to keep', days_to_keep)
        doit = '--doit' in dic
        hcdir = os.environ['HCDIR']

        if app == 'core':
            logging.info('This script is not available for the core app.')
            return False

        Test = custom_import('hc.%s.models.Test' % app)
        time_threshold = now() - timedelta(days=days_to_keep)
        old_tests = (Test.objects
                         .filter(endtime__lt=time_threshold)
                         .values_list('id', 'usercode__path')
                         .order_by())

        logging.info('Keeping test data from %d days', days_to_keep)
        for test_id, usercode in old_tests:
            logging.info('Processing test %d', test_id)
            testdir = '%s/apps/%s/testdirs/test_%d' % (hcdir, app, test_id)
            if os.path.exists(testdir):
                logging.debug(' Removing directory %s', testdir)
                if doit:
                    shutil.rmtree(testdir)
                    logging.debug(' Removed.')
            else:
                logging.debug(' Test directory already removed.')
            files = ['%s/apps/%s/testdirs/run-test-%d.sh' % (hcdir, app, test_id)] 
            files.extend(glob.glob('/tmp/*.%d.%s' % (test_id,
                                                     usercode.split('/')[-1])))
            for f in files:
                if os.path.exists(f):
                    logging.debug(' Removing extra file: %s', f)
                    if doit:
                        os.unlink(f)
                        logging.debug(' Removed.')
                else:
                    logging.debug(' Extra file %s already gone.', f)
