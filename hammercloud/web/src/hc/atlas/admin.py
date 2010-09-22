from hc.atlas.forms import MetricPermissionForm, TemplateUserForm, TestUserForm
from hc.atlas.models import *

from django.contrib import admin

from hc.core.base.admin.genericAdmin import *
from hc.core.base.forms.forms import TestAdminForm

from hc.core.base.rss.admin import *

## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## SIMPLE ADMIN CLASSES
##
## *BackendAdmin
## *CloudAdmin
## *DspatternAdmin
## *GangaBinAdmin
## *HostAdmin
## *InputTypeAdmin
## *JobTemplateAdmin
## *OptionFileAdmin
## *TestScriptAdmin
## *UserCode
##

class BackendAdmin(BackendAdminBase):
  pass

class CloudAdmin(CloudAdminBase):
  pass

class DspatternAdmin(DspatternAdminBase):
  pass

class GangaBinAdmin(GangaBinAdminBase):
  pass

class HostAdmin(HostAdminBase):
  pass
 
class InputTypeAdmin(InputTypeAdminBase):
  pass

class JobTemplateAdmin(JobTemplateAdminBase):
  pass

class OptionFileAdmin(OptionFileAdminBase):
  pass

class TestScriptAdmin(TestScriptAdminBase):
  pass

class UserCodeAdmin(UserCodeAdminBase):
  pass

## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## SITE ADMIN CLASSES
##
## *SiteAdmin
##

class SiteAdmin(SiteAdminBase):
  pass


## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## TEMPLATE ADMIN CLASSES
##
## *TemplateBackendInline
## *TemplateCloudInline
## *TemplateDspatternInline
## *TemplateHostInline
## *TemplateSiteInline
## [*TemplateUserInline]
##
## *TemplateAdmin
## *TemplateBackendAdmin
## *TemplateCloudAdmin
## *TemplateDspatternAdmin
## *TemplateHostAdmin
## *TemplateSiteAdmin
## *TemplateUserAdmin
##

class TemplateBackendInline(TemplateInlineBase):
  model = TemplateBackend

class TemplateCloudInline(TemplateInlineBase):
  model = TemplateCloud

class TemplateDspatternInline(TemplateInlineBase):
  model = TemplateDspattern
 
class TemplateHostInline(TemplateInlineBase):
  model = TemplateHost

class TemplateSiteInline(TemplateInlineBase):
  model = TemplateSite

class TemplateAdmin(TemplateAdminBase):
  inlines = [TemplateHostInline, TemplateBackendInline, TemplateCloudInline, TemplateSiteInline, TemplateDspatternInline]

class TemplateBackendAdmin(TemplateBackendAdminBase):
  pass

class TemplateCloudAdmin(TemplateCloudAdminBase):
  pass

class TemplateDspatternAdmin(TemplateDspatternAdminBase):
  pass

class TemplateHostAdmin(TemplateHostAdminBase):
  pass

class TemplateSiteAdmin(TemplateSiteAdminBase):
  pass

class TemplateUserAdmin(TemplateUserAdminBase):
  form = TemplateUserForm


## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## TEST ADMIN CLASSES
##
## *TestBackendInline
## *TestCloudInline
## *TestDspatternInline
## *TestHostInline
## *TestSiteInline
## [*TestUserInline]
##
## *TestAdmin
## *TestBackendAdmin
## *TestCloudAdmin
## *TestDspatternAdmin
## *TestHostAdmin
## *TestJournalAdmin
## *TestSiteAdmin
## *TestUserAdmin
##

class TestBackendInline(TestInlineBase):
  model = TestBackend

class TestCloudInline(TestInlineBase):
  model = TestCloud

class TestDspatternInline(TestInlineBase):
  model = TestDspattern

class TestHostInline(TestInlineBase):
  model = TestHost

class TestSiteInline(TestInlineBase):
  model = TestSite

class TestAdmin(TestAdminBase):
  inlines = [TestHostInline,TestBackendInline,TestCloudInline,TestSiteInline,TestDspatternInline]
#  form = TestAdminForm

class TestBackendAdmin(TestBackendAdminBase):
  pass

