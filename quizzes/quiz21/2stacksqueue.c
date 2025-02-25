#include <stddef.h>
#include <stdlib.h>

#include "queue_os.h"
#include "stack.h"

struct Queue
{
    stack_ty* stack1;
    stack_ty* stack2;
};

queue_ty* QueueCreate(size_t capacity)
{
    /* ### Make improvements to the code below as needed ### */

    queue_ty* queue = malloc(sizeof(*queue));
	if (queue == NULL)
		return (NULL);

	queue->stack1 = StackCreate(capacity);
    if(NULL == queue->stack1)
    {
        free(queue);
        return (NULL);
    }
		
    queue->stack2 = StackCreate(capacity);
    if(NULL == queue->stack2)
    {
        free(queue->stack1);
        queue->stack1 = NULL;
        free(queue);
    	return (NULL);
    }
    
    
    return (queue);
}

void QueueDestroy(queue_ty* queue)
{
    free(queue->stack1);
    queue->stack1 = NULL;
    free(queue->stack2);
    queue->stack2 = NULL;
    free(queue);
}

void QueueEnqueue(queue_ty* queue, int data)
{
    StackPush(queue->stack1, data);
}

int QueueDequeue(queue_ty* queue)
{
    int tmp = 0;
    while(1 != StackSize(queue->stack1))
    {
        StackPush(queue->stack2, StackPeek(queue->stack1));
        StackPop(queue->stack1);
    }
   
    tmp = StackPeek(queue->stack1);
    StackPop(queue->stack1);
      
    while(0 != StackSize(queue->stack2))
	{
        StackPush(queue->stack1, StackPeek(queue->stack2));
		StackPop(queue->stack2);
    }
    return (tmp);
}

int QueueIsEmpty(queue_ty* queue)
{
    if(0 == StackSize(queue->stack1))
    {
       return (1);
    }
    return (0);
}

