from django.conf.urls import include, patterns
from django.contrib import admin

admin.autodiscover()

urlpatterns = patterns('',
    # If some HammerCloud application urls are needed, add them here.
    # (r'^app/atlas', include('hc.atlas.urls'))

    (r'', include('hc.core.urls')),
    (r'', include('hc.core.base.rss.urls')),
    (r'', include('hc.core.base.xhr.urls')),
    (r'', include('hc.core.base.xmlrpc.urls')),

    (r'^admin/', include(admin.site.urls)),
    (r'^admin/varnish/', include('varnishapp.urls')),
)
