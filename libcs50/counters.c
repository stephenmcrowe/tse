/*
 * Stephen Crowe
 * CS50 - Prof. Palmer
 * 13 April 2018
 * Lab3
 *
 * counters.c - a linked list which holds an integer key
 * and a corresponding count. key and count are non-zero
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include "counters.h"
#include "memory.h"

/* global types */
typedef struct counters {
	struct countersnode *head;
} counters_t;

/* file-local global variables */
//none

/* local types */
typedef struct countersnode {
	int key;
	int count;
	struct countersnode *next;
} countersnode_t;

/* local functions */
static countersnode_t *countersnode_new(const int key);

/* Create a new (empty) counter structure; return NULL if error. */
counters_t *counters_new(void) {
	counters_t *counters = count_malloc(sizeof(counters_t));

	if (counters == NULL) {
		return NULL;
	}
	else {
		counters->head = NULL;
		return counters;
	}
}

/* Increment the counter indicated by key; key must be >= 0.
 *  * If the key does not yet exist, create a counter for it and initialize to 1.
 *   * Ignore if ctrs is NULL or key is negative.
 *    */
void counters_add(counters_t *ctrs, const int key) {
	if (ctrs != NULL && key >= 0) {
		countersnode_t *curr = ctrs->head;
		while (curr != NULL) {
			if (curr->key == key) {
				curr->count = curr->count + 1;
				return;
			}
			curr = curr->next;
		}

		countersnode_t *new = countersnode_new(key);
		if (new != NULL) {
			new->next = ctrs->head;
			ctrs->head = new;
		}
	}
	// Memtest only activates if counters_add calls a new malloc
	#ifdef MEMTEST
		count_report(stdout, "End of counters_add");
	#endif
}

/* countersnode_new */
/* Allocate and initialize a bagnode with the key count set to 1 */
static countersnode_t *countersnode_new(const int key) {
	if (key >= 0) {
		countersnode_t *node = count_malloc(sizeof(countersnode_t));

		if (node == NULL) {
			return NULL;
		}
		else {
			node->key = key;
			node->count = 1;
			node->next = NULL;
			return node;
		}
	}
	return NULL;
}

/* Return current value of counter associated with the given key;
 *  * return 0 if ctrs is NULL or if key is not found.
 *   */
int counters_get(counters_t *ctrs, const int key) {
	if (ctrs != NULL) {
		countersnode_t *curr = ctrs->head;
		while (curr != NULL) {
			if (key  == curr->key) {
				return curr->count;
			}
			curr = curr->next;
		}
	}
	return 0;
}

/* Set the current value of counter associated with the given key;
 *  * If the key does not yet exist, create a counter for it and initialize to
 *   * the given value. Ignore if ctrs is NULL, if key < 0, or count < 0.
 *    */
void counters_set(counters_t *ctrs, const int key, int count) {
	if (ctrs != NULL && key >= 0 && count >= 0) {
		countersnode_t *curr = ctrs->head;
		while (curr != NULL) {
			if (key == curr->key) {
				curr->count = count;
				return;
			}
			curr = curr->next;
		}
		countersnode_t *new = countersnode_new(key);
		if (new != NULL) {
			new->key = key;
			new->count = count;
			new->next = ctrs->head;
			ctrs->head = new;
		}
	}
	// Memtest only activates if counters_add calls a new malloc
	#ifdef MEMTEST
		count_report(stdout, "End of counters_set");
	#endif
}

/* Print all counters; provide the output file.
 *  * Ignore if NULL fp. Print (null) if NULL ctrs.
 *   */
void counters_print(counters_t *ctrs, FILE *fp) {
	if (fp != NULL) {
		if (ctrs != NULL) {
			countersnode_t *curr = ctrs->head;
			while (curr != NULL) {
				fprintf(fp, " %i %i", curr->key, curr->count);
				curr = curr->next;
			}
		}
		else {
			fputs("(null)", fp);
		}
	}
}

/* Iterate over all counters in the set (in undefined order):
 *  * call itemfunc for each item, with (arg, key, count).
 *   * If ctrs==NULL or itemfunc==NULL, do nothing.
 *    */
void counters_iterate(counters_t *ctrs, void *arg,
		                      void (*itemfunc)(void *arg, const int key, int count)) {
	if (ctrs != NULL && itemfunc != NULL) {
		countersnode_t *curr = ctrs->head;
		while (curr != NULL) {
			(*itemfunc)(arg, curr->key, curr->count);
			curr = curr->next;
		}
	}
}

/* Delete the whole counters. ignore NULL ctrs. */
void counters_delete(counters_t *ctrs) {
	if (ctrs != NULL) {
		countersnode_t *curr = ctrs->head;
		while (curr != NULL) {
			countersnode_t *next = curr->next;
			count_free(curr);
			curr = next;
		}
		count_free(ctrs);
	}
	#ifdef MEMTEST
		count_report(stdout, "End of counters_delete");
	#endif
}

