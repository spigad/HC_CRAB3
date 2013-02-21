#!/usr/bin/env python

import datetime
import MySQLdb
import os.path
import urllib2

class SLSSensor(object):

  INSTANCES = ('ATLAS', 'CMS', 'LHCb')

  URLs = {'main': 'http://hammercloud.cern.ch/hc/',
          'ATLAS': 'http://hammercloud.cern.ch/hc/app/atlas/',
          'CMS': 'http://hammercloud.cern.ch/hc/app/cms/',
          'LHCb': 'http://hammercloud.cern.ch/hc/app/lhcb/',
          'voatlas159': 'http://voatlas159.cern.ch/',
          }

  DBs = {'core': ('dbodhccore.cern.ch', 5510, 'gangarbt', 'VIrz2Gs8-0', 'dev_core', 4),
         'ATLAS': ('dbodhcatlas.cern.ch', 5500, 'gangarbt', 'VIrz2Gs8-0', 'dev_atlas', 4),
         'CMS': ('dbodhccms.cern.ch', 5500, 'gangarbt', 'VIrz2Gs8-0', 'dev_cms', 4),
         'LHCb': ('dbodhclhcb.cern.ch', 5501, 'gangarbt', 'VIrz2Gs8-0', 'dev_lhcb', 4),
         }

  INPUT_DIR = '/data/hc/web/templates/sls/'

  OUTPUT_DIR = '/data/hc/sls/output/'

  def connect(self, db_info):
    """Creates a connection to a database."""
    return  MySQLdb.connect(host=db_info[0],
                            user=db_info[2],
                            passwd=db_info[3],
                            db=db_info[4],
                            port=db_info[1])

  def check_db(self, db_info):
    """Checks the MySQL db is is up."""
    try:
        c = self.connect(db_info)
        c.close()
        return True
    except MySQLdb.Error:
        return False

  def check_url(self, url):
    """Checks the HTTP status code of a given URL."""
    try:
        page = urllib2.urlopen(url)
        if page.code / 100 == 2:
            return True
        else:
            return False
    except:
        return False

  def replace_in_file(self, input_path, output_path, subs):
    """Replaces the subs pairs and writes to output."""
    template = open(input_path)
    output = open(output_path, 'w')
    for l in template.xreadlines():
        for k, v in subs.iteritems():
            l = l.replace(k, str(v))
        output.write(l)
    output.close()
    template.close()

  def get_autoexclusions(self):
    """Gets the number of tests running for a given instance."""
    try:
        conn = self.connect(self.DBs['ATLAS'])
        curs = conn.cursor()
        curs.execute(r"""SELECT COUNT(*)
                           FROM test_incidence
                          WHERE comment LIKE '%will be set to brokeroff%'
                                AND comment NOT LIKE '%by an external tool or user%'
                                AND mtime >= DATE_SUB(NOW(), INTERVAL 1 DAY);""")
        exclusions = curs.fetchone()[0]
        conn.close()
        return exclusions
    except MySQLdb.Error:
        return 0

  def get_tests_running(self, instance):
    """Gets the number of tests running for a given instance."""
    try:
        conn = self.connect(self.DBs[instance])
        curs = conn.cursor()
        curs.execute(r"select count(*) from test where state = 'running';")
        total = curs.fetchone()[0]
        if DBs[instance][5] == 4:
            curs.execute(r"select count(*) from test as t inner join template as tt on t.template = tt.id and t.state = 'running' and tt.category = 'functional';")
        else:
            curs.execute(r"select count(*) from test as t inner join test_template as tt on t.test_template = tt.id and t.state = 'running' and tt.category = 'functional';")
        functional = curs.fetchone()[0]
        if DBs[instance][5] == 4:
            curs.execute(r"select count(*) from test as t inner join template as tt on t.template = tt.id and t.state = 'running' and tt.category = 'stress';")
        else:
            curs.execute(r"select count(*) from test as t inner join test_template as tt on t.test_template = tt.id and t.state = 'running' and tt.category = 'stress';")
        stress = curs.fetchone()[0]
        conn.close()
        return (total, functional, stress)
    except MySQLdb.Error:
        return (0, 0, 0)
    except:
        return (0, 0, 0)

  def get_website_statuses(self):
    """Returns the list of sites and statuses."""
    return [(service, self.check_url(url)) for service, url in self.URLs.iteritems()]

  def get_database_statuses(self):
    """Returns the list of sites and web_stats."""
    return [(service, self.check_db(db)) for service, db in self.DBs.iteritems()]

  def get_up(self, stats, instance=None):
    """Returns the number of elements up."""
    def count(x, y):
        if y[1] and (instance is None or instance == y[0]):
            return x+1
        return x
    return reduce(count, stats, 0)

  def get_availability(self, web_stats, db_stats, instance=None):
    """Returns the availability value for the service."""
    def count(x, y):
        if instance is None or instance == y:
            return x+1
        return x
    try:
        return (self.get_up(web_stats, instance) + self.get_up(db_stats, instance)) * 100 / reduce(count, self.URLs.keys() + self.DBs.keys(), 0)
    except:
        return 0.0

  def generate_instance_accounting(self, instance, web_stats, db_stats):
    """Generates the XML file for the accounting ingotmation for a given instance."""
    (total, functional, stress) = self.get_tests_running(instance)
    subs = {'###DAY###': datetime.date.today().isoformat(),
            '###WEBSITES_TARGET###': 1,
            '###WEBSITES_UP###': self.get_up(web_stats, instance),
            '###DBS_TARGET###': 1,
            '###DBS_UP###': self.get_up(db_stats, instance),
            '###TOTAL_RUNNING###': total,
            '###FUNCTIONAL_RUNNING###': functional,
            '###STRESS_RUNNING###': stress}
    if instance == 'ATLAS':
        subs['###AUTOEXCLUSIONS###'] = self.get_autoexclusions()
    self.replace_in_file(os.path.join(self.INPUT_DIR, 'accounting.%s.xml' % instance.lower()),
                         os.path.join(self.OUTPUT_DIR, 'accounting.%s.xml' % instance.lower()),
                         subs)

  def generate_accounting(self, web_stats, db_stats):
    """Generates the XML file for the accounting information (KPIs)."""
    subs = {'###DAY###': datetime.date.today().isoformat(),
            '###WEBSITES_TARGET###': len(self.URLs),
            '###WEBSITES_UP###': self.get_up(web_stats),
            '###DBS_TARGET###': len(self.DBs),
            '###DBS_UP###': self.get_up(db_stats)}
    self.replace_in_file(os.path.join(self.INPUT_DIR, 'accounting.xml'),
                         os.path.join(self.OUTPUT_DIR, 'accounting.xml'),
                         subs)
    for instance in self.INSTANCES:
        self.generate_instance_accounting(instance, web_stats, db_stats)

  def generate_instance_sls(self, instance, web_stats, db_stats):
    """Generates the XML file for the SLS main update."""
    subs = {'###AVAILABILITY###': self.get_availability(web_stats, db_stats, instance),
            '###TIMESTAMP###': datetime.datetime.now().strftime('%Y-%m-%dT%H:%M:%S')}
    self.replace_in_file(os.path.join(self.INPUT_DIR, 'sls.%s.xml' % instance.lower()),
                         os.path.join(self.OUTPUT_DIR, 'sls.%s.xml' % instance.lower()),
                         subs)

  def generate_sls(self, web_stats, db_stats):
    """Generates the XML file for the SLS main update."""
    subs = {'###AVAILABILITY###': self.get_availability(web_stats, db_stats),
            '###TIMESTAMP###': datetime.datetime.now().strftime('%Y-%m-%dT%H:%M:%S')}
    self.replace_in_file(os.path.join(self.INPUT_DIR, 'sls.xml'),
                         os.path.join(self.OUTPUT_DIR, 'sls.xml'),
                         subs)
    for instance in self.INSTANCES:
        self.generate_instance_sls(instance, web_stats, db_stats)

  def run(self, app='core', dic=None):

    if app != 'core':
      print '[WARNING][%s][sls_sensor] not available at non core app.' % (app)
      return 1

    web_stats = self.get_website_statuses()
    db_stats = self.get_database_statuses()
    self.generate_sls(web_stats, db_stats)
    self.generate_accounting(web_stats, db_stats)

    return 1


if __name__ == '__main__':
  SLSSensor().run()
