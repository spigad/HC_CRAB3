from django.conf import settings
from django.conf.urls import include, patterns, url
from django.contrib import admin

admin.autodiscover()

urlpatterns = patterns('',
    # If some HammerCloud application urls are needed, add them here.
    # (r'^app/atlas', include('hc.atlas.urls'))

    (r'', include('hc.core.urls')),
    (r'', include('hc.core.base.rss.urls')),
    (r'', include('hc.core.base.xhr.urls')),
    (r'', include('hc.core.base.xmlrpc.urls')),

    url(r'^admin/', include(admin.site.urls), kwargs={'SSL': True}),
    (r'^admin/varnish/', include('varnishapp.urls')),
)

# TODO(rmedrano): move these URLs to a debug URLs file.
if settings.DEBUG:
    urlpatterns += patterns(
        (r'^', include('debug_toolbar_htmltidy.urls')),
        (r'', include('debug_toolbar_user_panel.urls')),
    )
