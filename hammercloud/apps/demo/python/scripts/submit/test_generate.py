import os,time, random
from urllib2 import URLError,HTTPError,Request,urlopen
from datetime import datetime

class TestGenerate:

  def run(self,test):

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
  
    if os.environ.has_key('DEMO_PARAM'):
      DEMO_PARAM = os.environ['DEMO_PARAM']
      if not str(DEMO_PARAM) == str(inputtype):
        print 'DEMO_PARAM in environment:%s, DEMO_PARAM in inputtype: %s.'
        return 0
    else:
      print 'No DEMO_PARAM found'
      return 0


    print "**** Start DBS discovery"
    
    # FIND THE DATASETS AND DO WHATEVER YOU NEED

    # returns datasets (dictionary)

    print "**** End DBS discovery"

    total = 0
    fid = 0

    # Modify the following code in order to fit whatever you got from the DBS
    # As it is now, does not work.

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

        print('\n*** Generating %d jobs for site %s (ddm location %s)\n'%(maxnumdataset,site,sites[site]))

        if len(datasets[site]) < 1:
          print "skipping %s"%location
          sitenumjobs[site] = 0

        else:

          if index == len(datasets[site]):
            index = 0

          ff = open(jobtemplate,'r')
          outFile_content = ff.read()
          ff.close()

          outFile_content = outFile_content.replace('####PARAM1####', param1)
          outFile_content = outFile_content.replace('####PARAM2####', param2)
          outFile_content = outFile_content.replace('####PARAM3####', param3)
          outFile_content = outFile_content.replace('####PARAM4####', param4)

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

    print '\n**** TOTAL %02d jobs generated' %(total)
    return 1    
