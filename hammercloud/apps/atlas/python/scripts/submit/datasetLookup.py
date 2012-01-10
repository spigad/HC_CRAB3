#!/usr/bin/env python

import fnmatch, time, sys
from dq2.clientapi.DQ2 import DQ2
from dq2.info.TiersOfATLAS import ToACache
from cPickle import dump, load

if __name__ == '__main__':

    tstart = time.time()
    print 'Start: %s' %(time.ctime())

    if sys.argv:
        picklefile = sys.argv[1]
    else:
        picklefile = 'datasetCache.pickle'

    #try:
    #    inp=open(picklefile,'rb')
    #    datasetsDict=load(inp)
    #    inp.close()
    #except:
    #    datasetsDict = {}

    dq2 = DQ2()
    sites = []
    tokens = ['DATADISK', 'LOCALGROUPDISK', 'USERDISK', 'SCRATCHDISK', 'HOTDISK', 'PRODDISK', 'CALIBDISK' ] 
    #tokens = ['DATADISK', 'LOCALGROUPDISK' ]
    #tokens = ['DATADISK' ] 

    datasetsDict = {}

    for site in ToACache.sites:
        for token in tokens:
            if site.endswith(token) and not site in sites:
                sites.append(site)

    #sites = sites[:3]

    print '%s locations' %(len(sites))
    ndatasets = 0

    for location in sites:
        print time.ctime()
        print "%s" %(location)
        temp = dq2.listDatasetsByNameInSite(site=location, complete=None, name=None, p=None, rpp=None, group=None )
        datasets = list(temp)        
        ndatasets += len(datasets)
        print "%s datasets" %(len(datasets))
        print time.ctime()
        
        datasetsDict[location] = datasets

    out = open(picklefile,'wb')
    dump(datasetsDict,out)
    out.close()

    print 'Datasets total: %s' %(ndatasets)
    
    tend = time.time()
    print 'End: %s' %( time.ctime() )
    print 'Duration: %5.2f s' %(tend - tstart )
    
