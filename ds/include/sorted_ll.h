/******************************************************************************
* File: sorted_ll.h
*
* Purpose:
*   Provides an interface for sorted linked list implementation.
*
* Author:
*   Matan Chen
*
* Review History:
*   - Ofir
*
******************************************************************************/

#ifndef __SORTED_LL_H__
#define __SORTED_LL_H__

#include <stddef.h> /* size_t */
#include "doubly_ll.h" /* dlist_itr_t */

typedef struct srt_ll srt_ll_t; /* list type */
typedef struct srt_itr srt_itr_t; /* iterator type */

struct srt_itr
{
	dlist_itr_t itr;

	#ifndef NDEBUG
	srt_ll_t* list;
	#endif
};

/*******************************USER FUNCTION TYPEDEF************************/

/* is the left value before the right value (sorted) */
typedef int(*is_before_t)(const void*, const void*);

/* 
Input: gets 2 elements to compare
Output: return TRUE or FALSE
Purpose: user must set his own comparator func for data
Complexity: o(1)
*/

/*******************************************************************************/

/*******************************************************************************/
/* Function: SrtLLCreate.
 * Purpose: Creates and initializes a new sorted (doubly) linked list.
 * Receives: 
 * Returns: A pointer to the list.
 */
srt_ll_t* SrtLLCreate(is_before_t is_before); 
/*******************************************************************************/

/*******************************************************************************/
/* Function: SrtLLDestroy.
 * Purpose: Frees all the nodes and the list itself.
 * Receives: A pointer to thelist
 * Returns: 
 * Complexity: O(1).
 */
void SrtLLDestroy(srt_ll_t* list); 
/*******************************************************************************/

/*******************************************************************************/
/* Function: SrtLLItrBegin.
 * Purpose: Creates an iterator that points to the first element of the list.
 * Receives: A pointer to a list.
 * Returns: An iterator that points to the first element.
 * Complexity: O(n).
 */
srt_itr_t SrtLLItrBegin(const srt_ll_t* list);
/*******************************************************************************/

/*******************************************************************************/
/* Function: SrtLLItrEnd
 * Purpose: Creates an iterator that points to the dummy tail node.
 * Receives: A pointer to a list.
 * Returns: An iterator that points to the tail dummy node.
 * Complexity: O(1).
 */
srt_itr_t SrtLLItrEnd(const srt_ll_t* list);
/*******************************************************************************/

/*******************************************************************************/
/* Function: SrtLLItrNext.
 * Purpose: Increments an iterator (the iterator points to the next element).
 * Receives: an iterator.
 * Returns: The received iterator incremented by 1.
 * Complexity: O(1).
 */
srt_itr_t SrtLLItrNext(srt_itr_t itr);
/*******************************************************************************/

/*******************************************************************************/
/* Function: SrtLLItrPrev
 * Purpose: Decrements an iterator (the iterator points to the previous element).
 * Receives: an iterator.
 * Returns: The received iterator decremented by 1.
 * Undefined behavior: When used on the tail dummy node (on SrtLLItrEnd)
 * Complexity: O(1).
 */
srt_itr_t SrtLLItrPrev(srt_itr_t itr);
/*******************************************************************************/

/*******************************************************************************/
/* Function: SrtLLIsEmpty
 * Purpose: Check if the list is empty.
 * Receives: An iterator.
 * Returns: 1 if the list is empty, 0 otherwise.
 * Undefined behavior: When used on the first element.
 * Complexity: O(1).
 */
int SrtLLIsEmpty(const srt_ll_t* list);
/*******************************************************************************/

/*******************************************************************************/
/* Function: SrtLLItrIsEqual.
 * Purpose: Check if two iterators are equal (point to the same address).
 * Receives: Two iterators.
 * Returns: 1 if the iterators are equal, 0 otherwise.
 * Complexity: O(1).
 */
int SrtLLItrIsEqual(srt_itr_t itr1, srt_itr_t itr2);
/*******************************************************************************/

/*******************************************************************************/
/* Function: SrtLLInsert.
 * Purpose: Inserts a new element to the list.
 * Receives: A pointer to a list and the element (data).
 * Returns: On success, an iterator to the newly added element, otherwise, an iterator to the dummy tail (SrtLLItrEnd).
 * Complexity: O(n).
 */
