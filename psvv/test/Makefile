BINARY=test_psvv
CC=gcc
CXX=g++
RM=rm -rf
CPP_FILES := $(wildcard *.cpp)
C_FILES := $(wildcard *.c)
OBJS := $(addprefix obj/,$(notdir $(C_FILES:.c=.o)))
TMPS := gmon.out

BASE_PATH=../..
BASE_LIB_PATH=$(BASE_PATH)/lib
BASE_HEADER_PATH=$(BASE_PATH)/include

CPPFLAGS=-g -O0 --coverage -Wall
CFLAGS=-g -pg -O0 --coverage -Wall -I${BASE_HEADER_PATH}
LDFLAGS=-g -pg -O0 --coverage -L${BASE_LIB_PATH} -Wl,-rpath=${BASE_LIB_PATH} 
LDLIBS=-lmath -lpsvv -lm

all: main

main: $(OBJS)
	$(CC) $(LDFLAGS) -o ${BINARY} $(OBJS) $(LDLIBS) 

obj/%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<
clean:
	$(RM) $(OBJS) $(OBJS)

dist-clean: clean
	$(RM) ${BINARY} $(TMPS) out obj/*
