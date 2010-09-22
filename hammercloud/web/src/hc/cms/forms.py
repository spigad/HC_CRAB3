from django import forms
from hc.core.base.forms.metacreator import FormMetaCreator

from django.contrib.auth.models import User

class MetricPermissionForm(forms.ModelForm):
  __metaclass__ = FormMetaCreator

class TemplateUserForm(forms.ModelForm):
  __metaclass__ = FormMetaCreator

  def clean(self):
    cleaned_data = self.cleaned_data
    if self.cleaned_data.get("user"):
      cleaned_data['user'] = self.cleaned_data.get("user").username
    return self.cleaned_data

class TestJournalForm(forms.ModelForm):
  __metaclass__ = FormMetaCreator

  def clean(self):

    cleaned_data = self.cleaned_data
    if self.cleaned_data.get("user"):
    
      cleaned_data['user'] = self.cleaned_data.get("user").username

    return self.cleaned_data

class TestUserForm(forms.ModelForm):
  __metaclass__ = FormMetaCreator

  def clean(self):

    cleaned_data = self.cleaned_data
    if self.cleaned_data.get("user"):

      cleaned_data['user'] = self.cleaned_data.get("user").username

    return self.cleaned_data