srt_itr_t SrtLLInsert(srt_ll_t* list, void* data);
/*******************************************************************************/

/*******************************************************************************/
/* Function: SrtLLRemove.
 * Purpose: Removes an new element from the list.
 * Receives: An iterator to the element for removal.
 * Returns: An iterator to the following element.
 * Complexity: O(1).
 */
srt_itr_t SrtLLRemove(srt_itr_t itr);
/*******************************************************************************/

/*******************************************************************************/
/* Function: SrtLLPopFront.
 * Purpose: Removes an element from the front of the list (beginning).
 * Receives: A pointer to a list.
 * Returns: The element that was removed.
 * Undefined behavior: When used on an empty list.
 * Complexity: O(1).
 */
void* SrtLLPopFront(srt_ll_t* list);
/*******************************************************************************/

/*******************************************************************************/
/* Function: SrtLLPopBack.
 * Purpose: Removes an element from the back of the list (end).
 * Receives: A pointer to a list.
 * Returns: The element that was removed.
 * Undefined behavior: When used on an empty list.
 * Complexity: O(1).
 */
void* SrtLLPopBack(srt_ll_t* list);
/*******************************************************************************/

/*******************************************************************************/
/* Function: SrtLLCount.
 * Purpose: Counts the number of elements in the list.
 * Receives: A pointer to a list.
 * Returns: The number of elements in the list.
 * Complexity: O(n).
 */
size_t SrtLLCount(const srt_ll_t* list);
/*******************************************************************************/

/*******************************************************************************/
/* Function: SrtLLGetData.
 * Purpose: Gets an element.
 * Receives: An iterator to the element.
 * Returns: The element.
 * Undefined behavior: When used on the tail dummy node (on SrtLLItrEnd).
 * Complexity: O(1).
 */
void* SrtLLGetData(srt_itr_t);
/*******************************************************************************/

/*******************************************************************************/
/* Function: SrtLLFind.
 * Purpose: Finds an element in the list.
 * Receives: A pointer to the list, and the element to find.
 * Returns: An iterator to the element if found in the list, otherwise,
 *			an iterator to the dummy tail node (SrtLLItrEnd).
 * Undefined behavior: When used on the tail dummy node (on SrtLLItrEnd).
 * Complexity: O(n).
 */
srt_itr_t SrtLLFind(srt_ll_t* list, void* data);
/*******************************************************************************/

/*******************************************************************************/
/* Function: SrtLLFindIf.
 * Purpose: Finds an element in the list according to a different match function.
 * Receives: A pointer to the list, the element to find, and the compare function.
 * Returns: An iterator to the element if found in the list, otherwise, 
 *			an iterator to the dummy tail node (SrtLLItrEnd).
 * Undefined behavior: When used on the tail dummy node (on SrtLLItrEnd).
 * Complexity: O(n).
 */
srt_itr_t SrtLLFindIf(srt_itr_t from, srt_itr_t to, match_func_t is_match, void* data);
/*******************************************************************************/

/*******************************************************************************/
/* Function: SrtLLForEach.
 * Purpose: Applies an action on each element between from and to.
 * Receives: An iterator from, iterator to, the action function and the parameter used by the action functon.
 * Returns: status, 0 if successful for all elements, otherwise the status code for th failure.
 * Complexity: O(n).
 */
int SrtLLForEach(srt_itr_t from, srt_itr_t to, action_func_t action, void* param);
/*******************************************************************************/

/*******************************************************************************/
/* Function: SrtLLMerge.
 * Purpose: Merges the list src into th list dst, such that dst remains sorted. leaves src an empty list.
 * Receives: A pointer to the dst list and to the src list.
 * Returns: Pointer to the dst list.
 * Complexity: O(n + m).
 * NOTE: Iterators of src no longer point to their corresponding lists in debug mode,
 *		 they are to be treated as invalid in their functionality for certain operations.
 */
srt_ll_t* SrtLLMerge(srt_ll_t* dst, srt_ll_t* src);
/*******************************************************************************/

#endif
