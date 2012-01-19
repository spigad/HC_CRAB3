#!/usr/bin/env python

import fnmatch, time, sys
from cPickle import dump, load
from dq2.info.TiersOfATLAS import ToACache

picklefile= '/data/hc/apps/atlas/python/scripts/submit/datasetCache.pickle'

def loadDatasetsDict(picklefile='datasetCache.pickle'):
  _datasetsDict = {}
  print 'Loading _datasetsDict from %s ...' %picklefile
  retry = 0
  while retry<3:
    try:
      inp=open(picklefile,'rb')
      _datasetsDict=load(inp)
      inp.close()
      print '_datasetsDict loaded from %s' %picklefile
      retry = 3
    except:
      _datasetsDict = {}
    if not _datasetsDict:
      print 'ERROR loading _datasetsDict from %s, Try %s ' %(picklefile, retry)
      retry +=1
      time.sleep(30)

  return _datasetsDict

if __name__ == '__main__':

    pattern = ''

    if sys.argv:
        #picklefile = sys.argv[1]
        pattern = sys.argv[2]

    tstart = time.time()
    print 'Start: %s' %(time.ctime())

    tokens = ['DATADISK', 'LOCALGROUPDISK']
    sites = []

    for site in ToACache.sites:
        for token in tokens:
            if site.endswith(token) and not site in sites:
                sites.append(site)

    print '%s locations' %(len(sites))
    ndatasets = 0

    _datasetsDict= {}
    if not _datasetsDict:
        _datasetsDict = loadDatasetsDict(picklefile)

    for location in sites:
        print time.ctime()
        if not _datasetsDict.has_key(location): continue
        print "%s" %(location)
        temp = _datasetsDict[location]
        datasets = list(temp)        
        print "%s datasets" %(len(datasets))
        result = fnmatch.filter(datasets, pattern)
        print "%s datasets match" %(len(result))

        print time.ctime()
        
    
    tend = time.time()
    print 'End: %s' %( time.ctime() )
    print 'Duration: %5.2f s' %(tend - tstart )
