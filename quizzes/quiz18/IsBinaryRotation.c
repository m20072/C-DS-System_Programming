#include <stddef.h>
typedef unsigned long ulong_t;

int IsBinaryRotation(ulong_t a, ulong_t b)
{
    /* ### Write your code below this line ### */
	size_t i = 0;
    size_t bits = sizeof(ulong_t) * 8;
    
    for(i = 0; i < bits; ++i)
    {
        b = ((b << i) | (b >> (bits-i)));
    	if(a == b)
        {
            break;
        }
    }
    return (a == b);
}