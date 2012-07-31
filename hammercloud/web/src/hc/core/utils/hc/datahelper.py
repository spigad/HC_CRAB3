from hc.core.base.models.managers.functions import test_fm,site_fm
from hc.core.utils.generic.class_func import custom_import


from datetime import date,timedelta

class Datahelper:

  def annotateTest(self, test):
    """Adds information to the test object from the SummaryTest."""

    # This lookup should be already chached in test. We're calling to
    # ensure that the data is there.
    sts = test.getSummaryTests_for_test.all()[0]

    test.sites     = sts.sites.split(',')
    test.clouds    = sts.clouds.split(',')
    test.numsites  = len(test.sites)
    test.total     = sts.total
    test.submitted = sts.submitted
    test.failed    = sts.failed
    test.completed = sts.completed
    test.running   = sts.running
    test.other     = test.total - (test.submitted +
                                   test.running +
                                   test.completed +
                                   test.failed)
    return test

  def annotateTests(self,tests):

    for test in tests:
      test = self.annotateTest(test)
  
    return tests

  def annotateTestPerMetric(self,test):
    """Adds information to the test grouped by metric."""
    return test_fm.getTestMetrics(test)

  def annotateTestPerSite(self, test):
    """Adds information to the test grouped by site."""
    return site_fm.getTestMetrics(test)

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
