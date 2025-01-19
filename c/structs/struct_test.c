/******************************************************************************
* File: struct_test.c
*
* Purpose:
*   Test suite for struct.h functions providing verification of functionality
*	of struct.c which implements elements to hold polymorphic datatypes.
*
* Notes:
*   - tests element creation, int addition, printing, and cleanup
*   
* Author:
*   Shani Zuniga
*
******************************************************************************/

#include <stdio.h>						/* printf */
#include <assert.h>                     /* assert macro */
#include "struct.h"                     /* functions to test */

#define SIZE 10 						/* test array size */

void TestCreateArray(mixed_data_t* array)
{
	assert(SUCCESS == InitInt(array + 0, 0));
	assert(SUCCESS == InitInt(array + 1, 1));
	assert(SUCCESS == InitInt(array + 2, 2));
	assert(SUCCESS == InitInt(array + 3, -3));
	assert(SUCCESS == InitFloat(array + 4, 4.0));
	assert(SUCCESS == InitFloat(array + 5, 5.0));
	assert(SUCCESS == InitFloat(array + 6, -6.0));
	assert(SUCCESS == InitString(array + 7, "7"));
	assert(SUCCESS == InitString(array + 8, "8"));
	assert(SUCCESS == InitString(array + 9, "9"));
}

void TestPrintArray(mixed_data_t* array)
{
	size_t i = 0;
	
	printf("[ ");
	for (i = 0; i < SIZE; ++i)
	{
		assert(0 == array[i].print(array + i));
		printf(", ");
	}
	printf("]\n");
}

void TestAddIntToArray(mixed_data_t* array)
{
	size_t i = 0;
	
	for (i = 0; i < SIZE; ++i)
	{
		assert(0 == array[i].add_int(array + i, 10));
	}
	for (i = 0; i < SIZE; ++i)
	{
		assert(0 == array[i].add_int(array + i, -1));
	}
}

void TestCleanArray(mixed_data_t* array)
{
	size_t i = 0;
	
	for (i = 0; i < SIZE; ++i)
	{
		assert(0 == array[i].clean_up(array + i));
	}
}

int main(void)
{
	mixed_data_t array[SIZE];
	
	printf("Beginning struct.c tests...\n\n");
	
	TestCreateArray(array);
	TestPrintArray(array);
	TestAddIntToArray(array);
	TestPrintArray(array);
	TestCleanArray(array);

	printf("\nAll tests completed successfully\n");
	return 0;
}

