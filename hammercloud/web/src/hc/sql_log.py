from django.db import connections
from django.template import Template, Context
from hc.core.utils.hc import cernmail
from collections import defaultdict

class SQLLogMiddleware:

  def process_response(self, request, response):
    time = defaultdict(float)
    count = defaultdict(int)
    send = False

    for c in connections:
      count[c] = len(connections[c].queries)
      for q in connections[c].queries:
        time[c] += float(q['time'])
      if count[c] > 100 or time[c] > 2000.0:
        send = True

    t = '''
         There was a view with slow performance: %s
           Details:
             time = %s
             count = %s
        '''
    if send:
      cernmail.send('ramon.medrano.llamas@cern.ch', 'SLOW VIEW', str(t % (request.path, time, count)))
      
    return response
