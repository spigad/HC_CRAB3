from django import forms
from django.contrib.admin.widgets import FilteredSelectMultiple
from django.contrib.auth.models import User

from hc.core.utils.generic.class_func import custom_import

from datetime import datetime
from datetime import timedelta
from django.utils.safestring import mark_safe
from django.utils.html import escape

from django.forms.util import ErrorList

class FormGenerator():

  def getMetricPermissionForm(self,module):

    mt = custom_import('hc.'+module+'.models.MetricType')

    dic = {}
    dic['name']         = forms.CharField(max_length=255)
    dic['description']  = forms.CharField(max_length=255)
    dic['index']        = forms.ModelMultipleChoiceField(mt.objects.all(),widget=FilteredSelectMultiple("MetricTypes",False))
    dic['summary']      = forms.ModelMultipleChoiceField(mt.objects.all(),widget=FilteredSelectMultiple("MetricTypes",False))
    dic['pertab']       = forms.ModelMultipleChoiceField(mt.objects.all(),widget=FilteredSelectMultiple("MetricTypes",False))
    dic['cron_allowed'] = forms.ModelMultipleChoiceField(mt.objects.all(),widget=FilteredSelectMultiple("MetricTypes",False))

    return dic

  def getTestJournalForm(self,module):

    SEVERITY_CHOICES = (
      (u'common', u'common'),
      (u'maintenance', u'maintenance'),
      (u'error',u'error'),
      (u'other',u'other')
    )

    Test = custom_import('hc.'+module+'.models.Test')

    dic = {}
    dic['severity'] = forms.CharField(max_length=255,widget=forms.Select(choices=SEVERITY_CHOICES))
    dic['test']     = forms.ModelChoiceField(queryset=Test.objects.all())
    dic['user']     = forms.ModelChoiceField(queryset=User.objects.filter(groups__name__startswith=module))
    dic['comment']  = forms.CharField(max_length=4095,widget=forms.Textarea)

    return dic

  def getTemplateUserForm(self,module):

    Template = custom_import('hc.'+module+'.models.Template')

    dic = {}
    dic['template'] = forms.ModelChoiceField(queryset=Template.objects.all())
    dic['user']     = forms.ModelChoiceField(queryset=User.objects.filter(groups__name__startswith=module))

    return dic
    
  def getTestUserForm(self,module):

    Test = custom_import('hc.'+module+'.models.Test')

    dic = {}
    dic['test']     = forms.ModelChoiceField(queryset=Test.objects.all())
    dic['user']     = forms.ModelChoiceField(queryset=User.objects.filter(groups__name__startswith=module))

    return dic


## FORMS WITH METHODS

class TestAdminForm(forms.ModelForm):
  def clean(self):
    '''
    Personalization of the clean method.
    '''
    cleaned_data = self.cleaned_data
    if not self.instance.state in ['draft','unapproved']:
      self._errors["starttime"] = ErrorList(["You cannot modify a test unless it is in draft or unapproved state. Use the Manage page instead."])
    else:
      if cleaned_data.get("starttime"):
        starttime = cleaned_data["starttime"]
        if self.instance.id and (not self.instance.state in ['draft','unapproved']):
          if starttime != self.instance.starttime:
            self.cleaned_data["starttime"] = self.instance.starttime
            self.changed_data.remove('starttime')
            self._errors["starttime"] = ErrorList(["Start time not modifiable, leave %s"%str(self.instance.starttime)])
          if self.cleaned_data.get("endtime") and self.instance.state in ['completed','error']:
            if cleaned_data["endtime"] != self.instance.endtime:
              self._errors["endtime"] = ErrorList(["You can't change anymore the endtime, leave %s"%str(self.instance.endtime)])
        else:
          if starttime-datetime.now()<timedelta(0,0,0,0,30):
            self._errors["starttime"] = ErrorList(["Start time must be more than 30 minutes in the future"])
        cleaned_data["starttime"] = starttime.replace(second=0)
        if cleaned_data.get("endtime"):
          cleaned_data["endtime"] = cleaned_data["endtime"].replace(second=0)
          if cleaned_data["endtime"] < starttime:
            self._errors["endtime"] = ErrorList(["End time before than start time"])

    return cleaned_data

