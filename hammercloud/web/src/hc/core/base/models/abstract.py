from django.db import models

from hc.core.base.models.metacreator import MetaCreator
from hc.core.base.models.managers.objects.test_om import TestManager
from hc.core.utils.generic.class_func import custom_import

from datetime import datetime

## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## SIMPLE BASE CLASSES
##
## *BackendBase
## *CloudBase
## *DspatternBase
## *FileBase
## *GangaBinBase
## *HostBase
## *InputTypeBase
## *MetricPermBase
## *TestOptionBase
##

class BackendBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  name        = models.CharField(unique=True, max_length=255)
  description = models.CharField(max_length=2047, blank=True)
  mtime       = models.DateTimeField()

  # Functions manager: -> hc.core.base.models.managers.functions.backend_fm
  # Admin manager    : -> hc.core.base.models.managers.admin.backend_am

  def __unicode__(self):
    return '%s'%self.name

  def save(self):
    self.mtime = datetime.now()
    super(BackendBase, self).save()

  class Meta:
    abstract = True
    db_table = u'backend'

class CloudBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  code        = models.CharField(unique=True, max_length=63)
  name        = models.CharField(unique=True, max_length=255)
  description = models.CharField(max_length=2047, blank=True)
  mtime       = models.DateTimeField()

  # Functions manager: -> hc.core.base.models.managers.functions.cloud_fm
  # Admin manager    : -> hc.core.base.models.managers.admin.cloud_am

  def __unicode__(self):
    return '%s'%self.name

  def save(self):
    self.mtime = datetime.now() 
    super(CloudBase, self).save()

  class Meta:
    abstract = True
    db_table = u'cloud'
    ordering = ['code']

class DspatternBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  pattern     = models.CharField(unique=True, max_length=255)
  description = models.CharField(max_length=2047, blank=True)
  mtime       = models.DateTimeField()

  def __unicode__(self):
    return '%s'%self.pattern

  def save(self):
    self.mtime = datetime.now()
    super(DspatternBase, self).save()

  class Meta:
    abstract = True
    db_table = u'dspattern'

class GangaBinBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  path        = models.CharField(unique=True,max_length=255)
  description = models.CharField(max_length=2047, blank=True)
  mtime       = models.DateTimeField()

  def __unicode__(self):
    return '%s'%self.path

  def save(self):
    self.mtime = datetime.now()
    super(GangaBinBase, self).save()

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
  mtime       = models.DateTimeField()

  def __unicode__(self):
    return '%s'%self.name

  def save(self):
    self.mtime = datetime.now()
    super(HostBase, self).save()

  class Meta:
    abstract = True
    db_table = u'host'

class InputTypeBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  type        = models.CharField(unique=True,max_length=255)
  description = models.CharField(max_length=2047, blank=True)
  mtime       = models.DateTimeField()

  def __unicode__(self):
    return '%s'%self.type

  def save(self):
    self.mtime = datetime.now()
    super(InputTypeBase,self).save()

  class	Meta:
    abstract = True
    db_table = u'inputtype'

class JobTemplateBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  path        = models.CharField(unique=True, max_length=255)
  description = models.CharField(max_length=2047, blank=True)
  mtime       = models.DateTimeField()

  def __unicode__(self):
    return '%s'%self.path

  def save(self):
    self.mtime = datetime.now()
    super(JobTemplateBase, self).save()

  class Meta:
    abstract = True
    db_table = u'jobtemplate'

class MetricPermBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  name        = models.CharField(unique=True, max_length=255)
  description = models.CharField(max_length=2047, blank=True)
  mtime       = models.DateTimeField()

  #index        -> hc.core.base.models.keys.m2m.generator.generateM2M('MetricType','MetricPerm','index',{})
  #summary      -> hc.core.base.models.keys.m2m.generator.generateM2M('MetricType','MetricPerm','persite',{})
  #pertab       -> hc.core.base.models.keys.m2m.generator.generateM2M('MetricType','MetricPerm','permetric',{})
  #cron_allowed -> hc.core.base.models.keys.m2m.generator.generateM2M('MetricType','MetricPerm','cron_allowed',{})


  def __unicode__(self):
    return '%s'%self.description

  def save(self):
    self.mtime = datetime.now()
    super(MetricPermBase, self).save()

  class Meta:
    abstract = True
    db_table = u'metricperm'

class OptionFileBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  path        = models.CharField(unique=True, max_length=255)
  description = models.CharField(max_length=2047, blank=True)
  mtime       = models.DateTimeField()

  def __unicode__(self):
    return '%s'%self.path

  def save(self):
    self.mtime = datetime.now()
    super(OptionFileBase, self).save()

  class Meta:
    abstract = True
    db_table = u'optionfile'

class TestOptionBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  config      = models.CharField(max_length=2047)
  submit      = models.CharField(max_length=2047)
  report      = models.CharField(max_length=2047)
  description = models.CharField(max_length=2047, blank=True)
  mtime       = models.DateTimeField()

  def __unicode__(self):
    return '%s'%self.description

  def save(self):
    self.mtime = datetime.now()
    super(TestOptionBase,self).save()

  class	Meta:
    abstract = True
    db_table = u'testoption'

class UserCodeBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  path        = models.CharField(unique=True, max_length=255)
  description = models.CharField(max_length=2047, blank=True)
  mtime       = models.DateTimeField()

  def __unicode__(self):
    return '%s'%self.path

  def save(self):
    self.mtime = datetime.now()
    super(UserCodeBase, self).save()

  class Meta:
    abstract = True
    db_table = u'usercode'

## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## SITE BASE CLASSES
##
## *SiteBase
##

class SiteBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  name        = models.CharField(unique=True,max_length=255)
  description = models.CharField(max_length=2047, blank=True)
  ddm         = models.CharField(max_length=511, blank=True)
  enabled     = models.BooleanField(blank=True)
  queue       = models.CharField(max_length=511, blank=True)
  mtime       = models.DateTimeField()

  #cloud     -> hc.core.base.models.keys.fk.generator.generateFK('Cloud','Site','cloud',{})
  #backend   -> hc.core.base.models.kays.fk.generator.generateFK('Backend','Site','backend',{})

  # Functions manager: -> hc.core.base.models.managers.functions.site_fm

  def __unicode__(self):
    return '%s'%self.name

  def save(self):
    self.mtime = datetime.now()
    super(SiteBase, self).save()

  class Meta:
    abstract = True
    db_table = u'site'
    ordering = ['name']


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

  id                 = models.AutoField(primary_key=True)
  category           = models.CharField(choices = CATEGORY_CHOICES, max_length = 31)
  description        = models.CharField(max_length=255)
  active             = models.BooleanField()  
  lifetime           = models.IntegerField(default=0)
  output_dataset     = models.CharField(max_length = 1023, default='')
  extraargs          = models.CharField(max_length=1023, blank=True)
  mtime              = models.DateTimeField()

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

  def save(self):
    self.mtime = datetime.now()
    super(TemplateBase, self).save()

  class Meta:
    abstract = True
    db_table = u'template'
    ordering = ['-id']

class TemplateBackendBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  mtime       = models.DateTimeField()

  #backend   -> hc.core.base.models.keys.fk.generator.generateFK('Backend','TemplateBackend','backend',{})
  #template  -> hc.core.base.models.keys.fk.generator.generateFK('Template','TemplateBackend','template',{})

  def __unicode__(self):
    return '%s - %s'%(self.template,self.backend)

  def save(self):
    self.mtime = datetime.now()
    super(TemplateBackendBase, self).save()

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
  mtime                 = models.DateTimeField()

  #cloud               -> hc.core.base.models.keys.fk.generator.generateFK('Cloud','TemplateCloud','cloud',{})
  #template            -> hc.core.base.models.keys.fk.generator.generateFK('Template','TemplateCloud','template',{})

  def __unicode__(self):
    return '%s - %s'%(self.template,self.cloud)

  def save(self):
    self.mtime = datetime.now()
    super(TemplateCloudBase, self).save()

  class Meta:
    abstract = True
    db_table = u'template_cloud'
    #unique_together -> hc.core.base.models.fk.relation.UNIQUE_TOGETHER_DIC   
    
class TemplateDspatternBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  mtime       = models.DateTimeField()

  #dspattern -> hc.core.base.models.keys.fk.generator.generateFK('Dspattern','TemplateDspattern','dspattern',{})
  #template  -> hc.core.base.models.keys.fk.generator.generateFK('Template','TemplateDspattern','template',{})

  def __unicode__(self):
    return '%s - %s'%(self.template,self.dspattern)

  def save(self):
    self.mtime = datetime.now()
    super(TemplateDspatternBase, self).save()

  class Meta:
    abstract = True
    db_table = u'template_dspattern'
    #unique_together -> hc.core.base.models.keys.relation.UNIQUE_TOGETHER_DIC

class TemplateHostBase(models.Model):
  __metaclass__ = MetaCreator

  id         = models.AutoField(primary_key=True)
  mtime      = models.DateTimeField()

  #host     -> hc.core.base.models.keys.fk.generator.generateFK('Host','TemplateHost','host',{})
  #template -> hc.core.base.models.keys.fk.generator.generateFK('Template','TemplateHost','template',{})

  def __unicode__(self):
    return '%s - %s'%(self.template,self.host)

  def save(self):
    self.mtime = datetime.now()
    super(TemplateHostBase, self).save()

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
  mtime                 = models.DateTimeField()

  #site                -> hc.core.base.models.keys.fk.generator.generateFK('Site','TemplateSite','site',{})
  #template            -> hc.core.base.models.keys.fk.generator.generateFK('Template','TemplateSite','template',{})

  def __unicode__(self):
    return '%s - %s'%(self.template,self.site)

  def save(self):
    self.mtime = datetime.now()
    super(TemplateSiteBase, self).save()

  class Meta:
    abstract = True
    db_table = u'template_site'
    #unique_together -> hc.core.base.models.keys.relation.UNIQUE_TOGETHER_DIC

class TemplateUserBase(models.Model):
  __metaclass__ = MetaCreator

  id    = models.AutoField(primary_key=True)
#  user = models.IntegerField()
  user  = models.CharField(max_length=127)
  mtime = models.DateTimeField()

  #template -> hc.core.base.models.keys.fk.generator.generateFK('Template','TemplateUser','template',{})

  def save(self):
    self.mtime = datetime.now()
    super(TemplateUserBase, self).save()

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
## *TestSiteBase
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
  description        = models.CharField(max_length=255)
  starttime          = models.DateTimeField()
  endtime            = models.DateTimeField()  
  output_dataset     = models.CharField(max_length = 1023, default='')
  version            = models.IntegerField(choices = VERSION_CHOICES, default = 4)
  pause              = models.BooleanField()
  state              = models.CharField(blank=True,default='draft',choices = STATE_CHOICES, max_length = 31)
  atjobid            = models.IntegerField(default = 0, null=True, blank=True)
  extraargs          = models.CharField(max_length=1023, blank=True)
  cloned             = models.IntegerField(default = 0, null=True, blank=True)
  mtime              = models.DateTimeField()

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

  def save(self):
    self.mtime = datetime.now()

    # No test can be saved with active functional template
    if self.template.category == 'functional' and self.template.active and self.starttime >= datetime.now():
      return 0

    test = custom_import('hc.'+self._meta.app_label+'.models.Test')
    t    = test.objects.filter(id = self.id)

    dontsave = ['error','completed']
    if t:
      if t[0].state in dontsave:
        t[0].state = self.state
        super(TestBase, t[0]).save()
      else:
        super(TestBase, self).save()

    if not t:
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
      self.description      = obj.description

