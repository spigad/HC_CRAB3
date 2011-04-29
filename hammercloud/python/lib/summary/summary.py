from hc.core.utils.hc.stats import Stats
from hc.core.utils.generic.class_func import custom_import

from datetime import datetime,timedelta

from hc.core.utils.plots.charts import hist,pie,line

import numpy

def summarize(app,test):

  now = datetime.now()

  s_t   = test.getSummaryTests_for_test.all()[0]
  s_t_s = test.getSummaryTestSites_for_test.all()

  stats = Stats()

  Qobjects                = {}
  Qobjects['test']        = [test]
  #small hack to remove duplicated in the list
  Qobjects['metric_type'] = list(set(list(test.metricperm.index.all()) + list(test.metricperm.pertab.all()) + list(test.metricperm.summary.all())))
  Qobjects['site']        = [ ts.site for ts in test.getTestSites_for_test.all() ]

  commands = {'sort_by':'test','type':'raw_value','completed':False}

  title,values = stats.process(Qobjects,commands)[0]
  values = dict(values)

  s_t.submitted = float(test.getResults_for_test.filter(ganga_status='s').count())
  s_t.running   = float(test.getResults_for_test.filter(ganga_status='r').count())
  s_t.completed = float(test.getResults_for_test.filter(ganga_status='c').count())
  s_t.failed    = float(test.getResults_for_test.filter(ganga_status='f').count())
  s_t.total     = float(test.getResults_for_test.count())

  if s_t.total:
    s_t.c_t = s_t.completed / s_t.total
    s_t.f_t = s_t.failed / s_t.total

  if s_t.completed or s_t.failed:
    s_t.c_cf = s_t.completed / (s_t.completed + s_t.failed)

  if values.has_key('Overall.'):
    for metric in test.metricperm.summary.all():
      rate = [float(dic[metric.name]) for dic in values['Overall.'] if (metric.name != 'c_cf' and dic[metric.name] != None)]
      if rate:
        mean = round(numpy.mean(rate),3)
        setattr(s_t,metric.name,mean)

  s_t.save()

  SummaryEvolution = custom_import('hc.%s.models.SummaryEvolution'%(app))

  frozen_time = datetime.now().replace(second=0).replace(microsecond=0)
  min = str(frozen_time.minute)
  if min > '9':
    min = min[1]

  if min > '4':
    frozen_time = frozen_time.replace(minute=5)
  else:
    frozen_time = frozen_time.replace(minute=0)

  evol_lock   = SummaryEvolution.objects.filter(test=test).filter(time__gt=frozen_time-timedelta(minutes=5))

  for sts in s_t_s:
    sts.submitted = float(test.getResults_for_test.filter(site=sts.test_site.site).filter(ganga_status='s').count())
    sts.running   = float(test.getResults_for_test.filter(site=sts.test_site.site).filter(ganga_status='r').count())
    sts.completed = float(test.getResults_for_test.filter(site=sts.test_site.site).filter(ganga_status='c').count())
    sts.failed    = float(test.getResults_for_test.filter(site=sts.test_site.site).filter(ganga_status='f').count())
    sts.total     = float(test.getResults_for_test.filter(site=sts.test_site.site).count())

    if not evol_lock:
      #Save to Summary Evolution
      se = SummaryEvolution(test=test,site=sts.test_site.site,time=frozen_time)
      se.submitted = sts.submitted
      se.running   = sts.running
      se.completed = sts.completed
      se.failed    = sts.failed
      se.total     = sts.total
      se.save()

    if sts.total:
      sts.c_t = sts.completed / sts.total
      sts.f_t = sts.failed / sts.total

    if sts.completed or sts.failed:
      sts.c_cf = sts.completed / (sts.completed + sts.failed)

    if values.has_key(sts.test_site.site.name):
      for metric in test.metricperm.summary.all():
        rate = [float(dic[metric.name]) for dic in values[sts.test_site.site.name] if (metric.name != 'c_cf' and dic[metric.name] != None)]
        if rate:
          mean = round(numpy.mean(rate),3)
          setattr(sts,metric.name,mean)

    sts.save()
  print 'Summarize for %s took %s'%(test.id,datetime.now()-now)

