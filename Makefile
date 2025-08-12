# SPDX-License-Identifier: MIT

# Makefile for Amber's BBS Interface
# Buildsys by Gale Faraday

# `generate` must be called before `all` to build version information and other
# machine generated files.

.PHONY: all clean run generate
.SUFFIXES:

.DEFAULT_GOAL := all

TARGET     := $(shell basename $(CURDIR))
SOURCES    := src/
BUILD      := build/
GENABLES   := $(SOURCES)version.c
OBJS       := $(patsubst $(SOURCES)%.c,$(BUILD)%.o,$(wildcard $(SOURCES)*.c))
EXECUTABLE := $(TARGET)


CC      := gcc
LD      := gcc
CFLAGS  := -std=c99 -pedantic -Wall -Wextra -Wno-unused-parameter -O2 -ggdb
LDFLAGS := $(CFLAGS) -lncurses

all: $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

.IGNORE: clean
clean:
	@rm -rvf $(BUILD) $(EXECUTABLE) $(GENABLES)

generate: $(GENABLES)

$(GENABLES): genver.sh
	./genver.sh

$(EXECUTABLE): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

$(OBJS): $(BUILD)%.o : $(SOURCES)%.c
	-@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -o $@ -c $<
