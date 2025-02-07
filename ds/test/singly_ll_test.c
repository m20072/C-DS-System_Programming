/******************************************************************************
* File: singly_ll_test.c
*
* Purpose:
*   Test suite for singly_ll.h
*
* Notes:
*   - <insert notes here>
*   
* Author:
*   Shani Zuniga
*
******************************************************************************/


#include <stdio.h> /* printf */
#include "../include/singly_ll.h"

#define FORMAT		"\x1b[1;36m"
#define UNFORMAT	"\x1b[1;0m"
#define FAIL_FORMAT	"\x1b[1;31m"

static int IsMatch(void* data1, void* data2)
{
	return *(int*)data1 == *(int*)data2;
}

static int AddInt(void* data, void* param)
{
	*(int*)data = *(int*)data + *(int*)param;
	return 0;
}

static int TestListCreateDestroy(void)
{
	slist_t* list = NULL;
	int status = 0;
	
	printf("Testing List Create/Destroy...");
	list = ListCreate();
	
	if (NULL == list)
	{
		printf(FAIL_FORMAT "\n\tFAILED: List creation returned NULL\n" UNFORMAT);
		return 1;
	}
	
	if (0 == ListIsEmpty(list))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected empty list, but got non-empty\n" UNFORMAT);
		status = 1;
	}
	
	if (0 != ListCount(list))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected count 0, but got %lu\n" UNFORMAT, 
			   (unsigned long)ListCount(list));
		status = 1;
	}
	
	ListDestroy(list);
	
	if (0 == status)
	{
		printf(FORMAT "\tPASSED\n" UNFORMAT);
	}
	return status;
}

static int TestListInsertRemove(void)
{
	slist_t* list = NULL;
	slist_itr_t itr = NULL;
	int val1 = 42;
	int val2 = 24;
	int status = 0;
	
	printf("Testing List Insert/Remove...");
	list = ListCreate();
	
	if (NULL == list)
	{
		printf(FAIL_FORMAT "\n\tFAILED: List creation returned NULL\n" UNFORMAT);
		return 1;
	}

	itr = ListItrEnd(list);
	if (NULL == ListInsertBefore(itr, &val1))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Insert before end failed\n" UNFORMAT);
		status = 1;
	}
	
	if (1 != ListCount(list))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected count 1, but got %lu\n" UNFORMAT,
			   (unsigned long)ListCount(list));
		status = 1;
	}
	
	itr = ListItrBegin(list);
	if (NULL == ListInsertBefore(itr, &val2))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Insert before begin failed\n" UNFORMAT);
		status = 1;
	}
	
	if (2 != ListCount(list))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected count 2, but got %lu\n" UNFORMAT,
			   (unsigned long)ListCount(list));
		status = 1;
	}

	itr = ListItrBegin(list);
	itr = ListRemove(itr);
	if (1 != ListCount(list))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected count 1 after remove, but got %lu\n" UNFORMAT,
			   (unsigned long)ListCount(list));
		status = 1;
	}

	itr = ListItrBegin(list);
	itr = ListRemove(itr);
	if (0 != ListCount(list))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected count 0 after remove, but got %lu\n" UNFORMAT,
			   (unsigned long)ListCount(list));
		status = 1;
	}

	ListDestroy(list);
	
	if (0 == status)
	{
		printf(FORMAT "\tPASSED\n" UNFORMAT);
	}
	return status;
}

static int TestListIterators(void)
{
	slist_t* list = NULL;
	slist_itr_t itr1 = NULL;
	slist_itr_t itr2 = NULL;
	int val = 42;
	int status = 0;

	printf("Testing List Iterators...");
	list = ListCreate();
	
	if (NULL == list)
	{
		printf(FAIL_FORMAT "\n\tFAILED: List creation returned NULL\n" UNFORMAT);
		return 1;
	}

	itr1 = ListItrEnd(list);
	if (NULL == ListInsertBefore(itr1, &val))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Insert before end failed\n" UNFORMAT);
		status = 1;
	}

	itr1 = ListItrBegin(list);
	itr2 = ListItrEnd(list);
	if (0 != ListItrIsEqual(itr1, itr2))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Begin and End iterators should not be equal\n" UNFORMAT);
		status = 1;
	}

	itr1 = ListItrNext(itr1);
	if (!ListItrIsEqual(itr1, itr2))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Next of Begin should equal End\n" UNFORMAT);
		status = 1;
	}

	ListDestroy(list);
	
	if (0 == status)
	{
		printf(FORMAT "\tPASSED\n" UNFORMAT);
	}
	return status;
}

static int TestListDataAccess(void)
{
	slist_t* list = NULL;
	slist_itr_t itr = NULL;
	int val1 = 42;
	int val2 = 24;
	int status = 0;

	printf("Testing List Data Access...");
	list = ListCreate();
	
	if (NULL == list)
	{
		printf(FAIL_FORMAT "\n\tFAILED: List creation returned NULL\n" UNFORMAT);
		return 1;
	}

	itr = ListItrEnd(list);
	itr = ListInsertBefore(itr, &val1);
	if (val1 != *(int*)ListGetData(itr))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected data %d, but got %d\n" UNFORMAT,
			   val1, *(int*)ListGetData(itr));
		status = 1;
	}

	ListSetData(itr, &val2);
	if (val2 != *(int*)ListGetData(itr))
	{
		printf(FAIL_FORMAT "\n\tFAILED: After SetData expected %d, but got %d\n" UNFORMAT,
			   val2, *(int*)ListGetData(itr));
		status = 1;
	}
	
	ListDestroy(list);
	
	if (0 == status)
	{
		printf(FORMAT "\tPASSED\n" UNFORMAT);
	}
	return status;
}

