from django.http import HttpResponse,HttpResponseRedirect,Http404
from django.template import Context, loader, RequestContext

from django.shortcuts import get_object_or_404,render_to_response

from hc.core.utils.hc.datahelper import Datahelper
from hc.core.utils.hc.stats import Stats

from hc.core.base.forms import forms

from hc.core.base.views.json.records import get_records
from django.db.models import Min,Max,Count,Q
from django.forms.models import modelformset_factory
from django.core.cache import cache
from django.core.paginator import Paginator, InvalidPage, EmptyPage
from django.core.urlresolvers import reverse
from django.conf import settings

from hc.core.utils.generic.class_func import custom_import
from hc.core.utils.generic.dic_config import DicConfig
from hc.core.base.models.managers.functions import test_fm

from datetime import date,timedelta,datetime

from hc.core.base.views import configuration

import dateutil.parser,re,time

#######################################################
## DEFAULT CONTEXT
#######################################################

def defaultContext(request):

  request_path = request.path

  app = request_path.split('app/')[1].split('/')[0]
  if request_path.find('admin')>-1:
    request_path = reverse('index-view')

  config = configuration.PARTICULARITIES[app]

  c = DicConfig(config)

  return {'app':app, 'user':request.user, 'request_path':request_path,'config':c}

#######################################################
## LOGIN VIEWS
#######################################################

#def logout(request):
#  logout_user(request)
#  next = request.GET.get('next', None)
#  if next:
#    return HttpResponseRedirect(next)
#  else:
#    raise Http404

class GenericView():

#######################################################
## INDEX BLOCK
#######################################################

  def index(self,request,dic={'Test':None},*args,**kwargs):

    test = dic['Test']
    app  = test.__module__.split('.')[1]

    stress, functional = [], []

    stress +=  test.objects.jobs('running'    ,'stress'     ,1)
    stress +=  test.objects.jobs('running'    ,'stress'     ,0)
    stress +=  test.objects.jobs('running'    ,'functional' ,0)
    stress +=  test.objects.jobs('submitting' ,'stress'     ,1)
    stress +=  test.objects.jobs('submitting' ,'stress'     ,0)
    stress +=  test.objects.jobs('submitting' ,'functional' ,0)
    stress +=  test.objects.jobs('scheduled'  ,'stress'     ,1)
    stress +=  test.objects.jobs('scheduled'  ,'stress'     ,0)
    stress +=  test.objects.jobs('scheduled'  ,'functional' ,0)
             
    
    functional +=  test.objects.jobs('running'    ,'functional' ,1) 
    functional +=  test.objects.jobs('submitting' ,'functional' ,1) 
    functional +=  test.objects.jobs('scheduled'  ,'functional' ,1)
                 

    dh         = Datahelper()
    stress     = dh.annotateTests(stress)
    functional = dh.annotateTests(functional)

    tests = {'stress':stress,'functional':functional}

    t = loader.select_template(['%s/index.html'%(app),'core/app/index.html'])
    c = RequestContext(request,
                       {'tests':tests},
                       [defaultContext]
                       )
    return HttpResponse(t.render(c))


#######################################################
## BACKENDS BLOCK
#######################################################

  def backends(self,request,dic={'Backend':None},*args,**kwargs):

    backend = dic['Backend']
    app     = backend.__module__.split('.')[1]

    try:
      backends = backend.objects.all()
    except:
      raise Http404

    t = loader.select_template(['%s/more/backends.html'%(app),'core/app/more/backends.html'])
    c = RequestContext(request,
                       {'backends': backends},
                       [defaultContext]
                      )
    return HttpResponse(t.render(c))


#######################################################
## CLOUDS BLOCK
#######################################################

  def clouds(self,request,dic={'Cloud':None},*args,**kwargs):

    cloud = dic['Cloud']
    app   = cloud.__module__.split('.')[1]

    try:
      clouds = cloud.objects.all().order_by('code') 
    except:
      raise Http404

    t = loader.select_template(['%s/more/clouds.html'%(app),'core/app/more/clouds.html'])
    c = RequestContext(request,
                       {'clouds': clouds},
                       [defaultContext]
                      )
    return HttpResponse(t.render(c))

  def cloud(self,request,cloud_id,dic={'Cloud':None},*args,**kwargs):

    cloud = dic['Cloud']
    app   = cloud.__module__.split('.')[1]

    try:
      cloud = cloud.objects.get(pk=cloud_id)
    except:
      raise Http404

    cloud.charts = []
    cloud.sites = cloud.getSites_for_cloud.all()
   
    t = loader.select_template(['%s/more/cloud.html'%(app),'core/app/more/cloud.html'])
    c = RequestContext(request,
                       {'cloud': cloud},
                       [defaultContext]
                      )
    return HttpResponse(t.render(c))


#######################################################
## DSPATTERNS BLOCK
#######################################################

  def dspatterns(self,request,dic={'Dspattern':None},*args,**kwargs):

    dspattern = dic['Dspattern']
    app       = dspattern.__module__.split('.')[1]

    try:
      dspatterns = dspattern.objects.all()
    except:
      raise Http404

    t = loader.select_template(['%s/more/dspatterns.html'%(app),'core/app/more/dspatterns.html'])
    c = RequestContext(request,
                       {'dspatterns': dspatterns},
                       [defaultContext]
                      )
    return HttpResponse(t.render(c))


#######################################################
## HOSTS BLOCK
#######################################################

  def hosts(self,request,dic={'Host':None},*args,**kwargs):

    host = dic['Host']
    app  = host.__module__.split('.')[1]

    try:
      hosts = host.objects.all()
    except:
      raise Http404

    t = loader.select_template(['%s/more/hosts.html'%(app),'core/app/more/hosts.html'])
    c = RequestContext(request,
                       {'hosts': hosts},
                       [defaultContext]
                      )
    return HttpResponse(t.render(c))

  def host(self,request,host_id,dic={'Host':None},*args,**kwargs):

    host = dic['Host']
    app  = host.__module__.split('.')[1]

    try:
      host = host.objects.get(pk=host_id)
    except:
      raise Http404

    t = loader.select_template(['%s/more/host.html'%(app),'core/app/more/host.html'])
    c = RequestContext(request,
                       {'host': host},
                       [defaultContext]
                      )
    return HttpResponse(t.render(c))

