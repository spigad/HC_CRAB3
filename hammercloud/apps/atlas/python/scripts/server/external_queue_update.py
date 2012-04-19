from pandatools import Client
from hc.atlas.models import *
from django.core.exceptions import ObjectDoesNotExist
import commands
import datetime
import logging
import re
import time
import unittest


STATUS_OPTION = 'panda_status'
COMMENT_OPTION = 'panda_comment'
TIMESTAMP_OPTION = 'panda_timestamp'


class ExternalQueueUpdate:
  """ATLAS External Queue Update script."""

  def save_blacklistevent_for_site(self, site, event, reason):
    """Stores a BlacklistEvent for a site, with the event as specified."""
    be = BlacklistEvent(reason=reason,
                        timestamp=datetime.datetime.now(),
                        external=True,
                        event=event,
                        site=site)
    be.save()

  def update_status_for_site(self, site):
    """Updates the status from the PanDA Client if it is different or not
       existing in the site options table."""
    now = datetime.datetime.now()
    # Get current status from PanDA client.
    try:
        status = Client.PandaSites[site.name]['status']
        comment = Client.PandaSites[site.name]['comment']
    except KeyError:
        logging.warning("No information available for site %s in PanDA tools", site.name)
        return
    # Get current status stored in the DB.
    try:
      current_status = SiteOption.objects.get(site=site, option_name=STATUS_OPTION)
      # If changed, update.
      if current_status.option_value != status:
        try:
          current_status.option_value = status
          current_status.save()
          # Don't forget to update the timestamp and comment.
          current_timestamp = SiteOption.objects.get(site=site, option_name=TIMESTAMP_OPTION)
          current_timestamp.option_value = now
          current_timestamp.save()
          current_comment = SiteOption.objects.get(site=site, option_name=COMMENT_OPTION)
          current_comment.option_value = comment
          current_comment.save()
          logging.info("Site '%s' updated to the new status ('%s' -> '%s')",
                       site.name, current_status, status)
          # Store a BlacklistEvent for an external change (those that don't start with
          # HC, note that only if the status is changed).
          if not comment.startswith('HC'):
            if status == 'online':
              self.save_blacklistevent_for_site(site, 'whitelist', 'Set to online by an external tool or user.')
            elif status in ('brokeroff', 'test') and current_status.option_value not in ('brokeroff', 'test'):
              self.save_blacklistevent_for_site(site, 'blacklist', 'Set to %s by an external tool or user.' % status)
            else:
              logging.info('Site %s is now in %s status set by an external tool or user.', site_name, status)
            TestLog(comment="%s was set to '%s' by an external agent."%(site.name,status), severity='queuecontrol', user=1).save()
        except ObjectDoesNotExist, MultipleObjectsReturned:
          logging.error("PanDA options for site '%s' are inconsistent", site.name)
          TestLog(comment="QueueControl detected that PanDA options for site %s ('%s') are inconsistent."%(site.name,status), severity='warning', user=1).save()
          return
      else:
        logging.info("Site '%s' not needed to be updated (status='%s')", site.name, status)
    except ObjectDoesNotExist:
      # First time we see this site.
      SiteOption(site=site, option_name=STATUS_OPTION, option_value=status).save()
      SiteOption(site=site, option_name=COMMENT_OPTION, option_value=comment).save()
      SiteOption(site=site, option_name=TIMESTAMP_OPTION, option_value=now).save()
      return
    except MultipleObjectsReturned:
      logging.error("PanDA status '%s' for site '%s' is inconsistent (duplicated).", STATUS_OPTION, site.name)
      TestLog(comment="QueueControl error: PanDA status '%s' for site '%s' is inconsistent (duplicated)."%(STATUS_OPTION,site.name), severity='warning', user=1).save()
      return

  def run(self, debug=False, test=False):
    """Main runner of the updater script."""
    for site in Site.objects.filter(enabled=True).filter(name__startswith='ANALY'):
      self.update_status_for_site(site)
    return True
