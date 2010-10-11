#from django.core.mail import mail_admins
from django.core.mail import send_mass_mail
from django.core.urlresolvers import reverse
from django.contrib.auth.models import User

def method(self, request, queryset):

  app  = self.__module__.split('.')[1]
  objs = {'cancelled':[],'wrong':[],'notify':[]}
  allowed_states = ['draft','unapproved','tobescheduled','scheduled']

  url = 'http://'+request.META['HTTP_HOST']+request.META['SCRIPT_NAME']

  for t in queryset:
    if t.state in allowed_states:
      t.state = 'cancelled'
      objs['cancelled'] += ['%s/admin/%s/test/%d/ \n'%(url,app,t.id)]
      t.save()
      # If we cancell, we notify users.
      objs['notify'] += [t]
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

#  [User.objects.filter(username=tu.username)[0].email for tu in t.getTestUsers_for_test.all() for t in objs['notify']]

  users = [u.email for u in User.objects.filter(groups__name='%s_admin'%(app))]
  message1 = ('[HammerCloud][CANCEL]',msg,'hammercloud@mail.cern.ch',users)
  
  
  send_mass_mail((message1,), fail_silently=False)  


#  mail_admins('[HammerCloud][CANCEL]',msg,fail_silently=True)
  self.message_user(request, message_bit)

