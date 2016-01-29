# Makefile template for shared library

LIB_NAME=math
DIST=debug
#  
#  CC = gcc # C compiler

ifeq ($(strip $(DIST)),debug)
      CFLAGS = -fPIC -Wall -Wextra -pg -g -lm # C flags
else
	CFLAGS = -fPIC -Wall -Wextra -O2  # C flags
endif

#LDFLAGS = -shared  # linking flags
LDFLAGS = -shared  # linking flags
RM = rm -f  # rm command
#TARGET_LIB = libmath.so # target lib
TARGET_LIB = lib${LIB_NAME}.so # target lib

BASE_PATH=..
BASE_LIB_PATH=$(BASE_PATH)/lib
BASE_HEADER_PATH=$(BASE_PATH)/include
TARGET_LIB_PATH=$(BASE_PATH)/lib

SRCS = math.c # source files
OBJS = $(SRCS:.c=.o)

CFLAGS += -I${BASE_HEADER_PATH}
LDFLAGS += -L${BASE_LIB_PATH} 
LDLIBS=-lmath -lpsvv -lm
	 
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
