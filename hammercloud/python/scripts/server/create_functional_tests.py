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

    templates = template.objects.filter(category='FUNCTIONAL').filter(active=1)

    if not templates:
      print '[INFO][%s] No suitable templates.'%(app)

    token = 0
 
    for template in templates:
      tests = template.getTests_for_template.filter(state__in=['running','tobescheduled','submitting','scheduled','draft'])
      if not tests:
        print '[INFO][%s][create_functional_tests] Inserting new test for template %s - %s'%(app,template.id,template.description)
        token = 1
        rnd_life = float(template.lifetime) * (1.0 + random() * 0.2 - 0.1)
        new_test = test(starttime=datetime.now(),endtime=datetime.now()+timedelta(days=rnd_life),template=template,state='tobescheduled')
        new_test.output_dataset = 'GR%s'%(template.id)
        new_test.save()

    if not token:
      print '[INFO][%s][create_functional_tests] No new tests inserted'%(app)

    return 1
