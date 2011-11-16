import sys, os, re, time, commands, urllib, imp, gzip
from datetime import datetime, date, timedelta
from hc.atlas.models import *
from pandatools import Client

# This script is generating txt files for SAM reporting
# This script is generating the blacklist file sum.txt/sum.html and efficiency files eff.html/txt
# This script is filling the DB table summary_gangarobot for fast rendering of the gangarobot django view

# where files are stored
htmlDirReport =  os.path.join('/data/hc/apps/atlas/sam/')

#Clouds-sites info
ng_ces = [ 'grid.uio.no',
           'ce01.titan.uio.no',
           'arc.bccs.uib.no',
           'gateway01.dcsc.ku.dk',
           'pikolit.ijs.si',
           'arc-ce01.pdc.kth.se',
           'grad.uppmax.uu.se',
           'jeannedarc.hpc2n.umu.se',
           'arc-ce.smokerings.nsc.liu.se',
           'siri.lunarc.lu.se',
           'lheppc50.unibe.ch',
           'grid03.unige.ch',
           'arc01.lcg.cscs.ch',
           ]


class Robot:

  def getTiersOfATLASCache(self):
    """Download TiersOfATLASCache.py"""
    url = 'http://atlas.web.cern.ch/Atlas/GROUPS/DATABASE/project/ddm/releases/TiersOfATLASCache.py'
    #local = os.path.join(os.environ['TMPDIR'],'TiersOfATLASCache.py')
    local = os.path.join('/tmp/','TiersOfATLASCache.py')
    try:
      urllib.urlretrieve(url, local)
    except IOError:
      print 'Failed to download TiersOfATLASCache.py'
    try:
      tiersofatlas = imp.load_source('',local)
    except SyntaxError:
      print 'Error loading TiersOfATLASCache.py'
      return None
    return tiersofatlas


  def getAGISsites(self):
    #wget -nd -r -O agis.list --tries=1 https://project-adc-operations.web.cern.ch/project-adc-operations/SSB/published/SITE_EXCLUSION/agis_T0T1T2_list.data
    try:
      infile = open('/data/hc/apps/atlas/config/agis.list', "r")
    except:
      print 'ERROR, could not open agis_T0T1T2_list.data'
      return []
    siteList = []
    siteTiers = []
    for line in infile:
      linelist =  line.split()
      #print linelist
      siteList.append(linelist[2])  # 3rd element of the string, after date and time
      siteTiers.append(linelist[3])  # 4rd element of the string, is Tiers type
    infile.close()
    print siteList
    return siteList


  def getEfficiency(self, site, num_required_failures, hours, testIDString):
    completed = 0
    failed = 0
    samreport    = dict()  #sam report
    #print 'Querying DB for site '+sitename
    #get last x test results     
    #print qry
    rows_tests = Result.objects.exclude(ganga_subjobid=1000000).filter(test__in=testIDString).filter(site=site).filter(fixed=True).filter(mtime__gte=(datetime.now()-timedelta(seconds=hours*3600))).order_by('-mtime')[:num_required_failures]
    #print rows_tests   
    if rows_tests:
      for row_test in rows_tests:
        #print '-----------'
        #print row_test
        testid      = str(row_test.test.id)  
        starttime   = str(row_test.start_time)
        endtime     = str(row_test.stop_time)     
        gangajobid  = str(row_test.ganga_jobid)       
        gangastatus = str(row_test.ganga_status)       
        site_name   = str(row_test.site.name)       
        inds        = str(row_test.inds)       
        reason      = str(row_test.reason)       
        ce          = str(row_test.actual_ce)
        description = str(row_test.test.template.description)
        # LCG SAM, Blacklist
        #distinguish panda sites (CE unknown) from WMS sites (actual CE)
        if (ce=="unknown"):   #panda
            string = site_name
        else:   #lcg
          # remove queue from ce
          if (ce.find(':2119/')>0): 
            tmp = ce.split ( ':2119/' )
            ce = tmp[0]
          if (ce.find(':8443/')>0): 
            tmp = ce.split ( ':8443/' )
            ce = tmp[0]
          string = ce
        # ATTENTION   SAM REPORT  
        # this is only saving the LAST (with respect to mtime) test of the list 
        # so only ONE test per site, even if more have been running, i.e. with different athena version, input type, etc
        # for LCG sites store 1 test per CE
        if (gangastatus in ['c', 'f']):
          testresult = dict()        
          testresult["testid"]  = testid   
          testresult["starttime"]   = starttime
          testresult["endtime"]   = endtime     
          testresult["gangajobid"]  = gangajobid        
          testresult["gangastatus"] = gangastatus        
          testresult["site"]   = site_name
          testresult["inds"]   = inds         
          testresult["reason"]   = reason        
          testresult["ce"]    = ce
          testresult["description"] = description
          testresult["siteid"]   = site.id 
          testresult["agis"]   = site.alternate_name 
          samreport[string] = testresult
          #calculate efficiency for summary_gangarobot table (gangarobot web page) and Ganga Blacklist
          if gangastatus in ['c']:
            completed = completed+1       
          if gangastatus in ['f']:
            failed = failed + 1 
      #end loop over test results             
    # summary_gangarobot table (gangarobot web page) + Blacklist
    #    for string,result in samreport.items():
    #    #     if not((key=='summary')or(key=='SAM')):
    #        print '------------------         SAM results       ------------------------------------'
    #        print 'Query result for site/ce '+str(string)
    #        for key,value in result.items():     
    #    #     if not((key=='summary')or(key=='SAM')):
    #            print str(key) +' '+str(value)
    return samreport, completed, failed


  def queryDB(self, tiersofatlas):
    today = date.today()
    now = datetime.now()
    print 'Generating report for '+str(today)     
    samreport    = dict()  #sam report (per site)
    samreports   = dict() #total
    effresults     = dict()  #blacklisting
    pandablacklist = dict()  #blacklisting for Panda
    siteagis       = dict()  #site -> agis relationship
    siteidHC       = dict()  #site -> site ID in HC DB
    pandaIDString = []      
    lcgID = []
    lcgIDString = ''               
    # DB connection
    num_required_failures_panda = 3
    num_required_failures_lcg = 5
    hours_panda = 3
    hours_lcg = 12
    #   test_panda = (67,80,95,96)
    test_panda = (146,160,145,163,162,116,168,164)
    test_lcg = (140,)
    #get id of last 2 tests for each test template 
    # --> limit should always be #templates*2, to get the tests running in the last day
    pandaIDString = [list(Test.objects.filter(template__id=test_template).order_by('-id')[:2]) for test_template in test_panda]
    print 'Checking the following Panda tests '
    print pandaIDString
    #get id of last 4 LCG tests with test template 9 (LCG 15.6.9), 76 (LCG 16.0.2)
    # --> limit should always be #templates*2, to get the tests running in the last day
    lcgIDString = list(Test.objects.filter(template__id__in=test_lcg).order_by('-id')[:len(test_lcg)*2])
    #print lcgID, pandaID
    #print lcgIDString, pandaIDString
    # getting sites
    sites = Site.objects.filter(enabled=True)
    if not sites:
      print "Error no sites from DB query!"
    else:  
      for site in sites:
        # PANDA Blaclisting policy
        if site.name.startswith('ANALY'):
          completed_total = 0
          failed_total = 0
          notEnough = 0
          for tests in pandaIDString: #check efficiency for every test
            samreport, completed, failed = self.getEfficiency(site, num_required_failures_panda, hours_panda, tests) 
            completed_total = completed_total + completed
            failed_total = failed_total + failed
            if (failed > 0): 
              print str(site.name) + ' '+str(failed) + ' failed tests in test '+str(tests)
            if ((failed+completed) < num_required_failures_panda): #not enough jobs in one template, mark site in gray
              print str(site.name) + ' only '+str(failed+completed) + ' completed tests in test '+str(tests) 
              notEnough = 1
          total = float(completed_total + failed_total)
          completed = completed_total
          failed = failed_total
          efficiency = -1.
          if (total > 0):  # at least 1 test, no test with not enough jobs 
            efficiency = float(completed_total)/total       
          print str(site.name)+' efficiency '+str(efficiency)+' on '+str(total) + ' tests' 
          pandablacklist[site.name] = failed_total -  num_required_failures_panda  # >= 0 if total = num_required_failures, otherwise negative        
          if (failed_total > 0):
            print str(site.name)+' blacklisting '+str(pandablacklist[site.name])+' on '+str(failed_total) + ' failed tests'
            efficiency = 0. #overwrite efficiency for Gangarobot webpage  
          elif (notEnough):
            print str(site.name)+' WARNING '+str(pandablacklist[site.name])+' not enough completed tests'
            efficiency = -1. #overwrite efficiency for Gangarobot webpage                    
        else:      # LCG Blaclisting policy
          samreport, completed, failed = self.getEfficiency(site, num_required_failures_lcg, hours_lcg, lcgIDString)        
          total = float(completed + failed)
          efficiency = -1.
          if (total > 0):  # at least 1 test 
            efficiency = float(completed)/total       
          print str(site.name)+' efficiency '+str(efficiency)+' on '+str(total) + ' tests'        
          pandablacklist[site.name] = total -  num_required_failures_lcg  # = 0 if total = num_required_failures, otherwise negative        
        #copy SAM results    
        for string,result in samreport.items():
          #print '------SAM report-----'
          #print 'Query result for site/ce '+str(string)
          samreports[site.name]=result 
          #for key,value in result.items():     
            #print str(key) +' '+str(value)
        effresults[site.name] = efficiency
        siteagis[site.name] = site.alternate_name             
        siteidHC[site.name] = site.id
        # Gangarobot webpage:
        # write efficiency to db
        #don't show in red sites that are not blacklisted      
        if ((efficiency == 0.) and (pandablacklist[site.name]<0.)):
          efficiency = 0.000001
        try:
          rows = SummaryRobot.objects.filter(site=site,day=today)
        except:
          rows = []
          print 'Exception from query for SummarySite'
        if rows:
          sr = rows[0]
        else:
          sr = SummaryRobot(site=site, day=today)
        sr.completed      = int(completed)
        sr.failed         = int(failed)
        sr.total          = int(total)
        sr.efficiency     = float(efficiency)
        sr.efficiencyNorm = sr.efficiency*float(completed)
        if float(total) > 0:
          sr.errorrate     = float(failed)/float(total)
          sr.errorrateNorm = sr.errorrate*float(completed)
        else:
          sr.errorrate     = 0.0
          sr.errorrateNorm = 0.0
        sr.mtime = datetime.now()
        sr.save()
      #end loop over sites
    #end loop if sites                    
    #    for string,result in samreports.items():
    #    print '--------SAM report TOTAL---'
    #  print 'Query result for site/ce '+str(string) 
    #  for key,value in result.items():     
    #    print str(key) +' '+str(value)
    return samreports, effresults, siteagis, siteidHC, pandablacklist


  def genReport(self, samreport, effresults, siteagis, siteid, pandablacklist,tiersofatlas):
    today = date.today()
    filedate = today.isoformat()+'_' 
    now = datetime.now()
    #print filedate
    # Write out raw text file summary for SAM/ ATLAS SSB   
    for string,result in samreport.items():
      print '----------------------------'
      print 'Writing report for site/ce '+str(string) 
      print result
      cename      = result['ce']
      cestatus    = result['gangastatus']
      cejobid     = result['gangajobid']
      cequeue     = result['site']
      cesename    = result['site']
      cereason    = result['reason']            
      description = result['description']
      inds        = result['inds']            
      starttime   = result['starttime']
      endtime     = result['endtime'] 
      #siteid      = result['siteid']    
      #agis        = result['agis']    
      cebackend = ''
      if string.startswith("ANALY"):
        cebackend = '@panda'
        alternatename = cequeue
        try:
          cename = Client.PandaSites[cequeue]['queue'].split('/')[0]
        except:
          cename = 'panda@unknown-ce'
        alternatename = Client.PandaSites[cequeue]['ddm']
        if (alternatename.find("_SCRATCHDISK")>=0):
          alternatename = alternatename.replace("_SCRATCHDISK", "_MCDISK")
        if (alternatename.find("_USERDISK")>=0):
          alternatename = alternatename.replace("_USERDISK", "_MCDISK")
        if (alternatename.find("_MCDISK")<0):
          print "ERROR alternate name does not contain _MCDISK "+alternatename
      else:
        cebackend = '@wms'
        try:
          alternatename = tiersofatlas.sites[cesename]['alternateName'][0]
        except (TypeError, KeyError):
          alternatename = 'NONAME'
      ceOutFile = os.path.join(htmlDirReport, filedate+cename+cebackend+'.out')
      ceOutLatestResultsFile = os.path.join(htmlDirReport, 'LatestResults_'+cename+cebackend+'.out')
      #print 'output file '+ str(ceOutFile)
      # manipulations to get the right format to be written out
      # not really necessary...
      if string.startswith("ANALY"):
        cequeue = alternatename
        alternatename = string
      starttime = starttime.replace(' ', '_')
      endtime = endtime.replace(' ', '_')
      if ((cestatus.find('c'))>=0):
        cestatusid = 1
        cestatuslong = cestatus.replace('c','completed')
      elif ((cestatus.find('r'))>=0):
        cestatusid = 0
        cestatuslong = cestatus.replace('r','running')
      elif ((cestatus.find('a'))>=0):
        cestatusid = 0
        cestatuslong = cestatus.replace('a','aborted')
      elif ((cestatus.find('f'))>=0):
        cestatusid = 0
        cestatuslong = cestatus.replace('f','failed')
      elif ((cestatus.find('s'))>=0):
        cestatusid = 0
        cestatuslong = cestatus.replace('s','submitted')
      line = cename+','+alternatename+','+cequeue+','+cestatuslong+','+str(cestatusid)+','+cejobid+','+cereason+','+description+','+inds+','+starttime+','+endtime+'\n'
      cf = open(ceOutFile,'w')
      cf.write(line)
      cf.write('\n')
      cf.close()
      cf = open(ceOutLatestResultsFile,'w')
      cf.write(line)
      cf.write('\n')
      cf.close()
    # Write out sum.txt for Blacklisting/ ATLAS SSB
    outfailedLCG = []
    outfailedPanda = []
    outeffLCG = []
    outeffPanda = []
    lcgSSB = []
    pandaSSB = []    
    lcgBlacklistSSB = []
    pandaBlacklistSSB = []
    #get site list from AGIS
    siteAGISPanda = self.getAGISsites()
    siteAGISLCG = self.getAGISsites()
    for site in effresults:
      #default to everything OK
      efficiency = float(effresults[site])
      efficiency_100 = int (efficiency*100.)
      blacklist = 100
      color = ' green '
      color_bl = ' green '
      #print out efficiency
      if (efficiency >= 0.):
        if site.startswith('ANALY'):
          outeffPanda.append(str(site)+' '+str(efficiency_100)+'%')
        elif (site.endswith('MCDISK') or site.endswith('DATADISK')):  #no DATADISK
          outeffLCG.append(str(site)+' '+str(efficiency_100)+'%')
      # Blacklist site: 
      # more than 3 failed tests in panda
      if site.startswith('ANALY'):
        if ((pandablacklist[site] >=0.)):
          if not site in outfailedPanda:    
            print 'PANDA Blacklisting for '+str(site)+' : '+str(pandablacklist[site])  
            outfailedPanda.append(site)
            color_bl = ' red '
            color = ' red '
            blacklist = 0
            efficiency = 0                      
        # WARNING: efficiency = 0 and less than 5 tests 
        elif (pandablacklist[site] > -3.):
          color = ' yellow '
      # Job failures for LCG
      elif (site.endswith('MCDISK') or site.endswith('DATADISK')):      
        if ((efficiency == 0.)and (pandablacklist[site] ==0.)) :
          if not site in outfailedLCG:
            print 'LCG Blacklisting '+str(site)+' efficiency '+str(efficiency_100)+'%'
            alternatename = tiersofatlas.sites[site]['alternateName'][0]
            #add alternate name sites
            for sites in tiersofatlas.sites.keys():
              if tiersofatlas.sites[sites].has_key('alternateName') and tiersofatlas.sites[sites]['alternateName']:
                if alternatename == tiersofatlas.sites[sites]['alternateName'][0]:
                  outfailedLCG.append(sites)
            #print 'in sum.txt, efficiency '+str(efficiency)     
            color = ' red '
            color_bl = ' red '
            blacklist = 0
        # WARNING: efficiency = 0 and less than 5 tests 
        elif (efficiency <= .5):
          color = ' yellow '
      #site not tested
      if ((efficiency < 0.) and ( site.startswith('ANALY') or site.endswith('MCDISK') or site.endswith('DATADISK'))):  
        #print 'Site not tested '+str(site)+' efficiency '+str(efficiency_100)+'%'
        blacklist = 'n/a'                     
        color = ' white '
        color_bl = ' white '
        efficiency_100 = 'n/a'
      #Efficiency SSB    
      url='http://hammercloud.cern.ch/hc/app/atlas/robot/site/'+str(siteid[site])
      #link to Panda Monitor for Panda tests
      if (site.startswith('ANALY')):
        url='http://panda.cern.ch/server/pandamon/query?job=*&site='+str(site)+'&type=analysis&hours=12&processingType=gangarobot'
      now_utc = datetime.utcnow()
      time=now_utc.strftime("%Y-%m-%d %H-%M-%S")
      #time = now.strftime("%Y-%m-%d %H-%M-%S")
      lineSSB = time +' '+siteagis[site]+' '+str(efficiency_100)+color+url+'\n'    
      #ONLY SITES that are in AGIS
      if ((site.startswith('ANALY')) and (siteagis[site] in siteAGISPanda)):
        pandaSSB.append(lineSSB)
        siteAGISPanda.remove(siteagis[site])
        #print lineSSB
      elif ((site.endswith('MCDISK') or site.endswith('DATADISK') ) and (siteagis[site] in siteAGISLCG)):
        lcgSSB.append(lineSSB)
        siteAGISLCG.remove(siteagis[site])
      #Blacklist SSB
      url = ' http://hammercloud.cern.ch/sam/sum.html ' 
      lineSSB = time +' '+siteagis[site]+' '+str(blacklist)+color_bl+url+'\n'  
      #ONLY SITES that are in AGIS
      if ((site.startswith('ANALY')) and (siteagis[site] in siteAGISPanda)):
        #use autoexclusion for Panda
        if (pandablacklist[site] ==3):
          print 'Blacklisting '+str(site)+' (Panda autoexclusion) '
          blacklist = 0
          color_bl = ' red '
        else:
          blacklist = 100
          color_bl = ' green '  
        url = ' http://hammercloud.cern.ch/hc/app/atlas/ '
        lineSSB = time +' '+siteagis[site]+' '+str(blacklist)+color_bl+url+'\n'  
        pandaBlacklistSSB.append(lineSSB)
      elif ((site.endswith('MCDISK') or site.endswith('DATADISK')) and (siteagis[site] in siteAGISLCG)):
        lcgBlacklistSSB.append(lineSSB)
    # add sites that are in AGIS but not tested
    for site in siteAGISLCG:
      lcgBlacklistSSB.append(time +' '+site+' no-test green http://hammercloud.cern.ch/atlas/ \n') 
      lcgSSB.append(time +' '+site+' no-test green http://hammercloud.cern.ch/atlas/ \n')
    for site in siteAGISPanda:
      pandaBlacklistSSB.append(time +' '+site+' no-test green http://hammercloud.cern.ch/atlas/ \n') 
      pandaSSB.append(time +' '+site+' no-test green http://hammercloud.cern.ch/atlas/ \n')
    # Write summary
    outeffLCG = sorted(outeffLCG, key=str.lower)
    outeffPanda = sorted(outeffPanda, key=str.lower)
    outfailedLCG = sorted(outfailedLCG, key=str.lower)
    outfailedPanda = sorted(outfailedPanda, key=unicode.lower)
    rawOutFile = os.path.join(htmlDirReport, 'sum.txt')
    rf = open(rawOutFile,'w')
    rf.write(':'.join(outfailedLCG))             
    rf.close()
    rawOutFile = os.path.join(htmlDirReport, 'sum_panda.txt')
    rf = open(rawOutFile,'w')
    rf.write(':'.join(outfailedPanda))             
    rf.close()    
    rawOutFile = os.path.join(htmlDirReport, 'sum.html')
    rf = open(rawOutFile,'w')
    rf.write('<br>'.join(outfailedLCG))             
    rf.close()
    rawOutFile = os.path.join(htmlDirReport, 'sum_panda.html')
    rf = open(rawOutFile,'w')
    rf.write('<br>'.join(outfailedPanda))             
    rf.close()
    rawOutFile = os.path.join(htmlDirReport, 'eff.html')
    rf = open(rawOutFile,'w')
    rf.write('<h1>Report generated at '+str(now)+' </h1>')          
    rf.write('<h1>Efficiency for LCG sites</h1>')                 
    rf.write('<br>'.join(outeffLCG))             
    rf.write('<h1>Efficiency for Panda sites</h1>')                    
    rf.write('<br>'.join(outeffPanda))             
    rf.close()
    rawOutFile = os.path.join(htmlDirReport, 'eff.txt')
    rf = open(rawOutFile,'w')
    rf.write('Report generated at '+str(now)+' \n\n')          
    rf.write('Efficiency for LCG sites \n\n')          
    rf.write('\n'.join(outeffLCG))       
    rf.write('\n\n Efficiency for Panda sites \n\n')        
    rf.write('\n'.join(outeffPanda))         
    rf.close()
    # Write ATLAS SSB report    
    rawOutFile = os.path.join(htmlDirReport, 'Gangarobot_SSB_lcg.data')
    rf = open(rawOutFile,'w')
    rf.writelines(lcgSSB)             
    rf.close()
    rawOutFile = os.path.join(htmlDirReport, 'Gangarobot_SSB_panda.data')
    rf = open(rawOutFile,'w')
    rf.writelines(pandaSSB)             
    rf.close()
    rawOutFile = os.path.join(htmlDirReport, 'Blacklist_SSB_lcg.data')
    rf = open(rawOutFile,'w')
    rf.writelines(lcgBlacklistSSB)            
    rf.close()
    rawOutFile = os.path.join(htmlDirReport, 'Blacklist_SSB_panda.data')
    rf = open(rawOutFile,'w')
    rf.writelines(pandaBlacklistSSB)             
    rf.close()
    return 1


  def addnewline(self, path):
    filenames=[]
    for root, dirs, files in os.walk(path):
      for name in files:       
        filename = os.path.join(root, name)
        #print filename
        if (filename.find('.out')>0): 
          filenames.append(filename)
    for filename in filenames:
      #print filename
      f = open(filename, 'a')
      f.write('\n')
      f.close()


  def run(self):
    # Load TiersOfAtlasCache.py file and create site/cloud info variables
    tiersofatlas = self.getTiersOfATLASCache()
    #samreport is for SAM report, effresults, siteagis siteid is for BL and SSB
    samreport, effresults, siteagis, siteid, pandablacklist = self.queryDB(tiersofatlas)
    self.genReport(samreport, effresults, siteagis, siteid, pandablacklist,tiersofatlas)
    #remove old files
    print "removing old files"
    command ="find /data/hc/app/atlas/sam -mtime +7 -exec rm {} \;"
    commands.getstatusoutput(command)
    #    print "adding new line"
    #    addnewline('/data/hammercloud/atlas/sam/') 
    return 1

# Wget options
# -r Turn on recursive retrieving. 
#    When running Wget with -r, but without -N or -nc, re-downloading a file will result in the new copy simply overwriting the old. 
#    Adding -nc will prevent this behavior, instead causing the original version to be preserved and any newer copies on the server to be ignored.
#    When running Wget with -N, with or without -r, the decision as to whether or not to download a newer copy of a file depends on the local and remote timestamp and size of the file. 
# -nH Disable generation of host-prefixed directories.
# -l depth

#  wget -r -l 1 -N -nH "http://hammercloud.cern.ch/sam/" >>GangaRobot_wget_log
#  wget -r -l 1 -nc -nH "http://hammercloud.cern.ch/sam/" 
