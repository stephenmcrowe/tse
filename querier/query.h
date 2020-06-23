/*
 * Stephen Crowe
 * CS50 - Prof. Palmer
 * 11 May 2018
 * Lab 6
 *
 * query.h - a module for TSE to work with the input
 */

#ifndef __QUERY_H
#define __QUERY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "counters.h"
#include "hashtable.h"
#include "linkedList.h"


/* Tokenize a query buffer into words.
 * Make all letters lowercase.
 * Return the bad non-letter character or 't' if no
 * errors occurred.
 * @query - the buffer of chars to tokenize
 * @words - a pointer to store pointers to the beginning
 *     of words in the query. Filled by this function.
 * @return - a character to denote the status of the query.
 *     A non-letter character for an error.
 *     A null termination character to pass if the query has 0 length.
 *     A 't' to show that the query is normal. */
char normalizeQuery(char *query, char **words);

/* Merge the second counters into the first counters.
 * The second counters is unchanged.
 * @ctrsA - the counters structure to be modified
 * @ctrsB - the other counters structure to merge with. */
void countersMerge(counters_t *ctrsA, counters_t *ctrsB);

/* Intersect the two counters structures and return a new
 * counters with their intersection.
 * Intersection indicates that both structures have the key.
 * Keeps the minimum count of two keys.
 * @ctrsA - a counters structure
 * @ctrsB - a counters structure
 * @return - a new counters structure with the intersection
 *      of ctrsA and ctrsB. Must be freed by the caller. */
counters_t *countersIntersect(counters_t *ctrsA, counters_t *ctrsB);


/* Given the query broken into an array of words, return 
 * a counters structure with the finalized documents.
 * Parses through the andSequences and the orSequences.
 * andSequences take precedence over orSequences.
 * @words - an array of pointers to the queried words
 * @ht - the index of words, documents, and the wordcount.
 * @return - a final counters structure for the query. */
counters_t *parseQuery(char **words, hashtable_t *ht);

/* Checks the query's syntax
 * 'and' and 'or' cannot be first or last
 * 'and' and 'or' cannot be adjacent
 * @words - an array of pointers to the queried words
 * @return - true if it is a valid query */
bool isValidSyntax(char **words);

/* Print a normalized version of the query.
 * Used in conjunction with normalizeQuery().
 * Normalized means lowercase separated by spaces
 * i.e. "  Dartmouth   Or College" -> "dartmouth or college"
 * @words - an array of pointers to the queried words
 * @fp - the pointer to the file to print to */
void printQuery(char **words, FILE *fp);

/* Sorts the counters list via an insertion sort.
 * Sorts the list by decreasing order according to
 * the count
 * @ctrs - the counters struct to sort
 * @return - a sorted linked list (ctrs is unmodified)*/
linkedList_t *countersSortByVal(counters_t *ctrs);

/* Print the matches to the query in the format
 *     score: <count> doc: <docname> <url>
 * @list - a sorted list containing doccount structs
 * @pageDir - the directory where the crawler files are stored */
void printMatches(linkedList_t *list, char *pageDir);

/* Given a query, index, and crawler directory, rank and print matches.
 * Pseudocode:
 *   normalize query, breaking it up into words
 *	 print a clean query
 *	 validate the 'and' 'or' syntax
 *	 combine counters structs into one to rank by parsing the query
 *	 sort the final structure
 *	 print all the matching documents
 * @query - the query from the user
 * @ht - the datastructure that holds the index
 * @pageDir - the crawler directory */
void querySearch(char *query, hashtable_t *ht, char *pagedir);

#endif
