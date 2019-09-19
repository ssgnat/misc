#!/bin/bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/../../bin/lib
killall hzbusd
cd ../../bin/
./hzbusd -s /tmp/hzbus.sock &
cd -
./test_conduit
sleep 1
killall test_conduit
killall hzbusd

