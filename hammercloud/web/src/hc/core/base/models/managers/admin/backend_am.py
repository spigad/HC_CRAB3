from hc.core.base.models.managers.functions import backend_fm
from hc.core.utils.generic.truncate import truncateList

def getBackendSitesStringAdmin(backend):
  return truncateList(backend_fm.getSites(backend),2)
getBackendSitesStringAdmin.short_description = 'Sites'

