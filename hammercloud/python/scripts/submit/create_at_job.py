from hc.core.utils.generic.class_func import custom_import
from django.db.models import Min

import commands,time,os,os.path

me = 'hammercloud-noreply@cern.ch'
#you = 'daniel.colin.vanderster@cern.ch,0041764870482@sms.switch.ch'                                                                                                                  
you = 'daniel.colin.vanderster@cern.ch,ramon.medrano.llamas@cern.ch'

class CreateAtJob:

  def send_alert(self, msg):
    sendmail_location = "/usr/sbin/sendmail" # sendmail location                                                                                                                      
    p = os.popen("%s -t" % sendmail_location, "w")
    p.write("From: %s\n" % me)
    p.write("To: %s\n" % you)
    p.write("Subject: HammerCloud Test Restarted\n")
    p.write("\n") # blank line separating headers from body                                                                                                                           
    p.write(msg)
    status = p.close()

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
  
  def logFileUpdated(self,app,test):
    HCAPP = self.getHCAPP(app)
    HCDIR = self.getHCDIR(app)
    if not HCAPP or not HCDIR:
      return 0

    try:
      mtime = os.stat('%s/testdirs/test_%d/stdouterr.txt'%(HCAPP,test.id)).st_mtime
    except OSError:
      print '[ERROR][%s][create_at_job] stdouterr.txt for test %d doesn\'t exist!'%(app,test.id)
      return False
    age = int(time.time())-mtime
    if age > 60:
      print '[ERROR][%s][create_at_job] stdouterr.txt for test %d not updated for %d s'%(app,test.id,age)
      return False
    return True

  def gangaProcessRunning(self,app,test):
    cmd = 'ps -ef | grep bin/ganga | grep -v grep | grep %d'%test.id
    if os.system(cmd):
      print '[ERROR][%s][create_at_job] ganga process does not appear to be running for test %d'%(app,test.id)
      return False
    return True

  def testScriptRunning(self,app,test):
    # check if process is running                                                                                                                                                     
    cmd = 'ps -ef | grep "./hc-test-run.sh %d" | grep -v grep'%test.id
    if os.system(cmd):
      print '[ERROR][%s][create_at_job] test script does not appear to be running for test %d'%(app,test.id)
      return False
    return True

  def testPaused(self,app,test):
    HCAPP = self.getHCAPP(app)
    HCDIR = self.getHCDIR(app)
    if not HCAPP or not HCDIR:
      return 0
    txt = 'Test %d is paused'%test.id
    cmd = 'grep "%s" %s/testdirs/test_%d/stdouterr.txt'%(txt,HCAPP,test.id)
    if os.system(cmd):
        print '[ERROR][%s][create_at_job] test %d is not paused'%(app,test.id)
        return False
    return True

  def checkFault(self,app,test):
    HCAPP = self.getHCAPP(app)
    HCDIR = self.getHCDIR(app)
    if not HCAPP or not HCDIR:
      return 0
    # check logfile for JobAccessError or segmentation fault                                                                                                                          
    txt = ['JobAccessError','Segmentation fault']
    for t in txt:
      cmd = 'grep "%s" %s/testdirs/test_%d/stdouterr.txt'%(t,HCAPP,test.id)
      if not os.system(cmd):
        print '[ERROR][%s][create_at_job] %s found in stdouterr.txt for test %d'%(app,t,test.id)
        return True
    return False

  def stateFileExists(self,app,test):
    # check for state file in /tmp                                                                                                                                                    
    try:
      mtime = os.stat('/tmp/hc-cron.running.%d'%test.id).st_mtime
      os.remove('/tmp/hc-cron.running.%d'%test.id)
    except OSError:
      print '[ERROR][%s][create_at_job] hc-cron.running.%d doesn\'t exist'%(app,test.id)
      return False
    return True


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
    test.state   = 'scheduled'
    test.host    = host
    test.save(commit=True)
    atjobid = commands.getoutput('at -f %s/testdirs/run-test-%d.sh %s'%(HCAPP,test.id,time)).rstrip()
    test.atjobid = int(atjobid.split()[1])
    test.save()

    print '[INFO][%s][create_at_job] Starting test %s: %s\n'%(app,test.id,atjobid)
    return 1

  def rescheduleJob(self,app,test):
    HCAPP = self.getHCAPP(app)
    if not HCAPP:
      return 0

    atjobid = commands.getoutput('at -f %s/testdirs/run-test-%d.sh now'%(HCAPP,test.id)).rstrip()
    test.atjobid = int(atjobid.split()[1])
    test.save()
    print '[INFO][%s][create_at_job] restarting test %d: %s\n'%(app,test.id,atjobid)
    return atjobid


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

    for t in tests:
      test_hosts = sorted(t.getTestHosts_for_test.all().filter(host__active=1),
                          key=lambda x: x.host.loadavg1m + test.objects.filter(starttime__gte=(datetime.now() - timedelta(seconds=300))).filter(host=x.host).count()*3.0)

      if not test_hosts:
        print '[ERROR][%s][create_at_job] Test %s without active test_hosts.'%(app,t.id)

      else:
        if test_hosts[0].host.name == hostname:
          print '[INFO][%s][create_at_job] Test %s assigned to %s'%(app,t.id,hostname)
        
          if self.createScript(app,t):
           if self.scheduleJob(app,t,test_hosts[0].host):
             time.sleep(10)  

        else:
          print '[INFO][%s][create_at_job] Test %s NOT assigned to %s.'%(app,t.id,hostname) 
          print '[INFO][create_at_job][%s] Registered loads.'%(app)
          for thl in test_hosts:
            print '%s: %3f'%(thl.host.name,thl.host.loadavg1m)
    
    #test = custom_import('hc.%s.models.Test'%(app))
    tests = test.objects.filter(state='running').filter(host__name=hostname)
    if not tests:
      print '[INFO][%s][create_at_job] No tests found on state: running'%(app)
    
    for test in tests:
      if self.logFileUpdated(app, test):
        continue

      if self.gangaProcessRunning(app, test):
        continue

      if self.testScriptRunning(app, test):
        continue

      if self.testPaused(app, test):
        continue

      self.checkFault(app, test)
      
      if self.stateFileExists(app, test):
        print '[INFO][%s][create_at_job] Test %d on %s had lockfile removed.'%(app,test.id,hostname) 
        self.send_alert('%s\nTest %d on %s had lockfile removed.'%(time.ctime(),test.id,hostname))
        
      res = self.rescheduleJob(app, test)
      print '[INFO][%s][create_at_job] Test %d on %s has been restarted: %s.'%(app,test.id,hostname,res) 
      self.send_alert('%s\nTest %d on %s has been restarted: %s.'%(time.ctime(),test.id,hostname,res))

    return 1
