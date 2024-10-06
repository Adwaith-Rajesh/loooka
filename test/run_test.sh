#!/bin/env bash

TEST_DIR=./test

for i in $TEST_DIR/*.c
do
    gcc -Wall -Wextra -I./src -I./src/utils -I./src/ds $i
    ./a.out
done


rm ./a.out
