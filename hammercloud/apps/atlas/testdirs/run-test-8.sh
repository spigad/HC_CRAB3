cd /data/hammercloud/apps/atlas
mkdir -p testdirs/test_8
if [ -e "testdirs/test_8/stdouterr.txt" ]
then
  mv testdirs/test_8/stdouterr.txt testdirs/test_8/stdouterr.txt.`date +%s`
fi
./test-scripts/testscript 8 gangabin &> testdirs/test_8/stdouterr.txt
