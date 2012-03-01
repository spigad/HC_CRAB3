from hc.core.base.models.managers.functions import test_fm,site_fm
from hc.core.utils.generic.class_func import custom_import


from datetime import date,timedelta

class Datahelper:

  def annotateTest(self,test):
    sts = test.getSummaryTests_for_test.all()[0]
    test.sites     = sts.sites.split(',')
    test.clouds    = sts.clouds.split(',')
    test.numsites  = len(test.sites)
    test.total     = sts.total
    test.submitted = sts.submitted
    test.failed    = sts.failed
    test.completed = sts.completed
    test.running   = sts.running
    test.other     = test.total - (test.submitted + test.running + test.completed + test.failed)
    return test

  def annotateTests(self,tests):

    for test in tests:
      test = self.annotateTest(test)
  
    return tests

  def annotateTestPerMetric(self,test):

    test.metricTypes = test.metricperm.pertab.all()     
    test.perMetric = []

    for metric_type in test.metricTypes:
      metric_type.sites = list(test.getTestMetrics_for_test.filter(metric__metric_type=metric_type)) + list(test_fm.getTestSitesMetrics(test,metric_type))
      test.perMetric.append(metric_type)
    return test

  def annotateTestPerSite(self,test):

    test_sites = test.getTestSites_for_test.all()
    test.metricTypes = test.metricperm.pertab.all()

    test.perSite = []
  
    test.overall = list(test.getTestMetrics_for_test.exclude(metric__metric_type__name__startswith='evol_'))

    for test_site in test_sites:

      site = test_site.site
           
      site.metrics = list(site_fm.getSiteTestMetrics(site,test))
           
#      site.backend_exitcodes = site.getBackendExitCodes(test)
#      site.app_exitcodes = site.getAppExitCodes(test)
#      site.backend_reasons = site.getBackendReasons(test)
#      site.numevents = site.getNumEvents(test)
#      (site.numfiles,site.numfiles_details) = site.getTestNumfiles(test)
#      site.out = site.getTestOutput(test)
           
      test.perSite.append(site)
    return test

  def annotateSitesEfficiency(self,sites,day,app):

#    yesterday = date.today()-timedelta(1)

    s_r = custom_import('hc.%s.models.SummaryRobot'%(app))

    srs = list(s_r.objects.filter(site__in=sites).filter(day=day))

    for site in list(sites):
      sr = filter(lambda x: x.site_id == site.id, srs)
      if sr: 
        site.eff = sr[0].efficiency
      else:
        site.eff = -1

    return sites
