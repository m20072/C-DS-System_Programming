/******************************************************************************
* File: stack.h
*
* Purpose:
*   Provides an interface for stack implementation.
*
* Author:
*   Matan Chen
*
* Review History:
*   - Daniel
*
******************************************************************************/


#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h> /* size_t */

typedef struct stack stack_t;

/* Returns a pointer to a dynamically allocated stack of maximal size capacity, each element size is element_size */
stack_t* Create(size_t capacity, size_t element_size);

/* Frees dynamically allocated stack components, and the stack itself */
void Destroy(stack_t* stk);

/* Pushes an element onto the top of the stack */
void Push(stack_t* stk, const void* val);

/* Pops an element from the top of the stack */
void Pop(stack_t* stk);

/* Returns the current element on the top of the stack */
void* Peek(const stack_t* stk);

/* Returns 1 if the stack is empty, otherwise returns 0 */
int IsEmpty(const stack_t* stk);

/* Returns the current number of elements in the stack */
size_t Size(const stack_t* stk);

/* Returns the maximal elements capacity of the stack */
size_t Capacity(const stack_t* stk);

#endif
