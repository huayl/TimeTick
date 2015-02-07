LIBDIR=$(HOME)/lib
INCDIR=$(HOME)/include 
    
CC = gcc

INCLUDES = -I$(INCDIR) -I /usr/include

LIBS = -L$(LIBDIR) -ltqueue 

all:test


runtick.o: runtick.c
	$(CC) -c $(INCLUDES)  runtick.c

runtick: runtick.o
	$(CC) -o runtick runtick.o $(LIBS)

clean:
	rm -f runtick *.o