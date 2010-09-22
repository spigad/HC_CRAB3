from django.contrib.auth import logout as logout_user
from django.http import HttpResponse,Http404,HttpResponseRedirect
from django.template import Context, loader, RequestContext

from django.shortcuts import get_object_or_404,render_to_response

from hc.core.utils.hc.datahelper import Datahelper

from hc.core.base.views.json.records import get_records
from django.db.models import Min,Max,Count


#######################################################
## DEFAULT CONTEXT
#######################################################

def defaultContext(request):

  request_path = request.path
  
  app = request_path.split('/')[3]
  if request_path.find('admin')>-1:
    request_path = reverse('index-view')

  return {'app':app, 'user':request.user, 'request_path':request_path}

#######################################################
## LOGIN VIEWS
#######################################################

def logout(request):
  logout_user(request)
  next = request.GET.get('next', None)
  if next:
    return HttpResponseRedirect(next)
  else:
    raise Http404

class GenericView():

#######################################################
## INDEX BLOCK
#######################################################

  def index(self,request,dic={'Test':None},*args,**kwargs):

    test = dic['Test']
    app  = test.__module__.split('.')[1]

    stress, functional = [], []

    stress +=  test.objects.jobs('running'    ,'stress'     ,1)
    stress +=  test.objects.jobs('running'    ,'functional' ,0)
    stress +=  test.objects.jobs('submitting' ,'stress'     ,1)
    stress +=  test.objects.jobs('submitting' ,'functional' ,0)
    stress +=  test.objects.jobs('scheduled'  ,'stress'     ,1)
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
## CLOUDS BLOCK
#######################################################

  def clouds(self,request,dic={'Cloud':None},*args,**kwargs):

    cloud = dic['Cloud']
    app   = cloud.__module__.split('.')[1]

#    clouds = Cloud.objects.exclude(name__startswith='ALL').order_by('code')
    try:
      clouds = cloud.objects.all().order_by('code') 
    except:
      raise Http404

    t = loader.select_template(['%s/clouds.html'%(app),'core/app/clouds.html'])
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

#    #ALL_PANDA and ALL_LCG are not displayed
#    if cloud.name.startswith('ALL'):
#      raise Http404

#    dh = HCDataHelper()
    cloud.charts = []
#    cloud.charts.append(dh.getChartUsg('running','Running Jobs',cloud_id=cloud_id))
#   cloud.charts.append(dh.getChartUsg('completed','Completed Jobs',cloud=cloud_id))
    cloud.sites = cloud.getSites_for_cloud.all()
   
    t = loader.select_template(['%s/cloud.html'%(app),'core/app/cloud.html'])
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

    t = loader.select_template(['%s/dspatterns.html'%(app),'core/app/dspatterns.html'])
    c = RequestContext(request,
                       {'dspatterns': dspatterns},
                       [defaultContext]
                      )
    return HttpResponse(t.render(c))


