/*
*	Writer : Matan Chen
*	Implementation of doubly linked list test
*	
*	 
*
*	Reviewed by: 
*
*/

#include <stdio.h>
#include "../include/doubly_ll.h"


#define BOLD_FORMAT "\x1b[1;38m"
#define PASS_FORMAT	"\x1b[1;36m"
#define FAIL_FORMAT	"\x1b[1;31m"
#define UNFORMAT	"\x1b[1;0m"

/*****************************************************************************/

static int PrintInt(void* data, void* param)
{
    (void)param;
    printf("%d \n", *(int*)data);
    return 1;
}

static int IsMatch(const void* data, const void* param)
{
    return (*(int*)data == *(int*)param);
}


static int TestCreate(void)
{
	int status = 1;
	dlist_t* list = DLLCreate();
	
	if (NULL != list)
	{
		printf(PASS_FORMAT "\t\tPASSED - Create\n" UNFORMAT);
		status = 0;
	}
	
	DLLDestroy(list);
	
	return status;
}

static int TestCountIsEmptyInsert(void)
{
	int status = 1;
	int num = 5;
	dlist_t* list = DLLCreate();
	dlist_itr_t itr = DLLItrEnd(list);
	dlist_itr_t new = NULL;
	
	if (NULL == list)
	{
		printf(PASS_FORMAT "\tFAILED - List\n" UNFORMAT);
		status = 0;
	}
	
	if (1 == DLLIsEmpty(list))
	{
		printf(PASS_FORMAT "\t\tPASSED - Is Empty\n" UNFORMAT);
		status = 0;
	}
	else
	{
		printf(PASS_FORMAT "\tFAILED - Is Empty\n" UNFORMAT);
	}
	
	new = DLLInsertBefore(list , itr , &num);
	
	if (num == *(int*)DLLGetData(new) && (NULL != DLLItrNext(new)))
	{
		printf(PASS_FORMAT "\t\tPASSED - Insert\n" UNFORMAT);
		status = 0;
	}
	
	else
	{
		printf(PASS_FORMAT "\tFAILED - Insert\n" UNFORMAT);
	}
	
	if (1 == DLLCount(list))
	{
		printf(PASS_FORMAT "\t\tPASSED - Count\n" UNFORMAT);
		status = 0;
	}
	
	else
	{
		printf(PASS_FORMAT "\tFAILED - Count\n" UNFORMAT);
	}
	
	DLLRemove(new);
	
	if (0 == DLLCount(list))
	{
		printf(PASS_FORMAT "\t\tPASSED - Remove\n" UNFORMAT);
		status = 0;
	}
	else
	{
		printf(PASS_FORMAT "\t\tFAILED - Remove\n" UNFORMAT);
	}
	
	DLLDestroy(list);
	return status;
}

static int TestBackIsEqual(void)
{
	int status = 1;
	int num = 5 , num2 = 8;
	dlist_t* list = DLLCreate();
	dlist_itr_t new = NULL;
	dlist_itr_t check = NULL;
	
	if (NULL == list)
	{
		printf(PASS_FORMAT "\tFAILED - List\n" UNFORMAT);
		status = 0;
	}
	
	new = DLLPushBack(list, &num2);
	
	if (num2 == *(int*)DLLGetData(new))
	{
		check = DLLItrEnd(list);
		check= DLLItrPrev(check);
		if (1 == DLLItrIsEqual (check , new))
		{
		printf(PASS_FORMAT "\t\tPASSED - PushBack & Equal\n" UNFORMAT);
		status = 0;
		}
	}

	num = *(int*)DLLPopBack(list);
	
	if (0 == DLLCount(list) && (8 == num))
	{
		printf(PASS_FORMAT "\t\tPASSED - PopBack \n" UNFORMAT);
		status = 0;
	}
	
	else
	{
		printf(PASS_FORMAT "\tFAILED - Count\n" UNFORMAT);
	}
	
	DLLDestroy(list);
	return status;
}

static int TestFrontIsEqual(void)
{
	int status = 1;
	int num = 5 , num2 = 8;
	dlist_t* list = DLLCreate();
	dlist_itr_t new = NULL;
	dlist_itr_t check = NULL;
	
	if (NULL == list)
	{
		printf(PASS_FORMAT "\tFAILED - List\n" UNFORMAT);
		status = 0;
	}
	
	new = DLLPushFront(list, &num2);
	
	if (num2 == *(int*)DLLGetData(new))
	{
		check = DLLItrBegin(list);
		if (1 == DLLItrIsEqual (check , new))
		{
		printf(PASS_FORMAT "\t\tPASSED - PushFront & Equal\n" UNFORMAT);
		status = 0;
		}
	}

	num = *(int*)DLLPopFront(list);
	
	if (0 == DLLCount(list) && (8 == num))
	{
		printf(PASS_FORMAT "\t\tPASSED - PopFront \n" UNFORMAT);
		status = 0;
	}
	
	else
	{
		printf(PASS_FORMAT "\tFAILED - Count\n" UNFORMAT);
	}
	
	DLLDestroy(list);
	return status;
}

