import commands
import datetime
import re
import time
import unittest
import sys

from hc.core.utils.hc import cernmail
from hc.atlas.models import Site, Result, SiteOption, Template, TemplateSite, Test, TestLog, BlacklistEvent
from pandatools import Client

SITETYPE = 'production'
Client.PandaSites = Client.getSiteSpecs(SITETYPE)[1]
DEBUG = False

class Policy:
  """Base class for blacklisting policies."""

  def filter_jobs_by_template(self, jobs, template):
    """Filters by template ID."""
    return filter(lambda x: x.test.template.id == template, jobs)

  def evaluate(self, jobs, site, blacklist, failed_templates_target, num_jobs_per_template):
    """Generic evaluator for XFromY templates."""
    if not jobs:
      blacklist.site_has_no_jobs(site)
      return False
    failed_templates = 0
    ids = []
    for t in blacklist.templates:
      template_jobs = self.filter_jobs_by_template(jobs, t)
      if len(template_jobs) < num_jobs_per_template:
        blacklist.sitesNeedingJobs[t].append(site)
        continue
      if reduce(lambda x, y: x and y.ganga_status == 'f', template_jobs[:num_jobs_per_template], True):
        failed_templates += 1
        ids.extend(map(lambda x: x.backendID, template_jobs[:num_jobs_per_template]))
    if failed_templates < failed_templates_target:
      return False
    blacklist.add_reason(site, 'BlackListing policy %s True. See jobs %s' % (self.__class__.__name__, repr(ids)))
    return True


class BlackListingPolicyLastOneFromAll(Policy):
  def evaluate(self, jobs, site, blacklist):
    return Policy.evaluate(self, jobs, site, blacklist, 4, 1)


class BlackListingPolicyLastTwoFromTwo(Policy):
  def evaluate(self, jobs, site, blacklist):
    return Policy.evaluate(self, jobs, site, blacklist, 2, 2)


class BlackListingPolicyLastFourFromOne(Policy):
  def evaluate(self, jobs, site, blacklist):
    return Policy.evaluate(self, jobs, site, blacklist, 1, 4)


class BlackListingPolicyLastOneFromThree(Policy):
  def evaluate(self, jobs, site, blacklist):
    return Policy.evaluate(self, jobs, site, blacklist, 3, 1)


class BlackListingPolicyLastThreeFromOne(Policy):
  def evaluate(self, jobs, site, blacklist):
    return Policy.evaluate(self, jobs, site, blacklist, 1, 3)


class BlackListingPolicyLastTwoPlusOne(Policy):
  def evaluate(self, jobs, site, blacklist):
    if not jobs:
      blacklist.site_has_no_jobs(site)
      return False
    failed_two_templates = 0
    failed_one_templates = 0
    ids = []
    for t in blacklist.templates:
      template_jobs = self.filter_jobs_by_template(jobs, t)
      if len(template_jobs) < 2:
        blacklist.sitesNeedingJobs[t].append(site)
        continue
      if template_jobs[0].ganga_status == 'f' and template_jobs[1].ganga_status == 'f':
        failed_two_templates += 1
        ids.extend((template_jobs[0].backendID, template_jobs[1].backendID))
      elif template_jobs[0].ganga_status == 'f':
        failed_one_templates += 1
        ids.append(template_jobs[0].backendID)
    if failed_two_templates >= 2 or (failed_two_templates >= 1 and failed_one_templates >= 1):
      blacklist.add_reason(site, 'BlackListing policy Last-Two-Plus-One True. See jobs %s' % repr(ids))
      return True
    return False


