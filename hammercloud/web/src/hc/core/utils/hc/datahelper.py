from hc.core.base.models.managers.functions import test_fm,site_fm

from datetime import date,timedelta

class Datahelper:

  def annotateTest(self,test):
    test.sites     = test_fm.getTestSiteNames(test)
    test.clouds    = test_fm.getTestCloudCodes(test)
    test.numsites  = test_fm.getTestNumSites(test)
    test.total     = test_fm.getTestTotalJobs(test)
    test.submitted = test_fm.getTestSubmittedJobs(test)
    test.failed    = test_fm.getTestFailedJobs(test)
    test.completed = test_fm.getTestCompletedJobs(test)
    test.running   = test_fm.getTestRunningJobs(test)
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

  def annotateSitesEfficiency(self,sites,day):

#    yesterday = date.today()-timedelta(1)

    for site in sites:

#      sr = site.getSummaryRobots_for_site.filter(day=yesterday)   
      sr = site.getSummaryRobots_for_site.filter(day=day)
      if sr: 
        sr = sr[0]
        site.eff = sr.efficiency
      else:
        site.eff = -1

    return sites
