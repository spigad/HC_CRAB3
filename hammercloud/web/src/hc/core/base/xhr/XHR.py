from django.http import HttpResponse
from hc.core.base.xhr.parser import XhrQueryParser
from django.utils import simplejson

def jsonXhr(request,app):

  xqp   = XhrQueryParser()

  data  = xqp.parse(request,app) 

  data = simplejson.dumps(data)
  
  data = data.replace('null','None')
  data = data.replace('true','True')
  data = data.replace('false','False')

  return HttpResponse(data,'application/javascript')


#Maybe implemented on a paralell Universe..

#def yamlXhr(request,app):
# xqp   = XhrQueryParser()
# data  = xqp.parse(request,app)
# return HttpResponse('comming soon')

#def xmlXhr(request,app):
# xqp   = XhrQueryParser()
# data  = xqp.parse(request,app)
# return HttpResponse('coming soon')