class WhiteListingPolicyLastTwoFromAll(Policy):
  def evaluate(self, jobs, site, blacklist):
    if not jobs:
      blacklist.site_has_no_jobs(site)
      blacklist.add_reason(site, 'WhiteListing policy Last-Two-From-All not passed. Site needs for all templates %s' % repr(blacklist.templates))
      return True
    ok_templates = 0
    ids = []
    for t in blacklist.templates:
      template_jobs = self.filter_jobs_by_template(jobs, t)
      if len(template_jobs) < 2:
        blacklist.sitesNeedingJobs[t].append(site)
        continue
      if template_jobs[0].ganga_status == 'c' and template_jobs[1].ganga_status == 'c':
        ok_templates += 1
      else:
        if template_jobs[0].ganga_status != 'c': ids.append(template_jobs[0].backendID)
        if template_jobs[1].ganga_status != 'c': ids.append(template_jobs[1].backendID)
    if ok_templates < len(blacklist.templates):
      blacklist.add_reason(site, 'WhiteListing policy Last-Two-From-All not passed. See jobs %s' % repr(ids))
      return True
    return False


class BlacklistingTest(unittest.TestCase):
  def create_result_list_from_tuples(self, tuples):
    results = []
    for (ganga_status, template_id, backendID) in tuples:
      results.append(Result(ganga_status=ganga_status, test=Test(template=Template(id=template_id)), backendID=backendID))
    return results

  def testBlacklistingPolicyLastOneFromAll(self):
    b = ProductionBlacklist(templates=(67, 80, 95, 96), debug=True)

    self.assertEqual(False, BlackListingPolicyLastOneFromAll().evaluate((), 'ANALY_TEST', b)) # base case

    failed = (('f', 67, None), ('f', 80, None), ('f', 95, None), ('f', 96, None))
    self.assertEqual(True, BlackListingPolicyLastOneFromAll().evaluate(self.create_result_list_from_tuples(failed), 'ANALY_TEST', b))

    notall = (('f', 67, None), ('c', 80, None), ('f', 95, None), ('f', 96, None))
    self.assertEqual(False, BlackListingPolicyLastOneFromAll().evaluate(self.create_result_list_from_tuples(notall), 'ANALY_TEST', b))

    notall = (('c', 67, None), ('c', 80, None), ('f', 95, None), ('f', 96, None))
    self.assertEqual(False, BlackListingPolicyLastOneFromAll().evaluate(self.create_result_list_from_tuples(notall), 'ANALY_TEST', b))

    notall = (('c', 67, None), ('c', 80, None), ('c', 95, None), ('c', 96, None))
    self.assertEqual(False, BlackListingPolicyLastOneFromAll().evaluate(self.create_result_list_from_tuples(notall), 'ANALY_TEST', b))

    notall = (('f', 67, None), ('f', 80, None), ('f', 95, None))
    self.assertEqual(False, BlackListingPolicyLastOneFromAll().evaluate(self.create_result_list_from_tuples(notall), 'ANALY_TEST', b))

  def testBlacklistingPolicyLastTwoFromTwo(self):
    b = ProductionBlacklist(templates=(67, 80, 95, 96), debug=True)

    self.assertEqual(False, BlackListingPolicyLastTwoFromTwo().evaluate((), 'ANALY_TEST', b)) # base case

    failed = (('f', 67, None), ('f', 80, None), ('f', 95, None), ('f', 96, None), ('f', 67, None), ('f', 80, None), ('f', 95, None), ('f', 96, None))
    self.assertEqual(True, BlackListingPolicyLastTwoFromTwo().evaluate(self.create_result_list_from_tuples(failed), 'ANALY_TEST', b))

    notall = (('f', 67, None), ('c', 80, None), ('f', 95, None), ('f', 96, None), ('f', 67, None), ('c', 80, None), ('f', 95, None), ('f', 96, None))
    self.assertEqual(True, BlackListingPolicyLastTwoFromTwo().evaluate(self.create_result_list_from_tuples(notall), 'ANALY_TEST', b))

    notall = (('c', 67, None), ('c', 80, None), ('f', 95, None), ('f', 96, None), ('c', 67, None), ('c', 80, None), ('f', 95, None), ('f', 96, None))
    self.assertEqual(True, BlackListingPolicyLastTwoFromTwo().evaluate(self.create_result_list_from_tuples(notall), 'ANALY_TEST', b))

    notall = (('c', 67, None), ('c', 80, None), ('c', 95, None), ('c', 96, None), ('c', 67, None), ('c', 80, None), ('c', 95, None), ('c', 96, None))
    self.assertEqual(False, BlackListingPolicyLastTwoFromTwo().evaluate(self.create_result_list_from_tuples(notall), 'ANALY_TEST', b))

  def testBlacklistingPolicyLastFourFromOne(self):
    b = ProductionBlacklist(templates=(67, 80, 95, 96), debug=True)

    self.assertEqual(False, BlackListingPolicyLastFourFromOne().evaluate((), 'ANALY_TEST', b)) # base case

    failed = (('f', 67, None), ('f', 67, None), ('f', 67, None), ('f', 67, None))
    self.assertEqual(True, BlackListingPolicyLastFourFromOne().evaluate(self.create_result_list_from_tuples(failed), 'ANALY_TEST', b))

    notall = (('f', 67, None), ('f', 67, None), ('c', 67, None), ('f', 67, None))
    self.assertEqual(False, BlackListingPolicyLastFourFromOne().evaluate(self.create_result_list_from_tuples(notall), 'ANALY_TEST', b))


