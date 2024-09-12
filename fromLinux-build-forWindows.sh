#!/bin/bash
#Compile the parts
x86_64-w64-mingw32-gcc -c modules/sqlite3.c
x86_64-w64-mingw32-g++ -c main.cpp

#Join them into one binary
x86_64-w64-mingw32-g++ -o Banking-System-x86_64-Windows.bin main.o sqlite3.o