#!/bin/bash
cppcheck --enable=all --check-config . .. -I. -I../../../cmockery/src/google -I../ 
