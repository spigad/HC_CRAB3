from django.contrib import admin
from hc.core.base.rss.managers.admin import feed_am

## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## FEED BASE CLASSES
##
## *HCFeedAdminBase
##

class HCFeedAdminBase(admin.ModelAdmin):

  list_display = ('title', feed_am.getFeedDescriptionStringAdmin,)
  fieldsets = [
    ('Feed', {'fields': ['title','description','severity']})
  ]

  class Meta:
    abstract = True

class AppFeedAdminBase(admin.ModelAdmin):

  list_display = ('title', feed_am.getFeedDescriptionStringAdmin,)
  fieldsets = [
    ('Feed', {'fields': ['title','description','severity']})
  ]

  class Meta:
    abstract = True

class CloudFeedAdminBase(admin.ModelAdmin):

  list_display = ('title', feed_am.getFeedDescriptionStringAdmin,)
  fieldsets = [
    ('Feed', {'fields': ['title','description','cloud','severity']})
  ]

  class Meta:
    abstract = True

class SiteFeedAdminBase(admin.ModelAdmin):

  list_display = ('title', feed_am.getFeedDescriptionStringAdmin,)
  fieldsets = [
    ('Feed', {'fields': ['title','description','site','severity']})
  ]

  class Meta:
    abstract = True

class TemplateFeedAdminBase(admin.ModelAdmin):

  list_display = ('title', feed_am.getFeedDescriptionStringAdmin,)
  fieldsets = [
    ('Feed', {'fields': ['title','description','template','severity']})
  ]

  class Meta:
    abstract = True

class TestFeedAdminBase(admin.ModelAdmin):

  list_display = ('title', feed_am.getFeedDescriptionStringAdmin,)
  fieldsets = [
    ('Feed', {'fields': ['title','description','test','severity']})
  ]

  class Meta:
    abstract = True

