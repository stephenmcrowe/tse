/*
 * Stephen Crowe
 * CS50 - Prof. Palmer
 * 4 May 2018
 * Lab5 Indexer
 *
 * index.c - 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "pagedir.h"
#include "webpage.h"
#include "hashtable.h"
#include "counters.h"
#include "file.h"
#include "word.h"

/* Local Functions */
static void printIndex(void *file, const char *word, void *ctrs);
static void insertWord(hashtable_t *ht, char *word, int i);
static void combPage(hashtable_t *ht, webpage_t *page, int id);
static void printCounters(void *file, const int key, int count);
static webpage_t *extractWebpage(FILE *fp);

/* Reads a directory of crawler files and then builds an
 * inverted-index in the hashtable provided.
 * @pageDir - the page directory that has all the crawler
 * files
 * @ht - the hashtable to build and store the index in */
void indexBuild(char *pageDir, hashtable_t *ht)
{
	if (pageDir != NULL && ht != NULL) {
		int i = 0;
		int maxDigits = snprintf(NULL, 0, "%d", INT_MAX); //Passing NULL,0 gives len of str

		
		char *pageDirec = appendSlash(pageDir);

		// Construct the path to the filename
		char *crawlerFile = malloc(strlen(pageDirec) + maxDigits + 1);	
		snprintf(crawlerFile, strlen(pageDirec)+maxDigits, "%s%d", pageDirec, i);

		FILE *fp;
		while ((fp = fopen(crawlerFile, "r")) != NULL) {
			// Reconstruct the webpage structure from the file
			webpage_t *page = extractWebpage(fp);
			combPage(ht, page, i);

			//scour webpage to get a word
			//add words to hashtable by looking through html
				//add word to hashtable 

			webpage_delete(page);
			fclose(fp);
			i++;
			snprintf(crawlerFile, strlen(pageDirec)+maxDigits, "%s%d", pageDirec, i);
		}
		free(pageDirec);
		free(crawlerFile);
	}
}

/* Given file from crawler stored in the format:
 * 		url
 * 		depth
 * 		html
 * Reconstruct the webpage struct and return it.
 * The caller is responsible for calling webpage_delete()
 * @fp - the file pointer for the webpage
 * @return - the webpage struct */
static webpage_t *extractWebpage(FILE *fp)
{
	if (fp == NULL) {
		return NULL;
	}
	char *url = readlinep(fp);
	char *depth = readlinep(fp);
	char *html = readfilep(fp);
	webpage_t *result = webpage_new(url, 1, html);
	free(url);
	free(depth);
	if (result == NULL) {
		return NULL;
	}
	return result;
}

/* Look through the page and add any words to the hashtable.
 * @ht - the hashtable to build the index information
 * @page - the webpage to look through and find words
 * @id - the id of the page */
static void combPage(hashtable_t *ht, webpage_t *page, int id)
{
	int pos = 0;
	char *word;
	while ((pos = webpage_getNextWord(page, pos, &word)) > 0) {
		NormalizeWord(word);
		insertWord(ht, word, id);
		free(word);
   	}
}

/* A helper function for inserting words, docIDs, and 
 * their corresponding count into the hashtable.
 * Called within indexBuild.
 * @ht - the hashtable to build the index information
 * @word - the word to hash into the hashtable
 * @i - the id of file with the word */ 
static void insertWord(hashtable_t *ht, char *word, int i)
{
	if (ht != NULL && word != NULL) {
		counters_t *ctrs = hashtable_find(ht, word);
		if (ctrs != NULL) {
			counters_add(ctrs, i);
		}
		else {
			ctrs = counters_new();
			counters_add(ctrs, i);
			hashtable_insert(ht, word, ctrs);
		}
	}
}

/* Saves the index stored within the hashtable to the
 * filename specified. Saves the index in the format:
 * 		word docID count [docID count]
 * @filename - the filename to save the index in
 * @ht - the hashtable with the index information */
void indexSave(char *filename, hashtable_t *ht)
{
	FILE *fp;
	if ((fp = fopen(filename, "w")) == NULL) {
		return;
	}
	hashtable_iterate(ht, (void *)fp, printIndex);
	fclose(fp);
}

/* A helper function for printing the index containing the
 * hashtable to a file. Called within indexSave. 
 * Prints in the format:
 * 		word docID count [docID count]
 * @file - the file pointer to print to
 * @word - the word to print
 * @ctrs - the counters object that contains the docId and
 * count */
static void printIndex(void *file, const char *word, void *ctrs)
{
	FILE *fp = (FILE*)file;
	fprintf(fp, "%s", word);
	counters_iterate((counters_t*)ctrs, (void *)fp, printCounters);
	fprintf(fp, "\n");
}

// To pass to counters iterate
static void printCounters(void *file, const int key, int count)
{
	FILE *fp = (FILE*)file;
	fprintf(fp, " %d %d", key, count);
}


/* Loads in the hashtable from the file created by indexer
 * File format needs to be of the format:
 * 		word docID count [docID count]
 * @filname - the name of the file to load created by indexer
 * @ht - the hashtable to store the index information */
bool indexLoad(char *filename, hashtable_t *ht)
{
	if (filename != NULL && ht != NULL) {
		FILE *fp = fopen(filename, "r");
		if (fp == NULL) {
			return false;
		}
		
		char *line = NULL;
		while ((line = readlinep(fp)) != NULL) { 
			//Create a new counters structure for each word
			counters_t *ctrs = counters_new();

			char *word = NULL;
			char *id; char *count;
			//Split the lines with the " " (space) delimiter
			word = strtok(line, " ");
			while ((id = strtok(NULL, " ")) &&
				   	(count = strtok(NULL, " "))) {
				// Convert the strings to ints
				int idNum = strtol(id, (char**)NULL, 10);
				int countNum = strtol(count, (char**)NULL, 10);
				counters_set(ctrs, idNum, countNum);
			}

			hashtable_insert(ht, word, ctrs);
			free(line);
		}
		fclose(fp);
		return true;
	}
	return false;
}
