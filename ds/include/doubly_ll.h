/******************************************************************************
* File: doubly_ll.h
*
* Purpose:
*   Provides an interface for doubly linked list implementation.
*
* Author:
*   Matan Chen
*
* Review History:
*   - Daniel
*
******************************************************************************/

#ifndef __DOUBLY_LL_H__
#define __DOUBLY_LL_H__
#include <stddef.h> /* size_t */

typedef struct dlist dlist_t;
typedef struct node* dlist_itr_t;

/*******************************USER FUNCTION TYPEDEF************************/

/* 
Input: gets 2 elements to compare
Output: return TRUE or FALSE
Purpose: user must set his own comparator func for data
Complexity: o(1)
*/
typedef int (*match_func_t) (const void* first, const void* second);

/* 
Input: gets itr and param
Output: return TRUE or FALSE
Purpose: user must set his own action func for data
Complexity: o(1)
*/
typedef int (*action_func_t) (void* data, void* param);

/******************************************************************************/

/* Creates a new doubly linked list and returns a pointer to it or NULL if failed. O(1) */
dlist_t* DLLCreate();

/* Receives a list ptr, frees all dynamically allocated nodes, and the list itself. O(n) */
void DLLDestroy(dlist_t* list);

/* Receives a list ptr, returns the number of elements in the list. O(n) */
size_t DLLCount(const dlist_t* list);

/* Receives a list ptr, returns 1 if the list is empty, 0 otherwise. O(1) */
int DLLIsEmpty(const dlist_t* list);

/* Receives a list ptr, returns an iterator to the first element in the list. O(1) */
dlist_itr_t DLLItrBegin(const dlist_t* list);

/* Receives a list ptr, returns an iteratorto the tail of the list. O(1) */
dlist_itr_t DLLItrEnd(const dlist_t* list);


/* Receives an iterator, returns an iteator to the next element. O(1) 
 * Undefined behavior if the received iterator points to the tail.
 */
dlist_itr_t DLLItrNext(dlist_itr_t itr);

/* Receives an iterator, returns an iteator to the next element. O(1) 
 * Undefined behavior if the received iterator points to the head.
 */
dlist_itr_t DLLItrPrev(dlist_itr_t itr);

/* Receives two iterators, returns 1 if they are equal (point to the same element), 0 otherwise. O(1) */
int DLLItrIsEqual(dlist_itr_t itr1, dlist_itr_t itr2);

/* Receives an iterator, returns the data of the associated element. O(1) */
void* DLLGetData(dlist_itr_t itr);

/* Receives an iteator and a ptr to data, sets the ptr to data of the associated element to the new ptr to data. O(1) */
void DLLSetData(dlist_itr_t itr, const void* data);

/* Receives a list, an iterator and data, Inserts a new element with the new data before the iterator element, returns an iteratorto that element. O(1)
 * Returns ItrEnd if fails */
dlist_itr_t DLLInsertBefore(dlist_t* list, dlist_itr_t itr, void* data);

/* Receives an iterator to an element to be removed, returns an iterator to the element after that. O(1).
 * Undefined behavior if used on ItrEnd */
dlist_itr_t DLLRemove(dlist_itr_t itr);

/* Receives a list and data, Adds an element to the beginning of the list with that data, and returns an iterator to it. O(1) */
dlist_itr_t DLLPushFront(dlist_t* list, void* data);

/* Receives a list and data, Adds an element to the end of the list with that data, and returns an iterator to it. O(1) */
dlist_itr_t DLLPushBack(dlist_t* list, void* data);

/*Receives a list, removes the first element of the list and returns its data */
void* DLLPopFront(dlist_t* list);

/* Receives a list, removes the last elementof the list and returns its data */
void* DLLPopBack(dlist_t* list);

/* Applies an action function to each element in the given range ('from' including, 'to' excluding)
 * Returns 0 if successful, 1 if the action function failed. O(n) */
int DLLForEach(dlist_itr_t from, dlist_itr_t to, action_func_t action, void* param);

/* Receives 3 iterators, where, from and to. 
 * Adds the sequence of nodes from 'from' to 'to' (excluding 'to') starting from the previous to the where iterator element.
 * returns an iterator to the original element prior to where iterator element. O(1) */
dlist_itr_t DLLSplice(dlist_itr_t where, dlist_itr_t from, dlist_itr_t to);

/* Receives: iterator 'from', iterator 'to', a 'is_match' function and data.
 * Search for an element (between 'from' and 'to' itrerators) that matches the condition with data provided as argument.
 * Returns an iterator to the found element, or an iterator to the tail if not found. O(n) */
dlist_itr_t DLLFind(dlist_itr_t from, dlist_itr_t to, match_func_t is_match, const void* data);
 
 /* Receives: iterator 'from', iterator 'to', a 'is_match' function, data and an output list.
  * Search for multiple elements (between 'from' and 'to' itrerators) that match the condition with data provided as argument.
  * Adds each found element to the output list.
  * Returns 0 on success, and 1 if failed. O(n) */
int DLLMultiFind(dlist_itr_t from, dlist_itr_t to, match_func_t is_match, const void* data, dlist_t* output);

#endif
