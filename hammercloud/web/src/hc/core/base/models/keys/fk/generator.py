from django.db import models
from django.db.models.fields import FieldDoesNotExist


def generateFK(cls,obj1_name,obj2_name,fk_to_obj1,dic):

  Obj1 = getattr(cls,obj1_name)
  Obj2 = getattr(cls,obj2_name)

  if Obj1 and Obj2:

    try:
      Obj2._meta.get_field(fk_to_obj1)
    except FieldDoesNotExist:

      if not dic:
        fk_model = models.ForeignKey(Obj1,db_column=fk_to_obj1,related_name='get'+Obj2.__name__+'s_for_'+fk_to_obj1)
      elif dic.has_key('null'):
        fk_model = models.ForeignKey(Obj1,db_column=fk_to_obj1,related_name='get'+Obj2.__name__+'s_for_'+fk_to_obj1,null=True)
      elif dic.has_key('unique'):
        fk_model = models.ForeignKey(Obj1,db_column=fk_to_obj1,related_name='get'+Obj2.__name__+'s_for_'+fk_to_obj1,unique=True)

      Obj2.add_to_class(
        fk_to_obj1,
        fk_model
      )
      setattr(cls,obj2_name,Obj2)

  return cls


