from hc.core.base.models.managers.functions import test_fm
from hc.core.utils.generic.truncate import truncateList

def getTestBackendNamesStringAdmin(test):
  return truncateList(test_fm.getTestBackendNames(test),2)
getTestBackendNamesStringAdmin.short_description = 'Backends'

def getTestHostNamesStringAdmin(test):
  return truncateList(test_fm.getTestHostNames(test),2)
getTestHostNamesStringAdmin.short_description = 'Hosts'

def getTestSiteNamesStringAdmin(test):
  return truncateList(test_fm.getTestSiteNames(test),2)
getTestSiteNamesStringAdmin.short_description = 'Sites'

def getTestCloudCodesStringAdmin(test):
  return truncateList(test_fm.getTestCloudCodes(test),2)
getTestCloudCodesStringAdmin.short_description = 'Clouds'

def getTestJobTemplateStringAdmin(test):
  return str(test.jobtemplate).rsplit('/',1)[1]
getTestJobTemplateStringAdmin.short_description = 'Jobtemplate'
   
def getTestUsercodeStringAdmin(test):
  return str(test.usercode).rsplit('/',1)[1]
getTestUsercodeStringAdmin.short_description = 'Usercode'
   
def getTestOptionFileStringAdmin(test):
  return str(test.option_file).rsplit('/',1)[1]
getTestOptionFileStringAdmin.short_description = 'Option File'
