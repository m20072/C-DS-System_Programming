/******************************************************************************
* File: circ_buf.c
*
* Purpose:
*   implements circ_buf.h
*   
* Author:
*   Matan Chen
*
* Review History:
*   - 
*
******************************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "../include/circ_buf.h"

#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
#define HEAD(BUF) (BUF->arr + BUF->head_idx)
#define HEAD_INDEX(BUF) (BUF->head_idx)
#define TAIL_INDEX(BUF) ((size_t)(BUF->head_idx + BUF->size) % BUF->capacity)
#define TAIL(BUF) (BUF->arr + TAIL_INDEX(BUF))
#define MIN(a,b) ((a < b) ? a : b)

struct circ_buf
{
	size_t capacity;
	size_t size;
	size_t head_idx;
	char arr[1];
};

circ_buf_t* BufCreate(size_t capacity)
{
	circ_buf_t* buffer = (circ_buf_t*)calloc(1, OFFSETOF(circ_buf_t, arr) + capacity);
	if(NULL == buffer)
	{
		return NULL;
	}
	buffer->capacity = capacity;
	return buffer;
}


void BufDestroy(circ_buf_t* buf)
{
	assert(NULL != buf);
	memset(buf, 0, OFFSETOF(circ_buf_t, arr) + buf->capacity);
	free(buf);
	buf = NULL;
}

size_t BufFreeSpace(const circ_buf_t* buf)
{
	assert(NULL != buf);
	return (buf->capacity - buf->size);
}

size_t BufSize(const circ_buf_t* buf)
{
	assert(NULL != buf);
	return buf->size;
}

int BufIsEmpty(const circ_buf_t* buf)
{
	assert(NULL != buf);
	return (0 == buf->size);
}


ssize_t BufRead(circ_buf_t* buf, char* dst, size_t n_bytes)
{
	size_t bytes_to_wrap = 0;
	size_t bytes_to_read = 0;
	size_t first_chunk = 0;
	size_t second_chunk = 0;
	
	if (NULL == buf || NULL == dst)
	{
		return (-1);
	}

	bytes_to_wrap = buf->capacity - HEAD_INDEX(buf);
	bytes_to_read = MIN(buf->size, n_bytes);
	first_chunk = MIN(bytes_to_read, bytes_to_wrap);

	memcpy(dst, HEAD(buf), first_chunk);
	HEAD_INDEX(buf) += (first_chunk % buf->capacity);
    if (first_chunk < bytes_to_read) 
    {
    	second_chunk = (bytes_to_read - first_chunk);
        memcpy(dst + first_chunk, buf->arr, second_chunk);
        HEAD_INDEX(buf) += (second_chunk % buf->capacity);
    }

	buf->size -= bytes_to_read;
	return bytes_to_read;
}

ssize_t BufWrite(circ_buf_t* buf, const char* src, size_t n_bytes)
{
	size_t bytes_to_wrap = 0;
	size_t bytes_to_write = 0;
	size_t first_chunk = 0;
	size_t second_chunk = 0;
	
	if (NULL == buf || NULL == src)
	{
		return (-1);
	}

	
	bytes_to_wrap = buf->capacity - TAIL_INDEX(buf);
	bytes_to_write = MIN(BufFreeSpace(buf), n_bytes);
	first_chunk = MIN(bytes_to_write, bytes_to_wrap);
	
	memcpy(TAIL(buf), src, first_chunk);
	buf->size += first_chunk; /* needed before the if, incase the condition is met */

	if(first_chunk < bytes_to_write)
	{
		second_chunk = bytes_to_write - first_chunk;
		memcpy(TAIL(buf), src + first_chunk, second_chunk);
		buf->size += second_chunk;
	}
	return bytes_to_write;
}
