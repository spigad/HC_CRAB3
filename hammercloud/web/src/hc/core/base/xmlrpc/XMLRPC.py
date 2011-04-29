# Patchless XMLRPC Service for Django
# Kind of hacky, and stolen from Crast on irc.freenode.net:#django
# Self documents as well, so if you call it from outside of an XML-RPC Client
# it tells you about itself and its methods
#
# Brendan W. McAdams <brendan.mcadams@thewintergrp.com>

# SimpleXMLRPCDispatcher lets us register xml-rpc calls w/o
# running a full XMLRPC Server.  It's up to us to dispatch data

from SimpleXMLRPCServer import SimpleXMLRPCDispatcher
from django.http import HttpResponse
from django.contrib.csrf.middleware import csrf_exempt

from hc.core.utils.generic.class_func import custom_import
from django.conf import settings
from django.forms.models import model_to_dict

from datetime import datetime,timedelta

# Create a Dispatcher; this handles the calls and translates info to function maps
#dispatcher = SimpleXMLRPCDispatcher() # Python 2.4
dispatcher = SimpleXMLRPCDispatcher(allow_none=True, encoding=None) # Python 2.5
 
@csrf_exempt
def rpc_handler(request):
        """
        the actual handler:
        if you setup your urls.py properly, all calls to the xml-rpc service
        should be routed through here.
        If post data is defined, it assumes it's XML-RPC and tries to process as such
        Empty post assumes you're viewing from a browser and tells you about the service.
        """


        if len(request.POST):
                response = HttpResponse(mimetype="application/xml")
                response.write(dispatcher._marshaled_dispatch(request.raw_post_data))
        else:
                response = HttpResponse()
                response.write("<b>This is an XML-RPC Service.</b><br>")
                response.write("You need to invoke it using an XML-RPC Client!<br>")
                response.write("The following methods are available:<ul>")
                methods = dispatcher.system_listMethods()

                for method in methods:
                        # right now, my version of SimpleXMLRPCDispatcher always
                        # returns "signatures not supported"... :(
                        # but, in an ideal world it will tell users what args are expected
                        sig = dispatcher.system_methodSignature(method)

                        # this just reads your docblock, so fill it in!
                        help =  dispatcher.system_methodHelp(method)

                        response.write("<li><b>%s</b>: [%s] %s" % (method, sig, help))

                response.write("</ul>")
                response.write('<a href="http://www.djangoproject.com/"> <img src="http://media.djangoproject.com/img/badges/djangomade124x25_grey.gif" border="0" alt="Made with Django." title="Made with Django."></a>')

        response['Content-length'] = str(len(response.content))
        return response

def createTest(testReq):
        """
        Create a test. Argument is a dictionary of the form:
        Returns the test ID.
        """

        if not isinstance(testReq,dict):
          return (False,{'type':'FORMAT','response':'expecting a dictionary'})

        if not testReq.has_key('app'):
          return (False,{'type':'MISSING','response':'missing app key'})

        app = testReq['app']
        PLUGINS = [ a.split('.')[1] for a in settings.INSTALLED_APPS if a.startswith('hc') and not 'core' in a]
        
        if app not in PLUGINS:
            return (False,{'type':'UNKNOWN','response':'app %s not available'%(testReq['app'])})

        Test = custom_import("hc.%s.models.Test"%app)
        TestSite = custom_import("hc.%s.models.TestSite"%app)
        Template = custom_import("hc.%s.models.Template"%app)
        Site = custom_import("hc.%s.models.Site"%app)

        if not testReq.has_key('template'):
          return (False,{'type':'MISSING','response':'missing template key'})

        try:
            template = Template.objects.get(pk=testReq['template'])
        except:
            return (False,{'type':'UNKNOWN','response':'exception getting template %s'%(testReq['template'])})

        # TODO validate the temaplte

        # get the sites
        siteObjs = []

        if not testReq.has_key('sites'):
          return (False,{'type':'MISSING','response':'missing sites key'})

        if not len(testReq['sites']):
          return (False,{'type':'MISSING','response':'no sites'})
          
        for s in testReq['sites']:

            if not isinstance(s,dict):
              return (False,{'type':'FORMAT','response':'Wrong site format.'})

            if not s.has_key('name'):
              return (False,{'type':'FORMAT','response':'Wrong sites format.'})

            site = Site.objects.filter(name=s['name'])
            if not site:
              return (False,{'type':'UNKNOWN','response':'site %s not valid'%s['name']})
            siteObjs.append(site[0])
   
        if not testReq.has_key('duration'):
          return (False,{'type':'MISSING','response':'missing duration key'})

        if not isinstance(testReq['duration'],int):
          return (False,{'type':'MISSING','response':'wrong duration format'})

        if not testReq.has_key('description'):
          return (False,{'type':'MISSING','response':'missing description key'})

        starttime = datetime.now()

        if testReq.has_key('starttime'):

