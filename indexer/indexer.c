/*
 * Stephen Crowe
 * CS50 - Prof. Palmer
 * 5 May 2018
 * Lab 5 indexer
 *
 * indexer.c - a program to be used in conjunction with crawler
 * usage: ./indexer pageDirectory indexFilename
 * Creates an index from the crawler output pageDirectory in
 * indexFilename in the format (for each line):
 * 		word docID count [docID count]
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hashtable.h"
#include "pagedir.h"
#include "webpage.h"
#include "index.h"
#include "counters.h"

int main(const int argc, char *argv[])
{
	// Validate arguments
	char *pageDir;
	if (argc == 3 && isCrawlerDir((pageDir= appendSlash(argv[1])))) {
		free(pageDir);
		//Make sure the file can be created
		FILE *fp = fopen(argv[2], "w");
		if (fp == NULL) {
			fprintf(stderr, "Please provide a valid pathname for the indexFilename.\n");
			fprintf(stderr, "usage: ./indexer pageDirectory indexFilename\n");
			exit(2);
		}
		fclose(fp);

		// Instantiate hashtable
		hashtable_t *ht = hashtable_new(500);
		if (ht == NULL) {
			fprintf(stderr, "out of memory\n");
			exit(3);
		}

		// Build the index in the hashtable structure
		indexBuild(argv[1], ht);
		// Save the index to a file
		indexSave(argv[2], ht);
		printf("The index %s has been created.\n", argv[2]);

		//Cleanup
		hashtable_delete(ht, (void(*)(void*))counters_delete);
	}
	else {
		free(pageDir);
		// Error out with proper usage
		fprintf(stderr, "usage: ./indexer pageDirectory indexFilename\n");
		exit(1);
	}
}
