from hc.core.models import Plugin,HCFeed
from django.contrib import admin

from hc.core.base.rss.admin import HCFeedAdminBase

class PluginAdmin(admin.ModelAdmin):

  list_display = ('name',)
  fieldsets = [
    ('Cloud', {'fields': ['name']})
  ]
#  list_filter = ['name']
#  search_fields = ['name']

class HCFeedAdmin(HCFeedAdminBase):
  pass


admin.site.register(HCFeed,HCFeedAdmin)
admin.site.register(Plugin,PluginAdmin)
