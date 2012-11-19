import os
import resource

# Set resource limits to prevent machine crashes and debug.
resource.setrlimit(resource.RLIMIT_CPU, (10, 60))  # Seconds
resource.setrlimit(resource.RLIMIT_AS, (1073741824, 2147483648))  # Bytes

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'hc.settings')

from django.core.wsgi import get_wsgi_application
application = get_wsgi_application()
