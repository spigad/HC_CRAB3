from hc.core.utils.generic.class_func import custom_import

from django.core.exceptions import ObjectDoesNotExist
from django.forms.models import model_to_dict

from datetime import datetime

class XhrQueryParser:

  ##                    ##
  ## AUXILIAR FUNCTIONS ##
  ##                    ##
 
  def _getTests(self,dic,queryDict):
    
    error_msg = ''
    tests     = []

    if not queryDict['tests']:
      error_msg = "I'm waiting for your test Ids..."
    else:
      for id in queryDict['tests']:
        try:
          id = int(id)
          test = dic['Test'].objects.get(pk=id)
          tests.append(test)
        except ValueError:
          error_msg = "I'm waiting for integer test Ids..."
          tests     = []
          break
        except ObjectDoesNotExist:
          error_msg = "Test %s not found."%(id)
          tests     = []
          break
        except:
          error_msg = "An original error happened."
          tests     = []
          break 

    return (error_msg,tests)

  def _getSites(self,dic,queryDict):

    error_msg = ''
    sites     = []

    if not queryDict['sites']:
      error_msg = "I'm waiting for your site names..."
    else:
      for name in queryDict['sites']:
        try:
          name = str(name)
          site = dic['Site'].objects.get(name=name)
          sites.append(site)
        except ValueError:
          error_msg = "I'm waiting for string site names..."
          tests     = []
          break
        except ObjectDoesNotExist:
          error_msg = "Site %s not found."%(name)
          tests     = []
          break
        except:
          error_msg = "An original error happened."
          tests     = []
          break

    return (error_msg,sites)


  def _getFields(self,dic,queryDict):

    fields     = ['id','site','ganga_status','start_time','submit_time','stop_time','backendID']
    exclude    = []

    if queryDict['detailed'] and queryDict['detailed'] == '1':
      fields     = []
      exclude    = ['mtime']

    timefields = []
    for rfield in dic['Result']._meta.fields:
      if rfield.__class__.__name__ == 'DateTimeField':
        timefields += [rfield.name]
    
    return (fields,exclude,timefields)

  def _getTemplateFields(self,dic,queryDict):

    fields     = ['id','category','description']
    exclude    = []

    if queryDict['detailed'] and queryDict['detailed'] == '1':
      fields   = ['id','category','description']
      exclude  = ['metricperm','lifetime','active','output_dataset']  

    return (fields,exclude)

  ##             ##
  ## XHR ACTIONS ##
  ##             ##

  def _templates(self,dic,queryDict):
      
    fields,exclude = self._getTemplateFields(dic, queryDict)  
      
    tmpls = dic['Template'].objects.all()    
    
    templates = [ model_to_dict(v,fields=fields,exclude=exclude) for v in tmpls ]   
    
    for template in templates:
        
      if queryDict['detailed'] and queryDict['detailed'] == '1':
          
        tmpl                    = dic['Template'].objects.get(pk=template['id'])
        template['usercode']    = tmpl.usercode.path
        template['jobtemplate'] = tmpl.jobtemplate.path
        template['gangabin']    = tmpl.gangabin.path
        template['optionfile']  = tmpl.optionfile.path
        template['inputtype']   = tmpl.inputtype.type
        template['testoption']  = tmpl.testoption.name                     

    return {'templates':templates}

  def _number_of_results(self,dic,queryDict):
    error_msg,tests = self._getTests(dic,queryDict)

    data = {}
    for test in tests:
      value = test.getResults_for_test.count()
      data[test.id] = {'number_of_results':value}

    return 1 and error_msg or data

  def _results(self,dic,queryDict):

    error_msg,tests = self._getTests(dic,queryDict)

    fields,exclude,timefields = self._getFields(dic,queryDict)

    data = {}
    for test in tests:
      values = test.getResults_for_test.all()
      values = [ model_to_dict(v,fields=fields,exclude=exclude) for v in values]
      for value in values:
        try:
          value['site'] = dic['Site'].objects.get(pk=value['site']).name
        except:
          pass
        for tf in timefields:
          if value.has_key(tf) and type(value[tf]) == datetime:
            value[tf] = value[tf].isoformat()

      data[test.id] = {'results':values}

    return 1 and error_msg or data


  def _results_at_site(self,dic,queryDict):
    error_msg,tests = self._getTests(dic,queryDict)
    error_msg,sites = self._getSites(dic,queryDict)

    fields,exclude,timefields = self._getFields(dic,queryDict)

    data = {}
    for test in tests:

      values = {}
      for site in sites:
        
        results = test.getResults_for_test.filter(site=site)
        results = [ model_to_dict(r,fields=fields,exclude=exclude) for r in results]

        for result in results:
          result['site'] = site.name
          for tf in timefields:
            if result.has_key(tf) and type(result[tf]) == datetime:
              result[tf] = result[tf].isoformat()

        values[site.name] = results

      data[test.id] = {'results_at_site':values}     
    return 1 and error_msg or data


  ##        ##
  ## PARSER ##
  ##        ##

  def parse(self,request,app):
    
    ACTIONS = {'number_of_results':self._number_of_results,
               'results':self._results,
               'results_at_site':self._results_at_site,
               'templates':self._templates}

    dic = {'Test'     :custom_import('hc.'+app+'.models.Test'),
           'Site'     :custom_import('hc.'+app+'.models.Site'),
           'Result'   :custom_import('hc.'+app+'.models.Result'),
           'Template' :custom_import('hc.'+app+'.models.Template')}

    error_msg = ''

    if request.method == 'GET':

      queryDict = {}

      queryDict['action']   = request.GET.get('action','')
      queryDict['detailed'] = request.GET.get('detailed','')
      queryDict['tests']    = request.GET.getlist('test')
      queryDict['sites']    = request.GET.getlist('site')

      if not queryDict['action']:
        error_msg = 'Missing action.'
      elif queryDict['action'] not in ACTIONS.keys():
        error_msg = 'Wrong action %s.'%(queryDict['action'])

    else:
      error_msg = 'Expected a GET request.'

    if error_msg:
      data = error_msg
    else:
      data = ACTIONS[queryDict['action']](dic,queryDict)

    return data
