#!/usr/bin/python2.5
import getopt,os,sys

from scripts.actions import CronActions
from django.conf import settings

SHORT_OPS = 'f:o:t:h'

try:
  dict = {}
  opts, args = getopt.getopt(sys.argv[1:], SHORT_OPS)
  for o,a in opts:
    dict[o] = a 
except getopt.GetoptError, err:
  print str(err) 
  help()
  sys.exit(2)

def help():

  functions = [func for func in dir(CronActions) if not func[0]=='_']
  
  USAGE = '''\nList of allowed options
  -f : Set the function you want to execute. Below, allowed functions.
       %s
  -h : Print help. '''%(apps,functions)

  print USAGE

def run():

  ca = CronActions()

  if dict.has_key('-h'):
    help()
  elif dict.has_key('-f'):
    if not os.environ.has_key('APP'):
      print '[ERROR] Application env variable APP not found.'
      help()
    elif not os.environ['APP'] in [app.split('.')[1] for app in settings.INSTALLED_APPS if not app.startswith('django')]:
      print '[ERROR] Please, check your parameters. Wrong application name.'
      help()      
    else:
      app = os.environ['APP']
#      try:
      func = getattr(ca,dict['-f'])
      func(app,dict)
#      except:
#        print '[ERROR][%s] The function %s failed misserabily.'%(app,dict['-f'])
#        help()
  else:
    print '[ERROR] Please, check your parameters. Missing function name.'
    help()


if __name__ == '__main__':
  run()
  sys.exit()
