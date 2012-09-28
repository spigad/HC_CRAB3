from hc.core.utils.generic.class_func import custom_import

class Blacklist:

  def run(self, app, dic):

    if app == 'core':
      print '[ERROR][%s][blacklist] not available at core app.' % (app)
      return 1

    # Check if the autoexclusion is enabled in the global options.
    global_option = custom_import('hc.%s.models.GlobalOption' % (app))
    try:
      if global_option.objects.get(option_name='autoexclusion_status').option_value == 'disabled':
        print '[WARNING][%s][blacklist] autoexclusion has been disabled.' % (app)
        return 1
    except:
      print '[WARNING][%s][blacklist] there is a problem with the global options. autoexclusion will run by default.' % (app)

    # Look for the app blacklisting script and run it.
    app_script = custom_import('%s.python.scripts.server.blacklist.Blacklist' % (app))

    if app_script:
      try:
        app_script().run(debug=True, test=False)
      except:
        print '[ERROR][%s][blacklist] app blacklisting script failed.' % (app)
        return 0

    return 1