def plot(app,test,completed=False):

  now = datetime.now()

  s_t   = test.getSummaryTests_for_test.all()[0]
  s_t_s = test.getSummaryTestSites_for_test.all()

  stats = Stats()

  Qobjects                = {}
  Qobjects['test']        = [test]
  #small hack to remove duplicated in the list
  Qobjects['metric_type'] = list(set(list( test.metricperm.index.all()) + list(test.metricperm.pertab.all()) ))
  Qobjects['site']        = [ ts.site for ts in test.getTestSites_for_test.all() ]

  commands = {'sort_by':'test','type':'plot','completed':completed}

  test_title,values = stats.process(Qobjects,commands)[0][0]

  MetricType= custom_import('hc.%s.models.MetricType'%(app))
  Metric = custom_import('hc.%s.models.Metric'%(app))
  TestMetric = custom_import('hc.%s.models.TestMetric'%(app))
  SiteMetric = custom_import('hc.%s.models.SiteMetric'%(app))
  Site = custom_import('hc.%s.models.Site'%(app))

  for metric_title,urls in values:
    mt = MetricType.objects.filter(title=metric_title)
    if mt:

      for plot_title,url in urls:

        if not url:
          print '%s %s'%(plot_title,url)
          continue

        if plot_title == 'Overall.':
          # then, it goes to TestMetric

          test_metric = test.getTestMetrics_for_test.filter(metric__metric_type__title=metric_title)

          if test_metric:
            test_metric = test_metric[0]
            metric = test_metric.metric
            metric.url = url
            metric.save()
          else:
            m = Metric(url=url,metric_type=mt[0])
            m.save()
            tm = TestMetric(metric=m,test=test)
            tm.save()
        else:
          # then, it goes to SiteMetric
          site = Site.objects.filter(name=plot_title)
          if site:

            site_metric = test.getSiteMetrics_for_test.filter(site=site[0]).filter(metric__metric_type__title=metric_title)

            if site_metric:
              site_metric = site_metric[0]
              metric = site_metric.metric
              metric.url = url
              metric.save()
            else:
              m = Metric(url=url,metric_type=mt[0])
              m.save()
              sm = SiteMetric(metric=m,test=test,site=site[0])
              sm.save()
          else:
#            logger.info("Wow, I don't know this site: %s"%(plot_title))
              print "Wow, I don't know this site: %s"%(plot_title)      

    else:
#      logger.info('No metric type recognised with this name: %s'%(metric_title))
        print 'No metric type recognised with this name: %s'%(metric_title)

  print 'Plot for %s took %s'%(test.id,datetime.now()-now)


def evolution(app,test):

  now = datetime.now()

  summary_evolution = test.getSummaryEvolutions_for_test
  sites             = sorted([ ts.site for ts in test.getTestSites_for_test.all()])

  evols  = [ summary_evolution.filter(site=site).order_by('time') for site in sites]
  labels = []

  size = len(evols[0])
  total_sub = []
  total_run = []
  total_com = []
  total_fai = []

  MetricType = custom_import('hc.%s.models.MetricType'%(app))
  Metric     = custom_import('hc.%s.models.Metric'%(app))
  TestMetric = custom_import('hc.%s.models.TestMetric'%(app))
  SiteMetric = custom_import('hc.%s.models.SiteMetric'%(app))

  for site_evols in evols:

    if site_evols:

      counter  = 0
      new_evol = []

      step = int(len(site_evols)/50) + 1
      for site_evol in site_evols:
        counter += 1
        if counter == step:
          counter  = 0
          new_evol += [site_evol]

      submitted = [ e.submitted for e in new_evol]
      running   = [ e.running   for e in new_evol]
      completed = [ e.completed for e in new_evol]
      failed    = [ e.failed    for e in new_evol]

      #Four labels
      label_step = int(size/4)

      labels = [site_evols[0].time.isoformat(),site_evols[size-1].time.isoformat()]

      sr = line([submitted,running],labels,('submitted','running'),'Submitted / Running %s'%(site_evols[0].site.name),['e7a900','0094ee'])
      cf = line([completed,failed] ,labels,('completed','failed') ,'Completed / Failed %s'%(site_evols[0].site.name),['15ca00','e81c01'])

      site_metric = site_evols[0].site.getSiteMetrics_for_site.filter(test=test).filter(metric__metric_type__name='evol_sr')
      if site_metric:
        site_metric = site_metric[0]
        metric = site_metric.metric
        metric.url = sr 
        metric.save()
      else:
        mt = MetricType.objects.filter(name='evol_sr')[0]
        m = Metric(url=sr,metric_type=mt)
        m.save()
        sm = SiteMetric(metric=m,test=test,site=site_evols[0].site)
        sm.save()

