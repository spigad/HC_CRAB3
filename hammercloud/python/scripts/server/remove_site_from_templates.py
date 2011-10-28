import sys

from hc.core.utils.generic.class_func import custom_import
from hc.atlas.models import Template, Site, TemplateSite

class RemoveSiteFromTemplates:
  """Script to remove a site lis from the templates."""

  def run(self,app,dic):
    """Main runner of the add FT script."""

    if app == 'core':
      print '[ERROR][%s][remove_site_from_templates] not available at core app.'%(app)
      return 1

    template = custom_import('hc.%s.models.Template'%(app))
    site     = custom_import('hc.%s.models.Site'%(app))
    templatesite = custom_import('hc.%s.models.TemplateSite'%(app))
    
    # Find the AFT templates
    templates = template.objects #.filter(description__contains='AFT')
    print 'Using templates:', templates
    
    # Get args
    sys.argv.reverse()
    sys.argv.pop()
    sys.argv.pop()

    # Add the sites
    for site_name in sys.argv:
      for templ in templates:
        print 'Removing',site_name,'from',templ
        try:
          s = site.objects.get(name=site_name)
        except:
          print '[ERROR][%s][remove_site_from_templates] site %s not found.' % (app,site_name)
          return 0
        try:
          t_s = templatesite(site=s,
                             template=templ)
          t_s.delete()
          print 'Site',site_name,'removed'
        except:
          pass

    return 1
