/******************************************************************************
* File: singly_ll.h
*
* Purpose:
*   Provides an interface for singly linked list implementation.
*
* Author:
*   Matan Chen
*
* Review History:
*   - Albert
*
******************************************************************************/

#ifndef __SINGLY_LL_H__
#define __SINGLY_LL_H__

#include <stddef.h>		/* for size_t */

typedef struct slist slist_t;
typedef struct node node_t;
typedef node_t* slist_itr_t;

typedef int (*match_func_t) (void*, void*);
typedef int (*action_func_t) (void*, void*);

/* Creates a new singly linked list and returns a pointer to it. O(1) */
slist_t* ListCreate();

/* Receives a list ptr, frees all dynamically allocated nodes, and the list itself. O(n) */
void ListDestroy(slist_t* list);

/* Receives a list ptr, returns an iterator to the first element. O(1) */
slist_itr_t ListItrBegin(const slist_t* list);

/* Receives an iterator, returns an iterator to the next element. O(1) */
slist_itr_t ListItrNext(slist_itr_t itr);

/* Receives a list ptr, returns an iterator to the end of the list (past the last element). O(1) */
slist_itr_t ListItrEnd(slist_t* list);

/* Receives two iterators, returns 1 if they are equal, 0 otherwise. O(1) */
int ListItrIsEqual(slist_itr_t itr1, slist_itr_t itr2);

/* Receives an iterator, returns a pointer to the data stored in the node (by reference). O(1)
 * Attempt to get tail data will return NULL */
void* ListGetData(slist_itr_t itr);

/* Receives an iterator and a data ptr, sets the node's data to the provided value (by reference). O(1) 
 * Attempt to set tail data (ListItrEnd data) will not occur. */
void ListSetData(slist_itr_t itr, const void* data);

/* Receives an iterator and a data ptr, inserts a new node before the iterator position
 * Returns an iterator to the newly inserted node. O(1) */
slist_itr_t ListInsertBefore(slist_itr_t itr, const void* data);

/* Receives an iterator, removes the node at the iterator position
 * Returns an iterator to the next node. O(1) 
 * Undefined behaviour if attempt to remove tail */
slist_itr_t ListRemove(slist_itr_t itr);

/* Receives a list ptr, returns the number of elements in the list. O(n) */
size_t ListCount(const slist_t* list);

/* Receives a list ptr, returns 1 if the list is empty, 0 otherwise. O(1) */
int ListIsEmpty(slist_t* list);

/* Search for an element (between 'from' and 'to' itrerators) that matches the condition with data
 * Returns an iterator to the found element, or NULL if not found. O(n) */
slist_itr_t ListFind(slist_itr_t from, slist_itr_t to, match_func_t is_match, const void* data);

/* Applies an action function to each element in the given range
 * Returns 0 if successful, 1 if the action function failed. O(n) */
int ListForEach(slist_itr_t from, slist_itr_t to, action_func_t action_func, const void* param);

/* Receives a destination and a source, appends the src to the destination, leaving the src an empty list. O(1) */
slist_t* ListAppend(slist_t* list_dest, slist_t* list_src);

#endif /* __SINGLY_LL_H__ */
