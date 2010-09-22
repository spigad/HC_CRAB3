from hc.core.base.models.managers.functions import cloud_fm
from hc.core.utils.generic.truncate import truncateList

def getCloudSitesStringAdmin(cloud):
  return truncateList(cloud_fm.getSites(cloud),2)
getCloudSitesStringAdmin.short_description = 'Sites'

