/*
 * Stephen Crowe
 * CS50 - Prof. Palmer
 * 11 May 2018
 * Lab6 querier
 *
 * linkedList.c - a linkedlist implementation supporting size
 * and inserting in a specific position.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* local types */
typedef struct listnode {
	void *item;
	struct listnode *next;
} listnode_t;

/* global types */
typedef struct linkedList {
	struct listnode *head;
	int size;
} linkedList_t;

/* Allocate a listnode and instantiate its vars.
 * return NULL if error, otherwise return the listnode. */
static listnode_t *listnode_new(void *item)
{
	listnode_t *node = malloc(sizeof(listnode_t));

	if (node == NULL) {
		return NULL; //error allocating
	}
	else {
		node->item = item;
		node->next = NULL;
		return node;
	}
}

/* Allocate a linkedList and instantiate its vars.
 * return NULL if error, otherwise return the linkedList */
linkedList_t *linkedList_new(void)
{
	linkedList_t *list = malloc(sizeof(linkedList_t));

	if (list == NULL) {
		return NULL; //error allocating list
	}
	else {
		list->head = NULL;
		list->size = 0;
		return list;
	}
}

/* Get method for accessing the size */
int list_size(linkedList_t *list)
{
	if (list != NULL)
		return list->size;
	return -1;
}

/* Insert the item at the head of the list */
void list_insert_head(linkedList_t *list, void *item)
{
	if (list != NULL && item != NULL) {
		listnode_t *new = listnode_new(item);
		if (new != NULL) {
			new->next = list->head;
			list->head = new;
			list->size = list->size + 1;
		}
	}
}

/* Insert the item at the position specified in the list.
 * Does nothing if list is null, item is null, or pos is
 * out of the range of the list.
 * @list - the list to insert an item into
 * @item - the item to insert
 * @pos - the position to put the item. 
 * 		  0 <= pos <= listsize+1 */
void list_insert_at(linkedList_t *list, void *item, int pos)
{
	if (list != NULL && item != NULL && 
		pos >= 0 && pos <= list->size + 1) {
		if (pos == 0) {
			list_insert_head(list, item);
		}
		else {
			listnode_t *new = listnode_new(item);
			if (new != NULL) {
				listnode_t *curr = list->head;
				int i = 1;
				while (i < pos) {
					curr = curr->next;
					i++;
				}
				new->next = curr->next;
				curr->next = new;
				list->size = list->size + 1;
			}
		}
	}
}

/* Find and return the item at the position specified.
 * Return NULL if list is NULL or pos is out of range
 * @list - the list with the items
 * @pos - the position of the item to get
 * 		  0 <= pos <= listsize */
void *list_get(linkedList_t *list, int pos)
{
	if (list != NULL && pos >= 0 && pos <= list->size) {
		listnode_t *curr = list->head;
		int i = 0;
		while (i < pos) {
			curr = curr->next;
			i++;
		}
		if (curr != NULL)
			return curr->item;
	}
	return NULL;
}

/* Iterate through the list and call the itemfunc on 
 * each item. */
void list_iterate(linkedList_t *list, void *arg,
		                 void (*itemfunc)(void *arg, void *item) ) {
	if (list != NULL && itemfunc != NULL) {
		for (listnode_t *curr = list->head; curr != NULL; curr = curr->next) {
			(*itemfunc)(arg, curr->item);
		}
	}
}

/* Delete the list
 * @list - the list to delete
 * @itemdelete - the function to delete the items 
 * 				 in the list */
void list_delete(linkedList_t *list, void (*itemdelete)(void *item))
{
	if (list != NULL) {
		listnode_t *curr = list->head;
		int i=0;
		while (curr != NULL) {
			if (itemdelete != NULL) {
				(*itemdelete)(curr->item);
			}
			listnode_t *next = curr->next;
			free(curr);
			curr = next;
			i++;
		}
		free(list);
	}
}
