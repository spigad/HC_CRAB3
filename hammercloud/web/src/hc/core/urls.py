from django.conf.urls.defaults import *

urlpatterns = patterns('hc.core.views',
  url(r'^$', 'portal', name='portal-view'),
  )

urlpatterns += patterns('django.views.generic.simple',
  ('^app/(?P<app>[a-z]+)/admin/$', 'redirect_to', {'url': '/hc/admin/%(app)s/'}),
  )

urlpatterns += patterns('hc.core.base.views.control',
  url(r'^accounts/logout/$', 'logout', name='logout-view'),
  )

urlpatterns += patterns('',
  url(r'^accounts/login/$', 'django.contrib.auth.views.login', {'template_name': 'core/app/login.html'}, name='login-view'),
)


urlpatterns += patterns('hc.core.base.views.dispatcher',

  url(r'^app/(?P<app>[a-z]+)/$'                               , 'dispatcher', name='index-view'        , kwargs={'func':'index'}),

  #More HC
  url(r'^app/(?P<app>[a-z]+)/backends/$'                      , 'dispatcher', name='backends-view'     , kwargs={'func':'backends'}),
  url(r'^app/(?P<app>[a-z]+)/clouds/$'                        , 'dispatcher', name='clouds-view'       , kwargs={'func':'clouds'}),
  url(r'^app/(?P<app>[a-z]+)/cloud/(?P<cloud_id>\d+)/$'       , 'dispatcher', name='cloud-view'        , kwargs={'func':'cloud'}),
  url(r'^app/(?P<app>[a-z]+)/dspatterns/$'                    , 'dispatcher', name='dspatterns-view'   , kwargs={'func':'dspatterns'}),
  url(r'^app/(?P<app>[a-z]+)/hosts/$'                         , 'dispatcher', name='hosts-view'        , kwargs={'func':'hosts'}),
  url(r'^app/(?P<app>[a-z]+)/host/(?P<host_id>\d+)/$'         , 'dispatcher', name='host-view'         , kwargs={'func':'host'}),
  url(r'^app/(?P<app>[a-z]+)/jobtemplates/$'                  , 'dispatcher', name='jobtemplates-view' , kwargs={'func':'jobtemplates'}),
  url(r'^app/(?P<app>[a-z]+)/metric_types/$'                         , 'dispatcher', name='metric_types-view'     , kwargs={'func':'metric_types'}),
  url(r'^app/(?P<app>[a-z]+)/metric_type/(?P<metric_type_id>\d+)/$'  , 'dispatcher', name='metric_type-view'      , kwargs={'func':'metric_type'}),
  url(r'^app/(?P<app>[a-z]+)/metric_permissions/$'            , 'dispatcher', name='metric_permissions-view' , kwargs={'func':'metric_permissions'}),
  url(r'^app/(?P<app>[a-z]+)/more/$'                          , 'dispatcher', name='more-view'         , kwargs={'func':'more'}),
  url(r'^app/(?P<app>[a-z]+)/optionfiles/$'                   , 'dispatcher', name='optionfiles-view'  , kwargs={'func':'optionfiles'}),
  url(r'^app/(?P<app>[a-z]+)/sites/$'                         , 'dispatcher', name='sites-view'        , kwargs={'func':'sites'}),
  url(r'^app/(?P<app>[a-z]+)/site/(?P<site_id>\d+)/$'         , 'dispatcher', name='site-view'         , kwargs={'func':'site'}),
  url(r'^app/(?P<app>[a-z]+)/templates/$'                     , 'dispatcher', name='templates-view'    , kwargs={'func':'templates'}),
  url(r'^app/(?P<app>[a-z]+)/template/(?P<template_id>\d+)/$' , 'dispatcher', name='template-view'     , kwargs={'func':'template'}),
  url(r'^app/(?P<app>[a-z]+)/testoptions/$'                   , 'dispatcher', name='testoptions-view'  , kwargs={'func':'testoptions'}),
  url(r'^app/(?P<app>[a-z]+)/usercodes/$'                     , 'dispatcher', name='usercodes-view'    , kwargs={'func':'usercodes'}),

  #TEST
  url(r'^app/(?P<app>[a-z]+)/test/(?P<test_id>\d+)/$'         , 'dispatcher', name='test-view'         , kwargs={'func':'test'}),
  url(r'^app/(?P<app>[a-z]+)/testlist/(?P<list_type>[a-z]+)/$', 'dispatcher', name='testlist-view'     , kwargs={'func':'testlist'}),
  url(r'^app/(?P<app>[a-z]+)/testclone/(?P<test_id>\d+)/$'    , 'dispatcher', name='testclone-view'    , kwargs={'func':'testclone'}),
  url(r'^app/(?P<app>[a-z]+)/testmodify/(?P<test_id>\d+)/$'   , 'dispatcher', name='testmodify-view'   , kwargs={'func':'testmodify'}),

  #AJAX
  url(r'^app/(?P<app>[a-z]+)/ajax/test/(?P<test_id>\d+)/(?P<type>[a-z]+)/$'    , 'dispatcher', name='testaccordion-view'  , kwargs={'func':'testaccordion'}),
  url(r'^app/(?P<app>[a-z]+)/ajax/testlogs/(?P<test_id>\d+)/$'                 , 'dispatcher', name='ajaxtestlogs-view' , kwargs={'func':'ajaxtestlogs'}),
  url(r'^app/(?P<app>[a-z]+)/ajax/testlogs/(?P<test_id>\d+)/report$', 'dispatcher', name='ajaxtestlogreport-view', kwargs={'func':'ajaxtestlogreport'}),
  url(r'^app/(?P<app>[a-z]+)/ajax/testalarms/(?P<test_id>\d+)/$'               , 'dispatcher', name='ajaxtestalarms-view' , kwargs={'func':'ajaxtestalarms'}),
  url(r'^app/(?P<app>[a-z]+)/ajax/testmetrics/(?P<test_id>\d+)/$'   , 'dispatcher', name='ajaxtestmetrics-view', kwargs={'func':'ajaxtestmetrics'}),
  url(r'^app/(?P<app>[a-z]+)/ajax/testsites/(?P<test_id>\d+)/$'     , 'dispatcher', name='ajaxtestsites-view'  , kwargs={'func':'ajaxtestsites'}),
  url(r'^app/(?P<app>[a-z]+)/ajax/testjobs/(?P<test_id>\d+)(?:/(?P<site_id>\d+))?/$'      , 'dispatcher', name='ajaxtestjobs-view'  , kwargs={'func':'ajaxtestjobs'}),
  url(r'^app/(?P<app>[a-z]+)/ajax/testevolution/(?P<test_id>\d+)/$' , 'dispatcher', name='ajaxtestevolution-view', kwargs={'func':'ajaxtestevolution'}),
  url(r'^app/(?P<app>[a-z]+)/ajax/(?P<type>[a-z]+)/get_list/(?P<id>\d+)(?:/(?P<filter>\d+))?/$'     , 'dispatcher', name='get_list-view'     , kwargs={'func':'get_list'}),


  #ROBOT
  url(r'^app/(?P<app>[a-z]+)/robot/$'                         , 'dispatcher', name='robot-view'        , kwargs={'func':'robot'}),
  url(r'^app/(?P<app>[a-z]+)/robot/site/(?P<site_id>\d+)/$'   , 'dispatcher', name='robotsite-view'    , kwargs={'func':'robotsite'}),
  url(r'^app/(?P<app>[a-z]+)/robot/list/$'                    , 'dispatcher', name='robotlist-view'    , kwargs={'func':'robotlist'}),
  url(r'^app/(?P<app>[a-z]+)/robot/stats/$'                   , 'dispatcher', name='robotstats-view'   , kwargs={'func':'robotstats'}),
  url(r'^app/(?P<app>[a-z]+)/robot/jobs/$'                    , 'dispatcher', name='robotjobs-view'    , kwargs={'func':'robotjobs'}),
  url(r'^app/(?P<app>[a-z]+)/robot/historical/$'              , 'dispatcher', name='historical-view'   , kwargs={'func':'historical'}),
  url(r'^app/(?P<app>[a-z]+)/robot/incidents/$'               , 'dispatcher', name='incidents-view'    , kwargs={'func':'incidents'}),
  url(r'^app/(?P<app>[a-z]+)/robot/autoexclusion/$'           , 'dispatcher', name='autoexclusion-view', kwargs={'func':'autoexclusion'}),
  url(r'^app/(?P<app>[a-z]+)/autoexclusion/(?P<action>[a-z]+)/(?P<sitename>[A-Za-z0-9_-]+)$'           , 'dispatcher', name='autoexclusion_set-view', kwargs={'func':'autoexclusion_set'}),
  url(r'^app/(?P<app>[a-z]+)/contact/(?P<sitename>[A-Za-z0-9_-]+)/disable$' , 'dispatcher', name='contact_unset-view', kwargs={'func':'contact_unset'}),
  url(r'^app/(?P<app>[a-z]+)/contact/(?P<sitename>[A-Za-z0-9_-]+)/(?P<email>[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.]+\.[a-zA-Z]{2,4}(,[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.]+\.[a-zA-Z]{2,4})*)$' , 'dispatcher', name='contact_set-view', kwargs={'func':'contact_set'}),
  url(r'^app/(?P<app>[a-z]+)/ssb/(?P<list_type>[a-z]+)/$'     , 'dispatcher', name='robot_ssb-view'    , kwargs={'func':'robot_ssb'}),

  #STATS
  url(r'^app/(?P<app>[a-z]+)/stats/$'                         , 'dispatcher', name='stats-view'      , kwargs={'func':'stats'}),
  url(r'^app/(?P<app>[a-z]+)/evolution/$'                     , 'dispatcher', name='evolution-view'  , kwargs={'func':'evolution'}),
  url(r'^app/(?P<app>[a-z]+)/statistics/$'                    , 'dispatcher', name='statistics-view' , kwargs={'func':'statistics'}),
  url(r'^app/(?P<app>[a-z]+)/joberrors/$'                    , 'dispatcher', name='joberrors-view' , kwargs={'func':'joberrors'}),
  url(r'^app/(?P<app>[a-z]+)/abortedjobs/$'                    , 'dispatcher', name='abortedjobs-view' , kwargs={'func':'abortedjobs'}),
  url(r'^app/(?P<app>[a-z]+)/failedjobs/$'                    , 'dispatcher', name='failedjobs-view' , kwargs={'func':'failedjobs'}),


  #XHR
  #url(r'^app/(?P<app>[a-z]+)/xhr/(?P<format>\w+)/$'         , 'dispatcher', name ='xhr-view'      , kwargs={'func':'xhr'}),  

  )

