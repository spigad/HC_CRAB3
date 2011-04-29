from API.Models.HCModels import TestHCModel

import pickle

class Client:
    
    def submitTest(self,dic):
        
      msg = ''
      
      if not dic.has_key('obj'):
        msg = '[ERROR][submitTest] No "obj" key.'    
        
      if not isinstance(dic['obj'],TestHCModel):
        msg = '[ERROR][submitTest] No TestHCModel object, %s instead'%dic['obj'].__class__      
    
      if msg:
        return (0,msg)
    
      test_dic = dic['obj'].objToDict()
    
      try:
        dump = pickle.dumps(test_dic,pickle.HIGHEST_PROTOCOL)
      except pickle.PickleError, e:
        msg = '[ERROR][submitTest] %s'%e
        return (0,msg)
      except Exception, e:
        msg = '[ERROR][submitTest] %s'%e
        return (0,msg)
    
      print dump
      
      return (1,dump)
    
    def parseDic(self,dic):
        
      KEYS    = ['action','obj']
      ACTIONS = {'submitTest':self.submitTest}
    
      queryStr = ''
      status   = 0

      #Check if there are wrong actions in the list
      key_actions = filter(lambda x:x not in KEYS,[key for key in dic.keys()])
      if key_actions:
        queryStr = '[ERROR] Wrong dic key(s): %s'%(key_actions)
      elif not dic.has_key('action'):
        queryStr = '[ERROR] Missing action.' 
      elif dic['action'] not in ACTIONS.keys():
        queryStr = '[ERROR] Wrong action: %s'%(dic['action'])
    
      if queryStr:
        return (status,queryStr)

      return ACTIONS[dic['action']](dic)    
    
    
    def submit(self,app,dic):
        
      status,output = self.parseDic(dic)    

      if status:
          
        exit_code, message = 1,2 # doSubmission

      return output