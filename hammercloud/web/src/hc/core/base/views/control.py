from django.contrib.auth import logout as logout_user
from django.http import Http404, HttpResponseRedirect

"""View handlers for the login/logout."""


def logout(request):
    """Logs out the user and redirects to the following URL.

    The URL must have a GET parameter to redirect to.
    """
    logout_user(request)
    following = request.GET.get('next', None)
    if following:
        return HttpResponseRedirect(following)
    else:
        raise Http404