#          starttime = testReq['starttime']         
#
#          if isinstance(starttime,str):
#            if not isinstance(starttime,str):
#              return (False,{'type':'FORMAT','response':'Wrong datetime format'})
#              return (False,{'type':'FORMAT','response':'%s' % starttime.__class__.__name__}) 
#            else:
          try:
            starttime = datetime.strptime(testReq['starttime'],'%Y-%m-%d %H:%M:%S')
          except:
            return (False,{'type':'FORMAT','response':'Wrong datetime format, conversion error'})              

          if starttime < datetime.now() - timedelta( minutes = 5 ):
            return (False,{'type':'FORMAT','response':'Starttime more than 5 min in the past'})


        # create the test
        try:
            test = Test(
                starttime=starttime,
                endtime=starttime+timedelta(seconds=testReq['duration']),
                description=testReq['description'],
                template=template,
                state='tobescheduled'
            )
            test.save()
        except:
            return (False,{'type':'UNKNOWN','response':'error saving test'})

        for site in siteObjs:
            ts = TestSite(test=test,site=site)
            ts.save()

        return (True,{'response':{'id':test.id,'status':test.state,'starttime':test.starttime.strftime('%Y-%m-%d %H:%M:%S'),'endtime':test.endtime.strftime('%Y-%m-%d %H:%M:%S')}})

def getTemplates(templReq):

  """
    Given an app, returns a list of templates.
  """

  if not isinstance(templReq,dict):
    return (False,{'type':'FORMAT','response':'expecting a dictionary'})

  if not templReq.has_key('app'):
    return (False,{'type':'MISSING','response':'missing app key'})

  app = templReq['app']
  PLUGINS = [ a.split('.')[1] for a in settings.INSTALLED_APPS if a.startswith('hc') and not 'core' in a]

  if app not in PLUGINS:
    return (False,{'type':'UNKNOWN','response':'app %s not available'%(templReq['app'])})

  Template = custom_import("hc.%s.models.Template"%app)
  
  templates = Template.objects.all()

  fields  = ['id','category','description']
  exclude = []

  if templReq.has_key('detailed') and templReq['detailed'] == 1:
  #  fields   = ['id','category','description']
    exclude  = ['metricperm','lifetime','active','output_dataset']  

  templates = [ model_to_dict(t,fields=fields,exclude=exclude) for t in templates ]

  return (True,{'response':{'templates':templates}})

def getTest(testReq):

  """
    Given an app and a testID, returns basic test information.
  """

  if not isinstance(testReq,dict):
    return (False,{'type':'FORMAT','response':'expecting a dictionary'})

  if not testReq.has_key('app'):
    return (False,{'type':'MISSING','response':'missing app key'})

  app = testReq['app']
  PLUGINS = [ a.split('.')[1] for a in settings.INSTALLED_APPS if a.startswith('hc') and not 'core' in a]

  if app not in PLUGINS:
    return (False,{'type':'UNKNOWN','response':'app %s not available'%(testReq['app'])})

  Test = custom_import("hc.%s.models.Test"%app)

  if not testReq.has_key('test'):
    return (False,{'type':'MISSING','response':'missing test key'})

  if not isinstance(testReq['test'],int):
    return (False,{'response':'Test id must be int.'})

  try:
    test = Test.objects.get(pk=testReq['test'])
  except:
    return (False,{'type':'UNKNOWN','response':'Error importing test'})

  test_sites = test.getTestSites_for_test.all()
  sites = ','.join([ts.site.name for ts in test_sites])

  dic = {
         'id':test.id,
         'description':test.description,
         'starttime':test.starttime.strftime('%Y-%m-%d %H:%M:%S'),
         'endtime':test.endtime.strftime('%Y-%m-%d %H:%M:%S'),
         'state':test.state,
         'site':sites,
         'template':test.template.__unicode__()

  }

  return (True,{'response':{'test':dic}})
  

