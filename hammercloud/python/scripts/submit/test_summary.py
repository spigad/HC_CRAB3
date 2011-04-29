from hc.core.utils.generic.class_func import custom_import
from lib.summary import summary

import os,commands

class TestSummary:

  def check(self,app,dic):
    if app == 'core':
      print '[ERROR][%s][test_summary] not available at core app.'%(app)
      return 0
 
    #If there is no -t, we run agains all tests in the host machine. 

    force,plot,summarize,evolution     = 0,0,0,0

    if not dic.has_key('-o'):
      print '[WARNING][%s][test_summary] Taking values by default, plot=1, summarize=1, evolution=1, force=0'
      plot      = 1
      summarize = 1
      evolution = 1
    else:
      if 'f' in dic['-o']:
        force     = 1
      if 'p' in dic['-o']:
        plot      = 1
      if 's' in dic['-o']:
        summarize = 1
      if 'e' in dic['-o']:
        evolution = 1

    test = []

    if dic.has_key('-t'):
      try:
        testid = int(dic['-t'])
      except ValueError:
        print '[ERROR][%s][test_summary] <int>TestID expected, got %s'%(app,dic['-t'])
        return 0
      #IMPORT
      Test = custom_import('hc.%s.models.Test'%(app))

      try:
        test = Test.objects.get(pk=testid)
      except:
        print '[ERROR][%s][test_summary] Could not get test with id %s from DB.'%(app,testid)
        return 0

      if not test.state == 'running' and not force:
        print '[ERROR][%s][test_summary] Test %s is on state %s, instead of running and force is %s.'%(app,test.id,test.state,force)
        return 0

    if not plot and not summarize and not evolution:
      print '[ERROR][%s][test_summary] Plot,summarize and evolution are set to 0.'(app)
   
    print '[INFO][%s][test_summary] Plot:%s, Summarize:%s and Evolution:%s.'%(app,plot,summarize,evolution)

    print test

    return (test,plot,summarize,evolution,force)
    
  def run(self,app,dic):
    
    try:
      tests,pl,su,ev,fo = self.check(app,dic)
    except:
      return 0

    if not tests:
      hostname = commands.getoutput('hostname')
      #IMPORT
      test = custom_import('hc.%s.models.Test'%(app))
      tests = test.objects.filter(host__name=hostname).filter(state__in=['submitting','running'])
    else:
      tests = [tests]

    for t in tests:
      if pl:
        try:

          #For every test, if endtime < now: fo == 1

          if fo:
            summary.plot(app,t,completed=True)
          else:
            summary.plot(app,t)
        except:
          print '[ERROR][%s][test_summary][plot] Test %s.'%(app,t.id)
      if su:
        try:
          summary.summarize(app,t)
        except:
          print '[ERROR][%s][test_summary][summarize] Test %s.'%(app,t.id)
      if ev:
        try:
          summary.evolution(app,t)
        except:
          print '[ERROR][%s][test_summary][evolution] Test %s.'%(app,t.id)

    print '[INFO][%s][test_summary] Ended.'%(app)
