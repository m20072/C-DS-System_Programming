/******************************************************************************
* File: filename.h
*
* Purpose:
*   Provides an interface for priority queue implementation.
*
* Author:
*   Matan Chen
*
* Review History:
*   - 
*
******************************************************************************/

#ifndef __P_QUEUE_H__
#define __P_QUEUE_H__

#include "../include/sorted_ll.h"

typedef int (*is_match_t)(const void* data, const void* param);
typedef int (*cmp_func_t)(const void* data1, const void* data2);
typedef struct p_queue p_queue_t;

p_queue_t* PQCreate(cmp_func_t cmp_func);
void PQDestroy(p_queue_t* p_queue);
int PQEnqueue(p_queue_t* p_queue, void* data);
void PQDequeue(p_queue_t* p_queue);
void* PQPeek(const p_queue_t* p_queue);
int PQIsEmpty(const p_queue_t* p_queue);
size_t PQCount(const p_queue_t* p_queue);
void PQClear(p_queue_t* p_queue);
void PQRemove(p_queue_t* p_queue, is_match_t is_match, const void* param);

#endif
