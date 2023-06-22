#!/bin/sh

# Support the CC environment variable as the desired C compiler
if [ "$CC" = "" ]
then
    CC=cc
fi

if [ "$CFLAGS" = "" ]
then
    CFLAGS="-Wall -Werror -std=c++17"
fi

$CC src/*.cpp -o rhinoxr2.exe
