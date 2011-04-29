#from API.Interface.help import help_msg
#from API.Interface.translator import Translator
#from API.query.xhrQuery import XhrQuery
from API.Utilities.translator import Translator
from API.Utilities.client import Client

class HammerCloud:

  """
     Main class to interact with the server side.
     
     There are getter and setter methods. Getter methods
     are xhr queries, and setter methods, well, I don't
     know yet.
  
  """
  

  def __init__(self,app):
    self.app    = app
    self.trans  = Translator()
    self.client = Client()

  def getNumberOfResults(self,test_id):   
    dic = {'action':'NumberOfResults','tests':test_id}
    return self.trans.get(self.app,dic)

  def getResults(self,test_id,detailed=False):
    dic = {'action':'Results','tests':test_id,'detailed':detailed}
    return self.trans.get(self.app,dic)

  def getResultsAtSite(self,test_id,site_name,detailed=False):
    dic = {'action':'ResultsAtSite','tests':test_id,'sites':site_name,'detailed':detailed}
    return self.trans.get(self.app,dic)

  def getTemplates(self,detailed = False):
    dic = {'action':'Templates','detailed':detailed}  
    return self.trans.get(self.app,dic)

  def submitTest(self,test):
    dic = {'action':'submitTest','obj':test}
    return self.client.submit(self.app,dic)