def getResults(resReq):

  """
    Given an app and a testID, returns all results.
  """

  if not isinstance(resReq,dict):
    return (False,{'type':'FORMAT','response':'expecting a dictionary.'})

  if not resReq.has_key('app'):
    return (False,{'type':'MISSING','response':'missing app key'})

  app = resReq['app']
  PLUGINS = [ a.split('.')[1] for a in settings.INSTALLED_APPS if a.startswith('hc') and not 'core' in a]

  if app not in PLUGINS:
    return (False,{'type':'UNKNOWN','response':'app %s not available'%(resReq['app'])})

  Test     = custom_import("hc.%s.models.Test"%app)
  Template = custom_import("hc.%s.models.Template"%app)
  Result   = custom_import("hc.%s.models.Result"%app)
  Site     = custom_import("hc.%s.models.Site"%app)

  if not resReq.has_key('test'):
    return (False,{'type':'MISSING','response':'missing test key'})

  if not isinstance(resReq['test'],int):
    return (False,{'type':'FORMAT','response':'Test id must be int.'})

  try:
    test = Test.objects.get(pk=resReq['test'])
  except:
    return (False,{'type':'UNKNOWN','response':'Error importing test'})

  fields     = ['id','site','ganga_status','start_time','submit_time','stop_time','backendID']
  exclude    = []

  if resReq.has_key('detailed') and resReq['detailed'] == 1:
    fields     = []
    exclude    = ['mtime']
  
  timefields = []
  for rfield in Result._meta.fields:
    if rfield.__class__.__name__ == 'DateTimeField':
      timefields += [rfield.name]

  results = test.getResults_for_test.all()
  results = [ model_to_dict(r,fields=fields,exclude=exclude) for r in results]

  for result in results:
    try:
      result['site'] = Site.objects.get(pk=result['site']).name
    except:
      return (False,{'type':'UNKNOWN','response':'Error getting result site name'})
    for tf in timefields:
      if result.has_key(tf) and type(result[tf]) == datetime:
        result[tf] = result[tf].strftime('%Y-%m-%d %H:%M:%S')

  return (True,{'response':{'results':results}})  

def getSummarizedResults(sumReq):

  """
    Given an app and a test id, returns summarized results.
  """

  if not isinstance(sumReq,dict):
    return (False,{'type':'FORMAT','response':'expecting a dictionary.'})

  if not sumReq.has_key('app'):
    return (False,{'type':'MISSING','response':'missing app key'})

  app = sumReq['app']
  PLUGINS = [ a.split('.')[1] for a in settings.INSTALLED_APPS if a.startswith('hc') and not 'core' in a]

  if app not in PLUGINS:
    return (False,{'type':'UNKNOWN','response':'app %s not available'%(sumReq['app'])})

  Test        = custom_import("hc.%s.models.Test"%app)
  SummaryTest = custom_import("hc.%s.models.SummaryTest"%app)

  if not sumReq.has_key('test'):
    return (False,{'type':'FORMAT','response':'missing test key'})

  if not isinstance(sumReq['test'],int):
    return (False,{'type':'FORMAT','response':'Test id must be int.'})

  try:
    test = Test.objects.get(pk=sumReq['test'])
  except:
    return (False,{'type':'UNKNOWN','response':'Error importing test'})

  fields     = ['id','sites','clouds','submitted','running','completed','failed','total']
  exclude    = []

  if sumReq.has_key('detailed') and sumReq['detailed'] == 1:
    fields     = []
    exclude    = ['mtime','test']

  timefields = []
  for rfield in SummaryTest._meta.fields:
    if rfield.__class__.__name__ == 'DateTimeField':
      timefields += [rfield.name]

  summaries = test.getSummaryTests_for_test.all()
  summaries = [ model_to_dict(s,fields=fields,exclude=exclude) for s in summaries]

  for summary in summaries:
#    try:
#      summary['test'] = Te.objects.get(pk=result['site']).name
#    except:
#      return (False,{'response':'Error getting result site name'})
    for tf in timefields:
      if summary.has_key(tf) and type(summary[tf]) == datetime:
        summary[tf] = summary[tf].strftime('%Y-%m-%d %H:%M:%S')

  return (True,{'response':{'summary':summaries}})

  


# you have to manually register all functions that are xml-rpc-able with the dispatcher
# the dispatcher then maps the args down.
# The first argument is the actual method, the second is what to call it from the XML-RPC side...
dispatcher.register_function(createTest,           'createTest')
dispatcher.register_function(getTemplates,         'getTemplates')
dispatcher.register_function(getResults,           'getResults')
dispatcher.register_function(getSummarizedResults, 'getSummarizedResults')
dispatcher.register_function(getTest,              'getTest')
