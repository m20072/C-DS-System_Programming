#include <assert.h>
#include <stdio.h>

size_t findNextAliveIndex(size_t* arr, size_t size, size_t index);
size_t Josephnlogn(size_t* arr, size_t size);
size_t Josephn(size_t* arr, size_t size);

size_t findNextAliveIndex(size_t* arr, size_t size, size_t index) /* receives the array starting from the point we're at on this moment */
{
    assert(NULL != arr);

    do
    {
        index = (index + 1)%size;
    } while(0 != arr[index]); /* while didnt get to alive soldier */

    return index;
}

size_t Josephnlogn(size_t* arr, size_t size) /* n, n/2, n/4, n/8, n/16  ~=  n*log(n)*/
{
    int kill = 1;
    size_t current_index = 0;
    size_t next_index = 0;
    size_t i;

    assert(NULL != arr);

    for(i = 0;i<size;++i)
    {
        arr[i] = 0; /* 0 = alive */
    }

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
    return current_index;
}

size_t Josephn(size_t* arr, size_t size)
{
    int kill = 1;
    size_t current_index = 0;
    size_t next_index;
    size_t i;

    assert(NULL != arr);

    for(i = 0;i<size;++i)
    {
        arr[i] = i + 1;
    }

    arr[size-1] = 0;

    while(arr[current_index] != current_index)
    {
        next_index = arr[current_index];

        if(1 == kill)
        {
            arr[current_index] = arr[next_index]; /* arr[currentIndex] points to the alive soldier that the dying one points to */
            kill = 0;
        }
        else
        {
            current_index = arr[current_index];
            kill = 1;
        }
    }
    return current_index;
}


int main()
{
    size_t size = 7;
    size_t soldiers[7];

    printf("for %lu soldiers, last alive is index: %lu\n", size, Josephnlogn(soldiers, size));

    return 0;
}

