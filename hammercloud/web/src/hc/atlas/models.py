from django.db import models
from hc.core.base.models.abstract import *
from hc.core.base.rss.abstract import *

import subprocess

##
## SIMPLE CLASSES
##
## *GlobalOption
##
class GlobalOption(GlobalOptionBase):
  pass

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
  ATLAS_TOPOLOGY = None

  def __load_topology(self):
    try:
      from atlas.utils.atlas_topology import ATLASTopology
      self.ATLAS_TOPOLOGY = ATLASTopology()
    except:
      print "Could not create ATLAS topology object."

  def site_type(self):
    if self.name.startswith('ANALY'):
      return 'analysis'
    elif self.cloud.name.endswith('PROD'):
      return 'production'
    return 'other'

  def ssb_name(self):
    try:
      if self.ATLAS_TOPOLOGY is None:
        self.__load_topology()
      site_name = ATLAS_TOPOLOGY.get_site_id_of_panda_queue(self.name, site_type=self.site_type())
    except:
      return 'Toplogy not loaded'
    if site_name is not None:
      return site_name
    else:
      return self.name
    

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
class TemplateSiteAlarm(TemplateSiteAlarmBase):
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
  # ATLAS parameters
  exit_status_1         = models.IntegerField(blank=True,null=True)
  exit_status_2         = models.IntegerField(blank=True,null=True)

  actual_ce             = models.CharField(max_length=511, blank=True, null=True)
  arch                  = models.CharField(max_length=511, blank=True, null=True)
  inds                  = models.CharField(max_length=1023, blank=True, null=True)
  logfile_guid          = models.CharField(max_length=511, blank=True, null=True)
  outds                 = models.CharField(max_length=1023, blank=True, null=True)
  output_location       = models.CharField(max_length=511, blank=True, null=True)

  ganga_number_of_files = models.IntegerField(blank=True,null=True)
  numevents             = models.IntegerField(blank=True,null=True)
  numfiles              = models.IntegerField(blank=True,null=True)
  percent_cpu           = models.FloatField(blank=True,null=True)
  wallclock             = models.FloatField(blank=True,null=True)

  #numevents / wallclock
  eventrate             = models.FloatField(blank=True,null=True)
  #numevents / pandatime3 || numevents / (ganga_time_4 - ganga_time_3)
  events_athena         = models.FloatField(blank=True,null=True)
  
  jdl_time              = models.DateTimeField(blank=True,null=True)
  pandatime1            = models.IntegerField(blank=True,null=True)  
  pandatime2            = models.IntegerField(blank=True,null=True)
  pandatime3            = models.IntegerField(blank=True,null=True)
  pandatime4            = models.IntegerField(blank=True,null=True)
  pandatime5            = models.IntegerField(blank=True,null=True)
  #ganga_time_2 - ganga_time_1
  nonpandatime1         = models.IntegerField(blank=True,null=True)
  #ganga_time_3 - ganga_time_2
  nonpandatime2         = models.IntegerField(blank=True,null=True)
  #ganga_time_4 - ganga_time_3
  nonpandatime3         = models.IntegerField(blank=True,null=True)
  #ganga_time_5 - ganga_time_4
  nonpandatime4         = models.IntegerField(blank=True,null=True)

  net_eth_rx_preathena  = models.IntegerField(null=True, blank=True)
  net_eth_rx_postathena = models.IntegerField(null=True, blank=True)

  timetorun             = models.FloatField(null=True, blank=True)

  def save(self):
    try:
      td = self.start_time - self.submit_time
      self.timetorun = (td.microseconds + (td.seconds + td.days * 24 * 3600) * 10**6) / 10**6
    except TypeError: # Just for the Nones on the times.
      pass
    super(Result, self).save()

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

  wallclock             = models.IntegerField(blank=True,null=True)
  numevents             = models.IntegerField(blank=True,null=True)
  numfiles              = models.IntegerField(blank=True,null=True)
  percent_cpu           = models.IntegerField(blank=True,null=True)
  ganga_number_of_files = models.IntegerField(blank=True,null=True) 

  #numevents / wallclock
  eventrate             = models.FloatField(blank=True,null=True)
  #numevents / pandatime3 || numevents / (ganga_time_4 - ganga_time_3)
  events_athena         = models.FloatField(blank=True,null=True)

  pandatime1            = models.IntegerField(blank=True,null=True)
  pandatime2            = models.IntegerField(blank=True,null=True)
  pandatime3            = models.IntegerField(blank=True,null=True)
  pandatime4            = models.IntegerField(blank=True,null=True)
  pandatime5            = models.IntegerField(blank=True,null=True)
  #ganga_time_2 - ganga_time_1
  nonpandatime1         = models.IntegerField(blank=True,null=True)
  #ganga_time_3 - ganga_time_2
  nonpandatime2         = models.IntegerField(blank=True,null=True)
  #ganga_time_4 - ganga_time_3
  nonpandatime3         = models.IntegerField(blank=True,null=True)
  #ganga_time_5 - ganga_time_4
  nonpandatime4         = models.IntegerField(blank=True,null=True)
  timetorun             = models.FloatField(blank=True,null=True)


class SummaryTestSite(SummaryTestSiteBase):

  wallclock             = models.IntegerField(blank=True,null=True)
  numevents             = models.IntegerField(blank=True,null=True)
  numfiles              = models.IntegerField(blank=True,null=True)
  percent_cpu           = models.IntegerField(blank=True,null=True)
  ganga_number_of_files = models.IntegerField(blank=True,null=True) 

  #numevents / wallclock
  eventrate             = models.FloatField(blank=True,null=True)
  #numevents / pandatime3 || numevents / (ganga_time_4 - ganga_time_3)
  events_athena         = models.FloatField(blank=True,null=True)

  pandatime1            = models.IntegerField(blank=True,null=True)
  pandatime2            = models.IntegerField(blank=True,null=True)
  pandatime3            = models.IntegerField(blank=True,null=True)
  pandatime4            = models.IntegerField(blank=True,null=True)
  pandatime5            = models.IntegerField(blank=True,null=True)
  #ganga_time_2 - ganga_time_1
  nonpandatime1         = models.IntegerField(blank=True,null=True)
  #ganga_time_3 - ganga_time_2
  nonpandatime2         = models.IntegerField(blank=True,null=True)
  #ganga_time_4 - ganga_time_3
  nonpandatime3         = models.IntegerField(blank=True,null=True)
  #ganga_time_5 - ganga_time_4
  nonpandatime4         = models.IntegerField(blank=True,null=True)
  timetorun             = models.FloatField(blank=True,null=True)


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

# Custom functions to get the reports of downtime from PanDA. Please remove as soon
# as DDM offers this capability.
def blacklisting_panda_report(days=30):
  try:
    command = r'/afs/cern.ch/user/r/rmedrano/public/panda_report/panda_report'
    return subprocess.Popen([command, '-t', str(days), '-w'], stdout=subprocess.PIPE).communicate()[0]
  except OSError:
    return 'Could not retrieve data from PanDA incidents database.'


##
## MESSAGE BUS CLASSES
##
## *MessageBusEvent
##

class MessageBusEvent(MessageBusEventBase):
  pass
