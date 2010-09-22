from django.core.mail import mail_admins

def method(self, request, queryset):

  app  = self.__module__.split('.')[1]
  objs = {'approved':[],'wrong':[]}
  url = 'http://'+request.META['HTTP_HOST']+request.META['SCRIPT_NAME']

  for t in queryset:
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

  mail_admins('[HammerCloud][APPROVED]',msg,fail_silently=True)
  self.message_user(request, message_bit)

