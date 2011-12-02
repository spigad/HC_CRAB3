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
  #[report]
  closed            = models.CharField(max_length=3, blank=True, null=True)
  destination       = models.CharField(max_length=511, blank=True, null=True)
  jobId             = models.IntegerField(blank=True,null=True)
  lbTimestamp       = models.DateTimeField(blank=True,null=True)
  processStatus     = models.CharField(max_length=511, blank=True, null=True)
  scheduledAtSite   = models.DateTimeField(blank=True,null=True)
  scheduler         = models.CharField(max_length=511, blank=True,null=True)
  schedulerId       = models.CharField(max_length=511, blank=True,null=True)
  schedulerParentId = models.CharField(max_length=511, blank=True,null=True)
  service           = models.CharField(max_length=511, blank=True,null=True)
  state             = models.CharField(max_length=511, blank=True,null=True)
  status            = models.CharField(max_length=511, blank=True,null=True)
  statusReason      = models.CharField(max_length=511, blank=True,null=True)
  statusScheduler   = models.CharField(max_length=511, blank=True,null=True)
  submission        = models.IntegerField(blank=True,null=True)
#  submissionTime    = models.DateTimeField(blank=True,null=True)
  taskId            = models.IntegerField(blank=True,null=True)

  #[StorageParams]
  stats      = models.CharField(max_length=511, blank=True,null=True)
  cache_hint = models.CharField(max_length=511, blank=True,null=True)
  enabled    = models.CharField(max_length=511, blank=True,null=True)
  read_hint  = models.CharField(max_length=511, blank=True,null=True)

  #[CrabTiming]
  ExeTime       = models.FloatField(blank=True,null=True)
  WrapperTime   = models.FloatField(blank=True,null=True)
  UserCPUTime   = models.FloatField(blank=True,null=True)
  SysCPUTime    = models.FloatField(blank=True,null=True)
  CPUPercentage = models.FloatField(blank=True,null=True)
  StageoutTime  = models.FloatField(blank=True,null=True)

  #[Timing]
  TotalJobCPU   = models.FloatField(blank=True,null=True)
  AvgEventCPU   = models.FloatField(blank=True,null=True)
  MaxEventTime  = models.FloatField(blank=True,null=True)
  AvgEventTime  = models.FloatField(blank=True,null=True)
  MinEventCPU   = models.FloatField(blank=True,null=True)
  TotalEventCPU = models.FloatField(blank=True,null=True)
  TotalJobTime  = models.FloatField(blank=True,null=True)
  MinEventTime  = models.FloatField(blank=True,null=True)
  MaxEventCPU   = models.FloatField(blank=True,null=True)

  #[StorageTiming]
  file_readv_total_msecs                                = models.FloatField(blank=True,null=True)
  tstoragefile_read_actual_total_msecs                  = models.FloatField(blank=True,null=True)
  tstoragefile_seek_max_msecs                           = models.FloatField(blank=True,null=True)
  file_prefetch_total_msecs                             = models.FloatField(blank=True,null=True)
  file_readv_num_operations                             = models.FloatField(blank=True,null=True)
  tstoragefile_read_actual_max_msecs                    = models.FloatField(blank=True,null=True)
  tstoragefile_read_num_operations                      = models.FloatField(blank=True,null=True)
  tstoragefile_read_async_num_successful_operations     = models.FloatField(blank=True,null=True)
  tstoragefile_read_num_successful_operations           = models.FloatField(blank=True,null=True)
  tstoragefile_read_total_msecs                         = models.FloatField(blank=True,null=True)
  tstoragefile_seek_total_msecs                         = models.FloatField(blank=True,null=True)
  file_readv_total_megabytes                            = models.FloatField(blank=True,null=True)
  tstoragefile_read_max_msecs                           = models.FloatField(blank=True,null=True)
  tstoragefile_read_async_total_msecs                   = models.FloatField(blank=True,null=True)
  tstoragefile_read_total_megabytes                     = models.FloatField(blank=True,null=True)
  file_readv_max_msecs                                  = models.FloatField(blank=True,null=True)
  file_readv_num_successful_operations                  = models.FloatField(blank=True,null=True)
  tstoragefile_read_via_cache_total_msecs               = models.FloatField(blank=True,null=True)
  tstoragefile_read_async_min_msecs                     = models.FloatField(blank=True,null=True)
  tstoragefile_seek_num_operations                      = models.FloatField(blank=True,null=True)
  file_read_max_msecs                                   = models.FloatField(blank=True,null=True)
  tstoragefile_read_via_cache_num_operations            = models.FloatField(blank=True,null=True)
  tstoragefile_read_via_cache_min_msecs                 = models.FloatField(blank=True,null=True)
  tstoragefile_seek_total_megabytes                     = models.FloatField(blank=True,null=True)
  tstoragefile_read_via_cache_ma_msecs                  = models.FloatField(blank=True,null=True)
  tstoragefile_seek_num_successful_operations           = models.FloatField(blank=True,null=True)
  tstoragefile_read_via_cache_num_successful_operations = models.FloatField(blank=True,null=True)
  tstoragefile_read_actual_num_operations               = models.FloatField(blank=True,null=True)
  tstoragefile_read_min_msecs                           = models.FloatField(blank=True,null=True)
  file_read_total_msecs                                 = models.FloatField(blank=True,null=True)
  tstoragefile_read_actual_min_msecs                    = models.FloatField(blank=True,null=True)
  tstoragefile_read_async_num_operations                = models.FloatField(blank=True,null=True)
  file_read_num_successful_operations                   = models.FloatField(blank=True,null=True)
  file_prefetch_total_megabytes                         = models.FloatField(blank=True,null=True)
  file_prefetch_num_successful_operations               = models.FloatField(blank=True,null=True)
  file_read_num_operations                              = models.FloatField(blank=True,null=True)
  tstoragefile_seek_min_msecs                           = models.FloatField(blank=True,null=True)
  file_read_total_megabytes                             = models.FloatField(blank=True,null=True)
  file_read_min_msecs                                   = models.FloatField(blank=True,null=True)
  file_prefetch_num_operations                          = models.FloatField(blank=True,null=True)
  file_readv_min_msecs                                  = models.FloatField(blank=True,null=True)
  tstoragefile_read_async_max_msecs                     = models.FloatField(blank=True,null=True)
  tstoragefile_read_via_cache_total_megabytes           = models.FloatField(blank=True,null=True)
  tstoragefile_read_async_total_megabytes               = models.FloatField(blank=True,null=True)
  tstoragefile_read_actual_num_successful_operations    = models.FloatField(blank=True,null=True)
  tstoragefile_read_actual_total_megabytes              = models.FloatField(blank=True,null=True)
  file_prefetch_min_msecs                               = models.FloatField(blank=True,null=True)

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
  #[StorageParams]
  stats      = models.CharField(max_length=511, blank=True,null=True)
  cache_hint = models.CharField(max_length=511, blank=True,null=True)
  enabled    = models.CharField(max_length=511, blank=True,null=True)
  read_hint  = models.CharField(max_length=511, blank=True,null=True)

  #[CrabTiming]
  ExeTime       = models.FloatField(blank=True,null=True)
  WrapperTime   = models.FloatField(blank=True,null=True)
  UserCPUTime   = models.FloatField(blank=True,null=True)
  SysCPUTime    = models.FloatField(blank=True,null=True)
  CPUPercentage = models.FloatField(blank=True,null=True)
  StageoutTime  = models.FloatField(blank=True,null=True)

  #[Timing]
  TotalJobCPU   = models.FloatField(blank=True,null=True)
  AvgEventCPU   = models.FloatField(blank=True,null=True)
  MaxEventTime  = models.FloatField(blank=True,null=True)
  AvgEventTime  = models.FloatField(blank=True,null=True)
  MinEventCPU   = models.FloatField(blank=True,null=True)
  TotalEventCPU = models.FloatField(blank=True,null=True)
  TotalJobTime  = models.FloatField(blank=True,null=True)
  MinEventTime  = models.FloatField(blank=True,null=True)
  MaxEventCPU   = models.FloatField(blank=True,null=True)

  #[StorageTiming]
  file_readv_total_msecs                                = models.FloatField(blank=True,null=True)
  tstoragefile_read_actual_total_msecs                  = models.FloatField(blank=True,null=True)
  tstoragefile_seek_max_msecs                           = models.FloatField(blank=True,null=True)
  file_prefetch_total_msecs                             = models.FloatField(blank=True,null=True)
  file_readv_num_operations                             = models.FloatField(blank=True,null=True)
  tstoragefile_read_actual_max_msecs                    = models.FloatField(blank=True,null=True)
  tstoragefile_read_num_operations                      = models.FloatField(blank=True,null=True)
  tstoragefile_read_async_num_successful_operations     = models.FloatField(blank=True,null=True)
  tstoragefile_read_num_successful_operations           = models.FloatField(blank=True,null=True)
  tstoragefile_read_total_msecs                         = models.FloatField(blank=True,null=True)
  tstoragefile_seek_total_msecs                         = models.FloatField(blank=True,null=True)
  file_readv_total_megabytes                            = models.FloatField(blank=True,null=True)
  tstoragefile_read_max_msecs                           = models.FloatField(blank=True,null=True)
  tstoragefile_read_async_total_msecs                   = models.FloatField(blank=True,null=True)
  tstoragefile_read_total_megabytes                     = models.FloatField(blank=True,null=True)
  file_readv_max_msecs                                  = models.FloatField(blank=True,null=True)
  file_readv_num_successful_operations                  = models.FloatField(blank=True,null=True)
  tstoragefile_read_via_cache_total_msecs               = models.FloatField(blank=True,null=True)
  tstoragefile_read_async_min_msecs                     = models.FloatField(blank=True,null=True)
  tstoragefile_seek_num_operations                      = models.FloatField(blank=True,null=True)
  file_read_max_msecs                                   = models.FloatField(blank=True,null=True)
  tstoragefile_read_via_cache_num_operations            = models.FloatField(blank=True,null=True)
  tstoragefile_read_via_cache_min_msecs                 = models.FloatField(blank=True,null=True)
  tstoragefile_seek_total_megabytes                     = models.FloatField(blank=True,null=True)
  tstoragefile_read_via_cache_ma_msecs                  = models.FloatField(blank=True,null=True)
  tstoragefile_seek_num_successful_operations           = models.FloatField(blank=True,null=True)
  tstoragefile_read_via_cache_num_successful_operations = models.FloatField(blank=True,null=True)
  tstoragefile_read_actual_num_operations               = models.FloatField(blank=True,null=True)
  tstoragefile_read_min_msecs                           = models.FloatField(blank=True,null=True)
  file_read_total_msecs                                 = models.FloatField(blank=True,null=True)
  tstoragefile_read_actual_min_msecs                    = models.FloatField(blank=True,null=True)
  tstoragefile_read_async_num_operations                = models.FloatField(blank=True,null=True)
  file_read_num_successful_operations                   = models.FloatField(blank=True,null=True)
  file_prefetch_total_megabytes                         = models.FloatField(blank=True,null=True)
  file_prefetch_num_successful_operations               = models.FloatField(blank=True,null=True)
  file_read_num_operations                              = models.FloatField(blank=True,null=True)
  tstoragefile_seek_min_msecs                           = models.FloatField(blank=True,null=True)
  file_read_total_megabytes                             = models.FloatField(blank=True,null=True)
  file_read_min_msecs                                   = models.FloatField(blank=True,null=True)
  file_prefetch_num_operations                          = models.FloatField(blank=True,null=True)
  file_readv_min_msecs                                  = models.FloatField(blank=True,null=True)
  tstoragefile_read_async_max_msecs                     = models.FloatField(blank=True,null=True)
  tstoragefile_read_via_cache_total_megabytes           = models.FloatField(blank=True,null=True)
  tstoragefile_read_async_total_megabytes               = models.FloatField(blank=True,null=True)
  tstoragefile_read_actual_num_successful_operations    = models.FloatField(blank=True,null=True)
  tstoragefile_read_actual_total_megabytes              = models.FloatField(blank=True,null=True)
  file_prefetch_min_msecs                               = models.FloatField(blank=True,null=True)

