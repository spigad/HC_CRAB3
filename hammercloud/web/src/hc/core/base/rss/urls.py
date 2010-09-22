from django.conf.urls.defaults import *
from hc.core.base.rss.feeds import *

urlpatterns = patterns('',
   url(r'^feed/$'                                                         , HCEntriesFeed()),
   url(r'^feed/app/(?P<app>[a-z]+)/$'                                     , AppEntriesFeed()),
   url(r'^feed/app/(?P<app>[a-z]+)/cloud/(?P<cloud_id>\d+)/$'             , CloudEntriesFeed()),
   url(r'^feed/app/(?P<app>[a-z]+)/site/(?P<site_id>\d+)/$'               , SiteEntriesFeed()),
   url(r'^feed/app/(?P<app>[a-z]+)/template/(?P<template_id>\d+)/$'       , TemplateEntriesFeed()),
   url(r'^feed/app/(?P<app>[a-z]+)/test/(?P<test_id>\d+)/$'               , TestEntriesFeed()),
)

