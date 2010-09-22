#from django.db import models

def getTemplateBackendNames(template):
  return [tb.backend.name for tb in template.getTemplateBackends_for_template.all()]

def getTemplateSiteNames(template):
  return [ts.site.name for ts in template.getTemplateSites_for_template.all()]

def  getTemplateCloudCodes(template):
  ################################################## WHY DISTINCT ??
  return [tc.cloud.code for tc in template.getTemplateClouds_for_template.all()]

def getTemplateHostNames(template):
  return [th.host.name for th in template.getTemplateHosts_for_template.all()]


