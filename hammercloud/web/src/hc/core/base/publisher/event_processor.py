
'''Module for event processing across all HammerCloud.'''

from hc.core.utils.generic.class_func import custom_import
from hc.core.utils.generic.observable import Observable
from hc.core.utils.generic.singleton import Singleton
import datetime
import logging
import time

LOGGER = logging.getLogger(__name__)


class EventPublisher(object):
    '''Common interface for event publishing using the app list of publishers'''

    __metaclass__ = Singleton

    def __init__(self, app):
        super(EventPublisher, self).__init__()
        self.message_bus = custom_import('hc.%s.models.MessageBusEvent' % app)
        if self.message_bus is None:
            raise ValueError('No App Publishers or Event Bus for %s' % app)

    def process_event(self, severity, rel_site=None, rel_test=None, **event):
        '''Sends an event to the app publishers through the message bus.'''
        try:
            self.message_bus(type=severity,
                             timestamp=datetime.datetime.now(),
                             mtime=datetime.datetime.now(),
                             processed=False,
                             extra=event,
                             site=rel_site,
                             test=rel_test).save()
        except:
            raise
            LOGGER.error('Achtung!: Could not save the event.')


class EventConsumer(object):
    '''Consumer for the events. Thought to be run inside an event loop.'''

    __metaclass__ = Singleton

    def __init__(self, app):
        super(EventConsumer, self).__init__()
        self.app = app
        # TODO: hack to avoid the Django manage Python path.
        import sys
        if sys.path[0] == '/data/hc/web/src/hc':
            del sys.path[0]
        self.publishers = custom_import('%s.python.lib.publishers.app_publishers.AppPublishers' % app)
        self.message_bus = custom_import('hc.%s.models.MessageBusEvent' % app)
        if self.publishers is None or self.message_bus is None:
            raise ValueError('No App Publishers or Event Bus for %s' % app)
        self.publishers = self.publishers(app)

    def run(self):
        '''Runner for the event loop for this consumer.'''
        try:
            self._event_loop()
        except:
            raise
            LOGGER.error('THE RUN LOOP HAS ENDED WITH ERROR')

    def _event_loop(self):
        '''This is the main event loop for the event processing.'''
        while True:
            for event in self.message_bus.objects.filter(processed=False):
                self.publishers.process_event(event.type, **event.extra)
                event.processed = True
                event.save()
            time.sleep(5.0)
        LOGGER.error('The event processor has ended prematurely.')


class EventProcessor(Observable):
    '''Class that processes the events sent by all the HammerCloud code. Stores
       logs and publishes them to the appropriate services.'''

    def __init__(self):
        super(EventProcessor, self).__init__()
        self.subscribers = []

    def subscribe_publisher(self, publisher):
        '''Adds a subscriber to recive updates, since this is a singleton, we
           are done with creating instances.'''
        self.subscribe(publisher)

    def process_event(self, **event):
        '''Emits a new event request and returns the exit stuff of each
           subscriber after the publish the event.'''
        self.broadcast(**event)
        return self.status()
