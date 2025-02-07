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

int main()
{
    printf("%d", IsStringRotation("abc", "cab"));
    return 0;
}