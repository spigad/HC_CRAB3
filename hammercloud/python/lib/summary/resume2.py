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

  st = test.objects.filter(endtime__gt=yy).filter(endtime__lt=y).aggregate(Min('starttime'))['starttime__min']
  #Runs over all tests, not only the algo selected tests.
  #st = test.objects.aggregate(Min('starttime'))['starttime__min']
  st = st.replace(microsecond=0).replace(second=0).replace(minute=0).replace(hour=0)

  et = st + timedelta(days=1)

  #from 04-12-2010 12:00 to 05-12-2010 23:59 there are more than one day.
  #we take it as 2 days
#  days = y.day - st.day + 1 
#  print days
  days = y -st
  days = days.days
#  print days + 1

#  return 0

  for d in xrange(0,days):
    
    stt = st+timedelta(days=d)
    ett = et+timedelta(days=d)

    print stt
    print ett

    if test.objects.filter(starttime__lt=stt).filter(state__in=['submitting','running']):  
      print 'Found running tests'
      break
    else:
      sevs = sev.objects.filter(time__gte=stt).filter(time__lt=ett)
      ress  = result.objects.filter(mtime__gte=stt).filter(mtime__lt=ett)

      if not sevs and not ress:
        continue

      print 'Compressing'

      sites = site.objects.all()
      for s in sites:

        ressSite   = ress.filter(site=s)
        sevsSite   = sevs.filter(site=s)

        ressSites  = [ rs['test'] for rs in ressSite.values('test').distinct() ]
        sevsSites  = [ ss['test'] for ss in sevsSite.values('test').distinct() ]

        if sevsSite or ressSite:
          print '  %s'%(s)
        else:
          continue
 
        testSites = list(set(ressSites+sevsSites))

        if not testSites:
          continue

        for t in testSites:        

          sevsTest = sevsSite.filter(test__id=t)
          ressTest = ressSite.filter(test__id=t)

          vals = sevsTest.aggregate(running=Avg('running'),submitted=Avg('submitted'),total=Avg('total'))
          comp = ressTest.filter(ganga_status='c').count()
          fail = ressTest.filter(ganga_status='f').count()
          vals['completed'] = comp
          vals['failed']    = fail 

          if len(sevsTest) == 1:
            #Already compressed or only one value.
            #Anycase, force time to desired one (noon).

            sevsTest[0].time = stt.replace(minute=10)
            print '    %s %s --'%(t,s)
            sevsTest[0].save()

          else:

            for sevsT in sevsTest:
              sevsT.delete()
 
            try:
              t = test.objects.get(pk=t)
            except:
              print 'ERROR, test %s not known'%(t)
              continue

            se = sev(site=s,test=t,time=stt.replace(minute=10))         
            for k in vals.keys():
              attr = 0
              if vals[k]:
                attr = vals[k]  
              setattr(se,k,attr)
            se.save()

            print '    %s %s %s'%(t,s.name,vals)

  return 1
