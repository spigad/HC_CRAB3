#from API.query.xhrQuery import XhrQuery
from API.Utilities.xhrQuery import XhrQuery
import types

class Translator:

  def number_of_results(self,dic):

    msg = ''

    if not dic.has_key('tests'):
      msg = '[ERROR][number_of_results] No "tests" key.'
    elif not dic['tests']:
      msg = '[ERROR][number_of_results] Empty tests.'
    
    if type(dic['tests']) == types.IntType:
      dic['tests'] = [dic['tests']]

    if filter(lambda x:type(x) != types.IntType,dic['tests']):
      msg = '[ERROR][number_of_results] Non integer id(s).'      

    if msg:
      return (0,msg)
    else:
      concat = '&test='
      action = '?action=number_of_results' 
      queryStr = action+concat+concat.join([str(t_id) for t_id in dic['tests']])

      if dic.has_key('detailed') and dic['detailed'] == True:
        queryStr += '&detailed=1'

      return (1,queryStr)

  def results(self,dic):

    msg = ''

    if not dic.has_key('tests'):
      msg = '[ERROR][results] No "tests" key.'
    elif not dic['tests']:
      msg = '[ERROR][results] Empty tests.'

    if type(dic['tests']) == types.IntType:
      dic['tests'] = [dic['tests']]

    if filter(lambda x:type(x) != types.IntType,dic['tests']):
      msg = '[ERROR][results] Non integer id(s).'

    if msg:
      return (0,msg)
    else:
      concat = '&test='
      action = '?action=results'
      queryStr = action+concat+concat.join([str(t_id) for t_id in dic['tests']])
      return (1,queryStr)

  def templates(self,dic):
      
    queryStr = '?action=templates'    

    if dic.has_key('detailed') and dic['detailed'] == True:
      queryStr += '&detailed=1'
      
    return (1,queryStr)       

  def results_at_site(self,dic):
    msg = ''

    if not dic.has_key('tests'):
      msg = '[ERROR][results_at_site] No "tests" key.'
    elif not dic['tests']:
      msg = '[ERROR][results_at_site] Empty tests.'

    if type(dic['tests']) == types.IntType:
      dic['tests'] = [dic['tests']]

    if filter(lambda x:type(x) != types.IntType,dic['tests']):
      msg = '[ERROR][results_at_site] Non integer id(s).'

    if not dic.has_key('sites'):
      msg = '[ERROR][results_at_site] No "sites" key.'
    elif not dic['sites']:
      msg = '[ERROR][results_at_site] Empty sites.'

    if type(dic['sites']) == types.StringType:
      dic['sites'] = [dic['sites']]
    elif type(dic['sites']) == types.ListType:
      if filter(lambda x:type(x) != types.StringType,dic['sites']):
        msg = '[ERROR][results_at_site] Non string site names.'
    else:
      msg = '[ERROR][results_at_site] No string or list of strings'

    if msg:
      return (0,msg)
    else:
      concat1 = '&test='
      concat2 = '&site='
      action = '?action=results_at_site'
      queryStr = action+concat1+concat1.join([str(t_id) for t_id in dic['tests']])+concat2+concat2.join([site for site in dic['sites']])

      if dic.has_key('detailed') and dic['detailed'] == True:
        queryStr += '&detailed=1'

      return (1,queryStr)


  def parseDic(self,dic):

    KEYS    = ['action','tests','sites','detailed']
    ACTIONS = {'NumberOfResults':self.number_of_results,
               'Results':self.results,
               'ResultsAtSite':self.results_at_site,
               'Templates':self.templates}

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

  def get(self,app,dic):

    status,output = self.parseDic(dic)

    if status:
      exit_code,expression = XhrQuery().get(app,output)
      if exit_code:
        output = eval(expression)
      else:  
        output = expression    

    return output
