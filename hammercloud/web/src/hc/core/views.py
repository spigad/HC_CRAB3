from django.http import HttpResponse
from django.template import loader, RequestContext
from django.conf import settings


def portal(request):

  apps = []

  for app in settings.INSTALLED_APPS:
    if not app.startswith('django'):
      app = app.split('.')[1]
      if app != 'core':
        apps.append(app)    
    
  t = loader.get_template('core/portal/index.html')
  c = RequestContext(request,
                     {'apps': apps},
                     )
  return HttpResponse(t.render(c))

