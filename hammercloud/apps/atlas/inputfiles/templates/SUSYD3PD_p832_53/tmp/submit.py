#!/bin/python

import os, commands, shlex, subprocess, glob

#####################################

if __name__ == '__main__':

###############################################################################################################
#                                             options  
###############################################################################################################

  dataset = 'Egamma'
  #dataset = 'Muons'
  #dataset = 'MC'
  #dataset = 'MSUGRA'
  #dataset = 'PHENO'

  #period=''
  #period = 'F' 
  #syst = ''
  syst = 'trigger'
  #syst = 'jer'
  #syst = 'jesplus'
  #syst = 'jesminus'

  #submit = 'panda'
  submit = 'ganga'
  date = '.090212.1'  
  
  athena = '17.0.2'
#  periods = ['B','D','E','F','G','H','I','J','K','L','M'] 
#  periods = ['M'] 
  periods = ['D','E','F','G','H','I','J','K','L'] 

  print 'Submitting to '+submit
  
###############################################################################################################
#                                             OPEN SUBMIT FILE SCRIPT 
###############################################################################################################

  f = open('submit.sh', 'w')
  f.write('#!/bin/sh \n')

  if submit in ['panda']:

    f.write('source ~/scripts/pandaSetup \n')

  # for Ganga submission: use only one tarball!
  first = -1 
  tarballPath = '/data/etp4/flegger/gangadir/tarball'
  if submit in ['ganga']:
    first = 1
    f.write('source /afs/cern.ch/sw/ganga/install/etc/setup-atlas.sh \n')
    #f.write('asetup '+athena+' \n')
    f.write('asetup '+athena+' --single --testarea $PWD \n') 
    f.write('rm -f '+tarballPath+'/job*.tar.gz \n') 

    
  f.write('source RootCore/scripts/setup.sh \n')  

  
###############################################################################################################
#                                             BUILD COMMAND LINE -- constant part  
###############################################################################################################
  
  extFiles = [
'grl/data11_7TeV.periodAllYear_DetStatus-v36-pro10_CoolRunQuery-00-04-08_Susy.xml',
'iLumiCalc/ilumicalc_histograms_EF_e20_medium_178044-184169.root',
'iLumiCalc/ilumicalc_histograms_EF_mu18_178044-184169.root',
'SUSYTools/data/fest_periodF_v1.root',
'iLumiCalc/PileUp101111Run3.root'    
   ]

  extFilesListPanda =''
  extFilesListGanga =''

  for File in extFiles:
     extFilesListPanda = extFilesListPanda + ',' + File
     extFilesListGanga = extFilesListGanga + ':' + File

  #remove first : or ,
  if extFilesListPanda.startswith(","):
    extFilesListPanda = extFilesListPanda[1:]

  if extFilesListGanga.startswith(":"):
    extFilesListGanga = extFilesListGanga[1:]
    
  comFirstPanda = 'prun --exec \"echo %IN > input.txt; root.exe runPanda.C\" --athenaTag='+athena
#  comFirstGanga = 'ganga -o[Panda]chirpconfig="chirp^gar-ex-chirp.garching.physik.uni-muenchen.de^/flegger^-d chirp" athena --inDS '  
  comFirstGanga = 'ganga -o[Configuration]RUNTIME_PATH=/data/etp1/elmsheus/Ganga/GangaAtlas /data/etp1/elmsheus/Ganga/GangaAtlas/scripts/athena --inDS '
  
  excludedSite='ANALY_CERN,ANALY_CERN_XROOTD,ANALY_INFN-NAPOLI,ANALY_CSCS'
  
  #comLaterGanga = ' --athena_exe EXE --split 2 --athena_release '+athena+' --useRootCore --panda ' + ' --excludedSite=' +excludedSite+' '
  #comLaterGanga = ' --athena_exe EXE --split 2 --useRootCore --panda ' + ' --excludedSite=' +excludedSite+' '
  comLaterGanga = ' --athena_release '+athena+' --useRootCore --panda --cloud DE --excludedSite=' +excludedSite+' --split 2 --athena_exe EXE'

   
###############################################################################################################
#                                             Input Dataset list  
###############################################################################################################
    
  for period in periods:
    inDSs = {}
    fileName= '.'+period+date  # meaningful only for panda submission
    
    # get datasets in one period
    if dataset in ['Egamma']:

      out = '_electronStream'
      inputFile = 'egamma'+period+'.txt'
    
    if dataset in ['Muons']:

      out = '_muonStream'
      inputFile = 'muon'+period+'.txt'
    
    if dataset in ['MC']:
      out = ''
      inputFile = 'mc10a_p543.txt'

    fDS = open(inputFile, 'r')
    for line in fDS:
      #line = line.replace ( '\n', '/' )
      line = line.replace ( '\n', '' )
      lineSplit = line.split( '.' )
      runNumber = lineSplit[1]
      # strip first 00 in case of data samples
      if (len(runNumber) == 8):
         runNumber = runNumber[2:]
      inDSs[runNumber] = line

    # now loop over all datasets (in one period)
    for key,value in inDSs.iteritems():
     	  
      outFile =  '_' + key +out
      outputFiles = ' result'+outFile+'.root,result'+outFile+'.txt '

      if syst in ['jer']:
        outputFiles = ' jer'+outFile+'.root,jer'+outFile+'.txt '

      if syst in ['jesplus']:
        outputFiles = ' jesplus'+outFile+'.root,jesplus'+outFile+'.txt '

      if syst in ['jesminus']:
        outputFiles = ' jesminus'+outFile+'.root,jesminus'+outFile+'.txt '

      if syst in ['trigger']:
        outputFiles = ' trigger'+outFile+'.root,trigger'+outFile+'.txt '

      outDS = 'user.flegger.'+outFile+fileName
      outDSGanga = outFile+fileName
      commandlinePanda = comFirstPanda  + ' --useRootCore '+ ' --cloud=DE --excludedSite=' +excludedSite+' --inDS '+ value + ' --outDS '+outDS + ' --outputs ' + outputFiles +' --extFile ' + extFilesListPanda

      if (first==0):
        comLaterGangaTarball = ' --user_area ${FILES[0]} '+ comLaterGanga
      if (first==1):
        print 'Using tarball path '+tarballPath
        comLaterGangaTarball = ' --user_area_path '+tarballPath+' '+ comLaterGanga
	
      commandlineGanga = comFirstGanga + value + ' --cloud DE --outputdata ' + outputFiles + comLaterGangaTarball + ' --outDS '+outDSGanga + ' --inputsandbox '+  extFilesListGanga + ' runGanga.sh'  

###############################################################################################################
#                                             Write command line to file
###############################################################################################################

#    if (key in ['167607','167661','167680','167776','167844']):
#    if not(key in ['106484']):
      if (1==1):
        if submit in ['panda']:
    
          print commandlinePanda    
          f.write(commandlinePanda+'\n')
    
        if submit in ['ganga']:
    
          print commandlineGanga
          f.write(commandlineGanga+'\n')
      
          if (first==1):
	    first = 0
	    f.write('FILES='+tarballPath+'/job*.tar.gz'+'\n')
	    f.write('for f in $FILES\n')
	    f.write('do\n')
	    f.write('  echo "Submitting tarball $f ..."\n')
	    f.write('done\n')
    
  f.close() 
  
  print 'Have you checked the Rootcore libraries, grl and pileup reweighting files to be shipped???'     
#p = subprocess.Popen('source submit.sh', shell=True)
#sts = os.waitpid(p.pid, 0)[1] 