#######################################################
## JOBTEMPLATES BLOCK
#######################################################

  def jobtemplates(self,request,dic={'JobTemplate':None},*args,**kwargs):

    jobtemplate = dic['JobTemplate']
    app         = jobtemplate.__module__.split('.')[1]

    try:
      jobtemplates = jobtemplate.objects.all()
    except:
      raise Http404

    t = loader.select_template(['%s/more/jobtemplates.html'%(app),'core/app/more/jobtemplates.html'])
    c = RequestContext(request,
                       {'jobtemplates': jobtemplates},
                       [defaultContext]
                      )
    return HttpResponse(t.render(c))

#######################################################
## METRICS BLOCK
#######################################################

  def metric_types(self,request,dic={'MetricType':None},*args,**kwargs):

    metric_type = dic['MetricType']
    app         = metric_type.__module__.split('.')[1]

    try:
      metric_types = metric_type.objects.all()
    except:
      raise Http404

    t = loader.select_template(['%s/more/metric_types.html'%(app),'core/app/more/metric_types.html'])
    c = RequestContext(request,
                       {'metric_types': metric_types},
                       [defaultContext]
                      )
    return HttpResponse(t.render(c))

  def metric_type(self,request,metric_type_id,dic={'MetricType':None},*args,**kwargs):

    metric_type = dic['MetricType']
    app         = metric_type.__module__.split('.')[1]

    try:
      metric_type = metric_type.objects.get(pk=metric_type_id)
    except:
      raise Http404

    t = loader.select_template(['%s/more/metric_type.html'%(app),'core/app/more/metric_type.html'])
    c = RequestContext(request,
                       {'metric_type': metric_type},
                       [defaultContext]
                      )
    return HttpResponse(t.render(c))

  def metric_permissions(self,request,dic={'MetricPerm':None},*args,**kwargs):

    metric_permission = dic['MetricPerm']
    app               = metric_permission.__module__.split('.')[1]

    try:
      metric_permissions = metric_permission.objects.all()
    except:
      raise Http404

    t = loader.select_template(['%s/more/metric_permissions.html'%(app),'core/app/more/metric_permissions.html'])
    c = RequestContext(request,
                       {'metric_permissions': metric_permissions},
                       [defaultContext]
                      )
    return HttpResponse(t.render(c))


#######################################################
## MORE BLOCK
#######################################################

  def more(self,request,dic={'Test':None},*args,**kwargs):

    test = dic['Test']
    app  = test.__module__.split('.')[1]

    t = loader.select_template(['%s/more/more.html'%(app),'core/app/more/more.html'])
    c = RequestContext(request,
                       {},
                       [defaultContext]
                      )
    return HttpResponse(t.render(c))



#######################################################
## OPTIONFILES BLOCK
#######################################################

  def optionfiles(self,request,dic={'OptionFile':None},*args,**kwargs):

    optionfile = dic['OptionFile']
    app        = optionfile.__module__.split('.')[1]

    try:
      optionfiles = optionfile.objects.all()
    except:
      raise Http404

    t = loader.select_template(['%s/more/optionfiles.html'%(app),'core/app/more/optionfiles.html'])
    c = RequestContext(request,
                       {'optionfiles': optionfiles},
                       [defaultContext]
                      )
    return HttpResponse(t.render(c))


#######################################################
## SITES BLOCK
#######################################################

  def sites(self,request,dic={'Site':None},*args,**kwargs):

    site = dic['Site']
    app  = site.__module__.split('.')[1]

    try:
      sites = site.objects.all()
    except:
      raise Http404
 
    t = loader.select_template(['%s/more/sites.html'%(app),'core/app/more/sites.html'])
    c = RequestContext(request,
                      {'sites': sites},
                      [defaultContext]
                      )
    return HttpResponse(t.render(c))

  def site(self,request,site_id,dic={'Site':None},*args,**kwargs):

    app = dic['Site'].__module__.split('.')[1]

    try:
      site = dic['Site'].objects.get(pk=site_id)
    except:
      raise Http404

    site.charts = []
   
    t = loader.select_template(['%s/more/site.html'%(app),'core/app/more/site.html'])
    c = RequestContext(request,
                       {'site': site},
                       [defaultContext]
                       )
    return HttpResponse(t.render(c))


#######################################################
## TEMPLATES BLOCK
#######################################################

  def templates(self,request,dic={'Template':None},*args,**kwargs):

    template = dic['Template']
    app      = template.__module__.split('.')[1]

    try:
      templates = template.objects.all()
    except:
      raise Http404

    t = loader.select_template(['%s/more/templates.html'%(app),'core/app/more/templates.html'])
    c = RequestContext(request,
                       {'templates': templates},
                       [defaultContext]
                      )
    return HttpResponse(t.render(c))   

  def template(self,request,template_id,dic={'Template':None},*args,**kwargs):

    template = dic['Template']
    app      = template.__module__.split('.')[1]

    try:
      template = template.objects.get(pk=template_id)
    except:
      raise Http404

    template.hosts      = template.getTemplateHosts_for_template.all()
    template.sites      = template.getTemplateSites_for_template.all()
    template.dspatterns = template.getTemplateDspatterns_for_template.all()

    t = loader.select_template(['%s/more/template.html'%(app),'core/app/more/template.html'])
    c = RequestContext(request,
                       {'template': template},
                       [defaultContext]
                      )
    return HttpResponse(t.render(c))


#######################################################
## TESTOPTIONS BLOCK
#######################################################

  def testoptions(self,request,dic={'TestOption':None},*args,**kwargs):

    testoption = dic['TestOption']
    app        = testoption.__module__.split('.')[1]

    try:
      testoptions = testoption.objects.all()
    except:
      raise Http404

    t = loader.select_template(['%s/more/testoptions.html'%(app),'core/app/more/testoptions.html'])
    c = RequestContext(request,
                       {'testoptions': testoptions},
                       [defaultContext]
                      )
    return HttpResponse(t.render(c))


