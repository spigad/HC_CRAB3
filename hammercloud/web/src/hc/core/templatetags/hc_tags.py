from django import  template
from hc.core.utils.generic.truncate import truncateList,truncateString
import re

register = template.Library()

def hostEntity(value):
  '''
  Filter for Django template system that given a string return the first
  token before the first dot, used to get the name of the host
  from an url of the type: 'voatlas49.cern.ch'
  '''
  try:
    host = value.name
    return host.split('.',1)[0]
  except:
    return ''

def trunc(list,args):
  return truncateList(list,args)

def chop(string,args):
  return truncateString(string,args)

def jobid_linkify(value):
  '''
  Looks for PanDA IDs and changes them to HTML links to PanDAmon.
  '''
  try:
    return re.compile(r'([0-9]{10})').sub(lambda m: '<a href="http://panda.cern.ch/server/pandamon/query?job=%s">%s</a>' % (m.group(1), m.group(1)), value)
  except:
    return value

def cutcsv(value,arg):

  try:
    ITEMS = arg
    list = ''
    items = value.split(',')
    for i in range(0,min(len(items),ITEMS)):
      list += str(items[i])+','

    if len(items)-ITEMS > 0:
        list += '%d&nbsp;more...'%(len(items)-ITEMS)
    else:
        list = list[:-1]    

  except:
    list = '--'

  return list

register.filter('cutcsv',cutcsv)
register.filter('hostEntity',hostEntity)
register.filter('trunc',trunc)
register.filter('chop',chop)
register.filter('jobid',jobid_linkify)
