import datetime
from collections import defaultdict
from django.db import models
from django.db.models import Count


class BlacklistAutomata(object):
  """Automata for calculating blacklisting counts.

  Small automata that process blacklisting events streams to get the number of
  sites excluded.

  Attributes:
      _transitions: a dictionary representing the automata transitions with the new
                    status, a possible action and the count of sites.
  """
  _transitions = { 0: { 'blacklist': (1, None, 1),
                        'whitelist': (2, None, 0) },
                   1: { 'blacklist': (1, None, 1),
                        'whitelist': (2, None, 0) },
                   2: { 'blacklist': (1, None, 1),
                        'whitelist': (2, None, 0) },
                   3: { 'blacklist': (0, None, 0),
                        'whitelist': (0, None, 0) } }

  def __init__(self, site=None):
    """Inits with an optional site to allow classification of automata."""
    super(BlacklistAutomata, self).__init__()
    self.site = site
    self.status = 0
    self.count = 0

  def event(self, event):
    """Process an event.

    Follow the automata transition to the new status and execute an optional action.

    Arguments:
        event: the event name (blacklist or whitelist).
    """
    (self.status, action, self.count) = self._transitions[self.status][event]
    if action:
      action()


def timify_events(events):
  """Groups events by its time.

  Returns a generator by yielding of lists of events that have the same timestamp
  to be processed group by group.

  Arguments:
      events: a list of events to make groups.
  Returns:
      yields groups of events with the same timestamp.
  """
  events = iter(events)
  last_time = None
  group = []

  while True:
    try:
      i = events.next()
      if i.timestamp != last_time:
        if group:
          yield group
        group = []
        last_time = i.timestamp
      group.append(i)
    except StopIteration:
      break


class BlacklistEventManager(models.Manager):
  """Manager for the BlaclistEvent model.

  Class that override the default Manager for the BlacklistEvent object in the data models.
  """

  def get_autoexclusion_chart(self, time_limit=None, site=None, cloud=None):
    """Generates the autoexclusion chart.

    Generates the autoexclusion chart by processing the stream of events.

    Arguments:
        time_limit: timeout for a missing whitelisting event.
        site: site to filter by.
        cloud: cloud to filter by.
    Returns:
        a list of timestamps with the count of sites blacklisted and some notes (site names).
    """
    limit = datetime.datetime.now() - datetime.timedelta(days=30)
    events = super(BlacklistEventManager, self).get_query_set().select_related()
    if time_limit:
      events = events.filter(timestamp__gte=datetime.datetime.now() - time_limit)
    if cloud:
      events = events.filter(site__cloud__id=cloud)
    if site:
      events = events.filter(site__id=site)
    events = events.order_by('timestamp')
    site_statuses = defaultdict(BlacklistAutomata)
    chart = []
    # Avoid multiquery. select_related does not work on generic relations.
    for event_group in timify_events(events):
      sites_boff, sites_online = [], []
      for e in event_group:
        site_statuses[e.site.name].event(e.event)
        if e.timestamp > limit:
          if e.event == 'blacklist':
            sites_boff.append(e.site.name) # Should be in query cache
          elif e.event == 'whitelist':
            sites_online.append(e.site.name) # Should be in query cache
      chart.append((e.timestamp,
                    sum(map(lambda x: x.count, site_statuses.values())),
                    sites_boff,
                    sites_online))
    return chart

  def get_top_excluded_sites(self, time_limit=30, number=None):
    """List of the most excluded sites in the last days."""
    return (super(BlacklistEventManager, self).get_query_set()
                                              .filter(event='blacklist')
                                              .filter(timestamp__gte=(datetime.datetime.now() - datetime.timedelta(days=time_limit)))
                                              .values_list('site__name')
                                              .annotate(blacklists=Count('event'))
                                              .order_by('-blacklists')[:number])
