from django.core.mail import mail_admins

def method(self, request, queryset):

  CLONED_THRESHOLD = 2

  app  = self.__module__.split('.')[1]
  url = 'http://'+request.META['HTTP_HOST']+request.META['SCRIPT_NAME']

  objs = {'auto':[],'send':[],'wrong':[]}
  for t in queryset:
    if t.state in ['draft','cancelled']:

      # SECURITY CHECK

      if not t.getTestHosts_for_test.all():
        objs['wrong'] += ['%s/admin/%s/test/%d/ \n  reason: No hosts assigned.\n'%(url,app,t.id)]
      elif not t.getTestSites_for_test.all():
        objs['wrong'] += ['%s/admin/%s/test/%d/ \n  reason: No sites assigned.\n'%(url,app,t.id)]
      elif not t.getTestUsers_for_test.all():
        objs['wrong'] += ['%s/admin/%s/test/%d/ \n  reason: No users assigned.\n'%(url,app,t.id)]
      elif not t.getTestDspatterns_for_test.all():
        objs['wrong'] += ['%s/admin/%s/test/%d/ \n  reason: No dspatterns assigned.\n'%(url,app,t.id)]

      # GOOD TESTS

      elif t.cloned > CLONED_THRESHOLD:
        t.state = 'tobescheduled'
        objs['auto'] += ['%s/admin/%s/test/%d/ \n Starttime: %s'%(url,app,t.id,t.starttime.ctime())]
      else:
        t.state='unapproved'
        objs['send'] += ['%s/admin/%s/test/%d/ \n Starttime: %s'%(url,app,t.id,t.starttime.ctime())]

      t.save()

  msg = 'Tests sent for approval by %s:\n\n'%(request.user.username)
  message_bit = ''
  if objs['send']:
    msg += 'TO BE APPROVED:\n'
    msg += '\n    '.join(objs['send'])
    message_bit += str(len(objs['send']))+' test(s) sent for approval,'
  if objs['auto']:
    msg += 'AUTOAPPROVED:\n'
    msg += '\n    '.join(objs['auto'])
    message_bit += str(len(objs['auto']))+' test(s) autoapproved,'
  if objs['wrong']:
    msg += 'WRONG:\n'
    msg += '\n    '.join(objs['wrong'])
    message_bit += str(len(objs['wrong']))+' test(s) with wrong format ( check your email for details!),'

  mail_admins('[HammerCloud][NEW]',msg,fail_silently=True)
  self.message_user(request, message_bit)


