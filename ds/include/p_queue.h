/******************************************************************************
* File: filename.h
*
* Purpose:
*   Provides an interface for priority queue implementation.
*
* Author:
*   Matan Chen
*
* Review History:
*   - 
*
******************************************************************************/

#ifndef __P_QUEUE_H__
#define __P_QUEUE_H__

#include <stddef.h> /* size_t */

typedef struct p_queue p_queue_t;

/*******************************************************************************/
/* Purpose: User-defined comparator function to define priority order of elements.
 * Receives: Two elements to compare.
 * Output:
 * 		- A negative value if the first element has higher priority.  
 *		- Zero if both elements have equal priority.
 *		- A positive value if the first element has lower priority.
 */
typedef int(*compare_func_t)(const void* data1, const void* data2);
/*******************************************************************************/

/*******************************************************************************/
/* Purpose: User-defined match function to determine if an element matches a given condition.
 * Receives:
 *      - data: The element to be checked.
 *      - param: The parameter used to compare against the element.
 * Output: 1 if the element matches the condition, 0 otherwise.
 */
typedef int (*is_match_func_t)(const void* data, const void* param);
/*******************************************************************************/

/*******************************************************************************/
/* Function: PQCreate
 * Purpose: Creates and initializes a new priority queue.
 * Receives: User defined compare function to define priority order of elements.
 * Returns: A pointer to the priority queue.
 * Complexity: O(1).
 */
p_queue_t* PQCreate(compare_func_t cmp_func);
/*******************************************************************************/

/*******************************************************************************/
/* Function: PQDestroy
 * Purpose: Destroys the priority queue and frees all associated memory.
 * Receives: A pointer to the priority queue to be destroyed.
 * Returns: None.
 * Complexity: O(n), where n is the number of elements in the queue.
 */
void PQDestroy(p_queue_t* p_queue);
/*******************************************************************************/

/*******************************************************************************/
/* Function: PQEnqueue
 * Purpose: Adds an element to the priority queue, maintaining the priority order.
 * Receives:
 *      - p_queue: A pointer to the priority queue.
 *      - data: The element to be added to the queue.
 * Returns:
 *      - 0 on success, non-zero value on failure.
 * Complexity: O(n), where n is the number of elements in the queue.
 */
int PQEnqueue(p_queue_t* p_queue, void* data);
/*******************************************************************************/

/*******************************************************************************/
/* Function: PQDequeue
 * Purpose: Removes the highest-priority element from the queue.
 * Receives: A pointer to the priority queue.
 * Returns: None.
 * Undefined behavior: When used on an empty queue.
 * Complexity: O(n), where n is the number of elements in the queue.
 */
void PQDequeue(p_queue_t* p_queue);
/*******************************************************************************/

/*******************************************************************************/
/* Function: PQPeek
 * Purpose: Retrieves the highest-priority element without removing it from the queue.
 * Receives: A pointer to the priority queue.
 * Returns: A pointer to the highest-priority element.
 * Undefined behavior: When used on an empty queue.
 * Complexity: O(1).
 */
void* PQPeek(const p_queue_t* p_queue);
/*******************************************************************************/

/*******************************************************************************/
/* Function: PQIsEmpty
 * Purpose: Checks whether the priority queue is empty.
 * Receives: A pointer to the priority queue.
 * Returns:
 *      - 1 if the queue is empty.
 *      - 0 if the queue is not empty.
 * Complexity: O(1).
 */
int PQIsEmpty(const p_queue_t* p_queue);
/*******************************************************************************/

/*******************************************************************************/
/* Function: PQCount
 * Purpose: Returns the number of elements in the priority queue.
 * Receives: A pointer to the priority queue.
 * Returns: The number of elements in the queue.
 * Complexity: O(n), where n is the number of elements in the queue.
 */
size_t PQCount(const p_queue_t* p_queue);
/*******************************************************************************/

/*******************************************************************************/
/* Function: PQClear
 * Purpose: Clears all elements from the priority queue without destroying the queue.
 * Receives: A pointer to the priority queue.
 * Returns: None.
 * Complexity: O(n), where n is the number of elements in the queue.
 */
void PQClear(p_queue_t* p_queue);
/*******************************************************************************/

/*******************************************************************************/
/* Function: PQRemove
 * Purpose: Removes an element from the queue based on the user's matching criteria.
 * Receives:
 *      - p_queue: A pointer to the priority queue.
 *      - is_match: A user-defined match function to match elements for removal.
 *      - param: The parameter used for matching.
 * Returns: None.
 * Complexity: O(n), where n is the number of elements in the queue.
 */
void PQRemove(p_queue_t* p_queue, is_match_func_t is_match, const void* param);
/*******************************************************************************/
#endif
