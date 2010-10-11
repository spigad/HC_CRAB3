#from django.contrib.auth.models import User

def getTestLogCommentStringAdmin(test_log): 
  comment = test_log.comment
  if len(comment) > 60:
    comment = comment[:60]+'...'
  return comment
getTestLogCommentStringAdmin.short_description = 'Comment'

#def getTestJournalUserNameStringAdmin(test_journal): 
#  try:
#    name = User.objects.get(pk=test_journal.user).username
#  except:
#    name = '_not_defined_'
#  return name
#getTestJournalUserNameStringAdmin.short_description = 'User'

