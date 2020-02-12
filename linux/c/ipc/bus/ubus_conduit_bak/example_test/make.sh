#!/bin/bash

make -B T=event_client
make -B T=event_server

./test.sh event_server event_client
