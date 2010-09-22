import commands

class Cron(object):

  def registerHost(self):
    host=commands.getoutput('hostname')
    load=commands.getoutput("cat /proc/loadavg | awk '{print $1}'")
    load=float(load)
    print 'Host: %s with load %s'%(host,load)

  def run(self):
    self.registerHost()
