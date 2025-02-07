#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include "minstack.h"

struct MinStack
{
    stack_ty* stack;
    /* ### If necessary add more data members below this line ### */
    int minValue;
};

minstack_ty* MinStackCreate(size_t capacity)
{
    /* ### Make improvements to the code below as needed ### */
    
    minstack_ty* minstack = (minstack_ty*)malloc(sizeof(minstack_ty));
	if (minstack == NULL)
		return NULL;

	minstack->stack = StackCreate(capacity);
    if(minstack->stack == NULL)
    {
        free(minstack);
        return NULL;
    }
    minstack->minValue = 0;
    return minstack;
}

/* Return the minimum value in the stack */
int MinStackGetMin(minstack_ty* minstack)
{
    return minstack->minValue;
}

int MinStackPush(minstack_ty* minstack, int data)
{
    int valToPush = data;

    assert(minstack != NULL);

    if (StackSize(minstack->stack) == 0)
        minstack->minValue = data;

    else if (data < minstack->minValue)
    {
        valToPush = 2 * data - minstack->minValue;
        minstack->minValue = data;
    }

    return StackPush(minstack->stack, valToPush);
}

void MinStackPop(minstack_ty* minstack)
{
    int top = 0;

    assert(minstack != NULL);

    top = StackPeek(minstack->stack);
    if (top < minstack->minValue)
        minstack->minValue = 2 * minstack->minValue - top;

    StackPop(minstack->stack);
}