class SummaryTestSite(SummaryTestSiteBase):
  #[StorageParams]
  stats      = models.CharField(max_length=511, blank=True,null=True)
  cache_hint = models.CharField(max_length=511, blank=True,null=True)
  enabled    = models.CharField(max_length=511, blank=True,null=True)
  read_hint  = models.CharField(max_length=511, blank=True,null=True)

  #[CrabTiming]
  ExeTime       = models.FloatField(blank=True,null=True)
  WrapperTime   = models.FloatField(blank=True,null=True)
  UserCPUTime   = models.FloatField(blank=True,null=True)
  SysCPUTime    = models.FloatField(blank=True,null=True)
  CPUPercentage = models.FloatField(blank=True,null=True)
  StageoutTime  = models.FloatField(blank=True,null=True)

  #[Timing]
  TotalJobCPU   = models.FloatField(blank=True,null=True)
  AvgEventCPU   = models.FloatField(blank=True,null=True)
  MaxEventTime  = models.FloatField(blank=True,null=True)
  AvgEventTime  = models.FloatField(blank=True,null=True)
  MinEventCPU   = models.FloatField(blank=True,null=True)
  TotalEventCPU = models.FloatField(blank=True,null=True)
  TotalJobTime  = models.FloatField(blank=True,null=True)
  MinEventTime  = models.FloatField(blank=True,null=True)
  MaxEventCPU   = models.FloatField(blank=True,null=True)

  #[StorageTiming]
  file_readv_total_msecs                                = models.FloatField(blank=True,null=True)
  tstoragefile_read_actual_total_msecs                  = models.FloatField(blank=True,null=True)
  tstoragefile_seek_max_msecs                           = models.FloatField(blank=True,null=True)
  file_prefetch_total_msecs                             = models.FloatField(blank=True,null=True)
  file_readv_num_operations                             = models.FloatField(blank=True,null=True)
  tstoragefile_read_actual_max_msecs                    = models.FloatField(blank=True,null=True)
  tstoragefile_read_num_operations                      = models.FloatField(blank=True,null=True)
  tstoragefile_read_async_num_successful_operations     = models.FloatField(blank=True,null=True)
  tstoragefile_read_num_successful_operations           = models.FloatField(blank=True,null=True)
  tstoragefile_read_total_msecs                         = models.FloatField(blank=True,null=True)
  tstoragefile_seek_total_msecs                         = models.FloatField(blank=True,null=True)
  file_readv_total_megabytes                            = models.FloatField(blank=True,null=True)
  tstoragefile_read_max_msecs                           = models.FloatField(blank=True,null=True)
  tstoragefile_read_async_total_msecs                   = models.FloatField(blank=True,null=True)
  tstoragefile_read_total_megabytes                     = models.FloatField(blank=True,null=True)
  file_readv_max_msecs                                  = models.FloatField(blank=True,null=True)
  file_readv_num_successful_operations                  = models.FloatField(blank=True,null=True)
  tstoragefile_read_via_cache_total_msecs               = models.FloatField(blank=True,null=True)
  tstoragefile_read_async_min_msecs                     = models.FloatField(blank=True,null=True)
  tstoragefile_seek_num_operations                      = models.FloatField(blank=True,null=True)
  file_read_max_msecs                                   = models.FloatField(blank=True,null=True)
  tstoragefile_read_via_cache_num_operations            = models.FloatField(blank=True,null=True)
  tstoragefile_read_via_cache_min_msecs                 = models.FloatField(blank=True,null=True)
  tstoragefile_seek_total_megabytes                     = models.FloatField(blank=True,null=True)
  tstoragefile_read_via_cache_ma_msecs                  = models.FloatField(blank=True,null=True)
  tstoragefile_seek_num_successful_operations           = models.FloatField(blank=True,null=True)
  tstoragefile_read_via_cache_num_successful_operations = models.FloatField(blank=True,null=True)
  tstoragefile_read_actual_num_operations               = models.FloatField(blank=True,null=True)
  tstoragefile_read_min_msecs                           = models.FloatField(blank=True,null=True)
  file_read_total_msecs                                 = models.FloatField(blank=True,null=True)
  tstoragefile_read_actual_min_msecs                    = models.FloatField(blank=True,null=True)
  tstoragefile_read_async_num_operations                = models.FloatField(blank=True,null=True)
  file_read_num_successful_operations                   = models.FloatField(blank=True,null=True)
  file_prefetch_total_megabytes                         = models.FloatField(blank=True,null=True)
  file_prefetch_num_successful_operations               = models.FloatField(blank=True,null=True)
  file_read_num_operations                              = models.FloatField(blank=True,null=True)
  tstoragefile_seek_min_msecs                           = models.FloatField(blank=True,null=True)
  file_read_total_megabytes                             = models.FloatField(blank=True,null=True)
  file_read_min_msecs                                   = models.FloatField(blank=True,null=True)
  file_prefetch_num_operations                          = models.FloatField(blank=True,null=True)
  file_readv_min_msecs                                  = models.FloatField(blank=True,null=True)
  tstoragefile_read_async_max_msecs                     = models.FloatField(blank=True,null=True)
  tstoragefile_read_via_cache_total_megabytes           = models.FloatField(blank=True,null=True)
  tstoragefile_read_async_total_megabytes               = models.FloatField(blank=True,null=True)
  tstoragefile_read_actual_num_successful_operations    = models.FloatField(blank=True,null=True)
  tstoragefile_read_actual_total_megabytes              = models.FloatField(blank=True,null=True)
  file_prefetch_min_msecs                               = models.FloatField(blank=True,null=True)


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


##
## BLACKLISTING CLASSES
##
## *BlacklistEvent
##

class BlacklistEvent(BlacklistEventBase):
  pass
