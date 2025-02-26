#include <stdio.h>  /* For printf */
#include <stdlib.h> /* For malloc, free */

#include "../include/fsa.h"



#define GREEN "\x1b[1;32m"
#define RED "\x1b[1;31m"
#define UNFORMAT "\x1b[1;0m"

int result = 0;

/* Function Declarations */
void TestFSASuggestSize();
void TestFSAInit();
void TestFSAAllocate();
void TestFSAFree();
void TestFSACountFree();
void TestMemoryIntegrity();

int main(void)
{
    TestFSASuggestSize();
    TestFSAInit();
    TestFSAAllocate();
    TestFSAFree();
    TestFSACountFree();
    TestMemoryIntegrity();

	if (0 == result)
	{
    	printf(GREEN "\n🫡🫡🫡🫡 All tests completed successfully 🫡🫡🫡🫡\n" UNFORMAT);
    }
    
    return (0);
}

/* Test FSASuggestSize function */
void TestFSASuggestSize()
{
    size_t actual_size = FSASuggestSize(16, 10);

    if (actual_size != 168)
    {
        printf(RED "FSASuggestSize FAILED: Expected 168, Got %lu\n" UNFORMAT, actual_size);
        --result;
    }
    
    actual_size = FSASuggestSize(15, 10);
    
    if (actual_size != 168)
    {
        printf(RED "FSASuggestSize FAILED: Expected 168, Got %lu\n" UNFORMAT, actual_size);
        --result;
    }
    
    actual_size = FSASuggestSize(1, 10);
    
    if (actual_size != 88)
    {
        printf(RED "FSASuggestSize FAILED: Expected 88, Got %lu\n" UNFORMAT, actual_size);
        --result;
    }
    
    printf(GREEN "FSASuggestSize PASSED\n" UNFORMAT);
}

/* Test FSAInit function */
void TestFSAInit()
{
    size_t block_size = 16;
    size_t num_blocks = 10;
    size_t expected_value;
    size_t* current_block;
    size_t suggested_size = FSASuggestSize(block_size, num_blocks);
    void* memory = malloc(suggested_size);
    fsa_t* fsa = FSAInit(memory, suggested_size, block_size);

    if (NULL == fsa)
    {
        printf(RED "FSAInit FAILED: Returned NULL\n" UNFORMAT);
        --result;
    }
    else
    {
		expected_value = 8 + 16;
		current_block = (size_t*)((char*)memory + 8);
		
		while (expected_value + 16 < suggested_size)
		{
	  		if (*current_block != expected_value)
	  		{
	  			printf(RED "FSAInit FAILED: Expected %lu, Got %lu\n" UNFORMAT, expected_value, *current_block);
	  			--result;
	  			break;
			}
			
		    current_block = (size_t*)((char*)memory + expected_value);
		    expected_value += 16;
		}
		    printf(GREEN "FSAInit PASSED\n" UNFORMAT);
    }

    free(memory);
}


/* Test FSAAllocate function */
void TestFSAAllocate()
{
    size_t block_size = 16;
    size_t num_blocks = 3;
    size_t suggested_size = FSASuggestSize(block_size, num_blocks);
    void* memory = malloc(suggested_size);
    fsa_t* fsa = FSAInit(memory, suggested_size, block_size);
    void* block1 = NULL;
    void* block2 = NULL;
    void* block3 = NULL;
    void* block4 = NULL;

    block1 = FSAAllocate(fsa);
    block2 = FSAAllocate(fsa);
    block3 = FSAAllocate(fsa);
    block4 = FSAAllocate(fsa); /* Should return NULL */

    if (block1 == NULL || block2 == NULL || block3 == NULL)
    {
        printf(RED "FSAAllocate FAILED: One or more blocks could not be allocated\n" UNFORMAT);
        --result;
    }
    else
    {
        printf(GREEN "FSAAllocate PASSED\n" UNFORMAT);
    }

    if (block4 != NULL)
    {
        printf(RED "FSAAllocate FAILED: Allocated more blocks than available\n" UNFORMAT);
        --result;
    }
    else
    {
        printf(GREEN "FSAAllocate correctly returned NULL when full\n" UNFORMAT);
    }

    free(memory);
}

