import os
import sys
import resource

# Set resource limits to prevent machine crashes
resource.setrlimit(resource.RLIMIT_CPU, (10, 60)) # Seconds
resource.setrlimit(resource.RLIMIT_AS, (2147483648, 4294967296)) # Bytes

# This list of paths ends reversed and prepended to the PYTHONPATH
sys.path.insert(0, '/data/hc/external/lib/python2.6/site-packages/memcache_toolbar')
sys.path.insert(0, '/data/hc/external/lib/python2.6/site-packages/debug_toolbar')
sys.path.insert(0, '/data/hc/external/lib/python2.6/site-packages')
sys.path.insert(0, '/data/hc/external/django/Django-1.4')
sys.path.insert(0, '/data/hc/web/src')
sys.path.insert(0, '/data/hc/apps')

os.environ['DJANGO_SETTINGS_MODULE'] = 'hc.settings'

import django.core.handlers.wsgi
application = django.core.handlers.wsgi.WSGIHandler()
