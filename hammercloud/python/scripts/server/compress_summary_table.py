from hc.core.utils.generic.class_func import custom_import

from datetime import datetime,timedelta

from lib.summary import resume,resume2


class CompressSummaryTable:

  def check(self,app,dic):

    if app == 'core':
      print '[ERROR][%s][compress_summary_table] not available at core app.'%(app)
      return 0

    compress = ''

    if not dic.has_key('-o'):
      print '[WARNING][%s][compress_summary_table] Taking values by default: daily'
      compress = 'daily'
    else:
      if 'd' in dic['-o']:
        compress = 'daily'
      elif 'w' in dic['-o']:
        compress = 'weekly'
      elif 'm' in dic['-o']:
        compress = 'monthly'
      elif 'y' in dic['-o']:
        compress = 'yearly'
      else:
        print "[ERROR][%s][compress_summary_table] Please, don't be evil. Options available are d(aily), w(eekly), m(onthly), y(early)."%(app)
        return 0
    
    return compress

  def run(self,app,dic):

    compress = self.check(app,dic)

    try:
      resume2.resume(app,compress)
    except:
      print '[ERROR][%s][compress_summary_table] Error resuming summary_evolution table.'%(app)

    return 1
