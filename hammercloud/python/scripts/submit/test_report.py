from hc.core.utils.generic.class_func import custom_import
from datetime import datetime

import os

class TestReport:

  def check(self,app,dic):
    if app == 'core':
      print '[ERROR][%s][test_report] not available at core app.'%(app)
      return 0

    if not dic.has_key('-t'):
      print '[ERROR][%s][test_report] Test ID missing.'%(app)
      return 0

    try:
      testid = int(dic['-t'])
    except ValueError:
      print '[ERROR][%s][test_report] <int>TestID expected, got %s'%(app,dic['-t'])
      return 0

    #IMPORT
    test = custom_import('hc.%s.models.Test'%(app))

    try:
      test = test.objects.get(pk=testid)
    except:
      print '[ERROR][%s][test_report] Could not get test with id %s from DB.'%(app,testid)
      return 0

    if not test.state == 'running':
      print '[ERROR][%s][test_report] Test %s is on state %s, instead of running.'%(app,test.id,test.state)
      return 0

    if not test.endtime >= datetime.now():
      print '[ERROR][%s][test_report] Test %s entime value is on the past.'%(app,testid)
      return 0

    print '[INFO][%s][test_report] Reporting jobs for Test %s.'%(app,testid)

    return test
   
  
  def report(self,test,app,dic):

    # Path of the working directory
    if os.environ.has_key('HCDIR'):
      HCDIR = os.environ['HCDIR']
    else:
      print '[ERROR][%s][test_report] No HCDIR found'%(app)
      return 0

    if os.environ.has_key('HCAPP'):
      HCAPP = os.environ['HCAPP']
    else:
      print '[ERROR][%s][test_report] No HCAPP found'%(app)
      return 0

    # Check if the application has an specific script for this task
    if os.path.exists('%s/scripts/submit/test-report.sh' % HCAPP):
      base = HCAPP
    else:
      print '[INFO][%s][test_report] Specific test_report does not exist.'%(app)
      base = HCDIR

    print '[INFO][%s][test_report] /bin/sh %s/scripts/submit/test-report.sh %d "%s %s"'%(app,base,test.id,test.extraargs,test.testoption.report)
    result =  os.system('/bin/sh %s/scripts/submit/test-report.sh %d "%s %s"'%(base,test.id,test.extraargs,test.testoption.report))

    #0 means good in shell scripting.
    if result == 0:
      return 1
    return 0

  def run(self,app,dic):
    
    test = self.check(app,dic)
    if test:
      self.report(test,app,dic)
    else:
      print 'Game over !'
      return 0
