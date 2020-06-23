/*
 * Stephen Crowe
 * CS50 - Prof. Palmer
 * 11 May 2018
 * Lab 6
 *
 * query.c - a module for TSE to work with the input
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "file.h"
#include "counters.h"
#include "hashtable.h"
#include "linkedList.h"

/******************* Local function prototypes ****************/

static void countersMergeHelper(void *arg, const int key, int count);
static void countersIntersectHelper(void *arg, const int key, int count);
static void countersCopy(void *arg, const int key, int count);
static void countersSort(void *arg, const int key, int count);


/******************* Local types and functions ****************/


/* Local type wrapper
 * Used to wrap up three counters structures
 * for countersIntersect() */
typedef struct wrapper {
	counters_t *a;
	counters_t *b;
	counters_t *final;
} wrapper_t;

/* A constructor for the wrapper type
 * Wraps up three counters structures to be passed to
 * counters_iterate.
 * Caller is responsable for freeing the wrapper returned */
static wrapper_t *wrapper_new(counters_t *ctrsA, counters_t *ctrsB, counters_t *ctrsFinal) 
{
	wrapper_t *result = malloc(sizeof(wrapper_t));
	result->a = ctrsA;
	result->b = ctrsB;
	result->final = ctrsFinal;
	return result;
}

/* Local type doccount
 * Used to wrap up docId and count into a
 * single struct */
typedef struct doccount {
	int docId;
	int count;
} doccount_t;

/* A constructor for the doccount type
 * Allocate and return the new doccount struct. */
doccount_t *doccount_new(int id, int num)
{
	doccount_t *result = malloc(sizeof(doccount_t));
	result->docId = id;
	result->count = num;
	return result;
}

/* A print function for testing.
 * Commented to prevent warnings. */
/* 
static void doccount_print(void *arg, void *doccount)
{
	doccount_t *dc = doccount;
	printf("Doc:%d count:%d, ", dc->docId, dc->count);
}*/

/* Getter. Return the docId of the doccount */
static int doccount_getDocId(doccount_t *dc)
{
	return dc->docId;
}

/* Getter. Return the count of the doccount */
static int doccount_getCount(doccount_t *dc)
{
	return dc->count;
}

/* The helper function for countersMerge. Used in conjunction
 * with counters_iterate.
 * Consider inserting the key into one counters structure. If
 * the key already exists, add it to the existing count. Otherwise
 * add a new key into the counters structure.
 * @arg - the counters structure to modify
 * @key - the current key
 * @count - the current count corresponding to that key */
static void countersMergeHelper(void *arg, const int key, int count)
{
	counters_t *ctrsA = arg;
	int countA = counters_get(ctrsA, key);
	counters_set(ctrsA, key, count + countA);
}

/* The helper function for countersIntersect. Used in conjunction
 * with counters_iterate.
 * Consider a key and its count. If it exists in both counters
 * structures, keep the minimum count. Otherwise, remove the key.
 * @arg - the wrapper structure to hold the two counters structures
 * and the one to build.
 * @key - the current key
 * @count - current count corresponding to that key */
static void countersIntersectHelper(void *arg, const int key, int count)
{
	wrapper_t *wp = arg;
	counters_t *ctrsA = wp->a;
	counters_t *ctrsB = wp->b;
	counters_t *final = wp->final;
	int countA = counters_get(ctrsA, key);
	int countB = counters_get(ctrsB, key);
	// Don't set any keys to 0
	if (countA == 0 || countB == 0) {
		;
	}
	else if (countA > countB) {
		counters_set(final, key, countB);
	}
	else {
		counters_set(final, key, countA);
	}
}

/* A function to copy a counters structure.
 * Used in conjunction with counters_iterate. */
static void countersCopy(void *arg, const int key, int count)
{
	counters_t *copy = arg;
	counters_set(copy, key, count);
}

/* A function that implements insertion sort for a
 * counters struct. Used in conjunction with counters_iterate.
 * The list is sorted in decreasing order.
 * @arg - the linkedList struct to be built
 * @key - the current key
 * @count - the count corresponding to the key */
static void countersSort(void *arg, const int key, int count)
{
	linkedList_t *list = (linkedList_t *)arg;
	int i = 0;
	doccount_t *dc = list_get(list, i);
	while (i < list_size(list) && dc->count > count) {
		dc = list_get(list, i);
		i++;
	}
	doccount_t *newDC = doccount_new(key, count);
	list_insert_at(list, newDC, i);
}

