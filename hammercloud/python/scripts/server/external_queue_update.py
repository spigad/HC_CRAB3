from hc.core.utils.generic.class_func import custom_import

class ExternalQueueUpdate:

  def run(self, app, dic):

    if app == 'core':
      print '[ERROR][%s][external_queue_update] not available at core app.' % (app)
      return 1

    # Look for the app blacklisting script and run it.
    app_script = custom_import('%s.python.scripts.server.external_queue_update.ExternalQueueUpdate' % (app))

    if app_script:
      try:
        app_script().run()
      except:
        print '[ERROR][%s][external_queue_update] app external_queue_update script failed.' % (app)
        return 0

    return 1
