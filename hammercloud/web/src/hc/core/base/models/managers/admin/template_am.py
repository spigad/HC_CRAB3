from hc.core.base.models.managers.functions import template_fm
from hc.core.utils.generic.truncate import truncateList

def getTemplateBackendNamesStringAdmin(template):
  return truncateList(template_fm.getTemplateBackendNames(template),2)
getTemplateBackendNamesStringAdmin.short_description = 'Backends'

def getTemplateSiteNamesStringAdmin(template):
  return truncateList(template_fm.getTemplateSiteNames(template),2)
getTemplateSiteNamesStringAdmin.short_description = 'Sites'

def getTemplateCloudCodesStringAdmin(template):
  return truncateList(template_fm.getTemplateCloudCodes(template),2)
getTemplateCloudCodesStringAdmin.short_description = 'Clouds'

def getTemplateHostNamesStringAdmin(template):
  return truncateList(template_fm.getTemplateHostNames(template),2)
getTemplateHostNamesStringAdmin.short_description = 'Hosts'
