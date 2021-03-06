from hc.core.utils.generic.class_func import custom_import
from datetime import datetime
import time

class TestGenerate:

  def check(self,app,dic):
    if app == 'core':
      print '[ERROR][%s][test_generate] not available at core app.'%(app)
      return 0

    if not dic.has_key('-t'):
      print '[ERROR][%s][test_generate] Test ID missing.'%(app)
      return 0

    try:
      testid = int(dic['-t'])
    except ValueError:
      print '[ERROR][%s][test_generate] <int>TestID expected, got %s'%(app,dic['-t'])
      return 0

#    try:
#      mode = dic['-m']
#    except:
#      print '[ERROR][%s][test_generate] <string>Mode expected'%(app)
#      return

    #IMPORT
    test = custom_import('hc.%s.models.Test'%(app))

    try:
      test = test.objects.get(pk=testid)
    except:
      print '[ERROR][%s][test_generate] Could not get test with id %s from DB.'%(app,testid)
      return 0

    #if not test.starttime.replace( second = 0 ) < datetime.now():
    #  print '[ERROR][%s][test_generate] Test %s starttime value is on the future.'%(app,testid)
    #  return 0

    if not test.state == 'scheduled':
      print '[ERROR][%s][test_generate] Test %s is on state %s, instead of scheduled.'%(app,test.id,test.state)
      return 0

    print '[INFO][%s][test_generate] Generating jobs for Test %s.'%(app,testid)

    return test
   
  def run(self,app,dic):
    
    test = self.check(app,dic)
    mode = 0

    try:
      mode = dic['-m']
    except:
      print '[ERROR][%s][test_generate] <string>Mode expected'%(app)

    if test and mode:

      tg = custom_import('%s.python.scripts.submit.test_generate.TestGenerate'%(app))
      
      if tg:
        
        try:
          result = tg().run(test,mode)
        except:
          import sys
          print '[INFO][%s][test_generate] Error while generating jobs for test %d. %s %s'%(app,test.id,sys.exc_info()[0],sys.exc_info()[1])
          result = 0
        
        if result:
          test.state = 'submitting'
          test.save()
          print '[INFO][%s][test_generate] Test %s is in submitting state.'%(app,test.id)
          return 1
        else:
          time.sleep(300)
          test.state = 'error'
          test.save()
          print '[ERROR][%s][test_generate] Error running %s.python.scripts.submit.test_generate.TestGenerate'%(app,app)
          return 0
      else:
        #Game over !
        time.sleep(300)                                      
        test.state = 'error'
        test.save()
        print '[ERROR][%s][test_generate] Could not import %s.python.scripts.submit.test_generate.TestGenerate'%(app,app)
        return 0
    else:
      #Game over !
      return 0
