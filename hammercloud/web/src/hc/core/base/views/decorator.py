from hc.core.base.views.generic import GenericView
from hc.core.utils.generic.class_func import custom_import

from functools import wraps

from django.http import HttpResponse

import inspect

class GenericView_dec(object):

  def __init__(self, function):
    name = function.__name__

    self.function = None
    self.plugin = function.__module__.split('.')[1]

    #If there are more than one coincidence some
    #fireworks will appear. Control that.

    #If there is no coincidence, fireworks as well.

    names = dir(GenericView)

    for key in names:
      if key.startswith(name):
        self.function = key

  def __call__(self,*args,**kwargs):

    name = self.function

    f = getattr(GenericView,name)
    inspection = inspect.getargspec(f)

    # Some magic numbers, but every abstract view 
    # has as params: 
    # ([self,request,dic],None,None,(dic,))
    dic = inspection[3][0]

    for item in dic.keys():
      dic[item] = custom_import('hc.'+self.plugin+'.models.'+item)

    kwargs['dic'] = dic

    return f(GenericView(),*args,**kwargs)

def GenView_dec(*args,**kwargs):

  try:
    params = kwargs['params']
  except KeyError:
    params = None

  def inner_render(function):
    def wrapped(*args,**kwargs):

      plugin = function.__module__.split('.')[1]
      name   = function.__name__

      try:
        f= getattr(GenericView,name)
      except:
        #Return something better than this could be a good idea.
        return None

      inspection = inspect.getargspec(f)

      dic = inspection[3][0]

      for item in dic.keys():
        dic[item] = custom_import('hc.'+plugin+'.models.'+item)

      kwargs['dic']    = dic
      kwargs['params'] = params

      if not params.has_key('on') or params['on']!=True:
        return HttpResponse('This page is not enabled. Please, contact via Savannah if you have doubts.')

      return f(GenericView(),*args,**kwargs)

    return wraps(function)(wrapped)
  return inner_render
