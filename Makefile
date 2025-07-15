CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra
LIBS=-lncursesw
EXECUTABLE=bbs

.PHONY: all
all: make


make:
	$(CC) $(CFLAGS) $(LIBS) bbs.c -o $(EXECUTABLE)

.PHONY: execute
execute:
	./$(EXECUTABLE)

.PHONY: run
run: make execute
