from collections import defaultdict
from datetime import timedelta
from django.db.models import Avg, Max, Min
from django.utils.timezone import now
from hc.core.base.models.managers.functions import site_fm, test_fm
from hc.core.base.views.configuration import PARTICULARITIES
from hc.core.utils.generic.class_func import custom_import

"""The datahelper module offers general functionality to manage HC data."""


class Datahelper(object):
    """Provides methods to perform common tasks with HC specific data."""

    def annotateTest(self, test):
        """Adds information to the test object from the SummaryTest."""
        super(Datahelper, self).__init__()
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

    # TODO(rmedrano): the following methods have a lot in common and should be
    #                 refactored.

    def timeBreakdownSeries(self, app, starttime=now() - timedelta(days=7),
                            sites=None, clouds=None, templates=None,
                            golden=False, category=None, site_class=None):
        """Generates the time breakdown for the filters provided.

        Receives the following arguments:
         starttime = time zone aware datetime object for the start time.
         sites = iterable of site objects to filter .
         clouds = clouds for the filtering, iterable.
         templates = templates list to filter out.
         golden = if set, only will who results from golden templates.
         category = whether stress tests or functional (if None, both).
         site_class = whether production or analysis (if None, both).
        """
        kwargs = {}
        for k, v in PARTICULARITIES[app]['timings'].iteritems():
            for m in (Min, Avg, Max):
                kwargs['%s_%s' % (k, m.__name__)] = m(v)
        s_t_s = custom_import('hc.%s.models.SummaryTestSite' % (app))
        queryset = (s_t_s.objects
                         .filter(test__starttime__gt=starttime)
                         .filter(test_site__site__enabled=True))
        if sites:
            queryset = queryset.filter(test_site__site__in=sites)
        if clouds:
            queryset = queryset.filter(test_site__site__cloud__in=clouds)
        if templates:
            queryset = queryset.filter(test_site__test__template__in=templates)
        #if golden:
        queryset = queryset.filter(test_site__test__template__is_golden=True)
        if category:
            queryset = queryset.filter(test_site__test__template__category='category')
        if site_class:
            raise NotImplementedError('Not yet added to the DB.')
        summaries = (queryset.values('test_site__site__name')
                             .annotate(**kwargs))
        series = defaultdict(list)
        for summary in summaries:
            # Exclude possible values with null.
            if not all(x is None for k, x in summary.iteritems()
                       if k != 'test_site__site__name'):
                for metric, value in summary.iteritems():
                    series[metric].append(value)
        return series

    def performanceSeries(self, app, starttime=now() - timedelta(days=7),
                          sites=None, clouds=None, templates=None,
                          golden=False, category=None, site_class=None):
        """Generates the performance comparison for the filters set.

        Receives the following arguments:
         starttime = time zone aware datetime object for the start time.
         sites = iterable of site objects to filter .
         clouds = clouds for the filtering, iterable.
         templates = templates list to filter out.
         golden = if set, only will who results from golden templates.
         category = whether stress tests or functional (if None, both).
         site_class = whether production or analysis (if None, both).
        """
        kwargs = {}
        for k, v in PARTICULARITIES[app]['performance'].iteritems():
            for m in (Min, Avg, Max):
                kwargs['%s_%s' % (k, m.__name__)] = m(v)
        s_t_s = custom_import('hc.%s.models.SummaryTestSite' % (app))
        queryset = (s_t_s.objects
                         .filter(test__starttime__gt=starttime)
                         .filter(test_site__site__enabled=True))
        if sites:
            queryset = queryset.filter(test_site__site__in=sites)
        if clouds:
            queryset = queryset.filter(test_site__site__cloud__in=clouds)
        if templates:
            queryset = queryset.filter(test_site__test__template__in=templates)
        #if golden:
        queryset = queryset.filter(test_site__test__template__is_golden=True)
        if category:
            queryset = queryset.filter(test_site__test__template__category='category')
        if site_class:
            raise NotImplementedError('Not yet added to the DB.')
        summaries = (queryset.values('test_site__site__name')
                             .annotate(**kwargs))
        series = defaultdict(list)
        for summary in summaries:
            # Exclude possible values with null.
            if not all(x is None for k, x in summary.iteritems()
                       if k != 'test_site__site__name'):
                for metric, value in summary.iteritems():
                    series[metric].append(value)
        return series
