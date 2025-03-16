/*
*	Writer : Matan Chen
*	Implementation of sort test
*	
*	 
*
*	Reviewed by: 
*
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "../include/sort_algo.h"

static void TestCompareSortAlgo(void (*sort_func)(int*, size_t));
static int IsSorted(int* arr, size_t size);
static void TestCompareAlgos();
static void TestCountingSort();
static void TestRadixSort();

int main(void)
{
	srand(time(NULL));
	TestCompareAlgos();
	printf("\n");
	TestCountingSort();
	printf("\n");
	TestRadixSort();
	return 0;
}

static void TestCompareAlgos()
{
	printf("Testing Bubble Sort:\n");
	TestCompareSortAlgo(&BubbleSort);
	
	printf("\nTesting Selection Sort:\n");
	TestCompareSortAlgo(&SelectionSort);

	printf("\nTesting Insertion Sort:\n");
	TestCompareSortAlgo(&InsertionSort);
}

static void TestCountingSort()
{
	int arr[5000];
	size_t i = 0;
	for(i = 0; i < 5000; ++i)
	{
		arr[i] = (rand() % 100) + 1;
	}

	printf("Testing Counting Sort:\n");
	printf("Before sort, IsSorted: %d\n", IsSorted(arr, 5000));
	CountingSort(arr, 5000);
	printf("After sort, IsSorted: %d\n", IsSorted(arr, 5000));
}

static void TestRadixSort()
{
	int arr[5000];
	size_t i = 0;
	for(i = 0; i < 5000; ++i)
	{
		arr[i] = (rand() % 9000000) + 1000000;
	}

	printf("Testing Radix Sort:\n");
	printf("Before sort, IsSorted: %d\n", IsSorted(arr, 5000));
	RadixSort(arr, 5000);
	printf("After sort, IsSorted: %d\n", IsSorted(arr, 5000));
}

static void TestCompareSortAlgo(void (*sort_func)(int*, size_t))
{
	int arr[5000];
	size_t i = 0;
	for(i = 0; i < 5000; ++i)
	{
		arr[i] = rand();
	}
	
	printf("Before sort, IsSorted: %d\n", IsSorted(arr, 5000));
	sort_func(arr, 5000);
	printf("After sort, IsSorted: %d\n", IsSorted(arr, 5000));

}

static int IsSorted(int* arr, size_t size)
{
	size_t i = 0;
	--size;
	for(i = 0; i < size; ++i)
	{
		if(arr[i + 1] < arr[i])
		{
			return (0);
		}
	}
	return (1);
}