# SPDX-License-Identifier: MIT

CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra -O2 -ggdb
LIBS=-lncursesw
EXECUTABLE=bbs

# .PHONY: all
# all: make

make: bbs

bbs: bbs.c home.c home.h globals.h
	$(CC) $(CFLAGS) $(LIBS) bbs.c home.c -o $(EXECUTABLE)

run: bbs
	./$(EXECUTABLE)
