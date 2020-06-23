/*
 * Stephen Crowe
 * CS50 - Prof. Palmer
 * 4 May 2018
 * Lab 5 Indexer
 *
 * index.h - the header file for the index.c module
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include "hashtable.h"
#include "webpage.h"

/* Reads a directory of crawler files and then builds an
 * inverted-index in the hashtable provided.
 * @pageDir - the page directory that has all the crawler
 * files
 * @ht - the hashtable to build and store the index in */
void indexBuild(char *pageDir, hashtable_t *ht);

/* Saves the index stored within the hashtable to the
 * filename specified. Saves the index in the format:
 * 		word docID count [docID count]
 * @filename - the filename to save the index in
 * @ht - the hashtable with the index information */
void indexSave(char *filename, hashtable_t *ht);

/* Loads in the hashtable from the file created by indexer
 * File format needs to be of the format:
 * 		word docID count [docID count]
 * @filname - the name of the file to load created by indexer
 * @ht - the hashtable to store the index information
 * @return - true if it loaded correctly */
bool indexLoad(char *filename, hashtable_t *ht);
