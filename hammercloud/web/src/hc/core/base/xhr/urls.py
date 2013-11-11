from django.conf.urls import patterns, url

urlpatterns = patterns('hc.core.base.xhr.XHR',
    url(r'^app/(?P<app>[a-z]+)/xhr/json/$', 'jsonXhr', name ='jsonXhr-view'),
)
