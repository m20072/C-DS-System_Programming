/******************************************************************************
* File: circ_buf.h
*
* Purpose:
*   Provides an interface for circular buffer implementation.
*
* Author:
*   Matan Chen
*
* Review History:
*   - Albert
*
******************************************************************************/

#ifndef __CIRC_BUF_H__
#define __CIRC_BUF_H__

#include <sys/types.h>

typedef struct circ_buf circ_buf_t;

/* Creates a circular buffer and returns a pointer to it. O(n) */
circ_buf_t* BufCreate(size_t capacity);

/* Frees dynamically allocated memory of the circular buffer and its components. O(1) */
void BufDestroy(circ_buf_t* buf);

/* Returns the number of free bytes in the buffer. O(1) */
size_t BufFreeSpace(const circ_buf_t* buf);

/* Returns the number of elements in the buffer. O(1) */
size_t BufSize(const circ_buf_t* buf);

/* Check if buffer is empty, returns 1 if empty, 0 otherwise. O(1) */
int BufIsEmpty(const circ_buf_t* buf);

/* Read from buffer into dst, Returns the number of bytes that were read. O(n) */
ssize_t BufRead(circ_buf_t* buf, char* dst, size_t n_bytes);

/* Write from src into buffer, Returns the number of bytes that were written. O(n) */
ssize_t BufWrite(circ_buf_t* buf, const char* src, size_t n_bytes);

#endif /* __CIRC_BUF_H__ */
