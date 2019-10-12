#!/bin/bash

SUCESS=true

for i in {1..50}; do
    ./tp 4 1 1 test_files/alot out 
    diff out test_files/alot4.out

    if [ $? -gt 0 ]; then
        SUCESS=false
    fi

    ./tp 4 1 1 test_files/oneblk out
    diff out test_files/oneblk4.out

    if [ $? -gt 0 ]; then
        SUCESS=false
    fi

    ./tp 4 2 2 test_files/alot out
    diff out test_files/alot4.out

    if [ $? -gt 0 ]; then
        SUCESS=false
		fi

    #./tp 3 1 1 test_files/zeroblk out
    #diff out test_files/zeroblk3.out

    if [ $? -gt 0 ]; then
        SUCESS=false
    fi
		
		./tp 8 1 1 test_files/pad out
    diff out test_files/pad8.out

    if [ $? -gt 0 ]; then
        SUCESS=false
    fi
done

if [ "$SUCESS" = true ]; then
    echo "OK"
else
    echo "FAILED"
fi
