#from django.db import models

def getSites(cloud):
  '''
  Method that return the site names belonging to the
  cloud object.
  '''
  return [s.name for s in cloud.getSites_for_cloud.all()]                                                       

def isPanda(cloud):
  '''
  Method that return True if the Cloud is a Panda Cloud,
  False in the other cases
  '''
  if 'PANDA' in cloud.code:
    return 1
  return 0

def  isNG(self):
  '''
  Method that return True if the Cloud is a  Cloud,
  False in the other cases
  '''
  if 'NG' in cloud.code:
    return 1
  return 0

