import simplejson, urllib2

class SchedConfig(object):
    def __init__(self):
        self.url = "http://pandaserver.cern.ch:25080/cache/schedconfig/schedconfig.all.json"
        self.json = None
        self.siteids = []
        self.queues = []
        self.bysiteid = {}
        self.byqueue = None
        self.load()
        self.make_bysiteid()

    def load(self):
        retries = 5
        while not self.queues:
            try:
                self.json = urllib2.urlopen(self.url).read()
                self.byqueue = simplejson.loads(self.json)
                self.queues = self.byqueue.keys()
            except ValueError:
                if retries:
                    sleep(1)
                    retries -= 1
                else:
                    raise Exception('error loading json from %s' % self.url)

    def make_bysiteid(self):
        for (queue,config) in self.byqueue.iteritems():
            siteid = config['siteid']
            if siteid not in self.siteids:
                self.siteids.append(siteid)

            try:
                self.bysiteid[siteid]['queues'][queue] = config
            except KeyError:
                self.bysiteid[siteid] = {}
                self.bysiteid[siteid]['queues'] = {}
                self.bysiteid[siteid]['queues'][queue] = config

    def get_queues_from_siteid(self, siteid, status = None, comments = None):
        queues = []
        if comments == None:
            comments = ()
        for q, config in self.bysiteid[siteid]['queues'].iteritems():
            if status and status != config['status']:
                continue
            try:
                if comments and config['comment'] not in comments:
                    continue
            except KeyError:
                if comments and config['comment_'] not in comments:
                    continue
            queues.append(q)
        return tuple(queues)
