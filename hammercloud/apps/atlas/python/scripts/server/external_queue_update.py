from atlas.utils.atlas_topology import ATLASTopology, ATLASTopologyError
from django.core.exceptions import ObjectDoesNotExist
from django.utils.timezone import now
from hc.atlas.models import BlacklistEvent, Site, SiteOption, TestLog
from pandatools import Client
import logging


ATLAS_TOPOLOGY = ATLASTopology()
STATUS_OPTION = 'panda_status'
COMMENT_OPTION = 'panda_comment'
TIMESTAMP_OPTION = 'panda_timestamp'
HEPSPEC_OPTION = 'hepspec_declared'


class ExternalQueueUpdate:
    """ATLAS External Queue Update script."""

    def save_blacklistevent_for_site(self, site, event, reason):
        """Stores a BlacklistEvent for a site, with the event as specified."""
        BlacklistEvent(reason=reason, timestamp=now(), external=True,
                       event=event, site=site).save()

    def update_site_field(self, site, field, value, save=True):
        """Updates the field of the object only if it changes."""
        if getattr(site, field) != value:
            setattr(site, field, value)
            if save:
                site.save()

    def set_site_option(self, site, option_name, option_value):
        try:
            option = SiteOption.objects.get(site=site, option_name=option_name)
            if option.option_value != option_value:
                option.option_value = option_value
                option.save()
        except SiteOption.MultipleObjectsReturned:
            logging.error('The site option is corrupted (multiple values)')
        except SiteOption.DoesNotExist:
            SiteOption(site=site, option_name=option_name,
                       option_value=option_value).save()

    def update_status_for_site(self, site):
        """Updates the status from the PanDA Client if it is different or not
           existing in the site options table."""
        # Update the information coming from the ATLAS topology.
        try:
            self.update_site_field(site, 'real_name',
                                   ATLAS_TOPOLOGY.get_site_from_siteid(site.name))
            self.update_site_field(site, 'ddm',
                                   ATLAS_TOPOLOGY.get_ddm_from_siteid(site.name))
            self.set_site_option(site, HEPSPEC_OPTION,
                                 ATLAS_TOPOLOGY.get_hepspec_from_siteid(site.name))
        except ATLASTopologyError, ae:
            logging.error(ae)
        # Get current status from PanDA client.
        try:
            status = Client.PandaSites[site.name]['status']
            comment = Client.PandaSites[site.name]['comment']
        except KeyError:
            logging.warning("No information found for %s in PanDA", site.name)
            return
        # Get current status stored in the DB.
        try:
            current_status = SiteOption.objects.get(site=site,
                                                    option_name=STATUS_OPTION)
        except ObjectDoesNotExist:
            # First time we see this site.
            self.set_site_option(site, STATUS_OPTION, status)
            self.set_site_option(site, TIMESTAMP_OPTION, now())
            self.set_site_option(site, COMMENT_OPTION, comment)
        else:
            if current_status.option_value != status:
                self.set_site_option(site, STATUS_OPTION, status)
                self.set_site_option(site, TIMESTAMP_OPTION, now())
                self.set_site_option(site, COMMENT_OPTION, comment)
                logging.info("Site '%s' status updated ('%s' -> '%s')",
                             site.name, current_status, status)
                # Store a BlacklistEvent for an external change (those that
                # don't start with HC, note that only if the status is
                # changed).
                if not comment.startswith('HC'):
                    if status == 'online':
                        self.save_blacklistevent_for_site(site, 'whitelist',
                                                          'Set to online by an external tool or user.')
                    elif (status in ('brokeroff', 'test')
                          and current_status.option_value not in ('brokeroff', 'test')):
                        self.save_blacklistevent_for_site(site, 'blacklist',
                                                          'Set to %s by an external tool or user.' % status)
                    else:
                        logging.info('Site %s is now in %s status set by an external tool or user.',
                                     site.name, status)
                    TestLog(comment="%s was set to '%s' by an external agent." % (site.name, status),
                            severity='queuecontrol', user=1).save()

    def run(self, debug=False, test=False):
        """Main runner of the updater script."""
        for site in Site.objects.filter(enabled=True):
            self.update_status_for_site(site)
        return True
