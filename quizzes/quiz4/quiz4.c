#include <stddef.h>

typedef struct Result
{
    size_t index_1;
    size_t index_2;
} result_ty;

result_ty TwoElementsSum(const int numbers[], size_t size, int sum)
{
    /* ### Write your code below this line ### */
    const int* p_end = numbers + (size - 1); /* points to last element in the array*/
    const int* p_start = numbers;
    int tmp_sum;
    result_ty result /* { ... } */;
    
    while(numbers < p_end)
    {
        tmp_sum = *numbers + *p_end;
        
        if(tmp_sum > sum)
        {
            --p_end;
            continue;
        }
        
        if(tmp_sum < sum)
        {
            ++numbers;
            continue;
        }
        
        break; /* tmp_sum == sum */
    }
    result.index_1 = numbers - p_start;
    result.index_2 = p_end - p_start;

    return result;
}
