from hc.core.utils.generic.class_func import custom_import

import os,commands,re

class TestAlarm:

  def check(self,app,dic):
    if app == 'core':
      print '[ERROR][%s][test_alarm] not available at core app.'%(app)
      return 0

    hostname = commands.getoutput('hostname')
 
    print '[INFO][%s][test_alarm] Running alarms for host %s.'%(app,hostname)

    #IMPORT
    test = custom_import('hc.%s.models.Test'%(app))

    hostname='vocms57.cern.ch'  
    tests = test.objects.filter(host__name=hostname).filter(state='running')   
    return tests

  def log(self,result,log,matches):
    for status,l in log:
      print '    %s %s'%(status,l)
    return 1

  def extendedLog(self,result,log,matches):
    for status,l in log:
      print '    %s %s'%(status,l)
      for k,v in matches.items():
        if k in l:
          l = l.replace(k,v)
      print '    %s'%(l)
    return 1

  def email(self,result,log,matches):
    pass
 
  def sendSMS(self,result,log,matches):
    pass
  
  def run(self,app,dic):
    
    tests = self.check(app,dic)   
    #IMPORT
    alarms = custom_import('%s.python.lib.alarms.app_alarms.AppAlarms'%(app))()
    
    if tests:
      print ''
      for test in tests:
        print '-- Test %s'%(test.id)

        ## GET TEST SITES 
        tss = test.getTestSites_for_test.all()
        if not tss:
          print '  No sites defined for this test.'
          continue
 
        ## GET TEST SITE ALARMS
        tas = test.getTestSiteAlarms_for_test.all().order_by('site')              
        if not tas:
          print '  No alarms defined for this test.'  
          continue
        else:
          #Push to logs (but only once)
          if not test.getTestLogs_for_test.filter(comment__icontains='Active alarms'):
            test_log = custom_import('hc.%s.models.TestLog'%(app))  
            comment = 'Active alarms: '
            for ta in tas:
              comment += '%s '%(ta.alarm.name) 
            testlog = test_log(test=test,comment=comment,user='gangarbt',serverity='maintenance')
            testlog.save()

        raw  = {}
        proc = {}

        ## GET RAW DATA FROM RESULTS OF TEST.METRICPERM.CRON_ALLOWED METRICS
        metricnames = [m.name for m in test.metricperm.cron_allowed.all() if m.name != 'c_cf']
        metrics = metricnames

        for m in metrics:
          raw[m] = {}
          for ts in tss:
            raw[m][ts.site.name] = []

        if not 'site__name' in metrics:
          metrics += ['site__name']

        values = test.getResults_for_test.values(*metrics)

        for value in values:
          site = value['site__name']
          for k,v in value.items():
            if v != None and v != 'NULL' and not 'site__name' in k:
              raw[k][site] += [v]

        actions = {}

        for ts in tss:
          print '  %s:'%(ts.site.name)
          
          for ta in tas:
            if ta.site == ts.site:
              if not ta.active:
                print '*   %s alarm NOT active.'%(ta.alarm.name)
                continue
              else:
                print '*   %s alarm.'%(ta.alarm.name)

              alarm = getattr(alarms,ta.alarm.name)
              result,logs,matches = alarm.run(raw,proc,site)              
     
              progress = float(result[False])/float(result[False]+result[True])

              if result['ERROR']:
                print '    %s errors.'%(result['ERROR'])
                ta.state = 'empty'
              elif not result[True]:
                print '    Ok'
                ta.status = 'passed'
              else:
                print '    %s failures.'%(result[True])
                print '    %s completed.'%(result[False])             
                ta.status = 'failed'

                test_log = custom_import('hc.%s.models.TestLog'%(app))
                comment = 'Alarm %s - %s reported on site %s: %s failures (and %s completed) See alarms for details.'%(ta.alarm.name,ta.alarm.description,ta.site.name,result[True],result[False])
                testlog = test_log(test=test,comment=comment,user='gangarbt',severity='error')
                testlog.save()

              ta.progress = progress
              ta.log = logs
              ta.save()

              dont_be_evil = re.compile(r'^[A-Za-z]*$')

              for action in ta.actions.split(';'):
                if action:
                  if action in TestAlarm.__dict__.keys() and not action.startswith('__') and action not in ['check','run'] and re.findall(dont_be_evil,action):
                    getattr(self,action)(result,logs,matches)
                  else:
                    print 'Unknown/evil action %s'%(action)

    else:
      print "[INFO][%s][test_alarm] No running tests."%(app)
      return 1

