CC=gcc
CXX=g++
RM=rm -rf
CPP_FILES := $(wildcard *.cpp)
C_FILES := $(wildcard *.c)
OBJS := $(addprefix obj/,$(notdir $(C_FILES:.c=.o)))

CPPFLAGS=-g -O0 --coverage -Wall
CFLAGS=-g -O0 --coverage -Wall
LDFLAGS=-g -O0 --coverage 
LDLIBS=

all: main

main: $(OBJS)
	$(CC) $(LDFLAGS) -o toolbox $(OBJS) $(LDLIBS) 

obj/%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<
clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) toolbox out obj/*
