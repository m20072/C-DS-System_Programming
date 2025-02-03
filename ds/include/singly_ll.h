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
*   - 
*
******************************************************************************/

#ifndef __SINGLY_LL_H__
#define __SINGLY_LL_H__

#include <stddef.h>		/* for size_t */

typedef struct slist_t slist_t;
typedef struct node_t node_t;
typedef node_t* slist_itr_t;

typedef int (*match_func_t) (void*, void*);
typedef int (*action_func_t) (void*, void*);

/* Creates a new singly linked list and returns a pointer to it */
slist_t* ListCreate();

/* Receives a list ptr, frees all dynamically allocated nodes, and the list itself */
void ListDestroy(slist_t* list);

/* Receives a list ptr, returns an iterator to the first element */
slist_itr_t ListItrBegin(const slist_t* list);

/* Receives an iterator, returns an iterator to the next element */
slist_itr_t ListItrNext(slist_itr_t itr);

/* Receives a list ptr, returns an iterator to the end of the list (past the last element) */
slist_itr_t ListItrEnd(slist_t* list);

/* Receives two iterators, returns 1 if they are equal, 0 otherwise */
int ListItrIsEqual(slist_itr_t itr1, slist_itr_t itr2);

/* Receives an iterator, returns a pointer to the data stored in the node (by reference) */
void* ListGetData(slist_itr_t itr);

/* Receives an iterator and a data ptr, sets the node's data to the provided value (by reference) */
void ListSetData(slist_itr_t itr, const void* data);

/* Receives an iterator and a data ptr, inserts a new node before the iterator position
 * Returns an iterator to the newly inserted node */
slist_itr_t ListInsertBefore(slist_itr_t itr, const void* data);

/* Receives an iterator, removes the node at the iterator position
 * Returns an iterator to the next node */
slist_itr_t ListRemove(slist_itr_t itr);

/* Receives a list ptr, returns the number of elements in the list */
size_t ListCount(const slist_t* list);

/* Receives a list ptr, returns 1 if the list is empty, 0 otherwise */
int ListIsEmpty(slist_t* list);

/* Search for an element (between 'from' and 'to' itrerators) that matches the condition with data
 * Returns an iterator to the found element, or NULL if not found */
slist_itr_t ListFind(slist_itr_t from, slist_itr_t to, match_func_t is_match, const void* data);

/* Applies an action function to each element in the given range
 * Returns 0 if successful, 1 if the action function failed */
int ListForEach(slist_itr_t from, slist_itr_t to, action_func_t action_func, const void* param);


#endif /* __SINGLY_LL_H__ */