static int TestForEach(void)
{
    int status = 1;
    int nums[] = {1, 2, 3, 4, 5};
    dlist_t* list = DLLCreate();
    dlist_itr_t begin = NULL;
    dlist_itr_t end = NULL;
    size_t i = 0;
    
    for (i = 0; i < 5; ++i)
    {
        DLLPushBack(list, &nums[i]);
    }
    
    begin = DLLItrBegin(list);
    end = DLLItrEnd(list);
    
    if (1 == DLLForEach(begin, end, PrintInt, NULL))
    {
        printf(PASS_FORMAT "\t\tPASSED - ForEach\n" UNFORMAT);
        status = 0;
    }
    else
    {
        printf(FAIL_FORMAT "\tFAILED - ForEach\n" UNFORMAT);
    }
    
    DLLDestroy(list);
    return status;
}

static int TestSplice(void)
{
    int status = 1;
    int nums1[] = {1, 2, 3};
    int nums2[] = {4, 5, 6};
    dlist_t* list1 = DLLCreate();
    dlist_t* list2 = DLLCreate();
    dlist_itr_t where = NULL;
    dlist_itr_t from = NULL;
    dlist_itr_t to = NULL;
    size_t i = 0;
    
    for (i = 0; i < 3; ++i)
    {
        DLLPushBack(list1, &nums1[i]);
        DLLPushBack(list2, &nums2[i]);
    }
    
    where = DLLItrBegin(list1);
    from = DLLItrBegin(list2);
    to = DLLItrEnd(list2);
    DLLSplice(where, from, to);
    
    if (6 == DLLCount(list1) && 0 == DLLCount(list2))
    {
        printf(PASS_FORMAT "\t\tPASSED - Splice\n" UNFORMAT);
        status = 0;
    }
    else
    {
        printf(FAIL_FORMAT "\tFAILED - Splice\n" UNFORMAT);
    }
    
    DLLDestroy(list1);
    DLLDestroy(list2);
    return status;
}

static int TestFind(void)
{
    int status = 1;
    int nums[] = {1, 2, 3, 4, 5};
    int to_find = 3;
    dlist_t* list = DLLCreate();
    dlist_itr_t begin = NULL;
    dlist_itr_t end = NULL;
    dlist_itr_t found = NULL;
    size_t i = 0;
    
    for (i = 0; i < 5; ++i)
    {
        DLLPushBack(list, &nums[i]);
    }
    
    begin = DLLItrBegin(list);
    end = DLLItrEnd(list);
    
    found = DLLFind(begin, end, IsMatch, &to_find);
    
    if (to_find == *(int*)DLLGetData(found))
    {
        printf(PASS_FORMAT "\t\tPASSED - Find\n" UNFORMAT);
        status = 0;
    }
    else
    {
        printf(FAIL_FORMAT "\tFAILED - Find\n" UNFORMAT);
    }
    
    DLLDestroy(list);
    return status;
}

static int TestMultiFind(void)
{
    int status = 1;
    int nums[] = {1, 3, 2, 3, 4, 3, 5};
    int to_find = 3;
    dlist_t* list = DLLCreate();
    dlist_t* output = DLLCreate();
    dlist_itr_t begin = NULL;
    dlist_itr_t end = NULL;
    size_t i = 0;
    
    for (i = 0; i < 7; ++i)
    {
        DLLPushBack(list, &nums[i]);
    }
    
    begin = DLLItrBegin(list);
    end = DLLItrEnd(list);
    
    if (0 == DLLMultiFind(begin, end, IsMatch, &to_find, output))
    {
        if (3 == DLLCount(output))
        {
            printf(PASS_FORMAT "\t\tPASSED - MultiFind\n" UNFORMAT);
            status = 0;
        }
    }
    else
    {
        printf(FAIL_FORMAT "\tFAILED - MultiFind\n" UNFORMAT);
    }
    
    DLLDestroy(list);
    DLLDestroy(output);
    return status;
}
static int TestSetData(void)
{
    int status = 1;
    int num = 5;
    int new_num = 10;
    dlist_t* list = DLLCreate();
    dlist_itr_t itr = NULL;
    
    itr = DLLPushFront(list, &num);
    DLLSetData(itr, &new_num);
    
    if (new_num == *(int*)DLLGetData(itr))
    {
        printf(PASS_FORMAT "\t\tPASSED - SetData\n" UNFORMAT);
        status = 0;
    }
    else
    {
        printf(FAIL_FORMAT "\tFAILED - SetData\n" UNFORMAT);
    }
    
    DLLDestroy(list);
    return status;
}


int main(void)
{    
    int status = 0;

    status |= TestCreate();
    status |= TestCountIsEmptyInsert();
    status |= TestBackIsEqual();
    status |= TestFrontIsEqual();
    status |= TestForEach();
    status |= TestSplice();
    status |= TestFind();
    status |= TestMultiFind();
    status |= TestSetData();
    
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