#######################################################
## USERCODES BLOCK
#######################################################

  def usercodes(self,request,dic={'UserCode':None},*args,**kwargs):

    usercode = dic['UserCode']
    app      = usercode.__module__.split('.')[1]

    try:
      usercodes = usercode.objects.all()
    except:
      raise Http404

    t = loader.select_template(['%s/more/usercodes.html'%(app),'core/app/more/usercodes.html'])
    c = RequestContext(request,
                       {'usercodes': usercodes},
                       [defaultContext]
                      )
    return HttpResponse(t.render(c))


#######################################################
## TESTS BLOCK
#######################################################


  def test(self,request,test_id,dic={'Test':None},*args,**kwargs):

    test = dic['Test']
    app  = test.__module__.split('.')[1]

    test = get_object_or_404(test,pk=test_id)
    dh         = Datahelper()
    test = dh.annotateTest(test)

    metricperms = test.metricperm.index.all()

    summary = ''
    if test.getSummaryTests_for_test.count():
      summary = test.getSummaryTests_for_test.all()[0]  

    #Independently of the number of metrics selected on the MetricPerm.index,
    #for the test main page only the 3 first ones are selected.

    test_metrics = test.getTestMetrics_for_test.filter(metric__metric_type__in=metricperms)[:3]

    patterns = test.getTestDspatterns_for_test.all()

    t = loader.select_template(['%s/test/test.html'%(app),'core/app/test/test.html'])
    c = RequestContext(request,
                      {'test': test,'test_metrics':test_metrics,'summary':summary,'patterns':patterns},
                      [defaultContext] 
                    )
    return HttpResponse(t.render(c))

  def testclone(self,request,test_id,dic={'Test':None},*args,**kwargs):

    test = dic['Test']
    app  = test.__module__.split('.')[1]

    test = get_object_or_404(test,pk=test_id)

    error = None

    if not(request.user.is_superuser or request.user.is_staff or request.user.groups.filter(name__endswith='admin').filter(name__startswith=app)):
      error = "You are not allowed to clone this test!"

    if request.method == 'POST':

      if request.POST.has_key('Test'):

        queryset = get_object_or_404(dic['Test'],pk=request.POST['Test'])
        from hc.core.base.admin.actions import clone

        new_obj_id = clone.view_method(self, request, queryset)
        if new_obj_id:
          next = reverse('portal-view')
          return HttpResponseRedirect(next+'admin/%s/test/%s'%(app,new_obj_id))  
        else:
          error = 'Internal error.'


      else:
        error = 'Mal formated form.'     

    t = loader.select_template(['%s/test/testclone.html'%(app),'core/app/test/testclone.html'])
    c = RequestContext(request,
                       {'test': test, 'error': error },
                       [defaultContext])
    return HttpResponse(t.render(c))

  def testmodify(self,request,test_id,dic={'Test':None,'TestLog':None},*args,**kwargs):

    test = dic['Test']
    app  = test.__module__.split('.')[1]

    testlog = dic['TestLog']

    test = get_object_or_404(test,pk=test_id)
    usernames = [tu.user for tu in test.getTestUsers_for_test.all()]

    error,done,message,form,formset = None,0,'',None,None

    if not(request.user.is_superuser or request.user.username in usernames or request.user.groups.filter(name__endswith='admin').filter(name__startswith=app)):
      error = "You are not allowed to modify this test!"

    else:

      form = custom_import('hc.core.base.forms.forms.TestRunningModifyForm')(app)

      TestSite = custom_import('hc.'+app+'.models.TestSite')

      if request.method == 'POST':  

        TestSiteFormSet = modelformset_factory(TestSite,
                             fields=('num_datasets_per_bulk', 'min_queue_depth', 'max_running_jobs', 'resubmit_enabled', 'resubmit_force'),
                             extra=0)
        form = form(request.POST, instance=test)
        formset = TestSiteFormSet(request.POST,
                                  queryset=TestSite.objects.filter(test=test.id))

#        if not form.cleaned_data,has_key('pause'):
#          form.cleaned_data['pause'] == 'off'

        if form.is_valid() and formset.is_valid():

          values  = form.cleaned_data  
          comment = 'Test modifications: '           

          for change in form.changed_data:
            comment += '%s -> %s, '%(change,values[change])

          if comment != 'Test modifications: ':
            testlog = testlog(test=test,comment=comment,user=request.user.username)
            testlog.save()

          form.save()
          formset.save()
          message = 'Test modified!'

          done = 1
        else:
          message = 'Correct data!'
          TestSiteFormSet = modelformset_factory(TestSite,
                               fields=('site','num_datasets_per_bulk', 'min_queue_depth', 'max_running_jobs', 'resubmit_enabled', 'resubmit_force'),
                               extra=0)
          formset = TestSiteFormSet(queryset=TestSite.objects.filter(test=test_id))

      else:
      
        form = form(instance=test)

        TestSiteFormSet = modelformset_factory(TestSite,
                             fields=('site','num_datasets_per_bulk', 'min_queue_depth', 'max_running_jobs', 'resubmit_enabled', 'resubmit_force'),
                             extra=0)
        formset = TestSiteFormSet(queryset=TestSite.objects.filter(test=test.id))

    t = loader.select_template(['%s/test/testmodify.html'%(app),'core/app/test/testmodify.html'])
    c = RequestContext(request,
                       {'test': test, 'user': request.user, 'form':form, 'formset':formset, 'error':error, 'done':done, 'message':message },
                       [defaultContext])
    return HttpResponse(t.render(c))


  def testlist(self,request,list_type,dic={'Test':None},*args,**kwargs):

    test = dic['Test']
    app  = test.__module__.split('.')[1]

    if not list_type in  ['all','functional','stress','scheduled','submitting','error','running','completed']:
        raise Http404

    list_type = 'testlist'+str(list_type)
    help = True

    #Here there is no customization allowed.
    return render_to_response('core/app/test/testlist.html', locals(), context_instance = RequestContext(request, {}, [defaultContext]))


