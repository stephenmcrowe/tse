/*
 * Stephen Crowe
 * CS50 - Prof. Palmer
 * 11 May 2018
 * Lab6 querier
 *
 * linkedList.h - header file for the linkedList module.
 *
 * A linkedList is a collection of items.
 * Supports a size attribute and inserting in a specific 
 * position.
 *
 */

#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

#include <stdio.h>

/* Global types */
typedef struct linkedList linkedList_t;

/* Allocate a linkedList and instantiate its vars.
 * return NULL if error, otherwise return the linkedList */
linkedList_t *linkedList_new(void);

/* Get method for accessing the size */
int list_size(linkedList_t *list);

/* Insert the item at the head of the list
 * A NULL list is ignored.
 * A NULL item is ignored. */
void list_insert_head(linkedList_t *list, void *item);

/* Insert the item at the position specified in the list.
 * Does nothing if list is null, item is null, or pos is
 * out of the range of the list.
 * @list - the list to insert an item into
 * @item - the item to insert
 * @pos - the position to put the item. 
 * 		  0 <= pos <= listsize+1 */
void list_insert_at(linkedList_t *list, void *item, int pos);

/* Find and return the item at the position specified.
 * Return NULL if list is NULL or pos is out of range
 * @list - the list with the items
 * @pos - the position of the item to get
 * 		  0 <= pos <= listsize */
void *list_get(linkedList_t *list, int pos);

/* Iterate through the list and call the itemfunc on 
 * each item. */
void list_iterate(linkedList_t *list, void *arg,void (*itemfunc)(void *arg, void *item) );

/* Delete the list
 * @list - the list to delete
 * @itemdelete - the function to delete the items 
 * 				 in the list */
void list_delete(linkedList_t *list, void (*itemdelete)(void *item));

#endif
