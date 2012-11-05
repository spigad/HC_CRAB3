from django.db.models  import  Q
from django.template.loader import render_to_string
from django.http import HttpResponse


def escape_json_string(string):
  """Returns the string JSONnized, if it is a string."""
  if type(string) in (unicode, str):
    return string.replace('\n', '\\n').replace('\t', '\\t').replace('\r', '\\r')
  return string


def get_records(request, querySet, columnIndexNameMap, searchableColumns, jsonTemplatePath, type, app, *args):
  """Gets a set of records based on a query set and columns names for AJAX queries."""
  # Dic will hold the matching between the column search names and the model fields.
  # TODO(rmedrano): remove this ugly dictionary from here. This is a *pain*.
  dic = {}
  if "testlist" in type:
    dic = {'id': 'test_id',
           'status': 'test__state',
           'host': 'test__host__name',
           'cloud': 'clouds',
           'template': 'test__template__description',
           'inputtype': 'test__inputtype__type',
           'starttime': 'test__starttime',
           'endtime': 'test__endtime',
           'sites': 'nr_sites',
           'jobs': 'total',
           }
    querySet = querySet.select_related('test__template', 'test__host', 'test__inputtype')
  elif type == "testsites":
    dic = {'site': 'test_site__site__name',
           'submitted': 'submitted',
           'running': 'running',
           'completed': 'completed',
           'failed': 'failed',
           'eff': 'c_cf',
           'total': 'total',
           'datasets': 'test_site__site__num_datasets_per_bulk',
           'queue': 'test_site__min_queue_depth',
           'max_running': 'test_site__max_running_jobs',
           'resubmit': 'test_site__resubmit_enabled',
           'force':'test_site__resubmit_force',
           }
    querySet = querySet.select_related('test_site', 'test_site__site')
  elif type == "testsummary":
    dic = {'site': 'testsite__site__name'}
    dic.update(searchableColumns)
    querySet = querySet.select_related('test_site', 'test_site__site')
  elif type == "robotlist":
    dic = {'site': 'site__name',
           'completed': 'completed',
           'failed': 'failed',
           'total': 'total',
           'efficiency': 'efficiency',
           'efficiencyNorm': 'efficiencyNorm',
           'errorrate': 'errorrate',
           'errorrateNorm': 'errorrateNorm',
           }
  elif type == "testjobs":
    dic = {'status': 'ganga_status',
           'site': 'site__name',
           'job': 'ganga_jobid',
           'subjob': 'ganga_subjobid',
           'backendID': 'backendID',
           'reason': 'reason',
           'submit': 'submit_time',
           'start': 'start_time',
           'end': 'stop_time',
           }
    querySet = querySet.select_related('site')
  elif type == 'robotjobs':
    dic = {'status': 'ganga_status',
           'site': 'site__name',
           'test': 'test__id',
           'job': 'ganga_jobid',
           'subjob': 'ganga_subjobid',
           'backendID': 'backendID',
           'reason': 'reason',
           'submit': 'submit_time',
           'start': 'start_time',
           'end': 'stop_time',
           }
  elif type == 'testreasons':
    dic = {'site': 'site__name',
           'reason':'reason',
           }

  #Safety measure. If someone messes with iDisplayLength manually, we clip it to
  #the max value of 100.
  if not 'iDisplayLength' in request.GET or not request.GET['iDisplayLength']:
    iDisplayLength = 50 #default value
  else:
    iDisplayLength = min(int(request.GET['iDisplayLength']), 100)
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
      sortedColName = columnIndexNameMap[int(request.GET['iSortCol_' + str(sortedColIndex)])]
      sortingDirection = request.GET['sSortDir_' + str(sortedColIndex)]
      if sortingDirection == 'desc':
        sortedColName = '-' + sortedColName
      asortingCols.append(sortedColName)
    querySet = querySet.order_by(*asortingCols)
  #apply filtering by value sent by user
  if not 'sSearch' in request.GET or not request.GET['sSearch']:
    customSearch = '' #default value
  else:
    customSearch = request.GET['sSearch'].encode('utf-8');

  ## PERSONALIZED FILTER
  # We build a personalized Q object with the filter query.
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
          kwargz = {key + "__icontains": filter[1]}
          outputQ = Q(**kwargz)
          querySet = querySet.filter(outputQ)
      if '>' in customSearch:
        filter = customSearch.split('>')
        try:
          key = dic[filter[0]]
        except:
          filter[1] = ''
        if filter[1] != '':
          kwargz = {key + "__gt": filter[1]}
          outputQ = Q(**kwargz)
          querySet = querySet.filter(outputQ)
      if '<' in customSearch:
        filter = customSearch.split('<')
        try:
          key = dic[filter[0]]
        except:
          filter[1] = ''
        if filter[1] != '':
          kwargz = {key + "__lt": filter[1]}
          outputQ = Q(**kwargz)
          querySet = querySet.filter(outputQ)

  if type == 'testreasons':
    from django.db.models import Count
    querySet = querySet.values('reason', 'site__name').annotate(Count('id'))

  #count how many records match the final criteria
  iTotalRecords = iTotalDisplayRecords = querySet.count()
  #get the slice
  querySet = querySet[startRecord:endRecord]
  #prepare the JSON with the response
  if not 'sEcho' in request.GET or not request.GET['sEcho']:
    sEcho = '0' #default value
  else:
    sEcho = request.GET['sEcho'] #this is required by datatables
  escaped_locals = locals()
  for k in escaped_locals:
    escaped_locals[k] = escape_json_string(escaped_locals[k])
  jstonString = render_to_string(jsonTemplatePath, escaped_locals)
  return HttpResponse(jstonString, mimetype="application/javascript")
