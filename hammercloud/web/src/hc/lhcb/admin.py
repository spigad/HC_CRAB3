from hc.lhcb.forms import MetricPermissionForm, TemplateUserForm ,TestJournalForm, TestUserForm
from hc.lhcb.models import *

from django.contrib import admin

from hc.core.base.admin.genericAdmin import *

from hc.core.base.rss.admin import HCFeedAdminBase

## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## SIMPLE ADMIN CLASSES
##
## *CloudAdmin
## *DspatternAdmin
## *FileAdmin
## *HostAdmin
##

class CloudAdmin(CloudAdminBase):
  pass

class DspatternAdmin(DspatternAdminBase):
  pass

class FileAdmin(FileAdminBase):
  pass

class HostAdmin(HostAdminBase):
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
## *TemplateCloudInline
## *TemplateDspatternInline
## *TemplateHostInline
## *TemplateSiteInline
## [*TemplateUserInline]
##
## *TemplateAdmin
## *TemplateCloudAdmin
## *TemplateDspatternAdmin
## *TemplateHostAdmin
## *TemplateSiteAdmin
## *TemplateUserAdmin
##

class TemplateDspatternInline(TemplateInlineBase):
  model = TemplateDspattern
 
class TemplateCloudInline(TemplateInlineBase):
  model = TemplateCloud

class TemplateHostInline(TemplateInlineBase):
  model = TemplateHost

class TemplateSiteInline(TemplateInlineBase):
  model = TemplateSite

class TemplateAdmin(TemplateAdminBase):
  inlines = [TemplateHostInline, TemplateCloudInline, TemplateSiteInline, TemplateDspatternInline]

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
## *TestCloudInline
## *TestDspatternInline
## *TestHostInline
## *TestSiteInline
## [*TestUserInline]
##
## *TestAdmin
## *TestCloudAdmin
## *TestDspatternAdmin
## *TestHostAdmin
## *TestJournalAdmin
## *TestSiteAdmin
## *TestUserAdmin
##

class TestCloudInline(TestInlineBase):
  model = TestCloud

class TestDspatternInline(TestInlineBase):
  model = TestDspattern

class TestHostInline(TestInlineBase):
  model = TestHost

class TestSiteInline(TestInlineBase):
  model = TestSite

class TestAdmin(TestAdminBase):
  inlines = [TestHostInline,TestCloudInline,TestSiteInline, TestDspatternInline]

class TestCloudAdmin(TestCloudAdminBase):
  pass

class TestDspatternAdmin(TestDspatternAdminBase):
  pass

class TestHostAdmin(TestHostAdminBase):
  pass

class TestJournalAdmin(TestJournalAdminBase):
  form = TestJournalForm

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
## HCFEED ADMIN CLASSES
##
## *HCFeedAdmin
##

class HCFeedAdmin(HCFeedAdminBase):
  pass


##########################################################################################################

admin.site.register(Cloud,CloudAdmin)
admin.site.register(Dspattern,DspatternAdmin)
admin.site.register(File,FileAdmin)
admin.site.register(Host,HostAdmin)
admin.site.register(Site,SiteAdmin)

admin.site.register(Template,TemplateAdmin)
admin.site.register(TemplateCloud,TemplateCloudAdmin)
admin.site.register(TemplateDspattern,TemplateDspatternAdmin)
admin.site.register(TemplateHost,TemplateHostAdmin)
admin.site.register(TemplateSite,TemplateSiteAdmin)
admin.site.register(TemplateUser,TemplateUserAdmin)

admin.site.register(Test,TestAdmin)
admin.site.register(TestCloud,TestCloudAdmin)
admin.site.register(TestDspattern,TestDspatternAdmin)
admin.site.register(TestHost,TestHostAdmin)
admin.site.register(TestJournal,TestJournalAdmin)
admin.site.register(TestSite,TestSiteAdmin)
admin.site.register(TestUser,TestUserAdmin)

admin.site.register(MetricType,MetricTypeAdmin)
admin.site.register(Metric,MetricAdmin)
admin.site.register(MetricPermission,MetricPermissionAdmin)
#[admin.site.register(GlobalMetric,GlobalMetric)]
admin.site.register(SiteMetric,SiteMetricAdmin)
admin.site.register(TestMetric,TestMetricAdmin)

admin.site.register(SummaryRobot,SummaryRobotAdmin)

admin.site.register(HCFeed,HCFeedAdmin)
