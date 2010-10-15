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
      objs['wrong']  += ['%s/admin/%s/test/%d/ \n  reason: Not allowed state to cancel.\n'%(url,app,t.id)]

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

  test_users = [t.getTestUsers_for_test.all() for t in objs['notify'] if t.getTestUsers_for_test.all()]

  users = []

  for tus in test_users:
    for tu in tus:
      user = User.objects.filter(username=tu.user)
      if user and not user[0].email in users:
        users += [user[0].email]

  admins = [u.email for u in User.objects.filter(groups__name='%s_admin'%(app))]
  message1 = ('[HammerCloud][%s][CANCEL]'%(app.upper()),msg,'hammercloud@mail.cern.ch',admins)
  
  message2 = ('[HammerCloud][%s][CANCEL]'%(app.upper()),msg,'hammercloud@mail.cern.ch',users)

  send_mass_mail((message1,message2), fail_silently=False)  


  self.message_user(request, message_bit)

