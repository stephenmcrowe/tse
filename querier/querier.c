/*
 * Stephen Crowe
 * CS50 - Prof. Palmer
 * 11 May 2018
 * Lab 6
 *
 * querier.c - 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "hashtable.h"
#include "counters.h"
#include "index.h"
#include "pagedir.h"
#include "file.h"
#include "query.h"


int main(const int argc, char *argv[])
{
	char *pageDir;
	if (argc == 3 && isCrawlerDir((pageDir = appendSlash(argv[1])))) {
		free(pageDir);
		hashtable_t *ht = hashtable_new(200);
		if (ht == NULL) {
			fprintf(stderr, "out of memory\n");
			exit(3);
		}
		//Attempt to load the index from the file
		if (!indexLoad(argv[2], ht)) {
			fprintf(stderr, "index directory %s not found\n", argv[2]);
			exit(2);
		}

		//Begin reading from the user
		char *pageDirec = appendSlash(argv[1]);
		char *query;
		while ((query = readlinep(stdin)) != NULL) {
			//Do entire query
			querySearch(query, ht, pageDirec);
			free(query);
		}
		
		//Cleanup
		hashtable_delete(ht, (void(*)(void*))counters_delete);
		free(pageDirec);
	}
	else {
		free(pageDir);
		fprintf(stderr, "usage: ./querier pageDirectory indexFilename\n");
		exit(1);
	}
}


