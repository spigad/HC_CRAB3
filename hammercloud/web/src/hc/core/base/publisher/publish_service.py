
'''Module for the service publishers.'''

from hc.core.utils.hc import cernmail


class Event(object):
    '''Class for the events that are going to be processed by the message bus'''

    def __init__(self, **kwargs):
        for attr, val in kwargs.iteritems():
            setattr(self, attr, val)


class ServicePublisher(object):
    '''Base class for a service publisher. Provides the basic interface to make
       this class a callable.'''

    def __init__(self):
        super(ServicePublisher, self).__init__()

    def __call__(self, *args, **kwargs):
        self.publish_event(*args, **kwargs)

    def publish_event(self, **event):
        '''Publish an event using this service.'''
        raise NotImplementedError


class EmailAlert(ServicePublisher):
    '''This publisher sends and email to the corresponding addresses.'''

    def __init__(self, addresses, prefix=''):
        super(EmailAlert, self).__init__()
        self._addresses = addresses
        self._prefix = prefix

    def publish_event(self, **event):
        '''Sends the email.'''
        event = Event(**event)
        #pylint: disable=E1101
        cernmail.send(self._addresses, self._prefix + event.subject, event.description)


class RobotPublisher(ServicePublisher):
    '''Publisher for Robot.'''

    def __init__(self):
        super(RobotPublisher, self).__init__()

    def publish_event(self, **event):
        '''In this case, is just storing a site option, and the Django views
           will do the rest.'''
        pass


class IncidentPublisher(ServicePublisher):
    '''Publisher for Incidents page.'''

    def __init__(self):
        super(IncidentPublisher, self).__init__()

    def publish_event(self, **event):
        '''In this case, save the incident.'''
        pass


class RSSPublisher(ServicePublisher):
    '''Publisher for the RSS page.'''

    def __init__(self):
        super(RSSPublisher, self).__init__()

    def publish_event(self, **event):
        '''In this case, save an RSS entry so the clients get updated.'''
        pass


class TwitterPublisher(ServicePublisher):
    '''This publisher sends an update to Twitter (just an example of generic
       publisher).'''

    def __init__(self):
        super(TwitterPublisher, self).__init__()
        # Setup Twitter API

    def publish_event(self, **event):
        '''Sends the tweet.'''
        raise NotImplementedError


class DummyPublisher(ServicePublisher):
    '''Just a test of the publisher.'''

    def publish_event(self, **event):
        '''Returns the event.'''
        return event
