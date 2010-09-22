#!/bin/sh

echo '_._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
echo '_                                                                 _'
echo '_                           Script Test                           _'
echo '_._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
echo '_'
echo '_'


if [ -z $1 ]
then
    echo '_  ERROR! Please, set application tag.'
    echo '_'
    echo '_                         End Script Test                         _'
    echo '_._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
    echo '_'
    exit
fi

if [ -z $2 ]
then
    echo '_  ERROR! Please, set function'
    echo '_'
    echo '_                         End Script Test                         _'
    echo '_._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
    echo '_'
    exit
fi

if [ -z $3 ]
then
    echo '_  No HCDIR provided. Using HCDIR=/data/hammercloud'
    HCDIR=/data/hammercloud
else
    HCDIR=$3
fi

echo '_'
source $HCDIR/scripts/config/config-main.sh $1 $HCDIR
echo '_'

cd $HCDIR

echo '_ CODE: python' python/scripts/cron_dispatcher.py -a $1 -f create_functional_tests
echo '_'
python python/scripts/cron_dispatcher.py -a $1 -f $2
echo '_'
echo '_ END CODE'

echo '_'
echo '_                         End Script Test                         _'
echo '_._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._'
echo '_'
