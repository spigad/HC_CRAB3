#from django.db import models
from django.forms.models import ModelFormMetaclass

from hc.core.base.forms.forms import FormGenerator

import types

class FormMetaCreator(ModelFormMetaclass):

  def __new__(cls, name, bases, attrs):

    (dic,methods) = None,None

    if attrs.has_key('__module__'):

      module = attrs['__module__'].split('.')[1]
      try:
        f = getattr(FormGenerator,'get'+name)
        dic = f(FormGenerator(),module)

        for k,v in dic.items():
          attrs[k] = v
      except:
        pass

    form = super(FormMetaCreator, cls).__new__(cls, name, bases, attrs)

#    if methods:
#      f = types.MethodType(methods['clean'], form, FormMetaCreator)
#      form.clean = f

    return form


