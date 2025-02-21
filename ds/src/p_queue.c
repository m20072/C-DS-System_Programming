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
*   - 
*
******************************************************************************/
#include <assert.h>

#include "../include/p_queue.h"

struct p_queue
{
	srt_ll_t* list;
};

p_queue_t* PQCreate(cmp_func_t cmp_func)
{
	p_queue_t* p_queue = NULL;
	assert(NULL != cmp_func);
		
	p_queue = (p_queue_t*)malloc(sizeof(p_queue_t));
	if(NULL == p_queue)
	{
		return NULL;
	}
	
	p_queue_t->list = SrtLLCreate(cmp_func);
	if(NULL == p_queue_t->list)
	{
		return NULL;
	}
	
}
