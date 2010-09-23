from hc.core.utils.generic.class_func import custom_import
from datetime import datetime

class TestGenerate():

  def check(self,dic)
    app = dic['-a']
    if app == 'core':
      print '[ERROR][%s][test_generate] not available at core app.'%(app)
      return 0

    if not dic.has_key('-t'):
      print '[ERROR][%s][test_generate] Test ID missing.'%(app)
      return 0

    try:
      testid = int(dic[-t])
    except ValueError:
      print '[ERROR][%s][test_generate] <int>TestID expected, got %s'%(app,dic['-t'])
      return 0

    #IMPORT
    test = custom_import('hc.%s.models.Test'%(app))

    try:
      test = test.objects.get(pk=testid)
    except:
      print '[ERROR][%s][test_generate] Could not get test with id %s from DB.'%(app,testid)
      return 0

    if not test.starttime <= datetime.now():
      print '[ERROR][%s][test_generate] Test %s starttime value is on the future.'%(app,testid)
      return 0

    if not test.state = 'scheduled':
      print '[ERROR][%s][test_generate] Test %s is on state: %s instead of scheduled.'%(app,test.state)
      return 0

    print '[INFO][%s][test_generate] Generating jobs for Test %s.'%(app,testid)

    return test
   

  def run(self,dic):
    
    test = self.check(dic):
    if test:

      tg = custom_import('%s.python.submit.test_generate.TestGenerate'%(dic['-a']))
      if tg:
        if tg.run():
          # if everything is Ok, state=submitting
      else:
        #Game over !
        print '[ERROR][%s][test_generate] Could not import %s.python.submit.test_generate.TestGenerate'%(dic['-a'],dic['-a'])
        return 0
    else:
      #Game over !
      return 0