/*******************  Global Functions ********************/


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
char normalizeQuery(char *query, char **words)
{
	if (query == NULL || strlen(query) == 0) {
		return '\0';
	}
	int idx = 0;
	bool last = false;		//Was the char before the currect char a letter?
	int end = strlen(query); //Putting null terminators changes strlen()
	for (int i = 0; i<end; i++) {
		query[i] = tolower(query[i]);
		//If it is a letter and the last character was not,
		//then it is the start of a word
		if (isalpha(query[i])) {
			if (!last) {
				char *startWord;
				startWord = &query[i];
				words[idx] = startWord;
				idx++;
			}
			last = true;
		}
		//If it is a space and the last character was a
		//letter, then it is the end of a word.
		else if (isspace(query[i])) {
			if (last) {
				query[i] = '\0';
				last = false;
			}
		}
		else {
			//Must be able to loop through. NULL = end
			words[idx] = NULL;
			return query[i]; //Return bad character
		}
	}
	//Must be able to loop through. NULL = end
	words[idx] = NULL;
	return 't';
}

/* Merge the second counters into the first counters.
 * The second counters is unchanged.
 * @ctrsA - the counters structure to be modified
 * @ctrsB - the other counters structure to merge with. */
void countersMerge(counters_t *ctrsA, counters_t *ctrsB)
{
	counters_iterate(ctrsB, ctrsA, countersMergeHelper);
}

/* Intersect the two counters structures and return a new
 * counters with their intersection.
 * Intersection indicates that both structures have the key.
 * Keeps the minimum count of two keys.
 * @ctrsA - a counters structure
 * @ctrsB - a counters structure
 * @return - a new counters structure with the intersection
 *      of ctrsA and ctrsB. Must be freed by the caller. */
counters_t *countersIntersect(counters_t *ctrsA, counters_t *ctrsB)
{
	counters_t *result = counters_new();
	wrapper_t *wp = wrapper_new(ctrsA, ctrsB, result);
	counters_iterate(ctrsB, wp, countersIntersectHelper);
	counters_iterate(ctrsA, wp, countersIntersectHelper);
	free(wp);
	return result;
}

/* Given the query broken into an array of words, return 
 * a counters structure with the finalized documents.
 * Parses through the andSequences and the orSequences.
 * andSequences take precedence over orSequences.
 * @words - an array of pointers to the queried words
 * @ht - the index of words, documents, and the wordcount.
 * @return - a final counters structure for the query. */
counters_t *parseQuery(char **words, hashtable_t *ht)
{
	if (words != NULL && ht != NULL) {
		//Initialize variables
		counters_t *ctrsQuery = counters_new();
		counters_t *ctrsAnd;
		counters_t *ctrsWord;
		const char *and = "and";
		const char *or = "or";
		int i = 0;
		bool andSequence = false;
		
		//Loop through all the words in the query
		while (words[i] != NULL) {
			char *currWord = words[i];
			//Catch "and"
			if (!strcmp(currWord, and)) {
				;
			}
			//Addition
			/*Catch "or", set andSequence to false, and merge the
			  running product (ctrsAnd) with the final counters */
			else if (!strcmp(currWord, or)) {
				andSequence = false;
				countersMerge(ctrsQuery, ctrsAnd);
				counters_delete(ctrsAnd);
			}
			//Multiplication
			/*If it's a word and an andSequence,
			  intersect the running product with the current counters */
			else if (andSequence) {
				ctrsWord = hashtable_find(ht, currWord);
				counters_t *delete = ctrsAnd;
				ctrsAnd = countersIntersect(ctrsAnd, ctrsWord);
				counters_delete(delete);
			}
			//Product = 1
			/*If it's a word but not an andSequence,
			  copy the current counters to ctrsAnd to
			  start the running product */
			else {
				ctrsWord = hashtable_find(ht, currWord);
				ctrsAnd = counters_new();
				counters_iterate(ctrsWord, ctrsAnd, countersCopy);
				andSequence = true;
			}
			i++;
		}

		//Merge the last andSequence
		countersMerge(ctrsQuery, ctrsAnd);
		counters_delete(ctrsAnd);
		return ctrsQuery;
	}
	return NULL;
}

