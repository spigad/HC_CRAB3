#!/usr/bin/env python

from django.utils.timezone import now
from hc.atlas.models import GlobalOption
import commands, sys

def checkNightly(rel,cmtconfig):
    # Check release on CVMFS
    cmd = "ls -l /cvmfs/atlas-nightlies.cern.ch/repo/sw/nightlies/%s/%s/ | grep latest" %(cmtconfig,rel)
    rc, out = commands.getstatusoutput(cmd)
    dirrel = "rel_0"
    if rc!=0:
        print "ERROR during execution of: '%s' " %cmd
        return
    else:
        dirrel = out[-5:]

    # Get last rel from DB
    tmprel = rel.replace('.','')
    tmpvar = 'last_nightly_%s_value' %tmprel
    try:
        dbrel = GlobalOption.objects.get(option_name=tmpvar)
    except GlobalOption.DoesNotExist:
        GlobalOption(option_name=tmpvar, option_value=dirrel).save()
        dbrel = GlobalOption.objects.get(option_name=tmpvar)
        tmpvar = 'last_nightly_%s_change' %tmprel
        GlobalOption(option_name=tmpvar, option_value=now()).save()

    # If CVMFS rel values is different from DB value -> update
    if not dbrel.option_value==dirrel:
        try:
            dbrel = GlobalOption.objects.get(option_name=tmpvar)
            dbrel.option_value = dirrel
            dbrel.save()
        except GlobalOption.DoesNotExist:
            GlobalOption(option_name=tmpvar, option_value=dirrel).save()

        tmpvar = 'last_nightly_%s_change' %tmprel
        try:
            lastchange = GlobalOption.objects.get(option_name=tmpvar)
            lastchange.option_value = now()
            lastchange.save()
        except GlobalOption.DoesNotExist:
            GlobalOption(option_name=tmpvar, option_value=now()).save()

        try:
            print "CVMFS %s release changed. Update HammerCloud DB with: %s, %s" %(rel, dirrel, lastchange.option_value) 
        except:
            pass
    else:
        try:
            tmpvar = 'last_nightly_%s_change' %tmprel
            lastchange = GlobalOption.objects.get(option_name=tmpvar)
            print "CVMFS %s release unchanged. DB entries: %s, %s" %(rel, dbrel.option_value, lastchange.option_value)
        except:
            pass

    return

if __name__ == "__main__" :
    checkNightly("17.X.0","x86_64-slc5-gcc43-opt")
    checkNightly("18.X.0","x86_64-slc5-gcc43-opt")
    checkNightly("17.2.X","i686-slc5-gcc43-opt")
