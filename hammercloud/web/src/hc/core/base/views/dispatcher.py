from django.http import Http404
from hc.core.utils.generic.class_func import custom_import

def dispatcher(request,app,*args,**kwargs):
  res = None
  func = kwargs.pop('func')
 
  try:
    m = custom_import('hc.'+app+'.views.'+func)
    res = m(request,*args,**kwargs)
  except:
    raise Http404

  return res