class TestCloudAdmin(TestCloudAdminBase):
  pass

class TestDspatternAdmin(TestDspatternAdminBase):
  pass

class TestHostAdmin(TestHostAdminBase):
  pass

#class TestJournalAdmin(TestJournalAdminBase):
#  form = TestJournalForm

class TestSiteAdmin(TestSiteAdminBase):
  pass

class TestUserAdmin(TestUserAdminBase):
  form = TestUserForm


## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## METRIC ADMIN CLASSES
##
## *MetricTypeAdmin
## *MetricAdmin
## *MetricPermission
## *[GlobalMetricAdmin]
## *SiteMetricAdmin
## *TestMetricAdmin
##

class MetricAdmin(MetricAdminBase):
  pass

class MetricTypeAdmin(MetricTypeAdminBase):
  pass

class MetricPermissionAdmin(MetricPermissionAdminBase):
  form = MetricPermissionForm

class SiteMetricAdmin(SiteMetricAdminBase):
  pass

class TestMetricAdmin(TestMetricAdminBase):
  pass


## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## SUMMARY ADMIN CLASSES
##
## * SummaryRobotAdmin
##

class SummaryRobotAdmin(SummaryRobotAdminBase):
  pass

## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## FEED ADMIN CLASSES
##
## *AppFeedAdmin
## *CloudFeedAdmin
## *SiteFeedAdmin
## *TemplateFeedAdmin
## *TestFeedAdmin
##

class AppFeedAdmin(AppFeedAdminBase):
  pass
class CloudFeedAdmin(CloudFeedAdminBase):
  pass
class SiteFeedAdmin(SiteFeedAdminBase):
  pass
class TemplateFeedAdmin(TemplateFeedAdminBase):
  pass
class TestFeedAdmin(TestFeedAdminBase):
  pass


##########################################################################################################

admin.site.register(Backend,BackendAdmin)
admin.site.register(Cloud,CloudAdmin)
admin.site.register(Dspattern,DspatternAdmin)
admin.site.register(GangaBin,GangaBinAdmin)
admin.site.register(Host,HostAdmin)
admin.site.register(InputType,InputTypeAdmin)
admin.site.register(JobTemplate,JobTemplateAdmin)
admin.site.register(OptionFile,OptionFileAdmin)
admin.site.register(TestScript,TestScriptAdmin)
admin.site.register(UserCode,UserCodeAdmin)

admin.site.register(Site,SiteAdmin)

admin.site.register(Template,TemplateAdmin)
admin.site.register(TemplateBackend,TemplateBackendAdmin)
admin.site.register(TemplateCloud,TemplateCloudAdmin)
admin.site.register(TemplateDspattern,TemplateDspatternAdmin)
admin.site.register(TemplateHost,TemplateHostAdmin)
admin.site.register(TemplateSite,TemplateSiteAdmin)
admin.site.register(TemplateUser,TemplateUserAdmin)

admin.site.register(Test,TestAdmin)
admin.site.register(TestBackend,TestBackendAdmin)
admin.site.register(TestCloud,TestCloudAdmin)
admin.site.register(TestDspattern,TestDspatternAdmin)
admin.site.register(TestHost,TestHostAdmin)
#admin.site.register(TestJournal,TestJournalAdmin)
admin.site.register(TestSite,TestSiteAdmin)
admin.site.register(TestUser,TestUserAdmin)

admin.site.register(MetricType,MetricTypeAdmin)
admin.site.register(Metric,MetricAdmin)
admin.site.register(MetricPermission,MetricPermissionAdmin)
#[admin.site.register(GlobalMetric,GlobalMetric)]
admin.site.register(SiteMetric,SiteMetricAdmin)
admin.site.register(TestMetric,TestMetricAdmin)

admin.site.register(SummaryRobot,SummaryRobotAdmin)

admin.site.register(AppFeed,AppFeedAdmin)
admin.site.register(CloudFeed,CloudFeedAdmin)
admin.site.register(SiteFeed,SiteFeedAdmin)
admin.site.register(TemplateFeed,TemplateFeedAdmin)
admin.site.register(TestFeed,TestFeedAdmin)


