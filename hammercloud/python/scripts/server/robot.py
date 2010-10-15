from hc.core.utils.generic.class_func import custom_import

from datetime import date,datetime,timedelta

class Robot:

  def run(self,app,dic):

    if app == 'core':
      print '[ERROR][%s][create_functional_tests] not available at core app.'%(app)
      return 1

    # IMPORTS
    result = custom_import('hc.%s.models.Result'%(app))
    site   = custom_import('hc.%s.models.Site'%(app))
    srobot = custom_import('hc.%s.models.SummaryRobot'%(app))

    today     = date.today()
    yesterday = today-timedelta(1)

    results = result.objects.filter(mtime__gt=yesterday).filter(mtime__lt=today)

    if not results:
      print '[INFO][%s] No suitable results.'%(app)

    print 'ROBOT FOR %s'%(yesterday)

    sites = site.objects.all()
 
    for site in sites:
      completed = results.filter(site=site).filter(ganga_status='c').count()
      failed    = results.filter(site=site).filter(ganga_status='f').count()
      total     = results.filter(site=site).count()

      cf = float(completed + failed)

      efficiency     = -1
      efficiencyNorm = -1
      errorrate      = -1
      errorrateNorm  = -1

      if (cf > 0.):
        efficiency     = float(completed)/cf
        efficiencyNorm = float(efficiency)*float(completed)
        errorrate      = float(failed)/cf
        errorrateNorm  = float(errorrate)*float(failed)      

      print '%s - %s'%(site.name,efficiency)

      sr = srobot(site=site,completed=completed,failed=failed,total=total,efficiency=efficiency,efficiencyNorm=efficiencyNorm,errorrate=errorrate,errorrateNorm=errorrateNorm,day=yesterday)
      sr.save()      

    return 1
