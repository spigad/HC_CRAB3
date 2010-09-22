from django.conf import settings
from hc.core.utils.class_func import custom_import

def run():

  for app in settings.INSTALLED_APPS:

    if not app.startswith('django'):
      output_info = '%s.cron'%app
      ## Dynamically import a module called 'cron'
      ## from each INSTALLED_APP (if it exists)
      try:
        cron_mod = custom_import(app+'.cron.Cron')
        output_info += '... FOUND'
        print output_info

        ## 3. Execute the cron's run method (if it exists)
        if hasattr(cron_mod, 'run'):
          f = getattr(cron_mod,'run')
          f(cron_mod())

      except ImportError:
        # ignore packages that don't have a cron module
        output_info += '... SKIPPED'
        print output_info

if __name__ == "__main__":
    run()



