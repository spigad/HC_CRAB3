from hc.core.utils.plots.charts import hist,pie,line
from django.shortcuts import get_object_or_404
from django.contrib.auth.models import User
from django.db.models import Min,Max,Count
from numpy import *

import time,datetime
import numpy

class Stats:

  ## QUERY

  def parseQuery(self,request, dic):
    
    obj = {}
    obj['metric_type'] = dic['MetricType']
    obj['test']        = dic['Test']
    obj['cloud']       = dic['Cloud']
    obj['site']        = dic['Site']
    obj['template']    = dic['Template']

    query = {}

    query['metric_type']     = request.REQUEST.getlist('metric_type')
    query['site']            = request.REQUEST.getlist('site')
    query['cloud']           = request.REQUEST.getlist('cloud')
    query['test']            = request.REQUEST.getlist('test')
    query['template']        = request.REQUEST.getlist('template')

    commands = {}

    commands['type']            = request.REQUEST.get('type','')
    commands['go']              = request.REQUEST.get('go','') 
    commands['sort_by']         = request.REQUEST.get('sort_by','')
    commands['completed']       = request.REQUEST.get('completed','')

    advanced = {}

    advanced['from']            = request.REQUEST.get('from','')
    advanced['starttime']       = request.REQUEST.get('starttime','')
    advanced['to']              = request.REQUEST.get('to','')
    advanced['endtime']         = request.REQUEST.get('endtime','')

    Qobjects = {}
    error = ''

    if commands['type'] and not commands['type'] in ['plot','rank','timeline']:
      error = 'Please, check the type introduced.'

    date_format = "%Y-%m-%d %H:%M:%S"

    if advanced['from'] and advanced['from']!='From' and not error:
      if advanced['starttime'] and advanced['starttime']!='Starttime':
        s_time = advanced['from']+' '+advanced['starttime']
      else:
        s_time = advanced['from']+' 00:00:00'
      try:
        commands['starttime'] =  datetime.datetime.fromtimestamp(time.mktime(time.strptime(s_time,date_format)))
      except:
        error = 'Please, format properly starttime.'
    else:
      if advanced['starttime'] and advanced['starttime']!='Starttime':
        error = 'Please, set a data for start time.' 

    if advanced['to'] and advanced['to']!='To' and not error:
      if advanced['endtime'] and advanced['endtime']!='Endtime':
        e_time = advanced['to']+' '+advanced['endtime']
      else:
        e_time = advanced['to']+' 00:00:00'
      try:
        commands['endtime'] =  datetime.datetime.fromtimestamp(time.mktime(time.strptime(e_time,date_format)))
      except:
        error = 'Please, format properly endtime.'
    else:
      if advanced['endtime'] and advanced['endtime']!='Endtime':
        error = 'Please, set a data for end time.' 
    
    if not error:
      try:
        for key,values in query.items():
          Qobjects[key] = []
          for item in values:
            id = int(item)
            Qobjects[key].append(get_object_or_404(obj[key],pk=id))
  
      except:
        error = 'An error ocurred. Please contact admin if it occurs again.'

    return (Qobjects,commands,obj,error)


  ## DIALOG

  def getDialog(self,obj,Qobjects):

    dialog   = []

    clouds = obj['cloud'].objects.all()
    for cloud in clouds:
      cloud.sites = cloud.getSites_for_cloud.all()
      
    for class_name,class_instance in obj.items():

      if not Qobjects.has_key(class_name):
        if class_name == 'template' and Qobjects['test']:
          pass
        elif class_name == 'cloud' and Qobjects['site']:
          pass
        elif class_name == 'site':
          dialog += [(class_name,clouds)]
        else:
          dialog += [(class_name,class_instance.objects.all())]

      else:
        if class_name == 'site':
          clouds = list(clouds)
          for item in Qobjects[class_name]:
            if item.cloud in clouds:
              cloud_index = clouds.index(item.cloud)
              cloud = clouds[cloud_index]
              if item in cloud.sites:
                cloud.sites = list(cloud.sites)
                index = cloud.sites.index(item)
                cloud.sites.remove(item)
                item.selected = 'selected'
                cloud.sites.insert(index,item)

          dialog += [(class_name,clouds)]
        else:
          class_instance_objs = list(class_instance.objects.all())
          for item in Qobjects[class_name]:
            if item in class_instance_objs:
              index = class_instance_objs.index(item)
              class_instance_objs.remove(item)
              item.selected = 'selected'
              class_instance_objs.insert(index,item)

          dialog += [(class_name,class_instance_objs)]

    return dialog


  ## PLOTS, RANKS, TIMELINES

  def filterQuery(self,query,commands):

    if commands.has_key('starttime'):
      query = query.filter(mtime__gt=commands['starttime'])

    if commands.has_key('endtime'):
      query = query.filter(mtime__lt=commands['endtime'])

    return query  

  def filterStatus(self,query,dic):

    status      = ['c','f','r','s','n','g','h','k','d']
    status_done = ['c','f']

    if not query.count():
      return dic

    q = query.exclude(test__state='completed')
    if q.count() > 0:
      for s in status:
        c = q.filter(ganga_status=s).count()
        if dic.has_key(s):
          dic[s] += c
        else:
          dic[s] = c

    q = query.filter(test__state='completed')
    if q.count() > 0:
      for s in status_done:
        c = q.filter(ganga_status=s).count()
        if dic.has_key(s):
          dic[s] += c
        else:
          dic[s] = c

    return dic


  ## PLOTS, RANKS, TIMELINES ...

