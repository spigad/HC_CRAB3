import sys

from hc.atlas.models import Template, Site, TemplateSite

class RemoveSiteFromTemplates:
  """Script to remove a site list from all templates."""

  def run(self):
    """Main runner of the add FT script."""
    
    # Find the AFT templates
    templates = Template.objects #.filter(description__contains='AFT')
    print 'Using templates:', templates
    
    # Get args
    sys.argv.reverse()
    sys.argv.pop()

    # Add the sites
    for site_name in sys.argv:
      for template in templates:
        print 'Removing',site_name,'from',template
        try:
          site = Site.objects.get(name=site_name)
        except:
          print '[ERROR][atlas][remove_site_from_templates] site %s not found.' % site_name
          return 0
        try:
          t_s = TemplateSite.objects.get(site=site, template=template)
          t_s.delete()
          print 'Site',site_name,'removed'
        except:
          pass

    return 1

if __name__ == '__main__':
  RemoveSitesFromTemplates().run()
