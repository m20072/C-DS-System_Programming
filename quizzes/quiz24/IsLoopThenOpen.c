#include <stddef.h>

typedef struct SllNode
{
    struct SllNode* next;
    int data;
} sll_node_ty;

sll_node_ty* IsLoopThenOpen(sll_node_ty* head)
{
    /* ### Write your code below this line ### */
    sll_node_ty* slow_runner = head;
    sll_node_ty* fast_runner = head;
    
    if(NULL == head)
    {
        return (NULL);
    }
    
    while(NULL != fast_runner->next && NULL != fast_runner->next->next)
    {
        fast_runner = fast_runner->next->next;
        slow_runner = slow_runner->next;
        
        /* if met, there is a loop */
        if(fast_runner == slow_runner)
        {
            /* Find the start of the loop */
            slow_runner = head;
            
			while (slow_runner->next != fast_runner->next)
            {
                slow_runner = slow_runner->next;
                fast_runner = fast_runner->next;
            }
            fast_runner->next = NULL;
            return fast_runner;
        }
    }

    return (NULL);
}
