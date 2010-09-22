from django.conf import settings
from hc.core.utils.class_func import custom_import

import sys

try:
  freq = int(sys.argv[1])
except IndexError:
  print "Frequency required"
  sys.exit()
except ValueError:
  print "Integer required"
  sys.exit()

def run():

  print 'Frequency: %d'%(freq)

  for app in settings.INSTALLED_APPS:

    if not app.startswith('django'):
  
      output_info = '  %s'%app
      ## Dynamically import a module called 'cron.cron_settings'
      ## from each INSTALLED_APP (if it exists)
      try:
        cron_mod = custom_import(app+'.cron_settings.CRONJOBS')
        output_info += '... FOUND cron_settings.py'
        print output_info

        if cron_mod.has_key(str(freq)):
          for cron in cron_mod[str(freq)]:
            cronjob = '    *%s'%(cron) 

            try:
              cron_function = custom_import('%s.crontab.jobs.%s.Cron'%(app,cron))
              if hasattr(cron_function, 'run'):
                f = getattr(cron_function,'run')
                f(cron_function())
                cronjob += ' -> Ok.'
              else:
                cronjob += ' -> ERROR: skipped due to LACK of run method'
            except ImportError:
              cronjob += ' ERROR: skipped due to IMPORT ERROR.'
            except:
              cronjob += ' ERROR: skipped due to TERRIBLE ERROR.'             
           
            print cronjob

      except ImportError:
        # ignore packages that don't have a cron.cron_settings module
        output_info += '... SKIPPED'
        print output_info
      


if __name__ == "__main__":
    run()



