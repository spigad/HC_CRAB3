from hc.core.base.views.decorator import GenView_dec

@GenView_dec()
def index(request):
  pass

@GenView_dec()
def clouds(request):
  pass

@GenView_dec()
def cloud(request,cloud_id):
  pass

@GenView_dec()
def dspatterns(request):
  pass

@GenView_dec()
def files(request):
  pass

@GenView_dec()
def hosts(request):
  pass

@GenView_dec()
def host(request,host_id):
  pass

@GenView_dec()
def sites(request):
  pass

@GenView_dec()
def site(request,site_id):
  pass

@GenView_dec()
def templates(request):
  pass

@GenView_dec()
def template(request,template_id):
  pass

@GenView_dec()
def test(request,test_id):
  pass

@GenView_dec()
def testlist(request,list_type):
  pass

@GenView_dec()
def get_list(request,type,test_id):
  pass

@GenView_dec()
def testaccordion(request,test_id,type):
  pass

@GenView_dec()
def ajaxtestmetrics(request,test_id):
  pass

@GenView_dec()
def ajaxsitemetrics(request,test_id):
  pass

@GenView_dec()
def ajaxjournal(request,test_id):
  pass

@GenView_dec()
def robot(request):
  pass
