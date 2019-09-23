#!/bin/bash

function MAKETARGET()
{
    echo $1 CLIENT
    #make NAME=CLIENT clean && make TARGET=-D$1 MODE=-DCLIENT NAME=CLIENT >build.log 2>&1
    make -B TARGET=-D$1 MODE=-DCLIENT NAME=CLIENT
    echo $1 SERVER
    #make NAME=CLIENT clean && make TARGET=-D$1 MODE=-DSERVER NAME=SERVER >build.log 2>&1
    make -B TARGET=-D$1 MODE=-DSERVER NAME=SERVER

    if [ $1 == "TEST_CLI_EVENTS" ];then
        ./test.sh CLIENT SERVER
    else
        ./test.sh SERVER CLIENT
    fi
}




MAKETARGET TEST_CALL
MAKETARGET TEST_SRV_EVENTS
MAKETARGET TEST_CLI_EVENTS

