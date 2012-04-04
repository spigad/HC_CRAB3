from hc.core.utils.generic.class_func import custom_import

from datetime import datetime,timedelta
from random import random

class CreateFunctionalTests:

  def run(self,app,dic):

    if app == 'core':
      print '[ERROR][%s][create_functional_tests] not available at core app.'%(app)
      return 1

    # IMPORTS
    template       = custom_import('hc.%s.models.Template'%(app))
    test           = custom_import('hc.%s.models.Test'%(app))
    test_log       = custom_import('hc.%s.models.TestLog'%(app))

    templates = template.objects.filter(category='FUNCTIONAL').filter(active=1)

    if not templates:
      print '[INFO][%s] No suitable templates.'%(app)

    token = 0
 
    for template in templates:
      tests = template.getTests_for_template.filter(state__in=['running','tobescheduled','submitting','scheduled','draft'])
      #TODO: filter out tests that have endtime within 30 minutes for app=atlas
      if not tests:
        print '[INFO][%s][create_functional_tests] Inserting new test for template %s - %s'%(app,template.id,template.description)
        token = 1
        rnd_life = float(template.lifetime) * (1.0 + random() * 0.2 - 0.1)
        new_test = test(starttime=datetime.now(),endtime=datetime.now()+timedelta(days=rnd_life),template=template,state='tobescheduled')
        new_test.output_dataset = 'GR%s'%(template.id)
        # Save the initial test for the cloning of the template.
        new_test.save()
        # Assign the host for the test now, so there are no conflicts.
        # TODO: Refactor this code.
        test_hosts = sorted(new_test.getTestHosts_for_test.all().filter(host__active=1),
                            key=lambda x: x.host.loadavg1m)
        new_test.host = test_hosts[0].host
        # Save the test host and log the change.
        new_test.save()
        test_log(test=new_test, comment='Test %d was assigned to %s.'%(new_test.id,new_test.host), user='gangarbt', severity='testinfo').save()
        print '[INFO][create_functional_tests][%s] Test %d was assigned to %s.'%(app,new_test.id,new_test.host)
        print '[INFO][create_functional_tests][%s] Registered loads.'%(app)
        for thl in test_hosts:
          print '%s: %3f'%(thl.host.name,thl.host.loadavg1m)

    for stress_test in test.objects.filter(host=None).filter(template__category='stress').filter(state='tobescheduled').filter(starttime__lte=(datetime.now() + timedelta(seconds=300))):
      # Assign the host to stress tests that will start in 5 minutes from now.
      test_hosts = sorted(stress_test.getTestHosts_for_test.all().filter(host__active=1),
                          key=lambda x: x.host.loadavg1m)
      stress_test.host = test_hosts[0].host
      # Save the test host and log the change.
      stress_test.save()
      test_log(test=stress_test, comment='Test %d was assigned to %s.'%(stress_test.id,stress_test.host), user='gangarbt', severity='testinfo').save()
      print '[INFO][create_functional_tests][%s] Test %d was assigned to %s.'%(app,stress_test.id,stress_test.host)
      print '[INFO][create_functional_tests][%s] Registered loads.'%(app)
      for thl in test_hosts:
        print '%s: %3f'%(thl.host.name,thl.host.loadavg1m)

    if not token:
      print '[INFO][%s][create_functional_tests] No new tests inserted'%(app)

    return 1
