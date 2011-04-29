cd /data/hc/apps/atlas
mkdir -p testdirs/test_8
if [ -e "testdirs/test_8/stdouterr.txt" ]
then
  mv testdirs/test_8/stdouterr.txt testdirs/test_8/stdouterr.txt.`date +%s`
fi
cd /data/hc
./scripts/submit/test-run.sh atlas /data/hc/external/ganga/install/HEAD/bin/ganga 8 -m default &> /data/hc/apps/atlas/testdirs/test_8/stdouterr.txt
