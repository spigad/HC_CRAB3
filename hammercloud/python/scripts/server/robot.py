from hc.core.utils.generic.class_func import custom_import

from datetime import datetime,timedelta

class Robot():

  def run(self,app,dic):

    if app == 'core':
      print '[ERROR][%s][create_functional_tests] not available at core app.'%(app)
      return 1

    # IMPORTS
    result = custom_import('hc.%s.models.Result'%(app))
    site   = custom_import('hc.%s.models.Site'%(app))
    srobot = custom_import('hc.%s.models.SummaryRobot'%(app))

    results = result.objects.filter(mtime__gt=datetime.now()-timedelta(days=1))

    if not results:
      print '[INFO][%s] No suitable results.'%(app)

    sites = site.objects.all()
 
    for site in sites:
      completed = results.filter(site=site).filter(ganga_status='c').count()
      failed    = results.filter(site=site).filter(ganga_status='f').count()

      total = float(completed + failed)
      #efficiency = 0.
      if (total > 0.):
        efficiency = float(completed)/total
      else:
        efficiency = -1      

      print '%s - %s'%(site.name,efficiency)

      sr = site.getSummaryRobots_for_site.all()
      if sr:
        sr = sr[0]
        sr.efficiency = efficiency
      else:
        sr = srobot(site=site,efficiency=efficiency)
      sr.save()      

    return 1
