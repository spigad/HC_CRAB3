from hc.core.utils.generic.class_func import custom_import
from django.db.models import Min

import commands,time,os

class CreateAtJob:

  def getHCAPP(self,app):
    HCAPP = os.getenv('HCAPP')
    if not HCAPP:
      print '[ERROR][%s][create_at_job] Env variable HCAPP not defined.'%(app)
      return 0
    else:
      return HCAPP

  def getHCDIR(self,app):
    HCDIR = os.getenv('HCDIR')
    if not HCDIR:
      print '[ERROR][%s][create_at_job] Env variable HCDIR not defined.'%(app)
      return 0
    else:
      return HCDIR

  def createScript(self,app,test):

    HCAPP = self.getHCAPP(app)
    HCDIR = self.getHCDIR(app)
    if not HCAPP or not HCDIR:
      return 0

    gangabin = HCDIR+'/external/ganga'+test.gangabin.path

    try:
      f=open('%s/testdirs/run-test-%d.sh'%(HCAPP,test.id),'w')
      f.write('cd %s\n'%(HCAPP))
      f.write('mkdir -p testdirs/test_%d\n'%(test.id))
      f.write('if [ -e "testdirs/test_%d/stdouterr.txt" ]\nthen\n  mv testdirs/test_%d/stdouterr.txt testdirs/test_%d/stdouterr.txt.`date +%%s`\nfi\n'%(test.id,test.id,test.id))
      f.write('cd %s\n'%(HCDIR))
      f.write('./scripts/submit/test-run.sh %s %s %d %s &> %s/testdirs/test_%d/stdouterr.txt\n'%(app,gangabin,test.id,test.testoption.config,HCAPP,test.id))
      f.close()
    except:
      print '[ERROR][%s][create_at_job] Error writting run-test-%d.sh.'%(app,test.id)
      return 0

    return 1

  def scheduleJob(self,app,test,host):

    HCAPP = self.getHCAPP(app)
    if not HCAPP:
      return 0

    time=test.starttime.strftime('%H:%M %m%d%y')
#    atjobid = commands.getoutput('at -f %s/testdirs/run-test-%d.sh %s'%(HCAPP,test.id,time)).rstrip()
    test.state   = 'scheduled'
#    test.atjobid = int(atjobid.split()[1])
    test.host    = host
    test.save() 

#    print '[INFO][%s][create_at_job] Starting test %s: %s\n'%(app,test.id,atjobid)
    return 1

  def run(self,app,dic):

    if app == 'core':
      print '[ERROR][%s][create_at_job] not available at core app.'%(app)
      return 0

    # IMPORTS
    test = custom_import('hc.%s.models.Test'%(app))
    
    hostname = commands.getoutput('hostname')

    tests = test.objects.filter(state='tobescheduled')
    if not tests:
      print '[INFO][%s][create_at_job] No tests found on state: tobescheduled'%(app)      

    for test in tests:
      test_hosts = test.getTestHosts_for_test.all().filter(host__active=1).order_by('host__loadavg1m')

      if not test_hosts:
        print '[ERROR][%s][create_at_job] Test %s without active test_hosts.'%(app,test.id)

      else:
        if test_hosts[0].host.name == hostname:
          print '[INFO][%s][create_at_job] Test %s assigned to %s'%(app,test.id,hostname)
        
          if self.createScript(app,test):
           if self.scheduleJob(app,test,test_hosts[0].host):
             time.sleep(10)  

        else:
          print '[INFO][%s][create_at_job] Test %s NOT assigned to %s.'%(app,test.id,hostname) 
          print '[INFO][create_at_job][%s] Registered loads.'%(app)
          for thl in test_hosts:
            print '%s: %3f'%(thl.host.name,thl.host.loadavg1m)	        

    return 1
