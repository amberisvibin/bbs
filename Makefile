CC=gcc
CFLAGS=-lncursesw
EXECUTABLE=bbs

all: make

make:
	$(CC) $(CFLAGS) bbs.c -o $(EXECUTABLE)

run:
	./$(EXECUTABLE)
