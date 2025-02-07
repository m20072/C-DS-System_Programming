#include <stddef.h>

typedef struct Result
{
    size_t start_index;
    size_t end_index;
    int sum;
} result_ty;

result_ty MaxSubArray(const int numbers[], size_t size)
{
    result_ty result = {0, 0, 0};
    
    /* ### Write your code below this line ### */
	int current_sum = 0;
    size_t i = 0;
    size_t start = 0;
    
    
    for(i = 0; i < size; ++i)
    {
        if(numbers[i] > (current_sum + numbers[i]))
        {
            start = i;
            current_sum = numbers[i];
        }
        else
        {
            current_sum = current_sum + numbers[i]; /* start_index remains same */
        }
        
        if(current_sum > result.sum)
        {
            	result.start_index = start;
            	result.end_index = i;
            	result.sum = current_sum;
        }
    }
    return result;
}
