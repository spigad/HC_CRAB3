import getopt,sys,os
from datetime import date, timedelta
from hc.core.utils.generic.class_func import custom_import

def main():
    try:
        opts, args = getopt.getopt(sys.argv[2:], "", ["doit"])
        app = str(sys.argv[1])
    except getopt.GetoptError, err:
        # print help information and exit:
        print str(err) # will print something like "option -a not recognized"
        usage()
        sys.exit(2)
    doit = False
    for o, a in opts:
        if o in ("--doit"):
            doit=True
        else:
            assert False, "unhandled option"
   
    

    #cursor.execute ("select distinct id,endtime from test where date_add(endtime,interval 30 day)<now()")
    days = timedelta(days=30)
    begin = date.today() - days
    t = custom_import('hc.%s.models.Test'%(app))
    tests = t.objects.filter(endtime__lt=begin)
    for test in tests:
        print "Test #%d: ended %s."%(test.id, test.endtime),
        dir = '/data/hc/apps/cms/testdirs/test_%d'%test.id
        if os.path.exists(dir):
            print "going to rm -rf %s"%dir,
            if doit: 
                os.system('rm -rf %s'%dir)
                print "done",
            else:
                print "need to --doit",
        else:
            print "testdir already deleted",
        f = '/data/hc/apps/cms/testdirs/run-test-%d.sh'%test.id
        if os.path.exists(f):
            print "going to rm %s"%f,
            if doit: 
                os.system('rm %s'%f)
                print "done"
            else:
                print "need to --doit"
        else:
            print "runscript already deleted"


if __name__ == "__main__":
    main()