/* Checks the query's syntax
 * 'and' and 'or' cannot be first or last
 * 'and' and 'or' cannot be adjacent
 * @words - an array of pointers to the queried words
 * @return - true if it is a valid query */
bool isValidSyntax(char **words)
{
	if (words == NULL) {
		return false;
	}
	int i=0;
	char *keywords[2] = { "and", "or" };
	bool lastWasKeyword = false;
	while (words[i] != NULL) {
		int compare;
		for (int j=0; j<sizeof(keywords)/sizeof(keywords[0]); j++) {
			compare = strcmp(words[i], keywords[j]);
			if (!compare) {
				if (i == 0) {
					fprintf(stderr, "'%s' cannot be first\n", keywords[j]);
					return false;
				}
				else if (words[i+1] == NULL) {
					fprintf(stderr, "'%s' cannot be last\n", keywords[j]);
					return false;
				}
				else if (lastWasKeyword) {
					fprintf(stderr, "keywords 'and' and 'or' cannot be adjacent\n");
					return false;
				}
				else {
					lastWasKeyword = true;
				}
			}
		}
		if (compare && strcmp(words[i], "and")) {	
			lastWasKeyword = false;
		}
		i++;
	}
	return true;
}

/* Print a normalized version of the query.
 * Used in conjunction with normalizeQuery().
 * Normalized means lowercase separated by spaces
 * i.e. "  Dartmouth   Or College" -> "dartmouth or college"
 * @words - an array of pointers to the queried words
 * @fp - the pointer to the file to print to */
void printQuery(char **words, FILE *fp)
{
	fprintf(fp, "Query: ");
	for (int i=0; words[i] != NULL; i++) {
		printf("%s ", words[i]);
	}
	printf("\n");
}

/* Sorts the counters list via an insertion sort.
 * Sorts the list by decreasing order according to
 * the count
 * @ctrs - the counters struct to sort
 * @return - a sorted linked list (ctrs is unmodified)*/
linkedList_t *countersSortByVal(counters_t *ctrs)
{
	linkedList_t *list = linkedList_new();
	counters_iterate(ctrs, list, countersSort);
	return list;
}

/* Print the matches to the query in the format
 *     score: <count> doc: <docname> <url>
 * @list - a sorted list containing doccount structs
 * @pageDir - the directory where the crawler files are stored */
void printMatches(linkedList_t *list, char *pageDir)
{
	//Validate parameters
	if (list != NULL && pageDir != NULL) {
		int size = list_size(list);
		if (size == 0) {
			//Handle an empty list
			printf("No documents match\n");
		}
		else {
			//Loop through the list
			for (int i=0; i<size; i++) {
				//Get the score and id
				doccount_t *dc = list_get(list, i);
				if (dc == NULL) {
					return;
				}
				int score = doccount_getCount(dc);
				int id = doccount_getDocId(dc);

				//Passing NULL,0 gives len of str
				int maxDigits = snprintf(NULL, 0, "%d", INT_MAX);
		
				// Construct the path to the filename
				char *crawlerFile = malloc(strlen(pageDir) + maxDigits + 1);	
				snprintf(crawlerFile, strlen(pageDir)+maxDigits, "%s%d", pageDir, id);
				FILE *fp;
		
				//Open and read the file
				if ((fp = fopen(crawlerFile, "r")) != NULL) {
					char *url = readlinep(fp);
					//Finally print out the match
					printf("score:%3d doc%4d: %s\n", score, id, url);
					free(url);
					fclose(fp);
				}
				free(crawlerFile);
			}
		}
	}
}

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
void querySearch(char *query, hashtable_t *ht, char *pageDir)
{
	char badChar;
	char *words[(strlen(query)+1)/2 + 1];
	if ((badChar = normalizeQuery(query, words)) == 't') {
		printQuery(words, stdout);
		if (isValidSyntax(words)) {
			counters_t *ctrsQuery = parseQuery(words, ht);
			linkedList_t *list = countersSortByVal(ctrsQuery);
			printMatches(list, pageDir);

			//Cleanup structures
			counters_delete(ctrsQuery);
			list_delete(list, free);
		}
	}
	else if (badChar != '\0') {
		fprintf(stderr, "Error: bad character '%c' in query.\n", badChar);
	}
}
