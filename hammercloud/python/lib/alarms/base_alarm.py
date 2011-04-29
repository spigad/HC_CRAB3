import re

class BaseAlarm(object):

  def __init__(self,trigger):
    self.trigger = trigger

  def operation(self,metricname,operation,sitename,raw,proc):

    if metricname == 'allcronmetrics':
      metrics = raw.keys()
    elif metricname in raw.keys():
      metrics = [metricname]
    else:
      return proc

    for metric in metrics:
      if proc.has_key(metric):
        if proc[metric].has_key(operation):
          if proc[metric][operation].has_key(sitename):
            continue
        else:
          proc[metric][operation] = {}
      else:
        proc[metric] = {operation:{}}

      proc = getattr(self,operation)(metric,sitename,raw,proc)

    return proc

  def parseTrigger(self,raw,proc,sitename,ops=[]):
    #Notation:
    #<type><ops>_<metric>
    #<type>   : g(lobal),s(ite)
    #<metric> : all,cron_allowed metric.names
    if not ops:
      ops = ['mean','stdv','max','min']

    metrics = raw.keys()
    matches = []

    for o in ops:

      g = re.compile(r'g%s_\w*'%(o))
      s = re.compile(r's%s_\w*'%(o))

      gs = re.findall(g,self.trigger)
      if gs:
        for match in gs:
          proc = self.operation(match.split('_',1)[1],o,'global',raw,proc)
          if not match in matches:
            matches.append(match)

      ss = re.findall(s,self.trigger)
      if ss:
        for match in ss:
          proc = self.operation(match.split('_',1)[1],o,sitename,raw,proc)
          if not match in matches:
            matches.append(match)

    return proc,matches

  def substitute(self,match,site,metric):

    range_op,param_metric = match.split('_',1)
    if param_metric != 'allcronmetrics':
      metric = param_metric
    if range_op[0] == 'g':
      site = 'global'

    return 'proc["%s"]["%s"]["%s"]'%(metric,range_op[1:],site)

  def run(self,raw,proc,site):

    if not self.trigger:
      print '[ERROR][ALARM] No trigger.'
      return (-1,'[ERROR][ALARM] No trigger.')

    proc,matches = self.parseTrigger(raw,proc,site)
    metrics      = raw.keys()

    evals = [self.trigger]*len(metrics)
    new_matches = []

    counter = 0
    for metric in metrics:
      for match in matches:
        nm = self.substitute(match,site,metric)
        new_matches += [nm]
        evals[counter] = evals[counter].replace(match,nm)
      counter += 1

    results = {True:0,False:0,'ERROR':0}
    log     = []

    for evl in evals:
      try:
        output = eval(evl)
      except:
        output = 'ERROR'

      results[output] += 1
      log += [(output,evl)]

    match_val = {}
    for m in new_matches:
      try:
        output = eval(m)
      except:
        output = 'ERROR'
      match_val[m] = str(output)

    return (results,log,match_val)

