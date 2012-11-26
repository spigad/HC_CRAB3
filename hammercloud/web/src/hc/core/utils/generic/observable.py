"""Base class that allows to implement the observer pattern easily."""


class Observable(dict):
    """Adds the subscription and emit methods for events."""

    def __init__(self):
        super(Observable, self).__init__()

    def subscribe(self, subscriber):
        """Adds a new subscriber to the subscriber list. Each subscriber must
           be a callable."""
        self[subscriber] = None

    def broadcast(self, *args, **kwargs):
        """Sends an event to all the subscribers."""
        for subscriber in self:
            self[subscriber] = subscriber(*args, **kwargs)

    def status(self):
        """Returns a tuple with the statuses of the last event emission."""
        return tuple(self.values())
