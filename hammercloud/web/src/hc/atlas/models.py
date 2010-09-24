from django.db import models
from hc.core.base.models.abstract import *

from hc.core.base.rss.abstract import *

#class MetricPerm(MetricPermBase):
#  pass

##
## SIMPLE CLASSES
##
## *Backend
## *Cloud
## *Dspattern
## *GangaBin
## *Host
## *InputType
## *JobTemplate
## *OptionFile
## *TestOption
## *UserCode 
## 

class Backend(BackendBase):
  pass
class Cloud(CloudBase):
  pass
class Dspattern(DspatternBase):
  pass
class GangaBin(GangaBinBase):
  pass
class Host(HostBase):
  pass
class InputType(InputTypeBase):
  pass
class JobTemplate(JobTemplateBase):
  pass
class MetricPerm(MetricPermBase):
  pass
class OptionFile(OptionFileBase):
  pass
class TestOption(TestOptionBase):
  pass
class UserCode(UserCodeBase):
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
## *TemplateBackend
## *TemplateCloud
## *TemplateDspattern
## *TemplateHost
## *TemplateSite
## *TemplateUser
##

class Template(TemplateBase):
  pass
class TemplateBackend(TemplateBackendBase):
  pass
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
## *TestBackend
## *TestCloud
## *TestDspattern
## *TestHost
## *TestSite
## *TestUser
##

class Test(TestBase):
  pass
class TestBackend(TestBackendBase):
  pass
class TestCloud(TestCloudBase):
  pass
class TestDspattern(TestDspatternBase):
  pass
class TestHost(TestHostBase):
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
  exit_status_1         = models.IntegerField(null=True)
  exit_status_2         = models.IntegerField(null=True)
  inds                  = models.CharField(max_length=1023)
  outds                 = models.CharField(max_length=1023)
  output_location       = models.CharField(max_length=255)
  wallclock             = models.IntegerField(null=True)
  numevents             = models.IntegerField(null=True)
  numfiles              = models.IntegerField(null=True)
  percent_cpu           = models.IntegerField(null=True)
  jdl_time              = models.DateTimeField(null=True)
  ganga_number_of_files = models.IntegerField(null=True)
  backend_id            = models.CharField(max_length=1023)
  backend_reason        = models.CharField(max_length=1023)
  fixed                 = models.IntegerField(null=True)
  net_eth_rx_preathena  = models.IntegerField(null=True)
  net_eth_rx_postathena = models.IntegerField(null=True)
  pandatime1            = models.IntegerField(null=True)
  pandatime2            = models.IntegerField(null=True)
  pandatime3            = models.IntegerField(null=True)
  pandatime4            = models.IntegerField(null=True)
  arch                  = models.CharField(max_length=511)
  actual_ce             = models.CharField(max_length=127, null=True)
  logfile_guid          = models.CharField(max_length=63, null=True)

##
## METRIC CLASSES
##
## *MetricType
## *Metric
## *SiteMetric
## *TestMetric
##

class MetricType(MetricTypeBase):
  pass
class Metric(MetricBase):
  pass
class SiteMetric(SiteMetricBase):
  pass
class TestMetric(TestMetricBase):
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

class AppFeed(AppFeedBase):
  pass
class CloudFeed(CloudFeedBase):
  pass
class SiteFeed(SiteFeedBase):
  pass
class TemplateFeed(TemplateFeedBase):
  pass
class TestFeed(TestFeedBase):
  pass

