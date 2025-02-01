#include <stdio.h>
#include <string.h>

void function(char ch)
{
    static size_t alphabet[26] = { 0 };
    static size_t i = 0;
    static size_t max_occurance = 0;

    if('0' == ch)
    {
        for(i = 0; i < 25; ++i)
        {
            if(alphabet[i] > max_occurance)
            {
                max_occurance = alphabet[i];
            }
        }
        printf("the char with maximal occurnce occured %lu times\n", max_occurance);
        max_occurance = 0;
        memset(alphabet, 0, 26 * 8);
    }
    else 
    {
        ++alphabet[ch - 'a'];
    }
}

size_t NumSetBitsLong(long num)
{
    size_t count = 0;
    if(0 == num)
    {
        return 0;
    }

    while(0 != num)
    {
        num = (num & (num-1));
        ++count;
    }
    return count;
}