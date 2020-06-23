# Makefile for the "indexer" program.
#
# Stephen Crowe
# CS50 - Prof. Palmer

CC=gcc
CFLAGS=-Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50 -I../common -L../libcs50 -L../common
PROG = indexer indextest
INDEXOBJ = indexer.o
INDEXTESTOBJ = indextest.o
LIBS = -lcommon -lcs50

.PHONY: all test debug clean

all: $(PROG)

# executable depends on object files
indexer: $(INDEXOBJ)
	$(CC) $(CFLAGS) $(INDEXOBJ) $(LIBS) -o $@

indextest: $(INDEXTESTOBJ)
	$(CC) $(CFLAGS) $(INDEXTESTOBJ) $(LIBS) -o $@

# object files depend on include files
indexer.o: ../libcs50/hashtable.h ../common/index.h ../libcs50/counters.h
indextest.o: ../libcs50/hashtable.h ../common/index.h ../libcs50/counters.h

test: $(PROG)
	./indexer /net/ifs-users/scrowe/cs50/labs/tse/crawler/testruns/savedPages/letters10pages/ /net/ifs-users/scrowe/cs50/labs/tse/crawler/testruns/savedPages/letters10pages/indexertest.out
	./indextest /net/ifs-users/scrowe/cs50/labs/tse/crawler/testruns/savedPages/letters10pages/indexertest.out indextest.out

clean:
	rm -f $(PROG)
	rm -f indextest.out
	rm -f *~ *.o
	rm -rf *.dSYM
