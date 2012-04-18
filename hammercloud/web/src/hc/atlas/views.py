from hc.core.base.views.decorator import GenView_dec
from django.contrib.auth.decorators import login_required
from django.views.decorators.cache import cache_page

@cache_page(60 * 5)
@GenView_dec(params={'on':True})
def index(request):
  pass

@login_required
@GenView_dec(params={'on':True})
def backends(request):
  pass

@login_required
@GenView_dec(params={'on':True})
def clouds(request):
  pass

@login_required
@GenView_dec(params={'on':True})
def cloud(request,cloud_id):
  pass

@login_required
@GenView_dec(params={'on':True})
def dspatterns(request):
  pass

@login_required
@GenView_dec(params={'on':True})
def hosts(request):
  pass

@login_required
@GenView_dec(params={'on':True})
def host(request,host_id):
  pass

@login_required
@GenView_dec(params={'on':True})
def jobtemplates(request,jobtemplate_id):
  pass

@login_required
@GenView_dec(params={'on':True})
def metric_types(request):
  pass

@login_required
@GenView_dec(params={'on':True})
def metric_permissions(request,metric_permission_id):
  pass

@login_required
@GenView_dec(params={'on':True})
def metric_type(request,metric_type_id):
  pass

@GenView_dec(params={'on':True})
def more(request):
  pass

@login_required
@GenView_dec(params={'on':True})
def optionfiles(request,optionfile_id):
  pass

@login_required
@GenView_dec(params={'on':True})
def testoptions(request,testoption_id):
  pass

@login_required
@GenView_dec(params={'on':True})
def sites(request):
  pass

@login_required
@GenView_dec(params={'on':True})
def site(request,site_id):
  pass

@login_required
@GenView_dec(params={'on':True})
def templates(request):
  pass

#@login_required
@GenView_dec(params={'on':True})
def template(request,template_id):
  pass

@GenView_dec(params={'on':True})
def test(request,test_id):
  pass

@GenView_dec(params={'on':True})
def testlist(request,list_type):
  pass

@login_required
@GenView_dec(params={'on':True})
def testclone(request,test_id):
  pass

@login_required
@GenView_dec(params={'on':True})
def testmodify(request,test_id):
  pass

@login_required
@GenView_dec(params={'on':True})
def usercodes(request, usercode_id):
  pass

@GenView_dec(params={'on':True})
def get_list(request,type,id):
  pass

@GenView_dec(params={'on':True})
def testaccordion(request,test_id,type):
  pass

#######################################################
## AJAX BLOCK
#######################################################

@GenView_dec(params={'on':True})
def ajaxtestmetrics(request,test_id):
  pass

@GenView_dec(params={'on':True})
def ajaxtestsites(request,test_id):
  pass

@GenView_dec(params={'on':True})
def ajaxtestjobs(request,test_id):
  pass

@GenView_dec(params={'on':True})
def ajaxtestjobsbysite(request,test_id,site_id):
  pass

@GenView_dec(params={'on':True})
def ajaxtestevolution(request,test_id):
  pass

@GenView_dec(params={'on':True})
def ajaxtestlogs(request,test_id):
  pass

@GenView_dec(params={'on':True})
def ajaxtestalarms(request,test_id):
  pass

@login_required
@GenView_dec(params={'on':True})
def ajaxtestlogreport(request, test_id):
  pass

#######################################################
## ROBOT BLOCK
#######################################################

@GenView_dec(params={'on':True})
def robot(request):
  pass

@GenView_dec(params={'on':True})
def robotsite(request, site_id):
  pass

@GenView_dec(params={'on':True})
def robotlist(request):
  pass

@GenView_dec(params={'on':True})
def robotstats(request):
  pass

@GenView_dec(params={'on':True})
def robotjobs(request):
  pass

@GenView_dec(params={'on':True})
def historical(request):
  pass

@GenView_dec(params={'on':True})
def incidents(request):
  pass

@cache_page(60 * 30)
@GenView_dec(params={'on':True,'autoexclusion':{'option_name':'autoexclusion','option_value':'disable','site__name__startswith':'ANALY'},'extra_report':'hc.atlas.models.blacklisting_panda_report'})
def autoexclusion(request):
  pass

@GenView_dec(params={'on':True})
def autoexclusion_set(request):
  pass

@GenView_dec(params={'on':True})
def contact_set(request):
  pass

@GenView_dec(params={'on':True})
def contact_unset(request):
  pass

@GenView_dec(params={'on':True})
def robot_ssb(request):
  pass

#######################################################
## STATS BLOCK
#######################################################

@GenView_dec(params={'on':True})
def evolution(request):
  pass

@GenView_dec(params={'on':True})
def stats(request):
  pass

@GenView_dec(params={'on':True})
def statistics(request):
  pass

@cache_page(60 * 60 * 2)
@GenView_dec(params={'on':True})
def joberrors(request):
  pass

@GenView_dec(params={'on':True,'field':'reason','extra':'reason'})
def abortedjobs(request):
  pass

@GenView_dec(params={'on':True,'field':'exit_status_2','extra':'reason'})
def failedjobs(request):
  pass