#######################################################
## AJAX BLOCK
#######################################################

  def get_list(self,request,type,id,filter,dic={'SummaryTest':None,'SummaryTestSite':None,'SummaryRobot':None,'Result':None},*args,**kwargs):

    summary_test = dic['SummaryTest']
    app          = summary_test.__module__.split('.')[1]

    summary_test_site = dic['SummaryTestSite']
    summary_robot     = dic['SummaryRobot']
    result            = dic['Result']

    searchableColumns = {}
    jsonTemplatePath = 'core/app/json/'

    if type == 'testsites':
      querySet = summary_test_site.objects.filter(test__id=id)
      columnIndexNameMap = {0:'test_site__site__name',1:'submitted',2:'running',3:'completed',4:'failed',5:'c_cf',6:'total',7:'test_site__num_datasets_per_bulk',8:'test_site__min_queue_depth',9:'test_site__max_running_jobs',10:'test_site__resubmit_enabled',11:'test_site__resubmit_force',12:'test_site__site__name'}
      jsonTemplatePath += 'testsites.txt'

    elif type == 'testsummary':
      querySet = summary_test_site.objects.select_related('site', 'test_site', 'test_site__site', 'test__metricperm', 'test__metricperm__summary').filter(test__id=id)
      metr = querySet[0].test.metricperm.summary.all()
      columnIndexNameMap = {0:'test_site__site__name'} 
      for i in xrange(0,len(metr)):
        metric = metr[i].name
        columnIndexNameMap[i+1] = metr[i].name
        searchableColumns[metr[i].name] = metr[i].name

      jsonTemplatePath = str(app)+'/json/'+str(querySet[0].test.metricperm.name)+'.txt'

    elif type.startswith('testlist'):

      mode = type.replace('testlist','')
      if mode == 'all':
        querySet = summary_test.objects.all()
      elif mode in ['functional','stress']:
        querySet = summary_test.objects.filter(test__template__category=mode)
      elif mode in ['scheduled','submitting','error','running','completed']:
        querySet = summary_test.objects.filter(test__state=mode)
      else:
        raise Http404

      columnIndexNameMap = {0:'test__id',1:'test__state',2:'test__host__name',3:'clouds',4:'test__template__id',5:'test__inputtype',6:'test__starttime',7:'test__endtime',8:'nr_sites',9:'total',10:'test__id'}

      jsonTemplatePath += 'testlist.txt'

    elif type == 'robotlist':
#      yesterday = date.today()-timedelta(1)

      day = request.GET.get('day','day')
      if not bool(re.compile(r'[^0-9-]').search(day)):
        day = datetime(*time.strptime(day, "%Y-%m-%d")[0:5])
      else:
        day = date.today()-timedelta(1)

#      querySet = summary_robot.objects.filter(day=yesterday)
      querySet = summary_robot.objects.filter(day=day)
      columnIndexNameMap = {0:'site__name',1:'completed',2:'failed',3:'total',4:'efficiency',5:'efficiencyNorm',6:'errorrate',7:'errorrateNorm'}
      jsonTemplatePath += 'robotlist.txt'

    elif type == 'testjobs':
      querySet = result.objects.filter(test__id=id).exclude(ganga_subjobid=1000000)
      if filter is not None:
        try:
          site_id = int(filter)
          if site_id > 0: 
            querySet = querySet.filter(site__id=filter)
        except:
          pass
      columnIndexNameMap = {0:'ganga_status',1:'site__name',2:'ganga_jobid',3:'ganga_subjobid',4:'backendID',5:'submit_time',6:'start_time',7:'stop_time',8:'reason'}
      jsonTemplatePath += 'testjobs.txt'

    elif type == 'robotjobs':
      #      yesterday = date.today()-timedelta(1)

      day = request.GET.get('day','day')
      if not bool(re.compile(r'[^0-9-]').search(day)):
        day = datetime(*time.strptime(day, "%Y-%m-%d")[0:5])
      else:
        day = date.today()-timedelta(1)

      querySet = result.objects.filter(mtime__gt=day).filter(mtime__lt=day+timedelta(days=1)).filter(test__template__category='functional').exclude(ganga_subjobid=1000000)
      columnIndexNameMap = {0:'ganga_status',1:'site__name',2:'test__id',3:'ganga_jobid',4:'ganga_subjobid',5:'backendID',6:'submit_time',7:'start_time',8:'stop_time',9:'reason'}

      jsonTemplatePath += 'robotjobs.txt'

    elif type == 'testreasons':
      querySet = result.objects.filter(test__id=id).filter(ganga_status='f').exclude(ganga_subjobid=1000000)
      columnIndexNameMap = {0:'reason',1:'site__name'}
      jsonTemplatePath += 'testreasons.txt'

    else:
      raise Http404

    return get_records(request, querySet, columnIndexNameMap, searchableColumns, jsonTemplatePath, type, app)


  def testaccordion(self,request,test_id,type,dic={'Test':None},*args,**kwargs):

    test = dic['Test']
    app  = test.__module__.split('.')[1]

    ACCORDION = ['testsites','testsummary','testbackend','testapplication','testreasons','testcompleted','teststdouterr']
    list = False

    if not type in ACCORDION:
      raise Http404

    test = get_object_or_404(test,pk=test_id)
    page = type

    items = []
    if type == 'testsummary':
      page = test.metricperm.name

    elif type == 'testreasons':
      page = 'testreasons'

    t = loader.select_template(['%s/ajax/%s.html'%(app,page),'core/app/ajax/%s.html'%(page)])
    c = Context({'test_id': test_id,'list':list,'type':type,'items':items,'app':app,'MEDIA_URL':settings.MEDIA_URL})
    return HttpResponse(t.render(c))

  def ajaxtestmetricsbysite(self,request,test_id,dic={'Test':None},*args,**kwargs):

    test = dic['Test']
    app  = test.__module__.split('.')[1]

    test = get_object_or_404(test,pk=test_id)
    #logs = test.getTestLogs_for_test.all()

    plots = test.getSiteMetrics_for_test.all()
  
    t = loader.select_template(['%s/testmetricsbysite.html'%(app),'core/app/testmetricsbysite.html'])
    c = Context({'plots':plots,'app':app,'test':test})
    return HttpResponse(t.render(c))

  def ajaxtestjobs(self,request,test_id,site_id,dic={'Test':None,'Site':None},*args,**kwargs):

    test = dic['Test']
    site = dic['Site']
    app  = test.__module__.split('.')[1]

    test = get_object_or_404(test,pk=test_id)
    try:
      site_id = int(site_id)
      site = site.objects.get(id=site_id)
    except:
      site = None
      site_id = 0
    type = 'testjobs'

    t = loader.select_template(['%s/test/testjobs.html'%(app),'core/app/test/testjobs.html'])
    c = Context({'app':app,'test':test,'site':site_id,'type':type, 'MEDIA_URL':settings.MEDIA_URL})
    return HttpResponse(t.render(c))

  def ajaxtestevolution(self,request,test_id,dic={'Test':None},*args,**kwargs):

    test = dic['Test']
    app  = test.__module__.split('.')[1]

    test  = get_object_or_404(test,pk=test_id)

    evolution = {}
    evolution['Overall'] = test.getTestMetrics_for_test.filter(metric__metric_type__name__in=['evol_sr','evol_cf'])
    for ts in test.getTestSites_for_test.all():
      evolution[ts.site.name] = ts.site.getSiteMetrics_for_site.filter(test=ts.test).filter(metric__metric_type__name__in=['evol_sr','evol_cf'])

    for k,v in evolution.items():
      if not v:
        del evolution[k]

    t = loader.select_template(['%s/test/testevolution.html'%(app),'core/app/test/testevolution.html'])
    c = Context({'app':app,'test':test,'evolution':evolution})
    return HttpResponse(t.render(c))

  def ajaxtestalarms(self,request,test_id,dic={'Test':None},*args,**kwargs):

    test = dic['Test']
    app  = test.__module__.split('.')[1]

    test = get_object_or_404(test,pk=test_id)
    alarms = test.getTestSiteAlarms_for_test.all()
    for ta in alarms:
      logs = []
      if ta.log:
        logs = eval(ta.log)
      ta.log = logs

    t = loader.select_template(['%s/test/testalarms.html'%(app),'core/app/test/testalarms.html'])
    c = Context({'tas':alarms,'app':app,'test':test,'MEDIA_URL':settings.MEDIA_URL})
    return HttpResponse(t.render(c))

  def ajaxtestlogs(self,request,test_id,dic={'Test':None},*args,**kwargs):

    test = dic['Test']
    app  = test.__module__.split('.')[1]

    test = get_object_or_404(test,pk=test_id)
    logs = test.getTestLogs_for_test.all().order_by('-mtime')
    
    t = loader.select_template(['%s/test/testlogs.html'%(app),'core/app/test/testlogs.html'])
    c = Context({'logs':logs,'app':app,'test':test})
    return HttpResponse(t.render(c))

  def ajaxtestlogreport(self,request,test_id,dic={'Test':None,'TestLog':None},*args,**kwargs):

    test    = dic['Test']
    testlog = dic['TestLog']
    app     = test.__module__.split('.')[1]

    test = get_object_or_404(test,pk=test_id)

    usernames = [tu.user for tu in test.getTestUsers_for_test.all()]

    form = ''
    done = 0
    error = ''
 
    if not(request.user.is_superuser or request.user in usernames or request.user.groups.filter(name__endswith='admin').filter(name__startswith=app)):
        error = "You are not allowed to report incidences in this test."
    
    else:

      done = 0      

      testlog = testlog(test=test)

      form = custom_import('hc.core.base.forms.forms.TestLogReportForm')(app)
      if request.method == 'POST':
        form = form(request.POST,instance=testlog)
 
        if form.is_valid():
          log      = form.save(commit=False)
