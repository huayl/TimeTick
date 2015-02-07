#*************************************************
# 名称：Makefile
# 功能：编译MD5加密开发库  
# 作者：华玉磊
# 时间: 2009年
#**************************************************/

.SUFFIXES: .c .o

LIBDIR=$(HOME)/lib
LIBINCDIR=$(HOME)/src/libsrc/include
    
CC=gcc

LIBS=libtqueue.a libtqueue.so

CFLAGS=-Wall -O2 -I. -I$(LIBINCDIR)

LDFLAGS=-L. -L$(LIBDIR)

#LDLIBS= -lsocket -lnsl -lresolv -lrt

AR=ar

ARFLAGS=r

all:$(LIBS)

libtqueue.a:libtdiff.o libtq.o libutil.o libtqctl.o
	$(AR) $(ARFLAGS) $@ $?
	
libtqueue.so:libtdiff.c libtq.c libutil.c libtqctl.c
	rm -f *.o
	$(CC) -fPIC -shared $(CFLAGS) -o $@ $?

install:
	mv  $(LIBS) $(LIBDIR)
#	mv  *.h  $(INCDIR)  
	rm -f  *.o *.out *core 
	
clean:
	rm -f  *.o *.out *core 
	rm -f $(LIBS) 
