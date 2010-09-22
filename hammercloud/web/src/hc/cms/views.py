from hc.core.base.views.decorator import GenView_dec
from hc.core.base.views.generic import logout

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
def sites(request):
  pass

@GenView_dec()
def site(request,site_id):
  pass

@GenView_dec()
def template(request,template_id):
  pass

@GenView_dec()
def test(request,test_id):
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

