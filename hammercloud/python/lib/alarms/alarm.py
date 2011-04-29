from lib.alarms.base_alarm import BaseAlarm

import numpy
#import re

class Alarm(BaseAlarm):

  def __init__(self,trigger):
    super(Alarm,self).__init__(trigger)

  def max(self,metricname,sitename,raw,proc):
    vals = []
    if sitename == 'global':
      for r in raw[metricname].values():
        vals += r
    else:
      vals = raw[metricname][sitename]

    if 'NULL' in vals:
      vals = vals.remove('NULL')
    if None in vals:
      vals = vals.remove(None)

    if len(vals):
      proc[metricname]['max'][sitename] = max(vals)
    return proc

  def min(self,metricname,sitename,raw,proc):
    vals = []
    if sitename == 'global':
      for r in raw[metricname].values():
        vals += r
    else:     
      vals = raw[metricname][sitename]

    if 'NULL' in vals:
      vals = vals.remove('NULL')
    if None in vals:
      vals = vals.remove(None)

    if len(vals):
      proc[metricname]['min'][sitename] = min(vals)

    return proc

  def mean(self,metricname,sitename,raw,proc):
    vals = []
    if sitename == 'global':
      for r in raw[metricname].values():
        vals += r
    else:
      vals = raw[metricname][sitename]

    if 'NULL' in vals:
      vals = vals.remove('NULL')
    if None in vals:
      vals = vals.remove(None)
   
    if len(vals):
      proc[metricname]['mean'][sitename] = numpy.mean(vals)
    return proc

  def stdv(self,metricname,sitename,raw,proc):
    vals = []
    if sitename == 'global':
      for r in raw[metricname].values():
        vals += r         
    else:
      vals = raw[metricname][sitename]

    if 'NULL' in vals:
      vals = vals.remove('NULL')
    if None in vals:
      vals = vals.remove(None)

    if len(vals):
      proc[metricname]['stdv'][sitename] = numpy.std(vals)
    return proc

  def parseTrigger(self,raw,proc,sitename):
    #Notation:
    #<type><ops>_<metric>
    #<type>   : g(lobal),s(ite) 
    #<metric> : all,cron_allowed metric.names
    ops = ['mean','stdv','max','min']
    return super(Alarm,self).parseTrigger(raw,proc,sitename,ops)

  def run(self,raw,proc,site):
    return super(Alarm,self).run(raw,proc,site)


