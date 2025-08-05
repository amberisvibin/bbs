# SPDX-License-Identifier: MIT

# Makefile for Amber's BBS Interface
# Buildsys by Gale Faraday

.PHONY: all clean run
.SUFFIXES:

.DEFAULT_GOAL := all

TARGET     := $(shell basename $(CURDIR))
SOURCES    := src/
BUILD      := build/
OBJS       := $(patsubst $(SOURCES)%.c,$(BUILD)%.o,$(wildcard $(SOURCES)*.c))
EXECUTABLE := $(TARGET)


CC      := gcc
LD      := gcc
CFLAGS  := -std=c99 -pedantic -Wall -Wextra -O2 -ggdb
LDFLAGS := $(CFLAGS) -lncursesw

all: $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

.IGNORE: clean
clean:
	@rm -rvf $(BUILD) $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

$(OBJS): $(BUILD)%.o : $(SOURCES)%.c
	-@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -o $@ -c $<
