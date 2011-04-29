from lib.alarms.default_alarms import DefaultAlarms
from lib.alarms.alarm import Alarm

class AppAlarms(DefaultAlarms):

  def __init__(self):
    super(AppAlarms,self).__init__()
    self.alarm3 = Alarm('3>1')

