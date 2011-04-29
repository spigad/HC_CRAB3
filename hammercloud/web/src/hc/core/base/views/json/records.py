from django.db.models  import  Q
from django.template.loader import render_to_string
from django.http import HttpResponse

def get_records(request, querySet, columnIndexNameMap, searchableColumns, jsonTemplatePath, type, app, *args):

  dic = {}
  if "testlist" in type:
    dic = {'id':'test__id','status':'test__state','host':'test__host__name','cloud':'clouds','template':'test__template__description','inputtype':'test__inputtype__type','starttime':'test__starttime','endtime':'test__endtime','sites':'nr_sites','jobs':'total'}
  elif type == "testsites":
    dic = {'site':'test_site__site__name','submitted':'submitted','running':'running','completed':'completed','failed':'failed','eff':'c_cf','total':'total','datasets':'test_site__site__num_datasets_per_bulk','queue':'test_site__min_queue_depth','max_running':'test_site__max_running_jobs','resubmit':'test_site__resubmit_enabled','force':'test_site__resubmit_force'}
  elif type == "testsummary":
    dic = {'site':'testsite__site__name'}
    dic.update(searchableColumns)
  elif type == "robotlist":
    dic = {'site':'site__name','completed':'completed','failed':'failed','total':'total','efficiency':'efficiency','efficiencyNorm':'efficiencyNorm','errorrate':'errorrate','errorrateNorm':'errorrateNorm'}
  elif type == "testjobs":
    dic = {'status':'ganga_status','site':'site__name','job':'ganga_jobid','subjob':'ganga_subjobid','backendID':'backendID','reason':'reason','submit':'submit_time','start':'start_time','end':'stop_time'}
  elif type == 'robotjobs':
    dic = {'status':'ganga_status','site':'site__name','test':'test__id','job':'ganga_jobid','subjob':'ganga_subjobid','backendID':'backendID','reason':'reason','submit':'submit_time','start':'start_time','end':'stop_time'}
  elif type == 'testreasons':
    dic = {'site':'site__name','reason':'reason'}

  #Safety measure. If someone messes with iDisplayLength manually, we clip it to
  #the max value of 100.
  if not 'iDisplayLength' in request.GET or not request.GET['iDisplayLength']:
    iDisplayLength = 50 # default value
  else:
    iDisplayLength = min(int(request.GET['iDisplayLength']),200)
  if not 'iDisplayStart' in request.GET or not request.GET['iDisplayStart']:
    startRecord = 0 #default value
  else:
    startRecord = int(request.GET['iDisplayStart'])
  endRecord = startRecord + iDisplayLength
  #apply ordering
  if not 'iSortingCols' in request.GET or not request.GET['iSortingCols']:
    iSortingCols = 0 #default value
  else:
    iSortingCols = int(request.GET['iSortingCols'])
  asortingCols = []
   
  if iSortingCols>0:
    for sortedColIndex in range(0, iSortingCols):
      sortedColName = columnIndexNameMap[int(request.GET['iSortCol_'+str(sortedColIndex)])]
      sortingDirection = request.GET['sSortDir_'+str(sortedColIndex)]
      if sortingDirection == 'desc':
        sortedColName = '-'+sortedColName
      asortingCols.append(sortedColName)  
    querySet = querySet.order_by(*asortingCols)
  #apply filtering by value sent by user
  if not 'sSearch' in request.GET or not request.GET['sSearch']:
    customSearch = '' #default value
  else:
    customSearch = request.GET['sSearch'].encode('utf-8');

  ## PERSONALIZED FILTER
#  if customSearch !='' and customSearch[0] == '>':
  if customSearch !='':
  
    outputQ = None
    filter = []

    if '&' in customSearch:
      customSearchs = customSearch.split('&')
    else:
      customSearchs = [customSearch]

    for customSearch in customSearchs:

      if ':' in customSearch:
        filter = customSearch.split(':')
        try:
          key = dic[filter[0]]
        except:
          filter[1] = ''

        if filter[1] != '':
          kwargz = {key+"__icontains" : filter[1]}  
          q = Q(**kwargz)
          outputQ = q
          querySet = querySet.filter(outputQ)

      if '>' in customSearch:
        filter = customSearch.split('>')
        try:
          key = dic[filter[0]]
        except:
          filter[1] = ''

        if filter[1] != '':
          kwargz = {key+"__gt" : filter[1]}
          q = Q(**kwargz)
          outputQ = q
          querySet = querySet.filter(outputQ)

      if '<' in customSearch:
        filter = customSearch.split('<')
        try:
          key = dic[filter[0]]
        except:
          filter[1] = ''

        if filter[1] != '':
          kwargz = {key+"__lt" : filter[1]}
          q = Q(**kwargz)
          outputQ = q
          querySet = querySet.filter(outputQ)

  if type == 'testreasons':
    from django.db.models import Count
    querySet = querySet.values('reason','site__name').annotate(Count('id'))

  #count how many records match the final criteria
  iTotalRecords = iTotalDisplayRecords = querySet.count()
  #get the slice
  querySet = querySet[startRecord:endRecord]
  #prepare the JSON with the response
  if not 'sEcho' in request.GET or not request.GET['sEcho']:
    sEcho = '0' #default value
  else:
    sEcho = request.GET['sEcho'] #this is required by datatables
  jstonString = render_to_string(jsonTemplatePath, locals())
  return HttpResponse(jstonString, mimetype="application/javascript")
