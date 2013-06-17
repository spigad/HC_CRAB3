from django.db import models
from django.db import IntegrityError
from django.utils.timezone import now

from hc.core.base.models.fields import PickledObjectField
from hc.core.base.models.metacreator import MetaCreator
from hc.core.base.models.managers.objects.test_om import TestManager
from hc.core.base.models.managers.objects.blacklistevent_om import BlacklistEventManager
from hc.core.base.models.managers.objects.testlog_om import TestLogManager
from hc.core.base.models.managers.functions import test_fm
from hc.core.utils.generic.class_func import custom_import

from datetime import datetime
import time

## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## GLOBAL BASE CLASSES
##
## *GlobalOptionBase
##

class GlobalOptionBase(models.Model):
  """Global option.

  Stores global options for an app in a key/value fashion.

  Attributes:
      id: integer for the primary key.
      option_name: string for the option name (unique).
      option_value: longer string for the option value.
      mtime: last modification time of the object.
  """
  __metaclass__ = MetaCreator

  COLORS = {
    'enabled': 'green',
    'disabled': 'red',
    'warning': 'yellow',
  }

  ACTIONS = {
    'enabled': 'disable',
    'disabled':'enable',
    'warning': 'enable',
  }

  id            = models.AutoField(primary_key=True)
  option_name   = models.CharField(unique=True, max_length=255)
  option_value  = models.CharField(max_length=2047, blank=True)
  mtime         = models.DateTimeField(auto_now=True)

  def __unicode__(self):
    return '%s: %s' % (self.option_name, self.option_value)

  @classmethod
  def get_autoexclusion_status(cls):
    """Reports the autoexclusion status.

    Reports the autoexclusion status by returning a dictionary with the following fields:
      - status: string with the status definition.
      - last_site: last site excluded (Site object).
      - last_timestamp: last exclusion time.
      - last_pass: timestamp of the last autoexclusion run.
      - action: action to take (enable, disable) in function of the current status.
      - color: suggested color of the status (for reports).

    Arguments:
        cls: is the class object to process, in this case GlobalOption.
    Returns:
        the dictionary specified above.
    """
    app  = cls.__module__.split('.')[1]
    be = custom_import('hc.%s.models.BlacklistEvent' % app)
    status = {}

    try:
      status['status'] = cls.objects.get(option_name='autoexclusion_status').option_value
      status['last_pass'] = datetime.fromtimestamp(float(cls.objects.get(option_name='autoexclusion_last_timestamp').option_value))
      status['color'] = cls.COLORS[status['status']]
      status['action'] = cls.ACTIONS[status['status']]
      status['last_site'], status['last_timestamp'] = be.get_last_excluded_site()
      status['author'] = cls.objects.get(option_name='autoexclusion_author').option_value
    except cls.DoesNotExist:
      status['status'] = 'unknown'
      status['last_pass'] = None
      status['color'] = 'gray'
      status['action'] = 'enable'
      status['last_site'], status['last_timestamp'] = None, None
      status['author'] = None

    return status

  @classmethod
  def disable_autoexclusion(cls, user=None):
    """Disables the autoexclusion globally.

    Sets or adds the global option 'autoexclusion_status' with a value of 'disabled'
    and does the same processing with the 'autoexclusion_last_timestamp' option.

    Arguments:
        cls: is the class object to process, in this case GlobalOption.
    """
    cls.change_autoexclusion('disabled', user=user)

  @classmethod
  def enable_autoexclusion(cls, user=None):
    """Enables the autoexclusion globally.

    Sets or adds the global option 'autoexclusion_status' with a value of 'enabled'
    and does the same processing with the 'autoexclusion_last_timestamp' option.

    Arguments:
        cls: is the class object to process, in this case GlobalOption.
    """
    cls.change_autoexclusion('enabled', user=user)

  @classmethod
  def change_autoexclusion(cls, status, user=None):
    """Changes the status of the autoexclusion.

    Sets the new status of the autoexclusion and the timestamp for the change. This
    timestamp is a local epoch string, used for simplicity. Be careful when reading.

    Arguments:
        cls: is the class object to process, in this case GlobalOption.
        status: (str) the new status, must be 'disabled' or 'enabled'
    """
    if status not in ('enabled', 'disabled'):
      raise ValueError('Status for autoexclusion must be disabled or enabled')
    cls.set_option('autoexclusion_status', status)
    cls.set_option('autoexclusion_last_timestamp', str(int(time.time())))
    if user:
      cls.set_option('autoexclusion_author', user)

  @classmethod
  def set_option(cls, option_name, option_value, forced=False):
    """Sets the value for an option.

    Will update or create a new option value for the given option_name.

    Arguments:
        cls: is the class object to process, in this case GlobalOption.
        option_name: name for the option, must be unique.
        option_value: value (str) for the option.
        forced: force the setting the new option whether is chaning or not.

    Returns:
        True if the option was changed, False if not.
    """
    try:
      option = cls.objects.get(option_name=option_name)
      if option.option_value != option_value or forced:
        option.option_value = option_value
        option.save()
        return True
      return False
    except cls.MultipleObjectsReturned:
      raise ValueError('The option is corrupted (multiple values)')
    except cls.DoesNotExist:
      cls(option_name=option_name, option_value=option_value).save()
      return True

  class Meta:
    abstract = True
    db_table = u'global_option'

## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## SIMPLE BASE CLASSES
##
## *AlarmBase
## *BackendBase
## *CloudBase
## *CloudOptionBase
## *DspatternBase
## *FileBase
## *GangaBinBase
## *HostBase
## *InputTypeBase
## *MetricPermBase
## *TestOptionBase
##

class AlarmBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  name        = models.CharField(unique=True, max_length=255)
  description = models.CharField(max_length=2047, blank=True)
  mtime       = models.DateTimeField(auto_now=True)

  def __unicode__(self):
    return '%s'%self.name

  class Meta:
    abstract = True
    db_table = u'alarm'

class BackendBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  name        = models.CharField(unique=True, max_length=255)
  description = models.CharField(max_length=2047, blank=True)
  mtime       = models.DateTimeField(auto_now=True)

  # Functions manager: -> hc.core.base.models.managers.functions.backend_fm
  # Admin manager    : -> hc.core.base.models.managers.admin.backend_am

  def __unicode__(self):
    return '%s'%self.name

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(BackendBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'backend'

class CloudBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  code        = models.CharField(unique=True, max_length=63)
  name        = models.CharField(unique=True, max_length=255)
  description = models.CharField(max_length=2047, blank=True)
  mtime       = models.DateTimeField(auto_now=True)

  # Functions manager: -> hc.core.base.models.managers.functions.cloud_fm
  # Admin manager    : -> hc.core.base.models.managers.admin.cloud_am

  def __unicode__(self):
    return '%s'%self.name

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now() 
#    super(CloudBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'cloud'
    ordering = ['code']

class CloudOptionBase(models.Model):
  __metaclass__ = MetaCreator

  id           = models.AutoField(primary_key=True)
  option_name  = models.CharField(max_length=63, blank=True)
  option_value = models.TextField(blank=True)
  mtime       = models.DateTimeField(auto_now=True)

  #cloud     -> hc.core.base.models.keys.fk.generator.generateFK('Cloud','CloudOption','cloud',{})

  class Meta:
    abstract = True
    db_table = u'cloud_option'
    #unique_together -> hc.core.base.models.keys.relation.UNIQUE_TOGETHER_DIC

class DspatternBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  pattern     = models.CharField(unique=True, max_length=255)
  description = models.CharField(max_length=2047, blank=True)
  mtime       = models.DateTimeField(auto_now=True)

  def __unicode__(self):
    return '%s'%self.pattern

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(DspatternBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'dspattern'

class GangaBinBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  path        = models.CharField(unique=True,max_length=255)
  description = models.CharField(max_length=2047, blank=True)
  mtime       = models.DateTimeField(auto_now=True)

  def __unicode__(self):
    return '%s'%self.path

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(GangaBinBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'gangabin'

class HostBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  name        = models.CharField(unique=True, max_length=255)
  description = models.CharField(max_length=2047, blank=True)
  loadavg1m   = models.FloatField(default=0)
  active      = models.BooleanField()
  mtime       = models.DateTimeField(auto_now=True)

  def __unicode__(self):
    return '%s'%self.name

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(HostBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'host'

class InputTypeBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  type        = models.CharField(unique=True,max_length=255)
  description = models.CharField(max_length=2047, blank=True)
  mtime       = models.DateTimeField(auto_now=True)

  def __unicode__(self):
    return '%s'%self.type

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(InputTypeBase,self).save()
#    return 1

  class	Meta:
    abstract = True
    db_table = u'inputtype'

class JobTemplateBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  path        = models.CharField(unique=True, max_length=255)
  description = models.CharField(max_length=2047, blank=True)
  mtime       = models.DateTimeField(auto_now=True)

  def __unicode__(self):
    return '%s'%self.path

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(JobTemplateBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'jobtemplate'

class MetricPermBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  name        = models.CharField(unique=True, max_length=255)
  description = models.CharField(max_length=2047, blank=True)
  mtime       = models.DateTimeField(auto_now=True)

  #index        -> hc.core.base.models.keys.m2m.generator.generateM2M('MetricType','MetricPerm','index',{})
  #summary      -> hc.core.base.models.keys.m2m.generator.generateM2M('MetricType','MetricPerm','persite',{})
  #pertab       -> hc.core.base.models.keys.m2m.generator.generateM2M('MetricType','MetricPerm','permetric',{})
  #cron_allowed -> hc.core.base.models.keys.m2m.generator.generateM2M('MetricType','MetricPerm','cron_allowed',{})

  def __unicode__(self):
    return '%s'%self.name

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(MetricPermBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'metricperm'

class OptionFileBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  path        = models.CharField(unique=True, max_length=255)
  description = models.CharField(max_length=2047, blank=True)
  mtime       = models.DateTimeField(auto_now=True)

  def __unicode__(self):
    return '%s'%self.path

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(OptionFileBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'optionfile'

class TestOptionBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  name        = models.CharField(max_length=255)
  config      = models.CharField(max_length=2047,blank=True)
  submit      = models.CharField(max_length=2047,blank=True)
  report      = models.CharField(max_length=2047,blank=True)
  description = models.CharField(max_length=2047,blank=True)
  mtime       = models.DateTimeField(auto_now=True)

  def __unicode__(self):
    return '%s'%self.name

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(TestOptionBase,self).save()
#    return 1
 
  class	Meta:
    abstract = True
    db_table = u'testoption'

class UserCodeBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  path        = models.CharField(unique=True, max_length=255)
  description = models.CharField(max_length=2047, blank=True)
  mtime       = models.DateTimeField(auto_now=True)

  def __unicode__(self):
    return '%s'%self.path

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(UserCodeBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'usercode'

## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## SITE BASE CLASSES
##
## *SiteBase
## *SiteOptionBase
##

class SiteBase(models.Model):
  __metaclass__ = MetaCreator

  CLASS_CHOICES = (
    (u'analysis', u'analysis'),
    (u'production', u'production'),
    (u'hybrid', u'hybrid'),
    (u'test', u'test'),
  )

  id             = models.AutoField(primary_key=True)
  name           = models.CharField(unique=True,max_length=255)
  alternate_name = models.CharField(max_length=511, blank=True)
  description    = models.CharField(max_length=2047, blank=True)
  ddm            = models.CharField(max_length=511, blank=True)
  enabled        = models.BooleanField(blank=True)
  queue          = models.CharField(max_length=511, blank=True)
  monitoring_link= models.CharField(max_length=2047, blank=True)
  mtime          = models.DateTimeField(auto_now=True)
  real_name      = models.CharField(max_length=255, blank=True)
  category       = models.CharField(choices = CLASS_CHOICES, max_length = 31, db_column='class')

  #cloud     -> hc.core.base.models.keys.fk.generator.generateFK('Cloud','Site','cloud',{})
  #backend   -> hc.core.base.models.kays.fk.generator.generateFK('Backend','Site','backend',{})

  # Functions manager: -> hc.core.base.models.managers.functions.site_fm

  def __unicode__(self):
    return '%s'%self.name

  def site_type(self):
    # By default, say analysis. Apps should redefine if not.
    return 'analysis'

  def ssb_name(self):
    # By default, say the site name. Apps should redefine if not.
    return self.name

  class Meta:
    abstract = True
    db_table = u'site'
    ordering = ['name']


class SiteOptionBase(models.Model):
  __metaclass__ = MetaCreator

  id           = models.AutoField(primary_key=True)
  option_name  = models.CharField(max_length=63, blank=True)
  option_value = models.TextField(blank=True)
  mtime       = models.DateTimeField(auto_now=True)
  
  #site     -> hc.core.base.models.keys.fk.generator.generateFK('Site','SiteOption','site',{})

  @classmethod
  def set_option(cls, site, option_name, option_value, forced=False):
    """Sets the value for an option.

    Will update or create a new option value for the given option_name.

    Arguments:
        cls: is the class object to process, in this case GlobalOption.
        site: site to search for the option.
        option_name: name for the option, must be unique.
        option_value: value (str) for the option.
        forced: force the setting the new option whether is chaning or not.

    Returns:
        True if the option was changed, False if not.
    """
    try:
      option = cls.objects.get(site=site, option_name=option_name)
      if option.option_value != option_value or forced:
        option.option_value = option_value
        option.save()
        return True
      return False
    except cls.MultipleObjectsReturned:
      raise ValueError('The option is corrupted (multiple values)')
    except cls.DoesNotExist:
      cls(site=site, option_name=option_name, option_value=option_value).save()
      return True

  class Meta:
    abstract = True
    db_table = u'site_option'
    #unique_together -> hc.core.base.models.keys.relation.UNIQUE_TOGETHER_DIC


## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## TEMPLATE BASE CLASSES
##
## *TemplateBase
## *TemplateBackendBase
## *TemplateCloudBase
## *TemplateDspatternBase
## *TemplateHostBase
## *TemplateSiteBase
## *TemplateUserBase
##

class TemplateBase(models.Model):
  __metaclass__ = MetaCreator

  CATEGORY_CHOICES = (
    (u'functional', u'functional'),
    (u'stress', u'stress'),
  )
  
  PROCESSING_CLASS_CHOICES = (
    (u'analysis', u'analysis'),
    (u'production', u'production'),
  )

  id                 = models.AutoField(primary_key=True)
  category           = models.CharField(choices = CATEGORY_CHOICES, max_length = 31)
  description        = models.CharField(max_length=255)
  active             = models.BooleanField()  
  lifetime           = models.IntegerField(default=0)
  output_dataset     = models.CharField(max_length = 1023, default='')
  extraargs          = models.CharField(max_length=1023, blank=True)
  mtime              = models.DateTimeField(auto_now=True)
  is_golden          = models.BooleanField(default=0,blank=True)
  obsolete           = models.BooleanField(default=0,blank=True)
  period             = models.IntegerField(default=0)
  type               = models.CharField(blank=True, max_length = 31)
  processing_class   = models.CharField(choices = PROCESSING_CLASS_CHOICES, max_length = 31)
  quality            = models.CharField(blank=True, max_length = 31)
  processing_meta    = models.CharField(blank=True, max_length = 31)

  #jobtemplate      -> hc.core.base.models.keys.fk.generator.generateFK('JobTemplate','Template','jobtemplate',{})
  #usercode         -> hc.core.base.models.keys.fk.generator.generateFK('UserCode','Template','usercode',{})
  #optionfile       -> hc.core.base.models.keys.fk.generator.generateFK('OptionFile','Template','option_file',{})
  #metricperm       -> hc.core.base.models.keys.fk.generator.generateFK('MetricPermission','Template','metricperm',{})
  #gangabin         -> hc.core.base.models.keys.fk.generator.generateFK('GangaBin','Template','gangabin',{})
  #inputtype        -> hc.core.base.models.keys.fk.generator.generateFK('Inputtype','Template','inputtype',{})
  #testoption       -> hc.core.base.models.keys.fk.generator.generateFK('TestOption','Template','testoption',{})

  # Functions manager: -> hc.core.base.models.managers.functions.template_fm
  # Admin manager    : -> hc.core.base.models.managers.admin.template_am

  def __unicode__(self):
    return '%s (%s) - %s'%(self.id,self.category,self.description)

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(TemplateBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'template'
    ordering = ['-id']

class TemplateBackendBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  resubmit_enabled      = models.BooleanField(default=True)
  resubmit_force        = models.BooleanField()
  num_datasets_per_bulk = models.IntegerField(default=1, db_column='num_datasets_per_bulk')
  min_queue_depth       = models.IntegerField(default=0, db_column='min_queue_depth')
  max_running_jobs      = models.IntegerField(default=1, db_column='max_running_jobs')
  mtime       = models.DateTimeField(auto_now=True)

  #backend   -> hc.core.base.models.keys.fk.generator.generateFK('Backend','TemplateBackend','backend',{})
  #template  -> hc.core.base.models.keys.fk.generator.generateFK('Template','TemplateBackend','template',{})

  def __unicode__(self):
    return '%s - %s'%(self.template,self.backend)

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(TemplateBackendBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'template_backend'
    #unique_together -> hc.core.base.models.keys.relation.UNIQUE_TOGETHER_DIC

class TemplateCloudBase(models.Model):
  __metaclass__ = MetaCreator

  id                    = models.AutoField(primary_key=True)
  resubmit_enabled      = models.BooleanField(default=True)
  resubmit_force        = models.BooleanField()
  num_datasets_per_bulk = models.IntegerField(default=1, db_column='num_datasets_per_bulk')
  min_queue_depth       = models.IntegerField(default=0, db_column='min_queue_depth')
  max_running_jobs      = models.IntegerField(default=1, db_column='max_running_jobs')
  mtime                 = models.DateTimeField(auto_now=True)

  #cloud               -> hc.core.base.models.keys.fk.generator.generateFK('Cloud','TemplateCloud','cloud',{})
  #template            -> hc.core.base.models.keys.fk.generator.generateFK('Template','TemplateCloud','template',{})

  def __unicode__(self):
    return '%s - %s'%(self.template,self.cloud)

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(TemplateCloudBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'template_cloud'
    #unique_together -> hc.core.base.models.fk.relation.UNIQUE_TOGETHER_DIC   
    
class TemplateDspatternBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  mtime       = models.DateTimeField(auto_now=True)

  #dspattern -> hc.core.base.models.keys.fk.generator.generateFK('Dspattern','TemplateDspattern','dspattern',{})
  #template  -> hc.core.base.models.keys.fk.generator.generateFK('Template','TemplateDspattern','template',{})

  def __unicode__(self):
    return '%s - %s'%(self.template,self.dspattern)

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(TemplateDspatternBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'template_dspattern'
    #unique_together -> hc.core.base.models.keys.relation.UNIQUE_TOGETHER_DIC

class TemplateHostBase(models.Model):
  __metaclass__ = MetaCreator

  id         = models.AutoField(primary_key=True)
  mtime      = models.DateTimeField(auto_now=True)

  #host     -> hc.core.base.models.keys.fk.generator.generateFK('Host','TemplateHost','host',{})
  #template -> hc.core.base.models.keys.fk.generator.generateFK('Template','TemplateHost','template',{})

  def __unicode__(self):
    return '%s - %s'%(self.template,self.host)

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(TemplateHostBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'template_host'
    #unique_together -> hc.core.base.models.keys.relation.UNIQUE_TOGETHER_DIC

class TemplateSiteBase(models.Model):
  __metaclass__ = MetaCreator

  id                    = models.AutoField(primary_key=True)
  resubmit_enabled      = models.BooleanField(default=True)
  resubmit_force        = models.BooleanField()
  num_datasets_per_bulk = models.IntegerField(default=1, db_column='num_datasets_per_bulk')
  min_queue_depth       = models.IntegerField(default=0, db_column='min_queue_depth')
  max_running_jobs      = models.IntegerField(default=1, db_column='max_running_jobs')
  mtime                 = models.DateTimeField(auto_now=True)

  #site                -> hc.core.base.models.keys.fk.generator.generateFK('Site','TemplateSite','site',{})
  #template            -> hc.core.base.models.keys.fk.generator.generateFK('Template','TemplateSite','template',{})

  def __unicode__(self):
    return '%s - %s'%(self.template,self.site)

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(TemplateSiteBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'template_site'
    #unique_together -> hc.core.base.models.keys.relation.UNIQUE_TOGETHER_DIC

class TemplateSiteAlarmBase(models.Model):
  __metaclass__ = MetaCreator

  id                    = models.AutoField(primary_key=True)
  active                = models.BooleanField(default=True)
  actions               = models.CharField(max_length = 1023, blank=True, null=True)
  mtime                 = models.DateTimeField(auto_now=True)

  #alarm               -> hc.core.base.models.keys.fk.generator.generateFK('Alarm','TemplateSiteAlarm','alarm',{})
  #site                -> hc.core.base.models.keys.fk.generator.generateFK('Site','TemplateSiteAlarm','site',{})
  #test                -> hc.core.base.models.keys.fk.generator.generateFK('Template','TemplateSiteAlarm','template',{})

  def __unicode__(self):
    return '%s - %s'%(self.test,self.site)

  class Meta:
    abstract = True
    db_table = u'template_site_alarm'
    #unique_together -> hc.core.base.models.keys.relation.UNIQUE_TOGETHER_DIC

class TemplateUserBase(models.Model):
  __metaclass__ = MetaCreator

  id    = models.AutoField(primary_key=True)
#  user = models.IntegerField()
  user  = models.CharField(max_length=127)
  mtime = models.DateTimeField(auto_now=True)

  #template -> hc.core.base.models.keys.fk.generator.generateFK('Template','TemplateUser','template',{})

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(TemplateUserBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'template_user'
    #unique_together -> hc.core.base.models.keys.relation.UNIQUE_TOGETHER_DIC


## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## TEST BASE CLASSES
##
## *TestBase
## *TestBackendBase
## *TestCloudBase
## *TestDspatternBase
## *TestHostBase
## *TestLogBase
## *TestSiteBase
## *TestSiteAlarmBase
## *TestStateBase
## *TestUserBase
##

class TestBase(models.Model):
  __metaclass__ = MetaCreator

  STATE_CHOICES = (
    (u'draft', u'draft'),
    (u'unapproved', u'unapproved'),
    (u'tobescheduled', u'tobescheduled'),
    (u'scheduled', u'scheduled'),
    (u'submitting', u'submitting'),
    (u'running', u'running'),
    (u'completed', u'completed'),
    (u'error', u'error'),
    (u'cancelled',u'cancelled'),
  )

  VERSION_CHOICES = (
    (4,4),
    )    

  objects = TestManager()

  id                 = models.AutoField(primary_key=True)
  description        = models.CharField(max_length=255,blank=True,help_text="Introduce a human readable description.")
  starttime          = models.DateTimeField(help_text="Starttime MUST be AL LEAST 30 minutes from now.")
  endtime            = models.DateTimeField()  
  output_dataset     = models.CharField(max_length = 1023, default='')
  version            = models.IntegerField(choices = VERSION_CHOICES, default = 4)
  pause              = models.BooleanField(default=0,blank=True)
  state              = models.CharField(blank=True,default='draft',choices = STATE_CHOICES, max_length = 31)
  atjobid            = models.IntegerField(default = 0, null=True, blank=True)
  extraargs          = models.CharField(max_length=1023, blank=True, help_text="Add extra instructions to the ganga command.")
  cloned             = models.IntegerField(default = 0, blank=True)
  mtime              = models.DateTimeField(auto_now=True)
  is_golden          = models.BooleanField(default=0,blank=True)
  period             = models.IntegerField(default=0)
  processing_meta    = models.CharField(blank=True, max_length = 31)

  #jobtemplate      -> hc.core.base.models.keys.fk.generator.generateFK('JobTemplate','Test','jobtemplate',{})
  #usercode         -> hc.core.base.models.keys.fk.generator.generateFK('UserCode','Test','usercode',{})
  #optionfile       -> hc.core.base.models.keys.fk.generator.generateFK('OptionFile','Test','option_file',{})
  #template         -> hc.core.base.models.keys.fk.generator.generateFK('Template','Test','template',{})
  #host             -> hc.core.base.models.keys.fk.generator.generateFK('Host','Test','host',{'null':True})
  #metricperm       -> hc.core.base.models.keys.fk.generator.generateFK('MetricPermission','Test','metricperm',{})
  #gangabin         -> hc.core.base.models.keys.fk.generator.generateFK('GangaBin','Test','gangabin',{})
  #inputtype        -> hc.core.base.models.keys.fk.generator.generateFK('Inputtype','Test','inputtype',{})
  #testoption       -> hc.core.base.models.keys.fk.generator.generateFK('TestOption','Test','testoption',{})

  # Functions manager: -> hc.core.base.models.managers.functions.test_fm
  # Admin manager    : -> hc.core.base.models.managers.admin.test_am

  def __unicode__(self):
    return '%s'%self.id

  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
    self.starttime = self.starttime.replace(second=0)
    self.endtime = self.endtime.replace(second=0)
    # Set the test on draft status to prevent race condition when saving all the
    # test takes more than 0.
    if self.state == 'tobescheduled':
        final_state = self.state
        self.state = 'draft'
    else:
        final_state = self.state

    #If we want default behaviour:
    if args and args[0].has_key('default') and args[0]['default']:
      self.state = final_state  
      super(TestBase,self).save()
      return 1

    #If we are clonning, we do NOT copy TestInlines.
    clone = False
    if args and args[0].has_key('clone') and args[0]['clone']:
      clone = True

    # No test can be saved with active functional template
    if self.template.category == 'functional' and self.template.active:
      try:
        end = self.starttime >= now()
      except:
        end = self.starttime >= datetime.now()
      if end:
        return 0

    test = custom_import('hc.'+self._meta.app_label+'.models.Test')
    t    = test.objects.filter(id = self.id)

    dontsave = ['error','completed']
    if final_state in dontsave:
      self.state = final_state
      super(TestBase, self).save()
      return 0

    # Voodoo time: the t[0].id==id is doing magic, do not delete !!!
    if t and t[0].id==self.id:

      # DON'T BE UGLY WITH THIS !
      # You can overwrite from python commands any test option,
      # but keep in mind what are you doing.

      try:
        jobtemplate = self.jobtemplate
      except:
        jobtemplate = t[0].jobtemplate

      try:
        usercode = self.usercode
      except:
        usercode = t[0].usercode

      try:
        optionfile = self.optionfile
      except:
        optionfile = t[0].optionfile

      try:
        inputtype = self.inputtype
      except:
        inputtype = t[0].inputtype

      try:
        output_dataset = self.output_dataset
      except:
        output_dataset = t[0].output_dataset

      try:
        testoption = self.testoption
      except:
        testoption = t[0].testoption

      try:
        template = self.template
      except:
        template = t[0].template

      try:
        gangabin = self.gangabin
      except:
        gangabin = t[0].gangabin

      try:
        extraargs = self.extraargs
      except:
        extraargs = t[0].extraargs

      try:
        is_golden = self.is_golden
      except:
        is_golden = t[0].is_golden

      try:
        period = self.period
      except:
        period = t[0].period

      try:
        metricperm = self.metricperm
      except:
        metricperm = t[0].metricperm

      try:
        processing_meta = self.processing_meta
      except:
        processing_meta = t[0].processing_meta

      self.jobtemplate     = jobtemplate
      self.usercode        = usercode
      self.optionfile      = optionfile
      self.inputtype       = inputtype
      self.output_dataset  = output_dataset
      self.testoption      = testoption
      self.template        = template
      self.gangabin        = gangabin
      self.extraargs       = extraargs
      self.is_golden       = is_golden
      self.period          = period
      self.metricperm      = metricperm
      self.processing_meta = processing_meta

      self.state = final_state
      super(TestBase, self).save()

    else:
      #It's a new test, copy from template.
      obj = self.template

      self.jobtemplate      = obj.jobtemplate
      self.usercode         = obj.usercode
      self.optionfile       = obj.optionfile
      self.inputtype        = obj.inputtype
      self.metricperm       = obj.metricperm
      self.output_dataset   = obj.output_dataset
      self.testoption       = obj.testoption
      self.gangabin         = obj.gangabin
      self.extraargs        = obj.extraargs
      self.is_golden        = obj.is_golden
      self.period           = obj.period
      self.processing_meta  = obj.processing_meta

      super(TestBase, self).save()

        # Create summary test registry. 
        # Next updates will be done by a script.
      summary_test = custom_import('hc.'+self._meta.app_label+'.models.SummaryTest')
      summary_test = summary_test(test=self)
      summary_test.save()

#      else:
#        #We cannot create tests in error or completed states.
#        return 0

      if not clone:
        #HOSTS (ONLY UPDATED ON CREATION)
        test_host      = custom_import('hc.'+self._meta.app_label+'.models.TestHost')
        template_hosts = self.template.getTemplateHosts_for_template.all()
        for th in template_hosts:
          th = test_host(host = th.host, test=self)
          th.save()

        #SITES (ONLY UPDATED ON CREATION)
        test_site      = custom_import('hc.'+self._meta.app_label+'.models.TestSite')
        template_sites = self.template.getTemplateSites_for_template.all()

        for ts in template_sites:
          ts = test_site(site = ts.site, 
                      test=self,
                      resubmit_enabled=ts.resubmit_enabled,
                      resubmit_force=ts.resubmit_force,
                      num_datasets_per_bulk=ts.num_datasets_per_bulk,
                      min_queue_depth=ts.min_queue_depth,
                      max_running_jobs=ts.max_running_jobs)
          ts.save({'new':True})

        #DSPATTERNS (ONLY UPDATED ON CREATION)
        test_dspattern      = custom_import('hc.'+self._meta.app_label+'.models.TestDspattern')
        template_dspatterns = self.template.getTemplateDspatterns_for_template.all()
        for td in template_dspatterns:
          td = test_dspattern(dspattern = td.dspattern, test=self)
          td.save()

        #USERS (ONLY UPDATED ON CREATION)
        test_user      = custom_import('hc.'+self._meta.app_label+'.models.TestUser')
        template_users = self.template.getTemplateUsers_for_template.all()
        for tu in template_users:
          tu = test_user(user = tu.user, test=self)
          tu.save()

        #CLOUDS (ONLY UPDATED ON CREATION)
        test_cloud = custom_import('hc.'+self._meta.app_label+'.models.TestCloud')
        template_clouds = self.template.getTemplateClouds_for_template.all()
        for tc in template_clouds:
          tc = test_cloud(cloud = tc.cloud, 
                          test=self, 
                          resubmit_enabled=tc.resubmit_enabled,
                          resubmit_force=tc.resubmit_force,
                          num_datasets_per_bulk=tc.num_datasets_per_bulk,
                          min_queue_depth=tc.min_queue_depth,
                          max_running_jobs=tc.max_running_jobs)
          tc.save()

        #BACKENDS (ONLY UPDATED ON CREATION)
        test_backend = custom_import('hc.'+self._meta.app_label+'.models.TestBackend')
        template_backends = self.template.getTemplateBackends_for_template.all()
        for tb in template_backends:
          tb = test_backend(backend = tb.backend, 
                            test=self,
                            resubmit_enabled=tb.resubmit_enabled,
                            resubmit_force=tb.resubmit_force,
                            num_datasets_per_bulk=tb.num_datasets_per_bulk,
                            min_queue_depth=tb.min_queue_depth,
                            max_running_jobs=tb.max_running_job)
          tb.save()

        #ALARMS (ONLY UPDATED ON CREATION)
        test_site_alarm = custom_import('hc.'+self._meta.app_label+'.models.TestSiteAlarm')
        template_site_alarms = self.template.getTemplateSiteAlarms_for_template.all()

        for tsa in template_site_alarms:
          tsa = test_site_alarm(site=tsa.site, 
                                test=self,
                                alarm=tsa.alarm,
                                active=tsa.active,
                                actions=tsa.actions)
          tsa.save({'new':True})

      # Storing the final state.
      self.state = final_state
      super(TestBase, self).save()

      return 1

  class Meta:
    abstract = True
    db_table = u'test'
    ordering = ['-id']

class TestBackendBase(models.Model):
  __metaclass__ = MetaCreator

  id        = models.AutoField(primary_key=True)
  resubmit_enabled      = models.BooleanField(default=True)
  resubmit_force        = models.BooleanField()
  num_datasets_per_bulk = models.IntegerField(default=1, db_column='num_datasets_per_bulk')
  min_queue_depth       = models.IntegerField(default=0, db_column='min_queue_depth')
  max_running_jobs      = models.IntegerField(default=1, db_column='max_running_jobs')
  mtime     = models.DateTimeField(auto_now=True)

  #backend -> hc.core.base.models.keys.fk.generator.generateFK('Backend','TestBackend','backend',{})
  #test    -> hc.core.base.models.keys.fk.generator.generateFK('Test','TestBackend','test',{})

  def __unicode__(self):
    return '%s - %s'%(self.test,self.backend)

  def save(self,*args,**kwargs):

    sites = self.backend.getSites_for_backend.all()

    for site in sites:
    
      dic = {'new':False}

      #If test is functional and site not enabled, we skip
      if self.test.template.category == 'functional' and not site.enabled:
        continue 

      ts = self.test.getTestSites_for_test.filter(site=site)
      if ts:
        ts = ts[0]
      else:
        test_site = custom_import('hc.'+self.test._meta.app_label+'.models.TestSite')
        ts = test_site(test=self.test,site=site)
        dic['new'] = True  

      ts.resubmit_enabled = self.resubmit_enabled
      ts.resubmit_force = self.resubmit_force
      ts.num_datasets_per_bulk = self.num_datasets_per_bulk
      ts.min_queue_depth = self.min_queue_depth
      ts.max_running_jobs = self.max_running_jobs

      ts.save(dic)

#    dontsave = ['error','completed']
#    if self.test.state not in dontsave:
#    super(TestBackendBase, self).save()

    return 1

  class Meta:
    abstract = True
    db_table = u'test_backend'
    #unique_together -> hc.core.base.models.keys.relation.UNIQUE_TOGETHER_DIC

class TestCloudBase(models.Model):
  __metaclass__ = MetaCreator

  id                    = models.AutoField(primary_key=True)
  resubmit_enabled      = models.BooleanField(default=True)
  resubmit_force        = models.BooleanField()
  num_datasets_per_bulk = models.IntegerField(default=1, db_column='num_datasets_per_bulk')
  min_queue_depth       = models.IntegerField(default=0, db_column='min_queue_depth')
  max_running_jobs      = models.IntegerField(default=1, db_column='max_running_jobs')
  mtime                 = models.DateTimeField(auto_now=True)

  #cloud               -> hc.core.base.models.keys.fk.generator.generateFK('Cloud','TestCloud','cloud',{})
  #test                -> hc.core.base.models.keys.fk.generator.generateFK('Test','TestCloud','test',{})

  def __unicode__(self):
    return '%s - %s'%(self.test,self.cloud)

  def save(self,*args,**kwargs):
    self.mtime = now()

    sites = self.cloud.getSites_for_cloud.all()

    for site in sites:

      dic = {'new':False}

      #If test is functional and site not enabled, we skip
      if self.test.template.category == 'functional' and not site.enabled:
        continue

      ts = self.test.getTestSites_for_test.filter(site=site)
      if ts:
        ts = ts[0]
      else:
        test_site = custom_import('hc.'+self._meta.app_label+'.models.TestSite')
        ts = test_site(test=self.test,site=site)
        dic['new'] = True

      ts.resubmit_enabled = self.resubmit_enabled
      ts.resubmit_force = self.resubmit_force
      ts.num_datasets_per_bulk = self.num_datasets_per_bulk
      ts.min_queue_depth = self.min_queue_depth
      ts.max_running_jobs = self.max_running_jobs

      ts.save(dic)

#    dontsave = ['error','completed']
#    if self.test.state not in dontsave:
#    super(TestCloudBase, self).save()

    return 1

  class Meta:
    abstract = True
    db_table = u'test_cloud'
    #unique_together -> hc.core.base.models.keys.relation.UNIQUE_TOGETHER_DIC

class TestDspatternBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  mtime       = models.DateTimeField(auto_now=True)

  #dspattern -> hc.core.base.models.keys.fk.generator.generateFK('Dspattern','TestDspattern','dspattern',{})
  #test      -> hc.core.base.models.keys.fk.generator.generateFK('Test','TestDspattern','test',{})

  def __unicode__(self):
    return '%s - %s'%(self.test,self.dspattern)

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#
#    dontsave = ['error','completed']
#    if self.test.state not in dontsave:
#      super(TestDspatternBase, self).save()

    return 1

  class Meta:
    abstract = True
    db_table = u'test_dspattern'
    #unique_together -> hc.core.base.models.keys.relation.UNIQUE_TOGETHER_DIC

class TestHostBase(models.Model):
  __metaclass__ = MetaCreator

  id     = models.AutoField(primary_key=True)
  mtime  = models.DateTimeField(auto_now=True)

  #host -> hc.core.base.models.keys.fk.generator.generateFK('Host','Test','host',{})
  #test -> hc.core.base.models.keys.fk.generator.generateFK('Test','TestHost','test',{})

  def __unicode__(self):
    return '%s - %s'%(self.test,self.host)

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#
#    dontsave = ['error','completed']
#    if self.test.state not in dontsave:
#      super(TestHostBase, self).save()

    return 1

  class Meta:
    abstract = True
    db_table = u'test_host'
    #unique_together -> hc.core.base.models.keys.relation.UNIQUE_TOGETHER_DIC

class TestLogBase(models.Model):
  __metaclass__ = MetaCreator

  SEVERITY_CHOICES = (
    (u'blacklisting', u'blacklisting'),
    (u'whitelisting', u'whitelisting'),
    (u'debug',u'debug'),
    (u'warning',u'warning'),
    (u'error',u'error'),
    (u'testinfo',u'testinfo'),
    (u'queuecontrol',u'queuecontrol'),
    (u'other',u'other'),
  )

  objects = TestLogManager()

  id          = models.AutoField(primary_key=True)
  comment     = models.CharField(max_length=4097)
  severity    = models.CharField(choices = SEVERITY_CHOICES, max_length = 15, default='other')
  user        = models.CharField(max_length = 31)
  mtime       = models.DateTimeField(auto_now=True)

  #test -> hc.core.base.models.keys.fk.generator.generateFK('Test','TestLog','test',{})

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(TestLogBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'test_log'

class TestSiteBase(models.Model):
  __metaclass__ = MetaCreator

  id                    = models.AutoField(primary_key=True)
  resubmit_enabled      = models.BooleanField(default=True)
  resubmit_force        = models.BooleanField()
  num_datasets_per_bulk = models.IntegerField(default=1, db_column='num_datasets_per_bulk')
  min_queue_depth       = models.IntegerField(default=0, db_column='min_queue_depth')
  max_running_jobs      = models.IntegerField(default=1, db_column='max_running_jobs')
  mtime                 = models.DateTimeField(auto_now=True)

  #site                -> hc.core.base.models.keys.fk.generator.generateFK('Site','TestSite','site',{})
  #test                -> hc.core.base.models.keys.fk.generator.generateFK('Test','TestSite','test',{})

  def __unicode__(self):
    return '%s - %s'%(self.test,self.site)

  def save(self,*args,**kwargs):

    #If we are clonning...
    default = False
    if args and args[0].has_key('default') and args[0]['default']:
      default = True

    #For functional tests, only enabled sites are taken into account.
    if self.site.enabled or self.test.template.category == 'stress' or default:

      #If we are clonning...
      clone = False
      if args and args[0].has_key('clone') and args[0]['clone']:
        clone = True

      #If we are creating...
      new = False
      if args and args[0].has_key('new') and args[0]['new']:
        new = True

      if not self.test.getTestSites_for_test.filter(site=self.site):
        new = True

      ## IMPORTANT ! 
      ## Check that this TestSite was not previously added by TestCloud or TestBackend
      overwrite = False
      test_site = self.test.getTestSites_for_test.filter(site=self.site)
      if test_site:
        test_site = test_site[0]
        test_site.resubmit_enabled      = self.resubmit_enabled
        test_site.resubmit_force        = self.resubmit_force
        test_site.num_datasets_per_bulk = self.num_datasets_per_bulk
        test_site.min_queue_depth       = self.min_queue_depth
        test_site.max_running_jobs      = self.max_running_jobs
#        test_site.save()
        try:
          super(TestSiteBase, test_site).save()
        except IntegrityError:
          pass
        overwrite = True

      if (clone or new) and not overwrite:

        super(TestSiteBase, self).save()

        summary_test_site = custom_import('hc.'+self._meta.app_label+'.models.SummaryTestSite')
        sts = summary_test_site(test=self.test,test_site=self)
        try:
          sts.save()
        except IntegrityError:
          pass

        summary_test = custom_import('hc.'+self._meta.app_label+'.models.SummaryTest')

        summary_test = summary_test.objects.filter(test=self.test)[0]
  
        if summary_test.sites:  
          summary_test.sites += ',%s'%(self.site.name)
          summary_test.nr_sites += 1
        else:
          summary_test.sites = self.site.name
          summary_test.nr_sites = 1

        if summary_test.clouds:
          if not self.site.cloud.code in summary_test.clouds:
            summary_test.clouds += ',%s'%(self.site.cloud.code)
            summary_test.nr_clouds += 1
        else:
          summary_test.clouds = self.site.cloud.code
          summary_test.nr_clouds = 1

        try:
          summary_test.save()
        except IntegrityError:
          pass

  def delete(self):

    #Update SummaryTest
    sts = self.test.getSummaryTests_for_test.all()
    if sts:
      st = sts[0]
      if st.sites:
        st.sites.replace('%s,'%(self.site.name),'')
        st.sites.replace('%s'%(self.site.name),'')
        st.nr_sites -= 1

        tss = self.test.getTestSites_for_test.filter(site__cloud=self.site.cloud)
        if len(tss) == 1:
          st.clouds.replace('%s,'%(self.site.cloud.code),'')
          st.clouds.replace('%s'%(self.site.cloud.code),'')
          st.nr_clouds -= 1

        st.save()

    super(TestSiteBase,self).delete()

  class Meta:
    abstract = True
    db_table = u'test_site'
    #unique_together -> hc.core.base.models.keys.relation.UNIQUE_TOGETHER_DIC

class TestSiteAlarmBase(models.Model):
  __metaclass__ = MetaCreator

  STATUS = (
    (u'empty',u'empty'),
    (u'failed', u'failed'),
    (u'passed', u'passed')
  )

  id                    = models.AutoField(primary_key=True)
  active                = models.BooleanField(default=True)
  status                = models.CharField(choices = STATUS, max_length = 15, default = 'empty')
  progress              = models.FloatField(default=0)
  log                   = models.CharField(max_length = 20000, blank=True, null=True)
  actions               = models.CharField(max_length = 1023, blank=True, null=True)
  mtime                 = models.DateTimeField(auto_now=True)

  #alarm               -> hc.core.base.models.keys.fk.generator.generateFK('Alarm','TestSiteAlarm','alarm',{})
  #site                -> hc.core.base.models.keys.fk.generator.generateFK('Site','TestSiteAlarm','site',{})
  #test                -> hc.core.base.models.keys.fk.generator.generateFK('Test','TestSiteAlarm','test',{})

  def __unicode__(self):
    return '%s - %s'%(self.test,self.site)

  def save(self,*args,**kwargs):
    # Clone or save the TestSiteAlarm object from the TemplateSiteAlarm...
    default = False
    if args and args[0].has_key('default') and args[0]['default']:
      default = True

    # Only copy data from enabled sites for functional tests. All on stress.
    if self.site.enabled or self.test.template.category == 'stress' or default:

      # Check if cloning
      clone = False
      if args and args[0].has_key('clone') and args[0]['default']:
        clone = True

      # Check if we are creating a new objects
      new = False
      if args and args[0].has_key('new') and args[0]['new']:
        new = True

      if not self.test.getTestSiteAlarms_for_test.filter(site=self.site,alarm=self.alarm):
        new = True

      ## IMPORTANT!
      ## Check that this TestSiteAlarm was not previously added
      overwrite = False
      test_site_alarm = self.test.getTestSiteAlarms_for_test.filter(site=self.site,alarm=self.alarm)
      if test_site_alarm:
        # Actions to copy data to an *existing* test_site_alarm
        test_site_alarm = test_site_alarm[0]
        test_site_alarm.active = self.active
        test_site_alarm.status = self.status
        test_site_alarm.progress = self.progress
        test_site_alarm.log = self.log
        test_site_alarm.actions = self.actions
        super(TestSiteAlarmBase, test_site_alarm).save()
        overwrite = True

      if (clone or new) and not overwrite:
        super(TestSiteAlarmBase, self).save()

  class Meta:
    abstract = True
    db_table = u'test_site_alarm'
    #unique_together -> hc.core.base.models.keys.relation.UNIQUE_TOGETHER_DIC

class TestStateBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  ganga_jobid = models.IntegerField()
  copied      = models.BooleanField()
  mtime       = models.DateTimeField(auto_now=True)

  #test -> hc.core.base.models.keys.fk.generator.generateFK('Test','TestState','test',{})

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#
#    dontsave = ['error','completed']
#    if self.test.state not in dontsave:
#      super(TestStateBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'test_state'
    #unique_together -> hc.core.base.models.keys.relation.UNIQUE_TOGETHER_DIC

class TestUserBase(models.Model):
  __metaclass__ = MetaCreator

  id     = models.AutoField(primary_key=True)
#  user  = models.IntegerField()
  user   = models.CharField(max_length=127)
  mtime  = models.DateTimeField(auto_now=True)

  #test -> hc.core.base.models.keys.fk.generator.generateFK('Test','TestUser','test',{})

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#
#    dontsave = ['error','completed']
#    if self.test.state not in dontsave:
#      super(TestUserBase, self).save()
#
#    return 1

  class Meta:
    abstract = True
    db_table = u'test_user'
    #unique_together -> hc.core.base.models.keys.relation.UNIQUE_TOGETHER_DIC

## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## RESULT BASE CLASSES
##
## *ResultBase
## *ResultMetricBase
##

class ResultBase(models.Model):
  __metaclass__ = MetaCreator

  id             = models.AutoField(primary_key=True)
  ganga_jobid    = models.IntegerField()
  ganga_subjobid = models.IntegerField()
  ganga_status   = models.CharField(max_length=3,null=True)

  ganga_time_1   = models.DateTimeField(null=True)
  ganga_time_2   = models.DateTimeField(null=True)
  ganga_time_3   = models.DateTimeField(null=True)
  ganga_time_4   = models.DateTimeField(null=True)
  ganga_time_5   = models.DateTimeField(null=True)

  start_time     = models.DateTimeField(null=True)
  submit_time    = models.DateTimeField(null=True)
  stop_time      = models.DateTimeField(null=True)

  backendID      = models.CharField(max_length=511,null=True)
  reason         = models.CharField(max_length=4095,null=True)

  fixed          = models.BooleanField()

  mtime          = models.DateTimeField(auto_now=True)

  #site         -> hc.core.base.models.keys.fk.generator.generateFK('Site','Result','site',{})
  #test         -> hc.core.base.models.keys.fk.generator.generateFK('Test','Result','test',{})
  #r_metric     -> hc.core.base.models.keys.fk.generator.generateFK('ResultMetric','Result','r_metric',{})

#  Not needed unicode
#  def __unicode__(self):

#  def save(self,*args,**kwargs):
#    super(ResultBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'result'
    #unique_together -> hc.core.base.models.keys.relation.UNIQUE_TOGETHER_DIC

#class ResultMetricBase(models.Model):
#  __metaclass__ = MetaCreator
#
#  id = models.AutoField(primary_key=True)
#  mtime = UnixTimestampField(auto_created=True)
#
#  #result -> hc.core.base.models.keys.fk.generator.generateFK('Result','ResultMetric','result',{})
#
##  Not needed unicode
##  def __unicode__(self):
#
#  class Meta:
#    abstract = True
#    db_table = u'result_metric'


## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## METRIC BASE CLASSES
##
## *MetricTypeBase
## *MetricBase
## *MetricPerm
## [*GlobalMetricBase]
## *SiteMetricBase
## *TestMetricBase
##

class MetricTypeBase(models.Model):
  __metaclass__ = MetaCreator

  PLOT_TYPE = (
    (u'Hist', u'Hist'),
    (u'Pie',  u'Pie'),
    (u'Time', u'Time'),
  )

  id          = models.AutoField(primary_key=True)
  name        = models.CharField(unique=True, max_length=255)
  title       = models.CharField(max_length=255)
  type        = models.CharField(choices = PLOT_TYPE, max_length=15)
  description = models.CharField(max_length=2047,blank=True)
  rate        = models.BooleanField(default=False)
  scale_max   = models.FloatField(blank=True,null=True)
  scale_min   = models.FloatField(blank=True,null=True)
  hist_bins   = models.IntegerField(blank=True,null=True)
  mtime       = models.DateTimeField(auto_now=True)

  def __unicode__(self):
    return '%s'%(self.title)

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(MetricTypeBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'metric_type'

class MetricBase(models.Model):
  __metaclass__ = MetaCreator

  id            = models.AutoField(primary_key=True)
  url           = models.CharField(max_length=4095)
  mtime         = models.DateTimeField(auto_now=True)

  #metric_type -> hc.core.base.models.keys.fk.generator.generateFK('MetricType','Metric','metric_type',{})

  def __unicode__(self):
    return '%s - %s'%(self.id,self.metric_type)   

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(MetricBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'metric'



#class MetricPermissionBase(models.Model):
#  __metaclass__ = MetaCreator

#  id             = models.AutoField(primary_key=True)
#  name           = models.CharField(unique=True, max_length=255)
#  description    = models.CharField(max_length=4095)
#  mtime          = models.DateTimeField()

#  #index        -> hc.core.base.models.keys.m2m.generator.generateM2M('MetricType','MetricPermission','index',{})
#  #summary      -> hc.core.base.models.keys.m2m.generator.generateM2M('MetricType','MetricPermission','persite',{})
#  #pertab       -> hc.core.base.models.keys.m2m.generator.generateM2M('MetricType','MetricPermission','permetric',{})
#  #cron_allowed -> hc.core.base.models.keys.m2m.generator.generateM2M('MetricType','MetricPermission','cron_allowed',{})

#  def __unicode__(self):
#    return '%s'%(self.description)

#  def save(self):
#    self.mtime = datetime.now()
#    super(MetricPermissionBase, self).save()

#  class Meta:
#    abstract = True
#    db_table = u'metricpermission'

#class GlobalMetricBase(models.Model):
#  __metaclass__ = MetaCreator
#
#  class Meta:
#    abstract = True
#    db_table = u'global_metric'

class SiteMetricBase(models.Model):
  __metaclass__ = MetaCreator

  id       = models.AutoField(primary_key=True)
  mtime    = models.DateTimeField(auto_now=True)

  #metric -> hc.core.base.models.keys.fk.generator.generateFK('Metric','SiteMetric','metric',{})
  #site   -> hc.core.base.models.keys.fk.generator.generateFK('Site','SiteMetric','site',{})  
  #test   -> hc.core.base.models.keys.fk.generator.generateFK('Test','SiteMetric','test',{})

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(SiteMetricBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'site_metric'

class TestMetricBase(models.Model):
  __metaclass__ = MetaCreator

  id       = models.AutoField(primary_key=True)
  mtime    = models.DateTimeField(auto_now=True)

  #metric -> hc.core.base.models.keys.fk.generator.generateFK('Metric','TestMetric','metric',{})
  #test   -> hc.core.base.models.keys.fk.generator.generateFK('Test','TestMetric','test',{})

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(TestMetricBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'test_metric'


## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## USAGE BASE CLASSES
##
## *UsgSlice
## *UsgSite
##

class UsgSliceBase(models.Model):
  __metaclass__ = MetaCreator

  TYPE_CHOICES = (
    (u'daily',u'daily'),
    (u'weekly',u'weekly'),
    (u'monthly',u'monthly'),
    (u'yearly',u'yearly'),
  )

  id    = models.AutoField(primary_key=True)
  type  = models.CharField(choices = TYPE_CHOICES, max_length = 31)
  start = models.DateTimeField()
  end   = models.DateTimeField()
  mtime = models.DateTimeField(auto_now=True)

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(UsgSliceBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'usg_slice'


class UsgSiteBase(models.Model):
  __metaclass__ = MetaCreator

  TYPE_CHOICES = (
    (u'daily',u'daily'),
    (u'weekly',u'weekly'),
    (u'monthly',u'monthly'),
    (u'yearly',u'yearly'),
  )

  id        = models.AutoField(primary_key=True)
  time      = models.DateTimeField()
  running   = models.IntegerField(default=0)
  completed = models.IntegerField(default=0)
  failed    = models.IntegerField(default=0)
  type      = models.CharField(choices = TYPE_CHOICES, max_length = 31)
  mtime     = models.DateTimeField(auto_now=True)

  #site    -> hc.core.base.models.keys.fk.generator.generateFK('Site','UsgSite','site',{})

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(UsgSiteBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'usg_site'


## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## SUMMARY BASE CLASSES
##
## *SummaryMetricBase
## *SummaryTestBase
## [*SummarySiteBase]
## *SummaryRobot
## *SummaryEvolution
##

#class SummaryMetricBase(models.Model):
#  __metaclass__ = MetaCreator
#
#  id = models.AutoField(primary_key=True)
#  mtime = UnixTimestampField(auto_created=True)
#
##  Not needed unicode
##  def __unicode__(self):
#
#  class Meta:
#    abstract = True
#    db_table = u'summary_metric'

class SummaryTestBase(models.Model):
  __metaclass__ = MetaCreator

  id              = models.AutoField(primary_key=True)
  intermediumtime = models.DateTimeField(null=True)

  sites           = models.CharField(max_length=4095,null=True)
  clouds          = models.CharField(max_length=511,null=True)

  nr_sites        = models.IntegerField(default=0,null=True)
  nr_clouds       = models.IntegerField(default=0,null=True)

  submitted       = models.IntegerField(default=0,null=True)
  running         = models.IntegerField(default=0,null=True)
  completed       = models.IntegerField(default=0,null=True)
  failed          = models.IntegerField(default=0,null=True)
  total           = models.IntegerField(default=0,null=True)

  c_cf            = models.FloatField(default=0,null=True)
  c_t             = models.FloatField(default=0,null=True)
  f_t             = models.FloatField(default=0,null=True)

  mtime           = models.DateTimeField(auto_now=True)

  #test          -> hc.core.base.models.keys.fk.generator.generateFK('Test','SummaryTest','test',{})
#  #s_metric -> hc.core.base.models.keys.fk.generator.generateFK('SummaryMetric','SummaryTest','s_metric',{})

#  Not needed unicode
#  def __unicode__(self):

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(SummaryTestBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'summary_test'

class SummaryTestSiteBase(models.Model):
  __metaclass__ = MetaCreator

  id              = models.AutoField(primary_key=True)
  intermediumtime = models.DateTimeField(null=True)

  submitted       = models.IntegerField(default=0,null=True)
  running         = models.IntegerField(default=0,null=True)
  completed       = models.IntegerField(default=0,null=True)
  failed          = models.IntegerField(default=0,null=True)
  total           = models.IntegerField(default=0,null=True)

  c_cf            = models.FloatField(default=0,null=True)
  c_t             = models.FloatField(default=0,null=True)
  f_t             = models.FloatField(default=0,null=True)

  mtime           = models.DateTimeField(auto_now=True)

  #test          -> hc.core.base.models.keys.fk.generator.generateFK('Test','SummaryTestSite','test',{})
  #site          -> hc.core.base.models.keys.fk.generator.generateFK('Site','SummaryTestSite','site',{})
#  #s_metric -> hc.core.base.models.keys.fk.generator.generateFK('SummaryMetric','SummaryTestSite','s_metric',{})

#  Not needed unicode
#  def __unicode__(self):

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(SummaryTestSiteBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'summary_test_site'

class SummaryRobotBase(models.Model):
  __metaclass__ = MetaCreator

  id             = models.AutoField(primary_key=True)
  completed      = models.IntegerField(default=0)
  failed         = models.IntegerField(default=0)
  total          = models.IntegerField(default=0)
  efficiency     = models.FloatField(default=0)
  efficiencyNorm = models.FloatField(default=0)
  errorrate      = models.FloatField(default=0)
  errorrateNorm  = models.FloatField(default=0)
  day            = models.DateField()
  mtime          = models.DateTimeField(auto_now=True)

  #site     -> hc.core.base.models.keys.fk.generator.generateFK('Site','SummaryRobot','site',{})

#  Not needed unicode
#  def __unicode__(self):

#  def save(self,*args,**kwargs):
#    self.mtime = datetime.now()
#    super(SummaryRobotBase, self).save()
#    return 1

  class Meta:
    abstract = True
    db_table = u'summary_robot'
    #unique_together -> hc.core.base.models.keys.relation.UNIQUE_TOGETHER_DIC

class SummaryEvolutionBase(models.Model):
  __metaclass__ = MetaCreator

  id             = models.AutoField(primary_key=True)
  submitted      = models.IntegerField(default=0)
  running        = models.IntegerField(default=0)
  completed      = models.IntegerField(default=0)
  failed         = models.IntegerField(default=0)
  total          = models.IntegerField(default=0)
  time           = models.DateTimeField()
  mtime          = models.DateTimeField(auto_now=True)

  #test     -> hc.core.base.models.keys.fk.generator.generateFK('Test','SummaryEvolution','test',{})
  #site     -> hc.core.base.models.keys.fk.generator.generateFK('Site','SummaryEvolution','site',{})

  class Meta:
    abstract = True
    db_table = u'summary_evolution'
    #unique_together -> hc.core.base.models.keys.relation.UNIQUE_TOGETHER_DIC

## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## BLACKLISTING BASE CLASSES
##
## *BlacklistEventBase
##

class BlacklistEventBase(models.Model):
  __metaclass__ = MetaCreator

  EVENT_CHOICES = (
    (u'blacklist', u'blacklist'),
    (u'whitelist', u'whitelist'),
  )
  
  objects     = BlacklistEventManager()

  id          = models.AutoField(primary_key=True)
  event       = models.CharField(choices = EVENT_CHOICES, max_length = 31)
  reason      = models.CharField(max_length=4095)
  timestamp   = models.DateTimeField()
  mtime       = models.DateTimeField(auto_now=True)
  external    = models.BooleanField()

  #test       -> hc.core.base.models.keys.fk.generator.generateFK('Test','BlacklistEvent','test',{})
  #site       -> hc.core.base.models.keys.fk.generator.generateFK('Site','BlacklistEvent','site',{})

  @classmethod
  def get_last_excluded_site(cls):
    """Get the last autoexcluded site.

    Returns the site name of the last autoexcluded site, with the timestamp of
    the exclusion.

    Returns:
        a tuple of (site, timestamp), being site a Site object and timestamp a
        datetime object.
    """
    event = cls.objects.select_related('site').filter(event='blacklist').order_by('-timestamp')[0]
    return (event.site, event.timestamp)

  class Meta:
    abstract = True
    db_table = u'blacklist_event'

## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## MESSAGE BUS CLASSES
##
## *MessageBusEventBase
##

class MessageBusEventBase(models.Model):
  __metaclass__ = MetaCreator

  MBUS_TYPES = (
    (u'error', u'error'),
    (u'incident', u'incident'),
    (u'blacklist', u'blacklist'),
    (u'robot', u'robot'),
    (u'alert', u'alert'),
  )

  id          = models.AutoField(primary_key=True)
  type        = models.CharField(choices=MBUS_TYPES, max_length=31)
  timestamp   = models.DateTimeField()
  mtime       = models.DateTimeField(auto_now=True)
  processed   = models.BooleanField(default=False)
  extra       = PickledObjectField(null=True)

  #test        -> hc.core.base.models.keys.fk.generator.generateFK('Test','MessageBusEvent','test',{})
  #site        -> hc.core.base.models.keys.fk.generator.generateFK('Site','MessageBusEvent','site',{})

  class Meta:
    abstract = True
    db_table = u'message_bus_event'
