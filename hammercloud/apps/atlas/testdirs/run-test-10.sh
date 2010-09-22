cd /data/hammercloud/apps/atlas
mkdir -p testdirs/test_10
if [ -e "testdirs/test_10/stdouterr.txt" ]
then
  mv testdirs/test_10/stdouterr.txt testdirs/test_10/stdouterr.txt.`date +%s`
fi
./test-scripts/testscript 10 gangabin &> testdirs/test_10/stdouterr.txt