############################################################### HISTS

  def cloud_proc(self,Qobjects,commands,extra=[]):

    values_list = []
    metric_list = [m.name for m in Qobjects['metric_type'] if m.name != 'c_cf'] + extra

    for cloud in Qobjects['cloud']:
      values = []
      title  = 'Cloud %s.'%(cloud.name)
      sites  = cloud.getSites_for_cloud.all()

      #Overall
      val_list = []
      for site in sites:
        query = site.getResults_for_site.filter(ganga_status='c').exclude(ganga_subjobid=1000000)
        query = self.filterQuery(query,commands)
        val_list += query.values(*metric_list).all()
      values = [('Overall.',val_list)]

      if Qobjects['test']:
        for test in Qobjects['test']:
          val_list = []
          for site in sites:
            query = site.getResults_for_site.filter(ganga_status='c').filter(test=test).exclude(ganga_subjobid=1000000)
            query = self.filterQuery(query,commands)
            val_list += query.values(*metric_list).all()
          values += [('Test %s.'%(test.id),val_list)]

      elif Qobjects['template']:
        for template in Qobjects['template']:
          val_list = []
          tests = template.getTests_for_template.all()
          for test in tests:
            for site in sites:
              query = site.getResults_for_site.filter(ganga_status='c').filter(test=test).exclude(ganga_subjobid=1000000)
              query = self.filterQuery(query,commands)
              val_list += query.values(*metric_list).all()
          values += [('Template %s.'%(template.id),val_list)]

      values_list += [(title,values)]

    return values_list

  def site_proc(self,Qobjects,commands,extra=[]):

    values_list = []
    metric_list = [ m.name for m in Qobjects['metric_type'] if m.name != 'c_cf'] + extra

    for site in Qobjects['site']:
      values = []
      title  = 'Site %s.'%(site.name)

      #Overall
      query = site.getResults_for_site.filter(ganga_status='c').exclude(ganga_subjobid=1000000)
      query = self.filterQuery(query,commands)
      values = [('Overall.',query.values(*metric_list).all())]

      if Qobjects['test']:
        for test in Qobjects['test']:
          query = site.getResults_for_site.filter(ganga_status='c').filter(test=test.id).exclude(ganga_subjobid=1000000)
          query = self.filterQuery(query,commands)
          values += [('Test %s'%(test.id),query.values(*metric_list).all())]

      elif Qobjects['template']:
        for template in Qobjects['template']:
          tests = template.getTests_for_template.all()
          val_list = []
          for test in tests:
            query = site.getResults_for_site.filter(ganga_status='c').filter(test=test.id).exclude(ganga_subjobid=1000000)
            query = self.filterQuery(query,commands)
            val_list += query.values(*metric_list).all()
          values += [('Template %s'%(template.id),val_list)]

      values_list += [(title,values)]

    return values_list

  def test_proc(self,Qobjects,commands,extra=[]):

    values_list = []
    metric_list = [ m.name for m in Qobjects['metric_type'] if m.name != 'c_cf'] + extra

    for test in Qobjects['test']:
      values = []
      title = 'Test %s'%(test.id)

      #Overall
      query = test.getResults_for_test.filter(ganga_status='c').exclude(ganga_subjobid=1000000)
      query = self.filterQuery(query,commands)
      values = [('Overall.',query.values(*metric_list).all())]

      if Qobjects['site']:
        for site in Qobjects['site']:
          query = test.getResults_for_test.filter(ganga_status='c').filter(site=site).exclude(ganga_subjobid=1000000)
          query = self.filterQuery(query,commands)
          values += [(site.name,query.values(*metric_list).all())]

      elif Qobjects['cloud']:
        for cloud in Qobjects['cloud']:
          val_list = []
          for site in cloud.getSites_for_cloud.all():
            query = test.getResults_for_test.filter(ganga_status='c').filter(site=site).exclude(ganga_subjobid=1000000)
            query = self.filterQuery(query,commands)
            val_list += query.values(*metric_list).all()
          values += [(cloud.name,val_list)]

      values_list += [(title,values)]

    return values_list

  def template_proc(self,Qobjects,commands,extra=[]):

    values_list = []
    metric_list = [ m.name for m in Qobjects['metric_type'] if m.name != 'c_cf'] + extra

    for template in Qobjects['template']:
      values = []
      title  = 'Template %s.'%(template.id)

      #Overall
      val_list = []
      for test in template.getTests_for_template.all():
        query = test.getResults_for_test.filter(ganga_status='c').exclude(ganga_subjobid=1000000)
        query = self.filterQuery(query,commands)
        val_list += query.values(*metric_list).all()
      values = [('Overall.',val_list)]

      if Qobjects['test']:

        sites = []
        for site in Qobjects['site']:
          sites += [site]
        for cloud in Qobjects['cloud']:
          for site in cloud.getSites_for_cloud.all():
            sites += [site]

        if sites: #get by_test with given sites
          for test in Qobjects['test']:
            if test.template == template:
              val_list = []
              for site in sites:
                query = test.getResults_for_test.filter(ganga_status='c').filter(site=site).exclude(ganga_subjobid=1000000)
                query = self.filterQuery(query,commands)
                val_list += query.values(*metric_list).all()
              values += [('Test %s'%(test.id),val_list)]

        else: #get by_test with all possible sites
          for test in tests:
            if test.template == template:
              query = test.getResults_for_test.filter(ganga_status='c').exclude(ganga_subjobid=1000000)
              query = self.filterQuery(query,commands)
              values += [('Test %s'%(test.id),query.values(*metric_list).all())]

      else:
        tests = template.getTests_for_template.all()

        if Qobjects['site']:
          for site in Qobjects['site']:
            val_list = []
            for test in tests:
              query = test.getResults_for_test.filter(ganga_status='c').filter(site=site).exclude(ganga_subjobid=1000000)
              query = self.filterQuery(query,commands)
              val_list += query.values(*metric_list).all()
            values += [(site.name,val_list)]

        elif Qobjects['cloud']:
          for cloud in Qobjects['cloud']:
            val_list = []
            for site in cloud.getSites_for_cloud.all():
              for test in tests:
                query = test.getResults_for_test.filter(ganga_status='c').filter(site=site).exclude(ganga_subjobid=1000000)
                query = self.filterQuery(query,commands)
                val_list += query.values(*metric_list).all()
            values += [(cloud.name,val_list)]

      values_list += [(title,values)]

    return values_list


