#include <stddef.h>
#include <stdio.h>
#include <assert.h>

int FindNumArray(int num, int* arr, size_t size)
{
    size_t i = 0;
    int product = 1;
    for(i = 0; i < size; ++i)
    {
        product *= (arr[i] - num);
    }
    return (0 == product);
}

int main()
{
    int arr[] = {100, 129, 4, 33, 6, 36};
    assert(FindNumArray(4, arr, 6));
    return 0;
}