/******************************************************************************
* File: doubly_ll.c
*
* Purpose:
*   implements doubly_ll.h
*   
* Author:
*   Matan Chen
*
* Review History:
*   - 
*
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/doubly_ll.h"

typedef struct node node_t;

struct node
{
	void* data;
	node_t* next;
	node_t* prev;
};

struct dlist
{
	node_t head;
	node_t tail;
};


static dlist_itr_t NodeToItr(node_t* node);
static node_t* ItrToNode(dlist_itr_t itr);
static node_t* NewNode(void* data, node_t* prev_node, node_t* next_node);
static int NodeCount(void* param1, void* param2);


dlist_t* DLLCreate()
{
	dlist_t* dlist = (dlist_t*)malloc(sizeof(dlist_t));
	if(NULL == dlist)
	{
		return NULL;
	}
	dlist->head.prev = NULL;
	dlist->head.next = &dlist->tail;
	dlist->head.data = NULL;
	
	dlist->tail.prev = &dlist->head;
	dlist->tail.next = NULL;
	dlist->tail.data = NULL;
	
	return (dlist);
}

void DLLDestroy(dlist_t* list) /* memset also before free(list) */
{
	node_t* current_node = list->head.next; /* current_node is a ptr to tail if empty list */
	
	while(NULL != current_node->next)
	{
		current_node = current_node->next;
		free(current_node->prev);
		current_node->prev = NULL;
	}
	free(list);
}

dlist_itr_t DLLItrBegin(const dlist_t* list)
{
	assert(NULL != list); /* assert on list->head.next?*/
	return (NodeToItr(list->head.next));
}

/* return list->tail */
dlist_itr_t DLLItrEnd(const dlist_t* list)
{
	assert(NULL != list);
	return NodeToItr((node_t*)&list->tail);
}

dlist_itr_t DLLItrNext(dlist_itr_t itr)
{
	node_t* next_node = ItrToNode(itr)->next; /* undefined to do so on the tail */
	assert(next_node); /* remove this? */
	return (NodeToItr(next_node));
}

/* undefined behavior if itr is head */
dlist_itr_t DLLItrPrev(dlist_itr_t itr)
{
	node_t* prev_node = ItrToNode(itr)->prev; /* undefined to do so on the tail */
	assert(prev_node); /* remove this? */
	return (NodeToItr(prev_node));
}

void* DLLGetData(dlist_itr_t itr)
{
	return (ItrToNode(itr)->data);
}

void DLLSetData(dlist_itr_t itr, const void* data)
{
	ItrToNode(itr)->data = (void*)data;
}

int DLLIsEmpty(const dlist_t* list)
{
	return (list->head.next == &list->tail);
}

int DLLItrIsEqual(dlist_itr_t itr1, dlist_itr_t itr2)
{
	return (itr1 == itr2);
}

dlist_itr_t DLLPushFront(dlist_t* list, void* data)
{
	assert(NULL != list);
	return DLLInsertBefore(list, NodeToItr(list->head.next), data);
}


dlist_itr_t DLLPushBack(dlist_t* list, void* data)
{
	assert(NULL != list);
	return DLLInsertBefore(list, NodeToItr(&list->tail), data);
}


void* DLLPopFront(dlist_t* list)
{
	void* data = (list->head.next)->data;
	DLLRemove(NodeToItr(list->head.next));
	return (data);
}

void* DLLPopBack(dlist_t* list)
{
	void* data = (list->tail.prev)->data;
	DLLRemove(NodeToItr(list->tail.prev));
	return (data);
}

size_t DLLCount(const dlist_t* list)
{
	size_t count = 0;
	assert(NULL != list);

	DLLForEach(NodeToItr(list->head.next), NodeToItr((node_t*)&list->tail), &NodeCount, &count);
	return (count);
}

dlist_itr_t DLLRemove(dlist_itr_t itr)
{
	node_t* deleted_node = ItrToNode(itr);
	(deleted_node->next)->prev = deleted_node->prev;
	(deleted_node->prev)->next = deleted_node->next;
	
	itr = NodeToItr(deleted_node->next);
	free(deleted_node); /* memset before? */
	return (itr);
}

dlist_itr_t DLLFind(dlist_itr_t from, dlist_itr_t to, match_func_t is_match, const void* data)
{
	node_t* node_from = ItrToNode(from);
	assert(NULL != is_match);
	assert(NULL != data);
	
	while(!DLLItrIsEqual(from, to) && 0 == is_match(node_from->data, (void*)data))
	{
		from = NodeToItr(node_from->next);
		node_from = node_from->next;
	}
	return (!DLLItrIsEqual(from, to) ? from : to);
}

int DLLMultiFind(dlist_itr_t from, dlist_itr_t to, match_func_t is_match, const void* data, dlist_t* output)
{	
	node_t* found_node = ItrToNode(DLLFind(from, to, is_match, data));
	
	while(!DLLItrIsEqual(NodeToItr(found_node), to))
	{
		if(DLLItrIsEqual(NodeToItr(&output->tail), DLLPushBack(output, (void*)data))) /* push into output list */
		{
			return (-1); /* if pushback failed (returned tail iterator) */
		}
		found_node = ItrToNode(DLLFind(NodeToItr(found_node->next), to, is_match, data));
	}
	return (0);
}

dlist_itr_t DLLSplice(dlist_itr_t where, dlist_itr_t from, dlist_itr_t to)
{
	node_t* node_where = ItrToNode(where);
	node_t* node_from = ItrToNode(from);
	node_t* node_to = ItrToNode(to);
	node_t* tmp = where->prev;
	
	(node_where->prev)->next = node_from;
	(node_from->prev)->next = node_to;
	
	(node_to->prev)->next = node_where;
	node_where->prev = node_to->prev;

	node_to->prev = node_from->prev;
	
	node_from->prev = tmp;
	return (tmp);
}

dlist_itr_t DLLInsertBefore(dlist_t* list, dlist_itr_t itr, void* data) /* return DLLItrEnd(list) if failed */
{
	
	node_t* after_node = ItrToNode(itr);
	node_t* mid_node = NewNode(data, after_node->prev, after_node);
	
	
	assert(NULL != list);
	
	if(NULL == mid_node)
	{
		return (DLLItrEnd(list));
	}
	(after_node->prev)->next = mid_node;
	after_node->prev = mid_node;
	return (NodeToItr(mid_node));
}

int DLLForEach(dlist_itr_t from, dlist_itr_t to, action_func_t action, void* param)
{
	int status = 0;
	node_t* node_from = ItrToNode(from);
	
	assert(NULL != action);

	while(0 == status && !DLLItrIsEqual(from, to))
	{
		status = action(node_from->data, param);
		from = NodeToItr(node_from->next);
		node_from = node_from->next;
	}
	return (status);
}

static dlist_itr_t NodeToItr(node_t* node)
{
	/* NULL CHECK? */
	return (dlist_itr_t)node;
	
}
static node_t* ItrToNode(dlist_itr_t itr)
{
	return (node_t*)(itr);	
}

static int NodeCount(void* param1, void* param2)
{
	(void)param1;
	++*(size_t*)param2;
	return (0);
}

static node_t* NewNode(void* data, node_t* prev_node, node_t* next_node)
{
	node_t* new_node = (node_t*)malloc(sizeof(node_t));
	if(NULL == new_node)
	{
		return NULL;
	}
	new_node->data = data;
	new_node->prev = prev_node;
	new_node->next = next_node;
	return (new_node);
}
