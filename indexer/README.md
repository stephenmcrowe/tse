# CS50 Lab 5
## Stephen Crowe, May 2018

### indexer

The *indexer* is a program to be used in conjunction with the crawler program. It takes the page directory output of the crawler and a filename as parameters to execute properly. It then combs through the pages to count all the words and save that index in the filename.

### Usage

The *indexer* program should be run as follows:
	./indexer pageDirectory filename

### Implementation

The indexer is implemented with a hashtable with the keys corresponding to words in the webpages and the items are counters structures. The counters structure holds the id of the webpage and the number of times the word was found in that webpage.

The indexer primarily uses functions from the *common* library. See the *index* module or the [IMPLEMENTATION](IMPLEMENTATION.md) document for specifics on implementation.

### Assumptions

The crawler directory must have created a .crawler file to be valid.

No other assumptions.

### Compilation

To compile, simply `make indexer.o`.

To test, simply `make test`.
See [TESTING](TESTING.md) for details of testing and an example test run.
