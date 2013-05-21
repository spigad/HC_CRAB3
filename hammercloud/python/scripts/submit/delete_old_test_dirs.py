import getopt,sys,os
from datetime import date, timedelta
from hc.core.utils.generic.class_func import custom_import

def main():
    days_to_keep = 3
    try:
        opts, _ = getopt.getopt(sys.argv[2:], "", ["days=","doit"])
        app = str(sys.argv[1])
    except getopt.GetoptError, err:
        # print help information and exit:
        print str(err) # will print something like "option -a not recognized"
        sys.exit(2)
    doit = False
    for o, a in opts:
        if o in ("--doit"):
            doit=True
        elif o in ('--days'):
            try:
                days_to_keep = int(a)
            except:
                pass
        else:
            assert False, "unhandled option"
   
    

    #cursor.execute ("select distinct id,endtime from test where date_add(endtime,interval 30 day)<now()")
    print 'Keeping tests for %d days.' % days_to_keep
    days = timedelta(days=days_to_keep)
    begin = date.today() - days
    t = custom_import('hc.%s.models.Test'%(app))
    tests = t.objects.filter(endtime__lt=begin)
    for test in tests:
        print "Test #%d: ended %s."%(test.id, test.endtime),
        dir = '%s/apps/%s/testdirs/test_%d'%(os.environ['HCDIR'],app,test.id)
        if os.path.exists(dir):
            print "going to rm -rf %s"%dir,
            if doit: 
                os.system('rm -rf %s'%dir)
                print "done.",
            else:
                print "need to --doit.",
        else:
            print "testdir already deleted.",
        files = ['%s/apps/%s/testdirs/run-test-%d.sh'%(os.environ['HCDIR'],app,test.id), 
                '/tmp/%d.%s'%(test.id, str(test.usercode).split('/')[-1])]
        for f in files:
            if os.path.exists(f):
                print "going to rm %s"%f,
                if doit: 
                    os.system('rm %s'%f)
                    print "done.",
                else:
                    print "need to --doit.",
            else:
                print "no such file %s." % f,
        print


if __name__ == "__main__":
    main()
