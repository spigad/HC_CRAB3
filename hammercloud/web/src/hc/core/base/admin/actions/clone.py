from hc.core.base.admin.actions.rules import clone_rules
#from hc.core.utils.generic.class_func import custom_import

from django.db.models.fields import CharField
from time import time

##
##  MAIN CLONE METHOD
##
def method(self,request,queryset):

  rows_updated = 0
  for item in queryset:
    if clone(item):
      rows_updated += 1
  if rows_updated == 1:
    message_bit = "1 object was"
  else:
    message_bit = "%s objects were" % rows_updated
  self.message_user(request, "%s successfully cloned." % message_bit)

def clone(object):
  new_obj = []
#  try:
  new_obj = clone_object(object)
  new_obj.saveClone()

  if clone_rules.INLINES.has_key(new_obj._meta.object_name):
    inlines = clone_inlines(new_obj,object)
#  except:
#    new_obj = []

  return new_obj

## creates the new object (not saved into DB) taking into account the unique=True 
## and the RULES stablished beforehand.
def clone_object(object):
  args = {}
  for fld in object._meta.fields:
    if fld is not object._meta.pk:
      args[fld.name] = getattr(object,fld.name)
      if fld.unique:
        if isinstance(fld,CharField):
          args[fld.name] += ' (copy@%s)'%(int(time()))
  if clone_rules.RULES.has_key(object._meta.object_name):
    for key,func in clone_rules.RULES[object._meta.object_name].items():
      f = getattr(clone_rules,func)
      args[key] = f(args[key])

  return object.__class__(**args)

## METHOD that given the INLINES RULES,
## starts the cloning proccess.
def clone_inlines(new_obj,object):
  
  inlines = []
  key,list = clone_rules.INLINES[new_obj._meta.object_name]
  for item in list:
    f = getattr(object,'get%ss_for_%s'%(item,key))
    for inline_object in f.all():
      inlines += [clone_unique(inline_object,key,new_obj)]

  return inlines

## METHOD TO CLONE objects with unique_together=True
def clone_unique(object,key,new_object):

  obj = clone_object(object)
  setattr(obj,key,new_object)
  obj.saveClone()
    
  return obj

