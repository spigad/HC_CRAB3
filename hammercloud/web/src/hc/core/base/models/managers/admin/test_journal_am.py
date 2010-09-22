#from django.contrib.auth.models import User

def getTestJournalCommentStringAdmin(test_journal): 
  comment = test_journal.comment
  if len(comment) > 60:
    comment = comment[:60]+'...'
  return comment
getTestJournalCommentStringAdmin.short_description = 'Comment'

#def getTestJournalUserNameStringAdmin(test_journal): 
#  try:
#    name = User.objects.get(pk=test_journal.user).username
#  except:
#    name = '_not_defined_'
#  return name
#getTestJournalUserNameStringAdmin.short_description = 'User'

