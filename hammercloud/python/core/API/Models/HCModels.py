from API.Models.BaseHCModel import BaseHCModel

import types

class TestHCModel( BaseHCModel ):
    
  def __init__( self,
                app,
                starttime,
                endtime,
                template,
                description = '',
                sites = [] ):
    
    self.app         = app
    self.starttime   = starttime
    self.endtime     = endtime
    self.template    = template
    self.description = description
    
    if not isinstance(sites,types.ListType):
      sites = [sites]   
    
    self.sites = sites
    
#from API.Models.BaseHCModel import BaseHCModel 
#
#import types
#
#'''
#  ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
#  ##
#  ## SIMPLE HC MODELS
#  ##
#  ## *AlarmHCModel
#  ## *BackendHCModel
#  ## *CloudHCModel
#  ## *CloudOptionHCModel
#  ## *DspatternHCModel
#  ## *GangaBinHCModel
#  ## *HostHCModel
#  ## *InputTypeHCModel
#  ## *JobTemplateHCModel
#  ## *MetricPermHCModel
#  ## *OptionFileHCModel
#  ## *TestOptionHCModel
#  ## *UserCodeHCModel
#  ##
#'''
#
#class AlarmHCModel( BaseHCModel ):
#    
#  type = 'alarm'
#  
#  def __init__( self,
#                name,
#                description = '' ):
#      
#    self.name        = name
#    self.description = description        
#
#class BackendHCModel( BaseHCModel ):
#    
#  type = 'backend'  
#    
#  def __init__( self,
#                name,
#                description = '' ):
#      
#    self.name        = name
#    self.description = description
#
#class CloudHCModel( BaseHCModel ):
#
#  type = 'cloud'
#
#  def __init__( self,
#                code,
#                name,
#                description = '',
#                cloud_option = [] ):
#  
#    self.code        = code
#    self.name        = name
#    self.description = description
#    
#    if not isinstance(cloud_option,types.ListType):
#      cloud_option = [cloud_option]   
#    
#    self.cloud_option = cloud_option
#
#    
#class CloudOptionHCModel( BaseHCModel ):
#    
#  type = 'cloud_option'  
#    
#  def __init( self,
#              option_name,
#              option_value,
#              cloud = None ):
#    
#    self.cloud        = cloud
#    self.option_name  = option_name
#    self.option_value = option_value          
#      
#class DspatternHCModel( BaseHCModel ):
#
#  type = 'dspattern' 
#
#  def __init__( self,
#                pattern,
#                description = '' ):
#    
#    self.pattern     = pattern
#    self.description = description
#    
#class GangaBinHCModel( BaseHCModel ):
#    
#  type = 'gangabin' 
#  
#  def __init__( self,
#                path,
#                description = ''):
#      
#    self.path        = path
#    self.description = description
#    
#class HostHCModel( BaseHCModel ):
#    
#  type = 'host'
#  
#  def __init__( self,
#                name,
#                active = 0,
#                loadavg1m = 0,
#                description = '' ):
#    
#    self.name        = name
#    self.active      = active
#    self.loadavg1m   = loadavg1m 
#    self.description = description
#    
#class InputTypeHCModel( BaseHCModel ):
#    
#  type = 'inputtype'
#  
#  def __init__( self,
#                type,
#                description = '' ):
#      
#    self.type        = type
#    self.description = description
#    
#class JobTemplateHCModel( BaseHCModel ):
#    
#  type = 'jobtemplate'
#  
#  def __init__( self,
#                path,
#                description = '' ):
#      
#    self.path        = path
#    self.description = description
#
#'''
#  MetricPermHCModel is incomplete
#''' 
#class MetricPermHCModel( BaseHCModel ):
#    
#  type = 'metricperm'
#  
#  def __init__( self,
#                name,
#                description = '' ):
#      
#    self.name        = name
#    self.description = description
#    
#class OptionFileHCModel( BaseHCModel ):
#    
#  type = 'optionfile'
#  
#  def __init__( self,
#                path,
#                description = '' ):
#      
#    self.path        = path
#    self.description = description        
#
#class TestOptionHCModel( BaseHCModel ):
#    
#  type = 'testoption'
#  
#  def __init__( self,
#                name,
#                config = '',
#                submit = '',
#                report = '',
#                description = '' ):  
#    
#    self.name        = name
#    self.config      = config
#    self.submit      = submit
#    self.report      = report
#    self.description = description
#                     
#class UserCodeHCModel( BaseHCModel ):
#    
#  type = 'usercode'
#  
#  def __init__( self,
#                path,
#                description = '' ):
#    
#    self.path        = path
#    self.description = description     
#
#
#'''
#  ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
#  ## 
#  ## SITE HC MODELS
#  ##
#  ## *SiteHCModel
#  ## *SiteOptionHCModel
#  ##
#'''  
#
#class SiteHCModel( BaseHCModel ):
#    
#  type = 'site'  
#    
#  def __init__( self,
#                name,
#                cloud,
#                backend,
#                ddm = '',
#                queue = '',
#                enabled = False,
#                description = '',
#                alternate_name = '',
#                site_option = [] ):
#
#    self.name           = name
#    self.cloud          = cloud
#    self.backend        = backend
#    self.ddm            = ddm
#    self.queue          = queue
#    self.enabled        = enabled   
#    self.description    = description        
#    self.alternate_name = alternate_name
#    
#    if not isinstance(site_option,types.ListType):
#      site_option = [site_option]   
#    
#    self.site_option = site_option
#
#
#class SiteOptionHCModel( BaseHCModel ):
#    
#  type = 'site_option'  
#    
#  def __init__( self,
#                option_name,
#                option_value,
#                site = None, ):
#      
#    self.site         = site
#    self.option_name  = option_name
#    self.option_value = option_value   
#
#    
#'''
#  ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
#  ##
#  ## TEMPLATE HC MODELS
#  ##
#  ## *TemplateHCModel
#  ## *TemplateBackendHCModel
#  ## *TemplateCloudHCModel
#  ## *TemplateDspatternHCModel
#  ## *TemplateHostHCModel
#  ## *TemplateSiteHCModel
#  ## *TemplateUserHCModel
#  ##
#'''       
#
#class TemplateHCModel( BaseHCModel ):
#    
#  type = 'template'
#  
#  template_inlines = ['backend','cloud','dspattern','host','site','user']
#  
#  def __init__( self, 
#                category,
#                jobtemplate,
#                inputtype,
#                usercode,
#                optionfile,
#                gangabin,
#                testoption,
#                metricperm,
#                active = False,
#                lifetime = 0,
#                extraargs = '',
#                description = '',
#                output_dataset = '',
#                **kwargs ):    
#                         
#    self.category       = category
#    self.jobtmeplate    = jobtemplate
#    self.inputtype      = inputtype
#    self.usercode       = usercode
#    self.optionfile     = optionfile
#    self.gangabin       = gangabin
#    self.testoption     = testoption
#    self.metricperm     = metricperm
#    self.active         = active
#    self.lifetime       = lifetime
#    self.extraargs      = extraargs
#    self.description    = description
#    self.output_dataset = output_dataset   
#    
#    for ti in self.template_inlines:
#        
#      name = 'template_%s'%ti
#        
#      if kwargs.has_key(name):
#        template_inline = kwargs[name]
#        if not isinstance(template_inline,types.ListType):
#          template_inline = [template_inline]
#        setattr(self,name,template_inline)                      
#                         
#class TemplateBackendHCModel( BaseHCModel ):
#    
#  type = 'template_backend'
#    
#  def __init__( self,
#                backend,
#                template = None,  
#                resubmit_enabled = True,
#                resubmit_force = False,
#                num_datasets_per_bulk = 1,
#                min_queue_depth = 0,
#                max_running_jobs = 1 ):
#      
#    self.backend               = backend
#    self.template              = template
#    self.resubmit_enabled      = resubmit_enabled
#    self.resubmit_force        = resubmit_force
#    self.num_datasets_per_bulk = num_datasets_per_bulk
#    self.min_queue_depth       = min_queue_depth
#    self.max_running_jobs      = max_running_jobs
#       
#class TemplateCloudHCModel( BaseHCModel ):
#
#  type = 'template_cloud'
#    
#  def __init__( self,
#                cloud,
#                template = None,  
#                resubmit_enabled = True,
#                resubmit_force = False,
#                num_datasets_per_bulk = 1,
#                min_queue_depth = 0,
#                max_running_jobs = 1 ):
#      
#    self.cloud                 = cloud
#    self.template              = template
#    self.resubmit_enabled      = resubmit_enabled
#    self.resubmit_force        = resubmit_force
#    self.num_datasets_per_bulk = num_datasets_per_bulk
#    self.min_queue_depth       = min_queue_depth
#    self.max_running_jobs      = max_running_jobs
#
#class TemplateDspatternHCModel( BaseHCModel ):
#
#  type = 'template_dspattern'
#  
#  def __init__( self,
#                dspattern,
#                template = None ):
#      
#    self.dspattern = dspattern
#    self.template  = template    
#
#class TemplateHostHCModel( BaseHCModel ):
#
#  type = 'template_host'
#  
#  def __init__( self,
#                host,
#                template = None):
#      
#    self.host     = host
#    self.template = template    
#
#
#class TemplateSiteHCModel( BaseHCModel ):
#    
#  type = 'template_site'
#    
#  def __init__( self,
#                site,
#                template = None,  
#                resubmit_enabled = True,
#                resubmit_force = False,
#                num_datasets_per_bulk = 1,
#                min_queue_depth = 0,
#                max_running_jobs = 1 ):
#      
#    self.site                  = site
#    self.template              = template
#    self.resubmit_enabled      = resubmit_enabled
#    self.resubmit_force        = resubmit_force
#    self.num_datasets_per_bulk = num_datasets_per_bulk
#    self.min_queue_depth       = min_queue_depth
#    self.max_running_jobs      = max_running_jobs
#
#class TemplateUserHCModel( BaseHCModel ):
#     
#  type = 'template_user'
#  
#  def __init__( self,
#                user,
#                template = None):
#      
#    self.user     = user
#    self.template = template         
#   
#     
#'''
#  ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
#  ##
#  ## TEST HC MODELS
#  ##
#  ## *TestHCModel
#  ## *TestBackendHCModel
#  ## *TestCloudHCModel
#  ## *TestDspatternHCModel
#  ## *TestHostHCModel
#  ## *TestLogHCModel
#  ## *TestSiteHCModel
#  ## *TestSiteAlarmHCModel
#  ## *TestUserHCModel
#  ##
#'''     
#
#class TestHCModel( BaseHCModel ):
#    
#  type = 'test'
#    
#  test_inlines = ['backend','cloud','dspattern','host','log','site','site_alarm','user']  
#    
#  def __init__( self,
#                starttime,
#                endtime,
#                template,
#                extraargs = '',
#                description = '',
#                output_dataset = '',
#                **kwargs):        
#      
#    self.starttime      = starttime
#    self.endtime        = endtime
#    self.template       = template
#    self.extraargs      = extraargs
#    self.description    = description      
#    self.output_dataset = output_dataset  
#      
#    for ti in self.test_inlines:
#        
#      name = 'test_%s'%ti
#        
#      if kwargs.has_key(name):
#        test_inline = kwargs[name]
#        if not isinstance(test_inline,types.ListType):
#          test_inline = [test_inline]
#        setattr(self,name,test_inline)
#                   
#      
#class TestBackendHCModel( BaseHCModel ):
#    
#  type = 'test_backend'
#    
#  def __init__( self,
#                backend,
#                test = None,  
#                resubmit_enabled = True,
#                resubmit_force = False,
#                num_datasets_per_bulk = 1,
#                min_queue_depth = 0,
#                max_running_jobs = 1 ):
#       
#    self.backend               = backend
#    self.test                  = test
#    self.resubmit_enabled      = resubmit_enabled
#    self.resubmit_force        = resubmit_force
#    self.num_datasets_per_bulk = num_datasets_per_bulk
#    self.min_queue_depth       = min_queue_depth
#    self.max_running_jobs      = max_running_jobs
#    
#class TestCloudHCModel( BaseHCModel ):
#    
#  type = 'test_cloud'
#
#  def __init__( self,
#                cloud,
#                test = None,  
#                resubmit_enabled = True,
#                resubmit_force = False,
#                num_datasets_per_bulk = 1,
#                min_queue_depth = 0,
#                max_running_jobs = 1 ):
#        
#    self.cloud                 = cloud
#    self.test                  = test
#    self.resubmit_enabled      = resubmit_enabled
#    self.resubmit_force        = resubmit_force
#    self.num_datasets_per_bulk = num_datasets_per_bulk
#    self.min_queue_depth       = min_queue_depth
#    self.max_running_jobs      = max_running_jobs
#
#    
#class TestDspatternHCModel( BaseHCModel ):
#    
#  type = 'test_dspattern'
#  
#  def __init__( self,
#                dspattern,
#                test = None ):
#      
#    self.dspattern = dspattern
#    self.test      = test    
#    
#class TestHostHCModel( BaseHCModel ):
#    
#  type = 'test_host'
#  
#  def __init__( self,
#                host,
#                test = None ):
#        
#    self.host = host
#    self.test = test    
#    
#class TestLogHCModel( BaseHCModel ):
#    
#  type = 'test_log'
#  
#  def __init__( self,
#                comment,
#                user,
#                test = None,
#                severity = 'common' ):
#  
#    self.test     = test
#    self.comment  = comment
#    self.user     = user
#    self.severity = 'common'
#    
#class TestSiteHCModel( BaseHCModel ):
#    
#  type = 'test_site' 
#   
#  def __init__( self,
#                site,  
#                test = None,
#                resubmit_enabled = True,
#                resubmit_force = False,
#                num_datasets_per_bulk = 1,
#                min_queue_depth = 0,
#                max_running_jobs = 1 ):
#        
#    self.site                  = site
#    self.test                  = test
#    self.resubmit_enabled      = resubmit_enabled
#    self.resubmit_force        = resubmit_force
#    self.num_datasets_per_bulk = num_datasets_per_bulk
#    self.min_queue_depth       = min_queue_depth
#    self.max_running_jobs      = max_running_jobs
#   
#   
#class TestSiteAlarmHCModel( BaseHCModel ):
#    
#  type = 'test_site_alarm'  
#     
#  def __init__( self,
#                site,
#                alarm,
#                test = None,
#                active = True,
#                actions = '' ):   
#      
#    self.site    = site
#    self.test    = test
#    self.alarm   = alarm
#    self.active  = active 
#    self.actions = actions 
#     
#class TestUserHCModel( BaseHCModel ):
#    
#  type = 'test_user'
#  
#  def __init__( self,
#                user,
#                test = None ):
#      
#    self.user = user
#    self.test = test        