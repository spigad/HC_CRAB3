from hc.core.utils.generic.class_func import custom_import

from datetime import date,datetime,timedelta

class Robot:

  def run(self,app,dic):

    if app == 'core':
      print '[ERROR][%s][robot] not available at core app.'%(app)
      return 1

    # Look for the app robot script and run it.
    try:
      app_script = custom_import('%s.python.scripts.server.robot.Robot' % (app))
    except ImportError:
      app_script = None

    if app_script:
      try:
        app_script().run()
        return 1
      except:
        print '[ERROR][%s][blacklist] app robot script failed.' % (app)
        return 0
    
    # If there is no app script, run a general one.

    # IMPORTS
    result = custom_import('hc.%s.models.Result'%(app))
    site   = custom_import('hc.%s.models.Site'%(app))
    srobot = custom_import('hc.%s.models.SummaryRobot'%(app))

    today     = date.today()

    yesterday = today-timedelta(1)

    results = result.objects.filter(mtime__gt=yesterday).filter(mtime__lt=today).filter(test__template__category='functional')

    if not results:
      print '[INFO][%s][robot] No suitable results.'%(app)

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
      else:
        submitted    = results.filter(site=site).filter(ganga_status='s').count()
        running      = results.filter(site=site).filter(ganga_status='r').count()
        # If jobs were submitted, but no one completed of failed, we add to blue category.
        if (submitted+running):
          efficiency     = -2
          efficiencyNorm = -2
          errorrate      = -2
          errorrateNorm  = -2

      print '%s - %s'%(site.name,efficiency)

      sr = srobot(site=site,completed=completed,failed=failed,total=total,efficiency=efficiency,efficiencyNorm=efficiencyNorm,errorrate=errorrate,errorrateNorm=errorrateNorm,day=yesterday)
      sr.save()      

    return 1
