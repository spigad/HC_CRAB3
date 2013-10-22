from django.http import Http404
from hc.core.utils.generic.class_func import custom_import

"""Dispatcher of the view request to the app view implementation."""

# TODO(rmedrano): move this to Class Based Generic Views.


def dispatcher(request, app, *args, **kwargs):
    """Loads the proper view function from the requested app."""
    try:
        func = kwargs.pop('func')
        m = custom_import('hc.' + app + '.views.' + func)
        return m(request, *args, **kwargs)
    except (ImportError, KeyError, TypeError):
        raise
