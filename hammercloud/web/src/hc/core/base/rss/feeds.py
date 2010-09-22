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
    return get_object_or_404(Plugin, name=app)

  def title(self,obj):
    return "HammerCloud-%s"%(obj.name.upper())

  def description(self,obj):
    return "Updates, changes and additions to HammerCloud-%s."%(obj.name.upper())

  def link(self,obj):
    return "/hc/feed/app/%s/"%(obj.name)

  def items(self,obj):
    app_hc_feed = custom_import('hc.%s.models.AppFeed'%(obj.name))
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
    plugin          = get_object_or_404(Plugin,name=app)
    plugin.cloud_id = cloud_id
    return plugin

  def title(self,obj):
    class_cloud_feed = custom_import('hc.%s.models.Cloud'%(obj.name))
    cloud_feed       = get_object_or_404(class_cloud_feed,pk=obj.cloud_id)

    return "Hammercloud-%s for cloud %s"%(obj.name.upper(),cloud_feed.name)

  def description(self,obj):
    class_cloud_feed = custom_import('hc.%s.models.Cloud'%(obj.name))
    cloud_feed       = get_object_or_404(class_cloud_feed,pk=obj.cloud_id)

    return "Updates, changes and additions to cloud %s at HammerCloud-%s "%(cloud_feed.name,obj.name.upper())

  def link(self,obj):
    return "/hc/feed/app/%s/cloud/%s/"%(obj.name,obj.cloud_id)

  def items(self,obj):
    class_cloud_feed = custom_import('hc.%s.models.CloudFeed'%(obj.name))
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
    plugin         = get_object_or_404(Plugin,name=app)
    plugin.site_id = site_id
    return plugin

  def title(self,obj):
    class_site_feed = custom_import('hc.%s.models.Site'%(obj.name))
    site_feed       = get_object_or_404(class_site_feed,pk=obj.site_id)

    return "Hammercloud-%s for site %s"%(obj.name.upper(),site_feed.name)

  def description(self,obj):
    class_site_feed = custom_import('hc.%s.models.Site'%(obj.name))
    site_feed       = get_object_or_404(class_site_feed,pk=obj.site_id)

    return "Updates, changes and additions to site %s at HammerCloud-%s "%(site_feed.name,obj.name.upper())

  def link(self,obj):
    return "/hc/feed/app/%s/site/%s/"%(obj.name,obj.site_id)

  def items(self,obj):
    class_site_feed = custom_import('hc.%s.models.SiteFeed'%(obj.name))
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
    plugin             = get_object_or_404(Plugin,name=app)
    plugin.template_id = template_id
    return plugin

  def title(self,obj):
    class_template_feed = custom_import('hc.%s.models.Template'%(obj.name))
    template_feed       = get_object_or_404(class_template_feed,pk=obj.template_id)

    return "Hammercloud-%s for template %s"%(obj.name.upper(),template_feed.name)

  def description(self,obj):
    class_template_feed = custom_import('hc.%s.models.Template'%(obj.name))
    template_feed       = get_object_or_404(class_template_feed,pk=obj.template_id)

    return "Updates, changes and additions to template %s at HammerCloud-%s "%(template_feed.name,obj.name.upper())

  def link(self,obj):
    return "/hc/feed/app/%s/template/%s/"%(obj.name,obj.template_id)

  def items(self,obj):
    class_template_feed = custom_import('hc.%s.models.TemplateFeed'%(obj.name))
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
    plugin         = get_object_or_404(Plugin,name=app)
    plugin.test_id = test_id
    return plugin

  def title(self,obj):
    class_test_feed = custom_import('hc.%s.models.Test'%(obj.name))
    test_feed       = get_object_or_404(class_test_feed,pk=obj.test_id)

    return "Hammercloud-%s for test %s"%(obj.name.upper(),test_feed.id)

  def description(self,obj):
    class_test_feed = custom_import('hc.%s.models.Test'%(obj.name))
    test_feed       = get_object_or_404(class_test_feed,pk=obj.test_id)

    return "Updates, changes and additions to test %s at HammerCloud-%s "%(test_feed.id,obj.name.upper())

  def link(self,obj):
    return "/hc/feed/app/%s/test/%s/"%(obj.name,obj.test_id)

  def items(self,obj):
    class_test_feed = custom_import('hc.%s.models.TestFeed'%(obj.name))
    return class_test_feed.objects.all().order_by('-id')[:30]

  def item_title(self, obj):
    return '%s'%('['+obj.severity+']'+str(obj.title))

  def item_description(self, obj):
    return '%s'%(obj.description)

  def item_link(self,obj):
    app = obj.__module__.split('.')[1]
    return "/hc/feed/app/%s/test/%d/"%(app,obj.test_id)


