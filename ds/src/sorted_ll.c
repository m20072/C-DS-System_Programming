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
*   - Ofir
*
******************************************************************************/

#include <stdlib.h> /* allocations and free */
#include <string.h> /* memset */
#include <assert.h> /* assert */
#include "../include/sorted_ll.h"

struct srt_ll
{
	dlist_t* dlist;
	is_before_t is_before;
};

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
	assert(NULL != list);
	DLLDestroy(list->dlist);
	memset(list, 0, sizeof(*list));
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
	#ifndef NDEBUG
	if (itr1.list != itr2.list)
	{
		return (0);
	}
	#endif
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
	assert(NULL != list);
	return (DLLPopFront(list->dlist));
}

void* SrtLLPopBack(srt_ll_t* list)
{
	assert(NULL != list);
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

	#ifndef NDEBUG
	if (from.list != to.list)
	{
		return (1);
	}
	#endif

	return (DLLForEach(from.itr, to.itr, action, param));
}

srt_itr_t SrtLLFindIf(srt_itr_t from, srt_itr_t to, match_func_t is_match, void* data)
{
	assert(NULL != is_match);
	assert(NULL != data);

	#ifndef NDEBUG
	if (from.list != to.list)
	{
		return (to);
	}
	#endif

	from.itr = DLLFind(from.itr, to.itr, is_match, data);
	return (from);
		
}

srt_itr_t SrtLLFind(srt_ll_t* list, void* data)
{
	srt_itr_t curr_itr = { 0 };
	srt_itr_t end_itr = { 0 };
	assert(NULL != list);
	assert(NULL != data);

	curr_itr = SrtLLItrBegin(list);
	end_itr = SrtLLItrEnd(list);
	
	while(!SrtLLItrIsEqual(curr_itr, end_itr) && (0 > list->is_before(SrtLLGetData(curr_itr), data)))
	{
		curr_itr = SrtLLItrNext(curr_itr);
	}
	return((!SrtLLItrIsEqual(curr_itr, end_itr) && (0 == list->is_before(SrtLLGetData(curr_itr), data))) ? curr_itr : end_itr);
}

srt_itr_t SrtLLInsert(srt_ll_t* list, void* data)
{
	srt_itr_t struct_itr = { 0 };
	assert(NULL != list);
	assert(NULL != data);
	
	struct_itr = SrtLLItrBegin(list);
	
	while((!SrtLLItrIsEqual(struct_itr, SrtLLItrEnd(list))) && (0 > list->is_before(SrtLLGetData(struct_itr), data)))
	{
		struct_itr = SrtLLItrNext(struct_itr);
	}
	struct_itr.itr = DLLInsertBefore(list->dlist, struct_itr.itr, data);
	return struct_itr;
}

srt_ll_t* SrtLLMerge(srt_ll_t* dst, srt_ll_t* src)
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
		if((0 >= dst->is_before(SrtLLGetData(to), SrtLLGetData(where)))) /* according to dst is_before */
		{
			to = SrtLLItrNext(to);
		}
		else
		{
			if(!SrtLLItrIsEqual(from, to))
			{
				DLLSplice(where.itr, from.itr, to.itr);
			}
			from.itr = to.itr;
			where = SrtLLItrNext(where);
		}
	}
	to.itr = src_end.itr;
	DLLSplice(where.itr, from.itr, to.itr);
	return dst;
}

