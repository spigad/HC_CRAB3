from lib.alarms.alarm import Alarm

class DefaultAlarms(object):

  def __init__(self):
    self.default1 = Alarm('abs(gmean_allcronmetrics - smean_allcronmetrics) > 2*gstdv_allcronmetrics')
    self.default2 = Alarm('gmax_allcronmetrics < 2000')
