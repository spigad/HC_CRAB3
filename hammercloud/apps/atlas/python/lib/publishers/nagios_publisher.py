
'''Publisher service for Nagios.'''

import ConfigParser
import logging
import stomp
import datetime
import time
from hc.core.base.publisher.publish_service import ServicePublisher
from atlas.utils.atlas_topology import ATLASTopology

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
        self.atlas_topology = ATLASTopology()

    def publish_event(self, **event):
        '''Publish an event to Nagios. Be careful to provide the extra dict'''
        try:
            conn = stomp.Connection([(self.host, self.port)])
            conn.start()
            conn.connect()
            for ce in self.atlas_topology.get_ces_for_panda_queue(event['site']):
                conn.send(self._format_message(host_name=ce,
                                               timestamp=datetime.datetime.now(),
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
            event['timestamp'] = event['timestamp'].strftime("%Y-%m-%dT%H:%M:%SZ")
            return msg % event
        except:
            raise RuntimeError('extra dict not provided with the event')
