import os

SOURCES_FILTER = r'.*\\.py\\Z(?ms)|.*\\.html\\Z(?ms)'

# Setup settings.
os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'hc.settings')

# Set up the monitoring for file changes only in debug.
from django.conf import settings

if settings.DEBUG:
    import hc.monitor
    import re
    for dirname, _, files in os.walk(os.path.dirname(__file__)):
        for name in  [f for f in files if re.match(SOURCES_FILTER, f)]:
            hc.monitor.track(os.path.join(dirname, name))
    hc.monitor.start(interval=5.0)

# Start the WSGi application.
from django.core.wsgi import get_wsgi_application
application = get_wsgi_application()
