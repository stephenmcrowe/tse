# Makefile for the "crawler" program.
#
# Stephen Crowe
# CS50 - Prof. Palmer

CC=gcc
CFLAGS=-Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50 -I../common
PROG = crawler
OBJS = crawler.o ../common/pagedir.o  ../libcs50/webpage.o
LIBS = -L../libcs50 -lcs50 #-L../common -lcommon

.PHONY: all test debug clean

all: $(PROG)

# executable depends on object files
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(PROG)

# object files depend on include files
crawler.o: ../common/pagedir.h
pagedir.o: ../common/pagedir.h ../libcs50/webpage.h
webpage.o: ../libcs50/webpage.h

test: $(PROG)
	./crawler http://old-www.cs.dartmouth.edu/~scrowe/index.html /net/ifs-users/scrowe/cs50/labs/tse/test 5

debug: TESTING=-DDEBUG
debug: $(PROG)
	./crawler http://old-www.cs.dartmouth.edu/~scrowe/index.html /net/ifs-users/scrowe/cs50/labs/tse/test 2

clean:
	rm -f $(PROG)
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f ../test/*
