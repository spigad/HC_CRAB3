from django.core.mail import mail_admins,send_mass_mail
from django.contrib.auth.models import User

from hc.core.utils.generic.class_func import custom_import

def method(self, request, queryset):

  app  = self.__module__.split('.')[1]
  objs = {'approved':[],'wrong':[]}
  url = 'http://'+request.META['HTTP_HOST']+request.META['SCRIPT_NAME']

  for t in queryset:

    own_user = t.getTestUsers_for_test.filter(user=request.user.username)
    #If the person who approves the test is not in the TestUsers list, we add him/her/it.
    if not own_user:
      TestUser = custom_import('hc.'+app+'.models.TestUser')
      tu = TestUser(test=t,user=request.user.username)
      tu.save()

    if t.state in ['unapproved','draft','cancelled']:

      if not t.getTestHosts_for_test.all():
        objs['wrong'] += ['%s/admin/%s/test/%d/ \n  reason: No hosts assigned.\n'%(url,app,t.id)]
      elif not t.getTestSites_for_test.all():
        objs['wrong'] += ['%s/admin/%s/test/%d/ \n  reason: No sites assigned.\n'%(url,app,t.id)]
      elif not t.getTestUsers_for_test.all():
        objs['wrong'] += ['%s/admin/%s/test/%d/ \n  reason: No users assigned.\n'%(url,app,t.id)]
      elif not t.getTestDspatterns_for_test.all():
        objs['wrong'] += ['%s/admin/%s/test/%d/ \n  reason: No dspatterns assigned.\n'%(url,app,t.id)]
      else:
        objs['approved'] += ['%s/admin/%s/test/%d/ \n Starttime: %s'%(url,app,t.id,t.starttime.ctime())]
        t.state = 'tobescheduled'
        t.save()

  msg = 'Tests marked as approved by %s:\n\n'%(request.user.username)
  message_bit = ''
  if objs['approved']:
    msg += 'APPROVED:\n'
    msg += '\n    '.join(objs['approved'])
    message_bit += str(len(objs['approved']))+' test(s) marked as approved,'
  if objs['wrong']:
    msg += 'WRONG:\n'
    msg += '\n    '.join(objs['wrong'])
    message_bit += str(len(objs['wrong']))+' test(s) with wrong format ( check your email for details!).'

  test_users = [t.getTestUsers_for_test.all() for t in queryset if t.getTestUsers_for_test.all()]

  users = []

  for tus in test_users:
    for tu in tus:
      user = User.objects.filter(username=tu.user)
      if user and not user[0].email in users:
        users += [user[0].email]

  admins = [u.email for u in User.objects.filter(groups__name='%s_admin'%(app))]

  message1 = ('[HammerCloud][%s][APPROVED]'%(app.upper()),msg,'hammercloud@mail.cern.ch',admins)
  message2 = ('[HammerCloud][%s][APPROVED]'%(app.upper()),msg,'hammercloud@mail.cern.ch',users)

  send_mass_mail((message1,message2), fail_silently=False)

#  mail_admins('[HammerCloud][APPROVED]',msg,fail_silently=True)
  self.message_user(request, message_bit)

