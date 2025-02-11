/******************************************************************************
* File: sorted_ll.c
*
* Purpose:
*   implements sorted_ll.h
*   
* Author:
*   Matan Chen
*
* Review History:
*   - 
*
******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/sorted_ll.h"

struct srt_ll
{
	dlist_t* dlist;
	is_before_t is_before;
};

/*struct srt_itr
{
	dlist_itr_t itr;
};*/

srt_ll_t* SrtLLCreate(is_before_t is_before)
{
	srt_ll_t* list = (srt_ll_t*)malloc(sizeof(*list));
	if(NULL == list)
	{
		return NULL;
	}
	
	list->dlist = DLLCreate();
	if(NULL == list->dlist)
	{
		free(list);
		return NULL;
	}
	
	list->is_before = is_before;
	return (list);
}

void SrtLLDestroy(srt_ll_t* list)
{
	DLLDestroy(list->dlist);
	memset(list, 0, sizeof(*list)); /* same as setting list->dlist = NULL, but does it to all fields of list */
	free(list);
}

srt_itr_t SrtLLItrBegin(const srt_ll_t* list)
{
	srt_itr_t struct_itr = { 0 };
	assert(NULL != list);
	struct_itr.itr = DLLItrBegin(list->dlist);
	#ifndef NDEBUG 
	struct_itr.list = (srt_ll_t*)list;
	#endif
	return (struct_itr);
}

srt_itr_t SrtLLItrEnd(const srt_ll_t* list)
{
	srt_itr_t struct_itr = { 0 };
	assert(NULL != list);
	struct_itr.itr = DLLItrEnd(list->dlist);
	#ifndef NDEBUG 
	struct_itr.list = (srt_ll_t*)list;
	#endif
	return (struct_itr);
}

srt_itr_t SrtLLItrNext(srt_itr_t itr)
{
	itr.itr = DLLItrNext(itr.itr);
	return (itr);
}

srt_itr_t SrtLLItrPrev(srt_itr_t itr)
{
	itr.itr = DLLItrPrev(itr.itr);
	return (itr);
}

int SrtLLIsEmpty(const srt_ll_t* list)
{
	assert(NULL != list);
	return (DLLIsEmpty(list->dlist));
}

int SrtLLItrIsEqual(srt_itr_t itr1, srt_itr_t itr2)
{
	return DLLItrIsEqual(itr1.itr, itr2.itr);
}

srt_itr_t SrtLLRemove(srt_itr_t itr)
{
	srt_itr_t struct_itr = { 0 };
	struct_itr.itr = DLLRemove(itr.itr);
	return (struct_itr);
}

void* SrtLLPopFront(srt_ll_t* list)
{
	assert(list);
	return (DLLPopFront(list->dlist));
}

void* SrtLLPopBack(srt_ll_t* list)
{
	assert(list);
	return (DLLPopBack(list->dlist));
}

size_t SrtLLCount(const srt_ll_t* list)
{
	assert(NULL != list);
	return (DLLCount(list->dlist));
}

void* SrtLLGetData(srt_itr_t itr)
{
	return (DLLGetData(itr.itr));
}

int SrtLLForEach(srt_itr_t from, srt_itr_t to, action_func_t action, void* param)
{
	assert(NULL != action);
	return (DLLForEach(from.itr, to.itr, action, param));
}


/* return 'to' if not found, otherwise return the iterator of node than match the function find if*/
srt_itr_t SrtLLFindIf(srt_itr_t from, srt_itr_t to, match_func_t is_match, void* data)
{
	assert(NULL != is_match);
	/* gets from and to iterators, and tries to find according to */
	from.itr = DLLFind(from.itr, to.itr, is_match, data);
	return (from);
		
}

srt_itr_t SrtLLFind(srt_ll_t* list, void* data)
{
	srt_itr_t curr_itr = { 0 };
	srt_itr_t end_itr = { 0 };
	assert(NULL != list);

	curr_itr = SrtLLItrBegin(list);
	end_itr = SrtLLItrEnd(list);
	
	/* traverse until not bigger, and then check if equal, if not, return the tail */
	while(!SrtLLItrIsEqual(curr_itr, end_itr) && (0 < list->is_before(SrtLLGetData(curr_itr), data))) /* while curr_itr data is before data, continue to traverse */
	{
		curr_itr = SrtLLItrNext(curr_itr); /* curr_itr isnt ==  end_itr AND is_before returned negative value meaning that curr_itr is before data */
	}
	return((0 == list->is_before(SrtLLGetData(curr_itr), data)) ? curr_itr : end_itr); /* if its equal return it, otherwise return end_itr */
}

srt_itr_t SrtLLInsert(srt_ll_t* list, void* data)
{
	srt_itr_t struct_itr = { 0 };
	assert(NULL != list);
	
	struct_itr = SrtLLItrBegin(list);
	
	while((!SrtLLItrIsEqual(struct_itr, SrtLLItrEnd(list))) && (0 > list->is_before(SrtLLGetData(struct_itr), data)))
	{
		struct_itr = SrtLLItrNext(struct_itr);
	}
	struct_itr.itr = DLLInsertBefore(list->dlist, struct_itr.itr, data);
	return struct_itr;
}

srt_ll_t* SrtLLMerge(srt_ll_t* dst, srt_ll_t* src) /* assuming both lists have the same sorting? assert check that? if check that? or no need to check at all */
{
	srt_itr_t where = { 0 };
	srt_itr_t from = { 0 };
	srt_itr_t to = { 0 };
	srt_itr_t src_end = { 0 };
	srt_itr_t dst_end = { 0 };
	
	assert(dst != NULL);
	assert(src != NULL);
	
	where = SrtLLItrBegin(dst);
	from = SrtLLItrBegin(src);
	to = SrtLLItrBegin(src);
	src_end = SrtLLItrEnd(src);
	dst_end = SrtLLItrEnd(dst);
	
	while(!SrtLLItrIsEqual(to, src_end) && !SrtLLItrIsEqual(where, dst_end))
	{
		if((0 >= dst->is_before(SrtLLGetData(to), SrtLLGetData(where)))) /* is to smaller than where?  */
		{
			to = SrtLLItrNext(to);
		}
		else /*if(!SrtLLItrIsEqual(from, to))*/
		{
			if(!SrtLLItrIsEqual(from, to))
			{
				DLLSplice(where.itr, from.itr, to.itr);
			}
			from.itr = to.itr;
			where = SrtLLItrNext(where);
		}
	}

	/* once we get here, either the 'where' is on dummy or the 'to' is on dummy*/
	/* either way, we can set 'to' to be on dummy (even if it already is thats fine) */
	/* and we can just splice all of that behind 'where', whether 'where' is the dummy or not doesnt matter */
	to.itr = src_end.itr;

	/*if(!SrtLLItrIsEqual(from, to))*/
	DLLSplice(where.itr, from.itr, to.itr); /* do a final splice when we reached src_end */
	
	return dst;
}

