#Compiler
CC=gcc

uname_S := $(shell sh -c 'uname -s 2>/dev/null || echo not')

#Source code files
SRC=caches.c auxiliary.c 

#Flags
#CFLAGS=-Wformat -g #with debugging info
CFLAGS=-Wformat 

#LDFLAGS=-lrt
LDFLAGS=
ifeq ($(uname_S),Linux)
    LDFLAGS += 
endif

#Optional flags
OPT_FLAGS=

OBJECTS=$(SRC:.c=.o)
EXECUTABLE=cacheTest

all: $(EXECUTABLE)
	
$(EXECUTABLE): $(SRC) 
	$(CC) $(CFLAGS) $(OPT_FLAGS) $(SRC) $(LDFLAGS) -o $(EXECUTABLE)


clean:
	/bin/rm -rf *.o cacheTest


