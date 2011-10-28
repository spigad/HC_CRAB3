import sys

from hc.core.utils.generic.class_func import custom_import
from hc.atlas.models import Template, Site, TemplateSite

class AddSiteToFT:
  """Script to add a site list to the FT templates."""

  def run(self,app,dic):
    """Main runner of the add FT script."""

    if app == 'core':
      print '[ERROR][%s][add_site_to_ft] not available at core app.'%(app)
      return 1

    template = custom_import('hc.%s.models.Template'%(app))
    site     = custom_import('hc.%s.models.Site'%(app))
    templatesite = custom_import('hc.%s.models.TemplateSite'%(app))
    
    # Find the AFT templates
    templates = template.objects.filter(description__contains='AFT')
    print 'Using templates:', templates
    
    # Get args
    sys.argv.reverse()
    sys.argv.pop()
    sys.argv.pop()
    sys.argv.pop()
    sys.argv.pop()

    # Add the sites
    for site_name in sys.argv:
      for templ in templates:
        print 'Adding',site_name,'to',templ
        try:
          s = site.objects.get(name=site_name)
        except:
          print '[ERROR][%s][add_site_to_ft] site %s not found.' % (app,site_name)
          return 0
        try:
          t_s = templatesite(site=s,
                             template=templ,
                             resubmit_enabled=True,
                             resubmit_force=False,
                             num_datasets_per_bulk=1,
                             min_queue_depth=0,
                             max_running_jobs=1)
          t_s.save()
          print 'Site',site_name,'added'
        except:
          pass

    return 1
