#from django.contrib.contenttypes.models import ContentType
#from django.db import models

########################################################################
## OTHER
########################################################################

#def getStdOutErr(test):
#  '''
#  Method that return the last # lines of the stdouterr.txt file
#  relative to the test instance
#  '''
#  req = Request("http://atlas-ganga-storage.cern.ch/test_%s/stdouterr.txt"%test.id)
#  try:
#    response = urlopen(req)
#  except URLError, e:
#    return None
#  else:
#    stdouterr = response.read()
#    stdouterrl = stdouterr.rsplit('\n',70)
#    stdouterr = '\n'.join(stdouterrl[2:])
#    return stdouterr.replace('\x1b','')

#def isPanda(test):
#  result = ContentType.objects.get(app_label=test._meta.app_label, model="result").model_class()
#  s = result.objects.filter(test=test.id,site__startswith='ANALY_')
#  if s:
#    return 1
#  return 0

#########################################################################
## BACKENDS BLOCK
#########################################################################

def getTestBackendNames(test):
  ##                                WHY DISTINCT ???
  return [tb.backend.name for tb in test.getTestBackends_for_test.all()]

#########################################################################
## CLOUDS BLOCK
#########################################################################

def getTestCloudCodes(test):
#  return [tc.cloud.code for tc in test.getTestClouds_for_test.all()]
  #return [dic['site__cloud__code'] for dic in test.getTestSites_for_test.all().values('site__cloud__code').distinct()]
  return test.getSummaryTests_for_test.all()[0].clouds.split(',')

def getTestNumClouds(test):
  return len(test.getTestSites_for_test.all().values('site__cloud__code').distinct())

#def getClouds(test):
#  '''
#  Method that return the list of the Cloud instances that belong to the Test instance
#  '''
#  cursor = connection.cursor()
#  cursor.execute('select distinct cloud.id,cloud.code from cloud,site,test_site where test_site.test=%s and test_site.site=site.id and site.cloud=cloud.id',[self.id])
#  return [Cloud(id=c[0],code=c[1]) for c in cursor.fetchall()]
#  return list(set([s.cloud for s in test.getTestSites_for_test.all()]))
      

#########################################################################
## DSPATTERNS BLOCK
#########################################################################

#def getDsPatterns(test):
#  '''
#  Method that return the Dspattern object related to the Test instance
#  '''
#  dspattern = ContentType.objects.get(app_label=test._meta.app_label, model="dspattern").model_class()
#  return dspattern.objects.filter(testdspattern__test__exact=test.id).only('pattern')

#########################################################################
## HOSTS BLOCK
#########################################################################

def getTestHostNames(test):
  return [th.host.name for th in test.getTestHosts_for_test.all()]


#########################################################################
## SITES BLOCK
#########################################################################

def getTestSiteNames(test):
  #return [ts.site.name for ts in test.getTestSites_for_test.all().select_related('site')]
  return test.getSummaryTests_for_test.all()[0].sites.split(',')

def getTestNumSites(test):
  return test.getTestSites_for_test.count()   

#########################################################################
## JOBS BLOCK
#########################################################################

def getTestTotalJobs(test):
#  '''
#  Method that return the number of the total jobs of the Test object instance
#  '''
#  result = ContentType.objects.get(app_label=test._meta.app_label, model="result").model_class()
#  return result.objects.filter(test=test.id).count()
  #return test.getResults_for_test.exclude(ganga_subjobid=1000000).count()
  return test.getSummaryTests_for_test.all()[0].total

def getTestSubmittedJobs(test):
#  '''
#  Method that return the number of the submitted jobs of the Test object instance
#  '''
#  result = ContentType.objects.get(app_label=test._meta.app_label, model="result").model_class()
#  return result.objects.filter(test=test.id).filter(ganga_status='s').count()
  #return test.getResults_for_test.filter(ganga_status='s').exclude(ganga_subjobid=1000000).count()
  return test.getSummaryTests_for_test.all()[0].submitted

def getTestRunningJobs(test):
#  '''
#  Method that return the number of the submitted jobs of the Test object instance
#  '''
#  result = ContentType.objects.get(app_label=test._meta.app_label, model="result").model_class()
#  return result.objects.filter(test=test.id).filter(ganga_status='r').count()
  #return test.getResults_for_test.filter(ganga_status='r').exclude(ganga_subjobid=1000000).count()
  return test.getSummaryTests_for_test.all()[0].running

def getTestCompletedJobs(test):
#  '''
#  Method that return the number of the submitted jobs of the Test object instance
#  '''
#  result = ContentType.objects.get(app_label=test._meta.app_label, model="result").model_class()
#  return result.objects.filter(test=test.id).filter(ganga_status='c').count()
  #return test.getResults_for_test.filter(ganga_status='c').exclude(ganga_subjobid=1000000).count()
  return test.getSummaryTests_for_test.all()[0].completed

def getTestFailedJobs(test):
#  '''
#  Method that return the number of the submitted jobs of the Test object instance
#  '''
#  result = ContentType.objects.get(app_label=test._meta.app_label, model="result").model_class()
#  return result.objects.filter(test=test.id).filter(ganga_status='f').count()
  #return test.getResults_for_test.filter(ganga_status='f').exclude(ganga_subjobid=1000000).count()
  return test.getSummaryTests_for_test.all()[0].failed

def getTestOtherJobs(test):
#  '''
#  Method that return the number of other jobs of the Test object instance
#  '''
#  result = ContentType.objects.get(app_label=test._meta.app_label, model="result").model_class()
#  return result.objects.filter(test=test.id).filter(ganga_status='f').count()
  return (test.getResults_for_test.exclude(ganga_status='s')
                                  .exclude(ganga_status='r')
                                  .exclude(ganga_status='c')
                                  .exclude(ganga_status='f')
                                  .exclude(ganga_subjobid=1000000).count())

#########################################################################
## METRICS BLOCK
#########################################################################

#def getTestMetricsTypes(test):
#  '''
#  Method that return a list containing the MetricType that are available
#  for the Test instance
#  '''
#  return MetricType.objects.filter(metric__testmetric__test=self.id).only('name').distinct()
#   
#def getTestMetricsTypesNames(self):
#  '''
#  Method that return a list containing the MetricType names that are available
#  for the Test instance
#  '''
#  return [i.name for i in self.getMetricsTypes()]
#
#def getTestMetricsTypesIndex(test):
#  '''
#  Method that return a list containing the MetricType names that
#  are showed in the Overall tab for a single Test page
#  '''
#  return ['status','cpu','eventrate']
#  
   
def getTestSitesMetrics(test,metric_type):
  return test.getSiteMetrics_for_test.filter(metric__metric_type=metric_type)
