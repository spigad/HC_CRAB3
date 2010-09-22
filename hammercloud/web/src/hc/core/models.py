from django.db import models

from hc.core.base.models.abstract import *
from hc.core.base.models.fields import UnixTimestampField

from hc.core.base.rss.abstract import HCFeedBase

class Plugin(models.Model):

  name = models.CharField(max_length = 16)
  mtime = UnixTimestampField(auto_created=True)
  
  class Meta:
    db_table = 'plugin'

class HCFeed(HCFeedBase):
  pass
