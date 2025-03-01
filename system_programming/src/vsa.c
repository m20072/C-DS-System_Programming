/******************************************************************************
* File: vsa.c
*
* Purpose:
*   implements vsa.h
*   
* Author:
*   Matan Chen
*
* Review History:
*   - 
*
******************************************************************************/
#include  <assert.h>
#include "../include/vsa.h"
struct vsa
{
    long block_size;
};

#define ABS(num) ((num < 0) ? -num : num)
#define META_SIZE (sizeof(vsa_t))
#define WORD_SIZE (sizeof(size_t))
#define UPPER_ALIGN_SIZE(size) ((size + (WORD_SIZE - 1)) & ~(WORD_SIZE - 1))
#define LOWER_ALIGN_SIZE(size) (size & ~(WORD_SIZE - 1))
#define NEXT_BLOCK(current_block) ((vsa_t*)((char*)current_block + META_SIZE + ABS(current_block->block_size)))

vsa_t* VSAInit(void* memory, size_t memory_size)
{
    vsa_t* vsa = (vsa_t*)memory;
    
    assert(NULL != memory);
    memory_size = LOWER_ALIGN_SIZE(memory_size);
    if(memory_size <= 2 * META_SIZE)
    {
        return (NULL);
    }
    vsa->block_size = memory_size - 2 * META_SIZE; /* first block meta-data */
    ((vsa_t*)((char*)vsa + memory_size - META_SIZE))->block_size = 0; /* end block meta-data */
    return (vsa);
}

void* VSAAllocate(vsa_t* vsa, size_t memory_size)
{
    long aligned_size = UPPER_ALIGN_SIZE(memory_size);
    vsa_t* current_block = vsa;
    vsa_t* next_block = NULL;
    vsa_t* new_block = NULL;

    assert(NULL != vsa);

    next_block = NEXT_BLOCK(current_block);

    /* defrag (if possible) until found large enough block (first fit) or until reached end */
    while((current_block->block_size < aligned_size) && (0 != current_block->block_size))
    {
        /* if current and next blocks are free, merge blocks */
        if((0 < current_block->block_size) && (0 < next_block->block_size))
        {
            current_block->block_size += META_SIZE + next_block->block_size;
        }
        else  /* current block and/or next block are not free to merge, go to next block. */
        {
            current_block = next_block;
        }
        next_block = NEXT_BLOCK(current_block);
    }

    /* didn't find large enough block (reached end) return NULL */
    if(0 == current_block->block_size)
    {
        return NULL;
    }

    /* found large enough block */
    /* edge case where block is exactly the size needed or one meta_size larger, don't write new meta-data, and dont change current_block size, just flip sign */
    if((current_block->block_size == aligned_size) || (current_block->block_size == aligned_size - (long)META_SIZE))
    {
        current_block->block_size = -current_block->block_size;
        return ((char*)current_block + META_SIZE);
    }

    /* block is larger than size needed by more than meta_size, create a new meta-data with the left-over size */
    new_block = (vsa_t*)((char*)current_block + META_SIZE + aligned_size);
    new_block->block_size = current_block->block_size - aligned_size - META_SIZE;
    current_block->block_size = -aligned_size;
    return ((char*)current_block + META_SIZE);
}

size_t VSALargestBlock(vsa_t* vsa)
{
    long largest = 0;
    vsa_t* current_block = vsa;
    vsa_t* next_block = NULL;

    assert(NULL != vsa);
    
    /* find largest free block and defrag on the go */
    while(0 != current_block->block_size)
    {
        next_block = NEXT_BLOCK(current_block);

        /* if current and next blocks are free, merge. */
        if(0 < current_block->block_size && 0 < next_block->block_size)
        {
            current_block->block_size += META_SIZE + next_block->block_size;
        }
        else /* current block and/or next block are not free to merge, update largest and go to next block. */
        {
            if(largest < current_block->block_size)
            {
                largest = current_block->block_size;
            }
            current_block = NEXT_BLOCK(current_block);
        }
    }
    return largest;
}

void VSAFree(void* block)
{
    vsa_t* meta_ptr = (vsa_t*)((char*)block - META_SIZE);
    if(NULL == block)
    {
        return;
    }
    meta_ptr->block_size *= -1;
}