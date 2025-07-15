CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra
LIBS=-lncursesw
EXECUTABLE=bbs

all: make

make:
	$(CC) $(CFLAGS) $(LIBS) bbs.c -o $(EXECUTABLE)

run:
	./$(EXECUTABLE)
