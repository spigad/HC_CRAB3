from hc.core.utils.generic.class_func import custom_import

class Blacklist:

  def run(self, app, dic):

    if app == 'core':
      print '[ERROR][%s][blacklist] not available at core app.' % (app)
      return 1

    # Look for the app blacklisting script and run it.
    app_script = custom_import('%s.python.scripts.server.blacklist.Blacklist' % (app))

    if app_script:
      try:
        app_script().run(debug=True, test=False)
      except:
        print '[ERROR][%s][blacklist] app blacklisting script failed.' % (app)
        return 0

    return 1
