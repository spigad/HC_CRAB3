#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Ask me if you have questions/problems. Thomas M.
# Version 0.1.8
import os, sys
import commands
from ROOT import *

import sys
  
def prepareDatasetFormat(dataset):
    return dataset.replace("\n","")  
 
def createdq2outputTmpForDataSet(dataset):
    print "creating dq2output from ", dataset
    commands.getstatusoutput("rm dq2output.tmp")
    print '2'
    appenddq2outputTmpForDataSetAtSite(dataset,"LRZ-LMU_LOCALGROUPDISK")
    print '3'
    appenddq2outputTmpForDataSetAtSite(dataset,"LRZ-LMU_PHYS-SUSY")
    print '4'
def appenddq2outputTmpForDataSetAtSite(dataset,site):
    command = "dq2-ls -f -p -L "+site+" " +dataset+" | sed 's%srm://lcg-lrz-se.lrz-muenchen.de%dcap://lcg-lrz-dcache.grid.lrz-muenchen.de%' >> dq2output.tmp"
    a, b = commands.getstatusoutput(command)
    if b.find("dq2-ls")>-1 :
        print "you have to init dq2-ls"
        sys.exit()
    if a!=0: outputfile.write("failed to open" + thisDataSetName)
 
ROOT.gROOT.SetBatch(True)
  
if sys.version_info < (2, 5):
  print "Python Version: " + sys.version_info
  raise "must use python 2.5 or greater \n You can try python2.5 "+ sys.argv[0]


filename = "dataset_list.tmp"
if len(sys.argv)==1:
    print ("Usage: \n" + sys.argv[0] + "datasetname [, datasetname2, ...]")
    print (" or ")
    print (sys.argv[0] + " -f file_with_list_of_datasetnames ")
    
    sys.exit()

if sys.argv[1]=="-f":
    filename = sys.argv[2]
if sys.argv[1]!="-f":
    createinputfile = open(filename,'w')
    for arg in sys.argv[1:]:
        createinputfile.write(arg+"\n")
    createinputfile.close()
notknown=0
notreplicated=0
outputfile = open ('output.tmp','w')
notreplicatedfile = open ('notreplicated.tmp','w')
notknownfile = open ('notknown.tmp','w')
outputfile.write('Starting to register datasets\n' )
f = open(filename, 'r')

proof = TProof.Open("")

for DataSetName in f:
    print "Doing dataset ", DataSetName
    thisDataSetName = prepareDatasetFormat(DataSetName)
    print "Doing thisdataset ", thisDataSetName
    createdq2outputTmpForDataSet(thisDataSetName)
    print '1'

    filenames = []
    filelist_filename = 'filelist_'+thisDataSetName.replace("/","")+'.tmp'
    f3 = open (filelist_filename,'w')
    f2 = open ('dq2output.tmp','r')
    lines = 0
    success=1
    f2lines = 0
    print '11'
    for outputline in f2:
        if outputline.find("voms-proxy-init")>-1:
            print outputline
            sys.exit()
        f2lines=f2lines+1
        if (outputline.find("dcap://lcg")==0) and (outputline.find(".root")>0):
            filenames.append(outputline)
            f3.write(outputline)
            lines=lines+1
    print '12'
    if f2lines==0:
        outputfile.write("WARNING: Dataset not known in dq2-ls: " + thisDataSetName + "\n" )
        notknownfile.write(thisDataSetName + "\n" )
        notknown=notknown+1
        success=0
    if lines==0 and f2lines>0:
        outputfile.write("WARNING: Dataset is not replicated at LRZ " + thisDataSetName + "\n" )
        notreplicatedfile.write(thisDataSetName + "\n" )
        notreplicated=notreplicated+1
        success=0
    print '13'
    if lines>0:
        #print lines
        #print filenames
        fc = TFileCollection()
        for f in filenames: 
            filename = f.rstrip('\n')
            fc.Add(filename)

        print '21'
        
        #proof.SetParallel(4)

        datasetname = thisDataSetName.replace("/","")
        #print datasetname
        #print fc
        
        rc = proof.RegisterDataSet(datasetname,fc,"OV")

        if rc:
            print 'Successfully registered dataset %s' %datasetname
        else:
            print 'ERROR registering dataset %s' %datasetname

proof.Close()


outputfile.close()
notreplicatedfile.close()
notknownfile.close()
outputfile = open ('output.tmp','r')
print "outputfile: "
for outputline in outputfile:
    print outputline
if notknown>0:
    print (str(notknown) + " datasets are not qknown to dq2-ls. A list has been saved in notknown.tmp")
if notreplicated>0:
    print (str(notreplicated) + " datasets are not replicated at LRZ. A list has been saved in notreplicated.tmp. You can rerun the list with "+ sys.argv[0] + " -f notreplicated.tmp")

