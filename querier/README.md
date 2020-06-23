# CS50 Lab 5
## Stephen Crowe, May 2018

### indexer

The *querier* is a program to be used in conjunction with the *crawler* and *indexer* programs. It takes the page directory output of the crawler and the index filename to execute properly. It then returns matches according to the amount of times the words appeared in the crawl.

### Usage

The *querier* program should be run as follows:
	./querier pageDirectory indexFilename

### Implementation

The querier is implemented with various structures - a hashtable of counters to represent the index, an array of pointers to words in the buffer, and a linked list to sort the final counters structure.

The querier uses functions from the *common* library, but most of the code is in the *query* module.  See the [IMPLEMENTATION](IMPLEMENTATION.md) document for specifics on implementation.

### Assumptions

The crawler directory must have created a .crawler file to be valid. The indexer must have created an index file

No other assumptions.

### Compilation

To compile, simply `make querier.o`.

To test, simply `make test`.
See [TESTING](TESTING.md) for details of testing and an example test run.
