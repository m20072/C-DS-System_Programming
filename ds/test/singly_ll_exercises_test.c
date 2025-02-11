/******************************************************************************
* File: singly_ll_ext_test.c
*
* Purpose:
*   Test suite for singly_ll_ext.h
*   
* Author:
*   Shani Zuniga
*
******************************************************************************/

#include <stdio.h> /* printf */
#include <stdlib.h>	/* malloc, free */
#include "../include/singly_ll_exercises.h"

#define BOLD_FORMAT "\x1b[1;38m"
#define PASS_FORMAT	"\x1b[1;36m"
#define FAIL_FORMAT	"\x1b[1;31m"
#define UNFORMAT	"\x1b[1;0m"

static int g_total_checks = 0;
static int g_failed_checks = 0;


/* Function prototypes */
static node_t* CreateTestList(node_t* head, int* values, size_t length);
static void DestroyTestList(node_t* head);

/* Test function prototypes */
static int TestFlip1Item(void);
static int TestFlip2Items(void);
static int TestFlip5Items(void);
static int TestHasLoop(void);
static int TestFindIntersection(void);

/*****************************************************************************/

static node_t* CreateTestList(node_t* head, int* values, size_t length)
{
   size_t i = 0;
   node_t* runner = NULL;

   if (NULL == head)
   {
   	head = (node_t*)malloc(sizeof(node_t));
   	if (NULL == head)
	{
   		return NULL;
	}
	head->data = (void*)&values[0];
   	head->next = NULL;
   	runner = head;

   	for (i = 1; i < length; ++i)
   	{
   		runner->next = (node_t*)malloc(sizeof(node_t));
   		if (NULL == runner->next)
   		{
   			DestroyTestList(head);
   			return NULL;
   		}
   		runner = runner->next;
   		runner->data = (void*)&values[i];
   		runner->next = NULL;
   	}
   }

   return head;
}

static void DestroyTestList(node_t* head)
{
   node_t* current = head;
   node_t* next = NULL;

   while (NULL != current)
   {
   	next = current->next;
   	free(current);
   	current = next;
   }
}

/*****************************************************************************/

