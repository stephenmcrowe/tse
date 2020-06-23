/*
 * Stephen Crowe
 * CS50 - Prof. Palmer
 * Lab 5 Indexer
 *
 * testindex.c - a unit testing file for the index module. It runs hardcoded test cases for fast testing.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"
#include "hashtable.h"
#include "counters.h"

int main()
{
	char *pageDirtest = "/net/ifs-users/scrowe/cs50/labs/tse/crawler/testruns/savedPages/letters10pages";

	hashtable_t *ht = hashtable_new(10);
	indexBuild(pageDirtest, ht);

	printf("This is for testing the index.c\n");

	char *filename = "testindex.out";
	indexSave(filename, ht);
	hashtable_delete(ht, (void(*)(void*))counters_delete);

	hashtable_t *loadHt = hashtable_new(15);
	indexLoad(filename, loadHt);
	hashtable_delete(loadHt, (void(*)(void*))counters_delete);
}
