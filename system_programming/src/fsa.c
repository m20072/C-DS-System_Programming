/******************************************************************************
* File: fsa.c
*
* Purpose:
*   implements fsa.h
*   
* Author:
*   Matan Chen
*
* Review History:
*   - 
*
******************************************************************************/
#include <assert.h> /* assert */
#include "../include/fsa.h" /* own header */

#define FSA_SIZE (sizeof(struct fsa))
#define META_SIZE (sizeof(size_t))
#define WORD_SIZE (sizeof(size_t))
/*at least meta size blocks (incase meta size is bigger than word size), and word size aligned */
#define ALIGN_SIZE(block_size) \
    (((block_size > META_SIZE ? (block_size) : META_SIZE) + \
    (WORD_SIZE - 1)) & ~(WORD_SIZE - 1))

struct fsa
{
    size_t block_header;
};

size_t FSASuggestSize(size_t block_size, size_t num_blocks)
{
    return (FSA_SIZE + (ALIGN_SIZE(block_size) * num_blocks)); /* fsa struct and word size aligned blocks of meta data size at least */
}

fsa_t* FSAInit(void* memory, size_t memory_size, size_t block_size)
{
	fsa_t* fsa = (fsa_t*)memory;
    size_t total_blocks = 0;
    size_t* block_runner = NULL;
    size_t i = 0;
    block_size = ALIGN_SIZE(block_size);
    total_blocks = ((memory_size - FSA_SIZE) / block_size);

    assert(NULL != memory);

    if(0 == block_size || memory_size < block_size)
    {
        return NULL;
    }

    fsa->block_header = FSA_SIZE;
    block_runner = (size_t*)((char*)memory + fsa->block_header);
    
    for(i = 1; i < total_blocks; ++i)
    {
        *block_runner = FSA_SIZE + (block_size * i);
        block_runner = (size_t*)((char*)block_runner + block_size);
    }

    *block_runner = (size_t)0;
    return (fsa);
}

void* FSAAllocate(fsa_t* fsa)
{
	size_t* free_block = NULL;

    assert(NULL != fsa);
    free_block = (size_t*)((char*)fsa + fsa->block_header);
	
	if (0 == fsa->block_header) /* no free blocks */
	{
		return (NULL);
	}
	fsa->block_header = *free_block;
	return (free_block);
}

size_t FSACountFree(fsa_t* fsa)
{
    size_t count = 0;
    size_t* block_runner = NULL;

    assert(NULL != fsa);
    block_runner = (size_t*)((char*)fsa + fsa->block_header);

    while(0 != *block_runner)
    {
        block_runner = (size_t*)((char*)fsa + *block_runner);
        ++count;
    }
    return (++count);
}

void FSAFree(fsa_t* fsa, void* block)
{
    assert(NULL != fsa);
    if(NULL == block)
    {
        return;
    }

	*(size_t*)block = fsa->block_header;
	fsa->block_header = (size_t)block - (size_t)fsa;
}