#/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

# BASE_CLASS_NAMES_FK_RELATED

#This is a list with the names of the xxxBase classes
#involved in FK relations. Pointing object or pointed
#one.

BASE_CLASS_NAMES_FK_RELATED = [
                               "BackendBase",
                               "CloudBase",
                               "CloudFeedBase",
                               "DspatternBase",
                               "GangaBinBase",
                               "HostBase",
                               "InputTypeBase",
                               "JotTemplateBase",
                               "MetricBase",
                               "MetricTypeBase",
                               "MetricPermBase",
                               "OptionFileBase",
                               "SiteBase",
                               "SiteFeedBase",
                               "SiteMetricBase",
                               "SummaryRobotBase",
                               "SummaryTestBase",
                               "SummaryTestSiteBase",
                               "TemplateBase",
                               "TemplateBackend",
                               "TemplateCloudBase",
                               "TemplateDspatternBase",
                               "TemplateFeedBase",
                               "TemplateHostBase",
                               "TemplateSiteBase",
                               "TemplateUserBase",
                               "TestBase",
                               "TestBackendBase",
                               "TestCloudBase",
                               "TestDspatternBase",
                               "TestFeedBase",
                               "TestHostBase",
                               "TestLogBase",
                               "TestMetricBase",
                               "TestOptionBase",
                               "TestSiteBase", 
                               "TestStateBase",
                               "TestUserBase",
                               "ResultBase",
                               "UserCodeBase",
                               "UsgSiteBase",
                              ]

#/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

# FK_LIST

#In this list, every single FK relation between abstract (xxBase) classes is defined.
#There is no need to write the field in the abstract model.

#The sintax of the FK is the following:
#(Obj1,Obj2,name_of_fk_in_Obj2_pointing_to_Obj1,args)

FK_LIST = [
           ('Backend','Site','backend',{}),
           ('Backend','TemplateBackend','backend',{}),
           ('Backend','TestBackend','backend',{}),
           ('Cloud','CloudFeed','cloud',{}),
           ('Cloud','Site','cloud',{}),
           ('Cloud','TemplateCloud','cloud',{}),
           ('Cloud','TestCloud','cloud',{}),
           ('Dspattern','TemplateDspattern','dspattern',{}),
           ('Dspattern','TestDspattern','dspattern',{}),
           ('GangaBin','Template','gangabin',{}),
           ('GangaBin','Test','gangabin',{}),
           ('Host','TemplateHost','host',{}),
           ('Host','Test','host',{'null':'True'}),
           ('Host','TestHost','host',{}),
           ('InputType','Template','inputtype',{}),
           ('InputType','Test','inputtype',{}),
           ('JobTemplate','Template','jobtemplate',{}),
           ('JobTemplate','Test','jobtemplate',{}),
           ('Metric','SiteMetric','metric',{}),
           ('Metric','TestMetric','metric',{}),
           ('MetricPerm','Template','metricperm',{}),
           ('MetricPerm','Test','metricperm',{}),
           ('MetricType','Metric','metric_type',{}),
           ('OptionFile','Template','optionfile',{}),
           ('OptionFile','Test','optionfile',{}),
           ('Site','SiteFeed','site',{}),
           ('Site','SiteMetric','site',{}),
           ('Site','SummaryRobot','site',{'unique':True}),
           ('Site','Result','site',{}),
           ('Site','TemplateSite','site',{}),
           ('Site','TestSite','site',{}),
           ('Site','UsgSite','site',{}),
           ('Template','TemplateBackend','template',{}),
           ('Template','TemplateCloud','template',{}),
           ('Template','TemplateDspattern','template',{}),
           ('Template','TemplateFeed','template',{}),
           ('Template','TemplateHost','template',{}),
           ('Template','TemplateSite','template',{}),
           ('Template','TemplateUser','template',{}),
           ('Template','Test','template',{'help':'You can not add ACTIVE FUNCTIONAL templates.'}),
           ('Test','TestFeed','test',{}),
           ('Test','TestMetric','test',{}),
           ('Test','SiteMetric','test',{}),
           ('Test','SummaryTest','test',{'unique':True}),
           ('Test','SummaryTestSite','test',{}),
           ('Test','Result','test',{}),
           ('Test','TestBackend','test',{}),
           ('Test','TestCloud','test',{}),
           ('Test','TestDspattern','test',{}),
           ('Test','TestHost','test',{}),
           ('Test','TestLog','test',{}),
           ('Test','TestSite','test',{}),
           ('Test','TestState','test',{}),
           ('Test','TestUser','test',{}),
           ('TestOption','Template','testoption',{}),
           ('TestOption','Test','testoption',{}),
           ('TestSite','SummaryTestSite','test_site',{}),
           ('UserCode','Template','usercode',{}),
           ('UserCode','Test','usercode',{}),
         ]

#/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

# BASE_CLASS_NAMES_M2M_RELATED

#This is a list with the names of the xxxBase classes
#involved in M2M relations. Pointing object or pointed
#one.

BASE_CLASS_NAMES_M2M_RELATED = [
                               "MetricTypeBase",
                               "MetricPermissionBase",
                              ]

#/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

# M2M_LIST

#In this list, every single M2M relation between abstract (xxBase) classes is defined.
#There is no need to write the field in the abstract model.

#The sintax of the M2M is the following:
#(Obj1,Obj2,name_of_m2m_in_Obj2_pointing_to_Obj1,args)

M2M_LIST = [
           ('MetricType','MetricPerm','index',{}),
           ('MetricType','MetricPerm','summary',{}),
           ('MetricType','MetricPerm','pertab',{}),
           ('MetricType','MetricPerm','cron_allowed',{}),
           ]

#/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\


#UNIQUE_TOGETHER_DIC

#In this dictionary, every single unqique_together meta attribute between abstract (xxBase) classes is defined.
#There is no need to write the field in the abstract model. (Some nice fireworks will appear if you do so.)

#The sintax of the unique_together is the following:
#(Obj1,(keys))

UNIQUE_TOGETHER_DIC = {
                        'ResultBase'            : ('ganga_jobid','ganga_subjobid','test'),
                        'SummaryTestSiteBase'   : ('test_site','test'),
                        'TemplateBackendBase'   : ('backend','template'),
                        'TemplateCloudBase'     : ('cloud','template'),
                        'TemplateDspatternBase' : ('dspattern','template'),
                        'TemplateHostBase'	: ('host','template'),
                        'TemplateSiteBase'      : ('site','template'),
                        'TemplateUserBase'      : ('user','template'),
                        'TestBackendBase'       : ('backend','test'),
                        'TestCloudBase'         : ('cloud','test'), 
                        'TestDspatternBase'     : ('dspattern','test'),
                        'TestHostBase'          : ('host','test'),
                        'TestSiteBase'          : ('site','test'),
                        'TestStateBase'         : ('ganga_jobid','test'),
                        'TestUserBase'          : ('test','user'),
                      }


#/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

