from django.contrib.auth.models import User

def getTemplateUserNameStringAdmin(template_user):
  
  try:
    name = User.objects.get(pk=template_user.user).username
  except:
    name = '_not_defined_'
  return name
getTemplateUserNameStringAdmin.short_description = 'User'

