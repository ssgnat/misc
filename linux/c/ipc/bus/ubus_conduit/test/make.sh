#!/bin/bash

function MAKETARGET()
{
    echo $1
    make clean && make TARGET=$1
}


MAKETARGET TEST_CALL
MAKETARGET TEST_SRV_EVENTS
MAKETARGET TEST_CLI_EVENTS

