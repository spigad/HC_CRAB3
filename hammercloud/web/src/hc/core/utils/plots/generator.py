from hc.core.utils.generic.class_func import custom_import
from hc.core.utils.plots.charts import pie,hist

class Generator():

  COLORS = dict({'c':'5EFB6E', 'f':'FF0000', 'r':'79BAEC', 's':'FFF380', 'n':'F75D59', 'o':'38ACEC'})
  app = ''

  def __init__(self,app):
    self.app = app

  def genTestPlots(self,test_id):

    test        = custom_import('hc.%s.models.Test'%(self.app))
    metric      = custom_import('hc.%s.models.Metric'%(self.app))   
    test_metric = custom_import('hc.%s.models.TestMetric'%(self.app))

    try:
      test = test.objects.get(pk=test_id)
    except:
      return 0

    testsites = test.getTestSites_for_test.all()
    
    metric_types = test.metrics.cron_allowed.all()
    for metric_type in metric_types:
      url = genOverallPlot(self,test,metric_type)
      overall_metric = metric(url=url,metric_type=metric_type)      
      overall_metric.save()
      t_m = test_metric(test=test,metric=overall_metric)
      t_m.save()

      for testsite in testsites:
        url = genSitePlot(self,testsite,metric_type)
        site_metric = metric(url=url,metric_type=metric_type)
        site_metric.save()
        t_m = test_metric(test=test,metric=site_metric)
        t_m.save()

  def genOverallPlot(self,test,metric_type):

    if metric_type.type == 'Pie':
      return genOverallPiePlot(self,test,metric_type)
    else:
      return genOverallHistPlot(self,test,metric_type)

  def genSitePlot(self,testsite,metric_type):

    if metric_type.type == 'Pie':
      return genSitePiePlot(self,testsite,metric_type)
    else:
      return genSiteHistPlot(self,testsite,metric_type)

###########
# OVERALL
###########

  def genOverallPiePlot(self,test,metric_type):

    state = test.state
    status_count = test.getResults_for_test.values(metric_type.name).annotate(Count(metric_type.name))
    
    labels,values,colors = [],[],[]
    
    for sc in status_count:

      status = sc[metric_type.name]
      count  = sc[str(metric_type.name)+'_count']

      if metric_type.name == 'ganga_status':
        if (state == 'completed' and status in ['c','f']) or (state != 'completed'):
          color = 'o'
          if (status in self.COLORS):
            color = status
          colors.append(self.COLORS[color]) 
          labels.append("%s (%s)"%(status,count))
          values.append(count)
     # else:
     # Dictionary to convert colours           

    return pie(values,labels,metric_type.title,colors)

  def genOverallHistPlot(self,test,metric_type):

    values = test.getResults_for_test.filter(ganga_status='c').values(metric_type.name)
    rate = [ dic[metric_type.name] for dic in values ]
    return hist(rate, 20, metric_type.name ,metric_type.title)#, (0,50))

###########
# PIE
###########

  def genSitePiePlot(self,testsite,metric_type):

    test = testsite.test
    site = testsite.site

    state = test.state
    status_count = test.getResults_for_test.filter(site=site).values(metric_type.name).annotate(Count(metric_type.name))

    labels,values,colors = [],[],[]

    for sc in status_count:

      status = sc[metric_type.name]
      count  = sc[str(metric_type.name)+'_count']

      if metric_type.name == 'ganga_status':
        if (state == 'completed' and status in ['c','f']) or (state != 'completed'):
          color = 'o'
          if (status in self.COLORS):
            color = status
          colors.append(self.COLORS[color])
          labels.append("%s (%s)"%(status,count))
          values.append(count)
     # else:
     # Dictionary to convert colours

    return pie(values,labels,metric_type.title,colors)

  def genSiteHistPlot(self,testsite,metric_type):

    test = testsite.test
    site = testsite.site
 
    values = test.getResults_for_test.filter(site=site).filter(ganga_status='c').values(metric_type.name)
    rate = [ dic[metric_type.name] for dic in values ]
    return hist(rate, 20, metric_type.name ,metric_type.title)#, (0,50))