############################################################### PIES

  def cloud_proc_pie(self,Qobjects,commands,extra=[]):

    values_list = []

    for cloud in Qobjects['cloud']:

      values = []
      title  = 'Cloud %s.'%(cloud.name)
      sites  = cloud.getSites_for_cloud.all()

      #Overall
      dic = {}
      for site in sites:
        query = site.getResults_for_site.exclude(ganga_subjobid=1000000)
        query = self.filterQuery(query,commands)
        dic = self.filterStatus(query,dic)
      values = [('Overall.',dic)]

      if Qobjects['test']:
        for test in Qobjects['test']:
          dic = {}
          for site in sites:
            query = site.getResults_for_site.filter(test=test).exclude(ganga_subjobid=1000000)
            query = self.filterQuery(query,commands)
            dic = self.filterStatus(query,dic)
          values += [('Test %s.'%(test.id),dic)]

      elif Qobjects['template']:
        for template in Qobjects['template']:
          dic = {}
          tests = template.getTests_for_template.all()
          for test in tests:
            for site in sites:
              query = site.getResults_for_site.filter(test=test).exclude(ganga_subjobid=1000000)
              query = self.filterQuery(query,commands)
              dic = self.filterStatus(query,dic)
          values += [('Template %s.'%(template.id),dic)]

      values_list += [(title,values)]

    return values_list

  def site_proc_pie(self,Qobjects,commands,extra=[]):

    values_list = []

    for site in Qobjects['site']:
      values = []
      title  = 'Site %s.'%(site.name)

      #Overall
      query = site.getResults_for_site.exclude(ganga_subjobid=1000000)
      query = self.filterQuery(query,commands)
      dic = self.filterStatus(query,{})
      if dic:
        values = [('Overall.',dic)]

      if Qobjects['test']:
        for test in Qobjects['test']:
          query = site.getResults_for_site.filter(test=test.id).exclude(ganga_subjobid=1000000)
          query = self.filterQuery(query,commands)
          dic = self.filterStatus(query,{})
          if dic:
            values += [('Test %s'%(test.id),dic)]

      elif Qobjects['template']:
        for template in Qobjects['template']:
          tests = template.getTests_for_template.all()
          dic = {}
          for test in tests:
            query = site.getResults_for_site.filter(test=test.id).exclude(ganga_subjobid=1000000)
            query = self.filterQuery(query,commands)
            dic = self.filterStatus(query,dic)
          values += [('Template %s'%(template.id),dic)]

      values_list += [(title,values)]

    return values_list


  def test_proc_pie(self,Qobjects,commands,extra=[]):
    values_list = []

    for test in Qobjects['test']:
      values = []
      title = 'Test %s'%(test.id)

      #Overall
      query = test.getResults_for_test.exclude(ganga_subjobid=1000000)
      query = self.filterQuery(query,commands)
      dic = self.filterStatus(query,{})
      if dic:
        values = [('Overall.',dic)]

      if Qobjects['site']:
        for site in Qobjects['site']:
          query = test.getResults_for_test.filter(site=site).exclude(ganga_subjobid=1000000)
          query = self.filterQuery(query,commands)
          dic = self.filterStatus(query,{})
          if dic:
            values += [(site.name,dic)]

      elif Qobjects['cloud']:
        for cloud in Qobjects['cloud']:
          dic = {}
          for site in cloud.getSites_for_cloud.all():
            query = test.getResults_for_test.filter(site=site).exclude(ganga_subjobid=1000000)
            query = self.filterQuery(query,commands)
            dic = self.filterStatus(query,dic)
          values += [(cloud.name,dic)]

      values_list += [(title,values)]

    return values_list


  def template_proc_pie(self,Qobjects,commands,extra=[]):

    values_list = []

    for template in Qobjects['template']:
      values = []
      title  = 'Template %s.'%(template.id)

      #Overall
      dic = {}
      for test in template.getTests_for_template.all():
        query = test.getResults_for_test.exclude(ganga_subjobid=1000000)
        query = self.filterQuery(query,commands)
        dic = self.filterStatus(query,dic)
      values = [('Overall.',dic)]

      if Qobjects['test']:

        sites = []
        for site in Qobjects['site']:
          sites += [site]
        for cloud in Qobjects['cloud']:
          for site in cloud.getSites_for_cloud.all():
            sites += [site]

        if sites: #get by_test with given sites
          for test in Qobjects['test']:
            if test.template == template:
              dic = {}
              for site in sites:
                query = test.getResults_for_test.filter(site=site).exclude(ganga_subjobid=1000000)
                query = self.filterQuery(query,commands)
                dic = self.filterStatus(query,dic)
              values += [('Test %s'%(test.id),dic)]

        else: #get by_test with all possible sites
          for test in Qobjects['test']:
            if test.template == template:
              query = test.getResults_for_test.exclude(ganga_subjobid=1000000)
              query = self.filterQuery(query,commands)
              dic = self.filterStatus(query,{})
              if dic:
                values += [('Test %s'%(test.id),dic)]

      else:
        tests = template.getTests_for_template.all()

        if Qobjects['site']:
          for site in Qobjects['site']:
            dic = {}
            for test in tests:
              query = test.getResults_for_test.filter(site=site).exclude(ganga_subjobid=1000000)
              query = self.filterQuery(query,commands)
              dic = self.filterStatus(query,dic)
            values += [(site.name,dic)]

        elif Qobjects['cloud']:
          for cloud in Qobjects['cloud']:
            dic = {}
            for site in cloud.getSites_for_cloud.all():
              for test in tests:
                query = test.getResults_for_test.filter(site=site).exclude(ganga_subjobid=1000000)
                query = self.filterQuery(query,commands)
                dic = self.filterStatus(query,dic)
            values += [(cloud.name,dic)]

      values_list += [(title,values)]

    return values_list