class TestSuperUserAdminForm(forms.ModelForm):
#  class Meta:
#        '''
#        Meta informations for the form.
#        '''
#    from hc.atlas.models import Test
#    model = Test

  def clean(self):
    cleaned_data = self.cleaned_data
    if not self.instance.state in ['draft','unapproved']:
      self._errors["starttime"] = ErrorList(["You cannot modify a test unless it is in draft or unapproved state. Use the Manage page instead."])
    else:
      if cleaned_data.get("starttime"):
        starttime = cleaned_data["starttime"]
        if self.instance.id and (not self.instance.state in ['draft','unapproved']):
          if starttime != self.instance.starttime:
            self.cleaned_data["starttime"] = self.instance.starttime
            self.changed_data.remove('starttime')
            self._errors["starttime"] = ErrorList(["Start time not modifiable, leave %s"%str(self.instance.starttime)])
          if self.cleaned_data.get("endtime") and self.instance.state in ['completed','error']:
            if cleaned_data["endtime"] != self.instance.endtime:
              self._errors["endtime"] = ErrorList(["You can't change anymore the endtime, leave %s"%str(self.instance.endtime)])
#       else:
#         if starttime-datetime.now() < timedelta(0,0,0,0,30)
#           self._errors["starttime"] = ErrorList(["Startime cannot be on the past."])
        cleaned_data["starttime"] = starttime.replace(second=0)
        if cleaned_data.get("endtime"):
          cleaned_data["endtime"] = cleaned_data["endtime"].replace(second=0)
          if cleaned_data["endtime"] < starttime:
            self._errors["endtime"] = ErrorList(["End time before than start time"])

    return cleaned_data


############## OTHERS ############################


class ReadOnlyWidget(forms.Widget):
  def __init__(self, original_value, display_value):
    self.original_value = original_value
    self.display_value = display_value

    super(ReadOnlyWidget, self).__init__()

  def render(self, name, value, attrs=None):
    if self.display_value is not None:
      return unicode(self.display_value)
    return unicode(self.original_value)

  def value_from_datadict(self, data, files, name):
    return self.original_value

class ReadOnlyAdminFields(object):
  def get_form(self, request, obj=None):

    form = super(ReadOnlyAdminFields, self).get_form(request, obj)

    if hasattr(self, 'readonly'):
      for field_name in self.readonly:
        if field_name in form.base_fields:
          if hasattr(obj, 'get_%s_display' % field_name):
            display_value = getattr(obj, 'get_%s_display' % field_name)()
            original_value  = getattr( obj, field_name, '' )
          elif hasattr( obj, '%s_id' % field_name ):
            original_value  = getattr( obj, "%s_id" % field_name, '' )
            display_value   = getattr( obj, field_name, '' )
          # other field type
          else:
            original_value  = getattr( obj, field_name, '' )
            display_value   = getattr( obj, field_name, '' )

#          else:
#            display_value = None
#          form.base_fields[field_name].widget = ReadOnlyWidget(getattr(obj, field_name, ''), display_value)

          form.base_fields[field_name].widget     = ReadOnlyWidget( original_value, display_value )
          form.base_fields[field_name].required = False

    return form

class ModelLinkWidget(forms.HiddenInput):

  def __init__(self, admin_site, original_object,superuser):
    self.admin_site = admin_site
    self.original_object = original_object
    self.superuser = superuser
    super(ModelLinkWidget,self).__init__()
   
  def render(self, name, value, attrs=None):

    if self.original_object is not None:
      try:
        if self.superuser:
          link = '../../%s/%d' % (#self.admin_site.root_path,
                             #      self.original_object._meta.app_label,
                                   self.original_object._meta.module_name,
                                   self.original_object.id)
        else:
          link = '../../../../app/%s/%s/%d'%(self.original_object._meta.app_label,
                                             self.original_object._meta.module_name,
                                             self.original_object.id)
        return super(ModelLinkWidget, self).render(name, value, attrs) + mark_safe('<a href="%s">%s</a>' % (link, escape(unicode(self.original_object))))
      except:
        return "None"    
    else:
      return "None"
                                                               
class ModelLinkAdminFields(object):
  def get_form(self, request, obj=None):

    form = super(ModelLinkAdminFields, self).get_form(request, obj)

    if hasattr(self, 'modellink'):
      for field_name in self.modellink:
        if field_name in form.base_fields:
          form.base_fields[field_name].widget = ModelLinkWidget(self.admin_site, getattr(obj, field_name, ''),request.user.is_superuser)
          form.base_fields[field_name].required = False
    return form
