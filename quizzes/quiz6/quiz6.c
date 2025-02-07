#include <stddef.h>
#include <stdio.h>

size_t NumCoupleSetBitsInByte(unsigned char byte)
{
    size_t i = 0;
    size_t count = 0;
    int is_last_on = 0;

    for(i = 0; i < 8; ++i)
    {
        if(1 == (1 & (byte >> i))) /* met if current iteration bit is on */
        {
            if(1 == is_last_on)
            {
                ++count;
            }
            is_last_on = 1;
        }
        else 
        {
            is_last_on = 0;
        }
    }
    return count;
}

size_t NumSetBitsLong(long num)
{
    size_t count = 0;
    while(0 != num)
    {
        num &= (num - 1);
        ++count;
    }
    return count;
}


int main()
{
    size_t i = 0;
    for(i = 0; i < 9 ;++i) /* check for all numbers from 0 to 8 including */
    {
        printf("num couple set bits in the num %lu is: %lu\n", i, NumCoupleSetBitsInByte(i));
    }

    for(i = 0; i < 9 ;++i) /* check for all numbers from 0 to 8 including */
    {
        printf("num set bits (optimal) in the num %lu is: %lu\n", i, NumSetBitsLong(i));
    }
    return 0;
}