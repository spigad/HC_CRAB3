from django.db import models
from hc.core.base.models.fields import UnixTimestampField
from hc.core.base.models.metacreator import MetaCreator

from datetime import datetime

class HCFeedBase(models.Model):

  SEVERITY_CHOICES = (
    (u'info', u'info'),
    (u'maintenance', u'maintenance'),
    (u'error',u'error'),
    (u'report',u'report'),
    (u'other',u'other')
  )

  id          = models.AutoField(primary_key=True)
  title       = models.CharField(max_length=255)
  description = models.CharField(max_length=4095)
  severity    = models.CharField(choices = SEVERITY_CHOICES, max_length=15)
#  mtime       = UnixTimestampField(auto_created=True)
  mtime       = models.DateTimeField()

  def __unicode__(self):
    return '%s (%s)'%(self.title,self.severity)

  def save(self):
    self.mtime = datetime.now()
    super(HCFeedBase, self).save()

  class Meta:
    abstract = True
    db_table = u'hc_feed'

class AppFeedBase(HCFeedBase):

  class Meta:
    abstract = True
    db_table = u'app_feed'

class CloudFeedBase(HCFeedBase):

  __metaclass__ = MetaCreator

  #cloud -> hc.core.base.models.keys.fk.generator.generateFK('Cloud','CloudFeed','cloud',{})

  class Meta:
    abstract = True
    db_table = u'cloud_feed'

class SiteFeedBase(HCFeedBase):

  __metaclass__ = MetaCreator

  #site -> hc.core.base.models.keys.fk.generator.generateFK('Site','SiteFeed','site',{})

  class Meta:
    abstract = True
    db_table = u'site_feed'

class TemplateFeedBase(HCFeedBase):

  __metaclass__ = MetaCreator

  #template -> hc.core.base.models.keys.fk.generator.generateFK('Template','TemplateFeed','template',{})

  class Meta:
    abstract = True
    db_table = u'template_feed'

class TestFeedBase(HCFeedBase):

  __metaclass__ = MetaCreator

  #test -> hc.core.base.models.keys.fk.generator.generateFK('Test','TestFeed','test',{})

  class Meta:
    abstract = True
    db_table = u'test_feed'

