from django.contrib.syndication.views import Feed
from hc.core.models import HCFeed,Plugin

from django.http import Http404

from django.shortcuts import get_object_or_404

from hc.core.utils.generic.class_func import custom_import

class HCEntriesFeed(Feed):

  title = "HammerCloud"
  link = "/hc/feed/"
  description = "Updates, changes and additions to HammerCloud."
  title_template = 'feeds/title.html'
  description_template = 'feeds/description.html'

  def items(self):
    return HCFeed.objects.all().order_by('-id')[:30]

  def item_title(self, obj):
    return '%s'%('['+obj.severity+']'+str(obj.title))

  def item_description(self, obj):
    return '%s'%(obj.description)

  def item_link(self,obj):
    return self.link

class AppEntriesFeed(Feed):

  def get_object(self, request, app):
    return app

  def title(self,obj):
    return "HammerCloud-%s"%(obj.upper())

  def description(self,obj):
    return "Updates, changes and additions to HammerCloud-%s."%(obj.upper())

  def link(self,obj):
    return "/hc/feed/app/%s/"%(obj)

  def items(self,obj):
    app_hc_feed = custom_import('hc.%s.models.AppFeed'%(obj))
    return app_hc_feed.objects.all().order_by('-id')[:30]

  def item_title(self, obj):
    return '%s'%('['+obj.severity+']'+str(obj.title))

  def item_description(self, obj):
    return '%s'%(obj.description)

  def item_link(self,obj):
    app = obj.__module__.split('.')[1]
    return '/hc/feed/app/%s/'%(app)

class CloudEntriesFeed(Feed):

  def get_object(self, request, app, cloud_id):
    return (app,cloud_id)

  def title(self,obj):
    plugin,cloud_id = obj
    class_cloud_feed = custom_import('hc.%s.models.Cloud'%(plugin))
    cloud_feed       = get_object_or_404(class_cloud_feed,pk=cloud_id)

    return "Hammercloud-%s for cloud %s"%(plugin.upper(),cloud_feed.name)

  def description(self,obj):
    plugin,cloud_id = obj
    class_cloud_feed = custom_import('hc.%s.models.Cloud'%(plugin))
    cloud_feed       = get_object_or_404(class_cloud_feed,pk=cloud_id)

    return "Updates, changes and additions to cloud %s at HammerCloud-%s "%(cloud_feed.name,plugin.upper())

  def link(self,obj):
    plugin,cloud_id = obj
    return "/hc/feed/app/%s/cloud/%s/"%(plugin,cloud_id)

  def items(self,obj):
    plugin,cloud_id = obj
    class_cloud_feed = custom_import('hc.%s.models.CloudFeed'%(plugin))
    return class_cloud_feed.objects.all().order_by('-id')[:30]

  def item_title(self, obj):
    return '%s'%('['+obj.severity+']'+str(obj.title))

  def item_description(self, obj):
    return '%s'%(obj.description)

  def item_link(self,obj):
    app = obj.__module__.split('.')[1]
    return "/hc/feed/app/%s/cloud/%d/"%(app,obj.cloud_id)

class SiteEntriesFeed(Feed):

  def get_object(self, request, app, site_id):
    return (app,site_id)

  def title(self,obj):
    plugin,site_id = obj
    class_site_feed = custom_import('hc.%s.models.Site'%(plugin))
    site_feed       = get_object_or_404(class_site_feed,pk=site_id)

    return "Hammercloud-%s for site %s"%(plugin.upper(),site_feed.name)

  def description(self,obj):
    plugin,site_id = obj
    class_site_feed = custom_import('hc.%s.models.Site'%(plugin))
    site_feed       = get_object_or_404(class_site_feed,pk=site_id)

    return "Updates, changes and additions to site %s at HammerCloud-%s "%(site_feed.name,plugin.upper())

  def link(self,obj):
    plugin,site_id = obj
    return "/hc/feed/app/%s/site/%s/"%(plugin,site_id)

  def items(self,obj):
    plugin,site_id = obj
    class_site_feed = custom_import('hc.%s.models.SiteFeed'%(plugin))
    return class_site_feed.objects.all().order_by('-id')[:30]

  def item_title(self, obj):
    return '%s'%('['+obj.severity+']'+str(obj.title))

  def item_description(self, obj):
    return '%s'%(obj.description)

  def item_link(self,obj):
    app = obj.__module__.split('.')[1]
    return "/hc/feed/app/%s/site/%d/"%(app,obj.site_id)

class TemplateEntriesFeed(Feed):

  def get_object(self, request, app, template_id):
    return (app,template_id)

  def title(self,obj):
    plugin,template_id = obj
    class_template_feed = custom_import('hc.%s.models.Template'%(plugin))
    template_feed       = get_object_or_404(class_template_feed,pk=template_id)

    return "Hammercloud-%s for template %s"%(plugin.upper(),template_feed.name)

  def description(self,obj):
    plugin,template_id = obj
    class_template_feed = custom_import('hc.%s.models.Template'%(plugin))
    template_feed       = get_object_or_404(class_template_feed,pk=template_id)

    return "Updates, changes and additions to template %s at HammerCloud-%s "%(template_feed.name,plugin.upper())

  def link(self,obj):
    plugin,template_id = obj
    return "/hc/feed/app/%s/template/%s/"%(plugin,template_id)

  def items(self,obj):
    plugin,template_id = obj
    class_template_feed = custom_import('hc.%s.models.TemplateFeed'%(plugin))
    return class_template_feed.objects.all().order_by('-id')[:30]

  def item_title(self, obj):
    return '%s'%('['+obj.severity+']'+str(obj.title))

  def item_description(self, obj):
    return '%s'%(obj.description)

  def item_link(self,obj):
    app = obj.__module__.split('.')[1]
    return "/hc/feed/app/%s/template/%d/"%(app,obj.template_id)

class TestEntriesFeed(Feed):

  def get_object(self, request, app, test_id):
    return (app,test_id)

  def title(self,obj):
    plugin,test_id = obj
    class_test_feed = custom_import('hc.%s.models.Test'%(plugin))
    test_feed       = get_object_or_404(class_test_feed,pk=test_id)

    return "Hammercloud-%s for test %s"%(plugin.upper(),test_feed.id)

  def description(self,obj):
    plugin,test_id = obj
    class_test_feed = custom_import('hc.%s.models.Test'%(plugin))
    test_feed       = get_object_or_404(class_test_feed,pk=test_id)

    return "Updates, changes and additions to test %s at HammerCloud-%s "%(test_feed.id,plugin.upper())

  def link(self,obj):
    plugin,test_id = obj
    return "/hc/feed/app/%s/test/%s/"%(plugin,test_id)

  def items(self,obj):
    plugin,test_id = obj
    class_test_feed = custom_import('hc.%s.models.TestFeed'%(plugin))
    return class_test_feed.objects.all().order_by('-id')[:30]

  def item_title(self, obj):
    return '%s'%('['+obj.severity+']'+str(obj.title))

  def item_description(self, obj):
    return '%s'%(obj.description)

  def item_link(self,obj):
    app = obj.__module__.split('.')[1]
    return "/hc/feed/app/%s/test/%d/"%(app,obj.test_id)


