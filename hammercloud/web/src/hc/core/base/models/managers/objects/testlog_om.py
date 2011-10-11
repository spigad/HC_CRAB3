import datetime
from collections import defaultdict
from django.db import models
from django.db.models import Count


class TestLogManager(models.Manager):
  '''
  Class that override the default Manager for the TestLog object in the data models
  '''
  def get_filtered_incidents(self, query=None, time=72):
    '''
    Filter for the incidents view, mainly.
    '''
    if not filter or len(filter) == 0:
      filter = '%'
    if not hours or hours <= 0:
      hours = 72
    return (super(TestLogManager, self).filter(comment__like=filter)
                                       .filter(mtime__gte=(datetime.datetime.now - datetime.timedelta(hours=hours)))
                                       .order_by('-mtime'))
