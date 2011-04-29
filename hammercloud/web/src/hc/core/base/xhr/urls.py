from django.conf.urls.defaults import *

urlpatterns = patterns('hc.core.base.xhr.XHR',
  url(r'^app/(?P<app>[a-z]+)/xhr/json/$'    , 'jsonXhr', name ='jsonXhr-view'),
#  url(r'^app/(?P<app>[a-z]+)/xhr/yaml/$'    , 'yamlXhr', name ='yamlXhr-view'),
#  url(r'^app/(?P<app>[a-z]+)/xhr/xml/$'     , 'xmlXhr' , name ='xmlXhr-view')
  )

