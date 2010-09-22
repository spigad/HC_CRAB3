#from django.db import models

def getSites(backend):
  '''
  Method that return the site names belonging to the
  backend object.
  '''
  return [s.name for s in backend.getSites_for_backend.all()]                                                       