static int TestListFind(void)
{
	slist_t* list = NULL;
	slist_itr_t itr = NULL;
	int values[] = {1, 2, 3, 4, 5};
	int target = 3;
	size_t i = 0;
	size_t n_values = 5;
	int status = 0;

	printf("Testing List Find...");
	list = ListCreate();
	
	if (NULL == list)
	{
		printf(FAIL_FORMAT "\n\tFAILED: List creation returned NULL\n" UNFORMAT);
		return 1;
	}

	itr = ListItrEnd(list);
	for (i = 0; i < n_values; ++i)
	{
		itr = ListInsertBefore(itr, &values[i]);
	}

	itr = ListFind(ListItrBegin(list), ListItrEnd(list), IsMatch, &target);
	if (ListItrEnd(list) == itr)
	{
		printf(FAIL_FORMAT "\n\tFAILED: Find returned End iterator for existing value\n" UNFORMAT);
		status = 1;
	}
	
	if (target != *(int*)ListGetData(itr))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Find returned wrong value. Expected %d, got %d\n" UNFORMAT,
			   target, *(int*)ListGetData(itr));
		status = 1;
	}

	ListDestroy(list);
	
	if (0 == status)
	{
		printf(FORMAT "\t\tPASSED\n" UNFORMAT);
	}
	return status;
}

static int TestListForEach(void)
{
	slist_t* list = NULL;
	slist_itr_t itr = NULL;
	int values[] = {1, 2, 3, 4, 5};
	int expected[] = {2, 3, 4, 5, 6};
	int param = 1;
	size_t i = 0;
	size_t n_values = 5;
	int status = 0;

	printf("Testing List ForEach...");
	list = ListCreate();
	
	if (NULL == list)
	{
		printf(FAIL_FORMAT "\n\tFAILED: List creation returned NULL\n" UNFORMAT);
		return 1;
	}

	itr = ListItrEnd(list);
	for (i = 0; i < n_values; ++i)
	{
		itr = ListInsertBefore(itr, &values[i]);
	}

	ListForEach(ListItrBegin(list), ListItrEnd(list), AddInt, &param);

	for (i = 0; i < n_values; ++i)
	{
		if (expected[i] != values[i])
		{
			printf(FAIL_FORMAT "\n\tFAILED: At index %lu, expected %d but got %d\n" UNFORMAT,
				   (unsigned long)i, expected[i], values[i]);
			status = 1;
		}
	}

	ListDestroy(list);
	
	if (0 == status)
	{
		printf(FORMAT "\t\tPASSED\n" UNFORMAT);
	}
	return status;
}

static int TestListAppend(void)
{
	slist_t* list1 = NULL;
	slist_t* list2 = NULL;
	slist_itr_t itr = NULL;
	int values1[] = {1, 2, 3};
	int values2[] = {4, 5, 6};
	int expected[] = {1, 2, 3, 4, 5, 6};
	size_t i = 0;
	int status = 0;

	printf("Testing List Append...");
	list1 = ListCreate();
	list2 = ListCreate();
	
	if (NULL == list1 || NULL == list2)
	{
		printf(FAIL_FORMAT "\n\tFAILED: List creation returned NULL\n" UNFORMAT);
		return 1;
	}

	for (i = 0; i < 3; ++i)
	{
		itr = ListItrEnd(list1);
		itr = ListInsertBefore(itr, &values1[i]);	

		itr = ListItrEnd(list2);
		itr = ListInsertBefore(itr, &values2[i]);
	}

	list1 = ListAppend(list1, list2);
	if (6 != ListCount(list1))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected count 6 after append, but got %lu\n" UNFORMAT,
			   (unsigned long)ListCount(list1));
		status = 1;
	}
	
	if (1 != ListIsEmpty(list2))
	{
		printf(FAIL_FORMAT "\n\tFAILED: List2 should be empty after append\n" UNFORMAT);
		status = 1;
	}
	
	itr = ListItrBegin(list1);
	for (i = 0; i < 6; ++i)
	{
		if (expected[i] != *(int*)ListGetData(itr))
		{
			printf(FAIL_FORMAT "\n\tFAILED: At index %lu, expected %d but got %d\n" UNFORMAT,
				   (unsigned long)i, expected[i], *(int*)ListGetData(itr));
			status = 1;
		}
		itr = ListItrNext(itr);
	}

	ListDestroy(list1);
	ListDestroy(list2);
	
	if (0 == status)
	{
		printf(FORMAT "\t\tPASSED\n" UNFORMAT);
	}
	return status;
}

int main(void)
{	
	int status = 0;
	
	status |= TestListCreateDestroy();
	status |= TestListInsertRemove();
	status |= TestListIterators();
	status |= TestListDataAccess();
	status |= TestListFind();
	status |= TestListForEach();
	status |= TestListAppend();

	if (0 == status)
	{
		printf(FORMAT "\nAll tests completed successfully\n" UNFORMAT);
	}
	else
	{
		printf(FAIL_FORMAT "\nSome tests failed\n" UNFORMAT);
	}
	
	return status;
}
