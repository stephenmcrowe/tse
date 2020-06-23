/*
 * Stephen Crowe
 * CS50 - Prof. Palmer
 * 13 April 2018
 * Lab3
 *
 * hashtable.c - a hashtable implementation which stores keys and corresponding
 * items. Utilizes the set structure. Keys are strings and items are void pointers
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include "jhash.h"
#include "hashtable.h"
#include "memory.h"
#include "set.h"

/****************************** global types ***********************************/
typedef struct hashtable {
	struct set **table;
	int size;
} hashtable_t;

/********************** file-local global variables ****************************/
// none

/******************************* local types ***********************************/
// none

/**************************** local functions **********************************/
// none

/*************************** global functions **********************************/
/* Create a new (empty) hashtable; return NULL if error. */
hashtable_t *hashtable_new(const int num_slots) {
	if (num_slots > 0) {
		// Actual hashtable
		hashtable_t *ht = count_malloc(sizeof(hashtable_t));
		if (ht == NULL) {
			return NULL;
		}

		// Sets within hashtable
		ht->table = count_calloc(num_slots, sizeof(struct set*));
		if (ht->table == NULL) {
			return NULL;
		}
		else {
			ht->size = num_slots;
			for (int i=0; i<num_slots; i++) {
				set_t *new = set_new();
				// Error in making inner set
				if (new == NULL) { return NULL; } 
				ht->table[i] = new;
			}
		}
		#ifdef MEMTEST
			count_report(stdout, "End of hashtable_new");
		#endif
		return ht;
	}
	return NULL;
}

/* Insert item, identified by key (string), into the given hashtable.
 * The key string is copied for use by the hashtable.
 * Return false if key exists in ht, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
bool hashtable_insert(hashtable_t *ht, const char *key, void *item) {
	if (ht != NULL && key != NULL && item != NULL) {
		unsigned long hashkey = JenkinsHash(key, ht->size);
		return set_insert(ht->table[hashkey], key, item);
	}
	return false;
}

/* Return the item associated with the given key;
 * return NULL if hashtable is NULL, key is NULL, key is not found.
 */
void *hashtable_find(hashtable_t *ht, const char *key) {
	if (ht != NULL && key != NULL) {
		unsigned long hashkey = JenkinsHash(key, ht->size);
		return set_find(ht->table[hashkey], key);
	}
	return NULL;
}

/* Print the whole table; provide the output file and func to print each item.
 * Ignore if NULL fp. Print (null) if NULL ht.
 * Print a table with no items if NULL itemprint.
 */
void hashtable_print(hashtable_t *ht, FILE *fp,
                     void (*itemprint)(FILE *fp, const char *key, void *item)) {
	if (fp != NULL) {
		if (ht != NULL) {
			fputc('[', fp);
			for (int i=0; i < ht->size; i++) {
				set_t *set = ht->table[i];
				if (set != NULL) {
					set_print(set, fp, itemprint);
				}
				fputc(',', fp);
				fputc(' ', fp);
			}
			fputc(']', fp);
		}
		else {
			fputs("(null)", fp);
		}
	}
}

/* Iterate over all items in the table; in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If ht==NULL or itemfunc==NULL, do nothing.
 */
void hashtable_iterate(hashtable_t *ht, void *arg,
               void (*itemfunc)(void *arg, const char *key, void *item) ) {
	if (ht != NULL && itemfunc != NULL) {
		for (int i=0; i < ht->size; i++) {
			set_t *set = ht->table[i];
			set_iterate(set, arg, itemfunc);
		}
	}
}

/* Delete the whole hashtable; ignore NULL ht.
 * Provide a function that will delete each item (may be NULL).
 */
void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item) ) {
	if (ht != NULL) {
		for (int i=0; i < ht->size; i++) {
			set_t *set = ht->table[i];
			set_delete(set, itemdelete);
		}
		count_free(ht->table);
		count_free(ht);
	}

	#ifdef MEMTEST
		count_report(stdout, "End of hashtable_delete");
	#endif
}
