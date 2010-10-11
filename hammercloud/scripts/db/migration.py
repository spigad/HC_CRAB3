#!/usr/bin/python2.5

import hcutil,sys
from hc.cms.models import *

def getClouds(cursor):
  cursor.execute('select name,code from cloud order by id')
  clouds = cursor.fetchall()

  for cloud in clouds:
    c = Cloud(name=cloud[0],code=cloud[1])
    c.save()

def getBackends(cursor):

  b = Backend(name='CMSSW')
  b.save()

def getSites(cursor):  
  cursor.execute('select site.name,cloud.name,site.ddm,site.enabled from site,cloud where site.cloud=cloud.id order by site.id')
  sites = cursor.fetchall()

  b = Backend.objects.all()[0]

  for site in sites:
    c = Cloud.objects.filter(name=site[1])[0]
    s = Site(name=site[0],cloud=c,ddm=site[2],enabled=site[3],backend=b)
    s.save()

if __name__ == '__main__':

  conn = hcutil.connect()
  cursor = conn.cursor ()

  #GET CLOUDS:
  getClouds(cursor)

  #GET BACKENDS:
  getBackends(cursor)

  #GET SITES:
  getSites(cursor)

  cursor.close ()
  conn.commit()
  conn.close()
  sys.exit()

