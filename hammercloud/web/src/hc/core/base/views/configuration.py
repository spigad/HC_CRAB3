"""This dictionary provides configurations for the apps."""

# TODO(rmedrano): move this to a more common place, like local_settings.py


PARTICULARITIES = {'atlas': {'cloud': 'Cloud',
                             'base_template': 'atlas/base.html',
                             'sls': 'HC.ATLAS',
                             'monitoring_url': 'http://panda.cern.ch/server/pandamon/query?job=',
                             'metrics': {'queue': 'timetorun',
                                         'stagein': 'pandatime2',
                                         'running': 'pandatime3',
                                         'stageout': 'pandatime4'},
                             },
                   'cms': {'cloud': 'Region',
                           'base_template': 'cms/base.html',
                           'sls': 'HC.CMS',
                           'monitoring_url': 'http://dashb-cms-job.cern.ch/dashboard/request.py/detailView?schedulerJobId=',
                           'metrics': {'queue': None,
                                       'stagein': None,
                                       'running': None,
                                       'stageout': None},
                           },
                   'lhcb': {'cloud': 'T1',
                            'base_template': 'core/app/base.html',
                            'sls': 'HC.LHCb',
                            'monitoring_url': None,
                            'metrics': {'queue': None,
                                        'stagein': None,
                                        'running': None,
                                        'stageout': None},
                            }
                   }
