from django.contrib import admin
from django.core.mail import mail_admins

from hc.core.base.models.managers.admin import backend_am,cloud_am,template_am,test_am,test_journal_am,test_user_am,template_user_am
from hc.core.base.forms.forms import ReadOnlyAdminFields,ModelLinkAdminFields
from hc.core.base.forms.forms import TestAdminForm,TestSuperUserAdminForm

from hc.core.utils.generic.class_func import custom_import
from django.http import Http404

from hc.core.base.admin.actions import cancel,clone,delete_marked,delete_view,make_approved,pause,unpause,send_for_approval

## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## ACTIONS ADMIN BASE CLASE
##
## *ActionsAdminBase
##
##

class ActionsAdminBase(admin.ModelAdmin):

  actions = ['clone','delete_marked','send_for_approval','cancel','pause','make_approved','unpause']

  def get_actions(self, request):
    actions = super(ActionsAdminBase, self).get_actions(request)

    del actions['delete_selected']

#    if not request.user.is_superuser:
#      del actions['delete_selected']
#    else:
#      del actions['delete_marked']

    if self.model._meta.unique_together:
      del actions['clone']

    if self.model._meta.object_name == "Test":

      if not request.user.is_superuser:
        del actions['cancel']
        del actions['make_approved']

    else:
      del actions['send_for_approval']
      del actions['cancel']
      del actions['make_approved']
      del actions['pause']
      del actions['unpause']

    return actions

  def cancel(self, request, queryset):
    cancel.method(self, request, queryset)
  cancel.short_description = "Cancel selected tests."

  def clone(self, request, queryset):  
    clone.method(self, request, queryset)
  clone.short_description = "Clone multiple objects."  

  def delete_marked(self, request, queryset):
    delete_marked.method(self, request, queryset)
  delete_marked.short_description = "Delete multiple objects."

  def delete_view(self, request, object_id, extra_context=None):
    delete_view.method(self, request, object_id, extra_context=None)
    return super(ActionsAdminBase, self).delete_view(request, object_id, extra_context=None)

  def make_approved(self, request, queryset):
    make_approved.method(self, request, queryset)
  make_approved.short_description = "Mark selected tests as approved"

  def send_for_approval(self, request, queryset):
    send_for_approval.method(self, request, queryset)
  send_for_approval.short_description = "Send selected tests for approval"

  def pause(self, request, queryset):
    pause.method(self, request, queryset)
  pause.short_description = "Pause selected tests."

  def unpause(self, request, queryset):
    unpause.method(self, request, queryset)
  unpause.short_description = "Unpause selected tests."

  class Meta:
    abstract = True

## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## SIMPLE ADMIN BASE CLASSES
##
## *CloudAdminBase
## *BackendAdminBase
## *DspatternAdminBase
## *GangaBinAdminBase
## *HostAdminBase
## *InputTypeAdminBase
## *JobTemplateAdminBase
## *OptionFileAdminBase
## *TestScriptAdminBase
## *UserCodeAdminBase
##

class BackendAdminBase(ActionsAdminBase):

  list_display = ('name', 'description', backend_am.getBackendSitesStringAdmin,)
  fieldsets = [
    ('Backend', {'fields': ['name','description']})
  ]

  class Meta:
    abstract = True

class CloudAdminBase(ActionsAdminBase):

  list_display = ('name', 'code', 'description',cloud_am.getCloudSitesStringAdmin,)
  fieldsets = [
    ('Cloud', {'fields': ['name','code','description']})
  ]

  class Meta:
    abstract = True

class DspatternAdminBase(ActionsAdminBase):
  list_display = ('pattern','description')
  fieldsets = [
    (None, {'fields': ['pattern','description']})
  ]

  class Meta:
    abstract = True

class GangaBinAdminBase(ActionsAdminBase):
  list_display = ('path','description')
  fieldsets = [
    (None, {'fields': ['path','description']})
  ]

  class Meta:
    abstract = True

class HostAdminBase(ActionsAdminBase):
  list_display = ('name','loadavg1m','description','active')
  fieldsets = [
    (None, {'fields': ['name','description','active']})
  ]

  class Meta:
    abstract = True

class InputTypeAdminBase(ActionsAdminBase):
  list_display = ('type','description')
  fieldsets = [
    (None, {'fields': ['type','description']})
  ]   

  class	Meta:
    abstract = True

class JobTemplateAdminBase(ActionsAdminBase):
  list_display = ('path','description')
  fieldsets = [
    (None, {'fields': ['path','description']})
  ]

  class Meta:
    abstract = True

class OptionFileAdminBase(ActionsAdminBase):
  list_display = ('path','description')
  fieldsets = [
    (None, {'fields': ['path','description']})
  ]

  class Meta:
    abstract = True

class TestScriptAdminBase(ActionsAdminBase):
  list_display = ('script','description')
  fieldsets = [
    (None, {'fields': ['script','description']})
  ]   

  class	Meta:
    abstract = True

class UserCodeAdminBase(ActionsAdminBase):
  list_display = ('path','description')
  fieldsets = [
    (None, {'fields': ['path','description']})
  ]

  class Meta:
    abstract = True


## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## SITE ADMIN BASE CLASSES
##
## *SiteAdminBase
##

class SiteAdminBase(ActionsAdminBase):
  list_display = ('name', 'description','cloud', 'backend', 'enabled')
  fieldsets = [
    (None, {'fields': ['name','description','cloud','backend','ddm','enabled','queue']}),
  ]

  class Meta:
    abstract = True


## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## TEMPLATE ADMIN BASE CLASSES
##
## *TemplateAdminBase
## *TemplateBackendAdminBase
## *TemplateCloudAdminBase
## *TemplateDspatternAdminBase
## *TemplateHostAdminBase
## *TemplateSiteAdminBase
## [*TemplateUserAdmin]
##
## *TemplateInlineBase
##

class TemplateAdminBase(ActionsAdminBase):

  #inlines -> customized at plugin level
  list_display = ('id', 'category', 'active', 'description','lifetime','inputtype',template_am.getTemplateBackendNamesStringAdmin,template_am.getTemplateCloudCodesStringAdmin,template_am.getTemplateSiteNamesStringAdmin,template_am.getTemplateHostNamesStringAdmin)
  save_on_top = True
  fieldsets = [
    ('Type information', {'fields': ['category','description']                                }),
    (None,               {'fields': ['lifetime','active']                                     }),
    ('Files',            {'fields': ['jobtemplate','usercode','optionfile','metricperm']}),
    (None,               {'fields': ['inputtype','testscript','gangabin','extraargs']         }),
  ]

  class Meta:
    abstract = True

class TemplateBackendAdminBase(ActionsAdminBase):

  list_display = ('template', 'backend')
  fieldsets = [
    ('None', {'fields': ['template','backend']})
  ]

  class Meta:
    abstract = True

class TemplateCloudAdminBase(ActionsAdminBase):

  list_display = ('template', 'cloud')
  fieldsets = [
    (None, {'fields':['template','cloud']})
  ]

  class Meta:
    abstract = True

class TemplateDspatternAdminBase(ActionsAdminBase):

  list_display = ('template', 'dspattern')
  fieldsets = [
    (None, {'fields':['template','dspattern']})
  ]

  class Meta:
    abstract = True 

class TemplateHostAdminBase(ActionsAdminBase):

  list_display = ('template', 'host')
  fieldsets = [
    (None, {'fields':['template','host']})
  ]

  class Meta:
    abstract = True 

class TemplateSiteAdminBase(ActionsAdminBase):

  list_display = ('template', 'site')
  fieldsets = [
    (None, {'fields':['template','site']})
  ]

  class Meta:
    abstract = True 

class TemplateUserAdminBase(admin.ModelAdmin):

  list_display = ('template',template_user_am.getTemplateUserNameStringAdmin)
  fieldsets = [ 
    (None,{'fields':['template','user']})
  ]

#  def delete_view(self, request, object_id, extra_context=None):
#
#    request_path = request.path
#    app = request_path.split('/')[3]
#
#    teu  = custom_import('hc.'+app+'.models.TemplateUser')
#    test = custom_import('hc.'+app+'.models.Test')
#
#    template = teu.objects.get(pk=object_id).template
#    tests = test.objects.filter(template=te.id)
#
#    if tests:
#      raise Http404
#
#    users = [str(tu.user) for tu in template.getTemplateUsers_for_template.all()]
#    user = str(request.user)
#
#    if (user in users) or (request.user.is_superuser):
#      return super(TemplateUserAdminBase, self).delete_view(request, object_id, extra_context=None)
#    else:
#      raise Http404


  class Meta:
    abstract = True

class TemplateInlineBase(admin.TabularInline):

  #model -> customized at plugin level
  extra = 3
  fk_name = 'template'
  exclude = ['mtime',]

  class Meta:
    abstract = True


## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## TEST ADMIN BASE CLASSES
##
## *TestAdminBase
## *TemplateBackendAdminBase
## *TestCloudAdminBase
## *TestDspatternAdminBase
## *TestHostAdminBase
## *TestJournalAdminBase
## *TestSiteAdminBase
## *TestUserAdminBase
##
## *TemplateInlineBase


class TestAdminBase(ReadOnlyAdminFields,ModelLinkAdminFields,ActionsAdminBase):

  #inlines -> customized at plugin level
  list_display = ('id', 'starttime', 'endtime','description','pause', 'state','inputtype', test_am.getTestCloudCodesStringAdmin, test_am.getTestSiteNamesStringAdmin, 'template')
  date_hierarchy = 'starttime'
  save_on_top = True
  modellink = ('',)  
  readonly = ('',)   

  def add_view(self,request, *args, **kwargs):
    self.modellink =('',)
    self.readonly  =('',)
    self.fieldsets = [
      ('Date information', {'fields': ['starttime','endtime']}),
      (None              , {'fields': ['description']        }),
      ('Template'        , {'fields': ['template']           }),
    ]

    if request.user.is_superuser:
      self.form = TestSuperUserAdminForm
    else:
      self.form = TestAdminForm
    return super(TestAdminBase, self).add_view(request,*args, **kwargs)

  def change_view(self,request, *args, **kwargs):
    self.modellink = ('template',)  
    self.readonly  = ('metricperm','inputtype','testscript','jobtemplate','usercode','optionfile')

    self.fieldsets = [
      ('Date information', {'fields': ['starttime','endtime']                                   }),
      (None              , {'fields': ['description']                                           }),
      ('Files'           , {'fields': ['jobtemplate','usercode','optionfile','metricperm']}),
      (None              , {'fields': ['inputtype','testscript','gangabin','extraargs']         }),
      ('Template'        , {'fields': ['template']                                              }),
    ]

    if request.user.is_superuser:
      self.form = TestSuperUserAdminForm
    else:
      self.form = TestAdminForm
    return super(TestAdminBase, self).change_view(request,*args, **kwargs)

  class Media:
    js = ('js/jquery-1.4.2.min.js','js/hide_divs.js',)

  class Meta:
    abstract = True


