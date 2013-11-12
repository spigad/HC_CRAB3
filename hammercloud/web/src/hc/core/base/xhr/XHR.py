from django.http import HttpResponse
from hc.core.base.xhr.parser import XhrQueryParser
import json


def jsonXhr(request,app):
  xqp = XhrQueryParser()

  data = json.dumps(xqp.parse(request,app))
  data = data.replace('null', 'None')
  data = data.replace('true', 'True')
  data = data.replace('false', 'False')

  return HttpResponse(data, 'application/javascript')

