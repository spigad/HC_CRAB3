
'''Has the list of publishers for events. They are categorized by severity, with
   an event processor per severity.'''

from hc.core.utils.generic.class_func import custom_import
from hc.core.utils.generic.singleton import Singleton
from hc.core.base.publisher.event_processor import EventProcessor
import logging

LOGGER = logging.getLogger(__name__)

#pylint: disable=R0921
class DefaultPublishers(dict):
    '''This class is the base logic for the apps to add publsihers on demand.'''

    __metaclass__ = Singleton

    def __init__(self, app):
        super(DefaultPublishers, self).__init__()
        if app is None or type(app) is not str or app == 'core':
            raise RuntimeError('App not valid for the Publishing service')
        message_bus = custom_import('hc.%s.models.MessageBusEvent' % app)
        if message_bus is None:
            raise RuntimeError('Could not import TestLog from the app')
        self._load_default_publishers()

    def _load_default_publishers(self):
        '''Loads the default publishers for this app.'''
        raise NotImplementedError

    def subscribe_publisher(self, severity, publisher):
        '''Adds a publisher for a given severity level.'''
        try:
            if severity not in self:
                self[severity] = EventProcessor()
            self[severity].subscribe_publisher(publisher)
        except KeyError:
            LOGGER.error('No processor for severity %s' % severity)

    def process_event(self, severity, **event):
        '''Sends an event for all the subscribers of the level.'''
        try:
            self[severity].process_event(**event)
            return self[severity].status()
        except KeyError:
            LOGGER.error('No processor for severity %s' % severity)
            return None
