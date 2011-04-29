from django.conf import settings

class PrimaryRouter(object):

  def db_for_read(self, model, **hints):

    '''
    If the label belongs to a plugin, it reads from the pluign specific DB
    Otherwise, it reads from the defautl DB
    '''

#    PLUGINS = ['atlas','cms','lhcb']
    PLUGINS = [ app.split('.')[1] for app in settings.INSTALLED_APPS if app.startswith('hc') and not 'core' in app]

    if model._meta.app_label in PLUGINS:
      return model._meta.app_label

    return None

  def db_for_write(self, model, **hints):

    '''
    If the label belongs to a plugin, it reads from the pluign specific DB
    Otherwise, it reads from the defautl DB
    '''

#    PLUGINS = ['atlas','cms','lhcb']
    PLUGINS = [ app.split('.')[1] for app in settings.INSTALLED_APPS if app.startswith('hc') and not 'core' in app]

    if model._meta.app_label in PLUGINS:
      return model._meta.app_label

    return None

  def allow_relation(self, obj1, obj2, **hints):

    '''
    Literally: no opinion about objects relations and foreign keys.
    '''
   
    return None

  def allow_syncdb(self, db, model):

    '''
    Sync every app with the right database
    '''

#    PLUGINS = ['atlas','cms','lhcb']
    PLUGINS = [ app.split('.')[1] for app in settings.INSTALLED_APPS if app.startswith('hc') and not 'core' in app]

    if db in PLUGINS:
      return model._meta.app_label == db
    elif model._meta.app_label in PLUGINS:
      return False
    return None

