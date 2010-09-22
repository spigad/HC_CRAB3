from hc.core.utils.generic.class_func import custom_import
from django.http import Http404

def method(self, request, object_id, extra_context=None):

    app  = self.__module__.split('.')[1] 
    name = self.model._meta.object_name

    try:
      checkFunction = custom_import('hc.core.base.admin.actions.delete_view.check%s'%(name))
      users = checkFunction(app, object_id)
    except:
      #Clouc, backend,... etc, must not be deleted if they are at any test/template
      users = []

    if not(request.user in users) and not(request.user.is_superuser):
      raise Http404

def checkTemplate(app, object_id):

  test = custom_import('hc.'+app+'.models.Test')
  tests = test.objects.filter(template=object_id)

  template = custom_import('hc.'+app+'.models.Template')
  template = template.objects.get(pk=object_id)

  if tests:
    raise Http404

  users = [str(tu.user) for tu in template.getTemplateUsers_for_template.all()]
  return users

def checkTemplateBackend(app, object_id):

  teb  = custom_import('hc.'+app+'.models.TemplateBackend')
  test = custom_import('hc.'+app+'.models.Test')

  template = teb.objects.get(pk=object_id).template
  tests = test.objects.filter(template=template)

  if tests:
    raise Http404

  users = [str(tu.user) for tu in template.getTemplateUsers_for_template.all()]
  return users

def checkTemplateCloud(app, object_id):

  tec  = custom_import('hc.'+app+'.models.TemplateCloud')
  test = custom_import('hc.'+app+'.models.Test')

  template = tec.objects.get(pk=object_id).template
  tests = test.objects.filter(template=template)

  if tests:
    raise Http404

  users = [str(tu.user) for tu in template.getTemplateUsers_for_template.all()]
  return users


def checkTemplateDspattern(app, object_id):

  ted  = custom_import('hc.'+app+'.models.TemplateDspattern')
  test = custom_import('hc.'+app+'.models.Test')

  template = ted.objects.get(pk=object_id).template
  tests = test.objects.filter(template=template)

  if tests:
    raise Http404

  users = [str(tu.user) for tu in template.getTemplateUsers_for_template.all()]
  return users

def checkTemplateHost(app, object_id):

  teh  = custom_import('hc.'+app+'.models.TemplateHost')
  test = custom_import('hc.'+app+'.models.Test')

  template = teh.objects.get(pk=object_id).template
  tests = test.objects.filter(template=template)

  if tests:
    raise Http404

  users = [str(tu.user) for tu in template.getTemplateUsers_for_template.all()]
  return users

def checkTemplateSite(app, object_id):

  tes  = custom_import('hc.'+app+'.models.TemplateSite')
  test = custom_import('hc.'+app+'.models.Test')

  template = tes.objects.get(pk=object_id).template
  tests = test.objects.filter(template=template)

  if tests:
    raise Http404

  users = [str(tu.user) for tu in template.getTemplateUsers_for_template.all()]
  return users

def checkTest(app, object_id):

  allowed_states = ['draft','unapproved','tobescheduled','scheduled']

  test = custom_import('hc.'+app+'.models.Test')
  test = test.objects.get(pk=object_id)
  if not test.state in allowed_states:
    raise Http404

  users = [str(tu.user) for tu in test.getTestUsers_for_test.all()]
  return users

def checkTestBackend(app, object_id):

  allowed_states = ['draft','unapproved','tobescheduled','scheduled']

  tb = custom_import('hc.'+app+'.models.TestBackend')
  test = tb.objects.get(pk=object_id).test

  if not test.state in allowed_states:
    raise Http404

  users = [str(tu.user) for tu in test.getTestUsers_for_test.all()]
  return users

def checkTestCloud(app, object_id):

  allowed_states = ['draft','unapproved','tobescheduled','scheduled']

  tc = custom_import('hc.'+app+'.models.TestCloud')
  test = tc.objects.get(pk=object_id).test

  if not test.state in allowed_states:
    raise Http404

  users = [str(tu.user) for tu in test.getTestUsers_for_test.all()]
  return users

def checkTestDspattern(app, object_id):

  allowed_states = ['draft','unapproved','tobescheduled','scheduled']

  td = custom_import('hc.'+app+'.models.TestDspattern')
  test = td.objects.get(pk=object_id).test

  if not test.state in allowed_states:
    raise Http404

  users = [str(tu.user) for tu in test.getTestUsers_for_test.all()]
  return users

def checkTestHost(app, object_id):

  allowed_states = ['draft','unapproved','tobescheduled','scheduled']

  th = custom_import('hc.'+app+'.models.TestHost')
  test = td.objects.get(pk=object_id).test

  if not test.state in allowed_states:
    raise Http404

  users = [str(tu.user) for tu in test.getTestUsers_for_test.all()]
  return users

def checkTestSite(app, object_id):

  allowed_states = ['draft','unapproved','tobescheduled','scheduled']

  ts = custom_import('hc.'+app+'.models.TestSite')
  test = ts.objects.get(pk=object_id).test

  if not test.state in allowed_states:
    raise Http404

  users = [str(tu.user) for tu in test.getTestUsers_for_test.all()]
  return users

