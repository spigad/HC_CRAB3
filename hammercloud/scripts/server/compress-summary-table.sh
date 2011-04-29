#!/bin/sh

echo ''
echo '_ Compress Summary Table Main.'
echo ''


if [ -z $1 ]
then
    echo '  ERROR! Please, set application tag.'
    echo ''
    echo '_ End Compress Summary Table.'
    echo ''
    exit
fi

# WARNING !
if [ -f /tmp/compress-summary-table_$1.running ]
then
    echo '  ERROR! Script 'compress-summary-table_$1 already running.
    echo ''
    echo '_ End Compress Summary Table Main.'
    echo ''
    exit
fi

touch /tmp/compress-summary-table_$1.running
echo '  Lock written: '/tmp/compress-summary-table_$1.running

#Get HCDIR from current installation.
HCDIR=`which $0|sed 's/\/scripts/ /g'|awk '{print $1}'`

echo ''
source $HCDIR/scripts/config/config-main.sh $1 $HCDIR
echo ''

cd $HCDIR

echo '  CODE: python python/scripts/dispatcher.py -f compress_summary_table'
echo ''
python python/scripts/dispatcher.py -f compress_summary_table -o 'd'
echo ''
echo '  END CODE'
rm -f /tmp/compress-summary-table_$1.running

echo '  Lock released: '/tmp/compress-summary-table_$1.running
echo ''
echo '_ End Compress Summary Table Main.'
echo ''
