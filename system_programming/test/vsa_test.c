/*
*	Writer : Matan Chen
*	Implementation of vsa
*	
*	 
*
*	Reviewed by: 
*
*/
#include <stdio.h>  /* For printf */
#include <stdlib.h> /* For malloc */

#include "../include/vsa.h"


#define GREEN "\x1b[1;32m"
#define RED "\x1b[1;31m"
#define UNFORMAT "\x1b[1;0m"


int result = 0;

/* Function Declarations */
void TestVSAInit();
void TestVSAAllocate();
void TestVSALargestBlock();

int main(void)
{
	printf("\n\n");
	TestVSAInit();
	TestVSAAllocate();
	TestVSALargestBlock();
	
	if (0 == result)
	{
    	printf(GREEN "\n🫡🫡🫡🫡 All tests completed successfully 🫡🫡🫡🫡\n\n\n" UNFORMAT);
    }
    
    return (1);
}

void TestVSALargestBlock()
{
	int res = 0;
	void *ptr1, *ptr2, *ptr3, *ptr4, *ptr5;
	size_t memory_size = 100;
	void* memory = malloc (memory_size);
	
	vsa_t* vsa = VSAInit(memory, memory_size);
	
	if (80 != VSALargestBlock(vsa))
	{
		printf(RED "Failed TestVSALargestBlock 0: received largest block of %lu and expected 80\n" UNFORMAT, VSALargestBlock(vsa));
		--res;
	}
	
	ptr1 = VSAAllocate(vsa, 20); /* aligned 24 */
	if (48 != VSALargestBlock(vsa))
	{
		printf(RED "Failed TestVSALargestBlock 1: received largest block of %lu and expected 48\n" UNFORMAT, VSALargestBlock(vsa));
		--res;
	}
	
	ptr2 = VSAAllocate(vsa, 16);
	if (24 != VSALargestBlock(vsa))
	{
		printf(RED "Failed TestVSALargestBlock 2: received largest block of %lu and expected 24\n" UNFORMAT, VSALargestBlock(vsa));
		--res;
	}
	
	ptr3 = VSAAllocate(vsa, 8);
	if (8 != VSALargestBlock(vsa))
	{
		printf(RED "Failed TestVSALargestBlock 3: received largest block of %lu and expected 8\n" UNFORMAT, VSALargestBlock(vsa));
		--res;
	}
	
	ptr4 = VSAAllocate(vsa, 8);
	if (0 != VSALargestBlock(vsa))
	{
		printf(RED "Failed TestVSALargestBlock 4: received largest block of %lu and expected 0\n" UNFORMAT, VSALargestBlock(vsa));
		--res;
	}
	
	VSAFree(ptr2);
	VSAFree(ptr4);
	if (16 != VSALargestBlock(vsa))
	{
		printf(RED "Failed TestVSALargestBlock 5: received largest block of %lu and expected 16\n" UNFORMAT, VSALargestBlock(vsa));
		--res;
	}
	
	VSAFree(ptr3);
	if (48 != VSALargestBlock(vsa))
	{
		printf(RED "Failed TestVSALargestBlock 6: received largest block of %lu and expected 48\n" UNFORMAT, VSALargestBlock(vsa));
		--res;
	}
	
	
	if (res == 0)
	{
		printf(GREEN "PASSED TestVSALargestBlock test!\n" UNFORMAT);
	}
	
	result -= res;
	free (memory);
	
}

void TestVSAAllocate()
{
	int res = 0;
	void *ptr1, *ptr2, *ptr3, *ptr4, *ptr5;
	size_t memory_size = 100;
	void* memory = malloc (memory_size);
	
	vsa_t* vsa = VSAInit(memory, memory_size); /* 80 */
	
	ptr1 = VSAAllocate(vsa, 100);  /* still 80 */
	if (NULL != ptr1)
	{
		printf(RED "Failed TestVSAAllocate 0: received allocation of %ld and expected NULL\n" UNFORMAT, *(long*) ((char*) ptr1 - 8));
		--res;
	}
	
	ptr1 = VSAAllocate(vsa, 10);
	if (*(long*) ((char*) ptr1 - 8) != -16)
	{
		printf(RED "Failed TestVSAAllocate 1: received allocation of %ld and expected -16\n" UNFORMAT, *(long*) ((char*) ptr1 - 8));
		--res;
	}
	
	ptr2 = VSAAllocate(vsa, 58);
	if (NULL != ptr2)
	{
		printf(RED "Failed TestVSAAllocate 2: received allocation of %ld and expected NULL (not enough of space)\n" UNFORMAT, *(long*) ((char*) ptr2 - 8));
		--res;
	}
	
	ptr2 = VSAAllocate(vsa, 24);
	if (*(long*) ((char*) ptr2 - 8) != -24)
	{
		printf(RED "Failed TestVSAAllocate 3: received allocation of %ld and expected -24\n" UNFORMAT, *(long*) ((char*) ptr2 - 8));
		--res;
	}
	
	ptr3 = VSAAllocate(vsa, 8);
	if (*(long*) ((char*) ptr3 - 8) != -8)
	{
		printf(RED "Failed TestVSAAllocate 4: received allocation of %ld and expected -8\n" UNFORMAT, *(long*) ((char*) ptr3 - 8));
		--res;
	}
	
	ptr4 = VSAAllocate(vsa, 8);
	if (*(long*) ((char*) ptr4 - 8) != -8)
	{
		printf(RED "Failed TestVSAAllocate 5: received allocation of %ld and expected -8\n" UNFORMAT, *(long*) ((char*) ptr4 - 8));
		--res;
	}
	
	ptr5 = VSAAllocate(vsa, 8);
	if (NULL != ptr5)
	{
		printf(RED "Failed TestVSAAllocate 6: received allocation of %ld and expected NULL\n" UNFORMAT, *(long*) ((char*) ptr5 - 8));
		--res;
	}

	VSAFree(ptr2);
	VSAFree(ptr3);

	ptr5 = VSAAllocate(vsa, 32);
	if (*(long*) ((char*) ptr5 - 8) != -32)
	{
		printf(RED "Failed TestVSAAllocate 6: received allocation of %ld and expected -32\n" UNFORMAT, *(long*) ((char*) ptr5 - 8));
		--res;
	}

	if (res == 0)
	{
		printf(GREEN "PASSED TestVSAAllocate test!\n" UNFORMAT);
	}

	result -= res;
	free (memory);
}

void TestVSAInit()
{
	int res = 0;
	size_t memory_size = 100;
	void* memory = malloc (memory_size);
	
	vsa_t* vsa = VSAInit(memory, memory_size);
	
	if (NULL == vsa)
	{
		printf(RED "Failed TestVSAInit: received NULL during init\n" UNFORMAT);
		--res;
	}
	
	if (VSALargestBlock(vsa) != 80)
	{
		printf(RED "Failed TestVSAInit: received largetest block %lu, expected 80\n" UNFORMAT, VSALargestBlock(vsa));
		--res;
	}
	
	if (res == 0)
	{
		printf(GREEN "PASSED TestVSAInit test!\n" UNFORMAT);
	}
	
	result -= res;
	free (memory);
}
