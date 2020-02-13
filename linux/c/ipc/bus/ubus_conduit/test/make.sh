#!/bin/bash

function MAKETARGET()
{
    echo $1
    make clean && make TARGET=-D$1 >build.log 2>&1
    #sudo ./test.sh
}


MAKETARGET TEST_CALL
MAKETARGET TEST_SRV_EVENTS
MAKETARGET TEST_CLI_EVENTS

