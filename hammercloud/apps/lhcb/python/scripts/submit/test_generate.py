import os,time, random
from datetime import datetime

class TestGenerate:

  # No mode distinction yet

  def run(self,test,mode):

    print '==%s=='%(mode)

    sites={}
    sitenumjobs={}
    datasetpatterns = []

    test_sites      = test.getTestSites_for_test.exclude(site__name='UNKNOWN')
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

    #Usercode
    usercode = basePath+'/inputfiles/usercode/'+usercode

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
  
    total = 0
    fid = 0

    if not len(datasetpatterns) > 0:
      print 'Something went really wrong. Never can reach this point without datasetpatterns !!'
      return 0

    for site in sites.keys():

      index = 0

      print('\n*** Generating %d jobs for site %s (ddm location %s)\n'%(sitenumjobs[site],site,sites[site]))

      while sitenumjobs[site] > 0:

        fid = fid+1

        if index == len(datasetpatterns):
          index = 0

        ff = open(jobtemplate,'r')
        outFile_content = ff.read()
        ff.close()

        outFile_content = outFile_content.replace('####_OPTSFILE_####', usercode)
        outFile_content = outFile_content.replace('####_SITE_####', site)
        outFile_content = outFile_content.replace('####_PATTERN_####', datasetpatterns[index])

        # 1 because there is only one dataset.
        outFileName = os.path.join( basePath, outFilePath, '%d_%03d_%s.py'%(fid,1,site) )
        outFile = open(outFileName,'w')
        outFile.write(outFile_content)
        outFile.write('\n')
        outFile.close()

        print '    Generated: %s: %s, %d, %s ' %(site, sites[site], 1, datasetpatterns[index])
        print '    %02d datasets generated at %s: %s' %(1, site, sites[site])

        # reuse the datasets if not enough jobs
        if 1 < sitenumjobs[site]:
          print '  %s not done. generating more jobs'%site
        sitenumjobs[site]=sitenumjobs[site]-1
        index += 1
        total += 1

    print '\n**** TOTAL %02d jobs generated' %(total)
    return 1    
