from django.contrib.auth.models import User

def getTestUserNameStringAdmin(test_user):
  
  try:
    name = User.objects.get(pk=test_user.user.id).username
  except:
    name = '_not_defined_'
  return name
getTestUserNameStringAdmin.short_description = 'User'