#######################################################
## FILES BLOCK
#######################################################

  def files(self,request,dic={'File':None},*args,**kwargs):

    file = dic['File']
    app  = file.__module__.split('.')[1]

    try:
      files = file.objects.all()
    except:
      raise Http404

    t = loader.select_template(['%s/files.html'%(app),'core/app/files.html'])
    c = RequestContext(request,
                       {'files': files},
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

    t = loader.select_template(['%s/hosts.html'%(app),'core/app/hosts.html'])
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

    t = loader.select_template(['%s/host.html'%(app),'core/app/host.html'])
    c = RequestContext(request,
                       {'host': host},
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
#    except ObjectDoesNotExist:
#      raise Http404
#    except AttributeError:
#      raise Http500
    except:
      raise Http404
 
    t = loader.select_template(['%s/sites.html'%(app),'core/app/sites.html'])
    c = RequestContext(request,
                      {'sites': sites},
                      [defaultContext]
                      )
    return HttpResponse(t.render(c))

  def site(self,request,site_id,dic={'Site':None},*args,**kwargs):

    app = dic['Site'].__module__.split('.')[1]

    try:
      site = dic['Site'].objects.get(pk=site_id)
#    except ObjectDoesNotExist:
#      raise Http404
#    except AttributeError:
#      raise Http500
    except:
      raise Http404

#    dh = HCDataHelper()
    site.charts = []
#    site.charts.append(dh.getChartUsg('running','Running Jobs',site=site_id))
#        site.charts.append(dh.getChartUsg('completed','Completed Jobs',site=site_id))
   
    t = loader.select_template(['%s/site.html'%(app),'core/app/site.html'])
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

    t = loader.select_template(['%s/templates.html'%(app),'core/app/templates.html'])
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
#    except ObjectDoesNotExist:
#      raise Http404
#    except AttributeError:
#      raise Http500
    except:
      raise Http404

    template.hosts      = template.getTemplateHosts_for_template.all()
    template.sites      = template.getTemplateSites_for_template.all()
    template.dspatterns = template.getTemplateDspatterns_for_template.all()

    t = loader.select_template(['%s/template.html'%(app),'core/app/template.html'])
    c = RequestContext(request,
                       {'template': template},
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

    metrics = test.metrics.index.all()

    summary = ''
    if test.getSummaryTests_for_test.count():
      summary = test.getSummaryTests_for_test.all()[0]  

    #Independently of the number of metrics selected on the MetricPermissions.index,
    #for the test main page only the 3 first ones are selected.

    test_metrics = test.getTestMetrics_for_test.filter(metric__metric_type__in=metrics)[:3]

    t = loader.select_template(['%s/test.html'%(app),'core/app/test.html'])
    c = RequestContext(request,
                      {'test': test,'test_metrics':test_metrics,'summary':summary},
                      [defaultContext] 
                    )
    return HttpResponse(t.render(c))

  def testlist(self,request,list_type,dic={'Test':None},*args,**kwargs):

    test = dic['Test']
    app  = test.__module__.split('.')[1]

    if not list_type in  ['all','scheduled','submitting','error','running','completed']:
        raise Http404

    list_type = 'testlist'+str(list_type)

    #Here there is no customization allowed.
    return render_to_response('core/app/testlist.html', locals(), context_instance = RequestContext(request))


#######################################################
## AJAX BLOCK
#######################################################

  def get_list(self,request,type,test_id,dic={'SummaryTest':None,'SummaryTestSite':None},*args,**kwargs):

    summary_test = dic['SummaryTest']
    app          = summary_test.__module__.split('.')[1]

    summary_test_site = dic['SummaryTestSite']

    searchableColumns = []
    jsonTemplatePath = 'core/app/json/'

    if type == 'testsites':
      querySet = summary_test_site.objects.filter(test__id=test_id)
      columnIndexNameMap = {0:'test_site__site__name',1:'submitted',2:'running',3:'completed',4:'failed',5:'test_site__num_datasets_per_bulk',6:'test_site__min_queue_depth',7:'test_site__max_running_jobs',8:'test_site__resubmit_enabled',9:'test_site__resubmit_force',10:'test_site__site__name'}
      jsonTemplatePath += 'testsites.txt'

    elif type == 'testsummary':
      querySet = summary_test_site.objects.filter(test__id=test_id)
      metr = querySet[0].test.metrics.summary.all() 
      columnIndexNameMap = {0:'test_site__site__name'} 
      for i in xrange(0,len(metr)):
#        table_redirect = ''
        metric = metr[i].name
#        if not metric in ['submitted','running','completed','failed','total','c_cf','c_t','s_t','r_t','f_t']:        
#          table_redirect = 's_metric__'
        columnIndexNameMap[i+1] = metr[i].name

      searchableColumns = {'site':'testsite__site__name'}
      jsonTemplatePath = str(app)+'/json/'+str(querySet[0].test.metrics.name)+'.txt'

    elif type.startswith('testlist'):

      mode = type.replace('testlist','')
      if mode == 'all':
        querySet = summary_test.objects.all()
      elif mode in ['scheduled','submitting','error','running','completed']:
        querySet = summary_test.objects.filter(test__state=mode)
      else:
        raise Http404

      columnIndexNameMap = {0:'test__id',1:'test__state',2:'test__host__name',3:'clouds',4:'test__template__id',5:'test__inputtype',6:'test__starttime',7:'test__endtime',8:'nr_sites',9:'total',10:'test__id'}
      jsonTemplatePath += 'testlist.txt'

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
    table = type

    items = []
    if type == 'testsummary':
      table = test.metrics.name

#    elif type == 'testbackend':
#        dh = HCDataHelper()
#        items = dh.annotateBackendExitCodes(test)
#    elif type == 'testapplication':
#        dh = HCDataHelper()
#        items = dh.annotateApplicationExitCodes(test)
#    elif type == 'testreasons':
#        dh = HCDataHelper()
#        items = dh.annotateBackendReasons(test)
#    elif type == 'testcompleted':
#        dh = HCDataHelper()
#        items = dh.annotateExampleCompletedJobs(test)
#    elif type == 'teststdouterr':
#        dh = HCDataHelper()
#        items = dh.annotateStdouterr(test)

    t = loader.select_template(['%s/ajax/%s.html'%(app,table),'core/app/ajax/%s.html'%(table)])
    c = Context({'test_id': test_id,'list':list,'type':type,'items':items,'app':app})
    return HttpResponse(t.render(c))


#  def ajaxtestmetrics(self,request,test_id,dic={'Test':None},*args,**kwargs):
#    app = dic['Test'].__module__.split('.')[1]
#    try:
#      test = dic['Test'].objects.get(pk=test_id)
#    except:
#      raise Http404
#    dh   = Datahelper()
#    test = dh.annotateTestPerMetric(test)
#    t = loader.select_template(['%s/testmetrics.html'%(app),'core/app/testmetrics.html'])
#    c = Context({'test': test})
#    return HttpResponse(t.render(c))


#  def ajaxsitemetrics(self,request,test_id,dic={'Test':None},*args,**kwargs):
#    app = dic['Test'].__module__.split('.')[1]
#    try:
#      test = dic['Test'].objects.get(pk=test_id)
#    except:
#      raise Http404
#    dh   = Datahelper()
#    test = dh.annotateTestPerSite(test)
#    t = loader.select_template(['%s/sitemetrics.html'%(app),'core/app/sitemetrics.html'])
#    c = Context({'test': test})
#    return HttpResponse(t.render(c))


#######################################################
## ROBOT BLOCK
#######################################################

  def robot(self,request,dic={'Site':None,'Cloud':None},*args,**kwargs):

    site = dic['Site']
    app  = site.__module__.split('.')[1]
  
    sites = site.objects.order_by('cloud')
    cloud = dic['Cloud']
    clouds =  cloud.objects.all()

    dh = Datahelper()

    sites = dh.annotateSitesEfficiency(sites)  

    t = loader.select_template(['%s/robot.html'%(app),'core/app/robot.html'])
    c = RequestContext(request,
                      {'sites': sites,'clouds':clouds},
                      [defaultContext]
                    )
    return HttpResponse(t.render(c))

#######################################################
## STATS BLOCK
#######################################################

  def stats(self,request,dic={'Site':None,'Result':None,'Cloud':None,'Template':None,'Test':None},*args,**kwargs):

    site = dic['Site']
    app  = site.__module__.split('.')[1]

    template  = dic['Template']
    test = dic['Test']
    cloud  = dic['Cloud']

    ## Overall 
    
    result  = dic['Result']
    total = result.objects.count()
    completed = result.objects.filter(ganga_status='c').count()
    failed = result.objects.filter(ganga_status='f').count()
    
    completed_total, failed_total = 0,0
    if total:
      completed_total = float(completed)/float(total)
      failed_total    = float(failed)/float(total)

    version = test.objects.all().aggregate(Max('version'))['version__max']
    since   = test.objects.all().aggregate(Min('starttime'))['starttime__min']
    vsince  = test.objects.filter(version=version).aggregate(Min('starttime'))['starttime__min']

    ##### Overall plot

    completed_plot = result.objects.filter(ganga_status='c').values('test__version').annotate(count=Count('test__version'))
    failed_plot    = result.objects.filter(ganga_status='f').values('test__version').annotate(count=Count('test__version'))

    overall_plot = []
    overall_labl = []

    #If they have different lenghts, it will crash
    for i in xrange(0,len(completed_plot)):
      overall_plot.append(completed_plot[i]['count'])
      overall_labl.append('C v.'+str(completed_plot[i]['test__version']))
      overall_plot.append(failed_plot[i]['count'])
      overall_labl.append('F v.'+str(failed_plot[i]['test__version']))    

    from hc.core.utils.plots.charts import pie
    overall_url = pie(overall_plot,overall_labl,'')

    ## Sites

    sites = site.objects.count()
    clouds = cloud.objects.count()

    sites_per_cloud = list(site.objects.values('cloud').annotate(count=Count('cloud')).order_by('count'))
    max_site_per_cloud,min_site_per_cloud = {},{}

    sites_plot = []
    sites_labl = []

    for s_p_c in sites_per_cloud:
      c = get_object_or_404(cloud,pk=s_p_c['cloud'])
      sites_plot.append(s_p_c['count'])
      sites_labl.append(c.code)

    sites_url = pie(sites_plot,sites_labl,'')

    if sites_per_cloud:
      min = sites_per_cloud[0]
      max = sites_per_cloud.pop()
      cloudM = get_object_or_404(cloud,pk=max['cloud'])
      cloudm = get_object_or_404(cloud,pk=min['cloud'])
      max_site_per_cloud = [(max['count'],cloudM)]
      min_site_per_cloud = [(min['count'],cloudm)]

    sites_per_cloud = 0
    if clouds and sites:
      sites_per_cloud = float(sites)/float(clouds)

    ## Users
    
    from django.contrib.auth.models import User
    users = User.objects.filter(groups__name__startswith=app).distinct().count()

    ## Tests

    templates = template.objects.count()

    tests = test.objects.count()

    tests_per_template = list(test.objects.values('template').annotate(count=Count('template')).order_by('count'))

    tests_plot = []
    tests_labl = []

    for t_p_t in tests_per_template:
      t = get_object_or_404(template,pk=t_p_t['template'])
      tests_plot.append(t_p_t['count'])
      tests_labl.append(t.id)

    tests_url = pie(tests_plot,tests_labl,'')


    max_test_per_template,min_test_per_template = {},{}
    if tests_per_template:
      min = tests_per_template[0]
      max = tests_per_template.pop()
      templateM = get_object_or_404(template,pk=max['template'])
      templatem = get_object_or_404(template,pk=min['template'])
      max_test_per_template = [(max['count'],templateM)]
      min_test_per_template = [(min['count'],templatem)]

    tests_per_template = 0
    if tests and templates:
      tests_per_template = float(tests)/float(templates)

    t = loader.select_template(['%s/stats.html'%(app),'core/app/stats.html'])
    c = RequestContext(request,
#                      {'sites': sites,'results':results,'users':users,'clouds':cloud,''},
                      locals(),
                      [defaultContext]
                    )
    return HttpResponse(t.render(c))

  def plots(self,request,dic={'MetricType':None,'Test':None,'Site':None,'Cloud':None,'Host':None,'Template':None},*args,**kwargs):

    metric_type = dic['MetricType']
    test        = dic['Test']
    cloud       = dic['Cloud']
    site        = dic['Site']
    host        = dic['Host']
    template    = dic['Template']
    app = metric_type.__module__.split('.')[1]

    metric_types = metric_type.objects.all()
    tests        = test.objects.all()
    clouds       = cloud.objects.all()
    templates    = template.objects.all()

    for cloud in clouds:
      cloud.sites = cloud.getSites_for_cloud.all()

    ## PLOT GENERATOR ##

    metric_q   = request.GET.getlist('metric')
    site_q     = request.GET.getlist('site')
    cloud_q    = request.GET.getlist('cloud')
    test_q     = request.GET.getlist('test')
    template_q = request.GET.getlist('template')
    
    dialog     = request.GET.get('dialog','')
    combine    = request.GET.get('combine','')

    plots = []
    msg = ''
    objects = {}

    if dialog:
      
      dialog = {'metric'   : (metric_q  , metric_types),
                     'site'     : (site_q    , clouds      ),
                     'cloud'    : (cloud_q   , clouds      ),
                     'test'     : (test_q    , tests       ),    
                     'template' : (template_q, templates   ) 
                    }
      
      t = loader.select_template(['%s/plots.html'%(app),'core/app/plots.html'])
      c = RequestContext(request,
                      {'dialog':dialog},
                      [defaultContext]
                    )
      return HttpResponse(t.render(c))


    try:
      objects['metric'] = []
      if metric_q:   
        for m_q in metric_q:
          id = int(m_q)
          objects['metric'].append(get_object_or_404(metric_type,pk=id))

        if site_q:
          objects['site'] = []
          for s_q in site_q:
            id = int(s_q)
            objects['site'].append(get_object_or_404(site,pk=id))

        if cloud_q:
          objects['cloud'] = []  
          for c_q in cloud_q:
            id = int(c_q)
            objects['cloud'].append(get_object_or_404(cloud,pk=id))

        if test_q:
          objects['test'] = []
          for t_q in test_q:
            id = int(t_q)
            objects['test'].append(get_object_or_404(test,pk=id))

        if template_q:
          objects['template'] = []
          for tt_q in template_q:
            id = int(tt_q)
            objects['template'].append(get_object_or_404(template,pk=id))

    except:
      msg = 'An error ocurred. Please contact admin if it occurs again.'

    if objects.has_key('metric') and not combine: 

      from hc.core.utils.plots.charts import hist  

      for metr in objects['metric']:         

        metr.plots = {}

        if objects.has_key('cloud'):

          plot_list = []

          for cloud in objects['cloud']:
            sites = cloud.getSites_for_cloud.all()
            values = []
            for site in sites:
              values += site.getResults_for_site.filter(ganga_status='c').values(metr.name).all()
            rate = [ dic[metr.name] for dic in values ]
            url = hist(rate, 20, metr.name ,metr.title)
            if url:
              plot_list += [(url,None,None)]
            else:
              plot_list += [(None,cloud.name,None)]

          metr.plots['cloud'] = plot_list 

        if objects.has_key('site'):

          plot_list = []

          for site in objects['site']:
            values = site.getResults_for_site.filter(ganga_status='c').values(metr.name).all()
            rate = [ dic[metr.name] for dic in values ]
            url = hist(rate, 20, metr.name ,metr.title)
            if url:
              plot_list += [(url,None,None)]
            else:
              plot_list += [(None,site.name,None)]   

          metr.plots['site'] = plot_list

        if objects.has_key('test'):

          plot_list = []

          for test in objects['test']:
            values = test.getResults_for_test.filter(ganga_status='c').values(metr.name).all()
            rate = [ dic[metr.name] for dic in values ]
            url = hist(rate, 20, metr.name ,metr.title)
            if url:
              plot_list += [(url,None,None)]
            else:
              plot_list += [(None,test.id,None)]

          metr.plots['test']         = plot_list

        if objects.has_key('template'):

          plot_list = []
          
          for template in objects['template']:
            tests = template.getTests_for_template.all()
            values = []
            for test in tests:
              values += test.getResults_for_test.filter(ganga_status='c').values(metr.name).all()
            rate = [ dic[metr.name] for dic in values ]
            url = hist(rate, 20, metr.name ,metr.title)
            if url:
              plot_list += [(url,None,None)]
            else:
              plot_list += [(None,template.description,None)]

          metr.plots['template']         = plot_list

        plots.append(metr)  

    if objects.has_key('metric') and combine:
      from hc.core.utils.plots.charts import hist
      for metr in objects['metric']:
        metr.plots = {}
        cloud_site_list = []
        if objects.has_key('cloud'):
          if objects.has_key('site'):
            cloud_site_dic = {}
            for site in objects['site']:
              if not cloud_site_dic.has_key(site.cloud.name):
                cloud_site_dic[site.cloud.name] =  [site]
              else:
                cloud_site_dic[site.cloud.name] += [site]
            for cloud in objects['cloud']:
              if cloud_site_dic.has_key(cloud.name):
                cloud_site_list += [(cloud,cloud_site_dic[cloud.name])]
          else:
            for cloud in objects['cloud']:
              cloud_site_list += [(cloud,None)] 
        elif objects.has_key('site'):
          cloud_site_dic = {}
          for site in objects['site']:
            if not cloud_site_dic.has_key(site.cloud.name):
              cloud_site_dic[site.cloud.name] =  [site]
            else:
              cloud_site_dic[site.cloud.name] += [site]
          cloud_site_list = [(k,v) for k,v in cloud_site_dic.items()]   

        if cloud_site_list:

          sites = []
          for k,c in cloud_site_list:
            if c:
              sites += c
            else:
              sites += k.getSites_for_cloud.all()

          if objects.has_key('test'):
            for test in objects['test']:
              plot_list = []
              for site in sites:
                values = test.getResults_for_test.filter(ganga_status='c').filter(site=site).values(metr.name).all() 
                rate = [ dic[metr.name] for dic in values ]
                url = hist(rate, 20, metr.name ,metr.title)
                if url:
                  plot_list += [(url,test.id,site.name)]
                else:
                  plot_list += [(None,test.id,site.name)]
              metr.plots['Test %s'%(test.id)] = plot_list

          if objects.has_key('template'):
            for template in objects['template']:
              tests = template.getTests_for_template.all()
              plot_list = []
              for site in sites:
                values = []
                for test in tests:
                  values += test.getResults_for_test.filter(ganga_status='c').filter(site=site).values(metr.name).all()
                rate = [ dic[metr.name] for dic in values ]
                url = hist(rate, 20, metr.name ,metr.title)
                if url:
                  plot_list += [(url,template.id,site.name)]
                else:
                  plot_list += [(None,template.description,site.name)]

              metr.plots['Template %s'%(template.description)] = plot_list

          if not objects.has_key('test') and not objects.has_key('template'):
            plot_list = []
            for site in sites:
              values = site.getResults_for_site.filter(ganga_status='c').values(metr.name).all()
              rate = [ dic[metr.name] for dic in values ]
              url = hist(rate, 20, metr.name ,metr.title)
              if url:
                plot_list += [(url,None,None)]
              else:
                plot_list += [(None,site.name,None)]
            metr.plots['site'] = plot_list             
        else:       
          if objects.has_key('test'):
            plot_list = []
            for test in objects['test']:
              values = test.getResults_for_test.filter(ganga_status='c').values(metr.name).all()
              rate = [ dic[metr.name] for dic in values ]
              url = hist(rate, 20, metr.name ,metr.title)
              if url:
                plot_list += [(url,None)]
              else:
                plot_list += [(None,test.id)]
            metr.plots['test']         = plot_list

          if objects.has_key('template'):
            plot_list = []
            for template in objects['template']:
              tests = template.getTests_for_template.all()
              values = []
              for test in tests:
                values += test.getResults_for_test.filter(ganga_status='c').values(metr.name).all()
              rate = [ dic[metr.name] for dic in values ]
              url = hist(rate, 20, metr.name ,metr.title)
              if url:
                plot_list += [(url,None)]
              else:
                plot_list += [(None,template.description)]
            metr.plots['template']         = plot_list

        plots.append(metr)


    ## END PLOT GENERATOR ##

    t = loader.select_template(['%s/plots.html'%(app),'core/app/plots.html'])
    c = RequestContext(request,
                      locals(),
                      [defaultContext]
                    )
    return HttpResponse(t.render(c))

