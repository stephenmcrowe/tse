# Makefile for the "querier" program.
#
# Stephen Crowe
# CS50 - Prof. Palmer

CC=gcc
CFLAGS=-Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50 -I../common
PROG = querier
OBJ = querier.o query.o linkedList.o
LIBS = -L../libcs50 -L../common -lcommon -lcs50

.PHONY: all test clean

all: $(PROG)

# executable depends on object files
$(PROG): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(PROG)

# object files depend on include files
querier.o: ../libcs50/hashtable.h ../common/index.h ../libcs50/counters.h query.h
query.o: query.h ../libcs50/counters.h linkedList.h
linkedList.o: linkedList.h

test: $(PROG)
	./querier ../crawler/testruns/savedPages/wikipedia1pages/ ../crawler/testruns/savedPages/wikipedia1pages/index < tests/wikipedia.txt

clean:
	rm -f $(PROG)
	rm -f *~ *.o
	rm -rf *.dSYM