#          log.test = test
          log.user = request.user.username
          log.save()
          done = 1
      else:
        form = form(instance=testlog)     
 
    t = loader.select_template(['%s/test/testlogreport.html'%(app),'core/app/test/testlogreport.html'])
    c = RequestContext(request,
                       {'test': test, 'form':form,'done':done,'error':error},
                       [defaultContext])
    return HttpResponse(t.render(c))

  def ajaxtestsites(self,request,test_id,dic={'Test':None},*args,**kwargs):

    test = dic['Test']
    app  = test.__module__.split('.')[1]

    test = get_object_or_404(test,pk=test_id)

    dh   = Datahelper()
    test = dh.annotateTestPerSite(test)

    t = loader.select_template(['%s/test/testsites.html'%(app),'core/app/test/testsites.html'])
    c = Context({'test': test})
    return HttpResponse(t.render(c))

  def ajaxtestmetrics(self,request,test_id,dic={'Test':None},*args,**kwargs):

    test = dic['Test']
    app  = test.__module__.split('.')[1]
    
    test = get_object_or_404(test,pk=test_id)

    dh   = Datahelper()
    test = dh.annotateTestPerMetric(test)

    t = loader.select_template(['%s/test/testmetrics.html'%(app),'core/app/test/testmetrics.html'])
    c = Context({'test': test})
    return HttpResponse(t.render(c))


#######################################################
## ROBOT BLOCK
#######################################################

  def robot(self,request,dic={'Site':None,'SiteOption':None,'Cloud':None,'Backend':None},*args,**kwargs):

    site = dic['Site']
    siteoption = dic['SiteOption']
    app  = site.__module__.split('.')[1]
  
    sites    = list(site.objects.filter(enabled=True).exclude(id__in=map(lambda x: x.site_id, siteoption.objects.filter(option_name='autoexclusion').filter(option_value='disable'))))
    cloud    = dic['Cloud']
    clouds   = list(cloud.objects.exclude(code__contains='ALL').exclude(name__contains='TEST'))
    backend  = dic['Backend']
    backends = list(backend.objects.all())

    dh = Datahelper()

    day = request.GET.get('day','day')
    if not bool(re.compile(r'[^0-9-]').search(day)):
      day = datetime(*time.strptime(day, "%Y-%m-%d")[0:5])
    else:
      day = date.today()
      #FIXME: This is not generic!
      if app != 'atlas':
        day = date.today()-timedelta(1)

    sites = dh.annotateSitesEfficiency(sites,day,app)

    t = loader.select_template(['%s/robot/robot.html'%(app),'core/app/robot/robot.html'])
    c = RequestContext(request,
                      {'sites': sites,'clouds':clouds,'backends':backends,'day':day},
                      [defaultContext]
                    )
    return HttpResponse(t.render(c))

  def robotsite(self,request,site_id,dic={'Site':None},*args,**kwargs):

    site = dic['Site']
    app  = site.__module__.split('.')[1]

    site = get_object_or_404(site,pk=site_id)

