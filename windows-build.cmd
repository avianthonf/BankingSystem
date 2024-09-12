#Compile the parts
gcc -c modules/sqlite3.c
g++ -c main.cpp

#Join them into one binary
g++ -o Banking-System-x86_64-Windows.bin main.o sqlite3.o