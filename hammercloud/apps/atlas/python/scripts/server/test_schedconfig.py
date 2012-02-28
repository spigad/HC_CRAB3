from schedconfig import SchedConfig
import unittest

class TestSchedConfig(unittest.TestCase):

    def setUp(self):
        self.schedconfig = SchedConfig()

    def test_queues(self):
        # make sure schedconfig.queues is a list of queues
        queue_a = self.schedconfig.queues[0]
        assert('-' in queue_a)

        for q in self.schedconfig.byqueue:
            assert(q in self.schedconfig.queues)

    def test_siteids(self):
        for q,config in self.schedconfig.byqueue.iteritems():
            assert(config['siteid'] in self.schedconfig.siteids)

    def test_byqueue(self):
        queue_a = self.schedconfig.queues[0]
        siteid_a = self.schedconfig.byqueue[queue_a]['siteid']

    def test_bysiteid(self):
        queue_a = self.schedconfig.queues[0]
        siteid_a = self.schedconfig.byqueue[queue_a]['siteid']
        assert(queue_a in self.schedconfig.bysiteid[siteid_a]['queues'].keys())
        assert(siteid_a == self.schedconfig.bysiteid[siteid_a]['queues'][queue_a]['siteid'])

    def test_hcworkflow(self):
        queue_a = self.schedconfig.queues[0]
        siteid_a = self.schedconfig.byqueue[queue_a]['siteid']
        print siteid_a
        print self.schedconfig.get_queues_from_siteid(siteid_a,'online')
        print self.schedconfig.get_queues_from_siteid(siteid_a,'test',('HC.Test.Me','HC.Blacklist.set.test'))
        print self.schedconfig.get_queues_from_siteid('DESY-HH','online')
        print self.schedconfig.get_queues_from_siteid('DESY-HH','test',('HC.Test.Me','HC.Blacklist.set.test'))

if __name__ == '__main__':
    unittest.main()

