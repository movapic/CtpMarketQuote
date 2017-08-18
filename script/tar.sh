#!/bin/bash
curdir=$(dirname $0)
cd $curdir
curdir=$(pwd)
pardir=$(dirname $curdir)
cd $pardir/logdir
datestr=$(date -d today +"%Y%m%d")
../build/bin/tickfetch tick.$datestr.csv $datestr
tar zcvf $datestr.tar.gz *_$datestr.csv
rm *_$datestr.csv
