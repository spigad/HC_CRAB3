from hc.core.base.views.decorator import GenView_dec
from django.contrib.auth.decorators import login_required

@GenView_dec()
def index(request):
  pass

@login_required
@GenView_dec()
def backends(request):
  pass

@login_required
@GenView_dec()
def clouds(request):
  pass

@login_required
@GenView_dec()
def cloud(request,cloud_id):
  pass

@login_required
@GenView_dec()
def dspatterns(request):
  pass

@login_required
@GenView_dec()
def hosts(request):
  pass

@login_required
@GenView_dec()
def host(request,host_id):
  pass

@login_required
@GenView_dec()
def jobtemplates(request,jobtemplate_id):
  pass

@login_required
@GenView_dec()
def metric_types(request):
  pass

@login_required
@GenView_dec()
def metric_permissions(request,metric_permission_id):
  pass

@login_required
@GenView_dec()
def metric_type(request,metric_type_id):
  pass

@GenView_dec()
def more(request):
  pass

@login_required
@GenView_dec()
def optionfiles(request,optionfile_id):
  pass

@login_required
@GenView_dec()
def testoptions(request,testoption_id):
  pass

@login_required
@GenView_dec()
def sites(request):
  pass

@login_required
@GenView_dec()
def site(request,site_id):
  pass

@login_required
@GenView_dec()
def templates(request):
  pass

@login_required
@GenView_dec()
def template(request,template_id):
  pass

@GenView_dec()
def test(request,test_id):
  pass

@GenView_dec()
def testlist(request,list_type):
  pass

@login_required
@GenView_dec()
def testclone(request,test_id):
  pass

@login_required
@GenView_dec()
def testmodify(request,test_id):
  pass

@login_required
@GenView_dec()
def usercodes(request, usercode_id):
  pass

@GenView_dec()
def get_list(request,type,test_id):
  pass

@GenView_dec()
def testaccordion(request,test_id,type):
  pass

#######################################################
## AJAX BLOCK
#######################################################

@GenView_dec()
def ajaxtestmetrics(request,test_id):
  pass

@GenView_dec()
def ajaxtestsites(request,test_id):
  pass

@GenView_dec()
def ajaxtestlogs(request,test_id):
  pass

@login_required
@GenView_dec()
def ajaxtestlogreport(request, test_id):
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

@GenView_dec()
def statistics(request):
  pass
