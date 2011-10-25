import sys

from hc.atlas.models import Template, Site, TemplateSite

class AddSiteToFT:
  """Script to add a site list to the FT templates."""

  def run(self):
    """Main runner of the add FT script."""
    
    # Find the AFT templates
    templates = Template.objects.filter(description__contains='AFT')
    print 'Using templates:', templates
    
    # Get args
    sys.argv.reverse()
    sys.argv.pop()

    # Add the sites
    for site_name in sys.argv:
      for template in templates:
        print 'Adding',site_name,'to',template
        try:
          site = Site.objects.get(name=site_name)
        except:
          print '[ERROR][atlas][add_site_to_ft] site %s not found.' % site_name
          return 0
        try:
          t_s = TemplateSite(site=site,
                             template=template,
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

if __name__ == '__main__':
  AddSiteToFT().run()