########################################################################## PROCESS

  def process(self,Qobjects,commands):
    
    container = {}
    error = ''    
    hist_list = []
    pie_list = []

    sort_by   = commands['sort_by']
    type      = commands['type']
    completed = commands['completed']

    #Dummy protection.
    for key in ['metric_type','site','cloud','test','template']:
      if not Qobjects.has_key(key):
        Qobjects[key] = []

    if not type in ['plot','rank','timeline','raw_value']:
      error = 'Please, select a statistics type.'
      return ({},error)
    elif type == 'timeline':
      extra = ['mtime']
    else:
      extra = []

    pie_flag = False
    if 'c_cf' in [m.name for m in Qobjects['metric_type']]:
      pie_flag = True

    hist_flag = False
    if (not pie_flag and len(Qobjects['metric_type'])) or (pie_flag and len(Qobjects['metric_type'])>0 ):
      hist_flag = True

    if not sort_by:
      error = 'Please, select a sorting parameter.'

    elif 'evol_cf' in [m.name for m in Qobjects['metric_type']] or 'evol_sr' in [m.name for m in Qobjects['metric_type']]:
      error = 'Not available yet.'

    elif not Qobjects.has_key('metric_type'):
      error = 'Please, select at least one metric.'

    elif not Qobjects['metric_type']:
      error = 'Please, select at least one metric.'

    elif not error and not(Qobjects['site'] or Qobjects['cloud'] or Qobjects['test'] or Qobjects['template']):
      error = 'Please, select a filter for this metric type.'

    elif Qobjects['cloud'] and Qobjects['site']:
      error = 'Please, decide if you want to filter either by site or by cloud.'

    elif not Qobjects[sort_by]:
      error = 'You must select at least one %s.'%(sort_by)

    elif sort_by == 'cloud':
      if Qobjects['test'] and Qobjects['template']:
        error = 'Please, decide if you want to filter either by test or by template.'
      else:
        if hist_flag:
          hist_list = self.cloud_proc(Qobjects,commands,extra)
        if pie_flag and not type == 'raw_value':
          pie_list = self.cloud_proc_pie(Qobjects,commands,extra)

    elif sort_by == 'site':
      if Qobjects['test'] and Qobjects['template']:
        error = 'Please, decide if you want to filter either by test or by template.'
      else:
        if hist_flag:
          hist_list = self.site_proc(Qobjects,commands,extra)
        if pie_flag and not type == 'raw_value':
          pie_list = self.site_proc_pie(Qobjects,commands,extra)

    elif sort_by == 'test':
      if Qobjects['test'] and Qobjects['template']:
        error = 'Please, decide if you want to filter either by test or by template.'
      else:
        if hist_flag:
          hist_list = self.test_proc(Qobjects,commands,extra)
        if pie_flag and not type == 'raw_value':
          pie_list = self.test_proc_pie(Qobjects,commands,extra)

    elif sort_by == 'template':
      if hist_flag:
        hist_list = self.template_proc(Qobjects,commands,extra)
      if pie_flag and not type == 'raw_value':
        pie_list = self.template_proc_pie(Qobjects,commands,extra)

    if type in ['rank','timeline'] and pie_flag:
      error = 'Efficiency metric not supported yet.'

    if type == 'rank' and not error:
      container = self.rank(hist_list,pie_list,Qobjects['metric_type'])
    elif type == 'plot' and not error:
      container = self.plot(hist_list,pie_list,Qobjects['metric_type'],completed)
    elif type == 'timeline' and not error:
      if len(Qobjects['metric_type']) > 1:
        error = 'Multi metric timeline is not implemented yet.'    
        titles = ''
      else:
        titles,container = self.timeline(hist_list,pie_list,Qobjects['metric_type'])
    elif type == 'raw_value':
      return hist_list
    else:
      titles = ''
      container = {}

    if type=='timeline':
      return (titles,container,error)
             
    return (container,error)

  def rank(self,hist_list,pie_list,metrics):

    container = {}

    for title,values in hist_list:
 
      if not container.has_key(title):
        container[title] = {}

      for metric in metrics:

        for rank_title,value in values:
          rate = [ dic[metric.name] for dic in value ]

          if rate:
            x_sub = []
            for k in rate:
              if k != None:
                x_sub += [float(k)]
            rate = x_sub

            mean = round(numpy.mean(rate),1)
            std  = round(numpy.std(rate),1)
          else:
            mean = '-'
            std  = '-'

          if not container[title].has_key(rank_title):
            container[title][rank_title] = []

        container[title][rank_title] += [(mean,std)]

    #Sort dictionary
    keys = container.keys()
    keys.sort()
    for key in keys:
      subkeys = container[key].keys()
      subkeys.sort()
      container[key] = [(subkey,container[key][subkey]) for subkey in subkeys]
    container = [(key,container[key]) for key in keys]

    return container

  def plot(self,hist_list,pie_list,metrics,completed):

    ## IF COMPLETED, PIE CHART ONLY RETURNS C and F

    container = {}

    for title,values in hist_list:

      if not container.has_key(title):
        container[title] = []

      for metric in metrics:

        if metric.name != 'c_cf':

          plot_list = []
  
          for plot_title,value in values:
            rate = [ dic[metric.name] for dic in value ]
            url = ''
            url = hist(rate, 20, metric.title, plot_title)
         
            if url:
              plot_list += [(plot_title,url)]

          container[title] += [(metric.title,plot_list)]

