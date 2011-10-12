from django.db import models

from datetime import datetime, timedelta
from time import strftime

class EmptyField(models.Field):

    description = "Empty field used to validate unique_together clauses"

    def __init__(self, *args, **kwargs):
        super(EmptyField, self).__init__(*args, **kwargs)

class UnixTimestampField(models.DateTimeField):
    """UnixTimestampField: creates a DateTimeField that is represented on the
    database as a TIMESTAMP field rather than the usual DATETIME field.
    """
    def __init__(self, null=False, blank=False, **kwargs):
        super(UnixTimestampField, self).__init__(**kwargs)
        # default for TIMESTAMP is NOT NULL unlike most fields, so we have to
        # cheat a little:
        self.blank, self.isnull = blank, null
        self.null = True # To prevent the framework from shoving in "not null".
       
    def db_type(self, connection=None):
        typ=['TIMESTAMP']
        # See above!
        if self.isnull:
            typ += ['NULL']
        if self.auto_created:
            typ += ['default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP']
        return ' '.join(typ)
   
    def to_python(self, value):
        return datetime.from_timestamp(value)
   
    def get_db_prep_value(self, value, connection=None, prepared=False):
        if value==None:
            return None
        return strftime('%Y%m%d%H%M%S',value.timetuple())
