import datetime
from collections import defaultdict
from django.db import models
from django.db.models import Count,Q


class TestLogManager(models.Manager):
  '''
  Class that override the default Manager for the TestLog object in the data models
  '''
  def get_filtered_incidents(self, query=None, time=72, site_name=None, severity=None):
    '''
    Filter for the incidents view, mainly.
    '''
    if not query or len(query) == 0:
      query = ''
    if not time or time <= 0:
      time = 72
    basic = (super(TestLogManager, self).get_query_set()
                                        .select_related('test')
                                        .filter(comment__contains=query)
                                        .filter(mtime__gte=(datetime.datetime.now() - datetime.timedelta(hours=time))))
    # Filter by severity
    if severity:
      if severity == u'white+blacklisting':
        basic = basic.filter(Q(severity='whitelisting') | Q(severity='blacklisting'))
      else:
        basic = basic.filter(severity=severity)
    # Filter by site name.
    if site_name:
      basic = basic.filter(comment__contains=site_name)
    return basic.order_by('-mtime')
