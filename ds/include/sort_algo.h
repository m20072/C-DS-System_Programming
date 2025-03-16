/******************************************************************************
* File: filename.h
*
* Purpose:
*   Provides an interface for sort implementation.
*
* Author:
*   Matan Chen
*
* Review History:
*   - 
*
******************************************************************************/

#ifndef __SORT_H__
#define __SORT_H__

#include <stddef.h>

void BubbleSort(int* arr, size_t size);
void SelectionSort(int* arr, size_t size);
void InsertionSort(int* arr, size_t size);
void CountingSort(int* arr, size_t size);
void RadixSort(int* arr, size_t size);

#endif /* __SORT_H__ */
