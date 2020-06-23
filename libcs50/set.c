/*
 * Stephen Crowe
 * CS50 - Prof. Palmer
 * 13 April 2018
 * Lab3
 *
 * set.c - a simple linked list where each node holds a 
 * key:value pair. The keys are null-terminated strings
 * and the values are pointers to anything.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include "set.h"
#include "memory.h"

/* global types */
typedef struct set {
	struct setnode *head;
} set_t;

/* File-local global variables */
/* none */

/* local types */
typedef struct setnode {
	const char *key;
	void *item;
	struct setnode *next;
} setnode_t;

/* local functions */
static setnode_t *setnode_new(const char *key, void *item);

/* Create a new (empty) set; return NULL if error. */
set_t *set_new(void) {
	set_t *result = count_malloc(sizeof(set_t));

	if (result == NULL) {
		return NULL; // error allocating memory
	}
	else {
		result->head = NULL;
		return result;
	}
}

/* Insert item, identified by a key (string), into the given set.
 *  * The key string is copied for use by the set.
 *   * Return false if key exists, any parameter is NULL, or error;
 *    * return true iff new item was inserted.
 *     */
bool set_insert(set_t *set, const char *key, void *item) {
	if (set != NULL && key != NULL && item != NULL) {
		setnode_t *curr = set->head;
		while(curr != NULL) {
			if (strcmp(curr->key, key) == 0) {
				return false;
			}
			curr = curr->next;
		}

		// Create a copy of the key
		char *keycopy = count_malloc(strlen(key) + 1);
		strcpy(keycopy, key);
		setnode_t *new = setnode_new(keycopy, item);
		if (new != NULL) {
			//Add the new node to the head
			new->next = set->head;
			set->head = new;
			return true;
		}
	}
	return false;
}

/* Allocate and initialize a setnode */
static setnode_t *setnode_new(const char *key, void *item) {
	if (key != NULL && item != NULL) {
		setnode_t *node = count_malloc(sizeof(setnode_t));

		if (node == NULL) {
			return NULL; //Error allocating memory; return error
		}
		else {
			node->key = key;
			node->item = item;
			return node;
		}
	}
	return NULL;
}

/* Return the item associated with the given key;
 *  * return NULL if set is NULL, key is NULL, or key is not found.
 *   */
void *set_find(set_t *set, const char *key) {
	if (set != NULL && key != NULL) {
		setnode_t *curr = set->head;
		while (curr != NULL) {
			if (strcmp(curr->key, key) == 0) {
				return curr->item;
			}
			curr = curr->next;
		}
	}
	return NULL;
}

/* Print the whole set; provide the output file and func to print each item.
 *  * Ignore if NULL fp. Print (null) if NULL set.
 *   * Print a set with no items if NULL itemprint.
 *   */
void set_print(set_t *set, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item) ) {
	if (fp != NULL) {
		if (set != NULL) {
			fputc('{', fp);
			for (setnode_t *curr = set->head; curr != NULL; curr = curr->next) {
				if (itemprint != NULL) {
					(*itemprint)(fp, curr->key, curr->item);
					fputc(',', fp);
					fputc(' ', fp);
				}
			}
			fputc('}', fp);
		}
		else {
			fputs("(null)", fp);
		}
	}
}

/* Iterate over all items in the set, in undefined order.
 *  * Call the given function on each item, with (arg, key, item).
 *   * If set==NULL or itemfunc==NULL, do nothing.
 *    */
void set_iterate(set_t *set, void *arg,
		                 void (*itemfunc)(void *arg, const char *key, void *item) ) {
	if (set != NULL && itemfunc != NULL) {
		for (setnode_t *curr = set->head; curr != NULL; curr = curr->next) {
			(*itemfunc)(arg, curr->key, curr->item);
		}
	}
}

/* Delete the whole set; ignore NULL set.
 *  * Provide a function that will delete each item (may be NULL).
 *   */
void set_delete(set_t *set, void (*itemdelete)(void *item) ) {
	if (set != NULL) {
		setnode_t *curr = set->head;
		while (curr != NULL) {
			if (itemdelete != NULL) {
				(*itemdelete)(curr->item);
			}
			setnode_t *next = curr->next;	//remember what comes next
			count_free((char *)curr->key);
			count_free(curr);
			curr = next;
		}
		count_free(set);
	}

	#ifdef MEMTEST
		count_report(stdout, "End of set_delete");
	#endif
}
