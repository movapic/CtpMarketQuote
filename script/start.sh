#!/bin/bash
curdir=$(dirname $0)
cd $curdir
curdir=$(pwd)
pardir=$(dirname $curdir)
export LD_LIBRARY_PATH=$pardir/dynlib/
cd $pardir
echo $pardir
./build/bin/tickquote --outpath=logdir --cfgfile=build/bin/conn.cfg