/* Test FSAFree function */
void TestFSAFree()
{
    size_t block_size = 16;
    size_t num_blocks = 3;
    size_t suggested_size = FSASuggestSize(block_size, num_blocks);
    void* memory = malloc(suggested_size);
    fsa_t* fsa = FSAInit(memory, suggested_size, block_size);

    void* block1 = FSAAllocate(fsa);
    void* block2 = FSAAllocate(fsa);
    
    
    *(size_t*) block1 = 97;
    *(size_t*) block2 = 99;
    
    if (*(size_t*) block2 != 99)
    {
    	printf(RED "FSAFree FAILED: couldn't write to block2\n" UNFORMAT);
    	--result;
	}
	
    FSAFree(fsa, block2);
    block2 = FSAAllocate(fsa);
    
    if(*(size_t*)block2 != 40)
    {
    	printf(RED "FSAFree FAILED: Problem with free\n" UNFORMAT);
    	--result;
	}
	else
	{
		printf(GREEN "FSAFree PASSED\n" UNFORMAT);
	}
	
    free(memory);
}

/* Test FSACountFree function */
void TestFSACountFree()
{
	void* block1 = NULL;
	void* block2 = NULL;
    size_t block_size = 16;
    size_t num_blocks = 3;
    size_t suggested_size = FSASuggestSize(block_size, num_blocks);
    void* memory = malloc(suggested_size);
    fsa_t* fsa = FSAInit(memory, suggested_size, block_size);

    if (FSACountFree(fsa) != num_blocks)
    {
        printf(RED "FSACountFree FAILED: Expected %lu, Got %lu\n" UNFORMAT, 
               num_blocks, FSACountFree(fsa));
        --result;
    }
    else
    {
        printf(GREEN "FSACountFree PASSED (initial state)\n" UNFORMAT);
    }

    block1 = FSAAllocate(fsa);
    block2 = FSAAllocate(fsa);

    if (FSACountFree(fsa) != 1)
    {
        printf(RED "FSACountFree FAILED after 2 allocations: Expected 1, Got %lu\n" UNFORMAT, 
               FSACountFree(fsa));
        --result;
    }
    else
    {
        printf(GREEN "FSACountFree PASSED after 2 allocations\n" UNFORMAT);
    }

    FSAFree(fsa, block1);
    FSAFree(fsa, block2);

    if (FSACountFree(fsa) != 3)
    {
        printf(RED "FSACountFree FAILED after freeing: Expected 3, Got %lu\n" UNFORMAT, 
               FSACountFree(fsa));
        --result;
    }
    else
    {
        printf(GREEN "FSACountFree PASSED after freeing all blocks\n" UNFORMAT);
    }

    free(memory);
}

/* Test Memory Integrity (write and read back values) */
void TestMemoryIntegrity()
{
	int* block4 = NULL;
    size_t block_size = sizeof(int);
    size_t num_blocks = 5;
    size_t suggested_size = FSASuggestSize(block_size, num_blocks);
    void* memory = malloc(suggested_size);
    fsa_t* fsa = FSAInit(memory, suggested_size, block_size);

    int* block1 = (int*)FSAAllocate(fsa);
    int* block2 = (int*)FSAAllocate(fsa);
    int* block3 = (int*)FSAAllocate(fsa);

    *block1 = 100;
    *block2 = 200;
    *block3 = 300;

    if (*block1 != 100 || *block2 != 200 || *block3 != 300)
    {
        printf(RED "Memory Integrity Test FAILED: Incorrect values after writing\n" UNFORMAT);
        --result;
    }
    else
    {
        printf(GREEN "Memory Integrity Test PASSED\n" UNFORMAT);
    }

    FSAFree(fsa, block2);
    block4 = (int*)FSAAllocate(fsa); /* Should reuse block2 */

    *block4 = 400; /* Overwrite */

    if (*block1 != 100 || *block3 != 300 || *block4 != 400)
    {
        printf(RED "Memory Integrity Test FAILED after reallocation\n" UNFORMAT);
        --result;
    }
    else
    {
        printf(GREEN "Memory Integrity Test PASSED after reallocation\n" UNFORMAT);
    }

    free(memory);
}
