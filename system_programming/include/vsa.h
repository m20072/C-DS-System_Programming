/******************************************************************************
* File: vsa.h
*
* Purpose:
*   Provides an interface for vsa implementation.
*
* Author:
*   Matan Chen
*
* Review History:
*   - 
*
******************************************************************************/

#ifndef __VSA_H__
#define __VSA_H__

#include <stddef.h>

typedef struct vsa vsa_t;

/*******************************************************************************/
/* Function: VSAInit
 * Purpose: Initializes a variable-size allocator (VSA) in a given memory region.
 * Receives: memory - Pointer to the allocated memory region.
 *           memory_size - Size of the allocated memory region in bytes.
 * Returns: A pointer to the initialized VSA, or NULL on failure.
 * Complexity: O(1).
 */
vsa_t* VSAInit(void* memory, size_t memory_size);
/*******************************************************************************/

/*******************************************************************************/
/* Function: VSAAllocate
 * Purpose: Allocates a block of memory of the requested size from the VSA.
 * Receives: vsa - Pointer to the variable-size allocator.
 *           memory_size - Size of the block to allocate in bytes.
 * Returns: A pointer to the allocated block, or NULL if no sufficient space is available.
 * Complexity: O(n).
 */
void* VSAAllocate(vsa_t* vsa, size_t memory_size);
/*******************************************************************************/

/*******************************************************************************/
/* Function: VSALargestBlock
 * Purpose: Finds the largest contiguous free block available in the VSA.
 * Receives: vsa - Pointer to the variable-size allocator.
 * Returns: The size of the largest available block in bytes.
 * Complexity: O(n).
 */
size_t VSALargestBlock(vsa_t* vsa);
/*******************************************************************************/

/*******************************************************************************/
/* Function: VSAFree
 * Purpose: Frees a previously allocated block back to the VSA.
 * Receives: block - Pointer to the block to be freed.
 * Returns: None.
 * Complexity: O(1).
 */
void VSAFree(void* block);
/*******************************************************************************/

#endif /* __VSA_H__ */