#    day = date.today()-timedelta(1)

    day = request.GET.get('day','day')
    if not bool(re.compile(r'[^0-9-]').search(day)):
      day = datetime(*time.strptime(day, "%Y-%m-%d")[0:5])
    else:
      day = date.today()-timedelta(1)

    summary = site.getSummaryRobots_for_site.filter(day=day)
    if summary:
      summary = summary[0]

    t = loader.select_template(['%s/robot/robotsite.html'%(app),'core/app/robot/robotsite.html'])
    c = RequestContext(request,
                      {'site': site,'day':day,'summary':summary},
                      [defaultContext]
                    )
    return HttpResponse(t.render(c))

  def robotlist(self,request,dic={'SummaryRobot':None},*args,**kwargs):

    sr   = dic['SummaryRobot']
    app  = sr.__module__.split('.')[1]

#    day = date.today()-timedelta(1)

    day = request.GET.get('day','day')
    if not bool(re.compile(r'[^0-9-]').search(day)):
      day = datetime(*time.strptime(day, "%Y-%m-%d")[0:5])
    else:
      day = date.today()-timedelta(1)

    srs = sr.objects.filter(day=day)

    t = loader.select_template(['%s/robot/robotlist.html'%(app),'core/app/robot/robotlist.html'])
    c = RequestContext(request,
                      {'srs': srs,'day':day},
                      [defaultContext]
                    )
    return HttpResponse(t.render(c))

  def robotstats(self,request,dic={'SummaryRobot':None},*args,**kwargs):

    sr   = dic['SummaryRobot']
    app  = sr.__module__.split('.')[1]

#    day = date.today()-timedelta(1)

    day = request.GET.get('day','day')
    if not bool(re.compile(r'[^0-9-]').search(day)):
      day = datetime(*time.strptime(day, "%Y-%m-%d")[0:5])
    else:
      day = date.today()-timedelta(1)

    srs = sr.objects.filter(day=day)

    urls = []

    from hc.core.utils.plots.charts import hist,pie

    efficiency     = [sr.efficiency*100 for sr in srs if sr.efficiency > -1]
    urls += [hist(efficiency,20,day,'Efficiency')]

    efficiencynorm     = [sr.efficiencyNorm for sr in srs if sr.efficiencyNorm > -1]
    urls += [hist(efficiencynorm,20,day,'Efficiency(Norm)')]

    errorrate     = [sr.errorrate*100 for sr in srs if sr.errorrate > -1]
    urls += [hist(errorrate,20,day,'Errorrate')]

    errorratenorm = [sr.errorrateNorm for sr in srs if sr.errorrateNorm > -1]
    urls += [hist(errorratenorm,20,day,'Error Rate(Norm)')]

    completed = [sr.completed for sr in srs if sr.efficiency > -1]
    urls += [hist(completed,20,day,'Completed')]

    failed = [sr.failed for sr in srs if sr.efficiency > -1]
    urls += [hist(failed,20,day,'Failed')]

    total     = [sr.total for sr in srs if sr.efficiency > -1]
    urls += [hist(total,20,day,'Total')]


    t = loader.select_template(['%s/robot/robotstats.html'%(app),'core/app/robot/robotstats.html'])
    c = RequestContext(request,
                      {'srs': srs,'day':day,'urls':urls},
                      [defaultContext]
                    )
    return HttpResponse(t.render(c))

  def robotjobs(self,request,dic={'SummaryRobot':None},*args,**kwargs):

    sr   = dic['SummaryRobot']
    app  = sr.__module__.split('.')[1]

#    day = date.today()-timedelta(1)

    day = request.GET.get('day','day')
    if not bool(re.compile(r'[^0-9-]').search(day)):
      day = datetime(*time.strptime(day, "%Y-%m-%d")[0:5])
    else:
      day = date.today()-timedelta(1)

    srs = sr.objects.filter(day=day)

    t = loader.select_template(['%s/robot/robotjobs.html'%(app),'core/app/robot/robotjobs.html'])
    c = RequestContext(request,
                      {'srs': srs,'day':day},
                      [defaultContext]
                    )
    return HttpResponse(t.render(c))

  def historical(self,request,dic={'SummaryRobot':None,'Site':None,'Cloud':None},*args,**kwargs):

    sr   = dic['SummaryRobot']
    app  = sr.__module__.split('.')[1]

    LENGTH = 50

    day_from = request.GET.get('from','day_from')
    day_to = request.GET.get('to','day_to')

    if bool(re.compile(r'[^0-9-]').search(day_from)) or bool(re.compile(r'[^0-9-]').search(day_to)):
      #Mal format
      day_to   = date.today()
      day_from = day_to - timedelta(days=LENGTH)
    else:
      day_from = datetime(*time.strptime(day_from, "%Y-%m-%d")[0:5])
      day_to   = datetime(*time.strptime(day_to, "%Y-%m-%d")[0:5]) 

      if day_to > day_from + timedelta(days=LENGTH):
        day_to = day_from + timedelta(days=LENGTH) 
      else:
        LENGTH = day_to - day_from
    
    srs = sr.objects.filter(day__gte=day_from).filter(day__lte=day_to)
    site = dic['Site']

    hists = {}
    for site in site.objects.all():
      vals = srs.filter(site=site).order_by('day')  
      hists[site.name] = vals
#      if len(vals) != LENGTH:
#        hists[site.name] = []

