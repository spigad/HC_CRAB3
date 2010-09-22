from django.core.mail import mail_admins

def method(self, request, queryset):

  app  = self.__module__.split('.')[1]
  url = 'http://'+request.META['HTTP_HOST']+request.META['SCRIPT_NAME']
  objs = {'paused':[],'wrong':[]}
  allowed_states = ['running']

  for t in queryset:
    if t.state in allowed_states:
      if not t.pause:
        t.pause = 1
        objs['paused'] += ['%s/admin/%s/test/%d/ \n'%(url,app,t.id)]
        t.save()
      else:
        objs['wrong']     += ['%s/admin/%s/test/%d/ \n  reason: already paused test.\n'%(url,app,t.id)]
    else:
      objs['wrong']     += ['%s/admin/%s/test/%d/ \n  reason: Not allowed state to pause.\n'%(url,app,t.id)]

  msg = 'Tests paused by %s:\n\n'%(request.user.username)
  message_bit = ''
  if objs['paused']:
    msg += 'PAUSED:\n'
    msg += '\n    '.join(objs['paused'])
    message_bit += str(len(objs['paused']))+' test(s) paused,'
  if objs['wrong']:
    msg += 'WRONG:\n'
    msg += '\n    '.join(objs['wrong'])
    message_bit += str(len(objs['wrong']))+' test(s) could not be paused ( check your email for details!).'

  mail_admins('[HammerCloud][PAUSE]',msg,fail_silently=True)
  self.message_user(request, message_bit)

