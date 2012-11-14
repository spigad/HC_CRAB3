from django.http import Http404
from hc.core.utils.generic.class_func import custom_import


def dispatcher(request, app, *args, **kwargs):
    """Loads the proper view function from the reqeusted app."""
    try:
        func = kwargs.pop('func')
        m = custom_import('hc.' + app + '.views.' + func)
        return m(request, *args, **kwargs)
    except (KeyError, TypeError):
        raise Http404
