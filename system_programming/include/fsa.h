/******************************************************************************
* File: fsa.h
*
* Purpose:
*   Provides an interface for fsa implementation.
*
* Author:
*   Matan Chen
*
* Review History:
*   - 
*
******************************************************************************/

#ifndef __FSA_H__
#define __FSA_H__

#include <stddef.h> /* size_t */

typedef struct fsa fsa_t;

/*******************************************************************************/
/* Function: FSASuggestSize
 * Purpose: Calculates the required memory size for an FSA given block size and count.
 * Receives: block_size - Size of each block in bytes.
 *           num_blocks - Number of blocks required.
 * Returns: The total suggested memory size in bytes.
 * Complexity: O(1).
 */
size_t FSASuggestSize(size_t block_size, size_t num_blocks);
/*******************************************************************************/

/*******************************************************************************/
/* Function: FSAInit
 * Purpose: Initializes a fixed-size allocator (FSA) in a given memory region.
 * Receives: memory - Pointer to the allocated memory region.
 *           memory_size - Size of the allocated memory region in bytes.
 *           block_size - Size of each block in bytes.
 * Returns: A pointer to the initialized FSA, or NULL on failure.
 * Complexity: O(n).
 */
fsa_t* FSAInit(void* memory, size_t memory_size, size_t block_size);
/*******************************************************************************/

/*******************************************************************************/
/* Function: FSAAllocate
 * Purpose: Allocates a fixed size block of memory from the FSA.
 * Receives: fsa - Pointer to the fixed-size allocator.
 * Returns: A pointer to the allocated block, or NULL if no blocks are available.
 * Complexity: O(1).
 */
void* FSAAllocate(fsa_t* fsa);
/*******************************************************************************/

/*******************************************************************************/
/* Function: FSACountFree
 * Purpose: Counts the number of free blocks available in the FSA.
 * Receives: fsa - Pointer to the fixed-size allocator.
 * Returns: The number of available blocks.
 * Complexity: O(n).
 */
size_t FSACountFree(fsa_t* fsa);
/*******************************************************************************/

/*******************************************************************************/
/* Function: FSAFree
 * Purpose: Frees a previously allocated block back to the FSA.
 * Receives: fsa - Pointer to the fixed-size allocator.
 *           block - Pointer to the block to be freed.
 * Returns: None.
 * Complexity: O(1).
 */
void FSAFree(fsa_t* fsa, void* block);
/*******************************************************************************/

#endif /* __FSA_H__ */
