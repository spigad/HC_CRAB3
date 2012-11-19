from django.conf import settings

"""Delete sessionid and csrftoken cookies on logout.

Copied from: https://gist.github.com/1367640"""


class DeleteSessionOnLogoutMiddleware(object):
    """Middleware class to remove the cookies to improve varnish hit rate."""

    def process_view(self, request, view_func, view_args, view_kwargs):
        """Set _delete_session for cookie removal."""
        try:
            view_name = '.'.join((view_func.__module__, view_func.__name__))
            request._delete_session = view_name in ('django.contrib.admin.sites.logout',
                                                    'django.contrib.auth.views.logout')
        except AttributeError:
            pass

    def process_response(self, request, response):
        """If _delete_session is set by process_view, remove cookies."""
        if getattr(request, '_delete_session', False):
            response.delete_cookie(settings.CSRF_COOKIE_NAME,
                                   domain=settings.CSRF_COOKIE_DOMAIN)
            response.delete_cookie(settings.SESSION_COOKIE_NAME,
                                   settings.SESSION_COOKIE_PATH,
                                   settings.SESSION_COOKIE_DOMAIN)
        return response
