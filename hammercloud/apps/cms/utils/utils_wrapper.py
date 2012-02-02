import commands
from cms.utils import crab_parser

# TODO: Remove this hardlinked path by using $HCAPP and $HCDIR. We need to
#       propagate them up to here.
UTILS_DIR = '/data/hc/apps/cms/utils'
WSPC_DIR = '/data/hc/apps/cms/testdirs/test_%d/gangadir/workspace/gangarbt/LocalXML/%d/output'


def CMS_get_abort_code_from_CRAB(test_id, ganga_jobid, ganga_subjobid):
  '''Returns the abortion code for the job by parsing the LoggingInfo retrieved
     by CRAB in its workspace. The returned tuple is like (code, reason).'''
  results = []
  cmd = '%s/parselog.pl %s' % (UTILS_DIR, ('%s/job/CMSSW_%%d.LoggingInfo' % WSPC_DIR) % (test_id, ganga_jobid, ganga_subjobid + 1))
  status, output = commands.getstatusoutput(cmd)
  if status != 0:
    return None
  for line in iter(output.splitlines()):
    try:
      event, result, status_code = line.split('&')
      if event == 'Abort':
        results.append((result, status_code))
    except:
      continue
  return results


def CMS_get_app_code_from_CRAB(test_id, ganga_jobid, ganga_subjobid):
  '''Returns the application exit code for the job by parsing the stdout file
     of the job retrieved by CRAB.'''
  res_path = ('%s/res' % WSPC_DIR) % (test_id, ganga_jobid)
  return crab_parser.run(jobdir=res_path, jobid=ganga_subjobid + 1)