#    #Gangabin is editable, so the user decission is over the test_template.
#    if gangabin:
#      self.gangabin = gangabin 
#    #Extraargs is editable, so the user decission is over the test_template.
#    if extraargs != self.extraargs:
#      self.extraargs = extraargs
      
      if self.state not in dontsave:
        super(TestBase, self).save()
      else:
        pass
        #We cannot create tests in error or completed states.

    #dontsave = ['error','completed']
    #if self.state not in dontsave:
    #  super(TestBase, self).save()   

    #HOSTS (ONLY UPDATED ON CREATION)
    if not t:
      test_host      = custom_import('hc.'+self._meta.app_label+'.models.TestHost')
      template_hosts = self.template.getTemplateHosts_for_template.all()
      for th in template_hosts:
        th = test_host(host = th.host, test=self)
        th.save()

    #SITES (ONLY UPDATED ON CREATION)
    if not t:
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
        ts.save()

    #DSPATTERNS (ONLY UPDATED ON CREATION)
    if not t:
      test_dspattern      = custom_import('hc.'+self._meta.app_label+'.models.TestDspattern')
      template_dspatterns = self.template.getTemplateDspatterns_for_template.all()
      for td in template_dspatterns:
        td = test_dspattern(dspattern = td.dspattern, test=self)
        td.save()

    #USERS (ONLY UPDATED ON CREATION)
    if not t:
      test_user      = custom_import('hc.'+self._meta.app_label+'.models.TestUser')
      template_users = self.template.getTemplateUsers_for_template.all()
      for tu in template_users:
        tu = test_user(user = tu.user, test=self)
        tu.save()


  class Meta:
    abstract = True
    db_table = u'test'
    ordering = ['-id']

class TestBackendBase(models.Model):
  __metaclass__ = MetaCreator

  id        = models.AutoField(primary_key=True)
  mtime     = models.DateTimeField()

  #backend -> hc.core.base.models.keys.fk.generator.generateFK('Backend','TestBackend','backend',{})
  #test    -> hc.core.base.models.keys.fk.generator.generateFK('Test','TestBackend','test',{})

  def __unicode__(self):
    return '%s - %s'%(self.test,self.backend)

  def save(self):

    sites = self.backend.getSites_for_backend.all()

    for site in sites:
      ts = self.test.getTestSites_for_test.filter(site=site)
      if ts:
        ts = ts[0]
      else:
        test_site = custom_import('hc.'+t._meta.app_label+'.TestSite')
        ts = test_site(test=self.test,site=site)

      ts.resubmit_enabled = self.resubmit_enabled
      ts.resubmit_force = self.resubmit_force
      ts.num_datasets_per_bulk = self.num_datasets_per_bulk
      ts.min_queue_depth = self.min_queue_depth
      ts.max_running_jobs = self.max_running_jobs

      ts.save()

    dontsave = ['error','completed']
    if self.test.state not in dontsave:
      super(TestBackendBase, self).save()

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
  mtime                 = models.DateTimeField()

  #cloud               -> hc.core.base.models.keys.fk.generator.generateFK('Cloud','TestCloud','cloud',{})
  #test                -> hc.core.base.models.keys.fk.generator.generateFK('Test','TestCloud','test',{})

  def __unicode__(self):
    return '%s - %s'%(self.test,self.cloud)

  def save(self):
    self.mtime = datetime.now()

    sites = self.cloud.getSites_for_cloud.all()

    for site in sites:
      ts = self.test.getTestSites_for_test.filter(site=site)
      if ts:
        ts = ts[0]
      else:
        test_site = custom_import('hc.'+t._meta.app_label+'.TestSite')
        ts = test_site(test=self.test,site=site)

      ts.resubmit_enabled = self.resubmit_enabled
      ts.resubmit_force = self.resubmit_force
      ts.num_datasets_per_bulk = self.num_datasets_per_bulk
      ts.min_queue_depth = self.min_queue_depth
      ts.max_running_jobs = self.max_running_jobs

      ts.save()

    dontsave = ['error','completed']
    if self.test.state not in dontsave:
      super(TestCloudBase, self).save()

  class Meta:
    abstract = True
    db_table = u'test_cloud'
    #unique_together -> hc.core.base.models.keys.relation.UNIQUE_TOGETHER_DIC

