from django.contrib.auth.decorators import login_required
from django.views.decorators.cache import cache_page, never_cache
from hc.core.base.views.decorator import GenView_dec

"""Generic view module of HammerCloud for ATLAS.

Defines the generic views as empty functions which will get 'meat' by the view
generator decorator based on the parameters. All the caching settings are set
in this declaration.
"""

LONG_CACHE = 6 * 60 * 60  # 6 hours.
SHORT_CACHE = 60 * 60  # 1 hour.
MINI_CACHE = 5 * 60  # 5 minutes.


#######################################################
# GENERAL VIEWS
#######################################################

@GenView_dec(params={'on': True,
                     'other': 'nightly'})
def index(request):
    pass


@login_required
@GenView_dec(params={'on': True})
def backends(request):
    pass


@login_required
@GenView_dec(params={'on': True})
def clouds(request):
    pass


@login_required
@GenView_dec(params={'on': True})
def cloud(request, cloud_id):
    pass


@login_required
@GenView_dec(params={'on': True})
def dspatterns(request):
    pass


@login_required
@GenView_dec(params={'on': True})
def hosts(request):
    pass


@login_required
@GenView_dec(params={'on': True})
def host(request, host_id):
    pass


@login_required
@GenView_dec(params={'on': True})
def jobtemplates(request, jobtemplate_id):
    pass


@login_required
@GenView_dec(params={'on': True})
def metric_types(request):
    pass


@login_required
@GenView_dec(params={'on': True})
def metric_permissions(request, metric_permission_id):
    pass


@login_required
@GenView_dec(params={'on': True})
def metric_type(request, metric_type_id):
    pass


@GenView_dec(params={'on': True})
def more(request):
    pass


@login_required
@GenView_dec(params={'on': True})
def optionfiles(request, optionfile_id):
    pass


@login_required
@GenView_dec(params={'on': True})
def testoptions(request, testoption_id):
    pass


@login_required
@GenView_dec(params={'on': True})
def sites(request):
    pass


@login_required
@GenView_dec(params={'on': True})
def site(request, site_id):
    pass


@login_required
@GenView_dec(params={'on': True})
def templates(request):
    pass


@GenView_dec(params={'on': True})
def template(request, template_id):
    pass


@GenView_dec(params={'on': True})
def test(request, test_id):
    pass


@GenView_dec(params={'on': True})
def testlist(request, list_type):
    pass


@login_required
@GenView_dec(params={'on': True})
def testclone(request, test_id):
    pass


@login_required
@GenView_dec(params={'on': True})
def testmodify(request, test_id):
    pass


@login_required
@GenView_dec(params={'on': True})
def usercodes(request, usercode_id):
    pass


@GenView_dec(params={'on': True})
def get_list(request, list_type, list_id):
    pass


@GenView_dec(params={'on': True})
def testaccordion(request, test_id, test_type):
    pass


#######################################################
# AJAX VIEWS
#######################################################

@GenView_dec(params={'on': True})
def ajaxtestmetrics(request, test_id):
    pass


@GenView_dec(params={'on': True})
def ajaxtestsites(request, test_id):
    pass


@GenView_dec(params={'on': True})
def ajaxtestjobs(request, test_id):
    pass


@GenView_dec(params={'on': True})
def ajaxtestjobsbysite(request, test_id, site_id):
    pass


@GenView_dec(params={'on': True})
def ajaxtestevolution(request, test_id):
    pass


@GenView_dec(params={'on': True})
def ajaxtestlogs(request, test_id):
    pass


@GenView_dec(params={'on': True})
def ajaxtestalarms(request, test_id):
    pass


@login_required
@GenView_dec(params={'on': True})
def ajaxtestlogreport(request, test_id):
    pass


@GenView_dec(params={'on': True})
def ajaxreports(request, site_id):
    pass


@GenView_dec(params={'on': True})
def ajaxnightly(request):
    pass


#######################################################
# ROBOT VIEWS
#######################################################

@cache_page(LONG_CACHE)
@GenView_dec(params={'on': True})
def robot(request):
    pass


@cache_page(LONG_CACHE)
@GenView_dec(params={'on': True})
def robotsite(request, site_id):
    pass


@cache_page(LONG_CACHE)
@GenView_dec(params={'on': True})
def robotlist(request):
    pass


@cache_page(LONG_CACHE)
@GenView_dec(params={'on': True})
def robotstats(request):
    pass


@cache_page(LONG_CACHE)
@GenView_dec(params={'on': True})
def robotjobs(request):
    pass


@cache_page(LONG_CACHE)
@GenView_dec(params={'on': True})
def historical(request):
    pass


@cache_page(LONG_CACHE)
@GenView_dec(params={'on': True})
def incidents(request):
    pass


@cache_page(SHORT_CACHE)
@GenView_dec(params={'on': True,
                     'autoexclusion': {'option_name': 'autoexclusion',
                                       'option_value': 'disable',
                                       'site__name__startswith': 'ANALY'},
                     'extra_report': 'hc.atlas.models.blacklisting_panda_report'})
def autoexclusion(request):
    pass


@never_cache
@GenView_dec(params={'on': True})
def autoexclusion_set(request):
    pass


@never_cache
@login_required
@GenView_dec(params={'on': True})
def autoexclusion_control(request):
    pass


@never_cache
@GenView_dec(params={'on': True})
def autoexclusion_control_action(request):
    pass


@never_cache
@GenView_dec(params={'on': True})
def contact_set(request):
    pass


@never_cache
@GenView_dec(params={'on': True})
def contact_unset(request):
    pass


@cache_page(SHORT_CACHE)
@GenView_dec(params={'on': True})
def robot_ssb(request):
    pass


@GenView_dec(params={'on': True})
def nightly(request):
    pass


#######################################################
# STATS VIEWS
#######################################################

@GenView_dec(params={'on': True})
def reports(request):
    pass


@GenView_dec(params={'on': False})
def evolution(request):
    pass


@GenView_dec(params={'on': False})
def stats(request):
    pass


@GenView_dec(params={'on': False})
def statistics(request):
    pass


@cache_page(MINI_CACHE)
@GenView_dec(params={'on': True})
def joberrors(request):
    pass


@cache_page(MINI_CACHE)
@GenView_dec(params={'on': True,
                     'field': 'reason',
                     'extra': 'reason'})
def abortedjobs(request):
    pass


@cache_page(MINI_CACHE)
@GenView_dec(params={'on': True,
                     'field': 'exit_status_2',
                     'extra': 'reason'})
def failedjobs(request):
    pass