#    color = dict({'c':'5EFB6E', 'f':'FF0000', 'r':'79BAEC', 's':'FFF380', 'n':'F75D59', 'o':'38ACEC'})
    color = dict({'c':'15ca00', 'f':'e81c01', 'r':'0094ee', 's':'e7a900', 'n':'03aaf9', 'o':'bdb9b9',
                  'g':'ffd561', 'h':'6bc6ff', 'k':'fe7867', 'd':'76d3fe'})

    status = ['c','f','r','s','n','g','h','k','d']

    for title,values in pie_list:
      if not container.has_key(title):
        container[title] = []

      plot_list = []

      for plot_title,plot_dic in values:

        rate   = []
        labels = []
        colors = []

        for k,v in plot_dic.items():

          if (completed and k in ['c','f']) or not completed:

            if v:
              rate.append(v)
              labels.append('%s (%s)'%(k,v))

              if k in status:
                colors.append(color[k])
              else:
                colors.append(color['o'])      

        url = pie(rate,labels,plot_title,colors)
        plot_list += [(plot_title,url)]      

      container[title] += [(u'Efficiency',plot_list)]

    #Sort dictionary
    keys = container.keys()
    keys.sort()
    container = [(key,container[key]) for key in keys]

    return container

  def timeline(self,hist_list,pie_list,metrics):

    container = {}
    titles = []

    lista = {}
 
    overall_title = ''

    if len(metrics) == 1:
      overall_title = metrics[0].name
      if len(hist_list) == 1:
        title,values = hist_list[0]
        overall_title += '@ %s.'%(title)
        for sub_title,value in values:
          if not '%s-%s'%(title,sub_title) in titles:
            titles.append('%s-%s'%(title,sub_title))          
          for dic in value:
            date = dic['mtime']
            if not lista.has_key('%s-%s'%(title,sub_title)):
              lista['%s-%s'%(title,sub_title)] = []
            lista['%s-%s'%(title,sub_title)] += [(date,dic[metrics[0].name])]

      else:
        for title,values in hist_list:
          for sub_title,value in values:
            if not '%s-%s'%(title,sub_title) in titles:
              titles.append('%s-%s'%(title,sub_title))
            for dic in value:
              date = dic['mtime']
              if not lista.has_key('%s-%s'%(title,sub_title)):
                lista['%s-%s'%(title,sub_title)] = []
              lista['%s-%s'%(title,sub_title)] += [(date,dic[metrics[0].name])]

      for key,lista_values in lista.items():
        index = titles.index(key)
        for lista_date,lista_value in lista_values:        
          if not container.has_key(lista_date):
            container[lista_date] = ones(len(titles),float)*(-1)
          if lista_value:
            container[lista_date][index] = lista_value

      #Sort dictionary
      keys = container.keys()
      keys.sort()
      container = [(key,container[key]) for key in keys]

      return (titles,container)

