import os

path='/data/etp1/SUSYD3PD/SUSYD3PDMaker_0614/mc/'
#inputtype = 'panda'
inputtype = 'ganga'


#path = path+'SUGRA_tanbeta3_grid/user.ctopfel.SUSYD3PD.mc09_7TeV.114013.SU_1000_100_0_3_herwigpp_susy.merge.AOD.e542_s765_s767_r1302_r1306.000614.V4/'
path = path+'group10.phys-susy.SUSYD3PD.mc09_7TeV.106484.SU4_herwigpp_susy.merge.AOD.e542_s765_s767_r1302_r1306.000614.V2/'
f = open('input.txt', 'w')

dirList=os.listdir(path)
FilesList = []

#build list of files
for fname in dirList:
  print fname
  if fname.find('root')>0:
    #for Ganga, input list in one file per line
    if inputtype in ['ganga']:
      f.write(path+fname+'\n')    
    elif inputtype in ['panda']:
      FilesList.append(path+fname)
    else:
      print 'Please define inputtype (ganga or panda)'

#additional manip needed for Panda, no \n, comma separated list
if inputtype in ['panda']:
  extFilesList =''
  for File in FilesList:
    extFilesList = extFilesList + ',' + File
      
  #remove first ,
  if extFilesList.startswith(","):
    extFilesList = extFilesList[1:]
  print extFilesList
  
  f.write(extFilesList)        


f.close

