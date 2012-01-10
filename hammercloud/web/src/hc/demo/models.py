from django.db import models
from hc.core.base.models.abstract import *

from hc.core.base.rss.abstract import *

##
## SIMPLE CLASSES
##
## *Alarm
## *Backend
## *Cloud
## *CloudOption
## *Dspattern
## *GangaBin
## *Host
## *InputType
## *JobTemplate
## *OptionFile
## *TestOption
## *UserCode 
## 

class Alarm(AlarmBase):
  pass
class Backend(BackendBase):
  pass
class Cloud(CloudBase):
  pass
class CloudOption(CloudOptionBase):
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
## *SiteOption
##

class Site(SiteBase):
  pass

class SiteOption(SiteOptionBase):
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
## *TestLog
## *TestSite
## *TestSiteAlarm
## *TestState
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
class TestLog(TestLogBase):
  pass
class TestSite(TestSiteBase):
  pass
class TestSiteAlarm(TestSiteAlarmBase):
  pass
class TestState(TestStateBase):
  pass
class TestUser(TestUserBase):
  pass

##
## RESULT CLASSES
## 
## *Result
##

class Result(ResultBase):
  cms_field = models.FloatField(blank=True,null=True)

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
## *SummaryEvolution
## *SummaryRobot
## *SummaryTest
## *SummaryTestSite
##

class SummaryEvolution(SummaryEvolutionBase):
  pass
class SummaryRobot(SummaryRobotBase):
  pass
class SummaryTest(SummaryTestBase):
  cms_field = models.FloatField(blank=True,null=True)
class SummaryTestSite(SummaryTestSiteBase):
  cms_field = models.FloatField(blank=True,null=True)

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

