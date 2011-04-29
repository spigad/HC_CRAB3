from django import forms
from django.contrib.admin.widgets import FilteredSelectMultiple
from django.contrib.auth.models import User

from hc.core.utils.generic.class_func import custom_import
#from hc.core.base.forms.metacreator import FormMetaCreator

from datetime import datetime
from datetime import timedelta
from django.utils.safestring import mark_safe
from django.utils.html import escape

from django.forms.util import ErrorList

from django.forms import ModelForm

class FormGenerator:

  def getMetricPermForm(self,module):

    mt = custom_import('hc.'+module+'.models.MetricType')

    dic = {}
    dic['name']         = forms.CharField(max_length=255)
    dic['description']  = forms.CharField(max_length=255)
    dic['index']        = forms.ModelMultipleChoiceField(mt.objects.all(),widget=FilteredSelectMultiple("MetricTypes",False))
    dic['summary']      = forms.ModelMultipleChoiceField(mt.objects.all(),widget=FilteredSelectMultiple("MetricTypes",False))
    dic['pertab']       = forms.ModelMultipleChoiceField(mt.objects.all(),widget=FilteredSelectMultiple("MetricTypes",False))
    dic['cron_allowed'] = forms.ModelMultipleChoiceField(mt.objects.all(),widget=FilteredSelectMultiple("MetricTypes",False))

    return dic

  def getTestLogForm(self,module):

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
    dic['user']     = forms.ModelChoiceField(queryset=User.objects.filter(groups__name__startswith=module).distinct())
    dic['comment']  = forms.CharField(max_length=4095,widget=forms.Textarea)
    return dic

  def getTestLogReportForm(self,module):

    SEVERITY_CHOICES = (
      (u'common', u'common'),
      (u'maintenance', u'maintenance'),
      (u'error',u'error'),
      (u'other',u'other')
    )

    dic = {}
    dic['severity'] = forms.CharField(max_length=255,widget=forms.Select(choices=SEVERITY_CHOICES))
    dic['comment']  = forms.CharField(max_length=4095,widget=forms.Textarea)

    class Meta:
      model  = custom_import('hc.'+module+'.models.TestLog')
#      fields = ('severity','comment')

    dic['Meta'] = Meta

    return dic

  def getTestRunningModifyForm(self,module):

    dic = {}

    dic['endtime'] = forms.DateTimeField()
    dic['pause']   = forms.BooleanField(required=False)

    class Meta:
      model = custom_import('hc.'+module+'.models.Test')
#      fields = ('endtime','pause')

    dic['Meta'] = Meta
    return dic

  def getTemplateUserForm(self,module):

    Template = custom_import('hc.'+module+'.models.Template')

    dic = {}
    dic['template'] = forms.ModelChoiceField(queryset=Template.objects.all())
    dic['user']     = forms.ModelChoiceField(queryset=User.objects.filter(groups__name__startswith=module).distinct())

    return dic
    
  def getTestUserForm(self,module):

    Test = custom_import('hc.'+module+'.models.Test')

    dic = {}
    dic['test']     = forms.ModelChoiceField(queryset=Test.objects.all())
    dic['user']     = forms.ModelChoiceField(queryset=User.objects.filter(groups__name__startswith=module).distinct())

    return dic



                                                               
