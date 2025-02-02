/******************************************************************************
* File: vector.c
*
* Purpose:
*   implements vector.h
*   
* Author:
*   Matan Chen
*
* Review History:
*   - 
*
******************************************************************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* printf */
#include <string.h> /* memcpy */
#include "../include/vector.h"

#define MIN_CAPACITY 8
#define MAX(a,b) ((a > b) ? a : b)

struct vector
{
	void* vector_head;
	size_t element_size;
	size_t vector_size;
	size_t capacity;
};

vector_t* VectorCreate(size_t element_size, size_t capacity)
{
	vector_t* vector = (vector_t*)malloc(sizeof(vector_t));
	if(NULL == vector)
	{
		return NULL;
	}
	
    capacity = MAX(capacity, MIN_CAPACITY);

	vector->vector_head = (void*)malloc(element_size * capacity);
	if(NULL == vector->vector_head)
	{
		free(vector);
		return NULL;
	}
	
	vector->capacity = capacity;
	vector->vector_size = 0;
	vector->element_size = element_size;
	return vector;
}

void VectorDestroy(vector_t* vector)
{
    assert(NULL != vector);
    free(vector->vector_head);
    free(vector);
}

void* VectorAccessElement(const vector_t* vector, size_t index)
{
    assert(NULL != vector);
    assert(NULL != vector->vector_head);
    if(vector->vector_size <= index)
    {
        return NULL;
    }
    return ((char*)vector->vector_head + (index * vector->element_size));
}

int VectorPushBack(vector_t* vector, const void* data)
{
    void* tmp_vector_head = NULL;
    assert(NULL != vector);
    assert(NULL != vector->vector_head);
    assert(NULL != data);

    if(vector->vector_size == vector->capacity)
    {
        tmp_vector_head = (void*)realloc(vector->vector_head, (vector->capacity << 1) * vector->element_size);
        if(NULL == tmp_vector_head)
        {
            return 1; /* failure */
        }
        vector->vector_head = tmp_vector_head;
        vector->capacity <<= 1;
    }
    memcpy((char*)vector->vector_head + vector->vector_size * vector->element_size, data, vector->element_size);
    ++vector->vector_size;
    return 0;
}


/* If size is smaller than capacity/4, divides capacity by 2.
 * avoid division of capacity by 4, would mean realloc if followed by a VectorPushBack. */
void VectorPopBack(vector_t* vector)
{
    void* tmp_vector_head = NULL;
    assert(NULL != vector);
    assert(NULL != vector->vector_head);

    if(0 < vector->vector_size)
    {
        --vector->vector_size;
        if(vector->vector_size < (vector->capacity >> 2))
        {
            tmp_vector_head = (void*)realloc(vector->vector_head, MAX((vector->capacity >> 1), MIN_CAPACITY) * vector->element_size);
            if(NULL == tmp_vector_head)
            {
                return;
            }
            vector->vector_head = tmp_vector_head;
            vector->capacity = MAX((vector->capacity >> 1), MIN_CAPACITY);
        }
    }
}

size_t VectorCapacity(const vector_t* vector)
{
    assert(NULL != vector);
    return vector->capacity;
}

size_t VectorSize(const vector_t* vector)
{
    assert(NULL != vector);
    return vector->vector_size;
}

int VectorReserve(vector_t* vector, size_t new_capacity)
{
    void* tmp_vector_head = NULL;
    assert(NULL != vector);
    assert(NULL != vector->vector_head);

    if(new_capacity <= vector->capacity)
    {
        return 1;
    }

    tmp_vector_head = (void*)realloc(vector->vector_head, new_capacity * vector->element_size);
    if(NULL == tmp_vector_head)
    {
        return 1; /* failure */
    }
    vector->vector_head = tmp_vector_head;
    vector->capacity = new_capacity;
    return 0;
}

/* If vector_size*2 is smaller than capacity, shrink capacity to that. */
int VectorShrink(vector_t* vector)
{
    void* tmp_vector_head = NULL;
    size_t new_capacity = MAX(vector->vector_size << 1, MIN_CAPACITY);

    assert(NULL != vector);
    assert(NULL != vector->vector_head);

    if(new_capacity < vector->capacity)
    {
        tmp_vector_head = (void*)realloc(vector->vector_head, new_capacity * vector->element_size);
        if(NULL == tmp_vector_head)
        {
            return 1;
        }
        vector->vector_head = tmp_vector_head;
        vector->capacity = new_capacity;
    }
    return 0;
}
