#!/bin/bash

function MAKETARGET()
{
    CLINAME=CDT_PRESS_CLIENT
    SRVNAME=CDT_PRESS_SERVER
    echo $1 CLIENT
    #make NAME=CLIENT clean && make TARGET=-D$1 MODE=-DCLIENT NAME=CLIENT >build.log 2>&1
    make -B TARGET=-D$1 MODE=-DCLIENT NAME=$CLINAME
    echo $1 SERVER
    #make NAME=CLIENT clean && make TARGET=-D$1 MODE=-DSERVER NAME=SERVER >build.log 2>&1
    make -B TARGET=-D$1 MODE=-DSERVER NAME=$SRVNAME

    if [ $1 == "TEST_CLI_EVENTS" ];then
        ./test.sh $CLINAME $SRVNAME
    else
        ./test.sh $SRVNAME $CLINAME
    fi

}




MAKETARGET TEST_CALL
#MAKETARGET TEST_SRV_EVENTS
#MAKETARGET TEST_CLI_EVENTS
