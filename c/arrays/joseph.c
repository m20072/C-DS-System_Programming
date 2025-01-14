#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

size_t findNextAliveIndex(size_t* arr, size_t size, size_t index);
size_t Josephnlogn(size_t size);
size_t Josephn(size_t size);

size_t findNextAliveIndex(size_t* arr, size_t size, size_t index) /* receives the array starting from the point we're at on this moment */
{
    assert(NULL != arr);

    do
    {
        index = (index + 1)%size; /* next soldier */
    } while(0 != arr[index]); /* while didnt get to alive soldier */

    return index;
}

/* Reviewed by Korin o(n*log(n)) */
size_t Josephnlogn(size_t size) /* n, n/2, n/4, n/8, n/16  ~=  n*log(n)*/
{
    int kill = 1;
    size_t current_index = 0;
    size_t next_index = 0;
	size_t* arr = (size_t*)calloc(sizeof(size_t), size); /* calloc because 0 = alive */


    while(1)
    {
        /* start searching from previous killed soldier onwards (nextIndex, not currentIndex) */
        next_index = findNextAliveIndex(arr, size, next_index);

        if(next_index == current_index)
        {
            break;
        }

        if(1 == kill)
        {
			arr[next_index] = 1;
            kill = 0;
        }
        else
        {
            current_index = next_index;
            kill = 1;
        }
    }
    free(arr);
    return current_index;
}


/* Reviewed by Korin o(n) */
size_t Josephn(size_t size)
{
	size_t current_index = 0;
	size_t next_index;
	size_t i;
    
	size_t* arr = (size_t*)malloc(size * sizeof(size_t));

    for(i = 0;i<size-1;++i)
    {
        arr[i] = i + 1;
    }

    arr[size-1] = 0;

    while(arr[current_index] != current_index)
    {
        next_index = arr[current_index]; /* next soldier alive is arr[current_index], so thats the next index */ /* who is next soldier alive */
	arr[current_index] = arr[next_index]; /* change arr[current_index] so that it points to the one that the dying one is pointing to */ /* killing that next soldier */
	current_index = arr[current_index]; /* make the current_index for the next iteration be that soldier that the dying one pointed to */ /* giving the sword to the following one alive */
	
    }
    
    free(arr);
    return current_index;
}


int main()
{
    size_t size = 7;

	printf("for %lu soldiers, last alive is index: %lu\n", size, Josephn(size));
	printf("for %lu soldiers, last alive is index: %lu\n", size, Josephnlogn(size));

    return 0;
}

