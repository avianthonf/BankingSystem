#!/bin/bash
#Compile the parts
gcc -c modules/sqlite3.c
g++ -c main.cpp

#Join them into one binary
g++ -o Banking-System-x86_64-Linux.bin main.o sqlite3.o

# Ensure build output exists
if [ -f Banking-System-x86_64-Linux.bin ]; then
  echo "Build completed successfully."
else
  echo "Build failed."
  exit 1
fi