# Makefile template for shared library

LIB_NAME=sort
DIST=debug

#  
#  CC = gcc # C compiler
CFLAGS = -fPIC -Wall -Wextra -O2 -pg # C flags
#LDFLAGS = -shared  # linking flags
LDFLAGS = -shared  # linking flags
RM = rm -f  # rm command
#TARGET_LIB = libsort.so # target lib
TARGET_LIB = libsort.so # target lib

#BASE_PATH=/home/yyang/workspace/github/toolbox
BASE_PATH=/local/yyang/workspace/github/toolbox
BASE_LIB_PATH=$(BASE_PATH)/lib
BASE_HEADER_PATH=$(BASE_PATH)/include
TARGET_LIB_PATH=$(BASE_PATH)/lib

SRCS = sort.c quicksort_ll.c # source files
OBJS = $(SRCS:.c=.o)

CFLAGS += -I${BASE_HEADER_PATH}
LDFLAGS += -L${BASE_LIB_PATH} -lrandom
	 
.PHONY: all
all: ${TARGET_LIB}
	 
$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^
		 
$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@
			 
include $(SRCS:.c=.d)
	 
.PHONY: clean install
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d)

install:
	cp ${TARGET_LIB} ${TARGET_LIB_PATH}
	cp ${LIB_NAME}.h ${BASE_HEADER_PATH}
