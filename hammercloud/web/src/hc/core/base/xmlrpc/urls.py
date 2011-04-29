from django.conf.urls.defaults import *

urlpatterns = patterns('hc.core.base.xmlrpc.XMLRPC',
  url(r'^xmlrpc$'    , 'rpc_handler', name ='rpc_handler-view'),
  )