#    NOT IMPLEMENTED YET.
#    elif len(hist_list) == 1:
#      overall_title,values = hist_list[0] 
#    
     
#    return overall_title


###################################################################################################################
  ## OVERVIEW

  def overview_basic(self,dic):

    result = dic['Result']
    test   = dic['Test']

    total     = result.objects.count()
    completed = result.objects.filter(ganga_status='c').count()
    failed    = result.objects.filter(ganga_status='f').count()

    completed_total, failed_total = 0,0
    if total:
      completed_total = float(completed)/float(total)
      failed_total    = float(failed)/float(total)

    version = test.objects.all().aggregate(Max('version'))['version__max']
    since   = test.objects.all().aggregate(Min('starttime'))['starttime__min']
    vsince  = test.objects.filter(version=version).aggregate(Min('starttime'))['starttime__min']

    #PLOT
   
    completed_plot = result.objects.filter(ganga_status='c').values('test__version').annotate(count=Count('test__version'))
    failed_plot    = result.objects.filter(ganga_status='f').values('test__version').annotate(count=Count('test__version'))

    overall_plot = []
    overall_labl = []

    #If they have different lenghts, it will crash

    for i in xrange(0,len(completed_plot)):
      overall_plot.append(completed_plot[i]['count'])
      overall_labl.append('C v.'+str(completed_plot[i]['test__version']))

    for i in xrange(0,len(failed_plot)):
      overall_plot.append(failed_plot[i]['count'])
      overall_labl.append('F v.'+str(failed_plot[i]['test__version']))

    overall_url = pie(overall_plot,overall_labl,'')

    return (since,version,vsince,total,completed,completed_total,failed,failed_total,overall_url)

  def overview_sites(self,dic):

    site  = dic['Site']
    cloud = dic['Cloud']

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

    return (sites,clouds,max_site_per_cloud,min_site_per_cloud,sites_per_cloud,sites_url) 

  def overview_users(self,dic):
    site = dic['Site']
    app  = site.__module__.split('.')[1]
    users = User.objects.filter(groups__name__startswith=app).distinct().count()

    return users

  def overview_tests(self,dic):

    template = dic['Template']    
    test     = dic['Test']

    templates = template.objects.count()
    tests     = test.objects.count()

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

    return (templates,tests,max_test_per_template,min_test_per_template,tests_per_template,tests_url)

  def parseEvolQuery(self,request,dic):

    obj = {}
    obj['cloud']       = dic['Cloud']
    obj['site']        = dic['Site']

    query = {}
    query['site']            = list(set(request.REQUEST.getlist('site')))
    query['cloud']           = list(set(request.REQUEST.getlist('cloud')))

    error = 0

    Qobjects = {}
    Qobjects['type']         = request.REQUEST.get('type','running')
    TYPES = ['running','submitted','completed','failed','total']

    if not Qobjects['type'] in TYPES:
      Qobjects['type'] = 'running'

    try:
      for key,values in query.items():
        Qobjects[key] = []
        for item in values:
          id = int(item)
          Qobjects[key].append(get_object_or_404(obj[key],pk=id))
    except:
      error = 1  
  
    return (error,Qobjects)


  def overview_evol(self,request,dic):

    sumE  = dic['SummaryEvolution']
    cloud = dic['Cloud']
    site  = dic['Site']

    error,Qobjects = self.parseEvolQuery(request,dic)

    if error:
      return 0

    #Keep titles order !!

    titles  = {'Overall':0}

    if not Qobjects['site'] and not Qobjects['cloud']:  
      for c in cloud.objects.all():
        titles[c.name] = sumE.objects.filter(site__cloud__name=c.name).all()
    else:
      for c in Qobjects['cloud']:
        titles[c.name] = sumE.objects.filter(site__cloud__name=c.name).all()
      for s in Qobjects['site']:
        titles[s.name] = sumE.objects.filter(site=s).all() 

    values = {}

    for k,sumEs in titles.items():

      if k == 'Overall':
        continue

      for sE in sumEs:

        time = sE.time.replace(second=0).replace(microsecond=0)
        min = str(time.minute)
        if min > '9':
          min = min[1]
        if min > '4':
          time = time.replace(minute=5) 
        else:
          time = time.replace(minute=0)

        if not values.has_key(time):
          values[time] = {}
          for titl in titles:
            values[time][titl] = 0 

        val = getattr(sE,Qobjects['type'])

