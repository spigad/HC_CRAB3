from django.conf import settings

"""Router for the database access.

Allows the access to one database per app, distributing the load.
"""

PLUGINS = [app.split('.')[1] for app in settings.INSTALLED_APPS
           if app.startswith('hc') and 'core' not in app]


class PrimaryRouter(object):
    """Router for the database access."""

    def db_for_read(self, model, **hints):
        """Find database for read."""
        if model._meta.app_label in PLUGINS:
            return model._meta.app_label
        return 'default'

    def db_for_write(self, model, **hints):
        """Find database for write."""
        if model._meta.app_label in PLUGINS:
            return model._meta.app_label
        return 'default'

    def allow_relation(self, obj1, obj2, **hints):
        """The router does not forbid relations."""
        return None

    def allow_syncdb(self, db, model):
        """Sync each model to its database."""
        if db in PLUGINS:
            return model._meta.app_label == db
        elif model._meta.app_label in PLUGINS:
            return False
        return None
