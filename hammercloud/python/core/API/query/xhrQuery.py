from urllib2 import URLError,HTTPError,Request,urlopen
import socket

class XhrQuery:

  
  def get(self,app,queryStr):

    str = 'http://hammercloud.cern.ch/hc/app/%s/xhr/json/%s'%(app,queryStr)

    try:
      #Set 200 secs timeout
      socket.setdefaulttimeout(200)
      request = Request(str)
      f = urlopen(request)
      result = f.read()
      f.close()
      return (1,result)
    except HTTPError, e:
      str = '%s -> %s'%(e,str)
    except URLError, e:
      str = '%s -> %s'%(e,str)

    return (0,str)
