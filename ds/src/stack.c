/******************************************************************************
* File: stack.c
*
* Purpose:
*   implements stack.h
*   
* Author:
*   Matan Chen
*
* Review History:
*   - Daniel
*
******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/stack.h"

/* Management structure */
struct stack
{
	size_t capacity;
	size_t size;
	void* data;   
	size_t element_size;
};

/* Allocates memory for the stack struct and its data */
stack_t* Create(size_t capacity, size_t element_size)
{
	stack_t* stack = (stack_t*)malloc(sizeof(stack_t));
	if(NULL == stack)
	{
		return NULL;
	}
	
	stack->data = (void*)malloc(element_size * capacity);
	if(NULL == stack->data)
	{
		return NULL;
	}
	
	stack->capacity = capacity;
	stack->size = 0;
	stack->element_size = element_size;
	return stack;
}

/* Frees dynamically allocated memory */
void Destroy(stack_t* stk)
{
	assert(NULL != stk);
	free(stk->data);
	free(stk);
}

/* user checks if possible to push using size and capacity functions */
void Push(stack_t* stk, const void* val)
{
	assert(NULL != stk);
	memcpy((char*)stk->data + stk->size * stk->element_size, val, stk->element_size);
	++stk->size;
}

/* simply overwrite when add another element */
void Pop(stack_t* stk)
{
	assert(NULL != stk);
	--stk->size;
}

/* Returns the element at the top of the stack */
void* Peek(const stack_t* stk)
{
	assert(NULL != stk);
	return ((char*)stk->data + (stk->size - 1) * stk->element_size);
}
/* Checks if the stack is empty */
int IsEmpty(const stack_t* stk)
{
	assert(NULL != stk);
	return (0 == stk->size);
}

/* Returns the number of elements in the struct */
size_t Size(const stack_t* stk)
{
	assert(NULL != stk);
	return (stk->size);
}

/* Returns the maximal capacity of the stack */
size_t Capacity(const stack_t* stk)
{
	assert(NULL != stk);
	return (stk->capacity);	
}
