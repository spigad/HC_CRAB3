from hc.core.utils.generic.class_func import custom_import

class Blacklist:
  """ATLAS Blacklisting script. Runs the scripts for analysis and production
     queues."""

  def run(self, debug=False, test=False):
    """Main runner of the blacklisting script."""
    
    # Look for the app blacklisting script and run it.
    blacklist_modules = ('atlas.python.scripts.server.analysis_blacklist.AnalysisBlacklist',
                         'atlas.python.scripts.server.production_blacklist.ProductionBlacklist',
                         )

    for module_name in blacklist_modules:
      try:
        script = custom_import(module_name)
        script().run(test=False)
      except:
        print '[ERROR][atlas][blacklist] blacklisting script failed for module %s.' % module_name

    return 1