#    cloud = dic['Cloud']
#    clouds = cloud.objects.all()
#    for c in clouds:
#      c.sites = c.getSites_for_cloud.all()

    t = loader.select_template(['%s/robot/historical.html'%(app),'core/app/robot/historical.html'])
    c = RequestContext(request,
                      {'to':day_to,'from':day_from,'hists':hists,'length':LENGTH,'help':True},
                      [defaultContext]
                    )
    return HttpResponse(t.render(c))

  def incidents(self,request,dic={'TestLog':None,'Site':None},*args,**kwargs):

    tl   = dic['TestLog']
    si   = dic['Site']
    app  = tl.__module__.split('.')[1]

    q = request.GET.get('q', None)
    try:
        hours = int(request.GET.get('hours', ''))
    except ValueError, TypeError:
        hours = None
    try:
        page = int(request.GET.get('page', '1'))
    except ValueError:
        page = 1
    try:
        site_name = request.GET.get('site', None)
    except ValueError, TypeError:
        site_name = None
    try:
        severity = request.GET.get('severity', None)
    except ValueError, TypeError:
        severity = None
    incidents = tl.objects.get_filtered_incidents(query=q,
                                                  time=hours,
                                                  site_name=site_name,
                                                  severity=severity)
    sites = si.objects.filter(enabled=True).exclude(name__contains='DISK')
    severities = (u'white+blacklisting',)+zip(*tl.SEVERITY_CHOICES)[0]
    paginator = Paginator(list(incidents), 25)
    try:
        incident_list = paginator.page(page)
    except (EmptyPage, InvalidPage):
        incident_list = paginator.page(paginator.num_pages)
    t = loader.select_template(['%s/robot/incidents.html'%(app),'core/app/robot/incidents.html'])
    c = RequestContext(request, locals(), [defaultContext])
    return HttpResponse(t.render(c))

  def autoexclusion(self,request,dic={'SiteOption':None, 'Cloud':None, 'Site':None, 'BlacklistEvent':None},*args,**kwargs):

    so   = dic['SiteOption']
    cl   = dic['Cloud']
    si   = dic['Site']
    be   = dic['BlacklistEvent']
    app  = so.__module__.split('.')[1]

    params = {}
    if kwargs.has_key('params'):
      params = kwargs['params']

    clouds       = []
    sites        = []
    site_options = []
    message      = ''
    ext          = ''
    chart        = None
    top_month    = None
    top_week     = None
    top_month_extra = None
    top_week_extra = None

    #Autoexclusion enabled
    if params.has_key('autoexclusion'):
      try:
          cloud_id = int(request.GET.get('cloud', '0'))
      except ValueError, IndexError:
          cloud_id = None
      try:
          site_id = int(request.GET.get('site', '0'))
      except ValueError, IndexError:
          site_id = None
      site_options = so.objects.select_related().filter(**params['autoexclusion']).order_by('site__name')
      clouds = cl.objects.exclude(name__startswith='ALL')
      sites = si.objects.exclude(enabled=False)
      chart = be.objects.get_autoexclusion_chart(site=site_id, cloud=cloud_id)
      top_month = be.objects.get_top_excluded_sites(time_limit=30)
      top_week = be.objects.get_top_excluded_sites(time_limit=7)
      
      if params.has_key('extra_report'):
        extra_report = custom_import(params['extra_report'])
        if extra_report:
          top_month_extra = cache.get('%s_top_month_extra'%app)
          if not top_month_extra:
            top_month_extra = extra_report(days=30)
            cache.set('%s_top_month_extra'%app, top_month_extra, 7200)
          top_week_extra = cache.get('%s_top_week_extra'%app)
          if not top_week_extra:
            top_week_extra = extra_report(days=7)
            cache.set('%s_top_week_extra'%app, top_week_extra, 3600)
        else:
          raise RuntimeError('Could no import extra_report for %s: %s, %s' % (app, params['extra_report'], extra_report))
      
    else:
      message = 'AutoExclussion not enabled for %s.'%(app)

    t = loader.select_template(['%s/robot/autoexclusion.html'%(app),'core/app/robot/autoexclusion.html'])
    c = RequestContext(request, locals(), [defaultContext])

    return HttpResponse(t.render(c))

  def autoexclusion_set(self,request,action,sitename,dic={'Site':None,'SiteOption':None},*args,**kwargs):

    so   = dic['SiteOption']
    site = dic['Site']
    app  = so.__module__.split('.')[1]

    # ATLAS specific
    if action not in ('enable','disable'):
      raise Http404
    if not sitename.startswith('ANALY_'):
      raise Http404

    s=site.objects.filter(name=sitename)
    if not s:
      raise Http404

    site_option = so.objects.filter(option_name='autoexclusion').filter(site__name=sitename)
    if not site_option:
      so = so(site=s[0],option_name='autoexclusion',option_value=action)
    else:
        so = site_option[0]
        so.option_value=action
    so.save()

    return HttpResponse('Site %s autoexclusion %s'%(sitename,action))

