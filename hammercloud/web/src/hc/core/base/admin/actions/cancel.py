from django.core.mail import mail_admins
from django.core.urlresolvers import reverse

def method(self, request, queryset):

  app  = self.__module__.split('.')[1]
  objs = {'cancelled':[],'wrong':[]}
  allowed_states = ['draft','unapproved','tobescheduled','scheduled']

  url = 'http://'+request.META['HTTP_HOST']+request.META['SCRIPT_NAME']

  for t in queryset:
    if t.state in allowed_states:
      t.state = 'cancelled'
      objs['cancelled'] += ['%s/admin/%s/test/%d/ \n'%(url,app,t.id)]
      t.save()
    else:
      objs['wrong']     += ['%s/admin/%s/test/%d/ \n  reason: Not allowed state to cancel.\n'%(url,app,t.id)]

  msg = 'Tests cancelled by %s:\n\n'%(request.user.username)
  message_bit = ''
  if objs['cancelled']:
    msg += 'CANCELLED:\n'
    msg += '\n    '.join(objs['cancelled'])
    message_bit += str(len(objs['cancelled']))+' test(s) cancelled,'
  if objs['wrong']:
    msg += 'WRONG:\n'
    msg += '\n    '.join(objs['wrong'])
    message_bit += str(len(objs['wrong']))+' test(s) could not be cancelled ( check your email for details!).'

  mail_admins('[HammerCloud][CANCEL]',msg,fail_silently=True)
  self.message_user(request, message_bit)

