from django.contrib import admin
from hc.core.base.admin import ConfiguredAdmin
from hc.core.base.rss.admin import HCFeedAdminBase
from hc.core.models import Plugin, HCFeed

"""Admin configuration for the core models."""


class PluginAdmin(ConfiguredAdmin):
    """ModelAdmin for the plugins."""
    readonly_fields = ('mtime',)
    list_display = ('name', 'mtime')
    date_hierarchy = 'mtime'
    fieldsets = [
        ('Plugin', {'fields': ['name']})
        ]
    list_filter = ['name']
    search_fields = ['name']


class HCFeedAdmin(HCFeedAdminBase):
    pass


admin.site.register(HCFeed, HCFeedAdmin)
admin.site.register(Plugin, PluginAdmin)
