from django.db import models
from hc.core.base.models.fields import UnixTimestampField
from hc.core.base.rss.abstract import HCFeedBase

"""This is the model module for the core database."""


class Plugin(models.Model):
    """Plugins are the apps installed in HammerCloud (like ATLAS or CMS)."""
    name = models.CharField(max_length=16)
    mtime = UnixTimestampField(auto_created=True)

    class Meta:
        db_table = 'plugin'


class HCFeed(HCFeedBase):
    """Model for the HammerCloud RSS feed."""
    pass
