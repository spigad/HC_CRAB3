import sys, os, time
from random import shuffle

class TestGenerate:

  def convertQueueNameToDQ2Names(self, queue, test):
    from pandatools import Client
    from dq2.info.TiersOfATLAS import ToACache
    sites = []

    if 'PFT' in test.template.description:
        Client.PandaSites = Client.getSiteSpecs('production')[1]

    for site in Client.PandaSites[queue]['setokens'].values():
      sites.append(Client.convSrmV2ID(site))
    allowed_sites = []
    for site in ToACache.sites:
      if (site not in allowed_sites
          and Client.convSrmV2ID(site) in sites
          and site.find('TAPE') == -1 and 'DISK' in site):
        allowed_sites.append(site)
    return allowed_sites

  def run(self,test,mode):

    try:
      sys.stderr = open("/dev/null", "w")
      import dq2.info.TiersOfATLAS as TiersOfATLAS
      from dq2.clientapi.DQ2 import DQ2
      from dq2.common.dao.DQDaoException import DQDaoException
      from dq2.info.TiersOfATLAS import _refreshToACache, ToACache
    except:
      print 'ERROR: Could not import DQ2'
      return 0
#      sys.exit()

    # repair stderr
    sys.stderr = sys.__stderr__

    _refreshToACache()

    # All locations in a cloud
    sites={}           # sites to run jobs at, with values == ddm location for each site. note that because this is a dict, we only run 1 test per site, regardless of what is in the database
    locations=[]       # ddm locations (space token names)
    sitenumjobs={}     # jobs to a particular site

    test_sites = test.getTestSites_for_test.all()

    for ts in test_sites:
      locs = ts.site.ddm.split(',')
      site_locs = []
      for loc in locs:
        # ensure the locations are in ToACache
        if loc not in ToACache.sites.keys():
          continue
        if loc not in locations:
          locations.append(loc)
          site_locs.append(loc)

      try:
        extra_locs = self.convertQueueNameToDQ2Names(ts.site.name, test)
      except:
        extra_locs = []

      locations = locations + extra_locs
      site_locs = site_locs + extra_locs
      site_locs = list(set(site_locs)) # uniq

      sitenumjobs[ts.site.name] = int(ts.num_datasets_per_bulk)
      sites[ts.site.name] = ','.join(site_locs)
      print 'site', ts.site.name, 'locations', site_locs      
      ts.site.ddm = sites[ts.site.name]
      ts.save()

    locations = list(set(locations))
    shuffle(locations)
    # hack for CERN
    if 'CERN-PROD_LOCALGROUPDISK' in locations:
        locations.remove('CERN-PROD_LOCALGROUPDISK')
    print 'Looking in locations: %s' % locations

    # Locations to generate jobs for
    active_locations = locations

    # Path of the working directory
    if os.environ.has_key('HCAPP'):
      basePath = os.environ['HCAPP']
    else:
      basePath = '/tmp'

    # Dataset patterns
    datasetpatterns = []
    test_dspatterns = test.getTestDspatterns_for_test.all()
    for td in test_dspatterns:
      if td.dspattern.pattern.startswith('/'):
        file = open(td.dspattern.pattern)
        for l in file:
          datasetpatterns.append(l.strip())
        file.close()
      elif td.dspattern.pattern.startswith('http'):
        import urllib2
        url = td.dspattern.pattern
        try:
          patterns = urllib2.urlopen(url).read().split()
          print "Downloaded dspatterns", url, patterns
          for p in patterns:
            if p not in datasetpatterns:
              datasetpatterns.append(p)
        except:
          print 'failed to download url pattern',url
      elif td.dspattern.pattern.endswith('.txt'):
        file = open(basePath + '/inputfiles/templates/' + td.dspattern.pattern)
        for l in file:
          datasetpatterns.append(l.strip())
        file.close()
      else:
        datasetpatterns.append(td.dspattern.pattern)

    if len(datasetpatterns) == 0:
      print 'No dspatterns found for this test!'
      return 0
    print 'Dataset patterns to be used: %s' % datasetpatterns

    jobtemplate = basePath + '/inputfiles/templates/' + test.jobtemplate.path
    userarea    = basePath + '/inputfiles/templates/' + test.usercode.path
    joboptions  = basePath + '/inputfiles/templates/' + test.optionfile.path    

    try:
      pattern = '.*/(.*)$'
      joboptionsfilename = re.match(pattern, joboptions).group(1)
    except:
      joboptionsfilename = joboptions

    outputdatasetname = 'hc%d'%test.id #rows[0][3] + str(int(time.time()))

    inputtype = test.inputtype.type

    # Subdirectory where to store jobs
    testdir = 'testdirs/test_%d' %test.id
    outFilePath = 'testdirs/test_%d/jobs' %test.id
    try:
      os.mkdir(os.path.join(basePath,testdir))
    except OSError:
      pass
    try:
      os.mkdir(os.path.join(basePath,outFilePath))
    except OSError:
      pass

    dq2=DQ2()

    # Find overlap datasets
    datasetList = {}
    for location in locations:
      print "Datasets by pattern available at",location
      datasets = []
      for datasetpattern in datasetpatterns:
        print time.ctime()
        print 'dq2.listDatasetsByNameInSite(site=%s, name=%s)'%(repr(location),repr(datasetpattern))
        temp = dq2.listDatasetsByNameInSite(site=location, name=datasetpattern)
        temp = list(temp)
        datasets = datasets + temp
        print datasetpattern, location, len(temp)
        print time.ctime()
      datasetList[location] = datasets
      print

    # find location with most datasets
    print "TOTAL Datasets available"
    bestLoc = locations[0]
    for location in locations:
      print location, len(datasetList[location])
      if len(datasetList[location]) > len(datasetList[bestLoc]):
        bestLoc = location
    print

    print "OVERLAPPING DATASETS"
    overlapDatasets = []
    datasets = datasetList[bestLoc]
    for dataset in datasets:
      loc = []
      for location in locations:
        if dataset in datasetList[location]:
          loc.append(location)
      if len(loc)>=len(locations)-2:
        #for location in loc:
        #    datasetsiteinfo = dq2.listFileReplicas(location, dataset)
        #    nof = datasetsiteinfo[0]['found']
        overlapDatasets.append(dataset)
        print dataset, loc

    total = 0
    fid = 0
    for site in sites.keys():
      locs = sites[site].split(',')
      hasdata=False
      for location in locs:
        try:
          if len(datasetList[location]) > 0:
            hasdata=True
        except KeyError:
          pass
      if not hasdata:
        print 'skipping site %s with no data'%site
        continue

      useful_sites = len(locs)
      while sitenumjobs[site] > 0 and useful_sites > 0:
        for location in locs:
          fid = fid+1
          # site specific number of jobs
          maxnumdataset = sitenumjobs[site]
          if maxnumdataset < 1:
            print "%s has no more jobs needed. Skipping %s"%(site,location)
            continue

          print('\n*** Generating %d jobs for site %s (ddm location %s)\n'%(maxnumdataset,site,location))

          try:
            datasets = list(datasetList[location])
          except KeyError:
            print "Location %s does not exist...skipping" %location
            useful_sites -= 1
            continue

          print "%02d datasets with pattern %s at location %s " %(len(datasets),datasetpattern, location)

          if len(datasets) < 1:
            print "skipping %s"%location
            useful_sites -= 1
            continue

          # note that we can get here but the datasets are still not complete at the site

          # Adding overlap
          temp_datasets = datasets
          new_datasets = []
          for dataset in datasets:
            if dataset in overlapDatasets:
              new_datasets.append(dataset)
              temp_datasets.remove(dataset)

          # put the overlap datasets first
          datasets = new_datasets + temp_datasets

          if location in active_locations:
            print '%s is enabled' %location

            num = 1
            #numberoffiles = 0
            #itriggerupdate = 0
            #guidlistAll = []
            #lfnlistAll = []
            datasetAll = []
            shuffle(datasets)
            for dataset in datasets:
              # prevent double counting
              if dataset in datasetAll:
                continue
              # remove certain dataset pattern
              #if dataset.find('singlepart')>=0 or dataset.find('pile')>=0 or dataset.find('test')>=0 or dataset.find('atlfast')>=0 or dataset.find('user')>=0 or dataset.find('users')>=0 or dataset.find('higgswg')>=0 or dataset.find('_sub')>=0:
              if dataset.find('singlepart')>=0 or dataset.find('pile')>=0 or (dataset.find('test')>=0 and not 'HCtest' in dataset) or dataset.find('atlfast')>=0 or dataset.find('users')>=0 or dataset.find('higgswg')>=0 or dataset.find('_sub')>=0:
                print 'Skipping %s' %dataset
                continue

              # Get dataset info
              try:
                print time.ctime()
                print 'dq2.listFileReplicas(%s, %s)'%(repr(location),repr(dataset))
                datasetsiteinfo = dq2.listFileReplicas(location, dataset)
                print time.ctime()
              except:
                print 'crash: %s, %s' %(location, dataset)
                continue
              # Skip is data is not immutable
              try:
                immutable = datasetsiteinfo[0]['immutable']
              except:
                continue
              if not immutable:
                print 'Not immutable, skip %s, ' %dataset
                continue
              # Skip dataset if not complete at site
              try:
                print time.ctime()
                print 'dq2.listDatasetReplicas(%s)[dq2.listDatasets(%s)[%s][\'vuids\'][0]][0]'%(repr(dataset),repr(dataset),repr(dataset))
                incompleteLocations = dq2.listDatasetReplicas(dataset)[dq2.listDatasets(dataset)[dataset]['vuids'][0]][0]
                print time.ctime()
              except:
                incompleteLocations = []
              if location in incompleteLocations:
                print 'Not complete at %s, skip %s' %(location, dataset)
                continue

