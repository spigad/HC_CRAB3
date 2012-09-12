#!/usr/bin/env python

""" amixsec.py: script intended to dump AMI cross-section for a list of datasets 

Usage:
chmod u+x SUSYTools/python/amixsec.py
SUSYTools/python/amixsec.py --help
SUSYTools/python/amixsec.py --tag=pXXX

Warning: this script requires access to pyami (setting login/passwd)...
"""
__author__ = "Renaud Bruneliere"

import os,sys,subprocess
from pyAMI.pyAMI import AMI
from pyAMI.amiListDatasets import amiListDatasets

def parseCmdLine(args):
    """ Parse input command line to optdict.
    To get the whole list of options type : prepare_database_cern.py -h"""
    from optparse import OptionParser
    parser = OptionParser()
    parser.add_option("--tag", dest="tag", help="Production tag",default="_p832") 
    (config, args) = parser.parse_args(args)
    return config

def main():
    config = parseCmdLine(sys.argv[1:])
    ami = AMI()
    fdq2 = os.popen('dq2-ls mc*.merge.NTUP_SUSY.*%s/' % (config.tag))
    ldq2 = fdq2.readlines()
    lname = []
    lrawds = []
    for dq2name in ldq2:
        dq2name = dq2name.split('\n')[0]
        evntds = dq2name.replace('.merge.NTUP_SUSY.','.evgen.EVNT.')
        evnttag = evntds.split('.EVNT.')[1].split('_')[0]
        evntds = evntds.split(evnttag)[0]+evnttag
        if evntds in lname: continue
        lname.append(evntds)
        lrawds.append(evntds.split('.')[1])
    dsandname = zip(lrawds,lname)
    dsandname.sort()
    fin  = open('../data/susy_crosssections.txt','r')
    lin = {}
    for i,line in enumerate(fin):
        if i == 0: continue
        line = line.split('\n')[0]
        if line.startswith('#'): continue
        ds = line.split()[0]
        if ds in lin: continue
        lin[ds] = line
    fout = open('susy_crosssections_new.txt','w')
    fout.write('id/I:name/C:xsec/F:kfac/F:eff/F:relunc/F\n')
    for ds,dsname in dsandname:
        if ds in lin: 
            print ds,'already exists',lin[ds]
            continue
        # Check if events are available
        lcmd = ['GetDatasetInfo','logicalDatasetName=%s' % dsname]
        result = ami.execute(lcmd)
        myd = result.getDict()
        #print dsname,myd
        if not u'Element_Info' in myd: continue
        if not 'row_1' in myd[u'Element_Info']: continue
        xsec = -1.
        if u'crossSection_mean' in myd[u'Element_Info']['row_1'] and not u'Calculation impossible' in myd[u'Element_Info']['row_1'][u'crossSection_mean'] and not u'Error detected' in myd[u'Element_Info']['row_1'][u'crossSection_mean']: xsec = float(myd[u'Element_Info']['row_1'][u'crossSection_mean'])*1000. # convert to pb
        eff = 1.
        if u'GenFiltEff_mean' in myd[u'Element_Info']['row_1'] and not u'Calculation impossible' in myd[u'Element_Info']['row_1'][u'GenFiltEff_mean']: eff = float(myd[u'Element_Info']['row_1'][u'GenFiltEff_mean'])
        kfac = relunc = 1.
        line = '%s\t%s\t%f\t%f\t%f\t%f\n' % (ds,dsname.split('.')[2],xsec,kfac,eff,relunc)
        print line,
        fout.write(line)
        #break
    fout.close()
 
if __name__ == "__main__":
    main() 
