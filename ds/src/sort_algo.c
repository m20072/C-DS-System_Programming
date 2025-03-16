/******************************************************************************
* File: sort.c
*
* Purpose:
*   implements sort.h
*   
* Author:
*   Matan Chen
*
* Review History:
*   - 
*
******************************************************************************/

#include <stdlib.h> /* calloc, free */
#include <assert.h> /* assert */

#include "../include/sort_algo.h" /* own header */

#define BASE 10
#define DIGIT(num, digit_place) ((num / digit_place) % BASE) 

static void IntSwap(int* a, int* b);
static void RadixCountingSort(int* arr, size_t size, int digit_place);


void BubbleSort(int* arr, size_t size) 
{
    int swap_occured = 0;
    size_t i = 0;
    size_t j = 0;

    assert(NULL != arr);

    --size;
    for (i = 0; i < size; ++i)
    {
        swap_occured = 0;
        for (j = 0; j < size - i; ++j) 
        {
            if (arr[j] > arr[j + 1]) 
            {
                IntSwap(&arr[j], &arr[j + 1]);
                swap_occured = 1;
            }
        }
        if (0 == swap_occured)
            break;
    }
}

void SelectionSort(int* arr, size_t size)
{
    size_t i = 0;
    size_t j = 0;
    size_t smallest_index = 0;
    assert(NULL != arr);
    for(i = 0 ; i < size; ++i)
    {
        smallest_index = i;
        for (j = i + 1; j < size; ++j) /* i + 1 so we dont check at first iteration of nested loop the element against itself */
        {
            if(arr[j] < arr[smallest_index])
            {
                smallest_index = j;
            }
        }
        
        IntSwap(&arr[smallest_index], &arr[i]);
    }

}

void InsertionSort(int* arr, size_t size)
{
    size_t i = 0;
    size_t j = 0;
    int tmp = 0;
    assert(NULL != arr);

    for(i = 1; i < size; ++i)
    {
        tmp = arr[i]; /* likely that arr[i] will be overwritten in the j loop so save it */
        j = i;
        while (j > 0 && arr[j - 1] > tmp)
        {
            arr[j] = arr[j - 1];
            --j;
        }
        arr[j] = tmp;
    }
}



void CountingSort(int* arr, size_t size)
{
    size_t i = 0;
    int largest_num = 0;
    size_t* counting_arr = NULL;
    int* sorted_arr = NULL;
    assert(NULL != arr);

    for(i = 0; i < size; ++i)
    {
        if(largest_num < arr[i])
        {
            largest_num = arr[i];
        }
    }

    /* create a starting indexes array the size of the largest number in the unsorted array */
    counting_arr = (size_t*)calloc((size_t)(1 + largest_num), sizeof(size_t));
    if(NULL == counting_arr)
    {
        return;
    }

    sorted_arr = (int*)calloc(size, sizeof(int));
    if(NULL == sorted_arr)
    {
        free(counting_arr);
        return;
    }

    /* fill the starting indexes array with the number of occurences of each number in the unsorted array in the corresponding index*/
    for(i = 0; i < size; ++i)
    {
        ++counting_arr[arr[i]];
    }

    /* accumilitive addition */
    for(i = 0; i < (size_t)(largest_num); ++i)
    {
        counting_arr[i + 1] += counting_arr[i];
    }

    /* starting indexes array is ready, fill sorted array */
    for(i = size - 1; 0 < i; --i)
    {
        sorted_arr[--counting_arr[arr[i]]] = arr[i];
    }

    sorted_arr[--counting_arr[arr[i]]] = arr[i];

    /* copy sorted elements to original array */
    for(i = 0; i < size; ++i)
    {
        arr[i] = sorted_arr[i];
    }

    free(counting_arr);
    counting_arr = NULL;
    free(sorted_arr);
    sorted_arr = NULL;
}


void RadixSort(int* arr, size_t size)
{
    size_t largest_num = 0;
    size_t digit_place = 1;
    size_t i = 0;

    assert(NULL != arr);

    for(i = 0; i < size; ++i)
    {
        if((int)largest_num < arr[i])
        {
            largest_num = arr[i];
        }
    }

    while((largest_num / digit_place) != 0)
    {
        RadixCountingSort(arr, size, digit_place);
        digit_place *= BASE;
    }


}

static void RadixCountingSort(int* arr, size_t size, int digit_place)
{
    size_t i = 0;
    size_t counting_arr[BASE] = { 0 };
    int* sorted_arr = NULL; 

    sorted_arr = (int*)calloc(size, sizeof(int));
	if (NULL == sorted_arr)
	{
		return;
	}


    /* fill the starting indexes array with the number of occurences of each number in the unsorted array in the corresponding index*/
    for(i = 0; i < size; ++i)
    {
        ++counting_arr[DIGIT(arr[i], digit_place)];
    }

    /* accumilitive addition */
    for(i = 0; i < BASE; ++i)
    {
        counting_arr[i + 1] += counting_arr[i];
    }

    /* starting indexes array is ready, fill sorted array */
    for(i = size - 1; 0 < i; --i)
    {
        sorted_arr[--counting_arr[DIGIT(arr[i], digit_place)]] = arr[i];
    }

    sorted_arr[--counting_arr[DIGIT(arr[i], digit_place)]] = arr[i];

    /* copy sorted elements to original array */
    for(i = 0; i < size; ++i)
    {
        arr[i] = sorted_arr[i];
    }

    free(sorted_arr);
    sorted_arr = NULL;
}

static void IntSwap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}