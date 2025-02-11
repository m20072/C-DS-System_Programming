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
*   - Albert
*
******************************************************************************/
#include <sys/types.h> /* ssize_t */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */
#include <stdlib.h> /* dynamic memory allocations */
#include <errno.h>  /* errno */
#include "../include/circ_buf.h"

#define OFFSETOF(type, element) ((size_t)&(((type*)0)->element))
#define HEAD_INDEX(buf) (buf->head_idx)
#define TAIL_INDEX(buf) ((buf->head_idx + buf->size) % buf->capacity)
#define HEAD(buf) (buf->arr + buf->head_idx)
#define TAIL(buf) (buf->arr + TAIL_INDEX(buf))
#define BYTES_UNTIL_WRAP(buf, index) (buf->capacity - index)
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
	size_t first_chunk = 0;
	
	if (NULL == buf || NULL == dst)
	{
		return (-1);
	}

	n_bytes = MIN(buf->size, n_bytes);
	first_chunk = MIN(n_bytes, BYTES_UNTIL_WRAP(buf, HEAD_INDEX(buf)));
	
	memcpy(dst, HEAD(buf), first_chunk);
    memcpy(dst + first_chunk, buf->arr, (n_bytes - first_chunk)); /* second chunk */
    
	HEAD_INDEX(buf) += (n_bytes % buf->capacity);
	buf->size -= n_bytes;
	return n_bytes;
}

ssize_t BufWrite(circ_buf_t* buf, const char* src, size_t n_bytes)
{
	size_t first_chunk = 0;
	size_t tail_index = 0;
	
	assert(NULL != buf);
	assert(NULL != src);
	
	tail_index = TAIL_INDEX(buf);
	n_bytes = MIN(buf->capacity - buf->size, n_bytes);
	first_chunk = MIN(n_bytes, BYTES_UNTIL_WRAP(buf, tail_index));
	
	memcpy(buf->arr + tail_index, src, first_chunk);
	memcpy(buf->arr, src + first_chunk, (n_bytes - first_chunk)); /* second chunk */
	
	buf->size += n_bytes;
	return n_bytes;
}
