from hc.core.base.models.managers.functions import site_fm, test_fm
from hc.core.utils.generic.class_func import custom_import

"""The datahelper module offers general functionality to manage HC data."""


class Datahelper(object):
    """Provides methods to perform common tasks with HC specific data."""

    def annotateTest(self, test):
        """Adds information to the test object from the SummaryTest."""
        # This lookup should be already chached in test. We're calling to
        # ensure that the data is there.
        sts = test.getSummaryTests_for_test.all()[0]
        test.sites = sts.sites.split(',')
        test.clouds = sts.clouds.split(',')
        test.numsites = len(test.sites)
        test.total = sts.total
        test.submitted = sts.submitted
        test.failed = sts.failed
        test.completed = sts.completed
        test.running = sts.running
        test.other = test.total - (test.submitted + test.running +
                                   test.completed + test.failed)
        return test

    def annotateTests(self, tests):
        """Performs the annotation over a series of tests in an iterable."""
        return map(self.annotateTest, tests)

    def annotateTestPerMetric(self, test):
        """Adds information to the test grouped by metric."""
        return test_fm.getTestMetrics(test)

    def annotateTestPerSite(self, test):
        """Adds information to the test grouped by site."""
        return site_fm.getTestMetrics(test)

    def annotateSitesEfficiency(self, sites, day, app):
        """Annotates the efficiency of the sites provided."""
        s_r = custom_import('hc.%s.models.SummaryRobot' % (app))
        srs = list(s_r.objects.filter(site__in=sites).filter(day=day))
        for site in list(sites):
            sr = filter(lambda x: x.site_id == site.id, srs)
            if sr:
                site.eff = sr[0].efficiency
            else:
                site.eff = -1
        return sites
