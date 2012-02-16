
'''Publisher service for Nagios.'''

import ConfigParser
import logging
import stomp
import datetime
from hc.core.base.publisher.publish_service import ServicePublisher

CONFIG_FILE = '/data/hc/apps/atlas/config/neet.cfg'
LOGGER = logging.getLogger(__name__)


class NagiosPublisher(ServicePublisher):
    '''Publisher for Nagios system for ATLAS.'''

    def __init__(self):
        super(NagiosPublisher, self).__init__()
        config = ConfigParser.ConfigParser()
        config.read(CONFIG_FILE)
        self.host = config.get('Connection', 'HOST')
        self.port = int(config.get('Connection', 'PORT'))
        self.queue =  config.get('Connection', 'QUEUE')

    def publish_event(self, **event):
        '''Publish an event to Nagios. Be careful to provide the extra dict'''
        try:
            conn = stomp.Connection([(self.host, self.port)])
            conn.start()
            conn.connect()
            conn.send(self._format_message(timestamp=datetime.datetime.now(),
                                           **event),
                      destination=self.queue,
                      ack='auto')
            conn.disconnect()
        except:
            LOGGER.error('Could not send the message to Nagios! Skipping.')
            return False
        return True

    def _format_message(self, **event):
        '''Creates the string to send to MSG.'''
        msg = ('hostName: %(host_name)s\n'
               'metricName: %(metric_name)s\n'
               'metricStatus: %(metric_status)s\n'
               'timestamp: %(timestamp)s\n'
               'summaryData: %(subject)s\n'
               'detailsData: %(description)s EOT\n')
        try:
            return msg % event
        except:
            raise RuntimeError('extra dict not provided with the event')
