#include <stddef.h>
#include <string.h>
#include <stdio.h>

int IsStringRotation(const char* str1, const char* str2)
{
    size_t i = 0, j = 0, k = 0;
    size_t size = strlen(str1);

    if(size != strlen(str2))
    {
        return -1;
    }

    while(i < size)
    {
        j = i;
        while(str1[j++] == str2[k++])
        {
            if(j == size)
            {
                j = 0;
            }

            if(j == i)
            {
                return i;
            }
        }
        k = 0;
        ++i;

    }
    return -1;
}

#include <stddef.h>
#include <string.h>

int IsStringRotationv2(const char* str1, const char* str2)
{
    /* ### Write your code below this line ### */
    
    size_t str2_len = strlen(str2);
    size_t i = 0, j = 0, k = 0;
    
    if(strlen(str1) != str2_len)
    {
		return (-1);
    }
    
    while(j < str2_len) /* once str2 hits \0 no more to check */
    {
        while(*(str2 + i) == *(str1 + k))
        {
            k = (k + 1)%str2_len;
            ++i;
            if(k == j)
            {
                return (k); /* can return k or j*/
            }
        }
        ++j;
        k = j;
        i = 0;
        
    }
    return (-1);
}

int main()
{
    printf("%d", IsStringRotation("abc", "bca"));
    return 0;
}