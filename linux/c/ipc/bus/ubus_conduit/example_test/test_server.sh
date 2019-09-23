#!/bin/bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/../../bin/lib
killall hzbusd
../../bin/hzbusd -s /tmp/hzbus.sock &
sleep 5
./$1
killall $1
killall hzbusd