class ProductionBlacklist:
  """ATLAS Blacklisting script for production queues."""

  dan = 'daniel.colin.vanderster@cern.ch,ramon.medrano.llamas@cern.ch,gianfranco.sciacca@lhep.unibe.ch,johannes.elmsheuser@cern.ch'
  daops = 'atlas-adc-adcos-automatic-notifications@cern.ch,dvanders@cern.ch,johannes.elmsheuser@cern.ch,federica.legger@physik.uni-muenchen.de,ramon.medrano.llamas@cern.ch,jaroslava.schovancova@cern.ch,alessandro.di.girolamo@cern.ch,gianfranco.sciacca@lhep.unibe.ch,I.Ueda@cern.ch,Stephane.Jezequel@cern.ch'
  daexp = 'dvanders@cern.ch,johannes.elmsheuser@cern.ch,federica.legger@physik.uni-muenchen.de,ramon.medrano.llamas@cern.ch,jaroslava.schovancova@cern.ch,alessandro.di.girolamo@cern.ch,gianfranco.sciacca@lhep.unibe.ch'

  def __init__(self, templates=None):
    if not templates:
      self.templates = (439,440,441)
    else:
      self.templates = templates
    self.policies_for_test = (BlackListingPolicyLastOneFromThree, BlackListingPolicyLastTwoPlusOne,
                                   BlackListingPolicyLastThreeFromOne, WhiteListingPolicyLastTwoFromAll)
    self.policies_for_online = (BlackListingPolicyLastOneFromThree, BlackListingPolicyLastTwoPlusOne,
                                BlackListingPolicyLastThreeFromOne)
    self.debug = DEBUG
    self.test = False
    self.runningTests = None
    self.sitesNeedingJobs = {}
    for x in self.templates:
      self.sitesNeedingJobs[x] = []
    self.once = None
    self.reasons = {}
    self.log = ''
    self.once = False

  def run(self, test=False):
    """Main runner of the blacklisting script."""
    self.reasons = {}
    self.log = ''
    self.debug = DEBUG
    self.test = test
    self.once = False
    if self.debug:
      self.daops = self.daexp = self.dan
    if self.test:
      import sys
      sys.argv = ['']
      suite = unittest.TestLoader().loadTestsFromTestCase(BlacklistingTest)
      unittest.TextTestRunner(verbosity=2).run(suite)
      return True
    self.get_running_test()
    self.check_test_sites()
    self.check_online_sites()
    self.send_alert()
    return True

  def check_test_sites(self):
    self.sitesNeedingJobs = {}
    sitesToAutoSetOnline = []
    limit = datetime.datetime.now() - datetime.timedelta(hours=4)
    for x in self.templates:
      self.sitesNeedingJobs[x] = []
    bo_sites = self.get_sites(status='test')
    self.store_log("Checking these sites currently test because of HC: %s"%bo_sites, 'blacklisting')
    (_, newsites) = self.check_in_templates(bo_sites)
    if newsites:
      self.store_log('** New test sites not in templates: %s' % repr(newsites), 'warning')
    print self.runningTests
    for site in bo_sites:
      # The map() for the test ID is needed because MySQL 5.1 does not support nested IN
      # with ALL in a subquery (makes this QuerySet a little bit slower).
      res = Result.objects.exclude(ganga_subjobid=1000000).filter(fixed=1).filter(mtime__gt=limit).filter(test__id__in=map(lambda x: x.id, self.runningTests)).filter(site__name=site).order_by('-mtime')
      if reduce(lambda x, y: x and not y, map(lambda x: x().evaluate(res, site, self), self.policies_for_test), True) and not self.site_needs_jobs(site):
        sitesToAutoSetOnline.append(site)
      else:
        self.log_reasons((site,))
    if sitesToAutoSetOnline:
      self.add_log("")
      self.add_log("AUTO-WHITELIST: The following test sites will be set to online:")
      self.add_log("%s" % sitesToAutoSetOnline)
      for s in sitesToAutoSetOnline:
        if self.change_site_status(s, 'online'):
          self.store_log('Site %s was set to online' % s, 'whitelisting')
          self.send_cloud_online_alert(s)
          BlacklistEvent(event='whitelist', reason='', timestamp=datetime.datetime.now(), external=False, site=Site.objects.get(name=s)).save()

  def check_online_sites(self):
    self.sitesNeedingJobs = {}
    sitesToSetBrokeroff = []
    limit = datetime.datetime.now() - datetime.timedelta(hours=4)
    for x in self.templates:
      self.sitesNeedingJobs[x] = []
    online_sites = self.get_sites(status='online')
    (_, newsites) = self.check_in_templates(online_sites)
    if newsites:
      self.store_log('** New online sites not in templates: %s' % repr(newsites), 'warning')
    for site in online_sites:
      res = Result.objects.exclude(ganga_subjobid=1000000).filter(fixed=1).filter(mtime__gt=limit).filter(test__id__in=map(lambda x: x.id, self.runningTests)).filter(site__name=site).order_by('-mtime')
      if reduce(lambda x, y: x or y, map(lambda x: x().evaluate(res, site, self), self.policies_for_online), False):
        sitesToSetBrokeroff.append(site)

    for t in self.templates:
      if self.sitesNeedingJobs[t]:
        self.sitesNeedingJobs[t] = sorted(list(set(self.sitesNeedingJobs[t])))
        #self.add_log("The following online sites need more test jobs for template %d:" % t)
        #self.add_log("%s" % ', '.join(self.sitesNeedingJobs[t]))
        self.store_log("The following online sites need more test jobs for template %d: %s" % (t, ', '.join(self.sitesNeedingJobs[t])), 'warning')

    if sitesToSetBrokeroff:
      self.add_log("")
      self.add_log("BLACKLIST: The following online sites will be set to test:")
      self.add_log("%s" % sitesToSetBrokeroff)
      for s in sitesToSetBrokeroff:
        if self.change_site_status(s, 'test'):
          self.store_log('Site %s will be set to test' % s, 'blacklisting')
          self.store_log('%s blacklisting reason is %s' % (s, self.reasons[s]), 'blacklisting')
          self.send_cloud_alert(s)
          BlacklistEvent(event='blacklist', reason=self.reasons[s], timestamp=datetime.datetime.now(), external=False, site=Site.objects.get(name=s)).save()

  def change_site_status(self, site, new_status):
    if new_status not in ('test', 'online'):
      return False
    self.add_log('Changing %s status to %s:' % (site, new_status))
    if self.debug:
      self.add_log('DEBUG mode')
      return True
    now = int(time.time())
    if new_status == 'test':
      try:
        last_exclusion = Site.objects.filter(name=site)[0].getSiteOptions_for_site.filter(option_name='last_exclusion')[0].option_value
      except:
        last_exclusion = 0
      if now - last_exclusion < 21600:
        self.add_log('%s was recently auto-excluded. Skipping...' % site)
        return False

      cmd = "curl -s -k --cert $X509_USER_PROXY 'https://panda.cern.ch:25943/server/controller/query?tpmes=setmanual&queue=%s&moduser=HammerCloud&comment=HC.Blacklist.set.manual'" % site
      self.add_log('> ' + cmd)
      if not self.debug:
        self.add_log(commands.getoutput(cmd))
      cmd = "curl -s -k --cert $X509_USER_PROXY 'https://panda.cern.ch:25943/server/controller/query?tpmes=set%s&queue=%s&moduser=HammerCloud&comment=HC.Blacklist.set.%s'" % (new_status, site, new_status)
      self.add_log('> ' + cmd)
      if not self.debug:
        self.add_log(commands.getoutput(cmd))
      if new_status == 'test':
        try:
          option = Site.objects.filter(name=site)[0].getSiteOptions_for_site.filter(option_name='last_exclusion')[0]
          option.option_value = now
        except:
          option = SiteOption()
          option.option_name = 'last_exclusion'
          option.option_value = now
          option.site = Site.objects.get(name=site)
        option.save()

      Client.PandaSites = Client.getSiteSpecs(SITETYPE)[1]
      if not self.debug and Client.PandaSites[site]['status'] != new_status:
        self.store_log('Error setting %s to %s' % (site, new_status), 'error')
        return False
      return True

  def check_in_templates(self, sites):
    result = ([], [])
    for site in sites:
      if TemplateSite.objects.filter(template__id__in=self.templates).filter(site__name=site).count() == len(self.templates):
        result[0].append(site)
      else:
        self.add_reason(site, 'Missing from some templates.')
        result[1].append(site)
    return result

  def get_sites(self, status='online'):
    os = []
    ignore_sites = map(lambda x: x.site.name, SiteOption.objects.filter(option_name='autoexclusion').filter(option_value='disable'))
    if not self.once:
      self.store_log("Sites disabled from autoexclusion: %s"%(', '.join(ignore_sites),))
      self.once = True
    for s in Client.PandaSites.keys():
      if Client.PandaSites[s]['status'] == status and not re.search('test', s, re.I) and not re.search('local', s, re.I) and s not in ignore_sites:
        if status == 'test':
          if Client.PandaSites[s]['comment'] in ('HC.Blacklist.set.test', 'HC.Blacklist.set.manual', 'HC.Test.Me'):
            os.append(s)
        else:
          os.append(s)
    return os

  def get_running_test(self):
    """Sets the list of tests to process."""
    self.runningTests = Test.objects.filter(template__in=self.templates).exclude(state='error').order_by('-id').only('id')[:len(self.templates) * 2]

  def add_log(self, msg):
    self.log += '\n' + msg + '\n'
    #if self.debug:
    print '\n' + msg + '\n'

  def store_log(self, msg, category='other'):
    self.add_log(msg)
    TestLog(test=self.runningTests[0], comment=msg, severity=category, user=1).save()

  def log_reasons(self, sites):
    for site in sites:
      s = '%s (%s):' % (site, Client.PandaSites[site]['status'])
      s += '\n    %s\n' % ('\n'.join(self.reasons.get(site, '')))
      self.store_log(s, 'warning')

  def site_has_no_jobs(self, site):
    for t in self.templates:
      self.sitesNeedingJobs[t].append(site)

  def site_needs_jobs(self, site):
    for t in self.templates:
      if site in self.sitesNeedingJobs[t]:
        self.add_reason(site, 'Needs jobs in template %d' % t)
        return True
    return False

  def add_reason(self, site, reason):
    if self.reasons.get(site, None):
      self.reasons[site].append(reason)
    else:
      self.reasons[site] = [reason]
    TestLog(test=self.runningTests[0], comment='%s: %s' % (site, reason), severity='warning', user=1).save()

  def send_cloud_online_alert(self, site):
    try:
      cloud_support = Site.objects.filter(name=site)[0].cloud.getCloudOptions_for_cloud.only('option_value').filter(option_name='contact')[0].option_value
    except:
      self.add_reason(site, 'WARNING: could no get CloudOptions for site %s' % site)
      cloud_support = self.dan

    self.add_log('Sending auto-inclusion notice to %s cloud support.' % site)

    to = cloud_support + ',' + self.daops
    if self.debug:
        to = self.dan
    subject = "[HammerCloud] %s reset online at %s CET" % (site, time.ctime())
    if self.debug:
        subject += ' DEBUG'
    body = "Dear %s,\n\n" % cloud_support
    body += "%s is passing the HC test jobs and was automatically set online." % site
    body += "\n\n"
    body += "Cheers, ATLAS Distributed Analysis Operations\n"
    body += "\n\n"
    body += "Report generated on voatlas49 by /data/hammercloud/atlas/cronjobs/hc-blacklist.sh\n"

    cernmail.send(to, subject, body)

  def send_cloud_alert(self, site):
    try:
      cloud_support = Site.objects.filter(name=site)[0].cloud.getCloudOptions_for_cloud.only('option_value').filter(option_name='contact')[0].option_value
    except:
      self.add_reason(site, 'WARNING: could no get CloudOptions for site %s' % site)
      cloud_support = self.dan

    self.add_log('Sending exclusion notice to %s cloud support.' % site)

    to = cloud_support + ',' + self.daops
    if self.debug:
        to = self.dan
    subject = "[HammerCloud] %s Auto-Excluded at %s CET" % (site, time.ctime())
    if self.debug:
        subject += ' DEBUG'
    body = "Dear %s,\n\n" % cloud_support
    body += "%s has been automatically excluded from PanDA distributed production because it " % site
    body += "has failed the recent HC test jobs. You can see the exclusion policy at [1].\n\nEXCLUSION REASON:\n"
    body += "    "
    body += '\n'.join(self.reasons[site])
    body += "\n\n"
    body += "All recent test jobs can be viewed here:\n\n"
    body += "http://panda.cern.ch/server/pandamon/query?job=*&site=%s&type=ptest&hours=4&processingType=gangarobot-pft\n" % site
    body += "\n"
    body += "The queue status of %s is currently test.\n" % site
    body += "\n"
    body += "Please coordinate the necessary fixes. HC will reset the queue online when the jobs are succeeding. "
    body += "\n"
    body += "If you wish to disable this auto-exclusion service from changing %s, then please follow the instructions at [1].\n" % site
    body += "\n"
    body += "Cheers, ATLAS Distributed Analysis Operations\n"
    body += "\n"
    body += "[1] https://twiki.cern.ch/twiki/bin/view/IT/HammerCloud#APPENDIX_2_ATLAS_Automatic_Site\n"
    body += "\n\n"
    body += "Report generated on voatlas49 by /data/hc/apps/atlas/python/scripts/server/production_blacklist.py\n"

    cernmail.send(to, subject, body)

  def send_alert(self):
    if not self.log:
        return
    to = self.daexp
    subject = "[HammerCloud] Production Blacklisting Report at %s CET" % time.ctime()
    if self.debug:
        to = self.dan
        subject += ' DEBUG'
    body = "%s\n\n\nReport generated on voatlas49 by HammerCloud ATLAS blacklisting service." % self.log
    cernmail.send(to, subject, body)


if __name__ == '__main__':
  ProductionBlacklist().run(debug=True, test=False)