static int TestFlip1Item(void)
{
	int status = 0;
	node_t* head = NULL;
	node_t* result = NULL;
	int value = 42;
	
	printf("Testing Flip with 1 item...");
	
	head = CreateTestList(head, &value, 1);
	if (NULL == head)
	{
		printf(FAIL_FORMAT "\t\tFAILED: List creation failed\n" UNFORMAT);
		return 1;
	}
	
	result = Flip(head);
	++g_total_checks;
	if (NULL == result)
	{
		printf(FAIL_FORMAT "\t\tFAILED: Flip returned NULL\n" UNFORMAT);
		++g_failed_checks;
		DestroyTestList(head);
		return 1;
	}
	
	++g_total_checks;
	if (result->data != head->data)
	{
		printf(FAIL_FORMAT "\t\tFAILED: Data was corrupted\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}
	
	++g_total_checks;
	if (NULL != result->next)
	{
		printf(FAIL_FORMAT "\t\tFAILED: Next pointer not NULL\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}
	
	DestroyTestList(result);
	
	if (0 == status)
	{
		printf(PASS_FORMAT "\tPASSED\n" UNFORMAT);
	}
	
	return status;
}

static int TestFlip2Items(void)
{
	int status = 0;
	node_t* head = NULL;
	node_t* result = NULL;
	int values[2] = {1, 2};
	
	printf("Testing Flip with 2 items...");
	
	head = CreateTestList(head, values, 2);
	if (NULL == head)
	{
		printf(FAIL_FORMAT "\t\tFAILED: List creation failed\n" UNFORMAT);
		return 1;
	}
	
	result = Flip(head);
	++g_total_checks;
	if (NULL == result)
	{
		printf(FAIL_FORMAT "\t\tFAILED: Flip returned NULL\n" UNFORMAT);
		DestroyTestList(head);
		++g_failed_checks;
		return 1;
	}
	
	++g_total_checks;
	if (result->data != &values[1] || result->next->data != &values[0])
	{
		printf(FAIL_FORMAT "\t\tFAILED: Incorrect order after flip\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}
	
	++g_total_checks;
	if (NULL != result->next->next)
	{
		printf(FAIL_FORMAT "\t\tFAILED: List termination error\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}
	
	DestroyTestList(result);
	
	if (0 == status)
	{
		printf(PASS_FORMAT "\tPASSED\n" UNFORMAT);
	}
	
	return status;
}

static int TestFlip5Items(void)
{
	int status = 0;
	node_t* head = NULL;
	node_t* result = NULL;
	node_t* current = NULL;
	int values[5] = {1, 2, 3, 4, 5};
	int expected[5] = {5, 4, 3, 2, 1};
	int i = 0;
	
	printf("Testing Flip with 5 items...");
	
	head = CreateTestList(head, values, 5);
	if (NULL == head)
	{
		printf(FAIL_FORMAT "\t\tFAILED: List creation failed\n" UNFORMAT);
		return 1;
	}
	
	result = Flip(head);
	++g_total_checks;
	if (NULL == result)
	{
		printf(FAIL_FORMAT "\t\tFAILED: Flip returned NULL\n" UNFORMAT);
		DestroyTestList(head);
		++g_failed_checks;
		return 1;
	}
	
	current = result;
	for (i = 0; i < 5; ++i)
	{
		++g_total_checks;
		if (current->data != &values[expected[i] - 1])
		{
			printf(FAIL_FORMAT "\t\tFAILED: Wrong order at position %d\n" UNFORMAT, i);
			++g_failed_checks;
			status = 1;
			break;
		}
		current = current->next;
	}
	
	++g_total_checks;
	if (NULL != current)
	{
		printf(FAIL_FORMAT "\t\tFAILED: List termination error\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}
	
	DestroyTestList(result);
	
	if (0 == status)
	{
		printf(PASS_FORMAT "\tPASSED\n" UNFORMAT);
	}
	
	return status;
}

static int TestHasLoop(void)
{
	int status = 0;
	node_t* head = NULL;
	node_t* current = NULL;
	int values[4] = {1, 2, 3, 4};
	
	printf("Testing HasLoop...");
	
	/* test 1: without loop */
	head = CreateTestList(head, values, 4);
	++g_total_checks;
	if (HasLoop(head))
	{
		printf(FAIL_FORMAT "\t\tFAILED: False positive on non-loop list\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}
	
	/* test 2: with loop */
	current = head;
	while (NULL != current->next)
	{
		current = current->next;
	}
	current->next = head->next; /* Create loop to second element */
	
	++g_total_checks;
	if (0 == HasLoop(head))
	{
		printf(FAIL_FORMAT "\t\tFAILED: Failed to detect loop\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}
	
	/* cleanup */
	current->next = NULL; /* breaks loop */
	DestroyTestList(head);
	
	if (0 == status)
	{
		printf(PASS_FORMAT "\t\tPASSED\n" UNFORMAT);
	}
	
	return status;
}

static int TestFindIntersection(void)
{
	int status = 0;
	node_t* head1 = NULL;
	node_t* head2 = NULL;
	node_t* intersection = NULL;
	node_t* result = NULL;
	int values1[3] = {1, 2, 3};
	int values2[2] = {4, 5};
	
	printf("Testing FindIntersection...");
	
	/* test 1: w/o intersection */
	head1 = CreateTestList(head1, values1, 3);
	head2 = CreateTestList(head2, values2, 2);
	
	result = FindIntersection(head1, head2);
	++g_total_checks;
	if (NULL != result)
	{
		printf(FAIL_FORMAT "\t\tFAILED: False positive intersection\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}
	
	/* test 2: create intersectionn */
	intersection = head1->next;
	head2->next = intersection;
	
	result = FindIntersection(head1, head2);
	++g_total_checks;
	if (result != intersection)
	{
		printf(FAIL_FORMAT "\t\tFAILED: Missed intersection point\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}
	
	/* cleanup */
	head2->next = NULL;
	DestroyTestList(head1);
	DestroyTestList(head2);
	
	if (0 == status)
	{
		printf(PASS_FORMAT "\tPASSED\n" UNFORMAT);
	}
	
	return status;
}

/*****************************************************************************/

int main(void)
{	
	int status = 0;

	status |= TestFlip1Item();
	status |= TestFlip2Items();
	status |= TestFlip5Items();
	status |= TestHasLoop();
	status |= TestFindIntersection();

	printf("\n%s ======= Test Summary =======%s\n", BOLD_FORMAT, UNFORMAT);
	printf("┌──────────────────┬─────────┐\n");
	printf("│ Total checks     │ %7d │\n", g_total_checks);
	printf("│ Failed checks    │ %7d │\n", g_failed_checks);
	printf("└──────────────────┴─────────┘\n");
	if (0 == status)
	{
		printf(PASS_FORMAT "\nAll tests completed successfully\n" UNFORMAT);
	}
	else
	{
		printf(FAIL_FORMAT "\nSome tests failed\n" UNFORMAT);
	}
	return 0;
}

