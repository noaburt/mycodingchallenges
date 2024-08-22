

# This is the default makefile for coding challenges as set by mkcc 1.0.2

all: main test

main: main.c functions.c
      gcc -o main functions.c main.c -I. -Wall -pedantic

test: test.c
      gcc -o test test.c -Wall -pedantic

