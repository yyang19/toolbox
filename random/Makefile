# Makefile template for shared library
#  
#  CC = gcc # C compiler
CFLAGS = -fPIC -Wall -Wextra -O2 -g # C flags
LDFLAGS = -shared  # linking flags
RM = rm -f  # rm command
TARGET_LIB = librandom.so # target lib

BASE_PATH=/home/yyang/workspace/github/toolbox
#BASE_PATH=/local/yyang/workspace/github/toolbox
TARGET_LIB_PATH=$(BASE_PATH)/lib

SRCS = random.c # source files
OBJS = $(SRCS:.c=.o)
	 
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
