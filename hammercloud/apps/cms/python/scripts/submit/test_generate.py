import os,time, random
from urllib2 import URLError,HTTPError,Request,urlopen
from datetime import datetime

class TestGenerate:

  def run(self,test,mode):

    print '==%s=='%(mode)

    sites={}
    sitenumjobs={}
    datasetpatterns = []

    test_sites      = test.getTestSites_for_test.all()
    test_dspatterns = test.getTestDspatterns_for_test.all()

    for ts in test_sites:
      sitenumjobs[ts.site.name] = ts.num_datasets_per_bulk
      sites[ts.site.name]       = ts.site.ddm

    for td in test_dspatterns:  
      datasetpatterns.append(td.dspattern.pattern)

    jobtemplate     = test.jobtemplate.path
    usercode        = test.usercode.path
    optionfile      = test.optionfile.path
    inputtype       = test.inputtype

    outputdataset   = str(test.output_dataset) + str(int(time.time()))

    # Path of the working directory
    if os.environ.has_key('HCAPP'):
      basePath = os.environ['HCAPP']
    else:
      basePath = '/tmp'

    #Jobtemplate
    jobtemplate = basePath+'/inputfiles/templates/'+jobtemplate

    # Subdirectory where to store jobs
    testdir = 'testdirs/test_%d'%(test.id)
    outFilePath = 'testdirs/test_%d/jobs'%(test.id)
    
    try:
      os.mkdir(os.path.join(basePath,testdir))
    except OSError:
      pass
    try:
      os.mkdir(os.path.join(basePath,outFilePath))
    except OSError:
      pass

    # Path of the working directory
    if os.environ.has_key('HCDIR'):
      HCDIR = os.environ['HCDIR']
    else:
      HCDIR = '/tmp'

    """  
    if os.environ.has_key('CMSSW_VERSION'):
      CMSSW_VERSION = os.environ['CMSSW_VERSION']
      if not str(CMSSW_VERSION) == str(inputtype):
        print 'CMSSW_VERSION in environment:%s, CMSSW_VERSION in inputtype: %s.'
        return 0
    else:
      print 'No CMSSW_VERSION found'
      return 0
#      CMSSW_VERSION = inputtype 
    
#    if not CMSSW_VERSION in usercode:
#      print 'Usercode selected (%s) does not match CMSSW_VERSION (%s)'%(usercode,CMSSW_VERSION)    
#      return 0
    """
    PSET = HCDIR+'/apps/cms/inputfiles/usercode/'+str(usercode)

    """
    print "**** Start DBS discovery"
    
    datasets = {}
    for site in sites.keys():

      datasets[site] = []
      print " "+str(site)
      print "   start: "+str(datetime.now())

      for pattern in datasetpatterns:

        dataset = ''
        if False:
          try:
            url = 'https://cmsweb.cern.ch/dbs_discovery/aSearchShowAll?case=on&cff=0&caseSensitive=on&userInput=find%20dataset%20where%20dataset%20like%20%25'+pattern+'%25%20and%20site%3D'+site+'%20and%20dataset.status%20like%20VALID*&grid=0&fromRow=0&xml=0&sortName=&dbsInst=cms_dbs_prod_global&html=1&limit=-1&sortOrder=desc&userMode=user&method=dbsapi'
            request = Request(str(url))
            f = urlopen(request)
            dataset = f.read()
            f.close()
          except HTTPError, e:
            print "HTTPError: "+str(e.code)+"\n"
            print str(url)+'\n'
          except URLError, e:
            print "URLError: "+str(e.code)+"\n"
            print str(url)+'\n'

          dataset = dataset.replace(' ','')
          ds = dataset.split('\n')
          try:
            ds.remove('')
          except:
            pass
          random.shuffle(ds)
          for dset in ds:
            if not dset in datasets[site]:
              print "Pattern: "+pattern+"  Dataset from pattern: "+dset
              datasets[site].append(dset)
        else:
          print "Pattern: "+pattern+"  Dataset from pattern: "+pattern
          datasets[site].append(pattern)

      print "   end  : "+str(datetime.now())

    print "**** End DBS discovery"
    """
    total = 0
    fid = 0

    for ts in test_sites:
      maxnumdataset = sitenumjobs[ts.site.name]
      print('\n*** Generating %d tasks for site %s \n'%(maxnumdataset,ts.site.name))
      fid = fid+1

      for index in xrange(maxnumdataset):
        ff = open(jobtemplate,'r')
        outFile_content = ff.read()
        ff.close()

        outFile_content = outFile_content.replace('####WORKFLOW####', "HC_%s_%s_%s" % (str(test.template).split()[0], ts.site.name, datetime.now().strftime("%Y%m%d%H%M%S")))
        outFile_content = outFile_content.replace('####DATASETPATH####', datasetpatterns[index])
        outFile_content = outFile_content.replace('####PSET####', PSET)
        outFile_content = outFile_content.replace('####SITEWHITELIST####', ts.site.name)
        outFile_content = outFile_content.replace('####CMSSW####', str(inputtype))

        outFileName = os.path.join( basePath, outFilePath, '%d_%03d_%s.py'%(fid,1,ts.site.name) )
        print outFileName
        outFile = open(outFileName,'w')
        outFile.write(outFile_content)
        outFile.write('\n')
        outFile.close()
        total += 1


    """
    for site in sites.keys():
      hasdata=False
      try:
        if len(datasets[site]) > 0:
          hasdata=True
      except KeyError:
        pass
      if not hasdata:
        print 'skipping site %s with no available data'%site
        continue
      index = 0
      while sitenumjobs[site] > 0:

        fid = fid+1
        # site specific number of jobs
        maxnumdataset = sitenumjobs[site]

        print('\n*** Generating %d tasks for site %s \n'%(maxnumdataset,site))

        if len(datasets[site]) < 1:
          print "skipping %s"%location
          sitenumjobs[site] = 0

        ff = open(jobtemplate,'r')
        outFile_content = ff.read()
        ff.close()

        outFile_content = outFile_content.replace('####DATASETPATH####', datasets[site][index])
        outFile_content = outFile_content.replace('####PSET####', PSET)
        outFile_content = outFile_content.replace('####CE_WHITE_LIST####', site)
        outFile_content = outFile_content.replace('####SE_WHITE_LIST####', sites[site])

        # 1 because there is only one dataset.
        outFileName = os.path.join( basePath, outFilePath, '%d_%03d_%s.py'%(fid,1,site) )
        outFile = open(outFileName,'w')
        outFile.write(outFile_content)
        outFile.write('\n')
        outFile.close()

        print '    Generated: %s: %s, %d, %s ' %(site, sites[site], 1, datasets[site][index])
        print '    %02d datasets generated at %s: %s' %(1, site, sites[site])

        # reuse the datasets if not enough jobs
        if 1 < sitenumjobs[site]:
          print '  %s not done. generating more jobs'%site
        sitenumjobs[site]=sitenumjobs[site]-1
        index += 1
        total += 1
        """
    print '\n**** TOTAL %02d jobs generated' %(total)
    return 1    
