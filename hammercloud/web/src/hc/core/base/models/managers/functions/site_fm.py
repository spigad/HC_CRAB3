#from django.contrib.contenttypes.models import ContentType
#from django.db import models

def getSiteTestMetrics(site,test):
  return site.getSiteMetrics_for_site.filter(test=test).filter(metric__metric_type__in=test.metricTypes)

