
'''Has the list of publishers for events. They are categorized by severity, with
   an event processor per severity.'''

from lib.publishers.default_publishers import DefaultPublishers
from hc.core.base.publisher.publish_service import EmailAlert, RobotPublisher
from atlas.python.lib.publishers.nagios_publisher import NagiosPublisher
#from atlas.python.lib.publishers.ssb_publisher import SSBPublisher

#ATLAS_PEOPLE = 'daniel.colin.vanderster@cern.ch,ramon.medrano.llamas@cern.ch,johannes.elmsheuser@cern.ch,federica.legger@physik.uni-muenchen.de'
ATLAS_PEOPLE = 'ramon.medrano.llamas@cern.ch'


class AppPublishers(DefaultPublishers):
    '''This class has the ATLAS publishers services.'''

    def _load_default_publishers(self):
        '''Loads the default publishers for this app.'''
        self.subscribe_publisher('error',        EmailAlert(ATLAS_PEOPLE,
                                                            prefix='[HC-ATLAS][ERROR] '))
        #self.subscribe_publisher('error',        IncidentPublisher())

        self.subscribe_publisher('incident',     EmailAlert(ATLAS_PEOPLE,
                                                            prefix='[HC-ATLAS][INCIDENT] '))
        #self.subscribe_publisher('incident',     IncidentPublisher())

        self.subscribe_publisher('blacklist',    EmailAlert(ATLAS_PEOPLE,
                                                            prefix='[HC-ATLAS][BLACKLIST] '))
        #self.subscribe_publisher('blacklist',    NagiosPublisher())
        #self.subscribe_publisher('blacklist',    SSBPublisher())
        #self.subscribe_publisher('blacklist',    IncidentPublisher())

        #self.subscribe_publisher('robot',        RobotPublisher())
        #self.subscribe_publisher('robot',        NagiosPublisher())
        #self.subscribe_publisher('robot',        SSBPublisher())

        self.subscribe_publisher('aft-metrics',    NagiosPublisher())

        self.subscribe_publisher('alert',        EmailAlert(ATLAS_PEOPLE,
                                                            prefix='[HC-ATLAS][ALERT] '))
        #self.subscribe_publisher('alert',        IncidentPublisher())
