# Django settings for hc project.

DEBUG = False
TEMPLATE_DEBUG = DEBUG

ADMINS = (
    ('Mario', 'mario.ubeda.garcia@cern.ch'),
)

MANAGERS = ADMINS

DATABASES = {
    'default': {
        'ENGINE': 'mysql', 
        'NAME': 'hc_core',                      
        'USER': 'gangarbt',                     
        'PASSWORD': 'chinFanill0',              
        'HOST': 'localhost', 
        'PORT': '3306',      
    },
    'atlas': {
        'ENGINE': 'mysql',
        'NAME': 'hc_atlas',
        'USER': 'gangarbt',
        'PASSWORD': 'chinFanill0',
        'HOST': 'localhost',
        'PORT': '3306',
    },
    'cms': {
        'ENGINE': 'mysql',
        'NAME': 'hc_cms',
        'USER': 'gangarbt',
        'PASSWORD': 'chinFanill0',
        'HOST': 'localhost',
        'PORT': '3306',
    },
    'lhcb': {
        'ENGINE': 'mysql',
        'NAME': 'hc_lhcb',
        'USER': 'gangarbt',
        'PASSWORD': 'chinFanill0',
        'HOST': 'localhost',
        'PORT': '3306',
    }
}

DATABASE_ROUTERS = ['hc.router.PrimaryRouter']

#DATABASE_TABLE_ENGINE

# Local time zone for this installation. Choices can be found here:
# http://en.wikipedia.org/wiki/List_of_tz_zones_by_name
# although not all choices may be available on all operating systems.
# On Unix systems, a value of None will cause Django to use the same
# timezone as the operating system.
# If running in a Windows environment this must be set to the same as your
# system time zone.
TIME_ZONE = 'Europe/Zurich'

# Language code for this installation. All choices can be found here:
# http://www.i18nguy.com/unicode/language-identifiers.html
LANGUAGE_CODE = 'en-us'

SITE_ID = 1

LOGIN_URL = '/hc/accounts/login'

# If you set this to False, Django will make some optimizations so as not
# to load the internationalization machinery.
USE_I18N = True

# If you set this to False, Django will not format dates, numbers and
# calendars according to the current locale
USE_L10N = True

# Absolute path to the directory that holds media.
# Example: "/home/media/media.lawrence.com/"
MEDIA_ROOT = '/data/hammercloud/web/media/'

# URL that handles the media served from MEDIA_ROOT. Make sure to use a
# trailing slash if there is a path component (optional in other cases).
# Examples: "http://media.lawrence.com", "http://example.com/media/"
MEDIA_URL = 'http://lxvm0351.cern.ch/media/'

# URL prefix for admin media -- CSS, JavaScript and images. Make sure to use a
# trailing slash.
# Examples: "http://foo.com/media/", "/media/".
ADMIN_MEDIA_PREFIX = '/media/admin/'

# Make this unique, and don't share it with anybody.
SECRET_KEY = 'n*l@j-#3f#%0o^u=h5s5o+s6o47xur&ek%1-m=ei#v78b*q5#r'

# List of callables that know how to import templates from various sources.
TEMPLATE_LOADERS = (
    'django.template.loaders.filesystem.Loader',
    'django.template.loaders.app_directories.Loader',
#     'django.template.loaders.eggs.Loader',
)

MIDDLEWARE_CLASSES = (
    'django.middleware.common.CommonMiddleware',
    'django.contrib.sessions.middleware.SessionMiddleware',
    'django.middleware.csrf.CsrfViewMiddleware',
    'django.contrib.auth.middleware.AuthenticationMiddleware',
    'django.contrib.messages.middleware.MessageMiddleware',
)

ROOT_URLCONF = 'hc.urls'

TEMPLATE_DIRS = (
    # Put strings here, like "/home/html/django_templates" or "C:/www/django/templates".
    # Always use forward slashes, even on Windows.
    # Don't forget to use absolute paths, not relative paths.
    '/data/hammercloud/web/templates',
    
    
)

INSTALLED_APPS = (
    'hc.core',
    'hc.atlas',
    'hc.cms',
#    'hc.lhcb',
    'django.contrib.auth',
    'django.contrib.contenttypes',
    'django.contrib.sessions',
#    'django.contrib.sites',
    'django.contrib.messages',
    'django.contrib.admin',
)