class TestBackendAdminBase(ActionsAdminBase):

  list_display = ('test', 'backend')
  fieldsets = [
    (None, {'fields':['test','backend']})
  ]

  class Meta:
    abstract = True

class TestCloudAdminBase(ActionsAdminBase):

  list_display = ('test', 'cloud')
  fieldsets = [
    (None, {'fields':['test','cloud']})
  ]

  class Meta:
    abstract = True

class TestDspatternAdminBase(ActionsAdminBase):

  list_display = ('test', 'dspattern')
  fieldsets = [
    (None, {'fields':['test','dspattern']})
  ]

  class Meta:
    abstract = True

class TestHostAdminBase(ActionsAdminBase):

  list_display = ('test', 'host')
  fieldsets = [
    (None, {'fields':['test','host']})
  ]

  class Meta:
    abstract = True

class TestJournalAdminBase(admin.ModelAdmin):

  list_display = ('test','severity','user',test_journal_am.getTestJournalCommentStringAdmin)
  fieldsets = [
    (None,     {'fields':['test','severity','user']}),
    ('Comment',{'fields':['comment']})
  ]

  class Meta:
    abstract = True

class TestSiteAdminBase(ActionsAdminBase):

  list_display = ('test', 'site')
  fieldsets = [
    (None, {'fields':['test','site']})
  ]

  class Meta:
    abstract = True

class TestUserAdminBase(admin.ModelAdmin):

  list_display = ('test',test_user_am.getTestUserNameStringAdmin)
  fieldsets = [
    (None,{'fields':['test','user']})
  ]

  def delete_view(self, request, object_id, extra_context=None):

    allowed_states = ['draft','unapproved','tobescheduled','scheduled']

    request_path = request.path
    app = request_path.split('/')[3]

    tu = custom_import('hc.'+app+'.models.TestUser')
    test = tu.objects.get(pk=object_id).test
    if not test.state in allowed_states:
      raise Http404

    users = [str(tu.user) for tu in test.getTestUsers_for_test.all()]
    user = str(request.user)

    if (user in users) or (request.user.is_superuser):
      return super(TestUserAdminBase, self).delete_view(request, object_id, extra_context=None)
    else:
      raise Http404

  class Meta:
    abstract = True

class TestInlineBase(admin.TabularInline):

  #model -> customized at plugin level
  extra = 3
  fk_name = 'test'
  exclude = ['mtime',]

  class Meta:
    abstract = True


## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## SUMMARY ROBOT BASE CLASSES
##
## *SummaryRobotAdminBase
##

class SummaryRobotAdminBase(admin.ModelAdmin):

  list_display = ('site', 'efficiency')
  fieldsets = [
    ('Feed', {'fields': ['site','efficiency']})
  ]

  class Meta:
    abstract = True


## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##
## METRIC ADMIN BASE CLASSES
##
## *MetricTypeAdminBase
## *MetricAdminBase
## *MetricPermAdminBase
## *[GlobalMetricAdminBase]
## *SiteMetricAdminBase 
## *TestMetricAdminBase 
##

class MetricTypeAdminBase(admin.ModelAdmin):

  list_display = ('name','title','type')
  fieldsets = [
    (None, {'fields': ['name','title','type','description']})
  ]

  class Meta:
    abstract = True

class MetricAdminBase(admin.ModelAdmin):

  list_display = ('url','metric_type',)
  fieldsets = [
    (None, {'fields': ['url','metric_type']})
  ]

  class Meta:
    abstract = True

class MetricPermAdminBase(admin.ModelAdmin):

  list_display = ('name','description',)
  fieldsets = [
    ('Description'          , {'fields': ['name','description']}),
    ('Permissions' , {'fields': ['index','summary','pertab','cron_allowed']}),
  ]

  class Meta:
    abstract = True

class SiteMetricAdminBase(admin.ModelAdmin):

  list_display = ('metric','test','site')
  fieldsets = [
    (None, {'fields': ['metric','test','site']})
  ]

  class Meta:
    abstract = True

class TestMetricAdminBase(admin.ModelAdmin):

  list_display = ('metric','test',)
  fieldsets = [
    (None, {'fields': ['metric','test']})
  ]

  class Meta:
    abstract = True
