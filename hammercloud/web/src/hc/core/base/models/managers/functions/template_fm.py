def getTemplateBackendNames(template):
  """Returns the list of backends names."""
  return [tb.backend.name for tb in (template.getTemplateBackends_for_template
                                             .select_related('backend')
                                             .all())]


def getTemplateSiteNames(template):
  """Returns the list of site names."""
  return [ts.site.name for ts in (template.getTemplateSites_for_template
                                          .select_related('site')
                                          .all())]


def  getTemplateCloudCodes(template):
  """Returns the list of cloud names."""
  return [tc.cloud.code for tc in (template.getTemplateClouds_for_template
                                           .select_related('cloud')
                                           .all())]


def getTemplateHostNames(template):
  """Returns the host names."""
  return [th.host.name for th in (template.getTemplateHosts_for_template
                                          .select_related('host')
                                          .all())]
