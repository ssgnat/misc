#!/bin/bash
# source ./test.sh SERVER CLIENT
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/../../bin/lib
sudo killall hzbusd
sudo killall $1
sudo killall $2
../../bin/hzbusd -s /tmp/hzbus.sock &
sleep 5
./$1 &
sleep 10
./$2
killall $1
killall $2
killall hzbusd

