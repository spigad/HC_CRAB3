from hc.core.utils.generic.class_func import custom_import

import commands

class RegisterHost:

  def run(self,app,dic):

    # Exponential smoothing control.
    alpha = 0.2

    #IMPORTS
    host = custom_import('hc.%s.models.Host'%(app))

    hostname = commands.getoutput('hostname')
    load     = commands.getoutput("cat /proc/loadavg | awk '{print $1}'")
    load     = float(load)

    host = host.objects.filter(name=hostname)
    if host:
      host = host[0]
      host.loadavg1m = host.loadavg1m * (1.0 - alpha) + load * alpha
      host.save()
      print '[INFO][%s][register_host] Inserted new load:%s at %s.'%(app,host.loadavg1m,hostname)
    else:
      print '[ERROR][%s][register_host] Unknown host %s'%(app,hostname)
      return 0

    return 1
