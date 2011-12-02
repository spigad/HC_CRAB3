from django.http import HttpResponse
from django.template import loader, RequestContext
from django.conf import settings
from django.views.decorators.cache import cache_page

@cache_page(60 * 60 * 24)
def portal(request):

  apps = []

  for app in settings.INSTALLED_APPS:
    if app.startswith('hc'):
      app = app.split('.')[1]
      if app != 'core':
        apps.append(app)    
    
  t = loader.get_template('core/portal/index.html')
  c = RequestContext(request,
                     {'apps': apps},
                     )
  return HttpResponse(t.render(c))