class TestDspatternBase(models.Model):
  __metaclass__ = MetaCreator

  id          = models.AutoField(primary_key=True)
  mtime       = models.DateTimeField()

  #dspattern -> hc.core.base.models.keys.fk.generator.generateFK('Dspattern','TestDspattern','dspattern',{})
  #test      -> hc.core.base.models.keys.fk.generator.generateFK('Test','TestDspattern','test',{})

  def __unicode__(self):
    return '%s - %s'%(self.test,self.dspattern)

  def save(self):
    self.mtime = datetime.now()

    dontsave = ['error','completed']
    if self.test.state not in dontsave:
      super(TestDspatternBase, self).save()

  class Meta:
    abstract = True
    db_table = u'test_dspattern'
    #unique_together -> hc.core.base.models.keys.relation.UNIQUE_TOGETHER_DIC

class TestHostBase(models.Model):
  __metaclass__ = MetaCreator

  id     = models.AutoField(primary_key=True)
  mtime  = models.DateTimeField()

  #host -> hc.core.base.models.keys.fk.generator.generateFK('Host','Test','host',{})
  #test -> hc.core.base.models.keys.fk.generator.generateFK('Test','TestHost','test',{})

  def __unicode__(self):
    return '%s - %s'%(self.test,self.host)

  def save(self):
    self.mtime = datetime.now()

    dontsave = ['error','completed']
    if self.test.state not in dontsave:
      super(TestHostBase, self).save()

  class Meta:
    abstract = True
    db_table = u'test_host'
    #unique_together -> hc.core.base.models.keys.relation.UNIQUE_TOGETHER_DIC

class TestSiteBase(models.Model):
  __metaclass__ = MetaCreator

  id                    = models.AutoField(primary_key=True)
  resubmit_enabled      = models.BooleanField(default=True)
  resubmit_force        = models.BooleanField()
  num_datasets_per_bulk = models.IntegerField(default=1, db_column='num_datasets_per_bulk')
  min_queue_depth       = models.IntegerField(default=0, db_column='min_queue_depth')
  max_running_jobs      = models.IntegerField(default=1, db_column='max_running_jobs')
  mtime                 = models.DateTimeField()

  #site                -> hc.core.base.models.keys.fk.generator.generateFK('Site','TestSite','site',{})
  #test                -> hc.core.base.models.keys.fk.generator.generateFK('Test','TestSite','test',{})

  def __unicode__(self):
    return '%s - %s'%(self.test,self.site)

  def save(self):
    self.mtime = datetime.now()

    dontsave = ['error','completed']
    if self.test.state not in dontsave:
      super(TestSiteBase, self).save()

  class Meta:
    abstract = True
    db_table = u'test_site'
    #unique_together -> hc.core.base.models.keys.relation.UNIQUE_TOGETHER_DIC

class TestUserBase(models.Model):
  __metaclass__ = MetaCreator

  id     = models.AutoField(primary_key=True)
#  user  = models.IntegerField()
  user   = models.CharField(max_length=127)
  mtime  = models.DateTimeField()

  #test -> hc.core.base.models.keys.fk.generator.generateFK('Test','TestUser','test',{})

  def save(self):
    self.mtime = datetime.now()

    dontsave = ['error','completed']
    if self.test.state not in dontsave:
      super(TestUserBase, self).save()

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

  mtime          = models.DateTimeField()

  #site         -> hc.core.base.models.keys.fk.generator.generateFK('Site','Result','site',{})
  #test         -> hc.core.base.models.keys.fk.generator.generateFK('Test','Result','test',{})
  #r_metric     -> hc.core.base.models.keys.fk.generator.generateFK('ResultMetric','Result','r_metric',{})

#  Not needed unicode
#  def __unicode__(self):

  def save(self):
    self.mtime = datetime.now()
    super(ResultBase, self).save()

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
    (u'Pie', u'Pie')
  )

  id          = models.AutoField(primary_key=True)
  name        = models.CharField(unique=True, max_length=255)
  title       = models.CharField(max_length=255)
  type        = models.CharField(choices = PLOT_TYPE, max_length=15)
  description = models.CharField(max_length=2047) 
  mtime       = models.DateTimeField()

  def __unicode__(self):
    return '%s'%(self.title)

  def save(self):
    self.mtime = datetime.now()
    super(MetricTypeBase, self).save()

  class Meta:
    abstract = True
    db_table = u'metric_type'

