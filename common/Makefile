# Makefile for the "common" library
# Builds and compiles all these useful functions into a library
# Also builds the unit tests for the pagedir and index modules.
#
# Stephen Crowe
# CS50 - Prof. Palmer

CC=gcc
CFLAGS=-Wall -pedantic -std=c11 -ggdb -I../libcs50
LIB = libcommon.a
PROG = pagedirtest testindex
INDEXOBJS = testindex.o index.o pagedir.o word.o
PAGEOBJS = pagedirtest.o pagedir.o
LIBS = -L../libcs50 -lcs50 -lm

.PHONY: all test clean

all: $(LIB) $(PROG)

# Build the library by archiving object files
$(LIB): $(INDEXOBJS) $(PAGEOBJS)
	ar cr $(LIB) $(INDEXOBJS) $(PAGEOBJS)

# executable depends on object files
pagedirtest: $(PAGEOBJS)
	$(CC) $(CFLAGS) $(PAGEOBJS) $(LIBS) -o $@

testindex: $(INDEXOBJS)
	$(CC) $(CFLAGS) $(INDEXOBJS) $(LIBS) -o $@

# object files depend on include files
testindex.o: index.h ../libcs50/hashtable.h ../libcs50/counters.h
index.o: index.h pagedir.h word.h ../libcs50/file.h ../libcs50/webpage.h ../libcs50/hashtable.h ../libcs50/counters.h
pagedirtest.o: pagedir.h
pagedir.o: pagedir.h ../libcs50/webpage.h
word.o: word.h

test: $(PROG)
	./pagedirtest
	./testindex

clean:
	rm -f $(PROG)
	rm -f testindex.out
	rm -f *~ *.o
	rm -rf *.dSYM
