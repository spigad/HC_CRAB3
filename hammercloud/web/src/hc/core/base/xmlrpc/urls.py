from django.conf.urls import patterns, url

urlpatterns = patterns('hc.core.base.xmlrpc.XMLRPC',
    url(r'^xmlrpc$', 'rpc_handler', name ='rpc_handler-view'),
)
