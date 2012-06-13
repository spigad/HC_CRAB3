from django.db import models

class TestManager(models.Manager):
  '''
  Class that override the default Manager for the Test object in the data models
  '''
  def get_query_set(self):
    '''
    Method that return the default Queryset
    '''
    return super(TestManager, self).get_query_set()

  def scheduled(self):
    '''
    Method that return the Queryset with the Scheduled Test
    '''
    return super(TestManager, self).get_query_set().filter(state='scheduled')
   
  def submitting(self):
    '''
    Method that return the Queryset with the Submitting Test
    '''
    return super(TestManager, self).get_query_set().filter(state='submitting')
   
  def submiterror(self):
    '''
    Method that return the Queryset with the Error Test
    '''
    return super(TestManager, self).get_query_set().filter(state='error')
   
  def running(self):
    '''
    Method that return the Queryset with the Running Test
    '''
    return super(TestManager, self).get_query_set().filter(state='running')
   
  def completed(self):
    '''
    Method that return the Queryset with the Completed Test
    '''
    return super(TestManager, self).get_query_set().filter(state='completed')

  def jobs(self,type,category,active,golden=False):

    #return super(TestManager, self).get_query_set().filter(is_golden=golden).filter(state=type).filter(template__category=category).filter(template__active=active)
    return (super(TestManager, self)
            .get_query_set()
            .select_related('host', 'template')
            .filter(is_golden=golden,
                    state=type,
                    template__category=category,
                    template__active=active))

#  def runningS(self):
#    '''
#    Method that return the Queryset with the Running Test
#    '''
#    return super(TestManager, self).get_query_set().filter(state='running').filter(template__category='stress')    
#
#  def runningF(self,active=0):
#    '''
#    Method that return the Queryset with the Running Test
#    '''
#    return super(TestManager, self).get_query_set().filter(state='running').filter(template__category='functional').filter(template__active=active)
#
#  def scheduledS(self):
#    '''
#    Method that return the Queryset with the Scheduled Test
#    '''
#    return super(TestManager, self).get_query_set().filter(state='scheduled').filter(template__category='stress')
#
#  def scheduledF(self,active=0):
#    '''
#    Method that return the Queryset with the Scheduled Test
#    '''
#    return super(TestManager, self).get_query_set().filter(state='scheduled').filter(template__category='functional').filter(template__active=active)
#
#  def submittingS(self):
#    '''
#    Method that return the Queryset with the Submitting Test
#    '''
#    return super(TestManager, self).get_query_set().filter(state='submitting').filter(template__category='stress')
#
#  def submittingF(self,active=0):
#    '''
#    Method that return the Queryset with the Submitting Test
#    '''
#    return super(TestManager, self).get_query_set().filter(state='submitting').filter(template__category='functional').filter(template__active=active)

