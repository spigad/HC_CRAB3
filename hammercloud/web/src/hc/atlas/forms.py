from django import forms
from hc.core.base.forms.metacreator import FormMetaCreator
#from hc.core.base.forms.forms import TestAdminFormBase

from django.contrib.auth.models import User

#from datetime import datetime
#from datetime import timedelta
#
#from django.forms.util import ErrorList

class MetricPermForm(forms.ModelForm):
  __metaclass__ = FormMetaCreator

class TemplateUserForm(forms.ModelForm):
  __metaclass__ = FormMetaCreator

  def clean(self):
    cleaned_data = self.cleaned_data
    if self.cleaned_data.get("user"):
      cleaned_data['user'] = self.cleaned_data.get("user").username
    return self.cleaned_data

#class TestJournalForm(forms.ModelForm):
#  __metaclass__ = FormMetaCreator
#
#  def clean(self):
#
#    cleaned_data = self.cleaned_data
#    if self.cleaned_data.get("user"):
#    
#      cleaned_data['user'] = self.cleaned_data.get("user").username
#
#    return self.cleaned_data

class TestUserForm(forms.ModelForm):
  __metaclass__ = FormMetaCreator

  def clean(self):

    cleaned_data = self.cleaned_data
    if self.cleaned_data.get("user"):

      cleaned_data['user'] = self.cleaned_data.get("user").username

    return self.cleaned_data

#class TestAdminForm(TestAdminFormBase):
#  pass

