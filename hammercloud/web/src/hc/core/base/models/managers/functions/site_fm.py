
def getSiteTestMetrics(site, test):
  return (site.getSiteMetrics_for_site
              .filter(test=test)
              .filter(metric__metric_type__in=test.metricTypes)
              .order_by())


def getTestMetrics(test):
  """Returns the set of metrics of the test grouped by site."""
  # Does the same as above, but with just two queries.
  def filter_metrics(queryset):
    return (queryset.select_related('site', 'metric', 'metric__metric_type')
                    .exclude(metric__metric_type__name__startswith='evol'))
  test.perSite = []
  test.overall = filter_metrics(test.getTestMetrics_for_test)
  # Auxiliary structures.
  metrics = filter_metrics(test.getSiteMetrics_for_test)
  sites = set(map(lambda x: x.site, metrics))
  for site in sites:
    site.metrics = [y for y in metrics if y.site_id == site.id]
    test.perSite.append(site)
  return test
