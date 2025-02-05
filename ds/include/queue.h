/******************************************************************************
* File: queue.h
*
* Purpose:
*   Provides an interface for queue implementation.
*
* Author:
*   Matan Chen
*
* Review History:
*   - Yonatan
*
******************************************************************************/

#ifndef __QUEUE_H__
#define __QUEUE_H__
#include <stddef.h> /* size_t */

typedef struct Queue queue_t;

/* Creates a queue, returns a pointer to that queue */
queue_t* QueueCreate(); 

/* Frees dynamically allocated memory of the queue and its components */
void QueueDestroy(queue_t* queue);

/* Adds an element to the rear of the queue, returns 0 on success, 1 otherwise. O(1) */
int QueueEnqueue(queue_t* queue, void* data);

/* Removes an elemen from the frnt of the queue. O(1) */
void QueueDequeue(queue_t* queue);

/*  Returns the element at the front of the queue. O(1) */
void* QueuePeek(const queue_t* queue);

/* Returns the current size of the queue (number of elements) O(n) */
size_t QueueSize(const queue_t* queue);

/* Checks if the queue is empty, returns 1 if empty, 0 otherwise O(1) */
int QueueIsEmpty(const queue_t* queue);

/* Appends the src queue to the dst queue, src is not destroyed, it remains an empty queue. O(1) */
queue_t* QueueAppend(queue_t* queue_dst, queue_t* queue_src);

#endif /* __QUEUE_H__ */
