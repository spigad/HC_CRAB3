from django.db import models
from hc.core.base.models.abstract import *

from hc.core.base.rss.abstract import HCFeedBase

##
## SIMPLE CLASSES
##
## *Cloud
## *Dspattern
## *File
## *Host
##

class Cloud(CloudBase):
  pass
class Dspattern(DspatternBase):
  pass
class File(FileBase):
  pass
class Host(HostBase):
  pass


##
## SITE CLASSES
##
## *Site
##

class Site(SiteBase):
  pass


##
## TEMPLATE CLASSES
##
## *Template
## *TemplateCloud
## *TemplateDspattern
## *TemplateHost
## *TemplateSite
## *TemplateUser
##

class Template(TemplateBase):

  INPUTTYPE_CHOICES = (
    (u'DQ2_LOCAL', u'DQ2_LOCAL'),
    (u'DQ2_COPY', u'DQ2_COPY'),
    (u'FILE_STAGER', u'FILE_STAGER'),
    (u'PANDA', u'PANDA'),
    (u'DIRECT', u'DIRECT'),
    (u'TAG', u'TAG'),
    (u'null', u'null'),
  )

  inputtype = models.CharField(choices = INPUTTYPE_CHOICES, max_length = 15)

class TemplateCloud(TemplateCloudBase):
  pass
class TemplateDspattern(TemplateDspatternBase):
  pass
class TemplateHost(TemplateHostBase):
  pass
class TemplateSite(TemplateSiteBase):
  pass
class TemplateUser(TemplateUserBase):
  pass

##
## TEST CLASSES
##
## *Test
## *TestCloud
## *TestDspattern
## *TestJournal
## *TestHost
## *TestSite
## *TestUser
##

class Test(TestBase):

  INPUTTYPE_CHOICES = (
    (u'null', u'null'),
  )

  inputtype = models.CharField(choices = INPUTTYPE_CHOICES, max_length = 15)

class TestCloud(TestCloudBase):
  pass
class TestDspattern(TestDspatternBase):
  pass
class TestHost(TestHostBase):
  pass
class TestJournal(TestJournalBase):
  pass
class TestSite(TestSiteBase):
  pass
class TestUser(TestUserBase):
  pass

##
## RESULT CLASSES
## 
## *Result
##

class Result(ResultBase):
  exit_status_1 = models.IntegerField(null=True)
  exit_status_2 = models.IntegerField(null=True)
  inds = models.CharField(max_length=1023)
  outds = models.CharField(max_length=1023)
  output_location = models.CharField(max_length=255)
  wallclock = models.IntegerField(null=True)
  numevents = models.IntegerField(null=True)
  numfiles = models.IntegerField(null=True)
  percent_cpu = models.IntegerField(null=True)
  jdl_time = models.DateTimeField(null=True)
  ganga_number_of_files = models.IntegerField(null=True)
  backend_id = models.CharField(max_length=1023)
  backend_reason = models.CharField(max_length=1023)
  fixed = models.IntegerField(null=True)
  net_eth_rx_preathena = models.IntegerField(null=True)
  net_eth_rx_postathena = models.IntegerField(null=True)
  pandatime1 = models.IntegerField(null=True)
  pandatime2 = models.IntegerField(null=True)
  pandatime3 = models.IntegerField(null=True)
  pandatime4 = models.IntegerField(null=True)
  arch = models.CharField(max_length=511)
  actual_ce = models.CharField(max_length=127, null=True)
  logfile_guid = models.CharField(max_length=63, null=True)

##
## METRIC CLASSES
##
## *MetricType
## *Metric
##

class MetricType(MetricTypeBase):
  pass
class Metric(MetricBase):
  pass
class SiteMetric(SiteMetricBase):
  pass
class TestMetric(TestMetricBase):
  pass
class MetricPermission(MetricPermissionBase):
  pass

##
## USG CLASSES
##
## *UsgSlice
## *UsgSite
##

class UsgSlice(UsgSliceBase):
  pass
class UsgSite(UsgSiteBase):
  pass

##
## SUMMARY CLASSES
##
## *SummaryMetric
## *SummaryRobot
## *SummaryTest
## *SummaryTestSite
##

class SummaryRobot(SummaryRobotBase):
  pass
class SummaryTest(SummaryTestBase):
  pass
class SummaryTestSite(SummaryTestSiteBase):
  pass

##
## FEED CLASSES
##
## *HCFeed
##

class HCFeed(HCFeedBase):
  pass
