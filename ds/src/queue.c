/******************************************************************************
* File: queue.c
*
* Purpose:
*   implements queue.h
*   
* Author:
*   Matan Chen
*
* Review History:
*   - Yonatan
*
******************************************************************************/

#include <stdlib.h> /* dynamic allocations */
#include <assert.h> /* assert */
#include "../include/queue.h"
#include "../include/singly_ll.h"

struct Queue
{
    slist_t* list;
};

queue_t* QueueCreate()
{
	queue_t* queue = (queue_t*)malloc(sizeof(queue_t));
	if(NULL == queue)
	{
		return NULL;
	}
	
	queue->list = ListCreate();
	if(NULL == queue->list)
	{
		free(queue);
		queue = NULL;
		return NULL;
	}
	return queue;
}

void QueueDestroy(queue_t* queue)
{
	assert(NULL != queue);
	ListDestroy(queue->list);
	queue->list = NULL;
	free(queue);
	queue = NULL;
}


int QueueEnqueue(queue_t* queue, void* data)
{
	assert(NULL != queue);
	assert(NULL != data);
	return (NULL == ListInsertBefore(ListItrEnd(queue->list), data));
}

void QueueDequeue(queue_t* queue)
{
	assert(NULL != queue);
	ListRemove(ListItrBegin(queue->list));
}

void* QueuePeek(const queue_t* queue)
{
	assert(NULL != queue);
	return ListGetData(ListItrBegin(queue->list));
}

size_t QueueSize(const queue_t* queue)
{
	assert(NULL != queue);
	return ListCount(queue->list);	
}

int QueueIsEmpty(const queue_t* queue)
{
	assert(NULL != queue);
	return ListIsEmpty(queue->list);
}

queue_t* QueueAppend(queue_t* queue_dst, queue_t* queue_src)
{
	assert(NULL != queue_dst);
	assert(NULL != queue_src);
	ListAppend(queue_dst->list, queue_src->list);
	return queue_dst;
}



