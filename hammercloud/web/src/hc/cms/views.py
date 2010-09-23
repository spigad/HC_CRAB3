from hc.core.base.views.decorator import GenView_dec
from django.contrib.auth.decorators import login_required

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
def hosts(request):
  pass

@GenView_dec()
def host(request,host_id):
  pass

@GenView_dec()
def jobtemplates(request,jobtemplate_id):
  pass

@GenView_dec()
def metric_types(request):
  pass

@GenView_dec()
def metric_type(request,host_id):
  pass

@GenView_dec()
def optionfiles(request,optionfile_id):
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
def usercodes(request, usercode_id):
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

#######################################################
## ROBOT BLOCK
#######################################################

@GenView_dec()
def robot(request):
  pass


#######################################################
## STATS BLOCK
#######################################################

@GenView_dec()
def stats(request):
  pass

@login_required
@GenView_dec()
def statistics(request):
  pass
