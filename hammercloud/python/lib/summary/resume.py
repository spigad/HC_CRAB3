from hc.core.utils.generic.class_func import custom_import

from datetime import datetime,timedelta
from django.db.models import Min,Avg

import numpy

def resume(app,compress):
#  print app
#  print compress

  type = ['daily','weekly','monthly','yearly']
  if not compress in type:
    print '[resume] Type not known %s.'%(compress)
    return 0
  
  try:
    sev    = custom_import('hc.%s.models.SummaryEvolution'%(app))
    test   = custom_import('hc.%s.models.Test'%(app))
    site   = custom_import('hc.%s.models.Site'%(app))
    result = custom_import('hc.%s.models.Result'%(app))
  except:
    print '[resume] Error importing models.'  
    return 0

  #Algorithm
  #Get all tests that finished yesterday
  #Get the oldest starttime of the test selected
  #Get all SummaryEvolution values beween oldest_starttime and yesterday
  #For every day in the selection, check if there are tests running with starttime
  #older than day_end
  #If yes, continue 
  #If not, resume

  y = datetime.today() - timedelta(days=1)
  y = y.replace(microsecond=999999).replace(second=59).replace(minute=59).replace(hour=23)

  yy = y - timedelta(days=1)

#  st = test.objects.filter(endtime__gt=yy).filter(endtime__lt=y).aggregate(Min('starttime'))['starttime__min']
  st = test.objects.filter(endtime__lt=y).aggregate(Min('starttime'))['starttime__min']
  st = st.replace(microsecond=0).replace(second=0).replace(minute=0).replace(hour=0)

  et = st + timedelta(days=1)

  days = y -st
  days = days.days

  for d in xrange(0,days):
    
    stt = st+timedelta(days=d)
    ett = et+timedelta(days=d)

    print stt
    print ett

    if test.objects.filter(starttime__lt=stt).filter(state__in=['submitting','running']):  
      print 'Found running tests'
      break
    else:
      print 'Compressing'
      sites = site.objects.all()
      for s in sites:
        sevs = sev.objects.filter(time__gt=stt).filter(time__lt=ett).filter(site=s)
        ress = result.objects.filter(mtime__gt=stt).filter(mtime__lt=ett).filter(site=s)

        vals = sevs.aggregate(running=Avg('running'),submitted=Avg('submitted'),total=Avg('total'))
        comp = ress.filter(ganga_status='c').count()
        fail = ress.filter(ganga_status='f').count()
        vals['completed'] = comp
        vals['failed']    = fail 

        if len(sevs) == 1:

          #Already compressed or only one value.
          #Anycase, force time to desired one (noon).
          vals = len(sevs)

          sevs[0].time = st
#          sevs[0].save()

        else:
#          vals = 0
          se = sev(site=s,test=test,time=st)         
          for k in vals.keys():
            attr = 0
            if vals[k]:
              attr = vals[k]  
            setattr(se,k,attr)

#          se.total = 0
#          if vals['total]:
#            se.total = vals['total']
#          se.completed = 0
#          if vals['completed']:
#            se.completed = comp              
#          se.failed = 0
#          if fail:
#            se.failed = fail
#          se.submitted = 0
#          se.running = 0

#          se.save()

        print '%s %s'%(s.name,vals)

  return 1