#######################################################
## STATS BLOCK
#######################################################

  def evolution(self,request,dic={'Site':None,'Result':None,'Cloud':None,'Template':None,'Test':None,'SummaryEvolution':None},*args,**kwargs):

    site  = dic['Site']
    cloud = dic['Cloud'] 
    app  = site.__module__.split('.')[1]

    clouds = cloud.objects.all()
    for cloud in clouds:
      cloud.sites = cloud.getSites_for_cloud.all()

    stats = Stats()
    try:
      titles,evol,type = stats.overview_evol(request,dic)
    except:
      raise Http404

    t = loader.select_template(['%s/stats/evolution.html'%(app),'core/app/stats/evolution.html'])
    c = RequestContext(request,
                      {'titles':titles,'evol':evol,'clouds':clouds,'type':type,'help':True},
                      [defaultContext]
                    )
    return HttpResponse(t.render(c))

  def stats(self,request,dic={'Site':None,'Result':None,'Cloud':None,'Template':None,'Test':None},*args,**kwargs):

    site = dic['Site']
    app  = site.__module__.split('.')[1]

    stats = Stats()
    since,version,vsince,total,completed,completed_total,failed,failed_total,overall_url     = stats.overview_basic(dic)
    sites,clouds,max_site_per_cloud,min_site_per_cloud,sites_per_cloud,sites_url             = stats.overview_sites(dic)
    users                                                                                    = stats.overview_users(dic)
    templates,tests,max_test_per_template,min_test_per_template,tests_per_template,tests_url = stats.overview_tests(dic)


    t = loader.select_template(['%s/stats/stats.html'%(app),'core/app/stats/stats.html'])
    c = RequestContext(request,
                      locals(),
                      [defaultContext]
                    )
    return HttpResponse(t.render(c))

  def statistics(self,request,dic={'MetricType':None,'Test':None,'Site':None,'Cloud':None,'Template':None},*args,**kwargs):

    metric_type = dic['MetricType']
    app = metric_type.__module__.split('.')[1]

    stats = Stats()
    Qobjects,commands,obj,error = stats.parseQuery(request,dic)

    if not commands['go']:

      type = ''
      if commands.has_key('type'):
        type = commands['type']

      if not error:
        dialog = stats.getDialog(obj,Qobjects)
      else:
        dialog = []
      c = RequestContext(request,
                      {'dialog':dialog,'type':type,'sort_by':commands['sort_by'],'error':error},
                      [defaultContext]
                    )
    else:

      statistics = {}
      stats = Stats() 

      if commands['type'] == 'timeline':

        titles,statistics = [],[]
        if not error:
          titles,statistics,error = stats.process(Qobjects,commands)
        c = RequestContext(request,
                           {'titles':titles,'statistics':statistics,'error':error,'type':commands['type']},
                           [defaultContext]
                          )

      else:

        metrics = []
        if Qobjects.has_key('metric_type'):
          metrics = Qobjects['metric_type']

          statistics = []
          if not error:
            statistics,error = stats.process(Qobjects,commands)

        c = RequestContext(request,
                           {'statistics':statistics,'error':error,'type':commands['type'],'metrics':metrics},
                           [defaultContext]
                          )  

    t = loader.select_template(['%s/stats/statistics.html'%(app),'core/app/stats/statistics.html'])
    return HttpResponse(t.render(c))

  def joberrors(self,request,dic={'Site':None,'Result':None, 'Cloud':None},*args,**kwargs):
    site = dic['Site']
    cloud = dic['Cloud']
    result = dic['Result']
    app = site.__module__.split('.')[1]

    params = {}
    if kwargs.has_key('params'):
      params = kwargs['params']

    site_filters = Q()
    result_filters = Q()

    # Get the GET parameters for the QuerySet
    start_date = request.GET.get('start_date', None)
    if start_date:
      result_filters = result_filters & Q(mtime__gte=dateutil.parser.parse(start_date))
    end_date = request.GET.get('end_date', None)
    if end_date:
      result_filters = result_filters & Q(mtime__lte=dateutil.parser.parse(end_date))
    tests = filter(None, request.GET.getlist('test'))
    if tests:
      result_filters = result_filters & Q(test__in=tests)
    sites = filter(None, request.GET.getlist('site'))
    if sites:
      site_filters = site_filters & Q(id__in=sites)
    clouds = filter(None, request.GET.getlist('cloud'))
    if clouds:
      site_filters = site_filters & Q(cloud__id__in=clouds)
    templates = filter(None, request.GET.getlist('template'))
    if templates:
      result_filters = result_filters & Q(test__template__id__in=templates)

    sites_list = site.objects.exclude(enabled=False)
    clouds_list = cloud.objects.all()

    site_data = []
    sites_filtered = site.objects.filter(site_filters)
    results_filtered = result.objects.filter(result_filters)

    for s in sites_filtered.filter(enabled=1):
      r = results_filtered.filter(site=s)
      q = Q(ganga_status='f')
      if params.has_key('failed'):
        q = q & Q(**params['failed'])
      i = {'site': s,
           'finished': r.count(),
           'failed': r.filter(q).count(),
           'aborted': 0,
           'efficiency': 0.0}
      total_failed = r.filter(ganga_status='f').count()
      i['aborted'] = total_failed - i['failed']
      if i['finished'] > 0:
        i['efficiency'] = float(i['finished'] - total_failed) / float(i['finished'])
      site_data.append(i)

    #site_data.sort(key=lambda x: x['efficiency'], reverse=True)

    # TODO(rmedrano): Avoid passing the request by creating a custom url_with_get tag.
    get_params = request.GET.copy()
    try:
      del get_params['site']
    except KeyError:
      pass
    c = RequestContext(request, locals(), [defaultContext])
    t = loader.select_template(['%s/stats/joberrors.html'%(app),'core/app/stats/joberrors.html'])
    return HttpResponse(t.render(c))

  def abortedjobs(self,request,dic={'Site':None,'Result':None},*args,**kwargs):
    site = dic['Site']
    result = dic['Result']
    app = site.__module__.split('.')[1]

    params = {}
    if kwargs.has_key('params'):
      params = kwargs['params']

    # Get the GET parameters for the QuerySet
    result_filters = Q()
    start_date = request.GET.get('start_date', None)
    if start_date:
      result_filters = result_filters & Q(mtime__gte=dateutil.parser.parse(start_date))
    end_date = request.GET.get('end_date', None)
    if end_date:
      result_filters = result_filters & Q(mtime__lte=dateutil.parser.parse(end_date))
    tests = filter(None, request.GET.getlist('test'))
    if tests:
      result_filters = result_filters & Q(test__in=tests)
    templates = filter(None, request.GET.getlist('template'))
    if templates:
      result_filters = result_filters & Q(test__template__id__in=templates)

    site = request.GET.get('site', None)
    if not site:
      raise Http404

    site_data = []
    results_filtered = result.objects.filter(result_filters)

    site_data = results_filtered.values(params['field']).filter(site=site).annotate(jcount=Count(params['field']))

    c = RequestContext(request, {'site_data': site_data}, [defaultContext])
    t = loader.select_template(['%s/stats/abortedjobs.html'%(app),'core/app/stats/abortedjobs.html'])
    return HttpResponse(t.render(c))

  def failedjobs(self,request,dic={'Site':None,'Result':None},*args,**kwargs):
    site = dic['Site']
    result = dic['Result']
    app = site.__module__.split('.')[1]

    params = {}
    if kwargs.has_key('params'):
      params = kwargs['params']

    # Get the GET parameters for the QuerySet
    result_filters = Q()
    start_date = request.GET.get('start_date', None)
    if start_date:
      result_filters = result_filters & Q(mtime__gte=dateutil.parser.parse(start_date))
    end_date = request.GET.get('end_date', None)
    if end_date:
      result_filters = result_filters & Q(mtime__lte=dateutil.parser.parse(end_date))
    tests = filter(None, request.GET.getlist('test'))
    if tests:
      result_filters = result_filters & Q(test__in=tests)
    templates = filter(None, request.GET.getlist('template'))
    if templates:
      result_filters = result_filters & Q(test__template__id__in=templates)

    site = request.GET.get('site', None)
    if not site:
      raise Http404

    site_data = []
    results_filtered = result.objects.filter(result_filters)

    site_data = results_filtered.values(params['field']).filter(site=site).annotate(jcount=Count(params['field']))

    c = RequestContext(request, {'site_data': site_data}, [defaultContext])
    t = loader.select_template(['%s/stats/failedjobs.html'%(app),'core/app/stats/failedjobs.html'])
    return HttpResponse(t.render(c))
