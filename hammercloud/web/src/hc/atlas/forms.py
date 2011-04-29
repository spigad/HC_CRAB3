from django import forms
from hc.core.base.forms.metacreator import AdminFormMetaCreator
#from hc.core.base.forms.forms import TestAdminFormBase

from hc.core.utils.generic.class_func import custom_import	

from hc.atlas.models import TestLog

from django.contrib.auth.models import User

#from datetime import datetime
#from datetime import timedelta
#
#from django.forms.util import ErrorList

class MetricPermForm(forms.ModelForm):
  __metaclass__ = AdminFormMetaCreator

class TemplateUserForm(forms.ModelForm):
  __metaclass__ = AdminFormMetaCreator

  def clean(self):
    cleaned_data = self.cleaned_data
    if self.cleaned_data.get("user"):
      cleaned_data['user'] = self.cleaned_data.get("user").username
    return self.cleaned_data

class TestLogForm(forms.ModelForm):
  __metaclass__ = AdminFormMetaCreator

  def clean(self):

    cleaned_data = self.cleaned_data
    if self.cleaned_data.get("user"):
      self.cleaned_data["user"] = self.cleaned_data.get("user").username

    return self.cleaned_data

class TestUserForm(forms.ModelForm):
  __metaclass__ = AdminFormMetaCreator

  def clean(self):

    cleaned_data = self.cleaned_data
    if self.cleaned_data.get("user"):

      cleaned_data['user'] = self.cleaned_data.get("user").username

    return self.cleaned_data


