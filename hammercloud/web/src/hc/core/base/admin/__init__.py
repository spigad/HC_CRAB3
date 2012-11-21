from django.contrib import admin

"""Common definitions for hc.core.base.admin."""


class ConfiguredAdmin(admin.ModelAdmin):
    """Provides a common place to setup configurations for all the models."""
    actions_on_top = True
    actions_on_bottom = True
    save_on_top = True
    save_as = True
    list_select_related = True
    list_max_show_all = 50
    list_per_page = 25
