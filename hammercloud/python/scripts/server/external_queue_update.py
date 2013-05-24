from hc.core.utils.generic.class_func import custom_import
import logging

"""Crontab action to monitor changes on the WMS system of the VO.

Currenty, this cron is used mainly by ATLAS, to monitor external changes of the
queue status in order to detect external blacklists and to monitor when the
version of the Athena nightlies are deployed.
"""

APP_SCRIPTS = (
    '%s.python.scripts.server.external_queue_update.ExternalQueueUpdate',
    '%s.python.scripts.server.check_nightly.CheckNightly'
)


class ExternalQueueUpdate(object):
    """Launch the app montoring schema."""

    def run(self, app, dic):
        """Launches the monitoring scripts one by one."""
        if app != 'atlas':
            logging.error('This cron action is only available for ATLAS')
            return False

        for script in APP_SCRIPTS:
            logging.info('Launching app script: "%s"', script)
            script_object = custom_import(script % app)
            if script_object:
                script_object().run()

        return True
