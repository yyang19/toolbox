CC=gcc
CXX=g++
RM=rm -rf
CPP_FILES := $(wildcard *.cpp)
C_FILES := $(wildcard *.c)
OBJS := $(addprefix obj/,$(notdir $(C_FILES:.c=.o)))

BASE_PATH=/local/yyang/workspace/github/toolbox
#BASE_PATH=/home/yyang/workspace/github/toolbox
BASE_LIB_PATH=$(BASE_PATH)/lib
BASE_HEADER_PATH=$(BASE_PATH)/include

CPPFLAGS=-g -O0 --coverage -Wall
CFLAGS=-pg -O0 --coverage -Wall -I${BASE_HEADER_PATH}
LDFLAGS=-pg -O0 --coverage -L${BASE_LIB_PATH} -Wl,-rpath=${BASE_LIB_PATH} 
LDLIBS=-lrandom -lsort

all: main

main: $(OBJS)
	$(CC) $(LDFLAGS) -o test_sorting $(OBJS) $(LDLIBS) 

obj/%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<
clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) test_sorting out obj/*
