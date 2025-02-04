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
static slist_itr_t NodeToItr(node_t* node);
static node_t* ItrToNode(slist_itr_t itr);
static int NodeCount(void* param1, void* param2);

struct node
{
	node_t* next;
	void* data;
};

struct slist
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
	
	slist->head = slist->tail;
	return slist;
}

void ListDestroy(slist_t* list)
{
	node_t* prev = NULL;
	node_t* curr = NULL;
	
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
	return NodeToItr(list->head);
}

slist_itr_t ListItrNext(slist_itr_t itr)
{
	return NodeToItr(itr->next);
}

slist_itr_t ListItrEnd(slist_t* list)
{
	assert(NULL != list);
	return NodeToItr(list->tail);
}

int ListItrIsEqual(slist_itr_t itr1, slist_itr_t itr2)
{
	return itr1 == itr2;
}

void* ListGetData(slist_itr_t itr)
{	
	node_t* node = ItrToNode(itr);
	
	if(NULL == node->next) /* convert to node and then use on the node->next */
	{
		return NULL;
	}
	return node->data; /* possible to get dummy tail data */
}

void ListSetData(slist_itr_t itr, const void* data)
{
	node_t* node = ItrToNode(itr);

	if(NULL == node->next) /* dont allow setting dummy tail data */
	{
		return;
	}
	node->data = (void*)data;
}

slist_itr_t ListInsertBefore(slist_itr_t itr, const void* data)
{
	node_t* curr_node = ItrToNode(itr);
	node_t* after_node = NULL;

	assert(NULL != data);

	after_node = NewNode(curr_node->data, curr_node->next);
	if(NULL == after_node)
	{
		return NULL;
	}
	curr_node->data = (void*)data;
	curr_node->next = after_node;

	if(NULL == after_node->next) /* if the allocated node is a new dummy tail, update list tail field */
	{
		((slist_t*)after_node->data)->tail = after_node;
	}
	return itr;
}

slist_itr_t ListRemove(slist_itr_t itr)
{
	node_t* curr_node = ItrToNode(itr);
	node_t* removed_node = NULL;

	if(NULL == curr_node->next) /* attempt to remove dummy tail node */
	{
		return NULL;
	}

	removed_node = curr_node->next;
	curr_node->data = removed_node->data;
	curr_node->next = removed_node->next;

	if(NULL == curr_node->next) /* if replaced the removed node with dummy tail node, update list tail field */
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

	ListForEach(NodeToItr(list->head), NodeToItr(list->tail), &NodeCount, &count);
	return count;
}

int ListIsEmpty(slist_t* list)
{
	return (list->head == list->tail);
}

slist_itr_t ListFind(slist_itr_t from, slist_itr_t to, match_func_t is_match, const void* data)
{
	node_t* node_from = ItrToNode(from);
	assert(NULL != is_match);
	assert(NULL != data);
	
	while(!ListItrIsEqual(from, to) && 0 == is_match(node_from->data, (void*)data))
	{
		from = NodeToItr(node_from->next);
		node_from = node_from->next;
	}
	return (!ListItrIsEqual(from, to)) ? from : to;
}


int ListForEach(slist_itr_t from, slist_itr_t to, action_func_t action_func, const void* param)
{
	int status = 0;
	node_t* node_from = ItrToNode(from);
	
	assert(NULL != action_func);
	assert(NULL != param);

	while(0 == status && !ListItrIsEqual(from, to))
	{
		status = action_func(node_from->data, (void*)param);
		from = from->next;
		node_from = node_from->next;
	}
	return status;
}

slist_t* ListAppend(slist_t* list_dest, slist_t* list_src)
{
	/* dest dummy tail becomes a copy of first element in src */
	list_dest->tail->data = list_src->head->data;
	list_dest->tail->next = list_src->head->next;
	
	/* adjust dest tail to point to the src tail instead of what was previously dummy tail the dummy tail (and now is the first element of src) */
	list_dest->tail = list_src->tail;
	
	/* in src, make the node after the head be its new dummy tail */
	list_src->tail = list_src->head;
	list_src->tail->data = list_src;
	list_src->tail->next = NULL;
	
	return list_dest;
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

static slist_itr_t NodeToItr(node_t* node)
{
	assert(NULL != node);
	return (slist_itr_t)node;
}

static node_t* ItrToNode(slist_itr_t itr)
{
	return (node_t*)itr;
}
