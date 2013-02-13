#from django.db import models
from django.forms.models import ModelFormMetaclass

from hc.core.base.forms.formGenerator import FormGenerator

#from hc.core.utils.generic.class_func import custom_import

import types

class FormMetaCreator(ModelFormMetaclass):

  def __new__(cls, name, bases, attrs):

    def __create(*args):

      if args:
        module = args[0]
      elif attrs.has_key('__module__'):
        module = attrs['__module__'].split('.')[1]

      try:
        f = getattr(FormGenerator,'get'+name)
        dic = f(FormGenerator(),module)
        for k,v in dic.items():
          attrs[k] = v
      except:
        raise

      form = super(FormMetaCreator, cls).__new__(cls, name, bases, attrs)
      return form
    
    return __create

class AdminFormMetaCreator(ModelFormMetaclass):

  def __new__(cls, name, bases, attrs):

    if attrs.has_key('__module__'):
      module = attrs['__module__'].split('.')[1]

      try:
        f = getattr(FormGenerator,'get'+name)
        dic = f(FormGenerator(),module)
        for k,v in dic.items():
          attrs[k] = v
      except:
        pass

    form = super(AdminFormMetaCreator, cls).__new__(cls, name, bases, attrs)
    return form


