/******************************************************************************
* File: vector.h
*
* Purpose:
*   Provides an interface for vector implementation.
*
* Author:
*   Matan Chen
*
* Review History:
*   - Yana
*
******************************************************************************/

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h> /* size_t */

typedef struct vector vector_t;

/* Receives size of element and capacity, returns a pointer to a vector */
vector_t* VectorCreate(size_t element_size, size_t capacity);

/* receives a vector ptr, frees dynamically allocated vector components, and the vector itself */
void VectorDestroy(vector_t* vector);

/* Receives a vector ptr and an index, returns the element in the specified index */
void* VectorAccessElement(const vector_t* vector, size_t index);

/* Receives a vector ptr and an element,
 * pushes the element to the back of the vector.
 * returns  0 = success, 1 = failure */
int VectorPushBack(vector_t* vector, const void* data);

/* Receives a vector ptr, pops the element at the back of the vector, reducing its size.
 * Might shrink capacity based on capacity to size difference */
void VectorPopBack(vector_t* vector);

/* Receives a vector ptr, returns its current capacity */
size_t VectorCapacity(const vector_t* vector);

/* Receives a vector ptr, returns its current size (num of elements) */
size_t VectorSize(const vector_t* vector);

/* Receives a vector ptr and a new capacity value,
 * resizes the vector capacity to hold new_capacity number of elements.
 * returns 0 = success, 1 = failure */
int VectorReserve(vector_t* vector, size_t new_capacity);

/* Receives a vector ptr, shrinks capacity based on the vector size.
 * returns 0 = success, 1 = failure */
int VectorShrink(vector_t* vector);

#endif

