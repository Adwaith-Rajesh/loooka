#!/bin/env bash

TEST_DIR=./test

for i in $TEST_DIR/*.c
do
    gcc -Wall -Wextra -I./src $i
    ./a.out
done


rm ./a.out
