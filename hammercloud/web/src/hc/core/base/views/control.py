from django.contrib.auth import logout as logout_user
from django.http import Http404,HttpResponseRedirect


#######################################################
## LOGIN VIEWS
#######################################################

def logout(request):
  logout_user(request)
  next = request.GET.get('next', None)
  if next:
    return HttpResponseRedirect(next)
  else:
    raise Http404

