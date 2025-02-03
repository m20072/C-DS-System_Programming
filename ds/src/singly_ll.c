/******************************************************************************
* File: singly_ll.c
*
* Purpose:
*   implements singly_ll.h
*   
* Author:
*   Matan Chen
*
* Review History:
*   - 
*
******************************************************************************/
#include <stdlib.h> /* Dynamic allocations */
#include <assert.h> /* assert */
#include "../include/singly_ll.h"

static node_t* NewNode(void* data, node_t* next);
static int NodeCount(void* param1, void* param2);

struct node_t
{
	node_t* next;
	void* data;
};

struct slist_t
{
	node_t* head;
	node_t* tail;
};


slist_t* ListCreate()
{
	slist_t* slist = (slist_t*)malloc(sizeof(slist_t));
	if(NULL == slist)
	{
		return NULL;
	}

	slist->tail = NewNode(slist, NULL);
	if(NULL == slist->tail)
	{
		free(slist);
		return NULL;
	}

	slist->head = NewNode(NULL, slist->tail);
	if(NULL == slist->head)
	{
		free(slist->tail);
		free(slist);
		return NULL;
	}
	return slist;
}

void ListDestroy(slist_t* list)
{
	slist_itr_t prev = NULL;
	slist_itr_t curr = NULL;
	
	assert(NULL != list);

	prev = list->head;
	curr = prev->next;

	while(NULL != curr)
	{
		free(prev);
		prev = curr;
		curr = curr->next;
	}
	free(list);
}

slist_itr_t ListItrBegin(const slist_t* list)
{
	assert(NULL != list);
	return list->head->next; /* dummy tail return possibly */
}

slist_itr_t ListItrNext(slist_itr_t itr)
{
	assert(NULL != itr);
	/*return (NULL != itr->next->next) ? itr->next : NULL;*/ /* this is fine to do bcz we know that itr->next will not be NULL for sure, at worst it might be the dummy*/

	return itr->next;
}

slist_itr_t ListItrEnd(slist_t* list)
{
	assert(NULL != list);
	return list->tail;
}

int ListItrIsEqual(slist_itr_t itr1, slist_itr_t itr2)
{
	assert(NULL != itr1);
	assert(NULL != itr2);

	return itr1 == itr2;
}

void* ListGetData(slist_itr_t itr)
{
	assert(NULL != itr);

	if(NULL == itr->next) /* dont allow getting data from dummy tail*/
	{
		return NULL;
	}
	return itr->data; /* possible to get dummy tail data */
}

void ListSetData(slist_itr_t itr, const void* data)
{
	assert(NULL != data);

	if(NULL == itr->next) /* dont allow setting dummy tail data */
	{
		return;
	}
	itr->data = (void*)data;
}

slist_itr_t ListInsertBefore(slist_itr_t itr, const void* data)
{
	node_t* after_node = NULL;

	assert(NULL != itr);
	assert(NULL != data);

	after_node = NewNode(itr->data, itr->next);
	if(NULL == after_node)
	{
		return NULL;
	}
	itr->data = (void*)data;
	itr->next = after_node;

	if(NULL == after_node->next) /* if the allocated node is a new dummy tail, update list tail field */
	{
		((slist_t*)after_node->data)->tail = after_node;
	}
	return itr;
}

slist_itr_t ListRemove(slist_itr_t itr)
{
	node_t* removed_node = NULL;

	assert(NULL != itr);

	if(NULL == itr->next) /* attempt to remove dummy tail node */
	{
		return NULL;
	}

	removed_node = itr->next;
	itr->data = removed_node->data;
	itr->next = removed_node->next;

	if(NULL == itr->next) /* if replaced the removed node with dummy tail node, update list tail field */
	{
		((slist_t*)itr->data)->tail = itr;
	}
	free(removed_node);
	return itr;
}

size_t ListCount(const slist_t* list)
{
	size_t count = 0;
	assert(NULL != list);

	ListForEach(list->head->next, list->tail, &NodeCount, &count);
	return count;
}

int ListIsEmpty(slist_t* list)
{
	return (list->head->next == list->tail);
}

slist_itr_t ListFind(slist_itr_t from, slist_itr_t to, match_func_t is_match, const void* data)
{
	assert(NULL != from && NULL != to && NULL != is_match && NULL != data);

	while(from != to && 0 == is_match(from->data, (void*)data))
	{
		from = from->next;
	}
	return (from != to) ? from : NULL;
}

int ListForEach(slist_itr_t from, slist_itr_t to, action_func_t action_func, const void* param)
{
	int status = 0;

	assert(NULL != from && NULL != to && NULL != action_func && NULL != param);

	while(0 == status && from != to)
	{
		status = action_func(from->data, (void*)param);
		from = from->next;
	}
	return status;
}

static node_t* NewNode(void* data, node_t* next)
{
	node_t* new_node = (node_t*)malloc(sizeof(node_t));
	if(NULL == new_node)
	{
		return NULL;
	}
	new_node->data = data;
	new_node->next = next;
	return new_node;
}

static int NodeCount(void* param1, void* param2)
{
	(void)param1;
	++*(size_t*)param2;
	return 0;
}