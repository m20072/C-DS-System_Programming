/******************************************************************************
* File: singly_ll_exercises.c
*
* Purpose:
*   implements singly_ll_exercises.h
*   
* Author:
*   Matan Chen
*
* Review History:
*   - 
*
******************************************************************************/
#include <stdlib.h> /* Dynamic allocations */
#include "../include/singly_ll_exercises.h"

/* Reverses the order of a given slist. */
node_t* Flip(node_t* head)
{
	node_t* prev_tmp = NULL;
	node_t* next_tmp = NULL;

	while(NULL != head)
	{
		next_tmp = head->next; /* saving what head points to so that we can move to next node even when we change this node next */
		head->next = prev_tmp; /* making head->next point to NULL (reversing) */
		prev_tmp = head; /* now prev can be utilized for next iteration as current's iterations head */
		head = next_tmp; /* next iteration head is next_tmp */
	}
	return (prev_tmp);
}

/* Tells whether a given slist has loop. */
int HasLoop(const node_t* head)
{
	const node_t* fast = head;
	const node_t* slow = head;

	if(NULL == head) /* empty list has no loop */
	{
		return (0);	
	}

	while(NULL != fast->next && NULL != fast->next->next)
	{
		fast = fast->next->next;
		slow = slow->next;
		if(fast == slow)
		{
			return (1);
		}
	}
	return (0);
}

/* Returns a pointer to a first node mutual to both slists, if any. */
node_t* FindIntersection(node_t* head_1, node_t* head_2)
{
	node_t* runner_1 = head_1;
	node_t* runner_2 = head_2;

	if(NULL == head_1 || NULL == head_2) /* empty list on either means no mutual nodes */
	{
		return NULL;
	}

	while(runner_1 != runner_2) /* once they meet, its the mutual node, OR both are NULL, meaning no mutual node */
	{
		runner_1 = (NULL != runner_1) ? runner_1->next : head_2;
		runner_2 = (NULL != runner_2) ? runner_2->next : head_1;
	}
	return (runner_1);
}