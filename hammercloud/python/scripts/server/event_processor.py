from hc.core.utils.generic.class_func import custom_import

class EventProcessor:

  def run(self, app, dic):

    if app == 'core':
      print '[ERROR][%s][event_processor] not available at core app.' % (app)
      return 1

    # Look for the app blacklisting script and run it.
    app_script = custom_import('hc.core.base.publisher.event_processor.EventConsumer')

    if app_script:
      try:
        print '[INFO][%s][event_processor] Initializing the EventConsumer run loop.' % (app)
        app_script(app).run()
      except:
        raise
        print '[ERROR][%s][event_processor] app event procesor script failed.' % (app)
        return 0

    return 1
