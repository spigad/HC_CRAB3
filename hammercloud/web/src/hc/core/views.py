from django.conf import settings
from django.http import HttpResponse
from django.template import loader, RequestContext

"""Main module for the common views.

This module only renders the portal view, the rest are in the base package.
"""


def portal(request):
    """View handler for the home page, shows the list of HC apps."""
    apps = []

    for app in settings.INSTALLED_APPS:
        if app.startswith('hc'):
            app = app.split('.')[1]
            if app != 'core':
                apps.append(app)

    t = loader.get_template('core/portal/index.html')
    c = RequestContext(request, {'apps': apps})
    return HttpResponse(t.render(c))