class MetricBase(models.Model):
  __metaclass__ = MetaCreator

  id            = models.AutoField(primary_key=True)
  url           = models.CharField(max_length=4095)
  mtime         = models.DateTimeField()

  #metric_type -> hc.core.base.models.keys.fk.generator.generateFK('MetricType','Metric','metric_type',{})

  def __unicode__(self):
    return '%s - %s'%(self.id,self.metric_type)   

  def save(self):
    self.mtime = datetime.now()
    super(MetricBase, self).save()

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
  mtime    = models.DateTimeField()

  #metric -> hc.core.base.models.keys.fk.generator.generateFK('Metric','SiteMetric','metric',{})
  #site   -> hc.core.base.models.keys.fk.generator.generateFK('Site','SiteMetric','site',{})  
  #test   -> hc.core.base.models.keys.fk.generator.generateFK('Test','SiteMetric','test',{})

  def save(self):
    self.mtime = datetime.now()
    super(SiteMetricBase, self).save()

  class Meta:
    abstract = True
    db_table = u'site_metric'

class TestMetricBase(models.Model):
  __metaclass__ = MetaCreator

  id       = models.AutoField(primary_key=True)
  mtime    = models.DateTimeField()

  #metric -> hc.core.base.models.keys.fk.generator.generateFK('Metric','TestMetric','metric',{})
  #test   -> hc.core.base.models.keys.fk.generator.generateFK('Test','TestMetric','test',{})

  def save(self):
    self.mtime = datetime.now()
    super(TestMetricBase, self).save()

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
  mtime = models.DateTimeField()

  def save(self):
    self.mtime = datetime.now()
    super(UsgSliceBase, self).save()

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
  mtime     = models.DateTimeField()

  #site    -> hc.core.base.models.keys.fk.generator.generateFK('Site','UsgSite','site',{})

  def save(self):
    self.mtime = datetime.now()
    super(UsgSiteBase, self).save()

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
  s_t             = models.FloatField(default=0,null=True)
  r_t             = models.FloatField(default=0,null=True)
  f_t             = models.FloatField(default=0,null=True)

  mtime           = models.DateTimeField()

  #test          -> hc.core.base.models.keys.fk.generator.generateFK('Test','SummaryTest','test',{})
#  #s_metric -> hc.core.base.models.keys.fk.generator.generateFK('SummaryMetric','SummaryTest','s_metric',{})

#  Not needed unicode
#  def __unicode__(self):

  def save(self):
    self.mtime = datetime.now()
    super(SummaryTestBase, self).save()

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
  s_t             = models.FloatField(default=0,null=True)
  r_t             = models.FloatField(default=0,null=True)
  f_t             = models.FloatField(default=0,null=True)

  mtime           = models.DateTimeField()

  #test          -> hc.core.base.models.keys.fk.generator.generateFK('Test','SummaryTestSite','test',{})
  #test_site     -> hc.core.base.models.keys.fk.generator.generateFK('Site','SummaryTestSite','site',{})
#  #s_metric -> hc.core.base.models.keys.fk.generator.generateFK('SummaryMetric','SummaryTestSite','s_metric',{})

#  Not needed unicode
#  def __unicode__(self):

  def save(self):
    self.mtime = datetime.now()
    super(SummaryTestSiteBase, self).save()

  class Meta:
    abstract = True
    db_table = u'summary_test_site'

class SummaryRobotBase(models.Model):
  __metaclass__ = MetaCreator

  id         = models.AutoField(primary_key=True)
  efficiency = models.FloatField()
  mtime      = models.DateTimeField()

  #site     -> hc.core.base.models.keys.fk.generator.generateFK('Site','SummaryRobot','site',{'unique':True})

#  Not needed unicode
#  def __unicode__(self):

  def save(self):
    self.mtime = datetime.now()
    super(SummaryRobotBase, self).save()

  class Meta:
    abstract = True
    db_table = u'summary_robot'

