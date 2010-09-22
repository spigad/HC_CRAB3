from hc.core.utils.generic.class_func import custom_import
from django.http import Http404

def method(self, request, queryset):

    name = self.model._meta.object_name

    if 'Test' in name:
      name = 'Test'
    elif 'Template' in name:
      name = 'Template'
    elif name in ['Backend','Cloud','Dspattern','Host','Site']:
      name = 'InlineItem'
#    elif name in ['JobTemplate','OptionFile','UserCode','MetricPermission','InputType','TestScript','GangaBin']:

    try:
      checkFunction = custom_import('hc.core.base.admin.actions.delete_marked.check%s'%(name))
      objs = checkFunction(self, request, queryset)

      message_bit = ''
      if objs['deleted']:
        message_bit += str(len(objs['deleted']))+' %s(s) deleted'%(object_name)
      if objs['wrong']:
        message_bit += str(len(objs['wrong']))+' %s(s) could not be deleted'%(object_name)
    except:
      message_bit = 'Something went wrong. Please, report.'

    self.message_user(request, message_bit)

def checkInlineItem(self, request, queryset):

  object_name = self.model._meta.object_name
  objs = {'deleted':0,'wrong':0}

  for item in queryset:  

    f_templ = getattr(t,'getTemplate%ss_for_%s'%(object_name,object.lower()))
    f_test  = getattr(t,'getTest%ss_for_%s'%(object_name,object.lower()))
    if f_templ.all() or f_test.all():
      objs['wrong'] += 1
    else:
      objs['deleted'] += 1 
      item.delete()

  return objs


def checkTest(self, request, queryset):

  allowed_states = ['draft','unapproved','tobescheduled','scheduled']
  object_name = self.model._meta.object_name
  objs = {'deleted':0,'wrong':0}

  for t in queryset:

    if object_name == 'Test':
      state = t.state
    else:
      state = t.test.state

    if not state in allowed_states:
      objs['wrong'] += 1
    else:

      if object_name == 'Test':
        users = [str(tu.user) for tu in t.getTestUsers_for_test.all()]
      else:
        users = [str(tu.user) for tu in t.test.getTestUsers_for_test.all()]

      user = str(request.user)
      if not (user in users or request.user.is_superuser):
        objs['wrong'] += 1
      else:
        objs['deleted'] += 1
        t.delete()

  return objs

def checkTemplate(self, request, queryset):

  object_name = self.model._meta.object_name
  objs = {'deleted':0,'wrong':0}

  for t in queryset:
  
    if object_name == 'Template':
      tests = t.getTests_for_template.all()
    else:
      tests = t.template.getTests_for_template.all()

    if tests:
      objs['wrong'] += 1
    else:

      if object_name == 'Template':
        users = [str(tu.user) for tu in t.getTemplateUsers_for_template.all()]
      else:      
        users = [str(tu.user) for tu in t.template.getTemplateUsers_for_template.all()]

      user = str(request.user)
      if not (user in users or request.user.is_superuser):
        objs['wrong'] += 1
      else:
        objs['deleted'] += 1
        t.delete()

  return objs
