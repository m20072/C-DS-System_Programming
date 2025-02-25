/******************************************************************************
* File: filename.c
*
* Purpose:
*   implements p_queue.h
*   
* Author:
*   Matan Chen
*
* Review History:
*   - Shani
*
******************************************************************************/
#include <stdlib.h> /* dynamic allocation, free */
#include <assert.h> /* assert */

#include "../include/sorted_ll.h" /* sorted linked list */
#include "../include/p_queue.h" /* priority queue header */

struct p_queue
{
	srt_ll_t* list;
};

p_queue_t* PQCreate(compare_func_t cmp_func)
{
	p_queue_t* p_queue = NULL;
	assert(NULL != cmp_func);
		
	p_queue = (p_queue_t*)malloc(sizeof(p_queue_t));
	if(NULL == p_queue)
	{
		return (NULL);
	}
	
	p_queue->list = SrtLLCreate(cmp_func);
	if(NULL == p_queue->list)
	{
		free(p_queue);
		p_queue = NULL;
		return (NULL);
	}
	return (p_queue);
}

void PQDestroy(p_queue_t* p_queue)
{
	assert(NULL != p_queue);
	SrtLLDestroy(p_queue->list);
	p_queue->list = NULL;
	free(p_queue);
	p_queue = NULL;
}

int PQEnqueue(p_queue_t* p_queue, void* data)
{
	assert(NULL != p_queue);
	return SrtLLItrIsEqual(SrtLLInsert(p_queue->list, data), SrtLLItrEnd(p_queue->list));
}

void PQDequeue(p_queue_t* p_queue)
{
	assert(NULL != p_queue);
	SrtLLPopFront(p_queue->list);
}

void* PQPeek(const p_queue_t* p_queue)
{
	assert(NULL != p_queue);
	return SrtLLGetData(SrtLLItrBegin(p_queue->list));
}

int PQIsEmpty(const p_queue_t* p_queue)
{
	assert(NULL != p_queue);
	return SrtLLIsEmpty(p_queue->list);
}

size_t PQCount(const p_queue_t* p_queue)
{
	assert(NULL != p_queue);
	return (SrtLLCount(p_queue->list));
}

void PQClear(p_queue_t* p_queue)
{
	assert(NULL != p_queue);
	while(!PQIsEmpty(p_queue))
	{
		SrtLLPopFront(p_queue->list);
	}
}

void* PQRemove(p_queue_t* p_queue, is_match_func_t is_match, const void* param)
{
	void* data = NULL;
	srt_itr_t found_element = { 0 };
	assert(NULL != p_queue);

	found_element = SrtLLFindIf(SrtLLItrBegin(p_queue->list), SrtLLItrEnd(p_queue->list), is_match, (void*)param);
	data = SrtLLGetData(found_element);

	/*dont remove tail if its what was returned */
	if(!SrtLLItrIsEqual(found_element, SrtLLItrEnd(p_queue->list)))
	{
		SrtLLRemove(found_element);
	}
	return (data);
}