from django.db import models
from django.db.models.base import ModelBase

from hc.core.base.models.keys import relation

from hc.core.base.models.keys.fk.generator import generateFK
from hc.core.base.models.keys.m2m.generator import generateM2M

def checkFK(cls):

  for fk_tuple in relation.FK_LIST:
    
    obj1,obj2,fk_to_obj1,dic = fk_tuple
    cls = generateFK(cls,obj1,obj2,fk_to_obj1,dic)

  return cls

def checkM2M(cls):

  for fk_tuple in relation.M2M_LIST:

    obj1,obj2,m2m_to_obj1,dic = fk_tuple
    cls = generateM2M(cls,obj1,obj2,m2m_to_obj1,dic)

  return cls


class MetaCreator(ModelBase):

  #Having this here is ugly. The walkarround is worse.
  Alarm, Backend, Cloud, CloudOption, Dspattern, Host, Site, SiteOption = None, None, None, None, None, None, None, None
  GangaBin, InputType, JobTemplate, OptionFile, TestOption, UserCode = None, None, None, None, None, None
  Metric, MetricType, MetricPerm = None, None, None
  Result = None
  BlacklistEvent = None
  SiteMetric, TestMetric = None, None
  SummaryTest, SummaryTestSite, SummaryRobot, SummaryEvolution = None, None, None, None
  Template, TemplateBackend, TemplateCloud, TemplateDspattern, TemplateHost, TemplateSite, TemplateUser = None, None, None, None, None, None, None
  Test, TestBackend, TestCloud, TestDspattern, TestHost, TestLog, TestSite, TestState, TestUser = None, None, None, None, None, None, None, None, None
  TestSiteAlarm = None
  UsgSite = None
  MessageBusEvent = None

  #RSS
  CloudFeed,SiteFeed,TemplateFeed,TestFeed = None,None,None,None

  def __new__(cls, name, bases, attrs):

    model = super(MetaCreator, cls).__new__(cls, name, bases, attrs)
 
    for b in bases:
      setattr(cls,b.__name__[:-4],model)

      if b.__name__ in relation.BASE_CLASS_NAMES_FK_RELATED:
#        setattr(cls,b.__name__[:-4],model)
        cls = checkFK(cls)

      if b.__name__ in relation.BASE_CLASS_NAMES_M2M_RELATED:
#        setattr(cls,b.__name__[:-4],model)
        cls = checkM2M(cls)

      if relation.UNIQUE_TOGETHER_DIC.has_key(b.__name__):
 
        model._meta.unique_together.append(relation.UNIQUE_TOGETHER_DIC[b.__name__])

    return model  

