from django.conf import settings
from django.http import get_host, HttpResponsePermanentRedirect

"""Django middleware to redirect to a SSL url.

This is used mainly for the admin panel, but could be user for all the site.
Copied from: http://djangosnippets.org/snippets/880/"""


class SSLRedirect(object):
    """Middleware to redirect in some situations to a HTTPS context."""

    def process_view(self, request, view_func, view_args, view_kwargs):
        """Before answering to the request, check if SSL is needed."""
        if settings.DEBUG:
            return request
        if 'SSL' in view_kwargs:
            secure = view_kwargs['SSL']
            del view_kwargs['SSL']
        else:
            secure = False
        if not secure == self._is_secure(request):
            return self._redirect(request, secure)

    def _is_secure(self, request):
        """Check if we are in a HTTPS context or not."""
        if request.is_secure():
            return True
        if 'HTTP_X_FORWARDED_SSL' in request.META:
            return request.META['HTTP_X_FORWARDED_SSL'] == 'on'
        return False

    def _redirect(self, request, secure):
        """Performs the actual redirection."""
        protocol = secure and 'https' or 'http'
        newurl = "%s://%s%s" % (protocol, get_host(request), request.get_full_path())
        if settings.DEBUG and request.method == 'POST':
            raise RuntimeError('Cannot redirect to HTTPS while having POST.')
        return HttpResponsePermanentRedirect(newurl)
