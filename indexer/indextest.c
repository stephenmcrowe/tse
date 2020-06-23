/*
 * Stephen Crowe
 * CS50 - Prof. Palmer
 * 4 May 2018
 * Lab 5 Indexer
 *
 * indextest.c - A program to test load the file created by the
 * index program. Will simply load it in and then save it again
 * to a different filename.
 * usage: ./indextest oldFilename newFilename
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"
#include "hashtable.h"
#include "counters.h"

int main(const int argc, char *argv[])
{
	// Check to make sure the proper number of elements
	if (argc == 3) {
		hashtable_t *ht = hashtable_new(2);
		if (ht == NULL) {
			fprintf(stderr, "out of memory\n");
			exit(3);
		}
		//Attempt to load the index from the file
		if (!indexLoad(argv[1], ht)) {
			fprintf(stderr, "index directory %s not found\n", argv[1]);
			exit(2);
		}
		//Save the index to the new file
		indexSave(argv[2], ht);

		//Cleanup
		hashtable_delete(ht, (void(*)(void*))counters_delete);
	}
	else {
		fprintf(stderr, "usage: ./indextest oldFilename newFilename\n");
		exit(1);
	}
}