#      mt = MetricType.objects.filter(name='evol_sr')[0]
#      m = Metric(url=sr,metric_type=mt)
#      m.save()      
#      sm = SiteMetric(metric=m,test=test,site=site_evols[0].site)
#      sm.save()

      site_metric = site_evols[0].site.getSiteMetrics_for_site.filter(test=test).filter(metric__metric_type__name='evol_cf')
      if site_metric:
        site_metric = site_metric[0]
        metric = site_metric.metric
        metric.url = cf
        metric.save()
      else:
        mt = MetricType.objects.filter(name='evol_cf')[0]
        m = Metric(url=cf,metric_type=mt)
        m.save()
        sm = SiteMetric(metric=m,test=test,site=site_evols[0].site)
        sm.save()

#      mt = MetricType.objects.filter(name='evol_cf')[0]
#      m = Metric(url=cf,metric_type=mt)
#      m.save()
#      sm = SiteMetric(metric=m,test=test,site=site_evols[0].site)
#      sm.save()

      if total_sub:
        total_sub = [sum(pair) for pair in zip(total_sub, submitted)]
      else:
        total_sub = submitted
      if total_run:
        total_run = [sum(pair) for pair in zip(total_run, running)]
      else:
        total_run = running
      if total_com:
        total_com = [sum(pair) for pair in zip(total_com, completed)]
      else:
        total_com = completed
      if total_fai:
        total_fai = [sum(pair) for pair in zip(total_fai, failed)]
      else:
        total_fai = failed

  if labels:
    sr = line([total_sub,total_run],labels,('submitted','running'),'Submitted / Running Overall',['e7a900','0094ee'])

    test_metric = test.getTestMetrics_for_test.filter(metric__metric_type__name='evol_sr')
    if test_metric:
      test_metric = test_metric[0]
      metric = test_metric.metric
      metric.url = sr
      metric.save()    
    else:
      mt = MetricType.objects.filter(name='evol_sr')[0]
      m = Metric(url=sr,metric_type=mt)
      m.save()
      tm = TestMetric(metric=m,test=test)
      tm.save()

    cf = line([total_com,total_fai] ,labels,('completed','failed') ,'Completed / Failed Overall',['15ca00','e81c01'])
    test_metric = test.getTestMetrics_for_test.filter(metric__metric_type__name='evol_cf')
    if test_metric:
      test_metric = test_metric[0]
      metric = test_metric.metric
      metric.url = cf 
      metric.save()
    else:
      mt = MetricType.objects.filter(name='evol_cf')[0]
      m = Metric(url=cf,metric_type=mt)
      m.save()
      tm = TestMetric(metric=m,test=test)
      tm.save()

#    mt = MetricType.objects.filter(name='evol_cf')[0]
#    m = Metric(url=cf,metric_type=mt)
#    m.save()
#    tm = TestMetric(metric=m,test=test)
#    tm.save()

#    return charts

  print 'Evolution for %s took %s'%(test.id,datetime.now()-now)


