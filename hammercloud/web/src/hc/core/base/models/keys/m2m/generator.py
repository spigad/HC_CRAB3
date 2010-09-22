from django.db import models
from django.db.models.fields import FieldDoesNotExist


def generateM2M(cls,obj1_name,obj2_name,m2m_to_obj1,dic):

  Obj1 = getattr(cls,obj1_name)
  Obj2 = getattr(cls,obj2_name)

  if Obj1 and Obj2:

    try:
      Obj2._meta.get_field(m2m_to_obj1)
    except FieldDoesNotExist:

      if not dic:
        m2m_model = models.ManyToManyField(Obj1,related_name='get'+Obj2.__name__+'s_for_'+m2m_to_obj1)
      elif dic.has_key('null'):
        m2m_model = models.ManyToManyField(Obj1,related_name='get'+Obj2.__name__+'s_for_'+m2m_to_obj1,null=True)

      Obj2.add_to_class(
        m2m_to_obj1,
        m2m_model
      )
      setattr(cls,obj2_name,Obj2)

  return cls