#              numberoffiles = numberoffiles + datasetsiteinfo[0]['found']
#              if numberoffiles>0:
#                guidlist = datasetsiteinfo[0]['content']
#                lfnlist = []
#                print 'dq2.listFilesInDataset(%s)'%repr(dataset)
#                datasetfiles=dq2.listFilesInDataset(dataset)
#                for guid in guidlist:
#                  lfnlist.append(datasetfiles[0][guid]['lfn'])
#              else:
#                continue

              #guidlistAll = guidlistAll + guidlist
              #lfnlistAll = lfnlistAll + lfnlist
              datasetAll.append(dataset)

              num = num + 1
              if num > maxnumdataset:
                break

            # prevent infinite loop
            if (num-1) < 1:
              print 'No datasets: skipping site %s,%s'%(site,location)
              useful_sites -= 1
              continue

            ff = open(jobtemplate,'r')
            outFile_content = ff.read()
            ff.close()


            # make unique userarea file for test
            tmp_userarea = os.path.join('/tmp/', str(test.id) + '.' + os.path.split(userarea)[1])
            print 'linking', tmp_userarea, 'to', userarea
            try:
                os.symlink(userarea, tmp_userarea)
            except OSError: # file exists
                print 'symlink already exists'
                pass

            outFile_content = outFile_content.replace('####USERAREA####', tmp_userarea)
            outFile_content = outFile_content.replace('####JOBOPTIONS####', joboptions)
            outFile_content = outFile_content.replace('####JOBOPTIONSFILENAME####', joboptionsfilename)
            outFile_content = outFile_content.replace('####SITES####', repr(str(site)))
            outFile_content = outFile_content.replace('####OUTPUTDATASETNAME####', outputdatasetname+'.'+site+'.'+str(fid) )
            outFile_content = outFile_content.replace('####DATASET####', repr(datasetAll))
            outFile_content = outFile_content.replace('####INPUTTYPE####', inputtype)
            outFile_content = outFile_content.replace('####NUM####', repr((num-1)))
            outFile_content = outFile_content.replace('####TESTID####', str(test.id))

            outFileName = os.path.join( basePath, outFilePath, '%d_%03d_%s.py'%(fid,num-1,site) )
            outFile = open(outFileName,'w')
            outFile.write(outFile_content)
            outFile.write('\n')
            outFile.close()

            print 'Generated: %s: %s, %d, %s ' %(site, location, num-1, datasetAll)

            print '%02d datasets generated at %s: %s' %(num-1, site, location)
            total = total + num -1

            # reuse the datasets if not enough jobs
            if (num-1) < sitenumjobs[site]:
              print '%s not done. generating more jobs'%site
            sitenumjobs[site]=sitenumjobs[site]-(num-1)

    print '\n**** TOTAL %02d jobs generated' %(total)
    return 1