#      values[time][sE.site.cloud.name] += sE.running
        values[time][k]                  += val
        values[time]['Overall']          += val

    tkeys = titles.keys()
    tkeys.sort()
    titles = [(key,titles[key]) for key in tkeys]
  
    vkeys = values.keys()
    vkeys.sort()
    for key in vkeys:
      subkeys = values[key].keys()
      subkeys.sort()
      values[key] = [(subkey,values[key][subkey]) for subkey in subkeys]
    values = [(key,values[key]) for key in vkeys]

    return (titles,values,Qobjects['type'])


#################################################################################

##            EVOLUTION

  def evolution(self,test,flash):

    summary_evolution = test.getSummaryEvolutions_for_test
    sites             = sorted([ ts.site for ts in test.getTestSites_for_test.all()])

    if flash:
      return []

    evols  = [ summary_evolution.filter(site=site).order_by('time') for site in sites]
    charts = {}
    labels = []

    size = len(evols[0])

    total_sub = []
    total_run = []
    total_com = []
    total_fai = []

    for site_evols in evols:

      if site_evols:

        counter  = 0
        new_evol = []

        step = int(len(site_evols)/50) + 1
        for site_evol in site_evols:
          counter += 1
          if counter == step:
            counter  = 0
            new_evol += [site_evol]

        submitted = [ e.submitted for e in new_evol]
        running   = [ e.running   for e in new_evol]
        completed = [ e.completed for e in new_evol]
        failed    = [ e.failed    for e in new_evol]

        #Four labels
        label_step = int(size/4)

        labels = [site_evols[0].time.isoformat(),site_evols[size-1].time.isoformat()]
  
        charts[site_evols[0].site.name] = {}
        charts[site_evols[0].site.name]['SR'] = line([submitted,running],labels,('submitted','running'),'Submitted / Running %s'%(site_evols[0].site.name),['e7a900','0094ee'])
        charts[site_evols[0].site.name]['CF'] = line([completed,failed] ,labels,('completed','failed') ,'Completed / Failed %s'%(site_evols[0].site.name),['15ca00','e81c01'])

        if total_sub:
          total_sub = [sum(pair) for pair in zip(total_sub, submitted)]
        else:
          total_sub = submitted
        if total_run:
          total_run = [sum(pair) for pair in zip(total_run, running)]
        else:
          total_run = running
        if total_com:
          total_com = [sum(pair) for pair in zip(total_com, completed)]
        else:
          total_com = completed
        if total_fai:
          total_fai = [sum(pair) for pair in zip(total_fai, failed)]
        else:
          total_fai = failed

    if labels:
      charts['Overall'] = {}
      charts['Overall']['SR'] = line([total_sub,total_run],labels,('submitted','running'),'Submitted / Running Overall',['e7a900','0094ee'])
      charts['Overall']['CF'] = line([total_com,total_fai] ,labels,('completed','failed') ,'Completed / Failed Overall',['15ca00','e81c01'])

    return charts

