#!/bin/bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/../../bin/lib
killall hzbusd
../../bin/hzbusd /tmp/hzbus.sock&
sleep 5
./test_conduit &
sleep 5
killall test_conduit
killall hzbusd

